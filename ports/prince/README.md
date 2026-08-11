# Prince of Persia browser port

SDLPoP's original game raster is 320x200, but its desktop defaults create a
640x400 window. That made the PixelRAM CRT shader see 400 source rows and
caused moire/ring artifacts.

For the browser build we keep SDLPoP's SDL2 software renderer, but generate a
port-specific SDLPoP.ini with:

    pop_window_width = 320
    pop_window_height = 200
    use_correct_aspect_ratio = false
    use_integer_scaling = false
    scaling_type = sharp

The HTML shell then enlarges the actual 320x200 canvas for display, exactly
like a normal PixelRAM framebuffer. No special CRT-resolution override is
needed.

Build with:

    make prince
