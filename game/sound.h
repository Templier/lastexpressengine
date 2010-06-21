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
	    byte {1}        - is on disk
	    byte {1}        - ??
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

#include "common/array.h"
#include "common/system.h"
#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;
class StreamedSound;

class SoundManager : Common::Serializable {
public:
	SoundManager(LastExpressEngine *engine);
	~SoundManager();

	// Timer
	void handleTimer();

	// State (FIXME: to be renamed when we know more about it)
	void resetState() { _state |= 1; }
	void setupQueue(int a1, int a2 = 0);

	// Sound queue
	bool isBuffered(const char* filename, bool testForEntity = false);

	void removeFromQueue(const char* filename);
	void removeFromQueue(EntityIndex entity);

	bool isBuffered(EntityIndex entity);
	void processEntry(EntityIndex entity);

	// Misc
	void unknownFunction1();
	void unknownFunction2(const char* filename);
	void unknownFunction3();
	void unknownGameOver(bool isProcessing = true);

	// Sound playing
	void playSound(EntityIndex entity, const char *filename, int a3 = -1, byte a4 = 0);
	bool playSoundWithSubtitles(const char *filename, int param3, EntityIndex entity, byte a4 = 0);

	void playMusic(EntityIndex entity, byte id, int a3, byte a4);
	void playDialog(EntityIndex entity, EntityIndex entityDialog, int a3, byte a4);
	void playSoundEvent(EntityIndex entity, byte action, byte a3 = 0);

	void playFightSound(byte action, byte a4);

	// Dialog
	const char *getDialogName(EntityIndex entity) const;

	// Letters
	void readText(int id);

	// Sound bites
	void excuseMe(EntityIndex entity, int param2 = 0, int param3 = 0);
	const char *excuseMeCath() const;
	const char *justCheckingCath() const;
	const char *wrongDoorCath() const;
	const char *justAMinuteCath() const;

	// Tests
	static bool testParameter(int param);

	// Sound streams
	// TODO make private
	StreamedSound *getMusicStream() const { return _music; }
	StreamedSound *getSfxStream() const { return _sfx; }

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

private:
	LastExpressEngine* _engine;

	enum SoundState {
		kSoundState0 = 0,
		kSoundState1 = 1,
		kSoundState2 = 2
	};

	struct SoundEntry {
		//bool isOnDisk;
		//byte field_1;
		//byte field_2;
		//byte field_3;
		//int field_4;
		//int field_8;
		//int field_C;
		//int field_10;
		//int fileData;
		//int field_18;
		//int field_1C;
		//int field_20;
		//int field_24;
		//int field_28;
		//int archive;
		//int field_30;
		//int field_34;
		//int field_38;
		//int field_3C;
		//int field_40;
		EntityIndex entity;
		//int field_48;
		//int field_4C;
		char name1[16];
		char name2[16];
		//int next; // offset to the next structure in the list (not used)
		//Subtitle subtitle;

		SoundEntry() {
			entity = kEntityNone;
			strcpy((char*)&name1, "");
			strcpy((char*)&name2, "");
		};
	};

	// State
	int _state;

	// Sound streams
	StreamedSound *_music;
	StreamedSound *_sfx;

	// Unknown data
	uint32 _data0;
	uint32 _data1;
	uint32 _data2;

	// Sound cache
	Common::Array<SoundEntry *> _cache;

	SoundEntry *getEntry(EntityIndex index);
	SoundEntry *getEntry(Common::String name);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SOUND_H
