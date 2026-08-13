#include "pixelram.h"

#include <stdlib.h>
#include <time.h>

#define WIDTH  256
#define HEIGHT 128

static int clamp(int value, int low, int high)
{
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

int main(void)
{
    if (!screen_open(WIDTH, HEIGHT, pixel_indexed8, "PixelRAM fire"))
        return 1;

    srand((unsigned int)time(NULL));

    /* Black -> red -> orange -> yellow -> white. */
    for (int i = 0; i < 16; i++)
    {
        set_palette(i, i * 8, 0, 0);
        set_palette(i + 16, i * 8 + 128, i * 8, 0);
        set_palette(i + 32, 255, i * 8 + 128, i * 8);
        set_palette(i + 48, 255, 255, i * 8 + 128);
    }

    while (!should_close())
    {
        /* Heat the bottom two rows. */
        for (int y = HEIGHT - 2; y < HEIGHT; y++)
            for (int x = 10; x < WIDTH - 10; x++)
                set_pixel(x, y, 63);

        /* Pull heat upward and add a little random flicker. */
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                int color = get_pixel(x, y + 1) * 2;
                color += get_pixel(x - 1, y);
                color += get_pixel(x + 1, y);
                color /= 4;

                if (color > 0)
                    color += rand() % 7 - 3;

                set_pixel(x, y, (uint8_t)clamp(color, 0, 63));
            }
        }

        present();
    }

    screen_close();
    return 0;
}
