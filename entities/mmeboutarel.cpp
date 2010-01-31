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

#include "lastexpress/entities/mmeboutarel.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

MmeBoutarel::MmeBoutarel(LastExpressEngine *engine) : Entity(engine, kEntityMmeBoutarel) {
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function1);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function2);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function3);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function4);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function5);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function6);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function7);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function8);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function9);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter1);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function11);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function12);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function13);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function14);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function15);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function16);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter2);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function18);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function19);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter3);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function21);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter4);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function23);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function24);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function25);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter5);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function27);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function28);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(MmeBoutarel, function1, 1) {
	error("MmeBoutarel: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_S(MmeBoutarel, function2, 2) {
	error("MmeBoutarel: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_S(MmeBoutarel, function3, 3) {
	error("MmeBoutarel: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_I(MmeBoutarel, function4, 4) {
	error("MmeBoutarel: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_SI(MmeBoutarel, function5, 5) {
	error("MmeBoutarel: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_SI(MmeBoutarel, function6, 6) {
	error("MmeBoutarel: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_II(MmeBoutarel, function7, 7) {
	error("MmeBoutarel: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_S(MmeBoutarel, function8, 8) {
	error("MmeBoutarel: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function9, 9) {
	error("MmeBoutarel: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter1, 10) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(12)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityMmeBoutarel, kAction242526416, 0);

		getObjects()->update(kObjectCompartmentD, kEntityNone, kLocation2, kCursorNormal, kCursorNormal);
		getObjects()->update(kObject51, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_5790;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, function11, 11) {
	error("MmeBoutarel: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function12, 12) {
	error("MmeBoutarel: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function13, 13) {
	error("MmeBoutarel: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function14, 14) {
	error("MmeBoutarel: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function15, 15) {
	error("MmeBoutarel: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function16, 16) {
	error("MmeBoutarel: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter2, 17) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function18();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityMmeBoutarel);

		_data->getData()->field_491 = EntityData::kField491_4689;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentD, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject51, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject43, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, function18, 18) {
	error("MmeBoutarel: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function19, 19) {
	error("MmeBoutarel: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter3, 20) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function21();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityMmeBoutarel);

		_data->getData()->field_491 = EntityData::kField491_5790;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, function21, 21) {
	error("MmeBoutarel: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter4, 22) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function23();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityMmeBoutarel);

		_data->getData()->field_491 = EntityData::kField491_5790;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, function23, 23) {
	error("MmeBoutarel: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function24, 24) {
	error("MmeBoutarel: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function25, 25) {
	error("MmeBoutarel: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter5, 26) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function27();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityMmeBoutarel);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, function27, 27) {
	error("MmeBoutarel: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function28, 28) {
	error("MmeBoutarel: callback function 28 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(MmeBoutarel, 29)

} // End of namespace LastExpress
