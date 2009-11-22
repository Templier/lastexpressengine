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

#include "lastexpress/data/cursor.h"

#include "lastexpress/savegame.h"

#include "common/events.h"

namespace LastExpress {

class LastExpressEngine;
	
class Action;
class Beetle;
class Entities;
class Inventory;
class Objects;
class Menu;
class SavePoints;
class Scene;
class Sound;

class Logic {
public:
		
	Logic(LastExpressEngine *engine);
	~Logic();
	
	bool handleMouseEvent(Common::Event ev);

	void showMenu(bool visible);
	void startGame();
	void switchGame();

	void savegame(int param1, int param2, int param3);

	// Scene
	void loadScene(uint32 index);	
	void setScene(uint32 index);

	void loadSceneFromData(int param1, int param2, int param3);

	void updateTrainClock();
	void updateCursor();

	// Index processing
	void processScene();
	uint32 processIndex(uint32 index);
	bool checkSceneFields(uint32 index, bool isSecondCheck);

	// Accessors
	bool isGameStarted() { return _runState.gameStarted; }
	bool isShowingMenu() { return _runState.showingMenu; }
	GameId getGameId() { return _runState.gameId; }

	Cursor::CursorStyle getCursorStyle() { return _runState.cursorStyle; }
	Beetle     *getGameBeetle() { return _beetle; }
	Entities   *getGameEntities() { return _entities; }	
	Sound 	   *getGameSound() { return _sound; }	
	
private:
	
	// State
	struct RunState {
		GameId gameId;
		bool gameStarted;
		bool showingMenu;
		Cursor::CursorStyle cursorStyle;	// necessary to remember current cursor when inside inventory TODO remove?

		// flags
		byte flag_no_entity;
		byte flag_draw_entities;
		byte flag_menu;


		RunState() {
			gameId = kGameBlue;
			gameStarted = false;
			showingMenu = false;
			cursorStyle = Cursor::kCursorNormal;

			flag_no_entity = false;
			flag_draw_entities = false;
			flag_menu = false;
		}
	};

	LastExpressEngine *_engine;

	RunState _runState;     	///< State of the game session (this data won't be stored in savegames)
	
	Action *_action;			///< Actions
	Beetle *_beetle;			///< Beetle catching
	Entities *_entities;		///< Entities
	Menu *_menu;            	///< Main menu handling	
	Scene *_scene;				///< Current scene	
	Sound *_sound;				///< Sound	
	
	void drawScene(uint32 index);
	void preProcessScene(uint32 *index);
	void postProcessScene(uint32 *index);	

	void switchChapter();
	void playFinalSequence();

	void gameOver(int a1, int a2, int scene, bool showScene);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_LOGIC_H