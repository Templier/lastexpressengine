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
	    uint32 {4}      - Brightness (needs to be [0-6])
	    uint32 {4}      - Volume (needs to be [0-7])
	    uint32 {4}      - ?? needs to be = 9

	Game data Format
	-----------------

	uint32 {4}      - entity
	uint32 {4}      - current time
	uint32 {4}      - time delta (how much a tick is in "real" time)
	uint32 {4}      - time ticks
	uint32 {4}      - scene Index               max: 2500
	byte {1}        - use backup scene
	uint32 {4}      - backup Scene Index 1      max: 2500
	uint32 {4}      - backup Scene Index 2      max: 2500
	uint32 {4}      - selected inventory item   max: 32
	uint32 {4*1000} - ??
	uint32 {4*16}   - ??
	uint32 {4*16}   - ??
	uint32 {4*128}  - game progress
	byte {512}      - game events
	byte {7*32}     - inventory
	byte {5*128}    - objects
	byte {1262*40}  - entities (characters and train entities)

	uint32 {4}      - sound queue state
	uint32 {4}      - ??
	uint32 {4}      - number of sound entries
	byte {count*68} - sound entries

	byte {16*128}   - save point data
	uint32 {4}      - number of save points (max: 128)
	byte {count*16} - save points

	... more unknown stuff

*/

#include "lastexpress/shared.h"

#include "common/savefile.h"

namespace LastExpress {

class LastExpressEngine;

class SaveLoad {
public:

	SaveLoad(LastExpressEngine *engine);
	~SaveLoad();

	// Save & Load
	bool loadGame(GameId id);
	void saveGame(int param1, EntityIndex entity, EventIndex event);

	// Init
	static bool initSavegame(GameId id);

	// Getting information
	static bool isSavegamePresent(GameId id);
	static bool isSavegameValid(GameId id);

	// Opening save files
	static Common::InSaveFile *openForLoading(GameId id);
	static Common::OutSaveFile *openForSaving(GameId id);

private:
	LastExpressEngine *_engine;

	static Common::String getSavegameName(GameId id);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SAVELOAD_H