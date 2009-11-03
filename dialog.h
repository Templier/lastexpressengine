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

#ifndef LASTEXPRESS_DIALOG_H
#define LASTEXPRESS_DIALOG_H

#include "common/system.h"

namespace LastExpress {

class LastExpressEngine;

class Dialog {
public:

	Dialog(LastExpressEngine *engine);

	// Soundbites
	Common::String sound_excuseMe();
	Common::String sound_justChecking();
	Common::String sound_wrongDoor();
	Common::String sound_justAMinute();

private:
	LastExpressEngine* _engine;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_DIALOG_H
