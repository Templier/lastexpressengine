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
	ADD_CALLBACK_FUNCTION(Alouan, function1);
	ADD_CALLBACK_FUNCTION(Alouan, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Alouan, playSound);
	ADD_CALLBACK_FUNCTION(Alouan, updateFromTime);
	ADD_CALLBACK_FUNCTION(Alouan, checkEntity);
	ADD_CALLBACK_FUNCTION(Alouan, function6);
	ADD_CALLBACK_FUNCTION(Alouan, function7);
	ADD_CALLBACK_FUNCTION(Alouan, function8);
	ADD_CALLBACK_FUNCTION(Alouan, function9);
	ADD_CALLBACK_FUNCTION(Alouan, chapter1);
	ADD_CALLBACK_FUNCTION(Alouan, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Alouan, function12);
	ADD_CALLBACK_FUNCTION(Alouan, chapter2);
	ADD_CALLBACK_FUNCTION(Alouan, chapter2_handler);
	ADD_CALLBACK_FUNCTION(Alouan, chapter3);
	ADD_CALLBACK_FUNCTION(Alouan, chapter3_handler);
	ADD_CALLBACK_FUNCTION(Alouan, chapter4);
	ADD_CALLBACK_FUNCTION(Alouan, chapter4_handler);
	ADD_CALLBACK_FUNCTION(Alouan, function19);
	ADD_CALLBACK_FUNCTION(Alouan, chapter5);
	ADD_CALLBACK_FUNCTION(Alouan, chapter5_handler);
	ADD_CALLBACK_FUNCTION(Alouan, function22);
	ADD_CALLBACK_FUNCTION(Alouan, function23);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Alouan, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_SI(Alouan, enterExitCompartment, 2)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_S(Alouan, playSound, 3)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_I(Alouan, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_II(Alouan, checkEntity, 5)
	Entity::checkEntity(savepoint, true);
}

IMPLEMENT_FUNCTION(Alouan, function6, 6)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->position = kPosition_4070;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Alouan, setup_enterExitCompartment), "621Cf", kObjectCompartment6);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Alouan, setup_enterExitCompartment), "621Df", kObjectCompartment6);
			break;

		case 2:
			getData()->position = kPosition_4070;
			getEntities()->prepareSequences(kEntityAlouan);

			CALLBACK_ACTION();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function7, 7)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->position = kPosition_2740;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Alouan, setup_enterExitCompartment), "621Ch", kObjectCompartment8);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Alouan, setup_enterExitCompartment), "621Dh", kObjectCompartment8);
			break;

		case 2:
			getData()->position = kPosition_2740;
			getEntities()->prepareSequences(kEntityAlouan);

			CALLBACK_ACTION();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function8, 8)
	error("Alouan: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, function9, 9)
	error("Alouan: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, chapter1, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getData()->position = kPosition_2740;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter1_handler, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:

		TIME_CHECK_CALLBACK(Alouan, kTimeAlouan, params->param1, 1, setup_function9);

label_callback1:
		if (getState()->time > kTimeYasmin_7 && !params->param2) {
			params->param2 = 1;
			getSavePoints()->push(kEntityAlouan, kEntityTrain, kAction191070912, kPosition_4070);
			getData()->position = kPosition_4070;
		}

		if (getState()->time > kTimeAlouan_1 && !params->param3) {
			params->param3 = 1;
			getSavePoints()->push(kEntityAlouan, kEntityTrain, kAction191070912, kPosition_4840);

			setCallback(2);
			call(new ENTITY_SETUP(Alouan, setup_function8));
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->position = kPosition_4840;
			goto label_callback1;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function12, 12)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartment7, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment5, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->position = kPosition_4070;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;

		getEntities()->prepareSequences(kEntityAlouan);
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter2, 13)
	if (savepoint.action != kActionDefault)
		return;

	getEntities()->prepareSequences(kEntityAlouan);

	getData()->position = kPosition_2740;
	getData()->field_493 = kField493_1;
	getData()->car = kCarGreenSleeping;
	getData()->clothes = kClothesDefault;
	getData()->inventoryItem = kItemNone;

	setup_chapter2_handler();
}

IMPLEMENT_FUNCTION(Alouan, chapter2_handler, 14)
	error("Alouan: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, chapter3, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3_handler();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAlouan);

		getData()->position = kPosition_2740;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter3_handler, 16)
	error("Alouan: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, chapter4, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4_handler();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAlouan);

		getData()->position = kPosition_2740;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter4_handler, 18)
	error("Alouan: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, function19, 19)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartment7, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment5, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->position = kPosition_2740;
		getData()->field_493 = kField493_1;
		getData()->car = kCarGreenSleeping;

		getEntities()->prepareSequences(kEntityAlouan);
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter5, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5_handler();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAlouan);

		getData()->position = kPosition_3969;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, chapter5_handler, 21)
	if (savepoint.action == kAction70549068)
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
		getData()->position = kPosition_5000;
		getData()->field_493 = kField493_0;
		getData()->car = kCarGreenSleeping;
		break;

	case kAction17:
		if (getEntities()->checkFields5(kEntityNone, kCarGreenSleeping)) {
			setup_function23();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Alouan, setup_checkEntity), kCarGreenSleeping, kPosition_4070);
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
			getEntities()->prepareSequences(kEntityAlouan);

			getData()->position = kPosition_4070;
			getData()->field_493 = kField493_1;

			getObjects()->update(kObjectCompartment6, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
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
