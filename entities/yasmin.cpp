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

#include "lastexpress/entities/yasmin.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Yasmin::Yasmin(LastExpressEngine *engine) : Entity(engine, kEntityYasmin) {
	ADD_CALLBACK_FUNCTION(Yasmin, function1);
	ADD_CALLBACK_FUNCTION(Yasmin, function2);
	ADD_CALLBACK_FUNCTION(Yasmin, function3);
	ADD_CALLBACK_FUNCTION(Yasmin, function4);
	ADD_CALLBACK_FUNCTION(Yasmin, function5);
	ADD_CALLBACK_FUNCTION(Yasmin, function6);
	ADD_CALLBACK_FUNCTION(Yasmin, function7);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter1);
	ADD_CALLBACK_FUNCTION(Yasmin, function9);
	ADD_CALLBACK_FUNCTION(Yasmin, function10);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter2);
	ADD_CALLBACK_FUNCTION(Yasmin, function12);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter3);
	ADD_CALLBACK_FUNCTION(Yasmin, function14);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter4);
	ADD_CALLBACK_FUNCTION(Yasmin, function16);
	ADD_CALLBACK_FUNCTION(Yasmin, function17);
	ADD_CALLBACK_FUNCTION(Yasmin, chapter5);
	ADD_CALLBACK_FUNCTION(Yasmin, function19);
	ADD_CALLBACK_FUNCTION(Yasmin, function20);
	ADD_CALLBACK_FUNCTION(Yasmin, function21);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Yasmin, function1, 1) {
	error("Yasmin: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Yasmin, function2, 2) {
	error("Yasmin: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_S(Yasmin, function3, 3) {
	error("Yasmin: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Yasmin, function4, 4) {
	error("Yasmin: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_II(Yasmin, function5, 5) {
	error("Yasmin: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, function6, 6) {
	error("Yasmin: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, function7, 7) {
	error("Yasmin: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, chapter1, 8) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(9)
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_4840;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, function9, 9) {
	error("Yasmin: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, function10, 10) {
	error("Yasmin: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, chapter2, 11) {
	if (savepoint->action == kActionDefault) {
		getEntities()->drawSequences(kEntityYasmin);

		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		setup_function12();
	}
}

IMPLEMENT_FUNCTION(Yasmin, function12, 12) {
	error("Yasmin: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, chapter3, 13) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function14();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityYasmin);

		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, function14, 14) {
	error("Yasmin: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, chapter4, 15) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function16();
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, function16, 16) {
	error("Yasmin: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, function17, 17) {
	error("Yasmin: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, chapter5, 18) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function19();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityYasmin);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, function19, 19) {
	error("Yasmin: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, function20, 20) {
	error("Yasmin: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, function21, 21) {
	error("Yasmin: callback function 21 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Yasmin, 22)

} // End of namespace LastExpress
