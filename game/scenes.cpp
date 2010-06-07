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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "lastexpress/game/scenes.h"

#include "lastexpress/data/scene.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/beetle.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

SceneManager::SceneManager(LastExpressEngine *engine) : _engine(engine), _currentScene(NULL),
	_flagNoEntity(false), _flagDrawEntities(false), _flagDrawSequences(false),
	_clockHours(NULL), _clockMinutes(NULL), _hoursIndex(0), _minutesIndex(0) {
	_sceneLoader = new SceneLoader();
}

SceneManager::~SceneManager() {
	delete _currentScene;
	delete _sceneLoader;

	for (int i = 0; i < (int)_doors.size(); i++)
		delete _doors[i];

	_doors.clear();

	SAFE_DELETE(_clockHours);
	SAFE_DELETE(_clockMinutes);

	// Zero-out passed pointers
	_engine = NULL;
}

//////////////////////////////////////////////////////////////////////////
// DataFile
//////////////////////////////////////////////////////////////////////////
void SceneManager::loadSceneDataFile(ArchiveIndex archive) const {
	switch(archive) {
	case kArchiveCd1:
	case kArchiveCd2:
	case kArchiveCd3:
		if (!_sceneLoader->load(_engine->getResourceManager()->getFileStream(Common::String::printf("CD%iTRAIN.DAT", archive))))
			error("SceneManager::loadSceneDataFile: cannot load data file CD%iTRAIN.DAT", archive);
		break;

	default:
	case kArchiveAll:
		error("SceneManager::loadSceneDataFile: Invalid archive index (must be [1-3], was %d", archive);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Scene loading
//////////////////////////////////////////////////////////////////////////
void SceneManager::loadScene(SceneIndex index) {
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

	getFlags()->shouldRedraw = shouldRedraw;

	getLogic()->updateCursor();
}

void SceneManager::loadSceneFromObject(ObjectIndex object, bool alternate) {
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

void SceneManager::loadSceneFromItem(InventoryItem item) {
	if (item >= kPortraitOriginal)
		return;

	// Get the scene index from the item
	SceneIndex index = getInventory()->getEntry(item)->scene;
	if (!index)
		return;

	if (!getState()->sceneUseBackup) {
		getState()->sceneUseBackup = true;
		getState()->sceneBackup = getState()->scene;
	}

	loadScene(index);
}

void SceneManager::loadSceneFromPosition(CarIndex car, Position position, int param3) {
	loadScene(getSceneIndexFromPosition(car, position, param3));
}

void SceneManager::loadSceneFromItemPosition(InventoryItem item) {
	if (item >= kPortraitOriginal)
		return;

	// Check item location
	Inventory::InventoryEntry *entry = getInventory()->getEntry(item);
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

//////////////////////////////////////////////////////////////////////////
// Scene drawing & processing
//////////////////////////////////////////////////////////////////////////
void SceneManager::setScene(SceneIndex index) {
	_flagNoEntity = false;

	if (_flagDrawEntities) {
		// TODO Setup screen size (0, 80)x(480x480) (is it necessary for our animations?)
		getScenes()->drawScene(index);
		_flagNoEntity = true;
	} else {
		_flagDrawEntities = true;
		getScenes()->drawScene(index);
		_flagDrawEntities = false;
	}
}

void SceneManager::drawScene(SceneIndex index) {

	//////////////////////////////////////////////////////////////////////////
	// Preprocess
	preProcessScene(&index);

	//////////////////////////////////////////////////////////////////////////
	// Draw background
	debugC(9, kLastExpressDebugScenes, "== Drawing scene: %d ==", index);

	// Update scene
	delete _currentScene;
	_currentScene = getScene(index);
	_engine->getGraphicsManager()->draw(_currentScene, GraphicsManager::kBackgroundC, true);
	getState()->scene = index;

	//////////////////////////////////////////////////////////////////////////
	// Update entities
	Scene *scene = (getState()->sceneUseBackup ? getScene(getState()->sceneBackup) : _currentScene);

	getEntityData(kEntityNone)->field_491 = (EntityData::Field491Value)scene->getHeader()->count;
	getEntityData(kEntityNone)->car = (CarIndex)scene->getHeader()->car;

	// If we used the backup scene, we don't need the scene object anymore beyond this point
	if (getState()->sceneUseBackup)
		delete scene;

	getFlags()->flag_3 = true;

	if (getFlags()->gameRunning) {
		getSavePoints()->pushAll(kEntityNone, kAction17);
		getSavePoints()->process();

		if (_flagNoEntity)
			return;

		getEntities()->updateFields();
		getEntities()->updateSequences();
		getEntities()->updateCallbacks();
	}

	//////////////////////////////////////////////////////////////////////////
	// Show the scene
	askForRedraw();
	redrawScreen();

	////////////////////////////////////////////////////////////
	// Post process scene
	postProcessScene();
}

void SceneManager::processScene() {
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
		loadScene(processIndex(getState()->sceneBackup));
	else
		loadScene(getState()->sceneBackup);
}

LastExpress::SceneIndex SceneManager::processIndex(SceneIndex sceneIndex) {
	error("SceneManager::processIndex is not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Checks
//////////////////////////////////////////////////////////////////////////
bool SceneManager::checkPosition(SceneIndex index, CheckPositionType type) const {
	loadSceneObject(scene, (index ? index : getState()->scene));

	CarIndex car = (CarIndex)scene.getHeader()->car;
	Position position = scene.getHeader()->position;

	bool isInSleepingCar = (car == kCarGreenSleeping || car == kCarRedSleeping);

	switch (type) {
	default:
		error("SceneManager::checkPosition: Invalid position type: %d", type);

	case kCheckPositionType0:
		return isInSleepingCar && (position >= 1 && position <= 19);

	case kCheckPositionType1:
		return isInSleepingCar && (position >= 21 && position <= 40);

	case kCheckPositionLookingAtDoors:
		return isInSleepingCar && ((position >= 2 && position <= 17) || (position >= 23 && position <= 39));

	case kCheckPositionLookingAtClock:
		return car == kCarRestaurant && position == 81;
	}
}

bool SceneManager::checkCurrentPosition(bool doCheckOtherCars) const {
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

//////////////////////////////////////////////////////////////////////////
// Train
//////////////////////////////////////////////////////////////////////////
void SceneManager::updateDoorsAndClock() {
	// Clear all sequences from the list
	for (int i = 0; i < (int)_doors.size(); i++)
		removeFromList(_doors[i]);

	// Cleanup doors sequences
	_doors.clear();

	if (_clockHours)
		removeFromList(_clockHours, _hoursIndex);

	if (_clockMinutes)
		removeFromList(_clockMinutes, _minutesIndex);

	// Queue doors sequences for display
	if (checkPosition(kSceneNone, kCheckPositionLookingAtDoors)) {

		//ObjectIndex objectIndex = getEntityData(kEntityNone)->car == kCarGreenSleeping ?  kObjectCompartment1 : kObjectCompartmentA;

		// Iterate over locations
		//if (getObjects()->get(objectIndex)->location != kLocation2)
		//	continue;
	}

	// Queue clock sequences for display
	if (checkPosition(kSceneNone, kCheckPositionLookingAtClock)) {
		// Example scene: 349

		_clockHours = newSequence(Common::String::printf("SCLKH-81.seq"));
		_clockMinutes = newSequence(Common::String::printf("SCLKM-81.seq"));

		// Compute hours and minutes indexes


		// Adjust z-order and store sequences to list



	}
}

void SceneManager::resetDoorsAndClock() {
	for (int i = 0; i < (int)_doors.size(); i++)
		delete _doors[i];

	_doors.clear();

	SAFE_DELETE(_clockHours);
	SAFE_DELETE(_clockMinutes);

	// Remove the beetle sequences too if needed
	getBeetle()->unload();
}

//////////////////////////////////////////////////////////////////////////
// Sequence list
//////////////////////////////////////////////////////////////////////////
void SceneManager::drawFrames(bool refreshScreen) {
	error("SceneManager::drawFrames - Not implemented!");
}

void SceneManager::addToList(Sequence *sequence, uint32 frameIndex) {
	error("SceneManager::addToList - Not implemented!");
}

void SceneManager::removeFromList(Sequence *sequence, uint32 frameIndex) {
	error("SceneManager::removeFromList - Not implemented!");
}

void SceneManager::removeSequenceAndRedraw(Sequence *sequence, bool doRedraw, uint32 frameIndex) {
	if (!sequence)
		return;

	removeFromList(sequence, frameIndex);

	if (doRedraw)
		drawFrames(true);
}

void SceneManager::resetList() {
	_flagDrawSequences = true;

	// The original engine only deletes decompressed data, not the "sequences" since they are just pointers to a memory pool
	_list.clear();
}

//////////////////////////////////////////////////////////////////////////
// Helpers
//////////////////////////////////////////////////////////////////////////
bool SceneManager::loadScene(Scene * const scene, SceneIndex sceneIndex) {
	return _sceneLoader->loadScene(scene, sceneIndex);
}

Scene *SceneManager::getScene(SceneIndex sceneIndex) {
	return _sceneLoader->getScene(sceneIndex);
}


SceneIndex SceneManager::getSceneIndexFromPosition(CarIndex car, Position position, int param3) {
	// Probably can't happen (can we be called during cd-swap?)
	if (_sceneLoader->count() <= 1)
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

		if (index >= _sceneLoader->count())
			return getState()->scene;
	}

	// Process index if necessary
	loadSceneObject(scene, index);
	if (getEntities()->getPosition(100 * scene.getHeader()->car + scene.getHeader()->position))
		return processIndex(index);

	return index;
}

//////////////////////////////////////////////////////////////////////////
// Scene processing
//////////////////////////////////////////////////////////////////////////
#define PROCESS_HOTSPOT_SCENE(hotspot, index) \
	SceneIndex newScene = getAction()->processHotspot(*hotspot); \
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

void SceneManager::preProcessScene(SceneIndex *index) {

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
	if (getBeetle()->isLoaded()) {
		loadSceneObject(currentScene, *index);
		if (currentScene.getHeader()->type != Scene::kTypeLoadBeetleSequences)
			getBeetle()->unload();
	}
}

void SceneManager::postProcessScene() {

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

		getAction()->processHotspot(*hotspot);

		if (getFlags()->mouseRightClick) {
			loadSceneObject(hotspotScene, hotspot->scene);

			while (hotspotScene.getHeader()->type == Scene::kTypeList) {
				hotspot = hotspotScene.getHotspot();
				if (hotspot) {
					getAction()->processHotspot(*hotspot);

					// reload the scene
					loadScene(&hotspotScene, hotspot->scene);
				}
			}
		}

		EntityData::Field491Value field491 = getEntityData(kEntityNone)->field_491;
		if (getEntityData(kEntityNone)->car == kCar9 && (field491 == EntityData::kField491_4 || field491 == EntityData::kField491_3)) {
			EntityIndex entities[39];

			// Init entities
			entities[0] = kEntityNone;

			int progress = 0;

			for (uint i = 1; i < (unsigned)getEntities()->count(); i++) {
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
			if (!getBeetle()->isLoaded())
				getBeetle()->load();
		}
		break;

	case Scene::kTypeGameOver:
		if (getState()->time >= kTimeGameOver || getProgress().field_18 == 4)
			break;

		getSound()->unknownGameOver();
		getSound()->playSound(kEntityTrain, "LIB050.SND", 16);

		switch (getProgress().chapter) {
		default:
			getLogic()->gameOver(kTimeType0, kTime0, kSceneGameOverPolice2, true);
			break;

		case kChapter1:
			getLogic()->gameOver(kTimeType0, kTime0, kSceneGameOverAlarm, true);
			break;

		case kChapter4:
			getLogic()->gameOver(kTimeType0, kTime0, kSceneGameOverAlarm2, true);
			break;
		}
		break;

	case Scene::kTypeReadText:
        getSound()->readText(scene.getHeader()->param1);
		break;

	case Scene::kType133:
		if (getFlags()->flag_0) {
			getFlags()->flag_0 = false;
			getFlags()->shouldRedraw = true;
			getLogic()->updateCursor();
		}
		break;

	default:
		break;
	}
}

} // End of namespace LastExpress
