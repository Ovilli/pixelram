/*
 * PixelRAM video backend for OpenTTD.
 *
 * This file is part of the PixelRAM OpenTTD port. OpenTTD itself is
 * distributed under the GNU General Public License version 2.
 */

#include "../stdafx.h"
#include "../openttd.h"
#include "../gfx_func.h"
#include "../gfx_type.h"
#include "../blitter/factory.hpp"
#include "../core/geometry_func.hpp"
#include "../window_func.h"
#include "pixelram_v.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "../safeguards.h"

static FVideoDriver_PixelRAM iFVideoDriver_PixelRAM;

pixel_mode VideoDriver_PixelRAM::PixelMode() const
{
    switch (BlitterFactory::GetCurrentBlitter()->GetScreenDepth()) {
        case 8: return pixel_indexed8;
        case 32: return pixel_rgba32;
        default: return pixel_rgba32;
    }
}

std::optional<std::string_view> VideoDriver_PixelRAM::Start(const StringList &param)
{
    if (BlitterFactory::GetCurrentBlitter()->GetScreenDepth() != 8 &&
            BlitterFactory::GetCurrentBlitter()->GetScreenDepth() != 32) {
        return "PixelRAM supports OpenTTD's 8-bpp and 32-bpp blitters";
    }

    if (_cur_resolution.width == 0 || _cur_resolution.height == 0) {
        _cur_resolution = {800, 600};
    }

    auto result = VideoDriver_SDL_Base::Start(param);
    if (!result) {
        _cursor.in_window = true;
        set_target_fps(0);
#ifdef __EMSCRIPTEN__
        EM_ASM({
            const canvas = document.getElementById('canvas');
            if (canvas) canvas.style.cursor = 'none';
        });
#endif
    }
    return result;
}

void VideoDriver_PixelRAM::Stop()
{
    screen_close();
    VideoDriver_SDL_Base::Stop();
}

bool VideoDriver_PixelRAM::CreateMainWindow(uint w, uint h, uint flags)
{
    (void)flags;
    if (screen_width() > 0 && screen_height() > 0) return true;
    return screen_open(static_cast<int>(w), static_cast<int>(h), this->PixelMode(), "OpenTTD");
}

bool VideoDriver_PixelRAM::AllocateBackingStore(int w, int h, bool force)
{
    if (!force && w == screen_width() && h == screen_height() && screen_mode() == this->PixelMode()) {
        return false;
    }

    if (!screen_set_mode(w, h, this->PixelMode())) return false;

    const int bpp = BlitterFactory::GetCurrentBlitter()->GetScreenDepth();
    _screen.width = w;
    _screen.height = h;
    _screen.pitch = screen_pitch() / (bpp / 8);
    _screen.dst_ptr = framebuffer();

    CopyPalette(this->local_palette, true);
    this->UpdatePixelRAMPalette();
    this->dirty_rect = {};
    return true;
}

void *VideoDriver_PixelRAM::GetVideoPointer()
{
    return framebuffer();
}

void VideoDriver_PixelRAM::Paint()
{
    if (IsEmptyRect(this->dirty_rect) && this->local_palette.count_dirty == 0) return;

    this->CheckPaletteAnim();
    present();
    this->dirty_rect = {};
}

void VideoDriver_PixelRAM::UpdatePixelRAMPalette()
{
    if (screen_mode() != pixel_indexed8) {
        this->local_palette.count_dirty = 0;
        return;
    }

    for (int i = 0; i < this->local_palette.count_dirty; ++i) {
        const int index = this->local_palette.first_dirty + i;
        const auto &c = this->local_palette.palette[index];
        set_palette(index, c.r, c.g, c.b);
    }
    this->local_palette.count_dirty = 0;
}

void VideoDriver_PixelRAM::CheckPaletteAnim()
{
    if (!CopyPalette(this->local_palette)) return;

    Blitter *blitter = BlitterFactory::GetCurrentBlitter();
    switch (blitter->UsePaletteAnimation()) {
        case Blitter::PaletteAnimation::VideoBackend:
            this->UpdatePixelRAMPalette();
            break;

        case Blitter::PaletteAnimation::Blitter:
            blitter->PaletteAnimate(this->local_palette);
            this->local_palette.count_dirty = 0;
            break;

        case Blitter::PaletteAnimation::None:
            this->local_palette.count_dirty = 0;
            break;

        default:
            NOT_REACHED();
    }

    this->MakeDirty(0, 0, _screen.width, _screen.height);
}

bool VideoDriver_PixelRAM::ChangeResolution(int w, int h)
{
    if (w < 64 || h < 64) return false;
    _cur_resolution = {static_cast<uint>(w), static_cast<uint>(h)};
    this->ClientSizeChanged(w, h, true);
    return true;
}

bool VideoDriver_PixelRAM::ToggleFullscreen(bool fullscreen)
{
    _fullscreen = fullscreen;
    set_fullscreen(fullscreen);
    return true;
}

bool VideoDriver_PixelRAM::ClaimMousePointer()
{
    /* OpenTTD draws its own cursor. We hide only the browser cursor; no lock. */
#ifdef __EMSCRIPTEN__
    EM_ASM({
        const canvas = document.getElementById('canvas');
        if (canvas) canvas.style.cursor = 'none';
    });
#endif
    return true;
}

uint VideoDriver_PixelRAM::ConvertKey(pixel_key key, char32_t *character) const
{
    *character = WKC_NONE;

    if (key >= pixel_key_a && key <= pixel_key_z) {
        *character = static_cast<char32_t>(key);
        return static_cast<uint>('A' + (key - pixel_key_a));
    }
    if (key >= pixel_key_0 && key <= pixel_key_9) {
        *character = static_cast<char32_t>(key);
        return static_cast<uint>(key);
    }

    switch (key) {
        case pixel_key_escape: return WKC_ESC;
        case pixel_key_space: *character = U' '; return WKC_SPACE;
        case pixel_key_enter: return WKC_RETURN;
        case pixel_key_tab: return WKC_TAB;
        case pixel_key_backspace: return WKC_BACKSPACE;
        case pixel_key_insert: return WKC_INSERT;
        case pixel_key_delete: return WKC_DELETE;
        case pixel_key_home: return WKC_HOME;
        case pixel_key_end: return WKC_END;
        case pixel_key_page_up: return WKC_PAGEUP;
        case pixel_key_page_down: return WKC_PAGEDOWN;
        case pixel_key_left: return WKC_LEFT;
        case pixel_key_up: return WKC_UP;
        case pixel_key_right: return WKC_RIGHT;
        case pixel_key_down: return WKC_DOWN;
        case pixel_key_f1: return WKC_F1;
        case pixel_key_f2: return WKC_F2;
        case pixel_key_f3: return WKC_F3;
        case pixel_key_f4: return WKC_F4;
        case pixel_key_f5: return WKC_F5;
        case pixel_key_f6: return WKC_F6;
        case pixel_key_f7: return WKC_F7;
        case pixel_key_f8: return WKC_F8;
        case pixel_key_f9: return WKC_F9;
        case pixel_key_f10: return WKC_F10;
        case pixel_key_f11: return WKC_F11;
        case pixel_key_f12: return WKC_F12;
        case pixel_key_grave: *character = U'`'; return WKC_BACKQUOTE;
        case pixel_key_slash: *character = U'/'; return WKC_SLASH;
        case pixel_key_semicolon: *character = U';'; return WKC_SEMICOLON;
        case pixel_key_equals: *character = U'='; return WKC_EQUALS;
        case pixel_key_left_bracket: *character = U'['; return WKC_L_BRACKET;
        case pixel_key_right_bracket: *character = U']'; return WKC_R_BRACKET;
        case pixel_key_apostrophe: *character = U'\''; return WKC_SINGLEQUOTE;
        case pixel_key_comma: *character = U','; return WKC_COMMA;
        case pixel_key_period: *character = U'.'; return WKC_PERIOD;
        case pixel_key_minus: *character = U'-'; return WKC_MINUS;
        default: return WKC_NONE;
    }
}

void VideoDriver_PixelRAM::UpdateMouse()
{
    int x = 0;
    int y = 0;
    mouse_position(&x, &y);

    bool changed = false;
    if (_cursor.UpdateCursorPosition(x, y)) changed = true;

    if (mouse_button_pressed(pixel_mouse_left)) {
        _left_button_down = true;
        changed = true;
    }
    if (mouse_button_released(pixel_mouse_left)) {
        _left_button_down = false;
        _left_button_clicked = false;
        changed = true;
    }
    if (mouse_button_pressed(pixel_mouse_right)) {
        _right_button_down = true;
        _right_button_clicked = true;
        changed = true;
    }
    if (mouse_button_released(pixel_mouse_right)) {
        _right_button_down = false;
        changed = true;
    }

    if (changed) HandleMouseEvents();
}

void VideoDriver_PixelRAM::InputLoop()
{
    const bool old_ctrl_pressed = _ctrl_pressed;

    _ctrl_pressed = key_down(pixel_key_ctrl);
    _shift_pressed = key_down(pixel_key_shift);
    this->fast_forward_key_pressed = key_down(pixel_key_tab) && !key_down(pixel_key_alt);

    _dirkeys =
        (key_down(pixel_key_left) ? 1 : 0) |
        (key_down(pixel_key_up) ? 2 : 0) |
        (key_down(pixel_key_right) ? 4 : 0) |
        (key_down(pixel_key_down) ? 8 : 0);

    if (old_ctrl_pressed != _ctrl_pressed) HandleCtrlChanged();
    this->UpdateMouse();

    if (should_close()) HandleExitGameRequest();
}

bool VideoDriver_PixelRAM::PollEvent()
{
    pixel_key_event event;
    if (!poll_key_event(&event)) return false;
    if (!event.pressed) return true;

    char32_t character = WKC_NONE;
    uint keycode = this->ConvertKey(event.key, &character);

    if (key_down(pixel_key_shift)) keycode |= WKC_SHIFT;
    if (key_down(pixel_key_ctrl)) keycode |= WKC_CTRL;
    if (key_down(pixel_key_alt)) keycode |= WKC_ALT;

    if (keycode != WKC_NONE || character != WKC_NONE) {
        HandleKeypress(keycode, character);
    }

    return true;
}
