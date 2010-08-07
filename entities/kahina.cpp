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

#include "lastexpress/entities/kahina.h"

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

Kahina::Kahina(LastExpressEngine *engine) : Entity(engine, kEntityKahina) {
	ADD_CALLBACK_FUNCTION(Kahina, reset);
	ADD_CALLBACK_FUNCTION(Kahina, playSound);
	ADD_CALLBACK_FUNCTION(Kahina, savegame);
	ADD_CALLBACK_FUNCTION(Kahina, updateFromTime);
	ADD_CALLBACK_FUNCTION(Kahina, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Kahina, function6);
	ADD_CALLBACK_FUNCTION(Kahina, function7);
	ADD_CALLBACK_FUNCTION(Kahina, updateEntity);
	ADD_CALLBACK_FUNCTION(Kahina, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Kahina, chapter1);
	ADD_CALLBACK_FUNCTION(Kahina, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Kahina, function12);
	ADD_CALLBACK_FUNCTION(Kahina, function13);
	ADD_CALLBACK_FUNCTION(Kahina, function14);
	ADD_CALLBACK_FUNCTION(Kahina, function15);
	ADD_CALLBACK_FUNCTION(Kahina, chapter2);
	ADD_CALLBACK_FUNCTION(Kahina, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Kahina, chapter3);
	ADD_CALLBACK_FUNCTION(Kahina, function19);
	ADD_CALLBACK_FUNCTION(Kahina, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Kahina, function21);
	ADD_CALLBACK_FUNCTION(Kahina, function22);
	ADD_CALLBACK_FUNCTION(Kahina, function23);
	ADD_CALLBACK_FUNCTION(Kahina, function24);
	ADD_CALLBACK_FUNCTION(Kahina, function25);
	ADD_CALLBACK_FUNCTION(Kahina, function26);
	ADD_CALLBACK_FUNCTION(Kahina, function27);
	ADD_CALLBACK_FUNCTION(Kahina, chapter4);
	ADD_CALLBACK_FUNCTION(Kahina, chapter5);
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Kahina, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Kahina, playSound, 2)
	Entity::playSound(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Kahina, savegame, 3)
	Entity::savegame(savepoint);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_I(Kahina, updateFromTime, 4)
	if (savepoint.action == kAction137503360) {
		ENTITY_PARAM(0, 2) = 1;
		CALLBACK_ACTION()
	}

	Entity::updateFromTime(savepoint);
}

/**
 * Updates parameter 2 using ticks value
 *
 * @param savepoint The savepoint
 *                    - number of ticks to add
 */
IMPLEMENT_FUNCTION_NOSETUP(Kahina, updateFromTicks, 5)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION_I(Kahina, function6, 6)
	error("Kahina: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_II(Kahina, function7, 7)
	error("Kahina: callback function 7 not implemented!");
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Kahina, updateEntity, 8)
	if (savepoint.action == kActionExcuseMeCath) {
		if (getEvent(kEventKronosConversation) || getEvent(kEventKronosConversationFirebird)) {
			getSound()->playSound(kEntityPlayer, random(2) ? "CAT1019" : "CAT1019A");
		} else {
			getSound()->excuseMeCath();
		}
		return;
	}

	Entity::updateEntity(savepoint, true);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Kahina, enterExitCompartment, 9)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION(Kahina, chapter1, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentKronos, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_5000;
		getData()->posture = kPostureStanding;
		getData()->car = kCarKronos;

		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, chapter1Handler, 11)
	if (savepoint.action != kActionNone)
		return;

	if (getProgress().jacket != kJacketOriginal)
		TIME_CHECK_SAVEPOINT(kTime1107000, params->param1, kEntityKahina, kEntityMertens, kAction238732837);

	if (getProgress().eventMertensKronosInvitation)
		setup_function12();
}

IMPLEMENT_FUNCTION(Kahina, function12, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK(kTime1485000, params->param2, setup_function13);
		break;

	case kActionKnock:
		getSound()->playSound(kEntityPlayer, "LIB012");
		// Fallback to next action

	case kActionOpenDoor:
		if (!getEvent(kEventKronosGoingToInvitation)) {
			setCallback(1);
			call(new ENTITY_SETUP(Kahina, setup_savegame), kSavegameType2, kEventKronosGoingToInvitation);
			break;
		}

		if (savepoint.action == kActionOpenDoor)
			getSound()->playSound(kEntityPlayer, "LIB014");

		getScenes()->loadSceneFromPosition(kCarKronos, 80);
		getSavePoints()->push(kEntityKahina, kEntityKronos, kAction171849314);
		params->param1 = 1;
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocationNone, kCursorHandKnock, kCursorHand);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventKronosGoingToInvitation);
			getScenes()->loadSceneFromPosition(kCarKronos, 80);
			getSavePoints()->push(kEntityKahina, kEntityKronos, kAction171849314);
			params->param1 = 1;
		}
		break;

	case kAction137685712:
		setup_function13();
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, function13, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().field_14 || getState()->time >= kTime1201500 || params->param2 == kTimeInvalid || params->param1 >= (int)getState()->time)
			break;

		if (getState()->time <= kTime1197000) {
			if (!getEntities()->checkFields7(kCarGreenSleeping) || !params->param2) {
				params->param2 = getState()->time;

				if (!getState()->time)
					goto label_callback;
			}

			if (params->param2 >= (int)getState()->time)
				break;
		}

		params->param2 = kTimeInvalid;

label_callback:
		setCallback(1);
		call(new ENTITY_SETUP(Kahina, setup_function15));
		break;

	case kActionDefault:
		getData()->car = kCarKronos;
		getData()->entityPosition = kPosition_5000;
		getData()->posture = kPostureStanding;

		getObjects()->update(kObjectCompartmentKronos, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		params->param1 = getState()->time + 1800;
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, function14, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->exitCompartment(kEntityKahina, kObjectCompartmentF);
		CALLBACK_ACTION()
		break;

	case kAction4:
		getEntities()->exitCompartment(kEntityKahina, kObjectCompartmentF);
		CALLBACK_ACTION()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityKahina, "616Cf");
		getEntities()->enterCompartment(kEntityKahina, kObjectCompartmentF);
		getSavePoints()->push(kEntityKahina, kEntityMax, kAction158007856);
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, function15, 15)
	error("Kahina: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter2, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityKahina);

		getData()->entityPosition = kPosition_6000;
		getData()->posture = kPostureStanding;
		getData()->car = kCarKronos;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, chapter2Handler, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1) {
			if (!params->param2)
				params->param2 = getState()->time + 9000;

			if (params->param2 < (int)getState()->time) {
				params->param1 = 1;
				params->param2 = 0;
			}
		}

		if (getEvent(kEventKahinaAskSpeakFirebird) && getEvent(kEventKronosConversationFirebird) && getEntities()->isSittingOrStanding(kEntityPlayer, kCarKronos)) {
			if (!params->param3)
				params->param3 = getState()->time + 900;

			if (params->param3 < (int)getState()->time) {
				params->param3 = kTimeInvalid;

				setCallback(1);
				call(new ENTITY_SETUP(Kahina, setup_savegame), kSavegameType2, kEventKronosConversationFirebird);
				break;
			}
		}

label_callback_3:
		if (getState()->time > kTime1845000 && getEvent(kEventKronosConversationFirebird) && getEntities()->isInKronosSalon(kEntityPlayer)) {
			getObjects()->update(kObjectCompartmentKronos, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
			getScenes()->loadSceneFromPosition(kCarKronos, 87);
		}
		break;

	case kActionKnock:
	case kActionOpenDoor:
		if (getEvent(kEventKronosConversationFirebird))
			break;

		if (getEvent(kEventKahinaAskSpeakFirebird)) {
			if (getSound()->isBuffered(kEntityKahina))
				getSound()->processEntry(kEntityKahina);

			if (savepoint.action == kActionKnock)
				getSound()->playSound(kEntityPlayer, "LIB012");

			setCallback(4);
			call(new ENTITY_SETUP(Kahina, setup_savegame), kSavegameType2, kEventKronosConversationFirebird);
			break;
		}

		if (getEvent(kEventMilosCompartmentVisitAugust) || getEvent(kEventTatianaGivePoem) || getEvent(kEventTatianaBreakfastGivePoem)) {
			if (savepoint.action == kActionKnock)
				getSound()->playSound(kEntityPlayer, "LIB012");

			setCallback(7);
			call(new ENTITY_SETUP(Kahina, setup_savegame), kSavegameType2, kEventKahinaAskSpeakFirebird);
			break;
		}

		if (params->param1) {
			if (savepoint.action == kActionKnock)
				getSound()->playSound(kEntityPlayer, "LIB012");

			getAction()->playAnimation(kEventKahinaAskSpeak);
			getScenes()->processScene();

			getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(8);
			call(new ENTITY_SETUP_SIIS(Kahina, setup_playSound), "KRO3003");
		} else {
			getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(savepoint.action == kActionKnock ? 9 : 10);
			call(new ENTITY_SETUP_SIIS(Kahina, setup_playSound), savepoint.action == kActionKnock ? "LIB012" : "LIB013");
		}
		break;

	case kActionDefault:
		params->param1 = 1;
		getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorHandKnock, kCursorHand);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 4:
			getAction()->playAnimation(kEventKronosConversationFirebird);
			getObjects()->update(kObjectCompartmentKronos, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
			getScenes()->loadSceneFromPosition(kCarKronos, 80, 1);

			setCallback(getCallback() == 1 ? 2 : 5);
			call(new ENTITY_SETUP(Kahina, setup_updateFromTime), 900);
			break;

		case 2:
		case 5:
			setCallback(getCallback() == 2 ? 3 : 6);
			call(new ENTITY_SETUP_SIIS(Kahina, setup_playSound), "KRO3005");
			break;

		case 3:
			goto label_callback_3;

		case 7:
			getAction()->playAnimation(kEventKahinaAskSpeakFirebird);
			getScenes()->loadSceneFromPosition(kCarKronos, 81);
			getSound()->playSound(kEntityKahina, "KRO3004");
			break;

		case 8:
		case 9:
		case 10:
			getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorHandKnock, kCursorHand);
			if (getCallback() == 8)
				params->param1 = 0;
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, chapter3, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityKahina);

		getData()->entityPosition = kPosition_5000;
		getData()->posture = kPostureStanding;
		getData()->car = kCarKronos;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

/**
 * Update the entity, handling excuse me events and resetting the entity state after the argument with Anna in the bagage car
 *
 * @param param1 The car index
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Kahina, function19, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEvent(kEventAnnaBagageArgument))
			RESET_ENTITY_STATE(kEntityKahina, Kahina, setup_function22);

		if (getEntities()->updateEntity(kEntityKahina, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION()
		break;

	case kActionExcuseMeCath:
		if (getEvent(kEventKronosConversation) || getEvent(kEventKronosConversationFirebird))
			getSound()->playSound(kEntityPlayer, random(2) ? "CAT1019" : "CAT1019A");
		else
			getSound()->excuseMeCath();
		break;

	case kActionExcuseMe:
		getSound()->excuseMe(kEntityKahina);
		break;

	case kActionDefault:
		if (getEntities()->updateEntity(kEntityKahina, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION()
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, chapter3Handler, 20)
	error("Kahina: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function21, 21)
	error("Kahina: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function22, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1) {
			ObjectLocation location = getInventory()->get(kItemFirebird)->location;

			if (ENTITY_PARAM(0, 3) || location == kLocation3 || location == kLocation7) {
				setCallback(1);
				call(new ENTITY_SETUP(Kahina, setup_function25));
			} else if (location == kLocation2 || location == kLocation1) {
				setCallback(2);
				call(new ENTITY_SETUP(Kahina, setup_function26));
			}
		}
		break;

	case kActionDefault:
		getData()->car = kCarKronos;
		getData()->entityPosition = kPosition_5000;
		getData()->posture = kPostureStanding;
		break;

	case kActionDrawScene:
		if (getData()->car > kCarGreenSleeping || (getData()->car == kCarGreenSleeping && getData()->entityPosition > kPosition_2740))
			params->param1 = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, function23, 23)
	error("Kahina: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function24, 24)
	error("Kahina: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function25, 25)
	error("Kahina: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function26, 26)
	error("Kahina: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function27, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->checkFields6(kEntityPlayer))
			params->param1 = kEventKahinaPunchCar;
		else if (getEntities()->checkFields7(kCarGreenSleeping))
			params->param1 = kEventKahinaPunchBlue;
		else if (getEntities()->checkFields7(kCarRedSleeping))
			params->param1 = kEventKahinaPunchYellow;
		else if (getEntities()->isInSalon(kEntityPlayer))
			params->param1 = kEventKahinaPunchSalon;
		else if (getEntities()->isInRestaurant(kEntityPlayer))
			params->param1 = kEventKahinaPunchRestaurant;
		else if (getEntities()->isInKitchen(kEntityPlayer))
			params->param1 = kEventKahinaPunchKitchen;
		else if (getEntities()->isInBaggageCarEntrance(kEntityPlayer))
			params->param1 = kEventKahinaPunchBaggageCarEntrance;
		else if (getEntities()->isSittingOrStanding(kEntityPlayer, kCarBaggage))
			params->param1 = kEventKahinaPunchBaggageCar;

		if (params->param1) {
			setCallback(1);
			call(new ENTITY_SETUP(Kahina, setup_savegame), kSavegameType2, kSceneGameOverAlarm2);
		}
		break;

	case kActionDefault:
		getState()->timeDelta = 0;
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation((EventIndex)params->param1);
			getLogic()->gameOver(kInitTypeIndex, 1, kSceneNone, true);
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, chapter4, 28)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityKahina);
}

IMPLEMENT_FUNCTION(Kahina, chapter5, 29)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityKahina);
}

} // End of namespace LastExpress
