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

#include "lastexpress/menu.h"
#include "lastexpress/scene.h"

namespace LastExpress {

Logic::Logic(LastExpressEngine *engine) : _engine(engine) {
	_menu = new Menu(engine);

	// Get those from savegame
	_gameState = new SaveLoad::GameState();
	_gameState->currentTime = 2383200;
	_runState.gameStarted = true;
}

Logic::~Logic() {
	if (_gameState)
		delete _gameState;

	if (_menu)
		delete _menu;
}

//////////////////////////////////////////////////////////////////////////
// Menu handling
//////////////////////////////////////////////////////////////////////////

// Show main menu
void Logic::showMenu() {
	// TODO: load scene and set current scene
	_gameState->currentScene = _menu->getSceneIndex();
	_menu->showMenu();

	// TODO: move to shared method
	// Init the first savegame if needed
	if (!SaveLoad::isSavegamePresent(SaveLoad::kSavegameBlue))
		SaveLoad::initSavegame(SaveLoad::kSavegameBlue);
}

bool Logic::handleMouseEvent(Common::Event ev) {
	if (_gameState->currentScene == 0)
		return true;

	// FIXME: check hitbox & event from scene data


	// Special case for the main menu scene
	if (_gameState->currentScene == _menu->getSceneIndex()) {
		return _menu->handleStartMenuEvent(ev);
	}	

	return true;
}

// Switch to the next savegame
void Logic::switchGame() {
	// Switch back to blue game is the current game is not started
	if (!_runState.gameStarted) {
		_runState.savegameId = SaveLoad::kSavegameBlue;
		
	} else {
		_runState.savegameId = (SaveLoad::SavegameId)((_runState.savegameId + 1) % 6);
	}

	// Init savegame if needed
	if (!SaveLoad::isSavegamePresent(_runState.savegameId))
		SaveLoad::initSavegame(_runState.savegameId);

	// Reset run state
	_runState.gameStarted = false;

	// TODO load data from savegame, adjust volume & luminosity, etc...
	//////////////////////////////////////////////////////////////////////////
	// HACK for debug
	if (_runState.savegameId == SaveLoad::kSavegameBlue) {
		_gameState->currentTime = 2383200;
		_runState.gameStarted = true;
	}
	//////////////////////////////////////////////////////////////////////////

	// Redraw all menu elements
	showMenu();
}

} // End of namespace LastExpress
