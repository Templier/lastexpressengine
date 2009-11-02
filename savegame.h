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
	---------------

	header: 32 bytes
		uint32 {4}      - signature: 0x12001200
		uint32 {4}      - ?? needs to be [0; 5]
		uint32 {4}      - ?? needs to be >= 32 [1061100; timeMax]
		uint32 {4}      - ?? needs to be >= 32
		uint32 {4}      - ?? needs to be = 1
		uint32 {4}      - Brigthness (needs to be [0-6])
		uint32 {4}      - Volume (needs to be [0-7])
		uint32 {4}      - ?? needs to be = 9

	data:
		uint32 {4}      - ??
		uint32 {4}      - current time 
		uint32 {4}      - time delta (ie how much a tick is in "real" time)
		uint32 {4}      - time ticks
		uint32 {4}      - Scene Index               max: 2600
		byte {1}        - ??
		uint32 {4}      - Scene Index (copy?)       max: 2600
		uint32 {4}      - Scene Index (copy?)       max: 2600
		uint32 {4}      - Selected inventory item
		uint32 {4*1000} - ??
		uint32 {4*16}   - ??
		uint32 {4*16}   - ??
		uint32 {4*128}  - Game progress
		byte {512}      - Game events
		byte {7*32}     - Inventory
		byte {5*128}    - ??
		byte {1262*40}  - Game state (not sure what's in the struct yet)
		
		uint32 {4}      - ??
		uint32 {4}      - ??
		uint32 {4}      - Number of sound cache entries
		byte {count*68} - Sound cache entries

		byte {16*128}   - ?? array
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

#include "common/savefile.h"

namespace LastExpress {

enum GameId {
	kGameBlue,
	kGameRed,
	kGameGreen,
	kGamePurple,
	kGameTeal,
	kGameGold
};

class SaveLoad {
public:

	// Init & Access
	static bool initSavegame(GameId id);
	
	// Getting information
	static bool isSavegamePresent(GameId id);
	static bool isSavegameValid(GameId id);

private:
	static Common::String getSavegameName(GameId id);

	// Opening save files
	static Common::InSaveFile *openForLoading(GameId id);
	static Common::OutSaveFile *openForSaving(GameId id);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SAVELOAD_H
