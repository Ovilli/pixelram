---
title: Adding PixelRAM to a project
layout: page
nav_order: 7
---

# Adding PixelRAM to a project

The distributable library is exactly two files:

```text
pixelram.c
pixelram.h
```

A project can vendor those files directly or download a pinned release from GitHub.

## Makefile download

```make
PIXELRAM_VERSION := v0.1.17
PIXELRAM_BASE := https://raw.githubusercontent.com/specht/pixelram/$(PIXELRAM_VERSION)
PIXELRAM_DIR := vendor/pixelram

$(PIXELRAM_DIR)/pixelram.c:
	mkdir -p $(PIXELRAM_DIR)
	curl -fsSL $(PIXELRAM_BASE)/pixelram.c -o $@

$(PIXELRAM_DIR)/pixelram.h:
	mkdir -p $(PIXELRAM_DIR)
	curl -fsSL $(PIXELRAM_BASE)/pixelram.h -o $@
```

Then make your executable depend on both files and compile `pixelram.c` together with your program.

{: .important }
Use a release tag such as `v0.1.17`, not `main`, in teaching material. A pinned tutorial should keep compiling even after PixelRAM evolves.

## Platform dependency

PixelRAM keeps raylib out of the public header, but `pixelram.c` uses raylib internally as its platform backend. A native project therefore needs a compatible raylib development setup; a WebAssembly project needs raylib built for Emscripten as well as Asyncify at link time.

Hackschule Workspace already provides that toolchain, so student programs only include `pixelram.h` and compile `pixelram.c` with their own source.

## Why the implementation is one C file

The source file includes the platform backend and all built-in palette data. That makes distribution intentionally boring: no package manager, git submodule, generated source directory, or runtime assets are required by student projects.

The repository itself contains the palette source and generator so the built-in collection remains maintainable, but users of a release only need the two library files.
