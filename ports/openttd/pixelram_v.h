/*
 * PixelRAM video backend for OpenTTD.
 *
 * This file is part of the PixelRAM OpenTTD port. OpenTTD itself is
 * distributed under the GNU General Public License version 2.
 */

#ifndef VIDEO_PIXELRAM_H
#define VIDEO_PIXELRAM_H

#include "sdl2_v.h"

extern "C" {
#include "pixelram.h"
}

class VideoDriver_PixelRAM : public VideoDriver_SDL_Base {
public:
    std::string_view GetName() const override { return "pixelram"; }

    std::optional<std::string_view> Start(const StringList &param) override;
    void Stop() override;
    bool ChangeResolution(int w, int h) override;
    bool ToggleFullscreen(bool fullscreen) override;
    bool ClaimMousePointer() override;
    bool HasEfficient8Bpp() const override { return true; }

protected:
    Dimension GetScreenSize() const override { return {1067, 800}; }
    bool AllocateBackingStore(int w, int h, bool force = false) override;
    void *GetVideoPointer() override;
    void ReleaseVideoPointer() override {}
    bool CreateMainWindow(uint w, uint h, uint flags = 0) override;
    void Paint() override;
    void CheckPaletteAnim() override;
    void InputLoop() override;
    bool PollEvent() override;

private:
    pixel_mode PixelMode() const;
    void UpdatePixelRAMPalette();
    void UpdateMouse();
    uint ConvertKey(pixel_key key, char32_t *character) const;
};

class FVideoDriver_PixelRAM : public DriverFactoryBase {
public:
    FVideoDriver_PixelRAM() : DriverFactoryBase(Driver::DT_VIDEO, 10, "pixelram", "PixelRAM Video Driver") {}
    std::unique_ptr<Driver> CreateInstance() const override { return std::make_unique<VideoDriver_PixelRAM>(); }
};

#endif /* VIDEO_PIXELRAM_H */
