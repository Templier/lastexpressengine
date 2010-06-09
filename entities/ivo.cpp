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

#include "lastexpress/entities/ivo.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Ivo::Ivo(LastExpressEngine *engine) : Entity(engine, kEntityIvo) {
	ADD_CALLBACK_FUNCTION(Ivo, function1);
	ADD_CALLBACK_FUNCTION(Ivo, draw);
	ADD_CALLBACK_FUNCTION(Ivo, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Ivo, updateFromTime);
	ADD_CALLBACK_FUNCTION(Ivo, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Ivo, function6);
	ADD_CALLBACK_FUNCTION(Ivo, function7);
	ADD_CALLBACK_FUNCTION(Ivo, playSound);
	ADD_CALLBACK_FUNCTION(Ivo, function9);
	ADD_CALLBACK_FUNCTION(Ivo, savegame);
	ADD_CALLBACK_FUNCTION(Ivo, function11);
	ADD_CALLBACK_FUNCTION(Ivo, sitAtTableWithSalko);
	ADD_CALLBACK_FUNCTION(Ivo, leaveTableWithSalko);
	ADD_CALLBACK_FUNCTION(Ivo, chapter1);
	ADD_CALLBACK_FUNCTION(Ivo, function15);
	ADD_CALLBACK_FUNCTION(Ivo, function16);
	ADD_CALLBACK_FUNCTION(Ivo, function17);
	ADD_CALLBACK_FUNCTION(Ivo, chapter2);
	ADD_CALLBACK_FUNCTION(Ivo, function19);
	ADD_CALLBACK_FUNCTION(Ivo, function20);
	ADD_CALLBACK_FUNCTION(Ivo, function21);
	ADD_CALLBACK_FUNCTION(Ivo, chapter3);
	ADD_CALLBACK_FUNCTION(Ivo, function23);
	ADD_CALLBACK_FUNCTION(Ivo, chapter4);
	ADD_CALLBACK_FUNCTION(Ivo, function25);
	ADD_CALLBACK_FUNCTION(Ivo, function26);
	ADD_CALLBACK_FUNCTION(Ivo, function27);
	ADD_CALLBACK_FUNCTION(Ivo, function28);
	ADD_CALLBACK_FUNCTION(Ivo, function29);
	ADD_CALLBACK_FUNCTION(Ivo, chapter5);
	ADD_CALLBACK_FUNCTION(Ivo, function31);
	ADD_CALLBACK_FUNCTION(Ivo, function32);
	ADD_CALLBACK_FUNCTION(Ivo, function33);
	ADD_CALLBACK_FUNCTION(Ivo, function34);
}

IMPLEMENT_FUNCTION(Ivo, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Ivo, draw, 2)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SI(Ivo, enterExitCompartment, 3)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_I(Ivo, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_I(Ivo, updateFromTicks, 5)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION_II(Ivo, function6, 6)
	error("Ivo: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function7, 7)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Ivo, playSound, 8)
	Entity::playSound(savepoint, true);
}

IMPLEMENT_FUNCTION(Ivo, function9, 9)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION_II(Ivo, savegame, 10)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION(Ivo, function11, 11)
	error("Ivo: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, sitAtTableWithSalko, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->prepareSequences(kEntitySalko);
		getSavePoints()->push(kEntityIvo, kEntityTables2, kAction136455232);

		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityIvo, "023A1");
		getEntities()->drawSequenceRight(kEntitySalko, "023A2");
		getEntities()->drawSequenceRight(kEntityTables2, "023A3");
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, leaveTableWithSalko, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getSavePoints()->push(kEntityIvo, kEntityTables2, kAction103798704, "009E");
		getEntities()->prepareSequences(kEntitySalko);

		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityIvo, "023D1");
		getEntities()->drawSequenceRight(kEntitySalko, "023D2");
		getEntities()->drawSequenceRight(kEntityTables2, "023D3");
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter1, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(15)
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentH, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject47, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->field_491 = EntityData::kField491_4691;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;

		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function15, 15)
	error("Ivo: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function16, 16)
	error("Ivo: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function17, 17)
	if (savepoint.action == kActionDefault) {
		getData()->field_491 = EntityData::kField491_2740;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;

		getEntities()->prepareSequences(kEntityIvo);
		getObjects()->update(kObjectCompartmentH, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter2, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION(19, 1777500)
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityIvo);

		getData()->field_491 = EntityData::kField491_2740;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentH, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject47, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function19, 19)
	error("Ivo: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function20, 20)
	error("Ivo: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function21, 21)
	if (savepoint.action == kActionDefault) {
		getData()->field_491 = EntityData::kField491_2740;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentH, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter3, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function23();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityIvo);

		getData()->field_491 = EntityData::kField491_2740;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function23, 23)
	if (savepoint.action == kActionDefault)
		getObjects()->update(kObjectCompartmentH, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
}

IMPLEMENT_FUNCTION(Ivo, chapter4, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function25();
		break;

	case kActionDefault:
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function25, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeIvo && getEntities()->checkFields11()) {
			getData()->field_493 = EntityData::kField493_0;
			setup_function26();
		}
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityIvo, kEntityTables2, kAction136455232);
		getEntities()->drawSequenceLeft(kEntityIvo, "023B");
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function26, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Ivo, setup_leaveTableWithSalko));
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Ivo, setup_function11));
			break;

		case 2:
			setup_function27();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function27, 27)
	error("Ivo: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function28, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeIvo_1 && !params->param1) {
			params->param1 = 1;
			setCallback(1);
			call(new ENTITY_SETUP(Ivo, setup_function6), kCarRedSleeping, EntityData::kField491_2740);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Ivo, setup_enterExitCompartment), "613EH", kObjectCompartmentH);
			break;

		case 2:
			setup_function29();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function29, 29)
	if (savepoint.action == kActionDefault) {
		getEntities()->prepareSequences(kEntityIvo);
		getObjects()->update(kObjectCompartmentH, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->field_491 = EntityData::kField491_2740;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter5, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function31();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityIvo);

		getData()->field_491 = EntityData::kField491_540;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarBaggageRear;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function31, 31)
	if (savepoint.action == kAction70549068)
		setup_function32();
}

IMPLEMENT_FUNCTION(Ivo, function32, 32)
	error("Ivo: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function33, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getState()->time += 1800;

		setCallback(1);
		call(new ENTITY_SETUP(Ivo, setup_savegame), kSavegameType1, kEntityNone);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			getObjects()->update(kObject94, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);

		break;

	case kAction135800432:
		setup_function34();
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function34, 34)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityIvo);
}

} // End of namespace LastExpress
