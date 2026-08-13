/* OpenCrystalCaves input adapter for PixelRAM. */

#include "event.h"
#include "pixelram.h"

#include <memory>

namespace
{

class PixelRAMEvent final : public Event
{
 public:
  void poll_event(Input* input) override;
};

void tick_buttons(Input* input)
{
  input->up.tick();
  input->down.tick();
  input->left.tick();
  input->right.tick();
  input->d.tick();
  input->z.tick();
  input->x.tick();
  input->num_1.tick();
  input->num_2.tick();
  input->num_3.tick();
  input->num_4.tick();
  input->num_5.tick();
  input->num_6.tick();
  input->num_7.tick();
  input->num_8.tick();
  input->num_9.tick();
  input->num_0.tick();
  input->enter.tick();
  input->space.tick();
  input->escape.tick();
  input->backspace.tick();
  input->noclip.tick();
  input->ammo.tick();
  input->godmode.tick();
  input->reverse_gravity.tick();
  input->level_warp.tick();
  input->mouse_left.tick();
}

void set_key(Input* input, const pixel_key key, const bool down)
{
  switch (key)
  {
    case pixel_key_up: input->up.set_down(down); break;
    case pixel_key_down: input->down.set_down(down); break;
    case pixel_key_left: input->left.set_down(down); break;
    case pixel_key_right: input->right.set_down(down); break;
    case pixel_key_d: input->d.set_down(down); break;
    case pixel_key_z: input->z.set_down(down); break;
    case pixel_key_x: input->x.set_down(down); break;
    case pixel_key_g: input->reverse_gravity.set_down(down); break;
    case pixel_key_1: input->num_1.set_down(down); break;
    case pixel_key_2: input->num_2.set_down(down); break;
    case pixel_key_3: input->num_3.set_down(down); break;
    case pixel_key_4: input->num_4.set_down(down); break;
    case pixel_key_5: input->num_5.set_down(down); break;
    case pixel_key_6: input->num_6.set_down(down); break;
    case pixel_key_7: input->num_7.set_down(down); break;
    case pixel_key_8: input->num_8.set_down(down); break;
    case pixel_key_9: input->num_9.set_down(down); break;
    case pixel_key_0: input->num_0.set_down(down); break;
    case pixel_key_enter: input->enter.set_down(down); break;
    case pixel_key_space: input->space.set_down(down); break;
    case pixel_key_escape: input->escape.set_down(down); break;
    case pixel_key_backspace: input->backspace.set_down(down); break;
    default: break;
  }
}

}  // namespace

std::unique_ptr<Event> Event::create()
{
  return std::make_unique<PixelRAMEvent>();
}

void PixelRAMEvent::poll_event(Input* input)
{
  tick_buttons(input);

  pixel_key_event event;
  while (poll_key_event(&event))
  {
    set_key(input, event.key, event.pressed);
  }

  /* The original port treats these cheat codes as simultaneous chords. */
  input->noclip.set_down(key_down(pixel_key_i) && key_down(pixel_key_l) && key_down(pixel_key_m));
  input->ammo.set_down(
    key_down(pixel_key_x) && key_down(pixel_key_t) && key_down(pixel_key_r) && key_down(pixel_key_a));
  input->godmode.set_down(
    key_down(pixel_key_z) && key_down(pixel_key_e) && key_down(pixel_key_u) && key_down(pixel_key_s));
  input->level_warp.set_down(
    key_down(pixel_key_n) && key_down(pixel_key_e) && key_down(pixel_key_x) && key_down(pixel_key_t));

  int x = 0;
  int y = 0;
  mouse_position(&x, &y);
  input->mouse = geometry::Position(x, y);
  input->mouse_left.set_down(mouse_button_down(pixel_mouse_left));

  if (should_close())
  {
    input->escape.set_down(true);
  }
}
