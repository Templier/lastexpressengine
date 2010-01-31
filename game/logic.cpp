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
#include "lastexpress/data/cursor.h"
#include "lastexpress/data/scene.h"
#include "lastexpress/data/snd.h"

// Game
#include "lastexpress/game/action.h"
#include "lastexpress/game/beetle.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/menu.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"
#include "lastexpress/savegame.h"

namespace LastExpress {

Logic::Logic(LastExpressEngine *engine) : _engine(engine), _scene(NULL) {
	_action = new Action(engine);
	_beetle = new Beetle(engine);
	_entities = new Entities(engine);
	_menu = new Menu(engine);
	_sound = new Sound(engine);
}

Logic::~Logic() {
	delete _action;
	delete _beetle;
	delete _entities;
	delete _menu;
	delete _scene;
	delete _sound;
}

//////////////////////////////////////////////////////////////////////////
// Game & Menu
//////////////////////////////////////////////////////////////////////////

void Logic::startGame() {
	// Load scene data for the first cd
	loadSceneDataFile(kArchiveCd1);

	// Init data
	getInventory()->init();

	_entities->setup(kChapter1);

	showMenu(false);
	loadScene(kSceneDefault);

	// Set Cursor type
	_engine->getCursor()->setStyle(kCursorNormal);
	_engine->getCursor()->show(true);

	getInventory()->show(true);

	askForRedraw();
}

// Show main menu
void Logic::showMenu(bool visible) {

	if (!visible) {
		getInventory()->show(true);
		_runState.showingMenu = false;
		return;
	}

	// Hide inventory
	getInventory()->show(false);

	// TODO: load scene and set current scene
	_runState.showingMenu = true;
	getState()->scene = _menu->getSceneIndex();
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
		getState()->time = 2383200;
		_runState.gameStarted = true;
	}
	//////////////////////////////////////////////////////////////////////////

	// Redraw all menu elements
	showMenu(true);
}

// Handle game over
void Logic::gameOver(int a1, int a2, int scene, bool showScene) {

	warning("Logic::gameOver: not implemented!");
	loadScene(scene);
}

// Save game
void Logic::savegame(int param1, EntityIndex entity, EventIndex event) {
	warning("Logic::savegame: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Event Handling
//////////////////////////////////////////////////////////////////////////
bool Logic::handleMouseEvent(Common::Event ev) {

	// Special case for the main menu scene
	if (isShowingMenu()) {
		return _menu->handleStartMenuEvent(ev);
	}

	if (getInventory()->handleMouseEvent(ev))
		return true;

	// Check hitbox & event from scene data
	SceneHotspot *hotspot = NULL;
	if (_scene && _scene->checkHotSpot(ev.mouse, &hotspot)) {
		// Change mouse cursor
		_runState.cursorStyle = _action->getCursor(hotspot->action, (ObjectIndex)hotspot->param1, hotspot->param2, hotspot->param3, hotspot->cursor);

		// Handle click
		if ((ev.type == Common::EVENT_LBUTTONDOWN)) {
			_action->processHotspot(hotspot);
			if (hotspot->scene)
				setScene(hotspot->scene);

			// Switch to next chapter if necessary
			if (hotspot->action == SceneHotspot::kActionSwitchChapter && hotspot->param1 == getState()->progress.chapter)
				switchChapter();
		}
	} else {
		_runState.cursorStyle = kCursorNormal;
	}
	_engine->getCursor()->setStyle(_runState.cursorStyle);

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Scene
//////////////////////////////////////////////////////////////////////////
void Logic::loadSceneDataFile(ArchiveIndex archive) {
	switch(archive) {
	case kArchiveCd1:
	case kArchiveCd2:
	case kArchiveCd3:
		_engine->getSceneManager()->load(_engine->getResMan()->getFileStream(Common::String::printf("CD%iTRAIN.DAT", archive)));
		break;

	default:
	case kArchiveAll:
		error("Logic::loadSceneDataFile: Invalid archive index (must be [1-3], was %d", archive);
		break;
	}
}

void Logic::loadScene(uint32 index) {

	getFlags()->flag_0 = false;
	if (getState()->sceneUseBackup) {
		Scene *scene = getSceneObject(index);

		if (scene->getHeader()->param3 != 255) {
			getState()->sceneUseBackup = 0;
			getState()->sceneBackup2 = 0;
		}

		delete scene;
	}

	setScene(index);

	updateCursor();
}

void Logic::setScene(uint32 index) {
	_runState.flag_no_entity = false;

	if (_runState.flag_draw_entities) {
		// TODO Setup screen size (is it necessary for our animations?)
		drawScene(index);
		_runState.flag_no_entity = true;
	} else {
		_runState.flag_draw_entities = true;
		drawScene(index);
		_runState.flag_draw_entities = false;
	}
}

void Logic::drawScene(uint32 index) {
	preProcessScene(&index);

	// Draw background
	delete _scene;
	_scene = getSceneObject(index);
	_engine->getGraphicsManager()->draw(_scene, GraphicsManager::kBackgroundC, true);
	getState()->scene = index;

	// Update entities
	Scene *scene = (getState()->sceneUseBackup ? getSceneObject(getState()->sceneBackup) : _scene);

	getEntityData(kEntityNone)->field_491 = (EntityData::Field491Value)scene->getHeader()->count;
	getEntityData(kEntityNone)->field_495 = (EntityData::Field495Value)scene->getHeader()->field_13;

	if (getState()->sceneUseBackup)
		delete scene;

	if (getFlags()->flag_1) {
		getSavePoints()->pushAll(kEntityNone, kAction17);
		getSavePoints()->process();

		if (_runState.flag_no_entity)
			return;

		getEntities()->updateFields();
		getEntities()->setupSequences();
		getEntities()->setupCallbacks();
	}

	// Show the scene
	askForRedraw();
	_engine->getGraphicsManager()->update();
	_engine->_system->updateScreen();
	_engine->_system->delayMillis(10);

	postProcessScene(&getState()->scene);
}

void Logic::processScene() {
	if (!getState()->sceneUseBackup) {
		loadScene(getState()->scene);
		return;
	}

	getState()->sceneUseBackup = 0;

	// Select item if needed
	InventoryItem item = getInventory()->getFirstExaminableItem();
	if (item && getInventory()->getSelectedItem() == item)
		getInventory()->selectItem(item);

	Scene *backup = getSceneObject(getState()->sceneBackup);

	if (getState()->field1000[backup->getHeader()->field_15 + 100 * backup->getHeader()->field_13])
		loadScene(getLogic()->processIndex(getState()->sceneBackup));
	else
		loadScene(getState()->sceneBackup);

	delete backup;
}

uint32 Logic::processIndex(uint32 index) {
	error("Logic::processItem is not implemented!");
}

void Logic::loadSceneFromObject(ObjectIndex object) {
	switch (object) {
	default:
		break;

	case kObjectCompartment1:
	case kObjectCompartment2:
	case kObjectCompartment3:
	case kObjectCompartment4:
	case kObjectCompartment5:
	case kObjectCompartment6:
	case kObjectCompartment7:
	case kObjectCompartmentA:
	case kObjectCompartmentB:
	case kObjectCompartmentC:
	case kObjectCompartmentD:
	case kObjectCompartmentE:
	case kObjectCompartmentF:
	case kObjectCompartmentG:
		loadSceneFromData((object < 10 ? 3 : 4), 38 - (object - 1) * 2, 255);
		break;

	case kObjectCompartment8:
	case kObjectCompartmentH:
		loadSceneFromData(3, 25, 255);
		break;
	}
}

void Logic::loadSceneFromObject2(ObjectIndex object) {
	loadSceneFromData((object < 10 ? 3 : 4), 17 - (object - 1) * 2, 255);
}

void Logic::loadSceneFromData(int param1, int param2, int param3) {
	error("Logic::loadSceneFromData is not implemented!");

	// index = get index from fields
	// loadScene(index);
}

void Logic::loadSceneFromItem(InventoryItem item) {
	error("Logic::loadSceneFromItem is not implemented!");
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
	getObjects()->get((ObjectIndex)scene->getHeader()->param1).location

#define GET_ITEM_LOCATION(scene, parameter) \
	getInventory()->getEntry((InventoryItem)scene->getHeader()->parameter)->location

void Logic::preProcessScene(uint32 *index) {

	// Check index validity
	if (*index == 0 || *index > 2500)
		*index = 1;

	Scene* scene = getSceneObject(*index);

	switch (scene->getHeader()->type) {
	case Scene::kTypeItem:
	case Scene::kTypeItem2:
	case Scene::kTypeItem3:
	case Scene::kTypeEntity:
	case Scene::kTypeEntityItem: {
		int location = 0;
		ObjectLocation location1 = kLocationNone, location2 = kLocationNone, location3 = kLocationNone;
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

				Scene *currentScene = getSceneObject(*index);
				if (getObjects()->get((ObjectIndex)currentScene->getHeader()->param1).location2 == (*it)->location) {
					PROCESS_HOTSPOT_SCENE(*it, index);
					found = true;
				}
				delete currentScene;
			}
		}

		// If the scene has no hotspot or if we haven't found a proper hotspot, use the first hotspot from the current scene
		if (!found) {
			Scene *hotspotScene = getSceneObject(*index);
			SceneHotspot *hotspot = scene->getHotspot();

			PROCESS_HOTSPOT_SCENE(hotspot, index);

			delete hotspotScene;
		}
		break;
	}

	case Scene::kType7:
	case Scene::kType8:
		if (scene->getHeader()->param1 >= 16)
			break;

		if (getState()->field16[scene->getHeader()->param1] || getState()->field16_2[scene->getHeader()->param1]) {

			Scene *_currentScene = getSceneObject(getState()->scene);

			if ((checkSceneFields(getState()->scene, false) && checkSceneFields(*index, false) && _currentScene->getHeader()->count < scene->getHeader()->count)
			 || (checkSceneFields(getState()->scene, true)  && checkSceneFields(*index, true)  && _currentScene->getHeader()->count > scene->getHeader()->count)) {

				if (State::getPowerOfTwo(getState()->field16[scene->getHeader()->param1]) != 30
				 && State::getPowerOfTwo(getState()->field16_2[scene->getHeader()->param1]) != 30 )
					getSound()->playSound(kEntityNone, "CAT1126A");

				*index = scene->getHotspot()->scene;
			} else {
				*index = scene->getHotspot(1)->scene;
			}

			delete _currentScene;

			preProcessScene(index);
		} else {
			if (scene->getHeader()->type == Scene::kType7)
				break;

			if (scene->getHeader()->param2 >= 32)
				break;

			ObjectLocation location = getInventory()->getEntry((InventoryItem)scene->getHeader()->param2)->location;
			if (!location)
				break;

			for (Common::Array<SceneHotspot *>::iterator it = scene->getHotspots()->begin(); it != scene->getHotspots()->end(); ++it) {
				if ((*it)->location == location) {
					PROCESS_HOTSPOT_SCENE(*it, index);
					break;
				}
			}
		}
		break;

	default:
		break;
	}

	// Cleanup
	if (_beetle->isLoaded()) {
		// Get scene type
		Scene *currentScene = getSceneObject(*index);

		if (currentScene->getHeader()->type != Scene::kTypeLoadBeetleSequences)
			_beetle->unload();

		delete currentScene;
	}

	delete scene;
}

void Logic::postProcessScene(uint32 *index) {

	Scene* scene = getSceneObject(*index);

	switch (scene->getHeader()->type) {
	case Scene::kTypeList: {
		// Adjust time
		getState()->time += (scene->getHeader()->param1 + 10) * getState()->timeDelta;
		getState()->timeTicks += (scene->getHeader()->param1 + 10);

		// Some stuff related to menu?

		Scene *currentScene = getSceneObject(getState()->scene);
		SceneHotspot *hotspot = currentScene->getHotspot();
		_action->processHotspot(hotspot);

		if (getFlags()->flag_2) {
			Scene *hotspotScene = getSceneObject(hotspot->scene);
			while (hotspotScene->getHeader()->type == Scene::kTypeList) {
				hotspot = hotspotScene->getHotspot();
				_action->processHotspot(hotspot);

				uint16 nextScene = hotspot->scene;
				delete hotspotScene;
				hotspotScene = getSceneObject(nextScene);
			}
			delete hotspotScene;
		}

		EntityData::Field491Value field491 = getEntityData(kEntityNone)->field_491;
		if (getEntityData(kEntityNone)->field_495 == 9 && (field491 == 4 || field491 == 3)) {
			EntityIndex entities[39];

			int progress = 0;

			for (uint i = 1; i < 40; i++) {

				EntityData::Field493Value field493 = getEntityData((EntityIndex)i)->field_493;
				EntityData::Field495Value field495 = getEntityData((EntityIndex)i)->field_495;
				if (field491 == 4) {
					if (!(field495 != 4 || field493 <= 9270) || !(field495 != 5 || field493 >= 1540))
						entities[progress++] = (EntityIndex)i;
				} else {
					if (!(field495 != 3 || field493 <= 9270) || !(field495 != 4 || field493 >= 850))
						entities[progress++] = (EntityIndex)i;
				}
			}

			if (progress)
				getSound()->excuseMe((progress == 1) ? entities[0] : entities[random(progress)], 0 , 16);
		}

		if (hotspot && hotspot->scene)
			setScene(hotspot->scene);

		delete currentScene;
		break;
	}

	case Scene::kTypeSavePointChapter:
		if (getProgress().field_18 == 2)
			getSavePoints()->push(kEntityNone, kEntityChapters, kAction190346110);
		break;

	case Scene::kTypeLoadBeetleSequences:
		if ((getProgress().chapter == kChapter2 || getProgress().chapter == kChapter3)
		  && getInventory()->getEntry(kItemBeetle)->location == 3) {
			if (!_beetle->isLoaded())
				_beetle->load();
		}
		break;

	case Scene::kTypeGameOver:
		if (getState()->time >= 2418300 || getProgress().field_18 == 4)
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
		if (getFlags()->flag_0) {
			getFlags()->flag_0 = false;
			updateCursor();
		}
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
void Logic::switchChapter() {
	switch(getState()->progress.chapter) {
	default:
		break;

	case kChapter1:
		getInventory()->addItem(kItemParchemin);
		getInventory()->addItem(kItemMatchBox);
		// TODO call game logic
		break;

	case kChapter2:
		getInventory()->addItem(kItemScarf);
		// TODO call game logic
		break;

	case kChapter3:
		getInventory()->getEntry(kItemFirebird)->location = kLocation4;
		getInventory()->getEntry(kItemFirebird)->has_item = 0;
		getInventory()->getEntry(kItem11)->location = kLocation1;

		getInventory()->addItem(kItemWhistle);
		getInventory()->addItem(kItemKey);
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
	_action->playAnimation(kEventFinalSequence);
	// TODO
	// - function call
	// - reset game state
	// - reset save points
	// - ??value = 1

	showMenu(true);
}

void Logic::updateTrainClock() {
	warning("Logic::updateTrainClock: not implemented!");
}

void Logic::updateCursor() {
	warning("Logic::updateCursor: not implemented!");
}

bool Logic::checkSceneFields(uint32 index, bool isSecondCheck) {
	bool result = false;
	Scene *scene = getSceneObject((index ? index : getState()->scene));

	uint16 field13 = scene->getHeader()->field_13;
	byte field15 = scene->getHeader()->field_15;

	delete scene;

	result = (field13 == 3 || field13 == 4);

	if (!isSecondCheck)
		return result && (field15 >= 1 && field15 <= 19);

	return result && (field15 >= 21 && field15 <= 40);
}

} // End of namespace LastExpress
