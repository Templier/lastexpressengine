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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(1, Kahina, reset)
	Entity::reset(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(2, Kahina, playSound)
	Entity::playSound(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(3, Kahina, savegame, SavegameType, uint32)
	Entity::savegame(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(4, Kahina, updateFromTime, uint32)
	if (savepoint.action == kAction137503360) {
		ENTITY_PARAM(0, 2) = 1;
		CALLBACK_ACTION();
	}

	Entity::updateFromTime(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_NOSETUP(5, Kahina, updateFromTicks)
	Entity::updateFromTicks(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(6, Kahina, function6, TimeValue)
	error("Kahina: callback function 6 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(7 ,Kahina, function7, CarIndex, EntityPosition)
	error("Kahina: callback function 7 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(8, Kahina, updateEntity, CarIndex, EntityPosition)
	if (savepoint.action == kActionExcuseMeCath) {
		if (getEvent(kEventKronosConversation) || getEvent(kEventKronosConversationFirebird)) {
			getSound()->playSound(kEntityPlayer, rnd(2) ? "CAT1019" : "CAT1019A");
		} else {
			getSound()->excuseMeCath();
		}
		return;
	}

	Entity::updateEntity(savepoint, true);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(9, Kahina, enterExitCompartment, ObjectIndex)
	Entity::enterExitCompartment(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(10, Kahina, chapter1)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentKronos, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_5000;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarKronos;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(11, Kahina, chapter1Handler)
	if (savepoint.action != kActionNone)
		return;

	if (getProgress().jacket != kJacketOriginal)
		TIME_CHECK_SAVEPOINT(kTime1107000, params->param1, kEntityKahina, kEntityMertens, kAction238732837);

	if (getProgress().eventMertensKronosInvitation)
		setup_function12();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(12, Kahina, function12)
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
			setup_savegame(kSavegameTypeEvent, kEventKronosGoingToInvitation);
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(13, Kahina, function13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().field_14 || getState()->time >= kTime1201500 || params->param2 == kTimeInvalid || params->param1 >= getState()->time)
			break;

		if (getState()->time <= kTime1197000) {
			if (!getEntities()->isPlayerInCar(kCarGreenSleeping) || !params->param2) {
				params->param2 = getState()->time;

				if (!getState()->time)
					goto label_callback;
			}

			if (params->param2 >= getState()->time)
				break;
		}

		params->param2 = kTimeInvalid;

label_callback:
		setCallback(1);
		setup_function15();
		break;

	case kActionDefault:
		getData()->car = kCarKronos;
		getData()->entityPosition = kPosition_5000;
		getData()->location = kLocationOutsideCompartment;

		getObjects()->update(kObjectCompartmentKronos, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		params->param1 = getState()->time + 1800;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(14, Kahina, function14)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->exitCompartment(kEntityKahina, kObjectCompartmentF);
		CALLBACK_ACTION();
		break;

	case kAction4:
		getEntities()->exitCompartment(kEntityKahina, kObjectCompartmentF);
		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityKahina, "616Cf");
		getEntities()->enterCompartment(kEntityKahina, kObjectCompartmentF);
		getSavePoints()->push(kEntityKahina, kEntityMax, kAction158007856);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(15, Kahina, function15)
	error("Kahina: callback function 15 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(16, Kahina, chapter2)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityKahina);

		getData()->entityPosition = kPosition_6000;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarKronos;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorHandKnock, kCursorHand);

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(17, Kahina, chapter2Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1) {
			if (!params->param2)
				params->param2 = getState()->time + 9000;

			if (params->param2 < getState()->time) {
				params->param1 = 1;
				params->param2 = 0;
			}
		}

		if (getEvent(kEventKahinaAskSpeakFirebird) && getEvent(kEventKronosConversationFirebird) && getEntities()->isInsideTrainCar(kEntityPlayer, kCarKronos)) {
			if (!params->param3)
				params->param3 = getState()->time + 900;

			if (params->param3 < getState()->time) {
				params->param3 = kTimeInvalid;

				setCallback(1);
				setup_savegame(kSavegameTypeEvent, kEventKronosConversationFirebird);
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
			setup_savegame(kSavegameTypeEvent, kEventKronosConversationFirebird);
			break;
		}

		if (getEvent(kEventMilosCompartmentVisitAugust) || getEvent(kEventTatianaGivePoem) || getEvent(kEventTatianaBreakfastGivePoem)) {
			if (savepoint.action == kActionKnock)
				getSound()->playSound(kEntityPlayer, "LIB012");

			setCallback(7);
			setup_savegame(kSavegameTypeEvent, kEventKahinaAskSpeakFirebird);
			break;
		}

		if (params->param1) {
			if (savepoint.action == kActionKnock)
				getSound()->playSound(kEntityPlayer, "LIB012");

			getAction()->playAnimation(kEventKahinaAskSpeak);
			getScenes()->processScene();

			getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(8);
			setup_playSound("KRO3003");
		} else {
			getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(savepoint.action == kActionKnock ? 9 : 10);
			setup_playSound(savepoint.action == kActionKnock ? "LIB012" : "LIB013");
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
			setup_updateFromTime(900);
			break;

		case 2:
		case 5:
			setCallback(getCallback() == 2 ? 3 : 6);
			setup_playSound("KRO3005");
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(18, Kahina, chapter3)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityKahina);

		getData()->entityPosition = kPosition_5000;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarKronos;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(19, Kahina, function19, CarIndex, EntityPosition)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEvent(kEventAnnaBaggageArgument))
			RESET_ENTITY_STATE(kEntityKahina, Kahina, setup_function22);

		if (getEntities()->updateEntity(kEntityKahina, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION();
		break;

	case kActionExcuseMeCath:
		if (getEvent(kEventKronosConversation) || getEvent(kEventKronosConversationFirebird))
			getSound()->playSound(kEntityPlayer, rnd(2) ? "CAT1019" : "CAT1019A");
		else
			getSound()->excuseMeCath();
		break;

	case kActionExcuseMe:
		getSound()->excuseMe(kEntityKahina);
		break;

	case kActionDefault:
		if (getEntities()->updateEntity(kEntityKahina, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(20, Kahina, chapter3Handler)
	error("Kahina: callback function 20 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(21, Kahina, function21)
	error("Kahina: callback function 21 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(22, Kahina, function22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1) {
			ObjectLocation location = getInventory()->get(kItemFirebird)->location;

			if (ENTITY_PARAM(0, 3) || location == kLocation3 || location == kLocation7) {
				setCallback(1);
				setup_function25();
			} else if (location == kLocation2 || location == kLocation1) {
				setCallback(2);
				setup_function26();
			}
		}
		break;

	case kActionDefault:
		getData()->car = kCarKronos;
		getData()->entityPosition = kPosition_5000;
		getData()->location = kLocationOutsideCompartment;
		break;

	case kActionDrawScene:
		if (getData()->car > kCarGreenSleeping || (getData()->car == kCarGreenSleeping && getData()->entityPosition > kPosition_2740))
			params->param1 = 1;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(23, Kahina, function23)
	error("Kahina: callback function 23 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(24, Kahina, function24)
	error("Kahina: callback function 24 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(25, Kahina, function25)
	error("Kahina: callback function 25 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(26, Kahina, function26)
	error("Kahina: callback function 26 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(27, Kahina, function27)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->isInGreenCarEntrance(kEntityPlayer))
			params->param1 = kEventKahinaPunchCar;
		else if (getEntities()->isPlayerInCar(kCarGreenSleeping))
			params->param1 = kEventKahinaPunchBlue;
		else if (getEntities()->isPlayerInCar(kCarRedSleeping))
			params->param1 = kEventKahinaPunchYellow;
		else if (getEntities()->isInSalon(kEntityPlayer))
			params->param1 = kEventKahinaPunchSalon;
		else if (getEntities()->isInRestaurant(kEntityPlayer))
			params->param1 = kEventKahinaPunchRestaurant;
		else if (getEntities()->isInKitchen(kEntityPlayer))
			params->param1 = kEventKahinaPunchKitchen;
		else if (getEntities()->isInBaggageCarEntrance(kEntityPlayer))
			params->param1 = kEventKahinaPunchBaggageCarEntrance;
		else if (getEntities()->isInsideTrainCar(kEntityPlayer, kCarBaggage))
			params->param1 = kEventKahinaPunchBaggageCar;

		if (params->param1) {
			setCallback(1);
			setup_savegame(kSavegameTypeEvent, kSceneGameOverAlarm2);
		}
		break;

	case kActionDefault:
		getState()->timeDelta = 0;
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation((EventIndex)params->param1);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneNone, true);
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(28, Kahina, chapter4)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityKahina);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(29, Kahina, chapter5)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityKahina);
}

} // End of namespace LastExpress
