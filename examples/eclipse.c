#include "pixelram.h"



//https://www.thecrazyprogrammer.com/2016/12/bresenhams-midpoint-circle-algorithm-c-c.html

void drawCircle(int cx,int cy, int radius, int color_r,int color_g, int color_b) {
int x = 0;
int y = radius;
int p = 1 - radius;
while(x <= y){
    set_pixel_rgb(cx+x,cy+y,color_r,color_g,color_b);
    set_pixel_rgb(cx-x,cy+y,color_r,color_g,color_b);
    set_pixel_rgb(cx+x,cy-y,color_r,color_g,color_b);
    set_pixel_rgb(cx-x,cy-y,color_r,color_g,color_b);
    set_pixel_rgb(cx+y,cy+x,color_r,color_g,color_b);
    set_pixel_rgb(cx-y,cy+x,color_r,color_g,color_b);
    set_pixel_rgb(cx+y,cy-x,color_r,color_g,color_b);
    set_pixel_rgb(cx-y,cy-x,color_r,color_g,color_b);

    x++;
    if(p<0){
        p+=2 * x + 1;
    }else {
        y--;
        p+=2*(x-y)+1;
    }
}
}


int main(void)
{
    if (!screen_open(320, 180, pixel_rgb24, "PixelRAM"))
        return 1;

    while (!should_close())
    {
        int x = 160;
        int y = 90;
        int r = 50;

        //https://www.rapidtables.com/web/color/RGB_Color.html
        int c_r = 255;
        int c_g = 255;
        int c_b = 255;
        

        //https://www.geeksforgeeks.org/c/c-loops/
        for (int i = 0;i < 10; i++){
            drawCircle(x,y,r,c_r,c_g,c_b);
            r++;
            
            if(c_r > 64){
                c_r -= 10;
            }
            if(c_g > 64){
                c_g-= 10;
            }
            if(c_b > 64){
                c_b -= 10;
            }
        }
        

        present();
    }

    screen_close();
    return 0;
}




// #FIX-NEEDED : Random Black Points 