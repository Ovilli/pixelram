#!/usr/bin/env python3
"""Prepare a pinned OpenCrystalCaves checkout for the PixelRAM web port."""

from __future__ import annotations

import sys
from pathlib import Path


def replace_once(path: Path, old: str, new: str) -> None:
    text = path.read_text()
    count = text.count(old)
    if count != 1:
        raise RuntimeError(f"expected one match in {path} for {old!r}, found {count}")
    path.write_text(text.replace(old, new, 1))


def wrap_between(path: Path, start: str, end: str, prefix: str, suffix: str) -> None:
    text = path.read_text()
    a = text.find(start)
    b = text.find(end, a + len(start))
    if a < 0 or b < 0:
        raise RuntimeError(f"could not find patch anchors in {path}: {start!r} .. {end!r}")
    body = text[a:b]
    path.write_text(text[:a] + prefix + body + suffix + text[b:])


def main() -> int:
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} OPENCRYSTALCAVES_ROOT PIXELRAM_ROOT", file=sys.stderr)
        return 2

    root = Path(sys.argv[1]).resolve()
    pixelram_root = Path(sys.argv[2]).resolve()
    if not (root / "occ" / "CMakeLists.txt").is_file():
        raise RuntimeError(f"not an OpenCrystalCaves checkout: {root}")
    if not (pixelram_root / "pixelram.h").is_file():
        raise RuntimeError(f"not a PixelRAM checkout: {pixelram_root}")

    cmake = root / "occ" / "CMakeLists.txt"
    replace_once(
        cmake,
        "project(occ)\n",
        '''project(occ)\n\noption(PIXELRAM "Build OpenCrystalCaves for PixelRAM" OFF)\nif(PIXELRAM)\n  if(NOT EMSCRIPTEN)\n    message(FATAL_ERROR "The PixelRAM OpenCrystalCaves port requires Emscripten")\n  endif()\n  if(NOT PIXELRAM_ROOT)\n    message(FATAL_ERROR "PIXELRAM_ROOT must point at the PixelRAM checkout")\n  endif()\n  add_compile_definitions(PIXELRAM)\nendif()\n''',
    )
    replace_once(cmake, "if(UNIX AND NOT APPLE)\n", "if(UNIX AND NOT APPLE AND NOT EMSCRIPTEN)\n")
    replace_once(
        cmake,
        "find_package(SDL2 CONFIG REQUIRED)\nfind_package(SDL2_mixer CONFIG REQUIRED)\n",
        '''if(NOT PIXELRAM)\n  find_package(SDL2 CONFIG REQUIRED)\n  find_package(SDL2_mixer CONFIG REQUIRED)\nendif()\n''',
    )
    wrap_between(
        cmake,
        'add_subdirectory("image_viewer")',
        "# install/package",
        "if(NOT PIXELRAM)\n",
        "endif()\n\n",
    )
    replace_once(cmake, "# install/package\n", "if(NOT PIXELRAM)\n# install/package\n")
    cmake.write_text(cmake.read_text().rstrip() + "\nendif()  # NOT PIXELRAM packaging\n")

    wrapper_cmake = root / "occ" / "sdl_wrapper" / "CMakeLists.txt"
    original_wrapper = wrapper_cmake.read_text()
    wrapper_cmake.write_text(
        '''project(sdl_wrapper)\n\nif(PIXELRAM)\n  add_library(sdl_wrapper\n    "export/event.h"\n    "export/graphics.h"\n    "export/sdl_wrapper.h"\n    "${PIXELRAM_ROOT}/ports/crystal/event_pixelram.cc"\n    "${PIXELRAM_ROOT}/ports/crystal/graphics_pixelram.cc"\n    "${PIXELRAM_ROOT}/ports/crystal/sdl_wrapper_pixelram.cc"\n  )\n  target_include_directories(sdl_wrapper PUBLIC\n    "export"\n    "${PIXELRAM_ROOT}"\n  )\n  target_include_directories(sdl_wrapper PRIVATE\n    "src"\n  )\nelse()\n'''
        + original_wrapper
        + "endif()\n"
    )

    occ_cmake = root / "occ" / "occ" / "CMakeLists.txt"
    replace_once(
        occ_cmake,
        '''target_link_libraries(occ\n  "utils"\n  "sdl_wrapper"\n  "game"\n  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>\n  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>\n  $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>\n)\n''',
        '''if(PIXELRAM)\n  target_sources(occ PRIVATE "${PIXELRAM_ROOT}/pixelram.c")\n  target_include_directories(occ PRIVATE "${PIXELRAM_ROOT}")\n  target_compile_definitions(occ PRIVATE PLATFORM_WEB)\n  target_link_libraries(occ\n    "utils"\n    "sdl_wrapper"\n    "game"\n    raylib\n  )\n  set_target_properties(occ PROPERTIES OUTPUT_NAME "crystal" SUFFIX ".html")\nelse()\n  target_link_libraries(occ\n    "utils"\n    "sdl_wrapper"\n    "game"\n    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>\n    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>\n    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>\n  )\nendif()\n''',
    )

    player_state_cc = root / "occ" / "game" / "src" / "player_state.cc"
    replace_once(
        player_state_cc,
        '#include <cfgpath.h>\n',
        '''#ifndef PIXELRAM\n#include <cfgpath.h>\n#else\n#include <cstdio>\n#define MAX_PATH 512\nstatic void get_user_config_file(char* out, unsigned int maxlen, const char* appname)\n{\n  (void)appname;\n  std::snprintf(out, maxlen, "/OpenCrystalCaves.conf");\n}\n#endif\n''',
    )

    state_h = root / "occ" / "occ" / "src" / "state.h"
    replace_once(
        state_h,
        "  LevelId level_ = LevelId::FINALE;\n",
        "  LevelId level_ = LevelId::INTRO;\n",
    )

    state_cc = root / "occ" / "occ" / "src" / "state.cc"
    replace_once(
        state_cc,
        '''#ifdef _MSC_VER\n#define OS_NAME "Windows"\n#elif defined(__APPLE__)\n#define OS_NAME "macOS"\n#else\n#define OS_NAME "Linux"\n#endif\n''',
        '''#ifdef PIXELRAM\n#define OS_NAME "Browser"\n#elif defined(_MSC_VER)\n#define OS_NAME "Windows"\n#elif defined(__APPLE__)\n#define OS_NAME "macOS"\n#else\n#define OS_NAME "Linux"\n#endif\n''',
    )

    utils_h = root / "occ" / "occ" / "src" / "utils.h"
    replace_once(
        utils_h,
        '''// The size of the game camera after scaling - this should be based on the (dynamic) window size in the future\nstatic constexpr geometry::Size CAMERA_SIZE_SCALED = CAMERA_SIZE_STRETCHED * 3.0f;\n''',
        '''// The browser shell performs the final scaling for PixelRAM, so keep OCC's\n// logical framebuffer small. Native OCC retains its traditional 3x window.\n#ifdef PIXELRAM\nstatic constexpr geometry::Size CAMERA_SIZE_SCALED = CAMERA_SIZE_STRETCHED;\n#else\nstatic constexpr geometry::Size CAMERA_SIZE_SCALED = CAMERA_SIZE_STRETCHED * 3.0f;\n#endif\n''',
    )

    path_cc = root / "occ" / "utils" / "src" / "path.cc"
    replace_once(path_cc, '#include <find_steam_game.h>\n', '#ifndef PIXELRAM\n#include <find_steam_game.h>\n#endif\n')
    replace_once(
        path_cc,
        '''  char buf[4096];\n  // Try steam\n''',
        '''#ifndef PIXELRAM\n  char buf[4096];\n  // Try steam\n''',
    )
    replace_once(
        path_cc,
        '''  // Try media (contains shareware episode)\n''',
        '''#endif\n  // Try media (contains shareware episode)\n''',
    )

    misc_cc = root / "occ" / "utils" / "src" / "misc.cc"
    replace_once(
        misc_cc,
        '#include <cstdlib>\n',
        '''#include <cstdlib>\n\n#ifdef PIXELRAM\n#include <emscripten/emscripten.h>\nEM_JS(void, pixelram_occ_open_url, (const char* url), {\n  const value = UTF8ToString(url);\n  window.open(value, "_blank", "noopener");\n});\n#endif\n''',
    )
    replace_once(
        misc_cc,
        '''#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)\n''',
        '''#ifdef PIXELRAM\n  pixelram_occ_open_url(url.c_str());\n#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)\n''',
    )

    print("OpenCrystalCaves prepared for PixelRAM")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
