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

// Entities
#include "lastexpress/entities/chapters.h"

// Game
#include "lastexpress/game/action.h"
#include "lastexpress/game/beetle.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/fight.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/menu.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savegame.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

Logic::Logic(LastExpressEngine *engine)
	: _engine(engine), _currentScene(NULL) {
	_action   = new Action(engine);
	_beetle   = new Beetle(engine);
	_entities = new Entities(engine);
	_fight    = new Fight(engine);
	_menu     = new Menu(engine);
	_saveload = new SaveLoad(engine);
	_sound    = new Sound(engine);
	_state    = new State(engine);
}

Logic::~Logic() {
	delete _action;
	delete _beetle;
	delete _fight;
	delete _currentScene;
	delete _entities;
	delete _menu;
	delete _saveload;
	delete _sound;
	delete _state;

	// Zero-out passed pointers
	_engine = NULL;
}

//////////////////////////////////////////////////////////////////////////
// Game & Menu
//////////////////////////////////////////////////////////////////////////

void Logic::startGame() {
	// Load scene data for the first CD
	loadSceneDataFile(kArchiveCd1);

	// Initialize data
	getInventory()->init();

	_entities->setup(kChapter1);

	// DEBUG
	_menu->setShowStartup(false);
	_runState.showingMenu = false;
	getFlags()->gameRunning = true;
	SET_EVENT_HANDLERS(Logic); 

	// Set Cursor type
	_engine->getCursor()->setStyle(kCursorNormal);
	_engine->getCursor()->show(true);

	loadScene(kSceneDefault);

	getInventory()->show();

	askForRedraw();
}

// Show main menu
void Logic::showMenu(bool visible) {

	if (!visible) {
		getInventory()->show();
		_runState.showingMenu = false;
		return;
	}

	// Hide inventory
	// FIXME getInventory()->show(false);

	// TODO: load scene and set current scene
	_runState.showingMenu = true;
	getState()->scene = _menu->getSceneIndex();
	_menu->showMenu(false, kTimeType0, 0);

	// TODO reset showingMenu to false when starting/returning to a game and show inventory

	// TODO: move to shared method
	// Initialize the first savegame if needed
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

	// Initialize savegame if needed
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

//////////////////////////////////////////////////////////////////////////
// Event Handling
//////////////////////////////////////////////////////////////////////////
void Logic::eventMouseClick(const Common::Event &ev) {
	// Update state
	getGameState()->setCoordinates(ev.mouse);

	// Special case for the main menu scene
	if (isShowingMenu()) {
		_menu->eventMouseClick(ev);
		return;
	}

	if (getInventory()->handleMouseEvent(ev))
		return;

	// Check hit box & event from scene data
	SceneHotspot *hotspot = NULL;
	if (_currentScene && _currentScene->checkHotSpot(ev.mouse, &hotspot) && ev.type == Common::EVENT_LBUTTONUP) {
		SceneIndex scene = _action->processHotspot(*hotspot);
		if (scene != kSceneInvalid)
			hotspot->scene = scene;

		if (hotspot->scene)
			setScene(hotspot->scene);

		// Switch to next chapter if necessary
		if (hotspot->action == SceneHotspot::kActionSwitchChapter && hotspot->param1 == getState()->progress.chapter)
			switchChapter();
	}
}

void Logic::eventMouseMove(const Common::Event &ev) {
	// Special case for the main menu scene
	if (isShowingMenu()) {
		_menu->eventMouseMove(ev);
		return;
	}

	if (getInventory()->handleMouseEvent(ev))
		return;

	// Check hit box & event from scene data
	SceneHotspot *hotspot = NULL;
	if (_currentScene && _currentScene->checkHotSpot(ev.mouse, &hotspot))
		_runState.cursorStyle = _action->getCursor(hotspot->action, (ObjectIndex)hotspot->param1, hotspot->param2, hotspot->param3, hotspot->cursor);
	else
		_runState.cursorStyle = kCursorNormal;

	_engine->getCursor()->setStyle(_runState.cursorStyle);
}

//////////////////////////////////////////////////////////////////////////
// Scene
//////////////////////////////////////////////////////////////////////////
void Logic::loadSceneDataFile(ArchiveIndex archive) const {
	switch(archive) {
	case kArchiveCd1:
	case kArchiveCd2:
	case kArchiveCd3:
		if (!_engine->getSceneManager()->load(_engine->getResourceManager()->getFileStream(Common::String::printf("CD%iTRAIN.DAT", archive))))
			error("Logic::loadSceneDataFile: cannot load data file CD%iTRAIN.DAT", archive);
		break;

	default:
	case kArchiveAll:
		error("Logic::loadSceneDataFile: Invalid archive index (must be [1-3], was %d", archive);
		break;
	}
}

void Logic::loadScene(SceneIndex index) {

	getFlags()->flag_0 = false;
	getFlags()->flag_4 = true;

	if (getState()->sceneUseBackup) {
		loadSceneObject(scene, index);

		if (scene.getHeader()->param3 != 255) {
			getState()->sceneUseBackup = false;
			getState()->sceneBackup2 = kSceneNone;
		}
	}

	// Save shouldRedraw state and redraw if necessary
	bool shouldRedraw = getFlags()->shouldRedraw;
	if (shouldRedraw) {
		shouldRedraw = false;
		// TODO check whether we need to do that here
		askForRedraw();
		redrawScreen();
	}

	// Set the scene
	setScene(index);

	// TODO Events method call (might be a low level graphic that we don't need)

	if (getFlags()->gameRunning && getFlags()->shouldDrawEggOrHourGlass)
		getInventory()->drawEgg();

	// Restore shouldRedraw flag
	getFlags()->shouldRedraw = shouldRedraw;

	updateCursor();
}

void Logic::setScene(SceneIndex index) {
	_runState.flag_no_entity = false;

	if (_runState.flag_draw_entities) {
		// TODO Setup screen size (0, 80)x(480x480) (is it necessary for our animations?)
		drawScene(index);
		_runState.flag_no_entity = true;
	} else {
		_runState.flag_draw_entities = true;
		drawScene(index);
		_runState.flag_draw_entities = false;
	}
}

void Logic::drawScene(SceneIndex index) {

	//////////////////////////////////////////////////////////////////////////
	// Preprocess
	preProcessScene(&index);

	//////////////////////////////////////////////////////////////////////////
	// Draw background
	debugC(9, kLastExpressDebugScenes, "== Drawing scene: %d ==", index);

	// Update scene
	delete _currentScene;
	_currentScene = _engine->getSceneManager()->getScene(index);
	_engine->getGraphicsManager()->draw(_currentScene, GraphicsManager::kBackgroundC, true);
	getState()->scene = index;

	//////////////////////////////////////////////////////////////////////////
	// Update entities
	Scene *scene = (getState()->sceneUseBackup ? _engine->getSceneManager()->getScene(getState()->sceneBackup) : _currentScene);

	getEntityData(kEntityNone)->field_491 = (EntityData::Field491Value)scene->getHeader()->count;
	getEntityData(kEntityNone)->car = (CarIndex)scene->getHeader()->car;

	// If we used the backup scene, we don't need the scene object anymore beyond this point
	if (getState()->sceneUseBackup)
		delete scene;

	getFlags()->flag_3 = true;

	if (getFlags()->gameRunning) {
		getSavePoints()->pushAll(kEntityNone, kAction17);
		getSavePoints()->process();

		if (_runState.flag_no_entity)
			return;

		getEntities()->updateFields();
		getEntities()->setupSequences();
		getEntities()->setupCallbacks();
	}

	//////////////////////////////////////////////////////////////////////////
	// Show the scene
	askForRedraw();
	_engine->getGraphicsManager()->update();
	_engine->_system->updateScreen();

	////////////////////////////////////////////////////////////
	// Post process scene
	postProcessScene();
}

void Logic::processScene() {
	if (!getState()->sceneUseBackup) {
		loadScene(getState()->scene);
		return;
	}

	getState()->sceneUseBackup = false;

	// Select item if needed
	InventoryItem item = getInventory()->getFirstExaminableItem();
	if (item && getInventory()->getSelectedItem() == item)
		getInventory()->selectItem(item);

	loadSceneObject(backup, getState()->sceneBackup);

	if (getEntities()->getPosition(backup.getHeader()->position + 100 * backup.getHeader()->car))
		loadScene(getLogic()->processIndex(getState()->sceneBackup));
	else
		loadScene(getState()->sceneBackup);
}

LastExpress::SceneIndex Logic::processIndex(SceneIndex sceneIndex) {
	error("Logic::processIndex is not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Loading Scenes from Object/Items
//////////////////////////////////////////////////////////////////////////

void Logic::loadSceneFromObject(ObjectIndex object, bool alternate) {
	if (alternate) {
		loadSceneFromPosition((object < 10 ? kCarGreenSleeping : kCarRedSleeping), 17 - (object - 1) * 2);
		return;
	}

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
		loadSceneFromPosition((object < 10 ? kCarGreenSleeping : kCarRedSleeping), 38 - (object - 1) * 2);
		break;

	case kObjectCompartment8:
	case kObjectCompartmentH:
		loadSceneFromPosition(kCarGreenSleeping, 25);
		break;
	}
}

void Logic::loadSceneFromItem(InventoryItem item) {
	if (item >= kPortraitOriginal)
		return;

	// Get the scene index from the item
	SceneIndex index = _state->getGameInventory()->getEntry(item)->scene;
	if (!index)
		return;

	if (!getState()->sceneUseBackup) {
		getState()->sceneUseBackup = true;
		getState()->sceneBackup = getState()->scene;
	}

	loadScene(index);
}

void Logic::loadSceneFromItemPosition(InventoryItem item) {
	if (item >= kPortraitOriginal)
		return;

	// Check item location
	Inventory::InventoryEntry *entry = _state->getGameInventory()->getEntry(item);
	if (!entry->location)
		return;

	// Reset location
	entry->location = kLocationNone;

	if (item != kItem3 && item != kItem5 && item != kItem7)
		return;

	// Set field value
	CarIndex car = kCarRestaurant;
	if (item == kItem5) car = kCarRedSleeping;
	if (item == kItem7) car = kCarGreenSleeping;

	if (!getEntities()->checkFields5(kEntityNone, car))
		return;

	if (getFlags()->flag_0)
		return;

	// Get current scene position
	loadSceneObject(scene, getState()->scene);
	Position position = scene.getHeader()->position;

    if (getState()->sceneUseBackup) {
		loadSceneObject(sceneBackup, getState()->sceneBackup);
		position = sceneBackup.getHeader()->position;
	}

	// Checks are different for each item
	if ((item == kItem3 && position == 56)
	 || (item == kItem5 && (position >= 23 && position <= 32))
	 || (item == kItem7 && (position == 1 || (position >= 22 && position <= 33)))) {
		if (getState()->sceneUseBackup)
			getState()->sceneBackup = getSceneIndexFromPosition(car, position);
		else
           loadSceneFromPosition(car, position);
    }

}

void Logic::loadSceneFromPosition(CarIndex car, Position position, int param3) {
	loadScene(getSceneIndexFromPosition(car, position, param3));
}

SceneIndex Logic::getSceneIndexFromPosition(CarIndex car, Position position, int param3) {

	// Probably can't happen (can we be called during cd-swap?)
	if (_engine->getSceneManager()->count() <= 1)
		return getState()->scene;

	SceneIndex index = kSceneMenu;
	loadSceneObject(firstScene, index);
	SceneHeader *header = firstScene.getHeader();

	while (header->car != car
		|| header->position != position
		|| ((param3 != -1 || header->param3) && header->param3 != param3 && header->type != Scene::kTypeItem3)) {

		// Increment index and look at the next scene
		index = (SceneIndex)(index + 1);

		// Load the next scene
		loadSceneObject(scene, index);
		header = scene.getHeader();

		if (index >= _engine->getSceneManager()->count())
			return getState()->scene;
	}

	// Process index if necessary
	loadSceneObject(scene, index);
	if (getEntities()->getPosition(100 * scene.getHeader()->car + scene.getHeader()->position))
		return processIndex(index);

	return index;
}

//////////////////////////////////////////////////////////////////////////
// Scene pre/post & hotspots
//////////////////////////////////////////////////////////////////////////
#define PROCESS_HOTSPOT_SCENE(hotspot, index) \
	SceneIndex newScene = _action->processHotspot(*hotspot); \
	if (newScene != kSceneInvalid && newScene != kSceneStopProcessing) \
		(hotspot)->scene = newScene; \
	if ((hotspot)->scene && newScene != kSceneStopProcessing) { \
		*index = (hotspot)->scene; \
		preProcessScene(index); \
	}

#define GET_ENTITY_LOCATION(scene) \
	getObjects()->get((ObjectIndex)scene.getHeader()->param1).location

#define GET_ITEM_LOCATION(scene, parameter) \
	getInventory()->getEntry((InventoryItem)scene.getHeader()->parameter)->location

void Logic::preProcessScene(SceneIndex *index) {

	// Check index validity
	if (*index == 0 || *index > 2500)
		*index = kSceneMenu;

	loadSceneObject(scene, *index);

	switch (scene.getHeader()->type) {
	case Scene::kTypeItem:
	case Scene::kTypeItem2:
	case Scene::kTypeItem3:
	case Scene::kTypeEntity:
	case Scene::kTypeEntityItem: {
		int location = 0;
		ObjectLocation location1 = kLocationNone, location2 = kLocationNone, location3 = kLocationNone;
		byte type = scene.getHeader()->type;

		// Check bounds
		if (scene.getHeader()->param1 >= ((type == Scene::kTypeEntity || type == Scene::kTypeEntityItem) ? 128 : 32))
			break;

		if (type != Scene::kTypeItem && scene.getHeader()->param2 >= 32)
			break;

		if (type == Scene::kTypeItem3 && scene.getHeader()->param3 >= 32)
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

		for (Common::Array<SceneHotspot *>::iterator it = scene.getHotspots()->begin(); it != scene.getHotspots()->end(); ++it) {

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
		if (scene.getHeader()->param1 >= 128)
			break;

		bool found = false;
		if (scene.getHotspots()->size() > 0) {
			for (Common::Array<SceneHotspot *>::iterator it = scene.getHotspots()->begin(); it != scene.getHotspots()->end(); ++it) {
				// The index might be modified by the action, so reload the scene on each iteration
				loadSceneObject(currentScene, *index);

				if (getObjects()->get((ObjectIndex)currentScene.getHeader()->param1).location2 == (*it)->location) {
					PROCESS_HOTSPOT_SCENE(*it, index);
					found = true;
				}
			}
		}

		// If the scene has no hotspot or if we haven't found a proper hotspot, use the first hotspot from the current scene
		if (!found) {
			loadSceneObject(sceneHotspot, *index);
			SceneHotspot *hotspot = sceneHotspot.getHotspot();

			PROCESS_HOTSPOT_SCENE(hotspot, index);
		}
		break;
	}

	case Scene::kType7:
	case Scene::kType8:
		if (scene.getHeader()->param1 >= 16)
			break;

		if (getEntities()->getCompartments(scene.getHeader()->param1) || getEntities()->getCompartments1(scene.getHeader()->param1)) {

			loadSceneObject(currentScene, getState()->scene);

			if ((checkPosition(getState()->scene, kCheckPositionType0) && checkPosition(*index, kCheckPositionType0) && currentScene.getHeader()->count < scene.getHeader()->count)
			 || (checkPosition(getState()->scene, kCheckPositionType1)  && checkPosition(*index, kCheckPositionType1)  && currentScene.getHeader()->count > scene.getHeader()->count)) {

				if (State::getPowerOfTwo(getEntities()->getCompartments(scene.getHeader()->param1)) != 30
				 && State::getPowerOfTwo(getEntities()->getCompartments1(scene.getHeader()->param1)) != 30 )
					getSound()->playSound(kEntityNone, "CAT1126A");

				*index = scene.getHotspot()->scene;
			} else {
				*index = scene.getHotspot(kSceneMenu)->scene;
			}

			preProcessScene(index);
		} else {
			if (scene.getHeader()->type == Scene::kType7)
				break;

			if (scene.getHeader()->param2 >= 32)
				break;

			ObjectLocation location = getInventory()->getEntry((InventoryItem)scene.getHeader()->param2)->location;
			if (!location)
				break;

			for (Common::Array<SceneHotspot *>::iterator it = scene.getHotspots()->begin(); it != scene.getHotspots()->end(); ++it) {
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

	// Sound processing
	if (getSound()->isBuffered(kEntityTables4)) {
		loadSceneObject(currentScene, *index);
		if (currentScene.getHeader()->type != Scene::kTypeReadText || currentScene.getHeader()->param1)
			getSound()->processEntry(kEntityTables4);
	}

	// Cleanup
	if (_beetle->isLoaded()) {
		loadSceneObject(currentScene, *index);
		if (currentScene.getHeader()->type != Scene::kTypeLoadBeetleSequences)
			_beetle->unload();
	}
}

void Logic::postProcessScene() {

	loadSceneObject(scene, getState()->scene);

	switch (scene.getHeader()->type) {
	case Scene::kTypeList: {

		// Adjust time
		getState()->time += (scene.getHeader()->param1 + 10) * getState()->timeDelta;
		getState()->timeTicks += (scene.getHeader()->param1 + 10);

		//// FIXME Some stuff related to menu?
		//if (!getFlags()->mouse_right_click) {
		//	while ((unknown + 4 * scene->getHeader()->param1) > unknown) {
		//		if (getFlags()->mouse_right_click)
		//			break;

		//		getSoundMgr()->unknownFunction1();
		//		// TODO Subtitle drawing function
		//	}
		//}

		SceneHotspot *hotspot = scene.getHotspot();
		if (!hotspot)
			break;

		_action->processHotspot(*hotspot);

		if (getFlags()->mouseRightClick) {
			loadSceneObject(hotspotScene, hotspot->scene);

			while (hotspotScene.getHeader()->type == Scene::kTypeList) {
				hotspot = hotspotScene.getHotspot();
				if (hotspot) {
					_action->processHotspot(*hotspot);

					// reload the scene
					_engine->getSceneManager()->loadScene(&hotspotScene, hotspot->scene);
				}
			}
		}

		EntityData::Field491Value field491 = getEntityData(kEntityNone)->field_491;
		if (getEntityData(kEntityNone)->car == kCar9 && (field491 == EntityData::kField491_4 || field491 == EntityData::kField491_3)) {
			EntityIndex entities[39];

			// Init entities
			entities[0] = kEntityNone;

			int progress = 0;

			for (uint i = 1; i < (unsigned)_entities->count(); i++) {
				CarIndex car = getEntityData((EntityIndex)i)->car;

				// FIXME doesn't make sense to test field491 twice...
				if (field491 == EntityData::kField491_4) {
					if (!(car != kCarRedSleeping || field491 <= EntityData::kField491_9270)
					 || !(car != kCarRestaurant || field491 >= EntityData::kField491_1540))
						entities[progress++] = (EntityIndex)i;
				} else {
					if (!(car != kCarGreenSleeping || field491 <= EntityData::kField491_9270)
					 || !(car != kCarRedSleeping || field491 >= EntityData::kField491_850))
						entities[progress++] = (EntityIndex)i;
				}
			}

			if (progress)
				getSound()->excuseMe((progress == 1) ? entities[0] : entities[random(progress)], 0 , 16);
		}

		if (hotspot && hotspot->scene)
			setScene(hotspot->scene);

		break;
	}

	case Scene::kTypeSavePointChapter:
		if (getProgress().field_18 == 2)
			getSavePoints()->push(kEntityNone, kEntityChapters, kAction190346110);
		break;

	case Scene::kTypeLoadBeetleSequences:
		if ((getProgress().chapter == kChapter2 || getProgress().chapter == kChapter3)
		  && getInventory()->getEntry(kItemBeetle)->location == kLocation3) {
			if (!_beetle->isLoaded())
				_beetle->load();
		}
		break;

	case Scene::kTypeGameOver:
		if (getState()->time >= kTimeGameOver || getProgress().field_18 == 4)
			break;

		getSound()->unknownGameOver();
		getSound()->playSound(kEntityTrain, "LIB050.SND", 16);

		switch (getProgress().chapter) {
		default:
			gameOver(kTimeType0, kTime0, kSceneGameOverPolice2, true);
			break;

		case kChapter1:
			gameOver(kTimeType0, kTime0, kSceneGameOverAlarm, true);
			break;

		case kChapter4:
			gameOver(kTimeType0, kTime0, kSceneGameOverAlarm2, true);
			break;
		}
		break;

	case Scene::kTypeReadText:
        _sound->readText(scene.getHeader()->param1);
		break;

	case Scene::kType133:
		if (getFlags()->flag_0) {
			getFlags()->flag_0 = false;
			getFlags()->shouldRedraw = true;
			updateCursor();
		}
		break;

	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Game over, Chapters & credits
//////////////////////////////////////////////////////////////////////////

// Handle game over
void Logic::gameOver(TimeType type, TimeValue time, SceneIndex sceneIndex, bool showScene) {

	getSound()->unknownFunction3();
	getEntities()->reset();
	getFlags()->gameRunning = false;
	getSavePoints()->reset();
	getFlags()->flag_entities_0 = true;

	if (showScene) {

		getSound()->unknownGameOver(false);

		if (sceneIndex && !getFlags()->mouseRightClick) {
			loadScene(sceneIndex);

			while (getSound()->isBuffered(kEntityTables4)) {
				if (getFlags()->mouseRightClick)
					break;

				getSound()->unknownFunction1();
			}
		}
	}

	// Show Menu
	_menu->showMenu(false, type, time);
}

void Logic::switchChapter() {
	// Original engine clears the onDisk status for the sound cache here, which we don't need

	switch(getState()->progress.chapter) {
	default:
		break;

	case kChapter1:
		getInventory()->addItem(kItemParchemin);
		getInventory()->addItem(kItemMatchBox);

		RESET_ENTITY_STATE(kEntityChapters, Chapters, setup_chapter2);
		break;

	case kChapter2:
		getInventory()->addItem(kItemScarf);

		RESET_ENTITY_STATE(kEntityChapters, Chapters, setup_chapter3);
		break;

	case kChapter3:
		getInventory()->getEntry(kItemFirebird)->location = kLocation4;
		getInventory()->getEntry(kItemFirebird)->isPresent = false;
		getInventory()->getEntry(kItem11)->location = kLocation1;
		getInventory()->addItem(kItemWhistle);
		getInventory()->addItem(kItemKey);

		RESET_ENTITY_STATE(kEntityChapters, Chapters, setup_chapter4);
		break;

	case kChapter4:
		RESET_ENTITY_STATE(kEntityChapters, Chapters, setup_chapter5);
		break;

	case kChapter5:
		playFinalSequence();
		break;
	}
}

void Logic::playFinalSequence() {
	getSound()->unknownFunction3();

	_action->playAnimation(kEventFinalSequence);
	showCredits();

	getEntities()->reset();
	getSavePoints()->reset();
	getFlags()->flag_entities_0 = true;

	showMenu(true);
}

void Logic::showCredits() {
	error("Logic::showCredits: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Misc
//////////////////////////////////////////////////////////////////////////
void Logic::updateDoorsAndClock() {
	warning("Logic::updateDoorsAndClock: not implemented!");
}

void Logic::updateCursor(bool redraw) {
	warning("Logic::updateCursor: not implemented!");
}

bool Logic::checkPosition(SceneIndex index, CheckPositionType type) const {
	loadSceneObject(scene, (index ? index : getState()->scene));

	CarIndex car = (CarIndex)scene.getHeader()->car;
	Position position = scene.getHeader()->position;

	bool result = (car == kCarGreenSleeping || car == kCarRedSleeping);


	switch (type){
	default:
	case kCheckPositionType0:
		return result && (position >= 1 && position <= 19);

	case kCheckPositionType1:
		return result && (position >= 21 && position <= 40);

	case kCheckPositionType2:
		return result && ((position >= 2 && position <= 17) || (position >= 23 && position <= 39));
	}
}

bool Logic::checkCurrentPosition(bool doCheckOtherCars) const {
	loadSceneObject(scene, getState()->scene);

	Position position = scene.getHeader()->position;
	CarIndex car = (CarIndex)scene.getHeader()->car;

	if (!doCheckOtherCars)
		return (car == kCarGreenSleeping || car == kCarRedSleeping)
		   && ((position >= 41 && position <= 48) || (position >= 51 && position <= 58));

	if (position == 99)
		return true;

	switch (car){
	default:
		break;

	case kCarGreenSleeping:
	case kCarRedSleeping:
	case kCarLocomotive:
		if ((position >= 1 && position <= 18) || (position >= 22 && position <= 40))
			return true;
		break;

	case kCarRestaurant:
		if (position >= 73 && position <= 80)
			return true;

		if (position == 10 || position == 11)
			return true;

		break;

	case kCarBaggage:
		switch (position) {
		default:
			break;

		case 10:
		case 11:
		case 80:
		case 81:
		case 82:
		case 83:
		case 84:
		case 90:
		case 91:
			return true;
		}
		break;

	case kCarCoalTender:
		if (position == 2 || position == 10 || position == 11)
			return true;
		break;
	}

	return false;
}

} // End of namespace LastExpress
