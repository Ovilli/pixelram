---
title: WebAssembly
layout: page
nav_order: 6
---

# WebAssembly

PixelRAM is designed to work both as a native library and in a browser build. The web backend adds a few browser-friendly behaviors while keeping the framebuffer API small.

## One-shot programs

Before a web program has called `present()` explicitly, framebuffer changes are automatically displayed on the next browser animation frame. That makes a tiny example possible without introducing a main loop immediately:

```c
#include "pixelram.h"

int main(void)
{
    if (!screen_open(320, 180, pixel_indexed8, "PixelRAM"))
        return 1;

    set_pixel(screen_width() / 2, screen_height() / 2, 10);
    return 0;
}
```

This automatic presentation is a **web convenience**. Code that should behave identically in native and browser builds should present explicitly.

## Animation and Asyncify

The first explicit call to `present()` switches the web backend to the normal explicit frame model. An animation therefore uses the familiar loop:

```c
while (!should_close())
{
    /* update state */
    /* write pixels */
    present();
}
```

`present()` synchronizes with browser animation frames. PixelRAM targets 60 FPS by default; `set_target_fps()` can select a lower or different maximum. On high-refresh-rate displays PixelRAM skips browser animation frames as needed to honor the requested cap.

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

## Browser display controls

The repository's shared `shell.html` adds a small YouTube-style control bar at the bottom of the PixelRAM display. Move the pointer over the display to reveal it; it hides again after mouse inactivity.

The controls provide the console, CRT filter, and fullscreen without requiring students to remember keyboard shortcuts. Tooltips show the available shortcuts where applicable.

The console also contains the optional ARGS field used by some larger ports. While that text field has focus, its keystrokes are kept out of the running PixelRAM program.

## Mouse capture

`set_mouse_relative(true)` enables relative mouse input. Browsers require a user gesture for pointer lock, so PixelRAM captures and hides the pointer on the next click on the canvas. Escape releases browser pointer lock; a later click can capture it again while relative mode remains requested.

`mouse_delta()` reports the movement for the current backend frame. Multiple readers in the same frame see the same delta, which is important for larger engines that have more than one input layer.

Ordinary programs do not capture the pointer unless they explicitly enable relative mode.

## Fullscreen

`set_fullscreen(true)` requests fullscreen on the next canvas click because browsers require fullscreen changes to originate from a user gesture. The shared shell also exposes fullscreen directly through its bottom-right control.

Browsers reserve Escape for leaving fullscreen, so games that also use Escape for menus cannot reliably prevent that browser behavior.

## Pixel aspect ratio

`set_pixel_aspect()` exposes the desired pixel width/height ratio through the CSS custom property `--pixel-aspect-ratio` and triggers a resize event. The shared web shell uses that information when sizing the canvas. Native builds currently use square display pixels.
