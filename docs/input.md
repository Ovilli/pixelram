---
title: Keyboard and mouse
layout: page
nav_order: 4
---

# Keyboard and mouse

PixelRAM wraps the input needed by small demos and by larger engine ports. Application code does not need platform-specific key codes.

## Keyboard state

```c
if (key_down(pixel_key_left)) {
    /* key is currently held */
}

if (key_pressed(pixel_key_space)) {
    /* transitioned to down */
}

if (key_released(pixel_key_space)) {
    /* transitioned to up */
}
```

Letters use names such as `pixel_key_a`; function keys use `pixel_key_f1`; modifiers are `pixel_key_shift`, `pixel_key_ctrl` and `pixel_key_alt`.

## Queued key transitions

For engines that consume discrete input events, PixelRAM preserves transitions in a queue:

```c
pixel_key_event event;
while (poll_key_event(&event))
{
    if (event.pressed) {
        /* key down */
    } else {
        /* key up */
    }
}
```

This is useful for ports such as DOOM where a press/release transition must not be lost between engine ticks.

## Mouse

```c
int x, y;
mouse_position(&x, &y);

if (mouse_button_pressed(pixel_mouse_left)) {
    /* click */
}
```

Available buttons are `pixel_mouse_left`, `pixel_mouse_right`, and `pixel_mouse_middle`.

For first-person controls:

```c
set_mouse_relative(true);

int dx, dy;
mouse_delta(&dx, &dy);
```

On the web, relative mode uses browser pointer lock and is activated by the next user click.
