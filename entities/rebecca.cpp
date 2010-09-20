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

#include "lastexpress/entities/rebecca.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Rebecca::Rebecca(LastExpressEngine *engine) : Entity(engine, kEntityRebecca) {
	ADD_CALLBACK_FUNCTION(Rebecca, reset);
	ADD_CALLBACK_FUNCTION(Rebecca, updateFromTime);
	ADD_CALLBACK_FUNCTION(Rebecca, playSound);
	ADD_CALLBACK_FUNCTION(Rebecca, playSound16);
	ADD_CALLBACK_FUNCTION(Rebecca, callSavepoint);
	ADD_CALLBACK_FUNCTION(Rebecca, draw);
	ADD_CALLBACK_FUNCTION(Rebecca, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Rebecca, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(Rebecca, enterExitCompartment3);
	ADD_CALLBACK_FUNCTION(Rebecca, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Rebecca, callbackActionRestaurantOrSalon);
	ADD_CALLBACK_FUNCTION(Rebecca, updateEntity);
	ADD_CALLBACK_FUNCTION(Rebecca, updatePosition);
	ADD_CALLBACK_FUNCTION(Rebecca, draw2);
	ADD_CALLBACK_FUNCTION(Rebecca, function15);
	ADD_CALLBACK_FUNCTION(Rebecca, function16);
	ADD_CALLBACK_FUNCTION(Rebecca, function17);
	ADD_CALLBACK_FUNCTION(Rebecca, function18);
	ADD_CALLBACK_FUNCTION(Rebecca, function19);
	ADD_CALLBACK_FUNCTION(Rebecca, function20);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter1);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Rebecca, function23);
	ADD_CALLBACK_FUNCTION(Rebecca, function24);
	ADD_CALLBACK_FUNCTION(Rebecca, function25);
	ADD_CALLBACK_FUNCTION(Rebecca, function26);
	ADD_CALLBACK_FUNCTION(Rebecca, function27);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter2);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Rebecca, function30);
	ADD_CALLBACK_FUNCTION(Rebecca, function31);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter3);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Rebecca, function34);
	ADD_CALLBACK_FUNCTION(Rebecca, function35);
	ADD_CALLBACK_FUNCTION(Rebecca, function36);
	ADD_CALLBACK_FUNCTION(Rebecca, function37);
	ADD_CALLBACK_FUNCTION(Rebecca, function38);
	ADD_CALLBACK_FUNCTION(Rebecca, function39);
	ADD_CALLBACK_FUNCTION(Rebecca, function40);
	ADD_CALLBACK_FUNCTION(Rebecca, function41);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter4);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Rebecca, function44);
	ADD_CALLBACK_FUNCTION(Rebecca, function45);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter5);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Rebecca, function48);
	ADD_NULL_FUNCTION();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(1, Rebecca, reset)
	Entity::reset(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(2, Rebecca, updateFromTime, uint32)
	Entity::updateFromTime(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(3, Rebecca, playSound)
	Entity::playSound(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(4, Rebecca, playSound16)
	Entity::playSound(savepoint, false, getSound()->getSoundFlag(kEntityCoudert));
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SIIS(5, Rebecca, callSavepoint, EntityIndex, ActionIndex)
	Entity::callSavepoint(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(6, Rebecca, draw)
	Entity::draw(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(7, Rebecca, enterExitCompartment, ObjectIndex)
	Entity::enterExitCompartment(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(8, Rebecca, enterExitCompartment2, ObjectIndex)
	Entity::enterExitCompartment(savepoint, kPosition_4840, kPosition_4455, kCarRedSleeping, kObjectCompartmentE, true);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(9, Rebecca, enterExitCompartment3, ObjectIndex)
	Entity::enterExitCompartment(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(10, Rebecca, callbackActionOnDirection)
	Entity::callbackActionOnDirection(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(11, Rebecca, callbackActionRestaurantOrSalon)
	Entity::callbackActionRestaurantOrSalon(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(12, Rebecca, updateEntity, CarIndex, EntityPosition)
	Entity::updateEntity(savepoint, true);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SII(13, Rebecca, updatePosition, CarIndex, Position)
	Entity::updatePosition(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SSI(14, Rebecca, draw2, EntityIndex)
	Entity::draw2(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(15, Rebecca, function15)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (getEntities()->isOutsideAnnaWindow())
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 49);

		setCallback(1);
		setup_enterExitCompartment2("624Ae", kObjectCompartmentE);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getObjects()->update(kObjectOutsideBetweenCompartments, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);
			getData()->location = kLocationInsideCompartment;
			getEntities()->clearSequences(kEntityRebecca);

			CALLBACK_ACTION();
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(16, Rebecca, function16, bool)
	error("Rebecca: callback function 16 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(17, Rebecca, function17, bool)
	error("Rebecca: callback function 17 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(18, Rebecca, function18)
	error("Rebecca: callback function 18 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(19, Rebecca, function19)
	error("Rebecca: callback function 19 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(20, Rebecca, function20, TimeValue)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1 < getState()->time && !params->param5) {
			params->param5 = 1;

			getObjects()->update(kObjectCompartmentE, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject52, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);

			CALLBACK_ACTION();
			break;
		}

		if (!params->param2) {
			params->param6 = 0;
			goto label_process;
		}

		UPDATE_PARAM_GOTO(params->param6, getState()->timeTicks, 75, label_process);

		params->param2 = 0;
		params->param3 = 1;
		getObjects()->update(kObjectCompartmentE, kEntityRebecca, kLocation1, kCursorNormal, kCursorNormal);
		getObjects()->update(kObject52, kEntityRebecca, kLocation1, kCursorNormal, kCursorNormal);
		params->param6 = 0;

label_process:
		if (getProgress().chapter == kChapter1 && !ENTITY_PARAM(0, 3)) {
			if (params->param7 != kTimeInvalid && getState()->time > kTime1174500) {
				if (getState()->time <= kTime1183500) {
					if (!getEntities()->isDistanceBetweenEntities(kEntityRebecca, kEntityPlayer, 2000) || getSound()->isBuffered("CON1210") || !params->param7)
						params->param7 = getState()->time;

					if (params->param7 >= getState()->time)
						goto label_callback;
				}

				params->param7 = kTimeInvalid;
				ENTITY_PARAM(0, 3) = 1;

				getObjects()->update(kObjectCompartmentE, kEntityRebecca, kLocation1, kCursorNormal, kCursorNormal);
				getObjects()->update(kObject52, kEntityRebecca, kLocation1, kCursorNormal, kCursorNormal);

				setCallback(1);
				setup_playSound("REB1205");
				break;
			}
			goto label_callback;
		}

		if (getProgress().chapter == kChapter3 && !ENTITY_PARAM(0, 4) && params->param8 != kTimeInvalid && getState()->time > kTime2097000) {
			if (getState()->time <= kTime2106000) {
				if (!getEntities()->isDistanceBetweenEntities(kEntityRebecca, kEntityPlayer, 1000) || !params->param8)
					params->param8 = getState()->time;

				if (params->param8 >= getState()->time)
					goto label_callback;
			}

			params->param8 = kTimeInvalid;
			ENTITY_PARAM(0, 4) = 1;

			getObjects()->update(kObjectCompartmentE, kEntityRebecca, kLocation1, kCursorNormal, kCursorNormal);
			getObjects()->update(kObject52, kEntityRebecca, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(2);
			setup_playSound("REB3010");
			break;
		}

label_callback:
		if (ENTITY_PARAM(0, 2) && getEntities()->isDistanceBetweenEntities(kEntityRebecca, kEntityPlayer, 1000)) {
			getObjects()->update(kObjectCompartmentE, kEntityRebecca, kLocation1, kCursorNormal, kCursorNormal);
			getObjects()->update(kObject52, kEntityRebecca, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(3);
			setup_playSound("REB1040");
		}
		break;

	case kActionKnock:
	case kActionOpenDoor:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentE, kEntityRebecca, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityRebecca, kLocation1, kCursorHandKnock, kCursorHand);

		break;

	case kActionDrawScene:
		if (params->param3 || params->param2) {
			getObjects()->update(kObjectCompartmentE, kEntityRebecca, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject52, kEntityRebecca, kLocation1, kCursorHandKnock, kCursorHand);

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
		case 3:
			getObjects()->update(kObjectCompartmentE, kEntityRebecca, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject52, kEntityRebecca, kLocation1, kCursorHandKnock, kCursorHand);

			if (getCallback() != 2)
				ENTITY_PARAM(0, 2) = 0;

			if (getCallback() != 3)
				goto label_callback;
			break;

		case 4:
		case 5:
			if (rnd(2)) {
				setCallback(6);
				setup_playSound("REB1039");
			} else {
				setCallback(7);
				setup_playSound(rnd(2) ? "SOP1039" : "SOP1039A");
			}
			break;

		case 6:
		case 7:
			params->param4 = (getCallback() == 6 ? 0 : 1);
			getObjects()->update(kObjectCompartmentE, kEntityRebecca, kLocation1, kCursorTalk, kCursorNormal);
			getObjects()->update(kObject52, kEntityRebecca, kLocation1, kCursorTalk, kCursorNormal);
			params->param2 = 1;
			break;

		case 8:
		case 9:
		case 10:
		case 11:
			params->param2 = 0;
			params->param3 = 1;
			break;

		case 12:
			setCallback(13);
			setup_playSound16("JAC1012B");
			break;

		case 13:
			getObjects()->update(kObjectCompartmentE, kEntityRebecca, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject52, kEntityRebecca, kLocation1, kCursorHandKnock, kCursorHand);
			break;
		}
		break;

	case kAction254915200:
		getObjects()->update(kObjectCompartmentE, kEntityRebecca, kLocation1, kCursorNormal, kCursorNormal);
		getObjects()->update(kObject52, kEntityRebecca, kLocation1, kCursorNormal, kCursorNormal);

		setCallback(12);
		setup_playSound("REB1039A");
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(21, Rebecca, chapter1)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityRebecca, kAction224253538, 0);

		getObjects()->update(kObjectCompartmentE, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectOutsideBetweenCompartments, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getObjects()->updateLocation2(kObject110, kLocation1);

		getData()->entityPosition = kPosition_2830;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;

		ENTITY_PARAM(0, 2) = 1;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(22, Rebecca, chapter1Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_PLAYSOUND(Rebecca, kTime1084500, params->param3, 1, "REB1015");

		if (params->param4 == kTimeInvalid)
			goto label_callback_4;

		if (getState()->time > kTime1080000)
			goto label_playConversation;

		if (!getEntities()->isInSalon(kEntityPlayer) || !params->param4)
			params->param4 = getState()->time + 150;

		if (params->param4 >= getState()->time) {
label_callback_4:
			if (params->param1) {
				bool checkParam5 = false;
				if (!params->param5) {
					params->param5 = getState()->time + 900;
					checkParam5 = true;
				}

				if (checkParam5 || params->param5 < getState()->time) {
					if (getEntities()->isInSalon(kEntityPlayer)) {
						setCallback(5);
						setup_playSound("REB1013");
						break;
					}
				}
			}

label_callback_5:
			if (params->param2) {
				UPDATE_PARAM(params->param6, getState()->timeTicks, 90);
				getScenes()->loadSceneFromPosition(kCarRestaurant, 55);
			} else {
				params->param6 = 0;
			}
		} else {
label_playConversation:
			params->param4 = kTimeInvalid;

			if (getEntities()->isInSalon(kEntityPlayer))
				getProgress().field_B8 = 1;

			setCallback(4);
			setup_playSound("REB1012");
		}
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityRebecca, "107B");
		break;

	case kActionDrawScene:
		params->param2 = (getEntities()->isPlayerPosition(kCarRestaurant, 57) ? 1 : 0);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_updatePosition("107C", kCarRestaurant, 57);
			break;

		case 2:
			setCallback(3);
			setup_function18();
			break;

		case 3:
			setup_function23();
			break;

		case 4:
			params->param1 = 1;
			goto label_callback_4;

		case 5:
			getProgress().field_B4 = 1;
			params->param1 = 0;
			goto label_callback_5;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(23, Rebecca, function23)
	error("Rebecca: callback function 23 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(24, Rebecca, function24)
	error("Rebecca: callback function 24 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(25, Rebecca, function25)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function20(kTime1184400);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_function17(0);
			break;

		case 2:
			setup_function26();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(26, Rebecca, function26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK_SII(Rebecca, kTime1224000, params->param2, 1, setup_updatePosition, "118H", kCarRestaurant, 52);

		if (params->param1) {
			UPDATE_PARAM(params->param3, getState()->timeTicks, 90);

			getScenes()->loadSceneFromPosition(kCarRestaurant, 51);
		}
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityRebecca, "118D");
		break;

	case kActionDrawScene:
		params->param1 = getEntities()->isPlayerPosition(kCarRestaurant, 52);
		params->param3 = 0;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_function18();
			break;

		case 2:
			setup_function27();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(27, Rebecca, function27)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_4840;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentE, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getEntities()->clearSequences(kEntityRebecca);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(28, Rebecca, chapter2)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityRebecca);

		getData()->entityPosition = kPosition_4840;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentE, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getObjects()->updateLocation2(kObject110, kLocation2);

		ENTITY_PARAM(0, 2) = 1;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(29, Rebecca, chapter2Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function20(kTime1764000);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_function17(0);
			break;

		case 2:
			setup_function30();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(30, Rebecca, function30)
	error("Rebecca: callback function 30 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(31, Rebecca, function31)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_updateFromTime(900);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_enterExitCompartment("623CE", kObjectCompartmentE);
			break;

		case 2:
			getObjects()->update(kObjectCompartmentE, kEntityPlayer, kLocation2, kCursorNormal, kCursorNormal);
			getEntities()->drawSequenceLeft(kEntityRebecca, "504");
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(32, Rebecca, chapter3)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityRebecca);

		getData()->entityPosition = kPosition_4840;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(33, Rebecca, chapter3Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function20(kTime2016000);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function34();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(34, Rebecca, function34)
	error("Rebecca: callback function 34 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(35, Rebecca, function35)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function20(kTime2070000);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function36();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(36, Rebecca, function36)
	error("Rebecca: callback function 36 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(37, Rebecca, function37)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function20(kTime2110500);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function38();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(38, Rebecca, function38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->location = kLocationOutsideCompartment;

		setCallback(1);
		setup_enterExitCompartment3("624Be", kObjectCompartmentE);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentE, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
            getSavePoints()->push(kEntityRebecca, kEntitySophie, kAction259921280);

			setCallback(2);
			setup_updateEntity(kCarKronos, kPosition_9270);
			break;

		case 2:
			getSavePoints()->push(kEntityRebecca, kEntitySophie, kAction123668192);
			setup_function39();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(39, Rebecca, function39)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityRebecca);

		getObjects()->update(kObjectCompartmentE, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_6000;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarKronos;
		break;

	case kAction191668032:
		setup_function40();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(40, Rebecca, function40)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_9270;
		setCallback(1);
		setup_updateEntity(kCarGreenSleeping, kPosition_2740);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityRebecca, kEntitySophie, kAction292775040);
			setCallback(2);
			setup_updateEntity(kCarRedSleeping, kPosition_2740);
			break;

		case 2:
			getSavePoints()->push(kEntityRebecca, kEntityAnna, kAction191668032);
			setCallback(3);
			setup_updateEntity(kCarRedSleeping, kPosition_4840);
			break;

		case 3:
			getSavePoints()->push(kEntityRebecca, kEntitySophie, kAction123668192);
			setCallback(4);
			setup_function15();
			break;

		case 4:
			setup_function41();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(41, Rebecca, function41)
	if (savepoint.action == kActionDefault) {
		ENTITY_PARAM(0, 2) = 1;

		setCallback(1);
		setup_function20(kTimeEnd);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(42, Rebecca, chapter4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityRebecca);

		getData()->entityPosition = kPosition_4840;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->updateLocation2(kObject110, kLocation3);

		ENTITY_PARAM(0, 1) = 0;
		ENTITY_PARAM(0, 2) = 1;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(43, Rebecca, chapter4Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function20(kTime2385000);
		break;

	case kActionCallback:
		if (getCallback() == 1 || getCallback() == 2) {
			if (ENTITY_PARAM(0, 1)) {
				setup_function44();
			} else {
				setCallback(2);
				setup_function20((TimeValue)(getState()->time + 900));
			}
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(44, Rebecca, function44)
	error("Rebecca: callback function 44 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(45, Rebecca, function45)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_4840;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentE, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);

		getEntities()->clearSequences(kEntityRebecca);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			params->param1 = 1;
		break;

	case kAction205034665:
		if (!params->param1 && getState()->time < kTime2511000) {
			setCallback(1);
			setup_playSound("Reb6969");
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(46, Rebecca, chapter5)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityRebecca);

		getData()->entityPosition = kPosition_3969;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		getObjects()->updateLocation2(kObject110, kLocation4);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(47, Rebecca, chapter5Handler)
	if (savepoint.action == kActionProceedChapter5)
		setup_function48();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(48, Rebecca, function48)
	error("Rebecca: callback function 48 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_NULL_FUNCTION(49, Rebecca)

} // End of namespace LastExpress
