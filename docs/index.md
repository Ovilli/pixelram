---
title: Getting started
layout: home
nav_order: 1
---

# PixelRAM

PixelRAM is a tiny software framebuffer for fast, low-level pixel graphics and games. A PixelRAM program gets screen memory, input, timing, palettes, and a way to present completed animation frames. Everything else is yours to build.

It is deliberately different from Pixelflow Canvas. Pixelflow Canvas provides a canvas in Visual Studio Code and can be driven from different languages. PixelRAM is a compiled framebuffer library. The familiar programming model makes it possible to move a pixel algorithm from Pixelflow Canvas to much faster C/WebAssembly code without hiding the algorithm behind a graphics framework.

<a id="live-fire"></a>
## Live fire demo

This is the real `examples/fire.c`, compiled to WebAssembly as part of the documentation deployment. Move the mouse over the bottom of the display to reveal the console, CRT, and fullscreen controls.

<div class="pixelram-demo">
  <iframe src="demos/fire.html" title="PixelRAM fire demo" loading="lazy" allow="fullscreen"></iframe>
</div>

<style>
.pixelram-demo {
  width: 100%;
  aspect-ratio: 2 / 1;
  overflow: hidden;
  border-radius: 8px;
  background: #030405;
  box-shadow: 0 10px 35px rgba(0, 0, 0, .2);
}

.pixelram-demo iframe {
  display: block;
  width: 100%;
  height: 100%;
  border: 0;
}
</style>

## One pixel is enough

The smallest repository example opens an indexed screen and writes one bright-green VGA pixel in the center:

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

In `pixel_indexed8` mode, each framebuffer byte is a palette index. PixelRAM starts with the classic VGA palette, where index `10` is bright green.

For a tiny **web** program like this, `present()` is optional. PixelRAM automatically displays framebuffer changes until the program calls `present()` explicitly for the first time. This convenience is intended for one-shot browser examples.

## Animation adds `present()`

Once a program animates, use an explicit frame loop. This example erases a green pixel, moves it, redraws it, and then presents the completed frame:

```c
#include "pixelram.h"

int main(void)
{
    if (!screen_open(320, 180, pixel_indexed8, "PixelRAM animation"))
        return 1;

    int x = 0;
    int direction = 1;
    int y = screen_height() / 2;

    while (!should_close())
    {
        set_pixel(x, y, 0);

        x += direction;
        if (x == 0 || x == screen_width() - 1)
            direction = -direction;

        set_pixel(x, y, 10);
        present();
    }

    screen_close();
    return 0;
}
```

The first explicit `present()` switches a web program to the normal explicit frame model. PixelRAM targets **60 FPS by default**; call `set_target_fps(30)` or another value after `screen_open()` to choose a different cap.

## Build the repository examples

In Hackschule Workspace, the required Emscripten and raylib toolchain is already installed:

```sh
make
```

This creates:

```text
build/minimal.html
build/animation.html
build/fire.html
```

The public PixelRAM header contains no raylib types or functions; application code talks only to PixelRAM.

## Where next?

- [Palettes](palettes.html)
- [Pixels and framebuffer modes](pixels.html)
- [Keyboard and mouse](input.html)
- [Direct framebuffer access](framebuffer.html)
- [WebAssembly](web.html)
- [Adding PixelRAM to a project](distribution.html)
- [API reference](api.html)
