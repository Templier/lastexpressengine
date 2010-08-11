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
	ADD_CALLBACK_FUNCTION(Alexei, reset);
	ADD_CALLBACK_FUNCTION(Alexei, playSound);
	ADD_CALLBACK_FUNCTION(Alexei, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Alexei, draw);
	ADD_CALLBACK_FUNCTION(Alexei, updatePosition);
	ADD_CALLBACK_FUNCTION(Alexei, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Alexei, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Alexei, callSavepoint);
	ADD_CALLBACK_FUNCTION(Alexei, savegame);
	ADD_CALLBACK_FUNCTION(Alexei, updateEntity);
	ADD_CALLBACK_FUNCTION(Alexei, draw2);
	ADD_CALLBACK_FUNCTION(Alexei, callbackActionRestaurantOrSalon);
	ADD_CALLBACK_FUNCTION(Alexei, function13);
	ADD_CALLBACK_FUNCTION(Alexei, function14);
	ADD_CALLBACK_FUNCTION(Alexei, function15);
	ADD_CALLBACK_FUNCTION(Alexei, function16);
	ADD_CALLBACK_FUNCTION(Alexei, chapter1);
	ADD_CALLBACK_FUNCTION(Alexei, chapter1Handler);
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
	ADD_CALLBACK_FUNCTION(Alexei, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Alexei, function30);
	ADD_CALLBACK_FUNCTION(Alexei, function31);
	ADD_CALLBACK_FUNCTION(Alexei, chapter3);
	ADD_CALLBACK_FUNCTION(Alexei, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Alexei, function34);
	ADD_CALLBACK_FUNCTION(Alexei, function35);
	ADD_CALLBACK_FUNCTION(Alexei, function36);
	ADD_CALLBACK_FUNCTION(Alexei, chapter4);
	ADD_CALLBACK_FUNCTION(Alexei, chapter4Handler);
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

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Alexei, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Alexei, playSound, 2)
	Entity::playSound(savepoint);
}

/**
 * Updates parameter 2 using ticks value
 *
 * @param param1 The number of ticks to add
 */
IMPLEMENT_FUNCTION_I(Alexei, updateFromTicks, 3)
	Entity::updateFromTicks(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Alexei, draw, 4)
	Entity::draw(savepoint);
}

/**
 * Updates the position
 *
 * @param seq1   The sequence to draw
 * @param param4 The car
 * @param param5 The entity position
 */
IMPLEMENT_FUNCTION_SII(Alexei, updatePosition, 5)
	Entity::updatePosition(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Alexei, enterExitCompartment, 6)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Process callback action when the entity direction is not kDirectionRight
 */
IMPLEMENT_FUNCTION(Alexei, callbackActionOnDirection, 7)
	Entity::callbackActionOnDirection(savepoint);
}

/**
 * Call a savepoint (or draw sequence in default case)
 *
 * @param seq1   The sequence to draw in the default case
 * @param param4 The entity
 * @param param5 The action
 * @param seq1   The sequence name for the savepoint
 */
IMPLEMENT_FUNCTION_SIIS(Alexei, callSavepoint, 8)
	Entity::callSavepoint(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Alexei, savegame, 9)
	Entity::savegame(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Alexei, updateEntity, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionExcuseMeCath:
		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 18) || getEntities()->isPlayerPosition(kCarRedSleeping, 18)) {
			getSound()->excuseMe(kEntityAlexei);
		} else {
			if (getEvent(kEventAlexeiSalonVassili) || (getEvent(kEventTatianaAskMatchSpeakRussian) && getInventory()->hasItem(kItemPassengerList))) {
				getSound()->playSound(kEntityPlayer, random(2) ? "CAT1012" : "CAT1012A");
			} else {
				getSound()->excuseMeCath();
			}
		}
		// Stop execution here
		return;

	case kActionDefault:
		getData()->inventoryItem = kItemNone;
		break;
	}

	Entity::updateEntity(savepoint, true);
}

/**
 * Draws the entity along with another one
 *
 * @param seq1   The sequence to draw
 * @param seq2   The sequence to draw for the second entity
 * @param param7 The EntityIndex of the second entity
 */
IMPLEMENT_FUNCTION_NOSETUP(Alexei, draw2, 11)
	Entity::draw2(savepoint);
}

/**
 * Process callback action when somebody is standing in the restaurant or salon.
 */
IMPLEMENT_FUNCTION(Alexei, callbackActionRestaurantOrSalon, 12)
	Entity::callbackActionRestaurantOrSalon(savepoint);
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
			getData()->posture = kPostureStanding;
			getSavePoints()->push(kEntityAlexei, kEntityMertens, kAction302614416);
			getEntities()->drawSequenceLeft(kEntityAlexei, "602DB");
			getEntities()->enterCompartment(kEntityAlexei, kObjectCompartment2, true);
		}
		break;

	case kAction135664192:
		getObjects()->update(kObjectCompartment2, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getEntities()->exitCompartment(kEntityAlexei, kObjectCompartment2, true);

		CALLBACK_ACTION();
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function15, 15)
	error("Alexei: callback function 15 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - Time
//  - Sequence name
IMPLEMENT_FUNCTION_IS(Alexei, function16, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param7 && params->param1 < (int)getState()->time && !params->param8) {
			params->param8 = 1;

			getObjects()->update(kObjectCompartment2, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectHandleInsideBathroom, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

			CALLBACK_ACTION();
			break;
		}

		if (params->param5) {
			UPDATE_PARAM(CURRENT_PARAMS(1, 1), getState()->timeTicks, 75);

			params->param5 = 0;
			params->param6 = 1;

			getObjects()->update(kObjectCompartment2, kEntityAlexei, kLocation1, kCursorNormal, kCursorNormal);
			getObjects()->update(kObjectHandleInsideBathroom, kEntityAlexei, kLocation1, kCursorNormal, kCursorNormal);
		}

		CURRENT_PARAMS(1, 1) = 0;
		break;

	case kActionKnock:
	case kActionOpenDoor:
		getObjects()->update(kObjectCompartment2, kEntityAlexei, kLocation1, kCursorNormal, kCursorNormal);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityAlexei, kLocation1, kCursorNormal, kCursorNormal);

		if (params->param5) {
			if (savepoint.param.intValue == 18) {
				setCallback(4);
				call(new ENTITY_SETUP_SIIS(Alexei, setup_playSound), getSound()->justAMinuteCath());
				break;
			}

			if (getInventory()->hasItem(kItemPassengerList)) {
				setCallback(5);
				call(new ENTITY_SETUP_SIIS(Alexei, setup_playSound), random(2) ? getSound()->wrongDoorCath() : "CAT1503");
			} else {
				setCallback(6);
				call(new ENTITY_SETUP_SIIS(Alexei, setup_playSound), getSound()->wrongDoorCath());
			}
		} else {
			setCallback(savepoint.action == kActionKnock ? 1 : 2);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_playSound), savepoint.action == kActionKnock ? "LIB012" : "LIB013");
		}
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAlexei, (char*)&params->seq);
		getObjects()->update(kObjectCompartment2, kEntityAlexei, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityAlexei, kLocation1, kCursorHandKnock, kCursorHand);
		break;

	case kActionDrawScene:
		if (params->param6 || params->param5) {
			getObjects()->update(kObjectCompartment2, kEntityAlexei, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectHandleInsideBathroom, kEntityAlexei, kLocation1, kCursorHandKnock, kCursorHand);

			params->param5 = 0;
			params->param6 = 0;
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_playSound), "ALX1134A");
			break;

		case 3:
			getObjects()->update(kObjectCompartment2, kEntityAlexei, kLocation1, kCursorTalk, kCursorNormal);
			getObjects()->update(kObjectHandleInsideBathroom, kEntityAlexei, kLocation1, kCursorTalk, kCursorNormal);
			params->param5 = 1;
			break;

		case 4:
		case 5:
		case 6:
			params->param5 = 0;
			params->param6 = 1;
			break;

		case 7:
			setCallback(8);
			call(new ENTITY_SETUP(Alexei, setup_updateFromTicks), 300);
			break;

		case 8:
			setCallback(9);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_enterExitCompartment), "602Gb", kObjectCompartment2);
			break;

		case 9:
			getData()->posture = kPostureStanding;
			getSavePoints()->push(kEntityAlexei, kEntityMertens, kAction156567128);
			getEntities()->drawSequenceLeft(kEntityAlexei, "602Hb");
			getEntities()->enterCompartment(kEntityAlexei, kObjectCompartment2, true);
			break;

		case 10:
			getEntities()->exitCompartment(kEntityAlexei, kObjectCompartment2, true);

			getData()->posture = kPostureSitting;
			getData()->entityPosition = kPosition_7500;

			getEntities()->drawSequenceLeft(kEntityAlexei, (char *)&params->seq);
			getObjects()->update(kObjectCompartment2, kEntityAlexei, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectHandleInsideBathroom, kEntityAlexei, kLocation1, kCursorHandKnock, kCursorHand);

			params->param7 = 0;
			break;
		}
		break;

	case kAction124697504:
		setCallback(10);
		call(new ENTITY_SETUP_SIIS(Alexei, setup_enterExitCompartment), "602Ib", kObjectCompartment2);
		break;

	case kAction221617184:
		params->param7 = 1;
		getSavePoints()->push(kEntityAlexei, kEntityMertens, kAction100906246);

		setCallback(7);
		call(new ENTITY_SETUP_SIIS(Alexei, setup_playSound), "CON1024");
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter1, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler)
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment2, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_3969;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter1Handler, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime1089000 && getEntities()->isSomebodyStandingInRestaurantOrSalon()) {
			params->param2 = 0;

			getData()->posture = kPostureStanding;
			getData()->inventoryItem = kItemNone;

			getEntities()->updatePosition(kEntityAlexei, kCarRestaurant, 63, true);
			getInventory()->setLocationAndProcess(kItem17, kLocation1);

			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_callSavepoint), "005D", kEntityTables1, kActionDrawTablesWithChairs, "005E");
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
		params->param1 = getEntities()->isPlayerPosition(kCarRestaurant, 63);
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
			getSavePoints()->push(kEntityAlexei, kEntityTables1, kActionDrawTablesWithChairs, "005E");

			getData()->entityPosition = kPosition_3650;
			getData()->posture = kPostureStanding;

			getEntities()->clearSequences(kEntityAlexei);
			getInventory()->get(kItem17)->location = kLocation1;
			getScenes()->loadSceneFromPosition(kCarRestaurant, 63);

			setup_function19();
			break;
		}
		break;

	case kAction168046720:
		getData()->inventoryItem = kItemNone;
		break;

	case kAction168627977:
		getData()->inventoryItem = (InventoryItem)LOBYTE(params->param2);
		break;

	case kAction225182640:
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function19, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Alexei, setup_draw), "811DS");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Alexei, setup_updateEntity), kCarGreenSleeping, kPosition_9460);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Alexei, setup_updateEntity), kCarRestaurant, kPosition_850);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Alexei, setup_callbackActionRestaurantOrSalon));
			break;

		case 4:
			getData()->entityPosition = kPosition_1540;
			getData()->posture = kPostureStanding;

			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_draw), "811US");
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_draw), "933");
			break;

		case 6:
			getEntities()->updatePosition(kEntityAlexei, kCarRestaurant, 63, true);
			getScenes()->loadSceneFromItemPosition(kItem17);
			getSavePoints()->push(kEntityAlexei, kEntityTables1, kAction136455232);

			setCallback(7);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_callSavepoint), "005F", kObjectCompartmentC, kActionDrawTablesWithChairs, "005G");
			break;

		case 7:
			getEntities()->updatePosition(kEntityAlexei, kCarRestaurant, 63);
			getSavePoints()->push(kEntityAlexei, kEntityServers1, kAction302996448);

			setCallback(8);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_draw), "934");
			break;

		case 8:
			setCallback(9);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_draw), "811DS");
			break;

		case 9:
			setCallback(10);
			call(new ENTITY_SETUP(Alexei, setup_function13));
			break;

		case 10:
			if (getEntities()->isPlayerPosition(kCarGreenSleeping, 61))
				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);

			setCallback(11);
			call(new ENTITY_SETUP_ISII(Alexei, setup_function16), kTime1098000, "411");
			break;

		case 11:
			setup_function20();
			break;
		}
		break;
	}
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
			call(new ENTITY_SETUP(Alexei, setup_updateEntity), kCarRestaurant, kPosition_850);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Alexei, setup_callbackActionRestaurantOrSalon));
			break;

		case 3:
			getData()->entityPosition = kPosition_1540;
			getData()->posture = kPostureStanding;

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_updatePosition), "103A", kCarRestaurant, 52);
			break;

		case 4:
			getData()->posture = kPostureSitting;
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
	switch (savepoint.action) {
	default:
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;
		setCallback(1);
		call(new ENTITY_SETUP(Alexei, setup_savegame), kSavegameType2, kEventAlexeiSalonCath);
		break;

	case kActionDefault:
		if (getEvent(kEventAlexeiSalonVassili))
			getData()->inventoryItem = kItemInvalid;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventAlexeiSalonCath);
			getData()->car = kCarRestaurant;
			getData()->entityPosition = kPosition_9460;
			getEntities()->clearSequences(kEntityAlexei);
			getScenes()->loadSceneFromPosition(kCarRestaurant, 55);
			setup_function25();
			break;

		case 2:
			setup_function25();
			break;
		}
		break;

	case kAction135854208:
		getData()->inventoryItem = kItemNone;
		setCallback(2);
		call(new ENTITY_SETUP_SIIS(Alexei, setup_draw), "103G");
		break;
	}
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
		getData()->posture = kPostureSitting;

		getObjects()->update(kObjectCompartment2, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityPlayer, kLocation1, kCursorKeepValue, kCursorKeepValue);

		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 61))
			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 66);

		getEntities()->clearSequences(kEntityAlexei);
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, function27, 27)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObject10, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

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
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAlexei);

		getObjects()->update(kObjectCompartment2, kEntityAlexei, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityAlexei, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_7500;
		getData()->posture = kPostureSitting;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter2Handler, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_ISII(Alexei, setup_function16), kTime1791000, "411");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Alexei, setup_function14));
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Alexei, setup_updateEntity), kCarRestaurant, kPosition_850);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Alexei, setup_callbackActionRestaurantOrSalon));
			break;

		case 4:
			getData()->entityPosition = kPosition_1540;
			getData()->posture = kPostureStanding;

			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_draw), "811US");
			break;

		case 5:
			getEntities()->updatePosition(kEntityAlexei, kCarRestaurant, 63, true);

			setCallback(6);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_callSavepoint), "018B", kEntityTables1, kAction136455232, "BOGUS");
			break;

		case 6:
			getEntities()->updatePosition(kEntityAlexei, kCarRestaurant, 63);
			getSavePoints()->push(kEntityAlexei, kEntityTatiana, kAction290869168);
			setup_function30();
			break;
		}
		break;
	}
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
		if (getEntities()->isInRestaurant(kEntityPlayer))
			getEntities()->updateFrame(kEntityAlexei);

		setCallback(1);
		call(new ENTITY_SETUP(Alexei, setup_callbackActionOnDirection));
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
			call(new ENTITY_SETUP_ISII(Alexei, setup_function16), kTimeEnd, "411");
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
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAlexei);

		getObjects()->update(kObjectCompartment2, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter3Handler, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function34();
		break;

	case kAction122288808:
		getData()->entityPosition = kPosition_9270;
		getData()->posture = kPostureStanding;
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
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAlexei);

		getObjects()->update(kObjectCompartment2, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_7500;
		getData()->posture = kPostureSitting;
		getData()->car = kCarGreenSleeping;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter4Handler, 38)
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
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Alexei, setup_updateEntity), kCarGreenSleeping, kPosition_7500);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceRight(kEntityAlexei, "602Eb");
			getEntities()->enterCompartment(kEntityAlexei, kObjectCompartment2);

			getData()->posture = kPostureSitting;

			if (getEntities()->isSitting(kEntityPlayer, kCarGreenSleeping, kPosition_7500)) {
				getAction()->playAnimation(isDay() ? kEventCathTurningDay : kEventCathTurningNight);
				getSound()->playSound(kEntityPlayer, "BUMP");
				getScenes()->loadSceneFromObject(kObjectCompartment2);
			}

			setCallback(2);
			call(new ENTITY_SETUP(Alexei, setup_callbackActionOnDirection));
			break;

		case 2:
			getEntities()->exitCompartment(kEntityAlexei, kObjectCompartment2);
			getData()->entityPosition = kPosition_7500;
			getData()->posture = kPostureSitting;
			getEntities()->clearSequences(kEntityAlexei);

			setup_function41();
			break;
		}
		break;
	}
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
			call(new ENTITY_SETUP(Alexei, setup_updateEntity), kCarRestaurant, kPosition_850);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Alexei, setup_updatePosition), "103A", kCarRestaurant, 52);
			break;

		case 3:
			getData()->posture = kPostureSitting;
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
		getData()->posture = kPostureStanding;
		getData()->car = kCarNone;

		getObjects()->update(kObjectCompartment2, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter5, 48)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityAlexei);
}

} // End of namespace LastExpress
