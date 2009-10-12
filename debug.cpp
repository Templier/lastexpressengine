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

// Data
#include "lastexpress/animation.h"
#include "lastexpress/background.h"
#include "lastexpress/scene.h"
#include "lastexpress/sequence.h"
#include "lastexpress/sound.h"
#include "lastexpress/subtitle.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

#include "common/events.h"

namespace LastExpress {

Debugger::Debugger(LastExpressEngine *engine) : _engine(engine) {

	// Register the debugger commands
	DCmd_Register("playseq",   WRAP_METHOD(Debugger, cmd_playseq));
	DCmd_Register("showframe", WRAP_METHOD(Debugger, cmd_showframe));
	DCmd_Register("playsnd",   WRAP_METHOD(Debugger, cmd_playsnd));
	DCmd_Register("playsbe",   WRAP_METHOD(Debugger, cmd_playsbe));
	DCmd_Register("playnis",   WRAP_METHOD(Debugger, cmd_playnis));
	DCmd_Register("showbg",	   WRAP_METHOD(Debugger, cmd_showbg));
	DCmd_Register("loadscene", WRAP_METHOD(Debugger, cmd_loadscene));
	DCmd_Register("clear",	   WRAP_METHOD(Debugger, cmd_clear));
	DCmd_Register("listfiles", WRAP_METHOD(Debugger, cmd_listfiles));

	resetCommand();
}

Debugger::~Debugger() {
	Common::clearAllDebugChannels();
}

bool Debugger::hasCommand() {
	return (num_params != 0);
}

void Debugger::resetCommand() {
	command = NULL;
	command_params = NULL;
	num_params = 0;
}

int Debugger::getNumber(const char *arg) {
	return strtol(arg, (char **)NULL, 0);
}

void Debugger::copyCommand(int argc, const char **argv) {
	num_params = argc;

	command_params = (char **)malloc(argc);

	for (int i = 0; i < num_params; i++) {
		command_params[i] = (char *)malloc(strlen(argv[i]));
		strcpy(command_params[i], "");
		strcpy(command_params[i], argv[i]);
	}
}

void Debugger::callCommand() {
	(*command)(num_params, (const char **)command_params);
}

bool Debugger::cmd_playseq(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char *>(argv[1]));

		if (!_engine->getResource()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			command = WRAP_METHOD(Debugger, cmd_playseq);
			copyCommand(argc, argv);

			return false;
		} else {
			Sequence sequence;
			if (sequence.loadFile(filename)) {
				for (uint32 i = 0; i < sequence.count(); i++) {

					// Clear screen
					clearBg(A);

					sequence.showFrameBg(A, i);

					askForRedraw();
					redrawScreen();

					// Handle right-click to interrupt sequence
					Common::Event ev;
					_engine->getEventManager()->pollEvent(ev);
					if (ev.type == Common::EVENT_RBUTTONDOWN)
						break;

					_engine->_system->delayMillis(175);
				}
			}

			resetCommand();
		}
	} else {
		DebugPrintf("Syntax: playseq <seqname>\n");
	}
	return true;
}

bool Debugger::cmd_showframe(int argc, const char **argv) {
	if (argc == 3) {
		Common::String filename(const_cast<char *>(argv[1]));

		if (!_engine->getResource()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			command = WRAP_METHOD(Debugger, cmd_showframe);
			copyCommand(argc, argv);

			return false;
		} else {
			Sequence sequence;
			if (sequence.loadFile(filename)) {
				clearBgOverlay();

				if (!sequence.showFrameOverlay(getNumber(argv[2]))) {
					DebugPrintf("Invalid frame index: %i\n", filename.c_str());
					resetCommand();
					return true;
				}

				askForRedraw();
				redrawScreen();

				_engine->_system->delayMillis(1000);
			}

			resetCommand();
		}
	} else {
		DebugPrintf("Syntax: cmd_showframe <seqname> <index>\n");
	}
	return true;
}

bool Debugger::cmd_playsnd(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char *>(argv[1]));

		if (!_engine->getResource()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		_engine->_system->getMixer()->stopAll();
		playSfx(filename);

	} else {
		DebugPrintf("Syntax: playsnd <sndname>\n");
	}
	return true;
}

bool Debugger::cmd_playsbe(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char *>(argv[1]));

		if (!_engine->getResource()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			command = WRAP_METHOD(Debugger, cmd_playsbe);
			copyCommand(argc, argv);

			return false;
		} else {
			SubtitleManager subtitle;
			if (subtitle.loadFile(filename)) {
				for (uint i = 0; i < subtitle.count(); i++) {
					_engine->_system->fillScreen(0);
					subtitle.show(*_engine->getFont(), i);
					_engine->_system->delayMillis(1000);
				}
			}

			resetCommand();
		}

	} else {
		DebugPrintf("Syntax: playsbe <sbename>\n");
	}
	return true;
}

bool Debugger::cmd_playnis(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char *>(argv[1]));

		if (!_engine->getResource()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			command = WRAP_METHOD(Debugger, cmd_playnis);
			copyCommand(argc, argv);

			return false;
		} else {
			Animation animation;
			if (animation.loadFile(filename))
				animation.show();

			resetCommand();
		}

	} else {
		DebugPrintf("Syntax: playnis <nisname>\n");
	}
	return true;
}

bool Debugger::cmd_showbg(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char *>(argv[1]));

		if (!_engine->getResource()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			command = WRAP_METHOD(Debugger, cmd_showbg);
			copyCommand(argc, argv);

			return false;
		} else {
			clearBg(C);

			Background background;
			if (background.loadFile(filename)) {
				background.showBg(C);
				askForRedraw();
			}

			redrawScreen();

			// Pause for a second to be able to see the background
			_engine->_system->delayMillis(1000);

			resetCommand();
		}


	} else {
		DebugPrintf("Syntax: showbg <bgname>\n");
	}
	return true;
}

bool Debugger::cmd_loadscene(int argc, const char **argv) {
	if (argc >= 2) {

		if (argc > 3) {
			DebugPrintf("Syntax: loadscene (<cd number>) <scene index>\n");
			return true;
		}

		int cd = 1, index = 0;
		
		// Check args
		if (argc == 3) {
			cd = getNumber(argv[1]);
			index = getNumber(argv[2]);
		} else {
			index = getNumber(argv[1]);
		}

		if (cd <= 0 || cd > 3 || index < 0 || index > 2500) {
			DebugPrintf("Error: invalid cd number (1-3) or index value (0-2500)");
			return true;
		}
		
		// Store command
		if (!hasCommand()) {
			command = WRAP_METHOD(Debugger, cmd_loadscene);
			copyCommand(argc, argv);

			return false;
		} else {
			_engine->getGraphicsManager()->clear();

			Scene scene(_engine->getResource());
			if (scene.loadScene(cd)) {
				if (scene.showScene(C, index)) {
					askForRedraw();
				} else {
					DebugPrintf("Cannot load scene: %i", index);									
				}
			} else {
				DebugPrintf("Cannot load scenes from CD %i", cd);
			}

			redrawScreen();

			// Pause for a second to be able to see the background
			_engine->_system->delayMillis(1000);

			resetCommand();
		}


	} else {
		DebugPrintf("Syntax: loadscene <cd number> <scene index>\n");
	}
	return true;
}


bool Debugger::cmd_clear(int argc, const char **argv) {
	if (argc == 1) {

	} else {
		DebugPrintf("Syntax: clear - clear the screen\n");
	}

	return true;
}

bool Debugger::cmd_listfiles(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filter(const_cast<char *>(argv[1]));

		Common::ArchiveMemberList list;
		int count = _engine->getResource()->listMatchingMembers(list, filter);

		DebugPrintf("Number of matches: %d\n", count);
		for (Common::ArchiveMemberList::iterator it = list.begin(); it != list.end(); ++it) {
			DebugPrintf("%s\n", (*it)->getName().c_str());
		}
	} else {
		DebugPrintf("Syntax: listfiles <filter> (use * for all)\n");
	}

	return true;
}

} // End of namespace LastExpress
