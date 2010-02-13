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

const static EntityData::Field491Value field491_values[9] = {EntityData::kField491_0, EntityData::kField491_8200, EntityData::kField491_7500, EntityData::kField491_6470, EntityData::kField491_5790, EntityData::kField491_4840, EntityData::kField491_4070, EntityData::kField491_3050, EntityData::kField491_2740};

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
}

Entities::~Entities() {
	delete _header;

	for (uint i = 0; i < _entities.size(); i++)
		delete _entities[i];
}

void Entities::setup(ChapterIndex chapter) {
	if (chapter) {
		// Reset current call, inventory item & draw sequences
		for (uint i = 1; i < _entities.size(); i++) {
			_entities[i]->getData()->getData()->current_call = 0;
			_entities[i]->getData()->getData()->inventoryItem = kItemNone;

			prepareSequences((EntityIndex)i);
		}

		// Move that to reset method in state
		memset(getState()->field1000, 0, 1000*sizeof(int));
		memset(getState()->field16, 0, 16*sizeof(int));
		memset(getState()->field16_2, 0, 16*sizeof(int));

		// FIXME call to sound cache
	}

	// Skip "header"
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
		resetEntity((EntityIndex)i);

	warning("Entities::reset: not implemented!");
}

void Entities::resetEntity(EntityIndex entity) {
	warning("Entities::resetEntity: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Scene setup & drawing
//////////////////////////////////////////////////////////////////////////

void Entities::resetEntityState(EntityIndex entityIndex) {
	EntityData *data = getData(entityIndex);

	data->getData()->current_call = 0;
	data->getData()->inventoryItem = kItemNone;

	if (getSound()->isBuffered(entityIndex))
		getSound()->reset(entityIndex);

	prepareSequences(entityIndex);

	// update fields 4x1000, 4x16 & 4x16_2

	warning("Entities::resetEntity: not implemented!");
}

void Entities::updateFields() {
	if (!getFlags()->gameRunning)
		return;

	for (uint i = 0; i < _entities.size(); i++) {

		if (!getSavePoints()->getCallback((EntityIndex)i))
			continue;

		EntityData::Field491Value field_491 = _entities[i]->getData()->getData()->field_491;
		byte field_49A = _entities[i]->getData()->getData()->direction;
		int16 field_4A3 = _entities[i]->getData()->getData()->field_4A3;
		int16 field_4AB = _entities[i]->getData()->getData()->field_49B;

		switch (field_49A) {
		default:
			break;

		case 1:
		case 2:	// Replace calls to CheckFields8
			if (field_49A != 1 || (field_491 + field_4A3 * 10) >= 10000)
			{
				if (field_49A == 2) {
					if (field_491 > field_4A3 * 10)
						_entities[i]->getData()->getData()->field_491 = (EntityData::Field491Value)(_entities[i]->getData()->getData()->field_491 - field_4A3 * 10);
				}
			} else {
				_entities[i]->getData()->getData()->field_491 = (EntityData::Field491Value)(_entities[i]->getData()->getData()->field_491 + field_4A3 * 10);
			}
			break;

		case 3:
			_entities[i]->getData()->getData()->field_49D += 1;
			break;

		case 4:
			_entities[i]->getData()->getData()->field_4A1 += 9;
			break;

		case 5:
			if (field_4AB == 4)
				_entities[i]->getData()->getData()->field_4A1 += 9;
			break;

		}
	}
}

void Entities::setupSequences() {
	if (!getFlags()->gameRunning)
		return;

	// Update the train clock
	getLogic()->updateTrainClock();

	//////////////////////////////////////////////////////////////////////////
	// First pass: Drawing
	//////////////////////////////////////////////////////////////////////////
	for (uint i = 1; i < _entities.size(); i++) {
		EntityIndex entityIndex = (EntityIndex)i;

		if (!getSavePoints()->getCallback(entityIndex))
			continue;

		EntityData::EntityCallData *data = getData(entityIndex)->getData();

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

		if (data->direction == kDirection5) {

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

			data->direction = data->field_4AB;
			data->field_49D = -1;
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
		for (uint i = 1; i < _entities.size(); i++) {
			if (getFlags()->flag_entities_0)
				break;

			if (getSavePoints()->getCallback((EntityIndex)i)) {
				if (_entities[i]->getData()->getData()->field_4A8) {
					processed = true;
					processEntity((EntityIndex)i);
				}
			}
		}
	} while (!processed);
}

void Entities::processEntity(EntityIndex entity) {
	getFlags()->flag_entities_0 = true;
	warning("Entities::processEntity: not implemented!");
}

int Entities::getSoundValue(EntityIndex index) {
	error("Entities::getSoundValue: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
/// Fields update

void Entities::updateField1000(EntityIndex entity, int index, int value) {
	error("Entities::updateField1000: not implemented!");
}

void Entities::updateField1000ProcessScene(EntityIndex entity, int index, int value) {
	error("Entities::updateField1000: not implemented!");
}

void Entities::updateField1000_4(EntityIndex entity, ObjectIndex object) {
	error("Entities::updateField1000_4: not implemented!");
}

void Entities::updateField1000_5(EntityIndex entity, ObjectIndex object) {
	error("Entities::updateField1000_5: not implemented!");
}

void Entities::updateFields0(EntityIndex entity, ObjectIndex object) {
	error("Entities::updateFields0: not implemented!");
}

void Entities::updateFields1(EntityIndex entity, ObjectIndex object) {
	error("Entities::updateFields1: not implemented!");
}

void Entities::updateFields2(EntityIndex entity, ObjectIndex object) {
	error("Entities::updateFields2: not implemented!");
}

void Entities::updateFields3(EntityIndex entity, ObjectIndex object) {
	error("Entities::updateFields2: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Accessors
Entity *Entities::get(EntityIndex entity) {
	assert((uint)entity < _entities.size());

	if (entity == kEntityNone)
		error("Cannot get entity for index = 0!");

	return _entities[entity];
}

EntityData *Entities::getData(EntityIndex entity) {
	assert((uint)entity < _entities.size());

	if (entity == kEntityNone)
		return _header;

	return _entities[entity]->getData();
}

void Entities::saveLoadWithSerializer(Common::Serializer &ser) {
	_header->saveLoadWithSerializer(ser);
	for (uint i = 1; i < _entities.size(); i++)
		_entities[i]->saveLoadWithSerializer(ser);
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
	debugC(8, kLastExpressDebugLogic, "Drawing sequences for entity %d", index);



	warning("Entities::drawSequences: not implemented!");
}

void Entities::drawSequenceInternal(EntityIndex index, const char* sequence, EntityDirection direction) {
	debugC(8, kLastExpressDebugLogic, "Drawing sequence %s for entity %d (%d)", sequence, index, direction);

	// Copy sequence name
	Common::String processedName(sequence);
	processedName.toUppercase();
	processedName += "-";

	strcpy(getData(index)->getData()->sequenceName, processedName.c_str());

	// Reset fields
	getData(index)->getData()->field_49B = 0;
	getData(index)->getData()->field_49D = 0;
	getData(index)->getData()->field_4A1 = 0;

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
	EntityData::EntityCallData *data = getData(index)->getData();
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
			if (_header->getData()->field_491 > data->field_491)
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
			if (_header->getData()->field_491 <= data->field_491)
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
			if (_header->getData()->field_491 > data->field_491)
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
			if (_header->getData()->field_491 < data->field_491)
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
			if (_header->getData()->field_491 >= data->field_491)
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
			if (_header->getData()->field_491 < data->field_491)
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
			if (_header->getData()->field_491 > EntityData::kField491_8013)
				sprintf(sequence1, "%02d%01d-40d.seq", index, data->clothes);
			break;
		}
		break;

	// First part of sequence is already set
	case kDirectionLeft:
	case kDirectionRight:
		sprintf(sequence1, "%s%02d.seq", data->sequenceName, position);
		break;
	}
}

bool Entities::checkSequence0(EntityIndex entity) {
	return (getData(entity)->getData()->sequence0 && (getData(entity)->getData()->sequence0->getFrameInfo(0)->subType != 3));
}

//////////////////////////////////////////////////////////////////////////
//	Checks
//////////////////////////////////////////////////////////////////////////
bool Entities::compare(EntityIndex entity1, EntityIndex entity2) {
	error("Entities::compare: not implemented!");
}

bool Entities::checkEntity(EntityIndex entity, EntityData::Field495Value field495, EntityData::Field491Value field491) {
	error("Entities::checkEntity: not implemented!");
}

bool Entities::checkFields1(EntityIndex entity, EntityData::Field495Value field495, EntityData::Field491Value field491) {
	return (getEntityData(entity)->field_491 == field491 
		 && getEntityData(entity)->field_493 == EntityData::kField493_1 
		 && getEntityData(entity)->field_495 == field495);
}

bool Entities::checkFields2(ObjectIndex object) {

	EntityData::Field491Value field491 = EntityData::kField491_0;
	EntityData::Field495Value field495 = EntityData::kField495_0;

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
		field495 = EntityData::kField495_3;
		if (checkFields1(kEntityNone, field495, field491))
			return false;
		break;

	case kObjectHandleBathroom:
	case kObjectHandleInsideBathroom:
	case kObjectKitchen:
	case kObject20:
	case kObject21:
	case kObject22:
		field491 = field491_values[object-17];
		field495 = EntityData::kField495_3;
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
		field495 = EntityData::kField495_4;
		if (checkFields1(kEntityNone, field495, field491))
			return false;
		break;

	case kObject48:
	case kObject49:
	case kObject50:
	case kObject51:
	case kObject52:
	case kObject53:
		field491 = field491_values[object-48];
		field495 = EntityData::kField495_4;
		break;

	}

	uint index = 1;
	while (!checkFields1((EntityIndex)index, field495, field491) || index == kEntityVassili) {
		index++;
		if (index >= 40)
			return false;
	}

	return true;
}

bool Entities::checkFields3(EntityIndex entity) {
	return (getEntityData(entity)->field_495 == EntityData::kField495_3 
		 || getEntityData(entity)->field_495 == EntityData::kField495_4)
		 && getEntityData(entity)->field_493 == EntityData::kField493_1;
}

bool Entities::checkFields4(EntityData::Field495Value field495, int position) {
	loadSceneObject(scene, getState()->scene);

	return getEntityData(kEntityNone)->field_495 == field495 && scene.getHeader()->position == position;
}

bool Entities::checkFields5(EntityIndex entity, EntityData::Field495Value field495) {
	return getEntityData(entity)->field_495 == field495 && getEntityData(entity)->field_493 < EntityData::kField493_2;
}

bool Entities::checkFields6(EntityIndex entity) {
	return checkFields5(entity, EntityData::kField495_3) && getEntityData(entity)->field_491 < EntityData::kField491_850;
}

bool Entities::checkFields7(EntityData::Field495Value field495) {
	return checkFields5(kEntityNone, field495) && !getEntityData(kEntityNone)->field_493 && !checkFields6(kEntityNone);
}

bool Entities::isDirectionUpOrDown(EntityIndex entity) {
	return getEntityData(entity)->direction == kDirectionUp || getEntityData(entity)->direction == kDirectionDown;
}

bool Entities::checkFields9(EntityIndex entity1, EntityIndex entity2, int absValue) {
	return getEntityData(entity1)->field_495 == getEntityData(entity2)->field_495
	    && abs(getEntityData(entity1)->field_491 - getEntityData(entity2)->field_491) <= absValue
		&& (getEntityData(entity1)->field_493 != EntityData::kField493_2 || getEntityData(entity2)->field_493 != EntityData::kField493_2);
}

bool Entities::checkFields10(EntityIndex entity) {
	return getEntityData(entity)->field_493 < EntityData::kField493_3;
}

bool Entities::checkFields11() {
	for (uint i = 1; i < _entities.size(); i++) {
		EntityIndex index = (EntityIndex)i;

		if (!getEntityData(index)->field_493
		 && checkFields12(index)
		 || checkFields13(index))
			return false;
	}	
	return true;
}

bool Entities::checkFields12(EntityIndex entity) {
	return checkFields5(entity, EntityData::kField495_5)
		&& getEntityData(entity)->field_491 >= EntityData::kField491_1540
		&& getEntityData(entity)->field_491 <= EntityData::kField491_3650;
}

bool Entities::checkFields13(EntityIndex entity) {
	return checkFields5(entity, EntityData::kField495_5)
		&& getEntityData(entity)->field_491 >= EntityData::kField491_3650
		&& getEntityData(entity)->field_491 <= EntityData::kField491_5800;
}

bool Entities::checkFields14(EntityIndex entity) {
	return checkFields5(entity, EntityData::kField495_2)
		&& getEntityData(entity)->field_491 >= EntityData::kField491_5500
		&& getEntityData(entity)->field_491 <= EntityData::kField491_7500;
}

bool Entities::checkFields15() {
	return (getEntityData(kEntityNone)->field_491 == EntityData::kField491_7500 || getEntityData(kEntityNone)->field_491 == EntityData::kField491_8200)
		 && getEntityData(kEntityNone)->field_493 == EntityData::kField493_2
		 && getEntityData(kEntityNone)->field_495 == EntityData::kField495_3;
}

bool Entities::checkFields16() {
	return (getEntityData(kEntityNone)->field_491 == EntityData::kField491_4070 || getEntityData(kEntityNone)->field_491 == EntityData::kField491_4840)
		 && getEntityData(kEntityNone)->field_493 == EntityData::kField493_2
		 && getEntityData(kEntityNone)->field_495 == EntityData::kField495_4;
}

bool Entities::checkFields17(EntityIndex entity) {
	return checkFields5(entity, EntityData::kField495_5) && getEntityData(entity)->field_491 > EntityData::kField491_5800;
}

bool Entities::checkFields18(EntityData::Field495Value field495, EntityData::Field491Value field491) {
	for (uint i = 1; i < _entities.size(); i++) {
		
		if (checkFields1((EntityIndex)i, field495, field491))
			return false;
	}	
	return true;
}

bool Entities::checkFields19(EntityIndex entity, EntityData::Field495Value field495, EntityData::Field491Value field491) {
	
	if (getEntityData(entity)->field_495 != field495 ||  getEntityData(entity)->field_493 != EntityData::kField493_1)
		return false;

	EntityData::Field491Value entity_field491 = getEntityData(entity)->field_491;

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

bool Entities::checkFields20(EntityIndex entity) {
	return checkFields5(entity, EntityData::kField495_6)
		&& getEntityData(entity)->field_491 >= EntityData::kField491_4500
		&& getEntityData(entity)->field_491 <= EntityData::kField491_5500;
}

bool Entities::checkFields21(EntityIndex entity) {
	return checkFields5(entity, EntityData::kField495_6) && getEntityData(entity)->field_491 < EntityData::kField491_4500;
}

bool Entities::checkFields22(EntityIndex entity) {
	return checkFields5(entity, EntityData::kField495_2)
		&& getEntityData(entity)->field_491 >= EntityData::kField491_3500
		&& getEntityData(entity)->field_491 <= EntityData::kField491_5500;
}

bool Entities::checkFields23(EntityIndex entity) {
	return checkFields5(entity, EntityData::kField495_2) && getEntityData(entity)->field_491 > EntityData::kField491_7900;
}

bool Entities::checkFields24(EntityIndex entity, EntityData::Field491Value field491, int absValue) {
	return absValue >= abs(getEntityData(entity)->field_491 - field491);
}

bool Entities::checkFields25(EntityIndex entity) {
	if (getEntityData(entity)->direction == kDirectionUp && getLogic()->checkSceneFields(0, true))
		return true;

	return (getEntityData(entity)->direction == kDirectionDown && getLogic()->checkSceneFields(0, false));
}


} // End of namespace LastExpress
