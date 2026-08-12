#!/usr/bin/env python3
"""Prepare a pinned OpenTTD tree for the PixelRAM WebAssembly backend."""

from __future__ import annotations

import shutil
import sys
from pathlib import Path


def replace_once(path: Path, old: str, new: str, label: str) -> None:
    text = path.read_text()
    if old not in text:
        raise SystemExit(f"Could not find {label} in {path}")
    path.write_text(text.replace(old, new, 1))


def main() -> None:
    if len(sys.argv) != 3:
        raise SystemExit("usage: prepare.py OPENTTD_SOURCE PIXELRAM_ROOT")

    source = Path(sys.argv[1]).resolve()
    pixelram = Path(sys.argv[2]).resolve()
    port = pixelram / "ports" / "openttd"
    video = source / "src" / "video"
    embedded = video / "pixelram"
    embedded.mkdir(parents=True, exist_ok=True)

    shutil.copy2(port / "pixelram_v.cpp", video / "pixelram_v.cpp")
    shutil.copy2(port / "pixelram_v.h", video / "pixelram_v.h")
    shutil.copy2(pixelram / "pixelram.c", embedded / "pixelram.c")
    shutil.copy2(pixelram / "pixelram.h", embedded / "pixelram.h")
    shutil.copy2(pixelram / "shell.html", source / "os" / "emscripten" / "pixelram_shell.html")

    replace_once(
        video / "CMakeLists.txt",
        "if(NOT OPTION_DEDICATED)\n",
        "if(NOT OPTION_DEDICATED)\n"
        "    add_files(\n"
        "        pixelram_v.cpp\n"
        "        pixelram_v.h\n"
        "        pixelram/pixelram.h\n"
        "        CONDITION EMSCRIPTEN AND OPENTTD_PIXELRAM\n"
        "    )\n\n",
        "video source list",
    )

    replace_once(
        source / "CMakeLists.txt",
        "project(${BINARY_NAME}\n    VERSION 15.3\n    LANGUAGES CXX\n)\n",
        "project(${BINARY_NAME}\n    VERSION 15.3\n    LANGUAGES CXX\n)\n\n"
        "if(OPENTTD_PIXELRAM)\n"
        "    enable_language(C)\n"
        "endif()\n",
        "project declaration",
    )

    replace_once(
        source / "CMakeLists.txt",
        "    # Allow heap-growth, and start with a bigger memory size.\n",
        "    if(OPENTTD_PIXELRAM)\n"
        "        add_library(pixelram_runtime STATIC\n"
        "            ${CMAKE_SOURCE_DIR}/src/video/pixelram/pixelram.c\n"
        "        )\n"
        "        target_include_directories(pixelram_runtime PRIVATE\n"
        "            ${CMAKE_SOURCE_DIR}/src/video/pixelram\n"
        "        )\n"
        "        target_compile_definitions(pixelram_runtime PRIVATE PLATFORM_WEB)\n"
        "        target_include_directories(openttd_lib PRIVATE\n"
        "            ${CMAKE_SOURCE_DIR}/src/video/pixelram\n"
        "        )\n"
        "        target_link_libraries(openttd_lib pixelram_runtime)\n"
        "        target_link_libraries(WASM::WASM INTERFACE \"-lraylib\")\n"
        "        target_link_libraries(WASM::WASM INTERFACE \"-sUSE_GLFW=3\")\n"
        "        target_link_libraries(WASM::WASM INTERFACE \"-sASYNCIFY\")\n"
        "        if(OPENTTD_PIXELRAM_BASESET_DIR)\n"
        "            target_link_libraries(WASM::WASM INTERFACE \"--preload-file ${OPENTTD_PIXELRAM_BASESET_DIR}@/baseset\")\n"
        "        endif()\n"
        "    endif()\n\n"
        "    # Allow heap-growth, and start with a bigger memory size.\n",
        "PixelRAM Emscripten flags",
    )

    replace_once(
        source / "CMakeLists.txt",
        "    target_link_libraries(WASM::WASM INTERFACE \"--shell-file ${CMAKE_SOURCE_DIR}/os/emscripten/shell.html\")\n",
        "    if(OPENTTD_PIXELRAM)\n"
        "        target_link_libraries(WASM::WASM INTERFACE \"--shell-file ${CMAKE_SOURCE_DIR}/os/emscripten/pixelram_shell.html\")\n"
        "    else()\n"
        "        target_link_libraries(WASM::WASM INTERFACE \"--shell-file ${CMAKE_SOURCE_DIR}/os/emscripten/shell.html\")\n"
        "    endif()\n",
        "Emscripten shell",
    )

    # OpenTTD ships the Emscripten liblzma port it expects, but upstream's
    # FindLibLZMA.cmake assumes it was copied into the emsdk installation.
    # Emscripten also supports external ports by path, so keep the workspace
    # image generic and point CMake at OpenTTD's own pinned port definition.
    lzma_cmake = source / "os" / "emscripten" / "cmake" / "FindLibLZMA.cmake"
    lzma_text = lzma_cmake.read_text()
    bundled_port = "--use-port=contrib.liblzma"
    external_port = "--use-port=${CMAKE_SOURCE_DIR}/os/emscripten/ports/liblzma.py"
    if lzma_text.count(bundled_port) != 3:
        raise SystemExit(
            "Expected three contrib.liblzma references in OpenTTD FindLibLZMA.cmake"
        )
    lzma_cmake.write_text(lzma_text.replace(bundled_port, external_port))

    replace_once(
        source / "os" / "emscripten" / "pre.js",
        "Module.arguments.push('-mnull', '-snull', '-vsdl');",
        "Module.arguments = Module.arguments || [];\n"
        "Module.preRun = Module.preRun || [];\n"
        "Module.arguments.push('-mnull', '-snull', '-vpixelram', '-b32bpp-anim');",
        "Emscripten driver arguments",
    )

    print("OpenTTD prepared: PixelRAM video/input backend")


if __name__ == "__main__":
    main()
