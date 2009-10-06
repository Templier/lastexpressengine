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
#include "lastexpress/sequence.h"
#include "lastexpress/scene.h"

#include "graphics/cursorman.h"

namespace LastExpress {

Logic::Logic(LastExpressEngine *engine) : _engine(engine) {
	_runState = new RunState;
}

Logic::~Logic() {
	SAFE_DELETE(_runState);
}

// .text:00448590
void Logic::showMainMenu() {

	//Scene scene(_engine->_resource);
	//scene.load(1);

	// If no blue savegame exists, this might be the first time we start the game, so we show the full intro
	if (!SaveLoad::isSavegameValid(SaveLoad::SavegameBlue)) {
		if (!_runState->hasShownIntro) {
			Animation animation(_engine->_resource);

			// Show Broderbrund logo
			if (animation.load("1930.nis"))
				animation.show();

			// Play intro music
			_engine->_music->load("MUS001.SND");

			// Show The Smoking Car logo
			if (animation.load("1931.nis"))
				animation.show();

			_runState->hasShownIntro = true;
		}
	} else {
		if (!_runState->hasShownStartScreen) {
			_engine->_music->load("mus018.snd");

			// FIXME load data from scene: sceneIndex = 65
			
			// Show Start screen
			Background background(_engine->_resource);
			if (background.load("autoplay.bg"))
				background.show();

			_runState->hasShownStartScreen = true;
		}
	}

	// Set Cursor type
	_engine->_cursor->setStyle(Cursor::CursorNormal);
	_engine->_cursor->show(true);

	// TODO: Load sequences for buttons & help text
	//buttns.seq
	//helpnewr.seq

	

	// TODO Load Main menu scene (sceneIndex = 5 * savegame id (+ 1/2)) - see text:00449d80
}

// text:00448b30
bool Logic::HandleStartMenuEvent(StartMenuEvent event, byte clickStatus) {
	return false;
}


//////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////

// Get the sequence to use for the acorn highlight, depending of the currently loaded savegame
Sequence* Logic::getAcornHighlight(SaveLoad::SavegameId id) {
	
	// end of text:00449d80 (also sets up the main menu scene)

	// TODO replace with string array and access by index?
	Common::String name = "";
	switch (id) {
	case SaveLoad::SavegameBlue:
		name = "aconblue3.seq";
		break;

	case SaveLoad::SavegameRed:
		name = "aconred.seq";
		break;

	case SaveLoad::SavegameGreen:
		name = "acongren.seq";
		break;

	case SaveLoad::SavegamePurple:
		name = "aconpurp.seq";
		break;

	case SaveLoad::SavegameTeal:
		name = "aconteal.seq";
		break;

	case SaveLoad::SavegameGold:
		name = "acongold.seq";
		break;
	}

	Sequence *highlight = new Sequence(_engine->_resource);

	if (!highlight->load(name)) {
		delete highlight;
		return NULL;
	}

	return highlight;
}


} // End of namespace LastExpress
