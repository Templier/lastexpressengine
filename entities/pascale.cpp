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

#include "lastexpress/entities/pascale.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Pascale::Pascale(LastExpressEngine *engine) : Entity(engine, kEntityPascale) {
	ADD_CALLBACK_FUNCTION(Pascale, function1);
	ADD_CALLBACK_FUNCTION(Pascale, function2);
	ADD_CALLBACK_FUNCTION(Pascale, function3);
	ADD_CALLBACK_FUNCTION(Pascale, updateFromTime);
	ADD_CALLBACK_FUNCTION(Pascale, function5);
	ADD_CALLBACK_FUNCTION(Pascale, playSound);
	ADD_CALLBACK_FUNCTION(Pascale, draw2);
	ADD_CALLBACK_FUNCTION(Pascale, function8);
	ADD_CALLBACK_FUNCTION(Pascale, function9);
	ADD_CALLBACK_FUNCTION(Pascale, function10);
	ADD_CALLBACK_FUNCTION(Pascale, function11);
	ADD_CALLBACK_FUNCTION(Pascale, chapter1);
	ADD_CALLBACK_FUNCTION(Pascale, function13);
	ADD_CALLBACK_FUNCTION(Pascale, function14);
	ADD_CALLBACK_FUNCTION(Pascale, function15);
	ADD_CALLBACK_FUNCTION(Pascale, function16);
	ADD_CALLBACK_FUNCTION(Pascale, function17);
	ADD_CALLBACK_FUNCTION(Pascale, function18);
	ADD_CALLBACK_FUNCTION(Pascale, function19);
	ADD_CALLBACK_FUNCTION(Pascale, chapter2);
	ADD_CALLBACK_FUNCTION(Pascale, chapter3);
	ADD_CALLBACK_FUNCTION(Pascale, function22);
	ADD_CALLBACK_FUNCTION(Pascale, function23);
	ADD_CALLBACK_FUNCTION(Pascale, function24);
	ADD_CALLBACK_FUNCTION(Pascale, chapter4);
	ADD_CALLBACK_FUNCTION(Pascale, function26);
	ADD_CALLBACK_FUNCTION(Pascale, function27);
	ADD_CALLBACK_FUNCTION(Pascale, function28);
	ADD_CALLBACK_FUNCTION(Pascale, function29);
	ADD_CALLBACK_FUNCTION(Pascale, function30);
	ADD_CALLBACK_FUNCTION(Pascale, chapter5);
	ADD_CALLBACK_FUNCTION(Pascale, function32);
	ADD_CALLBACK_FUNCTION(Pascale, function33);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION_S(Pascale, function1, 1)
	error("Pascale: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function2, 2)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION(Pascale, function3, 3)
	if (savepoint.action == kActionExcuseMeCath) {
		if (!params->param1) {
			getSound()->excuseMe(kEntityPascale);
			params->param1 = 1;
		}
	}

	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_I(Pascale, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Pascale, function5, 5)
	error("Pascale: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_S(Pascale, playSound, 6)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Pascale, draw2, 7)
	Entity::draw2(savepoint);
}

IMPLEMENT_FUNCTION(Pascale, function8, 8)
	error("Pascale: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function9, 9)
	error("Pascale: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function10, 10)
	error("Pascale: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function11, 11)
	error("Pascale: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, chapter1, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function17();
 		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityPascale, kAction239072064, 0);
		getSavePoints()->addData(kEntityPascale, kAction257489762, 2);
		getSavePoints()->addData(kEntityPascale, kAction207769280, 6);
		getSavePoints()->addData(kEntityPascale, kAction101824388, 7);
		getSavePoints()->addData(kEntityPascale, kAction136059947, 8);
		getSavePoints()->addData(kEntityPascale, kAction223262556, 1);
		getSavePoints()->addData(kEntityPascale, kAction269479296, 3);
		getSavePoints()->addData(kEntityPascale, kAction352703104, 4);
		getSavePoints()->addData(kEntityPascale, kAction352768896, 5);
		getSavePoints()->addData(kEntityPascale, kAction191604416, 10);
		getSavePoints()->addData(kEntityPascale, kAction190605184, 11);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function13, 13)
	error("Pascale: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function14, 14)
	error("Pascale: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function15, 15)
	error("Pascale: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function16, 16)
	error("Pascale: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function17, 17)
	error("Pascale: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function18, 18)
	error("Pascale: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function19, 19)
	error("Pascale: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, chapter2, 20)
	if (savepoint.action == kActionDefault) {
		getEntities()->prepareSequences(kEntityPascale);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothes1;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject65, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	}
}

IMPLEMENT_FUNCTION(Pascale, chapter3, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function22();
 		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityPascale);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 7) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function22, 22)
	error("Pascale: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function23, 23)
	error("Pascale: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function24, 24)
	error("Pascale: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, chapter4, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function26();
 		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityPascale);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 2) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function26, 26)
	error("Pascale: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function27, 27)
	error("Pascale: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function28, 28)
	error("Pascale: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function29, 29)
	error("Pascale: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function30, 30)
	error("Pascale: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, chapter5, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function32();
 		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityPascale);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, function32, 32)
	error("Pascale: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, function33, 33)
	error("Pascale: callback function 33 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Pascale, 34)

} // End of namespace LastExpress
