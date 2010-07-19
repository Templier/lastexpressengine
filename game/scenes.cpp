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
	_flagNoEntity(false), _flagDrawEntities(false), _flagDrawSequences(false), _flagCoordinates(false),
	_clockHours(NULL), _clockMinutes(NULL), _hoursIndex(0), _minutesIndex(0) {
	_sceneLoader = new SceneLoader();
}

SceneManager::~SceneManager() {
	_currentScene = NULL; /* part of cache */
	delete _sceneLoader;

	// Clear sequences
	for (int i = 0; i < (int)_doors.size(); i++)
		delete _doors[i];

	_doors.clear();

	SAFE_DELETE(_clockHours);
	SAFE_DELETE(_clockMinutes);

	// Zero-out passed pointers
	_engine = NULL;
}

//////////////////////////////////////////////////////////////////////////
// Scene cache
//////////////////////////////////////////////////////////////////////////
void SceneManager::loadSceneDataFile(ArchiveIndex archive) {
	// Demo only has CD2TRAIN.DAT file
	if (_engine->isDemo())
		archive = kArchiveCd2;

	switch(archive) {
	case kArchiveCd1:
	case kArchiveCd2:
	case kArchiveCd3:
		if (!_sceneLoader->load(getArchive(Common::String::printf("CD%iTRAIN.DAT", archive))))
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
		Scene *scene = getScenes()->get(index);

		if (scene->param3 != 255) {
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

	if (getFlags()->isGameRunning && getFlags()->shouldDrawEggOrHourGlass)
		getInventory()->drawEgg();

	getFlags()->shouldRedraw = shouldRedraw;

	getLogic()->updateCursor();
}

void SceneManager::loadSceneFromObject(ObjectIndex object, bool alternate) {
	if (alternate) {
		loadSceneFromPosition((object < kObject10 ? kCarGreenSleeping : kCarRedSleeping), (Position)(17 - (object - 1) * 2));
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
		loadSceneFromPosition((object < kObject10 ? kCarGreenSleeping : kCarRedSleeping), (Position)(38 - (object - 1) * 2));
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
	Scene *scene = getScenes()->get(getState()->scene);
	Position position = scene->position;

    if (getState()->sceneUseBackup) {
		Scene *sceneBackup = getScenes()->get(getState()->sceneBackup);
		position = sceneBackup->position;
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
		drawScene(index);
		_flagNoEntity = true;
	} else {
		_flagDrawEntities = true;
		drawScene(index);
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
	_currentScene = get(index);
	_engine->getGraphicsManager()->draw(_currentScene, GraphicsManager::kBackgroundC, true);
	getState()->scene = index;

	//////////////////////////////////////////////////////////////////////////
	// Update entities
	Scene *scene = (getState()->sceneUseBackup ? get(getState()->sceneBackup) : _currentScene);

	getEntityData(kEntityNone)->entityPosition = (EntityPosition)scene->count;
	getEntityData(kEntityNone)->car = scene->car;

	getFlags()->flag_3 = true;

	if (getFlags()->isGameRunning) {
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

	Scene *backup = getScenes()->get(getState()->sceneBackup);

	if (getEntities()->getPosition(backup->car, backup->position))
		loadScene(processIndex(getState()->sceneBackup));
	else
		loadScene(getState()->sceneBackup);
}

LastExpress::SceneIndex SceneManager::processIndex(SceneIndex index) {
	Scene *scene = get(index);
	CarIndex car = scene->car;

	switch (car) {
	default:
		break;

	case kCarRedSleeping:
		if (checkPosition(index, kCheckPositionLookingAtDoors)) {
			Position position = (Position)(scene->position + (checkPosition(kSceneNone, kCheckPositionType0) ? -1 : 1));

			if (position == 4)
				position = 3;

			if (position == 24)
				position = 25;

			if (getEntities()->getPosition(car, position))
				return index;
			else
				return getSceneIndexFromPosition(car, position);
		} else {
			switch (scene->position) {
			default:
				break;

			case 41:
			case 51:
				if (!getEntities()->getPosition(car, 39))
					return getSceneIndexFromPosition(car, 39);
				// Fallback to next case

			case 42:
			case 52:
				if (!getEntities()->getPosition(car, 14))
					return getSceneIndexFromPosition(car, 14);
				// Fallback to next case

			case 43:
			case 53:
				if (!getEntities()->getPosition(car, 35))
					return getSceneIndexFromPosition(car, 35);
				// Fallback to next case

			case 44:
			case 54:
				if (!getEntities()->getPosition(car, 10))
					return getSceneIndexFromPosition(car, 10);
				// Fallback to next case

			case 45:
			case 55:
				if (!getEntities()->getPosition(car, 32))
					return getSceneIndexFromPosition(car, 32);
				// Fallback to next case

			case 46:
			case 56:
				if (!getEntities()->getPosition(car, 7))
					return getSceneIndexFromPosition(car, 7);
				// Fallback to next case

			case 47:
			case 57:
				if (!getEntities()->getPosition(car, 27))
					return getSceneIndexFromPosition(car, 27);
				// Fallback to next case

			case 48:
			case 58:
				if (!getEntities()->getPosition(car, 2))
					return getSceneIndexFromPosition(car, 2);
				break;
			}
		}
		break;

	case kCarRestaurant:
		switch (scene->position) {
		default:
			break;

		case 52:
		case 53:
		case 54:
			if (!getEntities()->getPosition(car, 51))
				return getSceneIndexFromPosition(car, 51);
			// Fallback to next case

		case 50:
		case 56:
		case 57:
		case 58:
			if (!getEntities()->getPosition(car, 55))
				return getSceneIndexFromPosition(car, 55);
			// Fallback to next case

		case 59:
			if (!getEntities()->getPosition(car, 60))
				return getSceneIndexFromPosition(car, 60);
			// Fallback to next case

		case 60:
			if (!getEntities()->getPosition(car, 59))
				return getSceneIndexFromPosition(car, 59);
			// Fallback to next case

		case 62:
		case 63:
		case 64:
			if (!getEntities()->getPosition(car, 61))
				return getSceneIndexFromPosition(car, 61);
			// Fallback to next case

		case 66:
		case 67:
		case 68:
			if (!getEntities()->getPosition(car, 65))
				return getSceneIndexFromPosition(car, 65);
			// Fallback to next case

		case 69:
		case 71:
			if (!getEntities()->getPosition(car, 70))
				return getSceneIndexFromPosition(car, 70);
			break;
		}
		break;
	}

	return index;
}

//////////////////////////////////////////////////////////////////////////
// Checks
//////////////////////////////////////////////////////////////////////////
bool SceneManager::checkPosition(SceneIndex index, CheckPositionType type) const {
	Scene *scene = getScenes()->get((index ? index : getState()->scene));

	CarIndex car = (CarIndex)scene->car;
	Position position = scene->position;

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
	Scene *scene = getScenes()->get(getState()->scene);

	Position position = scene->position;
	CarIndex car = (CarIndex)scene->car;

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
	for (int i = 0; i < (int)_doors.size(); i++) {
		removeFromQueue(new SequenceFrame(_doors[i]));
		setCoordinates(new SequenceFrame(_doors[i]));
	}

	// Cleanup doors sequences
	_doors.clear();

	if (_clockHours) {
		removeFromQueue(new SequenceFrame(_clockHours, _hoursIndex));
		setCoordinates(new SequenceFrame(_clockHours, _hoursIndex));
	}

	if (_clockMinutes) {
		removeFromQueue(new SequenceFrame(_clockMinutes, _minutesIndex));
		setCoordinates(new SequenceFrame(_clockMinutes, _minutesIndex));
	}

	// Queue doors sequences for display
	if (checkPosition(kSceneNone, kCheckPositionLookingAtDoors)) {

		ObjectIndex firstIndex = kObjectNone;

		// Init objectIndex (or exit if not in one of the two compartment cars
		if (getEntityData(kEntityNone)->car == kCarGreenSleeping)
			firstIndex = kObjectCompartment1;
		else if (getEntityData(kEntityNone)->car == kCarRedSleeping)
			firstIndex = kObjectCompartmentA;
		else
			return;

		// Iterate over each door
		for (ObjectIndex index = firstIndex; index < (ObjectIndex)(firstIndex + 8); index = (ObjectIndex)(index + 1)) {

			// Doors is not open, nothing to do
			if (getObjects()->get(index).location != kLocation2)
				continue;

			// Load door sequence
			Scene *scene = getScenes()->get(getState()->scene);
			Common::String name = Common::String::printf("633X%c-%02d.seq", (index - firstIndex) + 65, scene->position);
			Sequence *sequence = loadSequence1(name, 255);

			// If the sequence doesn't exists, skip
			if (!sequence || !sequence->isLoaded())
				continue;

			_doors.push_back(sequence);

			// Adjust frame data and store in frame list
			SequenceFrame *frame = new SequenceFrame(sequence);
			frame->getInfo()->location = (checkPosition(kSceneNone, kCheckPositionType0) ? (firstIndex - index) - 1 : (index - firstIndex) - 8);

			// Add frame to list
			addToQueue(frame);
		}
	}

	// Queue clock sequences for display
	if (checkPosition(kSceneNone, kCheckPositionLookingAtClock)) {
		// Example scene: 349

		_clockHours = loadSequence1("SCLKH-81.seq", 255);
		_clockMinutes = loadSequence1("SCLKM-81.seq", 255);

		error("SceneManager::updateDoorsAndClock: not implemented!");

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
	if (!_flagDrawSequences)
		return;

	clearBg(GraphicsManager::kBackgroundOverlay);

	for (Common::List<SequenceFrame *>::iterator i = _queue.begin(); i != _queue.end(); ++i)
		_engine->getGraphicsManager()->draw(*i, GraphicsManager::kBackgroundOverlay);

	if (refreshScreen) {
		askForRedraw();
		redrawScreen();

		_flagDrawSequences = false;
	}
}

void SceneManager::addToQueue(SequenceFrame *frame) {
	if (!frame)
		return;

	// First check that the frame is not already in the queue
	for (Common::List<SequenceFrame *>::iterator i = _queue.begin(); i != _queue.end(); ++i) {
		if (frame->equal(*i))
			return;
	}

	debugC(8, kLastExpressDebugGraphics, "Adding frame: %s / %d", frame->getName().c_str(), frame->getFrame());

	// Set flag
	_flagDrawSequences = true;

	// Queue empty: just insert the frame
	if (_queue.empty()) {
		_queue.push_back(frame);
		return;
	}

	// Frame is closer: insert in first place
	if (frame->getInfo()->location > _queue.front()->getInfo()->location) {
		_queue.push_front(frame);
		return;
	}

	// Insert the frame in the queue based on location
	for (Common::List<SequenceFrame *>::iterator i = _queue.begin(); i != _queue.end(); ++i) {
		if (frame->getInfo()->location > _queue.front()->getInfo()->location) {
			_queue.insert(i, frame);
			return;
		}
	}

	// We are the last frame in location order, insert at the back of the queue
	_queue.push_back(frame);
}

void SceneManager::removeFromQueue(SequenceFrame /*const*/ *frame) {
	if (!frame)
		return;

	debugC(8, kLastExpressDebugGraphics, "Removing frame: %s / %d", frame->getName().c_str(), frame->getFrame());

	// Check that the frame is in the queue and remove it
	for (Common::List<SequenceFrame *>::iterator i = _queue.begin(); i != _queue.end(); ++i) {
		if (frame->equal(*i)) {			
			_queue.erase(i);
			_flagDrawSequences = true;
			break;
		}
	}
}

void SceneManager::removeAndRedraw(SequenceFrame **frame, bool doRedraw) {
	if (!frame)
		return;

	removeFromQueue(*frame);

	if (doRedraw)
		drawFrames(true);

	SAFE_DELETE(*frame);
}

void SceneManager::resetQueue() {
	_flagDrawSequences = true;

	// The original engine only deletes decompressed data, not the "sequences" since they are just pointers to a memory pool
	_queue.clear();
}

void SceneManager::setCoordinates(SequenceFrame *frame) {
	warning("SceneManager::setCoordinates - Not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Helpers
//////////////////////////////////////////////////////////////////////////
SceneIndex SceneManager::getSceneIndexFromPosition(CarIndex car, Position position, int param3) {
	// Probably can't happen (can we be called during cd-swap?)
	if (_sceneLoader->count() <= 1)
		return getState()->scene;

	SceneIndex index = kSceneMenu;

	Scene *firstScene = getScenes()->get(index);

	while (firstScene->car != car
		|| firstScene->position != position
		|| ((param3 != -1 || firstScene->param3) && firstScene->param3 != param3 && firstScene->type != Scene::kTypeItem3)) {

		// Increment index and look at the next scene
		index = (SceneIndex)(index + 1);

		// Load the next scene
		firstScene = getScenes()->get(index);

		if (index >= _sceneLoader->count())
			return getState()->scene;
	}

	// Process index if necessary
	Scene *scene = getScenes()->get(index);
	if (getEntities()->getPosition(scene->car, scene->position))
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
	getObjects()->get((ObjectIndex)scene->param1).location

#define GET_ITEM_LOCATION(scene, parameter) \
	getInventory()->getEntry((InventoryItem)scene->parameter)->location

void SceneManager::preProcessScene(SceneIndex *index) {

	// Check index validity
	if (*index == 0 || *index > 2500)
		*index = kSceneMenu;

	Scene *scene = getScenes()->get(*index);

	switch (scene->type) {
	case Scene::kTypeItem:
	case Scene::kTypeItem2:
	case Scene::kTypeItem3:
	case Scene::kTypeEntity:
	case Scene::kTypeEntityItem: {
		int location = 0;
		ObjectLocation location1 = kLocationNone, location2 = kLocationNone, location3 = kLocationNone;
		byte type = scene->type;

		// Check bounds
		if (scene->param1 >= ((type == Scene::kTypeEntity || type == Scene::kTypeEntityItem) ? 128 : 32))
			break;

		if (type != Scene::kTypeItem && scene->param2 >= 32)
			break;

		if (type == Scene::kTypeItem3 && scene->param3 >= 32)
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
		if (scene->param1 >= 128)
			break;

		bool found = false;
		if (scene->getHotspots()->size() > 0) {
			for (Common::Array<SceneHotspot *>::iterator it = scene->getHotspots()->begin(); it != scene->getHotspots()->end(); ++it) {
				// The index might be modified by the action, so reload the scene on each iteration
				Scene *currentScene = getScenes()->get(*index);

				if (getObjects()->get((ObjectIndex)currentScene->param1).location2 == (*it)->location) {
					PROCESS_HOTSPOT_SCENE(*it, index);
					found = true;
				}
			}
		}

		// If the scene has no hotspot or if we haven't found a proper hotspot, use the first hotspot from the current scene
		if (!found) {
			Scene *sceneHotspot = getScenes()->get(*index);
			SceneHotspot *hotspot = sceneHotspot->getHotspot();

			PROCESS_HOTSPOT_SCENE(hotspot, index);
		}
		break;
	}

	case Scene::kType7:
	case Scene::kType8:
		if (scene->param1 >= 16)
			break;

		if (getEntities()->getCompartments(scene->param1) || getEntities()->getCompartments1(scene->param1)) {

			Scene *currentScene = getScenes()->get(getState()->scene);

			if ((checkPosition(getState()->scene, kCheckPositionType0) && checkPosition(*index, kCheckPositionType0) && currentScene->count < scene->count)
			 || (checkPosition(getState()->scene, kCheckPositionType1)  && checkPosition(*index, kCheckPositionType1)  && currentScene->count > scene->count)) {

				if (State::getPowerOfTwo((uint32)getEntities()->getCompartments(scene->param1)) != 30
				 && State::getPowerOfTwo((uint32)getEntities()->getCompartments1(scene->param1)) != 30 )
					getSound()->playSound(kEntityNone, "CAT1126A");

				*index = scene->getHotspot()->scene;
			} else {
				*index = scene->getHotspot(1)->scene;
			}

			preProcessScene(index);
		} else {
			if (scene->type == Scene::kType7)
				break;

			if (scene->param2 >= 32)
				break;

			ObjectLocation location = getInventory()->getEntry((InventoryItem)scene->param2)->location;
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

	// Sound processing
	if (getSound()->isBuffered(kEntityTables4)) {
		if (getScenes()->get(*index)->type != Scene::kTypeReadText || getScenes()->get(*index)->param1)
			getSound()->processEntry(kEntityTables4);
	}

	// Cleanup
	if (getBeetle()->isLoaded()) {
		if (getScenes()->get(*index)->type != Scene::kTypeLoadBeetleSequences)
			getBeetle()->unload();
	}
}

void SceneManager::postProcessScene() {

	Scene *scene = getScenes()->get(getState()->scene);

	switch (scene->type) {
	case Scene::kTypeList: {

		// Adjust time
		getState()->time += (scene->param1 + 10) * getState()->timeDelta;
		getState()->timeTicks += (scene->param1 + 10);

		// TODO wait for a number of frames unless right mouse is clicked
		//if (!getFlags()->mouse_right_click) {
		//	while ((unknown + 4 * scene->param1) > unknown) {
		//		if (getFlags()->mouse_right_click)
		//			break;

		//		getSoundMgr()->unknownFunction1();
		//		// TODO Subtitle drawing function
		//	}
		//}

		SceneHotspot *hotspot = scene->getHotspot();
		if (!hotspot)
			break;

		getAction()->processHotspot(*hotspot);

		if (getFlags()->mouseRightClick) {
			Scene *hotspotScene = getScenes()->get(hotspot->scene);

			while (hotspotScene->type == Scene::kTypeList) {
				hotspot = hotspotScene->getHotspot();
				if (hotspot) {
					getAction()->processHotspot(*hotspot);

					// reload the scene
					hotspotScene = getScenes()->get(hotspot->scene);
				}
			}
		}

		// If several entities are there, choose one to sound "Excuse me"
		EntityPosition entityPosition = getEntityData(kEntityNone)->entityPosition;
		if (getEntityData(kEntityNone)->car == kCar9 && (entityPosition == kPosition_4 || entityPosition == kPosition_3)) {
			EntityIndex entities[39];

			// Init entities
			entities[0] = kEntityNone;

			uint progress = 0;

			for (uint i = 1; i < (unsigned)getEntities()->count(); i++) {
				CarIndex car = getEntityData((EntityIndex)i)->car;
				EntityPosition position = getEntityData((EntityIndex)i)->entityPosition;

				if (entityPosition == kPosition_4) {
					if ((car == kCarRedSleeping && position > kPosition_9270) || (car == kCarRestaurant && position < kPosition_1540))
						entities[progress++] = (EntityIndex)i;
				} else {
					if ((car == kCarGreenSleeping && position > kPosition_9270) || (car == kCarRedSleeping && position < kPosition_850))
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
			getSavePoints()->push(kEntityNone, kEntityChapters, kActionEndChapter);
		break;

	case Scene::kTypeLoadBeetleSequences:
		if ((getProgress().chapter == kChapter2 || getProgress().chapter == kChapter3)
		  && getInventory()->getEntry(kItemBeetle)->location == kLocation3) {
			if (!getBeetle()->isLoaded())
				getBeetle()->load();
		}
		break;

	case Scene::kTypeGameOver:
		if (getState()->time >= kTimeCityGalanta || getProgress().field_18 == 4)
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
        getSound()->readText(scene->param1);
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
