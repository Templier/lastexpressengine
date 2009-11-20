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

#include "lastexpress/game/savepoint.h"

#include "common/system.h"

namespace LastExpress {

class LastExpressEngine;

class Sound {
public:
	Sound(LastExpressEngine *engine);
	~Sound();

	// Sound playing
	void playSound(SavePoints::EntityIndex entity, const char *filename, int a3, byte a4);

	void playMusic(SavePoints::EntityIndex entity, byte id, int a3, byte a4);	
	void playDialog(SavePoints::EntityIndex entity, SavePoints::EntityIndex entityDialog, int a3, byte a4);
	void playSoundEvent(int index, byte action, byte a3);	

	// Dialog
	const char *getDialogName(SavePoints::EntityIndex entity);

	// Letters
	const char *readText(int id);

	// Sound bites
	void excuseMe(SavePoints::EntityIndex entity, int param2, int param3);
	const char *excuseMeCath();
	const char *justCheckingCath();
	const char *wrongDoorCath();
	const char *justAMinuteCath();

	// Tests
	static bool testParameter(int param);

private:
	LastExpressEngine* _engine;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SOUND_H
