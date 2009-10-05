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

#include "lastexpress/logic.h"
#include "lastexpress/background.h"
#include "lastexpress/animation.h"

namespace LastExpress {

Logic::Logic(LastExpressEngine *engine) : _engine(engine) {

	_hasStartedGame = false;
	_hasShownIntro = false;
	_hasShownStartScreen = false;
}

Logic::~Logic() {
}

// .text:00448590
void Logic::showMainMenu() {

	// FIXME Check savegames to see if a game has been started
	if (!_hasStartedGame) {
		if (!_hasShownIntro) {
			Animation animation(_engine->_resource);

			// Show Broderbrund logo
			if (animation.load("1930.nis"))
				animation.show();

			// Play intro music
			_engine->_music->load("MUS001.SND");

			// Show The Smoking Car logo
			if (animation.load("1931.nis"))
				animation.show();

			_hasShownIntro = true;
		}
	} else {
		if (!_hasShownStartScreen) {
			_engine->_music->load("mus018.snd");

			// FIXME load data from scene! (DAT files?)
			// Show Start screen
			Background background(_engine->_resource);
			if (background.load("autoplay.bg"))
				background.show();

			_hasShownStartScreen = true;
		}
	}

	// Do something with Timer sound
	// Adjust mouse pointer
}

} // End of namespace LastExpress
