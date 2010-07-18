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

#include "lastexpress/entities/servers0.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Servers0::Servers0(LastExpressEngine *engine) : Entity(engine, kEntityServers0) {
	ADD_CALLBACK_FUNCTION(Servers0, savepointCall);
	ADD_CALLBACK_FUNCTION(Servers0, updateFromTime);
	ADD_CALLBACK_FUNCTION(Servers0, draw);
	ADD_CALLBACK_FUNCTION(Servers0, updatePosition);
	ADD_CALLBACK_FUNCTION(Servers0, function5);
	ADD_CALLBACK_FUNCTION(Servers0, playSound);
	ADD_CALLBACK_FUNCTION(Servers0, function7);
	ADD_CALLBACK_FUNCTION(Servers0, function8);
	ADD_CALLBACK_FUNCTION(Servers0, function9);
	ADD_CALLBACK_FUNCTION(Servers0, function10);
	ADD_CALLBACK_FUNCTION(Servers0, chapter1);
	ADD_CALLBACK_FUNCTION(Servers0, function12);
	ADD_CALLBACK_FUNCTION(Servers0, function13);
	ADD_CALLBACK_FUNCTION(Servers0, function14);
	ADD_CALLBACK_FUNCTION(Servers0, function15);
	ADD_CALLBACK_FUNCTION(Servers0, function16);
	ADD_CALLBACK_FUNCTION(Servers0, function17);
	ADD_CALLBACK_FUNCTION(Servers0, function18);
	ADD_CALLBACK_FUNCTION(Servers0, function19);
	ADD_CALLBACK_FUNCTION(Servers0, function20);
	ADD_CALLBACK_FUNCTION(Servers0, function21);
	ADD_CALLBACK_FUNCTION(Servers0, function22);
	ADD_CALLBACK_FUNCTION(Servers0, chapter2);
	ADD_CALLBACK_FUNCTION(Servers0, function24);
	ADD_CALLBACK_FUNCTION(Servers0, function25);
	ADD_CALLBACK_FUNCTION(Servers0, function26);
	ADD_CALLBACK_FUNCTION(Servers0, chapter3);
	ADD_CALLBACK_FUNCTION(Servers0, function28);
	ADD_CALLBACK_FUNCTION(Servers0, function29);
	ADD_CALLBACK_FUNCTION(Servers0, function30);
	ADD_CALLBACK_FUNCTION(Servers0, chapter4);
	ADD_CALLBACK_FUNCTION(Servers0, function32);
	ADD_CALLBACK_FUNCTION(Servers0, function33);
	ADD_CALLBACK_FUNCTION(Servers0, function34);
	ADD_CALLBACK_FUNCTION(Servers0, function35);
	ADD_CALLBACK_FUNCTION(Servers0, chapter5);
	ADD_CALLBACK_FUNCTION(Servers0, function37);
	ADD_NULL_FUNCTION();
}

//////////////////////////////////////////////////////////////////////////
// Parameters:
//  - sequence name
//  - EntityIndex
//  - ActionIndex
//  - sequence name
IMPLEMENT_FUNCTION_SIIS(Servers0, savepointCall, 1)
	Entity::savepointCall(savepoint, true);
}

IMPLEMENT_FUNCTION_NOSETUP(Servers0, updateFromTime, 2)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_S(Servers0, draw, 3)
	Entity::draw(savepoint, true);
}

IMPLEMENT_FUNCTION_NOSETUP(Servers0, updatePosition, 4)
	Entity::updatePosition(savepoint, true);
}

IMPLEMENT_FUNCTION_NOSETUP(Servers0, function5, 5)
	EXPOSE_PARAMS(EntityData::EntityParametersIIII);

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getData()->direction != kDirectionRight)
			CALLBACK_ACTION();
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION();
 		break;

	case kActionExcuseMeCath:
		if (!params->param1) {
			getSound()->excuseMe(kEntityServers0);
			params->param1 = 1;
		}
		break;
	}
}

IMPLEMENT_FUNCTION_S(Servers0, playSound, 6)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION(Servers0, function7, 7)
	error("Servers0: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function8, 8)
	error("Servers0: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function9, 9)
	error("Servers0: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function10, 10)
	error("Servers0: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, chapter1, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function20();
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityServers0, kAction270410280, 0);
		getSavePoints()->addData(kEntityServers0, kAction304061224, 1);
		getSavePoints()->addData(kEntityServers0, kAction252568704, 10);
		getSavePoints()->addData(kEntityServers0, kAction286534136, 11);
		getSavePoints()->addData(kEntityServers0, kAction218983616, 12);
		getSavePoints()->addData(kEntityServers0, kAction218586752, 13);
		getSavePoints()->addData(kEntityServers0, kAction207330561, 14);
		getSavePoints()->addData(kEntityServers0, kAction286403504, 16);
		getSavePoints()->addData(kEntityServers0, kAction218128129, 17);
		getSavePoints()->addData(kEntityServers0, kAction270068760, 18);
		getSavePoints()->addData(kEntityServers0, kAction223712416, 2);
		getSavePoints()->addData(kEntityServers0, kAction237485916, 5);
		getSavePoints()->addData(kEntityServers0, kAction188893625, 8);
		getSavePoints()->addData(kEntityServers0, kAction204704037, 6);
		getSavePoints()->addData(kEntityServers0, kAction292758554, 7);
		getSavePoints()->addData(kEntityServers0, kAction337548856, 9);

		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function12, 12)
	handleServer(savepoint, "907", kEntityAnna, kAction268773672, &ENTITY_PARAM(0, 1));
}

IMPLEMENT_FUNCTION(Servers0, function13, 13)
	handleServer(savepoint, "911", kEntityAugust, kAction268773672, &ENTITY_PARAM(0, 2), "010F");
}

IMPLEMENT_FUNCTION(Servers0, function14, 14)
	handleServer(savepoint, "908", kEntityAnna, kAction170016384, &ENTITY_PARAM(0, 4));
}

IMPLEMENT_FUNCTION(Servers0, function15, 15)
	handleServer(savepoint, "912", kEntityAugust, kAction170016384, &ENTITY_PARAM(0, 5));
}

IMPLEMENT_FUNCTION(Servers0, function16, 16)
	error("Servers0: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function17, 17)
	error("Servers0: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function18, 18)
	error("Servers0: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function19, 19)
	error("Servers0: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5900;
		break;

	case kAction101632192:
		setup_function22();
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function21, 21)
	error("Servers0: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function22, 22)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;

		getEntities()->prepareSequences(kEntityServers0);
	}
}

IMPLEMENT_FUNCTION(Servers0, chapter2, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function24();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityServers0);

		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 4) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function24, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!getEntities()->checkFields17(kEntityServers0) || !getEntities()->checkFields11())
			break;

		if (ENTITY_PARAM(1, 3)) {
			setCallback(1);
			call(new ENTITY_SETUP(Servers0, setup_function25));
			break;
		}

		if (ENTITY_PARAM(1, 4)) {
			setCallback(2);
			call(new ENTITY_SETUP(Servers0, setup_function26));
		}
 		break;

	case kActionCallback:
		if (getCallback() != 1)
			break;

		if (ENTITY_PARAM(1, 4)) {
			setCallback(2);
			call(new ENTITY_SETUP(Servers0, setup_function26));
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function25, 25)
	error("Servers0: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function26, 26)
	error("Servers0: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, chapter3, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function28();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityServers0);

		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(1, 2) = 0;
		ENTITY_PARAM(1, 5) = 0;
		ENTITY_PARAM(1, 6) = 0;
		ENTITY_PARAM(2, 3) = 0;
		ENTITY_PARAM(2, 4) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function28, 28)
	error("Servers0: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function29, 29)
	error("Servers0: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function30, 30)
	error("Servers0: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, chapter4, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function32();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityServers0);

		getData()->entityPosition = kPosition_5900;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(1, 7) = 0;
		ENTITY_PARAM(1, 8) = 0;
		ENTITY_PARAM(2, 1) = 0;
		ENTITY_PARAM(2, 2) = 0;
		ENTITY_PARAM(2, 3) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function32, 32)
	error("Servers0: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function33, 33)
	error("Servers0: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function34, 34)
	error("Servers0: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function35, 35)
	error("Servers0: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, chapter5, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function37();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityServers0);

		getData()->entityPosition = kPosition_3969;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function37, 37)
	if (savepoint.action == kAction70549068)
		setup_nullfunction();
}

IMPLEMENT_NULL_FUNCTION(Servers0, 38)

void Servers0::handleServer(const SavePoint &savepoint, const char* name, EntityIndex entity, ActionIndex action, int *parameter, const char* name2) {
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5800;
		getData()->field_493 = kField493_0;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), name);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			// Prepare or draw sequences depending of value of string
			if (strcmp(name2, ""))
				getEntities()->prepareSequences(kEntityServers0);
			else
				getEntities()->drawSequenceLeft(kEntityServers0, name2);

			getSavePoints()->push(kEntityServers0, entity, action);
			*parameter = 0;

			CALLBACK_ACTION();
		}
		break;
	}
}

} // End of namespace LastExpress
