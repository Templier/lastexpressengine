MODULE := engines/lastexpress

MODULE_OBJS := \
	background.o \
	debug.o \
	detection.o \
	graphics.o \
	hpfarchive.o \
	lastexpress.o \
	logic.o \
	resource.o \
	saveload.o \
	sequence.o

# This module can be built as a plugin
ifeq ($(ENABLE_LASTEXPRESS), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
