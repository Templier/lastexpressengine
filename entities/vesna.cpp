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

#include "lastexpress/entities/vesna.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Vesna::Vesna(LastExpressEngine *engine) : Entity(engine, kEntityVesna) {
	ADD_CALLBACK_FUNCTION(Vesna, function1);
	ADD_CALLBACK_FUNCTION(Vesna, function2);
	ADD_CALLBACK_FUNCTION(Vesna, function3);
	ADD_CALLBACK_FUNCTION(Vesna, function4);
	ADD_CALLBACK_FUNCTION(Vesna, function5);
	ADD_CALLBACK_FUNCTION(Vesna, function6);
	ADD_CALLBACK_FUNCTION(Vesna, function7);
	ADD_CALLBACK_FUNCTION(Vesna, function8);
	ADD_CALLBACK_FUNCTION(Vesna, function9);
	ADD_CALLBACK_FUNCTION(Vesna, function10);
	ADD_CALLBACK_FUNCTION(Vesna, function11);
	ADD_CALLBACK_FUNCTION(Vesna, chapter1);
	ADD_CALLBACK_FUNCTION(Vesna, function13);
	ADD_CALLBACK_FUNCTION(Vesna, function14);
	ADD_CALLBACK_FUNCTION(Vesna, function15);
	ADD_CALLBACK_FUNCTION(Vesna, chapter2);
	ADD_CALLBACK_FUNCTION(Vesna, function17);
	ADD_CALLBACK_FUNCTION(Vesna, function18);
	ADD_CALLBACK_FUNCTION(Vesna, chapter3);
	ADD_CALLBACK_FUNCTION(Vesna, function20);
	ADD_CALLBACK_FUNCTION(Vesna, function21);
	ADD_CALLBACK_FUNCTION(Vesna, function22);
	ADD_CALLBACK_FUNCTION(Vesna, function23);
	ADD_CALLBACK_FUNCTION(Vesna, chapter4);
	ADD_CALLBACK_FUNCTION(Vesna, function25);
	ADD_CALLBACK_FUNCTION(Vesna, function26);
	ADD_CALLBACK_FUNCTION(Vesna, function27);
	ADD_CALLBACK_FUNCTION(Vesna, chapter5);
	ADD_CALLBACK_FUNCTION(Vesna, function29);
	ADD_CALLBACK_FUNCTION(Vesna, function30);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Vesna, function1, 1)
	error("Vesna: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_S(Vesna, function2, 2)
	error("Vesna: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Vesna, function3, 3)
	error("Vesna: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_S(Vesna, function4, 4)
	error("Vesna: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_II(Vesna, function5, 5)
	error("Vesna: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_I(Vesna, function6, 6)
	error("Vesna: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_II(Vesna, function7, 7)
	error("Vesna: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function8, 8)
	error("Vesna: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function9, 9)
	error("Vesna: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION_II(Vesna, function10, 10)
	error("Vesna: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function11, 11)
	error("Vesna: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, chapter1, 12)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(13)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityVesna, kAction124190740, 0);

		_data->getData()->field_491 = EntityData::kField491_4689;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function13, 13)
	error("Vesna: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function14, 14)
	error("Vesna: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function15, 15)
	error("Vesna: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, chapter2, 16)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function17();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityVesna);

		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function17, 17)
	error("Vesna: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function18, 18)
	error("Vesna: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, chapter3, 19)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function20();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityVesna);

		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function20, 20)
	error("Vesna: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function21, 21)
	error("Vesna: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function22, 22)
	error("Vesna: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function23, 23)
	error("Vesna: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, chapter4, 24)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Vesna, setup_function11));
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityVesna);

		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation3, kCursorHandKnock, kCursorHand);
		break;

	case kAction18:
		if (_data->getNextCallback() == 1)
			setup_function25();
	}
}

IMPLEMENT_FUNCTION(Vesna, function25, 25)
	error("Vesna: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function26, 26)
	error("Vesna: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function27, 27)
	error("Vesna: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, chapter5, 28)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function29();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityVesna);

		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function29, 29)
	error("Vesna: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function30, 30)
	error("Vesna: callback function 30 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Vesna, 31)

} // End of namespace LastExpress
