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

#include "lastexpress/saveload.h"

#include "lastexpress/debug.h"

#include "common/file.h"
#include "common/system.h"

namespace LastExpress {

// Savegame signature
const uint32 savegameSignature = 0x12001200;

// Names of savegames
const Common::String eggBlue("BLUE.EGG");
const Common::String eggRed("RED.EGG");
const Common::String eggGreen("GREEN.EGG");
const Common::String eggPurple("PURPLE.EGG");
const Common::String eggTeal("TEAL.EGG");
const Common::String eggGold("GOLD.EGG");

// Check if a specific savegame exists
bool SaveLoad::isSavegamePresent(SavegameId id) {
	if (!Common::File::exists(getSavegameName(id)))
		return false;

	return true;
}

// Check if the game has been started in the specific savegame
bool SaveLoad::isSavegameValid(SavegameId id) {
	uint32 luminosity, volume;

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
		debugC(2, kLastExpressDebugSavegame, "SaveLoad::isSavegameValid - Savegame seems to be corrupted (not enough data): %s", getSavegameName(id).c_str());
		return false;
	}

	bool isOk = false;

	if (save->readUint32LE() != savegameSignature)
		goto EXIT;

	if (save->readUint32LE() < 0)
		goto EXIT;

	if (save->readUint32LE() < 0x20)
		goto EXIT;

	if (save->readUint32LE() < 0x20)
		goto EXIT;

	if (save->readUint32LE() != 1)
		goto EXIT;

	luminosity = save->readUint32LE();
	if  (luminosity < 0 || luminosity > 6)
		goto EXIT;

	volume = save->readUint32LE();
	if  (volume < 0 || volume > 7)
		goto EXIT;

	if (save->readUint32LE() != 9)
		goto EXIT;

	isOk = true;

EXIT:
	delete save;
	return isOk;
}

bool SaveLoad::initSavegame(SavegameId id) {
	assert(!isSavegamePresent(id));

	Common::OutSaveFile *save = openForSaving(id);
	if (!save) {
		debugC(2, kLastExpressDebugSavegame, "SaveLoad::initSavegame - Cannot open savegame for writing: %s", getSavegameName(id).c_str());
		return false;
	}

	// Write default values to savegame
	save->writeUint32LE(savegameSignature);
	save->writeUint32LE(0);
	save->writeUint32LE(0x20);
	save->writeUint32LE(0x20);
	save->writeUint32LE(0x0);
	save->writeUint32LE(_defaultLuminosity);
	save->writeUint32LE(_defaultVolume);
	save->writeUint32LE(0x9);

	delete save;

	return true;
}

// Read savegame information
SaveLoad::GameState* SaveLoad::getGameState(SavegameId id) {
	// TODO: read info from savegame
	return new GameState;
}

//////////////////////////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////////////////////////

// Get the file name from the savegame ID
Common::String SaveLoad::getSavegameName(SavegameId id) {
	assert(id >=0 && id < 6);

	switch (id) {
	case kSavegameBlue:
		return eggBlue;

	case kSavegameRed:
		return eggRed;

	case kSavegameGreen:
		return eggGreen;

	case kSavegamePurple:
		return eggPurple;

	case kSavegameTeal:
		return eggTeal;

	case kSavegameGold:
		return eggGold;

	default:
		return "";
	}

	// should never happen!
	return "";
}

Common::InSaveFile *SaveLoad::openForLoading(SavegameId id) {
	Common::String savename = getSavegameName(id);
	return g_system->getSavefileManager()->openForLoading(savename);
}

Common::OutSaveFile *SaveLoad::openForSaving(SavegameId id) {
	Common::String savename = getSavegameName(id);
	return g_system->getSavefileManager()->openForSaving(savename);
}

} // End of namespace LastExpress
