---
title: Getting started
layout: home
nav_order: 1
---

# PixelRAM

PixelRAM is a tiny software framebuffer for fast, low-level pixel graphics and games. A PixelRAM program gets screen memory, input, timing, palettes, and a way to present a completed frame. Everything else is yours to build.

It is deliberately different from Pixelflow Canvas. Pixelflow Canvas provides a canvas in Visual Studio Code and can be driven from different languages. PixelRAM is a compiled framebuffer library. The familiar programming model makes it possible to take a pixel algorithm from Pixelflow Canvas and move it to much faster C/WebAssembly code without changing the idea behind the algorithm.

## Open a screen

```c
#include "pixelram.h"

int main(void)
{
    if (!screen_open(320, 180, pixel_indexed8, "Hello"))
        return 1;

    while (!should_close())
    {
        set_pixel(160, 90, 15);
        present();
    }

    screen_close();
    return 0;
}
```

`screen_open()` selects the logical screen size and framebuffer format. In `pixel_indexed8` mode, each pixel is one byte containing a palette index.

## The main loop

PixelRAM does not own your main loop. A typical program is simply:

```c
while (!should_close())
{
    /* update the program */
    /* write pixels */
    present();
}
```

`present()` makes the current software framebuffer visible and processes the input transitions needed by the event queue. PixelRAM targets **60 FPS by default** on both native and WebAssembly builds. You can choose another cap after opening the screen:

```c
set_target_fps(30);
```

Use `set_target_fps(0)` to disable PixelRAM's explicit FPS cap. In a browser, presentation still follows the browser's animation-frame cycle.

## Build the repository examples

With raylib development files available through `pkg-config`:

```sh
make
./build/minimal
./build/fire
```

The public PixelRAM header contains no raylib types or functions; application code talks only to PixelRAM.

## Where next?

- [Pixels and framebuffer modes](pixels.html)
- [Palettes](palettes.html)
- [The fire demo](fire.html)
- [Keyboard and mouse](input.html)
- [Direct framebuffer access](framebuffer.html)
- [WebAssembly](web.html)
- [Using only the two library files](distribution.html)
- [API reference](api.html)
