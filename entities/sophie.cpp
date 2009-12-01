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

#include "lastexpress/entities/sophie.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

#define CHAPTER_IMPLEMENTATION() \
	switch (savepoint->action) { \
	default: \
		break; \
	case SavePoints::kActionNone: \
		setup_function3(); \
		break; \
	case SavePoints::kActionDefault: \
		getEntities()->drawSequences(SavePoints::kEntitySophie); \
		_data->getData()->field_491 = 4840; \
		_data->getData()->field_493 = 1; \
		_data->getData()->field_495 = 4; \
		_data->getData()->field_4A5 = 0; \
		_data->getData()->inventoryItem = Inventory::kNoItem; \
		break; \
	}

#define DEFAULT_ACTION_IMPLEMENTATION() \
	if (savepoint->action == SavePoints::kActionDefault) { \
		_data->getData()->field_491 = 4840; \
		_data->getData()->field_493 = 1; \
		_data->getData()->field_495 = 4; \
		getEntities()->drawSequences(SavePoints::kEntitySophie); \
	}

Sophie::Sophie(LastExpressEngine *engine) : Entity(engine, SavePoints::kEntitySophie) {
	ADD_CALLBACK_FUNCTION(Sophie, function1);
	ADD_CALLBACK_FUNCTION(Sophie, function2);
	ADD_CALLBACK_FUNCTION(Sophie, function3);
	ADD_CALLBACK_FUNCTION(Sophie, chapter1);
	ADD_CALLBACK_FUNCTION(Sophie, function5);
	ADD_CALLBACK_FUNCTION(Sophie, chapter2);
	ADD_CALLBACK_FUNCTION(Sophie, chapter3);
	ADD_CALLBACK_FUNCTION(Sophie, chapter4);
	ADD_CALLBACK_FUNCTION(Sophie, function9);
	ADD_CALLBACK_FUNCTION(Sophie, chapter5);
	ADD_CALLBACK_FUNCTION(Sophie, function11);
	ADD_NULL_FUNCTION();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, function1, 1) {
	FUNCTION_1_IMPLEMENTATION(SavePoints::kEntitySophie)
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_INT2(Sophie, function2, 2) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: {
		_data->getCurrentParameters(0)->param3 = 0;

		// Sophie
		byte field_49A = _data->getData()->field_49A;
		int16 field_491 = _data->getData()->field_491;
		int16 field_495 = _data->getData()->field_495;

		// Rebecca
		int16 rebecca_field_491 = getEntityData(SavePoints::kEntityRebecca)->field_491;
		int16 rebecca_field_495 = getEntityData(SavePoints::kEntityRebecca)->field_495;

		if (getEntities()->checkFields9(SavePoints::kEntitySophie, SavePoints::kEntityRebecca, 500)
		 || (field_49A == 1 && field_495 >= rebecca_field_495 && field_491 > rebecca_field_491)
		 || (field_49A == 2 && field_495 <= rebecca_field_495 && field_491 < rebecca_field_491)) {
			 _data->getData()->field_49B = 0;
			 _data->getCurrentParameters(0)->param3 = 1;
		}

		if (!_data->getCurrentParameters(0)->param3)
			getEntities()->checkEntity(SavePoints::kEntitySophie, _data->getCurrentParameters(0)->param1, _data->getCurrentParameters(0)->param2);

		break;
	}

	case SavePoints::kAction5:
		getSound()->excuseMeCath();
		break;

	case SavePoints::kAction6:
		getSound()->excuseMe(SavePoints::kEntitySophie, 0, 0);
		break;

	case SavePoints::kActionDefault:
		getEntities()->checkEntity(SavePoints::kEntitySophie, _data->getCurrentParameters(0)->param1, _data->getCurrentParameters(0)->param2);
		break;

	case SavePoints::kAction123668192:
		CALL_PREVIOUS_SAVEPOINT(SavePoints::kEntitySophie)
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, function3, 3) {
	switch (savepoint->action) {
	default:
		break;
		
	case SavePoints::kActionNone:
		_data->getData()->field_491 = getEntityData(SavePoints::kEntityRebecca)->field_491;
		_data->getData()->field_495 = getEntityData(SavePoints::kEntityRebecca)->field_495;
		break;

	case SavePoints::kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequences(SavePoints::kEntitySophie);
			break;

		case 2:
			getEntities()->drawSequence(SavePoints::kEntitySophie, "BLANK");
			break;

		case 3:
			getEntities()->drawSequences(SavePoints::kEntitySophie);
			break;

		case 4:
			getEntities()->drawSequence(SavePoints::kEntitySophie, "BLANK");
			break;
		}
		break;

	case SavePoints::kAction125242096:
		_data->getData()->field_491 = getEntityData(SavePoints::kEntityRebecca)->field_491 - 100;
		_data->getData()->field_493 = getEntityData(SavePoints::kEntityRebecca)->field_493;
		_data->getData()->field_495 = getEntityData(SavePoints::kEntityRebecca)->field_495;

		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Sophie, setup_function2), 5, 850);
		break;

	case SavePoints::kAction136654208:
		_data->getData()->field_491 = getEntityData(SavePoints::kEntityRebecca)->field_491 + 100;
		_data->getData()->field_493 = getEntityData(SavePoints::kEntityRebecca)->field_493;
		_data->getData()->field_495 = getEntityData(SavePoints::kEntityRebecca)->field_495;

		_data->setNextCallback(2);
		call(new ENTITY_SETUP_DEFAULT(Sophie, setup_function2), 4, 4840);
		break;

	case SavePoints::kAction259921280:
		_data->getData()->field_491 = getEntityData(SavePoints::kEntityRebecca)->field_491 + 100;
		_data->getData()->field_493 = getEntityData(SavePoints::kEntityRebecca)->field_493;
		_data->getData()->field_495 = getEntityData(SavePoints::kEntityRebecca)->field_495;
		
		_data->setNextCallback(3);
		call(new ENTITY_SETUP_DEFAULT(Sophie, setup_function2), 2, 9640);
		break;

	case SavePoints::kAction292775040:
		_data->getData()->field_491 = 9270;
		_data->getData()->field_493 = 0;
		_data->getData()->field_495 = 2;

		_data->setNextCallback(4);
		call(new ENTITY_SETUP_DEFAULT(Sophie, setup_function2), 4, 4840);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter1, 4) {
	switch (savepoint->action) {
	default:
		break;	

	case SavePoints::kActionNone:
		if (getState()->time > 1062000)
			if (!_data->getCurrentParameters(0)->param1) {
				_data->getCurrentParameters(0)->param1 = 1;
				setup_function3();
			}
		break;

	case SavePoints::kActionDefault: 
		_data->getData()->field_491 = 4840;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 4;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, function5, 5) {
	DEFAULT_ACTION_IMPLEMENTATION()
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter2, 6) {
	CHAPTER_IMPLEMENTATION()
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter3, 7) {
	CHAPTER_IMPLEMENTATION()
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter4, 8) {
	CHAPTER_IMPLEMENTATION()
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, function9, 9) {
	DEFAULT_ACTION_IMPLEMENTATION()
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter5, 10){
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone:
		setup_function11();
		break;

	case SavePoints::kActionDefault:
		getEntities()->drawSequences(SavePoints::kEntitySophie);

		_data->getData()->field_491 = 3969;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 5;

		_data->getData()->inventoryItem = Inventory::kNoItem;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, function11, 11) {
	if (savepoint->action == SavePoints::kAction70549068)
		setup_nullfunction();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_NULL_FUNCTION(Sophie, 12)

} // End of namespace LastExpress
