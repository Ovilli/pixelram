---
title: API reference
layout: page
nav_order: 9
---

# API reference

## Screen

```c
bool screen_open(int width, int height, pixel_mode mode, const char *title);
bool screen_set_mode(int width, int height, pixel_mode mode);
void screen_close(void);
bool should_close(void);
void set_title(const char *title);

int screen_width(void);
int screen_height(void);
int screen_pitch(void);
pixel_mode screen_mode(void);
```

## Framebuffer and pixels

```c
void *framebuffer(void);
size_t framebuffer_size(void);

void set_pixel(int x, int y, uint8_t index);
uint8_t get_pixel(int x, int y);

void set_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);
bool get_pixel_rgb(int x, int y, uint8_t *r, uint8_t *g, uint8_t *b);

uint16_t rgb565_pack(uint8_t r, uint8_t g, uint8_t b);
```

## Palettes

```c
void set_palette(int index, uint8_t r, uint8_t g, uint8_t b);
void get_palette(int index, uint8_t *r, uint8_t *g, uint8_t *b);

bool use_palette(const char *name);
int palette_count(void);
const char *palette_name(int index);
```

`use_palette()` returns `false` for an unknown name. `palette_name()` returns `NULL` for an invalid index.

## Display and timing

```c
void present(void);
void wait_vblank(void);
void set_pixel_aspect(float ratio);
void set_fullscreen(bool enabled);

void sleep_ms(uint32_t ms);
double seconds(void);
uint32_t ticks_ms(void);
```

## Keyboard

```c
bool key_down(pixel_key key);
bool key_pressed(pixel_key key);
bool key_released(pixel_key key);
bool poll_key_event(pixel_key_event *event);
```

## Mouse

```c
void mouse_position(int *x, int *y);
void mouse_delta(int *dx, int *dy);
void set_mouse_position(int x, int y);

bool mouse_button_down(pixel_mouse_button button);
bool mouse_button_pressed(pixel_mouse_button button);
bool mouse_button_released(pixel_mouse_button button);
void set_mouse_relative(bool enabled);
```

## Pixel modes

```c
pixel_indexed8
pixel_rgb565
pixel_rgb24
pixel_rgba32
```
