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

#include "lastexpress/entities/rebecca.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Rebecca::Rebecca(LastExpressEngine *engine) : Entity(engine, kEntityRebecca) {
	ADD_CALLBACK_FUNCTION(Rebecca, function1);
	ADD_CALLBACK_FUNCTION(Rebecca, function2);
	ADD_CALLBACK_FUNCTION(Rebecca, function3);
	ADD_CALLBACK_FUNCTION(Rebecca, function4);
	ADD_CALLBACK_FUNCTION(Rebecca, function5);
	ADD_CALLBACK_FUNCTION(Rebecca, function6);
	ADD_CALLBACK_FUNCTION(Rebecca, function7);
	ADD_CALLBACK_FUNCTION(Rebecca, function8);
	ADD_CALLBACK_FUNCTION(Rebecca, function9);
	ADD_CALLBACK_FUNCTION(Rebecca, function10);
	ADD_CALLBACK_FUNCTION(Rebecca, function11);
	ADD_CALLBACK_FUNCTION(Rebecca, function12);
	ADD_CALLBACK_FUNCTION(Rebecca, function13);
	ADD_CALLBACK_FUNCTION(Rebecca, function14);
	ADD_CALLBACK_FUNCTION(Rebecca, function15);
	ADD_CALLBACK_FUNCTION(Rebecca, function16);
	ADD_CALLBACK_FUNCTION(Rebecca, function17);
	ADD_CALLBACK_FUNCTION(Rebecca, function18);
	ADD_CALLBACK_FUNCTION(Rebecca, function19);
	ADD_CALLBACK_FUNCTION(Rebecca, function20);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter1);
	ADD_CALLBACK_FUNCTION(Rebecca, function22);
	ADD_CALLBACK_FUNCTION(Rebecca, function23);
	ADD_CALLBACK_FUNCTION(Rebecca, function24);
	ADD_CALLBACK_FUNCTION(Rebecca, function25);
	ADD_CALLBACK_FUNCTION(Rebecca, function26);
	ADD_CALLBACK_FUNCTION(Rebecca, function27);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter2);
	ADD_CALLBACK_FUNCTION(Rebecca, function29);
	ADD_CALLBACK_FUNCTION(Rebecca, function30);
	ADD_CALLBACK_FUNCTION(Rebecca, function31);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter3);
	ADD_CALLBACK_FUNCTION(Rebecca, function33);
	ADD_CALLBACK_FUNCTION(Rebecca, function34);
	ADD_CALLBACK_FUNCTION(Rebecca, function35);
	ADD_CALLBACK_FUNCTION(Rebecca, function36);
	ADD_CALLBACK_FUNCTION(Rebecca, function37);
	ADD_CALLBACK_FUNCTION(Rebecca, function38);
	ADD_CALLBACK_FUNCTION(Rebecca, function39);
	ADD_CALLBACK_FUNCTION(Rebecca, function40);
	ADD_CALLBACK_FUNCTION(Rebecca, function41);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter4);
	ADD_CALLBACK_FUNCTION(Rebecca, function43);
	ADD_CALLBACK_FUNCTION(Rebecca, function44);
	ADD_CALLBACK_FUNCTION(Rebecca, function45);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter5);
	ADD_CALLBACK_FUNCTION(Rebecca, function47);
	ADD_CALLBACK_FUNCTION(Rebecca, function48);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Rebecca, function1, 1)
	error("Rebecca: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_I(Rebecca, function2, 2)
	error("Rebecca: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_S(Rebecca, function3, 3)
	error("Rebecca: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_S(Rebecca, function4, 4)
	error("Rebecca: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_SIIS(Rebecca, function5, 5)
	error("Rebecca: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_S(Rebecca, function6, 6)
	error("Rebecca: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Rebecca, function7, 7)
	error("Rebecca: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Rebecca, function8, 8)
	error("Rebecca: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Rebecca, function9, 9)
	error("Rebecca: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function10, 10)
	error("Rebecca: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function11, 11)
	error("Rebecca: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION_II(Rebecca, function12, 12)
	error("Rebecca: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_SII(Rebecca, function13, 13)
	error("Rebecca: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION_SSI(Rebecca, function14, 14)
	error("Rebecca: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function15, 15)
	error("Rebecca: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION_I(Rebecca, function16, 16)
	error("Rebecca: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION_I(Rebecca, function17, 17)
	error("Rebecca: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function18, 18)
	error("Rebecca: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function19, 19)
	error("Rebecca: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION_I(Rebecca, function20, 20)
	error("Rebecca: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, chapter1, 21)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(22)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityRebecca, kAction224253538, 0);

		getObjects()->update(kObjectCompartmentE, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject44, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getObjects()->updateLocation2(kObject110, kLocation1);

		_data->getData()->field_491 = EntityData::kField491_2830;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;

		ENTITY_PARAM(0, 2) = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function22, 22)
	error("Rebecca: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function23, 23)
	error("Rebecca: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function24, 24)
	error("Rebecca: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function25, 25)
	error("Rebecca: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function26, 26)
	error("Rebecca: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function27, 27)
	error("Rebecca: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, chapter2, 28)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function29();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityRebecca);

		_data->getData()->field_491 = EntityData::kField491_4840;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentE, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getObjects()->updateLocation2(kObject110, kLocation2);

		ENTITY_PARAM(0, 2) = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function29, 29)
	error("Rebecca: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function30, 30)
	error("Rebecca: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function31, 31)
	error("Rebecca: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, chapter3, 32)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function33();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityRebecca);

		_data->getData()->field_491 = EntityData::kField491_4840;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function33, 33)
	error("Rebecca: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function34, 34)
	error("Rebecca: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function35, 35)
	error("Rebecca: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function36, 36)
	error("Rebecca: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function37, 37)
	error("Rebecca: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function38, 38)
	error("Rebecca: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function39, 39)
	error("Rebecca: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function40, 40)
	error("Rebecca: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function41, 41)
	error("Rebecca: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, chapter4, 42)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function43();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityRebecca);

		_data->getData()->field_491 = EntityData::kField491_4840;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->updateLocation2(kObject110, kLocation3);

		ENTITY_PARAM(0, 1) = 0;
		ENTITY_PARAM(0, 2) = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function43, 43)
	error("Rebecca: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function44, 44)
	error("Rebecca: callback function 44 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function45, 45)
	error("Rebecca: callback function 45 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, chapter5, 46)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function47();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityRebecca);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->updateLocation2(kObject110, kLocation4);

		break;
	}
}

IMPLEMENT_FUNCTION(Rebecca, function47, 47)
	error("Rebecca: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, function48, 48)
	error("Rebecca: callback function 48 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Rebecca, 49)

} // End of namespace LastExpress
