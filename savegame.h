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
		uint32 {4}      - ??
		uint32 {4*1000} - ??
		uint32 {4*16}   - ??
		uint32 {4*16}   - ??
		uint32 {4*128}  - ??
		byte {512}      - ??
		byte {7*32}     - ??
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

	struct GameState {
		// Header
		uint32 brightness;
		uint32 volume;


		// TODO: NOT YET FOUND IN SAVEGAME
		uint32 currentScene;
		uint32 currentTime;

		GameState() {
			brightness = _defaultBrigthness;
			volume = _defaultVolume;

			currentScene = 0;
			currentTime = _defaultTime;
		}
	};

	// Init & Access
	static bool initSavegame(SavegameId id);
	static GameState* getGameState(SavegameId id);


	// Getting information
	static bool isSavegamePresent(SavegameId id);
	static bool isSavegameValid(SavegameId id);

private:
	static const uint32 _defaultBrigthness = 0x3;
	static const uint32 _defaultVolume = 0x7;
	static const uint32 _defaultTime = 1037700;


	static Common::String getSavegameName(SavegameId id);

	// Opening save files
	static Common::InSaveFile *openForLoading(SavegameId id);
	static Common::OutSaveFile *openForSaving(SavegameId id);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SAVELOAD_H
