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

#include "lastexpress/entities/kronos.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Kronos::Kronos(LastExpressEngine *engine) : Entity(engine, kEntityKronos) {
	ADD_CALLBACK_FUNCTION(Kronos, function1);
	ADD_CALLBACK_FUNCTION(Kronos, savegame);
	ADD_CALLBACK_FUNCTION(Kronos, function3);
	ADD_CALLBACK_FUNCTION(Kronos, playSound);
	ADD_CALLBACK_FUNCTION(Kronos, updateFromTime);
	ADD_CALLBACK_FUNCTION(Kronos, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Kronos, chapter1);
	ADD_CALLBACK_FUNCTION(Kronos, function8);
	ADD_CALLBACK_FUNCTION(Kronos, function9);
	ADD_CALLBACK_FUNCTION(Kronos, function10);
	ADD_CALLBACK_FUNCTION(Kronos, function11);
	ADD_CALLBACK_FUNCTION(Kronos, chapter2);
	ADD_CALLBACK_FUNCTION(Kronos, chapter3);
	ADD_CALLBACK_FUNCTION(Kronos, function14);
	ADD_CALLBACK_FUNCTION(Kronos, function15);
	ADD_CALLBACK_FUNCTION(Kronos, function16);
	ADD_CALLBACK_FUNCTION(Kronos, function17);
	ADD_CALLBACK_FUNCTION(Kronos, function18);
	ADD_CALLBACK_FUNCTION(Kronos, function19);
	ADD_CALLBACK_FUNCTION(Kronos, function20);
	ADD_CALLBACK_FUNCTION(Kronos, function21);
	ADD_CALLBACK_FUNCTION(Kronos, function22);
	ADD_CALLBACK_FUNCTION(Kronos, function23);
	ADD_CALLBACK_FUNCTION(Kronos, chapter4);
	ADD_CALLBACK_FUNCTION(Kronos, chapter5);
}

IMPLEMENT_FUNCTION(Kronos, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_II(Kronos, savegame, 2)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(Kronos, function3, 3)
	Entity::savepointCheckEntity(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Kronos, playSound, 4)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Kronos, updateFromTime, 5)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Kronos, updateFromTicks, 6)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION(Kronos, chapter1, 7)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(8)
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_6000;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_2;

		getObjects()->update(kObjectCeiling, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, function8, 8)
	error("Kronos: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function9, 9)
	error("Kronos: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function10, 10)
	error("Kronos: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function11, 11)
	error("Kronos: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, chapter2, 12)
	if (savepoint->action == kActionDefault)
		getEntities()->drawSequences(kEntityKronos);
}

IMPLEMENT_FUNCTION(Kronos, chapter3, 13)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function14();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityKronos);

		_data->getData()->field_491 = EntityData::kField491_6000;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_2;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCeiling, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, function14, 14)
	error("Kronos: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function15, 15)
	error("Kronos: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function16, 16)
	error("Kronos: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function17, 17)
	error("Kronos: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function18, 18)
	error("Kronos: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function19, 19)
	error("Kronos: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function20, 20)
	error("Kronos: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function21, 21)
	error("Kronos: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function22, 22)
	error("Kronos: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, function23, 23)
	error("Kronos: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, chapter4, 24)
	if (savepoint->action == kActionDefault)
		getEntities()->drawSequences(kEntityKronos);
}

IMPLEMENT_FUNCTION(Kronos, chapter5, 25)
	if (savepoint->action == kActionDefault)
		getEntities()->drawSequences(kEntityKronos);
}

} // End of namespace LastExpress
