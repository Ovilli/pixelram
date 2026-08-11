# DOOM

PixelRAM's DOOM target uses the GPL-licensed `doomgeneric` engine. The WAD is
not distributed by PixelRAM.

Place a legal `doom1.wad` next to the top-level Makefile and run:

```sh
make doom
```

PixelRAM downloads the pinned engine source and free MIDI instruments into
`.cache/`, then writes:

```text
build/doom.html
```

The generated HTML contains the engine and data needed by the browser build.
