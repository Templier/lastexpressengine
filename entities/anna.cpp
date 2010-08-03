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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "lastexpress/entities/anna.h"

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

Anna::Anna(LastExpressEngine *engine) : Entity(engine, kEntityAnna) {
	ADD_CALLBACK_FUNCTION(Anna, reset);
	ADD_CALLBACK_FUNCTION(Anna, draw);
	ADD_CALLBACK_FUNCTION(Anna, updatePosition);
	ADD_CALLBACK_FUNCTION(Anna, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Anna, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Anna, callSavepoint);
	ADD_CALLBACK_FUNCTION(Anna, playSound);
	ADD_CALLBACK_FUNCTION(Anna, callbackActionOnSomebodyStandingInRestaurantOrSalon);
	ADD_CALLBACK_FUNCTION(Anna, savegame);
	ADD_CALLBACK_FUNCTION(Anna, updateEntity);
	ADD_CALLBACK_FUNCTION(Anna, updateFromTime);
	ADD_CALLBACK_FUNCTION(Anna, function12);
	ADD_CALLBACK_FUNCTION(Anna, draw2);
	ADD_CALLBACK_FUNCTION(Anna, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Anna, function15);
	ADD_CALLBACK_FUNCTION(Anna, chapter1);
	ADD_CALLBACK_FUNCTION(Anna, function17);
	ADD_CALLBACK_FUNCTION(Anna, function18);
	ADD_CALLBACK_FUNCTION(Anna, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Anna, function20);
	ADD_CALLBACK_FUNCTION(Anna, function21);
	ADD_CALLBACK_FUNCTION(Anna, function22);
	ADD_CALLBACK_FUNCTION(Anna, function23);
	ADD_CALLBACK_FUNCTION(Anna, function24);
	ADD_CALLBACK_FUNCTION(Anna, function25);
	ADD_CALLBACK_FUNCTION(Anna, function26);
	ADD_CALLBACK_FUNCTION(Anna, function27);
	ADD_CALLBACK_FUNCTION(Anna, function28);
	ADD_CALLBACK_FUNCTION(Anna, function29);
	ADD_CALLBACK_FUNCTION(Anna, function30);
	ADD_CALLBACK_FUNCTION(Anna, function31);
	ADD_CALLBACK_FUNCTION(Anna, function32);
	ADD_CALLBACK_FUNCTION(Anna, function33);
	ADD_CALLBACK_FUNCTION(Anna, function34);
	ADD_CALLBACK_FUNCTION(Anna, function35);
	ADD_CALLBACK_FUNCTION(Anna, function36);
	ADD_CALLBACK_FUNCTION(Anna, function37);
	ADD_CALLBACK_FUNCTION(Anna, function38);
	ADD_CALLBACK_FUNCTION(Anna, function39);
	ADD_CALLBACK_FUNCTION(Anna, function40);
	ADD_CALLBACK_FUNCTION(Anna, function41);
	ADD_CALLBACK_FUNCTION(Anna, chapter2);
	ADD_CALLBACK_FUNCTION(Anna, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Anna, chapter3);
	ADD_CALLBACK_FUNCTION(Anna, function45);
	ADD_CALLBACK_FUNCTION(Anna, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Anna, function47);
	ADD_CALLBACK_FUNCTION(Anna, function48);
	ADD_CALLBACK_FUNCTION(Anna, leaveTableWithAugust);
	ADD_CALLBACK_FUNCTION(Anna, function50);
	ADD_CALLBACK_FUNCTION(Anna, function51);
	ADD_CALLBACK_FUNCTION(Anna, function52);
	ADD_CALLBACK_FUNCTION(Anna, function53);
	ADD_CALLBACK_FUNCTION(Anna, function54);
	ADD_CALLBACK_FUNCTION(Anna, function55);
	ADD_CALLBACK_FUNCTION(Anna, function56);
	ADD_CALLBACK_FUNCTION(Anna, function57);
	ADD_CALLBACK_FUNCTION(Anna, function58);
	ADD_CALLBACK_FUNCTION(Anna, function59);
	ADD_CALLBACK_FUNCTION(Anna, function60);
	ADD_CALLBACK_FUNCTION(Anna, function61);
	ADD_CALLBACK_FUNCTION(Anna, function62);
	ADD_CALLBACK_FUNCTION(Anna, function63);
	ADD_CALLBACK_FUNCTION(Anna, bagage);
	ADD_CALLBACK_FUNCTION(Anna, function65);
	ADD_CALLBACK_FUNCTION(Anna, chapter4);
	ADD_CALLBACK_FUNCTION(Anna, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Anna, function68);
	ADD_CALLBACK_FUNCTION(Anna, function69);
	ADD_CALLBACK_FUNCTION(Anna, function70);
	ADD_CALLBACK_FUNCTION(Anna, function71);
	ADD_CALLBACK_FUNCTION(Anna, function72);
	ADD_CALLBACK_FUNCTION(Anna, function73);
	ADD_CALLBACK_FUNCTION(Anna, chapter5);
	ADD_CALLBACK_FUNCTION(Anna, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Anna, function76);
	ADD_CALLBACK_FUNCTION(Anna, function77);
	ADD_CALLBACK_FUNCTION(Anna, function78);
	ADD_CALLBACK_FUNCTION(Anna, function79);
	ADD_CALLBACK_FUNCTION(Anna, function80);
	ADD_CALLBACK_FUNCTION(Anna, function81);
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Anna, reset, 1)
	Entity::reset(savepoint, true, true);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Anna, draw, 2)
	Entity::draw(savepoint);
}

/**
 * Updates the position
 *
 * @param seq1   The sequence to draw
 * @param param4 The car
 * @param param5 The entity position
 */
IMPLEMENT_FUNCTION_SII(Anna, updatePosition, 3)
	Entity::updatePosition(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Anna, enterExitCompartment, 4)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Process callback action when the entity direction is not kDirectionRight
 */
IMPLEMENT_FUNCTION(Anna, callbackActionOnDirection, 5)
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
IMPLEMENT_FUNCTION_SIIS(Anna, callSavepoint, 6)
	Entity::callSavepoint(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Anna, playSound, 7)
	Entity::playSound(savepoint);
}

/**
 * Process callback action when somebody is standing in the restaurant or salon.
 */
IMPLEMENT_FUNCTION(Anna, callbackActionOnSomebodyStandingInRestaurantOrSalon, 8)
	Entity::callbackActionOnSomebodyStandingInRestaurantOrSalon(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Anna, savegame, 9)
	Entity::savegame(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Anna, updateEntity, 10)
	if (savepoint.action == kActionExcuseMeCath) {
		if (getEvent(kEventAugustPresentAnna) || getEvent(kEventAugustPresentAnnaFirstIntroduction) || getProgress().chapter >= kChapter2)
			getSound()->playSound(kEntityPlayer, "CAT1001");
		else
			getSound()->excuseMeCath();

		return;
	}

	Entity::updateEntity(savepoint, true);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_I(Anna, updateFromTime, 11)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION(Anna, function12, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param2 && ENTITY_PARAM(0, 1))
			params->param2 = 1;

		if (params->param6) {
			if (!params->param7)
				params->param7 = getState()->timeTicks + 75;

			if (params->param7 < (int)getState()->timeTicks) {
				getSavePoints()->push(kEntityAnna, kEntityAnna, kAction2);

				params->param6 = 0;
				params->param7 = 0;
			}
		}

		if (params->param4) {
			UPDATE_PARAM(params->param8, getState()->timeTicks, 75);

			params->param4 = 0;
			params->param5 = 1;

			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorNormal, kCursorHand);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorNormal, kCursorHand);

			--params->param1;

			getSavePoints()->push(kEntityAnna, kEntityAnna, kAction2);
		}

		params->param8 = 0;
		break;

	case kAction2:
		if (params->param2) {
			CALLBACK_ACTION();
			break;
		}

		++params->param1;

		switch (params->param1) {
		default:
			break;

		case 1:
			getSound()->playSound(kEntityAnna, "ANN2135A");
			break;

		case 2:
			getSound()->playSound(kEntityAnna, "ANN2135B");
			break;

		case 3:
			getSound()->playSound(kEntityAnna, "ANN2135C");
			break;

		case 4:
			getSound()->playSound(kEntityAnna, "ANN2135C");
			break;

		case 5:
			getSound()->playSound(kEntityAnna, "ANN2135L");
			break;

		case 6:
			getSound()->playSound(kEntityAnna, "ANN2135K");
			break;

		case 7:
			getSound()->playSound(kEntityAnna, "ANN2135H");
			break;

		case 8:
			getSound()->playSound(kEntityAnna, "ANN2135K");
			break;

		case 9:
			getSound()->playSound(kEntityAnna, "ANN2135I");
			break;

		case 10:
			getSound()->playSound(kEntityAnna, "ANN2135J");
			break;

		case 11:
			getSound()->playSound(kEntityAnna, "ANN2135M");
			break;

		case 12:
			getSound()->playSound(kEntityAnna, "ANN2135L");
			break;

		case 13:
			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);

			CALLBACK_ACTION();
			break;
		}
		break;

	case kActionKnock:
		if (params->param4) {
			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorNormal, kCursorHand);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorNormal, kCursorHand);

			if (savepoint.param.intValue == 53) {
				getSound()->playSound(kEntityPlayer, getSound()->justAMinuteCath());
			} else if (getInventory()->hasItem(kItemPassengerList)) {
				if (random(2)) {
					getSound()->playSound(kEntityPlayer, getSound()->wrongDoorCath());
				} else {
					getSound()->playSound(kEntityPlayer, random(2) ? "CAT1506A" : "CAT1506");
				}
			} else {
				getSound()->playSound(kEntityPlayer, getSound()->wrongDoorCath());
			}

			params->param4 = 0;
			params->param5 = 0;
		} else {
			getSound()->removeFromQueue(kEntityAnna);

			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorNormal, kCursorNormal);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "LIB012");
		}
		break;

	case kActionOpenDoor:
		getSound()->removeFromQueue(kEntityAnna);
		setCallback(3);
		call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "LIB013");
		break;

	case kActionDefault:
		params->param1 = 1;
		getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectOutsideAnnaCompartment, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		if (getEntities()->isPlayerPosition(kCarRedSleeping, 49))
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 49);

		getEntities()->drawSequenceLeft(kEntityAnna, "418C");

		if (getSound()->isBuffered(kEntityAnna))
			getSound()->processEntry(kEntityAnna);

		getSound()->playSound(kEntityAnna, "ANN2135A");
		break;

	case kActionDrawScene:
		if (params->param5 || params->param4) {
			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);
			params->param4 = 0;
			params->param5 = 0;
		}

		if (getEntities()->isPlayerPosition(kCarRedSleeping, 60)) {
			++params->param3;
			if (params->param3 == 2) {
				setCallback(2);
				call(new ENTITY_SETUP_SIIS(Anna, setup_draw), "418B");
			}
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "Ann1016");
			break;

		case 2:
			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorTalk, kCursorHand);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorTalk, kCursorHand);
			params->param4 = 1;
			break;

		case 3:
			if (!getSound()->isBuffered(kEntityMax)) {
				setCallback(4);
				call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "MAX1120");
				break;
			}
			// Fallback to next case

		case 4:
			--params->param1;
			params->param6 = 1;
			break;

		case 5:
			getEntities()->drawSequenceLeft(kEntityAnna, "418A");
			break;
		}
		break;
	}
}

/**
 * Draws the entity along with another one
 *
 * @param seq1   The sequence to draw
 * @param seq2   The sequence to draw for the second entity
 * @param param7 The EntityIndex of the second entity
 */
IMPLEMENT_FUNCTION_SSI(Anna, draw2, 13)
	Entity::draw2(savepoint);
}

/**
 * Updates parameter 2 using ticks value
 *
 * @param param1 The number of ticks to add
 */
IMPLEMENT_FUNCTION_I(Anna, updateFromTicks, 14)
	Entity::updateFromTicks(savepoint);
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - time
//  - sequence
IMPLEMENT_FUNCTION_IS(Anna, function15, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1 < (int32)getState()->time && !params->param7) {
			params->param7 = 1;

			getObjects()->update(kObjectCompartmentF, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject53, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

			CALLBACK_ACTION();
			break;
		}

		if (params->param5) {
			UPDATE_PARAM(params->param8, getState()->timeTicks, 75);

			params->param5 = 0;
			params->param6 = 1;

			CursorStyle cursor = getEntities()->isSitting(kEntityMax, kCarRedSleeping, kPosition_4070) ? kCursorHand : kCursorNormal;

			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorNormal, cursor);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorNormal, cursor);
		}

		params->param8 = 0;
		break;

	case kActionOpenDoor:
		if (getEntities()->isSitting(kEntityMax, kCarRedSleeping, kPosition_4070)) {
			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorNormal, kCursorNormal);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "LIB013");
			break;
		}
		// Fallback to next action

	case kActionKnock:
		if (params->param5) {
			CursorStyle cursor = getEntities()->isSitting(kEntityMax, kCarRedSleeping, kPosition_4070) ? kCursorHand : kCursorNormal;

			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorNormal, cursor);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorNormal, cursor);

			if (savepoint.param.intValue == kObject53) {
				setCallback(6);
				call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), getSound()->justAMinuteCath());
			} else {
				if (getInventory()->hasItem(kItemPassengerList)) {
					setCallback(7);
					call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), random(2) ? getSound()->wrongDoorCath() : (random(2) ? "CAT1506" : "CAT1506A"));
				} else {
					setCallback(8);
					call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), getSound()->wrongDoorCath());
				}
			}
		} else {
			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorNormal, kCursorNormal);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(savepoint.action == kActionKnock ? 3 : 4);
			call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), savepoint.action == kActionKnock ? "LIB012" : "LIB013");
		}
		break;


	case kActionDefault:
		getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);
		getEntities()->drawSequenceLeft(kEntityAnna, (char *)&params->seq);
		break;

	case kActionDrawScene:
		if (params->param6 || params->param5) {
			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);

			params->param5 = 0;
			params->param6 = 0;
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (!getSound()->isBuffered(kEntityMax)) {
				setCallback(2);
				call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "MAX1120");
				break;
			}
			// Fallback to next case

		case 2:
			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorHandKnock, kCursorHand);
			break;

		case 3:
		case 4:
			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "ANN1016");
			break;

		case 5:
			getObjects()->update(kObjectCompartmentF, kEntityAnna, kLocation1, kCursorTalk, kCursorNormal);
			getObjects()->update(kObject53, kEntityAnna, kLocation1, kCursorTalk, kCursorNormal);
			params->param5 = 1;
			break;

		case 6:
		case 7:
		case 8:
			params->param5 = 0;
			params->param6 = 1;
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, chapter1, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityAnna, kAction291662081, 0);
		getSavePoints()->addData(kEntityAnna, kAction238936000, 1);

		getObjects()->update(kObjectCompartmentF, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject53, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectOutsideAnnaCompartment, kEntityPlayer, kLocation1, kCursorKeepValue, kCursorKeepValue);

		getData()->entityPosition = kPosition_8200;
		getData()->posture = kPostureSitting;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		break;
	}
}

IMPLEMENT_FUNCTION_II(Anna, function17, 17)
	error("Anna: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION_I(Anna, function18, 18)
	error("Anna: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter1Handler, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Anna, setup_enterExitCompartment), "618Ca", kObjectCompartment1);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->entityPosition = kPosition_8514;
			getData()->posture = kPostureStanding;

			setCallback(2);
			call(new ENTITY_SETUP(Anna, setup_updateEntity), kCarRedSleeping, kPosition_4070);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Anna, setup_enterExitCompartment), "618Af", kObjectCompartmentF);
			break;

		case 3:
			getEntities()->clearSequences(kEntityAnna);
			getData()->entityPosition = kPosition_4070;
			getData()->posture = kPostureSitting;

			setup_function20();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_ISII(Anna, setup_function15), kTime1093500, "NONE");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Anna, setup_enterExitCompartment), "618Bf", kObjectCompartmentF);
			break;

		case 2:
			getData()->posture = kPostureStanding;
			getSavePoints()->push(kEntityAnna, kEntityMax, kAction71277948);
			setup_function21();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function21, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function17), kCarRestaurant, kPosition_850);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Anna, setup_callbackActionOnSomebodyStandingInRestaurantOrSalon));
			break;

		case 2:
			getData()->entityPosition = kPosition_1540;
			getData()->posture = kPostureStanding;

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Anna, setup_draw), "801US");
			break;

		case 3:
			getEntities()->drawSequenceRight(kEntityAnna, "001B");
			if (getEntities()->isInSalon(kEntityPlayer))
				getEntities()->updateFrame(kEntityAnna);

			setCallback(4);
			call(new ENTITY_SETUP(Anna, setup_callbackActionOnDirection));
			break;

		case 4:
			setup_function22();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function22, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAnna, "001A");
		getSavePoints()->push(kEntityAnna, kEntityPascale, kAction223262556);
		break;

	case kAction157370960:
		getData()->posture = kPostureSitting;
		setup_function23();
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAnna, "001D");
		getSavePoints()->push(kEntityAnna, kEntityServers0, kAction270410280);
		getSavePoints()->push(kEntityAnna, kEntityTables0, kAction136455232);

		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function18), false);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceLeft(kEntityAnna, "001E");
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "ANN1048");
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Anna, setup_draw), "001F");
			break;

		case 3:
			getSavePoints()->push(kEntityAnna, kEntityServers0, kAction203859488);
			setup_function24();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function24, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAnna, "001G");

		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function18));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceLeft(kEntityAnna, "001H");
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "ANN1049");
			break;

		case 2:
			getSavePoints()->push(kEntityAnna, kEntityServers0, kAction136702400);
			setup_function25();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function25, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAnna, "001J");
		getProgress().field_28 = 1;

		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function18), 0);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 2:
			call(new ENTITY_SETUP(Anna, setup_callbackActionOnSomebodyStandingInRestaurantOrSalon));
			break;

		case 3:
			setup_function26();
			break;
		}
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityAnna, "BLANK");
		break;

	case kAction201437056:
		getEntities()->drawSequenceLeft(kEntityAnna, "001J");
		setCallback(2);
		call(new ENTITY_SETUP(Anna, setup_function18), kTime1138500);
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function26, 26)
	error("Anna: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function27, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAnna, kEntityMax, kAction101687594);
		setCallback(1);
		call(new ENTITY_SETUP_ISII(Anna, setup_function15), kTime1156500, "NONE");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			if (getProgress().field_14 == 29) {
				params->param1 = getState()->time + 900;
				setCallback(2);
				call(new ENTITY_SETUP_ISII(Anna, setup_function15), params->param1, "NONE");
			} else {
				setCallback(3);
				call(new ENTITY_SETUP_SIIS(Anna, setup_enterExitCompartment), "618Bf", kObjectCompartmentF);
			}
			break;

		case 3:
			getData()->posture = kPostureStanding;
			getSavePoints()->push(kEntityAnna, kEntityMax, kAction71277948);
			setup_function28();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function28, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function17), kCarRestaurant, kPosition_850);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Anna, setup_callbackActionOnSomebodyStandingInRestaurantOrSalon));
			break;

		case 2:
			getData()->posture = kPostureStanding;
			getData()->entityPosition = kPosition_1540;
			getScenes()->loadSceneFromItemPosition(kItem3);

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Anna, setup_updatePosition), "104A", kCarRestaurant, 56);
			break;

		case 3:
			getData()->posture = kPostureSitting;
			setup_function29();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function29, 29)
	error("Anna: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function30, 30)
	error("Anna: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function31, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_callbackActionOnSomebodyStandingInRestaurantOrSalon));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->posture = kPostureStanding;
			getSound()->playSound(kEntityAnna, "AUG1005");

			setCallback(2);
			call(new ENTITY_SETUP(Anna, setup_updateFromTicks), 150);
			break;

		case 2:
			getEntities()->updatePosition(kEntityAnna, kCarRestaurant, 56, true);

			setCallback(3);
			call(new ENTITY_SETUP_SSII(Anna, setup_draw2), "106C1", "106C2", kEntityAugust);
			break;

		case 3:
			getEntities()->updatePosition(kEntityAnna, kCarRestaurant, 56);
			getInventory()->setLocationAndProcess(kItem3, kLocation1);
			getSavePoints()->push(kEntityAnna, kEntityAugust, kAction159332865);

			setup_function32();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function32, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function17), kCarRedSleeping, kPosition_4070);
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Anna, setup_enterExitCompartment), "618Af", kObjectCompartmentF);
			break;

		case 2:
			getEntities()->clearSequences(kEntityAnna);

			getData()->entityPosition = kPosition_4070;
			getData()->posture = kPostureSitting;

			setup_function33();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function33, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAnna, kEntityMax, kAction101687594);

		params->param1 = getState()->time + 4500;
		setCallback(1);
		call(new ENTITY_SETUP_ISII(Anna, setup_function15), params->param1, "NONE");
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getObjects()->updateLocation2(kObjectCompartmentF, kLocation1);
			setup_function34();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function34, 34)
	error("Anna: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function35, 35)
	error("Anna: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function36, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentF, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_updateEntity), kCarRedSleeping, kPosition_8200);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentA, kEntityPlayer, kLocation1, kCursorKeepValue, kCursorKeepValue);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Anna, setup_enterExitCompartment), "608Aa", kObjectCompartmentA);
			break;

		case 2:
			getObjects()->update(kObjectCompartmentA, kEntityPlayer, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getData()->posture = kPostureSitting;
			getEntities()->clearSequences(kEntityAnna);

			setup_function37();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function37, 37)
  switch (savepoint.action) {
  default:
	break;

  case kActionDefault:
	getData()->entityPosition = kPosition_8200;
	getData()->posture = kPostureStanding;
	getData()->car = kCarRedSleeping;
	break;

  case kAction191477936:
	setup_function38();
	break;
  }
}

IMPLEMENT_FUNCTION(Anna, function38, 38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_7500;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "ANN1010");
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getSound()->playSound(kEntityPlayer, "MUS043");
			setup_function40();
		}
		break;
	}
}

IMPLEMENT_FUNCTION_II(Anna, function39, 39)
	error("Anna: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function40, 40)
	error("Anna: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function41, 41)
	error("Anna: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter2, 42)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAnna);

		getData()->entityPosition = kPosition_4070;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Anna, chapter2Handler, 43)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectOutsideAnnaCompartment, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function12));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_ISII(Anna, setup_function15), kTime1786500, "418C");
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Anna, setup_function12));
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP_ISII(Anna, setup_function15), kTime1818000, "418C");
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP(Anna, setup_function12));
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP_ISII(Anna, setup_function15), kTimeEnd, "418C");
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, chapter3, 44)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAnna);

		getData()->entityPosition = kPosition_4070;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothes3;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentF, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectOutsideAnnaCompartment, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject53, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION_I(Anna, function45, 45)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->posture = kPostureStanding;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Anna, setup_enterExitCompartment), "625Bf", kObjectCompartmentF);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityAnna, kEntityCoudert, params->param1 ? kAction185737168 : kAction185671840);
			getSound()->playSound(kEntityAnna, "Ann3147");
			getEntities()->drawSequenceLeft(kEntityAnna, "625EF");
			getEntities()->enterCompartment(kEntityAnna, kObjectCompartmentF, true);
			break;

		case 2:
			getEntities()->exitCompartment(kEntityAnna, kObjectCompartmentF, true);
			CALLBACK_ACTION();
			break;
		}
		break;

	case kAction157894320:
		setCallback(2);
		call(new ENTITY_SETUP(Anna, setup_updateFromTime), 75);
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, chapter3Handler, 46)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (getEntities()->isPlayerPosition(kCarRedSleeping, 60))
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 49);

		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function12));
		break;

	case kActionCallback:
		if (getCallback() == 1 || getCallback() == 2) {
			if (ENTITY_PARAM(0, 1)) {
				setup_function47();
			} else {
				setCallback(2);
				call(new ENTITY_SETUP_ISII(Anna, setup_function15), getState()->time + 4500, "418C");
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function47, 47)
	error("Anna: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function48, 48)
	error("Anna: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, leaveTableWithAugust, 49)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getSavePoints()->push(kEntityAnna, kEntityTables3, kActionDrawTablesWithChairs, "010M");
		getEntities()->clearSequences(kEntityAugust);

		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityTables3, "026J3");
		getEntities()->drawSequenceRight(kEntityAugust, "026J2");
		getEntities()->drawSequenceRight(kEntityAnna, "026J1");
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function50, 50)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "ann3141");
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Anna, setup_callbackActionOnSomebodyStandingInRestaurantOrSalon));
			break;

		case 2:
			getData()->posture = kPostureStanding;
			setCallback(3);
			call(new ENTITY_SETUP(Anna, setup_leaveTableWithAugust));
			break;

		case 3:
			setup_function51();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function51, 51)
	error("Anna: callback function 51 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function52, 52)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->exitCompartment(kEntityAnna, kObjectCompartmentF);
		getData()->entityPosition = kPosition_4070;
		getData()->posture = kPostureSitting;

		getEntities()->clearSequences(kEntityAnna);

		setup_function53();
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_updateEntity), kCarRedSleeping, kPosition_4070);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->drawSequenceRight(kEntityAnna, "688Af");
			getEntities()->enterCompartment(kEntityAnna, kObjectCompartmentF);
			getData()->posture = kPostureSitting;

			if (getEntities()->isSitting(kEntityPlayer, kCarRedSleeping, kPosition_4070) || getEntities()->isSitting(kEntityPlayer, kCarRedSleeping, kPosition_4455)) {
				getAction()->playAnimation(isDay() ? kEventCathTurningDay : kEventCathTurningNight);
				getSound()->playSound(kEntityPlayer, "BUMP");
				getScenes()->loadSceneFromObject(kObjectCompartmentF);
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function53, 53)
	error("Anna: callback function 53 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function54, 54)
	error("Anna: callback function 54 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function55, 55)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectOutsideAnnaCompartment, kEntityPlayer, kLocation2, kCursorKeepValue, kCursorKeepValue);

		if (getEntities()->isPlayerPosition(kCarRedSleeping, 78))
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 49);

		getObjects()->update(kObjectCompartmentF, kEntityPlayer, kLocation1, kCursorNormal, kCursorNormal);
		getObjects()->update(kObject53, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getInventory()->setLocationAndProcess(kItemKey, kLocation1);

		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function45), true);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentF, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
			setCallback(2);
			call(new ENTITY_SETUP(Anna, setup_updateEntity), kCarRedSleeping, kPosition_9270);
			break;

		case 2:
			setup_function56();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function56, 56)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAnna);
		getData()->entityPosition = kPosition_6000;
		getData()->posture = kPostureSitting;
		getData()->car = kCarKronos;
		break;

	case kAction191668032:
		setup_function57();
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function57, 57)
	error("Anna: callback function 57 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function58, 58)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_savegame), kSavegameType2, kEventAnnaSearchingCompartment);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventAnnaSearchingCompartment);
			getEntities()->clearSequences(kEntityAnna);
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 8);
			getSound()->playSound(kEntityAnna, "lib015");
			getSavePoints()->push(kEntityAnna, kEntityAugust, kAction122288808);
			setup_function59();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function59, 59)
	error("Anna: callback function 59 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function60, 60)
	error("Anna: callback function 60 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function61, 61)
	error("Anna: callback function 61 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function62, 62)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime2259000 && !params->param2) {
			params->param2 = 1;
			getSavePoints()->push(kEntityAnna, kEntityVesna, kAction189299008);
			setup_function63();
		}
		break;

	case kActionDefault:
		getData()->car = kCarBaggage;
		getProgress().field_54 = 1;
		break;

	case kAction235856512:
		params->param1 = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function63, 63)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAnna, kEntityChapters, kAction171843264);
		break;

	// Game over with Anna killed!
	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventAnnaKilled);
			getLogic()->gameOver(kTimeTypeTime, kTime2250000, kSceneGameOverAnnaDied, true);
		}
		break;

	// Anna will get killed...
	case kAction272177921:
		if (getSound()->isBuffered("MUS012"))
			getSound()->processEntry("MUS012");

		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_savegame), kSavegameType2, kEventAnnaKilled);
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, bagage, 64)
	error("Anna: callback function 64 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function65, 65)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_4070;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothes3;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectOutsideAnnaCompartment, kEntityPlayer, kLocation1, kCursorKeepValue, kCursorKeepValue);

		setCallback(1);
		call(new ENTITY_SETUP_ISII(Anna, setup_function15), kTimeEnd, "NONE");
	}
}

IMPLEMENT_FUNCTION(Anna, chapter4, 66)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAnna);

		getData()->entityPosition = kPosition_4070;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothes2;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Anna, chapter4Handler, 67)
	error("Anna: callback function 67 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function68, 68)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param1) {
			setCallback(1);
			call(new ENTITY_SETUP_ISII(Anna, setup_function15), kTime2511900, "NONE");
		}
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentF, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject53, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->car = kCarRedSleeping;
		getData()->entityPosition = kPosition_4070;
		getData()->posture = kPostureSitting;
		break;

	case kAction191001984:
		getObjects()->update(kObjectCompartmentF, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
		setup_function69();
		break;

	case kAction201431954:
		params->param1 = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function69, 69)
	error("Anna: callback function 69 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function70, 70)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function72), kCarRedSleeping, kPosition_4070);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Anna, setup_function71));
			break;

		case 2:
			getData()->posture = kPostureStanding;
			getEntities()->clearSequences(kEntityAnna);
			setup_function73();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function71, 71)
	error("Anna: callback function 71 not implemented!");
}

IMPLEMENT_FUNCTION_II(Anna, function72, 72)
	error("Anna: callback function 72 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function73, 73)
	error("Anna: callback function 73 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter5, 74)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAnna);

		getData()->entityPosition = kPosition_3969;
		getData()->posture = kPostureSitting;
		getData()->car = kCarBaggageRear;
		getData()->clothes = kClothes3;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectOutsideAnnaCompartment, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(Anna, chapter5Handler, 75)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			if (getProgress().field_C)
				getAction()->playAnimation(getEvent(kEventAnnaKissTrainHijacked) ? kEventAnnaBagageTies2 : kEventAnnaBagageTies);
			else
				getAction()->playAnimation(getEvent(kEventAnnaKissTrainHijacked) ? kEventAnnaBagageTies3 : kEventAnnaBagageTies4);

			getScenes()->loadSceneFromPosition(kCarBaggage, 8);
			setup_function76();
		}
		break;

	case kAction272177921:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_savegame), kSavegameType2, kEventAnnaBagageTies);
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function76, 76)
	if (savepoint.action == kAction158480160)
		setup_function77();
}

IMPLEMENT_FUNCTION(Anna, function77, 77)
	error("Anna: callback function 77 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function78, 78)
	error("Anna: callback function 78 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function79, 79)
	error("Anna: callback function 79 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function80, 80)
	error("Anna: callback function 80 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function81, 81)
	error("Anna: callback function 81 not implemented!");
}

} // End of namespace LastExpress
