EMCC := emcc
HOST_CC ?= cc

CFLAGS := -O2 -std=c11 -Wall -Wextra -Wpedantic

BUILD_DIR := build
CACHE_DIR := .cache
EXAMPLES := minimal animation fire
HTML := $(EXAMPLES:%=$(BUILD_DIR)/%.html)
SHELL_FILE := shell.html

WEB_FLAGS := \
	-DPLATFORM_WEB \
	-sUSE_GLFW=3 \
	-sASYNCIFY \
	-sSINGLE_FILE=1 \
	-sSINGLE_FILE_BINARY_ENCODE=0 \
	--shell-file $(SHELL_FILE)

.PHONY: all clean palettes test $(EXAMPLES) games prince prince-source prince-data clean-prince \
	doom doom-source doom-data doom-music clean-doom \
	descent descent-source descent-data descent-music clean-descent \
	openttd openttd-source openttd-data openttd-host clean-openttd

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

games: doom descent prince

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
DOOM_SHAREWARE_DIR := $(CACHE_DIR)/doom-shareware
DOOM_SHAREWARE_WAD := $(DOOM_SHAREWARE_DIR)/doom1.wad

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
	@if [ -f doom1.wad ]; then \
		echo "Using local DOOM data: doom1.wad"; \
	else \
		echo "No local DOOM data found; using the freely distributable DOOM 1.9 shareware IWAD."; \
		python3 tools/fetch_shareware.py doom "$(DOOM_SHAREWARE_WAD)"; \
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
		--shell-file "$(SHELL_FILE)" \
		-I. -I"$(DOOM_DIR)" \
		$(DOOM_SOURCES) \
		ports/doom/doom_pixelram.c \
		ports/doom/pixelram_doom.c \
		-lraylib -lm \
		--pre-js ports/doom/preload_game_files.js \
		--preload-file "$(FREEPATS_ROOT)/etc/timidity/freepats.cfg"@/timidity.cfg \
		--preload-file "$(FREEPATS_ROOT)/usr/share/midi/freepats"@/usr/share/midi/freepats \
		-o "$(BUILD_DIR)/doom.html"
	@wad="doom1.wad"; \
		if [ ! -f "$$wad" ]; then wad="$(DOOM_SHAREWARE_WAD)"; fi; \
		cp -p "$$wad" "$(BUILD_DIR)/doom1.wad"
	@echo
	@echo "Ready: $(BUILD_DIR)/doom.html"

clean-doom:
	rm -f "$(BUILD_DIR)"/doom.html "$(BUILD_DIR)"/doom.js "$(BUILD_DIR)"/doom.wasm "$(BUILD_DIR)"/doom.data "$(BUILD_DIR)"/doom1.wad
	rm -rf "$(DOOM_ROOT)" "$(FREEPATS_DIR)" "$(DOOM_SHAREWARE_DIR)"

# ----------------------------------------------------------------------
# Chocolate Descent
# ----------------------------------------------------------------------

DESCENT_REPO := https://github.com/InsanityBringer/ChocolateDescent.git
DESCENT_COMMIT := 03cfb6e2dbfee75a041d27fdc45cf561467b8ea4
DESCENT_ROOT := $(CACHE_DIR)/ChocolateDescent
DESCENT_BUILD := $(DESCENT_ROOT)/build-wasm
DESCENT_SHAREWARE_DIR := $(CACHE_DIR)/descent-shareware

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
	@git -C "$(DESCENT_ROOT)" reset -q --hard "$(DESCENT_COMMIT)"
	@git -C "$(DESCENT_ROOT)" clean -q -fdx
	python3 ports/descent/prepare.py "$(DESCENT_ROOT)" "."
	@echo "Chocolate Descent source ready."

descent-data:
	@if [ ! -f descent.hog ] && [ -f DESCENT.HOG ]; then cp DESCENT.HOG descent.hog; fi
	@if [ ! -f descent.pig ] && [ -f DESCENT.PIG ]; then cp DESCENT.PIG descent.pig; fi
	@if [ -f descent.hog ] && [ -f descent.pig ]; then \
		echo "Using local Descent data: descent.hog + descent.pig"; \
	else \
		echo "No complete local Descent data set found; using the freely distributable Descent 1.4 shareware data."; \
		python3 tools/fetch_shareware.py descent "$(DESCENT_SHAREWARE_DIR)"; \
	fi

descent: descent-source descent-data | $(BUILD_DIR)
	@if [ -f descent.hog ] && [ -f descent.pig ]; then \
		hog="descent.hog"; pig="descent.pig"; \
	else \
		hog="$(DESCENT_SHAREWARE_DIR)/descent.hog"; pig="$(DESCENT_SHAREWARE_DIR)/descent.pig"; \
	fi; \
	cp "$$hog" "$(DESCENT_ROOT)/descent.hog"; \
	cp "$$pig" "$(DESCENT_ROOT)/descent.pig"
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
	rm -f "$(BUILD_DIR)"/descent.html "$(BUILD_DIR)"/descent.js "$(BUILD_DIR)"/descent.wasm "$(BUILD_DIR)"/descent.data
	cp "$(DESCENT_BUILD)"/descent.html "$(BUILD_DIR)/"
	@if [ -f "$(DESCENT_BUILD)/descent.js" ]; then cp "$(DESCENT_BUILD)/descent.js" "$(BUILD_DIR)/"; fi
	@if [ -f "$(DESCENT_BUILD)/descent.wasm" ]; then cp "$(DESCENT_BUILD)/descent.wasm" "$(BUILD_DIR)/"; fi
	@if [ -f "$(DESCENT_BUILD)/descent.data" ]; then cp "$(DESCENT_BUILD)/descent.data" "$(BUILD_DIR)/"; fi
	cp -p "$(DESCENT_ROOT)/descent.hog" "$(BUILD_DIR)/descent.hog"
	cp -p "$(DESCENT_ROOT)/descent.pig" "$(BUILD_DIR)/descent.pig"
	@echo
	@echo "Ready: $(BUILD_DIR)/descent.html"

clean-descent:
	rm -f "$(BUILD_DIR)"/descent.html "$(BUILD_DIR)"/descent.js "$(BUILD_DIR)"/descent.wasm "$(BUILD_DIR)"/descent.data "$(BUILD_DIR)"/descent.hog "$(BUILD_DIR)"/descent.pig
	rm -rf "$(DESCENT_ROOT)" "$(DESCENT_MUSIC_DIR)" "$(DESCENT_SHAREWARE_DIR)"



# ----------------------------------------------------------------------
# OpenTTD -- free graphics, mouse-driven 800x600 port
# ----------------------------------------------------------------------

OPENTTD_REPO := https://github.com/OpenTTD/OpenTTD.git
OPENTTD_VERSION := 15.3
OPENTTD_ROOT := $(CACHE_DIR)/OpenTTD
OPENTTD_HOST_BUILD := $(OPENTTD_ROOT)/build-host
OPENTTD_WASM_BUILD := $(OPENTTD_ROOT)/build-pixelram
OPENTTD_BASESET_DIR := $(CACHE_DIR)/openttd-data/baseset

openttd-data: | $(CACHE_DIR)
	python3 tools/fetch_openttd_assets.py "$(OPENTTD_BASESET_DIR)"

openttd-source: | $(CACHE_DIR)
	@if [ ! -d "$(OPENTTD_ROOT)/.git" ]; then \
		echo "Downloading OpenTTD $(OPENTTD_VERSION) source..."; \
		git clone --depth 1 --branch "$(OPENTTD_VERSION)" "$(OPENTTD_REPO)" "$(OPENTTD_ROOT)"; \
	fi
	@git -C "$(OPENTTD_ROOT)" reset -q --hard "$(OPENTTD_VERSION)"
	@git -C "$(OPENTTD_ROOT)" clean -q -fdx
	python3 ports/openttd/prepare.py "$(OPENTTD_ROOT)" "."
	@echo "OpenTTD source ready."

openttd-host: openttd-source
	rm -rf "$(OPENTTD_HOST_BUILD)"
	cmake \
		-S "$(OPENTTD_ROOT)" \
		-B "$(OPENTTD_HOST_BUILD)" \
		-DCMAKE_BUILD_TYPE=Release \
		-DOPTION_TOOLS_ONLY=ON
	cmake --build "$(OPENTTD_HOST_BUILD)" --target tools -j"$$(nproc)"

openttd: openttd-data openttd-host | $(BUILD_DIR)
	rm -rf "$(OPENTTD_WASM_BUILD)"
	emcmake cmake \
		-S "$(OPENTTD_ROOT)" \
		-B "$(OPENTTD_WASM_BUILD)" \
		-DCMAKE_BUILD_TYPE=Release \
		-DHOST_BINARY_DIR="$(abspath $(OPENTTD_HOST_BUILD))" \
		-DOPTION_USE_ASSERTS=OFF \
		-DOPENTTD_PIXELRAM=ON \
		-DOPENTTD_PIXELRAM_BASESET_DIR="$(abspath $(OPENTTD_BASESET_DIR))"
	cmake --build "$(OPENTTD_WASM_BUILD)" --target openttd -j"$$(nproc)"
	rm -f "$(BUILD_DIR)"/openttd.html "$(BUILD_DIR)"/openttd.js \
	      "$(BUILD_DIR)"/openttd.wasm "$(BUILD_DIR)"/openttd.data
	cp "$(OPENTTD_WASM_BUILD)"/openttd.html "$(BUILD_DIR)/"
	@if [ -f "$(OPENTTD_WASM_BUILD)/openttd.js" ]; then cp "$(OPENTTD_WASM_BUILD)/openttd.js" "$(BUILD_DIR)/"; fi
	@if [ -f "$(OPENTTD_WASM_BUILD)/openttd.wasm" ]; then cp "$(OPENTTD_WASM_BUILD)/openttd.wasm" "$(BUILD_DIR)/"; fi
	@if [ -f "$(OPENTTD_WASM_BUILD)/openttd.data" ]; then cp "$(OPENTTD_WASM_BUILD)/openttd.data" "$(BUILD_DIR)/"; fi
	@echo
	@echo "Ready: $(BUILD_DIR)/openttd.html"

clean-openttd:
	rm -f "$(BUILD_DIR)"/openttd.html "$(BUILD_DIR)"/openttd.js \
	      "$(BUILD_DIR)"/openttd.wasm "$(BUILD_DIR)"/openttd.data
	rm -rf "$(OPENTTD_ROOT)" "$(CACHE_DIR)/openttd-data"


# ----------------------------------------------------------------------
# Prince of Persia (SDLPoP) -- first WebAssembly pass
# ----------------------------------------------------------------------

PRINCE_REPO := https://github.com/NagyD/SDLPoP.git
PRINCE_COMMIT := 3c5add5fb7f83d4ceb542823ab66d00146c4271b
PRINCE_ROOT := $(CACHE_DIR)/SDLPoP
PRINCE_SRC := $(PRINCE_ROOT)/src
PRINCE_CONFIG := $(CACHE_DIR)/prince/SDLPoP.ini
PRINCE_DATA_DIR := prince-data

PRINCE_SOURCE_NAMES := \
	main.c data.c \
	seg000.c seg001.c seg002.c seg003.c seg004.c \
	seg005.c seg006.c seg007.c seg008.c seg009.c \
	seqtbl.c replay.c options.c lighting.c screenshot.c menu.c \
	midi.c opl3.c stb_vorbis.c

PRINCE_SOURCES := $(addprefix $(PRINCE_SRC)/,$(PRINCE_SOURCE_NAMES))

prince-source: | $(CACHE_DIR)
	@if [ ! -d "$(PRINCE_ROOT)/.git" ]; then \
		echo "Downloading SDLPoP source..."; \
		git clone "$(PRINCE_REPO)" "$(PRINCE_ROOT)"; \
	fi
	@git -C "$(PRINCE_ROOT)" checkout -q --detach "$(PRINCE_COMMIT)"
	@git -C "$(PRINCE_ROOT)" reset -q --hard "$(PRINCE_COMMIT)"
	@git -C "$(PRINCE_ROOT)" clean -q -fdx
	@mkdir -p "$(dir $(PRINCE_CONFIG))"
	python3 ports/prince/prepare_config.py "$(PRINCE_ROOT)/SDLPoP.ini" "$(PRINCE_CONFIG)"
	python3 ports/prince/prepare_source.py "$(PRINCE_ROOT)"
	@echo "SDLPoP source ready."

prince-data:
	@if [ ! -f "$(PRINCE_DATA_DIR)/PRINCE.DAT" ]; then \
		echo "Prince of Persia game data is missing."; \
		echo "PixelRAM does not automatically download Prince data because its redistribution status is not clear enough."; \
		echo "Copy the complete DOS game data set into prince-data/ and run make prince again."; \
		exit 1; \
	fi

prince: prince-source prince-data | $(BUILD_DIR)
	@echo "Building Prince of Persia for WebAssembly..."
	$(EMCC) \
		-O2 -std=gnu99 -D_GNU_SOURCE=1 \
		-Wall -Wno-unused-variable -Wno-unused-function \
		-sUSE_SDL=2 \
		-sUSE_SDL_IMAGE=2 \
		-sSDL2_IMAGE_FORMATS='["png"]' \
		-sASYNCIFY \
		-sALLOW_MEMORY_GROWTH=1 \
		-sFORCE_FILESYSTEM \
		--pre-js ports/prince/prince_web.js \
		--shell-file "$(SHELL_FILE)" \
		-I"$(PRINCE_SRC)" \
		$(PRINCE_SOURCES) \
		-lm \
		--preload-file "$(PRINCE_DATA_DIR)@/data" \
		--preload-file "$(PRINCE_CONFIG)@/SDLPoP.ini" \
		-o "$(BUILD_DIR)/prince.html"
	@echo
	@echo "Ready: $(BUILD_DIR)/prince.html"

clean-prince:
	rm -f "$(BUILD_DIR)"/prince.html "$(BUILD_DIR)"/prince.js \
	      "$(BUILD_DIR)"/prince.wasm "$(BUILD_DIR)"/prince.data
	rm -rf "$(PRINCE_ROOT)" "$(CACHE_DIR)/prince"

clean:
	rm -rf "$(BUILD_DIR)"
