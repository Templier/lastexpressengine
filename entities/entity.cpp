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

#include "lastexpress/entities/entity_intern.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/state.h"
#include "lastexpress/game/savegame.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// EntityData
//////////////////////////////////////////////////////////////////////////
void EntityData::resetCurrentParameters() {
	// TODO see if this ever called without setting the call parameters just after
	// if not, we can optimize the thing and not instantiate an EntityCallParameters just to delete it afterwards
	_parameters[_data.current_call].clear();
	_parameters[_data.current_call].create();
}

void EntityData::saveLoadWithSerializer(Common::Serializer &) {
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

	// Zero-out passed pointers
	_engine = NULL;
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

//////////////////////////////////////////////////////////////////////////
// Shared functions
//////////////////////////////////////////////////////////////////////////

void Entity::function1(const SavePoint &savepoint) {
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->checkEntity(_entityIndex, EntityData::kField495_3, (EntityData::Field491Value)params->param1))
			params->param1 = (params->param1 == 10000) ? 0 : 10000;
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_0;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_3;
		params->param1 = 10000;
		break;
	}
}

void Entity::function1Clothes(const SavePoint &savepoint) {
	// Handle kAction1
	if (savepoint.action == kAction1) {

		// Select next available clothes
		_data->getData()->clothes = (EntityData::ClothesIndex)(_data->getData()->clothes + 1);
		if (_data->getData()->clothes > EntityData::kClothes3)
			_data->getData()->clothes = EntityData::kClothesDefault;

		return;
	}

	// Let the default function handle the other actions
	function1(savepoint);
}

//////////////////////////////////////////////////////////////////////////
// param1: ??
// param2: EventIndex
void Entity::savegame(const SavePoint &savepoint) {
	EntityData::EntityParametersIIII *params = (EntityData::EntityParametersIIII*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kActionDefault:
		save(_entityIndex, params->param1, (EventIndex)params->param2);
		CALL_PREVIOUS_SAVEPOINT()
		break;
	}
}

void Entity::playSound(const SavePoint &savepoint, bool resetItem, int param3) {
	EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kAction2:
		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kActionDefault:
		if (resetItem)
			_data->getData()->inventoryItem = kItemNone;

		getSound()->playSound(_entityIndex, params->seq1, param3);
		break;
	}
}

void Entity::draw(const SavePoint &savepoint) {
	EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kAction3:
		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(_entityIndex, params->seq1);
		break;
	}
}

void Entity::draw2(const SavePoint &savepoint) {
	EntityData::EntityParametersSSII *params = (EntityData::EntityParametersSSII*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kAction3:
		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(_entityIndex, params->seq1);
		getEntities()->drawSequenceRight((EntityIndex)params->param3, params->seq2);
		break;
	}
}

void Entity::updateFromTicks(const SavePoint &savepoint) {
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FROM_TICKS(2, 1)
		CALL_PREVIOUS_SAVEPOINT()
		break;
	}
}

void Entity::updateFromTime(const SavePoint &savepoint) {
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FROM_TIME(2, params->param1)
		CALL_PREVIOUS_SAVEPOINT()
		break;
	}
}


void Entity::savepointDirection(const SavePoint &savepoint) {
	switch (savepoint.action) {
	default:
		break;

	case kAction3:
		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kActionDefault:
		if (_data->getData()->direction != kDirectionRight)
			CALL_PREVIOUS_SAVEPOINT()
		break;
	}
}

void Entity::savepointCheckFields11(const SavePoint &savepoint) {
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
	case kActionDefault:
		if (getEntities()->checkFields11())
			CALL_PREVIOUS_SAVEPOINT()
		break;
	}
}

void Entity::savepointCheckEntity(const SavePoint &savepoint) {
	EntityData::EntityParametersIIII *params = (EntityData::EntityParametersIIII*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
	case kActionDefault:
		if (getEntities()->checkEntity(_entityIndex, (EntityData::Field495Value)params->param1, (EntityData::Field491Value)params->param2))
			CALL_PREVIOUS_SAVEPOINT()
		break;
	}
}

void Entity::savepointCall(const SavePoint &savepoint) {
	EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kAction3:
		if (!CURRENT_PARAMS(1, 1))
			getSavePoints()->call(_entityIndex, (EntityIndex)params->param2, (ActionIndex)params->param3, params->seq2);
		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kAction10:
		if (!CURRENT_PARAMS(1, 1)) {
			getSavePoints()->call(_entityIndex, (EntityIndex)params->param2, (ActionIndex)params->param3, params->seq2);
			CURRENT_PARAMS(1, 1) = 1;
		}
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(_entityIndex, params->seq1);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// param1: sequence
// param2: object index
void Entity::updateFields(const SavePoint &savepoint) {
	EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kAction3:
		getEntities()->updateFields1(_entityIndex, (ObjectIndex)params->param2);
		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(_entityIndex, params->seq1);
		getEntities()->updateFields0(_entityIndex, (ObjectIndex)params->param2);
		break;
	}
}

void Entity::updateField1000(const SavePoint &savepoint) {
	EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kAction3:
		getEntities()->updateField1000(_entityIndex, params->param2, params->param3);
		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(_entityIndex, params->seq1);
		getEntities()->updateField1000ProcessScene(_entityIndex, params->param2, params->param3);
		break;
	}
}

} // End of namespace LastExpress
