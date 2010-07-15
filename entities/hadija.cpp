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
	ADD_CALLBACK_FUNCTION(Hadija, function1);
	ADD_CALLBACK_FUNCTION(Hadija, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Hadija, playSound);
	ADD_CALLBACK_FUNCTION(Hadija, updateFromTime);
	ADD_CALLBACK_FUNCTION(Hadija, function5);
	ADD_CALLBACK_FUNCTION(Hadija, function6);
	ADD_CALLBACK_FUNCTION(Hadija, function7);
	ADD_CALLBACK_FUNCTION(Hadija, function8);
	ADD_CALLBACK_FUNCTION(Hadija, function9);
	ADD_CALLBACK_FUNCTION(Hadija, chapter1);
	ADD_CALLBACK_FUNCTION(Hadija, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Hadija, function12);
	ADD_CALLBACK_FUNCTION(Hadija, chapter2);
	ADD_CALLBACK_FUNCTION(Hadija, function14);
	ADD_CALLBACK_FUNCTION(Hadija, chapter3);
	ADD_CALLBACK_FUNCTION(Hadija, function16);
	ADD_CALLBACK_FUNCTION(Hadija, chapter4);
	ADD_CALLBACK_FUNCTION(Hadija, function18);
	ADD_CALLBACK_FUNCTION(Hadija, function19);
	ADD_CALLBACK_FUNCTION(Hadija, chapter5);
	ADD_CALLBACK_FUNCTION(Hadija, function21);
	ADD_CALLBACK_FUNCTION(Hadija, function22);
	ADD_CALLBACK_FUNCTION(Hadija, function23);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Hadija, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_SI(Hadija, enterExitCompartment, 2)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_S(Hadija, playSound, 3)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Hadija, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_II(Hadija, function5, 5)
	error("Hadija: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function6, 6)
	error("Hadija: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function7, 7)
	error("Hadija: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function8, 8)
	error("Hadija: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function9, 9)
	error("Hadija: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, chapter1, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getData()->position = kPosition_4070;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter1_handler, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_PLAYSOUND_2(Hadija, kTimeParisEpernay, params->param1, 1, "Har1100", kPosition_4840);

label_callback1:
		TIME_CHECK_CALLBACK(Hadija, kTimeRebecca_1_1, params->param2, 2, setup_function8);

label_callback2:
		if (params->param3 != kTimeInvalid && getState()->time > kTimeAnna) {

			if (getState()->time <= kTimeHadija_1_2) {

				if (!getEntities()->checkFields7(kCarGreenSleeping) || !getEntities()->checkFields1(kEntityMahmud, kCarGreenSleeping, kPosition_5790) || !params->param3) {
					params->param3 = getState()->time + 75;

					if (!params->param3) {
						setCallback(3);
						call(new ENTITY_SETUP(Hadija, setup_function7));
						return;
					}
				}

				if (params->param3 >= (int)getState()->time)
					return;
			}

			params->param3 = kTimeInvalid;

			setCallback(3);
			call(new ENTITY_SETUP(Hadija, setup_function7));
		}

label_callback3:
		TIME_CHECK_CALLBACK(Hadija, kTimeHadija_1, params->param4, 4, setup_function9);

label_callback4:
		if (params->param5 != kTimeInvalid && getState()->time > kTimeTables1) {
			if (getState()->time <= kTimeHadija_1_1) {

				if (!getEntities()->checkFields7(kCarGreenSleeping) || !getEntities()->checkFields1(kEntityMahmud, kCarGreenSleeping, kPosition_5790) || !params->param5) {
					params->param5 = getState()->time + 75;

					if (!params->param5) {
						setCallback(5);
						call(new ENTITY_SETUP(Hadija, setup_function6));
						return;
					}
				}

				if (params->param5 >= (int)getState()->time)
					return;
			}

			params->param5 = kTimeInvalid;

			setCallback(5);
			call(new ENTITY_SETUP(Hadija, setup_function6));
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
		getObjects()->update(kObjectCompartment8, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->position = kPosition_2740;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarGreenSleeping;

		getEntities()->prepareSequences(kEntityHadija);
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter2, 13)
	if (savepoint.action == kActionDefault) {

		getEntities()->prepareSequences(kEntityHadija);

		getData()->position = kPosition_3050;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		setup_function14();
	}
}

IMPLEMENT_FUNCTION(Hadija, function14, 14)
	error("Hadija: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, chapter3, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function16();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityHadija);

		getData()->position = kPosition_4070;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, function16, 16)
	error("Hadija: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, chapter4, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function18();
		break;

	case kActionDefault:
		getData()->position = kPosition_4070;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarGreenSleeping;
		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, function18, 18)
	error("Hadija: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function19, 19)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartment8, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->position = kPosition_4070;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarGreenSleeping;

		getEntities()->prepareSequences(kEntityHadija);
	}
}

IMPLEMENT_FUNCTION(Hadija, chapter5, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function21();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityHadija);

		getData()->position = kPosition_3969;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, function21, 21)
	if (savepoint.action == kAction70549068)
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
		getData()->position = kPosition_5000;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarGreenSleeping;
		break;

	case kAction17:
		if (getEntities()->checkFields5(kEntityNone, kCarGreenSleeping)) {
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
		call(new ENTITY_SETUP(Hadija, setup_function5), kCarGreenSleeping, kPosition_4070);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Hadija, setup_enterExitCompartment), "619AF", kObjectCompartment6);
			break;

		case 2:
			getEntities()->prepareSequences(kEntityHadija);

			getData()->position = kPosition_4840;
			getData()->field_493 = EntityData::kField493_1;

			getObjects()->update(kObjectCompartment5, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
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
