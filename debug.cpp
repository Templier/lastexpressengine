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

#include "lastexpress/debug.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/background.h"

namespace LastExpress {

Debugger::Debugger(LastExpressEngine *engine) {
	_engine = engine;

	// Register the debugger commands
	DCmd_Register("playseq",   WRAP_METHOD(Debugger, cmd_playseq));
	DCmd_Register("playsnd",   WRAP_METHOD(Debugger, cmd_playsnd));
	DCmd_Register("playsbe",   WRAP_METHOD(Debugger, cmd_playsbe));
	DCmd_Register("playnis",   WRAP_METHOD(Debugger, cmd_playnis));
	DCmd_Register("showbg",	   WRAP_METHOD(Debugger, cmd_showbg));
	DCmd_Register("listfiles", WRAP_METHOD(Debugger, cmd_listfiles));
}

Debugger::~Debugger() {
	Common::clearAllDebugChannels();
}

bool Debugger::cmd_playseq(int argc, const char **argv) {
	if (argc == 2) {
		return true;
	} else {
		DebugPrintf("Syntax: playseq <seqname>\n");
	}
	return true;
}

bool Debugger::cmd_playsnd(int argc, const char **argv) {
	if (argc == 2) {
		return true;
	} else {
		DebugPrintf("Syntax: playsnd <sndname>\n");
	}
	return true;
}

bool Debugger::cmd_playsbe(int argc, const char **argv) {
	if (argc == 3) {
		Common::String filename(const_cast<char*>(argv[1]));

		if (!_engine->_resources->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		Subtitle *subtitle = _engine->_resources->loadSubtitle(filename);
		subtitle->render(&_engine->_graphics->_foreground, (int)(argv[2]));
		_engine->_graphics->updateScreen(&_engine->_graphics->_foreground);
	} else {
		DebugPrintf("Syntax: playsbe <sbename> <time>\n");
	}
	return true;
}

bool Debugger::cmd_playnis(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char*>(argv[1]));

		if (!_engine->_resources->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		return true;
	} else {
		DebugPrintf("Syntax: playnis <nisname>\n");
	}
	return true;
}

bool Debugger::cmd_showbg(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char*>(argv[1]));

		if (!_engine->_resources->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		Background *background = _engine->_resources->loadBackground(filename);
		background->render(&_engine->_graphics->_background);

		_engine->_graphics->updateScreen(&_engine->_graphics->_background);
	} else {
		DebugPrintf("Syntax: showbg <bgname>\n");
	}
	return true;
}

bool Debugger::cmd_listfiles(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filter(const_cast<char*>(argv[1]));

		Common::ArchiveMemberList list;
		int count = _engine->_resources->listMatchingMembers(list, filter);

		DebugPrintf("Number of matches: %d\n", count);
		for (Common::ArchiveMemberList::iterator it = list.begin(); it != list.end(); ++it) {
			DebugPrintf("%s\n", (*it)->getName().c_str());
		}
		
		return true;
	} else {
		DebugPrintf("Syntax: listfiles <filter> (use * for all)\n");
	}
	return true;
}

} // End of LastExpress namespace