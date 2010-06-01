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

#include "lastexpress/entities/boutarel.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Boutarel::Boutarel(LastExpressEngine *engine) : Entity(engine, kEntityBoutarel) {
	ADD_CALLBACK_FUNCTION(Boutarel, function1);
	ADD_CALLBACK_FUNCTION(Boutarel, playSound);
	ADD_CALLBACK_FUNCTION(Boutarel, draw);
	ADD_CALLBACK_FUNCTION(Boutarel, updateFromTime);
	ADD_CALLBACK_FUNCTION(Boutarel, function5);
	ADD_CALLBACK_FUNCTION(Boutarel, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Boutarel, function7);
	ADD_CALLBACK_FUNCTION(Boutarel, function8);
	ADD_CALLBACK_FUNCTION(Boutarel, function9);
	ADD_CALLBACK_FUNCTION(Boutarel, function10);
	ADD_CALLBACK_FUNCTION(Boutarel, function11);
	ADD_CALLBACK_FUNCTION(Boutarel, function12);
	ADD_CALLBACK_FUNCTION(Boutarel, function13);
	ADD_CALLBACK_FUNCTION(Boutarel, function14);
	ADD_CALLBACK_FUNCTION(Boutarel, function15);
	ADD_CALLBACK_FUNCTION(Boutarel, function16);
	ADD_CALLBACK_FUNCTION(Boutarel, function17);
	ADD_CALLBACK_FUNCTION(Boutarel, function18);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter1);
	ADD_CALLBACK_FUNCTION(Boutarel, function20);
	ADD_CALLBACK_FUNCTION(Boutarel, function21);
	ADD_CALLBACK_FUNCTION(Boutarel, function22);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter2);
	ADD_CALLBACK_FUNCTION(Boutarel, function24);
	ADD_CALLBACK_FUNCTION(Boutarel, function25);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter3);
	ADD_CALLBACK_FUNCTION(Boutarel, function27);
	ADD_CALLBACK_FUNCTION(Boutarel, function28);
	ADD_CALLBACK_FUNCTION(Boutarel, function29);
	ADD_CALLBACK_FUNCTION(Boutarel, function30);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter4);
	ADD_CALLBACK_FUNCTION(Boutarel, function32);
	ADD_CALLBACK_FUNCTION(Boutarel, function33);
	ADD_CALLBACK_FUNCTION(Boutarel, function34);
	ADD_CALLBACK_FUNCTION(Boutarel, function35);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter5);
	ADD_CALLBACK_FUNCTION(Boutarel, function37);
	ADD_CALLBACK_FUNCTION(Boutarel, function38);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Boutarel, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Boutarel, playSound, 2)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_S(Boutarel, draw, 3)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_I(Boutarel, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_SII(Boutarel, function5, 5)
	Entity::updateField1000(savepoint);
}

IMPLEMENT_FUNCTION_SI(Boutarel, enterExitCompartment, 6)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_SI(Boutarel, function7, 7)
	error("Boutarel: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function8, 8)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION(Boutarel, function9, 9)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION_II(Boutarel, function10, 10)
	error("Boutarel: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION_I(Boutarel, function11, 11)
	error("Boutarel: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function12, 12)
	error("Boutarel: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function13, 13)
	error("Boutarel: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION_I(Boutarel, function14, 14)
	error("Boutarel: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION_IS(Boutarel, function15, 15)
	error("Boutarel: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION_IS(Boutarel, function16, 16)
	error("Boutarel: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION_IS(Boutarel, function17, 17)
	error("Boutarel: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION_I(Boutarel, function18, 18)
	error("Boutarel: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, chapter1, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(21)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityBoutarel, kAction203520448, 0);
		getSavePoints()->addData(kEntityBoutarel, kAction237889408, 1);

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject42, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->field_491 = EntityData::kField491_1750;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function20, 20)
	error("Boutarel: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function21, 21)
	error("Boutarel: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function22, 22)
	if (savepoint.action == kActionDefault) {		
		getData()->field_491 = EntityData::kField491_6470;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getEntities()->prepareSequences(kEntityBoutarel);
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter2, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function24();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityBoutarel);

		getData()->field_491 = EntityData::kField491_4689;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function24, 24)
	error("Boutarel: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function25, 25)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter3, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function27();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityBoutarel);

		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject50, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function27, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");		
		break;

	case kAction122288808:
		setup_function28();
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityBoutarel, "BLANK");
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function28, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Boutarel, setup_function11), 1);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function29();
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function29, 29)
	error("Boutarel: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function30, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");		
		break;

	case kAction122288808:
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityBoutarel, "BLANK");
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter4, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function32();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityBoutarel);

		getData()->field_491 = EntityData::kField491_6470;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject50, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function32, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeBoutarel && !params->param1) {
			params->param1 = 1;
			setup_function33();
		}
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getEntities()->drawSequenceLeft(kEntityBoutarel, "510");
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function33, 33)
	error("Boutarel: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function34, 34)
	error("Boutarel: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, function35, 35)
	if (savepoint.action == kActionDefault) {		
		getData()->field_491 = EntityData::kField491_6470;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;

		getEntities()->prepareSequences(kEntityBoutarel);

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Boutarel, chapter5, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function37();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityBoutarel);

		getData()->field_491 = EntityData::kField491_3969;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Boutarel, function37, 37)
	if (savepoint.action == kAction70549068)
		setup_function38();
}

IMPLEMENT_FUNCTION(Boutarel, function38, 38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->field_491 = EntityData::kField491_5790;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		break;

	case kAction135800432:
		setup_nullfunction();
		break;
	}
}

IMPLEMENT_NULL_FUNCTION(Boutarel, 39)

} // End of namespace LastExpress
