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

#include "lastexpress/action.h"
#include "lastexpress/animation.h"
#include "lastexpress/inventory.h"
#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/menu.h"
#include "lastexpress/resource.h"
#include "lastexpress/scene.h"

namespace LastExpress {

Logic::Logic(LastExpressEngine *engine) : _engine(engine), _scene(NULL) {
	_action = new Action(engine);
	_menu = new Menu(engine);
	_inventory = new Inventory(engine);

	// Get those from savegame
	_gameState = new GameState();

	// Init inventory
	_inventory->init();

	// HACK add more items for testing
	_inventory->addItem(Inventory::kMatchBox);
	_inventory->addItem(Inventory::kPassengerList);
	_inventory->addItem(Inventory::kScarf);
	_inventory->addItem(Inventory::kWhistle);
	_inventory->addItem(Inventory::kArticle);
	_inventory->addItem(Inventory::kBomb);
	_inventory->addItem(Inventory::kKey);
}

Logic::~Logic() {
	delete _action;
	delete _gameState;
	delete _menu;
	delete _inventory;
	delete _scene;
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

void Logic::startGame() {
	showMenu(false);

	setScene(_defaultScene);
	
	// Set Cursor type
	_engine->getCursor()->setStyle(Cursor::kCursorNormal);
	_engine->getCursor()->show(true);

	_inventory->show(true);

	askForRedraw();
}

bool Logic::handleMouseEvent(Common::Event ev) {

	// Special case for the main menu scene
	if (isShowingMenu()) {
		return _menu->handleStartMenuEvent(ev);
	}

	if (_inventory->handleMouseEvent(ev))
		return true;

	// Check hitbox & event from scene data
	// TODO cache current loaded scene
	SceneHotspot *hotspot = NULL;
	if (_scene && _scene->checkHotSpot(ev.mouse, &hotspot)) {
		// Change mouse cursor		
		_runState.cursorStyle = (Cursor::CursorStyle)hotspot->cursor;

		// Load next scene
		if ((ev.type == Common::EVENT_LBUTTONDOWN)) {
			_gameState->currentScene = hotspot->scene;
			_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundAll);
			showScene(_gameState->currentScene, GraphicsManager::kBackgroundC);
			askForRedraw();
		}
	} else {
		_runState.cursorStyle = Cursor::kCursorNormal;
	}
	_engine->getCursor()->setStyle(_runState.cursorStyle);

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

void Logic::setScene(uint32 index) {
	_gameState->currentScene = index;

	delete _scene;

	_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundAll);

	_scene = _engine->getScene(_gameState->currentScene); 
	_engine->getGraphicsManager()->draw(_scene, GraphicsManager::kBackgroundC);
}

//////////////////////////////////////////////////////////////////////////
// Soundbites
//////////////////////////////////////////////////////////////////////////
Common::String Logic::sound_excuseMe() {
	switch(((LastExpressEngine*)g_engine)->getRandom().getRandomNumber(3)) {
	case 0:
		return "CAT1126B";
	case 1:
		return "CAT1126C";
	case 2:
		return "CAT1126D";
	}

	return "CAT1126B";
}

Common::String Logic::sound_justChecking() {
	switch(((LastExpressEngine*)g_engine)->getRandom().getRandomNumber(4)) {
	case 0:
		return "CAT5001";
	case 1:
		return "CAT5001A";
	case 2:
		return "CAT5001B";
	case 3:
		return "CAT5001C";
	}

	return "CAT5001";
}

Common::String Logic::sound_wrongDoor() {
	switch(((LastExpressEngine*)g_engine)->getRandom().getRandomNumber(5)) {
	case 0:
		return "CAT1125";
	case 1:
		return "CAT1125A";
	case 2:
		return "CAT1125B";
	case 3:
		return "CAT1125C";
	case 4:
		return "CAT1125D";
	}

	return "CAT1125";
}

Common::String Logic::sound_justAMinute() {
	switch(((LastExpressEngine*)g_engine)->getRandom().getRandomNumber(3)) {
	case 0:
		return "CAT1520";
	case 1:
		return "CAT1521";
	case 2:
		return "CAT1125";	// ?? is this a bug in the original?
	}

	return "CAT1520";
}


} // End of namespace LastExpress
