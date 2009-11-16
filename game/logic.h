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

/*
	Game data Format
	-----------------

	uint32 {4}      - ??
	uint32 {4}      - current time 
	uint32 {4}      - time delta (how much a tick is in "real" time)
	uint32 {4}      - time ticks
	uint32 {4}      - Scene Index               max: 2600
	byte {1}        - Use backup scene
	uint32 {4}      - Backup Scene Index 1
	uint32 {4}      - Backup Scene Index 2
	uint32 {4}      - Selected inventory item
	uint32 {4*1000} - ??
	uint32 {4*16}   - ??
	uint32 {4*16}   - ??
	uint32 {4*128}  - Game progress
	byte {512}      - Game events
	byte {7*32}     - Inventory
	byte {5*128}    - Items
	byte {1262*40}  - Entities (characters and train entities)

	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - Number of sound cache entries
	byte {count*68} - Sound cache entries

	byte {16*128}   - Save point data
	uint32 {4}      - Number of save points (max: 128)
	byte {count*16} - Save points

	... more unknown stuff

	
	Sound cache entry: 68 bytes
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		char {16}       - ??
		char {16}       - ??

*/

#include "lastexpress/data/cursor.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/savegame.h"

#include "common/events.h"

namespace LastExpress {

class Action;
class Beetle;
class Dialog;
class Entities;
class Items;
class LastExpressEngine;
class Menu;
class SavePoints;

class Logic {
public:
	enum JacketType {
		kOriginalJacket = 1,
		kGreenJacket = 2
	};

	enum ChapterIndex {
		kCustom = 0,
		kChapter1 = 1,
		kChapter2 = 2,
		kChapter3 = 3,
		kChapter4 = 4,
		kChapter5 = 5
	};

	struct GameProgress {
		uint32 field_0;
		JacketType jacket;
		uint32 field_8;
		uint32 field_C;
		uint32 event_found_corpse;
		uint32 field_14;
		uint32 field_18;		
		uint32 portrait;
		uint32 field_20;
		uint32 field_24;
		uint32 field_28;
		uint32 chapter;
		uint32 field_30;
		uint32 event_august_met;
		uint32 is_nighttime;					///< 0 = day / 1 = night
		uint32 field_3C;
		uint32 field_40;
		uint32 field_44;
		uint32 field_48;
		uint32 field_4C;
		uint32 field_50;
		uint32 field_54;
		uint32 field_58;
		uint32 field_5C;
		uint32 field_60;
		uint32 field_64;
		uint32 field_68;
		uint32 event_mertens_august_waiting;
		uint32 event_mertens_chronos_invitation;
		uint32 field_74;
		uint32 field_78;	// time?
		uint32 field_7C;
		uint32 field_80;
		uint32 field_84;
		uint32 field_88;
		uint32 field_8C;
		uint32 field_90;
		uint32 field_94;
		uint32 field_98;
		uint32 field_9C;
		uint32 field_A0;
		uint32 field_A4;
		uint32 field_A8;
		uint32 field_AC;
		uint32 field_B0;
		uint32 field_B4;
		uint32 field_B8;
		uint32 field_BC;
		uint32 field_C0;
		uint32 field_C4;
		uint32 field_C8;
		uint32 field_CC;
		uint32 field_D0;
		uint32 field_D4;
		uint32 field_D8;
		uint32 field_DC;
		uint32 field_E0;
		uint32 field_E4;
		uint32 field_E8;
		uint32 field_EC;
		uint32 field_F0;
		uint32 field_F4;
		uint32 field_F8;
		uint32 field_FC;

		// TODO add missing fields

		GameProgress() {
			field_0 = 0;
			jacket = kOriginalJacket;
			field_8 = 0;
			field_C = 0;
			event_found_corpse = 0;
			field_14 = 0;
			field_18 = 0;		
			portrait = _defaultPortrait;
			field_20 = 0;
			field_24 = 0;
			field_28 = 0;
			chapter = kChapter1;
			field_30 = 0;
			event_august_met = 0;
			is_nighttime = 0;
			field_3C = 0;
			field_40 = 0;
			field_44 = 0;
			field_48 = 0;
			field_4C = 0;
			field_50 = 0;
			field_54 = 0;
			field_58 = 0;
			field_5C = 0;
			field_60 = 0;
			field_64 = 0;
			field_68 = 0;
			event_mertens_august_waiting = 0;
			event_mertens_chronos_invitation = 0;
			field_74 = 0;
			field_78 = 0;
			field_7C = 0;
			field_80 = 0;
			field_84 = 0;
			field_88 = 0;
			field_8C = 0;
			field_90 = 0;
			field_94 = 0;
			field_98 = 0;
			field_9C = 0;
			field_A0 = 0;
			field_A4 = 0;
			field_A8 = 0;
			field_AC = 0;
			field_B0 = 0;
			field_B4 = 0;
			field_B8 = 0;
			field_BC = 0;
			field_C0 = 0;
			field_C4 = 0;
			field_C8 = 0;
			field_CC = 0;
			field_D0 = 0;
			field_D4 = 0;
			field_D8 = 0;
			field_DC = 0;
			field_E0 = 0;
			field_E4 = 0;
			field_E8 = 0;
			field_EC = 0;
			field_F0 = 0;
			field_F4 = 0;
			field_F8 = 0;
			field_FC = 0;
		}
	};

	

	struct GameState {
		// Header
		uint32 brightness;
		uint32 volume;

		// Game data
		uint32 field_0;
		uint32 time;
		uint32 timeDelta;
		uint32 timeTicks;
		byte sceneUseBackup;
		uint32 scene;		
		uint32 sceneBackup;
		uint32 sceneBackup2;

		GameProgress progress;
		byte events[512];

		GameState() {
			brightness = _defaultBrigthness;
			volume = _defaultVolume;

			//Game data	
			time = _defaultTime;
			timeDelta = _defaultTimeDelta;
			timeTicks = 0;
			sceneUseBackup = 0;
			scene = _defaultScene;
			sceneBackup = 0;
			sceneBackup2 = 0;

			// Clear game events
			memset(events, 0, 512*sizeof(byte));
		}
	};
	
	Logic(LastExpressEngine *engine);
	~Logic();
	
	bool handleMouseEvent(Common::Event ev);

	void showMenu(bool visible);
	void startGame();
	void switchGame();

	// Scene
	void setScene(uint32 index);
	void updateTrainClock();
	void processItem();

	// Accessors
	bool isGameStarted() { return _runState.gameStarted; }
	bool isShowingMenu() { return _runState.showingMenu; }
	GameId getGameId() { return _runState.gameId; }

	Cursor::CursorStyle getCursorStyle() { return _runState.cursorStyle; }
	Dialog 	   *getGameDialog() { return _dialog; }
	Entities   *getGameEntities() { return _entities; }
	Inventory  *getGameInventory() { return _inventory; }
	Items	   *getGameItems() { return _items; }
	GameState  *getGameState() { return _gameState; }
	SavePoints *getGameSavePoints() { return _savepoints; }
	
private:
	static const uint32 _defaultBrigthness = 0x3;
	static const uint32 _defaultVolume = 0x7;
	static const uint32 _defaultTime = 1037700;
	static const uint32 _defaultTimeDelta = 3;
	static const uint32 _defaultPortrait = 32;	
	static const uint32 _defaultScene = 40;

	// State
	struct RunState {
		GameId gameId;
		bool gameStarted;
		bool showingMenu;
		Cursor::CursorStyle cursorStyle;	// necessary to remember current cursor when inside inventory TODO remove?

		RunState() {
			gameId = kGameBlue;
			gameStarted = false;
			showingMenu = false;
			cursorStyle = Cursor::kCursorNormal;
		}
	};

	LastExpressEngine *_engine;

	RunState _runState;     	///< State of the game session (this data won't be stored in savegames)
	
	Action *_action;			///< Actions
	Beetle *_beetle;			///< Beetle catching
	Dialog *_dialog;			///< Dialogs
	Entities *_entities;		///< Entities
	GameState *_gameState;		///< Global game state
	Inventory *_inventory;  	///< Inventory
	Items *_items;				///< Items
	Menu *_menu;            	///< Main menu handling
	Scene *_scene;				///< Current scene	
	SavePoints *_savepoints;	///< SavePoints
	
	
	
	void preProcessScene(uint32 *index);
	void postProcessScene(uint32 *index);	
	
	// Hotspots
	void processHotspot(SceneHotspot *hotspot);

	void hotspot_enterCompartment(SceneHotspot *hotspot);

	void switchChapter();
	void playFinalSequence();

	void gameOver(int a1, int a2, int scene, bool showScene);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_LOGIC_H