# PixelRAM big ports

The normal `make` target stays small and builds only the teaching examples. Optional targets demonstrate that the same framebuffer API can support real 1990s software-rendered games:

```sh
make doom
make crystal
make descent
make prince
```

`make games` builds all four.

PixelRAM downloads and caches pinned engine/source dependencies under `.cache/`. DOOM and Crystal Caves have shareware fallbacks. Descent and Prince of Persia intentionally require game data from your own copy.

## DOOM

Simply run:

```sh
make doom
```

If `doom1.wad` (or `DOOM1.WAD`) is next to the Makefile, PixelRAM uses it. Otherwise it downloads the original DOOM 1.9 shareware IWAD, verifies its SHA-256 checksum, and caches it under `.cache/doom-shareware/`. The shareware data contains the complete first episode.

Output:

```text
build/doom.html
```

The port uses doomgeneric and PixelRAM for the framebuffer/input layer. FreePats is downloaded separately for General MIDI playback.

## Crystal Caves

Simply run:

```sh
make crystal
```

The pinned OpenCrystalCaves source contains the original Crystal Caves shareware episode, so no separate game-data download is required for the fallback build. PixelRAM stages that shareware episode automatically.

If you have your own episode 1 data, copy the files into:

```text
crystal-caves-data/
```

When `CC1.GFX` is present there, the local data set replaces the bundled shareware `CC1` directory for the build. Lowercase filenames are accepted.

Output:

```text
build/crystal.html
```

OpenCrystalCaves already draws through a small `Window` / `Surface` abstraction. The port implements that abstraction with plain RGBA memory: scaling, alpha blending, lines, rectangles, and surface blits live entirely inside the adapter and write to PixelRAM's framebuffer. SDL_mixer remains only for sound.

## Descent

Copy these two files from your Descent installation into:

```text
descent-data/
```

Required files:

```text
DESCENT.HOG
DESCENT.PIG
```

Lowercase filenames are accepted too. For compatibility with older PixelRAM checkouts, root-level `descent.hog` and `descent.pig` are also still recognized.

Then run:

```sh
make descent
```

PixelRAM deliberately does not download substitute Descent game data. Using the full game files keeps the port on the same known-good data path as a normal Chocolate Descent installation, including the expected game resources and music tables.

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

The port uses the pinned SDLPoP source. PixelRAM mounts the complete local `prince-data/` directory as `/data`. Like Descent, PixelRAM does **not** automatically download Prince of Persia game data; use the files from your own game copy.

## Shareware fallback data

`tools/fetch_shareware.py` downloads only the DOOM 1.9 shareware `doom1.wad` fallback and refuses to use a file whose SHA-256 does not match the known release. The WAD comes from Debian's `doom-wad-shareware` source package; its SHA-256 is `1d7d43be501e67d927e415e0b8f3e29c3bf33075e859721816f652a526cac771`.

Crystal Caves is different: the pinned OpenCrystalCaves source already contains its shareware episode under `media/CC1`, so `make crystal` uses that copy directly when `crystal-caves-data/` is absent. Neither fallback is committed to the PixelRAM repository.

## Cleaning cached port sources

Each port has its own clean target when you want the pinned upstream source and downloaded fallback data prepared again from scratch:

```sh
make clean-doom
make clean-crystal
make clean-descent
make clean-prince
```
