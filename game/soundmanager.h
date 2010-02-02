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

#ifndef LASTEXPRESS_SOUNDMANAGER_H
#define LASTEXPRESS_SOUNDMANAGER_H

#include "lastexpress/shared.h"

/*
	Sound entry format
	------------------

	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - entity ID
	uint32 {4}      - ??
	uint32 {4}      - ??
	char {16}       - name1
	char {16}       - name2

	Sound cache format
	------------------

	byte {1}        - isOnDisk
	byte {1}        - ??
	byte {1}        - ??
	byte {1}        - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - fileData
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - archive
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - entity ID
	uint32 {4}      - ??
	uint32 {4}      - ??
	char {16}       - name1
	char {16}       - name2
	uint32 {4}      - next struct pointer
	uint32 {4}      - subtitle

*/
namespace LastExpress {

class LastExpressEngine;
class StreamedSound;

class SoundManager {
public:
	SoundManager(LastExpressEngine *engine);
	~SoundManager();

	// State (FIXME: to be renamed when we know more about it)
	void resetState() { _state |= 1; }
	void reset(EntityIndex entity);

	// Sound queue
	bool isFileInQueue(const char* filename);

	// Misc
	void unknownFunction1();

	// Sound streams
	// TODO: encapsulate
	StreamedSound *getMusicStream() const { return _music; }
	StreamedSound *getSfxStream() const { return _sfx; }

private:
	enum SoundState {
		kSoundState0 = 0,
		kSoundState1 = 1,
		kSoundState2 = 2
	};

	struct SoundEntry_t {

	};

	LastExpressEngine* _engine;

	// State
	int _state;

	// Sound streams
	StreamedSound *_music;
	StreamedSound *_sfx;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SOUNDMANAGER_H
