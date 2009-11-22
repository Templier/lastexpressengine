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
	_entities.push_back(new Tables(engine, 0));
	_entities.push_back(new Tables(engine, 1));
	_entities.push_back(new Tables(engine, 2));
	_entities.push_back(new Tables(engine, 3));
	_entities.push_back(new Tables(engine, 4));
	_entities.push_back(new Tables(engine, 5));

	ADD_ENTITY(Entity39);
}

Entities::~Entities() {	
	delete _header;

	for (uint i = 0; i < _entities.size(); i++)
		delete _entities[i];
}

void Entities::load(int callbackIndex) {

}

void Entities::setup(State::ChapterIndex chapter) {
	// TODO if chapter is not 0
	//  - reset current call for every entity & another entry
	//  - raw sequences
	//  - reset savegame fields (4x1000 & the two 4x16)

	// Skip "header"
	for (uint i = 1; i < _entities.size(); i++) {
		
		// Special case of chapters (prevents infinite loop as we will be called from Chapters functions when changing chapters)
		if (i == SavePoints::kChapters && chapter >= 2)			
			continue;	

		_entities[i]->setup(chapter);
	}
}

// Accessors
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
//	Checks
//////////////////////////////////////////////////////////////////////////
bool Entities::checkFields1(SavePoints::EntityIndex entity, int field495, int field491) {
	return (getData(entity)->getData()->field_491 == field491 && getData(entity)->getData()->field_493 == 1 && getData(entity)->getData()->field_495 == field495);
}

bool Entities::checkFields2(byte object) {

	int field491 = 0;
	int field495 = 0;	

	switch (object) {
	default:
		return false;

	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		field491 = field491_values[object];
		field495 = 3;
		if (checkFields1(SavePoints::kNone, field495, field491))
			return false;
		break;

	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
		field491 = field491_values[object-17];
		field495 = 3;
		break;

	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
		field491 = field491_values[object-32];
		field495 = 4;
		if (checkFields1(SavePoints::kNone, field495, field491))
			return false;
		break;

	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
		field491 = field491_values[object-48];
		field495 = 4;
		break;

	}

	uint index = 1;
	while (!checkFields1((SavePoints::EntityIndex)index, field495, field491) || index == SavePoints::kVassili) {
		index++;
		if (index >= 40)
			return false;
	}
	
	return true;
}

bool Entities::checkFields3(SavePoints::EntityIndex entity) {
	return (getData(entity)->getData()->field_495 == 3 || getData(entity)->getData()->field_495 == 4) && getData(entity)->getData()->field_493 == 1;
}

} // End of namespace LastExpress
