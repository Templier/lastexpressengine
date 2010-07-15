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
		if (getEntities()->checkEntity(_entityIndex, kCarGreenSleeping, (EntityPosition)params->param1))
			params->param1 = (params->param1 == 10000) ? 0 : 10000;
		break;

	case kActionDefault:
		getData()->position = kPositionNone;
		getData()->field_493 = kField493_0;
		getData()->car = kCarGreenSleeping;
		params->param1 = 10000;
		break;
	}
}

void Entity::function1Clothes(const SavePoint &savepoint) {
	// Handle kAction1
	if (savepoint.action == kAction1) {

		// Select next available clothes
		getData()->clothes = (ClothesIndex)(getData()->clothes + 1);
		if (getData()->clothes > kClothes3)
			getData()->clothes = kClothesDefault;

		return;
	}

	// Let the default function handle the other actions
	function1(savepoint);
}

//////////////////////////////////////////////////////////////////////////
// param1: savegame entry type
// param2: EventIndex
void Entity::savegame(const SavePoint &savepoint) {
	EntityData::EntityParametersIIII *params = (EntityData::EntityParametersIIII*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALLBACK_ACTION()
		break;

	case kActionDefault:
		save(_entityIndex, (SavegameType)params->param1, (EventIndex)params->param2);
		CALLBACK_ACTION()
		break;
	}
}

void Entity::playSound(const SavePoint &savepoint, bool resetItem, int param3) {
	EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kAction2:
		CALLBACK_ACTION()
		break;

	case kActionDefault:
		if (resetItem)
			getData()->inventoryItem = kItemNone;

		getSound()->playSound(_entityIndex, params->seq1, param3);
		break;
	}
}

void Entity::draw(const SavePoint &savepoint) {
	EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION()
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

	case kActionExitCompartment:
		CALLBACK_ACTION()
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
		UPDATE_PARAM(params->param2, getState()->timeTicks, 1)
		CALLBACK_ACTION()
		break;
	}
}

void Entity::updateFromTime(const SavePoint &savepoint) {
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM(params->param2, getState()->time, params->param1)
		CALLBACK_ACTION()
		break;
	}
}


void Entity::savepointDirection(const SavePoint &savepoint) {
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION()
		break;

	case kActionDefault:
		if (getData()->direction != kDirectionRight)
			CALLBACK_ACTION()
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
			CALLBACK_ACTION()
		break;
	}
}

void Entity::checkEntity(const SavePoint &savepoint) {
	EntityData::EntityParametersIIII *params = (EntityData::EntityParametersIIII*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
	case kActionDefault:
		if (getEntities()->checkEntity(_entityIndex, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION()
		break;
	}
}

void Entity::savepointCall(const SavePoint &savepoint) {
	EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		if (!CURRENT_PARAMS(1, 1))
			getSavePoints()->call(_entityIndex, (EntityIndex)params->param2, (ActionIndex)params->param3, params->seq2);
		CALLBACK_ACTION()
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
void Entity::enterExitCompartment(const SavePoint &savepoint) {
	EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->exitCompartment(_entityIndex, (ObjectIndex)params->param2);
		CALLBACK_ACTION()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(_entityIndex, params->seq1);
		getEntities()->enterCompartment(_entityIndex, (ObjectIndex)params->param2);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - Sequence
//  - CarIndex
//  - Position
void Entity::updatePosition(const SavePoint &savepoint) {
	EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters();

	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->updatePosition(_entityIndex, (CarIndex)params->param2, (Position)params->param3);
		CALLBACK_ACTION()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(_entityIndex, params->seq1);
		getEntities()->updatePosition(_entityIndex, (CarIndex)params->param2, (Position)params->param3, true);
		break;
	}
}

} // End of namespace LastExpress
