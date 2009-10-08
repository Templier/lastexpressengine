MODULE := engines/lastexpress

MODULE_OBJS := \
	animation.o \
	archive.o \
	background.o \
	cursor.o \
	debug.o \
	detection.o \
	font.o \
	lastexpress.o \
	logic.o \
	menu.o \
	resource.o \
	saveload.o \
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
