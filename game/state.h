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

#ifndef LASTEXPRESS_STATE_H
#define LASTEXPRESS_STATE_H

#include "lastexpress/shared.h"

#include "common/system.h"

namespace LastExpress {

class LastExpressEngine;

class Inventory;
class Objects;
class SavePoints;

class State {
public:
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
		uint32 is_egg_open;
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
		uint32 event_met_boutarel;
		uint32 event_met_hadija;
		uint32 event_met_yasmin;
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
			jacket = kJacketOriginal;
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
			is_egg_open = 0;
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
			event_met_boutarel = 0;
			event_met_hadija = 0;
			event_met_yasmin = 0;
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

		// Needs to be figured out
		int field1000[1000];
		int field16[16];
		int field16_2[16];

		GameState() {
			brightness = _defaultBrigthness;
			volume = _defaultVolume;

			//Game data
			time = _defaultTime;
			timeDelta = _defaultTimeDelta;
			timeTicks = 0;
			sceneUseBackup = 0;
			scene = kSceneDefault;
			sceneBackup = 0;
			sceneBackup2 = 0;

			// Clear game events
			memset(events, 0, 512*sizeof(byte));

			memset(field1000, 0, 1000*sizeof(int));
			memset(field16, 0, 16*sizeof(int));
			memset(field16_2, 0, 16*sizeof(int));
		}
	};

	struct Flags {
		bool flag_0;		
		bool flag_3;

		bool gameRunning;		
		
		// Mouse flags
		bool mouseLeftClick;
		bool mouseRightClick;
		bool mouseMove;

		bool flag_entities_0;
		bool flag_entities_1;

		bool shouldRedraw;
		bool shouldDrawEggOrHourGlass;

		Flags() {
			flag_0 = false;
			flag_3 = false;

			gameRunning = false;
			
			mouseRightClick = false;
			mouseLeftClick = false;
			mouseMove = false;

			flag_entities_0 = false;
			flag_entities_1 = false;

			shouldRedraw = false;
			shouldDrawEggOrHourGlass = false;
		}
	};

	State(LastExpressEngine *engine);
	~State();

	// Timer
	int timer;

	// Accessors
	Inventory  *getGameInventory() { return _inventory; }
	Objects    *getGameObjects() { return _objects; }
	SavePoints *getGameSavePoints() { return _savepoints; }
	GameState  *getGameState() { return _state; }
	Flags      *getGameFlags() { return _flags; }

	// Time checks
	bool isDayTime();

	// Helpers
	static uint32 getPowerOfTwo(uint32 x);

private:
	static const uint32 _defaultBrigthness = 0x3;
	static const uint32 _defaultVolume = 0x7;
	static const uint32 _defaultTime = 1037700;
	static const uint32 _defaultTimeDelta = 3;
	static const uint32 _defaultPortrait = 32;

	LastExpressEngine *_engine;

	Flags *_flags;				///< Flags
	Inventory *_inventory;  	///< Inventory
	Objects *_objects;			///< Objects
	SavePoints *_savepoints;	///< SavePoints
	GameState *_state;			///< State
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_STATE_H
