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
	case kActionNone: \
		setup_function3(); \
		break; \
	case kActionDefault: \
		getEntities()->drawSequences(kEntitySophie); \
		_data->getData()->field_491 = EntityData::kField491_4840; \
		_data->getData()->field_493 = EntityData::kField493_1; \
		_data->getData()->field_495 = EntityData::kField495_4; \
		_data->getData()->clothes = EntityData::kClothesDefault; \
		_data->getData()->inventoryItem = kItemNone; \
		break; \
	}

#define DEFAULT_ACTION_IMPLEMENTATION() \
	if (savepoint->action == kActionDefault) { \
		_data->getData()->field_491 = EntityData::kField491_4840; \
		_data->getData()->field_493 = EntityData::kField493_1; \
		_data->getData()->field_495 = EntityData::kField495_4; \
		getEntities()->drawSequences(kEntitySophie); \
	}

Sophie::Sophie(LastExpressEngine *engine) : Entity(engine, kEntitySophie) {
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
IMPLEMENT_FUNCTION(Sophie, function1, 1)
	FUNCTION_1_IMPLEMENTATION(kEntitySophie)
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(Sophie, function2, 2)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: {
		CURRENT_PARAM(3) = 0;

		// Sophie
		byte direction = _data->getData()->direction;
		EntityData::Field491Value field_491 = _data->getData()->field_491;
		EntityData::Field495Value field_495 = _data->getData()->field_495;

		// Rebecca
		EntityData::Field491Value rebecca_field_491 = getEntityData(kEntityRebecca)->field_491;
		EntityData::Field495Value rebecca_field_495 = getEntityData(kEntityRebecca)->field_495;

		if (getEntities()->checkFields9(kEntitySophie, kEntityRebecca, 500)
		|| (direction == kDirectionUp && field_495 >= rebecca_field_495 && field_491 > rebecca_field_491)
		|| (direction == kDirectionDown && field_495 <= rebecca_field_495 && field_491 < rebecca_field_491)) {
			 _data->getData()->field_49B = 0;
			 CURRENT_PARAM(3) = 1;
		}

		if (!CURRENT_PARAM(3))
			getEntities()->checkEntity(kEntitySophie, (EntityData::Field495Value)CURRENT_PARAM(1), (EntityData::Field491Value)CURRENT_PARAM(2));

		break;
	}

	case kAction5:
		getSound()->excuseMeCath();
		break;

	case kAction6:
		getSound()->excuseMe(kEntitySophie);
		break;

	case kActionDefault:
		getEntities()->checkEntity(kEntitySophie, (EntityData::Field495Value)CURRENT_PARAM(1), (EntityData::Field491Value)CURRENT_PARAM(2));
		break;

	case kAction123668192:
		CALL_PREVIOUS_SAVEPOINT(kEntitySophie)
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, function3, 3)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		_data->getData()->field_491 = getEntityData(kEntityRebecca)->field_491;
		_data->getData()->field_495 = getEntityData(kEntityRebecca)->field_495;
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequences(kEntitySophie);
			break;

		case 2:
			getEntities()->drawSequenceLeft(kEntitySophie, "BLANK");
			break;

		case 3:
			getEntities()->drawSequences(kEntitySophie);
			break;

		case 4:
			getEntities()->drawSequenceLeft(kEntitySophie, "BLANK");
			break;
		}
		break;

	case kAction125242096:
		_data->getData()->field_491 = (EntityData::Field491Value)(getEntityData(kEntityRebecca)->field_491 - 100);
		_data->getData()->field_493 = getEntityData(kEntityRebecca)->field_493;
		_data->getData()->field_495 = getEntityData(kEntityRebecca)->field_495;

		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Sophie, setup_function2), 5, 850);
		break;

	case kAction136654208:
		_data->getData()->field_491 = (EntityData::Field491Value)(getEntityData(kEntityRebecca)->field_491 + 100);
		_data->getData()->field_493 = getEntityData(kEntityRebecca)->field_493;
		_data->getData()->field_495 = getEntityData(kEntityRebecca)->field_495;

		_data->setNextCallback(2);
		call(new ENTITY_SETUP_DEFAULT(Sophie, setup_function2), 4, EntityData::kField491_4840);
		break;

	case kAction259921280:
		_data->getData()->field_491 = (EntityData::Field491Value)(getEntityData(kEntityRebecca)->field_491 + 100);
		_data->getData()->field_493 = getEntityData(kEntityRebecca)->field_493;
		_data->getData()->field_495 = getEntityData(kEntityRebecca)->field_495;

		_data->setNextCallback(3);
		call(new ENTITY_SETUP_DEFAULT(Sophie, setup_function2), 2, 9640);
		break;

	case kAction292775040:
		_data->getData()->field_491 = EntityData::kField491_9270;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_2;

		_data->setNextCallback(4);
		call(new ENTITY_SETUP_DEFAULT(Sophie, setup_function2), 4, EntityData::kField491_4840);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter1, 4)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(3)
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_4840;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, function5, 5)
	DEFAULT_ACTION_IMPLEMENTATION()
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter2, 6)
	CHAPTER_IMPLEMENTATION()
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter3, 7)
	CHAPTER_IMPLEMENTATION()
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter4, 8)
	CHAPTER_IMPLEMENTATION()
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, function9, 9)
	DEFAULT_ACTION_IMPLEMENTATION()
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter5, 10)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function11();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntitySophie);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, function11, 11)
	if (savepoint->action == kAction70549068)
		setup_nullfunction();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_NULL_FUNCTION(Sophie, 12)

} // End of namespace LastExpress
