/*
 * SDLPoP renders the original Prince of Persia game at 320x200, but
 * SDL/Emscripten may resize the browser canvas to a much larger backing
 * resolution. Tell the PixelRAM shell which raster the CRT shader should
 * reconstruct.
 */
window.PIXELRAM_LOGICAL_WIDTH = 320;
window.PIXELRAM_LOGICAL_HEIGHT = 200;
