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

#include "lastexpress/entities/servers1.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Servers1::Servers1(LastExpressEngine *engine) : Entity(engine, kEntityServers1) {
	ADD_CALLBACK_FUNCTION(Servers1, updateFromTime);
	ADD_CALLBACK_FUNCTION(Servers1, function2);
	ADD_CALLBACK_FUNCTION(Servers1, function3);
	ADD_CALLBACK_FUNCTION(Servers1, function4);
	ADD_CALLBACK_FUNCTION(Servers1, function5);
	ADD_CALLBACK_FUNCTION(Servers1, playSound);
	ADD_CALLBACK_FUNCTION(Servers1, function7);
	ADD_CALLBACK_FUNCTION(Servers1, chapter1);
	ADD_CALLBACK_FUNCTION(Servers1, function9);
	ADD_CALLBACK_FUNCTION(Servers1, function10);
	ADD_CALLBACK_FUNCTION(Servers1, function11);
	ADD_CALLBACK_FUNCTION(Servers1, function12);
	ADD_CALLBACK_FUNCTION(Servers1, function13);
	ADD_CALLBACK_FUNCTION(Servers1, function14);
	ADD_CALLBACK_FUNCTION(Servers1, function15);
	ADD_CALLBACK_FUNCTION(Servers1, function16);
	ADD_CALLBACK_FUNCTION(Servers1, chapter2);
	ADD_CALLBACK_FUNCTION(Servers1, function18);
	ADD_CALLBACK_FUNCTION(Servers1, function19);
	ADD_CALLBACK_FUNCTION(Servers1, function20);
	ADD_CALLBACK_FUNCTION(Servers1, function21);
	ADD_CALLBACK_FUNCTION(Servers1, chapter3);
	ADD_CALLBACK_FUNCTION(Servers1, function23);
	ADD_CALLBACK_FUNCTION(Servers1, function24);
	ADD_CALLBACK_FUNCTION(Servers1, chapter4);
	ADD_CALLBACK_FUNCTION(Servers1, function26);
	ADD_CALLBACK_FUNCTION(Servers1, function27);
	ADD_CALLBACK_FUNCTION(Servers1, function28);
	ADD_CALLBACK_FUNCTION(Servers1, function29);
	ADD_CALLBACK_FUNCTION(Servers1, chapter5);
	ADD_CALLBACK_FUNCTION(Servers1, function31);
	ADD_NULL_FUNCTION()
}

IMPLEMENT_FUNCTION_NOSETUP(Servers1, updateFromTime, 1)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION(Servers1, function2, 2)
	error("Servers1: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_SII(Servers1, function3, 3)
	error("Servers1: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function4, 4)
	error("Servers1: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_SIIS(Servers1, function5, 5)
	error("Servers1: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_S(Servers1, playSound, 6)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION(Servers1, function7, 7)
	error("Servers1: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, chapter1, 8)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		// call function 14
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityServers1, kAction223002560, 0);
		getSavePoints()->addData(kEntityServers1, kAction302996448, 2);
		getSavePoints()->addData(kEntityServers1, kAction269485588, 3);
		getSavePoints()->addData(kEntityServers1, kAction326144276, 4);
		getSavePoints()->addData(kEntityServers1, kAction302203328, 5);
		getSavePoints()->addData(kEntityServers1, kAction189688608, 6);
		getSavePoints()->addData(kEntityServers1, kAction236237423, 7);
		getSavePoints()->addData(kEntityServers1, kAction219377792, 8);
		getSavePoints()->addData(kEntityServers1, kAction256200848, 9);
		getSavePoints()->addData(kEntityServers1, kAction291721418, 10);
		getSavePoints()->addData(kEntityServers1, kAction258136010, 11);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, function9, 9)
	error("Servers1: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function10, 10)
	error("Servers1: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function11, 11)
	error("Servers1: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function12, 12)
	error("Servers1: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function13, 13)
	error("Servers1: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function14, 14)
	error("Servers1: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function15, 15)
	error("Servers1: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function16, 16)
	error("Servers1: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, chapter2, 17)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function18();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityServers1);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothes1;
		_data->getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 6) = 0;
		ENTITY_PARAM(0, 7) = 0;
		ENTITY_PARAM(0, 8) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, function18, 18)
	error("Servers1: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function19, 19)
	error("Servers1: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function20, 20)
	error("Servers1: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function21, 21)
	error("Servers1: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, chapter3, 22)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function23();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityServers1);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothes1;
		_data->getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 2) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, function23, 23)
	error("Servers1: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function24, 24)
	error("Servers1: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, chapter4, 25)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function26();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityServers1);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		// TODO: there is a second call to drawSequences in the original code (is it really needed?)
		getEntities()->drawSequences(kEntityServers1);

		ENTITY_PARAM(1, 2) = 0;
		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 4) = 0;
		ENTITY_PARAM(1, 5) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, function26, 26)
	error("Servers1: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function27, 27)
	error("Servers1: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function28, 28)
	error("Servers1: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function29, 29)
	error("Servers1: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, chapter5, 30)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function31();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityServers1);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, function31, 31)
	error("Servers1: callback function 31 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Servers1, 32)

} // End of namespace LastExpress
