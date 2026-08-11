# Palette source

`palettes.yaml` is the source used to generate PixelRAM's built-in named palettes and the palette documentation.

It is synchronized with:

`https://github.com/specht/pixelflow_canvas_ruby/blob/master/lib/pixelflow_canvas/palettes.yaml`

Run:

```sh
make palettes
```

or:

```sh
./tools/generate_palettes.py
```

The generator uses only the Python standard library. It replaces the generated palette block in `pixelram.c` and recreates `docs/palettes.md`.
