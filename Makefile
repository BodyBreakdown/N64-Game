V=1
INCLUDE_DIR=include
SOURCE_DIR=src
BUILD_DIR=build

include $(N64_INST)/include/n64.mk
include $(N64_INST)/include/t3d.mk

assets_fnt = $(wildcard assets/fonts/*.fnt)
assets_ttf = $(wildcard assets/fonts/*.ttf)
assets_png = $(wildcard assets/textures/*.png)
assets_txt = $(wildcard assets/*.txt)
assets_glb = $(wildcard assets/*.glb)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(addprefix filesystem/,$(notdir $(assets_ttf:%.ttf=%.font64))) \
			  $(addprefix filesystem/,$(notdir $(assets_fnt:%.fnt=%.font64))) \
			  $(addprefix filesystem/,$(notdir $(assets_txt:%.txt=%.txt))) \
			  $(addprefix filesystem/,$(notdir $(assets_glb:%.glb=%.t3dm)))

MKSPRITE_FLAGS ?=
MKFONT_FLAGS ?= --range 0-255 --monochrome

filesystem/%.sprite: assets/textures/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o filesystem "$<"
filesystem/%.txt: assets/%.txt
	@mkdir -p $(dir $@)
	@cp "$<" "$@"

filesystem/%.font64: assets/fonts/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -o filesystem "$<"

filesystem/%.font64: assets/fonts/%.fnt
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -o filesystem "$<"


filesystem/%.t3dm: assets/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -o filesystem $@

CFLAGS += -I$(INCLUDE_DIR) -I$(N64_INST)/include -O3

all: hey.z64
.PHONY: all

SRC_FILES := $(wildcard $(SOURCE_DIR)/*.c)
OBJS := $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES)) #$(BUILD_DIR)/main.o

$(BUILD_DIR)/hey.dfs: $(assets_conv) 
$(BUILD_DIR)/hey.elf: $(OBJS)

hey.z64: N64_ROM_TITLE="Hey"
hey.z64: $(BUILD_DIR)/hey.dfs 

clean:
	rm -f $(BUILD_DIR)/* *.z64
	rm -rf filesystem
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)