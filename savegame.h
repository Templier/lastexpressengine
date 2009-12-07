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
		Game state (see logic.h)
*/

#include "lastexpress/shared.h"

#include "common/savefile.h"

namespace LastExpress {

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
