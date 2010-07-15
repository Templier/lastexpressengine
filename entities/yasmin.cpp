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

#include "lastexpress/entities/yasmin.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Yasmin::Yasmin(LastExpressEngine *engine) : Entity(engine, kEntityYasmin) {
	ADD_CALLBACK_FUNCTION(Yasmin, function1);
	ADD_CALLBACK_FUNCTION(Yasmin, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Yasmin, playSound);
	ADD_CALLBACK_FUNCTION(Yasmin, updateFromTime);
	ADD_CALLBACK_FUNCTION(Yasmin, checkEntity);
	ADD_CALLBACK_FUNCTION(Yasmin, function6);
	ADD_CALLBACK_FUNCTION(Yasmin, function7);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter1);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Yasmin, function10);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter2);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter2_handler);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter3);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter3_handler);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter4);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter4_handler);
	ADD_CALLBACK_FUNCTION(Yasmin, function17);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter5);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter5_handler);
	ADD_CALLBACK_FUNCTION(Yasmin, function20);
	ADD_CALLBACK_FUNCTION(Yasmin, function21);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Yasmin, function1, 1)
	switch (savepoint.action) {
	default:
		break;

	case kActionExcuseMeCath:
		getSound()->excuseMeCath();
		break;

	case kActionExcuseMe:
		getSound()->excuseMe(kEntityYasmin);
		break;
	}

	// Process default actions
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_SI(Yasmin, enterExitCompartment, 2)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_S(Yasmin, playSound, 3)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Yasmin, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_II(Yasmin, checkEntity, 5)
	Entity::checkEntity(savepoint, true);
}

IMPLEMENT_FUNCTION(Yasmin, function6, 6)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->position = kPosition_4840;
		getData()->field_493 = kField493_0;

		setCallback(1);
		// Exit compartment
		call(new ENTITY_SETUP_SIIS(Yasmin, setup_enterExitCompartment), "615Be", kObjectCompartment5);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			call(new ENTITY_SETUP(Yasmin, setup_checkEntity), kCarGreenSleeping, kPosition_3050);
			break;

		case 2:
			// Enter compartment
			call(new ENTITY_SETUP_SIIS(Yasmin, setup_enterExitCompartment), "615Ag", kObjectCompartment7);
			break;

		case 3:
			getData()->field_493 = kField493_1;
			getEntities()->prepareSequences(kEntityYasmin);

			CALLBACK_ACTION()
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, function7, 7)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->position = kPosition_3050;
		getData()->field_493 = kField493_0;

		setCallback(1);
		// Exit compartment
		call(new ENTITY_SETUP_SIIS(Yasmin, setup_enterExitCompartment), "615Bg", kObjectCompartment7);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			call(new ENTITY_SETUP(Yasmin, setup_checkEntity), kCarGreenSleeping, kPosition_4840);
			break;

		case 2:
			// Enter compartment
			call(new ENTITY_SETUP_SIIS(Yasmin, setup_enterExitCompartment), "615Ae", kObjectCompartment5);
			break;

		case 3:
			getData()->field_493 = kField493_1;
			getEntities()->prepareSequences(kEntityYasmin);

			CALLBACK_ACTION()
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter1, 8)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getData()->position = kPosition_4840;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter1_handler, 9)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Yasmin, kTimeAnna, params->param1, 1, setup_function6);
		TIME_CHECK_CALLBACK(Yasmin, kTimeFrancois, params->param2, 3, setup_function7);
		TIME_CHECK_PLAYSOUND_2(Yasmin, kTimeYasmin_7, params->param3, 4, "Har1102", kPosition_4070);
		TIME_CHECK_PLAYSOUND(Yasmin, kTimeTables1, params->param4, 5, "Har1104");
		TIME_CHECK_PLAYSOUND(Yasmin, kTimeYasmin_8, params->param5, 6, "Har1106");
		TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin_9, params->param6, 7, setup_function6);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->position = kPosition_2740;
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Yasmin, setup_playSound), "Har1102");
			break;

		case 2:
			TIME_CHECK_CALLBACK(Yasmin, kTimeFrancois, params->param2, 3, setup_function7);
			// Fallback to case 3

		case 3:
			TIME_CHECK_PLAYSOUND_2(Yasmin, kTimeYasmin_7, params->param3, 4, "Har1102", kPosition_4070);
			// Fallback to case 4

		case 4:
			TIME_CHECK_PLAYSOUND(Yasmin, kTimeTables1, params->param4, 5, "Har1104");
			// Fallback to case 5

		case 5:
			TIME_CHECK_PLAYSOUND(Yasmin, kTimeYasmin_8, params->param5, 6, "Har1106");
			// Fallback to case 6

		case 6:
			TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin_9, params->param6, 7, setup_function6);
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, function10, 10)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartment7, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getData()->position = kPosition_3050;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;

		getEntities()->prepareSequences(kEntityYasmin);
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter2, 11)
	if (savepoint.action == kActionDefault) {
		getEntities()->prepareSequences(kEntityYasmin);

		getData()->position = kPosition_3050;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		setup_chapter2_handler();
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter2_handler, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin, params->param1, 1, setup_function7);

		if (getState()->time > kTimeYasmin_1 && !params->param2) {
			params->param2 = 1;
			getData()->position = kPosition_4070;

			getSavePoints()->push(kEntityYasmin, kEntityTrain, kAction191070912, kPosition_4070);
		}
		break;

	case kActionCallback:

		if (getCallback() != 1)
			break;

		if (getState()->time > kTimeYasmin_1 && !params->param2) {
			params->param2 = 1;
			getData()->position = kPosition_4070;

			getSavePoints()->push(kEntityYasmin, kEntityTrain, kAction191070912, kPosition_4070);
		}

		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter3, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3_handler();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityYasmin);

		getData()->position = kPosition_3050;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter3_handler, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin_2, params->param1, 1, setup_function6);
		TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin_3, params->param2, 2, setup_function7);
		TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin_4, params->param3, 3, setup_function6);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin_3, params->param2, 2, setup_function7);
			// Fallback to case 2

		case 2:
			TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin_4, params->param3, 3, setup_function6);
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter4, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4_handler();
		break;

	case kActionDefault:
		getData()->position = kPosition_3050;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter4_handler, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin_5, params->param1, 1, setup_function7);
		TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin_6, params->param2, 3, setup_function6);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->position = kPosition_4070;
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Yasmin, setup_playSound), "Har1110");
			break;

		case 2:
			TIME_CHECK_CALLBACK(Yasmin, kTimeYasmin_6, params->param2, 3, setup_function6);
			break;
		}
		break;
	}
}

// Same as existing function 10 ?
IMPLEMENT_FUNCTION(Yasmin, function17, 17)
	function10(savepoint);
}

IMPLEMENT_FUNCTION(Yasmin, chapter5, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5_handler();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityYasmin);

		getData()->position = kPosition_3969;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter5_handler, 19)
	if (savepoint.action == kAction70549068)
		setup_function20();
}

IMPLEMENT_FUNCTION(Yasmin, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM(params->param1, getState()->time, 2700);
		setup_function21();
		break;

	case kActionDefault:
		getData()->position = kPosition_2500;
		getData()->field_493 = kField493_0;
		getData()->car = kCarGreenSleeping;
		break;

	case kAction17:
		if (getEntities()->checkFields5(kEntityNone, kCarGreenSleeping)) {
			setup_function21();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, function21, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
	case kActionDefault:
		if (getEntities()->checkEntity(kEntityYasmin, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION();
		break;

	case kActionExcuseMeCath:
		getSound()->excuseMeCath();
		break;

	case kActionExcuseMe:
		getSound()->excuseMe(kEntityYasmin);
		break;
	}
}

IMPLEMENT_NULL_FUNCTION(Yasmin, 22)

} // End of namespace LastExpress
