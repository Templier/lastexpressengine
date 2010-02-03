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

#include "lastexpress/shared.h"

#include "common/system.h"

namespace LastExpress {

class LastExpressEngine;
class StreamedSound;

class Sound {
public:
	Sound(LastExpressEngine *engine);
	~Sound();

	// State (FIXME: to be renamed when we know more about it)
	void resetState() { _state |= 1; }
	void reset(EntityIndex entity);

	// Sound queue
	bool isFileInQueue(const char* filename);
	bool isBuffered(EntityIndex entityIndex);

	// Misc
	void unknownFunction1();

	// Sound playing
	void playSound(EntityIndex entity, const char *filename, int a3 = -1, byte a4 = 0);

	void playMusic(EntityIndex entity, byte id, int a3, byte a4);
	void playDialog(EntityIndex entity, EntityIndex entityDialog, int a3, byte a4);
	void playSoundEvent(int index, byte action, byte a3);

	// Dialog
	const char *getDialogName(EntityIndex entity);

	// Letters
	const char *readText(int id);

	// Sound bites
	void excuseMe(EntityIndex entity, int param2, int param3);
	const char *excuseMeCath();
	const char *justCheckingCath();
	const char *wrongDoorCath();
	const char *justAMinuteCath();

	// Tests
	static bool testParameter(int param);

	// Sound streams TODO make private
	StreamedSound *getMusicStream() const { return _music; }
	StreamedSound *getSfxStream() const { return _sfx; }

private:
	LastExpressEngine* _engine;

	enum SoundState {
		kSoundState0 = 0,
		kSoundState1 = 1,
		kSoundState2 = 2
	};

	struct SoundEntry_t {

	};

	// State
	int _state;

	// Sound streams
	StreamedSound *_music;
	StreamedSound *_sfx;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SOUND_H
