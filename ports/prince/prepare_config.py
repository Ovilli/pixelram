#!/usr/bin/env python3
from pathlib import Path
import sys

if len(sys.argv) != 3:
    raise SystemExit("usage: prepare_config.py UPSTREAM_INI OUTPUT_INI")

source = Path(sys.argv[1])
target = Path(sys.argv[2])

text = source.read_text(encoding="utf-8")

replacements = {
    "pop_window_width = default": "pop_window_width = 320",
    "pop_window_height = default": "pop_window_height = 200",
    "use_correct_aspect_ratio = false": "use_correct_aspect_ratio = false",
    "use_integer_scaling = false": "use_integer_scaling = false",
    "scaling_type = sharp": "scaling_type = sharp",
}

for old, new in replacements.items():
    if old not in text:
        raise RuntimeError(f"Expected SDLPoP setting not found: {old}")
    text = text.replace(old, new, 1)

target.parent.mkdir(parents=True, exist_ok=True)
target.write_text(text, encoding="utf-8")

print(f"Prepared {target}: 320x200 sharp browser framebuffer")
