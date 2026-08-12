# PixelRAM

**A tiny software framebuffer for fast, low-level pixel graphics and games.**

PixelRAM gives C programs the kind of screen that made early PC graphics fun: a block of memory full of pixels. There is no scene graph, no sprite engine, and no drawing API to learn first. Write pixels directly, use a palette if you want one, and build everything else yourself.

That makes PixelRAM small enough for teaching, but fast enough for software renderers and ports such as DOOM, Descent, and SDLPoP. The same library can be used natively or compiled to WebAssembly for the browser.

## Start with fire

This complete program creates the classic palette-based fire effect:

```c
#include "pixelram.h"

#include <stdlib.h>
#include <time.h>

#define WIDTH  256
#define HEIGHT 128

static int clamp(int value, int low, int high)
{
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

int main(void)
{
    if (!screen_open(WIDTH, HEIGHT, pixel_indexed8, "PixelRAM fire"))
        return 1;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 16; i++)
    {
        set_palette(i, i * 8, 0, 0);
        set_palette(i + 16, i * 8 + 128, i * 8, 0);
        set_palette(i + 32, 255, i * 8 + 128, i * 8);
        set_palette(i + 48, 255, 255, i * 8 + 128);
    }

    while (!should_close())
    {
        for (int y = HEIGHT - 2; y < HEIGHT; y++)
            for (int x = 10; x < WIDTH - 10; x++)
                set_pixel(x, y, 63);

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                int color = get_pixel(x, y + 1) * 2;
                color += get_pixel(x - 1, y);
                color += get_pixel(x + 1, y);
                color /= 4;

                if (color > 0)
                    color += rand() % 7 - 3;

                set_pixel(x, y, (uint8_t)clamp(color, 0, 63));
            }
        }

        present();
    }

    screen_close();
    return 0;
}
```

**[Run this exact example in your browser →](https://specht.github.io/pixelram/#live-fire)**

The live version is compiled from `examples/fire.c` whenever the documentation site is deployed. The source is intentionally close to the Pixelflow Canvas fire demo: the algorithm stays visible while C/WebAssembly makes it fast.

**[Read the documentation →](https://specht.github.io/pixelram/)**

## Smallest useful program

For a one-shot browser demo, drawing can be this small:

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

Color `10` is bright green in the default VGA palette. Web builds automatically show framebuffer changes until a program explicitly starts using `present()`, so a tiny one-shot example does not need a main loop. This auto-presentation is a browser convenience; portable/native animation code should use `present()` explicitly.

## Add animation

Animation introduces the normal PixelRAM frame loop. This example moves the same green pixel left and right:

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

The first explicit `present()` switches a web program from automatic one-shot presentation to the normal explicit frame model. From then on, call `present()` once after drawing each completed frame.

## Frame rate

PixelRAM targets **60 FPS by default**. Change the cap at any time after `screen_open()`:

```c
set_target_fps(30);
```

Use `set_target_fps(0)` to disable PixelRAM's explicit frame-rate cap. Native builds then run without a target FPS; browser builds still present on browser animation frames.

The frame-rate cap controls how often `present()` completes. Game logic that must behave identically at different frame rates should use `seconds()` or `ticks_ms()` for time-based movement.

## Build the examples

PixelRAM is designed for WebAssembly projects in Hackschule Workspace. The required Emscripten and raylib toolchain is already installed there.

Build all examples:

```sh
make
```

The resulting self-contained HTML files are written to `build/`:

```text
build/minimal.html
build/animation.html
build/fire.html
```

The Hackschule workspace supplies the platform toolchain, so student programs use only the PixelRAM API and do not need to call raylib directly.

## Use PixelRAM in another project

PixelRAM is deliberately distributable as two files:

```text
pixelram.c
pixelram.h
```

You can copy them into a project, add them to a template, or let a Makefile download a pinned release:

```make
PIXELRAM_VERSION := v0.1.17
PIXELRAM_BASE := https://raw.githubusercontent.com/specht/pixelram/$(PIXELRAM_VERSION)
PIXELRAM_DIR := vendor/pixelram

$(PIXELRAM_DIR)/pixelram.c:
	mkdir -p $(PIXELRAM_DIR)
	curl -fsSL $(PIXELRAM_BASE)/pixelram.c -o $@

$(PIXELRAM_DIR)/pixelram.h:
	mkdir -p $(PIXELRAM_DIR)
	curl -fsSL $(PIXELRAM_BASE)/pixelram.h -o $@
```

Pin a release tag rather than `main` so old teaching material continues to build after PixelRAM changes.

## Pixel modes

| Mode | Bytes per pixel | Meaning |
| --- | ---: | --- |
| `pixel_indexed8` | 1 | 0-255 index into the current palette |
| `pixel_rgb565` | 2 | 16-bit direct color |
| `pixel_rgb24` | 3 | 24-bit RGB |
| `pixel_rgba32` | 4 | 32-bit RGBA |

For introductory low-level graphics, `pixel_indexed8` is usually the most interesting mode. For ports and software renderers, `framebuffer()` exposes the memory directly in every mode.

## Palettes

PixelRAM contains the same 88 predefined palettes as Pixelflow Canvas, including `vga`, `aap_64`, `endesga_32`, `pico_8`, `sweetie_16`, and `zughy_32`.

```c
use_palette("pico_8");
set_palette(0, 20, 52, 100);
```

Changing a palette entry changes the appearance of all indexed pixels using that color without modifying the framebuffer.

The source palette list lives in `tools/palettes.yaml`; `tools/generate_palettes.py` regenerates both the C tables and the palette documentation.

## Why no drawing primitives?

PixelRAM intentionally stops at pixels and framebuffer memory. A line, circle, triangle rasterizer, raycaster, plasma effect, or software 3D renderer is something you can implement *on top* of the framebuffer rather than something the library hides.

This keeps the central model visible:

```c
set_pixel(x, y, color);
int color = get_pixel(x, y);
```

and, one level lower:

```c
uint8_t *pixels = framebuffer();
pixels[y * screen_pitch() + x] = color;
```

## WebAssembly

PixelRAM's web backend synchronizes explicit presentation with `requestAnimationFrame`, lets one-shot examples auto-present, yields through Asyncify for `sleep_ms()`, and uses browser pointer lock for relative mouse mode. A web build therefore needs a raylib/Emscripten toolchain and Asyncify enabled.

The shared browser shell also provides discoverable controls for the console, CRT filter, and fullscreen. Move the pointer over the bottom of the display to reveal them; the controls hide again after mouse inactivity.

## Larger ports

Optional Makefile targets demonstrate that the same framebuffer API can support real software-rendered games:

```sh
make doom
make descent
make prince
```

The engine source is downloaded and cached, while commercial game data is supplied separately. See [`PORTS.md`](PORTS.md) for the required files.

## Documentation

The complete documentation is available at **[https://specht.github.io/pixelram/](https://specht.github.io/pixelram/)**.

The GitHub Pages source lives in `docs/`, and `.github/workflows/pages.yml` builds and deploys it with GitHub Actions. The live fire example on the front page is compiled from the repository source during that workflow.

## Repository layout

```text
pixelram.c                library implementation
pixelram.h                public API
examples/minimal.c        one-shot browser example
examples/animation.c      smallest animated example
examples/fire.c           Pixelflow-to-PixelRAM bridge demo
docs/                     GitHub Pages documentation
ports/                    optional engine-port adapters
tools/palettes.yaml       shared Pixelflow palette source
tools/generate_palettes.py
tests/                    backend-independent framebuffer tests
Makefile
LICENSE
```

## License

PixelRAM is released under the GNU General Public License version 3. See `LICENSE`.
