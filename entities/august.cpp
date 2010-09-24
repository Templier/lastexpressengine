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

#include "lastexpress/entities/august.h"

#include "lastexpress/entities/verges.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

August::August(LastExpressEngine *engine) : Entity(engine, kEntityAugust) {
	ADD_CALLBACK_FUNCTION(August, reset);
	ADD_CALLBACK_FUNCTION(August, updateFromTime);
	ADD_CALLBACK_FUNCTION(August, draw);
	ADD_CALLBACK_FUNCTION(August, updatePosition);
	ADD_CALLBACK_FUNCTION(August, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(August, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(August, enterExitCompartment3);
	ADD_CALLBACK_FUNCTION(August, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(August, callSavepoint);
	ADD_CALLBACK_FUNCTION(August, callSavepointNoDrawing);
	ADD_CALLBACK_FUNCTION(August, draw2);
	ADD_CALLBACK_FUNCTION(August, playSound);
	ADD_CALLBACK_FUNCTION(August, playSound16);
	ADD_CALLBACK_FUNCTION(August, callbackActionRestaurantOrSalon);
	ADD_CALLBACK_FUNCTION(August, savegame);
	ADD_CALLBACK_FUNCTION(August, updateEntity);
	ADD_CALLBACK_FUNCTION(August, function17);
	ADD_CALLBACK_FUNCTION(August, updateEntity2);
	ADD_CALLBACK_FUNCTION(August, function19);
	ADD_CALLBACK_FUNCTION(August, function20);
	ADD_CALLBACK_FUNCTION(August, function21);
	ADD_CALLBACK_FUNCTION(August, chapter1);
	ADD_CALLBACK_FUNCTION(August, function23);
	ADD_CALLBACK_FUNCTION(August, dinner);
	ADD_CALLBACK_FUNCTION(August, chapter1Handler);
	ADD_CALLBACK_FUNCTION(August, function26);
	ADD_CALLBACK_FUNCTION(August, function27);
	ADD_CALLBACK_FUNCTION(August, function28);
	ADD_CALLBACK_FUNCTION(August, function29);
	ADD_CALLBACK_FUNCTION(August, restaurant);
	ADD_CALLBACK_FUNCTION(August, function31);
	ADD_CALLBACK_FUNCTION(August, function32);
	ADD_CALLBACK_FUNCTION(August, function33);
	ADD_CALLBACK_FUNCTION(August, function34);
	ADD_CALLBACK_FUNCTION(August, chapter2);
	ADD_CALLBACK_FUNCTION(August, chapter2Handler);
	ADD_CALLBACK_FUNCTION(August, function37);
	ADD_CALLBACK_FUNCTION(August, function38);
	ADD_CALLBACK_FUNCTION(August, function39);
	ADD_CALLBACK_FUNCTION(August, chapter3);
	ADD_CALLBACK_FUNCTION(August, function41);
	ADD_CALLBACK_FUNCTION(August, function42);
	ADD_CALLBACK_FUNCTION(August, chapter3Handler);
	ADD_CALLBACK_FUNCTION(August, function44);
	ADD_CALLBACK_FUNCTION(August, function45);
	ADD_CALLBACK_FUNCTION(August, function46);
	ADD_CALLBACK_FUNCTION(August, function47);
	ADD_CALLBACK_FUNCTION(August, function48);
	ADD_CALLBACK_FUNCTION(August, function49);
	ADD_CALLBACK_FUNCTION(August, function50);
	ADD_CALLBACK_FUNCTION(August, function51);
	ADD_CALLBACK_FUNCTION(August, function52);
	ADD_CALLBACK_FUNCTION(August, function53);
	ADD_CALLBACK_FUNCTION(August, function54);
	ADD_CALLBACK_FUNCTION(August, function55);
	ADD_CALLBACK_FUNCTION(August, function56);
	ADD_CALLBACK_FUNCTION(August, chapter4);
	ADD_CALLBACK_FUNCTION(August, chapter4Handler);
	ADD_CALLBACK_FUNCTION(August, function59);
	ADD_CALLBACK_FUNCTION(August, function60);
	ADD_CALLBACK_FUNCTION(August, function61);
	ADD_CALLBACK_FUNCTION(August, function62);
	ADD_CALLBACK_FUNCTION(August, function63);
	ADD_CALLBACK_FUNCTION(August, function64);
	ADD_CALLBACK_FUNCTION(August, function65);
	ADD_CALLBACK_FUNCTION(August, chapter5);
	ADD_CALLBACK_FUNCTION(August, chapter5Handler);
	ADD_CALLBACK_FUNCTION(August, function68);
	ADD_CALLBACK_FUNCTION(August, unhookCars);
	ADD_NULL_FUNCTION();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(1, August, reset)
	Entity::reset(savepoint, true);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(2, August, updateFromTime, uint32)
	Entity::updateFromTime(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(3, August, draw)
	Entity::draw(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SII(4, August, updatePosition, CarIndex, Position)
	Entity::updatePosition(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(5, August, enterExitCompartment, ObjectIndex)
	Entity::enterExitCompartment(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(6, August, enterExitCompartment2, ObjectIndex)
	Entity::enterExitCompartment(savepoint, kPosition_6470, kPosition_6130, kCarGreenSleeping, kObjectCompartment3, true);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(7, August, enterExitCompartment3, ObjectIndex)
	if (savepoint.action == kAction4) {
		getEntities()->exitCompartment(kEntityAugust, (ObjectIndex)params->param4);
		CALLBACK_ACTION();
		return;
	}

	Entity::enterExitCompartment(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(8, August, callbackActionOnDirection)
	Entity::callbackActionOnDirection(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SIIS(9, August, callSavepoint, EntityIndex, ActionIndex)
	Entity::callSavepoint(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_IIS(10, August, callSavepointNoDrawing, EntityIndex, ActionIndex)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		if (!params->param6)
			getSavePoints()->call(kEntityAugust, (EntityIndex)params->param1, (ActionIndex)params->param2, (char *)&params->seq);

		CALLBACK_ACTION();
		break;

	case kAction10:
		if (!params->param6) {
			getSavePoints()->call(kEntityAugust, (EntityIndex)params->param1, (ActionIndex)params->param2, (char *)&params->seq);
			params->param6 = 1;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SSI(11, August, draw2, EntityIndex)
	Entity::draw2(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(12, August, playSound)
	Entity::playSound(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(13, August, playSound16)
	Entity::playSound(savepoint, false, SoundManager::kFlagDefault);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(14, August, callbackActionRestaurantOrSalon)
	Entity::callbackActionRestaurantOrSalon(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(15, August, savegame, SavegameType, uint32)
	Entity::savegame(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(16, August, updateEntity, CarIndex, EntityPosition)
	if (savepoint.action == kActionExcuseMeCath) {
		getProgress().eventMetAugust ? getSound()->playSound(kEntityPlayer, rnd(2) ? "CAT1002A" : "CAT1002") : getSound()->excuseMeCath();
		return;
	}

	Entity::updateEntity(savepoint, true);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(17, August, function17, TimeValue)
	error("August: callback function 17 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(18, August, updateEntity2, CarIndex, EntityPosition)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->updateEntity(_entityIndex, (CarIndex)params->param1, (EntityPosition)params->param2)) {
			CALLBACK_ACTION();
		} else if (getEntities()->isDistanceBetweenEntities(kEntityAugust, kEntityPlayer, 1000)
		        && !getEntities()->isInGreenCarEntrance(kEntityPlayer)
				&& !getEntities()->isInsideCompartments(kEntityPlayer)
				&& !getEntities()->checkFields10(kEntityPlayer)) {

			if (getData()->car == kCarGreenSleeping || getData()->car == kCarRedSleeping) {
				ENTITY_PARAM(0, 1) = 1;
				CALLBACK_ACTION();
			}
		}
		break;

	case kActionDefault:
		if (getEntities()->updateEntity(_entityIndex, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(19, August, function19, bool, bool)
	error("August: callback function 19 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(20, August, function20, bool)
	error("August: callback function 20 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(21, August, function21, TimeValue)
	error("August: callback function 21 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(22, August, chapter1)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject11, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->entityPosition = kPosition_4691;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;

		getProgress().eventMetAugust = false;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(23, August, function23, TimeValue)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().field_14 == 29 || getProgress().field_14 == 3) {
			if (params->param3) {
				getData()->location = kLocationOutsideCompartment;

				setCallback(2);
				setup_enterExitCompartment("626Ea", kObjectCompartment1);
			} else {
				getEntities()->exitCompartment(kEntityAugust, kObjectCompartment1, true);
				getObjects()->update(kObjectCompartment1, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
				CALLBACK_ACTION();
			}
			break;
		}

		if (!params->param2) {

			if (!CURRENT_PARAMS(1, 3))
				CURRENT_PARAMS(1, 3) = getState()->timeTicks + 45;

			if (CURRENT_PARAMS(1, 3) >= getState()->timeTicks)
				break;

			if (!params->param5) {
				setCallback(8);
				setup_playSound("AUG1002B");
				break;
			}

label_callback_8:
			if (!CURRENT_PARAMS(1, 4))
				CURRENT_PARAMS(1, 4) = getState()->timeTicks + 75;

			if (CURRENT_PARAMS(1, 4) < getState()->timeTicks) {
				CURRENT_PARAMS(1, 4) = kTimeInvalid;

				getEntities()->exitCompartment(kEntityAugust, kObjectCompartment1, true);

				if (getProgress().eventCorpseMovedFromFloor) {
					setCallback(9);
					setup_enterExitCompartment("626Da", kObjectCompartment1);
				} else if (getEntities()->isInsideTrainCar(kEntityPlayer, kCarGreenSleeping)) {
					setCallback(10);
					setup_enterExitCompartment3("626Da", kObjectCompartment1);
				} else {
					getScenes()->loadSceneFromPosition(kCarNone, 1);
					getObjects()->update(kObjectOutsideTylerCompartment, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);
					setCallback(11);
					setup_savegame(kSavegameTypeEvent, kEventAugustFindCorpse);
				}
				break;
			}

label_callback_9:
			if (params->param3 && params->param1 < getState()->time && !CURRENT_PARAMS(1, 5)) {
				CURRENT_PARAMS(1, 5) = 1;
				getObjects()->update(kObjectCompartment1, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);

				setCallback(12);
				setup_enterExitCompartment("626Ea", kObjectCompartment1);
			}
			break;
		}

		if (!CURRENT_PARAMS(1, 1))
			CURRENT_PARAMS(1, 1) = getState()->timeTicks + 45;

		if (CURRENT_PARAMS(1, 1) >= getState()->timeTicks)
			break;

		if (getObjects()->get(kObjectCompartment1).location == kLocation1) {
			UPDATE_PARAM(CURRENT_PARAMS(1, 2), getState()->timeTicks, 75);

			getObjects()->update(kObjectCompartment1, kEntityAugust, getObjects()->get(kObjectCompartment1).location, kCursorNormal, kCursorNormal);

			params->param6++;

			switch (params->param6) {
			default:
				break;

			case 1:
				setCallback(5);
				setup_playSound("LIB013");
				return;

			case 2:
				setCallback(7);
				setup_playSound("LIB012");
				return;

			case 3:
				params->param8++;

				if (params->param8 >= 3) {
					getObjects()->update(kObjectCompartment1, kEntityPlayer, getObjects()->get(kObjectCompartment1).location, kCursorHandKnock, kCursorHand);
					CALLBACK_ACTION();
					break;
				}

				params->param6 = 0;
			}

			getObjects()->update(kObjectCompartment1, kEntityAugust, getObjects()->get(kObjectCompartment1).location, params->param4 ? kCursorNormal : kCursorTalk, kCursorHand);
			CURRENT_PARAMS(1, 2) = 0;
		} else {

			if (getProgress().eventCorpseMovedFromFloor && getProgress().jacket != kJacketBlood) {
				params->param7 = (getObjects()->get(kObjectCompartment1).location2 == kLocation1) ? 8 : 7;
				getObjects()->update(kObjectOutsideTylerCompartment, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

				setCallback(4);
				setup_savegame(kSavegameTypeEvent, kEventMeetAugustTylerCompartment);
			} else {
				getObjects()->update(kObjectOutsideTylerCompartment, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

				setCallback(3);
				setup_savegame(kSavegameTypeEvent, kEventAugustFindCorpse);
			}
		}
		break;

	case kActionKnock:
		if (params->param3) {
			getObjects()->update(kObjectCompartment1, kEntityAugust, kLocationNone, kCursorNormal, kCursorNormal);

			setCallback(15);
			setup_playSound("LIB012");
		} else if (!params->param4) {
			getObjects()->update(kObjectCompartment1, kEntityAugust, getObjects()->get(kObjectCompartment1).location, kCursorNormal, kCursorNormal);

			setCallback(17);
			setup_playSound("AUG1002A");
		}
		break;

	case kActionOpenDoor:
		if (getProgress().eventCorpseMovedFromFloor && getProgress().jacket != kJacketBlood) {
			if (params->param3) {
				getData()->location = kLocationInsideCompartment;

				params->param7 = (getObjects()->get(kObjectCompartment1).location2 == kLocation1) ? kEventMeetAugustHisCompartmentBed : kEventMeetAugustHisCompartment;
			} else {
				params->param7 = (getObjects()->get(kObjectCompartment1).location2 == kLocation1) ? kEventMeetAugustTylerCompartmentBed : kEventMeetAugustTylerCompartment;
			}

			setCallback(14);
			setup_savegame(kSavegameTypeEvent, kEventMeetAugustTylerCompartment);
		} else {
			getObjects()->update(kObjectOutsideTylerCompartment, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

			setCallback(13);
			setup_savegame(kSavegameTypeEvent, kEventAugustFindCorpse);
		}
		break;

	case kActionDefault:
		if (getEntities()->isInsideCompartment(kEntityPlayer, kCarGreenSleeping, kPosition_8200)
		 || getEntities()->isInsideCompartment(kEntityPlayer, kCarGreenSleeping, kPosition_7850)
		 || getEntities()->isOutsideAlexeiWindow()) {
			getObjects()->update(kObjectCompartment1, kEntityAugust, getObjects()->get(kObjectCompartment1).location, kCursorNormal, kCursorNormal);

			if (getEntities()->isOutsideAlexeiWindow())
				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);

			getSound()->playSound(kEntityPlayer, "LIB012");

			getObjects()->update(kObjectCompartment1, kEntityAugust, getObjects()->get(kObjectCompartment1).location, kCursorTalk, kCursorHand);

			params->param2 = 1;
		} else {
			setCallback(1);
			setup_enterExitCompartment("626Aa", kObjectCompartment1);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceLeft(kEntityAugust, "626Ba");
			getEntities()->enterCompartment(kEntityAugust, kObjectCompartment1, true);
			break;

		case 2:
			getObjects()->update(kObjectCompartment1, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
			CALLBACK_ACTION();
			break;

		case 3:
			getSound()->playSound(kEntityPlayer, "LIB014");
			getAction()->playAnimation(kEventAugustFindCorpse);
			if (getEvent(kEventDinerAugustOriginalJacket))
				getLogic()->gameOver(kSavegameTypeEvent2, kEventDinerAugustOriginalJacket, getProgress().eventCorpseFound ? kSceneGameOverStopPolice : kSceneGameOverPolice, true);
			else if (getProgress().eventCorpseMovedFromFloor)
				getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
			else
				getLogic()->gameOver(kSavegameTypeIndex, 1, getProgress().eventCorpseFound ? kSceneGameOverStopPolice : kSceneGameOverPolice, true);
			break;

		case 4:
			getObjects()->update(kObjectCompartment1, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
			getSound()->playSound(kEntityPlayer, "LIB014");
			getEntities()->clearSequences(kEntityAugust);
			getData()->location = kLocationInsideCompartment;

			getAction()->playAnimation((EventIndex)params->param7);
			getSound()->playSound(kEntityPlayer, "LIB015");
			getProgress().eventMetAugust = true;
			getData()->location = kLocationOutsideCompartment;

			getScenes()->loadScene(kScene41);

			CALLBACK_ACTION();
			break;

		case 5:
			setCallback(6);
			setup_playSound16("AUG1002B");
			break;

		case 6:
		case 7:
			getObjects()->update(kObjectCompartment1, kEntityAugust, getObjects()->get(kObjectCompartment1).location, params->param4 ? kCursorNormal : kCursorTalk, kCursorHand);
			ENTITY_PARAM(1, 2) = 0;
			break;

		case 8:
			params->param5 = 1;
			goto label_callback_8;

		case 9:
			params->param3 = 1;
			getEntities()->clearSequences(kEntityAugust);
			getData()->location = kLocationInsideCompartment;
			getObjects()->update(kObjectCompartment1, kEntityAugust, kLocationNone, kCursorHandKnock, kCursorHand);
			goto label_callback_9;

		case 10:
			getObjects()->update(kObjectOutsideTylerCompartment, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);
			setCallback(11);
			setup_savegame(kSavegameTypeEvent, kEventAugustFindCorpse);
			break;

		case 11:
			getAction()->playAnimation(kEventAugustFindCorpse);

			getLogic()->gameOver(getEvent(kEventDinerAugustOriginalJacket) ? kSavegameTypeEvent2 : kSavegameTypeIndex,
								 getEvent(kEventDinerAugustOriginalJacket) ? kEventDinerAugustOriginalJacket : 1,
								 getProgress().eventCorpseFound ? kSceneGameOverStopPolice : kSceneGameOverPolice,
								 true);
			break;

		case 12:
			getData()->location = kLocationOutsideCompartment;
			CALLBACK_ACTION();
			break;

		case 13:
			getSound()->playSound(kEntityPlayer, getObjects()->get(kObjectCompartment1).location == kLocation1 ? "LIB032" : "LIB014");
			getAction()->playAnimation(kEventAugustFindCorpse);

			if (getEvent(kEventDinerAugustOriginalJacket))
				getLogic()->gameOver(kSavegameTypeEvent2, kEventDinerAugustOriginalJacket, getProgress().eventCorpseFound ? kSceneGameOverStopPolice : kSceneGameOverPolice, true);
			else if (getProgress().eventCorpseMovedFromFloor)
				getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
			else
				getLogic()->gameOver(kSavegameTypeIndex, 1, getProgress().eventCorpseFound ? kSceneGameOverStopPolice : kSceneGameOverPolice, true);
			break;

		case 14:
			if (!params->param2)
				getSound()->playSound(kEntityPlayer, getObjects()->get(kObjectCompartment1).location == kLocation1 ? "LIB032" : "LIB014");

			getObjects()->update(kObjectCompartment1, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectOutsideTylerCompartment, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

			getAction()->playAnimation((EventIndex)params->param7);
			getProgress().eventMetAugust = true;
			getData()->location = kLocationOutsideCompartment;

			getScenes()->loadScene(kScene41);

			CALLBACK_ACTION();
			break;

		case 15:
			setCallback(16);
			setup_playSound("AUG1128A");
			break;

		case 16:
			getObjects()->update(kObjectCompartment1, kEntityAugust, kLocationNone, kCursorHandKnock, kCursorHand);
			break;

		case 17:
			params->param4 = 1;
			getObjects()->update(kObjectCompartment1, kEntityAugust, getObjects()->get(kObjectCompartment1).location, kCursorNormal, kCursorHand);
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(24, August, dinner)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_savegame(kSavegameTypeEvent, kEventDinerAugust);
		break;

	case kActionCallback:
		if (getCallback() == 1) {

			getAction()->playAnimation(getEntities()->isInRestaurant(kEntityAlexei) ? kEventDinerAugustAlexeiBackground : kEventDinerAugust);
			getProgress().eventMetAugust = true;

			getScenes()->loadSceneFromPosition(kCarRestaurant, 61);

			CALLBACK_ACTION();
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(25, August, chapter1Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param1 && getProgress().eventCorpseFound) {
			getSavePoints()->push(kEntityAugust, kEntityPascale, kAction239072064);
			params->param1 = 1;
		}

		if (getState()->time > kTime1080000 && !params->param3) {
			params->param3 = 1;

			if (!params->param1) {
				getSavePoints()->push(kEntityAugust, kEntityPascale, kAction239072064);
				params->param1 = 1;
			}
		}

		if (getState()->time > kTime1093500 && getEntities()->isSomebodyInsideRestaurantOrSalon()) {
			getData()->location = kLocationOutsideCompartment;
			getData()->inventoryItem = kItemNone;

			setCallback(1);
			setup_callSavepoint("010J", kEntityTables3, kActionDrawTablesWithChairs, "010K");
		}
		break;

	case kAction1:
		params->param2 = 0;
		getData()->inventoryItem = kItemNone;
		getSavePoints()->push(kEntityAugust, kEntityPascale, kAction191604416);

		if (getProgress().jacket == kJacketGreen) {
			setCallback(3);
			setup_dinner();
		} else {
			setCallback(4);
			setup_savegame(kSavegameTypeEvent, kEventDinerAugustOriginalJacket);
		}
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAugust, kEntityTables3, kAction136455232);
		getEntities()->drawSequenceLeft(kEntityAugust, "010B");

		if (!getProgress().eventMetAugust)
			params->param2 = kItemInvalid;

		getData()->inventoryItem = (InventoryItem)params->param2;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityAugust, kEntityServers0, kAction204704037);
			getEntities()->drawSequenceRight(kEntityAugust, "803DS");
			if (getEntities()->isInRestaurant(kEntityPlayer))
				getEntities()->updateFrame(kEntityAugust);

			setCallback(2);
			setup_callbackActionOnDirection();
			break;

		case 2:
			setup_function26();
			break;

		case 3:
			setup_function28();
			break;

		case 4:
			getSavePoints()->push(kEntityAugust, kEntityAlexei, kAction225182640);
			getAction()->playAnimation(kEventDinerAugustOriginalJacket);
			getObjects()->update(kObjectCompartment1, kEntityPlayer, kLocation3, kCursorNormal, kCursorNormal);

			getData()->location = kLocationOutsideCompartment;

			getSavePoints()->push(kEntityAugust, kEntityTables3, kActionDrawTablesWithChairs, "010K");
			getEntities()->drawSequenceRight(kEntityAugust, "010P");
			getScenes()->loadSceneFromPosition(kCarRestaurant, 65);

			setCallback(5);
			setup_callbackActionOnDirection();
			break;

		case 5:
			getSavePoints()->push(kEntityAugust, kEntityServers0, kAction204704037);
			getEntities()->drawSequenceRight(kEntityAugust, "803DS");
			if (getEntities()->isInRestaurant(kEntityPlayer))
				getEntities()->updateFrame(kEntityAugust);

			setCallback(6);
			setup_callbackActionOnDirection();
			break;

		case 6:
			getProgress().field_14 = 2;

			setCallback(7);
			setup_updateEntity(kCarGreenSleeping, kPosition_8200);
			break;

		case 7:
			setCallback(8);
			setup_function23(kTimeNone);
			break;

		case 8:
			getLogic()->gameOver(kSavegameTypeIndex, 0, kSceneNone, true);
			break;
		}
		break;

	case kAction168046720:
		getData()->inventoryItem = kItemNone;
		break;

	case kAction168627977:
		getData()->inventoryItem = (InventoryItem)params->param2;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(26, August, function26)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (getProgress().eventMetAugust || getProgress().field_14) {
			setCallback(5);
			setup_updateEntity(kCarGreenSleeping, kPosition_6470);
		} else {
			getProgress().field_14 = 2;
			setCallback(1);
			setup_updateEntity(kCarGreenSleeping, kPosition_8200);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_function23((TimeValue)(getState()->time + 13500));
			break;

		case 2:
			setCallback(3);
			setup_updateEntity(kCarGreenSleeping, kPosition_6470);
			break;

		case 3:
			setCallback(4);
			setup_function19(false, false);
			break;

		case 4:
			if (getProgress().field_14 == 2)
				getProgress().field_14 = 0;

			setCallback(7);
			setup_function21((TimeValue)(getState()->time + 900));
			break;

		case 5:
			setCallback(6);
			setup_function19(false, false);
			break;

		case 6:
			setCallback(7);
			setup_function21((TimeValue)(getState()->time + 900));
			break;

		case 7:
			setup_function27();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(27, August, function27)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function20(false);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_updateEntity(kCarRestaurant, kPosition_850);
			break;

		case 2:
			setCallback(3);
			setup_callbackActionRestaurantOrSalon();
			break;

		case 3:
			getData()->entityPosition = kPosition_1540;
			getData()->location = kLocationOutsideCompartment;

			setCallback(4);
			setup_draw("803US");
			break;

		case 4:
			getEntities()->drawSequenceRight(kEntityAugust, "010A");
			if (getEntities()->isInSalon(kEntityPlayer))
				getEntities()->updateFrame(kEntityAugust);

			setCallback(5);
			setup_callSavepointNoDrawing(kEntityTables3, kAction136455232, "BOGUS");
			break;

		case 5:
			getData()->location = kLocationInsideCompartment;
			setup_function28();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(28, August, function28)
	switch (savepoint.action) {
	default:
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;
		params->param1 = 0;

		setCallback(3);
		setup_dinner();
		break;

	case kActionDefault:
		if (!getProgress().eventMetAugust && getProgress().jacket == kJacketGreen)
			params->param1 = kItemInvalid;

		getEntities()->drawSequenceLeft(kEntityAugust, "010B");
		getSavePoints()->push(kEntityAugust, kEntityServers0, kAction304061224);
		getData()->inventoryItem = (InventoryItem)params->param1;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityAugust, kEntityServers0, kAction203859488);
			getData()->inventoryItem = (InventoryItem)params->param1;
			getEntities()->drawSequenceLeft(kEntityAugust, "010B");
			break;

		case 2:
			getSavePoints()->push(kEntityAugust, kEntityServers0, kAction136702400);
			getEntities()->drawSequenceLeft(kEntityAugust, "010B");
			setup_function29();
			break;
		}
		break;

	case kAction168046720:
		getData()->inventoryItem = kItemNone;
		break;

	case kAction168627977:
		getData()->inventoryItem = (InventoryItem)params->param1;
		break;

	case kAction170016384:
		getData()->inventoryItem = kItemNone;
		getEntities()->drawSequenceLeft(kEntityServers0, "BLANK");
		getEntities()->drawSequenceLeft(kEntityAugust, "010G");

		setCallback(2);
		setup_playSound("AUG1053");
		break;

	case kAction268773672:
		getData()->inventoryItem = kItemNone;
		getEntities()->drawSequenceLeft(kEntityAugust, "010D");

		setCallback(1);
		setup_playSound("AUG1052");
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(29, August, function29)
	error("August: callback function 29 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(30, August, restaurant)
	error("August: callback function 30 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(31, August, function31)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_updateEntity(kCarGreenSleeping, kPosition_6470);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_function19(0, 0);
			break;

		case 2:
			setCallback(2);
			setup_function21(kTime1161000);
			break;

		case 3:
		case 4:
			if (getProgress().field_14 == 29) {
				setCallback(4);
				setup_function21((TimeValue)(getState()->time + 900));
			} else {
				setup_function32();
			}
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(32, August, function32)
	error("August: callback function 32 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(33, August, function33)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(getProgress().eventMetAugust ? 1 : 2);
		setup_function21(getProgress().eventMetAugust ? (TimeValue)(getState()->time + 9000) : kTimeBedTime);
		break;

	case kActionCallback:
		if (getCallback() == 1 || getCallback() == 2)
			setup_function34();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(34, August, function34)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!getSound()->isBuffered(kEntityAugust) && getProgress().field_18 != 4)
			getSound()->playSound(kEntityAugust, "AUG1057");    // August snoring
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_6470;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		getEntities()->clearSequences(kEntityAugust);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(35, August, chapter2)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAugust);

		getData()->entityPosition = kPosition_3970;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartment3, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject11, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(36, August, chapter2Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_SAVEPOINT(kTime1755000, params->param2, kEntityAugust, kEntityServers0, kAction252568704);

		if (getState()->time > kTime1773000 && params->param1 && getEntities()->isSomebodyInsideRestaurantOrSalon()) {
			getData()->inventoryItem = kItemNone;
			getData()->location = kLocationOutsideCompartment;
			getEntities()->updatePositionEnter(kEntityAugust, kCarRestaurant, 62);

			setCallback(2);
			setup_callSavepoint("016C", kEntityTables0, kActionDrawTablesWithChairs, "016D");
		}
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;

		setCallback(1);
		setup_savegame(kSavegameTypeEvent, kEventAugustGoodMorning);
		break;

	case kActionDefault:
		if (!getEvent(kEventAugustGoodMorning))
				getData()->inventoryItem = kItemInvalid;

		getSavePoints()->push(kEntityAugust, kEntityTables0, kAction136455232);
		getEntities()->drawSequenceLeft(kEntityAugust, "016B");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventAugustGoodMorning);
			getScenes()->loadSceneFromPosition(kCarRestaurant, 61);
			break;

		case 2:
			getEntities()->updatePositionExit(kEntityAugust, kCarRestaurant, 62);
			getEntities()->drawSequenceRight(kEntityAugust, "803ES");
			if (getEntities()->isInRestaurant(kEntityPlayer))
				getEntities()->updateFrame(kEntityAugust);

			setCallback(3);
			setup_callbackActionOnDirection();
			break;

		case 3:
			getSavePoints()->push(kEntityAugust, kEntityServers0, kAction286534136);

			setCallback(4);
			setup_updateEntity(kCarGreenSleeping, kPosition_6470);
			break;

		case 4:
			setCallback(5);
			setup_function19(true, false);
			break;

		case 5:
			setup_function37();
			break;

		case 6:
			if (!getEvent(kEventAugustGoodMorning))
				getData()->inventoryItem = kItemInvalid;

			getSavePoints()->push(kEntityAugust, kEntityServers0, kAction219522616);
			getEntities()->drawSequenceLeft(kEntityAugust, "016B");
			params->param1 = 1;
			break;
		}
		break;

	case kAction123712592:
		getEntities()->drawSequenceLeft(kEntityAugust, "016A");
		getData()->inventoryItem = kItemNone;

		setCallback(6);
		setup_playSound("AUG2113");
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(37, August, function37)
	error("August: callback function 37 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(38, August, function38)
	error("August: callback function 38 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(39, August, function39)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (!ENTITY_PARAM(0, 1))
			getSound()->playSound(kEntityPlayer, "BUMP");

		setCallback(1);
		setup_savegame(kSavegameTypeEvent, kEventAugustArrivalInMunich);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventAugustArrivalInMunich);
			getSavePoints()->push(kEntityAugust, kEntityChapters, kActionChapter3);
			getEntities()->clearSequences(kEntityAugust);
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(40, August, chapter3)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAugust);

		getData()->entityPosition = kPosition_6470;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(41, August, function41, CarIndex, EntityPosition)
	error("August: callback function 41 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_III(42, August, function42, CarIndex, EntityPosition, bool)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param4 && getEntities()->isDistanceBetweenEntities(kEntityAugust, kEntityPlayer, 2000))
			getData()->inventoryItem = kItemInvalid;
		else
			getData()->inventoryItem = kItemNone;

		if (getEntities()->updateEntity(kEntityAugust, (CarIndex)params->param1, (EntityPosition)params->param2)) {
			getData()->inventoryItem = kItemNone;

			CALLBACK_ACTION();
		}
		break;

	case kAction1:
		params->param4 = 0;
		getData()->inventoryItem = kItemNone;

		getSound()->playSound(kEntityPlayer, "CAT1002");
		getSound()->playSound(kEntityAugust, getEvent(kEventAugustBringBriefcase) ? "AUG3103" : "AUG3100", SoundManager::kFlagInvalid, 15);
		break;

	case kActionExcuseMe:
		if (!getSound()->isBuffered(kEntityAugust))
			getSound()->excuseMe(kEntityAugust);
		break;

	case kActionDefault:
		if (getEntities()->updateEntity(kEntityAugust, (CarIndex)params->param1, (EntityPosition)params->param2)) {
			CALLBACK_ACTION();
			break;
		}

		if (params->param3) {
			params->param4 = 128;

			if (!getEvent(kEventAugustBringBriefcase))
				params->param4 = 147;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(43, August, chapter3Handler)
	error("August: callback function 43 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(44, August, function44)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->location = kLocationOutsideCompartment;

		setCallback(1);
		setup_updatePosition("122H", kCarRestaurant, 57);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (getEvent(kEventAugustMerchandise)) {
				setCallback(4);
				setup_function41(kCarGreenSleeping, kPosition_6470);
			} else {
				setCallback(2);
				setup_function17(kTime2043000);
			}
			break;

		case 2:
			if (!ENTITY_PARAM(0, 1)) {
				setCallback(4);
				setup_function41(kCarGreenSleeping, kPosition_6470);
			} else {
				setCallback(3);
				setup_savegame(kSavegameTypeEvent, kEventAugustMerchandise);
			}
			break;

		case 3:
			getAction()->playAnimation(kEventAugustMerchandise);
			if (getData()->car == kCarGreenSleeping && getEntities()->checkDistanceFromPosition(kEntityAugust, kPosition_6470, 500))
				getData()->entityPosition = kPosition_5970;

			getEntities()->updateEntity(kEntityAugust, kCarGreenSleeping, kPosition_6470);

			getEntities()->loadSceneFromEntityPosition(getData()->car,
			                                           (EntityPosition)(getData()->entityPosition + 750 * (getData()->direction == kDirectionUp ? -1 : 1)),
													   getData()->direction == kDirectionUp);

			setCallback(4);
			setup_function41(kCarGreenSleeping, kPosition_6470);
			break;

		case 4:
			setCallback(5);
			setup_function19(true, false);
			break;

		case 5:
			setup_function45();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(45, August, function45)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime2061000 && !params->param1) {
			params->param1 = 1;
			getData()->inventoryItem = kItemNone;

			setup_function46();
		}
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;
		getSound()->playSound(kEntityPlayer, "CAT1002");
		getSound()->playSound(kEntityAugust, "AUG3102", SoundManager::kFlagInvalid, 15);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityPlayer, kLocation2, kCursorNormal, kCursorNormal);
		getEntities()->drawSequenceLeft(kEntityAugust, "506A2");
		getData()->inventoryItem = kItem146;	// TODO which item is that?
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(46, August, function46)
	switch (savepoint.action) {
	default:
		TIME_CHECK_CALLBACK(August, kTime2088000, params->param1, 1, setup_function47);
		break;

	case kActionNone:
		break;

	case kActionDrawScene:
		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 43)) {
			setCallback(2);
			setup_draw("507B2");
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setup_function48();
			break;

		case 2:
			if (getEntities()->isPlayerPosition(kCarGreenSleeping, 43))
				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 34);

			getEntities()->clearSequences(kEntityAugust);
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(47, August, function47)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function20(true);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_function41(kCarGreenSleeping, kPosition_9460);
			break;

		case 2:
			getEntities()->clearSequences(kEntityAugust);
			setCallback(3);
			setup_updateFromTime(2700);
			break;

		case 3:
			setCallback(4);
			setup_function41(kCarGreenSleeping, kPosition_6470);
			break;

		case 4:
			setCallback(5);
			setup_function19(0, 0);
			break;

		case 5:
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(48, August, function48)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK(kTimeCityLinz, params->param1, setup_function49);
		break;

	case kActionKnock:
	case kActionOpenDoor:
		if (!getEvent(kEventAugustTalkCompartmentDoor) && !getEvent(kEventAugustTalkCompartmentDoorBlueRedingote)
		 && !getEvent(kEventAugustBringEgg) && !getEvent(kEventAugustBringBriefcase)) {

			if (savepoint.action == kActionKnock)
				getSound()->playSound(kEntityPlayer, "LIB012");

			setCallback(1);
			setup_savegame(kSavegameTypeEvent, kEventAugustTalkCompartmentDoor);
		}
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityAugust, kLocation1, kCursorHandKnock, kCursorHand);
		getData()->clothes = kClothes2;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventAugustTalkCompartmentDoor);
			getScenes()->processScene();

			setCallback(2);
			setup_function21(kTimeCityLinz);
			break;

		case 2:
			setup_function49();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(49, August, function49)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function20(false);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_updateEntity(kCarKronos, kPosition_9270);
			break;

		case 2:
			setup_function50();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(50, August, function50)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getEntities()->clearSequences(kEntityAugust);

		getData()->entityPosition = kPosition_6000;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarKronos;
		break;

	case kAction191668032:
		setup_function51();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(51, August, function51)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->car = kCarGreenSleeping;
		getData()->entityPosition = kPosition_850;
		getData()->location = kLocationOutsideCompartment;

		setCallback(1);
		setup_function42(kCarGreenSleeping, kPosition_5790, false);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityAugust, kEntityTatiana, kAction191668032);

			setCallback(2);
			setup_function42(kCarRedSleeping, kPosition_540, true);
			break;

		case 2:
			getEntities()->clearSequences(kEntityAugust);
			break;

		case 3:
			getEntities()->drawSequenceLeft(kEntityAugust, "BLANK");
			getSavePoints()->push(kEntityAugust, kEntityAnna, kAction123712592);
			break;
		}
		break;

	case kAction122288808:
		setup_function52();
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityAugust, "BLANK");
		break;

	case kAction169032608:
		setCallback(3);
		setup_function42(kCarRedSleeping, kPosition_3820, true);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(52, August, function52)
	error("August: callback function 52 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(53, August, function53)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_updateFromTime(2700);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_function20(false);
			break;

		case 2:
			setCallback(3);
			setup_updateEntity(kCarRestaurant, kPosition_850);
			break;

		case 3:
			setup_function54();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(54, August, function54)
	error("August: callback function 54 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(55, August, function55)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_callbackActionRestaurantOrSalon();
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->location = kLocationOutsideCompartment;

			setCallback(2);
			setup_updatePosition("105D3", kCarRestaurant, 57);
			break;

		case 2:
			setCallback(3);
			setup_updateEntity(kCarGreenSleeping, kPosition_6470);
			break;

		case 3:
			setCallback(4);
			setup_function19(1 /* true */, 0 /* false */);
			break;

		case 4:
			setup_function56();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(56, August, function56)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityPlayer, kLocation2, kCursorNormal, kCursorNormal);
		getEntities()->drawSequenceLeft(kEntityAugust, "507A3");
		break;

	case kActionDrawScene:
		if (!params->param1 && getEntities()->isPlayerPosition(kCarGreenSleeping, 43)) {
			setCallback(1);
			setup_draw("507B3");
		}
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			params->param1 = 1;
			getEntities()->drawSequenceLeft(kEntityAugust, "507A3");
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(57, August, chapter4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAugust);

		getData()->entityPosition = kPosition_6470;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothes2;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartment3, kEntityPlayer, kLocation2, kCursorNormal, kCursorNormal);

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(58, August, chapter4Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function20(false);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_updateEntity(kCarRestaurant, kPosition_850);
			break;

		case 2:
			setCallback(3);
			setup_callbackActionRestaurantOrSalon();
			break;

		case 3:
			getData()->entityPosition = kPosition_1540;
			getData()->location = kLocationOutsideCompartment;

			setCallback(4);
			setup_draw("803WS");
			break;

		case 4:
			getEntities()->drawSequenceRight(kEntityAugust, "010A3");
			if (getEntities()->isInSalon(kEntityPlayer))
				getEntities()->updateFrame(kEntityAugust);

			setCallback(5);
			setup_callSavepointNoDrawing(kEntityTables3, kAction136455232, "BOGUS");
			break;

		case 5:
			getData()->location = kLocationInsideCompartment;
			setup_function59();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(59, August, function59)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAugust, "010B3");
		getSavePoints()->push(kEntityAugust, kEntityPascale, kAction190605184);
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityAugust, "BLANK");
		break;

	case kAction123793792:
		setup_function60();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(60, August, function60)
	error("August: callback function 60 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(61, August, function61)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->location = kLocationOutsideCompartment;
		getEntities()->drawSequenceRight(kEntityAugust, "803FS");
		if (getEntities()->isInRestaurant(kEntityPlayer))
			getEntities()->updateFrame(kEntityAugust);

		setCallback(1);
		setup_callbackActionOnDirection();
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_updateEntity(kCarGreenSleeping, kPosition_6470);
			break;

		case 2:
			setCallback(3);
			setup_function19(false, false);
			break;

		case 3:
			setCallback(4);
			setup_function21((TimeValue)(getState()->time + 4500));
			break;

		case 4:
			setup_function62();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(62, August, function62)
	error("August: callback function 62 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(63, August, function63)
	error("August: callback function 63 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(64, August, function64)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param1)
			params->param1 = getState()->time + 1800;

		if (params->param1 >= getState()->time)
			break;

		if (getState()->time > kTime2430000 && getEntities()->isSomebodyInsideRestaurantOrSalon())  {
			getData()->location = kLocationOutsideCompartment;

			setCallback(1);
			setup_updatePosition("122J", kCarRestaurant, 57);
		}
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAugust, "122H");
		break;

	case kActionDrawScene:
		if (getEntities()->isPlayerPosition(kCarRestaurant, 57))
			getScenes()->loadSceneFromPosition(kCarRestaurant, 50);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_updateEntity(kCarGreenSleeping, kPosition_6470);
			break;

		case 2:
			setCallback(3);
			setup_enterExitCompartment2("696Dc", kObjectCompartment3);
			break;

		case 3:
			getEntities()->clearSequences(kEntityAugust);
			setup_function65();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(65, August, function65)
	switch (savepoint.action) {
	default:
		break;

	case kAction2:
		getSound()->playSound(kEntityAugust, "AUG1057");   // August snoring
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_6470;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		getEntities()->clearSequences(kEntityAugust);

		getObjects()->update(kObjectCompartment3, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		if (!getSound()->isBuffered(kEntityAugust))
			getSound()->playSound(kEntityAugust, "AUG1057");   // August snoring
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(66, August, chapter5)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAugust);

		getData()->entityPosition = kPosition_3969;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes2;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(67, August, chapter5Handler)
	if (savepoint.action == kActionProceedChapter5)
		setup_function68();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(68, August, function68)
	error("August: callback function 68 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(69, August, unhookCars)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		getSavePoints()->pushAll(kEntityAugust, kAction135800432);
		setup_nullfunction();
		break;

	case kActionDefault:
		getSound()->processEntries();
		if (getSound()->isBuffered("ARRIVE"))
			getSound()->removeFromQueue("ARRIVE");

		setCallback(1);
		setup_savegame(kSavegameTypeEvent, kEventAugustUnhookCarsBetrayal);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(getProgress().field_C ? kEventAugustUnhookCarsBetrayal : kEventAugustUnhookCars);
			getEntities()->clearSequences(kEntityAugust);
			getSound()->resetState();
			getSound()->playSound(kEntityPlayer, "MUS050");
			getScenes()->loadSceneFromPosition(kCarRestaurant, 85, 1);
			getSavePoints()->pushAll(kEntityAugust, kActionProceedChapter5);

			RESET_ENTITY_STATE(kEntityVerges, Verges, setup_function42)
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_NULL_FUNCTION(70, August)

} // End of namespace LastExpress
