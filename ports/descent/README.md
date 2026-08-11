# Descent

PixelRAM's Descent target uses Chocolate Descent with the browser platform
adapter in this directory.

Place compatible PC Descent data next to the top-level Makefile:

```text
descent.hog
descent.pig
```

Then run:

```sh
make descent
```

PixelRAM downloads the pinned Chocolate Descent source, TinySoundFont and the
TimGM6mb SoundFont into `.cache/`, applies the WebAssembly/PixelRAM platform
patches, and writes:

```text
build/descent.html
```

Sound effects use Emscripten OpenAL. Music uses TinySoundFont and Chocolate
Descent's existing HMP sequencer.
