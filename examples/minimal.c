#include "pixelram.h"

int main(void)
{
    if (!screen_open(320, 180, pixel_indexed8, "PixelRAM"))
        return 1;

    set_pixel(screen_width() / 2, screen_height() / 2, 10);
    return 0;
}
