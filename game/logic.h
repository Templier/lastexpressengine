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

#ifndef LASTEXPRESS_LOGIC_H
#define LASTEXPRESS_LOGIC_H

#include "lastexpress/shared.h"

#include "lastexpress/eventhandler.h"

#include "common/events.h"

namespace LastExpress {

class LastExpressEngine;

class Action;
class Beetle;
class Entities;
class Fight;
class Menu;
class SaveLoad;
class Scene;
class Sound;
class State;

class Logic : public EventHandler {
public:

	Logic(LastExpressEngine *engine);
	~Logic();

	void eventMouseClick(const Common::Event &ev);
	void eventMouseMove(const Common::Event &ev);

	void showMenu(bool visible);
	void startGame();
	void switchGame();

	void gameOver(TimeType type, uint32 time, SceneIndex sceneIndex, bool showScene);

	// Scene
	void loadSceneDataFile(ArchiveIndex archive) const;
	void loadScene(SceneIndex sceneIndex);
	void setScene(SceneIndex sceneIndex);

	void loadSceneFromObject(ObjectIndex object);
	void loadSceneFromObject2(ObjectIndex object);
	void loadSceneFromData(int param1, int param2, int param3);
	void loadSceneFromItem(InventoryItem item);

	void updateTrainClock();
	void updateCursor(bool redraw = true);

	// Index processing
	void processScene();
	SceneIndex processIndex(SceneIndex sceneIndex);
	bool checkSceneFields(SceneIndex sceneIndex, bool isSecondCheck) const;

	// Accessors
	bool isGameStarted() { return _runState.gameStarted; }
	bool isShowingMenu() { return _runState.showingMenu; }
	GameId getGameId() { return _runState.gameId; }
	CursorStyle getCursorStyle() { return _runState.cursorStyle; }

	Action 	   *getGameAction()   { return _action; }
	Beetle     *getGameBeetle()   { return _beetle; }
	Entities   *getGameEntities() { return _entities; }
	Fight      *getGameFight()    { return _fight; }
	SaveLoad   *getGameSaveLoad() { return _saveload; }
	Sound 	   *getGameSound()    { return _sound; }
	State      *getGameState()    { return _state; }

private:

	// State
	struct RunState {
		GameId gameId;
		bool gameStarted;
		bool showingMenu;
		CursorStyle cursorStyle;    // necessary to remember current cursor when inside inventory TODO remove?

		// flags
		bool flag_no_entity;
		bool flag_draw_entities;

		RunState() {
			gameId = kGameBlue;
			gameStarted = false;
			showingMenu = false;
			cursorStyle = kCursorNormal;

			flag_no_entity = false;
			flag_draw_entities = false;
		}
	};

	LastExpressEngine *_engine;

	RunState  _runState;        ///< State of the game session (this data won't be stored in savegames)

	Action   *_action;          ///< Actions
	Beetle   *_beetle;          ///< Beetle catching
	Entities *_entities;        ///< Entities
	Fight    *_fight;           ///< Fight handling
	Menu     *_menu;            ///< Main menu handling
	SaveLoad *_saveload;        ///< Save & loading
	Scene    *_currentScene;    ///< Current scene
	Sound    *_sound;           ///< Sound
	State    *_state;           ///< Game state

	void drawScene(SceneIndex sceneIndex);
	void preProcessScene(SceneIndex *index);
	void postProcessScene();

	void switchChapter();
	void playFinalSequence();
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_LOGIC_H
