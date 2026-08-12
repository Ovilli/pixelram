# PixelRAM big ports

The normal `make` target stays small and builds only the teaching examples. Optional targets demonstrate that the same framebuffer API can support real 1990s software-rendered games:

```sh
make doom
make descent
make prince
```

`make games` builds all three.

PixelRAM downloads and caches pinned engine/source dependencies under `.cache/`. DOOM and Descent can also fall back to their original freely distributable shareware data, so those two targets work out of the box. If you provide your own compatible full-game files, those are preferred automatically.

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

## Descent

Simply run:

```sh
make descent
```

If these files are next to the Makefile, PixelRAM uses them:

```text
descent.hog
descent.pig
```

Otherwise it downloads the original Descent 1.4 shareware archive, verifies the archive and extracted HOG/PIG files, and caches them under `.cache/descent-shareware/`.

Chocolate Descent is based on the later registered D1 source and normally expects a 621-string text table, while the 1.4 shareware data contains the older 514-string table. The PixelRAM web preparation step keeps the shareware strings unchanged and supplies empty entries only for the registered-only tail so the seven-level shareware game can start. Full registered data is used unchanged when supplied locally.

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

The port uses the pinned SDLPoP source. PixelRAM mounts the complete local `prince-data/` directory as `/data`. Unlike DOOM and Descent, PixelRAM does **not** automatically download Prince of Persia game data because there is not a sufficiently clear redistribution grant for those original assets.

## Shareware downloads

`tools/fetch_shareware.py` performs the fallback downloads and refuses to use files whose SHA-256 does not match the known release. The fallback data is never committed to the repository.

The sources used are:

- DOOM 1.9 shareware `doom1.wad`: Debian's `doom-wad-shareware` source package. The WAD's SHA-256 is `1d7d43be501e67d927e415e0b8f3e29c3bf33075e859721816f652a526cac771`.
- Descent 1.4 shareware: the unmodified `desc14sw.tar.gz` archive hosted by icculus.org. Debian game-data-packager records the archive and extracted HOG/PIG checksums and reproduces the shareware redistribution notice.

## Cleaning cached port sources

Each port has its own clean target when you want the pinned upstream source and downloaded fallback data prepared again from scratch:

```sh
make clean-doom
make clean-descent
make clean-prince
```

## OpenTTD (experimental)

OpenTTD is the first higher-resolution, mouse-driven PixelRAM port. It is also
fully free: no Transport Tycoon Deluxe files are required.

```sh
make openttd
```

PixelRAM pins OpenTTD 15.3 and downloads the official free base sets directly
from the OpenTTD project:

- OpenGFX 8.0 (`SHA-256 43a0c1dabf39cb865394f3a6cc36d4da5c10ecfaaf55652043104806810903be`)
- OpenSFX 1.0.3 (`SHA-256 e0a218b7dd9438e701503b0f84c25a97c1c11b7c2f025323fb19d6db16ef3759`)
- OpenMSX 0.4.2 (`SHA-256 5a4277a2e62d87f2952ea5020dc20fb2f6ffafdccf9913fbf35ad45ee30ec762`)

The initial port uses OpenTTD's existing Emscripten game loop but replaces its
active video/input backend with PixelRAM. OpenTTD draws directly into a
PixelRAM RGBA framebuffer at 800x600 and uses its own software mouse cursor.
Sound and music are disabled in this first milestone while the framebuffer and
input port is stabilized.

Output:

```text
build/openttd.html
```
