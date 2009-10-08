/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef LASTEXPRESS_DEBUG_H
#define LASTEXPRESS_DEBUG_H

#include "common/debug.h"
#include "gui/debugger.h"
#include "engines/engine.h"

namespace LastExpress {

enum {
	kLastExpressDebugAll = 1 << 0,
	kLastExpressDebugGraphics = 1 << 1,
	kLastExpressDebugResource = 1 << 2,
	kLastExpressDebugCursor = 1 << 3,
	kLastExpressDebugSound = 1 << 4,
	kLastExpressDebugSubtitle = 1 << 5,
	kLastExpressDebugSavegame = 1 << 6,
	kLastExpressDebugScenes = 1 << 7,
	kLastExpressDebugUnknown = 1 << 8
	// the current limitation is 32 debug levels (1 << 31 is the last one)
};

class LastExpressEngine;

class Debugger : public GUI::Debugger {
public:
	Debugger(LastExpressEngine *engine);
	~Debugger();

	bool hasCommand();
	void callCommand();

private:
	LastExpressEngine *_engine;

	bool cmd_playseq(int argc, const char **argv);
	bool cmd_showframe(int argc, const char **argv);
	bool cmd_playsnd(int argc, const char **argv);
	bool cmd_playsbe(int argc, const char **argv);
	bool cmd_playnis(int argc, const char **argv);
	bool cmd_showbg(int argc, const char **argv);
	bool cmd_listfiles(int argc, const char **argv);

	void resetCommand();
	void copyCommand(int argc, const char **argv);
	int getNumber(const char *arg);

	Debuglet *command;
	int num_params;
	char **command_params;
};

}  // End of LastExpress namespace

#endif // LASTEXPRESS_DEBUG_H
