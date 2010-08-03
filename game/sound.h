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

#ifndef LASTEXPRESS_SOUND_H
#define LASTEXPRESS_SOUND_H

/*

	Sound entry: 68 bytes (this is what appears in the savegames)
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - entity
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    char {16}       - name 1
	    char {16}       - name 2

	Sound queue entry: 120 bytes
	    uint16 {2}      - status
	    byte {1}        - ??
	    byte {1}        - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - file data pointer
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - archive structure pointer
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    uint32 {4}      - entity
	    uint32 {4}      - ??
	    uint32 {4}      - ??
	    char {16}       - name 1
	    char {16}       - name 2
	    uint32 {4}      - pointer to next entry in the queue
	    uint32 {4}      - subtitle data pointer

*/

#include "lastexpress/shared.h"

#include "common/list.h"
#include "common/system.h"
#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;
class StreamedSound;

class SoundManager : Common::Serializable {
public:
	enum SoundType {
		kSoundTypeNone = 0,
		kSoundType1,
		kSoundType2,
		kSoundType3,
		kSoundType4,
		kSoundType5,
		kSoundType6,
		kSoundType7,
		kSoundType8,
		kSoundType9,
		kSoundType10,
		kSoundType11,
		kSoundType12,
		kSoundType13,
		kSoundType14,
		kSoundType15,
		kSoundType16
	};

	enum FlagType {
		kFlagInvalid     = -1,
		kFlagNone        = 0x0,
		kFlag2           = 0x2,
		kFlag3           = 0x3,
		kFlag4           = 0x4,
		kFlag5           = 0x5,
		kFlag6           = 0x6,
		kFlag7           = 0x7,
		kFlag8           = 0x8,
		kFlag9           = 0x9,
		kFlag10          = 0xA,
		kFlag11          = 0xB,
		kFlag12          = 0xC,
		kFlag13          = 0xD,
		kFlag14          = 0xE,
		kFlag15          = 0xF,
		kFlagDefault     = 0x10,

		kFlagType1_2     = 0x1000000,
		kFlagSteam       = 0x1001007,
		kFlagType13      = 0x3000000,
		kFlagMenuClock   = 0x3080010,
		kFlagType7       = 0x4000000,
		kFlagType11      = 0x5000000,
		kFlagMusic       = 0x5000010,
		kFlagType3       = 0x6000000,
		kFlagLoop        = 0x6001008,
		kFlagType9       = 0x7000000,
	};

	SoundManager(LastExpressEngine *engine);
	~SoundManager();

	// Timer
	void handleTimer();

	// State
	void resetState() { _state |= kSoundType1; }

	// Sound queue
	void updateQueue();
	void resetQueue(SoundType type1, SoundType type2 = kSoundTypeNone);
	void clearQueue();

	// Subtitles
	void updateSubtitles();

	// Entry
	bool isBuffered(const char* filename, bool testForEntity = false);
	bool isBuffered(EntityIndex entity);
	void processEntry(EntityIndex entity);
	void processEntry(SoundType type);
	void processEntry(const char* filename);
	void processEntries();
	void removeFromQueue(const char* filename);
	void removeFromQueue(EntityIndex entity);

	// Misc
	void unknownFunction4();

	// Sound playing
	void playSound(EntityIndex entity, const char *filename, FlagType flag = kFlagInvalid, byte a4 = 0);
	SoundType playSoundWithSubtitles(const char *filename, FlagType flag, EntityIndex entity, byte a4 = 0);
	void playSoundEvent(EntityIndex entity, byte action, byte a3 = 0);
	void playDialog(EntityIndex entity, EntityIndex entityDialog, FlagType flag, byte a4);
	void playSteam(CityIndex index);
	void playFightSound(byte action, byte a4);
	void playLocomotiveSound();

	// Dialog & Letters
	void readText(int id);
	const char *getDialogName(EntityIndex entity) const;

	// Sound bites
	void excuseMe(EntityIndex entity, EntityIndex entity2 = kEntityPlayer, FlagType flag = kFlagNone);
	void excuseMeCath();
	const char *justCheckingCath() const;
	const char *wrongDoorCath() const;
	const char *justAMinuteCath() const;

	// FLags
	SoundManager::FlagType getSoundFlag(EntityIndex index) const;

	// Debug
	void stopAllSound();

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

private:
	LastExpressEngine* _engine;

	enum SoundStatus {
		kSoundStatus_20       = 0x20,
		kSoundStatusRemoved   = 0x200,

		kSoundStatus_8000     = 0x8000,
		kSoundStatus_100000   = 0x100000,
		kSoundStatus_40000000 = 0x40000000,

		kSoundStatusClear0    = 0x10,
		kSoundStatusClear1    = 0x1F,
		kSoundStatusClear2    = 0x80,
		kSoundStatusClear3    = 0x800,
		kSoundStatusClearAll  = 0xFFFFFFE0
	};

	enum SoundState {
		kSoundState0 = 0,
		kSoundState1 = 1,
		kSoundState2 = 2
	};

	struct SoundEntry {
		uint16 status;
		// byte field_2;
		byte field_3;
		SoundType type;    // int
		//int field_8;
		//int field_C;
		//int field_10;
		//int fileData;
		//int field_18;
		//int field_1C;
		//int field_20;
		//int field_24;
		//int field_28;
		Common::SeekableReadStream *stream;	// int
		//int field_30;
		//int field_34;
		//int field_38;
		int field_3C;
		int field_40;
		EntityIndex entity;
		int field_48;
		int field_4C;
		Common::String name1; //char[16];
		Common::String name2; //char[16];
		//int next; // offset to the next structure in the list (not used)
		//Subtitle subtitle;

		bool isStreamed; // TEMPORARY

		SoundEntry() {
			status = 0;
			field_3 = 0;
			type = kSoundTypeNone;
			stream = NULL;
			field_3C = 0;
			field_40 = 0;
			entity = kEntityNone;
			field_48 = 0;
			field_4C = 0;

			isStreamed = false;
		};
	};

	// State flag
	int _state;
	SoundType _currentType;

	// Sound stream
	StreamedSound *_soundStream;

	// Unknown data
	uint32 _data0;
	uint32 _data1;
	uint32 _data2;
	uint32 _flag;

	// Sound cache
	Common::List<SoundEntry *> _cache;

	SoundEntry *getEntry(EntityIndex index);
	SoundEntry *getEntry(Common::String name);
	SoundEntry *getEntry(SoundType type);

	void setupEntry(SoundEntry *entry, Common::String name, FlagType flag, int a4);
	void setEntryType(SoundEntry *entry, FlagType flag);
	void setEntryStatus(SoundEntry *entry, FlagType flag);
	bool setupCache(SoundEntry *entry);
	void loadSoundData(SoundEntry *entry, Common::String name);

	void updateEntry(SoundEntry *entry, uint value);
	void updateEntryState(SoundEntry *entry);
	void resetEntry(SoundEntry *entry);
	void removeEntry(SoundEntry *entry);


	// Subtitles
	void showSubtitles(SoundEntry *entry, Common::String filename);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SOUND_H
