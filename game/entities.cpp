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

#include "lastexpress/game/entities.h"

// Data
#include "lastexpress/data/scene.h"
#include "lastexpress/data/sequence.h"

// Entities
#include "lastexpress/entities/entity.h"

#include "lastexpress/entities/abbot.h"
#include "lastexpress/entities/alexei.h"
#include "lastexpress/entities/alouan.h"
#include "lastexpress/entities/anna.h"
#include "lastexpress/entities/august.h"
#include "lastexpress/entities/boutarel.h"
#include "lastexpress/entities/chapters.h"
#include "lastexpress/entities/cooks.h"
#include "lastexpress/entities/coudert.h"
#include "lastexpress/entities/entity39.h"
#include "lastexpress/entities/francois.h"
#include "lastexpress/entities/gendarmes.h"
#include "lastexpress/entities/hadija.h"
#include "lastexpress/entities/ivo.h"
#include "lastexpress/entities/kahina.h"
#include "lastexpress/entities/kronos.h"
#include "lastexpress/entities/mahmud.h"
#include "lastexpress/entities/max.h"
#include "lastexpress/entities/mertens.h"
#include "lastexpress/entities/milos.h"
#include "lastexpress/entities/mmeboutarel.h"
#include "lastexpress/entities/pascale.h"
#include "lastexpress/entities/rebecca.h"
#include "lastexpress/entities/salko.h"
#include "lastexpress/entities/servers0.h"
#include "lastexpress/entities/servers1.h"
#include "lastexpress/entities/sophie.h"
#include "lastexpress/entities/tables.h"
#include "lastexpress/entities/tatiana.h"
#include "lastexpress/entities/train.h"
#include "lastexpress/entities/vassili.h"
#include "lastexpress/entities/verges.h"
#include "lastexpress/entities/vesna.h"
#include "lastexpress/entities/yasmin.h"

// Game
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

static const int soundValues[32] = {
	16,	15,	14,	13,	12,
	11, 11,	10, 10,	9, 9, 8, 8,
	7, 7, 7, 6, 6, 6,
	5, 5, 5, 5,	4, 4, 4, 4,
	3, 3, 3, 3, 3
};

static const EntityData::Field491Value field491_values[9] = {EntityData::kField491_0, EntityData::kField491_8200,
	                                                         EntityData::kField491_7500, EntityData::kField491_6470,
	                                                         EntityData::kField491_5790, EntityData::kField491_4840,
	                                                         EntityData::kField491_4070, EntityData::kField491_3050,
	                                                         EntityData::kField491_2740};

#define ADD_ENTITY(class) \
	_entities.push_back(new class(engine));

//////////////////////////////////////////////////////////////////////////
// Entities
//////////////////////////////////////////////////////////////////////////
Entities::Entities(LastExpressEngine *engine) : _engine(engine) {
	_header = new EntityData();

	_entities.push_back(NULL);      // Header
	ADD_ENTITY(Anna);
	ADD_ENTITY(August);
	ADD_ENTITY(Mertens);
	ADD_ENTITY(Coudert);
	ADD_ENTITY(Pascale);
	ADD_ENTITY(Servers0);
	ADD_ENTITY(Servers1);
	ADD_ENTITY(Cooks);
	ADD_ENTITY(Verges);
	ADD_ENTITY(Tatiana);
	ADD_ENTITY(Vassili);
	ADD_ENTITY(Alexei);
	ADD_ENTITY(Abbot);
	ADD_ENTITY(Milos);
	ADD_ENTITY(Vesna);
	ADD_ENTITY(Ivo);
	ADD_ENTITY(Salko);
	ADD_ENTITY(Kronos);
	ADD_ENTITY(Kahina);
	ADD_ENTITY(Francois);
	ADD_ENTITY(MmeBoutarel);
	ADD_ENTITY(Boutarel);
	ADD_ENTITY(Rebecca);
	ADD_ENTITY(Sophie);
	ADD_ENTITY(Mahmud);
	ADD_ENTITY(Yasmin);
	ADD_ENTITY(Hadija);
	ADD_ENTITY(Alouan);
	ADD_ENTITY(Gendarmes);
	ADD_ENTITY(Max);
	ADD_ENTITY(Chapters);
	ADD_ENTITY(Train);

	// Special case for tables
	_entities.push_back(new Tables(engine, kEntityTables0));
	_entities.push_back(new Tables(engine, kEntityTables1));
	_entities.push_back(new Tables(engine, kEntityTables2));
	_entities.push_back(new Tables(engine, kEntityTables3));
	_entities.push_back(new Tables(engine, kEntityTables4));
	_entities.push_back(new Tables(engine, kEntityTables5));

	ADD_ENTITY(Entity39);

	// Init compartments & positions
	memset(&_compartments, 0, sizeof(_compartments));
	memset(&_compartments1, 0, sizeof(_compartments1));
	memset(&_positions, 0, sizeof(_positions));
}

Entities::~Entities() {
	delete _header;

	for (int i = 0; i < (int)_entities.size(); i++)
		delete _entities[i];

	// Zero passed pointers
	_engine = NULL;
}

//////////////////////////////////////////////////////////////////////////
// Accessors
//////////////////////////////////////////////////////////////////////////
Entity *Entities::get(EntityIndex entity) {
	assert((uint)entity < _entities.size());

	if (entity == kEntityNone)
		error("Cannot get entity for index = 0!");

	return _entities[entity];
}

EntityData::EntityCallData *Entities::getData(EntityIndex entity) const {
	assert((uint)entity < _entities.size());

	if (entity == kEntityNone)
		return _header->getCallData();

	return _entities[entity]->getData();
}

//////////////////////////////////////////////////////////////////////////
// Savegame
//////////////////////////////////////////////////////////////////////////
void Entities::saveLoadWithSerializer(Common::Serializer &ser) {
	_header->saveLoadWithSerializer(ser);
	for (uint i = 1; i < _entities.size(); i++)
		_entities[i]->saveLoadWithSerializer(ser);
}

//////////////////////////////////////////////////////////////////////////
// Setup
//////////////////////////////////////////////////////////////////////////
void Entities::setup(ChapterIndex chapter) {
	if (chapter) {
		// Reset current call, inventory item & draw sequences
		for (int i = 1; i < (int)_entities.size(); i++) {
			getData((EntityIndex)i)->current_call = 0;
			getData((EntityIndex)i)->inventoryItem = kItemNone;

			prepareSequences((EntityIndex)i);
		}

		// Init compartments & positions
		memset(&_compartments, 0, sizeof(_compartments));
		memset(&_compartments1, 0, sizeof(_compartments1));
		memset(&_positions, 0, sizeof(_positions));

		getSound()->setupQueue(13);
	}

	// we skip the header when doing entity setup
	for (uint i = 1; i < _entities.size(); i++) {
		// Special case of chapters (prevents infinite loop as we will be called from Chapters functions when changing chapters)
		if (i == kEntityChapters && chapter >= 2)
			continue;

		_entities[i]->setup(chapter);
	}
}

void Entities::reset() {
	// Reset header
	delete _header;
	_header = new EntityData();

	for (uint i = 1; i < _entities.size(); i++)
		resetSequences((EntityIndex)i);

	// Original games does some global cleanup of the sequence cache here
	// This is not needed since the sequences are not stored globally
}

//////////////////////////////////////////////////////////////////////////
// State & Sequences
//////////////////////////////////////////////////////////////////////////

void Entities::resetState(EntityIndex entityIndex) {
	getData(entityIndex)->current_call = 0;
	getData(entityIndex)->inventoryItem = kItemNone;

	if (getSound()->isBuffered(entityIndex))
		getSound()->removeFromQueue(entityIndex);

	prepareSequences(entityIndex);

	if (entityIndex == kEntity39)
		entityIndex = kEntityNone;

	if (entityIndex > kEntityChapters)
		return;

	int field = ~((uint)1 << entityIndex);

	// reset compartments and positions for this entity
	for (int i = 0; i < _positionsNumber; i++)
		_positions[i] &= field;

	for (int i = 0; i < _compartmentsNumber; i++) {
		_compartments[i] &= field;
		_compartments1[i] &= field;
	}

	getLogic()->updateCursor();
}


void Entities::updateFields() {
	if (!getFlags()->gameRunning)
		return;

	for (int i = 0; i < (int)_entities.size(); i++) {

		if (!getSavePoints()->getCallback((EntityIndex)i))
			continue;

		EntityData::EntityCallData *data = getData((EntityIndex)i);
		switch (data->direction) {
		default:
			break;

		case kDirectionUp:
		case kDirectionDown:	// Replaces calls to CheckFields8
			if (data->direction != kDirectionUp || (data->field_491 + data->field_4A3 * 10) >= 10000)
			{
				if (data->direction == kDirectionDown) {
					if (data->field_491 > data->field_4A3 * 10)
						data->field_491 = (EntityData::Field491Value)(data->field_491 - data->field_4A3 * 10);
				}
			} else {
				data->field_491 = (EntityData::Field491Value)(data->field_491 + data->field_4A3 * 10);
			}
			break;

		case kDirectionLeft:
			data->currentFrame2 += 1;
			break;

		case kDirectionRight:
			data->field_4A1 += 9;
			break;

		case kDirectionSwitch:
			if (data->direction2 == kDirectionRight)
				data->field_4A1 += 9;
			break;

		}
	}
}

void Entities::updateEntity(EntityIndex entityIndex) {
	Sequence *sequence = NULL;
	int16 *currentFrame = NULL;
	bool found = false;

	if (getData(entityIndex)->direction == kDirectionSwitch) {
		sequence = getData(entityIndex)->sequence3;
		currentFrame = &getData(entityIndex)->currentFrame3;
	} else {
		sequence = getData(entityIndex)->sequence2;
		currentFrame = &getData(entityIndex)->currentFrame2;
	}

	if (!sequence)
		return;

	// Save current values
	int16 oldFrame = *currentFrame;
	int16 field_4A1 = getData(entityIndex)->field_4A1;

	do {
		// Check we do not get past the end
		if (*currentFrame >= (int)sequence->count() - 1)
			break;

		// Get the proper frame
		FrameInfo *info = sequence->getFrameInfo(*currentFrame);

		if (info->field_33 & 8) {
			found = true;
		} else {
			if (info->soundAction == 35)
				found = true;

			getData(entityIndex)->field_4A1 += info->field_30;

			// Progress to the next frame
			++*currentFrame;
		}
	} while (!found);

	// Restore old values
	if (!found) {
		*currentFrame = oldFrame;
		getData(entityIndex)->field_4A1 = field_4A1;
	}
}

void Entities::setupSequences() {
	if (!getFlags()->gameRunning)
		return;

	// Update the train clock
	getLogic()->updateDoorsAndClock();

	//////////////////////////////////////////////////////////////////////////
	// First pass: Drawing
	//////////////////////////////////////////////////////////////////////////
	for (uint i = 1; i < _entities.size(); i++) {
		EntityIndex entityIndex = (EntityIndex)i;

		if (!getSavePoints()->getCallback(entityIndex))
			continue;

		EntityData::EntityCallData *data = getData(entityIndex);

		if (data->sequence0) {
			// TODO Queue sequence for drawing
			/* data->sequence0 = NULL; */
			warning("Entities::setupSequences: not implemented!");
		}

		if (data->sequence1) {
			// TODO Queue sequence for drawing
			/* data->sequence1 = NULL; */
			warning("Entities::setupSequences: not implemented!");
		}

		if (data->direction == kDirectionSwitch) {

			// Clear sequence 2
			if (data->sequence2) {
				delete data->sequence2;
				data->sequence2 = NULL;
			}

			// Replace by sequence 3 if available
			if (data->sequence3) {
				data->sequence2 = data->sequence3;
				strcpy(data->sequenceName2, data->sequenceName3);

				data->sequence3 = NULL;
				strcpy(data->sequenceName3, "");
			}

			data->direction = data->direction2;
			data->currentFrame2 = -1;
			data->field_49B = 0;
		}

		// Draw sequences
		drawSequencesInternal(entityIndex, data->direction, false);
	}

	//////////////////////////////////////////////////////////////////////////
	// Second pass: Load sequences for next pass
	//////////////////////////////////////////////////////////////////////////

	warning("Entities::setupSequences: not implemented!");
}

void Entities::resetSequences(EntityIndex entityIndex) const {

	// Reset direction
	if (getData(entityIndex)->direction == kDirectionSwitch) {
		getData(entityIndex)->direction = getData(entityIndex)->direction2;
		getData(entityIndex)->field_49B = 0;
		getData(entityIndex)->currentFrame2 = -1;
	}

	// FIXME: in the original engine, the sequence pointers might just be copies,
	// make sure we free the associated memory at some point
	getData(entityIndex)->sequence0 = NULL;
	getData(entityIndex)->sequence1 = NULL;

	SAFE_DELETE(getData(entityIndex)->sequence2);
	SAFE_DELETE(getData(entityIndex)->sequence3);
	SAFE_DELETE(getData(entityIndex)->sequence4);

	getData(entityIndex)->field_4A9 = 0;
	getData(entityIndex)->field_4AA = 0;
	getData(entityIndex)->field_4CD = 0;

	strcpy((char*)&getData(entityIndex)->sequenceName2, "");
	strcpy((char*)&getData(entityIndex)->sequenceName3, "");

	// Original engine resets flag to decompress data on the fly (we don't need to do that)
}

//////////////////////////////////////////////////////////////////////////
// Callbacks
//////////////////////////////////////////////////////////////////////////
void Entities::setupCallbacks() {
	if (!getFlags()->gameRunning)
		return;

	getFlags()->flag_entities_0 = false;

	if (getFlags()->flag_entities_1) {
		executeCallbacks();
		getFlags()->flag_entities_0 = true;
	} else {
		getFlags()->flag_entities_1 = true;
		executeCallbacks();
		getFlags()->flag_entities_1 = false;
	}
}

void Entities::executeCallbacks() {
	for (uint i = 1; i < _entities.size(); i++) {
		if (getFlags()->flag_entities_0)
			break;

		if (getSavePoints()->getCallback((EntityIndex)i))
			processEntity((EntityIndex)i);
	}

	if (getFlags()->flag_entities_0)
		return;

	bool processed = false;
	do {
		for (int i = 1; i < (int)_entities.size(); i++) {
			if (getFlags()->flag_entities_0)
				break;

			if (getSavePoints()->getCallback((EntityIndex)i)) {
				if (getData((EntityIndex)i)->field_4A8) {
					processed = true;
					processEntity((EntityIndex)i);
				}
			}
		}
	} while (!processed);
}

//////////////////////////////////////////////////////////////////////////
// Processing
//////////////////////////////////////////////////////////////////////////
void Entities::processEntity(EntityIndex entity) {
	getFlags()->flag_entities_0 = true;
	warning("Entities::processEntity: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Drawing
//////////////////////////////////////////////////////////////////////////
void Entities::drawSequenceLeft(EntityIndex index, const char* sequence) {
	drawSequenceInternal(index, sequence, kDirectionLeft);
}

void Entities::drawSequenceRight(EntityIndex index, const char* sequence) {
	drawSequenceInternal(index, sequence, kDirectionRight);
}

void Entities::prepareSequences(EntityIndex index) {
	debugC(8, kLastExpressDebugLogic, "Prepare sequences for entity %d", index);

	warning("Entities::prepareSequences: not implemented!");
}

void Entities::drawSequenceInternal(EntityIndex index, const char* sequence, EntityDirection direction) {
	debugC(8, kLastExpressDebugLogic, "Drawing sequence %s for entity %d (%d)", sequence, index, direction);

	// Copy sequence name
	Common::String processedName(sequence);
	processedName.toUppercase();
	processedName += "-";

	strcpy(getData(index)->sequenceName, processedName.c_str());

	// Reset fields
	getData(index)->field_49B = 0;
	getData(index)->currentFrame2 = 0;
	getData(index)->field_4A1 = 0;

	drawSequencesInternal(index, direction, true);
}

void Entities::drawSequencesInternal(EntityIndex index, EntityDirection direction, bool unknown) {
	//debugC(8, kLastExpressDebugLogic, "Drawing sequences for entity %d (%d)", index, field_49A);

	// HACK draw the sequence stored in SequenceName
	//char seq1[13];
	//char seq2[13];
	//memset(&seq1, 0, 13 * sizeof(char));
	//memset(&seq2, 0, 13 * sizeof(char));

	//getSequenceName(index, direction, (char*)&seq1, (char*)&seq2);

	//debugC(8, kLastExpressDebugLogic, "  sequence1: %s", seq1);

	//Sequence sequence;
	//if (sequence.loadFile(seq1)) {
	//	clearBg(GraphicsManager::kBackgroundOverlay);

	//	AnimFrame *frame = sequence.getFrame(0);
	//	_engine->getGraphicsManager()->draw(frame, GraphicsManager::kBackgroundOverlay);
	//	delete frame;

	//	askForRedraw();
	//}

	warning("Entities::drawSequencesInternal: not implemented!");
}

void Entities::getSequenceName(EntityIndex index, EntityDirection direction, char *sequence1, char *sequence2) {
	EntityData::EntityCallData *data = getData(index);
	loadSceneObject(currentScene, getState()->scene);
	int position = currentScene.getHeader()->position;

	// reset fields
	data->field_4A9 = 0;
	data->field_4AA = 0;

	switch (direction) {
	default:
		error("Entities::getSequenceName: Invalid value for field_49A: %d", direction);
		break;

	case kDirectionUp:
		switch (position) {
		default:
			error("Entities::getSequenceName: Invalid scene position %d (Direction UP)", position);
			break;

		case 1:
			if (data->field_491 < EntityData::kField491_2587)
				sprintf(sequence1, "%02d%01d-01u.seq", index, data->clothes);
			break;

		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			if (data->field_491 >= EntityData::kField491_9270)
				break;

			if (data->field_491 >= EntityData::kField491_8513) {
				sprintf(sequence1, "%02d%01d-%02deu.seq", index, data->clothes, position);
			} else {
				sprintf(sequence1, "%02d%01d-03u.seq", index, data->clothes);
				sprintf(sequence2, "%02d%01d-%02deu.seq", index, data->clothes, position);
				data->field_4A9 = 1;
			}
			break;

		case 18:
			if (data->field_491 >= EntityData::kField491_2436)
				sprintf(sequence1, "%02d%01d-18u.seq", index, data->clothes);
			break;

		case 22:
			if (getData(kEntityNone)->field_491 > data->field_491)
				sprintf(sequence1, "%02d%01d-22u.seq", index, data->clothes);
			break;

		case 23:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
			if (getData(kEntityNone)->field_491 <= data->field_491)
				break;

			if (data->field_491 >= EntityData::kField491_2087) {
				sprintf(sequence1, "%02d%01d-38u.seq", index, data->clothes);
				data->field_4A9 = 1;
			} else {
				sprintf(sequence1, "%02d%01d-%02deu.seq", index, data->clothes, position);
				sprintf(sequence2, "%02d%01d-38u.seq", index, data->clothes);
				data->field_4AA = 1;
			}
			break;

		case 40:
			if (getData(kEntityNone)->field_491 > data->field_491)
				sprintf(sequence1, "%02d%01d-40u.seq", index, data->clothes);
			break;
		}
		break;

	case kDirectionDown:
		switch (position) {
		default:
			error("Entities::getSequenceName: Invalid scene position %d (Direction DOWN)", position);
			break;

		case 1:
			if (getData(kEntityNone)->field_491 < data->field_491)
				sprintf(sequence1, "%02d%01d-01d.seq", index, data->clothes);
			break;

		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			if (getData(kEntityNone)->field_491 >= data->field_491)
				break;

			if (data->field_491 <= EntityData::kField491_8513) {
				sprintf(sequence1, "%02d%01d-03d.seq", index, data->clothes);
				data->field_4A9 = 1;
			} else {
				sprintf(sequence1, "%02d%01d-%02ded.seq", index, data->clothes, position);
				sprintf(sequence2, "%02d%01d-03d.seq", index, data->clothes);
				data->field_4AA = 1;
			}
			break;

		case 18:
			if (getData(kEntityNone)->field_491 < data->field_491)
				sprintf(sequence1, "%02d%01d-18d.seq", index, data->clothes);
			break;

		case 22:
			if (data->field_491 > EntityData::kField491_850)
				sprintf(sequence1, "%02d%01d-22d.seq", index, data->clothes);
			break;

		case 23:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
			if (data->field_491 <= EntityData::kField491_850)
				break;

			if (data->field_491 <= EntityData::kField491_2087) {
				sprintf(sequence1, "%02d%01d-%02ded.seq", index, data->clothes, position);
			} else {
				sprintf(sequence1, "%02d%01d-38d.seq", index, data->clothes);
				sprintf(sequence2, "%02d%01d-%02ded.seq", index, data->clothes, position);
				data->field_4A9 = 1;
			}
			break;

		case 40:
			if (getData(kEntityNone)->field_491 > EntityData::kField491_8013)
				sprintf(sequence1, "%02d%01d-40d.seq", index, data->clothes);
			break;
		}
		break;

	// First part of sequence is already set
	case kDirectionLeft:
	case kDirectionRight:
		sprintf(sequence1, "%s%02d.seq", (char*)&data->sequenceName, position);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
/// Compartments
//////////////////////////////////////////////////////////////////////////
void Entities::updatePosition(EntityIndex entity, CarIndex car, Position position, bool processScene) {
	if (entity == kEntity39)
		entity = kEntityNone;

	if (entity > kEntityChapters)
		return;

	_positions[100 * car + position] &= ~(1 << entity);

	if (processScene && (isPlayerPosition(car, position) || (car == kCarRestaurant && position == 57 && isPlayerPosition(kCarRestaurant, 50)))) {
		getSound()->excuseMe(entity);
		getLogic()->loadScene(getLogic()->processIndex(getState()->scene));
		getSound()->playSound(kEntityNone, "CAT1127A");
	} else {
		getLogic()->updateCursor();
	}
}

void Entities::enterCompartment(EntityIndex entity, ObjectIndex compartment, bool useFirstCompartments) {
	if (entity > kEntityChapters)
		return;

	switch (compartment) {
	default:
		// Return here so we do not update the compartments
		return;

	case kObjectCompartment1:
		updatePositionsEnter(entity, kCarGreenSleeping, 41, 51, 17, 38);
		break;

	case kObjectCompartment2:
		updatePositionsEnter(entity, kCarGreenSleeping, 42, 52, 15, 36);
		break;

	case kObjectCompartment3:
		updatePositionsEnter(entity, kCarGreenSleeping, 43, 53, 13, 34);
		break;

	case kObjectCompartment4:
		updatePositionsEnter(entity, kCarGreenSleeping, 44, 54, 11, 32);
		break;

	case kObjectCompartment5:
		updatePositionsEnter(entity, kCarGreenSleeping, 45, 55, 9, 30);
		break;

	case kObjectCompartment6:
		updatePositionsEnter(entity, kCarGreenSleeping, 46, 56, 7, 28);
		break;

	case kObjectCompartment7:
		updatePositionsEnter(entity, kCarGreenSleeping, 47, 57, 5, 26);
		break;

	case kObjectCompartment8:
		updatePositionsEnter(entity, kCarGreenSleeping, 48, 58, 3, 25);
		break;

	case kObjectCompartmentA:
		updatePositionsEnter(entity, kCarRedSleeping, 41, 51, 17, 38);
		break;

	case kObjectCompartmentB:
		updatePositionsEnter(entity, kCarRedSleeping, 42, 52, 15, 36);
		break;

	case kObjectCompartmentC:
		updatePositionsEnter(entity, kCarRedSleeping, 43, 53, 13, 34);
		break;

	case kObjectCompartmentD:
		updatePositionsEnter(entity, kCarRedSleeping, 44, 54, 11, 32);
		break;

	case kObjectCompartmentE:
		updatePositionsEnter(entity, kCarRedSleeping, 45, 55, 9, 30);
		break;

	case kObjectCompartmentF:
		updatePositionsEnter(entity, kCarRedSleeping, 46, 56, 7, 28);
		break;

	case kObjectCompartmentG:
		updatePositionsEnter(entity, kCarRedSleeping, 47, 57, 5, 26);
		break;

	case kObjectCompartmentH:
		updatePositionsEnter(entity, kCarRedSleeping, 48, 58, 3, 25);
		break;
	}

	// Update compartments
	int index = (compartment < 32 ? compartment - 1 : compartment - 24);
	if (useFirstCompartments)
		_compartments[index] |= (1 << entity);
	else
		_compartments1[index] |= (1 << entity);
}

void Entities::exitCompartment(EntityIndex entity, ObjectIndex compartment, bool useFirstCompartments) {
if (entity > kEntityChapters)
		return;

	// TODO factorize in one line
	switch (compartment) {
	default:
		// Return here so we do not update the compartments
		return;

	case kObjectCompartment1:
		updatePositionsExit(entity, kCarGreenSleeping, 41, 51);
		break;

	case kObjectCompartment2:
		updatePositionsExit(entity, kCarGreenSleeping, 42, 52);
		break;

	case kObjectCompartment3:
		updatePositionsExit(entity, kCarGreenSleeping, 43, 53);
		break;

	case kObjectCompartment4:
		updatePositionsExit(entity, kCarGreenSleeping, 44, 54);
		break;

	case kObjectCompartment5:
		updatePositionsExit(entity, kCarGreenSleeping, 45, 55);
		break;

	case kObjectCompartment6:
		updatePositionsExit(entity, kCarGreenSleeping, 46, 56);
		break;

	case kObjectCompartment7:
		updatePositionsExit(entity, kCarGreenSleeping, 47, 57);
		break;

	case kObjectCompartment8:
		updatePositionsExit(entity, kCarGreenSleeping, 48, 58);
		break;

	case kObjectCompartmentA:
		updatePositionsExit(entity, kCarRedSleeping, 41, 51);
		break;

	case kObjectCompartmentB:
		updatePositionsExit(entity, kCarRedSleeping, 42, 52);
		break;

	case kObjectCompartmentC:
		updatePositionsExit(entity, kCarRedSleeping, 43, 53);
		break;

	case kObjectCompartmentD:
		updatePositionsExit(entity, kCarRedSleeping, 44, 54);
		break;

	case kObjectCompartmentE:
		updatePositionsExit(entity, kCarRedSleeping, 45, 55);
		break;

	case kObjectCompartmentF:
		updatePositionsExit(entity, kCarRedSleeping, 46, 56);
		break;

	case kObjectCompartmentG:
		updatePositionsExit(entity, kCarRedSleeping, 47, 57);
		break;

	case kObjectCompartmentH:
		updatePositionsExit(entity, kCarRedSleeping, 48, 58);
		break;
	}

	// Update compartments
	int index = (compartment < 32 ? compartment - 1 : compartment - 24);
	if (useFirstCompartments)
		_compartments[index] &= ~(1 << entity);
	else
		_compartments1[index] &= ~(1 << entity);
}

void Entities::updatePositionsEnter(EntityIndex entity, CarIndex car, Position position1, Position position2, Position position3, Position position4) {
	if (entity == kEntity39)
		entity = kEntityNone;

	if (entity > kEntityChapters)
		return;

	_positions[100 * car + position1] |= (1 << entity);
	_positions[100 * car + position2] |= (1 << entity);

	// FIXME: also checking two DWORD values that do not seem to updated anywhere...
	if (isPlayerPosition(car, position1) || isPlayerPosition(car, position2) || isPlayerPosition(car, position3) || isPlayerPosition(car, position4)) {
		getSound()->excuseMe(entity);
		getLogic()->loadScene(getLogic()->processIndex(getState()->scene));
		getSound()->playSound(kEntityNone, "CAT1127A");
	} else {
		getLogic()->updateCursor();
	}
}

void Entities::updatePositionsExit(EntityIndex entity, CarIndex car, Position position1, Position position2) {
	if (entity == kEntity39)
		entity = kEntityNone;

	if (entity > kEntityChapters)
		return;

	_positions[100 * car + position1] &= ~(1 << entity);
	_positions[100 * car + position2] &= ~(1 << entity);

	getLogic()->updateCursor();
}

//////////////////////////////////////////////////////////////////////////
// Misc (Sound, etc.)
//////////////////////////////////////////////////////////////////////////
int Entities::getSoundValue(EntityIndex entity) {
	if (entity == kEntityNone)
		return 16;

	if (getData(entity)->car != getData(kEntityNone)->car)
		return 0;

	// Compute sound value
	int ret = 2;

	// Get default value if valid
	int index = abs(getData(entity)->field_491 - getData(kEntityNone)->field_491) / 230;
	if (index < 32)
		ret = soundValues[index];

	if (getData(entity)->field_493 == EntityData::kField493_2) {
		if (getData(entity)->car != kCarKronos
		&& !getEntities()->checkFields15()
		&& !getEntities()->checkFields16())
			return 0;

		return ret / 6;
	}

	switch (getData(entity)->car) {
	default:
		break;

	case kCarKronos:
		if (getEntities()->checkFields14(entity) != getEntities()->checkFields14(kEntityNone))
			ret >>= 1;
		break;

	case kCarGreenSleeping:
	case kCarRedSleeping:
		if (getEntities()->checkFields6(kEntityNone) && !getEntities()->checkFields14(entity))
			ret >>= 1;

		if (getData(kEntityNone)->field_493
		&& (getData(entity)->field_491 != EntityData::kField491_1 || !getEntities()->checkFields9(kEntityNone, entity, 400)))
			ret >>=1;
		break;

	case kCarRestaurant:
		if (getEntities()->checkFields12(entity) == getEntities()->checkFields12(kEntityNone)
		&& (getEntities()->checkFields13(entity) != getEntities()->checkFields13(kEntityNone)))
			ret >>=1;
		else
			ret >>=2;
		break;
	}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
//	Checks
//////////////////////////////////////////////////////////////////////////
bool Entities::checkSequence0(EntityIndex entity) {
	return (getData(entity)->sequence0 && (getData(entity)->sequence0->getFrameInfo(0)->subType != 3));
}

bool Entities::compare(EntityIndex entity1, EntityIndex entity2) {
	error("Entities::compare: not implemented!");
}

bool Entities::checkEntity(EntityIndex entity, CarIndex car, EntityData::Field491Value field491) {
	error("Entities::checkEntity: not implemented!");
}

bool Entities::checkFields1(EntityIndex entity, CarIndex car, EntityData::Field491Value field491) const {
	return (getData(entity)->field_491 == field491
		 && getData(entity)->field_493 == EntityData::kField493_1
		 && getData(entity)->car == car);
}

bool Entities::checkFields2(ObjectIndex object) const {

	EntityData::Field491Value field491 = EntityData::kField491_0;
	CarIndex car = kCarNone;

	switch (object) {
	default:
		return false;

	case kObjectCompartment1:
	case kObjectCompartment2:
	case kObjectCompartment3:
	case kObjectCompartment4:
	case kObjectCompartment5:
	case kObjectCompartment6:
	case kObjectCompartment7:
	case kObjectCompartment8:
		field491 = field491_values[object];
		car = kCarGreenSleeping;
		if (checkFields1(kEntityNone, car, field491))
			return false;
		break;

	case kObjectHandleBathroom:
	case kObjectHandleInsideBathroom:
	case kObjectKitchen:
	case kObject20:
	case kObject21:
	case kObject22:
		field491 = field491_values[object-17];
		car = kCarGreenSleeping;
		break;

	case kObjectCompartmentA:
	case kObjectCompartmentB:
	case kObjectCompartmentC:
	case kObjectCompartmentD:
	case kObjectCompartmentE:
	case kObjectCompartmentF:
	case kObjectCompartmentG:
	case kObjectCompartmentH:
		field491 = field491_values[object-32];
		car = kCarRedSleeping;
		if (checkFields1(kEntityNone, car, field491))
			return false;
		break;

	case kObject48:
	case kObject49:
	case kObject50:
	case kObject51:
	case kObject52:
	case kObject53:
		field491 = field491_values[object-48];
		car = kCarRedSleeping;
		break;

	}

	uint index = 1;
	while (!checkFields1((EntityIndex)index, car, field491) || index == kEntityVassili) {
		index++;
		if (index >= 40)
			return false;
	}

	return true;
}

bool Entities::checkFields3(EntityIndex entity) const {
	return (getData(entity)->car == kCarGreenSleeping
		 || getData(entity)->car == kCarRedSleeping)
		 && getData(entity)->field_493 == EntityData::kField493_1;
}

bool Entities::isPlayerPosition(CarIndex car, Position position) const {
	loadSceneObject(scene, getState()->scene);

	return getData(kEntityNone)->car == car && scene.getHeader()->position == position;
}

bool Entities::checkFields5(EntityIndex entity, CarIndex car) const {
	return getData(entity)->car == car && getData(entity)->field_493 < EntityData::kField493_2;
}

bool Entities::checkFields6(EntityIndex entity) const {
	return checkFields5(entity, kCarGreenSleeping) && getData(entity)->field_491 < EntityData::kField491_850;
}

bool Entities::checkFields7(CarIndex car) const {
	return checkFields5(kEntityNone, car) && !getData(kEntityNone)->field_493 && !checkFields6(kEntityNone);
}

bool Entities::isDirectionUpOrDown(EntityIndex entity) const {
	return getData(entity)->direction == kDirectionUp || getData(entity)->direction == kDirectionDown;
}

bool Entities::checkFields9(EntityIndex entity1, EntityIndex entity2, int absValue) const {
	return getData(entity1)->car == getData(entity2)->car
	    && abs(getData(entity1)->field_491 - getData(entity2)->field_491) <= absValue
		&& (getData(entity1)->field_493 != EntityData::kField493_2 || getData(entity2)->field_493 != EntityData::kField493_2);
}

bool Entities::checkFields10(EntityIndex entity) const {
	return getData(entity)->field_493 < EntityData::kField493_3;
}

bool Entities::checkFields11() const {
	for (uint i = 1; i < _entities.size(); i++) {
		EntityIndex index = (EntityIndex)i;

		if ((!getData(index)->field_493 && checkFields12(index)) || checkFields13(index))
			return false;
	}

	return true;
}

bool Entities::checkFields12(EntityIndex entity) const {
	return checkFields5(entity, kCarRestaurant)
		&& getData(entity)->field_491 >= EntityData::kField491_1540
		&& getData(entity)->field_491 <= EntityData::kField491_3650;
}

bool Entities::checkFields13(EntityIndex entity) const {
	return checkFields5(entity, kCarRestaurant)
		&& getData(entity)->field_491 >= EntityData::kField491_3650
		&& getData(entity)->field_491 <= EntityData::kField491_5800;
}

bool Entities::checkFields14(EntityIndex entity) const {
	return checkFields5(entity, kCarKronos)
		&& getData(entity)->field_491 >= EntityData::kField491_5500
		&& getData(entity)->field_491 <= EntityData::kField491_7500;
}

bool Entities::checkFields15() const {
	return (getData(kEntityNone)->field_491 == EntityData::kField491_7500 || getData(kEntityNone)->field_491 == EntityData::kField491_8200)
		 && getData(kEntityNone)->field_493 == EntityData::kField493_2
		 && getData(kEntityNone)->car == kCarGreenSleeping;
}

bool Entities::checkFields16() const {
	return (getData(kEntityNone)->field_491 == EntityData::kField491_4070 || getData(kEntityNone)->field_491 == EntityData::kField491_4840)
		 && getData(kEntityNone)->field_493 == EntityData::kField493_2
		 && getData(kEntityNone)->car == kCarRedSleeping;
}

bool Entities::checkFields17(EntityIndex entity) const {
	return checkFields5(entity, kCarRestaurant) && getData(entity)->field_491 > EntityData::kField491_5800;
}

bool Entities::checkFields18(CarIndex car, EntityData::Field491Value field491) const {
	for (uint i = 1; i < _entities.size(); i++) {

		if (checkFields1((EntityIndex)i, car, field491))
			return false;
	}
	return true;
}

bool Entities::checkFields19(EntityIndex entity, CarIndex car, EntityData::Field491Value field491) const {

	if (getData(entity)->car != car ||  getData(entity)->field_493 != EntityData::kField493_1)
		return false;

	EntityData::Field491Value entity_field491 = getData(entity)->field_491;

	// Test values
	if (field491 == EntityData::kField491_4455) {
		if (entity_field491 == EntityData::kField491_4070 || entity_field491 == EntityData::kField491_4455 || entity_field491 == EntityData::kField491_4840)
			return true;

		return false;
	}

	if (field491 == EntityData::kField491_6130) {
		if (entity_field491 == EntityData::kField491_5790 || entity_field491 == EntityData::kField491_6130 || entity_field491 == EntityData::kField491_6470)
			return true;

		return false;
	}

	if (field491 != EntityData::kField491_7850
	 || (entity_field491 != EntityData::kField491_7500 && entity_field491 != EntityData::kField491_7850 && entity_field491 != EntityData::kField491_8200))
		return false;

	return true;
}

bool Entities::checkFields20(EntityIndex entity) const {
	return checkFields5(entity, kCarBaggage)
		&& getData(entity)->field_491 >= EntityData::kField491_4500
		&& getData(entity)->field_491 <= EntityData::kField491_5500;
}

bool Entities::checkFields21(EntityIndex entity) const {
	return checkFields5(entity, kCarBaggage) && getData(entity)->field_491 < EntityData::kField491_4500;
}

bool Entities::checkFields22(EntityIndex entity) const {
	return checkFields5(entity, kCarKronos)
		&& getData(entity)->field_491 >= EntityData::kField491_3500
		&& getData(entity)->field_491 <= EntityData::kField491_5500;
}

bool Entities::checkFields23(EntityIndex entity) const {
	return checkFields5(entity, kCarKronos) && getData(entity)->field_491 > EntityData::kField491_7900;
}

bool Entities::checkFields24(EntityIndex entity, EntityData::Field491Value field491, int absValue) const {
	return absValue >= abs(getData(entity)->field_491 - field491);
}

bool Entities::checkFields25(EntityIndex entity) const {
	if (getData(entity)->direction == kDirectionUp && getLogic()->checkSceneFields(kSceneNone, true))
		return true;

	return (getData(entity)->direction == kDirectionDown && getLogic()->checkSceneFields(kSceneNone, false));
}


} // End of namespace LastExpress
