/*
 * Chocolate Descent platform backend for the PixelRAM.
 *
 * Chocolate Descent already renders into an 8-bit indexed software buffer.
 * This adapter presents that buffer through PixelRAM instead of SDL.
 */

#include <stdio.h>
#include <string.h>

#include "2d/gr.h"
#include "misc/error.h"
#include "platform/key.h"
#include "platform/mouse.h"
#include "platform/platform.h"
#include "platform/s_midi.h"

#include "pixelram.h"


static bool pixelram_ready = false;
static uint8_t palette6[256 * 3] = {0};

int WindowWidth = 320;
int WindowHeight = 200;
int BestFit = 0;
int Fullscreen = 0;
int SwapInterval = 1;

extern uint8_t *gr_video_memory;


static int descent_key(pixel_key key)
{
    switch (key)
    {
        case pixel_key_0: return KEY_0;
        case pixel_key_1: return KEY_1;
        case pixel_key_2: return KEY_2;
        case pixel_key_3: return KEY_3;
        case pixel_key_4: return KEY_4;
        case pixel_key_5: return KEY_5;
        case pixel_key_6: return KEY_6;
        case pixel_key_7: return KEY_7;
        case pixel_key_8: return KEY_8;
        case pixel_key_9: return KEY_9;

        case pixel_key_a: return KEY_A;
        case pixel_key_b: return KEY_B;
        case pixel_key_c: return KEY_C;
        case pixel_key_d: return KEY_D;
        case pixel_key_e: return KEY_E;
        case pixel_key_f: return KEY_F;
        case pixel_key_g: return KEY_G;
        case pixel_key_h: return KEY_H;
        case pixel_key_i: return KEY_I;
        case pixel_key_j: return KEY_J;
        case pixel_key_k: return KEY_K;
        case pixel_key_l: return KEY_L;
        case pixel_key_m: return KEY_M;
        case pixel_key_n: return KEY_N;
        case pixel_key_o: return KEY_O;
        case pixel_key_p: return KEY_P;
        case pixel_key_q: return KEY_Q;
        case pixel_key_r: return KEY_R;
        case pixel_key_s: return KEY_S;
        case pixel_key_t: return KEY_T;
        case pixel_key_u: return KEY_U;
        case pixel_key_v: return KEY_V;
        case pixel_key_w: return KEY_W;
        case pixel_key_x: return KEY_X;
        case pixel_key_y: return KEY_Y;
        case pixel_key_z: return KEY_Z;

        case pixel_key_minus:         return KEY_MINUS;
        case pixel_key_equals:        return KEY_EQUAL;
        case pixel_key_comma:         return KEY_COMMA;
        case pixel_key_period:        return KEY_PERIOD;
        case pixel_key_slash:         return KEY_DIVIDE;
        case pixel_key_semicolon:     return KEY_SEMICOL;
        case pixel_key_apostrophe:    return KEY_RAPOSTRO;
        case pixel_key_left_bracket:  return KEY_LBRACKET;
        case pixel_key_right_bracket: return KEY_RBRACKET;
        case pixel_key_grave:         return KEY_LAPOSTRO;

        case pixel_key_escape:    return KEY_ESC;
        case pixel_key_enter:     return KEY_ENTER;
        case pixel_key_backspace: return KEY_BACKSP;
        case pixel_key_tab:       return KEY_TAB;
        case pixel_key_space:     return KEY_SPACEBAR;

        case pixel_key_left:  return KEY_LEFT;
        case pixel_key_right: return KEY_RIGHT;
        case pixel_key_up:    return KEY_UP;
        case pixel_key_down:  return KEY_DOWN;

        case pixel_key_insert:    return KEY_INSERT;
        case pixel_key_home:      return KEY_HOME;
        case pixel_key_page_up:   return KEY_PAGEUP;
        case pixel_key_delete:    return KEY_DELETE;
        case pixel_key_end:       return KEY_END;
        case pixel_key_page_down: return KEY_PAGEDOWN;

        case pixel_key_shift: return KEY_LSHIFT;
        case pixel_key_ctrl:  return KEY_LCTRL;
        case pixel_key_alt:   return KEY_LALT;

        case pixel_key_f1:  return KEY_F1;
        case pixel_key_f2:  return KEY_F2;
        case pixel_key_f3:  return KEY_F3;
        case pixel_key_f4:  return KEY_F4;
        case pixel_key_f5:  return KEY_F5;
        case pixel_key_f6:  return KEY_F6;
        case pixel_key_f7:  return KEY_F7;
        case pixel_key_f8:  return KEY_F8;
        case pixel_key_f9:  return KEY_F9;
        case pixel_key_f10: return KEY_F10;
        case pixel_key_f11: return KEY_F11;
        case pixel_key_f12: return KEY_F12;

        default:
            return -1;
    }
}


static void update_mouse_buttons(void)
{
    static bool previous[3] = { false, false, false };

    const pixel_mouse_button pixelram_buttons[3] = {
        pixel_mouse_left,
        pixel_mouse_right,
        pixel_mouse_middle
    };

    const int descent_buttons[3] = {
        MBUTTON_LEFT,
        MBUTTON_RIGHT,
        MBUTTON_MIDDLE
    };

    for (int i = 0; i < 3; i++)
    {
        bool down =
            mouse_button_down(
                pixelram_buttons[i]
            );

        if (down && !previous[i])
            MousePressed(descent_buttons[i]);

        if (!down && previous[i])
            MouseReleased(descent_buttons[i]);

        previous[i] = down;
    }
}


static bool mode_dimensions(
    int mode,
    int *width,
    int *height)
{
    int w = 0;
    int h = 0;

    switch (mode)
    {
        case SM_320x200C:
            w = 320; h = 200;
            break;

        case SM_320x240U:
            w = 320; h = 240;
            break;

        case SM_320x400U:
            w = 320; h = 400;
            break;

        case SM_640x400V:
            w = 640; h = 400;
            break;

        case SM_640x480V:
            w = 640; h = 480;
            break;

        case SM_800x600V:
            w = 800; h = 600;
            break;

        case SM_1024x768V:
            w = 1024; h = 768;
            break;

        case SM_1280x1024V:
            w = 1280; h = 1024;
            break;

        case 19:
            w = 320; h = 100;
            break;

        case 21:
            w = 160; h = 100;
            break;

        default:
            return false;
    }

    if (width)
        *width = w;

    if (height)
        *height = h;

    return true;
}


static void set_descent_pixel_aspect(
    int width,
    int height)
{
    /*
     * Match the native Chocolate Descent backend, which fits every
     * software video mode into a 4:3 output rectangle.
     */
    set_pixel_aspect(
        (4.0f * height) /
        (3.0f * width)
    );
}


int plat_init()
{
    /*
     * Keep Chocolate Descent's configuration parser available, but the
     * browser display itself is deliberately the classic 320x200 mode.
     */
    plat_read_chocolate_cfg();

    WindowWidth = 320;
    WindowHeight = 200;
    NoOpenGL = true;

    return 0;
}


int plat_create_window()
{
    if (pixelram_ready)
        return 0;

    if (!screen_open(
            320,
            200,
            pixel_indexed8,
            "Chocolate Descent"))
    {
        return 1;
    }

    set_descent_pixel_aspect(
        320,
        200
    );

    for (int i = 0; i < 256; i++)
    {
        set_palette(
            i,
            palette6[i * 3 + 0] * 255 / 63,
            palette6[i * 3 + 1] * 255 / 63,
            palette6[i * 3 + 2] * 255 / 63
        );
    }

    pixelram_ready = true;

    return 0;
}


void plat_close_window()
{
    if (!pixelram_ready)
        return;

    screen_close();
    pixelram_ready = false;
}


void plat_close()
{
    plat_close_window();
}


void plat_display_error(
    const char *msg)
{
    fprintf(
        stderr,
        "Chocolate Descent: %s\n",
        msg ? msg : "(unknown error)"
    );
}


void plat_update_window()
{
    /*
     * An embedded browser canvas has no independent OS window to resize.
     * Keep Hackschule's responsive fit-to-page behavior and apply only
     * the setting that has a direct web equivalent.
     */
    set_fullscreen(
        Fullscreen != 0
    );
}


/*
 * Present for compatibility with code that expects the SDL backend helper.
 * The web shell itself handles the visible fullscreen/layout behavior.
 */
void plat_toggle_fullscreen()
{
    set_fullscreen(
        Fullscreen != 0
    );
}


int plat_check_gr_mode(
    int mode)
{
    return
        mode_dimensions(
            mode,
            nullptr,
            nullptr
        )
        ? 0
        : 11;
}


int plat_set_gr_mode(
    int mode)
{
    int width = 0;
    int height = 0;

    if (
        !mode_dimensions(
            mode,
            &width,
            &height
        )
    )
    {
        return 11;
    }

    if (
        !pixelram_ready &&
        plat_create_window() != 0
    )
    {
        return 1;
    }

    if (
        !screen_set_mode(
            width,
            height,
            pixel_indexed8
        )
    )
    {
        return 1;
    }

    WindowWidth = width;
    WindowHeight = height;

    set_descent_pixel_aspect(
        width,
        height
    );

    plat_write_palette(
        0,
        255,
        gr_palette
    );

    return 0;
}


void plat_write_palette(
    int start,
    int end,
    uint8_t *data)
{
    if (!data)
        return;

    if (start < 0)
        start = 0;

    if (end > 255)
        end = 255;

    if (end < start)
        return;

    for (
        int index = start;
        index <= end;
        index++)
    {
        int source =
            (index - start) * 3;

        uint8_t r =
            data[source + 0];

        uint8_t g =
            data[source + 1];

        uint8_t b =
            data[source + 2];

        palette6[index * 3 + 0] = r;
        palette6[index * 3 + 1] = g;
        palette6[index * 3 + 2] = b;

        if (pixelram_ready)
        {
            set_palette(
                index,
                (uint8_t)(r * 255 / 63),
                (uint8_t)(g * 255 / 63),
                (uint8_t)(b * 255 / 63)
            );
        }
    }
}


void plat_blank_palette()
{
    uint8_t black[256 * 3] = {0};

    plat_write_palette(
        0,
        255,
        black
    );
}


void plat_read_palette(
    uint8_t *dest)
{
    if (dest)
    {
        memcpy(
            dest,
            palette6,
            sizeof(palette6)
        );
    }
}


void plat_wait_for_vbl()
{
    wait_vblank();
}


static void copy_video_memory()
{
    if (
        !pixelram_ready ||
        !gr_video_memory ||
        !grd_curscreen
    )
    {
        return;
    }

    uint8_t *destination =
        (uint8_t *)framebuffer();

    uint8_t *source =
        gr_video_memory;

    int width =
        grd_curscreen->sc_w;

    int height =
        grd_curscreen->sc_h;

    int source_pitch =
        grd_curscreen->
            sc_canvas.
            cv_bitmap.
            bm_rowsize;

    int copy_width =
        width < screen_width()
        ? width
        : screen_width();

    int copy_height =
        height < screen_height()
        ? height
        : screen_height();

    for (
        int y = 0;
        y < copy_height;
        y++)
    {
        memcpy(
            destination +
                y * screen_pitch(),
            source +
                y * source_pitch,
            (size_t)copy_width
        );
    }
}


void plat_present_canvas(
    int sync)
{
    (void)sync;

#ifdef __EMSCRIPTEN__
    S_WebMusicPump();
#endif

    copy_video_memory();

    /*
     * present already yields to requestAnimationFrame in the web build.
     */
    present();
}


void plat_blit_canvas(
    grs_canvas *canv)
{
    if (
        !canv ||
        !gr_video_memory
    )
    {
        return;
    }

    if (
        canv->
            cv_bitmap.
            bm_type ==
        BM_SVGA
    )
    {
        int rows =
            canv->
                cv_bitmap.
                bm_h;

        int width =
            canv->
                cv_bitmap.
                bm_w;

        int source_pitch =
            canv->
                cv_bitmap.
                bm_rowsize;

        for (
            int y = 0;
            y < rows;
            y++)
        {
            memcpy(
                gr_video_memory +
                    y * width,
                canv->
                    cv_bitmap.
                    bm_data +
                    y * source_pitch,
                (size_t)width
            );
        }
    }
}


void plat_do_events()
{
    pixel_key_event event;

    while (
        poll_key_event(
            &event
        )
    )
    {
        int key =
            descent_key(
                event.key
            );

        if (key < 0)
            continue;

        if (event.pressed)
            KeyPressed(key);
        else
            KeyReleased(key);
    }

    update_mouse_buttons();
}


void plat_set_mouse_relative_mode(
    int state)
{
    set_mouse_relative(
        state != 0
    );
}
