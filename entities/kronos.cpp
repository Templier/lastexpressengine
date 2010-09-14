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

#include "lastexpress/entities/kronos.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Kronos::Kronos(LastExpressEngine *engine) : Entity(engine, kEntityKronos) {
	ADD_CALLBACK_FUNCTION(Kronos, reset);
	ADD_CALLBACK_FUNCTION(Kronos, savegame);
	ADD_CALLBACK_FUNCTION(Kronos, function3);
	ADD_CALLBACK_FUNCTION(Kronos, playSound);
	ADD_CALLBACK_FUNCTION(Kronos, updateFromTime);
	ADD_CALLBACK_FUNCTION(Kronos, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Kronos, chapter1);
	ADD_CALLBACK_FUNCTION(Kronos, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Kronos, function9);
	ADD_CALLBACK_FUNCTION(Kronos, function10);
	ADD_CALLBACK_FUNCTION(Kronos, function11);
	ADD_CALLBACK_FUNCTION(Kronos, chapter2);
	ADD_CALLBACK_FUNCTION(Kronos, chapter3);
	ADD_CALLBACK_FUNCTION(Kronos, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Kronos, function15);
	ADD_CALLBACK_FUNCTION(Kronos, function16);
	ADD_CALLBACK_FUNCTION(Kronos, function17);
	ADD_CALLBACK_FUNCTION(Kronos, function18);
	ADD_CALLBACK_FUNCTION(Kronos, function19);
	ADD_CALLBACK_FUNCTION(Kronos, function20);
	ADD_CALLBACK_FUNCTION(Kronos, function21);
	ADD_CALLBACK_FUNCTION(Kronos, function22);
	ADD_CALLBACK_FUNCTION(Kronos, function23);
	ADD_CALLBACK_FUNCTION(Kronos, chapter4);
	ADD_CALLBACK_FUNCTION(Kronos, chapter5);
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Kronos, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Kronos, savegame, 2)
	Entity::savegame(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Kronos, function3, 3)
	Entity::updateEntity(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_NOSETUP(Kronos, playSound, 4)
	Entity::playSound(savepoint);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_NOSETUP(Kronos, updateFromTime, 5)
	Entity::updateFromTime(savepoint);
}

/**
 * Updates parameter 2 using ticks value
 *
 * @param savepoint The savepoint
 *                    - number of ticks to add
 */
IMPLEMENT_FUNCTION_NOSETUP(Kronos, updateFromTicks, 6)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION(Kronos, chapter1, 7)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_6000;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarKronos;

		getObjects()->update(kObjectCeiling, kEntityPlayer, kLocation1, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, chapter1Handler, 8)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK(kTime1489500, params->param2, setup_function11);
		break;

	case kAction171849314:
		params->param1 = 1;
		break;

	case kAction202621266:
		setup_function9();
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, function9, 9)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_savegame(kSavegameTypeEvent, kEventKronosConversation);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventKronosConversation);
			getScenes()->loadSceneFromPosition(kCarKronos, 87);
            getSavePoints()->push(kEntityKronos, kEntityKahina, kAction137685712);
            setup_function10();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, function10, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK(kTime1489500, params->param1, setup_function11);

		if (params->param1 && getEntities()->isInsideTrainCar(kEntityPlayer, kCarKronos)) {
			UPDATE_PARAM(params->param3, getState()->timeTicks, 150);
			setup_function9();
		}
	break;

	case kActionDefault:
		getData()->entityPosition = kPosition_6000;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarKronos;

		getEntities()->clearSequences(kEntityKronos);
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, function11, 11)
	switch (savepoint.action) {
	default:
		break;

	case kAction2:
		params->param1++;
		getSound()->playSound(kEntityKronos, (params->param1 & 1) ? "KRO1001" : "KRO1002");
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_7000;

		if (!getSound()->isBuffered(kEntityKronos))
			getSound()->playSound(kEntityKronos, "KRO1001");
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, chapter2, 12)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityKronos);
}

IMPLEMENT_FUNCTION(Kronos, chapter3, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityKronos);

		getData()->entityPosition = kPosition_6000;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarKronos;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCeiling, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, chapter3Handler, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime1993500 && !params->param1 && !params->param2 && !params->param3)
			setup_function15();
		break;

	case kAction157159392:
		switch (savepoint.entity2) {
		case kEntityAnna:
			params->param1 = 1;
			break;

		case kEntityTatiana:
			params->param2 = 1;
			break;

		case kEntityAbbot:
			params->param3 = 1;
			break;

		default:
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, function15, 15)
	error("Kronos: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function16, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_savegame(kSavegameTypeEvent, kEventKronosVisit);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventKronosVisit);
			getSavePoints()->push(kEntityKronos, kEntityAnna, kAction101169422);
			getSavePoints()->push(kEntityKronos, kEntityTatiana, kAction101169422);
			getSavePoints()->push(kEntityKronos, kEntityAbbot, kAction101169422);
			getScenes()->loadSceneFromPosition(kCarRestaurant, 60);

			setup_function17();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, function17, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_7500;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarRedSleeping;

		setCallback(1);
		setup_function3(kCarGreenSleeping, kPosition_9270);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function18();
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, function18, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime2079000 && !params->param2) {
			getObjects()->updateLocation2(kObjectCompartmentKronos, kLocation3);
			getObjects()->update(kObjectCompartmentKronos, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
			params->param1 = 1;
			params->param2 = 1;
		}

		TIME_CHECK(kTime2106000, params->param3, setup_function19)
		else {
			if (params->param1 && getEntities()->isInKronosSanctum(kEntityPlayer)) {
				setCallback(1);
				setup_savegame(kSavegameTypeEvent, kEventKahinaPunchSuite4);
			}
		}
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_6000;
		getData()->car = kCarKronos;
		getData()->location = kLocationOutsideCompartment;
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventKahinaPunchSuite4);
			getLogic()->gameOver(kSavegameTypeEvent2, kEventCathJumpDownCeiling, kSceneNone, true);
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, function19, 19)
	error("Kronos: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function20, 20)
	error("Kronos: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function21, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->isInKronosSanctum(kEntityPlayer)) {
			setCallback(1);
			setup_savegame(kSavegameTypeEvent, kEventKahinaWrongDoor);
		}
		break;

	case kActionDefault:
		getProgress().field_40 = 0;
		getObjects()->update(kObjectCompartmentKronos, kEntityPlayer, kLocation3, kCursorNormal, kCursorNormal);
		getSavePoints()->push(kEntityKronos, kEntityRebecca, kAction191668032);
		if (!getEvent(kEventConcertLeaveWithBriefcase))
			setup_function22();
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventKahinaWrongDoor);

			if (getInventory()->hasItem(kItemBriefcase))
				getInventory()->removeItem(kItemBriefcase);

			getSound()->playSound(kEntityPlayer, "BUMP");

			getScenes()->loadSceneFromPosition(kCarKronos, 81);

			getSound()->playSound(kEntityPlayer, "LIB015");
		}
		break;

	case kAction235599361:
		setup_function22();
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, function22, 22)
	error("Kronos: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->isInKronosSanctum(kEntityPlayer)) {
			setCallback(1);
			setup_savegame(kSavegameTypeEvent, kEventKahinaWrongDoor);
		}
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentKronos, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventKahinaWrongDoor);

			if (getInventory()->hasItem(kItemBriefcase))
				getInventory()->removeItem(kItemBriefcase);

			getSound()->playSound(kEntityPlayer, "BUMP");

			getScenes()->loadSceneFromPosition(kCarKronos, 81);

			getSound()->playSound(kEntityPlayer, "LIB015");
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, chapter4, 24)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityKronos);
}

IMPLEMENT_FUNCTION(Kronos, chapter5, 25)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityKronos);
}

} // End of namespace LastExpress
