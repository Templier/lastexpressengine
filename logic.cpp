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

#include "lastexpress/inventory.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/menu.h"
#include "lastexpress/scene.h"

namespace LastExpress {

Logic::Logic(LastExpressEngine *engine) : _engine(engine) {
	_menu = new Menu(engine);
	_inventory = new Inventory(engine);

	// Get those from savegame
	_gameState = new SaveLoad::GameState();

	// Init inventory
	_inventory->init();

	// HACK set specific cursor style for inventory testing
	_engine->getCursor()->show(true);
	_runState.cursorStyle = Cursor::kCursorTurnLeft;
	_engine->getCursor()->setStyle(_runState.cursorStyle);
}

Logic::~Logic() {
	delete _gameState;
	delete _menu;
	delete _inventory;
}

//////////////////////////////////////////////////////////////////////////
// Menu handling
//////////////////////////////////////////////////////////////////////////

// Show main menu
void Logic::showMenu(bool visible) {

	if (!visible) {
		_inventory->show(true);
		_runState.showingMenu = false;
		return;
	}

	// Hide inventory
	_inventory->show(false);

	// TODO: load scene and set current scene
	_runState.showingMenu = true;
	_gameState->currentScene = _menu->getSceneIndex();
	_menu->showMenu();

	// TODO reset showingMenu to false when starting/returning to a game and show inventory	

	// TODO: move to shared method
	// Init the first savegame if needed
	if (!SaveLoad::isSavegamePresent(kGameBlue))
		SaveLoad::initSavegame(kGameBlue);
}

bool Logic::handleMouseEvent(Common::Event ev) {
	if (_gameState->currentScene == 0) {
		// FIXME: allow inventory to show
		_gameState->currentScene = 1;	
		_inventory->show(true);

		return true;
	}
		

	// Special case for the main menu scene
	if (isShowingMenu()) {
		return _menu->handleStartMenuEvent(ev);
	}

	// FIXME: check hitbox & event from scene data
	_inventory->handleMouseEvent(ev);

	return true;
}

// Switch to the next savegame
void Logic::switchGame() {
	// Switch back to blue game is the current game is not started
	if (!_runState.gameStarted) {
		_runState.gameId = kGameBlue;
	} else {
		_runState.gameId = (GameId)((_runState.gameId + 1) % 6);
	}

	// Init savegame if needed
	if (!SaveLoad::isSavegamePresent(_runState.gameId))
		SaveLoad::initSavegame(_runState.gameId);

	// Reset run state
	_runState.gameStarted = false;

	// TODO load data from savegame, adjust volume & luminosity, etc...
	//////////////////////////////////////////////////////////////////////////
	// HACK for debug
	if (_runState.gameId == kGameBlue) {
		_gameState->time = 2383200;
		_runState.gameStarted = true;
	}
	//////////////////////////////////////////////////////////////////////////

	// Redraw all menu elements
	showMenu(true);
}


//////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////

void Logic::action_pickGreenJacket() {
	// _gameState->progress.field_4 = 2; ???
	_inventory->addItem(Inventory::kMatchBox);
	// Set field_6 to 0 (in addItem?)

	// 2 unknown functions calls

	_inventory->setPortrait(Inventory::kPortraitGreen);	

}

} // End of namespace LastExpress
