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

#include "lastexpress/entities/vesna.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Vesna::Vesna(LastExpressEngine *engine) : Entity(engine, kEntityVesna) {
	ADD_CALLBACK_FUNCTION(Vesna, function1);
	ADD_CALLBACK_FUNCTION(Vesna, playSound);
	ADD_CALLBACK_FUNCTION(Vesna, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Vesna, draw);
	ADD_CALLBACK_FUNCTION(Vesna, checkEntity);
	ADD_CALLBACK_FUNCTION(Vesna, updateFromTime);
	ADD_CALLBACK_FUNCTION(Vesna, function7);
	ADD_CALLBACK_FUNCTION(Vesna, function8);
	ADD_CALLBACK_FUNCTION(Vesna, function9);
	ADD_CALLBACK_FUNCTION(Vesna, savegame);
	ADD_CALLBACK_FUNCTION(Vesna, function11);
	ADD_CALLBACK_FUNCTION(Vesna, chapter1);
	ADD_CALLBACK_FUNCTION(Vesna, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Vesna, function14);
	ADD_CALLBACK_FUNCTION(Vesna, function15);
	ADD_CALLBACK_FUNCTION(Vesna, chapter2);
	ADD_CALLBACK_FUNCTION(Vesna, function17);
	ADD_CALLBACK_FUNCTION(Vesna, function18);
	ADD_CALLBACK_FUNCTION(Vesna, chapter3);
	ADD_CALLBACK_FUNCTION(Vesna, function20);
	ADD_CALLBACK_FUNCTION(Vesna, function21);
	ADD_CALLBACK_FUNCTION(Vesna, function22);
	ADD_CALLBACK_FUNCTION(Vesna, function23);
	ADD_CALLBACK_FUNCTION(Vesna, chapter4);
	ADD_CALLBACK_FUNCTION(Vesna, function25);
	ADD_CALLBACK_FUNCTION(Vesna, function26);
	ADD_CALLBACK_FUNCTION(Vesna, function27);
	ADD_CALLBACK_FUNCTION(Vesna, chapter5);
	ADD_CALLBACK_FUNCTION(Vesna, function29);
	ADD_CALLBACK_FUNCTION(Vesna, function30);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Vesna, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Vesna, playSound, 2)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_SI(Vesna, enterExitCompartment, 3)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_S(Vesna, draw, 4)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_II(Vesna, checkEntity, 5)
	if (savepoint.action == kActionExcuseMeCath) {
		getSound()->playSound(kEntityNone, random(2) ? "CAT10150" : "CAT1015A");

		return;
	}

	Entity::checkEntity(savepoint, true);
}

IMPLEMENT_FUNCTION_I(Vesna, updateFromTime, 6)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_II(Vesna, function7, 7)
	error("Vesna: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function8, 8)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION(Vesna, function9, 9)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_II(Vesna, savegame, 10)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION(Vesna, function11, 11)
	error("Vesna: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, chapter1, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityVesna, kAction124190740, 0);

		getData()->entityPosition = kPosition_4689;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter1_handler, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		getData()->entityPosition = getEntityData(kEntityMilos)->entityPosition;
		getData()->field_493 = getEntityData(kEntityMilos)->field_493;
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->clearSequences(kEntityVesna);
			setup_function14();
		}
		break;

	case kAction204832737:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_function7), kCarRedSleeping, kPosition_3050);
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function14, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_3050;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		break;

	case kAction190412928:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_function11));
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function15, 15)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_3050;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;

		getEntities()->clearSequences(kEntityVesna);
		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter2, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function17();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVesna);

		getData()->entityPosition = kPosition_3050;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function17, 17)
	switch (savepoint.action) {
	default:
		break;

	case kAction135024800:
		setCallback(2);
		call(new ENTITY_SETUP(Vesna, setup_function18));
		break;

	case kAction137165825:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_function11));
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function18, 18)
	error("Vesna: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, chapter3, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function20();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVesna);

		getData()->entityPosition = kPosition_3050;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function20, 20)
	error("Vesna: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function21, 21)
	error("Vesna: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function22, 22)
	error("Vesna: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function23, 23)
	error("Vesna: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, chapter4, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_function11));
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVesna);

		getData()->entityPosition = kPosition_3050;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation3, kCursorHandKnock, kCursorHand);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function25();
	}
}

IMPLEMENT_FUNCTION(Vesna, function25, 25)
	error("Vesna: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function26, 26)
	error("Vesna: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function27, 27)
	if (savepoint.action == kActionDefault) {
		getEntities()->clearSequences(kEntityVesna);
		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_3050;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter5, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function29();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVesna);

		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function29, 29)
	switch (savepoint.action) {
	default:
		break;

	case kAction9:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_savegame), kSavegameType2, kEventCathVesnaRestaurantKilled);
		break;

	case kActionDefault:
		getObjects()->update(kObject64, kEntityVesna, kLocationNone, kCursorNormal, kCursorForward);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCathVesnaRestaurantKilled);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneNone, true);
		}
		break;

	case kAction134427424:
		getObjects()->update(kObject64, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
		setup_function30();
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function30, 30)
	error("Vesna: callback function 30 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Vesna, 31)

} // End of namespace LastExpress
