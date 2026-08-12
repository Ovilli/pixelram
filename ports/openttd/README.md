# OpenTTD

This is the first PixelRAM port of OpenTTD. It targets the pinned OpenTTD 15.3
release and uses only freely redistributable base sets:

- OpenGFX 8.0 graphics
- OpenSFX 1.0.3 sounds
- OpenMSX 0.4.2 music

Run:

```sh
make openttd
```

The initial port uses PixelRAM for the framebuffer, mouse, keyboard and
fullscreen handling. OpenTTD draws directly into PixelRAM's RGBA framebuffer;
there is no framebuffer conversion step.

The first milestone deliberately starts OpenTTD with its null sound and music
drivers while the graphics/input port is being stabilized. The free sound and
music sets are already downloaded and bundled so audio can be enabled next.

The default virtual resolution is 800x600. OpenTTD draws its own software mouse
cursor; PixelRAM does not pointer-lock the mouse for this port.

OpenTTD's Emscripten build needs liblzma for its compressed title game and
savegames. PixelRAM uses the `liblzma.py` port bundled with the pinned OpenTTD
source as an Emscripten external port. Nothing OpenTTD-specific has to be
installed into the workspace image.
