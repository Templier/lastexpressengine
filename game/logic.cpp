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

#include "lastexpress/game/logic.h"

// Data
#include "lastexpress/data/animation.h"
#include "lastexpress/data/scene.h"
#include "lastexpress/data/snd.h"

// Game
#include "lastexpress/game/action.h"
#include "lastexpress/game/beetle.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/menu.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"


namespace LastExpress {

Logic::Logic(LastExpressEngine *engine) : _engine(engine), _scene(NULL), _gameState(NULL) {
	_action = new Action(engine);
	_menu = new Menu(engine);
	_inventory = new Inventory(engine);
	_sound = new Sound(engine);
	_savepoints = new SavePoints(engine);
	_objects = new Objects(engine);
	_beetle = new Beetle(engine);
	_entities = new Entities(engine);
}

Logic::~Logic() {
	delete _action;
	delete _beetle;
	delete _sound;
	delete _objects;
	delete _gameState;
	delete _inventory;
	delete _menu;	
	delete _scene;
}

//////////////////////////////////////////////////////////////////////////
// Game & Menu
//////////////////////////////////////////////////////////////////////////

void Logic::startGame() {
	// Init data
	_inventory->init();

	delete _gameState;
	_gameState = new GameState();

	_entities->setup(kChapter1);

	showMenu(false);
	loadScene(1018);
	//loadScene(_defaultScene);
	
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
	_gameState->scene = _menu->getSceneIndex();
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
	loadScene(scene);
}

// Save game
void Logic::savegame() {
	warning("Logic::savegame is not implemented!");
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
		_runState.cursorStyle = _action->getCursor(hotspot->action, hotspot->param1, hotspot->param2, hotspot->param3, hotspot->cursor);

		// Handle click
		if ((ev.type == Common::EVENT_LBUTTONDOWN)) {
			_action->processHotspot(hotspot);
			if (hotspot->scene)
				setScene(hotspot->scene);

			// Switch to next chapter if necessary
			if (hotspot->action == SceneHotspot::kAction43 && hotspot->param1 == _gameState->progress.chapter)
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

void Logic::loadScene(uint32 index) {

	// TODO add rest of implementation
	setScene(index);
}

void Logic::setScene(uint32 index) {
	preProcessScene(&index);

	// Draw background
	delete _scene;
	_scene = _engine->getScene(index); 
	_engine->getGraphicsManager()->draw(_scene, GraphicsManager::kBackgroundC, true);
	_gameState->scene = index;

	// Update entities
	Scene *scene = (_gameState->sceneUseBackup ? _engine->getScene(_gameState->sceneBackup) : _scene);
	
	_entities->getEntityData(SavePoints::kNone)->field_491 = scene->getHeader()->count;
	_entities->getEntityData(SavePoints::kNone)->field_495 = scene->getHeader()->field_13;

	if (_gameState->sceneUseBackup)
		delete scene;

	_savepoints->pushAll(0, 17, 0);
	_savepoints->process();

	// TODO test + 3 function calls that draw sequences

	// Show the scene 
	askForRedraw();
	_engine->getGraphicsManager()->update();
	_engine->_system->updateScreen();
	_engine->_system->delayMillis(10);

	postProcessScene(&_gameState->scene);
}

void Logic::processScene() {
	error("Logic::processItem is not implemented!");
}

uint32 Logic::processIndex(uint32 index) {
	error("Logic::processItem is not implemented!");
}

void Logic::loadSceneFromData(int param1, int param2, int param3) {
	error("Logic::loadSceneFromData is not implemented!");

	// index = get index from fields
	// loadScene(index);
}

//////////////////////////////////////////////////////////////////////////
// Scene pre/post & hotspots
//////////////////////////////////////////////////////////////////////////
#define PROCESS_HOTSPOT_SCENE(hotspot, index) \
	_action->processHotspot(hotspot); \
	if ((hotspot)->scene) { \
		*index = (hotspot)->scene; \
		preProcessScene(index); \
	}

#define GET_ENTITY_LOCATION(scene) \
	_objects->get(scene->getHeader()->param1).location

#define GET_ITEM_LOCATION(scene, parameter) \
	_inventory->getEntry((Inventory::InventoryItem)scene->getHeader()->parameter)->location

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

				if (_objects->get(scene->getHeader()->param1).location == (*it)->location) {
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

			_action->processHotspot(hotspot);
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

		if (currentScene->getHeader()->type != Scene::kTypeLoadBeetleSequences)
			_beetle->unload();

		delete currentScene;
	}

	delete scene;
}

void Logic::postProcessScene(uint32 *index) {

	Scene* scene = _engine->getScene(*index);

	switch (scene->getHeader()->type) {
	case Scene::kTypeList: {
		// Adjust time
		_gameState->time += (scene->getHeader()->param1 + 10) * _gameState->timeDelta;
		_gameState->timeTicks += (scene->getHeader()->param1 + 10);

		// Some stuff related to menu?
		
		SceneHotspot *hotspot = scene->getHotspot(0);
		_action->processHotspot(hotspot);

		Scene *hotspotScene = _engine->getScene(hotspot->scene);
		while (hotspotScene->getHeader()->type == 128) {
			hotspot = hotspotScene->getHotspot(0);
			_action->processHotspot(hotspot);

			uint16 nextScene = hotspot->scene;
			delete hotspotScene;
			hotspotScene = _engine->getScene(nextScene);
		}

		// Some stuff related to entities (dialog Excuse me)

		if (hotspot->scene)
			setScene(hotspot->scene);

		break;
	}
		
	case Scene::kTypeSavePointChapter:
		if (getProgress().field_18 == 2)
			_savepoints->push(0, SavePoints::kChapters, 190346110, 0);
		break;

	case Scene::kTypeLoadBeetleSequences:
		if ((getProgress().chapter == kChapter2 || getProgress().chapter == kChapter3)
			&& _inventory->getEntry(Inventory::kBeetle)->location == 3) {
			if (!_beetle->isLoaded())
				_beetle->load();
		}		
		break;

	case Scene::kTypeGameOver:
		if (_gameState->time >= 2418300 || getProgress().field_18 == 4)
			break;

		playSfxStream("LIB050");
		switch (getProgress().chapter) {
		case kChapter1:
			gameOver(0, 0, 62, 1);
			break;

		case kChapter4:
			gameOver(0, 0, 64, 1);
			break;

		default:
			gameOver(0, 0, 63, 1);
			break;
		}
		break;

	case Scene::kTypeReadText: {
		const char *text = _sound->readText(scene->getHeader()->param1);
		if (text)
			playSfxStream(text);
		
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
// Misc
//////////////////////////////////////////////////////////////////////////

bool Logic::isDayTime() {
	return (_gameState->progress.chapter == kChapter1
		 || _gameState->progress.chapter == kChapter4
		 || (_gameState->progress.chapter == kChapter5 && _gameState->progress.is_nighttime));		
}

void Logic::switchChapter() {
	switch(_gameState->progress.chapter) {
	default:
		break;

	case kChapter1:
		_inventory->addItem(Inventory::kParchemin);
		_inventory->addItem(Inventory::kMatchBox);
		// TODO call game logic
		break;

	case kChapter2:
		_inventory->addItem(Inventory::kScarf);
		// TODO call game logic
		break;

	case kChapter3:
		_inventory->getEntry(Inventory::kFirebird)->location = 4;
		_inventory->getEntry(Inventory::kFirebird)->has_item = 0;
		_inventory->getEntry(Inventory::kItem11)->location = 1; // ??

		_inventory->addItem(Inventory::kWhistle);
		_inventory->addItem(Inventory::kKey);
		// TODO call game logic
		break;

	case kChapter4:
		// TODO call game logic
		break;

	case kChapter5:
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

void Logic::updateTrainClock() {

}

} // End of namespace LastExpress