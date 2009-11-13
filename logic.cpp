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
#include "lastexpress/beetle.h"
#include "lastexpress/dialog.h"
#include "lastexpress/entity.h"
#include "lastexpress/inventory.h"
#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/menu.h"
#include "lastexpress/resource.h"
#include "lastexpress/savepoint.h"
#include "lastexpress/scene.h"
#include "lastexpress/sound.h"

namespace LastExpress {

Logic::Logic(LastExpressEngine *engine) : _engine(engine), _scene(NULL) {
	_action = new Action(engine);
	_menu = new Menu(engine);
	_inventory = new Inventory(engine);
	_dialog = new Dialog(engine);
	_savepoints = new SavePoints();
	_entities = new Entities(engine);
	_beetle = new Beetle(engine);

	// Get those from savegame
	_gameState = new GameState();

	// Init inventory
	_inventory->init();
}

Logic::~Logic() {
	delete _action;
	delete _beetle;
	delete _dialog;
	delete _entities;
	delete _gameState;
	delete _inventory;
	delete _menu;	
	delete _scene;
}

//////////////////////////////////////////////////////////////////////////
// Game & Menu
//////////////////////////////////////////////////////////////////////////

void Logic::startGame() {
	showMenu(false);

	//setScene(_defaultScene);
	setScene(1018);
	
	// Set Cursor type
	_engine->getCursor()->setStyle(Cursor::kCursorNormal);
	_engine->getCursor()->show(true);

	_inventory->show(true);

	askForRedraw();
}

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

// Handle game over
void Logic::gameOver(int a1, int a2, int scene, bool showScene) {

	// TODO implement
	setScene(scene);
}

//////////////////////////////////////////////////////////////////////////
// Event Handling
//////////////////////////////////////////////////////////////////////////
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
		_runState.cursorStyle = getCursor(hotspot);

		// Handle click
		if ((ev.type == Common::EVENT_LBUTTONDOWN)) {
			processHotspot(hotspot);
			if (hotspot->scene)
				setScene(hotspot->scene);

			// Switch to next chapter if necessary
			if (hotspot->action == SceneHotspot::kAction43 && hotspot->param1 == _gameState->progress.index)
				switchChapter();
		}
	} else {
		_runState.cursorStyle = Cursor::kCursorNormal;
	}
	_engine->getCursor()->setStyle(_runState.cursorStyle);

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Scene
//////////////////////////////////////////////////////////////////////////
void Logic::setScene(uint32 index) {
	_gameState->currentScene = index;

	delete _scene;

	preProcessScene(&_gameState->currentScene);

	_scene = _engine->getScene(_gameState->currentScene); 
	_engine->getGraphicsManager()->draw(_scene, GraphicsManager::kBackgroundC, true);
	askForRedraw();

	// Show the scene 
	_engine->getGraphicsManager()->update();
	_engine->_system->updateScreen();
	_engine->_system->delayMillis(10);

	postProcessScene(&_gameState->currentScene);
}

void Logic::updateTrainClock() {

}

//////////////////////////////////////////////////////////////////////////
// Scene pre/post & hotspots
//////////////////////////////////////////////////////////////////////////
#define PROCESS_HOTSPOT_SCENE(hotspot, index) \
	processHotspot(hotspot); \
	if ((hotspot)->scene) { \
		*index = (hotspot)->scene; \
		preProcessScene(index); \
	}

#define GET_ENTITY_LOCATION(scene) \
	_entities->get(scene->getHeader()->param1).location

#define GET_ITEM_LOCATION(scene, parameter) \
	_inventory->getItem((Inventory::InventoryItem)scene->getHeader()->parameter)->location

void Logic::preProcessScene(uint32 *index) {

	// Check index validity
	if (*index == 0 || *index > 2500)
		*index = 1;

	Scene* scene = _engine->getScene(*index);

	switch (scene->getHeader()->type) {
	case Scene::kTypeItem:
	case Scene::kTypeItem2:	
	case Scene::kTypeItem3:
	case Scene::kTypeEntity:
	case Scene::kTypeEntityItem: {
		byte location1, location2, location3; 
		byte type = scene->getHeader()->type;

		// Check bounds
		if (scene->getHeader()->param1 >= ((type == Scene::kTypeEntity || type == Scene::kTypeEntityItem) ? 128 : 32))
			break;

		if (type != Scene::kTypeItem && scene->getHeader()->param2 >= 32)
			break;

		if (type == Scene::kTypeItem3 && scene->getHeader()->param3 >= 32)
			break;

		// Check location
		if (type == Scene::kTypeEntity || type == Scene::kTypeEntityItem)
			location1 = GET_ENTITY_LOCATION(scene);			
		else
			location1 = GET_ITEM_LOCATION(scene, param1);

		if (type != Scene::kTypeItem)
			location2 = GET_ITEM_LOCATION(scene, param2);

		if (type == Scene::kTypeItem3)
			location3 = GET_ITEM_LOCATION(scene, param3);

		int location = 0;

		if (location1)
			location = 1;

		if (type != Scene::kTypeItem && location2)
			location |= 2;

		if (type == Scene::kTypeItem3 && location3)
			location |= 4;

		if (!location)
			break;

		for (Common::Array<SceneHotspot *>::iterator it = scene->getHotspots()->begin(); it != scene->getHotspots()->end(); ++it) {
			
			if ((type == Scene::kTypeItem || type == Scene::kTypeEntity)) {
				if ((*it)->location != location1) {
					continue;
				}
			} else {
				if ((*it)->location != location 
				 || (*it)->param1 != location1 
				 || (*it)->param2 != location2) {
					continue;
				}
			}

			// Special case for TypeItem3
			if (type == Scene::kTypeItem3 && (*it)->param3 != location3)
				continue;
			
			PROCESS_HOTSPOT_SCENE(*it, index);
			break;
		}		
		break;
	}	

	case Scene::kType6: {
		if (scene->getHeader()->param1 >= 128)
			break;

		bool found = false;
		if (scene->getHotspots()->size() > 0) {
			for (Common::Array<SceneHotspot *>::iterator it = scene->getHotspots()->begin(); it != scene->getHotspots()->end(); ++it) {

				if (_entities->get(scene->getHeader()->param1).location == (*it)->location) {
					PROCESS_HOTSPOT_SCENE(*it, index);
					found = true;
					break;
				}
			}	
		}

		// If the scene has no hotspot or if we haven't found a proper hotspot, get the first hotspot from the current scene
		if (!found) {
			// TODO make sure we are doing the right thing here
			Scene *hotspotScene = _engine->getScene(*index);
			SceneHotspot *hotspot = scene->getHotspot(0);
			if (!hotspot) {
				delete hotspotScene;
				break;
			}

			processHotspot(hotspot);
			if (hotspot->scene) {
				*index = hotspot->scene;
				preProcessScene(index);

				// TODO else case missing
			}

			delete hotspotScene;
		}
		break;	
	}

	case Scene::kType7:
		if (scene->getHeader()->param1 >= 16)
			break;

		warning("Logic::preProcessScene: unimplemented scene type (%02d)", scene->getHeader()->type);		
		break;

	case Scene::kType8:
		if (scene->getHeader()->param1 >= 16)
			break;

		warning("Logic::preProcessScene: unsupported scene type (%02d)", scene->getHeader()->type);
		break;

	default:
		break;
	}

	// Cleanup
	if (_beetle->isLoaded()) {
		// Get scene type
		Scene *currentScene = _engine->getScene(*index);
		if (currentScene->getHeader()->type != -126)
			_beetle->unload();

		delete currentScene;
	}

	delete scene;
}

void Logic::postProcessScene(uint32 *index) {

	Scene* scene = _engine->getScene(*index);

	switch (scene->getHeader()->type) {
	case Scene::kTypeSequence: {
		// Adjust time
		_gameState->time += (scene->getHeader()->param1 + 10) * _gameState->timeDelta;
		_gameState->timeTicks += (scene->getHeader()->param1 + 10);

		// Some stuff

		SceneHotspot *hotspot = scene->getHotspot(0);
		processHotspot(hotspot);

		Scene *hotspotScene = _engine->getScene(hotspot->scene);
		while (hotspotScene->getHeader()->type == 128) {
			hotspot = hotspotScene->getHotspot(0);
			processHotspot(hotspot);

			uint16 nextScene = hotspot->scene;
			delete hotspotScene;
			hotspotScene = _engine->getScene(nextScene);
		}

		// More stuff

		if (hotspot->scene)
			setScene(hotspot->scene);

		break;
	}
		
	case Scene::kTypeSavePoint:
		if (getProgress().field_18 == 2)
			_savepoints->push(0, 31, 190346110, 0);
		break;

	case Scene::kTypeLoadBeetleSequences:
		if ((getProgress().index == 2 || getProgress().index == 3)
			&& _inventory->getItem(Inventory::kBeetle)->location == 3) {
			if (!_beetle->isLoaded())
				_beetle->load();
		}		
		break;

	case Scene::kTypeGameOver:
		if (_gameState->time >= 2418300 || getProgress().field_18 == 4)
			break;

		playSfx("LIB050");
		switch (getProgress().index) {
		case 1:
			gameOver(0, 0, 62, 1);
			break;

		case 4:
			gameOver(0, 0, 64, 1);
			break;

		default:
			gameOver(0, 0, 63, 1);
			break;
		}
		break;

	case Scene::kTypeReadText: {
		const char *text = _dialog->readText(scene->getHeader()->param1);
		if (text)
			playSfx(text);
		
		break;
	}

	case Scene::kType133:
		warning("Logic::postProcessScene: unsupported scene type (%02d)", scene->getHeader()->type);
		// TODO do some stuff with inventory
		break;
		
	default:
		break;
	}

	// Cleanup
	delete scene;
}

//////////////////////////////////////////////////////////////////////////
// Hotspot
//////////////////////////////////////////////////////////////////////////
void Logic::processHotspot(SceneHotspot *hotspot) {

	switch (hotspot->action) {
	case SceneHotspot::kAction1:
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);
		break;

	case SceneHotspot::kActionSavePoint:	
		_savepoints->push(0, hotspot->param1, hotspot->param2, 0);
		break;

	case SceneHotspot::kActionPlaySound:
		// TODO: Check validity: does the file exits (LIBxxx)?
		if (hotspot->param2)
			playSfx(_dialog->getSound(0, hotspot->param1, hotspot->param2));
		break;

	case SceneHotspot::kActionPlayMusic:		
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);

	case SceneHotspot::kActionKnockDoor:
		if (hotspot->param1 >= 128)
			break;

		if (_entities->get(hotspot->param1).field_0)
			_savepoints->push(0, _entities->get(hotspot->param1).field_0, 8, hotspot->param1);
		else
			playSfx(_dialog->getSound(0, 12, 0));
		
		break;

	case SceneHotspot::kAction6:
		// TODO extract to function
		if (hotspot->param1 >= 128)
			break;

		if (_entities->get(hotspot->param1).field_0) {
			_savepoints->push(0, _entities->get(hotspot->param1).field_0, 9, hotspot->param1);
			hotspot->scene = 0;
			break;
		}

		if (0 /* call to function that does a bunch of stuff */) {
			hotspot->scene = 0;
			break;
		}

		if (_entities->get(hotspot->param1).location == 1 || _entities->get(hotspot->param1).location == 3 || 0 /* another call to another function X*/) {
			error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);

			break;
		}

		if (hotspot->action != 16 || _inventory->getSelectedItem() != Inventory::kKey) {
			if (hotspot->param1 == 109) {
				playSfx(_dialog->getSound(0, 26, 0));
			} else {
				playSfx(_dialog->getSound(0, 14, 0));
				playSfx(_dialog->getSound(0, 15, 22));
			}
			break;
		}

		_entities->update(1, 0, 1, 10, 9);
		playSfx(_dialog->getSound(0, 16, 0));
		_inventory->unselectItem();
		hotspot->scene = 0;
		
		break;

	case SceneHotspot::kActionPlaySounds:
		playSfx(_dialog->getSound(0, hotspot->param1, 0));
		playSfx(_dialog->getSound(0, hotspot->param3, hotspot->param2));
		break;

	case SceneHotspot::kActionPlayAnimation:
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);

	case SceneHotspot::kActionOpenWindow:
		if (hotspot->param1 >= 128)
			break;

		// TODO update entity

		if ((hotspot->param1 < 9  || hotspot->param1 > 16)
		 && (hotspot->param1 < 40 || hotspot->param1 > 47)) {
			
			switch (hotspot->param2) {
			case 1:
				playSfx(_dialog->getSound(0, 24, 0));
				break;
			
			case 2:
				playSfx(_dialog->getSound(0, 36, 0));
				break;

			default:
				break;
			}
		}

		switch (hotspot->param2) {
		case 1:
			playSfx(_dialog->getSound(0, 21, 0));
			break;

		case 2:
			playSfx(_dialog->getSound(0, 20, 0));
			break;

		default:
			break;
		}

	case SceneHotspot::kAction10:
		if (hotspot->param1 >= 128)
			break;

		// TODO Store value in savegame_640
		if (hotspot->param1 != 112) {
			if (hotspot->param1 == 1)
				playSfx(_dialog->getSound(0, 73, 0));
		} else  {
			playSfx(_dialog->getSound(0, 96, 0));	
		}
		break;

	case SceneHotspot::kAction11:
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);

	case SceneHotspot::kActionCompartment: {
		Inventory::InventoryEntry* item = _inventory->getItem((Inventory::InventoryItem)hotspot->param1);

		if (hotspot->param1 >= 32 || !item->location)
			break;

		switch(hotspot->param1) {
		case 20:
			_action->pickCorpse(hotspot->param2);

			// TODO further process index

			// Add corpse to inventory
			if (hotspot->param2 != 4) { // bed position
				_inventory->addItem(Inventory::kCorpse);
				_inventory->selectItem(Inventory::kCorpse);
				_engine->getCursor()->setStyle(Cursor::kCursorCorpse);
			}
			break;


		}
		
		break;
	}

	case SceneHotspot::kActionDropItem:
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);

	case SceneHotspot::kActionExitCompartment:
		if (!getProgress().field_30 && getProgress().jacket != 0) {
			// TODO save game
			getProgress().field_30 = 1;
		}
		_entities->updateField4(1, hotspot->param2);

		// fall to case kActionEnterCompartment

	case SceneHotspot::kActionEnterCompartment:
		
		if (_entities->get(1).location == 1 || _entities->get(1).location == 3 || _inventory->getSelectedItem() == Inventory::kKey) {
			hotspot_enterCompartment(hotspot);
			break;
		}

		if (getProgress().event_found_corpse) {

			if (hotspot->action != 16 || _inventory->getItem(Inventory::kBriefcase)->location != 2) {
				hotspot_enterCompartment(hotspot);
			} else {				
				playSfx(_dialog->getSound(0, 14, 0));
				playSfx(_dialog->getSound(0, 15, 22));
				if (getProgress().field_78) {
					playMusic("MUS003");
					getProgress().field_78 = 0;
				}

				// TODO call to further process scene index
				error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);
			}
		} else {
			// TODO savegame
			playSfx("LIB014");
			_action->playAnimation(Action::kCathFindCorpse);
			playSfx("LIB015");
			getProgress().event_found_corpse = 1;
			hotspot->scene = 42; // Tyler compartment with corpse on floor
		}
		break;

	case SceneHotspot::kActionOutsideTrain:
	case SceneHotspot::kAction19:
	case SceneHotspot::kAction20:
	case SceneHotspot::kActionClimbUpTrain:
	case SceneHotspot::kAction22:
	case SceneHotspot::kActionClimbDownTrain:
	case SceneHotspot::kActionUnbound:
	case SceneHotspot::kAction25:
	case SceneHotspot::kAction26:
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);

	case SceneHotspot::kAction27:
		playSfx(_dialog->getSound(0, 31, 0));

		// TODO update game state
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);
		break;

	case SceneHotspot::kAction28:
	case SceneHotspot::kAction29:
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);

	case SceneHotspot::kActionCatchBeetle:	
		if (_beetle->isLoaded()) {
			if (_beetle->catchBeetle()) {
				_beetle->unload();
				_inventory->getItem(Inventory::kBeetle)->location = 1;
				_savepoints->push(0, 32, 202613084, 0);
			}
		}
		break;

	case SceneHotspot::kAction32:
	case SceneHotspot::KActionUseWhistle:
	case SceneHotspot::kActionOpenMatchBox:
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);

	case SceneHotspot::kActionOpenBed:
		playSfx(_dialog->getSound(0, 59, 0));
		break;

	case SceneHotspot::kActionDialog:
		playSfx(_dialog->getDialog((Dialog::DialogId)hotspot->param1));
		break;

	case SceneHotspot::kActionEggBox:
		playSfx(_dialog->getSound(0, 43, 0));
		if (getProgress().field_7C) {
			playMusic("MUS003");
			getProgress().field_7C = 0;
		}
		break;

	case SceneHotspot::kAction39:
		playSfx(_dialog->getSound(0, 24, 0));
		if (getProgress().field_80) {
			playMusic("MUS003");
			getProgress().field_80 = 0;
		}
		break;

	case SceneHotspot::kActionBed:
		playSfx(_dialog->getSound(0, 85, 0));
		// falls to case 12
	case SceneHotspot::kAction12:
		if (hotspot->param1 >= 128)
			break;

		if (_entities->get(hotspot->param1).field_0)
			_savepoints->push(0, _entities->get(hotspot->param1).field_0, 8, hotspot->param1);

		break;

	case SceneHotspot::kAction41:
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);

	case SceneHotspot::kAction42: {
		int value;
		switch (getProgress().index) {
		case 1:
			value = 1;
			break;
			
		case 2:
		case 3:
			value = 2;
			break;

		case 4:
		case 5:
			value = 4;
			break;
		}

		if (hotspot->param3 & value) {
			char filename[6];
			sprintf((char*)&filename, "MUS%03d", hotspot->param1);
			playMusic((char *)&filename);
			_savepoints->call(0, 32, 203863200, (int)&filename);
			_savepoints->push(0, 32, 222746496, hotspot->param2);

		}

		break;
	}

	case SceneHotspot::kAction44:
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);
		break;
	default:
		break;
	}
}

void Logic::hotspot_enterCompartment(SceneHotspot *hotspot) {
	if (hotspot->param1 >= 128)
		return;

	if (_entities->get(hotspot->param1).field_0) {
		_savepoints->push(0, _entities->get(hotspot->param1).field_0, 9, hotspot->param1);
		hotspot->scene = 0;
		return;
	}

	if (0 /*function call f(hotspot->param1, 1, 1) */) {
		hotspot->scene = 0;
		return;
	}

	byte location = _entities->get(hotspot->param1).location;
	if (location == 1 || location == 3 || 0 /* TODO function call */) {
		error("Logic::processHotspot: unsupported hotspot action (%02d)", hotspot->action);
		return;
	}

	if (hotspot->action != 16 || _inventory->getSelectedItem() != Inventory::kKey) {
		if (hotspot->param1 == 109) {
			playSfx(_dialog->getSound(0, 26, 0));
		} else {
			playSfx(_dialog->getSound(0, 14, 0));
			playSfx(_dialog->getSound(0, 15, 22));
		}
		return;
	}

	_entities->update(1, 0, 1, 10, 9);
	playSfx(_dialog->getSound(0, 16, 0));
	_inventory->unselectItem();
	hotspot->scene = 0;
}

//////////////////////////////////////////////////////////////////////////
// Cursor
//////////////////////////////////////////////////////////////////////////

Cursor::CursorStyle Logic::getCursor(SceneHotspot *hotspot) {

	// Simple cursor style
	if (hotspot->cursor != 128)
		return (Cursor::CursorStyle)hotspot->cursor;

	switch (hotspot->action) {
	default:
		return Cursor::kCursorNormal;

	case SceneHotspot::kAction1:
		if (!_gameState->currentScene3 && (_gameState->events[Action::kKronosBringFirebird] || _gameState->progress.field_74))				
			return Cursor::kCursorNormal;
		else
			return Cursor::kCursorBackward;		

	case SceneHotspot::kActionKnockDoor:
		if (hotspot->param1 >= 128)
			return Cursor::kCursorNormal;
		else
			return (Cursor::CursorStyle)_entities->get(hotspot->param1).cursor;
		
LABEL_KEY:
	case SceneHotspot::kAction6:
	case SceneHotspot::kActionExitCompartment:
		if (hotspot->param1 >= 128)
			return Cursor::kCursorNormal;
		
		if (1/* test with savegame data */)
			return Cursor::kCursorForward; // HACK should be extracted from savegame data 
		else
			return Cursor::kCursorKey;
		

	case SceneHotspot::kAction12:
		if (hotspot->param1 >= 128)
			return Cursor::kCursorNormal;
		else {
			if (_entities->get(hotspot->param1).field_0)
				return (Cursor::CursorStyle)_entities->get(hotspot->param1).cursor;
			else
				return Cursor::kCursorNormal;
		}

	case SceneHotspot::kActionCompartment:
		if (hotspot->param1 >= 32)
			return Cursor::kCursorNormal;
		
		if ((!_inventory->getSelectedItem() || _inventory->getItem(_inventory->getSelectedItem())->no_autoselect) 
			 && (hotspot->param1 != 21 || _gameState->progress.field_8 == 1))
			 return Cursor::kCursorHand;
		else
			return Cursor::kCursorNormal;			

	case SceneHotspot::kActionDropItem:
		if (hotspot->param1 >= 32)
			return Cursor::kCursorNormal;

		if (_inventory->getSelectedItem() != hotspot->param1)
			return Cursor::kCursorNormal;

		if (hotspot->param1 == 20 && hotspot->param2 == 4 && !_gameState->progress.field_50)
			return Cursor::kCursorNormal;

		if (hotspot->param1 == 18  && hotspot->param2 == 1 && _gameState->progress.field_5C)
			return Cursor::kCursorNormal;
	
		return (Cursor::CursorStyle)_inventory->getSelectedItem();

	case SceneHotspot::kAction15:
		if (hotspot->param1 >= 128)
			return Cursor::kCursorNormal;

		if (*(&_gameState->progress.field_0 + hotspot->param1) == hotspot->param2)
			return (Cursor::CursorStyle)hotspot->param3;

		return Cursor::kCursorNormal; 

	case SceneHotspot::kActionEnterCompartment:
		if (_inventory->getSelectedItem() != Inventory::kKey)
			goto LABEL_KEY;

		// TODO check other savegame struct...

		if (!_inventory->hasItem(Inventory::kKey))
			goto LABEL_KEY;

		if (_inventory->getSelectedItem() != Inventory::kFirebird && _inventory->getSelectedItem() != Inventory::kBriefcase)
			goto LABEL_KEY;

		return Cursor::kCursorKey;

	case SceneHotspot::kActionOutsideTrain:
		if (getProgress().jacket != Logic::kGreenJacket)
			return Cursor::kCursorNormal;

		if ((_gameState->events[Action::kCathLookOutsideWindowDay] || _gameState->events[Action::kCathLookOutsideWindowDay] || _entities->get(1).field_4)
		 && getProgress().field_50
		 && (hotspot->param1 != 45 || 1/*function call*/ && _entities->get(44).location == 2)
		 && _inventory->getSelectedItem() != Inventory::kBriefcase
		 && _inventory->getSelectedItem() != Inventory::kFirebird)
			return Cursor::kCursorForward; 

		return Cursor::kCursorNormal; 

	case SceneHotspot::kAction19:
		error("Logic::getCursor: unsupported cursor for action (%02d)", hotspot->action);

	case SceneHotspot::kActionClimbUpTrain:
		if (_gameState->progress.field_50
		 && (_gameState->progress.index == 2 || _gameState->progress.index == 3 || _gameState->progress.index == 5)
		 && _inventory->getSelectedItem() != Inventory::kFirebird 
		 && _inventory->getSelectedItem() != Inventory::kBriefcase)
			return Cursor::kCursorUp;

		return Cursor::kCursorNormal; 

	case SceneHotspot::kActionClimbDownTrain:
		error("Logic::getCursor: unsupported cursor for action (%02d)", hotspot->action);

	case SceneHotspot::kActionUnbound:
		if (hotspot->param2 != 2)
			return Cursor::kCursorNormal; 
				
		if (_gameState->events[Action::kCathBurnRope] || !_gameState->events[Action::kCathStruggleWithBonds2])
			return Cursor::kCursorNormal; 

		return Cursor::kCursorHand; 

	case SceneHotspot::kActionCatchBeetle:	
		error("Logic::getCursor: unsupported cursor for action (%02d)", hotspot->action);

	case SceneHotspot::KActionUseWhistle:
		if (hotspot->param1 != 3)
			return Cursor::kCursorNormal; 

		if (_inventory->getSelectedItem() == Inventory::kWhistle)
			return Cursor::kCursorWhistle;
		else
			return Cursor::kCursorNormal; 

	case SceneHotspot::kActionOpenBed:
		if (getProgress().index < 2)
			return Cursor::kCursorHand;
		
		return Cursor::kCursorNormal;		

	case SceneHotspot::kActionDialog:
		if (_dialog->getDialog((Dialog::DialogId)hotspot->param1))
			return Cursor::kCursorHandPointer; 

		return Cursor::kCursorNormal;

	case SceneHotspot::kActionBed:
		if (getProgress().field_18 == 2 && !getProgress().field_E4
		&& (_gameState->time > 1404000 || getProgress().event_august_met && getProgress().field_CC
		&& (!getProgress().field_24 || getProgress().field_3C)))
			return Cursor::kCursorSleep;

		return Cursor::kCursorNormal;
	}

}

//////////////////////////////////////////////////////////////////////////
// Misc
//////////////////////////////////////////////////////////////////////////

void Logic::switchChapter() {
	switch(_gameState->progress.index) {
	default:
		break;

	case 1:
		_inventory->addItem(Inventory::kParchemin);
		_inventory->addItem(Inventory::kMatchBox);
		// TODO call game logic
		break;

	case 2:
		_inventory->addItem(Inventory::kScarf);
		// TODO call game logic
		break;

	case 3:
		_inventory->getItem(Inventory::kFirebird)->location = 4;
		_inventory->getItem(Inventory::kFirebird)->has_item = 0;
		_inventory->getItem(Inventory::kItem11)->location = 1; // ??

		_inventory->addItem(Inventory::kWhistle);
		_inventory->addItem(Inventory::kKey);
		// TODO call game logic
		break;

	case 4:
		// TODO call game logic
		break;

	case 5:
		playFinalSequence();
		break;
	}
}

void Logic::playFinalSequence() {
	// TODO function call
	_action->playAnimation(Action::kFinalSequence);
	// TODO
	// - function call
	// - reset game state
	// - reset save points
	// - ??value = 1

	showMenu(true);
}

} // End of namespace LastExpress