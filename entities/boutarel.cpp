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
#include "lastexpress/game/inventory.h"
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
	ADD_CALLBACK_FUNCTION(Boutarel, reset);
	ADD_CALLBACK_FUNCTION(Boutarel, playSound);
	ADD_CALLBACK_FUNCTION(Boutarel, draw);
	ADD_CALLBACK_FUNCTION(Boutarel, updateFromTime);
	ADD_CALLBACK_FUNCTION(Boutarel, updatePosition);
	ADD_CALLBACK_FUNCTION(Boutarel, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Boutarel, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(Boutarel, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Boutarel, callbackActionRestaurantOrSalon);
	ADD_CALLBACK_FUNCTION(Boutarel, updateEntity);
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
	ADD_CALLBACK_FUNCTION(Boutarel, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Boutarel, function22);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter2);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Boutarel, function25);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter3);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Boutarel, function28);
	ADD_CALLBACK_FUNCTION(Boutarel, function29);
	ADD_CALLBACK_FUNCTION(Boutarel, function30);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter4);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Boutarel, function33);
	ADD_CALLBACK_FUNCTION(Boutarel, function34);
	ADD_CALLBACK_FUNCTION(Boutarel, function35);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter5);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Boutarel, function38);
	ADD_NULL_FUNCTION();
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Boutarel, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Boutarel, playSound, 2)
	Entity::playSound(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Boutarel, draw, 3)
	Entity::draw(savepoint);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_I(Boutarel, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

/**
 * Updates the position
 *
 * @param seq1   The sequence to draw
 * @param param4 The car
 * @param param5 The entity position
 */
IMPLEMENT_FUNCTION_SII(Boutarel, updatePosition, 5)
	Entity::updatePosition(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Boutarel, enterExitCompartment, 6)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Handles entering/exiting a compartment and updates position/play animation
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Boutarel, enterExitCompartment2, 7)
	Entity::enterExitCompartment(savepoint, kPosition_6470, kPosition_6130, kCarRedSleeping, kObjectCompartmentC, true);
}

/**
 * Process callback action when the entity direction is not kDirectionRight
 */
IMPLEMENT_FUNCTION(Boutarel, callbackActionOnDirection, 8)
	Entity::callbackActionOnDirection(savepoint);
}

/**
 * Process callback action when somebody is standing in the restaurant or salon.
 */
IMPLEMENT_FUNCTION(Boutarel, callbackActionRestaurantOrSalon, 9)
	Entity::callbackActionRestaurantOrSalon(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Boutarel, updateEntity, 10)
	if (savepoint.action == kActionExcuseMeCath) {

		if (getInventory()->hasItem(kItemPassengerList) && getState()->time > kTime1089000)
			getSound()->playSound(kEntityPlayer, "CAT1022");
		else
			getSound()->excuseMeCath();

		return;
	}

	Entity::updateEntity(savepoint, true);
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
		getData()->posture = kPostureSitting;

		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityTables2, "008A3");
		getEntities()->drawSequenceRight(kEntityMmeBoutarel, "008A2");
		getEntities()->drawSequenceRight(kEntityBoutarel, "008A1");

		if (getEntities()->isInSalon(kEntityPlayer)) {
			getEntities()->updateFrame(kEntityBoutarel);
			getEntityData(kEntityMmeBoutarel)->posture = getData()->posture;
			getEntityData(kEntityTables2)->posture = getData()->posture;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, leaveTableWithMmeBoutarel, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getSavePoints()->push(kEntityBoutarel, kEntityTables2, kActionDrawTablesWithChairs, "008F");
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
		call(new ENTITY_SETUP(Boutarel, setup_callbackActionRestaurantOrSalon));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->posture = kPostureStanding;

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Boutarel, setup_updatePosition), (const char *)&params->seq, kCarRestaurant, 52);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Boutarel, setup_updateEntity), kCarRedSleeping, kPosition_6470);
			break;

		case 3:
			setCallback(params->param1 ? 4 : 5);
			call(new ENTITY_SETUP_SIIS(Boutarel, setup_enterExitCompartment2), params->param1 ? "607Gc" : "607Ac", kObjectCompartmentC);
			break;

		case 4:
		case 5:
			getData()->posture = kPostureSitting;
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
		TIME_CHECK_CALLBACK_ACTION(Boutarel, params->param1, params->param6);

		if (params->param5) {
			UPDATE_PARAM(params->param7, getState()->timeTicks, 90)
			getScenes()->loadSceneFromPosition(kCarRestaurant, 51);
		} else {
			params->param7 = 0;
		}
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityBoutarel, (char *)&params->seq);
		break;

	case kActionDrawScene:
		params->param5 = (getEntities()->isPlayerPosition(kCarRestaurant, 52) ? 1 : 0);
		break;
	}
}

IMPLEMENT_FUNCTION_I(Boutarel, function18, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1 < getState()->time && !params->param4) {
			params->param4 = 1;

			getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject50, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);

			CALLBACK_ACTION();
			break;
		}

		if (params->param2) {
			UPDATE_PARAM(params->param5, getState()->timeTicks, 75);

			params->param2 = 0;
			params->param3 = 1;

			getObjects()->update(kObjectCompartmentC, kEntityBoutarel, kLocation1, kCursorNormal, kCursorNormal);
			getObjects()->update(kObject50, kEntityBoutarel, kLocation1, kCursorNormal, kCursorNormal);
		}

		params->param5 = 0;
		break;

	case kActionKnock:
	case kActionOpenDoor:
		getObjects()->update(kObjectCompartmentC, kEntityBoutarel, kLocation1, kCursorNormal, kCursorNormal);
		getObjects()->update(kObject50, kEntityBoutarel, kLocation1, kCursorNormal, kCursorNormal);

		if (params->param2) {
			if (savepoint.param.intValue == 50) {
				setCallback(4);
				call(new ENTITY_SETUP_SIIS(Boutarel, setup_playSound), getSound()->justAMinuteCath());
			} else if (getInventory()->hasItem(kItemPassengerList)) {
				setCallback(5);
				call(new ENTITY_SETUP_SIIS(Boutarel, setup_playSound), rnd(2) ? "CAT1511" : getSound()->wrongDoorCath());
			} else {
				setCallback(6);
				call(new ENTITY_SETUP_SIIS(Boutarel, setup_playSound), getSound()->wrongDoorCath());
			}
		} else {
			setCallback(savepoint.action == kActionKnock ? 1 : 2);
			call(new ENTITY_SETUP_SIIS(Boutarel, setup_playSound), savepoint.action == kActionKnock ? "LIB012" : "LIB013");
		}
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentC, kEntityBoutarel, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityBoutarel, kLocation1, kCursorHandKnock, kCursorHand);
		break;

	case kActionDrawScene:
		if (params->param3 || params->param2) {
			getObjects()->update(kObjectCompartmentC, kEntityBoutarel, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject50, kEntityBoutarel, kLocation1, kCursorHandKnock, kCursorHand);

			params->param2 = 0;
			params->param3 = 0;
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Boutarel, setup_playSound), rnd(2) ? "MRB1001" : "MRB1001A");
			break;

		case 3:
			getObjects()->update(kObjectCompartmentC, kEntityBoutarel, kLocation1, kCursorTalk, kCursorNormal);
			getObjects()->update(kObject50, kEntityBoutarel, kLocation1, kCursorTalk, kCursorNormal);

			params->param2 = 1;
			break;

		case 4:
		case 5:
		case 6:
			params->param2 = 0;
			params->param3 = 1;
			break;

		case 7:
			getSavePoints()->push(kEntityBoutarel, kEntityCoudert, kAction123199584);
			break;

		}
		break;

	case kAction122865568:
		getSavePoints()->push(kEntityBoutarel, kEntityCoudert, kAction88652208);
		break;

	case kAction221683008:
		setCallback(7);
		call(new ENTITY_SETUP_SIIS(Boutarel, setup_playSound), "MRB1001");
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter1, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityBoutarel, kAction203520448, 0);
		getSavePoints()->addData(kEntityBoutarel, kAction237889408, 1);

		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject42, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->entityPosition = kPosition_1750;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function20, 20)
	error("Boutarel: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, chapter1Handler, 21)
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
			getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocation1, kCursorNormal, kCursorNormal);
			getObjects()->update(kObject50, kEntityPlayer, kLocation1, kCursorNormal, kCursorNormal);

			if (getEntities()->isPlayerPosition(kCarRedSleeping, 54) || getEntities()->isPlayerPosition(kCarRedSleeping, 44))
				getScenes()->loadSceneFromPosition(kCarRedSleeping, 10);

			getEntities()->updatePositionExit(kEntityBoutarel, kCarRedSleeping, 54);
			getEntities()->updatePositionExit(kEntityBoutarel, kCarRedSleeping, 44);

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Boutarel, setup_playSound), "MRB1074");
			break;

		case 4:
			getEntities()->updatePositionExit(kEntityBoutarel, kCarRedSleeping, 54);
			getEntities()->updatePositionExit(kEntityBoutarel, kCarRedSleeping, 44);

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
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getEntities()->clearSequences(kEntityBoutarel);
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter2, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityBoutarel);

		getData()->entityPosition = kPosition_4689;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter2Handler, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Boutarel, kTime1759500, params->param2, 1, setup_function14);
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityBoutarel, "008D");
		break;

	case kActionDrawScene:
		if (getEntities()->isInRestaurant(kEntityPlayer) && !params->param1) {
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
		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter3, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityBoutarel);

		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject50, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter3Handler, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocation2, kCursorKeepValue, kCursorKeepValue);
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
		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocation2, kCursorKeepValue, kCursorKeepValue);
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
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityBoutarel);

		getData()->entityPosition = kPosition_6470;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject50, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter4Handler, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK(kTime2367000, params->param1, setup_function33);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function33, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1)
			TIME_CHECK_CALLBACK_I(Boutarel, kTime2389500, params->param2, 3, setup_function14, false);
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Boutarel, setup_function11), true);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceLeft(kEntityBoutarel, "008B");

			setCallback(2);
			call(new ENTITY_SETUP(Boutarel, setup_updateFromTime), 450);
			break;

		case 2:
			getSavePoints()->push(kEntityBoutarel, kEntityServers1, kAction256200848);
			break;

		case 3:
			setup_function34();
			break;
		}
		break;

	case kAction122288808:
		params->param1 = 1;
		getEntities()->drawSequenceLeft(kEntityBoutarel, "008D");
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityBoutarel, "BLANK");
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function34, 34)
	error("Boutarel: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function35, 35)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_6470;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;

		getEntities()->clearSequences(kEntityBoutarel);

		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter5, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityBoutarel);

		getData()->entityPosition = kPosition_3969;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter5Handler, 37)
	if (savepoint.action == kActionProceedChapter5)
		setup_function38();
}

IMPLEMENT_FUNCTION(Boutarel, function38, 38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		break;

	case kAction135800432:
		setup_nullfunction();
		break;
	}
}

IMPLEMENT_NULL_FUNCTION(Boutarel, 39)

} // End of namespace LastExpress
