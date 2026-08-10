#include "pixelram.h"

#include <stdlib.h>
#include <time.h>

#define WIDTH  256
#define HEIGHT 128

static int clamp_int(int value, int low, int high)
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
        set_palette(i,      i * 8,       0,           0);
        set_palette(i + 16, i * 8 + 128, i * 8,      0);
        set_palette(i + 32, 255,         i * 8 + 128, i * 8);
        set_palette(i + 48, 255,         255,         i * 8 + 128);
    }

    while (!should_close())
    {
        /* Keep two rows at the bottom hot. */
        for (int y = 126; y <= 127; y++)
            for (int x = 10; x <= 245; x++)
                set_pixel(x, y, 63);

        /* Apply the same tiny filter used by the Pixelflow Canvas demo. */
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                int c = get_pixel(x, y + 1) * 2;
                c += get_pixel(x - 1, y);
                c += get_pixel(x + 1, y);
                c /= 4;

                if (c > 0)
                    c += rand() % 7 - 3;

                c = clamp_int(c, 0, 63);
                set_pixel(x, y, (uint8_t)c);
            }
        }

        present();
    }

    screen_close();
    return 0;
}
