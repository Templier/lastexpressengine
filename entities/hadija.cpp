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

#include "lastexpress/entities/hadija.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Hadija::Hadija(LastExpressEngine *engine) : Entity(engine, kEntityHadija) {
	ADD_CALLBACK_FUNCTION(Hadija, function1);
	ADD_CALLBACK_FUNCTION(Hadija, function2);
	ADD_CALLBACK_FUNCTION(Hadija, function3);
	ADD_CALLBACK_FUNCTION(Hadija, function4);
	ADD_CALLBACK_FUNCTION(Hadija, function5);
	ADD_CALLBACK_FUNCTION(Hadija, function6);
	ADD_CALLBACK_FUNCTION(Hadija, function7);
	ADD_CALLBACK_FUNCTION(Hadija, function8);
	ADD_CALLBACK_FUNCTION(Hadija, function9);
	ADD_CALLBACK_FUNCTION(Hadija, chapter1);
	ADD_CALLBACK_FUNCTION(Hadija, function11);
	ADD_CALLBACK_FUNCTION(Hadija, function12);
	ADD_CALLBACK_FUNCTION(Hadija, chapter2);
	ADD_CALLBACK_FUNCTION(Hadija, function14);
	ADD_CALLBACK_FUNCTION(Hadija, chapter3);
	ADD_CALLBACK_FUNCTION(Hadija, function16);
	ADD_CALLBACK_FUNCTION(Hadija, chapter4);
	ADD_CALLBACK_FUNCTION(Hadija, function18);
	ADD_CALLBACK_FUNCTION(Hadija, function19);
	ADD_CALLBACK_FUNCTION(Hadija, chapter5);
	ADD_CALLBACK_FUNCTION(Hadija, function21);
	ADD_CALLBACK_FUNCTION(Hadija, function22);
	ADD_CALLBACK_FUNCTION(Hadija, function23);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Hadija, function1, 1) {
	error("Hadija: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Hadija, function2, 2) {
	error("Hadija: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_S(Hadija, function3, 3) {
	error("Hadija: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Hadija, function4, 4) {
	error("Hadija: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_II(Hadija, function5, 5) {
	error("Hadija: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function6, 6) {
	error("Hadija: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function7, 7) {
	error("Hadija: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function8, 8) {
	error("Hadija: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function9, 9) {
	error("Hadija: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, chapter1, 10) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(11)
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;

		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, function11, 11) {
	error("Hadija: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function12, 12) {
	error("Hadija: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, chapter2, 13) {
	if (savepoint->action == kActionDefault) {

		getEntities()->drawSequences(kEntityHadija);

		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		_data->getData()->field_4A5 = EntityData::kField4A5_0;
		_data->getData()->inventoryItem = kItemNone;

		setup_function14();
	}
}

IMPLEMENT_FUNCTION(Hadija, function14, 14) {
	error("Hadija: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, chapter3, 15) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function16();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityHadija);

		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;

		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, function16, 16) {
	error("Hadija: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, chapter4, 17) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function18();
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, function18, 18) {
	error("Hadija: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function19, 19) {
	error("Hadija: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, chapter5, 20) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function21();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityHadija);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->field_4A5 = EntityData::kField4A5_0;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Hadija, function21, 21) {
	error("Hadija: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function22, 22) {
	error("Hadija: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, function23, 23) {
	error("Hadija: callback function 23 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Hadija, 24)

} // End of namespace LastExpress
