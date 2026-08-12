Prince web presentation fix

SDLPoP's Emscripten canvas can contain its 320x200 software image inside a wider
letterboxed backing canvas. The Prince port now declares a 320x200 source
raster and a 4:3 display aspect.

The common shell uses those declarations only for Prince:
- normal display crops SDL's internal bars and fills a 4:3 frame;
- CRT mode first reconstructs an exact 320x200 nearest-neighbour image, then
  applies the CRT shader.

Other PixelRAM programs keep the direct canvas path unchanged.
