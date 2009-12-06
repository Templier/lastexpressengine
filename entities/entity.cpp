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

#include "lastexpress/game/state.h"
#include "lastexpress/game/savepoint.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// EntityData
//////////////////////////////////////////////////////////////////////////
void EntityData::setParameters(int callback, int index, EntityData::EntityParameters* parameters) {
	delete _parameters[_data.current_call].parameters[index];
	_parameters[_data.current_call].parameters[index] = parameters;
}

void EntityData::resetCurrentParameters() {
	// TODO see if this ever called without setting the call parameters just after
	// if not, we can optimize the thing and not instantiate an EntityCallParameters just to delete it afterwards
	_parameters[_data.current_call].clear();
	_parameters[_data.current_call].create();
}

void EntityData::saveLoadWithSerializer(Common::Serializer &ser) {
	error("EntityData::saveLoadWithSerializer: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Entity
//////////////////////////////////////////////////////////////////////////
Entity::Entity(LastExpressEngine *engine, EntityIndex index) : _engine(engine), _entityIndex(index) {
	_data = new EntityData();

	// Add first empty entry to callbacks array
	_callbacks.push_back(NULL);
}

Entity::~Entity() {
	for (uint i = 0; i < _callbacks.size(); i++)
		delete _callbacks[i];

	delete _data;
}

void Entity::setup(ChapterIndex index) {
	switch(index) {
	case kChapterAll:
		getSavePoints()->setCallback(_entityIndex, _callbacks[_data->getCurrentCallback()]);
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

} // End of namespace LastExpress
