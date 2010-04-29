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

#include "lastexpress/game/savegame.h"

#include "lastexpress/debug.h"

#include "common/file.h"
#include "common/system.h"

namespace LastExpress {

// Savegame signature
const uint32 SAVEGAME_SIGNATURE = 0x12001200;

// Names of savegames
const static struct {
	const char *saveFile;
} gameInfo[6] = {
	{"blue.egg"},
	{"red.egg"},
	{"green.egg"},
	{"purple.egg"},
	{"teal.egg"},
	{"gold.egg"}
};

//////////////////////////////////////////////////////////////////////////
// Constructors
//////////////////////////////////////////////////////////////////////////

SaveLoad::SaveLoad(LastExpressEngine *engine) : _engine(engine) {}

SaveLoad::~SaveLoad() {}

//////////////////////////////////////////////////////////////////////////
// Save & Load
//////////////////////////////////////////////////////////////////////////

// Load game
bool SaveLoad::loadGame(GameId id) {

	if (!SaveLoad::isSavegamePresent(id))
		return false;

	//Common::InSaveFile *save = SaveLoad::openForLoading(id);
	// Validate header




	warning("SaveLoad::loadgame: not implemented!");
	return false;
}

// Save game
void SaveLoad::saveGame(int param1, EntityIndex entity, EventIndex event) {
	warning("SaveLoad::savegame: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Static Members
//////////////////////////////////////////////////////////////////////////

// Check if a specific savegame exists
bool SaveLoad::isSavegamePresent(GameId id) {
	if (!Common::File::exists(getSavegameName(id)))
		return false;

	return true;
}

// Check if the game has been started in the specific savegame
bool SaveLoad::isSavegameValid(GameId id) {
	uint32 britghness, volume;

	if (!isSavegamePresent(id)) {
		debugC(2, kLastExpressDebugSavegame, "SaveLoad::isSavegameValid - Savegame does not exist: %s", getSavegameName(id).c_str());
		return false;
	}

	// Read first 32 bytes of savegame
	Common::InSaveFile *save = openForLoading(id);
	if (!save) {
		debugC(2, kLastExpressDebugSavegame, "SaveLoad::isSavegameValid - Cannot open savegame for reading: %s", getSavegameName(id).c_str());
		return false;
	}

	// Check there is enough data
	if (save->size() < 32) {
		debugC(2, kLastExpressDebugSavegame, "SaveLoad::isSavegameValid - Savegame seems to be corrupted (not enough data: %i bytes): %s", save->size(), getSavegameName(id).c_str());
		return false;
	}

	bool isOk = false;

	if (save->readUint32LE() != SAVEGAME_SIGNATURE)
		goto EXIT;

	save->readUint32LE();

	if (save->readUint32LE() < 0x20)
		goto EXIT;

	if (save->readUint32LE() < 0x20)
		goto EXIT;

	if (save->readUint32LE() != 1)
		goto EXIT;

	britghness = save->readUint32LE();
	if  (britghness > 6)
		goto EXIT;

	volume = save->readUint32LE();
	if  (volume > 7)
		goto EXIT;

	if (save->readUint32LE() != 9)
		goto EXIT;

	isOk = true;

EXIT:
	delete save;
	return isOk;
}

bool SaveLoad::initSavegame(GameId id) {
	assert(!isSavegamePresent(id));

	Common::OutSaveFile *save = openForSaving(id);
	if (!save) {
		debugC(2, kLastExpressDebugSavegame, "SaveLoad::initSavegame - Cannot open savegame for writing: %s", getSavegameName(id).c_str());
		return false;
	}

	// Write default values to savegame
	save->writeUint32LE(SAVEGAME_SIGNATURE);
	save->writeUint32LE(0);
	save->writeUint32LE(32);
	save->writeUint32LE(32);
	save->writeUint32LE(0);
	save->writeUint32LE(3);
	save->writeUint32LE(7);
	save->writeUint32LE(9);

	delete save;

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////////////////////////

// Get the file name from the savegame ID
Common::String SaveLoad::getSavegameName(GameId id) {
	if (id >= 6)
		error("SaveLoad::getSavegameName - attempting to use an invalid game id. Valid values: 0 - 5, was %d", id);

	return gameInfo[id].saveFile;
}

Common::InSaveFile *SaveLoad::openForLoading(GameId id) {
	return g_system->getSavefileManager()->openForLoading(getSavegameName(id));
}

Common::OutSaveFile *SaveLoad::openForSaving(GameId id) {
	return g_system->getSavefileManager()->openForSaving(getSavegameName(id));
}

} // End of namespace LastExpress
