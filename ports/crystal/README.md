# Crystal Caves

This port uses the pinned [OpenCrystalCaves](https://github.com/OpenCrystalCaves/OpenCrystalCaves) engine with PixelRAM as the visible framebuffer and input layer.

```sh
make crystal
```

The pinned OpenCrystalCaves source already contains the original Crystal Caves shareware episode, so no game-data download is required for the fallback build.

If you have your own Crystal Caves episode 1 data, put the files in:

```text
crystal-caves-data/
```

`CC1.GFX` is used to detect the local data set. When it is present, the complete contents of `crystal-caves-data/` replace the bundled shareware `CC1` directory for the build. Lowercase filenames are accepted and normalized when staged.

Output:

```text
build/crystal.html
```

## Port boundary

OpenCrystalCaves already separates drawing behind a small `Window` / `Surface` interface. The PixelRAM adapter implements that interface itself with plain RGBA memory. It performs the few operations OCC needs—nearest-neighbor surface scaling, alpha/tint blending, fills, lines, and rectangles—inside the port and writes the visible result directly into PixelRAM's `pixel_rgba32` framebuffer.

Input comes directly from PixelRAM. SDL_mixer remains in use only for the game's small generated sound-effect chunks.

PixelRAM itself still gains no sprite, line, rectangle, texture, or blit API; all of that compatibility code belongs to this port.
