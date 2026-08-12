# Descent

PixelRAM's Descent target uses Chocolate Descent with the browser platform
adapter in this directory.

Copy `DESCENT.HOG` and `DESCENT.PIG` from your Descent installation into:

```text
descent-data/
```

Lowercase filenames are accepted too. Root-level `descent.hog` and
`descent.pig` remain supported for compatibility with older checkouts.

Then run:

```sh
make descent
```

PixelRAM does not ship or download Descent game data.

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
