---
title: Direct framebuffer access
layout: page
nav_order: 5
---

# Direct framebuffer access

`set_pixel()` is convenient for teaching and small effects. For a software renderer or an engine port, access the framebuffer directly.

```c
uint8_t *pixels = framebuffer();
int pitch = screen_pitch();

pixels[y * pitch + x] = color;
```

In indexed mode the pitch is normally equal to the screen width because each pixel is one byte. Use `screen_pitch()` rather than assuming that relationship in generic code.

## RGB565

```c
uint8_t *pixels = framebuffer();
uint16_t *row = (uint16_t *)(pixels + y * screen_pitch());
row[x] = rgb565_pack(255, 128, 0);
```

## RGB24

Each pixel occupies three bytes in RGB order:

```c
uint8_t *pixels = framebuffer();
uint8_t *p = pixels + y * screen_pitch() + x * 3;
p[0] = r;
p[1] = g;
p[2] = b;
```

## RGBA32

Each pixel occupies four bytes in RGBA order.

## Mode changes

`screen_set_mode()` allocates a new framebuffer. A pointer obtained before the change is no longer valid:

```c
screen_set_mode(320, 200, pixel_indexed8);
uint8_t *pixels = framebuffer();
```

This direct-memory API is the part of PixelRAM intended for substantial software renderers and ports such as DOOM and Descent.
