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

#ifndef LASTEXPRESS_SAVELOAD_H
#define LASTEXPRESS_SAVELOAD_H

/*
	Savegame format

	header:
		uint32 {4}      - signature: 0x12001200
		uint32 {4}      - ?? needs to be >= 0
		uint32 {4}      - ?? needs to be >= 0x20
		uint32 {4}      - ?? needs to be >= 0x20
		uint32 {4}      - ?? needs to be = 1
		uint32 {4}      - Brigthness (needs to be [0-6])
		uint32 {4}      - Volume (needs to be [0-7])
		uint32 {4}      - ?? needs to be = 9

	data:
		uint32 {4}      - ??
		uint32 {4}      - current time
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - Scene Index				max: 2600
		byte {1}        - ??
		uint32 {4}      - Scene Index (copy?)		max: 2600
		uint32 {4}      - Selected inventory item
		uint32 {4}      - ??
		uint32 {4*1000} - ??
		uint32 {4*16}   - ??
		uint32 {4*16}   - ??
		uint32 {4*128}  - Game progress
		byte {512}      - ??
		byte {7*32}     - Inventory
		byte {5*128}    - ??
		byte {1262*40}  - Game state (not sure what's in the struct yet)
		uint32 {4}      - ??
		uint32 {4}      - ??

		uint32 {4}      - Number of sound cache entries?
		(for each sound cache entry)  - total = byte {68}
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

		byte {16*128}   - ??
		uint32 {4}      - Number of save points
		(for each save point)
			byte {16}   - ?? (maybe save point header?)

		... more unknown stuff


	Game progress:
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - portraitType (top left portrait - 32 to 37)
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - cd number
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - ??

	InventoryData (32 entries)
		byte {1}		- Item ID (16 to 29) - set to 0 for "undefined" items
		byte {1}		- Scene ID set to 31 -> 39 for matchbox, telegram, passengerlist, scarf, parchemin, firebird, briefcase, paper, article
		byte {1}		- ?? set to 0
		byte {1}		- ?? set to 1 for matchbox, match, telegram, whistle, key, firebird, briefcase, corpse, passengerlist
		byte {1}		- Is item in inventory (set to 1 for telegram and article)
		byte {1}		- ?? set to 1 (including entry 0 and excepting last entry) and set to 0 for XXXX(several entries), firebird, briefcase, corpse
		byte {1}		- ?? set to 0
		


	Save point: max: 126 - rotates through list (ie. goes back and overwrites first save point when full)
		uint32 {4}      - ?? (0 - 40 ?) type ?
		uint32 {4}      - ??
		uint32 {4}      - time or similar?
		uint32 {4}      - 0 or 1 ?
*/

#include "common/savefile.h"

namespace LastExpress {

class SaveLoad {
public:
	// Savegame
	enum SavegameId {
		kSavegameBlue,
		kSavegameRed,
		kSavegameGreen,
		kSavegamePurple,
		kSavegameTeal,
		kSavegameGold
	};

	struct GameProgress {
		uint32 cdNumber;
		uint32 portraitType;

		GameProgress() {
			cdNumber = _defaultCdNumber;
			portraitType = _defaultPortrait;
		}
	};

	struct InventoryEntry {
		byte item_id;
		byte scene_id;
		byte field_2;
		byte field_3;
		byte has_item;
		byte field_5;
		byte field_6;

		InventoryEntry() {
			item_id = 0;
			scene_id = 0;
			field_2 = 0;
			field_3 = 0;
			has_item = 0;
			field_5 = 1;	// TODO all except last it seems (is it really important?)
			field_6 = 0;
		}
	};

	struct GameState {
		// Header
		uint32 brightness;
		uint32 volume;

		// Game data		
		uint32 time;
		uint32 currentScene;
		uint32 selectedItem;

		GameProgress progress;
		InventoryEntry inventory[32];

		GameState() {
			brightness = _defaultBrigthness;
			volume = _defaultVolume;

			// TODO init inventory with default values (here or in Logic code?)

			currentScene = 0;
			time = _defaultTime;
		}
	};



	// Init & Access
	static bool initSavegame(SavegameId id);
	static GameState *getGameState(SavegameId id);

	// Getting information
	static bool isSavegamePresent(SavegameId id);
	static bool isSavegameValid(SavegameId id);

private:
	static const uint32 _defaultBrigthness = 0x3;
	static const uint32 _defaultVolume = 0x7;
	static const uint32 _defaultTime = 1037700;
	static const uint32 _defaultPortrait = 32;
	static const uint32 _defaultCdNumber = 1;

	static Common::String getSavegameName(SavegameId id);

	// Opening save files
	static Common::InSaveFile *openForLoading(SavegameId id);
	static Common::OutSaveFile *openForSaving(SavegameId id);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SAVELOAD_H
