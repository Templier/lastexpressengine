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

#include "lastexpress/entities/verges.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Verges::Verges(LastExpressEngine *engine) : Entity(engine, kEntityVerges) {
	ADD_CALLBACK_FUNCTION(Verges, function1);
	ADD_CALLBACK_FUNCTION(Verges, function2);
	ADD_CALLBACK_FUNCTION(Verges, function3);
	ADD_CALLBACK_FUNCTION(Verges, playSound);
	ADD_CALLBACK_FUNCTION(Verges, playSound16);
	ADD_CALLBACK_FUNCTION(Verges, function6);
	ADD_CALLBACK_FUNCTION(Verges, savegame);
	ADD_CALLBACK_FUNCTION(Verges, function8);
	ADD_CALLBACK_FUNCTION(Verges, function9);
	ADD_CALLBACK_FUNCTION(Verges, function10);
	ADD_CALLBACK_FUNCTION(Verges, function11);
	ADD_CALLBACK_FUNCTION(Verges, function12);
	ADD_CALLBACK_FUNCTION(Verges, function13);
	ADD_CALLBACK_FUNCTION(Verges, updateFromTime);
	ADD_CALLBACK_FUNCTION(Verges, function15);
	ADD_CALLBACK_FUNCTION(Verges, function16);
	ADD_CALLBACK_FUNCTION(Verges, function17);
	ADD_CALLBACK_FUNCTION(Verges, chapter1);
	ADD_CALLBACK_FUNCTION(Verges, function19);
	ADD_CALLBACK_FUNCTION(Verges, function20);
	ADD_CALLBACK_FUNCTION(Verges, function21);
	ADD_CALLBACK_FUNCTION(Verges, function22);
	ADD_CALLBACK_FUNCTION(Verges, function23);
	ADD_CALLBACK_FUNCTION(Verges, function24);
	ADD_CALLBACK_FUNCTION(Verges, function25);
	ADD_CALLBACK_FUNCTION(Verges, function26);
	ADD_CALLBACK_FUNCTION(Verges, chapter2);
	ADD_CALLBACK_FUNCTION(Verges, function28);
	ADD_CALLBACK_FUNCTION(Verges, chapter3);
	ADD_CALLBACK_FUNCTION(Verges, function30);
	ADD_CALLBACK_FUNCTION(Verges, function31);
	ADD_CALLBACK_FUNCTION(Verges, function32);
	ADD_CALLBACK_FUNCTION(Verges, function33);
	ADD_CALLBACK_FUNCTION(Verges, function34);
	ADD_CALLBACK_FUNCTION(Verges, function35);
	ADD_CALLBACK_FUNCTION(Verges, chapter4);
	ADD_CALLBACK_FUNCTION(Verges, function37);
	ADD_CALLBACK_FUNCTION(Verges, function38);
	ADD_CALLBACK_FUNCTION(Verges, chapter5);
	ADD_CALLBACK_FUNCTION(Verges, function40);
	ADD_CALLBACK_FUNCTION(Verges, function41);
	ADD_CALLBACK_FUNCTION(Verges, function42);
}

IMPLEMENT_FUNCTION(Verges, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Verges, function2, 2)
	error("Verges: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function3, 3)
	error("Verges: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_S(Verges, playSound, 4)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Verges, playSound16, 5)
	Entity::playSound(savepoint, false, 16);
}

IMPLEMENT_FUNCTION(Verges, function6, 6)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION_II(Verges, savegame, 7)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(Verges, function8, 8)
	error("Verges: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_S(Verges, function9, 9)
	error("Verges: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION_IIS(Verges, function10, 10)
	error("Verges: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function11, 11)
	error("Verges: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function12, 12)
	error("Verges: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_I(Verges, function13, 13)
	error("Verges: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION_I(Verges, updateFromTime, 14)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_IS(Verges, function15, 15)
	error("Verges: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION_ISS(Verges, function16, 16)
	error("Verges: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function17, 17)
	error("Verges: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter1, 18)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(26)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityVerges, kAction191337656, 0);
		getSavePoints()->addData(kEntityVerges, kAction226031488, 1);
		getSavePoints()->addData(kEntityVerges, kAction339669520, 1);
		getSavePoints()->addData(kEntityVerges, kAction167854368, 4);
		getSavePoints()->addData(kEntityVerges, kAction158617345, 2);
		getSavePoints()->addData(kEntityVerges, kAction168255788, 3);
		getSavePoints()->addData(kEntityVerges, kAction201431954, 5);
		getSavePoints()->addData(kEntityVerges, kAction168187490, 6);

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_5000;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_6;
		break;
	}
}

IMPLEMENT_FUNCTION_NOSETUP(Verges, function19, 19)
	error("Verges: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function20, 20)
	error("Verges: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function21, 21)
	error("Verges: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function22, 22)
	error("Verges: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function23, 23)
	error("Verges: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function24, 24)
	error("Verges: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function25, 25)
	error("Verges: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function26, 26)
	error("Verges: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter2, 27)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function28();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityVerges);

		_data->getData()->field_491 = EntityData::kField491_5000;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_6;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		ENTITY_PARAM(0, 3) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function28, 28)
	error("Verges: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter3, 29)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function23();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityVerges);

		_data->getData()->field_491 = EntityData::kField491_540;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 4) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION_S(Verges, function30, 30)
	error("Verges: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function31, 31)
	error("Verges: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function32, 32)
	error("Verges: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function33, 33)
	error("Verges: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function34, 34)
	error("Verges: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function35, 35)
	error("Verges: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter4, 36)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function37();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityVerges);

		_data->getData()->field_491 = EntityData::kField491_5000;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_6;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 6) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function37, 37)
	error("Verges: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function38, 38)
	error("Verges: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter5, 39)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function40();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityVerges);

		_data->getData()->field_491 = EntityData::kField491_3650;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityNone, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityNone, kLocationNone, kCursorNormal, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function40, 40)
	error("Verges: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function41, 41)
	error("Verges: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function42, 42)
	error("Verges: callback function 42 not implemented!");
}

} // End of namespace LastExpress
