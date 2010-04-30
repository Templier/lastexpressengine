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
	ADD_CALLBACK_FUNCTION(Servers0, function1);
	ADD_CALLBACK_FUNCTION(Servers0, updateFromTime);
	ADD_CALLBACK_FUNCTION(Servers0, function3);
	ADD_CALLBACK_FUNCTION(Servers0, function4);
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

IMPLEMENT_FUNCTION_SIIS(Servers0, function1, 1)
	error("Servers0: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Servers0, updateFromTime, 2)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_S(Servers0, function3, 3)
	error("Servers0: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Servers0, function4, 4)
	error("Servers0: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Servers0, function5, 5)
	error("Servers0: callback function 5 not implemented!");
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

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function12, 12)
	error("Servers0: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function13, 13)
	error("Servers0: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function14, 14)
	error("Servers0: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function15, 15)
	error("Servers0: callback function 15 not implemented!");
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
	error("Servers0: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function21, 21)
	error("Servers0: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, function22, 22)
	error("Servers0: callback function 22 not implemented!");
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

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothes1;
		_data->getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 4) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function24, 24)
	error("Servers0: callback function 24 not implemented!");
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

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothes1;
		_data->getData()->inventoryItem = kItemNone;

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

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

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

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function37, 37)
	error("Servers0: callback function 37 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Servers0, 38)

} // End of namespace LastExpress
