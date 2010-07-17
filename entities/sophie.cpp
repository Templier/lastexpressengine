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
	switch (savepoint.action) { \
	default: \
		break; \
	case kActionNone: \
		setup_chapters_handler(); \
		break; \
	case kActionDefault: \
		getEntities()->prepareSequences(kEntitySophie); \
		getData()->entityPosition = kPosition_4840; \
		getData()->field_493 = kField493_1; \
		getData()->car = kCarRedSleeping; \
		getData()->clothes = kClothesDefault; \
		getData()->inventoryItem = kItemNone; \
		break; \
	}

#define DEFAULT_ACTION_IMPLEMENTATION() \
	if (savepoint.action == kActionDefault) { \
		getData()->entityPosition = kPosition_4840; \
		getData()->field_493 = kField493_1; \
		getData()->car = kCarRedSleeping; \
		getEntities()->prepareSequences(kEntitySophie); \
	}

Sophie::Sophie(LastExpressEngine *engine) : Entity(engine, kEntitySophie) {
	ADD_CALLBACK_FUNCTION(Sophie, function1);
	ADD_CALLBACK_FUNCTION(Sophie, function2);
	ADD_CALLBACK_FUNCTION(Sophie, chapters_handler);
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
	Entity::function1(savepoint);
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - CarIndex
//  - EntityPosition
IMPLEMENT_FUNCTION_II(Sophie, function2, 2)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone: {
		params->param3 = 0;

		// Sophie
		byte direction = getData()->direction;
		EntityPosition position = getData()->entityPosition;
		CarIndex car = getData()->car;

		// Rebecca
		EntityPosition rebecca_position = getEntityData(kEntityRebecca)->entityPosition;
		CarIndex rebeccaCar = getEntityData(kEntityRebecca)->car;

		if (getEntities()->checkFields9(kEntitySophie, kEntityRebecca, 500)
		|| (direction == kDirectionUp && car >= rebeccaCar && position > rebecca_position)
		|| (direction == kDirectionDown && car <= rebeccaCar && position < rebecca_position)) {
			 getData()->field_49B = 0;
			 params->param3 = 1;
		}

		if (!params->param3)
			getEntities()->checkEntity(kEntitySophie, (CarIndex)params->param1, (EntityPosition)params->param2);

		break;
	}

	case kActionExcuseMeCath:
		getSound()->excuseMeCath();
		break;

	case kActionExcuseMe:
		getSound()->excuseMe(kEntitySophie);
		break;

	case kActionDefault:
		getEntities()->checkEntity(kEntitySophie, (CarIndex)params->param1, (EntityPosition)params->param2);
		break;

	case kAction123668192:
		CALLBACK_ACTION()
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapters_handler, 3)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		getData()->entityPosition = getEntityData(kEntityRebecca)->entityPosition;
		getData()->car = getEntityData(kEntityRebecca)->car;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->prepareSequences(kEntitySophie);
			break;

		case 2:
			getEntities()->drawSequenceLeft(kEntitySophie, "BLANK");
			break;

		case 3:
			getEntities()->prepareSequences(kEntitySophie);
			break;

		case 4:
			getEntities()->drawSequenceLeft(kEntitySophie, "BLANK");
			break;
		}
		break;

	case kAction125242096:
		getData()->entityPosition = (EntityPosition)(getEntityData(kEntityRebecca)->entityPosition - 100);
		getData()->field_493 = getEntityData(kEntityRebecca)->field_493;
		getData()->car = getEntityData(kEntityRebecca)->car;

		setCallback(1);
		call(new ENTITY_SETUP(Sophie, setup_function2), kCarRestaurant, kPosition_850);
		break;

	case kAction136654208:
		getData()->entityPosition = (EntityPosition)(getEntityData(kEntityRebecca)->entityPosition + 100);
		getData()->field_493 = getEntityData(kEntityRebecca)->field_493;
		getData()->car = getEntityData(kEntityRebecca)->car;

		setCallback(2);
		call(new ENTITY_SETUP(Sophie, setup_function2), kCarRedSleeping, kPosition_4840);
		break;

	case kAction259921280:
		getData()->entityPosition = (EntityPosition)(getEntityData(kEntityRebecca)->entityPosition + 100);
		getData()->field_493 = getEntityData(kEntityRebecca)->field_493;
		getData()->car = getEntityData(kEntityRebecca)->car;

		setCallback(3);
		call(new ENTITY_SETUP(Sophie, setup_function2), kCarKronos, kPosition_9460);
		break;

	case kAction292775040:
		getData()->entityPosition = kPosition_9270;
		getData()->field_493 = kField493_0;
		getData()->car = kCarKronos;

		setCallback(4);
		call(new ENTITY_SETUP(Sophie, setup_function2), kCarRedSleeping, kPosition_4840);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, chapter1, 4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapters_handler);
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_4840;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
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
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function11();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntitySophie);

		getData()->entityPosition = kPosition_3969;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Sophie, function11, 11)
	if (savepoint.action == kAction70549068)
		setup_nullfunction();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_NULL_FUNCTION(Sophie, 12)

} // End of namespace LastExpress
