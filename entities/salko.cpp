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

#include "lastexpress/entities/salko.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Salko::Salko(LastExpressEngine *engine) : Entity(engine, kEntitySalko) {
	ADD_CALLBACK_FUNCTION(Salko, function1);
	ADD_CALLBACK_FUNCTION(Salko, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Salko, draw);
	ADD_CALLBACK_FUNCTION(Salko, checkEntity);
	ADD_CALLBACK_FUNCTION(Salko, updateFromTime);
	ADD_CALLBACK_FUNCTION(Salko, savegame);
	ADD_CALLBACK_FUNCTION(Salko, function7);
	ADD_CALLBACK_FUNCTION(Salko, function8);
	ADD_CALLBACK_FUNCTION(Salko, chapter1);
	ADD_CALLBACK_FUNCTION(Salko, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Salko, function11);
	ADD_CALLBACK_FUNCTION(Salko, chapter2);
	ADD_CALLBACK_FUNCTION(Salko, function13);
	ADD_CALLBACK_FUNCTION(Salko, chapter3);
	ADD_CALLBACK_FUNCTION(Salko, function15);
	ADD_CALLBACK_FUNCTION(Salko, function16);
	ADD_CALLBACK_FUNCTION(Salko, function17);
	ADD_CALLBACK_FUNCTION(Salko, chapter4);
	ADD_CALLBACK_FUNCTION(Salko, function19);
	ADD_CALLBACK_FUNCTION(Salko, function20);
	ADD_CALLBACK_FUNCTION(Salko, function21);
	ADD_CALLBACK_FUNCTION(Salko, function22);
	ADD_CALLBACK_FUNCTION(Salko, chapter5);
	ADD_CALLBACK_FUNCTION(Salko, function24);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Salko, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_SI(Salko, enterExitCompartment, 2)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Salko, draw, 3)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_II(Salko, checkEntity, 4)
	Entity::checkEntity(savepoint);
}

IMPLEMENT_FUNCTION_I(Salko, updateFromTime, 5)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_II(Salko, savegame, 6)
	Entity::savegame(savepoint);
}

// Parameters:
// - Car
// - EntityPosition
IMPLEMENT_FUNCTION_II(Salko, function7, 7)
	error("Salko: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Salko, function8, 8)
	if (savepoint.action == kActionDefault) {
		getData()->position = kPosition_2740;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter1, 9)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getData()->position = kPosition_4691;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter1_handler, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		getData()->position = getEntityData(kEntityIvo)->position;
		getData()->field_493 = getEntityData(kEntityIvo)->field_493;
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->prepareSequences(kEntitySalko);
			setup_function8();
		}
		break;

	case kAction125242096:
		setCallback(1);
		call(new ENTITY_SETUP(Salko, setup_function7), kCarRedSleeping, kPosition_2740);
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function11, 11)
	if (savepoint.action == kActionDefault) {
		getData()->position = kPosition_2740;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;

		getEntities()->prepareSequences(kEntitySalko);
		getObjects()->update(kObjectCompartmentH, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Salko, chapter2, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntitySalko);

		getData()->position = kPosition_2740;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;

	case kAction136184016:
		setCallback(1);
		call(new ENTITY_SETUP(Salko, setup_function13));
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function13, 13)
	error("Salko: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Salko, chapter3, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function15();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntitySalko);

		getData()->position = kPosition_2740;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function15, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time < kTimeAugustVienna) {
			UPDATE_PARAM(params->param1, getState()->time, 81000);

			setCallback(1);
			call(new ENTITY_SETUP(Salko, setup_function16));
		}
		break;

	case kActionCallback:
		if (getCallback() == 1)
			params->param1 = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function16, 16)
	error("Salko: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Salko, function17, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->position = kPosition_6470;
		getData()->field_493 = kField493_0;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		setCallback(1);
		call(new ENTITY_SETUP(Salko, setup_checkEntity), kCarGreenSleeping, kPosition_2740);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Salko, setup_enterExitCompartment), "612Ch", kObjectCompartmentH);
			break;

		case 2:
			getEntities()->prepareSequences(kEntitySalko);
			getData()->position = kPosition_2740;
			getData()->field_493 = kField493_1;
			getSavePoints()->push(kEntitySalko, kEntityMilos, kAction157691176);

			setup_function15();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter4, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function19();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntitySalko);

		getData()->position = kPosition_5420;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function19, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->drawSequenceLeft(kEntitySalko, "BLANK");

			getData()->field_493 = kField493_1;

			setup_function20();
		}
		break;

	case kAction125242096:
		setCallback(1);
		call(new ENTITY_SETUP(Salko, setup_function7), kCarRedSleeping, kPosition_2740);
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->field_493 = kField493_0;
			if (getData()->position < kPosition_2087)
				getData()->position = kPosition_2088;

			setCallback(2);
			call(new ENTITY_SETUP(Salko, setup_checkEntity), kCarRestaurant, kPosition_850);
			break;

		case 2:
			getEntities()->prepareSequences(kEntitySalko);
			setup_function21();
			break;
		}
		break;

	case kAction55996766:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Salko, setup_enterExitCompartment), "612Dh", kObjectCompartmentH);
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function21, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeSalko && !params->param1) {
			params->param1 = 1;
			setCallback(1);
			call(new ENTITY_SETUP(Salko, setup_checkEntity), kCarRedSleeping, kPosition_2740);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Salko, setup_enterExitCompartment), "612Ch", kObjectCompartmentH);
			break;

		case 2:
			setup_function22();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function22, 22)
	if (savepoint.action == kActionDefault) {
		getEntities()->prepareSequences(kEntitySalko);
		getObjects()->update(kObjectCompartmentH, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->position = kPosition_2740;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter5, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function24();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntitySalko);

		getData()->position = kPosition_9460;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function24, 24)
	error("Salko: callback function 24 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Salko, 25)

} // End of namespace LastExpress
