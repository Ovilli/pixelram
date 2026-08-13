/*
 * OpenCrystalCaves graphics adapter for PixelRAM.
 *
 * PixelRAM deliberately has no sprite or drawing API.  OpenCrystalCaves,
 * however, already isolates its renderer behind a tiny Window/Surface
 * interface.  This adapter implements that interface with ordinary RGBA
 * memory and copies/blends pixels itself.  The visible target is PixelRAM's
 * pixel_rgba32 framebuffer; off-screen target surfaces are std::vectors.
 */

#include "graphics.h"
#include "pixelram.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <memory>
#include <utility>
#include <vector>

#define DR_PCX_IMPLEMENTATION
#include "dr_pcx.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "logger.h"

namespace
{

constexpr uint32_t pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  return static_cast<uint32_t>(r) | (static_cast<uint32_t>(g) << 8) | (static_cast<uint32_t>(b) << 16) |
         (static_cast<uint32_t>(a) << 24);
}

constexpr uint8_t red_of(uint32_t c) { return static_cast<uint8_t>(c); }
constexpr uint8_t green_of(uint32_t c) { return static_cast<uint8_t>(c >> 8); }
constexpr uint8_t blue_of(uint32_t c) { return static_cast<uint8_t>(c >> 16); }
constexpr uint8_t alpha_of(uint32_t c) { return static_cast<uint8_t>(c >> 24); }

uint32_t from_argb(uint32_t argb)
{
  const auto a = static_cast<uint8_t>(argb >> 24);
  const auto r = static_cast<uint8_t>(argb >> 16);
  const auto g = static_cast<uint8_t>(argb >> 8);
  const auto b = static_cast<uint8_t>(argb);
  return pack_rgba(r, g, b, a);
}

uint8_t mul_u8(uint8_t a, uint8_t b)
{
  return static_cast<uint8_t>((static_cast<unsigned>(a) * static_cast<unsigned>(b) + 127u) / 255u);
}

uint32_t blend_rgba(uint32_t dst, uint32_t src, uint8_t surface_alpha, const Color& tint)
{
  const uint8_t sr = mul_u8(red_of(src), tint.red);
  const uint8_t sg = mul_u8(green_of(src), tint.green);
  const uint8_t sb = mul_u8(blue_of(src), tint.blue);
  const uint8_t sa = mul_u8(alpha_of(src), surface_alpha);

  if (sa == 0)
    return dst;
  if (sa == 255)
    return pack_rgba(sr, sg, sb, 255);

  const unsigned inv = 255u - sa;
  const uint8_t dr = red_of(dst);
  const uint8_t dg = green_of(dst);
  const uint8_t db = blue_of(dst);
  const uint8_t da = alpha_of(dst);

  const auto out_r = static_cast<uint8_t>((static_cast<unsigned>(sr) * sa + static_cast<unsigned>(dr) * inv + 127u) / 255u);
  const auto out_g = static_cast<uint8_t>((static_cast<unsigned>(sg) * sa + static_cast<unsigned>(dg) * inv + 127u) / 255u);
  const auto out_b = static_cast<uint8_t>((static_cast<unsigned>(sb) * sa + static_cast<unsigned>(db) * inv + 127u) / 255u);
  const auto out_a = static_cast<uint8_t>(sa + (static_cast<unsigned>(da) * inv + 127u) / 255u);
  return pack_rgba(out_r, out_g, out_b, out_a);
}

class SurfacePixelRAM;

class WindowPixelRAM final : public Window
{
 public:
  explicit WindowPixelRAM(geometry::Size size) : size_(size) {}

  void set_size(geometry::Size size) override;
  void set_render_target(Surface* surface) override;
  std::unique_ptr<Surface> create_target_surface(geometry::Size size) override;
  void refresh() override;
  void fill_rect(const geometry::Rectangle& rect, const Color& color) override;
  void render_line(const geometry::Position& from, const geometry::Position& to, const Color& color) override;
  void render_rectangle(const geometry::Rectangle& rect, const Color& color) override;

  void blit(const SurfacePixelRAM& surface,
            const geometry::Rectangle& source,
            const geometry::Rectangle& dest,
            bool flip,
            const Color& tint);
  void blit_full(const SurfacePixelRAM& surface);

 private:
  struct BufferView
  {
    uint8_t* bytes;
    int width;
    int height;
    int pitch;
  };

  BufferView target_view();
  void write_pixel(BufferView& target, int x, int y, uint32_t rgba, bool blend, uint8_t alpha, const Color& tint);

  geometry::Size size_;
  SurfacePixelRAM* target_ = nullptr;
};

class SurfacePixelRAM final : public Surface
{
 public:
  SurfacePixelRAM(int w, int h, WindowPixelRAM& window)
    : w_(w), h_(h), pixels_(static_cast<size_t>(w) * static_cast<size_t>(h), 0), window_(window)
  {
  }

  int width() const override { return w_; }
  int height() const override { return h_; }

  void blit_surface(const geometry::Rectangle& source,
                    const geometry::Rectangle& dest,
                    bool flip = false,
                    Color tint = {0xff, 0xff, 0xff}) const override
  {
    window_.blit(*this, source, dest, flip, tint);
  }

  void blit_surface() const override { window_.blit_full(*this); }
  void set_alpha(uint8_t alpha) override { alpha_ = alpha; }

  uint32_t* data() { return pixels_.data(); }
  const uint32_t* data() const { return pixels_.data(); }
  int pitch() const { return w_ * static_cast<int>(sizeof(uint32_t)); }
  uint8_t alpha() const { return alpha_; }

 private:
  int w_;
  int h_;
  std::vector<uint32_t> pixels_;
  WindowPixelRAM& window_;
  uint8_t alpha_ = 255;
};

std::unique_ptr<SurfacePixelRAM> make_surface(int w, int h, Window& window)
{
  if (w <= 0 || h <= 0)
  {
    LOG_ERROR("Invalid surface dimensions %dx%d", w, h);
    return nullptr;
  }
  return std::make_unique<SurfacePixelRAM>(w, h, static_cast<WindowPixelRAM&>(window));
}

std::unique_ptr<Surface> surface_from_stbi(const std::filesystem::path& filename, Window& window)
{
  if (filename.empty())
  {
    LOG_ERROR("trying to load empty filename");
    return nullptr;
  }

  int width = 0;
  int height = 0;
  int channels = 0;
  unsigned char* decoded = stbi_load(filename.string().c_str(), &width, &height, &channels, 4);
  if (!decoded)
  {
    LOG_ERROR("could not load image %s: %s", filename.string().c_str(), stbi_failure_reason());
    return nullptr;
  }

  auto surface = make_surface(width, height, window);
  if (!surface)
  {
    stbi_image_free(decoded);
    return nullptr;
  }

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      const auto* p = decoded + (static_cast<size_t>(y) * width + x) * 4u;
      surface->data()[static_cast<size_t>(y) * width + x] = pack_rgba(p[0], p[1], p[2], p[3]);
    }
  }

  stbi_image_free(decoded);
  return surface;
}

}  // namespace

std::unique_ptr<Window> Window::create(const std::string& title,
                                       geometry::Size size,
                                       const std::filesystem::path& icon_path,
                                       const int flags)
{
  (void)icon_path;
  (void)flags;

  if (!screen_open(size.x(), size.y(), pixel_rgba32, title.c_str()))
  {
    LOG_CRITICAL("Could not initialize PixelRAM");
    return nullptr;
  }

  /* OpenCrystalCaves already owns its simulation cadence. */
  set_target_fps(0);
  return std::make_unique<WindowPixelRAM>(size);
}

void WindowPixelRAM::set_size(geometry::Size size)
{
  if (size.x() != size_.x() || size.y() != size_.y())
  {
    LOG_ERROR("Runtime window resizing is not supported by the PixelRAM backend");
  }
}

void WindowPixelRAM::set_render_target(Surface* surface)
{
  target_ = static_cast<SurfacePixelRAM*>(surface);
}

std::unique_ptr<Surface> WindowPixelRAM::create_target_surface(geometry::Size size)
{
  return make_surface(size.x(), size.y(), *this);
}

WindowPixelRAM::BufferView WindowPixelRAM::target_view()
{
  if (target_)
  {
    return {reinterpret_cast<uint8_t*>(target_->data()), target_->width(), target_->height(), target_->pitch()};
  }
  return {static_cast<uint8_t*>(framebuffer()), size_.x(), size_.y(), screen_pitch()};
}

void WindowPixelRAM::write_pixel(BufferView& target,
                                 int x,
                                 int y,
                                 uint32_t rgba,
                                 bool blend,
                                 uint8_t alpha,
                                 const Color& tint)
{
  if (x < 0 || y < 0 || x >= target.width || y >= target.height)
    return;

  auto* dst = reinterpret_cast<uint32_t*>(target.bytes + static_cast<size_t>(y) * target.pitch +
                                          static_cast<size_t>(x) * sizeof(uint32_t));
  if (blend)
    *dst = blend_rgba(*dst, rgba, alpha, tint);
  else
    *dst = rgba;
}

void WindowPixelRAM::refresh()
{
  present();
}

void WindowPixelRAM::fill_rect(const geometry::Rectangle& rect, const Color& color)
{
  auto target = target_view();
  const int x0 = std::max(0, rect.position.x());
  const int y0 = std::max(0, rect.position.y());
  const int x1 = std::min(target.width, rect.position.x() + rect.size.x());
  const int y1 = std::min(target.height, rect.position.y() + rect.size.y());
  if (x0 >= x1 || y0 >= y1)
    return;

  const uint32_t rgba = pack_rgba(color.red, color.green, color.blue, color.alpha);

  for (int y = y0; y < y1; ++y)
  {
    auto* row = reinterpret_cast<uint32_t*>(target.bytes + static_cast<size_t>(y) * target.pitch);
    std::fill(row + x0, row + x1, rgba);
  }
}

void WindowPixelRAM::render_line(const geometry::Position& from,
                                 const geometry::Position& to,
                                 const Color& color)
{
  auto target = target_view();
  const uint32_t rgba = pack_rgba(color.red, color.green, color.blue, color.alpha);

  int x0 = from.x();
  int y0 = from.y();
  const int x1 = to.x();
  const int y1 = to.y();
  const int dx = std::abs(x1 - x0);
  const int sx = x0 < x1 ? 1 : -1;
  const int dy = -std::abs(y1 - y0);
  const int sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;

  while (true)
  {
    write_pixel(target, x0, y0, rgba, false, 255, {0xff, 0xff, 0xff});
    if (x0 == x1 && y0 == y1)
      break;
    const int e2 = 2 * err;
    if (e2 >= dy)
    {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx)
    {
      err += dx;
      y0 += sy;
    }
  }
}

void WindowPixelRAM::render_rectangle(const geometry::Rectangle& rect, const Color& color)
{
  if (rect.size.x() <= 0 || rect.size.y() <= 0)
    return;

  const int left = rect.position.x();
  const int top = rect.position.y();
  const int right = left + rect.size.x() - 1;
  const int bottom = top + rect.size.y() - 1;
  render_line({left, top}, {right, top}, color);
  render_line({left, bottom}, {right, bottom}, color);
  render_line({left, top}, {left, bottom}, color);
  render_line({right, top}, {right, bottom}, color);
}

void WindowPixelRAM::blit(const SurfacePixelRAM& surface,
                          const geometry::Rectangle& source,
                          const geometry::Rectangle& dest,
                          bool flip,
                          const Color& tint)
{
  if (source.size.x() <= 0 || source.size.y() <= 0 || dest.size.x() <= 0 || dest.size.y() <= 0)
    return;

  auto target = target_view();
  const int dx0 = std::max(0, dest.position.x());
  const int dy0 = std::max(0, dest.position.y());
  const int dx1 = std::min(target.width, dest.position.x() + dest.size.x());
  const int dy1 = std::min(target.height, dest.position.y() + dest.size.y());

  for (int dy = dy0; dy < dy1; ++dy)
  {
    const int local_y = dy - dest.position.y();
    const int sy = source.position.y() +
                   static_cast<int>((static_cast<int64_t>(local_y) * source.size.y()) / dest.size.y());
    if (sy < 0 || sy >= surface.height())
      continue;

    for (int dx = dx0; dx < dx1; ++dx)
    {
      const int local_x = dx - dest.position.x();
      int src_local_x = static_cast<int>((static_cast<int64_t>(local_x) * source.size.x()) / dest.size.x());
      if (flip)
        src_local_x = source.size.x() - 1 - src_local_x;
      const int sx = source.position.x() + src_local_x;
      if (sx < 0 || sx >= surface.width())
        continue;

      const uint32_t src = surface.data()[static_cast<size_t>(sy) * surface.width() + sx];
      write_pixel(target, dx, dy, src, true, surface.alpha(), tint);
    }
  }
}

void WindowPixelRAM::blit_full(const SurfacePixelRAM& surface)
{
  auto target = target_view();
  blit(surface,
       geometry::Rectangle(0, 0, surface.width(), surface.height()),
       geometry::Rectangle(0, 0, target.width, target.height),
       false,
       {0xff, 0xff, 0xff});
}

std::unique_ptr<Surface> Surface::from_bmp(const std::filesystem::path& filename, Window& window)
{
  return surface_from_stbi(filename, window);
}

std::unique_ptr<Surface> Surface::from_image(const std::filesystem::path& filename, Window& window)
{
  return surface_from_stbi(filename, window);
}

std::unique_ptr<Surface> Surface::from_pcx_image(const std::filesystem::path& filename, Window& window)
{
  int width = 0;
  int height = 0;
  int channels = 0;
  drpcx_uint8* decoded = drpcx_load_file(filename.string().c_str(), DRPCX_FALSE, &width, &height, &channels, 4);
  if (!decoded)
  {
    LOG_ERROR("could not load PCX image %s", filename.string().c_str());
    return nullptr;
  }

  auto surface = make_surface(width, height, window);
  if (!surface)
  {
    drpcx_free(decoded);
    return nullptr;
  }

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      const auto* p = decoded + (static_cast<size_t>(y) * width + x) * 4u;
      surface->data()[static_cast<size_t>(y) * width + x] = pack_rgba(p[0], p[1], p[2], p[3]);
    }
  }

  drpcx_free(decoded);
  return surface;
}

std::unique_ptr<Surface> Surface::from_pixels(const int w, const int h, const uint32_t* pixels, Window& window)
{
  auto surface = make_surface(w, h, window);
  if (!surface)
    return nullptr;

  if (pixels)
  {
    const size_t count = static_cast<size_t>(w) * static_cast<size_t>(h);
    for (size_t i = 0; i < count; ++i)
      surface->data()[i] = from_argb(pixels[i]);
  }

  return surface;
}
