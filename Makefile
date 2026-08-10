CC ?= cc
CFLAGS ?= -O2 -std=c11 -Wall -Wextra -Wpedantic
CPPFLAGS ?=

RAYLIB_CFLAGS ?= $(shell pkg-config --cflags raylib 2>/dev/null)
RAYLIB_LIBS ?= $(shell pkg-config --libs raylib 2>/dev/null)

BUILD_DIR := build
EXAMPLES := minimal fire
BINARIES := $(EXAMPLES:%=$(BUILD_DIR)/%)

.PHONY: all clean palettes

all: $(BINARIES)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%: examples/%.c pixelram.c pixelram.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(RAYLIB_CFLAGS) -I. $< pixelram.c -o $@ $(RAYLIB_LIBS)

palettes:
	./tools/generate_palettes.py

clean:
	rm -rf $(BUILD_DIR)

TEST_BINARY := $(BUILD_DIR)/test_pixelram

.PHONY: test

test: $(TEST_BINARY)
	./$(TEST_BINARY)

$(TEST_BINARY): tests/test_pixelram.c pixelram.c pixelram.h tests/stub/raylib.h tests/stub/raylib_stub.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -Werror -Itests/stub -I. tests/test_pixelram.c pixelram.c tests/stub/raylib_stub.c -o $@
