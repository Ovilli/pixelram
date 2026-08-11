#ifndef PIXELRAM_H
#define PIXELRAM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PIXELRAM_VERSION_MAJOR 0
#define PIXELRAM_VERSION_MINOR 1
#define PIXELRAM_VERSION_PATCH 14
#define PIXELRAM_VERSION "0.1.14"

/*
 * PixelRAM is a small software framebuffer API.
 *
 * pixel_indexed8 stores one palette index per pixel.
 * The remaining modes store color values directly in the framebuffer.
 */
typedef enum {
    pixel_indexed8,
    pixel_rgb565,
    pixel_rgb24,
    pixel_rgba32
} pixel_mode;

/* Printable keys deliberately use their ASCII values. */
typedef enum {
    pixel_key_0 = '0',
    pixel_key_1 = '1',
    pixel_key_2 = '2',
    pixel_key_3 = '3',
    pixel_key_4 = '4',
    pixel_key_5 = '5',
    pixel_key_6 = '6',
    pixel_key_7 = '7',
    pixel_key_8 = '8',
    pixel_key_9 = '9',

    pixel_key_a = 'a',
    pixel_key_b = 'b',
    pixel_key_c = 'c',
    pixel_key_d = 'd',
    pixel_key_e = 'e',
    pixel_key_f = 'f',
    pixel_key_g = 'g',
    pixel_key_h = 'h',
    pixel_key_i = 'i',
    pixel_key_j = 'j',
    pixel_key_k = 'k',
    pixel_key_l = 'l',
    pixel_key_m = 'm',
    pixel_key_n = 'n',
    pixel_key_o = 'o',
    pixel_key_p = 'p',
    pixel_key_q = 'q',
    pixel_key_r = 'r',
    pixel_key_s = 's',
    pixel_key_t = 't',
    pixel_key_u = 'u',
    pixel_key_v = 'v',
    pixel_key_w = 'w',
    pixel_key_x = 'x',
    pixel_key_y = 'y',
    pixel_key_z = 'z',

    pixel_key_minus         = '-',
    pixel_key_equals        = '=',
    pixel_key_comma         = ',',
    pixel_key_period        = '.',
    pixel_key_slash         = '/',
    pixel_key_semicolon     = ';',
    pixel_key_apostrophe    = '\'',
    pixel_key_left_bracket  = '[',
    pixel_key_right_bracket = ']',
    pixel_key_grave         = '`',

    pixel_key_escape = 256,
    pixel_key_space,
    pixel_key_enter,
    pixel_key_tab,
    pixel_key_backspace,

    pixel_key_left,
    pixel_key_right,
    pixel_key_up,
    pixel_key_down,

    pixel_key_insert,
    pixel_key_home,
    pixel_key_page_up,
    pixel_key_delete,
    pixel_key_end,
    pixel_key_page_down,

    pixel_key_shift,
    pixel_key_ctrl,
    pixel_key_alt,

    pixel_key_f1,
    pixel_key_f2,
    pixel_key_f3,
    pixel_key_f4,
    pixel_key_f5,
    pixel_key_f6,
    pixel_key_f7,
    pixel_key_f8,
    pixel_key_f9,
    pixel_key_f10,
    pixel_key_f11,
    pixel_key_f12
} pixel_key;

typedef struct {
    pixel_key key;
    bool pressed;
} pixel_key_event;

typedef enum {
    pixel_mouse_left,
    pixel_mouse_right,
    pixel_mouse_middle
} pixel_mouse_button;

/* Screen --------------------------------------------------------------- */

bool screen_open(int width, int height, pixel_mode mode, const char *title);
bool screen_set_mode(int width, int height, pixel_mode mode);

void screen_close(void);
bool should_close(void);
void set_title(const char *title);

int screen_width(void);
int screen_height(void);
int screen_pitch(void);
pixel_mode screen_mode(void);

/* Framebuffer ---------------------------------------------------------- */

void *framebuffer(void);
size_t framebuffer_size(void);

/* Indexed pixels and palettes ----------------------------------------- */

/*
 * set_pixel() and get_pixel() operate in pixel_indexed8 mode.
 * Out-of-bounds writes are ignored; out-of-bounds reads return 0.
 */
void set_pixel(int x, int y, uint8_t index);
uint8_t get_pixel(int x, int y);

void set_palette(int index, uint8_t r, uint8_t g, uint8_t b);
void get_palette(int index, uint8_t *r, uint8_t *g, uint8_t *b);

/* Load one of the built-in Pixelflow-compatible palettes by name. */
bool use_palette(const char *name);
int palette_count(void);
const char *palette_name(int index);

/* Direct-color pixels -------------------------------------------------- */

/*
 * set_pixel_rgb() works in pixel_rgb565, pixel_rgb24 and pixel_rgba32.
 * get_pixel_rgb() works in every mode; in pixel_indexed8 it resolves the
 * palette index to RGB. Out-of-bounds reads return false and write zeros.
 */
void set_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);
bool get_pixel_rgb(int x, int y, uint8_t *r, uint8_t *g, uint8_t *b);

static inline uint16_t rgb565_pack(uint8_t r, uint8_t g, uint8_t b) {
    return (uint16_t)(
        ((uint16_t)(r >> 3) << 11) |
        ((uint16_t)(g >> 2) << 5) |
        ((uint16_t)(b >> 3))
    );
}

/* Display -------------------------------------------------------------- */

void present(void);
void wait_vblank(void);

/* Default: 60. Use 0 to disable PixelRAM's frame-rate cap. */
void set_target_fps(int fps);

/* Displayed pixel width / displayed pixel height. 1.0 means square. */
void set_pixel_aspect(float ratio);

/* On the web, enabling fullscreen takes effect on the next user click. */
void set_fullscreen(bool enabled);

/* Keyboard ------------------------------------------------------------- */

bool key_down(pixel_key key);
bool key_pressed(pixel_key key);
bool key_released(pixel_key key);

/* Preserves transitions in a queue, useful for ports such as DOOM. */
bool poll_key_event(pixel_key_event *event);

/* Mouse ---------------------------------------------------------------- */

void mouse_position(int *x, int *y);
void mouse_delta(int *dx, int *dy);
void set_mouse_position(int x, int y);

bool mouse_button_down(pixel_mouse_button button);
bool mouse_button_pressed(pixel_mouse_button button);
bool mouse_button_released(pixel_mouse_button button);

/* On the web, relative mode requests pointer lock on the next click. */
void set_mouse_relative(bool enabled);

/* Time ----------------------------------------------------------------- */

double seconds(void);
uint32_t ticks_ms(void);
void sleep_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif
