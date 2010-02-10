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
	ADD_CALLBACK_FUNCTION(Ivo, function3);
	ADD_CALLBACK_FUNCTION(Ivo, updateFromTime);
	ADD_CALLBACK_FUNCTION(Ivo, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Ivo, function6);
	ADD_CALLBACK_FUNCTION(Ivo, function7);
	ADD_CALLBACK_FUNCTION(Ivo, playSound);
	ADD_CALLBACK_FUNCTION(Ivo, function9);
	ADD_CALLBACK_FUNCTION(Ivo, savegame);
	ADD_CALLBACK_FUNCTION(Ivo, function11);
	ADD_CALLBACK_FUNCTION(Ivo, function12);
	ADD_CALLBACK_FUNCTION(Ivo, function13);
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

IMPLEMENT_FUNCTION_SI(Ivo, function3, 3)
	Entity::updateFields(savepoint);
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

IMPLEMENT_FUNCTION(Ivo, function12, 12)
	error("Ivo: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function13, 13)
	error("Ivo: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, chapter1, 14)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(15)
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentH, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject47, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_4691;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;

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
	error("Ivo: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, chapter2, 18)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION(19, 1777500)
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityIvo);

		_data->getData()->field_491 = EntityData::kField491_2740;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

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
	error("Ivo: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, chapter3, 22)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function23();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityIvo);

		_data->getData()->field_491 = EntityData::kField491_2740;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function23, 23)
	error("Ivo: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, chapter4, 24)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function25();
		break;

	case kActionDefault:
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function25, 25)
	error("Ivo: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function26, 26)
	error("Ivo: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function27, 27)
	error("Ivo: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function28, 28)
	error("Ivo: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function29, 29)
	error("Ivo: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, chapter5, 30)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function31();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityIvo);

		_data->getData()->field_491 = EntityData::kField491_540;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_1;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function31, 31)
	error("Ivo: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function32, 32)
	error("Ivo: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function33, 33)
	error("Ivo: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function34, 34)
	error("Ivo: callback function 34 not implemented!");
}

} // End of namespace LastExpress
