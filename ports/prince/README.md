# Prince of Persia / SDLPoP

Put the complete DOS Prince of Persia game data set in `prince-data/` next to the top-level Makefile. PixelRAM does not redistribute those assets. `make prince` checks for `PRINCE.DAT` and mounts the whole directory as `/data`.

The browser shell also supplies normalized 320x200 pointer coordinates so SDLPoP menu hit-testing matches the visible 4:3 display.
