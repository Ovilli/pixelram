# PixelRAM big ports

The normal `make` target stays small and builds only the teaching examples. Optional targets demonstrate that the same framebuffer API can support real 1990s software-rendered games:

```sh
make doom
make descent
make prince
```

`make games` builds all three.

PixelRAM downloads and caches pinned engine/source dependencies under `.cache/`, but it does **not** redistribute the commercial game data. Supply that data from your own copy of each game.

## DOOM

Put `doom1.wad` next to the Makefile:

```sh
make doom
```

Output:

```text
build/doom.html
```

The port uses doomgeneric and PixelRAM for the framebuffer/input layer. FreePats is downloaded separately for General MIDI playback.

## Descent

Put these files next to the Makefile:

```text
descent.hog
descent.pig
```

Then run:

```sh
make descent
```

Output:

```text
build/descent.html
```

The port uses Chocolate Descent. Sound effects use Emscripten OpenAL; music uses TinySoundFont. Relative mouse steering uses PixelRAM's browser pointer-lock path: click the game after it requests relative mode, and press Escape to release the pointer.

## Prince of Persia

Copy the complete DOS Prince of Persia data set into:

```text
prince-data/
```

The directory should contain `PRINCE.DAT` and the other data files from your game copy. Then run:

```sh
make prince
```

Output:

```text
build/prince.html
```

The port uses the pinned SDLPoP source. PixelRAM mounts the complete local `prince-data/` directory as `/data`; no Prince of Persia game assets are downloaded or committed by PixelRAM.

## Cleaning cached port sources

Each port has its own clean target when you want the pinned upstream source to be prepared again from scratch:

```sh
make clean-doom
make clean-descent
make clean-prince
```
