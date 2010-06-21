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

Logic::Logic(LastExpressEngine *engine) : _engine(engine) {
	_action   = new Action(engine);
	_beetle   = new Beetle(engine);
	_entities = new Entities(engine);
	_fight    = new Fight(engine);
	_saveload = new SaveLoad(engine);
	_state    = new State(engine);
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

void Logic::startGame() {
	// Load scene data for the first CD
	getScenes()->loadSceneDataFile(kArchiveCd1);

	// Initialize data
	getInventory()->init();

	_entities->setup(kChapter1);

	// DEBUG
	_engine->getMenu()->setShowStartup(false);
	_runState.showingMenu = false;
	getFlags()->gameRunning = true;
	SET_EVENT_HANDLERS(Logic);

	// Set Cursor type
	_engine->getCursor()->setStyle(kCursorNormal);
	_engine->getCursor()->show(true);

	getScenes()->loadScene(kSceneDefault);

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
	getState()->scene = _engine->getMenu()->getSceneIndex();
	_engine->getMenu()->showMenu(false, kTimeType0, 0);

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
		_engine->getMenu()->eventMouseClick(ev);
		return;
	}

	if (getInventory()->handleMouseEvent(ev))
		return;

	// Check hit box & event from scene data
	SceneHotspot *hotspot = NULL;
	if (getScenes()->getCurrentScene() && getScenes()->getCurrentScene()->checkHotSpot(ev.mouse, &hotspot) && ev.type == Common::EVENT_LBUTTONUP) {
		SceneIndex scene = _action->processHotspot(*hotspot);
		if (scene != kSceneInvalid)
			hotspot->scene = scene;

		if (hotspot->scene)
			getScenes()->setScene(hotspot->scene);

		// Switch to next chapter if necessary
		if (hotspot->action == SceneHotspot::kActionSwitchChapter && hotspot->param1 == getState()->progress.chapter)
			switchChapter();
	}
}

void Logic::eventTick(const Common::Event &ev) {
	// Special case for the main menu scene
	if (isShowingMenu()) {
		_engine->getMenu()->eventTick(ev);
		return;
	}

	if (getInventory()->handleMouseEvent(ev))
		return;

	// Check hit box & event from scene data
	SceneHotspot *hotspot = NULL;
	if (getScenes()->getCurrentScene() && getScenes()->getCurrentScene()->checkHotSpot(ev.mouse, &hotspot))
		_runState.cursorStyle = _action->getCursor(*hotspot);
	else
		_runState.cursorStyle = kCursorNormal;

	_engine->getCursor()->setStyle(_runState.cursorStyle);
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
			getScenes()->loadScene(sceneIndex);

			while (getSound()->isBuffered(kEntityTables4)) {
				if (getFlags()->mouseRightClick)
					break;

				getSound()->unknownFunction1();
			}
		}
	}

	// Show Menu
	_engine->getMenu()->showMenu(false, type, time);
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

							if (!getEntities()->getPosition(hotspotScene.getHeader()->position + 100 * hotspotScene.getHeader()->car)
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
