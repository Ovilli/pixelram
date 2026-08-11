Prince CRT fix v2

SDLPoP's browser canvas can be much larger than the original 320x200 raster.

The shell now detects ports which declare a logical framebuffer size different
from the actual browser canvas. Before applying the CRT shader it creates an
offscreen logical framebuffer using nearest-neighbour scaling and uploads that
exact raster to the CRT shader.

For Prince this means:

    SDL canvas (large) -> 320x200 logical canvas -> CRT shader

Other PixelRAM programs whose canvas already equals their logical framebuffer
continue to go directly into the CRT shader.

Rebuild with:

    make prince
