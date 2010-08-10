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

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Verges::Verges(LastExpressEngine *engine) : Entity(engine, kEntityVerges) {
	ADD_CALLBACK_FUNCTION(Verges, reset);
	ADD_CALLBACK_FUNCTION(Verges, draw);
	ADD_CALLBACK_FUNCTION(Verges, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Verges, playSound);
	ADD_CALLBACK_FUNCTION(Verges, playSound16);
	ADD_CALLBACK_FUNCTION(Verges, callbackActionOnSomebodyStandingInRestaurantOrSalon);
	ADD_CALLBACK_FUNCTION(Verges, savegame);
	ADD_CALLBACK_FUNCTION(Verges, updateEntity);
	ADD_CALLBACK_FUNCTION(Verges, function9);
	ADD_CALLBACK_FUNCTION(Verges, function10);
	ADD_CALLBACK_FUNCTION(Verges, function11);
	ADD_CALLBACK_FUNCTION(Verges, function12);
	ADD_CALLBACK_FUNCTION(Verges, function13);
	ADD_CALLBACK_FUNCTION(Verges, updateFromTime);
	ADD_CALLBACK_FUNCTION(Verges, function15);
	ADD_CALLBACK_FUNCTION(Verges, function16);
	ADD_CALLBACK_FUNCTION(Verges, function17);
	ADD_CALLBACK_FUNCTION(Verges, chapter1);
	ADD_CALLBACK_FUNCTION(Verges, talkHarem);
	ADD_CALLBACK_FUNCTION(Verges, talkPassengerList);
	ADD_CALLBACK_FUNCTION(Verges, talkGendarmes);
	ADD_CALLBACK_FUNCTION(Verges, function22);
	ADD_CALLBACK_FUNCTION(Verges, function23);
	ADD_CALLBACK_FUNCTION(Verges, policeGettingOffTrain);
	ADD_CALLBACK_FUNCTION(Verges, function25);
	ADD_CALLBACK_FUNCTION(Verges, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Verges, chapter2);
	ADD_CALLBACK_FUNCTION(Verges, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Verges, chapter3);
	ADD_CALLBACK_FUNCTION(Verges, function30);
	ADD_CALLBACK_FUNCTION(Verges, function31);
	ADD_CALLBACK_FUNCTION(Verges, function32);
	ADD_CALLBACK_FUNCTION(Verges, function33);
	ADD_CALLBACK_FUNCTION(Verges, function34);
	ADD_CALLBACK_FUNCTION(Verges, function35);
	ADD_CALLBACK_FUNCTION(Verges, chapter4);
	ADD_CALLBACK_FUNCTION(Verges, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Verges, function38);
	ADD_CALLBACK_FUNCTION(Verges, chapter5);
	ADD_CALLBACK_FUNCTION(Verges, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Verges, function41);
	ADD_CALLBACK_FUNCTION(Verges, function42);
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Verges, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Verges, draw, 2)
	Entity::draw(savepoint, true);
}

/**
 * Process callback action when the entity direction is not kDirectionRight
 */
IMPLEMENT_FUNCTION(Verges, callbackActionOnDirection, 3)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getData()->direction != kDirectionRight)
			CALLBACK_ACTION()
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION()
 		break;

	case kActionExcuseMeCath:
		if (!params->param1) {
			getSound()->excuseMe(kEntityVerges);
			params->param1 = 1;
		}
		break;
	}
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Verges, playSound, 4)
	Entity::playSound(savepoint);
}

/**
 * Plays sound
 *
 * @param savepoint The savepoint
 *                    - sound filename
 */
IMPLEMENT_FUNCTION_NOSETUP(Verges, playSound16, 5)
	Entity::playSound(savepoint, false, SoundManager::kFlagDefault);
}

/**
 * Process callback action when somebody is standing in the restaurant or salon.
 */
IMPLEMENT_FUNCTION(Verges, callbackActionOnSomebodyStandingInRestaurantOrSalon, 6)
	Entity::callbackActionOnSomebodyStandingInRestaurantOrSalon(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Verges, savegame, 7)
	Entity::savegame(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Verges, updateEntity, 8)
	if (savepoint.action == kActionExcuseMeCath) {
		if (!getSound()->isBuffered(kEntityVerges))
			getSound()->playSound(kEntityPlayer, "TRA1113", getSound()->getSoundFlag(kEntityVerges));

		return;
	}

	Entity::updateEntity(savepoint, true);
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - Sound name
IMPLEMENT_FUNCTION_S(Verges, function9, 9)
switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObject104, kEntityPlayer, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityPlayer, kLocationNone, kCursorNormal, kCursorHand);

		if (getEntities()->isInBaggageCar(kEntityPlayer) || getEntities()->isInKitchen(kEntityPlayer)) {
			getAction()->playAnimation(getEntities()->isInBaggageCar(kEntityPlayer) ? kEventVergesBagageCarOffLimits : kEventVergesCanIHelpYou);
			getSound()->playSound(kEntityPlayer, "BUMP");
			getScenes()->loadSceneFromPosition(kCarRestaurant, 65);
		}

		getScenes()->loadSceneFromItemPosition(kItem9);
		getData()->car = kCarRestaurant;
		getData()->entityPosition = kPosition_5900;

		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_callbackActionOnSomebodyStandingInRestaurantOrSalon));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->entityPosition = kPosition_5800;
			getData()->posture = kPostureStanding;
			getSound()->playSound(kEntityVerges, (char *)&params->seq1);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Verges, setup_draw), "813DD");
			break;

		case 2:
			if (!getSound()->isBuffered(kEntityVerges))
				getSound()->playSound(kEntityVerges, (char *)&params->seq1);

			getEntities()->drawSequenceRight(kEntityVerges, "813DS");

			if (getEntities()->isInRestaurant(kEntityPlayer))
				getEntities()->updateFrame(kEntityVerges);

			setCallback(3);
			call(new ENTITY_SETUP(Verges, setup_callbackActionOnDirection));
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP_IISI(Verges, setup_function10), kCarGreenSleeping, kPosition_540, (char *)&params->seq1);
			break;

		case 4:
			getEntities()->clearSequences(kEntityVerges);

			setCallback(5);
			call(new ENTITY_SETUP(Verges, setup_updateFromTime), 225);
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 6:
			CALLBACK_ACTION()
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - CarIndex
//  - EntityPosition
//  - Sound name
IMPLEMENT_FUNCTION_IIS(Verges, function10, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param7) {
			if (!getSound()->isBuffered(kEntityVerges)) {
				getSound()->playSound(kEntityVerges, (char *)&params->seq);
				params->param7 = 1;
			}
		}

		if (getEntities()->updateEntity(kEntityVerges, (CarIndex)params->param1, (EntityPosition)params->param2)) {
			CALLBACK_ACTION()
			break;
		}

		if (params->param6) {
			UPDATE_PARAM(params->param8, getState()->timeTicks, 75);

			getSound()->playSound(kEntityVerges, (char *)&params->seq);

			params->param6 = 0;
			params->param8 = 0;
		}
		break;

	case kAction2:
		params->param6 = 1;
		break;

	case kActionDefault:
		if (!getSound()->isBuffered(kEntityVerges)) {
			getSound()->playSound(kEntityVerges, params->seq);
			params->param7 = 1;
		}

		if (getEntities()->updateEntity(kEntityVerges, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION()
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function11, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarRestaurant, kPosition_540);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_callbackActionOnSomebodyStandingInRestaurantOrSalon));
			break;

		case 2:
			getData()->entityPosition = kPosition_1540;
			getData()->posture = kPostureStanding;

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Verges, setup_draw), "813US");
			break;

		case 3:
			getEntities()->drawSequenceRight(kEntityVerges, "813UD");

			if (getEntities()->isInSalon(kEntityPlayer))
				getEntities()->updateFrame(kEntityVerges);

			setCallback(4);
			call(new ENTITY_SETUP(Verges, setup_callbackActionOnDirection));
			break;

		case 4:
			getEntities()->clearSequences(kEntityVerges);

			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function12, 12)
	error("Verges: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_I(Verges, function13, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_savegame), kSavegameType2, kEventVergesSuitcase);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			if (getEvent(kEventVergesSuitcase) || getEvent(kEventVergesSuitcaseNight) || getEvent(kEventVergesSuitcaseOtherEntry) || getEvent(kEventVergesSuitcaseNightOtherEntry))
				params->param2 = 1;

			if (isDay() && getProgress().chapter != kChapter1)
				params->param2 = 1;

			if (params->param1) {
				if (isDay())
					getAction()->playAnimation(params->param2 ? kEventVergesSuitcaseOtherEntryStart : kEventVergesSuitcaseOtherEntry);
				else
					getAction()->playAnimation(params->param2 ? kEventVergesSuitcaseNightOtherEntryStart : kEventVergesSuitcaseNightOtherEntry);
			} else {
				if (isDay())
					getAction()->playAnimation(params->param2 ? kEventVergesSuitcaseStart : kEventVergesSuitcase);
				else
					getAction()->playAnimation(params->param2 ? kEventVergesSuitcaseNightStart : kEventVergesSuitcaseNight);
			}

			getEntities()->clearSequences(kEntityVerges);
			getScenes()->loadSceneFromPosition(kCarBaggage, 91);

			CALLBACK_ACTION()
		}
		break;
	}
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_I(Verges, updateFromTime, 14)
	Entity::updateFromTime(savepoint);
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - EntityIndex
//  - Sound name
IMPLEMENT_FUNCTION_IS(Verges, function15, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param5 && params->param6) {
			getSavePoints()->push(kEntityVerges, (EntityIndex)params->param1, kAction125499160);

			if (!getEntities()->isPlayerPosition(kCarGreenSleeping, 2) && !getEntities()->isPlayerPosition(kCarRedSleeping, 2))
				getData()->entityPosition = kPosition_2088;

			CALLBACK_ACTION()
		}
		break;

	case kAction2:
		params->param5 = 1;
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityVerges, "620F");
		getSavePoints()->push(kEntityVerges, (EntityIndex)params->param1, kAction171394341);
		break;

	case kAction155853632:
		params->param6 = 1;
		break;

	case kAction202558662:
		getEntities()->drawSequenceLeft(kEntityVerges, "620E");
		getSound()->playSound(kEntityVerges, (char *)&params->seq);
		break;
	}
}

IMPLEMENT_FUNCTION_ISS(Verges, function16, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (CURRENT_PARAMS(1, 1) && params->param8) {
			getSavePoints()->push(kEntityVerges, (EntityIndex)params->param1, kAction125499160);

			if (!getEntities()->isPlayerPosition(kCarGreenSleeping, 2) && !getEntities()->isPlayerPosition(kCarRedSleeping, 2))
				getData()->entityPosition = kPosition_2088;

			CALLBACK_ACTION()
		}
		break;

	case kAction2:
		CURRENT_PARAMS(1, 1)++;

		if (CURRENT_PARAMS(1, 1) == 1)
			getSound()->playSound(kEntityVerges, (char *)&params->seq2);
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityVerges, "620F");
		getSavePoints()->push(kEntityVerges, (EntityIndex)params->param1, kAction171394341);
		break;

	case kAction155853632:
		params->param8 = 1;
		break;

	case kAction202558662:
		getEntities()->drawSequenceLeft(kEntityVerges, "620E");
		getSound()->playSound(kEntityVerges, (char *)&params->seq1);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Verges, function17, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function12));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarGreenSleeping, kPosition_2000);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kEntityMertens, "TRA1291");
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 4:
			ENTITY_PARAM(0, 3) = 0;
			CALLBACK_ACTION()
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, chapter1, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityVerges, kActionDeliverMessageToTyler, 0);
		getSavePoints()->addData(kEntityVerges, kAction226031488, 1);
		getSavePoints()->addData(kEntityVerges, kAction339669520, 1);
		getSavePoints()->addData(kEntityVerges, kAction167854368, 4);
		getSavePoints()->addData(kEntityVerges, kAction158617345, 2);
		getSavePoints()->addData(kEntityVerges, kAction168255788, 3);
		getSavePoints()->addData(kEntityVerges, kAction201431954, 5);
		getSavePoints()->addData(kEntityVerges, kAction168187490, 6);

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		getData()->entityPosition = kPosition_5000;
		getData()->posture = kPostureStanding;
		getData()->car = kCarBaggage;
		break;
	}
}

IMPLEMENT_FUNCTION_NOSETUP(Verges, talkHarem, 19)
	talk(savepoint, "TRA1202", "TRA1201");
}

IMPLEMENT_FUNCTION(Verges, talkPassengerList, 20)
	talk(savepoint, "TRA1205", "TRA1206");
}

IMPLEMENT_FUNCTION(Verges, talkGendarmes, 21)
	talk(savepoint, "TRA1250", "TRA1251");
}

IMPLEMENT_FUNCTION(Verges, function22, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function12));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarGreenSleeping, kPosition_2000);
			break;

		case 2:
			if (getEvent(kEventMertensAskTylerCompartment) || getEvent(kEventMertensAskTylerCompartmentD) || getEvent(kEventMertensAugustWaiting)) {
				setCallback(3);
				call(new ENTITY_SETUP_ISSI(Verges, setup_function16), kCarGreenSleeping, "TRA1200", "TRA1201");
			} else {
				setCallback(4);
				call(new ENTITY_SETUP_ISSI(Verges, setup_function16), kCarGreenSleeping, "TRA1200A", "TRA1201");
			}
			break;

		case 3:
		case 4:
			getSavePoints()->push(kEntityVerges, kEntityMertens, kAction169633856);

			setCallback(5);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 5:
			CALLBACK_ACTION()
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getScenes()->loadSceneFromItemPosition(kItem9);

		getData()->entityPosition = kPosition_8200;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		break;

	case kAction191477936:
		getData()->entityPosition = kPosition_8200;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRedSleeping;

		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function11));
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, policeGettingOffTrain, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->checkFields9(kEntityVerges, kEntityPlayer, 1000) && !getEntityData(kEntityPlayer)->posture) {
			setCallback(1);
			call(new ENTITY_SETUP(Verges, setup_savegame), kSavegameType2, kEventGendarmesArrestation);
		}
		break;

	case kAction2:
		CALLBACK_ACTION()
		break;

	case kActionDefault:
		getSound()->playSound(kEntityVerges, "POL1101", SoundManager::kFlagDefault);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getSound()->processEntry(kEntityVerges);
			getAction()->playAnimation(kEventGendarmesArrestation);
			getLogic()->gameOver(kInitTypeIndex, 1, kSceneGameOverPolice1, true);
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function25, 25)
	error("Verges: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter1Handler, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (ENTITY_PARAM(0, 6)) {
			params->param1 = 1;
			params->param2 = 1;
			params->param3 = 1;
			params->param4 = 1;
			params->param5 = 1;
			params->param6 = 1;

			ENTITY_PARAM(0, 6) = 0;
		}

		if (ENTITY_PARAM(0, 2)) {
			setCallback(1);
			call(new ENTITY_SETUP(Verges, setup_function23));
			break;
		}

label_callback1:
		if (getEntities()->isInBaggageCarEntrance(kEntityPlayer)) {
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_function13), 0);
			break;
		}

label_callback2:
		if (ENTITY_PARAM(0, 7)) {
			setCallback(3);
			call(new ENTITY_SETUP(Verges, setup_function25));
			break;
		}

label_callback3:
		if (params->param6)
			goto label_callback12;

		TIME_CHECK_CALLBACK_S(Verges, kTimeChapter1, params->param7, 4, setup_function9, "TRA1001");

label_callback4:
		TIME_CHECK_CALLBACK(Verges, kTime1089000, params->param8, 5, setup_function12);

		params->param8 = 1;

		if (!params->param5) {
			setCallback(5);
			call(new ENTITY_SETUP(Verges, setup_function12));
			break;
		}

label_callback8:
		TIME_CHECK_CALLBACK_S(Verges, kTime1107000, CURRENT_PARAMS(1, 1), 9, setup_function9, "TRA1001A");

label_callback9:
		TIME_CHECK_CALLBACK_S(Verges, kTime1134000, CURRENT_PARAMS(1, 2), 10, setup_function9, "TRA1002");

label_callback10:
		TIME_CHECK_CALLBACK_S(Verges, kTime1165500, CURRENT_PARAMS(1, 3), 11, setup_function9, "TRA1003");

label_callback11:
		TIME_CHECK_CALLBACK_S(Verges, kTime1225800, CURRENT_PARAMS(1, 4), 12, setup_function9, "TRA1004");

label_callback12:
		if (ENTITY_PARAM(0, 5) && !params->param2) {
			setCallback(13);
			call(new ENTITY_SETUP(Verges, setup_talkGendarmes));
			break;
		}

label_callback13:
		if (getInventory()->hasItem(kItemPassengerList) && !params->param4 && (getState()->time < kTime1134000 || getState()->time > kTime1156500)) {
			setCallback(14);
			call(new ENTITY_SETUP(Verges, setup_talkPassengerList));
			break;
		}

label_callback14:
		if (ENTITY_PARAM(0, 3) && !params->param4 && (getState()->time < kTime1134000 || getState()->time > kTime1156500)) {
			setCallback(15);
			call(new ENTITY_SETUP(Verges, setup_function17));
			break;
		}

label_callback15:
		if (ENTITY_PARAM(0, 1) && !params->param5) {
			if (getState()->time < kTime1134000 || getState()->time > kTime1156500) {
				setCallback(16);
				call(new ENTITY_SETUP(Verges, setup_function22));
			}
		}
		break;

	case kActionOpenDoor:
		setCallback(17);
		call(new ENTITY_SETUP(Verges, setup_function13), savepoint.param.intValue < 106 ? true : false);
		break;

	case kActionDefault:
		getData()->car = kCarBaggage;
		getData()->entityPosition = kPosition_5000;
		getData()->posture = kPostureStanding;

		getEntities()->clearSequences(kEntityVerges);
		getInventory()->setLocationAndProcess(kItem9, kLocation1);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			goto label_callback1;

		case 2:
			goto label_callback2;

		case 3:
			goto label_callback3;

		case 4:
			goto label_callback4;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarGreenSleeping, kPosition_2000);
			break;

		case 6:
			setCallback(7);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kCarGreenSleeping, "TRA1202");
			break;

		case 7:
			setCallback(8);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 8:
			goto label_callback8;

		case 9:
			goto label_callback9;

		case 10:
			goto label_callback10;

		case 11:
			goto label_callback11;

		case 12:
			goto label_callback12;

		case 13:
			params->param2 = 1;
			goto label_callback13;

		case 14:
			params->param3 = 1;
			goto label_callback14;

		case 15:
			params->param4 = 1;
			goto label_callback15;

		case 16:
			params->param5 = 1;
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, chapter2, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVerges);

		getData()->entityPosition = kPosition_5000;
		getData()->posture = kPostureStanding;
		getData()->car = kCarBaggage;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		ENTITY_PARAM(0, 3) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, chapter2Handler, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->isInBaggageCarEntrance(kEntityPlayer)) {
			setCallback(1);
			call(new ENTITY_SETUP(Verges, setup_function13), false);
		}

label_callback_1:
		TIME_CHECK_CALLBACK_S(Verges, kTime1818900, params->param1, 2, setup_function9, "Tra2177");

label_callback_2:
		if (params->param2 == kTimeInvalid || !getState()->time)
			goto label_callback_6;

		if (getState()->time > kTime1836000) {
			params->param2 = kTimeInvalid;
			setCallback(3);
			call(new ENTITY_SETUP(Verges, setup_function12));
			break;
		}

		if (!getEntities()->isPlayerInCar(kCarRedSleeping) || !params->param2) {
			params->param2 = getState()->time;

			if (!params->param2) {
				setCallback(3);
				call(new ENTITY_SETUP(Verges, setup_function12));
				break;
			}
		}

		if (params->param2 >= (int)getState()->time) {
label_callback_6:

			if (ENTITY_PARAM(0, 3)) {
				setCallback(7);
				call(new ENTITY_SETUP(Verges, setup_function17));
			}

			break;
		}

		params->param2 = kTimeInvalid;
		setCallback(3);
		call(new ENTITY_SETUP(Verges, setup_function12));
		break;

	case kActionOpenDoor:
		setCallback(8);
		call(new ENTITY_SETUP(Verges, setup_function13), savepoint.param.intValue < 106);
		break;

	case kActionDefault:
		getInventory()->setLocationAndProcess(kItem9, kLocation1);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			goto label_callback_1;

		case 2:
			goto label_callback_2;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarRedSleeping, kPosition_2000);
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kEntityCoudert, "TRA2100");
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 6:
			goto label_callback_6;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, chapter3, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function23();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVerges);

		getData()->entityPosition = kPosition_540;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 4) = 0;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - sequence name
IMPLEMENT_FUNCTION_S(Verges, function30, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function12));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarRedSleeping, kPosition_2000);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kEntityCoudert, (char *)&params->seq1);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 4:
			CALLBACK_ACTION()
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function31, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function12));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarRedSleeping, kPosition_2000);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kEntityCoudert, "TRA3015");
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 4:
			getProgress().field_48 = 1;
			ENTITY_PARAM(0, 4) = 0;

			CALLBACK_ACTION()
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function32, 32)
	error("Verges: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function33, 33)
	error("Verges: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function34, 34)
	error("Verges: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function35, 35)
	error("Verges: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter4, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVerges);

		getData()->entityPosition = kPosition_5000;
		getData()->posture = kPostureStanding;
		getData()->car = kCarBaggage;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 6) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, chapter4Handler, 37)
	error("Verges: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function38, 38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObject104, kEntityPlayer, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityPlayer, kLocationNone, kCursorNormal, kCursorHand);
		getScenes()->loadSceneFromItemPosition(kItem9);
		getEntities()->clearSequences(kEntityVerges);

		getData()->entityPosition = kPosition_6469;
		getData()->posture = kPostureStanding;
		getData()->car = kCarGreenSleeping;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->clearSequences(kEntityVerges);
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_updateFromTime), 1800);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 3:
			setup_chapter4Handler();
			break;
		}
		break;

	case kAction125233040:
		getData()->entityPosition = kPosition_5790;

		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarGreenSleeping, kPosition_540);
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, chapter5, 39)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVerges);

		getData()->entityPosition = kPosition_3650;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityPlayer, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityPlayer, kLocationNone, kCursorNormal, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, chapter5Handler, 40)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->isInSalon(kEntityPlayer) && !getSound()->isBuffered(kEntityVerges))
			getSound()->playSound(kEntityVerges, "WAT5000");
		break;

	case kActionOpenDoor:
		if (getSound()->isBuffered(kEntityVerges))
			getSound()->processEntry(kEntityVerges);

		if (getSound()->isBuffered("MUS050"))
			getSound()->processEntry("MUS050");

		getObjects()->update(kObject65, kEntityPlayer, kLocationNone, kCursorNormal, kCursorForward);

		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_savegame), kSavegameType2, kEventCathFreePassengers);
		break;

	case kActionDefault:
		getScenes()->loadSceneFromItemPosition(kItem9);
		getObjects()->update(kObject65, kEntityVerges, kLocation1, kCursorNormal, kCursorForward);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCathFreePassengers);
			getSavePoints()->pushAll(kEntityVerges, kActionProceedChapter5);
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 40);
			setup_function41();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function41, 41)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->updateLocation2(kObjectRestaurantCar, kLocation3);
		getData()->car = kCarRedSleeping;
		getData()->entityPosition = kPosition_9460;
		getData()->posture = kPostureSitting;

		setCallback(1);
		call(new ENTITY_SETUP_IISI(Verges, setup_function10), kCarRedSleeping, kPosition_2000, "Tra5001");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceLeft(kEntityVerges, "620E");
			// Fallback to next case

		case 2:
			if (getSound()->isBuffered(kEntityVerges)) {
				setCallback(2);
				call(new ENTITY_SETUP(Verges, setup_updateFromTime), 225);
			} else {
				setCallback(3);
				call(new ENTITY_SETUP_SIIS(Verges, setup_playSound), "Con5001");
			}
			break;

		case 3:
			getSavePoints()->push(kEntityVerges, kEntityCoudert, kAction155991520);

			setCallback(4);
			call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarBaggageRear, kPosition_9460);
			break;

		case 4:
			setup_function42();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function42, 42)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityVerges);
}

void Verges::talk(const SavePoint &savepoint, const char *sound1, const char *sound2) {
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function12));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarRedSleeping, kPosition_2000);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kEntityCoudert, sound1);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Verges, setup_updateEntity), kCarGreenSleeping, kPosition_2000);
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kEntityMertens, sound2);
			break;

		case 5:
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 6:
			CALLBACK_ACTION()
			break;
		}
		break;
	}
}

} // End of namespace LastExpress
