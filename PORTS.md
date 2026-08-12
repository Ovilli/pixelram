# PixelRAM big ports

The normal `make` target stays small and offline. It builds only the teaching
examples.

Two optional targets demonstrate that the same framebuffer API can support
real 1990s software-rendered games:

```sh
make doom
make descent
```

## DOOM

Put `doom1.wad` next to the Makefile:

```sh
make doom
```

Output:

```text
build/doom.html
```

## Descent

Put these two files next to the Makefile:

```text
descent.hog
descent.pig
```

Then:

```sh
make descent
```

Output:

```text
build/descent.html
```

Downloaded source code and music assets are cached under `.cache/` and are not
committed. The game data files are also ignored by Git.
