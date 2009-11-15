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

#include "lastexpress/entities/chapters.h"

#include "lastexpress/game/logic.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// Entities
//////////////////////////////////////////////////////////////////////////
Entities::Entities(LastExpressEngine *engine) : _engine(engine) {
	_chapters = new Chapters(engine);
}

Entities::~Entities() {
	delete _chapters;
}

void Entities::load(int callbackIndex) {

}

void Entities::setup(Entity::ChapterIndex chapter) {
	// TODO if chapter is not 0
	//  - reset current call for every entity & another entry
	//  - raw sequences
	//  - reset savegame fields (4x1000 & the two 4x16)

	if (chapter < 2)
		_chapters->setup(chapter);
}


void Entities::saveLoadWithSerializer(Common::Serializer &ser) {
	_chapters->saveLoadWithSerializer(ser);
}


//////////////////////////////////////////////////////////////////////////
// Entity
//////////////////////////////////////////////////////////////////////////
Entity::~Entity() {
	for (uint i = 0; i < _callbacks.size(); i++)
		delete _callbacks[i];
}

void Entity::setup(ChapterIndex index) {
	switch(index) {
	case kCustom:
		getSavePoints()->setCallback(_entityIndex, _callbacks[_data.callbacks[_data.current_call]]);
		break;

	case kChapter1:
		setup_chapter1();
		break;

	case kChapter2:
		setup_chapter2();
		break;

	case kChapter3:
		setup_chapter3();
		break;

	case kChapter4:
		setup_chapter4();
		break;

	case kChapter5:
		setup_chapter5();
		break;

	default:
		break;
	}
}

void Entity::call(FunctionPointer function, int param1, int param2, int param3, int param4) {
	_data.current_call++;
	(*function)(param1, param2, param3, param4);
}

void Entity::saveLoadWithSerializer(Common::Serializer &ser) {

}


} // End of namespace LastExpress
