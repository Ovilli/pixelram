#!/usr/bin/env python3

from pathlib import Path
import shutil
import sys


def replace_once(text, old, new, label):
    if new in text:
        return text

    count = text.count(old)

    if count != 1:
        raise RuntimeError(
            f"{label}: expected anchor exactly once, found {count}"
        )

    return text.replace(old, new, 1)


def replace_function(text, signature, replacement, label):
    if replacement in text:
        return text

    start = text.find(signature)
    if start < 0:
        raise RuntimeError(f"{label}: signature not found")

    brace = text.find("{", start)
    if brace < 0:
        raise RuntimeError(f"{label}: opening brace not found")

    depth = 0
    end = None

    for pos in range(brace, len(text)):
        if text[pos] == "{":
            depth += 1
        elif text[pos] == "}":
            depth -= 1
            if depth == 0:
                end = pos + 1
                break

    if end is None:
        raise RuntimeError(f"{label}: closing brace not found")

    return text[:start] + replacement + text[end:]


def wrap_function_for_web(
    text,
    signature,
    web_body,
    label
):
    start = text.find(signature)

    if start < 0:
        raise RuntimeError(
            f"{label}: signature not found"
        )

    brace = text.find("{", start)

    if brace < 0:
        raise RuntimeError(
            f"{label}: opening brace not found"
        )

    depth = 0
    end = None

    for pos in range(brace, len(text)):
        if text[pos] == "{":
            depth += 1
        elif text[pos] == "}":
            depth -= 1

            if depth == 0:
                end = pos + 1
                break

    if end is None:
        raise RuntimeError(
            f"{label}: closing brace not found"
        )

    function = text[start:end]

    if "#ifdef __EMSCRIPTEN__" in function:
        return text

    prefix = text[start:brace + 1]
    native_body = text[brace + 1:end - 1]

    replacement = (
        prefix
        + "\n#ifdef __EMSCRIPTEN__\n"
        + web_body.rstrip()
        + "\n#else"
        + native_body
        + "\n#endif\n}"
    )

    return (
        text[:start]
        + replacement
        + text[end:]
    )


def main():
    if len(sys.argv) != 3:
        raise SystemExit(
            "usage: prepare_chocolatedescent.py "
            "CHOCOLATEDESCENT_DIR PIXELRAM_PROJECT_DIR"
        )

    source = Path(sys.argv[1]).resolve()
    project = Path(sys.argv[2]).resolve()

    if not (source / "CMakeLists.txt").exists():
        raise SystemExit(f"Not a ChocolateDescent checkout: {source}")

    port = project / "ports" / "descent"
    target = source / "platform" / "pixelram"
    target.mkdir(parents=True, exist_ok=True)

    for name in (
        "gr_pixelram.cpp",
        "mouse_pixelram.cpp",
        "audio_openal.cpp",
        "midi_tsf.cpp",
        "midi_tsf.h",
    ):
        shutil.copy2(port / name, target / name)

    for name in ("pixelram.c", "pixelram.h", "shell.html"):
        shutil.copy2(project / name, target / name)

    music_assets = project / ".cache" / "descent-music"
    tsf_header = music_assets / "tsf.h"
    soundfont = music_assets / "TimGM6mb.sf2"

    if not tsf_header.exists():
        raise RuntimeError(
            "Missing .cache/descent-music/tsf.h; run make descent-music"
        )

    if not soundfont.exists():
        raise RuntimeError(
            "Missing .cache/descent-music/TimGM6mb.sf2; run make descent-music"
        )

    shutil.copy2(
        tsf_header,
        target / "tsf.h"
    )

    shutil.copy2(
        soundfont,
        source / "TimGM6mb.sf2"
    )

    # --------------------------------------------------------------
    # CMake
    # --------------------------------------------------------------

    cmake_path = source / "CMakeLists.txt"
    cmake = cmake_path.read_text()

    pixelram_sources = '''set(PIXELRAM_SOURCES
    platform/pixelram/gr_pixelram.cpp
    platform/pixelram/mouse_pixelram.cpp
    platform/pixelram/audio_openal.cpp
    platform/pixelram/midi_tsf.cpp
    platform/pixelram/pixelram.c
)

'''

    if "set(PIXELRAM_SOURCES" not in cmake:
        cmake = replace_once(
            cmake,
            "set(SDL_SOURCES\n",
            pixelram_sources + "set(SDL_SOURCES\n",
            "CMake PixelRAM source list"
        )

    enable_pixelram = '''include_directories(.)
if (EMSCRIPTEN)
    add_definitions(-DUSE_VGA)
    set(SHARED_SOURCES ${SHARED_SOURCES} ${PIXELRAM_SOURCES})
endif()
'''

    if "-DUSE_VGA" not in cmake:
        cmake = replace_once(
            cmake,
            "include_directories(.)\n",
            enable_pixelram,
            "CMake PixelRAM backend"
        )

    pthread_old = "\tadd_link_options(-pthread)\n"
    pthread_new = '''    if (NOT EMSCRIPTEN)
        add_link_options(-pthread)
    endif()
'''

    if pthread_old in cmake and "if (NOT EMSCRIPTEN)" not in cmake:
        cmake = cmake.replace(pthread_old, pthread_new, 1)

    cmake = cmake.replace(
        "elseif(UNIX)\n",
        "elseif(UNIX OR EMSCRIPTEN)\n"
    )

    wasm_block = r'''
# ----------------------------------------------------------------------
# Hackschule PixelRAM / Emscripten
# ----------------------------------------------------------------------
if (EMSCRIPTEN)
    target_include_directories(
        ChocolateDescent
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/platform/pixelram"
        
    )

    target_link_libraries(
        ChocolateDescent
        raylib
        openal
    )

    target_compile_definitions(
        ChocolateDescent
        PRIVATE
        PLATFORM_WEB
    )

    target_compile_options(
        ChocolateDescent
        PRIVATE
        -O2
    )

    target_link_options(
        ChocolateDescent
        PRIVATE
        "SHELL:-sUSE_GLFW=3"
        "SHELL:-sASYNCIFY"
        "SHELL:-sALLOW_MEMORY_GROWTH=1"
        "SHELL:-sSTACK_SIZE=8388608"
        "SHELL:-sASSERTIONS=1"
        "SHELL:-sSTACK_OVERFLOW_CHECK=1"
        "SHELL:-sFORCE_FILESYSTEM"
        "SHELL:-sSINGLE_FILE=1"
        "SHELL:-sSINGLE_FILE_BINARY_ENCODE=0"
        "SHELL:--shell-file ${CMAKE_CURRENT_SOURCE_DIR}/platform/pixelram/shell.html"
        "SHELL:--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/descent.hog@/descent.hog"
        "SHELL:--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/descent.pig@/descent.pig"
        "SHELL:--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/TimGM6mb.sf2@/TimGM6mb.sf2"
    )

    set_target_properties(
        ChocolateDescent
        PROPERTIES
        OUTPUT_NAME "descent"
        SUFFIX ".html"
    )
endif()
'''

    if "Hackschule PixelRAM / Emscripten" not in cmake:
        cmake += wasm_block

    cmake_path.write_text(cmake)

    # --------------------------------------------------------------
    # main(): sound effects on, music/joystick off.
    # --------------------------------------------------------------

    main_path = source / "platform" / "unix" / "unixmain.cpp"
    main_text = main_path.read_text()

    main_text = main_text.replace(
        '#include "SDL.h" //[ISB] required for main replacement macro\n',
        ""
    )

    web_main = '''int main(int argc, char** argv) //[ISB] oops, must be called with c linkage...
{
#ifdef __EMSCRIPTEN__
    const char* web_argv[] = {
        argv[0],
        "-nojoystick"
    };

    return D_DescentMain(
        2,
        web_argv
    );
#else
    return D_DescentMain(
        argc,
        (const char**)argv
    );
#endif
}
'''

    main_text = replace_function(
        main_text,
        "int main(int argc, char** argv)",
        web_main,
        "unixmain.cpp main"
    )

    main_path.write_text(main_text)

    # --------------------------------------------------------------
    # Safe argv copy/lowercase for web.
    # --------------------------------------------------------------

    args_path = source / "misc" / "args.cpp"
    args_text = args_path.read_text()

    args_new = '''void InitArgs(int argc, const char** argv)
{
\tint i;

\tNum_args = 0;

#ifdef __EMSCRIPTEN__
\tfor (i = 0; i < argc && Num_args < 100; i++)
\t{
\t\tconst char* src = argv[i] ? argv[i] : "";
\t\tsize_t length = strlen(src);
\t\tchar* copy = (char*)malloc(length + 1);

\t\tif (!copy)
\t\t\tabort();

\t\tmemcpy(copy, src, length + 1);
\t\tArgs[Num_args++] = copy;
\t}

\tfor (i = 0; i < Num_args; i++)
\t{
\t\tif (Args[i][0] == '/')
\t\t\tArgs[i][0] = '-';

\t\tif (Args[i][0] == '-')
\t\t{
\t\t\tfor (char* p = Args[i]; *p; ++p)
\t\t\t{
\t\t\t\tif (*p >= 'A' && *p <= 'Z')
\t\t\t\t\t*p = (char)(*p - 'A' + 'a');
\t\t\t}
\t\t}
\t}
#else
\tfor (i = 0; i < argc; i++)
\t\tArgs[Num_args++] = _strdup(argv[i]);

\tfor (i = 0; i < Num_args; i++)
\t{
\t\tif (Args[i][0] == '/')
\t\t\tArgs[i][0] = '-';

\t\tif (Args[i][0] == '-')
\t\t\t_strlwr(Args[i]);
\t}
#endif
}
'''

    args_text = replace_function(
        args_text,
        "void InitArgs(int argc, const char** argv)",
        args_new,
        "args.cpp InitArgs"
    )

    args_path.write_text(args_text)

    # --------------------------------------------------------------
    # Fix upstream POSIX string-helper ABI mismatch.
    # --------------------------------------------------------------

    strutil_path = source / "platform" / "unix" / "strutil.cpp"
    strutil = strutil_path.read_text()

    for name in ("_strlwr", "_strupr", "_strrev"):
        pointer_signature = f"char* {name}(char *s1)"
        if pointer_signature in strutil:
            continue

        void_signature = f"void {name}(char *s1)"
        start = strutil.find(void_signature)

        if start < 0:
            raise RuntimeError(f"strutil.cpp: could not find {name}")

        brace = strutil.find("{", start)
        depth = 0
        end = None

        for pos in range(brace, len(strutil)):
            if strutil[pos] == "{":
                depth += 1
            elif strutil[pos] == "}":
                depth -= 1
                if depth == 0:
                    end = pos + 1
                    break

        if end is None:
            raise RuntimeError(f"strutil.cpp: bad function {name}")

        function = strutil[start:end]
        function = function.replace(
            void_signature,
            pointer_signature,
            1
        )

        first_brace = function.find("{")
        function = (
            function[:first_brace + 1]
            + "\n\tchar *result = s1;"
            + function[first_brace + 1:]
        )

        last_brace = function.rfind("}")
        function = (
            function[:last_brace]
            + "\n\treturn result;\n"
            + function[last_brace:]
        )

        strutil = strutil[:start] + function + strutil[end:]

    strutil_path.write_text(strutil)

    # --------------------------------------------------------------
    # Browser-safe game-loop FPS limiter.
    # --------------------------------------------------------------

    game_path = source / "main_d1" / "game.cpp"
    game = game_path.read_text()

    fps_old = '''\t\t\t//waiting loop for polled fps mode
\t\t\tuint64_t numUS = 1000000 / FPSLimit;
\t\t\t//[ISB] Combine a sleep with the polling loop to try to spare CPU cycles
\t\t\tuint64_t diff = (startTime + numUS) - I_GetUS();
\t\t\tif (diff > 5000) //[ISB] Sleep only if there's sufficient time to do so, since the scheduler isn't precise enough
\t\t\t\tI_DelayUS(diff - 5000);
\t\t\twhile (I_GetUS() < startTime + numUS)
\t\t\t{
\t\t\t\tplat_do_events();
\t\t\t}
'''

    fps_new = '''\t\t\t//waiting loop for polled fps mode
\t\t\tuint64_t numUS = 1000000 / FPSLimit;
#ifdef __EMSCRIPTEN__
\t\t\tuint64_t deadline = startTime + numUS;
\t\t\tuint64_t now = I_GetUS();

\t\t\tif (now < deadline)
\t\t\t\tI_DelayUS(deadline - now);

\t\t\tplat_do_events();
#else
\t\t\tuint64_t diff = (startTime + numUS) - I_GetUS();
\t\t\tif (diff > 5000)
\t\t\t\tI_DelayUS(diff - 5000);
\t\t\twhile (I_GetUS() < startTime + numUS)
\t\t\t{
\t\t\t\tplat_do_events();
\t\t\t}
#endif
'''

    if fps_new not in game:
        game = replace_once(
            game,
            fps_old,
            fps_new,
            "game.cpp FPS limiter"
        )

    game_path.write_text(game)

    # --------------------------------------------------------------
    # Browser MIDI: TinySoundFont + main-thread sequencer pump.
    #
    # Native Chocolate Descent runs MidiPlayer on std::thread. The web
    # path keeps the existing HMP sequencer but renders and queues several
    # PCM chunks once per presented frame, avoiding a pthread requirement.
    # --------------------------------------------------------------

    midi_path = source / "platform" / "s_midi.cpp"
    midi = midi_path.read_text()

    if '#include "platform/pixelram/midi_tsf.h"' not in midi:
        midi = replace_once(
            midi,
            '#include "platform/timer.h"\n',
            '#include "platform/timer.h"\n'
            '#ifdef __EMSCRIPTEN__\n'
            '#include "platform/pixelram/midi_tsf.h"\n'
            '#endif\n',
            "s_midi TinySoundFont include"
        )

    globals_anchor = 'std::thread* midiThread = nullptr;\n'

    web_globals = '''std::thread* midiThread = nullptr;

#ifdef __EMSCRIPTEN__
#define WEB_MIDI_SOFT_TICKS 4

static void *web_midi_source = nullptr;
static HMPFile *web_midi_song = nullptr;

static int web_midi_current_tick_frac = 0;
static int web_midi_tick_frac_delta = 0;

static uint16_t web_midi_buffer[
    (MIDI_SAMPLERATE / 120) *
    2 *
    WEB_MIDI_SOFT_TICKS
];
#endif
'''

    if "WEB_MIDI_SOFT_TICKS" not in midi:
        midi = replace_once(
            midi,
            globals_anchor,
            web_globals,
            "s_midi web globals"
        )

    init_web = '''
\tif (CurrentDevice != 0)
\t\treturn 0;

\tMidiTinySoundFont *tiny =
\t\tnew MidiTinySoundFont();

\tif (!tiny)
\t\treturn 1;

\ttiny->SetSampleRate(
\t\tMIDI_SAMPLERATE
\t);

\ttiny->CreateSynth();

\tif (!tiny->IsReady())
\t{
\t\tdelete tiny;
\t\tWarning(
\t\t\t"S_InitMusic: TinySoundFont could not load the browser SoundFont.\\n"
\t\t);
\t\treturn 1;
\t}

\tsynth = tiny;

\tsequencer =
\t\tnew MidiSequencer(
\t\t\tsynth,
\t\t\tMIDI_SAMPLERATE
\t\t);

\tif (!sequencer)
\t{
\t\tsynth->Shutdown();
\t\tdelete synth;
\t\tsynth = nullptr;
\t\treturn 1;
\t}

\tif (plat_start_midi(sequencer))
\t{
\t\tdelete sequencer;
\t\tsequencer = nullptr;

\t\tsynth->Shutdown();
\t\tdelete synth;
\t\tsynth = nullptr;

\t\treturn 1;
\t}

\tweb_midi_source =
\t\tmidi_start_source();

\tif (!web_midi_source)
\t{
\t\tplat_close_midi();

\t\tdelete sequencer;
\t\tsequencer = nullptr;

\t\tsynth->Shutdown();
\t\tdelete synth;
\t\tsynth = nullptr;

\t\treturn 1;
\t}

\tmidi_set_music_samplerate(
\t\tweb_midi_source,
\t\tMIDI_SAMPLERATE
\t);

\tCurrentDevice = device;

\treturn 0;
'''

    shutdown_web = '''
\tif (CurrentDevice == 0)
\t\treturn;

\tif (web_midi_song)
\t{
\t\tif (sequencer)
\t\t\tsequencer->StopSong();

\t\tdelete web_midi_song;
\t\tweb_midi_song = nullptr;
\t}

\tif (web_midi_source)
\t{
\t\tmidi_stop_source(
\t\t\tweb_midi_source
\t\t);

\t\tweb_midi_source = nullptr;
\t}

\tplat_close_midi();

\tif (synth)
\t{
\t\tsynth->Shutdown();
\t\tdelete synth;
\t\tsynth = nullptr;
\t}

\tif (sequencer)
\t{
\t\tdelete sequencer;
\t\tsequencer = nullptr;
\t}

\tCurrentDevice = 0;
\treturn;
'''

    startsong_web = '''
\tif (
\t\tCurrentDevice == 0 ||
\t\t!sequencer
\t)
\t{
\t\treturn 1;
\t}

\tif (web_midi_song)
\t{
\t\tsequencer->StopSong();
\t\tdelete web_midi_song;
\t\tweb_midi_song = nullptr;
\t}

\tif (web_midi_source)
\t{
\t\tmidi_stop_source(
\t\t\tweb_midi_source
\t\t);
\t}

\tweb_midi_source =
\t\tmidi_start_source();

\tif (!web_midi_source)
\t\treturn 1;

\tmidi_set_music_samplerate(
\t\tweb_midi_source,
\t\tMIDI_SAMPLERATE
\t);

\tweb_midi_song =
\t\tnew HMPFile(
\t\t\tlength,
\t\t\tdata
\t\t);

\tif (!web_midi_song)
\t\treturn 1;

\tsequencer->StartSong(
\t\tweb_midi_song,
\t\tloop
\t);

\tweb_midi_current_tick_frac = 0;

\tweb_midi_tick_frac_delta =
\t\t(
\t\t\t65536 *
\t\t\tweb_midi_song->GetTempo()
\t\t) /
\t\t120;

\t*handle = 0;

\treturn 0;
'''

    stopsong_web = '''
\tif (CurrentDevice == 0)
\t\treturn 1;

\tif (web_midi_song)
\t{
\t\tif (sequencer)
\t\t\tsequencer->StopSong();

\t\tdelete web_midi_song;
\t\tweb_midi_song = nullptr;
\t}

\tif (web_midi_source)
\t{
\t\tmidi_stop_source(
\t\t\tweb_midi_source
\t\t);

\t\tweb_midi_source =
\t\t\tmidi_start_source();

\t\tif (web_midi_source)
\t\t{
\t\t\tmidi_set_music_samplerate(
\t\t\t\tweb_midi_source,
\t\t\t\tMIDI_SAMPLERATE
\t\t\t);
\t\t}
\t}

\tweb_midi_current_tick_frac = 0;
\tweb_midi_tick_frac_delta = 0;

\treturn 0;
'''

    midi = wrap_function_for_web(
        midi,
        "int S_InitMusic(int device)",
        init_web,
        "S_InitMusic"
    )

    midi = wrap_function_for_web(
        midi,
        "void S_ShutdownMusic()",
        shutdown_web,
        "S_ShutdownMusic"
    )

    midi = wrap_function_for_web(
        midi,
        "uint16_t S_StartSong(int length, uint8_t* data, bool loop, uint32_t* handle)",
        startsong_web,
        "S_StartSong"
    )

    midi = wrap_function_for_web(
        midi,
        "uint16_t S_StopSong()",
        stopsong_web,
        "S_StopSong"
    )

    web_pump = '''
#ifdef __EMSCRIPTEN__
void S_WebMusicPump()
{
\tif (
\t\tCurrentDevice == 0 ||
\t\t!web_midi_source ||
\t\t!web_midi_song ||
\t\t!sequencer ||
\t\t!synth
\t)
\t{
\t\treturn;
\t}

\tmidi_dequeue_midi_buffers(
\t\tweb_midi_source
\t);

\twhile (
\t\tmidi_queue_slots_available(
\t\t\tweb_midi_source
\t\t)
\t)
\t{
\t\tfor (
\t\t\tint i = 0;
\t\t\ti < WEB_MIDI_SOFT_TICKS;
\t\t\ti++
\t\t)
\t\t{
\t\t\tweb_midi_current_tick_frac +=
\t\t\t\tweb_midi_tick_frac_delta;

\t\t\twhile (
\t\t\t\tweb_midi_current_tick_frac >=
\t\t\t\t65536
\t\t\t)
\t\t\t{
\t\t\t\tsequencer->Tick();

\t\t\t\tweb_midi_current_tick_frac -=
\t\t\t\t\t65536;
\t\t\t}

\t\t\tsequencer->Render(
\t\t\t\tMIDI_SAMPLERATE / 120,
\t\t\t\tweb_midi_buffer +
\t\t\t\t(
\t\t\t\t\tMIDI_SAMPLERATE /
\t\t\t\t\t120 *
\t\t\t\t\t2
\t\t\t\t) *
\t\t\t\ti
\t\t\t);
\t\t}

\t\tmidi_queue_buffer(
\t\t\tweb_midi_source,
\t\t\tMIDI_SAMPLERATE /
\t\t\t\t120 *
\t\t\t\tWEB_MIDI_SOFT_TICKS,
\t\t\tweb_midi_buffer
\t\t);
\t}

\tmidi_check_status(
\t\tweb_midi_source
\t);
}
#endif
'''

    if "void S_WebMusicPump()" not in midi:
        insert_at = midi.find(
            "HMPTrack::HMPTrack("
        )

        if insert_at < 0:
            raise RuntimeError(
                "s_midi.cpp: HMPTrack anchor not found"
            )

        midi = (
            midi[:insert_at]
            + web_pump
            + "\n"
            + midi[insert_at:]
        )

    midi_path.write_text(midi)

    midi_header_path = (
        source / "platform" / "s_midi.h"
    )

    midi_header = midi_header_path.read_text()

    web_decl = '''
#ifdef __EMSCRIPTEN__
void S_WebMusicPump();
#endif
'''

    if "S_WebMusicPump" not in midi_header:
        midi_header += web_decl

    midi_header_path.write_text(
        midi_header
    )

    # --------------------------------------------------------------
    # Browser-friendly sleeps.
    # --------------------------------------------------------------

    timer_path = source / "platform" / "timer.cpp"
    timer = timer_path.read_text()

    if '#include "platform/pixelram/pixelram.h"' not in timer:
        timer = replace_once(
            timer,
            '#include "fix/fix.h"\n',
            '''#include "fix/fix.h"

#ifdef __EMSCRIPTEN__
#include "platform/pixelram/pixelram.h"
#endif
''',
            "timer PixelRAM include"
        )

    delay_old = '''void I_Delay(int ms)
{
\tstd::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void I_DelayUS(uint64_t us)
{
\tstd::this_thread::sleep_for(std::chrono::microseconds(us));
}
'''

    delay_new = '''void I_Delay(int ms)
{
#ifdef __EMSCRIPTEN__
\tsleep_ms(ms > 0 ? (uint32_t)ms : 0);
#else
\tstd::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
}

void I_DelayUS(uint64_t us)
{
#ifdef __EMSCRIPTEN__
\tsleep_ms((uint32_t)((us + 999) / 1000));
#else
\tstd::this_thread::sleep_for(std::chrono::microseconds(us));
#endif
}
'''

    if "sleep_ms(" not in timer:
        timer = replace_once(
            timer,
            delay_old,
            delay_new,
            "timer delays"
        )

    mark_old = '''void I_MarkEnd(uint64_t numUS)
{
\tuint64_t diff = (markTick + numUS) - I_GetUS();
\tif (diff > 2000) //[ISB] Sleep only if there's sufficient time to do so, since the scheduler isn't precise enough
\t\tI_DelayUS(diff - 2000);
\twhile (I_GetUS() < markTick + numUS);
}
'''

    mark_new = '''void I_MarkEnd(uint64_t numUS)
{
#ifdef __EMSCRIPTEN__
\tuint64_t now = I_GetUS();
\tuint64_t end = markTick + numUS;

\tif (now < end)
\t\tI_DelayUS(end - now);
#else
\tuint64_t diff = (markTick + numUS) - I_GetUS();

\tif (diff > 2000)
\t\tI_DelayUS(diff - 2000);

\twhile (I_GetUS() < markTick + numUS);
#endif
}
'''

    if "#ifdef __EMSCRIPTEN__\n\tuint64_t now" not in timer:
        timer = replace_once(
            timer,
            mark_old,
            mark_new,
            "timer I_MarkEnd"
        )

    timer_path.write_text(timer)

    print(
        "ChocolateDescent prepared: "
        "PixelRAM + OpenAL sound + TinySoundFont music"
    )


if __name__ == "__main__":
    main()
