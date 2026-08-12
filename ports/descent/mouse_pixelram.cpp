/*
 * Mouse bridge from Chocolate Descent to the PixelRAM.
 */

#include "platform/mouse.h"

#include "pixelram.h"




void mouse_get_pos(
    int *x,
    int *y)
{
    mouse_position(
        x,
        y
    );

}


void mouse_get_delta(
    int *dx,
    int *dy)
{
    int x = 0;
    int y = 0;

    mouse_delta(
        &x,
        &y
    );

    if (dx)
        *dx =
            (int)(
                x *
                MouseScalar
            );

    if (dy)
        *dy =
            (int)(
                y *
                MouseScalar
            );
}


int mouse_get_btns()
{
    int buttons = 0;

    if (
        mouse_button_down(
            pixel_mouse_left
        )
    )
    {
        buttons |=
            1 << MBUTTON_LEFT;
    }

    if (
        mouse_button_down(
            pixel_mouse_right
        )
    )
    {
        buttons |=
            1 << MBUTTON_RIGHT;
    }

    if (
        mouse_button_down(
            pixel_mouse_middle
        )
    )
    {
        buttons |=
            1 << MBUTTON_MIDDLE;
    }

    return buttons;
}


void mouse_set_pos(
    int x,
    int y)
{
    set_mouse_position(
        x,
        y
    );
}
