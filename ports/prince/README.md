Prince CRT logical-resolution fix

SDLPoP draws Prince of Persia at 320x200, while SDL/Emscripten can give the
HTML canvas a much larger backing resolution. The PixelRAM CRT shader used to
mistake that enlarged canvas for the original raster, which produced far too
many scanlines and visible moire/dark rings.

This patch:
- teaches shell.html about an optional logical framebuffer size;
- makes the CRT shader use that logical size for Gaussian pixel/scanline
  reconstruction;
- tells the Prince port explicitly that its logical raster is 320x200.

Rebuild with:

    make prince

No SDLPoP source modification is required for this fix.
