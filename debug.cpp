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

#include "sound/mixer.h"

#include "lastexpress/debug.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/animation.h"
#include "lastexpress/background.h"
#include "lastexpress/sequence.h"
#include "lastexpress/subtitle.h"
#include "lastexpress/sound.h"

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
		Common::String filename(const_cast<char*>(argv[1]));

		if (!_engine->_resource->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		Sequence sequence(_engine->_resource);
		if (sequence.load(filename)) {
			for (uint32 i = 0; i < sequence.count(); i++) {
				sequence.show(i);
				_engine->_system->delayMillis(250);
			}
		}
	} else {
		DebugPrintf("Syntax: playseq <seqname>\n");
	}
	return true;
}

bool Debugger::cmd_playsnd(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char*>(argv[1]));

		if (!_engine->_resource->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		_engine->_system->getMixer()->stopAll();

		_engine->_sfx->load(filename);

	} else {
		DebugPrintf("Syntax: playsnd <sndname>\n");
	}
	return true;
}

bool Debugger::cmd_playsbe(int argc, const char **argv) {
	if (argc == 3) {
		Common::String filename(const_cast<char*>(argv[1]));

		if (!_engine->_resource->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		SubtitleManager subtitle(_engine->_resource);
		if (subtitle.load(filename)) {
			for (uint i = 0; i < subtitle.count(); i++) {
				_engine->_system->fillScreen(0);
				subtitle.show(*_engine->_font, i);
				_engine->_system->delayMillis(250);
			}
		}

	} else {
		DebugPrintf("Syntax: playsbe <sbename> <time>\n");
	}
	return true;
}

bool Debugger::cmd_playnis(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char*>(argv[1]));

		if (!_engine->_resource->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		Animation animation(_engine->_resource);
		if (animation.load(filename))
			animation.show();	

	} else {
		DebugPrintf("Syntax: playnis <nisname>\n");
	}
	return true;
}

bool Debugger::cmd_showbg(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char*>(argv[1]));

		if (!_engine->_resource->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		Background background(_engine->_resource);
		if (background.load(filename))
			background.show();

	} else {
		DebugPrintf("Syntax: showbg <bgname>\n");
	}
	return true;
}

bool Debugger::cmd_listfiles(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filter(const_cast<char*>(argv[1]));

		Common::ArchiveMemberList list;
		int count = _engine->_resource->listMatchingMembers(list, filter);

		DebugPrintf("Number of matches: %d\n", count);
		for (Common::ArchiveMemberList::iterator it = list.begin(); it != list.end(); ++it) {
			DebugPrintf("%s\n", (*it)->getName().c_str());
		}
	} else {
		DebugPrintf("Syntax: listfiles <filter> (use * for all)\n");
	}

	return true;
}

} // End of LastExpress namespace