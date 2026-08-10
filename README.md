# PixelRAM

**A tiny software framebuffer for fast, low-level pixel graphics and games.**

PixelRAM gives a C program a block of memory that represents the screen. You can read and write pixels, change palettes, handle input, and present complete frames. The public API deliberately stays small: it is meant for old-school graphics experiments, software renderers, teaching, and ports of engines such as DOOM or Descent.

PixelRAM is related to [Pixelflow Canvas](https://specht.github.io/pixelflow_canvas_ruby/) in spirit, but it is a different tool. Pixelflow Canvas is a Visual Studio Code canvas with language drivers. PixelRAM is a fast software framebuffer library. The fire demo in `examples/fire.c` is intentionally almost the same algorithm as the Ruby Pixelflow Canvas demo.

![PixelRAM fire demo](docs/images/fire.png)

Application code includes only `pixelram.h`; the platform backend is an implementation detail.

## First program

```c
#include "pixelram.h"

int main(void)
{
    if (!screen_open(320, 180, pixel_indexed8, "PixelRAM"))
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

In indexed mode every pixel is one byte containing a palette index from 0 to 255. The default palette is the classic 256-color VGA palette.

## Build the examples

PixelRAM currently uses raylib as its private platform backend. For a normal native build, install raylib including its development files and make sure `pkg-config raylib` works. Then:

```sh
make
./build/minimal
./build/fire
```

The Hackschule workspace already supplies the platform toolchain used by its PixelRAM projects, so student projects do not need to call raylib directly.

## Use PixelRAM in another project

PixelRAM is deliberately distributable as two files:

```text
pixelram.c
pixelram.h
```

You can copy them into a project, add them to a template, or let a Makefile download a pinned release:

```make
PIXELRAM_VERSION := v0.1.0
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

PixelRAM retains the web-aware behavior of the original framebuffer backend: presentation synchronizes with `requestAnimationFrame`, `sleep_ms()` yields through Asyncify, and relative mouse mode uses browser pointer lock. A web build therefore needs a raylib/Emscripten toolchain and Asyncify enabled.

## Documentation

The GitHub Pages source is in `docs/`, and `.github/workflows/pages.yml` builds it with Jekyll. After publishing the repository as `specht/pixelram`, set GitHub Pages to use **GitHub Actions** as its source. The intended documentation URL is:

`https://specht.github.io/pixelram/`

## Repository layout

```text
pixelram.c              library implementation
pixelram.h              public API
examples/minimal.c      smallest useful example
examples/fire.c         Pixelflow-to-PixelRAM bridge demo
docs/                   GitHub Pages documentation
tools/palettes.yaml     shared Pixelflow palette source
tools/generate_palettes.py
tests/                  backend-independent framebuffer tests
Makefile
LICENSE
```

## License

PixelRAM is released under the GNU General Public License version 3. See `LICENSE`.
