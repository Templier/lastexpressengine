MODULE := engines/lastexpress

MODULE_OBJS := \
	action.o \
	animation.o \
	archive.o \
	background.o \
	cursor.o \
	debug.o \
	detection.o \
	dialog.o \
	font.o \
	graphics.o \
	inventory.o \
	lastexpress.o \
	logic.o \
	menu.o \
	resource.o \
	savepoint.o \
	savegame.o \
	scene.o \
	sequence.o \
	sound.o \
	subtitle.o

# This module can be built as a plugin
ifeq ($(ENABLE_LASTEXPRESS), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
