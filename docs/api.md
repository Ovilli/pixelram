---
title: API reference
layout: page
nav_order: 8
---

# API reference

This page documents the complete public interface in `pixelram.h`. PixelRAM intentionally keeps that interface small: screen management, framebuffer access, pixels and palettes, presentation, input, and timing.

## Screen

### `screen_open`

```c
bool screen_open(int width, int height, pixel_mode mode, const char *title);
```

Creates the PixelRAM screen and allocates the software framebuffer.

- `width`, `height`: logical framebuffer size in pixels. Both must be greater than zero.
- `mode`: one of `pixel_indexed8`, `pixel_rgb565`, `pixel_rgb24`, or `pixel_rgba32`.
- `title`: window title. Pass `NULL` to use `PixelRAM`.
- Returns `true` on success and `false` if the arguments are invalid or the framebuffer/display resources could not be created.

A newly opened screen uses the VGA palette and a target frame rate of 60 FPS.

```c
if (!screen_open(320, 200, pixel_indexed8, "Fire"))
    return 1;
```

### `screen_set_mode`

```c
bool screen_set_mode(int width, int height, pixel_mode mode);
```

Changes the logical framebuffer size and/or pixel format of an already opened screen. The framebuffer is recreated and cleared, so existing pixel data is lost.

Returns `true` on success. Returns `false` if there is no open screen, a dimension is invalid, the mode is invalid, or new resources could not be allocated.

### `screen_close`

```c
void screen_close(void);
```

Releases PixelRAM's framebuffer and display resources. It is safe to call only after `screen_open()` has succeeded.

### `should_close`

```c
bool should_close(void);
```

Returns `true` when the program should leave its main loop, for example after the user closes the native window. It also returns `true` if no PixelRAM screen is open.

```c
while (!should_close())
{
    /* update and draw */
    present();
}
```

### `set_title`

```c
void set_title(const char *title);
```

Changes the window title of an open screen. A `NULL` title is ignored.

### `screen_width` / `screen_height`

```c
int screen_width(void);
int screen_height(void);
```

Return the current logical framebuffer width and height in pixels.

### `screen_pitch`

```c
int screen_pitch(void);
```

Returns the number of **bytes per framebuffer row**. Do not assume that this is always the same as the width: it depends on the pixel mode.

For the current PixelRAM formats:

| Mode | Pitch |
| --- | --- |
| `pixel_indexed8` | `width` |
| `pixel_rgb565` | `width * 2` |
| `pixel_rgb24` | `width * 3` |
| `pixel_rgba32` | `width * 4` |

Use `screen_pitch()` when doing direct framebuffer addressing.

### `screen_mode`

```c
pixel_mode screen_mode(void);
```

Returns the active framebuffer format.

## Framebuffer

### `framebuffer`

```c
void *framebuffer(void);
```

Returns a pointer to PixelRAM's software framebuffer. This is the fast, low-level interface intended for renderers and engine ports.

In indexed mode:

```c
uint8_t *pixels = framebuffer();
pixels[y * screen_pitch() + x] = color;
```

The pointer remains valid until `screen_set_mode()` or `screen_close()` recreates/frees the framebuffer.

### `framebuffer_size`

```c
size_t framebuffer_size(void);
```

Returns the framebuffer size in bytes (`screen_pitch() * screen_height()`).

## Indexed pixels

These functions are for `pixel_indexed8` mode.

### `set_pixel`

```c
void set_pixel(int x, int y, uint8_t index);
```

Writes one palette index to the framebuffer. Out-of-bounds writes are silently ignored. If the current mode is not `pixel_indexed8`, the call does nothing.

```c
set_pixel(10, 20, 15);
```

### `get_pixel`

```c
uint8_t get_pixel(int x, int y);
```

Reads one palette index from the framebuffer. Out-of-bounds reads return `0`. If the current mode is not `pixel_indexed8`, it also returns `0`.

The out-of-bounds behavior is deliberate and is useful for neighborhood algorithms such as the fire demo:

```c
int c = get_pixel(x, y + 1) * 2;
c += get_pixel(x - 1, y);
c += get_pixel(x + 1, y);
```

## Direct-color pixels

### `set_pixel_rgb`

```c
void set_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);
```

Writes an RGB color in `pixel_rgb565`, `pixel_rgb24`, or `pixel_rgba32` mode. Out-of-bounds writes are ignored. In `pixel_indexed8` mode this function does nothing, because an indexed pixel must contain a palette index rather than an RGB triplet.

In `pixel_rgba32` mode the alpha byte is written as 255.

### `get_pixel_rgb`

```c
bool get_pixel_rgb(int x, int y, uint8_t *r, uint8_t *g, uint8_t *b);
```

Reads the displayed RGB value of a pixel in **any** PixelRAM mode. In indexed mode it resolves the stored palette index through the current palette.

- Any of `r`, `g`, or `b` may be `NULL` if that component is not needed.
- Returns `true` for a valid pixel.
- Returns `false` for an invalid coordinate and writes zero to all non-`NULL` output pointers.

### `rgb565_pack`

```c
uint16_t rgb565_pack(uint8_t r, uint8_t g, uint8_t b);
```

Converts 8-bit RGB components to a packed 16-bit RGB565 value. This inline helper is useful when writing directly to a `pixel_rgb565` framebuffer.

```c
uint16_t *pixels = framebuffer();
pixels[y * screen_width() + x] = rgb565_pack(255, 128, 0);
```

## Palettes

Palette functions affect indexed rendering. A palette contains 256 RGB entries; palettes with fewer colors leave the remaining entries black when loaded through `use_palette()`.

### `set_palette`

```c
void set_palette(int index, uint8_t r, uint8_t g, uint8_t b);
```

Sets one palette entry. Valid indices are 0 through 255. Invalid indices are ignored.

Changing a palette entry immediately changes the appearance of every indexed pixel using that index; the framebuffer itself is not modified.

```c
set_palette(1, 255, 80, 0);
```

### `get_palette`

```c
void get_palette(int index, uint8_t *r, uint8_t *g, uint8_t *b);
```

Reads one palette entry. Any output pointer may be `NULL`. An invalid index produces zero for every requested component.

### `use_palette`

```c
bool use_palette(const char *name);
```

Loads one of PixelRAM's built-in Pixelflow-compatible palettes by name, for example:

```c
use_palette("vga");
use_palette("pico_8");
use_palette("aap_64");
```

Returns `true` if the name exists and `false` otherwise. Passing `NULL` returns `false`.

See [Palettes](palettes.html) for the complete visual list.

### `palette_count`

```c
int palette_count(void);
```

Returns the number of built-in named palettes.

### `palette_name`

```c
const char *palette_name(int index);
```

Returns the name of the built-in palette at the given registry index. The returned string is owned by PixelRAM and must not be modified or freed. Returns `NULL` for an invalid index.

This pair can be used to enumerate all palettes:

```c
for (int i = 0; i < palette_count(); i++)
    printf("%s\n", palette_name(i));
```

## Display

### `present`

```c
void present(void);
```

Makes the current software framebuffer visible. A normal PixelRAM program calls it once at the end of each frame.

PixelRAM targets 60 FPS by default. `present()` observes the target configured by `set_target_fps()` and also processes the input transitions used by `poll_key_event()`.

On the web, simple one-shot programs do not have to call `present()`: until the first explicit `present()`, framebuffer changes are automatically displayed on the next browser frame. Calling `present()` once switches the program to the normal explicit frame-presentation model.

```c
while (!should_close())
{
    /* update */
    /* write framebuffer */
    present();
}
```

### `set_target_fps`

```c
void set_target_fps(int fps);
```

Sets the maximum presentation rate. PixelRAM starts at **60 FPS**.

```c
set_target_fps(30);
```

- Positive values request that many frames per second.
- `0` disables PixelRAM's explicit frame-rate cap.
- Negative values are treated as `0`.

On native builds PixelRAM applies the cap through its private backend. In WebAssembly builds presentation is synchronized to browser animation frames and PixelRAM skips/waits through animation frames as needed to honor lower targets. Therefore `set_target_fps(30)` behaves consistently on a 60 Hz or 120 Hz display. With `set_target_fps(0)`, a web build is still ultimately limited by browser animation frames.

This controls presentation frequency, not simulation semantics. For movement that should be independent of FPS, measure elapsed time with `seconds()` or `ticks_ms()`.

### `wait_vblank`

```c
void wait_vblank(void);
```

Waits for the next browser animation frame in a WebAssembly build. It is currently a no-op on native builds.

Normal applications usually do **not** need to call this directly because `present()` handles presentation timing.

### `set_pixel_aspect`

```c
void set_pixel_aspect(float ratio);
```

Sets the desired displayed pixel width divided by displayed pixel height. `1.0f` means square pixels. Values less than or equal to zero are treated as `1.0f`.

In the web build this sets the CSS custom property `--pixel-aspect-ratio` for the surrounding page to use when sizing the canvas. Native builds currently use square display pixels.

### `set_fullscreen`

```c
void set_fullscreen(bool enabled);
```

Enables or disables fullscreen display. Native builds change fullscreen immediately. Browsers require fullscreen changes to originate from a user gesture, so a web build performs an enabled fullscreen request on the next click on the PixelRAM canvas.

## Keyboard

### `key_down`

```c
bool key_down(pixel_key key);
```

Returns `true` for as long as the key is held down. Use this for continuous controls such as movement.

```c
if (key_down(pixel_key_left))
    player_x--;
```

### `key_pressed`

```c
bool key_pressed(pixel_key key);
```

Returns `true` for the frame in which the key changes from up to down. Use this for one-shot actions such as opening a menu.

### `key_released`

```c
bool key_released(pixel_key key);
```

Returns `true` for the frame in which the key changes from down to up.

Left and right Shift, Ctrl, and Alt keys are intentionally folded into `pixel_key_shift`, `pixel_key_ctrl`, and `pixel_key_alt`.

### `poll_key_event`

```c
bool poll_key_event(pixel_key_event *event);
```

Reads the next queued key transition. This exists mainly for ports and engines that consume an event stream rather than polling key state.

```c
pixel_key_event event;
while (poll_key_event(&event))
{
    if (event.pressed)
        /* key went down */;
    else
        /* key went up */;
}
```

Returns `false` when the queue is empty or `event` is `NULL`. If the fixed-size queue fills, PixelRAM drops the oldest transition rather than blocking rendering.

## Mouse

### `mouse_position`

```c
void mouse_position(int *x, int *y);
```

Returns the current mouse position in PixelRAM screen coordinates. Either pointer may be `NULL`.

### `mouse_delta`

```c
void mouse_delta(int *dx, int *dy);
```

Returns mouse movement for the current backend frame. Either pointer may be `NULL`.

When relative mouse mode is active in a browser, PixelRAM uses pointer-lock movement. Browser movement is accumulated and snapshotted at the frame boundary, so multiple `mouse_delta()` calls during the same frame see the same delta instead of consuming one another.

### `set_mouse_position`

```c
void set_mouse_position(int x, int y);
```

Moves the mouse pointer to the requested position where the platform allows it.

### `mouse_button_down`

```c
bool mouse_button_down(pixel_mouse_button button);
```

Returns `true` while the requested mouse button is held.

### `mouse_button_pressed`

```c
bool mouse_button_pressed(pixel_mouse_button button);
```

Returns `true` on the frame in which the mouse button is pressed.

### `mouse_button_released`

```c
bool mouse_button_released(pixel_mouse_button button);
```

Returns `true` on the frame in which the mouse button is released.

### `set_mouse_relative`

```c
void set_mouse_relative(bool enabled);
```

Enables relative mouse input, useful for first-person games. Native builds capture/hide the cursor. Web builds request browser pointer lock; because browsers require a user gesture, pointer lock is acquired on the next click on the canvas.

## Time

### `seconds`

```c
double seconds(void);
```

Returns a monotonic-style elapsed time value in seconds suitable for measuring durations and frame-to-frame elapsed time.

```c
double last = seconds();

while (!should_close())
{
    double now = seconds();
    double dt = now - last;
    last = now;

    x += speed * dt;
    present();
}
```

Do not interpret the absolute value as wall-clock/calendar time.

### `ticks_ms`

```c
uint32_t ticks_ms(void);
```

Returns elapsed time in milliseconds as a 32-bit unsigned integer. It is convenient for old game-engine code that expects millisecond ticks. Like every 32-bit millisecond counter, it eventually wraps around.

### `sleep_ms`

```c
void sleep_ms(uint32_t ms);
```

Waits for approximately the requested number of milliseconds. Native builds sleep through the platform backend. WebAssembly builds yield asynchronously so that the browser remains responsive.

For ordinary animation timing prefer `set_target_fps()` and `present()`; `sleep_ms()` is useful when an algorithm explicitly needs a delay.

## Pixel modes

```c
pixel_indexed8
pixel_rgb565
pixel_rgb24
pixel_rgba32
```

| Mode | Storage | Typical use |
| --- | --- | --- |
| `pixel_indexed8` | 1 byte palette index per pixel | classic palette effects, fire, plasma, teaching |
| `pixel_rgb565` | 16-bit packed direct color | compact software renderers / ports |
| `pixel_rgb24` | 3 bytes R, G, B per pixel | straightforward true-color framebuffer |
| `pixel_rgba32` | 4 bytes R, G, B, A per pixel | 32-bit engine framebuffers and ports |

For low-level teaching, `pixel_indexed8` is usually the best place to start: one byte in memory is one pixel, and changing the palette can change the entire image without rewriting framebuffer memory.

## Key constants

Printable keys use familiar names such as `pixel_key_a`, `pixel_key_0`, `pixel_key_space`, and `pixel_key_minus`. PixelRAM also defines arrows, navigation keys, Shift/Ctrl/Alt, and `pixel_key_f1` through `pixel_key_f12`.

Mouse buttons are:

```c
pixel_mouse_left
pixel_mouse_right
pixel_mouse_middle
```
