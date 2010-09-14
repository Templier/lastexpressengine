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

#include "lastexpress/entities/hadija.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Hadija::Hadija(LastExpressEngine *engine) : Entity(engine, kEntityHadija) {
	ADD_CALLBACK_FUNCTION(Hadija, reset);
	ADD_CALLBACK_FUNCTION(Hadija, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Hadija, playSound);
	ADD_CALLBACK_FUNCTION(Hadija, updateFromTime);
	ADD_CALLBACK_FUNCTION(Hadija, updateEntity);
	ADD_CALLBACK_FUNCTION(Hadija, compartment6);
	ADD_CALLBACK_FUNCTION(Hadija, compartment8);
	ADD_CALLBACK_FUNCTION(Hadija, compartment6to8);
	ADD_CALLBACK_FUNCTION(Hadija, compartment8to6);
	ADD_CALLBACK_FUNCTION(Hadija, chapter1);
	ADD_CALLBACK_FUNCTION(Hadija, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Hadija, function12);
	ADD_CALLBACK_FUNCTION(Hadija, chapter2);
	ADD_CALLBACK_FUNCTION(Hadija, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Hadija, chapter3);
	ADD_CALLBACK_FUNCTION(Hadija, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Hadija, chapter4);
	ADD_CALLBACK_FUNCTION(Hadija, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Hadija, function19);
	ADD_CALLBACK_FUNCTION(Hadija, chapter5);
	ADD_CALLBACK_FUNCTION(Hadija, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Hadija, function22);
	ADD_CALLBACK_FUNCTION(Hadija, function23);
	ADD_NULL_FUNCTION();
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Hadija, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Hadija, enterExitCompartment, 2)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Hadija, playSound, 3)
	Entity::playSound(savepoint);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_NOSETUP(Hadija, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Hadija, updateEntity, 5)
	Entity::updateEntity(savepoint, true);
}

IMPLEMENT_FUNCTION(Hadija, compartment6, 6)
	COMPARTMENT_TO(Hadija, kObjectCompartment6, kPosition_4070, "619Cf", "619Df");
}

IMPLEMENT_FUNCTION(Hadija, compartment8, 7)
	COMPARTMENT_TO(Hadija, kObjectCompartment8, kPosition_2740, "619Ch", "619Dh");
}

IMPLEMENT_FUNCTION(Hadija, compartment6to8, 8)
	COMPARTMENT_FROM_TO(Hadija, kObjectCompartment6, kPosition_4070, "619Bf", kObjectCompartment8, kPosition_2740, "619Ah");
}

IMPLEMENT_FUNCTION(Hadija, compartment8to6, 9)
	COMPARTMENT_FROM_TO(Hadija, kObjectCompartment8, kPosition_2740, "619Bh", kObjectCompartment6, kPosition_4070, "619Af");
}

IMPLEMENT_FUNCTION(Hadija, chapter1, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_4070;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter1Handler, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_PLAYSOUND_UPDATEPOSITION(Hadija, kTimeParisEpernay, params->param1, 1, "Har1100", kPosition_4840);

label_callback1:
		TIME_CHECK_CALLBACK(Hadija, kTime1084500, params->param2, 2, setup_compartment6to8);

label_callback2:
		if (params->param3 != kTimeInvalid && getState()->time > kTime1093500) {

			if (getState()->time <= kTime1134000) {

				if (!getEntities()->isPlayerInCar(kCarGreenSleeping) || !getEntities()->isInsideCompartment(kEntityMahmud, kCarGreenSleeping, kPosition_5790) || !params->param3) {
					params->param3 = getState()->time + 75;

					if (!params->param3) {
						setCallback(3);
						setup_compartment8();
						return;
					}
				}

				if (params->param3 >= getState()->time)
					return;
			}

			params->param3 = kTimeInvalid;

			setCallback(3);
			setup_compartment8();
		}

label_callback3:
		TIME_CHECK_CALLBACK(Hadija, kTime1156500, params->param4, 4, setup_compartment8to6);

label_callback4:
		if (params->param5 != kTimeInvalid && getState()->time > kTime1165500) {
			if (getState()->time <= kTime1188000) {

				if (!getEntities()->isPlayerInCar(kCarGreenSleeping) || !getEntities()->isInsideCompartment(kEntityMahmud, kCarGreenSleeping, kPosition_5790) || !params->param5) {
					params->param5 = getState()->time + 75;

					if (!params->param5) {
						setCallback(5);
						setup_compartment6();
						return;
					}
				}

				if (params->param5 >= getState()->time)
					return;
			}

			params->param5 = kTimeInvalid;

			setCallback(5);
			setup_compartment6();
		}
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
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, function12, 12)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartment8, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_2740;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		getEntities()->clearSequences(kEntityHadija);
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter2, 13)
	if (savepoint.action == kActionDefault) {

		getEntities()->clearSequences(kEntityHadija);

		getData()->entityPosition = kPosition_3050;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		setup_chapter2Handler();
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter2Handler, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_POSITION(kTime1782000, params->param1, kPosition_2740);

		if (params->param2 == kTimeInvalid || getState()->time <= kTime1786500) {
			TIME_CHECK_CALLBACK(Hadija, kTime1822500, params->param3, 2, setup_compartment8to6);
			break;
		}

		if (getState()->time <= kTime1818000) {

			if (!getEntities()->isPlayerInCar(kCarGreenSleeping) || !params->param2)
				params->param2 = getState()->time + 75;

			if (params->param2 >= getState()->time) {
				TIME_CHECK_CALLBACK(Hadija, kTime1822500, params->param3, 2, setup_compartment8to6);
				break;
			}
		}

		params->param2 = kTimeInvalid;

		setCallback(1);
		setup_compartment8();
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			TIME_CHECK_CALLBACK(Hadija, kTime1822500, params->param3, 2, setup_compartment8to6);
			break;

		case 2:
			setCallback(3);
			setup_playSound("Har2012");
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter3, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityHadija);

		getData()->entityPosition = kPosition_4070;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter3Handler, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Hadija, kTime1998000, params->param1, 1, setup_compartment6to8);

label_callback1:
		TIME_CHECK_CALLBACK(Hadija, kTime2020500, params->param2, 2, setup_compartment8to6);

label_callback2:
		TIME_CHECK_CALLBACK(Hadija, kTime2079000, params->param3, 3, setup_compartment6to8);

label_callback3:
		TIME_CHECK_CALLBACK(Hadija, kTime2187000, params->param4, 4, setup_compartment8to6);

label_callback4:
		if (params->param5 != kTimeInvalid && getState()->time > kTime2196000)
			TIME_CHECK_CAR(Hadija, kTime2254500, params->param5, 5, setup_compartment6);
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
			goto label_callback2;

		case 3:
			goto label_callback3;

		case 4:
			goto label_callback4;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter4, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_4070;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;
		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter4Handler, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1 != kTimeInvalid)
			TIME_CHECK_CAR(Hadija, kTime1714500, params->param1, 1, setup_compartment6);

label_callback1:
		TIME_CHECK_CALLBACK(Hadija, kTime2367000, params->param2, 2, setup_compartment6to8);

label_callback2:
		TIME_CHECK_CALLBACK(Hadija, kTime2421000, params->param3, 3, setup_compartment8to6);

label_callback3:
		if (params->param4 != kTimeInvalid && getState()->time > kTime2425500)
			TIME_CHECK_CAR(Hadija, kTime2484000, params->param4, 4, setup_compartment6);
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
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, function19, 19)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartment8, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_4070;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarGreenSleeping;

		getEntities()->clearSequences(kEntityHadija);
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter5, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityHadija);

		getData()->entityPosition = kPosition_3969;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter5Handler, 21)
	if (savepoint.action == kActionProceedChapter5)
		setup_function22();
}

IMPLEMENT_FUNCTION(Hadija, function22, 22)
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
		if (getEntities()->isInsideTrainCar(kEntityPlayer, kCarGreenSleeping)) {
			setup_function23();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_updateEntity(kCarGreenSleeping, kPosition_4070);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_enterExitCompartment("619AF", kObjectCompartment6);
			break;

		case 2:
			getEntities()->clearSequences(kEntityHadija);

			getData()->entityPosition = kPosition_4840;
			getData()->location = kLocationInsideCompartment;

			getObjects()->update(kObjectCompartment5, kEntityPlayer, kLocation1, kCursorHandKnock, kCursorHand);
			break;
		}
		break;

	case kAction135800432:
		setup_nullfunction();
		break;
	}
}

IMPLEMENT_NULL_FUNCTION(Hadija, 24)

} // End of namespace LastExpress
