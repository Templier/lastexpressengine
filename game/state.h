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
		uint32 eventCorpseMovedFromFloor;
		uint32 field_C;
		uint32 eventCorpseFound;
		uint32 field_14;
		uint32 field_18;
		uint32 portrait;
		uint32 eventCorpseThrown;
		uint32 field_24;
		uint32 field_28;
		uint32 chapter;
		uint32 field_30;
		uint32 eventMetAugust;
		uint32 isNightTime;					///< 0 = day / 1 = night
		uint32 field_3C;
		uint32 field_40;
		uint32 field_44;
		uint32 field_48;
		uint32 field_4C;
		uint32 isTrainRunning;
		uint32 field_54;
		uint32 field_58;
		uint32 field_5C;
		uint32 field_60;
		uint32 field_64;
		uint32 field_68;
		uint32 eventMertensAugustWaiting;
		uint32 eventMertensChronosInvitation;
		uint32 isEggOpen;
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
		uint32 eventMetBoutarel;
		uint32 eventMetHadija;
		uint32 eventMetYasmin;
		uint32 field_DC;
		uint32 field_E0;
		uint32 field_E4;
		uint32 field_E8;
		uint32 field_EC;
		uint32 field_F0;
		uint32 field_F4;
		uint32 field_F8;
		uint32 field_FC;
		uint32 field_100;
		uint32 field_104;
		uint32 field_108;
		uint32 field_10C;
		uint32 field_110;
		uint32 field_114;
		uint32 field_118;
		uint32 field_11C;
		uint32 field_120;
		uint32 field_124;
		uint32 field_128;
		uint32 field_12C;
		uint32 field_130;
		uint32 field_134;
		uint32 field_138;
		uint32 field_13C;
		uint32 field_140;
		uint32 field_144;
		uint32 field_148;
		uint32 field_14C;
		uint32 field_150;
		uint32 field_154;
		uint32 field_158;
		uint32 field_15C;
		uint32 field_160;
		uint32 field_164;
		uint32 field_168;
		uint32 field_16C;
		uint32 field_170;
		uint32 field_174;
		uint32 field_178;
		uint32 field_17C;
		uint32 field_180;
		uint32 field_184;
		uint32 field_188;
		uint32 field_18C;
		uint32 field_190;
		uint32 field_194;
		uint32 field_198;
		uint32 field_19C;
		uint32 field_1A0;
		uint32 field_1A4;
		uint32 field_1A8;
		uint32 field_1AC;
		uint32 field_1B0;
		uint32 field_1B4;
		uint32 field_1B8;
		uint32 field_1BC;
		uint32 field_1C0;
		uint32 field_1C4;
		uint32 field_1C8;
		uint32 field_1CC;
		uint32 field_1D0;
		uint32 field_1D4;
		uint32 field_1D8;
		uint32 field_1DC;
		uint32 field_1E0;
		uint32 field_1E4;
		uint32 field_1E8;
		uint32 field_1EC;
		uint32 field_1F0;
		uint32 field_1F4;
		uint32 field_1F8;
		uint32 field_1FC;

		GameProgress() {
			field_0 = 0;
			jacket = kJacketOriginal;
			eventCorpseMovedFromFloor = 0;
			field_C = 0;
			eventCorpseFound = 0;
			field_14 = 0;
			field_18 = 0;
			portrait = _defaultPortrait;
			eventCorpseThrown = 0;
			field_24 = 0;
			field_28 = 0;
			chapter = kChapter1;
			field_30 = 0;
			eventMetAugust = 0;
			isNightTime = 0;
			field_3C = 0;
			field_40 = 0;
			field_44 = 0;
			field_48 = 0;
			field_4C = 0;
			isTrainRunning = 0;
			field_54 = 0;
			field_58 = 0;
			field_5C = 0;
			field_60 = 0;
			field_64 = 0;
			field_68 = 0;
			eventMertensAugustWaiting = 0;
			eventMertensChronosInvitation = 0;
			isEggOpen = 0;
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
			eventMetBoutarel = 0;
			eventMetHadija = 0;
			eventMetYasmin = 0;
			field_DC = 0;
			field_E0 = 0;
			field_E4 = 0;
			field_E8 = 0;
			field_EC = 0;
			field_F0 = 0;
			field_F4 = 0;
			field_F8 = 0;
			field_FC = 0;
			field_100 = 0;
			field_104 = 0;
			field_108 = 0;
			field_10C = 0;
			field_110 = 0;
			field_114 = 0;
			field_118 = 0;
			field_11C = 0;
			field_120 = 0;
			field_124 = 0;
			field_128 = 0;
			field_12C = 0;
			field_130 = 0;
			field_134 = 0;
			field_138 = 0;
			field_13C = 0;
			field_140 = 0;
			field_144 = 0;
			field_148 = 0;
			field_14C = 0;
			field_150 = 0;
			field_154 = 0;
			field_158 = 0;
			field_15C = 0;
			field_160 = 0;
			field_164 = 0;
			field_168 = 0;
			field_16C = 0;
			field_170 = 0;
			field_174 = 0;
			field_178 = 0;
			field_17C = 0;
			field_180 = 0;
			field_184 = 0;
			field_188 = 0;
			field_18C = 0;
			field_190 = 0;
			field_194 = 0;
			field_198 = 0;
			field_19C = 0;
			field_1A0 = 0;
			field_1A4 = 0;
			field_1A8 = 0;
			field_1AC = 0;
			field_1B0 = 0;
			field_1B4 = 0;
			field_1B8 = 0;
			field_1BC = 0;
			field_1C0 = 0;
			field_1C4 = 0;
			field_1C8 = 0;
			field_1CC = 0;
			field_1D0 = 0;
			field_1D4 = 0;
			field_1D8 = 0;
			field_1DC = 0;
			field_1E0 = 0;
			field_1E4 = 0;
			field_1E8 = 0;
			field_1EC = 0;
			field_1F0 = 0;
			field_1F4 = 0;
			field_1F8 = 0;
			field_1FC = 0;
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
		bool sceneUseBackup;       // byte
		SceneIndex scene;          // uint32
		SceneIndex sceneBackup;    // uint32
		SceneIndex sceneBackup2;   // uin32

		GameProgress progress;
		byte events[512];

		GameState() {
			brightness = _defaultBrigthness;
			volume = _defaultVolume;

			//Game data
			time = _defaultTime;
			timeDelta = _defaultTimeDelta;
			timeTicks = 0;
			sceneUseBackup = false;
			scene = kSceneDefault;
			sceneBackup = kSceneNone;
			sceneBackup2 = kSceneNone;

			// Clear game events
			memset(events, 0, 512*sizeof(byte));
		}
	};

	struct Flags {
		bool flag_0;
		bool flag_3;
		bool flag_4;
		bool flag_5;

		bool isGameRunning;

		// Mouse flags
		bool mouseLeftClick;
		bool mouseRightClick;

		bool flag_entities_0;
		bool flag_entities_1;

		bool shouldRedraw;
		bool shouldDrawEggOrHourGlass;

		Flags() {
			flag_0 = false;
			flag_3 = false;
			flag_4 = false;
			flag_5 = false;

			isGameRunning = false;

			mouseRightClick = false;
			mouseLeftClick = false;

			flag_entities_0 = false;
			flag_entities_1 = false;

			shouldRedraw = false;
			shouldDrawEggOrHourGlass = false;
		}
	};

	State(LastExpressEngine *engine);
	~State();

	// Accessors
	Inventory  *getGameInventory() { return _inventory; }
	Objects    *getGameObjects() { return _objects; }
	SavePoints *getGameSavePoints() { return _savepoints; }
	GameState  *getGameState() { return _state; }
	Flags      *getGameFlags() { return _flags; }

	// Time checks
	bool isDayTime() const;

	// Timer
	int getTimer() { return _timer; }
	void setTimer(int val) { _timer = val; }

	// Coordinates
	void setCoordinates(Common::Point coords) { _coords = coords; }
	const Common::Point getCoordinates() { return _coords; }

	// Helpers
	static uint32 getPowerOfTwo(uint32 x);

private:
	static const uint32 _defaultBrigthness = 0x3;
	static const uint32 _defaultVolume = 0x7;
	static const uint32 _defaultTime = 1037700;
	static const uint32 _defaultTimeDelta = 3;
	static const uint32 _defaultPortrait = 32;

	LastExpressEngine *_engine;

	// Timer
	int _timer;

	Flags *_flags;				///< Flags
	Inventory *_inventory;  	///< Inventory
	Objects *_objects;			///< Objects
	SavePoints *_savepoints;	///< SavePoints
	GameState *_state;			///< State
	Common::Point _coords;		///< Current coordinates
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_STATE_H
