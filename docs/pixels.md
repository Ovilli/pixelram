---
title: Pixels and modes
layout: page
nav_order: 3
---

# Pixels and framebuffer modes

PixelRAM supports four software framebuffer formats.

| Mode | Bytes per pixel | Use |
| --- | ---: | --- |
| `pixel_indexed8` | 1 | Palette graphics and classic effects |
| `pixel_rgb565` | 2 | Compact 16-bit direct color |
| `pixel_rgb24` | 3 | 24-bit RGB |
| `pixel_rgba32` | 4 | 32-bit RGBA |

## Indexed pixels

In `pixel_indexed8`, the framebuffer stores one palette index per pixel.

```c
set_pixel(20, 10, 15);
uint8_t color = get_pixel(20, 10);
```

`set_pixel()` ignores coordinates outside the screen. `get_pixel()` returns 0 for coordinates outside the screen. This behavior is intentional: neighborhood filters can read around the edges without special boundary code.

`set_pixel()` and `get_pixel()` operate only in `pixel_indexed8` mode.

Use `clear()` to fill the entire indexed framebuffer with one palette index:

```c
clear(0);
```

## Direct-color pixels

Use `set_pixel_rgb()` in one of the RGB modes:

```c
set_pixel_rgb(20, 10, 255, 80, 20);
```

Use `clear_rgb()` to fill the whole framebuffer in `pixel_rgb565`, `pixel_rgb24`, or `pixel_rgba32` mode:

```c
clear_rgb(20, 40, 80);
```

`clear_rgb()` does nothing in indexed mode; use `clear()` with a palette index there. In RGBA32 mode it writes alpha as 255.

`get_pixel_rgb()` works in every mode. In indexed mode it resolves the stored palette index to its current RGB color.

```c
uint8_t r, g, b;
if (get_pixel_rgb(20, 10, &r, &g, &b)) {
    /* use r, g and b */
}
```

## Changing mode

```c
screen_set_mode(320, 200, pixel_rgb565);
```

Changing mode replaces the framebuffer, so retrieve its address again if you previously stored it:

```c
uint16_t *pixels = framebuffer();
```
