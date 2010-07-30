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

#include "lastexpress/entities/abbot.h"

#include "lastexpress/entities/verges.h"

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

Abbot::Abbot(LastExpressEngine *engine) : Entity(engine, kEntityAbbot) {
	ADD_CALLBACK_FUNCTION(Abbot, reset);
	ADD_CALLBACK_FUNCTION(Abbot, draw);
	ADD_CALLBACK_FUNCTION(Abbot, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Abbot, function4);
	ADD_CALLBACK_FUNCTION(Abbot, function5);
	ADD_CALLBACK_FUNCTION(Abbot, draw2);
	ADD_CALLBACK_FUNCTION(Abbot, updateFromTime);
	ADD_CALLBACK_FUNCTION(Abbot, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Abbot, playSound);
	ADD_CALLBACK_FUNCTION(Abbot, savegame);
	ADD_CALLBACK_FUNCTION(Abbot, function11);
	ADD_CALLBACK_FUNCTION(Abbot, callSavepoint);
	ADD_CALLBACK_FUNCTION(Abbot, updatePosition);
	ADD_CALLBACK_FUNCTION(Abbot, function14);
	ADD_CALLBACK_FUNCTION(Abbot, chapter1);
	ADD_CALLBACK_FUNCTION(Abbot, chapter2);
	ADD_CALLBACK_FUNCTION(Abbot, chapter3);
	ADD_CALLBACK_FUNCTION(Abbot, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Abbot, function19);
	ADD_CALLBACK_FUNCTION(Abbot, function20);
	ADD_CALLBACK_FUNCTION(Abbot, function21);
	ADD_CALLBACK_FUNCTION(Abbot, function22);
	ADD_CALLBACK_FUNCTION(Abbot, function23);
	ADD_CALLBACK_FUNCTION(Abbot, function24);
	ADD_CALLBACK_FUNCTION(Abbot, function25);
	ADD_CALLBACK_FUNCTION(Abbot, function26);
	ADD_CALLBACK_FUNCTION(Abbot, function27);
	ADD_CALLBACK_FUNCTION(Abbot, function28);
	ADD_CALLBACK_FUNCTION(Abbot, function29);
	ADD_CALLBACK_FUNCTION(Abbot, function30);
	ADD_CALLBACK_FUNCTION(Abbot, function31);
	ADD_CALLBACK_FUNCTION(Abbot, function32);
	ADD_CALLBACK_FUNCTION(Abbot, function33);
	ADD_CALLBACK_FUNCTION(Abbot, function34);
	ADD_CALLBACK_FUNCTION(Abbot, function35);
	ADD_CALLBACK_FUNCTION(Abbot, function36);
	ADD_CALLBACK_FUNCTION(Abbot, function37);
	ADD_CALLBACK_FUNCTION(Abbot, function38);
	ADD_CALLBACK_FUNCTION(Abbot, chapter4);
	ADD_CALLBACK_FUNCTION(Abbot, function40);
	ADD_CALLBACK_FUNCTION(Abbot, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Abbot, function42);
	ADD_CALLBACK_FUNCTION(Abbot, function43);
	ADD_CALLBACK_FUNCTION(Abbot, function44);
	ADD_CALLBACK_FUNCTION(Abbot, function45);
	ADD_CALLBACK_FUNCTION(Abbot, function46);
	ADD_CALLBACK_FUNCTION(Abbot, drinkAfterDefuse);
	ADD_CALLBACK_FUNCTION(Abbot, function48);
	ADD_CALLBACK_FUNCTION(Abbot, pickBomb);
	ADD_CALLBACK_FUNCTION(Abbot, chapter5);
	ADD_CALLBACK_FUNCTION(Abbot, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Abbot, function52);
	ADD_CALLBACK_FUNCTION(Abbot, function53);
}

IMPLEMENT_FUNCTION(Abbot, reset, 1)
	Entity::reset(savepoint);
}

IMPLEMENT_FUNCTION_S(Abbot, draw, 2)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SI(Abbot, enterExitCompartment, 3)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_SI(Abbot, function4, 4)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->exitCompartment(kEntityAbbot, (ObjectIndex)params->param4, false);
		getData()->entityPosition = kPosition_6470;
		getData()->field_493 = kField493_1;

		CALLBACK_ACTION()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityAbbot, (char *)&params->seq1);
		getEntities()->enterCompartment(kEntityAbbot, (ObjectIndex)params->param4, false);

		getData()->field_493 = kField493_1;
		if (getEntities()->checkFields1(kEntityNone, kCarRedSleeping, kPosition_6470)
		 || getEntities()->checkFields1(kEntityNone, kCarRedSleeping, kPosition_6130)) {
			getAction()->playAnimation(isDay() ? kEventCathTurningDay : kEventCathTurningNight);
			getSound()->playSound(kEntityNone, "BUMP");
			getScenes()->loadSceneFromObject(kObjectCompartmentC, true);
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function5, 5)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_SSI(Abbot, draw2, 6)
	Entity::draw2(savepoint);
}

IMPLEMENT_FUNCTION_I(Abbot, updateFromTime, 7)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_I(Abbot, updateFromTicks, 8)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION_S(Abbot, playSound, 9)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_II(Abbot, savegame, 10)
	Entity::savegame(savepoint);
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - CarIndex
//  - EntityPosition
IMPLEMENT_FUNCTION_II(Abbot, function11, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->checkEntity(kEntityAbbot, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION()
		break;

	case kActionExcuseMeCath:
		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 18) || getEntities()->isPlayerPosition(kCarRedSleeping, 18)) {
			getSound()->excuseMe(kEntityAbbot);
		} else {
			if (getEvent(kEventAbbotIntroduction))
				getSound()->playSound(kEntityNone, "CAT1013");
			else
				getSound()->excuseMeCath();
		}
		break;

	case kActionExcuseMe:
		getSound()->excuseMe(kEntityAbbot);
		break;

	case kActionDefault:
		if (getEntities()->checkEntity(kEntityAbbot, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION()
		break;
	}
}

IMPLEMENT_FUNCTION_SIIS(Abbot, callSavepoint, 12)
	Entity::callSavepoint(savepoint);
}

IMPLEMENT_FUNCTION_SII(Abbot, updatePosition, 13)
	Entity::updatePosition(savepoint);
}

IMPLEMENT_FUNCTION(Abbot, function14, 14)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION(Abbot, chapter1, 15)
	if (savepoint.action == kActionDefault)
		getSavePoints()->addData(kEntityAbbot, kAction203073664, 0);
}

IMPLEMENT_FUNCTION(Abbot, chapter2, 16)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityAbbot);
}

IMPLEMENT_FUNCTION(Abbot, chapter3, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAbbot);

		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		getData()->clothes = kClothesDefault;

		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, chapter3Handler, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->entityPosition = kPosition_5800;
			getData()->field_493 = kField493_0;

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_draw), "804DD");
			break;

		case 2:
			getSavePoints()->push(kEntityAbbot, kEntityCooks, kAction236976550);
			getEntities()->drawSequenceRight(kEntityAbbot, "804DS");

			if (getEntities()->checkFields13())
				getEntities()->updateEntity(kEntityAbbot);

			setCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function5));
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Abbot, setup_function11), kCarRedSleeping, kPosition_6470);
			break;

		case 4:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_enterExitCompartment), "617AC", kObjectCompartmentC);
			break;

		case 5:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getData()->entityPosition = kPosition_6470;
			getData()->field_493 = kField493_1;

			setup_function19();
			break;
		}
		break;

	case kAction192054567:
		setCallback(1);
        call(new ENTITY_SETUP(Abbot, setup_function14));
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function19, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime1953000) {
			if (!params->param1) {
				params->param1 = 1;
				setCallback(3);
				call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "MrB3010");
			}
		}
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAbbot, "508A");
		getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122358304);

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "Abb3010");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Abbot, setup_updateFromTime), 900);
			break;

		case 2:
			getEntities()->drawSequenceLeft(kEntityAbbot, "508B");
			break;

		case 3:
			getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122288808);
			setup_function20();
			break;
		}
	}
}

IMPLEMENT_FUNCTION(Abbot, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime1966500 && getEntities()->checkFields13(kEntityBoutarel))
			setup_function21();
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAbbot, "509A");
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function21, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_draw), "509B");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject50, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_enterExitCompartment), "617Mc", kObjectCompartmentC);
			break;

		case 2:
			getData()->field_493 = kField493_0;

			setCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function11), kCarRestaurant, kPosition_850);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Abbot, setup_function14));
			break;

		case 4:
			getData()->entityPosition = kPosition_1540;
			getData()->field_493 = kField493_0;

			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_draw), "804US");
			break;

		case 5:
			getEntities()->drawSequenceRight(kEntityAbbot, "029J");
			if (getEntities()->checkFields12())
				getEntities()->updateEntity(kEntityAbbot);

			setCallback(6);
			call(new ENTITY_SETUP(Abbot, setup_function5));
			break;

		case 6:
			getEntities()->drawSequenceLeft(kEntityAbbot, "029H");
			getSavePoints()->push(kEntityAbbot, kEntityPascale, kAction207769280);
			break;

		case 7:
			setup_function22();
			break;
		}
		break;

	case kAction122288808:
		getSavePoints()->push(kEntityAbbot, kEntityTables4, kAction136455232);
		getData()->field_493 = kField493_1;

		setCallback(7);
        call(new ENTITY_SETUP_SIIS(Abbot, setup_draw), "029B");
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function22, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime1971000 && !params->param1) {
			params->param1 = 1;
			getSavePoints()->push(kEntityAbbot, kEntityServers0, kAction218586752);
		}

		if (getState()->time > kTime1989000 && getEntities()->checkFields11()) {
			getData()->inventoryItem = kItemNone;
			setup_function23();
		}
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;

		setCallback(1);
		call(new ENTITY_SETUP(Abbot, setup_savegame), kSavegameType2, kEventAbbotIntroduction);
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAbbot, "029E");
		if (!getEvent(kEventAbbotIntroduction))
			getData()->inventoryItem = (InventoryItem)kCursorProcess;
		break;

	case kActionCallback:
		if (getCallback() != 1)
			break;

		getAction()->playAnimation(kEventAbbotIntroduction);
		getSound()->playSound(kEntityNone, "LIB036");
		getScenes()->loadSceneFromPosition(kCarRestaurant, 61);
		break;

	case kAction122288808:
		getEntities()->drawSequenceLeft(kEntityAbbot, "029E");
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityAbbot, "BLANK");
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->field_493 = kField493_0;
		getEntities()->updatePosition(kEntityAbbot, kCarRestaurant, 67, true);

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_callSavepoint), "029F", kEntityTables4, kAction103798704, "029G");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->updatePosition(kEntityAbbot, kCarRestaurant, 67);
			getSavePoints()->push(kEntityAbbot, kEntityServers0, kAction270068760);
			getSavePoints()->push(kEntityAbbot, kEntityAnna, kAction238936000);
			getEntities()->drawSequenceRight(kEntityAbbot, "804DS");

			if (getEntities()->checkFields13())
				getEntities()->updateEntity(kEntityAbbot);

			setCallback(2);
			call(new ENTITY_SETUP(Abbot, setup_function5));
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function11), kCarRedSleeping, kPosition_6470);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_function4), "617Cc", 34);
			break;

		case 4:
			getData()->field_493 = kField493_1;

			setup_function24();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function24, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM(params->param1, getState()->time, 900);

		setup_function25();
		break;

	case kAction8:
	case kAction9:
		getObjects()->update(kObjectCompartmentC, kEntityAbbot, kLocation1, kCursorNormal, kCursorNormal);
		getObjects()->update(kObject50, kEntityAbbot, kLocation1, kCursorNormal, kCursorNormal);

		if (savepoint.action == kAction8) {
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "LIB012");
		} else {
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "LIB013");
		}
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAbbot);
		getObjects()->update(kObjectCompartmentC, kEntityAbbot, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityAbbot, kLocationNone, kCursorHandKnock, kCursorHand);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "Abb3001");
			break;

		case 3:
			getObjects()->update(kObjectCompartmentC, kEntityAbbot, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject50, kEntityAbbot, kLocation1, kCursorHandKnock, kCursorHand);
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function25, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_enterExitCompartment), "617Dc", kObjectCompartmentC);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->field_493 = kField493_0;
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject50, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

			setCallback(2);
			call(new ENTITY_SETUP(Abbot, setup_function11), kCarRestaurant,  kPosition_850);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function14));
			break;

		case 3:
			getData()->entityPosition = kPosition_1540;
			getData()->field_493 = kField493_0;

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_updatePosition), "115A", 5, 56);
			break;

		case 4:
			getData()->field_493 = kField493_1;
			getScenes()->loadSceneFromItemPosition(kItem3);

			setup_function26();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function26, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM(params->param2, getState()->time, 4500);

		if (getEntities()->checkFields11())
			setup_function27();
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAbbot, kEntityKronos, kAction157159392);
		getEntities()->drawSequenceLeft(kEntityAbbot, "115B");
		break;

	case kAction101169422:
		params->param1 = 1;
		break;

	}
}

IMPLEMENT_FUNCTION(Abbot, function27, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Abbot, setup_function14));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->field_493 = kField493_0;

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_updatePosition), "115C", 5, 56);
			break;

		case 2:
			getInventory()->setLocationAndProcess(kItem3, kLocation1);

			setCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function11), kCarRedSleeping, kPosition_6470);
			break;

		case 3:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_enterExitCompartment), "617Ac", kObjectCompartmentC);
			break;

		case 4:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getData()->entityPosition = kPosition_6470;
			getData()->field_493 = kField493_1;

			setup_function28();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function28, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Abbot, kTime2052000, params->param1, 1, setup_function29);
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122358304);
		getEntities()->drawSequenceLeft(kEntityAbbot, "508A");

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "abb3013");
		break;

	case kActionCallback:
		if (getCallback() == 1)
			getEntities()->drawSequenceLeft(kEntityAbbot, "508B");
		break;

	case kAction222609266:
		setup_function30();
	}
}

IMPLEMENT_FUNCTION(Abbot, function29, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122288808);
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_enterExitCompartment), "617Bc", kObjectCompartmentC);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);

			setCallback(2);
			call(new ENTITY_SETUP(Abbot, setup_function11), kCarRedSleeping, kPosition_9460);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_updateFromTicks), 450);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Abbot, setup_function11), kCarGreenSleeping, kPosition_540);
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP(Abbot, setup_updateFromTime), 225);
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Abbot, setup_function11), kCarRedSleeping, kPosition_6470);
			break;

		case 6:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

			setCallback(7);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_enterExitCompartment), "617Ac", kObjectCompartmentC);
			break;

		case 7:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122358304);
			getEntities()->drawSequenceLeft(kEntityAbbot, "508B");

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function30, 30)
switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "Abb3030");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122288808);
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_enterExitCompartment), "617Bc", kObjectCompartmentC);
			break;

		case 2:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getData()->field_493 = kField493_0;

			setCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function11), kCarRestaurant, kPosition_850);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Abbot, setup_function14));
			break;

		case 4:
			getData()->entityPosition = kPosition_1540;
			getData()->field_493 = kField493_0;

			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_updatePosition), "115A", 5, 56);
			break;

		case 5:
			getScenes()->loadSceneFromItemPosition(kItem3);
			getData()->field_493 = kField493_1;

			setup_function31();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function31, 31)
	error("Abbot: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function32, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Abbot, setup_function11), kCarRedSleeping, kPosition_6470);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_enterExitCompartment), "617Ac", kObjectCompartmentC);
			break;

		case 2:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getData()->entityPosition = kPosition_6470;
			getData()->field_493 = kField493_1;
			getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122358304);

			setup_function33();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function33, 33)
	error("Abbot: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function34, 34)
	error("Abbot: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function35, 35)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1 != kTimeInvalid && getState()->time > kTime2115000) {
			if (getState()->time <= kTime2124000) {
				if (!getEntities()->checkFields9(kEntityAbbot, kEntityNone, 2000) || !params->param1)
					params->param1 = (int)getState()->time;

				if (params->param1 >= (int)getState()->time)
					break;
			}

			params->param1 = kTimeInvalid;

			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "Abb3014");
		}
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAbbot, "508A");
		break;

	case kActionCallback:
		if (getCallback() == 1)
			getEntities()->drawSequenceLeft(kEntityAbbot, "508B");
		break;

	case kAction123712592:
		setup_function34();
	}
}

IMPLEMENT_FUNCTION(Abbot, function36, 36)
	error("Abbot: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function37, 37)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Abbot, setup_function11), kCarRedSleeping, kPosition_6470);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_enterExitCompartment), "617Ac", kObjectCompartmentC);
			break;

		case 2:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getData()->entityPosition = kPosition_6470;
			getData()->field_493 = kField493_1;
			getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122358304);

			setup_function38();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function38, 38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAbbot, "508A");

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "Abb3014A");
		break;

	case kActionCallback:
		if (getCallback() == 1)
			getEntities()->drawSequenceLeft(kEntityAbbot, "508B");
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, chapter4, 39)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAbbot);

		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 1) = 0;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - CarIndex
//  - EntityPosition
IMPLEMENT_FUNCTION_II(Abbot, function40, 40)
	error("Abbot: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, chapter4Handler, 41)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime2358000 && !params->param1) {
			params->param1 = 1;
			getSavePoints()->push(kEntityAbbot, kEntityServers0, kAction218128129);
		}

		if (getState()->time > kTime3289500 && getEntities()->checkFields11())
			setup_function42();

		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAbbot, kEntityTables4, kAction136455232);
		getEntities()->drawSequenceLeft(kEntityAbbot, "029E");
		getData()->field_493 = kField493_1;
		break;

	case kAction122288808:
		getEntities()->drawSequenceLeft(kEntityAbbot, "029E");
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityAbbot, "BLANK");
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function42, 42)
	error("Abbot: callback function 42 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function43, 43)
	error("Abbot: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function44, 44)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_6470;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;

		getEntities()->clearSequences(kEntityAbbot);

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		break;

	case kAction104060776:
		setup_function45();
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function45, 45)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_6471;
		getData()->car = kCarRedSleeping;
		getData()->field_493 = kField493_0;

		RESET_ENTITY_STATE(kEntityVerges, Verges, setup_function38);

		getEntities()->drawSequenceLeft(kEntityAbbot, "617Ec");
		getEntities()->enterCompartment(kEntityAbbot, kObjectCompartmentC);

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "Abb4010");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_enterExitCompartment), "617Kc");
			break;

		case 2:
			getEntities()->exitCompartment(kEntityAbbot, kObjectCompartmentC);
			getSavePoints()->push(kEntityAbbot, kEntityVerges, kAction125233040);

			setup_function46();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function46, 46)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_6471;

		setCallback(1);
		call(new ENTITY_SETUP(Abbot, setup_function40), kCarRestaurant, kPosition_850);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_drinkAfterDefuse();
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, drinkAfterDefuse, 47)
	switch (savepoint.action) {
	default:
		break;

	case kAction1:
		setCallback(3);
		call(new ENTITY_SETUP(Abbot, setup_savegame), kSavegameType2, kEventAbbotDrinkGiveDetonator);
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Abbot, setup_function14));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->entityPosition = kPosition_1540;
			getData()->field_493 = kField493_0;

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_draw), "126A");
			break;

		case 2:
			getData()->field_493 = kField493_1;
			getEntities()->drawSequenceLeft(kEntityAbbot, "126B");
			getData()->inventoryItem = kItemBomb;
			break;

		case 3:
			getAction()->playAnimation(kEventAbbotDrinkGiveDetonator);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneNone, true);
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function48, 48)
	error("Abbot: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, pickBomb, 49)
	error("Abbot::pickBomb: callback 49 function not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, chapter5, 50)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAbbot);

		getData()->entityPosition = kPosition_3969;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		getData()->clothes = kClothesDefault;
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, chapter5Handler, 51)
	if (savepoint.action == kActionProceedChapter5)
		setup_function52();
}

IMPLEMENT_FUNCTION(Abbot, function52, 52)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAbbot);

		getData()->entityPosition = kPositionNone;
		getData()->field_493 = kField493_0;
		getData()->car = kCarNone;
		break;

	case kAction135600432:
		setup_function53();
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function53, 53)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getInventory()->setLocationAndProcess(kItem25, kLocation1);
		getSavePoints()->push(kEntityAbbot, kEntityAnna, kAction158480160);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventLocomotiveAbbotGetSomeRest);
			getScenes()->processScene();
			break;

		case 2:
			getAction()->playAnimation(kEventLocomotiveAbbotShoveling);
			getScenes()->processScene();
			break;
		}
		break;

	case kAction168646401:
		if (!getEvent(kEventLocomotiveAbbotGetSomeRest)) {
			setCallback(1);
			call(new ENTITY_SETUP(Abbot, setup_savegame), kSavegameType2, kEventLocomotiveAbbotGetSomeRest);
			break;
		}

		if (!getEvent(kEventLocomotiveAbbotShoveling)) {
			setCallback(2);
			call(new ENTITY_SETUP(Abbot, setup_savegame), kSavegameType2, kEventLocomotiveAbbotShoveling);
			break;
		}

		getAction()->playAnimation(kEventLocomotiveAbbotShoveling);
		getScenes()->processScene();
		break;
	}
}

} // End of namespace LastExpress
