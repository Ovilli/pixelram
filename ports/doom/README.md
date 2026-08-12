# DOOM

PixelRAM's DOOM target uses the GPL-licensed `doomgeneric` engine.

Run:

```sh
make doom
```

If `doom1.wad` (or `DOOM1.WAD`) is present next to the top-level Makefile,
PixelRAM uses that file. Otherwise it downloads the original **DOOM 1.9
shareware** IWAD into `.cache/doom-shareware/` and verifies its SHA-256 before
using it. The shareware IWAD contains Episode 1, *Knee-Deep in the Dead*.

The fallback is kept out of the repository. The DOOM shareware WAD is freely
distributable; PixelRAM downloads the unmodified file hosted by Debian Sources.

PixelRAM also downloads the pinned engine source and free MIDI instruments into
`.cache/`, then writes:

```text
build/doom.html
```

The generated browser build loads `build/doom1.wad` beside the HTML file.
