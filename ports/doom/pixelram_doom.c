/*
 * PixelRAM implementation for the doomgeneric port.
 *
 * doomgeneric already exports data symbols named screen_width,
 * screen_height and key_down. Keep PixelRAM's public API unchanged for
 * ordinary programs, but privately rename those three symbols in this
 * translation unit so the two libraries can coexist.
 */
#define screen_width  pixelram_screen_width
#define screen_height pixelram_screen_height
#define key_down      pixelram_key_down

#include "../../pixelram.c"
