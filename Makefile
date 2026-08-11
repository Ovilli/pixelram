EMCC := emcc
HOST_CC ?= cc

CFLAGS := -O2 -std=c11 -Wall -Wextra -Wpedantic

BUILD_DIR := build
EXAMPLES := minimal fire
HTML := $(EXAMPLES:%=$(BUILD_DIR)/%.html)
SHELL_FILE := shell.html

WEB_FLAGS := \
	-DPLATFORM_WEB \
	-sUSE_GLFW=3 \
	-sASYNCIFY \
	-sSINGLE_FILE=1 \
	--shell-file $(SHELL_FILE)

.PHONY: all clean palettes test $(EXAMPLES)

all: $(HTML)

# Allow:
#   make minimal
#   make fire
$(EXAMPLES): %: $(BUILD_DIR)/%.html

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.html: examples/%.c pixelram.c pixelram.h $(SHELL_FILE) | $(BUILD_DIR)
	$(EMCC) $(CFLAGS) $(WEB_FLAGS) -I. \
		$< pixelram.c \
		-lraylib \
		-o $@

palettes:
	./tools/generate_palettes.py

TEST_BINARY := $(BUILD_DIR)/test_pixelram

test: $(TEST_BINARY)
	./$(TEST_BINARY)

$(TEST_BINARY): tests/test_pixelram.c pixelram.c pixelram.h tests/stub/raylib.h tests/stub/raylib_stub.c | $(BUILD_DIR)
	$(HOST_CC) -O2 -std=c11 -Wall -Wextra -Wpedantic -Werror \
		-Itests/stub -I. \
		tests/test_pixelram.c pixelram.c tests/stub/raylib_stub.c \
		-o $@

clean:
	rm -rf $(BUILD_DIR)
