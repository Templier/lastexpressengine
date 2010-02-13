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
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Yasmin::Yasmin(LastExpressEngine *engine) : Entity(engine, kEntityYasmin) {
	ADD_CALLBACK_FUNCTION(Yasmin, function1);
	ADD_CALLBACK_FUNCTION(Yasmin, enterExitCompartement);
	ADD_CALLBACK_FUNCTION(Yasmin, playSound);
	ADD_CALLBACK_FUNCTION(Yasmin, updateFromTime);
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

IMPLEMENT_FUNCTION(Yasmin, function1, 1)
	switch (savepoint->action) {
	default:
		break;

	case kAction5:
		getSound()->excuseMeCath();
		break;

	case kAction6:
		getSound()->excuseMe(kEntityYasmin);
		break;
	}

	// Process default actions
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_SI(Yasmin, enterExitCompartement, 2)
	Entity::updateFields(savepoint);
}

IMPLEMENT_FUNCTION_S(Yasmin, playSound, 3)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Yasmin, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_II(Yasmin, function5, 5)
	switch (savepoint->action) {
	default:
		break;

	case kAction5:
		getSound()->excuseMeCath();
		break;

	case kAction6:
		getSound()->excuseMe(kEntityYasmin);
		break;
	}

	// Process default actions
	Entity::savepointCheckEntity(savepoint);
}

IMPLEMENT_FUNCTION(Yasmin, function6, 6)
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_4840;
		_data->getData()->field_493 = EntityData::kField493_0;

		_data->setNextCallback(1);
		// Exit compartement
		call(new ENTITY_SETUP_SIIS(Yasmin, setup_enterExitCompartement), "615Be", kObjectCompartment5);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			call(new ENTITY_SETUP(Yasmin, setup_function5), EntityData::kField495_3, EntityData::kField491_3050);
			break;

		case 2:
			// Enter compartement
			call(new ENTITY_SETUP_SIIS(Yasmin, setup_enterExitCompartement), "615Ag", kObjectCompartment7);
			break;

		case 3:
			_data->getData()->field_493 = EntityData::kField493_1;
			getEntities()->prepareSequences(kEntityYasmin);

			CALL_PREVIOUS_SAVEPOINT()
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, function7, 7)
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_0;

		_data->setNextCallback(1);
		// Exit compartement
		call(new ENTITY_SETUP_SIIS(Yasmin, setup_enterExitCompartement), "615Bg", kObjectCompartment7);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			call(new ENTITY_SETUP(Yasmin, setup_function5), EntityData::kField495_3, EntityData::kField491_4840);
			break;

		case 2:
			// Enter compartement
			call(new ENTITY_SETUP_SIIS(Yasmin, setup_enterExitCompartement), "615Ae", kObjectCompartment5);
			break;

		case 3:
			_data->getData()->field_493 = EntityData::kField493_1;
			getEntities()->prepareSequences(kEntityYasmin);

			CALL_PREVIOUS_SAVEPOINT()
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter1, 8)
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

IMPLEMENT_FUNCTION(Yasmin, function9, 9)
	error("Yasmin: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, function10, 10)
	if (savepoint->action == kActionDefault) {
		getObjects()->update(kObjectCompartment7, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;

		getEntities()->prepareSequences(kEntityYasmin);
	}
}

IMPLEMENT_FUNCTION(Yasmin, chapter2, 11)
	if (savepoint->action == kActionDefault) {
		getEntities()->prepareSequences(kEntityYasmin);

		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		setup_function12();
	}
}

IMPLEMENT_FUNCTION(Yasmin, function12, 12)
	error("Yasmin: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, chapter3, 13)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function14();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityYasmin);

		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, function14, 14)
	error("Yasmin: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, chapter4, 15)
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

IMPLEMENT_FUNCTION(Yasmin, function16, 16)
	error("Yasmin: callback function 16 not implemented!");
}

// Same as existing function 10 ?
IMPLEMENT_FUNCTION(Yasmin, function17, 17)
	function10(savepoint);
}

IMPLEMENT_FUNCTION(Yasmin, chapter5, 18)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function19();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityYasmin);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Yasmin, function19, 19)
	if (savepoint->action == kAction70549068)
		setup_function20();
}

IMPLEMENT_FUNCTION(Yasmin, function20, 20)
	error("Yasmin: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Yasmin, function21, 21)
	error("Yasmin: callback function 21 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Yasmin, 22)

} // End of namespace LastExpress
