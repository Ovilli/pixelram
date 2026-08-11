# Prince of Persia / SDLPoP first pass

This is intentionally the first milestone rather than the final PixelRAM
backend.

`make prince`:

1. clones a pinned SDLPoP revision,
2. builds its existing software-rendered SDL2 code with Emscripten,
3. uses the same PixelRAM web shell as the other demos,
4. packages SDLPoP's upstream `data/` directory into `prince.data`.

No original game files need to be placed beside the Makefile for this test,
because the pinned SDLPoP repository itself contains the data resources used
by the port.

Run:

    make prince

Then open:

    build/prince.html

Expected generated files:

    build/prince.html
    build/prince.js
    build/prince.wasm
    build/prince.data

Why do this before the PixelRAM backend?
----------------------------------------

SDLPoP already performs the original game's software drawing into SDL
surfaces. If this first browser build runs correctly, the next patch can be
very small and focused: present the final 320x200 software surface through
PixelRAM and translate input through PixelRAM, while leaving the game's
drawing/resource/audio code untouched.
