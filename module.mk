MODULE := engines/lastexpress

MODULE_OBJS := \
	data/animation.o \
	data/archive.o \
	data/background.o \
	data/cursor.o \
	data/font.o \
	data/scene.o \
	data/sequence.o \
	data/sound.o \
	data/subtitle.o \
	entities/chapters.o \
	entities/entity.o \
	game/action.o \
	game/beetle.o \
	game/dialog.o \
	game/items.o \
	game/inventory.o \
	game/logic.o \
	game/menu.o \
	game/savepoint.o \
	debug.o \
	detection.o \
	graphics.o \
	lastexpress.o \
	resource.o \
	savegame.o

# This module can be built as a plugin
ifeq ($(ENABLE_LASTEXPRESS), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
