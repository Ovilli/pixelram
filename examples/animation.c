#include "pixelram.h"

int main(void)
{
    if (!screen_open(320, 180, pixel_indexed8, "PixelRAM animation"))
        return 1;

    int x = 0;
    int direction = 1;
    int y = screen_height() / 2;

    while (!should_close())
    {
        set_pixel(x, y, 0);

        x += direction;
        if (x == 0 || x == screen_width() - 1)
            direction = -direction;

        set_pixel(x, y, 10);
        present();
    }

    screen_close();
    return 0;
}
