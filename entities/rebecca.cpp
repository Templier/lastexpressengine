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

#include "lastexpress/entities/rebecca.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Rebecca::Rebecca(LastExpressEngine *engine) : Entity(engine, kEntityRebecca) {
	ADD_CALLBACK_FUNCTION(Rebecca, function1);
	ADD_CALLBACK_FUNCTION(Rebecca, updateFromTime);
	ADD_CALLBACK_FUNCTION(Rebecca, playSound);
	ADD_CALLBACK_FUNCTION(Rebecca, playSound16);
	ADD_CALLBACK_FUNCTION(Rebecca, function5);
	ADD_CALLBACK_FUNCTION(Rebecca, draw);
	ADD_CALLBACK_FUNCTION(Rebecca, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Rebecca, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(Rebecca, enterExitCompartment3);
	ADD_CALLBACK_FUNCTION(Rebecca, function10);
	ADD_CALLBACK_FUNCTION(Rebecca, function11);
	ADD_CALLBACK_FUNCTION(Rebecca, checkEntity);
	ADD_CALLBACK_FUNCTION(Rebecca, updatePosition);
	ADD_CALLBACK_FUNCTION(Rebecca, draw2);
	ADD_CALLBACK_FUNCTION(Rebecca, function15);
	ADD_CALLBACK_FUNCTION(Rebecca, function16);
	ADD_CALLBACK_FUNCTION(Rebecca, function17);
	ADD_CALLBACK_FUNCTION(Rebecca, function18);
	ADD_CALLBACK_FUNCTION(Rebecca, function19);
	ADD_CALLBACK_FUNCTION(Rebecca, function20);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter1);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Rebecca, function23);
	ADD_CALLBACK_FUNCTION(Rebecca, function24);
	ADD_CALLBACK_FUNCTION(Rebecca, function25);
	ADD_CALLBACK_FUNCTION(Rebecca, function26);
	ADD_CALLBACK_FUNCTION(Rebecca, function27);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter2);
	ADD_CALLBACK_FUNCTION(Rebecca, function29);
	ADD_CALLBACK_FUNCTION(Rebecca, function30);
	ADD_CALLBACK_FUNCTION(Rebecca, function31);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter3);
	ADD_CALLBACK_FUNCTION(Rebecca, function33);
	ADD_CALLBACK_FUNCTION(Rebecca, function34);
	ADD_CALLBACK_FUNCTION(Rebecca, function35);
	ADD_CALLBACK_FUNCTION(Rebecca, function36);
	ADD_CALLBACK_FUNCTION(Rebecca, function37);
	ADD_CALLBACK_FUNCTION(Rebecca, function38);
	ADD_CALLBACK_FUNCTION(Rebecca, function39);
	ADD_CALLBACK_FUNCTION(Rebecca, function40);
	ADD_CALLBACK_FUNCTION(Rebecca, function41);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter4);
	ADD_CALLBACK_FUNCTION(Rebecca, function43);
	ADD_CALLBACK_FUNCTION(Rebecca, function44);
	ADD_CALLBACK_FUNCTION(Rebecca, function45);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter5);
	ADD_CALLBACK_FUNCTION(Rebecca, function47);
	ADD_CALLBACK_FUNCTION(Rebecca, function48);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Rebecca, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_I(Rebecca, updateFromTime, 2)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_S(Rebecca, playSound, 3)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_S(Rebecca, playSound16, 4)
	Entity::playSound(savepoint, false, getEntities()->getSoundValue(kEntityCoudert));
}

IMPLEMENT_FUNCTION_SIIS(Rebecca, function5, 5)
	Entity::savepointCall(savepoint);
}

IMPLEMENT_FUNCTION_S(Rebecca, draw, 6)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SI(Rebecca, enterExitCompartment, 7)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_SI(Rebecca, enterExitCompartment2, 8)
	Entity::enterExitCompartment(savepoint, kPosition_4840, kPosition_4455, kCarRedSleeping, kObjectCompartmentE, true);
}

IMPLEMENT_FUNCTION_SI(Rebecca, enterExitCompartment3, 9)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION(Rebecca, function10, 10)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION(Rebecca, function11, 11)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION_II(Rebecca, checkEntity, 12)
	Entity::checkEntity(savepoint, true);
}

IMPLEMENT_FUNCTION_SII(Rebecca, updatePosition, 13)
	Entity::updatePosition(savepoint);
}

IMPLEMENT_FUNCTION_SSI(Rebecca, draw2, 14)
	Entity::draw2(savepoint);
}

IMPLEMENT_FUNCTION(Rebecca, function15, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (getEntities()->checkFields16())
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 49);

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Rebecca, setup_enterExitCompartment2), "624Ae", kObjectCompartmentE);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getObjects()->update(kObjectOutsideBetweenCompartments, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
			getData()->field_493 = kField493_1;
			getEntities()->clearSequences(kEntityRebecca);

			CALLBACK_ACTION();
		}
		break;
	}
}

IMPLEMENT_FUNCTION_I(Rebecca, function16, 16)
	error("Rebecca: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION_I(Rebecca, function17, 17)
	error("Rebecca: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function18, 18)
	error("Rebecca: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function19, 19)
	error("Rebecca: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION_I(Rebecca, function20, 20)
	error("Rebecca: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, chapter1, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityRebecca, kAction224253538, 0);

		getObjects()->update(kObjectCompartmentE, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectOutsideBetweenCompartments, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getObjects()->updateLocation2(kObject110, kLocation1);

		getData()->entityPosition = kPosition_2830;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;

		ENTITY_PARAM(0, 2) = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, chapter1_handler, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_PLAYSOUND(Rebecca, kTime1084500, params->param3, 1, "REB1015");

		if (params->param4 == kTimeInvalid || !getState()->time)
			goto label_function22_callback_4;

		if (getState()->time > kTime1080000) {
			params->param4 = kTimeInvalid;
			if (getEntities()->checkFields12(kEntityNone))
				getProgress().field_B8 = 1;

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Rebecca, setup_playSound), "REB1012");
			break;
		}

		if (!getEntities()->checkFields12(kEntityNone) || !params->param4) {
			params->param4 = getState()->time + 150;
			if (!params->param4) {
				if (getEntities()->checkFields12(kEntityNone))
					getProgress().field_B8 = 1;

				setCallback(4);
				call(new ENTITY_SETUP_SIIS(Rebecca, setup_playSound), "REB1012");
				break;
			}
		}

		if (params->param4 >= (int)getState()->time) {
label_function22_callback_4:
			if (params->param1) {
				bool checkParam5 = false;
				if (!params->param5) {
					params->param5 = (int)getState()->time + 900;
					checkParam5 = true;
				}

				if (checkParam5 || params->param5 < (int)getState()->time) {
					if (getEntities()->checkFields12(kEntityNone)) {
						setCallback(5);
						call(new ENTITY_SETUP_SIIS(Rebecca, setup_playSound), "REB1013");
						break;
					}
				}
			}

label_function22_callback_5:
			if (params->param2) {
				UPDATE_PARAM(params->param6, getState()->timeTicks, 90);
				getScenes()->loadSceneFromPosition(kCarRestaurant, 55);
			} else {
				params->param6 = 0;
			}
		} else {
			params->param4 = kTimeInvalid;
			if (getEntities()->checkFields12(kEntityNone))
				getProgress().field_B8 = 1;

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Rebecca, setup_playSound), "REB1012");
		}
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityRebecca, "107B");
		break;

	case kActionDrawScene:
		params->param2 = (getEntities()->isPlayerPosition(kCarRestaurant, 57) ? 1 : 0);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Rebecca, setup_updatePosition), "107C", kCarRestaurant, 57);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Rebecca, setup_function18));
			break;

		case 3:
			setup_function23();
			break;

		case 4:
			params->param1 = 1;
			goto label_function22_callback_4;

		case 5:
			getProgress().field_B4 = 1;
			params->param1 = 0;
			goto label_function22_callback_5;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function23, 23)
	error("Rebecca: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function24, 24)
	error("Rebecca: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function25, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Rebecca, setup_function20), kTime1184400);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Rebecca, setup_function17));
			break;

		case 2:
			setup_function26();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function26, 26)
	error("Rebecca: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function27, 27)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_4840;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentE, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getEntities()->clearSequences(kEntityRebecca);
	}
}

IMPLEMENT_FUNCTION(Rebecca, chapter2, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function29();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityRebecca);

		getData()->entityPosition = kPosition_4840;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentE, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getObjects()->updateLocation2(kObject110, kLocation2);

		ENTITY_PARAM(0, 2) = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function29, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Rebecca, setup_function20), kTime1764000);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Rebecca, setup_function17));
			break;

		case 2:
			setup_function30();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function30, 30)
	error("Rebecca: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function31, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Rebecca, setup_updateFromTime), 900);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Rebecca, setup_enterExitCompartment), "623CE", kObjectCompartmentE);
			break;

		case 2:
			getObjects()->update(kObjectCompartmentE, kEntityNone, kLocation2, kCursorNormal, kCursorNormal);
			getEntities()->drawSequenceLeft(kEntityRebecca, "504");
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, chapter3, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function33();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityRebecca);

		getData()->entityPosition = kPosition_4840;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function33, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Rebecca, setup_function20), kTime2016000);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function34();
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function34, 34)
	error("Rebecca: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function35, 35)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Rebecca, setup_function20), kTime2070000);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function36();
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function36, 36)
	error("Rebecca: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function37, 37)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Rebecca, setup_function20), kTime2110500);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function38();
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function38, 38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->field_493 = kField493_0;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Rebecca, setup_enterExitCompartment3), "624Be", kObjectCompartmentE);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentE, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
            getSavePoints()->push(kEntityRebecca, kEntitySophie, kAction259921280);

			setCallback(2);
			call(new ENTITY_SETUP(Rebecca, setup_checkEntity), kCarKronos, kPosition_9270);
			break;

		case 2:
			getSavePoints()->push(kEntityRebecca, kEntitySophie, kAction123668192);
			setup_function39();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function39, 39)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityRebecca);

		getObjects()->update(kObjectCompartmentE, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_6000;
		getData()->field_493 = kField493_1;
		getData()->car = kCarKronos;
		break;

	case kAction191668032:
		setup_function40();
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function40, 40)
	error("Rebecca: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function41, 41)
	if (savepoint.action == kActionDefault) {
		ENTITY_PARAM(0, 2) = 1;

		setCallback(1);
		call(new ENTITY_SETUP(Rebecca, setup_function20), kTimeEnd);
	}
}

IMPLEMENT_FUNCTION(Rebecca, chapter4, 42)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function43();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityRebecca);

		getData()->entityPosition = kPosition_4840;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->updateLocation2(kObject110, kLocation3);

		ENTITY_PARAM(0, 1) = 0;
		ENTITY_PARAM(0, 2) = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function43, 43)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Rebecca, setup_function20), kTime2385000);
		break;

	case kActionCallback:
		if (getCallback() == 1 || getCallback() == 2) {
			if (ENTITY_PARAM(0, 1)) {
				setup_function44();
			} else {
				setCallback(2);
				call(new ENTITY_SETUP(Rebecca, setup_function20), getState()->time + 900);
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function44, 44)
	error("Rebecca: callback function 44 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function45, 45)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_4840;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentE, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getEntities()->clearSequences(kEntityRebecca);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			params->param1 = 1;
		break;

	case kAction205034665:
		if (!params->param1 && getState()->time < kTime2511000) {
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Rebecca, setup_playSound), "Reb6969");
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, chapter5, 46)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function47();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityRebecca);

		getData()->entityPosition = kPosition_3969;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		getObjects()->updateLocation2(kObject110, kLocation4);
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function47, 47)
	if (savepoint.action == kAction70549068)
		setup_function48();
}

IMPLEMENT_FUNCTION(Rebecca, function48, 48)
	error("Rebecca: callback function 48 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Rebecca, 49)

} // End of namespace LastExpress
