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

#include "lastexpress/game/fight.h"

#include "lastexpress/data/scene.h"
#include "lastexpress/data/sequence.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Fight::Fight(LastExpressEngine *engine) : _engine(engine), _data(NULL) {}

Fight::~Fight() {
	clear();
}

//////////////////////////////////////////////////////////////////////////
// Public methods
//////////////////////////////////////////////////////////////////////////

bool Fight::setup(FightType type) {
	if (_data)
		error("Fight::setup - calling fight setup again while a fight is already in progress!");

	//////////////////////////////////////////////////////////////////////////
	// Prepare UI & state

	getInventory()->showHourGlass(true);
	// TODO events function
	// TODO global var
	getFlags()->flag_0 = 0;	
	getFlags()->flag_2 = 0;
	getEntities()->reset();

	// Compute scene to use
	SceneIndex sceneIndex;
	switch(type) {
	default:
		sceneIndex = kSceneFightDefault;
		break;

	case kFightMilos:
		sceneIndex = (getObjects()->get(kObjectCompartment1).location2 < kLocation3) ? kSceneFightMilos : kSceneFightMilosBedOpened;
		break;

	case kFightAnna:
		sceneIndex = kSceneFightAnna;
		break;

	case kFightIvo:
		sceneIndex = kSceneFightIvo;
		break;

	case kFightSalko:
		sceneIndex = kSceneFightSalko;
		break;

	case kFightVesna:
		sceneIndex = kSceneFightVesna;
		break;
	}

	if (getFlags()->shouldRedraw) {
		getFlags()->shouldRedraw = false;
		askForRedraw();
		redrawScreen();
	}

	// Load the scene object
	loadSceneObject(scene, sceneIndex);

	// Update game entities and state
	EntityData *entityData = getEntities()->getData(kEntityNone);
	entityData->getData()->field_491 = (EntityData::Field491Value)scene.getHeader()->count;
	entityData->getData()->field_493 = (EntityData::Field493Value)scene.getHeader()->field_11;

	getState()->scene = sceneIndex;

	getFlags()->flag_3 = 1;

	// Draw the scene
	_engine->getGraphicsManager()->draw(&scene, GraphicsManager::kBackgroundC);

	//////////////////////////////////////////////////////////////////////////
	// Setup the fight	
	_data = new FightData();
	if (!_data)
		error("Fight::setup - cannot create fight data structure!");

	loadData(type);

	// Show opponents & egg button
	Common::Event ev;
	handleMouseMove(ev, false);
	getInventory()->showHourGlass(false);

	// Start fight
	_hasLost = true;
	while (_data->isRunning) {
		// process events
		Common::Event ev;
		while (g_engine->getEventManager()->pollEvent(ev)) {
			switch (ev.type) {
			default:
				// default graphic handling?
				break;

			case Common::EVENT_MOUSEMOVE:
				eventMouseMove(ev);
				break;

			case Common::EVENT_LBUTTONDOWN:
			case Common::EVENT_LBUTTONUP:
			case Common::EVENT_RBUTTONDOWN:
				eventMouseClick(ev);
				break;
			}

			g_engine->_system->delayMillis(10);
		}		
	}	

	// Cleanup after fight is over
	clear();

	return _hasLost;
}

void Fight::setStopped() {
	if (_data)
		_data->isRunning = false;
}

//////////////////////////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////////////////////////

void Fight::clear() {
	if (!_data)
		return;

	// Clear data
	clearSequences(_data->player);
	clearSequences(_data->opponent);

	delete _data->player;
	delete _data->opponent;

	delete _data;
	_data = NULL;
}

void Fight::clearSequences(FightCombatant *combatant) {
	if (!combatant)
		return;

	// TODO Set function pointer
	// TODO Draw sequence (field 1C)

	// Free sequences
	for (uint i = 0; i < combatant->sequences.size(); i++)
		delete combatant->sequences[i];
}


void Fight::loadData(FightType type) {

}

//////////////////////////////////////////////////////////////////////////
// Events
//////////////////////////////////////////////////////////////////////////

void Fight::eventMouseClick(Common::Event ev) {

}

void Fight::eventMouseMove(Common::Event ev) {
	handleMouseMove(ev, true);
}

void Fight::handleMouseMove(Common::Event ev, bool isProcessing) {

}


} // End of namespace LastExpress
