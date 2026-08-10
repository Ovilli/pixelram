#include "pixelram.h"

int main(void)
{
    if (!screen_open(320, 180, pixel_indexed8, "PixelRAM"))
        return 1;

    while (!should_close())
    {
        for (int x = 0; x < screen_width(); x++)
        {
            int y = x * screen_height() / screen_width();
            set_pixel(x, y, 15);
        }

        present();
    }

    screen_close();
    return 0;
}
