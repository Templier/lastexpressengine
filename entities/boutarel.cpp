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

#include "lastexpress/entities/boutarel.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Boutarel::Boutarel(LastExpressEngine *engine) : Entity(engine, kEntityBoutarel) {
	ADD_CALLBACK_FUNCTION(Boutarel, function1);
	ADD_CALLBACK_FUNCTION(Boutarel, playSound);
	ADD_CALLBACK_FUNCTION(Boutarel, draw);
	ADD_CALLBACK_FUNCTION(Boutarel, updateFromTime);
	ADD_CALLBACK_FUNCTION(Boutarel, updatePosition);
	ADD_CALLBACK_FUNCTION(Boutarel, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Boutarel, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(Boutarel, function8);
	ADD_CALLBACK_FUNCTION(Boutarel, function9);
	ADD_CALLBACK_FUNCTION(Boutarel, function10);
	ADD_CALLBACK_FUNCTION(Boutarel, function11);
	ADD_CALLBACK_FUNCTION(Boutarel, enterTableWithMmeBoutarel);
	ADD_CALLBACK_FUNCTION(Boutarel, leaveTableWithMmeBoutarel);
	ADD_CALLBACK_FUNCTION(Boutarel, function14);
	ADD_CALLBACK_FUNCTION(Boutarel, function15);
	ADD_CALLBACK_FUNCTION(Boutarel, function16);
	ADD_CALLBACK_FUNCTION(Boutarel, function17);
	ADD_CALLBACK_FUNCTION(Boutarel, function18);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter1);
	ADD_CALLBACK_FUNCTION(Boutarel, function20);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Boutarel, function22);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter2);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter2_handler);
	ADD_CALLBACK_FUNCTION(Boutarel, function25);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter3);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter3_handler);
	ADD_CALLBACK_FUNCTION(Boutarel, function28);
	ADD_CALLBACK_FUNCTION(Boutarel, function29);
	ADD_CALLBACK_FUNCTION(Boutarel, function30);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter4);
	ADD_CALLBACK_FUNCTION(Boutarel, function32);
	ADD_CALLBACK_FUNCTION(Boutarel, function33);
	ADD_CALLBACK_FUNCTION(Boutarel, function34);
	ADD_CALLBACK_FUNCTION(Boutarel, function35);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter5);
	ADD_CALLBACK_FUNCTION(Boutarel, function37);
	ADD_CALLBACK_FUNCTION(Boutarel, function38);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Boutarel, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Boutarel, playSound, 2)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_S(Boutarel, draw, 3)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_I(Boutarel, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_SII(Boutarel, updatePosition, 5)
	Entity::updatePosition(savepoint);
}

IMPLEMENT_FUNCTION_SI(Boutarel, enterExitCompartment, 6)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_SI(Boutarel, enterExitCompartment2, 7)
	Entity::enterExitCompartment(savepoint, kPosition_6470, kPosition_6130, kObjectCompartmentC, true);
}

IMPLEMENT_FUNCTION(Boutarel, function8, 8)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION(Boutarel, function9, 9)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION_II(Boutarel, function10, 10)
	error("Boutarel: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION_I(Boutarel, function11, 11)
	error("Boutarel: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, enterTableWithMmeBoutarel, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->clearSequences(kEntityMmeBoutarel);
		getSavePoints()->push(kEntityBoutarel, kEntityTables2, kAction136455232);
		getData()->field_493 = kField493_1;

		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityTables2, "008A3");
		getEntities()->drawSequenceRight(kEntityMmeBoutarel, "008A2");
		getEntities()->drawSequenceRight(kEntityBoutarel, "008A1");

		if (getEntities()->checkFields12(kEntityNone)) {
			getEntities()->updateEntity(kEntityBoutarel);
			getEntityData(kEntityMmeBoutarel)->field_493 = getData()->field_493;
			getEntityData(kEntityTables2)->field_493 = getData()->field_493;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, leaveTableWithMmeBoutarel, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getSavePoints()->push(kEntityBoutarel, kEntityTables2, kAction103798704, "008F");
		getEntities()->clearSequences(kEntityMmeBoutarel);

		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityTables2, "008E3");
		getEntities()->drawSequenceRight(kEntityMmeBoutarel, "008E2");
		getEntities()->drawSequenceRight(kEntityBoutarel, "008E1");
		break;
	}
}

IMPLEMENT_FUNCTION_I(Boutarel, function14, 14)
	error("Boutarel: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION_IS(Boutarel, function15, 15)
	error("Boutarel: callback function 15 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Parameters:
// bool
// const char *
IMPLEMENT_FUNCTION_IS(Boutarel, function16, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Boutarel, setup_function9));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->field_493 = kField493_0;

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Boutarel, setup_updatePosition), (const char *)&params->seq, kCarRestaurant, 52);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Boutarel, setup_function10), kCarGreenSleeping, kPosition_6470);
			break;

		case 3:
			setCallback(params->param1 ? 4 : 5);
			call(new ENTITY_SETUP_SIIS(Boutarel, setup_enterExitCompartment2), params->param1 ? "607Gc" : "607Ac", kObjectCompartmentC);
			break;

		case 4:
		case 5:
			getData()->field_493 = kField493_1;
			getEntities()->clearSequences(kEntityBoutarel);

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION_IS(Boutarel, function17, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1 < (int)getState()->time && !params->param6) {
			params->param6 = 1;
			CALLBACK_ACTION();
			break;
		}

		if (!params->param5) {
			params->param7 = 0;
			break;
		}

		UPDATE_PARAM(params->param7, getState()->timeTicks, 90)
		getScenes()->loadSceneFromPosition(kCarRestaurant, 51);
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityMmeBoutarel, params->seq);
		break;

	case kAction17:
		params->param5 = (getEntities()->isPlayerPosition(kCarRestaurant, 52) ? 1 : 0);
		break;
	}
}

IMPLEMENT_FUNCTION_I(Boutarel, function18, 18)
	error("Boutarel: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, chapter1, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityBoutarel, kAction203520448, 0);
		getSavePoints()->addData(kEntityBoutarel, kAction237889408, 1);

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject42, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->entityPosition = kPosition_1750;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function20, 20)
	error("Boutarel: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, chapter1_handler, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_ISII(Boutarel, setup_function17), kTime1071000, "101A");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_ISII(Boutarel, setup_function16), false, "101B");
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Boutarel, setup_function18), kTime1102500);
			break;

		case 3:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorNormal, kCursorNormal);
			getObjects()->update(kObject50, kEntityNone, kLocation1, kCursorNormal, kCursorNormal);

			if (getEntities()->isPlayerPosition(kCarRedSleeping, 54) || getEntities()->isPlayerPosition(kCarRedSleeping, 44))
				getScenes()->loadSceneFromPosition(kCarRedSleeping, 10);

			getEntities()->updatePosition(kEntityBoutarel, kCarRedSleeping, 54, true);
			getEntities()->updatePosition(kEntityBoutarel, kCarRedSleeping, 44, true);

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Boutarel, setup_playSound), "MRB1074");
			break;

		case 4:
			getEntities()->updatePosition(kEntityBoutarel, kCarRedSleeping, 54);
			getEntities()->updatePosition(kEntityBoutarel, kCarRedSleeping, 44);

			setCallback(5);
			call(new ENTITY_SETUP(Boutarel, setup_function20));
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Boutarel, setup_function18), kTimeEnterChalons);
			break;

		case 6:
			setCallback(7);
			call(new ENTITY_SETUP_ISII(Boutarel, setup_function15), false, "102A");
			break;

		case 7:
			setCallback(8);
			call(new ENTITY_SETUP_ISII(Boutarel, setup_function17), kTime1183500, "102B");
			break;

		case 8:
			setCallback(9);
			call(new ENTITY_SETUP_ISII(Boutarel, setup_function16), false, "102C");
			break;

		case 9:
			setCallback(10);
			call(new ENTITY_SETUP(Boutarel, setup_function18), kTime1215000);
			break;

		case 10:
			setup_function22();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function22, 22)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_6470;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getEntities()->clearSequences(kEntityBoutarel);
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter2, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2_handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityBoutarel);

		getData()->entityPosition = kPosition_4689;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter2_handler, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Boutarel, kTime1759500, params->param2, 1, setup_function14);
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityBoutarel, "008D");
		break;

	case kAction17:
		if (getEntities()->checkFields13(kEntityNone) && !params->param1) {
			getSound()->playSound(kEntityBoutarel, "MRB2001");
			params->param1 = 1;
		}
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function25();
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function25, 25)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter3, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3_handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityBoutarel);

		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject50, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter3_handler, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");
		break;

	case kAction122288808:
		setup_function28();
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityBoutarel, "BLANK");
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function28, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Boutarel, setup_function11), 1);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function29();
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function29, 29)
	error("Boutarel: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function30, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");
		break;

	case kAction122288808:
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityBoutarel, "BLANK");
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter4, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function32();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityBoutarel);

		getData()->entityPosition = kPosition_6470;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject50, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function32, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK(kTime2367000, params->param1, setup_function33);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function33, 33)
	error("Boutarel: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function34, 34)
	error("Boutarel: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function35, 35)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_6470;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;

		getEntities()->clearSequences(kEntityBoutarel);

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter5, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function37();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityBoutarel);

		getData()->entityPosition = kPosition_3969;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function37, 37)
	if (savepoint.action == kAction70549068)
		setup_function38();
}

IMPLEMENT_FUNCTION(Boutarel, function38, 38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5790;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		break;

	case kAction135800432:
		setup_nullfunction();
		break;
	}
}

IMPLEMENT_NULL_FUNCTION(Boutarel, 39)

} // End of namespace LastExpress
