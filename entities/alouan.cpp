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

#include "lastexpress/entities/alouan.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Alouan::Alouan(LastExpressEngine *engine) : Entity(engine, kEntityAlouan) {
	ADD_CALLBACK_FUNCTION(Alouan, function1);
	ADD_CALLBACK_FUNCTION(Alouan, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Alouan, playSound);
	ADD_CALLBACK_FUNCTION(Alouan, updateFromTime);
	ADD_CALLBACK_FUNCTION(Alouan, function5);
	ADD_CALLBACK_FUNCTION(Alouan, function6);
	ADD_CALLBACK_FUNCTION(Alouan, function7);
	ADD_CALLBACK_FUNCTION(Alouan, function8);
	ADD_CALLBACK_FUNCTION(Alouan, function9);
	ADD_CALLBACK_FUNCTION(Alouan, chapter1);
	ADD_CALLBACK_FUNCTION(Alouan, function11);
	ADD_CALLBACK_FUNCTION(Alouan, function12);
	ADD_CALLBACK_FUNCTION(Alouan, chapter2);
	ADD_CALLBACK_FUNCTION(Alouan, function14);
	ADD_CALLBACK_FUNCTION(Alouan, chapter3);
	ADD_CALLBACK_FUNCTION(Alouan, function16);
	ADD_CALLBACK_FUNCTION(Alouan, chapter4);
	ADD_CALLBACK_FUNCTION(Alouan, function18);
	ADD_CALLBACK_FUNCTION(Alouan, function19);
	ADD_CALLBACK_FUNCTION(Alouan, chapter5);
	ADD_CALLBACK_FUNCTION(Alouan, function21);
	ADD_CALLBACK_FUNCTION(Alouan, function22);
	ADD_CALLBACK_FUNCTION(Alouan, function23);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Alouan, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_SI(Alouan, enterExitCompartment, 2)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_S(Alouan, playSound, 3)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_I(Alouan, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_II(Alouan, function5, 5)
	error("Alouan: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, function6, 6)
	error("Alouan: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, function7, 7)
	error("Alouan: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, function8, 8)
	error("Alouan: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, function9, 9)
	error("Alouan: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, chapter1, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(11)
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_2740;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function11, 11)
	error("Alouan: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, function12, 12)
	error("Alouan: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, chapter2, 13)
	if (savepoint.action != kActionDefault)
		return;

	getEntities()->prepareSequences(kEntityAlouan);

	_data->getData()->field_491 = EntityData::kField491_2740;
	_data->getData()->field_493 = EntityData::kField493_1;
	_data->getData()->car = kCarGreenSleeping;
	_data->getData()->clothes = kClothesDefault;
	_data->getData()->inventoryItem = kItemNone;

	setup_function14();
}

IMPLEMENT_FUNCTION(Alouan, function14, 14)
	error("Alouan: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, chapter3, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function16();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAlouan);

		_data->getData()->field_491 = EntityData::kField491_2740;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function16, 16)
	error("Alouan: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, chapter4, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function18();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAlouan);

		_data->getData()->field_491 = EntityData::kField491_2740;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->car = kCarGreenSleeping;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function18, 18)
	error("Alouan: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, function19, 19)
	error("Alouan: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, chapter5, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function21();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAlouan);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->car = kCarRestaurant;
		_data->getData()->clothes = kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Alouan, function21, 21)
	error("Alouan: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, function22, 22)
	error("Alouan: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Alouan, function23, 23)
	error("Alouan: callback function 23 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Alouan, 24)

} // End of namespace LastExpress
