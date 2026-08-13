#include "pixelram.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    assert(palette_count() == 88);
    assert(screen_open(4, 3, pixel_indexed8, "test"));
    assert(screen_width() == 4 && screen_height() == 3 && screen_pitch() == 4);
    uint8_t r=0,g=0,b=0;
    get_palette(1,&r,&g,&b);
    assert(r==0 && g==0 && b==0xaa);
    assert(use_palette("1bit_monitor_glow"));
    get_palette(0,&r,&g,&b); assert(r==0x22 && g==0x23 && b==0x23);
    get_palette(1,&r,&g,&b); assert(r==0xf0 && g==0xf6 && b==0xf0);
    get_palette(2,&r,&g,&b); assert(r==0 && g==0 && b==0);
    assert(!use_palette("does_not_exist"));
    set_pixel(2,1,7); assert(get_pixel(2,1)==7);
    set_pixel(-1,1,9); assert(get_pixel(-1,1)==0);
    assert(get_pixel(99,99)==0);
    clear(23);
    for (size_t i = 0; i < framebuffer_size(); i++)
        assert(((uint8_t *)framebuffer())[i] == 23);

    assert(screen_set_mode(2,2,pixel_rgb24));
    clear_rgb(9,19,29);
    for (int y = 0; y < 2; y++)
        for (int x = 0; x < 2; x++) {
            assert(get_pixel_rgb(x,y,&r,&g,&b));
            assert(r==9 && g==19 && b==29);
        }
    set_pixel_rgb(1,1,12,34,56);
    assert(get_pixel_rgb(1,1,&r,&g,&b)); assert(r==12&&g==34&&b==56);

    assert(screen_set_mode(2,2,pixel_rgba32));
    clear_rgb(30,60,90);
    for (size_t i = 0; i < 4; i++) {
        const uint8_t *pixel = (const uint8_t *)framebuffer() + i * 4;
        assert(pixel[0]==30 && pixel[1]==60 && pixel[2]==90 && pixel[3]==255);
    }
    set_pixel_rgb(0,0,200,100,50);
    assert(get_pixel_rgb(0,0,&r,&g,&b)); assert(r==200&&g==100&&b==50);

    assert(screen_set_mode(2,2,pixel_rgb565));
    clear_rgb(255,128,0);
    for (size_t i = 0; i < 4; i++)
        assert(((const uint16_t *)framebuffer())[i] == rgb565_pack(255,128,0));
    set_pixel_rgb(0,0,255,128,0);
    assert(get_pixel_rgb(0,0,&r,&g,&b)); assert(r>=248 && g>=125 && b==0);

    assert(!get_pixel_rgb(-1,0,&r,&g,&b)); assert(r==0&&g==0&&b==0);
    screen_close();
    puts("PixelRAM tests passed");
}
