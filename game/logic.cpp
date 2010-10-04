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
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

#define EVENT_TICKS_BEETWEEN_SAVEGAMES 450
#define GAME_TICKS_BEETWEEN_SAVEGAMES 2700

Logic::Logic(LastExpressEngine *engine) : _engine(engine) {
	_action   = new Action(engine);
	_beetle   = new Beetle(engine);
	_entities = new Entities(engine);
	_fight    = new Fight(engine);
	_saveload = new SaveLoad(engine);
	_state    = new State(engine);

	// Flags
	_flagActionPerformed = false;
	_ignoreFrameInterval = false;
	_ticksSinceLastSavegame = EVENT_TICKS_BEETWEEN_SAVEGAMES;
}

Logic::~Logic() {
	delete _action;
	delete _beetle;
	delete _fight;
	delete _entities;
	delete _saveload;
	delete _state;

	// Zero-out passed pointers
	_engine = NULL;
}

//////////////////////////////////////////////////////////////////////////
// Event Handling
//////////////////////////////////////////////////////////////////////////
#define REDRAW_CURSOR() { \
	if (getInventory()->isMagnifierInUse()) \
		_engine->getCursor()->setStyle(kCursorMagnifier); \
	if (getInventory()->isFlag1() \
	|| getInventory()->isFlag2() \
	|| getInventory()->isEggHighlighted()) \
		_engine->getCursor()->setStyle(kCursorNormal); \
	return; \
}

void Logic::eventMouse(const Common::Event &ev) {
	bool hotspotHandled = false;

	// Reset mouse flags
	getFlags()->mouseLeftClick = false;
	getFlags()->mouseRightClick = false;

	// Process event flags
	if (ev.type == Common::EVENT_LBUTTONUP) {

		if (getFlags()->frameInterval)
			_ignoreFrameInterval = false;

		getFlags()->frameInterval = false;
	}

	if (getFlags()->flag_0) {
		if (ev.type == Common::EVENT_LBUTTONUP || ev.type == Common::EVENT_RBUTTONUP) {
			getFlags()->flag_0 = false;
			getFlags()->shouldRedraw = true;
			updateCursor(true);
			getFlags()->frameInterval = true;
		}
		return;
	}

	if (_ignoreFrameInterval && getScenes()->checkCurrentPosition(true) && _engine->getCursor()->getStyle() == kCursorForward) {
		getFlags()->shouldRedraw = false;
		getFlags()->flag_0 = true;
		return;
	}

	// Update coordinates
	getGameState()->setCoordinates(ev.mouse);

	// Handle inventory
	getInventory()->handleMouseEvent(ev);

	// Stop processing is inside the menu
	if (getMenu()->isShown())
		return;

	// Handle whistle case
	if (getInventory()->getSelectedItem() == kItemWhistle
	 && !getProgress().isEggOpen
	 && !getEntities()->isPlayerPosition(kCarGreenSleeping, 59)
	 && !getEntities()->isPlayerPosition(kCarGreenSleeping, 76)
	 && !getInventory()->isFlag1()
	 && !getInventory()->isFlag2()
	 && !getInventory()->isEggHighlighted()
	 && !getInventory()->isMagnifierInUse()) {

		 // Update cursor
		_engine->getCursor()->setStyle(getInventory()->get(kItemWhistle)->cursor);

		// Check if clicked
		if (ev.type == Common::EVENT_LBUTTONUP && !getSound()->isBuffered("LIB045")) {

			getSound()->playSoundEvent(kEntityPlayer, 45);

			if (getEntities()->isPlayerPosition(kCarGreenSleeping, 26) || getEntities()->isPlayerPosition(kCarGreenSleeping, 25) || getEntities()->isPlayerPosition(kCarGreenSleeping, 23)) {
				getSavePoints()->push(kEntityPlayer, kEntityMertens, kAction226078300);
			} else if (getEntities()->isPlayerPosition(kCarRedSleeping, 26) || getEntities()->isPlayerPosition(kCarRedSleeping, 25) || getEntities()->isPlayerPosition(kCarRedSleeping, 23)) {
				getSavePoints()->push(kEntityPlayer, kEntityCoudert, kAction226078300);
			}

			if (!getState()->sceneUseBackup)
				getInventory()->unselectItem();
		}

		REDRAW_CURSOR()
	}

	// Handle match case
	if (getInventory()->getSelectedItem() == kItemMatch
	 && (getEntities()->isPlayerInCar(kCarGreenSleeping) || getEntities()->isPlayerInCar(kCarRedSleeping))
	 && getProgress().jacket == kJacketGreen
	 && !getInventory()->isFlag1()
	 && !getInventory()->isFlag2()
	 && !getInventory()->isEggHighlighted()
	 && !getInventory()->isMagnifierInUse()
	 && (getInventory()->get(kItem2)->location == kObjectLocationNone || getEntityData(kEntityPlayer)->car != kCarRedSleeping || getEntityData(kEntityPlayer)->entityPosition != kPosition_2300)) {

		// Update cursor
		_engine->getCursor()->setStyle(getInventory()->get(kItemMatch)->cursor);

		if (ev.type == Common::EVENT_LBUTTONUP) {

			getAction()->playAnimation(isNight() ? kEventCathSmokeNight : kEventCathSmokeDay);

			if (!getState()->sceneUseBackup)
				getInventory()->unselectItem();

			getScenes()->processScene();
		}

		REDRAW_CURSOR()
	}

	// Handle entity item case
	EntityIndex entityIndex = getEntities()->canInteractWith(ev.mouse);
	if (entityIndex
	 && !getInventory()->isFlag1()
	 && !getInventory()->isFlag2()
	 && !getInventory()->isEggHighlighted()
	 && !getInventory()->isMagnifierInUse()) {

		InventoryItem item = getEntityData(entityIndex)->inventoryItem;
		if (getInventory()->hasItem((InventoryItem)(item & kItemToggleHigh))) {
			hotspotHandled = true;

			_engine->getCursor()->setStyle(getInventory()->get((InventoryItem)(item & kItemToggleHigh))->cursor);

			if (ev.type == Common::EVENT_LBUTTONUP)
				getSavePoints()->push(kEntityPlayer, entityIndex, kAction1, (InventoryItem)(item & kItemToggleHigh));
		} else if ((InventoryItem)(item & kItemInvalid)) {
			hotspotHandled = true;

			_engine->getCursor()->setStyle(kCursorTalk2);

			if (ev.type == Common::EVENT_LBUTTONUP)
				getSavePoints()->push(kEntityPlayer, entityIndex, kAction1, kCursorNormal);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Handle standard actions
	if (hotspotHandled || getInventory()->isFlag1() || getInventory()->isFlag2() || getInventory()->isEggHighlighted())
		return;

	// Magnifier in use
	if (getInventory()->isMagnifierInUse()) {
		_engine->getCursor()->setStyle(kCursorMagnifier);

		if (getInventory()->isFlag1()
		 || getInventory()->isFlag2()
		 || getInventory()->isEggHighlighted())
			_engine->getCursor()->setStyle(kCursorNormal);

		return;
	}

	// Check hotspots
	int location = 0;
	SceneHotspot *hotspot = NULL;
	Scene *scene = getScenes()->get(getState()->scene);

	for (Common::Array<SceneHotspot *>::iterator it = scene->getHotspots()->begin(); it != scene->getHotspots()->end(); ++it) {
		if (!(*it)->isInside(ev.mouse))
			continue;

		if ((*it)->location < location)
			continue;

		if (!getAction()->getCursor(**it))
			continue;

		Scene *hotspotScene = getScenes()->get((*it)->scene);

		if (!getEntities()->getPosition(hotspotScene->car, hotspotScene->position)
		 || (*it)->cursor == kCursorTurnRight
		 || (*it)->cursor == kCursorTurnLeft) {
			 location = (*it)->location;
			 hotspot = *it;
		}
	}

	// No hotspot found: show the normal cursor
	if (!hotspot) {
		_engine->getCursor()->setStyle(kCursorNormal);
		return;
	}

	// Found an hotspot: update the cursor and perform the action if the user clicked the mouse
	_engine->getCursor()->setStyle(getAction()->getCursor(*hotspot));

	if (ev.type != Common::EVENT_LBUTTONUP || _flagActionPerformed)
		return;

	_flagActionPerformed = true;

	SceneIndex processedScene = getAction()->processHotspot(*hotspot);
	SceneIndex testScene = (processedScene == kSceneInvalid) ? hotspot->scene : processedScene;

	if (testScene) {
		getFlags()->shouldRedraw = false;

		getScenes()->setScene(testScene);

		if (getFlags()->shouldDrawEggOrHourGlass)
			getInventory()->drawEgg();

		getFlags()->shouldRedraw = true;
		updateCursor(true);
	}

	// Switch to next chapter if necessary
	if (hotspot->action == SceneHotspot::kActionSwitchChapter && hotspot->param1 == getState()->progress.chapter)
		switchChapter();
}

void Logic::eventTick(const Common::Event &) {
	uint ticks = 1;

	//////////////////////////////////////////////////////////////////////////
	// Adjust ticks if an action has been performed
	if (_flagActionPerformed)
		ticks = 10;

	_flagActionPerformed = false;

	//////////////////////////////////////////////////////////////////////////
	// Draw the blinking egg if needed
	if (getGlobalTimer() && !getFlags()->shouldDrawEggOrHourGlass)
		getInventory()->drawBlinkingEgg();

	//////////////////////////////////////////////////////////////////////////
	// Adjust time and save game if needed
	if (getFlags()->isGameRunning) {
		getState()->timeTicks += ticks;
		getState()->time += ticks * getState()->timeDelta;

		if (getState()->timeDelta) {

			// Auto-save
			if (!_ticksSinceLastSavegame) {
				_ticksSinceLastSavegame = EVENT_TICKS_BEETWEEN_SAVEGAMES;
				getSaveLoad()->saveGame(kSavegameTypeAuto, kEntityChapters, kEventNone);
			}

			// Save after game ticks interval
			if ((getState()->timeTicks - getSaveLoad()->getLastSavegameTicks()) > GAME_TICKS_BEETWEEN_SAVEGAMES)
				getSaveLoad()->saveGame(kSavegameTypeTickInterval, kEntityChapters, kEventNone);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Load scene and process hotspot
	if (getFlags()->flag_0 && !getFlags()->mouseLeftClick && !getFlags()->mouseRightClick) {
		Scene *scene = getScenes()->get(getState()->scene);

		if (getScenes()->checkCurrentPosition(true)
		&& !getEntities()->getPosition(scene->car, scene->position)) {

			// Process hotspot
			SceneHotspot *hotspot = scene->getHotspot();
			SceneIndex processedScene = getAction()->processHotspot(*hotspot);
			SceneIndex testScene = (processedScene == kSceneInvalid) ? hotspot->scene : processedScene;

			if (testScene) {
				getScenes()->setScene(testScene);
			} else {
				getFlags()->flag_0 = false;
				getFlags()->shouldRedraw = true;
				updateCursor(true);
			}

			if (getFlags()->isGameRunning)
				getSavePoints()->callAndProcess();

		} else {
			getFlags()->flag_0 = false;
			getFlags()->shouldRedraw = true;
			updateCursor(true);
		}

		return;
	}

	// Stop processing if the game is paused
	if (!getFlags()->isGameRunning)
		return;

	//////////////////////////////////////////////////////////////////////////
	// Update beetle, savepoints, entities and draw frames
	if (_beetle->isLoaded())
		_beetle->update();

	getSavePoints()->callAndProcess();
	getEntities()->updateCallbacks();
	getScenes()->drawFrames(true);

	//////////////////////////////////////////////////////////////////////////
	// Update cursor if we can interact with an entity
	EntityIndex entity = getEntities()->canInteractWith(getCoords());
	if (!entity) {
		if (_engine->getCursor()->getStyle() >= kCursorTalk2)
			updateCursor(false);

		return;
	}

	// Show item cursor on entity
	if (getInventory()->hasItem((InventoryItem)(getEntityData(entity)->inventoryItem & kItemToggleHigh)) && (int)getEntityData(entity)->inventoryItem != (int)kCursorTalk2) {
		_engine->getCursor()->setStyle(getInventory()->get((InventoryItem)(getEntityData(entity)->inventoryItem & kItemToggleHigh))->cursor);
		return;
	}

	getLogic()->updateCursor(false);
	_engine->getCursor()->setStyle(kCursorTalk2);
}

//////////////////////////////////////////////////////////////////////////
// Game over, Chapters & credits
//////////////////////////////////////////////////////////////////////////

// Handle game over
void Logic::gameOver(SavegameType type, uint32 value, SceneIndex sceneIndex, bool showScene) const {

	getSound()->processEntries();
	getEntities()->reset();
	getFlags()->isGameRunning = false;
	getSavePoints()->reset();
	getFlags()->flag_entities_0 = true;

	if (showScene) {

		getSound()->processEntry(SoundManager::kSoundType11);

		if (sceneIndex && !getFlags()->mouseRightClick) {
			getScenes()->loadScene(sceneIndex);

			while (getSound()->isBuffered(kEntityTables4)) {
				if (getFlags()->mouseRightClick)
					break;

				getSound()->updateQueue();
			}
		}
	}

	// Show Menu
	getMenu()->show(false, type, value);
}

void Logic::switchChapter() const {
	getSound()->clearStatus();

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
		getInventory()->get(kItemFirebird)->location = kObjectLocation4;
		getInventory()->get(kItemFirebird)->isPresent = false;
		getInventory()->get(kItem11)->location = kObjectLocation1;
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

void Logic::playFinalSequence() const {
	getSound()->processEntries();

	_action->playAnimation(kEventFinalSequence);
	showCredits();

	getEntities()->reset();
	getSavePoints()->reset();
	getFlags()->flag_entities_0 = true;

	getMenu()->show(false, kSavegameTypeIndex, 0);
}

void Logic::showCredits() const {
	error("Logic::showCredits: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Misc
//////////////////////////////////////////////////////////////////////////
void Logic::updateCursor(bool) const { /* the cursor is always updated, even when we don't want to redraw it */
	CursorStyle style = kCursorNormal;
	bool interact = false;

	if (getInventory()->getSelectedItem() != kItemWhistle
	 || getProgress().isEggOpen
	 || getEntities()->isPlayerPosition(kCarGreenSleeping, 59)
	 || getEntities()->isPlayerPosition(kCarGreenSleeping, 76)
	 || getInventory()->isFlag1()
	 || getInventory()->isFlag2()
	 || getInventory()->isEggHighlighted()
	 || getInventory()->isMagnifierInUse()) {

		if (getInventory()->getSelectedItem() != kItemMatch
		 || (!getEntities()->isPlayerInCar(kCarGreenSleeping) && !getEntities()->isPlayerInCar(kCarRedSleeping))
		 || getProgress().jacket != kJacketGreen
		 || getInventory()->isFlag1()
		 || getInventory()->isFlag2()
		 || getInventory()->isEggHighlighted()
		 || getInventory()->isMagnifierInUse()
		 || (getInventory()->get(kItem2)->location
		  && getEntityData(kEntityPlayer)->car == kCarRedSleeping
		  && getEntityData(kEntityPlayer)->entityPosition == kPosition_2300)) {

			EntityIndex entity = getEntities()->canInteractWith(getCoords());
			if (entity
			 && !getInventory()->isFlag1()
			 && !getInventory()->isFlag2()
			 && !getInventory()->isEggHighlighted()
			 && !getInventory()->isMagnifierInUse()) {
				 if (getInventory()->hasItem((InventoryItem)(getEntityData(entity)->inventoryItem & kItemToggleHigh))) {
					 interact = true;
					 style = getInventory()->get((InventoryItem)(getEntityData(entity)->inventoryItem & kItemToggleHigh))->cursor;
				 } else if ((int)getEntityData(entity)->inventoryItem == kItemInvalid) {
					 interact = true;
					 style = kCursorTalk2;
				 }
			}

			if (!interact
			 && !getInventory()->isFlag1()
			 && !getInventory()->isFlag2()
			 && !getInventory()->isEggHighlighted()
			 && !getInventory()->isMagnifierInUse()) {
				int location = 0;
				SceneHotspot *hotspot = NULL;
				Scene *scene = getScenes()->get(getState()->scene);

				// Check all hotspots
				for (Common::Array<SceneHotspot *>::iterator i = scene->getHotspots()->begin(); i != scene->getHotspots()->end(); ++i) {
					if ((*i)->isInside(getCoords()) && (*i)->location >= location) {
						if (getAction()->getCursor(**i)) {
							Scene *hotspotScene = getScenes()->get((*i)->scene);

							if (!getEntities()->getPosition(hotspotScene->car, hotspotScene->position)
							 || (*i)->cursor == kCursorTurnRight
							 || (*i)->cursor == kCursorTurnLeft) {
								hotspot = *i;
								location = (*i)->location;
							}
						}
					}
				}

				style = (hotspot) ? getAction()->getCursor(*hotspot) : kCursorNormal;
			}
		} else {
			style = getInventory()->get(kItemMatch)->cursor;
		}

	} else {
		style = getInventory()->get(kItemWhistle)->cursor;
	}

	if (getInventory()->isMagnifierInUse())
		style = kCursorMagnifier;

	if (getInventory()->isFlag1() || getInventory()->isFlag2() || getInventory()->isEggHighlighted())
		style = kCursorNormal;

	_engine->getCursor()->setStyle(style);
}

} // End of namespace LastExpress
