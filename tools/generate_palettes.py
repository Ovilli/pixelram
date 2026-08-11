#!/usr/bin/env python3
"""Generate PixelRAM's built-in C palette tables and palette documentation."""

from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "tools" / "palettes.yaml"
C_FILE = ROOT / "pixelram.c"
DOC_FILE = ROOT / "docs" / "palettes.md"
BEGIN = "/* PIXELRAM_PALETTES_BEGIN */"
END = "/* PIXELRAM_PALETTES_END */"


def read_palettes(path: Path):
    palettes = []
    current_name = None
    current_colors = None

    for line_number, raw in enumerate(path.read_text().splitlines(), 1):
        line = raw.strip()
        if not line or line == "---":
            continue

        if line.startswith(":") and line.endswith(":"):
            current_name = line[1:-1]
            current_colors = []
            palettes.append((current_name, current_colors))
            continue

        if line.startswith("- "):
            if current_colors is None:
                raise ValueError(f"color without palette at line {line_number}")
            match = re.fullmatch(r'-\s+"#([0-9a-fA-F]{6})"', line)
            if not match:
                raise ValueError(f"invalid color at line {line_number}: {line}")
            value = match.group(1)
            current_colors.append(tuple(int(value[i:i + 2], 16) for i in (0, 2, 4)))
            continue

        raise ValueError(f"unrecognized line {line_number}: {line}")

    if not palettes:
        raise ValueError("no palettes found")

    for name, colors in palettes:
        if not colors:
            raise ValueError(f"palette {name!r} is empty")
        if len(colors) > 256:
            raise ValueError(f"palette {name!r} has {len(colors)} colors; maximum is 256")

    return palettes


def c_identifier(name: str) -> str:
    value = re.sub(r"[^a-zA-Z0-9_]", "_", name)
    if not value or value[0].isdigit():
        value = "p_" + value
    return "palette_" + value


def generate_c(palettes):
    out = [BEGIN]

    for name, colors in palettes:
        ident = c_identifier(name)
        out.append(f"static const PaletteColor {ident}[] = {{")

        entries = [
            f"{{ 0x{r:02x}, 0x{g:02x}, 0x{b:02x} }}"
            for r, g, b in colors
        ]
        for i in range(0, len(entries), 4):
            out.append("    " + ", ".join(entries[i:i + 4]) + ",")

        out.append("};")
        out.append("")

    out.append("static const PaletteDefinition builtin_palettes[] = {")
    for name, colors in palettes:
        ident = c_identifier(name)
        out.append(f'    {{ "{name}", {ident}, {len(colors)} }},')
    out.append("};")
    out.append(END)
    return "\n".join(out)


def generate_docs(palettes):
    out = [
        "---",
        "title: Palettes",
        "layout: page",
        "nav_order: 2",
        "---",
        "",
        "# Palettes",
        "",
        "PixelRAM contains the same predefined palette collection as Pixelflow Canvas. "
        "The default is `vga`. A named palette replaces all 256 entries; unused entries become black.",
        "",
        "```c",
        'use_palette("aap_64");',
        "```",
        "",
        "You can also change any palette entry directly. Because indexed pixels store only an index, "
        "changing a palette color immediately changes every pixel using that index:",
        "",
        "```c",
        "set_palette(1, 255, 0, 0);",
        "```",
        "",
        "The built-in names are:",
        "",
    ]

    for name, colors in palettes:
        out += [f"## {name.replace('_', ' ').title()}", "", f'`use_palette("{name}")` — {len(colors)} colors', "", '<div class="palette">']
        for i, (r, g, b) in enumerate(colors):
            out.append(
                f'<span class="swatch" title="{i}: #{r:02x}{g:02x}{b:02x}" '
                f'style="background:#{r:02x}{g:02x}{b:02x}"></span>'
            )
        out += ["</div>", ""]

    out += [
        "<style>",
        ".palette { display:flex; flex-wrap:wrap; gap:3px; margin:.5rem 0 1.5rem; }",
        ".swatch { width:22px; height:22px; border-radius:4px; border:1px solid rgba(127,127,127,.25); }",
        "</style>",
        "",
    ]
    return "\n".join(out)


def main():
    palettes = read_palettes(SOURCE)

    source = C_FILE.read_text()
    start = source.index(BEGIN)
    end = source.index(END, start) + len(END)
    source = source[:start] + generate_c(palettes) + source[end:]
    C_FILE.write_text(source)

    DOC_FILE.write_text(generate_docs(palettes))
    print(f"generated {len(palettes)} palettes")


if __name__ == "__main__":
    main()
