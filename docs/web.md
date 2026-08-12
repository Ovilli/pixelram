---
title: WebAssembly
layout: page
nav_order: 7
---

# WebAssembly

PixelRAM is designed to work both as a native library and in a browser build. The public program stays the same:

```c
while (!should_close())
{
    /* update state and pixels */
    present();
}
```

The web backend is enabled when the implementation is compiled with `PLATFORM_WEB` using a raylib/Emscripten toolchain.

## Frame rate and Asyncify

`present()` synchronizes with browser animation frames. PixelRAM targets 60 FPS by default; `set_target_fps()` can select a lower or different maximum. On high-refresh-rate displays PixelRAM skips browser animation frames as needed to honor the requested cap.

For tiny one-shot demos, explicit presentation is optional: before a program has ever called `present()`, framebuffer writes are automatically shown on the next browser frame. The first explicit `present()` switches to the normal double-buffered frame model.

```c
set_target_fps(30);
```

`set_target_fps(0)` disables PixelRAM's additional cap, but browser presentation still follows `requestAnimationFrame()` and therefore the browser/display refresh cycle.

Both animation-frame waiting and `sleep_ms()` yield to the browser rather than blocking it. These operations use Emscripten Asyncify, so the final web link step must enable Asyncify.

A typical toolchain therefore defines `PLATFORM_WEB` and links with an option equivalent to:

```text
-sASYNCIFY
```

The exact raylib library path and the rest of the Emscripten link flags depend on the surrounding toolchain. PixelRAM deliberately does not bake those project-specific paths into its two distributable files.

## Mouse capture

`set_mouse_relative(true)` requests browser pointer lock. Browsers require a user gesture for pointer lock, so PixelRAM performs the request on the next click on the canvas.

Likewise, `set_fullscreen(true)` requests fullscreen on the next canvas click.

## Pixel aspect ratio

`set_pixel_aspect()` exposes the desired pixel width/height ratio through the CSS custom property `--pixel-aspect-ratio` and triggers a resize event. A custom web shell can use that property when sizing the canvas. Native builds currently use square display pixels.
