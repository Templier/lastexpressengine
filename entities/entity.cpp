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

#include "lastexpress/entities/entity.h"

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
#include "lastexpress/entities/entity24.h"
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
#include "lastexpress/entities/tables.h"
#include "lastexpress/entities/tatiana.h"
#include "lastexpress/entities/train.h"
#include "lastexpress/entities/vassili.h"
#include "lastexpress/entities/verges.h"
#include "lastexpress/entities/vesna.h"
#include "lastexpress/entities/yasmin.h"

#include "lastexpress/game/logic.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// Entities
//////////////////////////////////////////////////////////////////////////
Entities::Entities(LastExpressEngine *engine) : _engine(engine) {
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
	ADD_ENTITY(Entity24);	
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
	for (uint i = 0; i < _entities.size(); i++)
		delete _entities[i];
}

void Entities::load(int callbackIndex) {

}

void Entities::setup(Logic::ChapterIndex chapter) {
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
Entity::EntityData *Entities::getEntityData(uint index) {
	assert(index < _entities.size());

	if (index == 0)
		return &_header;

	return _entities[index]->getData();
}


// Serializer
void Entities::serialize(Common::Serializer &ser, Entity::EntityData *data) {
	// TODO implement
}

void Entities::saveLoadWithSerializer(Common::Serializer &ser) {
	serialize(ser, &_header);
	for (uint i = 1; i < _entities.size(); i++)
		serialize(ser, _entities[i]->getData());		
}


//////////////////////////////////////////////////////////////////////////
// Entity
//////////////////////////////////////////////////////////////////////////
Entity::Entity(LastExpressEngine *engine, SavePoints::EntityIndex index) : _engine(engine), _entityIndex(index) {
	// Add first empty entry to callbacks array
	_callbacks.push_back(NULL);
}

Entity::~Entity() {
	for (uint i = 0; i < _callbacks.size(); i++)
		delete _callbacks[i];
}

void Entity::setup(Logic::ChapterIndex index) {
	switch(index) {
	case Logic::kCustom:
		getSavePoints()->setCallback(_entityIndex, _callbacks[_data.callbacks[_data.current_call]]);
		break;

	case Logic::kChapter1:
		setup_chapter1();
		break;

	case Logic::kChapter2:
		setup_chapter2();
		break;

	case Logic::kChapter3:
		setup_chapter3();
		break;

	case Logic::kChapter4:
		setup_chapter4();
		break;

	case Logic::kChapter5:
		setup_chapter5();
		break;

	default:
		break;
	}
}

void Entity::call(FunctionPointer function, char* name, int param2, int param3, int param4) {
	_data.current_call++;
	(*function)(name, param2, param3, param4);
}

} // End of namespace LastExpress
