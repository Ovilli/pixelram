# Descent

PixelRAM's Descent target uses Chocolate Descent with the browser platform
adapter in this directory.

Run:

```sh
make descent
```

If `descent.hog` and `descent.pig` are present next to the top-level Makefile,
PixelRAM uses them. Otherwise it downloads the original **Descent 1.4
shareware** archive into `.cache/descent-shareware/`, verifies the archive and
both extracted game files by SHA-256, and builds the shareware version.

The fallback archive is the unmodified shareware release. Its own license states
that shareware Descent may be freely distributed in unmodified form without a
fee. PixelRAM does not commit or republish the archive.

PixelRAM downloads the pinned Chocolate Descent source, TinySoundFont and the
TimGM6mb SoundFont into `.cache/`, applies the WebAssembly/PixelRAM platform
patches, and writes:

```text
build/descent.html
```

Sound effects use Emscripten OpenAL. Music uses TinySoundFont and Chocolate
Descent's existing HMP sequencer.

## Mouse control in the browser

The WebAssembly port defaults to Descent's **Mouse** control scheme. When the
game requests relative mouse mode, click the game display to capture and hide
the pointer. Escape releases browser pointer lock; click the display again to
capture it. Menus and ordinary PixelRAM programs keep normal absolute mouse
input.
