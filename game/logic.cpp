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
// Game & Menu
//////////////////////////////////////////////////////////////////////////

void Logic::init() {
	// Initialize data
	getInventory()->init();

	//_entities->setup(kChapter1);

	// DEBUG
	//_engine->getMenu()->setShowStartup(false);
	//_runState.showingMenu = false;
	//getFlags()->gameRunning = true;
	//SET_EVENT_HANDLERS(Logic);

	//// Set Cursor type
	//_engine->getCursor()->setStyle(kCursorNormal);
	//_engine->getCursor()->show(true);

	//getScenes()->loadScene(kSceneDefault);

	//getInventory()->show();

	//askForRedraw();
}

//////////////////////////////////////////////////////////////////////////
// Event Handling
//////////////////////////////////////////////////////////////////////////
void Logic::eventMouse(const Common::Event &ev) {
	bool hotspotHandled = false;

	// Reset mouse flags
	getFlags()->mouseLeftClick = false;
	getFlags()->mouseRightClick = false;

	// TODO process event flags
	//warning("Logic::eventMouse: event flag processing not implemented!");

	// Update coordinates
	getGameState()->setCoordinates(ev.mouse);

	if (getInventory()->handleMouseEvent(ev))
		return;

	// Stop processing is inside the menu
	if (getMenu()->isShown())
		return;

	// TODO handle whistle case

	// TODO handle match case

	// TODO handle entity item case

	//////////////////////////////////////////////////////////////////////////
	// Handle standard actions
	if (hotspotHandled)
		return;

	// Magnifier in use
	if (getInventory()->isMagnifierInUse()) {
		_engine->getCursor()->setStyle(kCursorMagnifier);
		return;
	}

	// Check hotspots
	int location = 0;
	SceneHotspot *hotspot = NULL;
	loadSceneObject(scene, getState()->scene);

	for (Common::Array<SceneHotspot *>::iterator it = scene.getHotspots()->begin(); it != scene.getHotspots()->end(); ++it) {
		if (!(*it)->isInside(ev.mouse))
			continue;

		if ((*it)->location < location)
			continue;

		if (!getAction()->getCursor(**it))
			continue;

		loadSceneObject(hotspotScene, (*it)->scene);

		if (!getEntities()->getPosition(hotspotScene.getHeader()->car, hotspotScene.getHeader()->position)
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

	SceneIndex index = _action->processHotspot(*hotspot);
	if (index != kSceneInvalid || hotspot->scene) {
		getFlags()->shouldRedraw = false;

		getScenes()->setScene((index != kSceneInvalid && index != kSceneStopProcessing) ? index : hotspot->scene);

		if (getFlags()->shouldDrawEggOrHourGlass)
			getInventory()->drawEgg();

		getFlags()->shouldRedraw = true;
		updateCursor(true);
	}
	
	// Switch to next chapter if necessary
	if (hotspot->action == SceneHotspot::kActionSwitchChapter && hotspot->param1 == getState()->progress.chapter)
		switchChapter();
}

void Logic::eventTick(const Common::Event &ev) {
	int ticks = 1;

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
				save(kEntityChapters, kSavegameTypeAuto, kEventNone);
			}

			// Save after game ticks interval
			if (getSaveLoad()->getLastSavegameTicks() - getState()->timeTicks > GAME_TICKS_BEETWEEN_SAVEGAMES)
				save(kEntityChapters, kSavegameTypeTickInterval, kEventNone);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Load scene and process hotspot
	if (getFlags()->flag_0 && !getFlags()->mouseLeftClick && !getFlags()->mouseRightClick) {
		loadSceneObject(scene, getState()->scene);

		if (getScenes()->checkCurrentPosition(true) 
		 && scene.getHeader()->car
		 && !getEntities()->getPosition(scene.getHeader()->car, scene.getHeader()->position)) {

			// Process hotspot
			SceneHotspot *hotspot = scene.getHotspot();
			SceneIndex index = getAction()->processHotspot(*hotspot);
			if (index) {
				getScenes()->setScene(index);
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
	if (getInventory()->hasItem(getEntityData(entity)->inventoryItem) && getEntityData(entity)->inventoryItem != kCursorTalk2) {
		_engine->getCursor()->setStyle(getInventory()->getEntry(getEntityData(entity)->inventoryItem)->cursor);
		return;
	}

	getLogic()->updateCursor(false);
	_engine->getCursor()->setStyle(kCursorTalk2);
}

//////////////////////////////////////////////////////////////////////////
// Game over, Chapters & credits
//////////////////////////////////////////////////////////////////////////

// Handle game over
void Logic::gameOver(TimeType type, TimeValue time, SceneIndex sceneIndex, bool showScene) {

	getSound()->unknownFunction3();
	getEntities()->reset();
	getFlags()->isGameRunning = false;
	getSavePoints()->reset();
	getFlags()->flag_entities_0 = true;

	if (showScene) {

		getSound()->unknownGameOver(false);

		if (sceneIndex && !getFlags()->mouseRightClick) {
			getScenes()->loadScene(sceneIndex);

			while (getSound()->isBuffered(kEntityTables4)) {
				if (getFlags()->mouseRightClick)
					break;

				getSound()->unknownFunction1();
			}
		}
	}

	// Show Menu
	getMenu()->show(false, type, time);
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

	getMenu()->show(false, kTimeType0, 0);
}

void Logic::showCredits() {
	error("Logic::showCredits: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Misc
//////////////////////////////////////////////////////////////////////////
void Logic::updateCursor(bool redraw) {
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

		if (getInventory()->getSelectedItem() != kItemWhistle
		 || (!getEntities()->checkFields7(kCarGreenSleeping) && !getEntities()->checkFields7(kCarRedSleeping))
		 || getProgress().jacket != kJacketGreen
		 || getInventory()->isFlag1() 
		 || getInventory()->isFlag2() 
		 || getInventory()->isEggHighlighted()
		 || getInventory()->isMagnifierInUse()
		 || (getInventory()->getEntry(kItem2)->location 
		  && getEntityData(kEntityNone)->car == kCarRedSleeping 
		  && getEntityData(kEntityNone)->field_491 == EntityData::kField491_2300)) {

			EntityIndex entity = getEntities()->canInteractWith(getCoords());
			if (entity
			 && !getInventory()->isFlag1()
			 && !getInventory()->isFlag2()
			 && !getInventory()->isEggHighlighted()
			 && !getInventory()->isMagnifierInUse()) {
				 if (getInventory()->hasItem(getEntityData(entity)->inventoryItem)) {
					 interact = true;
					 style = getInventory()->getEntry(getEntityData(entity)->inventoryItem)->cursor;
				 } else if (getEntityData(entity)->inventoryItem == kCursorProcess) {
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
				loadSceneObject(scene, getState()->scene);

				// Check all hotspots
				for (Common::Array<SceneHotspot *>::iterator i = scene.getHotspots()->begin(); i != scene.getHotspots()->end(); ++i) {
					if ((*i)->isInside(getCoords()) && (*i)->location >= location) {
						if (getAction()->getCursor(**i)) {
							loadSceneObject(hotspotScene, (*i)->scene);

							if (!getEntities()->getPosition(hotspotScene.getHeader()->car, hotspotScene.getHeader()->position)
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
			style = getInventory()->getEntry(kItemMatch)->cursor;
		}
		
	} else {
		style = getInventory()->getEntry(kItemWhistle)->cursor;
	}

	if (getInventory()->isMagnifierInUse())
		style = kCursorMagnifier;

	if (getInventory()->isFlag1() || getInventory()->isFlag2() || getInventory()->isEggHighlighted())
		style = kCursorNormal;

	_engine->getCursor()->setStyle(style);
}



} // End of namespace LastExpress
