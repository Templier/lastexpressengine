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

// Savegame signatures
#define SAVEGAME_SIGNATURE 0x12001200
#define SAVEGAME_HEADER    0xE660E660

// Names of savegames
static const struct {
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

SaveLoad::SaveLoad(LastExpressEngine *engine) : _engine(engine) {
	_gameTicksLastSavegame = 0;
}

SaveLoad::~SaveLoad() {
	//Zero passed pointers
	_engine = NULL;
}

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
void SaveLoad::saveGame(SavegameType type, EntityIndex entity, EventIndex event) {
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
	if (!isSavegamePresent(id)) {
		debugC(2, kLastExpressDebugSavegame, "SaveLoad::isSavegameValid - Savegame does not exist: %s", getSavegameName(id).c_str());
		return false;
	}

	SavegameMainHeader header;
	if (!loadMainHeader(id, &header))
		return false;

	return validateMainHeader(header);
}


//////////////////////////////////////////////////////////////////////////
// Headers
//////////////////////////////////////////////////////////////////////////
bool SaveLoad::loadMainHeader(GameId id, SavegameMainHeader* header) {
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

	header->signature = save->readUint32LE();
	header->chapter = (ChapterIndex)save->readUint32LE();
	header->time = save->readUint32LE();
	header->field_C = save->readUint32LE();
	header->field_10 = save->readUint32LE();
	header->brightness = save->readSint32LE();
	header->volume = save->readSint32LE();
	header->field_1C = save->readUint32LE();

	return true;
}

void SaveLoad::loadEntryHeader(Common::InSaveFile *save, SavegameEntryHeader* header) {
	header->signature = save->readUint32LE();
	header->type = (HeaderType)save->readUint32LE();
	header->time = save->readUint32LE();
	header->field_C = save->readUint32LE();
	header->chapter = (ChapterIndex)save->readUint32LE();
	header->event = (EventIndex)save->readUint32LE();
	header->field_18 = save->readUint32LE();
	header->field_1C = save->readUint32LE();
}

bool SaveLoad::validateMainHeader(SavegameMainHeader &header) {
	if (header.signature != SAVEGAME_SIGNATURE)
		return false;

	if (header.chapter < 0)
		return false;

	if (header.time < 32)
		return false;

	if (header.field_C < 32)
		return false;

	if (header.field_10 != 1 && header.field_10)
		return false;

	if (header.brightness < 0 || header.brightness > 6)
		return false;

	if (header.volume < 0 || header.volume > 7)
		return false;

	if (header.field_1C != 9)
		return false;

	return true;
}

bool SaveLoad::validateEntryHeader(SavegameEntryHeader &header) {
	if (header.signature != SAVEGAME_HEADER)
		return false;

	if (header.type < kHeaderType1 || header.type > kHeaderType5)
		return false;

	if (header.time < kTimeStartGame || header.time > kTimeCityConstantinople)
		return false;

	if (header.field_C <= 0 || header.field_C >= 15)
		return false;

	if (header.chapter <= 0)
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Init
//////////////////////////////////////////////////////////////////////////
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
