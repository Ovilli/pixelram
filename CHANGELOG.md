# Changelog

## Unreleased

- Add `clear()` for indexed framebuffers and `clear_rgb()` for direct-color framebuffers
- Use `clear()` in the animation example and document the clear → draw → present frame pattern

## 0.1.0

Initial PixelRAM release.

- Indexed 8-bit, RGB565, RGB24 and RGBA32 software framebuffers
- Direct framebuffer access
- `set_pixel()` and `get_pixel()` helpers with safe out-of-bounds behavior
- RGB pixel helpers
- 88 built-in palettes shared with Pixelflow Canvas
- Keyboard transition queue suitable for game-engine ports
- Absolute and relative mouse input
- Native and WebAssembly-aware timing and presentation
- Fire demo derived from the Pixelflow Canvas teaching example
