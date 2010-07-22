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

#include "lastexpress/entities/pascale.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Pascale::Pascale(LastExpressEngine *engine) : Entity(engine, kEntityPascale) {
	ADD_CALLBACK_FUNCTION(Pascale, draw);
	ADD_CALLBACK_FUNCTION(Pascale, function2);
	ADD_CALLBACK_FUNCTION(Pascale, function3);
	ADD_CALLBACK_FUNCTION(Pascale, updateFromTime);
	ADD_CALLBACK_FUNCTION(Pascale, updatePosition);
	ADD_CALLBACK_FUNCTION(Pascale, playSound);
	ADD_CALLBACK_FUNCTION(Pascale, draw2);
	ADD_CALLBACK_FUNCTION(Pascale, function8);
	ADD_CALLBACK_FUNCTION(Pascale, function9);
	ADD_CALLBACK_FUNCTION(Pascale, function10);
	ADD_CALLBACK_FUNCTION(Pascale, function11);
	ADD_CALLBACK_FUNCTION(Pascale, chapter1);
	ADD_CALLBACK_FUNCTION(Pascale, function13);
	ADD_CALLBACK_FUNCTION(Pascale, sitAnna);
	ADD_CALLBACK_FUNCTION(Pascale, function15);
	ADD_CALLBACK_FUNCTION(Pascale, function16);
	ADD_CALLBACK_FUNCTION(Pascale, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Pascale, function18);
	ADD_CALLBACK_FUNCTION(Pascale, function19);
	ADD_CALLBACK_FUNCTION(Pascale, chapter2);
	ADD_CALLBACK_FUNCTION(Pascale, chapter3);
	ADD_CALLBACK_FUNCTION(Pascale, function22);
	ADD_CALLBACK_FUNCTION(Pascale, function23);
	ADD_CALLBACK_FUNCTION(Pascale, function24);
	ADD_CALLBACK_FUNCTION(Pascale, chapter4);
	ADD_CALLBACK_FUNCTION(Pascale, function26);
	ADD_CALLBACK_FUNCTION(Pascale, function27);
	ADD_CALLBACK_FUNCTION(Pascale, function28);
	ADD_CALLBACK_FUNCTION(Pascale, function29);
	ADD_CALLBACK_FUNCTION(Pascale, function30);
	ADD_CALLBACK_FUNCTION(Pascale, chapter5);
	ADD_CALLBACK_FUNCTION(Pascale, function32);
	ADD_CALLBACK_FUNCTION(Pascale, function33);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION_S(Pascale, draw, 1)
	Entity::draw(savepoint, true);
}

IMPLEMENT_FUNCTION(Pascale, function2, 2)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION(Pascale, function3, 3)
	if (savepoint.action == kActionExcuseMeCath) {
		if (!params->param1) {
			getSound()->excuseMe(kEntityPascale);
			params->param1 = 1;
		}
	}

	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_I(Pascale, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Pascale, updatePosition, 5)
	Entity::updatePosition(savepoint, true);
}

IMPLEMENT_FUNCTION_S(Pascale, playSound, 6)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Pascale, draw2, 7)
	Entity::draw2(savepoint);
}

IMPLEMENT_FUNCTION(Pascale, function8, 8)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_850;
		getData()->field_493 = kField493_0;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Pascale, setup_draw), "901");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			switch (getProgress().chapter) {
			default:
				break;

			case kChapter1:
				getSound()->playSound(kEntityPascale, "REB1198", -1, 30);
				break;

			case kChapter3:
				getSound()->playSound(kEntityPascale, "REB3001", -1, 30);
				break;

			case kChapter4:
				getSound()->playSound(kEntityPascale, "REB4001", -1, 30);
				break;
			}

			setCallback(2);
			call(new ENTITY_SETUP(Pascale, setup_function9));
			break;

		case 2:
			getSavePoints()->push(kEntityPascale, kEntityRebecca, kAction157370960);

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Pascale, setup_draw), "905");
			break;

		case 3:
			getEntities()->clearSequences(kEntityPascale);
			getData()->entityPosition = kPosition_5900;
			ENTITY_PARAM(0, 4) = 0;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function9, 9)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION();
 		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityPascale, "012C1");
		getEntities()->drawSequenceLeft(kEntityRebecca, "012C2");
		getEntities()->drawSequenceLeft(kEntityTables3, "012C3");
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function10, 10)
	error("Pascale: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function11, 11)
	error("Pascale: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, chapter1, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter1_handler();
 		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityPascale, kAction239072064, 0);
		getSavePoints()->addData(kEntityPascale, kAction257489762, 2);
		getSavePoints()->addData(kEntityPascale, kAction207769280, 6);
		getSavePoints()->addData(kEntityPascale, kAction101824388, 7);
		getSavePoints()->addData(kEntityPascale, kAction136059947, 8);
		getSavePoints()->addData(kEntityPascale, kAction223262556, 1);
		getSavePoints()->addData(kEntityPascale, kAction269479296, 3);
		getSavePoints()->addData(kEntityPascale, kAction352703104, 4);
		getSavePoints()->addData(kEntityPascale, kAction352768896, 5);
		getSavePoints()->addData(kEntityPascale, kAction191604416, 10);
		getSavePoints()->addData(kEntityPascale, kAction190605184, 11);

		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function13, 13)
	error("Pascale: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, sitAnna, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->updatePosition(kEntityPascale, kCarRestaurant, 62);

		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityTables0, "001C3");
		getEntities()->drawSequenceRight(kEntityAnna, "001C2");
		getEntities()->drawSequenceRight(kEntityPascale, "001C1");

		getEntities()->updatePosition(kEntityPascale, kCarRestaurant, 62, true);
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function15, 15)
	error("Pascale: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function16, 16)
	error("Pascale: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, chapter1_handler, 17)
switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param2) {
			if (getEntities()->isPlayerPosition(kCarRestaurant, 69)
			 || getEntities()->isPlayerPosition(kCarRestaurant, 70)
			 || getEntities()->isPlayerPosition(kCarRestaurant, 71))
				params->param2 = 1;

			if (!params->param2 && getEntities()->isPlayerPosition(kCarRestaurant, 61))
				params->param1 = 1;
		}

		if (!getEntities()->checkFields17(kEntityPascale))
			break;

		if (ENTITY_PARAM(0, 5) && ENTITY_PARAM(0, 6)) {
			setup_function18();
			break;
		}

		if (!getEntities()->checkFields11())
			goto label_callback3;

		if (params->param1 && !params->param2 && getEntities()->isPlayerPosition(kCarRestaurant, 61)) {
			setCallback(1);
			call(new ENTITY_SETUP(Pascale, setup_function11));
			break;
		}

label_callback1:
		if (ENTITY_PARAM(0, 1) && !ENTITY_PARAM(1, 3)) {
			setCallback(2);
			call(new ENTITY_SETUP(Pascale, setup_function13));
			break;
		}

label_callback2:
		if (ENTITY_PARAM(0, 3)) {
			setCallback(3);
			call(new ENTITY_SETUP(Pascale, setup_function16));
			break;
		}

label_callback3:
		if (ENTITY_PARAM(0, 2)) {
			setCallback(4);
			call(new ENTITY_SETUP(Pascale, setup_function15));
			break;
		}

label_callback4:
		if (ENTITY_PARAM(0, 4)) {
			setCallback(5);
			call(new ENTITY_SETUP(Pascale, setup_function8));
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			params->param1 = 0;
			params->param2 = 1;
			goto label_callback1;

		case 2:
			goto label_callback2;

		case 3:
			goto label_callback3;

		case 4:
			goto label_callback4;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function18, 18)
	if (savepoint.action != kActionNone)
		return;

	if (getState()->time > kTime1242000 && !params->param1) {
		params->param1 = 1;

		getSavePoints()->push(kEntityPascale, kEntityServers0, kAction101632192);
		getSavePoints()->push(kEntityPascale, kEntityServers1, kAction101632192);
		getSavePoints()->push(kEntityPascale, kEntityCooks, kAction101632192);
		getSavePoints()->push(kEntityPascale, kEntityVerges, kAction101632192);

		setup_function19();
	}
}

IMPLEMENT_FUNCTION(Pascale, function19, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param1 && getEntityData(kEntityNone)->entityPosition < kPosition_3650) {
			getObjects()->update(kObject65, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
			getSavePoints()->push(kEntityPascale, kEntityTables0, kAction103798704, "001P");
			getSavePoints()->push(kEntityPascale, kEntityTables1, kAction103798704, "005J");
			getSavePoints()->push(kEntityPascale, kEntityTables2, kAction103798704, "009G");
			getSavePoints()->push(kEntityPascale, kEntityTables3, kAction103798704, "010M");
			getSavePoints()->push(kEntityPascale, kEntityTables4, kAction103798704, "014F");
			getSavePoints()->push(kEntityPascale, kEntityTables5, kAction103798704, "024D");

			params->param1 = 1;
		}
		break;

	case kActionDefault:
		getData()->car = kCarRestaurant;
		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_0;

		getEntities()->clearSequences(kEntityPascale);
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, chapter2, 20)
	if (savepoint.action == kActionDefault) {
		getEntities()->clearSequences(kEntityPascale);

		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject65, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	}
}

IMPLEMENT_FUNCTION(Pascale, chapter3, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function22();
 		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityPascale);

		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 7) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function22, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!getEntities()->checkFields17(kEntityPascale))
			break;

		if (ENTITY_PARAM(0, 7)) {
			setCallback(1);
			call(new ENTITY_SETUP(Pascale, setup_function23));
			break;
		}

		if (ENTITY_PARAM(0, 4)) {
			setCallback(2);
			call(new ENTITY_SETUP(Pascale, setup_function8));
		}
 		break;

	case kActionCallback:
		if (getCallback() != 1)
			break;

		if (ENTITY_PARAM(0, 4)) {
			setCallback(2);
			call(new ENTITY_SETUP(Pascale, setup_function8));
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function23, 23)
	error("Pascale: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function24, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param1) {
			getSound()->playSound(kEntityPascale, "ABB3015A");
			params->param1 = 1;
		}
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION();
		break;

	case kAction10:
		getSavePoints()->push(kEntityPascale, kEntityTables4, kAction136455232);
		break;

	case kActionDefault:
		getSound()->playSound(kEntityPascale, "ABB3015", -1, 105u);
		getEntities()->drawSequenceRight(kEntityPascale, "029A1");
		getEntities()->drawSequenceRight(kEntityAbbot, "029A2");
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, chapter4, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function26();
 		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityPascale);

		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 2) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function26, 26)
	error("Pascale: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function27, 27)
	error("Pascale: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function28, 28)
	error("Pascale: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function29, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_1540;
		getData()->field_493 = kField493_0;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Pascale, setup_draw), "817DD");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceRight(kEntityPascale, "817DS");
			if (getEntities()->checkFields13(kEntityNone))
				getEntities()->updateEntity(kEntityPascale);

			setCallback(2);
			call(new ENTITY_SETUP(Pascale, setup_function3));
			break;

		case 2:
			getData()->entityPosition = kPosition_850;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function30, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_9270;
		getData()->field_493 = kField493_0;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Pascale, setup_draw), "817US");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceRight(kEntityPascale, "817UD");
			if (getEntities()->checkFields12(kEntityNone))
				getEntities()->updateEntity(kEntityPascale);

			setCallback(2);
			call(new ENTITY_SETUP(Pascale, setup_function3));
			break;

		case 2:
			getData()->entityPosition = kPosition_5900;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, chapter5, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function32();
 		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityPascale);

		getData()->entityPosition = kPosition_3969;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function32, 32)
	if (savepoint.action == kAction70549068)
		setup_function33();
}

IMPLEMENT_FUNCTION(Pascale, function33, 33)
	error("Pascale: callback function 33 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Pascale, 34)

} // End of namespace LastExpress
