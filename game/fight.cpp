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
#include "lastexpress/resource.h"

namespace LastExpress {

Fight::Fight(LastExpressEngine *engine) : _engine(engine), _data(NULL) {}

Fight::~Fight() {
	clear();
}

//////////////////////////////////////////////////////////////////////////
// Events
//////////////////////////////////////////////////////////////////////////

void Fight::eventMouseClick(Common::Event ev) {
	_data->isRunning = false;
}

void Fight::eventMouseMove(Common::Event ev) {
	handleMouseMove(ev, true);
}

void Fight::handleMouseMove(Common::Event ev, bool isProcessing) {

}

//////////////////////////////////////////////////////////////////////////
// Setup
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
	// FIXME move to start of fight?
	askForRedraw();
	redrawScreen();

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
			// FIXME Temporary
			askForRedraw();
			redrawScreen();
		}		
	}	

	// Cleanup after fight is over
	clear();

	return _hasLost;
}

//////////////////////////////////////////////////////////////////////////
// Status
//////////////////////////////////////////////////////////////////////////

void Fight::setStopped() {
	if (_data)
		_data->isRunning = false;
}

void Fight::bailout(bool hasLost) {
	_state = 0;
	_hasLost = hasLost;
	setStopped();
}

//////////////////////////////////////////////////////////////////////////
// Cleanup
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

//////////////////////////////////////////////////////////////////////////
// Drawing
//////////////////////////////////////////////////////////////////////////

void Fight::setSequenceAndDraw(FightCombatant *combatant, uint32 sequenceIndex, FightSequenceType type) {	
	if (combatant->sequences.size() < sequenceIndex)
		return;

	switch (type) {
	default:
		break;

	case kFightSequenceType0:
		if (combatant->sequenceIndex)
			return;

		combatant->currentSequence = combatant->sequences[sequenceIndex];
		combatant->sequenceIndex = sequenceIndex;
		draw(combatant);
		break;

	case kFightSequenceType1:
		combatant->currentSequence = combatant->sequences[sequenceIndex];
		combatant->sequenceIndex = sequenceIndex;
		combatant->sequenceIndex2 = 0;
		draw(combatant);
		break;

	case kFightSequenceType2:
		combatant->sequenceIndex2 = sequenceIndex;
		break;
	}	
}

void Fight::draw(FightCombatant *combatant) {
	Sequence* sequence = combatant->currentSequence2;

	if (!sequence)
		return;

	//////////////////////////////////////////////////////////////////////////
	// TODO redo to call drawSequence shared function?
	AnimFrame *frame = sequence->getFrame(0);
	_engine->getGraphicsManager()->draw(frame, GraphicsManager::kBackgroundOverlay);
	delete frame;
	//////////////////////////////////////////////////////////////////////////

	combatant->field_20 = 0;
	combatant->field_24 = 0;
}

//////////////////////////////////////////////////////////////////////////
// Loading
//////////////////////////////////////////////////////////////////////////

void Fight::loadData(FightType type) {

	switch (type) {
	default:
		break;

	case kFightMilos:
		loadMilosPlayer();
		loadMilosOpponent();
		break;

	case kFightAnna:
		loadAnnaPlayer();
		loadAnnaOpponent();
		break;

	case kFightIvo:
		loadIvoPlayer();
		loadIvoOpponent();
		break;

	case kFightSalko:
		loadSalkoPlayer();
		loadSalkoOpponent();
		break;

	case kFightVesna:
		loadVesnaPlayer();
		loadVesnaOpponent();
		break;
	}

	if (!_data->player || !_data->opponent)
		error("Fight::loadData - error loading fight data (type=%d)", type);

	if (!setOpponentAndCheckSequences()) {
		bailout(false);
		goto end_load;
	}

	_data->isRunning = true;

	if (_state < 5) {
		setSequenceAndDraw(_data->player, 0, kFightSequenceType0);
		setSequenceAndDraw(_data->opponent, 0, kFightSequenceType0);
		goto end_load;		
	}

	switch(type) {
	case kFightMilos:
		_data->opponent->field_30 = 1;
		setSequenceAndDraw(_data->player, 4, kFightSequenceType0);
		setSequenceAndDraw(_data->opponent, 0, kFightSequenceType0);
		break;

	case kFightIvo:
		_data->opponent->field_30 = 1;
		setSequenceAndDraw(_data->player, 3, kFightSequenceType0);
		setSequenceAndDraw(_data->opponent, 6, kFightSequenceType0);
		break;

	case kFightVesna:
		_data->opponent->field_30 = 1;
		setSequenceAndDraw(_data->player, 0, kFightSequenceType0);
		setSequenceAndDraw(_data->player, 3, kFightSequenceType2);
		setSequenceAndDraw(_data->opponent, 5, kFightSequenceType0);
		break;
	}



end_load:
	// TODO set unknown flag to 0
	return;
}

bool Fight::setOpponentAndCheckSequences() {

	// Set opponent
	_data->player->opponent = _data->opponent;
	_data->opponent->opponent = _data->player;

	// Check sequence count
	if (_data->player->sequences.size() != _data->opponent->sequences.size())
		return false;	
		
	return true;
}

//////////////////////////////////////////////////////////////////////////
// Milos
//////////////////////////////////////////////////////////////////////////

void Fight::loadMilosPlayer() {	
	// TODO set function pointer

	_data->player->sequences.push_back(newSequence("2001cr.seq"));
	_data->player->sequences.push_back(newSequence("2001cdl.seq"));
	_data->player->sequences.push_back(newSequence("2001cdr.seq"));
	_data->player->sequences.push_back(newSequence("2001cdm.seq"));
	_data->player->sequences.push_back(newSequence("2001csgr.seq"));
	_data->player->sequences.push_back(newSequence("2001csgl.seq"));
	_data->player->sequences.push_back(newSequence("2001dbk.seq"));
}

void Fight::loadMilosOpponent() {
	// TODO set function pointer

	_data->opponent->sequences.push_back(newSequence("2001or.seq"));
	_data->opponent->sequences.push_back(newSequence("2001oal.seq"));
	_data->opponent->sequences.push_back(newSequence("2001oam.seq"));
	_data->opponent->sequences.push_back(newSequence("2001okl.seq"));
	_data->opponent->sequences.push_back(newSequence("2001okm.seq"));
	_data->opponent->sequences.push_back(newSequence("2001dbk.seq"));
	_data->opponent->sequences.push_back(newSequence("2001wbk.seq"));

	getSound()->playSound(kEntityTables0, "MUS027", 16);

	_data->opponent->field_38 = 35;
}

//////////////////////////////////////////////////////////////////////////
// Anna
//////////////////////////////////////////////////////////////////////////

void Fight::loadAnnaPlayer() {}
void Fight::loadAnnaOpponent() {}

//////////////////////////////////////////////////////////////////////////
// Ivo
//////////////////////////////////////////////////////////////////////////

void Fight::loadIvoPlayer() {}
void Fight::loadIvoOpponent() {}

//////////////////////////////////////////////////////////////////////////
// Salko
//////////////////////////////////////////////////////////////////////////

void Fight::loadSalkoPlayer() {}
void Fight::loadSalkoOpponent() {}

//////////////////////////////////////////////////////////////////////////
// Vesna
//////////////////////////////////////////////////////////////////////////

void Fight::loadVesnaPlayer() {}
void Fight::loadVesnaOpponent() {}

} // End of namespace LastExpress
