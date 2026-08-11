/*
 * doom_pixelram.c
 *
 * doomgeneric platform adapter for the PixelRAM.
 *
 * The important part: this build uses DOOM's 8-bit CMAP256 path.
 * DG_ScreenBuffer is therefore a real 320x200 array of palette indices.
 */

/*
 * doomgeneric already defines global variables named screen_width and
 * screen_height. Rename PixelRAM's declarations locally while including
 * pixelram.h so both APIs can coexist in this translation unit.
 */
#define screen_width  pixelram_screen_width
#define screen_height pixelram_screen_height
#include "pixelram.h"
#undef screen_width
#undef screen_height

#include "doomgeneric.h"
#include "doomkeys.h"
#include "i_video.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DOOM_W 320
#define DOOM_H 200


static unsigned char doom_key_from_pixelram(
    pixel_key key)
{
    /*
     * doomgeneric accepts ordinary ASCII for letters,
     * digits and these punctuation keys.
     */
    if (
        (key >= pixel_key_a &&
         key <= pixel_key_z) ||

        (key >= pixel_key_0 &&
         key <= pixel_key_9) ||

        key == pixel_key_minus ||
        key == pixel_key_equals ||
        key == pixel_key_comma ||
        key == pixel_key_period
    )
    {
        return
            (unsigned char)key;
    }


    switch (key)
    {
        case pixel_key_enter:
            return KEY_ENTER;

        case pixel_key_escape:
            return KEY_ESCAPE;

        case pixel_key_tab:
            return KEY_TAB;

        case pixel_key_backspace:
            return KEY_BACKSPACE;


        case pixel_key_left:
            return KEY_LEFTARROW;

        case pixel_key_right:
            return KEY_RIGHTARROW;

        case pixel_key_up:
            return KEY_UPARROW;

        case pixel_key_down:
            return KEY_DOWNARROW;


        /*
         * Match doomgeneric's established SDL/Emscripten mapping.
         */
        case pixel_key_ctrl:
            return KEY_FIRE;

        case pixel_key_space:
            return KEY_USE;

        case pixel_key_shift:
            return KEY_RSHIFT;

        case pixel_key_alt:
            return KEY_LALT;


        case pixel_key_f1:
            return KEY_F1;

        case pixel_key_f2:
            return KEY_F2;

        case pixel_key_f3:
            return KEY_F3;

        case pixel_key_f4:
            return KEY_F4;

        case pixel_key_f5:
            return KEY_F5;

        case pixel_key_f6:
            return KEY_F6;

        case pixel_key_f7:
            return KEY_F7;

        case pixel_key_f8:
            return KEY_F8;

        case pixel_key_f9:
            return KEY_F9;

        case pixel_key_f10:
            return KEY_F10;

        case pixel_key_f11:
            return KEY_F11;

        case pixel_key_f12:
            return KEY_F12;

        default:
            return 0;
    }
}


void DG_Init(void)
{
    if (!screen_open(
            DOOM_W,
            DOOM_H,
            pixel_indexed8,
            "DOOM"))
    {
        fprintf(
            stderr,
            "Could not initialize PixelRAM\n"
        );

        exit(1);
    }


    /*
     * DOOM's 320x200 framebuffer was intended for a 4:3 display.
     */
    set_pixel_aspect(
        5.0f / 6.0f
    );


    printf(
        "DOOM -> doomgeneric -> PixelRAM -> raylib -> WebAssembly\n"
        "Framebuffer: %dx%d, 8-bit indexed colour\n",
        DOOM_W,
        DOOM_H
    );
}


void DG_DrawFrame(void)
{
    /*
     * With -DCMAP256, doomgeneric has already converted its internal
     * 320x200 video buffer into 8-bit DG_ScreenBuffer.
     *
     * So this is literally just a PixelRAM framebuffer copy.
     */
    memcpy(
        framebuffer(),
        DG_ScreenBuffer,
        DOOM_W * DOOM_H
    );


    /*
     * DOOM changes palettes for effects such as damage flashes.
     * i_video.c exposes the current 256 colours in CMAP256 mode.
     */
    if (palette_changed)
    {
        for (int i = 0; i < 256; i++)
        {
            set_palette(
                i,
                (uint8_t)colors[i].r,
                (uint8_t)colors[i].g,
                (uint8_t)colors[i].b
            );
        }

        palette_changed = false;
    }


    present();
}


void DG_SleepMs(
    uint32_t ms)
{
    sleep_ms(ms);
}


uint32_t DG_GetTicksMs(void)
{
    return ticks_ms();
}


int DG_GetKey(
    int *pressed,
    unsigned char *doom_key)
{
    pixel_key_event event;


    while (
        poll_key_event(
            &event
        )
    )
    {
        unsigned char key =
            doom_key_from_pixelram(
                event.key
            );


        if (key == 0)
            continue;


        *pressed =
            event.pressed
            ? 1
            : 0;

        *doom_key =
            key;

        return 1;
    }


    return 0;
}


void DG_SetWindowTitle(
    const char *title)
{
    set_title(title);
}


int main(
    int argc,
    char **argv)
{
    /*
     * Browser builds normally have no useful command line.
     *
     * With no arguments, jump directly into the shareware E1M1 level.
     */
    char *demo_argv[] =
    {
        argv[0],
        "-iwad",
        "doom1.wad",
        "-warp",
        "1",
        "1",
        "-skill",
        "3"
    };


    if (argc <= 1)
    {
        doomgeneric_Create(
            8,
            demo_argv
        );
    }
    else
    {
        doomgeneric_Create(
            argc,
            argv
        );
    }


    /*
     * Deliberately old-fashioned sequential main loop.
     *
     * present() and sleep_ms() yield to the browser through
     * Asyncify when necessary, then C resumes exactly where it stopped.
     */
    while (!should_close())
    {
        doomgeneric_Tick();
    }


    screen_close();

    return 0;
}
