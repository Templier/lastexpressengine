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

// Entities
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

#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

const static int field491_values[9] = {0, 8200, 7500, 6470, 5790, 4840, 4070, 3050, 2740};

#define ADD_ENTITY(class) \
	_entities.push_back(new class(engine));

//////////////////////////////////////////////////////////////////////////
// Entities
//////////////////////////////////////////////////////////////////////////
Entities::Entities(LastExpressEngine *engine) : _engine(engine) {
	_header = new EntityData();

	_entities.push_back(NULL);		// Header
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
	_entities.push_back(new Tables(engine, SavePoints::kEntityTables0));
	_entities.push_back(new Tables(engine, SavePoints::kEntityTables1));
	_entities.push_back(new Tables(engine, SavePoints::kEntityTables2));
	_entities.push_back(new Tables(engine, SavePoints::kEntityTables3));
	_entities.push_back(new Tables(engine, SavePoints::kEntityTables4));
	_entities.push_back(new Tables(engine, SavePoints::kEntityTables5));

	ADD_ENTITY(Entity39);
}

Entities::~Entities() {	
	delete _header;

	for (uint i = 0; i < _entities.size(); i++)
		delete _entities[i];
}

void Entities::setup(State::ChapterIndex chapter) {
	if (chapter) {
		// Reset current call, inventory item & draw sequences
		for (uint i = 1; i < _entities.size(); i++) {
			_entities[i]->getData()->getData()->current_call = 0;
			_entities[i]->getData()->getData()->inventoryItem = Inventory::kNoItem;

			drawSequences((SavePoints::EntityIndex)i);
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
		if (i == SavePoints::kEntityChapters && chapter >= 2)			
			continue;	

		_entities[i]->setup(chapter);
	}
}

void Entities::reset(SavePoints::EntityIndex entity) {
	EntityData *data = getData(entity);

	data->getData()->current_call = 0;
	data->getData()->inventoryItem = Inventory::kNoItem;

	// TODO clear sound cache for entity

	drawSequences(entity);
	
	// update fields 4x1000, 4x16 & 4x16_2
}

//////////////////////////////////////////////////////////////////////////
// Scene setup & drawing
void Entities::updateFields() {
	if (!getFlags()->flag_1)
		return;

	for (uint i = 0; i < _entities.size(); i++) {
		
		if (!getSavePoints()->getCallback((SavePoints::EntityIndex)i))
			continue;

		byte field_491 = _entities[i]->getData()->getData()->field_491;
		byte field_49A = _entities[i]->getData()->getData()->field_49A;
		int16 field_4A3 = _entities[i]->getData()->getData()->field_4A3;
		byte field_4AB = _entities[i]->getData()->getData()->field_49B;
		
		switch (field_49A) {
		default:
			break;

		case 1:
		case 2:	// Replace calls to CheckFields8
			if (field_49A != 1 || (field_491 + field_4A3 * 10) >= 10000)			
			{	
				if (field_49A == 2) {
					if (field_491 > field_4A3 * 10)
						_entities[i]->getData()->getData()->field_491 -= field_4A3 * 10;
				}
			} else {
				_entities[i]->getData()->getData()->field_491 += field_4A3 * 10;
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
	if (!getFlags()->flag_1)
		return;

	error("Entities::setupSequences: not implemented!");

}

void Entities::setupCallbacks() {
	if (!getFlags()->flag_1)
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

		if (getSavePoints()->getCallback((SavePoints::EntityIndex)i))
			processEntity((SavePoints::EntityIndex)i);
	}

	if (getFlags()->flag_entities_0)
		return;


	bool processed = false;
	do {
		for (uint i = 1; i < _entities.size(); i++) {
			if (getFlags()->flag_entities_0)
				break;

			if (getSavePoints()->getCallback((SavePoints::EntityIndex)i)) {
				if (_entities[i]->getData()->getData()->field_4A8) {
					processed = true;
					processEntity((SavePoints::EntityIndex)i);
				}				
			}
		}
	} while (!processed);
}

void Entities::processEntity(SavePoints::EntityIndex entity) {
	error("Entities::processEntity: not implemented!");
}


//////////////////////////////////////////////////////////////////////////
// Accessors
Entity *Entities::get(SavePoints::EntityIndex entity) {
	assert((uint)entity < _entities.size());

	if (entity == SavePoints::kEntityNone)
		error("Cannot get entity for index = 0!");

	return _entities[entity];
}

EntityData *Entities::getData(SavePoints::EntityIndex entity) {
	assert((uint)entity < _entities.size());

	if (entity == 0)
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
void Entities::storeSequenceName(SavePoints::EntityIndex entity, const char* sequence) {
	error("Entities::storeSequenceName: not implemented!");
}

void Entities::drawSequence(SavePoints::EntityIndex entity, const char* sequence) {
	warning("Entities::drawSequence: not implemented!");
}

void Entities::drawSequences(SavePoints::EntityIndex entity) {
	warning("Entities::drawSequences: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
//	Checks
//////////////////////////////////////////////////////////////////////////
bool Entities::compare(SavePoints::EntityIndex entity1, SavePoints::EntityIndex entity2) {
	error("Entities::compare: not implemented!");
}

bool Entities::checkEntity(SavePoints::EntityIndex entity, int field495, int field491) {
	error("Entities::checkEntity: not implemented!");
}

bool Entities::checkFields1(SavePoints::EntityIndex entity, int field495, int field491) {
	return (getData(entity)->getData()->field_491 == field491 && getData(entity)->getData()->field_493 == 1 && getData(entity)->getData()->field_495 == field495);
}

bool Entities::checkFields2(Objects::ObjectIndex object) {

	int field491 = 0;
	int field495 = 0;	

	switch (object) {
	default:
		return false;

	case Objects::kObjectCompartment1:
	case Objects::kObjectCompartment2:
	case Objects::kObjectCompartment3:
	case Objects::kObjectCompartment4:
	case Objects::kObjectCompartment5:
	case Objects::kObjectCompartment6:
	case Objects::kObjectCompartment7:
	case Objects::kObjectCompartment8:
		field491 = field491_values[object];
		field495 = 3;
		if (checkFields1(SavePoints::kEntityNone, field495, field491))
			return false;
		break;

	case Objects::kObjectHandleBathroom:
	case Objects::kObjectHandleInsideBathroom:
	case Objects::kObjectKitchen:
	case Objects::kObject20:
	case Objects::kObject21:
	case Objects::kObject22:
		field491 = field491_values[object-17];
		field495 = 3;
		break;

	case Objects::kObjectCompartmentA:
	case Objects::kObjectCompartmentB:
	case Objects::kObjectCompartmentC:
	case Objects::kObjectCompartmentD:
	case Objects::kObjectCompartmentE:
	case Objects::kObjectCompartmentF:
	case Objects::kObjectCompartmentG:
	case Objects::kObjectCompartmentH:
		field491 = field491_values[object-32];
		field495 = 4;
		if (checkFields1(SavePoints::kEntityNone, field495, field491))
			return false;
		break;

	case Objects::kObject48:
	case Objects::kObject49:
	case Objects::kObject50:
	case Objects::kObject51:
	case Objects::kObject52:
	case Objects::kObject53:
		field491 = field491_values[object-48];
		field495 = 4;
		break;

	}

	uint index = 1;
	while (!checkFields1((SavePoints::EntityIndex)index, field495, field491) || index == SavePoints::kEntityVassili) {
		index++;
		if (index >= 40)
			return false;
	}
	
	return true;
}

bool Entities::checkFields3(SavePoints::EntityIndex entity) {
	return (getData(entity)->getData()->field_495 == 3 || getData(entity)->getData()->field_495 == 4) && getData(entity)->getData()->field_493 == 1;
}

bool Entities::checkFields4(int field495, int field15) {

	Scene *scene = _engine->getScene(getState()->scene);
	bool ret = getData(SavePoints::kEntityNone)->getData()->field_495 == field495 && scene->getHeader()->field_15 == field15;
	delete scene;

	return ret;
}

bool Entities::checkFields5(SavePoints::EntityIndex entity, int field495) {
	return getData(entity)->getData()->field_495 == field495 && getData(entity)->getData()->field_493 < 2;
}


bool Entities::checkFields6(SavePoints::EntityIndex entity) {
	return checkFields5(entity, 3) && getData(entity)->getData()->field_491 < 850;
}

bool Entities::checkFields7(int field495) {
	return checkFields5(SavePoints::kEntityNone, field495) && !getData(SavePoints::kEntityNone)->getData()->field_493 && !checkFields6(SavePoints::kEntityNone);
}

bool Entities::checkFields8(SavePoints::EntityIndex entity) {
	return getData(entity)->getData()->field_49A == 1 || getData(entity)->getData()->field_49A == 2;
}

bool Entities::checkFields9(SavePoints::EntityIndex entity1, SavePoints::EntityIndex entity2, int value) {
	return getData(entity1)->getData()->field_495 == getData(entity2)->getData()->field_495
		&& abs(getData(entity1)->getData()->field_491 - getData(entity2)->getData()->field_491) <= value
		&& (getData(entity1)->getData()->field_493 !=2 || getData(entity2)->getData()->field_493 != 2);
}

bool Entities::checkFields10(SavePoints::EntityIndex entity) {
	return getData(entity)->getData()->field_493 < 3;
}

} // End of namespace LastExpress
