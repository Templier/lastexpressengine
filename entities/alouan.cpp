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

#include "lastexpress/entities/alouan.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Alouan::Alouan(LastExpressEngine *engine) : Entity(engine, kEntityAlouan) {
	ADD_CALLBACK_FUNCTION(Alouan, reset);
	ADD_CALLBACK_FUNCTION(Alouan, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Alouan, playSound);
	ADD_CALLBACK_FUNCTION(Alouan, updateFromTime);
	ADD_CALLBACK_FUNCTION(Alouan, updateEntity);
	ADD_CALLBACK_FUNCTION(Alouan, compartment6);
	ADD_CALLBACK_FUNCTION(Alouan, compartment8);
	ADD_CALLBACK_FUNCTION(Alouan, compartment6to8);
	ADD_CALLBACK_FUNCTION(Alouan, compartment8to6);
	ADD_CALLBACK_FUNCTION(Alouan, chapter1);
	ADD_CALLBACK_FUNCTION(Alouan, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Alouan, function12);
	ADD_CALLBACK_FUNCTION(Alouan, chapter2);
	ADD_CALLBACK_FUNCTION(Alouan, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Alouan, chapter3);
	ADD_CALLBACK_FUNCTION(Alouan, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Alouan, chapter4);
	ADD_CALLBACK_FUNCTION(Alouan, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Alouan, function19);
	ADD_CALLBACK_FUNCTION(Alouan, chapter5);
	ADD_CALLBACK_FUNCTION(Alouan, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Alouan, function22);
	ADD_CALLBACK_FUNCTION(Alouan, function23);
	ADD_NULL_FUNCTION();
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Alouan, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Alouan, enterExitCompartment, 2)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Alouan, playSound, 3)
	Entity::playSound(savepoint);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_I(Alouan, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Alouan, updateEntity, 5)
	Entity::updateEntity(savepoint, true);
}

IMPLEMENT_FUNCTION(Alouan, compartment6, 6)
	COMPARTMENT_TO(Alouan, kObjectCompartment6, kPosition_4070, "621Cf", "621Df");
}

IMPLEMENT_FUNCTION(Alouan, compartment8, 7)
	COMPARTMENT_TO(Alouan, kObjectCompartment8, kPosition_2740, "621Ch", "621Dh");
}

IMPLEMENT_FUNCTION(Alouan, compartment6to8, 8)
	COMPARTMENT_FROM_TO(Alouan, kObjectCompartment6, kPosition_4070, "621Bf", kObjectCompartment8, kPosition_2740, "621Ah");
}

IMPLEMENT_FUNCTION(Alouan, compartment8to6, 9)
	COMPARTMENT_FROM_TO(Alouan, kObjectCompartment8, kPosition_2740, "621Bh", kObjectCompartment6, kPosition_4070, "621Af");
}

IMPLEMENT_FUNCTION(Alouan, chapter1, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_2740;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter1Handler, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:

		TIME_CHECK_CALLBACK(Alouan, kTime1096200, params->param1, 1, setup_compartment8to6);

label_callback1:
		if (getState()->time > kTime1162800 && !params->param2) {
			params->param2 = 1;
			getSavePoints()->push(kEntityAlouan, kEntityTrain, kAction191070912, kPosition_4070);
			getData()->entityPosition = kPosition_4070;
		}

		if (getState()->time > kTime1179000 && !params->param3) {
			params->param3 = 1;
			getSavePoints()->push(kEntityAlouan, kEntityTrain, kAction191070912, kPosition_4840);

			setCallback(2);
			call(new ENTITY_SETUP(Alouan, setup_compartment6to8));
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->entityPosition = kPosition_4840;
			goto label_callback1;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function12, 12)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartment7, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment5, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_4070;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		getEntities()->clearSequences(kEntityAlouan);
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter2, 13)
	if (savepoint.action != kActionDefault)
		return;

	getEntities()->clearSequences(kEntityAlouan);

	getData()->entityPosition = kPosition_2740;
	getData()->location = kLocationInsideCompartment;
	getData()->car = kCarGreenSleeping;
	getData()->clothes = kClothesDefault;
	getData()->inventoryItem = kItemNone;

	setup_chapter2Handler();
}

IMPLEMENT_FUNCTION(Alouan, chapter2Handler, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param2 == kTimeInvalid)
			break;

		if (getState()->time <= kTime1777500) {
			if (!getEntities()->isPlayerInCar(kCarGreenSleeping) || !params->param2)
				params->param2 = getState()->time + 75;

			if (params->param2 >= getState()->time)
				break;
		}

		params->param2 = kTimeInvalid;

		setCallback(params->param1 ? 1 : 2);
		if (params->param1)
			call(new ENTITY_SETUP(Alouan, setup_compartment8));
		else
			call(new ENTITY_SETUP(Alouan, setup_compartment6));
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAlouan, kEntityTrain, kAction191070912, kPosition_4840);
		params->param1 = 1;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 3:
			params->param1 = 0;
			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Alouan, setup_playSound), "Har2011");
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP(Alouan, setup_updateFromTime), 900);
			break;

		case 5:
			getSavePoints()->push(kEntityAlouan, kEntityFrancois, kAction190219584);
			break;
		}
		break;

	case kAction189489753:
		setCallback(3);
		call(new ENTITY_SETUP(Alouan, setup_compartment8to6));
		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter3, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAlouan);

		getData()->entityPosition = kPosition_2740;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter3Handler, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Alouan, kTimeCitySalzbourg, params->param1, 1, setup_compartment8to6);

label_callback1:
		if (params->param2 != kTimeInvalid && getState()->time > kTime1989000)
			TIME_CHECK_CAR(Alouan, kTime2119500, params->param5, 5, setup_compartment8);

label_callback2:
		TIME_CHECK_PLAYSOUND(Alouan, kTime2052000, params->param3, 3, "Har1005");

label_callback3:
		TIME_CHECK_CALLBACK(Alouan, kTime2133000, params->param4, 4, setup_compartment6to8);

label_callback4:
		if (params->param5 != kTimeInvalid && getState()->time > kTime2151000)
			TIME_CHECK_CAR(Alouan, kTime2241000, params->param5, 5, setup_compartment8);
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAlouan, kEntityTrain, kAction191070912, kPosition_4840);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->entityPosition = kPosition_4840;
			goto label_callback1;

		case 2:
			goto label_callback2;

		case 3:
			goto label_callback3;

		case 4:
			goto label_callback4;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter4, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAlouan);

		getData()->entityPosition = kPosition_2740;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter4Handler, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1 != kTimeInvalid)
			TIME_CHECK_CAR(Alouan, kTime2443500, params->param1, 1, setup_compartment8);

label_callback1:
		TIME_CHECK_CALLBACK(Alouan, kTime2455200, params->param2, 2, setup_compartment8to6);

label_callback2:
		if (getState()->time > kTime2475000 && !params->param3) {
			params->param3 = 1;
			getSavePoints()->push(kEntityAlouan, kEntityTrain, kAction191070912, kPosition_4840);

			setCallback(3);
			call(new ENTITY_SETUP(Alouan, setup_compartment6to8));
		}		
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAlouan, kEntityTrain, kAction191070912, kPosition_4840);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			goto label_callback1;

		case 2:
			getSavePoints()->push(kEntityAlouan, kEntityTrain, kAction191070912, kPosition_4070);
			goto label_callback2;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function19, 19)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartment7, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment5, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_2740;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		getEntities()->clearSequences(kEntityAlouan);
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter5, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityAlouan);

		getData()->entityPosition = kPosition_3969;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter5Handler, 21)
	if (savepoint.action == kActionProceedChapter5)
		setup_function22();
}

IMPLEMENT_FUNCTION(Alouan, function22, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM(params->param1, getState()->time, 2700);
		setup_function23();
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5000;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarGreenSleeping;
		break;

	case kActionDrawScene:
		if (getEntities()->isInsideTrainCar(kEntityPlayer, kCarGreenSleeping))
			setup_function23();
		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Alouan, setup_updateEntity), kCarGreenSleeping, kPosition_4070);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Alouan, setup_enterExitCompartment), "619AF", kObjectCompartment5);
			break;

		case 2:
			getEntities()->clearSequences(kEntityAlouan);

			getData()->entityPosition = kPosition_4070;
			getData()->location = kLocationInsideCompartment;

			getObjects()->update(kObjectCompartment6, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
			break;
		}
		break;

	case kAction135800432:
		setup_nullfunction();
		break;
	}
}

IMPLEMENT_NULL_FUNCTION(Alouan, 24)

} // End of namespace LastExpress
