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

#include "lastexpress/entities/anna.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Anna::Anna(LastExpressEngine *engine) : Entity(engine, kEntityAnna) {
	ADD_CALLBACK_FUNCTION(Anna, function1);
	ADD_CALLBACK_FUNCTION(Anna, function2);
	ADD_CALLBACK_FUNCTION(Anna, function3);
	ADD_CALLBACK_FUNCTION(Anna, function4);
	ADD_CALLBACK_FUNCTION(Anna, function5);
	ADD_CALLBACK_FUNCTION(Anna, function6);
	ADD_CALLBACK_FUNCTION(Anna, function7);
	ADD_CALLBACK_FUNCTION(Anna, function8);
	ADD_CALLBACK_FUNCTION(Anna, function9);
	ADD_CALLBACK_FUNCTION(Anna, function10);
	ADD_CALLBACK_FUNCTION(Anna, function11);
	ADD_CALLBACK_FUNCTION(Anna, function12);
	ADD_CALLBACK_FUNCTION(Anna, function13);
	ADD_CALLBACK_FUNCTION(Anna, function14);
	ADD_CALLBACK_FUNCTION(Anna, function15);
	ADD_CALLBACK_FUNCTION(Anna, chapter1);
	ADD_CALLBACK_FUNCTION(Anna, function17);
	ADD_CALLBACK_FUNCTION(Anna, function18);
	ADD_CALLBACK_FUNCTION(Anna, function19);
	ADD_CALLBACK_FUNCTION(Anna, function20);
	ADD_CALLBACK_FUNCTION(Anna, function21);
	ADD_CALLBACK_FUNCTION(Anna, function22);
	ADD_CALLBACK_FUNCTION(Anna, function23);
	ADD_CALLBACK_FUNCTION(Anna, function24);
	ADD_CALLBACK_FUNCTION(Anna, function25);
	ADD_CALLBACK_FUNCTION(Anna, function26);
	ADD_CALLBACK_FUNCTION(Anna, function27);
	ADD_CALLBACK_FUNCTION(Anna, function28);
	ADD_CALLBACK_FUNCTION(Anna, function29);
	ADD_CALLBACK_FUNCTION(Anna, function30);
	ADD_CALLBACK_FUNCTION(Anna, function31);
	ADD_CALLBACK_FUNCTION(Anna, function32);
	ADD_CALLBACK_FUNCTION(Anna, function33);
	ADD_CALLBACK_FUNCTION(Anna, function34);
	ADD_CALLBACK_FUNCTION(Anna, function35);
	ADD_CALLBACK_FUNCTION(Anna, function36);
	ADD_CALLBACK_FUNCTION(Anna, function37);
	ADD_CALLBACK_FUNCTION(Anna, function38);
	ADD_CALLBACK_FUNCTION(Anna, function39);
	ADD_CALLBACK_FUNCTION(Anna, function40);
	ADD_CALLBACK_FUNCTION(Anna, function41);
	ADD_CALLBACK_FUNCTION(Anna, chapter2);
	ADD_CALLBACK_FUNCTION(Anna, function43);
	ADD_CALLBACK_FUNCTION(Anna, chapter3);
	ADD_CALLBACK_FUNCTION(Anna, function45);
	ADD_CALLBACK_FUNCTION(Anna, function46);
	ADD_CALLBACK_FUNCTION(Anna, function47);
	ADD_CALLBACK_FUNCTION(Anna, function48);
	ADD_CALLBACK_FUNCTION(Anna, function49);
	ADD_CALLBACK_FUNCTION(Anna, function50);
	ADD_CALLBACK_FUNCTION(Anna, function51);
	ADD_CALLBACK_FUNCTION(Anna, function52);
	ADD_CALLBACK_FUNCTION(Anna, function53);
	ADD_CALLBACK_FUNCTION(Anna, function54);
	ADD_CALLBACK_FUNCTION(Anna, function55);
	ADD_CALLBACK_FUNCTION(Anna, function56);
	ADD_CALLBACK_FUNCTION(Anna, function57);
	ADD_CALLBACK_FUNCTION(Anna, function58);
	ADD_CALLBACK_FUNCTION(Anna, function59);
	ADD_CALLBACK_FUNCTION(Anna, function60);
	ADD_CALLBACK_FUNCTION(Anna, function61);
	ADD_CALLBACK_FUNCTION(Anna, function62);
	ADD_CALLBACK_FUNCTION(Anna, function63);
	ADD_CALLBACK_FUNCTION(Anna, bagage);
	ADD_CALLBACK_FUNCTION(Anna, function65);
	ADD_CALLBACK_FUNCTION(Anna, chapter4);
	ADD_CALLBACK_FUNCTION(Anna, function67);
	ADD_CALLBACK_FUNCTION(Anna, function68);
	ADD_CALLBACK_FUNCTION(Anna, function69);
	ADD_CALLBACK_FUNCTION(Anna, function70);
	ADD_CALLBACK_FUNCTION(Anna, function71);
	ADD_CALLBACK_FUNCTION(Anna, function72);
	ADD_CALLBACK_FUNCTION(Anna, function73);
	ADD_CALLBACK_FUNCTION(Anna, chapter5);
	ADD_CALLBACK_FUNCTION(Anna, function75);
	ADD_CALLBACK_FUNCTION(Anna, function76);
	ADD_CALLBACK_FUNCTION(Anna, function77);
	ADD_CALLBACK_FUNCTION(Anna, function78);
	ADD_CALLBACK_FUNCTION(Anna, function79);
	ADD_CALLBACK_FUNCTION(Anna, function80);
	ADD_CALLBACK_FUNCTION(Anna, function81);
}

IMPLEMENT_FUNCTION(Anna, function1, 1)
	error("Anna: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_S(Anna, function2, 2)
	error("Anna: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_SII(Anna, function3, 3)
	error("Anna: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Anna, function4, 4)
	error("Anna: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function5, 5)
	error("Anna: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_SIIS(Anna, function6, 6)
	error("Anna: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_S(Anna, function7, 7)
	error("Anna: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function8, 8)
	error("Anna: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_II(Anna, function9, 9)
	error("Anna: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION_II(Anna, function10, 10)
	error("Anna: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION_I(Anna, function11, 11)
	error("Anna: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function12, 12)
	error("Anna: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_SSI(Anna, function13, 13)
	error("Anna: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION_I(Anna, function14, 14)
	error("Anna: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION_IS(Anna, function15, 15)
	error("Anna: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter1, 16)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(19)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityAnna, kAction291662081, 0);
		getSavePoints()->addData(kEntityAnna, kAction238936000, 1);

		getObjects()->update(kObjectCompartmentF, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject53, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject45, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_8200;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		_data->getData()->clothes = EntityData::kClothesDefault;

		break;
	}
}

IMPLEMENT_FUNCTION_II(Anna, function17, 17)
	error("Anna: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION_I(Anna, function18, 18)
	error("Anna: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function19, 19)
	error("Anna: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function20, 20)
	error("Anna: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function21, 21)
	error("Anna: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function22, 22)
	error("Anna: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function23, 23)
	error("Anna: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function24, 24)
	error("Anna: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function25, 25)
	error("Anna: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function26, 26)
	error("Anna: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function27, 27)
	error("Anna: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function28, 28)
	error("Anna: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function29, 29)
	error("Anna: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function30, 30)
	error("Anna: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function31, 31)
	error("Anna: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function32, 32)
	error("Anna: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function33, 33)
	error("Anna: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function34, 34)
	error("Anna: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function35, 35)
	error("Anna: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function36, 36)
	error("Anna: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function37, 37)
	error("Anna: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function38, 38)
	error("Anna: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION_II(Anna, function39, 39)
	error("Anna: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function40, 40)
	error("Anna: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function41, 41)
	error("Anna: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter2, 42)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function43();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityAnna);

		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothes1;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function43, 43)
	error("Anna: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter3, 44)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function46();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityAnna);

		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothes3;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentF, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject45, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject53, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION_I(Anna, function45, 45)
	error("Anna: callback function 45 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function46, 46)
	error("Anna: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function47, 47)
	error("Anna: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function48, 48)
	error("Anna: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function49, 49)
	error("Anna: callback function 49 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function50, 50)
	error("Anna: callback function 50 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function51, 51)
	error("Anna: callback function 51 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function52, 52)
	error("Anna: callback function 52 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function53, 53)
	error("Anna: callback function 53 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function54, 54)
	error("Anna: callback function 54 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function55, 55)
	error("Anna: callback function 55 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function56, 56)
	error("Anna: callback function 56 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function57, 57)
	error("Anna: callback function 57 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function58, 58)
	error("Anna: callback function 58 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function59, 59)
	error("Anna: callback function 59 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function60, 60)
	error("Anna: callback function 60 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function61, 61)
	error("Anna: callback function 61 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function62, 62)
	error("Anna: callback function 62 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function63, 63)
	error("Anna: callback function 63 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, bagage, 64)
	error("Anna: callback function 64 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function65, 65)
	error("Anna: callback function 65 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter4, 66)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function67();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityAnna);

		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothes2;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function67, 67)
	error("Anna: callback function 67 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function68, 68)
	error("Anna: callback function 68 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function69, 69)
	error("Anna: callback function 69 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function70, 70)
	error("Anna: callback function 70 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function71, 71)
	error("Anna: callback function 71 not implemented!");
}

IMPLEMENT_FUNCTION_II(Anna, function72, 72)
	error("Anna: callback function 72 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function73, 73)
	error("Anna: callback function 73 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter5, 74)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function75();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityAnna);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_1;
		_data->getData()->clothes = EntityData::kClothes3;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject45, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function75, 75)
	error("Anna: callback function 75 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function76, 76)
	error("Anna: callback function 76 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function77, 77)
	error("Anna: callback function 77 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function78, 78)
	error("Anna: callback function 78 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function79, 79)
	error("Anna: callback function 79 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function80, 80)
	error("Anna: callback function 80 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function81, 81)
	error("Anna: callback function 81 not implemented!");
}

} // End of namespace LastExpress
