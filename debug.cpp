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
#include "lastexpress/data/animation.h"
#include "lastexpress/data/background.h"
#include "lastexpress/data/cursor.h"
#include "lastexpress/data/scene.h"
#include "lastexpress/data/sequence.h"
#include "lastexpress/data/snd.h"
#include "lastexpress/data/subtitle.h"

#include "lastexpress/game/fight.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savegame.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

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
	DCmd_Register("showbg",    WRAP_METHOD(Debugger, cmd_showbg));
	DCmd_Register("loadscene", WRAP_METHOD(Debugger, cmd_loadscene));
	DCmd_Register("clear",     WRAP_METHOD(Debugger, cmd_clear));
	DCmd_Register("listfiles", WRAP_METHOD(Debugger, cmd_listfiles));
	DCmd_Register("loadgame",  WRAP_METHOD(Debugger, cmd_loadgame));
	DCmd_Register("fight",     WRAP_METHOD(Debugger, cmd_fight));

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

	// Exit the debugger!
	Cmd_Exit(0, 0);
}

void Debugger::callCommand() {
	(*command)(num_params, const_cast<const char **>(command_params));
}

bool Debugger::cmd_playseq(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char *>(argv[1]));

		filename += ".seq";

		if (!_engine->getResourceManager()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			command = WRAP_METHOD(Debugger, cmd_playseq);
			copyCommand(argc, argv);

			return false;
		} else {
			Sequence *sequence = new Sequence();
			if (sequence->loadFile(filename)) {
				_engine->getCursor()->show(false);
				SequencePlayer player(sequence);
				while (!player.hasEnded()) {
					// Clear screen
					clearBg(GraphicsManager::kBackgroundA);

					_engine->getGraphicsManager()->draw(&player, GraphicsManager::kBackgroundA);

					askForRedraw();
					redrawScreen();

					// Handle right-click to interrupt sequence
					Common::Event ev;
					_engine->getEventManager()->pollEvent(ev);
					if (ev.type == Common::EVENT_RBUTTONDOWN)
						break;

					_engine->_system->delayMillis(175);

					// Update the player status
					player.processTime();
				}
				_engine->getCursor()->show(true);
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

		filename += ".seq";

		if (!_engine->getResourceManager()->hasFile(filename)) {
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
				_engine->getCursor()->show(false);
				clearBg(GraphicsManager::kBackgroundOverlay);

				AnimFrame *frame = sequence.getFrame(getNumber(argv[2]));
				if (!frame) {
					DebugPrintf("Invalid frame index: %i\n", filename.c_str());
					resetCommand();
					return true;
				}

				_engine->getGraphicsManager()->draw(frame, GraphicsManager::kBackgroundOverlay);
				delete frame;

				askForRedraw();
				redrawScreen();

				_engine->_system->delayMillis(1000);
				_engine->getCursor()->show(true);
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

		if (!_engine->getResourceManager()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		_engine->_system->getMixer()->stopAll();

		// FIXME: use another sound stream for debug (the one in the engine is not setup for playing a single sound)
		getSound()->getSfxStream()->load(_engine->getResourceManager()->getFileStream(filename));
	} else {
		DebugPrintf("Syntax: playsnd <sndname>\n");
	}
	return true;
}

bool Debugger::cmd_playsbe(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filename(const_cast<char *>(argv[1]));

		filename += ".sbe";

		if (!_engine->getResourceManager()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			command = WRAP_METHOD(Debugger, cmd_playsbe);
			copyCommand(argc, argv);

			return false;
		} else {
			SubtitleManager subtitle(_engine->getFont());
			if (subtitle.loadFile(filename)) {
				_engine->getCursor()->show(false);
				for (uint16 i = 0; i < subtitle.getMaxTime(); i++) {
					clearBg(GraphicsManager::kBackgroundAll);

					subtitle.setTime(i);
					_engine->getGraphicsManager()->draw(&subtitle, GraphicsManager::kBackgroundOverlay);

					askForRedraw();
					redrawScreen();

					// Handle right-click to interrupt sequence
					Common::Event ev;
					_engine->getEventManager()->pollEvent(ev);
					if (ev.type == Common::EVENT_RBUTTONDOWN)
						break;

					_engine->_system->delayMillis(500);
					i += 25;
				}
				_engine->getCursor()->show(true);
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

		filename += ".nis";

		if (!_engine->getResourceManager()->hasFile(filename)) {
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
			if (animation.loadFile(filename)) {
				_engine->getCursor()->show(false);
				animation.play();
				_engine->getCursor()->show(true);
			}

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

		if (!_engine->getResourceManager()->hasFile(filename + ".BG")) {
			DebugPrintf("Cannot find file: %s\n", (filename + ".BG").c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			command = WRAP_METHOD(Debugger, cmd_showbg);
			copyCommand(argc, argv);

			return false;
		} else {
			clearBg(GraphicsManager::kBackgroundC);

			Background *background = _engine->getResourceManager()->loadBackground(filename);
			if (background) {
				_engine->getGraphicsManager()->draw(background, GraphicsManager::kBackgroundC);
				delete background;
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

			// Check for cd and load the proper data file in the fly
			// instead of relying on the engine scene manager which could have
			// loaded a different cd
			SceneManager *_sceneMan = new SceneManager();
			if (!_sceneMan->load(_engine->getResourceManager()->getFileStream(Common::String::printf("CD%iTRAIN.DAT", cd)))) {
				DebugPrintf("Cannot load data for CD %i", cd);
				resetCommand();
				return true;
			}

			clearBg(GraphicsManager::kBackgroundAll);

			Scene s;
			if (!_sceneMan->loadScene(&s, index)) {
				DebugPrintf("Cannot load scene %i from CD %i", index, cd);
				resetCommand();
				return true;
			}

			_engine->getGraphicsManager()->draw(&s, GraphicsManager::kBackgroundC);

			askForRedraw();
			redrawScreen();

			// Pause for a second to be able to see the scene
			_engine->_system->delayMillis(1000);

			delete _sceneMan;

			resetCommand();
		}
	} else {
		DebugPrintf("Syntax: loadscene (<cd number>) <scene index>\n");
	}
	return true;
}


bool Debugger::cmd_clear(int argc, const char **argv) {
	if (argc == 1) {
		clearBg(GraphicsManager::kBackgroundAll);
		askForRedraw();
		redrawScreen();
	} else {
		DebugPrintf("Syntax: clear - clear the screen\n");
	}

	return true;
}

bool Debugger::cmd_listfiles(int argc, const char **argv) {
	if (argc == 2) {
		Common::String filter(const_cast<char *>(argv[1]));

		Common::ArchiveMemberList list;
		int count = _engine->getResourceManager()->listMatchingMembers(list, filter);

		DebugPrintf("Number of matches: %d\n", count);
		for (Common::ArchiveMemberList::iterator it = list.begin(); it != list.end(); ++it) {
			DebugPrintf("%s\n", (*it)->getName().c_str());
		}
	} else {
		DebugPrintf("Syntax: listfiles <filter> (use * for all)\n");
	}

	return true;
}

bool Debugger::cmd_loadgame(int argc, const char **argv) {
	if (argc == 2) {
		int id = getNumber(argv[1]);

		if (id == 0 || id > 6)
			goto error;

		if (!getSaveLoad()->loadGame((GameId)(id - 1)))
			DebugPrintf("Error loading game with id=%d", id);

	} else {
error:
		DebugPrintf("Syntax: loadgame <id> (id=1-6)\n");
	}

	return true;
}

bool Debugger::cmd_fight(int argc, const char **argv) {
	if (argc == 2) {
		FightType type = (FightType)getNumber(argv[1]);

		// Load proper data file
		ArchiveIndex index = kArchiveCd1;
		switch (type) {
		default:
			goto error;

		case kFightMilos:
			index = kArchiveCd1;
			break;

		case kFightAnna:		
			index = kArchiveCd2;
			break;

		case kFightIvo:
		case kFightSalko:
		case kFightVesna:
			index = kArchiveCd3;
			break;
		}

		getLogic()->loadSceneDataFile(index);

		// Store command
		if (!hasCommand()) {
			command = WRAP_METHOD(Debugger, cmd_fight);
			copyCommand(argc, argv);

			return false;
		} else {
			clearBg(GraphicsManager::kBackgroundAll);
			askForRedraw();
			redrawScreen();

			int lastScene = getState()->scene;

			getFight()->setup(type) ? DebugPrintf("Lost fight!\n") : DebugPrintf("Won fight!\n");

			// Pause for a second to be able to see the final scene
			_engine->_system->delayMillis(1000);

			// Restore loaded archive
			switch (getProgress().chapter) {
			default:
			case kChapter1:
				index = kArchiveCd1;
				break;

			case kChapter2:
			case kChapter3:
				index = kArchiveCd2;
				break;

			case kChapter4:
			case kChapter5:
				index = kArchiveCd3;
				break;
			}

			getLogic()->loadSceneDataFile(index);

			// Stop audio and restore scene
			getSound()->getSfxStream()->stop();
			getSound()->getMusicStream()->stop();

			clearBg(GraphicsManager::kBackgroundAll);

			loadSceneObject(scene, lastScene);			
			_engine->getGraphicsManager()->draw(&scene, GraphicsManager::kBackgroundC);

			askForRedraw();
			redrawScreen();


			resetCommand();
		}
	} else {
error:
		DebugPrintf("Syntax: fight <id> (id=2001-2005)\n");
	}

	return true;
}

} // End of namespace LastExpress
