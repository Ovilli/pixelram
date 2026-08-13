/* OpenCrystalCaves runtime/timing adapter for PixelRAM. */

#include "sdl_wrapper.h"
#include "pixelram.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include <cstdlib>
#include <memory>

#include "logger.h"

namespace
{

constexpr int SAMPLE_RATE = 22050;
constexpr int AUDIO_CHANNELS = 2;

class PixelRAMSDLWrapper final : public SDLWrapper
{
 public:
  bool init() override;
  unsigned get_tick() override;
  void delay(const int ms) override;
};

void quit_audio()
{
  Mix_CloseAudio();
  SDL_Quit();
}

}  // namespace

std::unique_ptr<SDLWrapper> SDLWrapper::create()
{
  return std::make_unique<PixelRAMSDLWrapper>();
}

bool PixelRAMSDLWrapper::init()
{
  /*
   * SDL remains only for OpenCrystalCaves' software renderer and mixer.
   * PixelRAM/raylib owns the visible browser window and all input.
   */
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
  {
    LOG_CRITICAL("Could not initialize SDL support: %s", SDL_GetError());
    return false;
  }

  if (Mix_OpenAudio(SAMPLE_RATE, AUDIO_S16, AUDIO_CHANNELS, 1024) != 0)
  {
    LOG_CRITICAL("Could not open audio: %s", SDL_GetError());
    return false;
  }

  std::atexit(quit_audio);
  return true;
}

unsigned PixelRAMSDLWrapper::get_tick()
{
  return ticks_ms();
}

void PixelRAMSDLWrapper::delay(const int ms)
{
  if (ms > 0)
  {
    sleep_ms(static_cast<uint32_t>(ms));
  }
}
