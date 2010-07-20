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

#include "lastexpress/game/action.h"
#include "lastexpress/game/beetle.h"
#include "lastexpress/game/fight.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savegame.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

#include "common/debug-channels.h"
#include "common/events.h"

namespace LastExpress {

Debugger::Debugger(LastExpressEngine *engine) : _engine(engine), _command(NULL), _numParams(0), _commandParams(NULL) {

	//////////////////////////////////////////////////////////////////////////
	// Register the debugger commands

	// General
	DCmd_Register("help",      WRAP_METHOD(Debugger, cmdHelp));

	// Data
	DCmd_Register("listfiles", WRAP_METHOD(Debugger, cmdListFiles));

	DCmd_Register("playseq",   WRAP_METHOD(Debugger, cmdPlaySeq));
	DCmd_Register("showframe", WRAP_METHOD(Debugger, cmdShowFrame));
	DCmd_Register("showbg",    WRAP_METHOD(Debugger, cmdShowBg));
	DCmd_Register("playsnd",   WRAP_METHOD(Debugger, cmdPlaySnd));
	DCmd_Register("playsbe",   WRAP_METHOD(Debugger, cmdPlaySbe));
	DCmd_Register("playnis",   WRAP_METHOD(Debugger, cmdPlayNis));

	// Scene & interaction
	DCmd_Register("loadscene", WRAP_METHOD(Debugger, cmdLoadScene));
	DCmd_Register("fight",     WRAP_METHOD(Debugger, cmdFight));
	DCmd_Register("beetle",    WRAP_METHOD(Debugger, cmdBeetle));

	// Misc
	DCmd_Register("loadgame",  WRAP_METHOD(Debugger, cmdLoadGame));
	DCmd_Register("clear",     WRAP_METHOD(Debugger, cmdClear));

	resetCommand();
}

Debugger::~Debugger() {
	DebugMan.clearAllDebugChannels();

	// Zero passed pointers
	_engine = NULL;
	_command = NULL;
	_commandParams = NULL;
}

bool Debugger::hasCommand() const {
	return (_numParams != 0);
}

void Debugger::resetCommand() {
	_command = NULL;
	_commandParams = NULL;
	_numParams = 0;
}

int Debugger::getNumber(const char *arg) const {
	return strtol(arg, (char **)NULL, 0);
}

void Debugger::copyCommand(int argc, const char **argv) {
	_commandParams = (char **)malloc((uint)argc);
	if (!_commandParams)
		return;

	_numParams = argc;

	for (int i = 0; i < _numParams; i++) {
		_commandParams[i] = (char *)malloc(strlen(argv[i]));
		strcpy(_commandParams[i], "");
		strcpy(_commandParams[i], argv[i]);
	}

	// Exit the debugger!
	Cmd_Exit(0, 0);
}

void Debugger::callCommand() {
	if (_command)
		(*_command)(_numParams, const_cast<const char **>(_commandParams));
}

void Debugger::loadArchive(ArchiveIndex index) {
	_engine->getResourceManager()->loadArchive(index);
	getScenes()->loadSceneDataFile(index);
}

// Restore loaded archive
void Debugger::restoreArchive() {

	ArchiveIndex index = kArchiveCd1;

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

	_engine->getResourceManager()->loadArchive(index);
	getScenes()->loadSceneDataFile(index);
}

bool Debugger::cmdHelp(int argc, const char **argv) {
	DebugPrintf("Debug flags\n");
	DebugPrintf("-----------\n");
	DebugPrintf(" debugflag_list - Lists the available debug flags and their status\n");
	DebugPrintf(" debugflag_enable - Enables a debug flag\n");
	DebugPrintf(" debugflag_disable - Disables a debug flag\n");
	DebugPrintf("\n");
	DebugPrintf("Commands\n");
	DebugPrintf("--------\n");
	DebugPrintf(" listfiles - list files in the archive\n");
	DebugPrintf(" playseq - play a sequence\n");
	DebugPrintf(" showframe - show a frame from a sequence\n");
	DebugPrintf(" showbg - show a background\n");
	DebugPrintf(" playsnd - play a sound\n");
	DebugPrintf(" playsbe - play a subtitle\n");
	DebugPrintf(" playnis - play an animation\n");
	DebugPrintf(" loadscene - load a scene\n");
	DebugPrintf(" fight - start a fight\n");
	DebugPrintf(" beetle - start the beetle game\n");
	DebugPrintf(" loadgame - load a saved game\n");
	DebugPrintf(" clear - clear the screen\n");
	DebugPrintf("\n");
	return true;
}

//////////////////////////////////////////////////////////////////////////
// Play a sequence
bool Debugger::cmdPlaySeq(int argc, const char **argv) {
	if (argc == 2 || argc == 3) {
		Common::String filename(const_cast<char *>(argv[1]));
		filename += ".seq";

		if (argc == 3)
			loadArchive((ArchiveIndex)getNumber(argv[2]));

		if (!_engine->getResourceManager()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			_command = WRAP_METHOD(Debugger, cmdPlaySeq);
			copyCommand(argc, argv);

			return Cmd_Exit(0, 0);
		} else {
			Sequence *sequence = new Sequence(filename);
			if (sequence->load(getArchive(filename))) {

				// Check that we have at least a frame to show
				if (sequence->count() == 0) {
					delete sequence;
					return false;
				}

				_engine->getCursor()->show(false);

				SequenceFrame player(sequence, 0, true);
				do {
					// Clear screen
					clearBg(GraphicsManager::kBackgroundA);

					_engine->getGraphicsManager()->draw(&player, GraphicsManager::kBackgroundA);

					askForRedraw();
					redrawScreen();

					// Handle right-click to interrupt sequence
					Common::Event ev;
					_engine->getEventManager()->pollEvent(ev);
					if (ev.type == Common::EVENT_RBUTTONUP)
						break;

					_engine->_system->delayMillis(175);

					// go to the next frame
				} while (player.nextFrame());
				_engine->getCursor()->show(true);
			} else {
				// Sequence player is deleting his reference to the sequence, but we need to take care of it if the
				// sequence could not be loaded
				delete sequence;
			}

			resetCommand();

			if (argc == 3)
				restoreArchive();
		}
	} else {
		DebugPrintf("Syntax: playseq <seqname> (<cd number>)\n");
	}
	return true;
}

bool Debugger::cmdShowFrame(int argc, const char **argv) {
	if (argc == 3 || argc == 4) {
		Common::String filename(const_cast<char *>(argv[1]));
		filename += ".seq";

		if (argc == 4)
			loadArchive((ArchiveIndex)getNumber(argv[3]));

		if (!_engine->getResourceManager()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			_command = WRAP_METHOD(Debugger, cmdShowFrame);
			copyCommand(argc, argv);

			return Cmd_Exit(0, 0);
		} else {
			Sequence sequence(filename);
			if (sequence.load(getArchive(filename))) {
				_engine->getCursor()->show(false);
				clearBg(GraphicsManager::kBackgroundOverlay);

				AnimFrame *frame = sequence.getFrame((uint32)getNumber(argv[2]));
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

			if (argc == 4)
				restoreArchive();
		}
	} else {
		DebugPrintf("Syntax: cmd_showframe <seqname> <index> (<cd number>)\n");
	}
	return true;
}

bool Debugger::cmdPlaySnd(int argc, const char **argv) {
	if (argc == 2 || argc == 3) {

		if (argc == 3)
			loadArchive((ArchiveIndex)getNumber(argv[2]));

		// Add .SND at the end of the filename if needed
		Common::String name(const_cast<char *>(argv[1]));
		if (!name.contains('.'))
			name += ".SND";

		if (!_engine->getResourceManager()->hasFile(name)) {
			DebugPrintf("Cannot find file: %s\n", name.c_str());
			return true;
		}

		_engine->_system->getMixer()->stopAll();

		// FIXME: use another sound stream for debug (the one in the engine is not setup for playing a single sound)
		getSound()->getSfxStream()->load(getArchive(name));

		if (argc == 3)
			restoreArchive();
	} else {
		DebugPrintf("Syntax: playsnd <sndname> (<cd number>)\n");
	}
	return true;
}

bool Debugger::cmdPlaySbe(int argc, const char **argv) {
	if (argc == 2 || argc == 3) {
		Common::String filename(const_cast<char *>(argv[1]));

		if (argc == 3)
			loadArchive((ArchiveIndex)getNumber(argv[2]));

		filename += ".sbe";

		if (!_engine->getResourceManager()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			_command = WRAP_METHOD(Debugger, cmdPlaySbe);
			copyCommand(argc, argv);

			return Cmd_Exit(0, 0);
		} else {
			SubtitleManager subtitle(_engine->getFont());
			if (subtitle.load(getArchive(filename))) {
				_engine->getCursor()->show(false);
				for (uint16 i = 0; i < subtitle.getMaxTime(); i += 25) {
					clearBg(GraphicsManager::kBackgroundAll);

					subtitle.setTime(i);
					_engine->getGraphicsManager()->draw(&subtitle, GraphicsManager::kBackgroundOverlay);

					askForRedraw();
					redrawScreen();

					// Handle right-click to interrupt sequence
					Common::Event ev;
					_engine->getEventManager()->pollEvent(ev);
					if (ev.type == Common::EVENT_RBUTTONUP)
						break;

					_engine->_system->delayMillis(500);
				}
				_engine->getCursor()->show(true);
			}

			if (argc == 3)
				restoreArchive();

			resetCommand();
		}
	} else {
		DebugPrintf("Syntax: playsbe <sbename> (<cd number>)\n");
	}
	return true;
}

bool Debugger::cmdPlayNis(int argc, const char **argv) {
	if (argc == 2 || argc == 3) {
		Common::String filename(const_cast<char *>(argv[1]));

		if (argc == 3)
			loadArchive((ArchiveIndex)getNumber(argv[2]));

		filename += ".nis";

		if (!_engine->getResourceManager()->hasFile(filename)) {
			DebugPrintf("Cannot find file: %s\n", filename.c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			_command = WRAP_METHOD(Debugger, cmdPlayNis);
			copyCommand(argc, argv);

			return Cmd_Exit(0, 0);
		} else {
			// Make sure we are not called in a loop
			_numParams = 0;

			Animation animation;
			if (animation.load(getArchive(filename))) {
				_engine->getCursor()->show(false);
				animation.play();
				_engine->getCursor()->show(true);
			}

			if (argc == 3)
				restoreArchive();

			resetCommand();
		}
	} else {
		DebugPrintf("Syntax: playnis <nisname> (<cd number>)\n");
	}
	return true;
}

bool Debugger::cmdShowBg(int argc, const char **argv) {
	if (argc == 2 || argc == 3) {
		Common::String filename(const_cast<char *>(argv[1]));

		if (argc == 3)
			loadArchive((ArchiveIndex)getNumber(argv[2]));

		if (!_engine->getResourceManager()->hasFile(filename + ".BG")) {
			DebugPrintf("Cannot find file: %s\n", (filename + ".BG").c_str());
			return true;
		}

		// Store command
		if (!hasCommand()) {
			_command = WRAP_METHOD(Debugger, cmdShowBg);
			copyCommand(argc, argv);

			return Cmd_Exit(0, 0);
		} else {
			clearBg(GraphicsManager::kBackgroundC);

			Background *background = _engine->getResourceManager()->loadBackground(filename);
			if (background) {
				_engine->getGraphicsManager()->draw(background, GraphicsManager::kBackgroundC);
				delete background;
				askForRedraw();
			}

			redrawScreen();

			if (argc == 3)
				restoreArchive();

			// Pause for a second to be able to see the background
			_engine->_system->delayMillis(1000);

			resetCommand();
		}
	} else {
		DebugPrintf("Syntax: showbg <bgname> (<cd number>)\n");
	}
	return true;
}

bool Debugger::cmdLoadScene(int argc, const char **argv) {
	if (argc == 2 || argc == 3) {
		int cd = 1;
		SceneIndex index = (SceneIndex)getNumber(argv[1]);;

		// Check args
		if (argc == 3)
			loadArchive((ArchiveIndex)getNumber(argv[2]));

		if (index > 2500) {
			DebugPrintf("Error: invalid index value (0-2500)");
			return true;
		}

		// Store command
		if (!hasCommand()) {
			_command = WRAP_METHOD(Debugger, cmdLoadScene);
			copyCommand(argc, argv);

			return Cmd_Exit(0, 0);
		} else {

			clearBg(GraphicsManager::kBackgroundAll);

			/************  DEBUG  *************************/
			// Use to find scenes with certain values

			//for (int i = index; i < 2500; i++) {
			//	loadSceneObject(scene, i);

			//	if (scene.getHeader() && scene.getHeader()->car == 5 && scene.getHeader()->position == 81) {
			//		DebugPrintf("Found scene: %d", i);

			//		// Draw scene found
			//		_engine->getGraphicsManager()->draw(&scene, GraphicsManager::kBackgroundC);

			//		askForRedraw();
			//		redrawScreen();
			//		_engine->_system->delayMillis(500);

			//		break;
			//	}
			//}

			//delete _sceneLoader;
			//resetCommand();
			//return true;

			/*********************************************/
			Scene *scene = getScenes()->get(index);
			if (!scene) {
				DebugPrintf("Cannot load scene %i from CD %i", index, cd);
				resetCommand();

				return true;
			}

			_engine->getGraphicsManager()->draw(scene, GraphicsManager::kBackgroundC);

			askForRedraw();
			redrawScreen();

			// Pause for a second to be able to see the scene
			_engine->_system->delayMillis(500);

			if (argc == 3)
				restoreArchive();

			resetCommand();
		}
	} else {
		DebugPrintf("Syntax: loadscene <scene index> (<cd number>)\n");
	}
	return true;
}


bool Debugger::cmdClear(int argc, const char **) {
	if (argc == 1) {
		clearBg(GraphicsManager::kBackgroundAll);
		askForRedraw();
		redrawScreen();
	} else {
		DebugPrintf("Syntax: clear - clear the screen\n");
	}

	return true;
}

bool Debugger::cmdListFiles(int argc, const char **argv) {
	if (argc == 2 || argc == 3) {		
		Common::String filter(const_cast<char *>(argv[1]));

		// Load the proper archive
		if (argc == 3)	
			loadArchive((ArchiveIndex)getNumber(argv[2]));		

		Common::ArchiveMemberList list;
		int count = _engine->getResourceManager()->listMatchingMembers(list, filter);

		DebugPrintf("Number of matches: %d\n", count);
		for (Common::ArchiveMemberList::iterator it = list.begin(); it != list.end(); ++it)
			DebugPrintf(" %s\n", (*it)->getName().c_str());

		// Restore archive
		if (argc == 3)
			restoreArchive();
	} else {
		DebugPrintf("Syntax: listfiles <filter> (use * for all)\n (<cd number>)");
	}

	return true;
}

bool Debugger::cmdLoadGame(int argc, const char **argv) {
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

bool Debugger::cmdFight(int argc, const char **argv) {
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

		loadArchive(index);

		// Store command
		if (!hasCommand()) {
			_command = WRAP_METHOD(Debugger, cmdFight);
			copyCommand(argc, argv);

			return false;
		} else {
			// Make sure we are not called in a loop
			_numParams = 0;

			clearBg(GraphicsManager::kBackgroundAll);
			askForRedraw();
			redrawScreen();

			SceneIndex lastScene = getState()->scene;

			getFight()->setup(type) ? DebugPrintf("Lost fight!\n") : DebugPrintf("Won fight!\n");

			// Pause for a second to be able to see the final scene
			_engine->_system->delayMillis(1000);

			// Restore loaded archive
			restoreArchive();

			// Stop audio and restore scene
			getSound()->getSfxStream()->stop();
			getSound()->getMusicStream()->stop();

			clearBg(GraphicsManager::kBackgroundAll);

			Scene *scene = getScenes()->get(lastScene);
			_engine->getGraphicsManager()->draw(scene, GraphicsManager::kBackgroundC);

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

bool Debugger::cmdBeetle(int argc, const char **argv) {
	if (argc == 1) {
		// Load proper data file (beetle game in in Cd2)
		loadArchive(kArchiveCd2);

		// Store command
		if (!hasCommand()) {
			_command = WRAP_METHOD(Debugger, cmdBeetle);
			copyCommand(argc, argv);

			return false;
		} else {
			clearBg(GraphicsManager::kBackgroundAll);
			askForRedraw();
			redrawScreen();

			// Save current state
			SceneIndex previousScene = getState()->scene;
			ObjectLocation previousLocation = getInventory()->getEntry(kItemBeetle)->location;
			ChapterIndex previousChapter = (ChapterIndex)getProgress().chapter;

			// Setup scene & inventory
			getProgress().chapter = kChapter2;
			Scene *scene = getScenes()->get(kSceneBeetle);
			getInventory()->getEntry(kItemBeetle)->location = kLocation3;

			askForRedraw();
			redrawScreen();

			// Load the beetle game
			Action *action   = new Action(_engine);
			Beetle *beetle = new Beetle(_engine);
			if (!beetle->isLoaded())
				beetle->load();

			// Play the game
			Common::Event ev;
			bool playgame = true;
			while (playgame) {
				// Update beetle
				beetle->update();

				askForRedraw();
				redrawScreen();

				while (g_engine->getEventManager()->pollEvent(ev)) {

					switch (ev.type) {
					default:
						break;

					case Common::EVENT_KEYDOWN:
						// Exit beetle game on escape
						if (ev.kbd.keycode == Common::KEYCODE_ESCAPE)
							playgame = false;

						break;

					case Common::EVENT_MOUSEMOVE: {
						// Update cursor
						CursorStyle style = kCursorNormal;
						SceneHotspot *hotspot = NULL;
						if (scene->checkHotSpot(ev.mouse, &hotspot))
							style = action->getCursor(*hotspot);

						_engine->getCursor()->setStyle(style);
						break;
					}


					case Common::EVENT_LBUTTONUP:
					case Common::EVENT_RBUTTONUP:
						// Update coordinates
						getLogic()->getGameState()->setCoordinates(ev.mouse);

						if (beetle->catchBeetle())
							playgame = false;
						break;
					}

					_engine->_system->delayMillis(10);
				}
			}

			// Cleanup
			beetle->unload();
			delete beetle;
			delete action;

			// Pause for a second to be able to see the final scene
			_engine->_system->delayMillis(1000);

			// Restore state
			getProgress().chapter = previousChapter;
			getInventory()->getEntry(kItemBeetle)->location = previousLocation;

			// Restore loaded archive
			restoreArchive();

			// Stop audio and restore scene
			getSound()->getSfxStream()->stop();
			getSound()->getMusicStream()->stop();

			clearBg(GraphicsManager::kBackgroundAll);

			Scene *oldScene = getScenes()->get(previousScene);
			_engine->getGraphicsManager()->draw(oldScene, GraphicsManager::kBackgroundC);

			askForRedraw();
			redrawScreen();

			resetCommand();
		}
	} else {
		DebugPrintf("Syntax: beetle\n");
	}

	return true;
}

} // End of namespace LastExpress
