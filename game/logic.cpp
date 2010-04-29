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

	// DEBUG
	_menu->setShowStartup(false);
	_runState.showingMenu = false;
	getFlags()->gameRunning = true;

	// Set Cursor type
	_engine->getCursor()->setStyle(kCursorNormal);
	_engine->getCursor()->show(true);

	loadScene(kSceneDefault);

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
	_menu->showMenu(false, kTimeType0, 0);

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
void Logic::gameOver(TimeType type, uint32 time, SceneIndex sceneIndex, bool showScene)
{

	warning("Logic::gameOver: not implemented!");

	// TODO Sound call
	_entities->reset();
	//getFlags()->unkown_flag_1 = 0;
	getSavePoints()->reset();
	getFlags()->flag_entities_0 = true;

	if (showScene) {

		// Adjust luminosity
		// Loop over sound cache
		// Check if kEntityTrain is buffered
		// Call unknown function 1 and loop

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

//////////////////////////////////////////////////////////////////////////
// Event Handling
//////////////////////////////////////////////////////////////////////////
void Logic::eventMouseClick(const Common::Event &ev) {
	// Special case for the main menu scene
	if (isShowingMenu()) {
		_menu->eventMouseClick(ev);
		return;
	}

	if (getInventory()->handleMouseEvent(ev))
		return;

	// Check hitbox & event from scene data
	SceneHotspot *hotspot = NULL;
	if (_currentScene && _currentScene->checkHotSpot(ev.mouse, &hotspot) && ev.type == Common::EVENT_LBUTTONUP) {
		_action->processHotspot(hotspot);
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

	// Check hitbox & event from scene data
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

void Logic::loadScene(uint32 index) {

	getFlags()->flag_0 = false;

	// TODO update list of values for field 491

	if (getState()->sceneUseBackup) {
		loadSceneObject(scene, index);

		if (scene.getHeader()->param3 != 255) {
			getState()->sceneUseBackup = 0;
			getState()->sceneBackup2 = 0;
		}
	}

	// Save shouldRedraw state and redraw if necessary
	bool shouldRedraw = getFlags()->shouldRedraw;
	if (shouldRedraw) {
		shouldRedraw = 0;
		// TODO check whether we need to do that here
		askForRedraw();
		redrawScreen();
	}

	// Set the scene
	setScene(index);

	// TODO events

	if (getFlags()->gameRunning)
		if (getFlags()->shouldDrawEggOrHourGlass) {
			//getInventory()->drawEgg();
		}

	// Restore shouldRedraw flag
	getFlags()->shouldRedraw = shouldRedraw;

	updateCursor();
}

void Logic::setScene(uint32 index) {
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

void Logic::drawScene(uint32 index) {
	preProcessScene(&index);

	// Draw background
	delete _currentScene;
	_currentScene = _engine->getSceneManager()->getScene(index);
	_engine->getGraphicsManager()->draw(_currentScene, GraphicsManager::kBackgroundC, true);
	getState()->scene = index;

	// Update entities
	Scene *scene = (getState()->sceneUseBackup ? _engine->getSceneManager()->getScene(getState()->sceneBackup) : _currentScene);

	getEntityData(kEntityNone)->field_491 = (EntityData::Field491Value)scene->getHeader()->count;
	getEntityData(kEntityNone)->field_495 = (EntityData::Field495Value)scene->getHeader()->field_13;

	// If we used the backup scene, we don't need the scene object anymore beyond this point
	if (getState()->sceneUseBackup)
		delete scene;

	if (getFlags()->gameRunning) {
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

	postProcessScene();
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


	loadSceneObject(backup, getState()->sceneBackup);

	if (getState()->field1000[backup.getHeader()->position + 100 * backup.getHeader()->field_13])
		loadScene(getLogic()->processIndex(getState()->sceneBackup));
	else
		loadScene(getState()->sceneBackup);
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
	getObjects()->get((ObjectIndex)scene.getHeader()->param1).location

#define GET_ITEM_LOCATION(scene, parameter) \
	getInventory()->getEntry((InventoryItem)scene.getHeader()->parameter)->location

void Logic::preProcessScene(uint32 *index) {

	// Check index validity
	if (*index == 0 || *index > 2500)
		*index = 1;

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

		if (getState()->field16[scene.getHeader()->param1] || getState()->field16_2[scene.getHeader()->param1]) {

			loadSceneObject(currentScene, getState()->scene);

			if ((checkSceneFields(getState()->scene, false) && checkSceneFields(*index, false) && currentScene.getHeader()->count < scene.getHeader()->count)
			 || (checkSceneFields(getState()->scene, true)  && checkSceneFields(*index, true)  && currentScene.getHeader()->count > scene.getHeader()->count)) {

				if (State::getPowerOfTwo(getState()->field16[scene.getHeader()->param1]) != 30
				 && State::getPowerOfTwo(getState()->field16_2[scene.getHeader()->param1]) != 30 )
					getSound()->playSound(kEntityNone, "CAT1126A");

				*index = scene.getHotspot()->scene;
			} else {
				*index = scene.getHotspot(1)->scene;
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
		//if (!getFlags()->flag_2) {
		//	while ((unknown + 4 * scene->getHeader()->param1) > unknown) {
		//		if (getFlags()->flag_2)
		//			break;

		//		getSoundMgr()->unknownFunction1();
		//		// TODO Subtitle drawing function
		//	}
		//}

		SceneHotspot *hotspot = scene.getHotspot();
		_action->processHotspot(hotspot);

		if (getFlags()->mouseRightClick) {
			loadSceneObject(hotspotScene, hotspot->scene);

			while (hotspotScene.getHeader()->type == Scene::kTypeList) {
				hotspot = hotspotScene.getHotspot();
				_action->processHotspot(hotspot);

				// reload the scene
				_engine->getSceneManager()->loadScene(&hotspotScene, hotspot->scene);
			}
		}

		EntityData::Field491Value field491 = getEntityData(kEntityNone)->field_491;
		if (getEntityData(kEntityNone)->field_495 == EntityData::kField495_9 && (field491 == EntityData::kField491_4 || field491 == EntityData::kField491_3)) {
			EntityIndex entities[39];

			int progress = 0;

			for (uint i = 1; i < (unsigned)_entities->count(); i++) {
				EntityData::Field495Value field495 = getEntityData((EntityIndex)i)->field_495;

				// FIXME doesn't make sense to test field491 twice...
				if (field491 == EntityData::kField491_4) {
					if (!(field495 != EntityData::kField495_4 || field491 <= EntityData::kField491_9270)
					 || !(field495 != EntityData::kField495_5 || field491 >= EntityData::kField491_1540))
						entities[progress++] = (EntityIndex)i;
				} else {
					if (!(field495 != EntityData::kField495_3 || field491 <= EntityData::kField491_9270)
					 || !(field495 != EntityData::kField495_4 || field491 >= EntityData::kField491_850))
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

		// TODO: Sound cache handling

		playSfxStream("LIB050");
		switch (getProgress().chapter) {
		default:
			gameOver(kTimeType0, 0, kSceneGameOverPolice, true);
			break;

		case kChapter1:
			gameOver(kTimeType0, 0, kSceneGameOverAlarm, true);
			break;

		case kChapter4:
			gameOver(kTimeType0, 0, kSceneGameOverAlarm2, true);
			break;
		}
		break;

	case Scene::kTypeReadText:
		if (!getSound()->isBuffered(kEntityTables4)) {
			const char *text = _sound->readText(scene.getHeader()->param1);
			if (text)
				playSfxStream(text);
		}
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

void Logic::updateCursor(bool redraw) {
	warning("Logic::updateCursor: not implemented!");
}

bool Logic::checkSceneFields(SceneIndex index, bool isSecondCheck) const {
	bool result = false;
	loadSceneObject(scene, (index ? index : getState()->scene));

	uint16 field13 = scene.getHeader()->field_13;
	byte position = scene.getHeader()->position;

	result = (field13 == 3 || field13 == 4);

	if (!isSecondCheck)
		return result && (position >= 1 && position <= 19);

	return result && (position >= 21 && position <= 40);
}

} // End of namespace LastExpress
