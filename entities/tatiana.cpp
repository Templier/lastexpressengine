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

#include "lastexpress/entities/tatiana.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Tatiana::Tatiana(LastExpressEngine *engine) : Entity(engine, kEntityTatiana) {
	ADD_CALLBACK_FUNCTION(Tatiana, function1);
	ADD_CALLBACK_FUNCTION(Tatiana, function2);
	ADD_CALLBACK_FUNCTION(Tatiana, function3);
	ADD_CALLBACK_FUNCTION(Tatiana, function4);
	ADD_CALLBACK_FUNCTION(Tatiana, function5);
	ADD_CALLBACK_FUNCTION(Tatiana, function6);
	ADD_CALLBACK_FUNCTION(Tatiana, function7);
	ADD_CALLBACK_FUNCTION(Tatiana, function8);
	ADD_CALLBACK_FUNCTION(Tatiana, function9);
	ADD_CALLBACK_FUNCTION(Tatiana, function10);
	ADD_CALLBACK_FUNCTION(Tatiana, function11);
	ADD_CALLBACK_FUNCTION(Tatiana, function12);
	ADD_CALLBACK_FUNCTION(Tatiana, function13);
	ADD_CALLBACK_FUNCTION(Tatiana, function14);
	ADD_CALLBACK_FUNCTION(Tatiana, function15);
	ADD_CALLBACK_FUNCTION(Tatiana, function16);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter1);
	ADD_CALLBACK_FUNCTION(Tatiana, function18);
	ADD_CALLBACK_FUNCTION(Tatiana, function19);
	ADD_CALLBACK_FUNCTION(Tatiana, function20);
	ADD_CALLBACK_FUNCTION(Tatiana, function21);
	ADD_CALLBACK_FUNCTION(Tatiana, function22);
	ADD_CALLBACK_FUNCTION(Tatiana, function23);
	ADD_CALLBACK_FUNCTION(Tatiana, function24);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter2);
	ADD_CALLBACK_FUNCTION(Tatiana, function26);
	ADD_CALLBACK_FUNCTION(Tatiana, function27);
	ADD_CALLBACK_FUNCTION(Tatiana, function28);
	ADD_CALLBACK_FUNCTION(Tatiana, function29);
	ADD_CALLBACK_FUNCTION(Tatiana, function30);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter3);
	ADD_CALLBACK_FUNCTION(Tatiana, function32);
	ADD_CALLBACK_FUNCTION(Tatiana, function33);
	ADD_CALLBACK_FUNCTION(Tatiana, function34);
	ADD_CALLBACK_FUNCTION(Tatiana, function35);
	ADD_CALLBACK_FUNCTION(Tatiana, function36);
	ADD_CALLBACK_FUNCTION(Tatiana, function37);
	ADD_CALLBACK_FUNCTION(Tatiana, function38);
	ADD_CALLBACK_FUNCTION(Tatiana, function39);
	ADD_CALLBACK_FUNCTION(Tatiana, function40);
	ADD_CALLBACK_FUNCTION(Tatiana, function41);
	ADD_CALLBACK_FUNCTION(Tatiana, function42);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter4);
	ADD_CALLBACK_FUNCTION(Tatiana, function44);
	ADD_CALLBACK_FUNCTION(Tatiana, function45);
	ADD_CALLBACK_FUNCTION(Tatiana, function46);
	ADD_CALLBACK_FUNCTION(Tatiana, function47);
	ADD_CALLBACK_FUNCTION(Tatiana, function48);
	ADD_CALLBACK_FUNCTION(Tatiana, function49);
	ADD_CALLBACK_FUNCTION(Tatiana, function50);
	ADD_CALLBACK_FUNCTION(Tatiana, function51);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter5);
	ADD_CALLBACK_FUNCTION(Tatiana, function53);
	ADD_CALLBACK_FUNCTION(Tatiana, function54);
	ADD_CALLBACK_FUNCTION(Tatiana, function55);
}

IMPLEMENT_FUNCTION(Tatiana, function1, 1) {
	error("Tatiana: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_S(Tatiana, function2, 2) {
	error("Tatiana: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_S(Tatiana, function3, 3) {
	error("Tatiana: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_SII(Tatiana, function4, 4) {
	error("Tatiana: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Tatiana, function5, 5) {
	error("Tatiana: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Tatiana, function6, 6) {
	error("Tatiana: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_SIIS(Tatiana, function7, 7) {
	error("Tatiana: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function8, 8) {
	error("Tatiana: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Tatiana, function9, 9) {
	error("Tatiana: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION_I(Tatiana, function10, 10) {
	error("Tatiana: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function11, 11) {
	error("Tatiana: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION_II(Tatiana, function12, 12) {
	error("Tatiana: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_II(Tatiana, function13, 13) {
	error("Tatiana: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function14, 14) {
	error("Tatiana: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function15, 15) {
	error("Tatiana: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION_I(Tatiana, function16, 16) {
	error("Tatiana: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, chapter1, 17) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(19)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityTatiana, kAction191198209, 0);

		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject41, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_5419;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function18, 18) {
	error("Tatiana: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function19, 19) {
	error("Tatiana: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function20, 20) {
	error("Tatiana: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function21, 21) {
	error("Tatiana: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function22, 22) {
	error("Tatiana: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function23, 23) {
	error("Tatiana: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function24, 24) {
	error("Tatiana: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, chapter2, 25) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function26();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject41, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_5420;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothes2;
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function26, 26) {
	error("Tatiana: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function27, 27) {
	error("Tatiana: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function28, 28) {
	error("Tatiana: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function29, 29) {
	error("Tatiana: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function30, 30) {
	error("Tatiana: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, chapter3, 31) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function32();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_1750;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothes2;
		_data->getData()->inventoryItem = kItemNone;

		// Update inventory
		getInventory()->getEntry(kItemFirebird)->location = kLocation2;

		if (getEvent(kEventTatianaBreakfastGivePoem) || (getEvent(kEventTatianaGivePoem) && !getEvent(kEventTatianaBreakfastAlexei)))
			getInventory()->getEntry(kItemParchemin)->location = kLocation2;

		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function32, 32) {
	error("Tatiana: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function33, 33) {
	error("Tatiana: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function34, 34) {
	error("Tatiana: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function35, 35) {
	error("Tatiana: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function36, 36) {
	error("Tatiana: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function37, 37) {
	error("Tatiana: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function38, 38) {
	error("Tatiana: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function39, 39) {
	error("Tatiana: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function40, 40) {
	error("Tatiana: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function41, 41) {
	error("Tatiana: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function42, 42) {
	error("Tatiana: callback function 42 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, chapter4, 43) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function44();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_7500;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->clothes = EntityData::kClothes2;
		_data->getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 1) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function44, 44) {
	error("Tatiana: callback function 44 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function45, 45) {
	error("Tatiana: callback function 45 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function46, 46) {
	error("Tatiana: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function47, 47) {
	error("Tatiana: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function48, 48) {
	error("Tatiana: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function49, 49) {
	error("Tatiana: callback function 49 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function50, 50) {
	error("Tatiana: callback function 50 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function51, 51) {
	error("Tatiana: callback function 51 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, chapter5, 52) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function53();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityTatiana);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function53, 53) {
	error("Tatiana: callback function 53 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function54, 54) {
	error("Tatiana: callback function 54 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function55, 55) {
	error("Tatiana: callback function 55 not implemented!");
}

} // End of namespace LastExpress
