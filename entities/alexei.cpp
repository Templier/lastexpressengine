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

#include "lastexpress/entities/alexei.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Alexei::Alexei(LastExpressEngine *engine) : Entity(engine, kEntityAlexei) {
	ADD_CALLBACK_FUNCTION(Alexei, function1);
	ADD_CALLBACK_FUNCTION(Alexei, playSound);
	ADD_CALLBACK_FUNCTION(Alexei, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Alexei, draw);
	ADD_CALLBACK_FUNCTION(Alexei, updatePosition);
	ADD_CALLBACK_FUNCTION(Alexei, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Alexei, function7);
	ADD_CALLBACK_FUNCTION(Alexei, function8);
	ADD_CALLBACK_FUNCTION(Alexei, savegame);
	ADD_CALLBACK_FUNCTION(Alexei, function10);
	ADD_CALLBACK_FUNCTION(Alexei, draw2);
	ADD_CALLBACK_FUNCTION(Alexei, function12);
	ADD_CALLBACK_FUNCTION(Alexei, function13);
	ADD_CALLBACK_FUNCTION(Alexei, function14);
	ADD_CALLBACK_FUNCTION(Alexei, function15);
	ADD_CALLBACK_FUNCTION(Alexei, function16);
	ADD_CALLBACK_FUNCTION(Alexei, chapter1);
	ADD_CALLBACK_FUNCTION(Alexei, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Alexei, function19);
	ADD_CALLBACK_FUNCTION(Alexei, function20);
	ADD_CALLBACK_FUNCTION(Alexei, function21);
	ADD_CALLBACK_FUNCTION(Alexei, function22);
	ADD_CALLBACK_FUNCTION(Alexei, function23);
	ADD_CALLBACK_FUNCTION(Alexei, function24);
	ADD_CALLBACK_FUNCTION(Alexei, function25);
	ADD_CALLBACK_FUNCTION(Alexei, function26);
	ADD_CALLBACK_FUNCTION(Alexei, function27);
	ADD_CALLBACK_FUNCTION(Alexei, chapter2);
	ADD_CALLBACK_FUNCTION(Alexei, chapter2_handler);
	ADD_CALLBACK_FUNCTION(Alexei, function30);
	ADD_CALLBACK_FUNCTION(Alexei, function31);
	ADD_CALLBACK_FUNCTION(Alexei, chapter3);
	ADD_CALLBACK_FUNCTION(Alexei, chapter3_handler);
	ADD_CALLBACK_FUNCTION(Alexei, function34);
	ADD_CALLBACK_FUNCTION(Alexei, function35);
	ADD_CALLBACK_FUNCTION(Alexei, function36);
	ADD_CALLBACK_FUNCTION(Alexei, chapter4);
	ADD_CALLBACK_FUNCTION(Alexei, chapter4_handler);
	ADD_CALLBACK_FUNCTION(Alexei, function39);
	ADD_CALLBACK_FUNCTION(Alexei, function40);
	ADD_CALLBACK_FUNCTION(Alexei, function41);
	ADD_CALLBACK_FUNCTION(Alexei, function42);
	ADD_CALLBACK_FUNCTION(Alexei, function43);
	ADD_CALLBACK_FUNCTION(Alexei, function44);
	ADD_CALLBACK_FUNCTION(Alexei, function45);
	ADD_CALLBACK_FUNCTION(Alexei, function46);
	ADD_CALLBACK_FUNCTION(Alexei, function47);
	ADD_CALLBACK_FUNCTION(Alexei, chapter5);
}

IMPLEMENT_FUNCTION(Alexei, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Alexei, playSound, 2)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_I(Alexei, updateFromTicks, 3)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION_S(Alexei, draw, 4)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SII(Alexei, updatePosition, 5)
	Entity::updatePosition(savepoint);
}

IMPLEMENT_FUNCTION_SI(Alexei, enterExitCompartment, 6)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION(Alexei, function7, 7)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_SIIS(Alexei, function8, 8)
	Entity::savepointCall(savepoint);
}

IMPLEMENT_FUNCTION_II(Alexei, savegame, 9)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(Alexei, function10, 10)
	error("Alexei: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Alexei, draw2, 11)
	Entity::draw2(savepoint);
}

IMPLEMENT_FUNCTION(Alexei, function12, 12)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION(Alexei, function13, 13)
	error("Alexei: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function14, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Alexei, setup_enterExitCompartment), "602Fb", kObjectCompartment2);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getData()->field_493 = kField493_0;
			getSavePoints()->push(kEntityAlexei, kEntityMertens, kAction302614416);
			getEntities()->drawSequenceLeft(kEntityAlexei, "602DB");
			getEntities()->enterCompartment(kEntityAlexei, kObjectCompartment2);
		}
		break;

	case kAction135664192:
		getObjects()->update(kObjectCompartment2, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getEntities()->exitCompartment(kEntityAlexei, kObjectCompartment2);

		CALLBACK_ACTION();
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function15, 15)
	error("Alexei: callback function 15 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - TimeTicks
//  - Sequence name
IMPLEMENT_FUNCTION_IS(Alexei, function16, 16)
	error("Alexei: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, chapter1, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler)
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment2, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_3969;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter1_handler, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime1089000 && getEntities()->checkFields11()) {
			params->param2 = 0;

			getData()->field_493 = kField493_0;
			getData()->inventoryItem = kItemNone;

			getEntities()->updatePosition(kEntityAlexei, kCarRestaurant, 63, true);
			getInventory()->setLocationAndProcess(kItem17, kLocation1);

			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_function8), "005D", kEntityTables1, kAction103798704, "005E");
			break;
		}

		if (params->param1) {
			UPDATE_PARAM(params->param3, getState()->timeTicks, 90);
			getScenes()->loadSceneFromPosition(kCarRestaurant, 61);
		} else {
			params->param3 = 0;
		}
		break;

	case kAction1:
		params->param2 = 0;
		getData()->inventoryItem = kItemNone;

		setCallback(2);
		call(new ENTITY_SETUP(Alexei, setup_savegame), kSavegameType2, kEventAlexeiDiner);
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAlexei, kEntityTables1, kAction136455232);
		getEntities()->drawSequenceLeft(kEntityAlexei, "005B");

		params->param2 = kItemInvalid;
		getData()->inventoryItem = kItemInvalid;
		break;

	case kActionDrawScene:
		params->param1 = getEntities()->isPlayerPosition(kCarRestaurant, 63) ? 1 : 0;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->updatePosition(kEntityAlexei, kCarRestaurant, 63);
			setup_function19();
			break;

		case 2:
			getAction()->playAnimation(getProgress().jacket == kJacketGreen ? kEventAlexeiDiner : kEventAlexeiDinerOriginalJacket);
			getSavePoints()->push(kEntityAlexei, kEntityTables1, kAction103798704, "005E");

			getData()->entityPosition = kPosition_3650;
			getData()->field_493 = kField493_0;

			getEntities()->clearSequences(kEntityAlexei);
			getInventory()->getEntry(kItem17)->location = kLocation1;
			getScenes()->loadSceneFromPosition(kCarRestaurant, 63);

			setup_function19();
			break;
		}
		break;

	case kAction168046720:
		getData()->inventoryItem = kItemNone;
		break;

	case kAction168627977:
		getData()->inventoryItem = (InventoryItem)params->param2;
		break;

	case kAction225182640:
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function19, 19)
	error("Alexei: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Alexei, setup_function14));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Alexei, setup_function10), kCarRestaurant, kPosition_850);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Alexei, setup_function12));
			break;

		case 3:
			getData()->entityPosition = kPosition_1540;
			getData()->field_493 = kField493_0;

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_updatePosition), "103A", kCarRestaurant, 52);
			break;

		case 4:
			getData()->field_493 = kField493_1;
			setup_function26();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function21, 21)
	error("Alexei: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function22, 22)
	error("Alexei: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function23, 23)
	error("Alexei: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function24, 24)
	error("Alexei: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function25, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Alexei, setup_function13));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (getEntities()->isPlayerPosition(kCarGreenSleeping, 61))
				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);

			setCallback(2);
			call(new ENTITY_SETUP_ISII(Alexei, setup_function16), kTime1179000, "411");
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_ISII(Alexei, setup_function16), kTime1323000, "412");
			break;

		case 3:
			setup_function26();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function26, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK(kTime1512000, params->param1, setup_function27)
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_7500;
		getData()->car = kCarGreenSleeping;
		getData()->field_493 = kField493_1;

		getObjects()->update(kObjectCompartment2, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 61))
			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 66);

		getEntities()->clearSequences(kEntityAlexei);
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function27, 27)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObject10, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 66))
			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);

		getEntities()->drawSequenceLeft(kEntityAlexei, "412");
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter2, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2_handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAlexei);

		getObjects()->update(kObjectCompartment2, kEntityAlexei, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityAlexei, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_7500;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter2_handler, 29)
	error("Alexei: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function30, 30)
	error("Alexei: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function31, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityAlexei, "811DS");
		if (getEntities()->checkFields13(kEntityNone))
			getEntities()->updateEntity(kEntityAlexei);

		setCallback(1);
		call(new ENTITY_SETUP(Alexei, setup_function7));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Alexei, setup_function13));
			break;

		case 2:
			if (getEntities()->isPlayerPosition(kCarGreenSleeping, 61))
				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);

			setCallback(3);
			call(new ENTITY_SETUP_ISII(Alexei, setup_function16), 15803100, "411");
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter3, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3_handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAlexei);

		getObjects()->update(kObjectCompartment2, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter3_handler, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function34();
		break;

	case kAction122288808:
		getData()->entityPosition = kPosition_9270;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRedSleeping;

		setCallback(1);
		call(new ENTITY_SETUP(Alexei, setup_function13));
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityAlexei, "BLANK");
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function34, 34)
	error("Alexei: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function35, 35)
	error("Alexei: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function36, 36)
	error("Alexei: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, chapter4, 37)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4_handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAlexei);

		getObjects()->update(kObjectCompartment2, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_7500;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter4_handler, 38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_ISII(Alexei, setup_function16), kTime2354400, "411");
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function39();
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function39, 39)
	error("Alexei: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function40, 40)
	error("Alexei: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function41, 41)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 66))
			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);

		setCallback(1);
		call(new ENTITY_SETUP_ISII(Alexei, setup_function16), kTime2403000, "411");
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function42();
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function42, 42)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Alexei, setup_function14));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityAlexei, kEntityTatiana, kAction191198209);

			setCallback(2);
			call(new ENTITY_SETUP(Alexei, setup_function10), kCarRestaurant, kPosition_850);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_updatePosition), "103A", kCarRestaurant, 52);
			break;

		case 3:
			getData()->field_493 = kField493_1;
			setup_function43();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function43, 43)
	error("Alexei: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function44, 44)
	error("Alexei: callback function 44 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function45, 45)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Alexei, setup_function13));
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			if (getEntities()->isPlayerPosition(kCarGreenSleeping, 66))
				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);

			if (getInventory()->hasItem(kItemBomb)) {
				setup_function46();
			} else {
				setCallback(2);
				call(new ENTITY_SETUP_ISII(Alexei, setup_function16), kTimeEnd, "412");
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function46, 46)
	error("Alexei: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, function47, 47)
	if (savepoint.action == kActionDefault) {
		getEntities()->clearSequences(kEntityAlexei);

		getData()->entityPosition = kPositionNone;
		getData()->field_493 = kField493_0;
		getData()->car = kCarNone;

		getObjects()->update(kObjectCompartment2, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter5, 48)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityAlexei);
}

} // End of namespace LastExpress
