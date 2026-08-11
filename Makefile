EMCC := emcc
HOST_CC ?= cc

CFLAGS := -O2 -std=c11 -Wall -Wextra -Wpedantic

BUILD_DIR := build
CACHE_DIR := .cache
EXAMPLES := minimal fire
HTML := $(EXAMPLES:%=$(BUILD_DIR)/%.html)
SHELL_FILE := shell.html

WEB_FLAGS := \
	-DPLATFORM_WEB \
	-sUSE_GLFW=3 \
	-sASYNCIFY \
	-sSINGLE_FILE=1 \
	--shell-file $(SHELL_FILE)

.PHONY: all clean palettes test $(EXAMPLES) games \
	doom doom-source doom-data doom-music clean-doom \
	descent descent-source descent-data descent-music clean-descent

all: $(HTML)

$(EXAMPLES): %: $(BUILD_DIR)/%.html

$(BUILD_DIR):
	mkdir -p $@

$(CACHE_DIR):
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

# ======================================================================
# Big ports
# ======================================================================

games: doom descent

# ----------------------------------------------------------------------
# DOOM
# ----------------------------------------------------------------------

DOOM_REPO := https://github.com/ozkl/doomgeneric.git
DOOM_COMMIT := dcb7a8dbc7a16ce3dda29382ac9aae9d77d21284
DOOM_ROOT := $(CACHE_DIR)/doomgeneric
DOOM_DIR := $(DOOM_ROOT)/doomgeneric

FREEPATS_VERSION := 20060219-4
FREEPATS_URL := https://ftp.debian.org/debian/pool/main/f/freepats/freepats_$(FREEPATS_VERSION)_all.deb
FREEPATS_DIR := $(CACHE_DIR)/doom-music
FREEPATS_DEB := $(FREEPATS_DIR)/freepats.deb
FREEPATS_ROOT := $(FREEPATS_DIR)/root

DOOM_SOURCE_NAMES := \
	dummy.c am_map.c doomdef.c doomstat.c dstrings.c d_event.c d_items.c \
	d_iwad.c d_loop.c d_main.c d_mode.c d_net.c f_finale.c f_wipe.c \
	g_game.c hu_lib.c hu_stuff.c info.c i_cdmus.c i_endoom.c i_joystick.c \
	i_scale.c i_sound.c i_system.c i_timer.c memio.c m_argv.c m_bbox.c \
	m_cheat.c m_config.c m_controls.c m_fixed.c m_menu.c m_misc.c m_random.c \
	p_ceilng.c p_doors.c p_enemy.c p_floor.c p_inter.c p_lights.c p_map.c \
	p_maputl.c p_mobj.c p_plats.c p_pspr.c p_saveg.c p_setup.c p_sight.c \
	p_spec.c p_switch.c p_telept.c p_tick.c p_user.c r_bsp.c r_data.c \
	r_draw.c r_main.c r_plane.c r_segs.c r_sky.c r_things.c sha1.c sounds.c \
	statdump.c st_lib.c st_stuff.c s_sound.c tables.c v_video.c wi_stuff.c \
	w_checksum.c w_file.c w_main.c w_wad.c z_zone.c w_file_stdc.c i_input.c \
	i_video.c doomgeneric.c mus2mid.c i_sdlsound.c i_sdlmusic.c

DOOM_SOURCES := $(addprefix $(DOOM_DIR)/,$(DOOM_SOURCE_NAMES))

doom-source: | $(CACHE_DIR)
	@if [ ! -d "$(DOOM_ROOT)/.git" ]; then \
		echo "Downloading doomgeneric source..."; \
		git clone "$(DOOM_REPO)" "$(DOOM_ROOT)"; \
	fi
	@git -C "$(DOOM_ROOT)" checkout -q --detach "$(DOOM_COMMIT)"
	@echo "doomgeneric source ready."

doom-data:
	@if [ ! -f doom1.wad ] && [ -f DOOM1.WAD ]; then cp DOOM1.WAD doom1.wad; fi
	@if [ ! -f doom1.wad ]; then \
		echo; \
		echo "DOOM game data is missing."; \
		echo; \
		echo "Place doom1.wad next to this Makefile and run:"; \
		echo "  make doom"; \
		echo; \
		exit 1; \
	fi

$(FREEPATS_DEB):
	@mkdir -p "$(FREEPATS_DIR)"
	@echo "Downloading free General MIDI instruments for DOOM..."
	wget -q --show-progress "$(FREEPATS_URL)" -O "$@"

doom-music: $(FREEPATS_DEB)
	@rm -rf "$(FREEPATS_ROOT)"
	dpkg-deb -x "$(FREEPATS_DEB)" "$(FREEPATS_ROOT)"
	@test -f "$(FREEPATS_ROOT)/etc/timidity/freepats.cfg"
	@test -d "$(FREEPATS_ROOT)/usr/share/midi/freepats"
	@echo "DOOM music assets ready."

doom: doom-source doom-data doom-music | $(BUILD_DIR)
	@echo "Building DOOM for PixelRAM..."
	$(EMCC) \
		-O2 -std=c99 \
		-Wno-unused-variable -Wno-unused-function \
		-DCMAP256 -DFEATURE_SOUND \
		-DDOOMGENERIC_RESX=320 -DDOOMGENERIC_RESY=200 \
		-D_DEFAULT_SOURCE -DPLATFORM_WEB \
		-sUSE_GLFW=3 \
		-sUSE_SDL=2 \
		-sUSE_SDL_MIXER=2 \
		-sSDL2_MIXER_FORMATS='["mid"]' \
		-sASYNCIFY \
		-sFORCE_FILESYSTEM \
		-sSINGLE_FILE=1 \
		--shell-file "$(SHELL_FILE)" \
		-I. -I"$(DOOM_DIR)" \
		$(DOOM_SOURCES) \
		ports/doom/doom_pixelram.c \
		pixelram.c \
		-lraylib -lm \
		--embed-file doom1.wad@/doom1.wad \
		--embed-file "$(FREEPATS_ROOT)/etc/timidity/freepats.cfg"@/timidity.cfg \
		--embed-file "$(FREEPATS_ROOT)/usr/share/midi/freepats"@/usr/share/midi/freepats \
		-o "$(BUILD_DIR)/doom.html"
	@echo
	@echo "Ready: $(BUILD_DIR)/doom.html"

clean-doom:
	rm -f "$(BUILD_DIR)/doom.html"
	rm -rf "$(DOOM_ROOT)" "$(FREEPATS_DIR)"

# ----------------------------------------------------------------------
# Chocolate Descent
# ----------------------------------------------------------------------

DESCENT_REPO := https://github.com/InsanityBringer/ChocolateDescent.git
DESCENT_COMMIT := 03cfb6e2dbfee75a041d27fdc45cf561467b8ea4
DESCENT_ROOT := $(CACHE_DIR)/ChocolateDescent
DESCENT_BUILD := $(DESCENT_ROOT)/build-wasm

DESCENT_MUSIC_DIR := $(CACHE_DIR)/descent-music
TSF_HEADER := $(DESCENT_MUSIC_DIR)/tsf.h
TSF_URL := https://raw.githubusercontent.com/schellingb/TinySoundFont/main/tsf.h
TIMGM_VERSION := 1.3
TIMGM_ARCHIVE := $(DESCENT_MUSIC_DIR)/timgm6mb-soundfont.tar.gz
TIMGM_URL := https://deb.debian.org/debian/pool/main/t/timgm6mb-soundfont/timgm6mb-soundfont_$(TIMGM_VERSION).orig.tar.gz
TIMGM_ROOT := $(DESCENT_MUSIC_DIR)/timgm6mb
TIMGM_SF2 := $(DESCENT_MUSIC_DIR)/TimGM6mb.sf2

$(TSF_HEADER):
	@mkdir -p "$(DESCENT_MUSIC_DIR)"
	@echo "Downloading TinySoundFont..."
	wget -q --show-progress "$(TSF_URL)" -O "$@"

$(TIMGM_ARCHIVE):
	@mkdir -p "$(DESCENT_MUSIC_DIR)"
	@echo "Downloading TimGM6mb SoundFont..."
	wget -q --show-progress "$(TIMGM_URL)" -O "$@"

$(TIMGM_SF2): $(TIMGM_ARCHIVE)
	@rm -rf "$(TIMGM_ROOT)"
	@mkdir -p "$(TIMGM_ROOT)"
	tar xzf "$<" -C "$(TIMGM_ROOT)"
	@sf2="$$(find "$(TIMGM_ROOT)" -type f -iname '*.sf2' -print -quit)"; \
		if [ -z "$$sf2" ]; then echo "No .sf2 file found"; exit 1; fi; \
		cp "$$sf2" "$@"
	@test -s "$@"

descent-music: $(TSF_HEADER) $(TIMGM_SF2)
	@echo "Descent music assets ready."

descent-source: descent-music | $(CACHE_DIR)
	@if [ ! -d "$(DESCENT_ROOT)/.git" ]; then \
		echo "Downloading Chocolate Descent source..."; \
		git clone "$(DESCENT_REPO)" "$(DESCENT_ROOT)"; \
	fi
	@git -C "$(DESCENT_ROOT)" checkout -q --detach "$(DESCENT_COMMIT)"
	python3 ports/descent/prepare.py "$(DESCENT_ROOT)" "."
	@echo "Chocolate Descent source ready."

descent-data:
	@if [ ! -f descent.hog ] && [ -f DESCENT.HOG ]; then cp DESCENT.HOG descent.hog; fi
	@if [ ! -f descent.pig ] && [ -f DESCENT.PIG ]; then cp DESCENT.PIG descent.pig; fi
	@if [ ! -f descent.hog ] || [ ! -f descent.pig ]; then \
		echo; \
		echo "Descent game data is missing."; \
		echo; \
		echo "Place these files next to this Makefile:"; \
		echo "  descent.hog"; \
		echo "  descent.pig"; \
		echo; \
		echo "Then run:"; \
		echo "  make descent"; \
		echo; \
		exit 1; \
	fi

descent: descent-source descent-data | $(BUILD_DIR)
	cp descent.hog "$(DESCENT_ROOT)/descent.hog"
	cp descent.pig "$(DESCENT_ROOT)/descent.pig"
	rm -rf "$(DESCENT_BUILD)"
	emcmake cmake \
		-S "$(DESCENT_ROOT)" \
		-B "$(DESCENT_BUILD)" \
		-DCMAKE_BUILD_TYPE=Release \
		-DBUILD_EDITOR=OFF \
		-DNETWORK=OFF \
		-DCMAKE_DISABLE_FIND_PACKAGE_SDL2=TRUE \
		-DCMAKE_DISABLE_FIND_PACKAGE_OPENAL=TRUE \
		-DCMAKE_DISABLE_FIND_PACKAGE_FLUIDSYNTH=TRUE
	cmake --build "$(DESCENT_BUILD)" \
		--target ChocolateDescent \
		-j"$$(nproc)"
	cp "$(DESCENT_BUILD)/descent.html" "$(BUILD_DIR)/descent.html"
	@echo
	@echo "Ready: $(BUILD_DIR)/descent.html"

clean-descent:
	rm -f "$(BUILD_DIR)/descent.html"
	rm -rf "$(DESCENT_ROOT)" "$(DESCENT_MUSIC_DIR)"

clean:
	rm -rf "$(BUILD_DIR)"
