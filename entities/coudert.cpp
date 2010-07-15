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

#include "lastexpress/entities/coudert.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Coudert::Coudert(LastExpressEngine *engine) : Entity(engine, kEntityCoudert) {
	ADD_CALLBACK_FUNCTION(Coudert, function1);
	ADD_CALLBACK_FUNCTION(Coudert, function2);
	ADD_CALLBACK_FUNCTION(Coudert, function3);
	ADD_CALLBACK_FUNCTION(Coudert, function4);
	ADD_CALLBACK_FUNCTION(Coudert, function5);
	ADD_CALLBACK_FUNCTION(Coudert, function6);
	ADD_CALLBACK_FUNCTION(Coudert, function7);
	ADD_CALLBACK_FUNCTION(Coudert, savegame);
	ADD_CALLBACK_FUNCTION(Coudert, function9);
	ADD_CALLBACK_FUNCTION(Coudert, function10);
	ADD_CALLBACK_FUNCTION(Coudert, function11);
	ADD_CALLBACK_FUNCTION(Coudert, function12);
	ADD_CALLBACK_FUNCTION(Coudert, function13);
	ADD_CALLBACK_FUNCTION(Coudert, function14);
	ADD_CALLBACK_FUNCTION(Coudert, function15);
	ADD_CALLBACK_FUNCTION(Coudert, function16);
	ADD_CALLBACK_FUNCTION(Coudert, function17);
	ADD_CALLBACK_FUNCTION(Coudert, function18);
	ADD_CALLBACK_FUNCTION(Coudert, function19);
	ADD_CALLBACK_FUNCTION(Coudert, function20);
	ADD_CALLBACK_FUNCTION(Coudert, function21);
	ADD_CALLBACK_FUNCTION(Coudert, function22);
	ADD_CALLBACK_FUNCTION(Coudert, function23);
	ADD_CALLBACK_FUNCTION(Coudert, function24);
	ADD_CALLBACK_FUNCTION(Coudert, function25);
	ADD_CALLBACK_FUNCTION(Coudert, function26);
	ADD_CALLBACK_FUNCTION(Coudert, function27);
	ADD_CALLBACK_FUNCTION(Coudert, function28);
	ADD_CALLBACK_FUNCTION(Coudert, function29);
	ADD_CALLBACK_FUNCTION(Coudert, function30);
	ADD_CALLBACK_FUNCTION(Coudert, function31);
	ADD_CALLBACK_FUNCTION(Coudert, function32);
	ADD_CALLBACK_FUNCTION(Coudert, function33);
	ADD_CALLBACK_FUNCTION(Coudert, function34);
	ADD_CALLBACK_FUNCTION(Coudert, function35);
	ADD_CALLBACK_FUNCTION(Coudert, chapter1);
	ADD_CALLBACK_FUNCTION(Coudert, function37);
	ADD_CALLBACK_FUNCTION(Coudert, function38);
	ADD_CALLBACK_FUNCTION(Coudert, function39);
	ADD_CALLBACK_FUNCTION(Coudert, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Coudert, function41);
	ADD_CALLBACK_FUNCTION(Coudert, chapter2);
	ADD_CALLBACK_FUNCTION(Coudert, function43);
	ADD_CALLBACK_FUNCTION(Coudert, chapter3);
	ADD_CALLBACK_FUNCTION(Coudert, function45);
	ADD_CALLBACK_FUNCTION(Coudert, function46);
	ADD_CALLBACK_FUNCTION(Coudert, function47);
	ADD_CALLBACK_FUNCTION(Coudert, function48);
	ADD_CALLBACK_FUNCTION(Coudert, function49);
	ADD_CALLBACK_FUNCTION(Coudert, function50);
	ADD_CALLBACK_FUNCTION(Coudert, function51);
	ADD_CALLBACK_FUNCTION(Coudert, chapter4);
	ADD_CALLBACK_FUNCTION(Coudert, function53);
	ADD_CALLBACK_FUNCTION(Coudert, function54);
	ADD_CALLBACK_FUNCTION(Coudert, function55);
	ADD_CALLBACK_FUNCTION(Coudert, function56);
	ADD_CALLBACK_FUNCTION(Coudert, chapter5);
	ADD_CALLBACK_FUNCTION(Coudert, function58);
	ADD_CALLBACK_FUNCTION(Coudert, function59);
	ADD_CALLBACK_FUNCTION(Coudert, function60);
	ADD_CALLBACK_FUNCTION(Coudert, function61);
	ADD_CALLBACK_FUNCTION(Coudert, function62);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Coudert, function1, 1)
	Entity::function1Clothes(savepoint);
}

IMPLEMENT_FUNCTION_S(Coudert, function2, 2)
	error("Coudert: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Coudert, function3, 3)
	error("Coudert: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function4, 4)
	error("Coudert: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_SIII(Coudert, function5, 5)
	error("Coudert: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_S(Coudert, function6, 6)
	error("Coudert: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Coudert, function7, 7)
	error("Coudert: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_II(Coudert, savegame, 8)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(Coudert, function9, 9)
	error("Coudert: callback function 9 not implemented!");
}


// Parameters: time offset
IMPLEMENT_FUNCTION_I(Coudert, function10, 10)
	error("Coudert: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function11, 11)
	error("Coudert: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function12, 12)
	error("Coudert: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_II(Coudert, function13, 13)
	error("Coudert: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function14, 14)
	error("Coudert: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function15, 15)
	error("Coudert: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function16, 16)
	error("Coudert: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function17, 17)
	error("Coudert: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function18, 18)
	error("Coudert: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function19, 19)
	error("Coudert: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION_II(Coudert, function20, 20)
	error("Coudert: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function21, 21)
	error("Coudert: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function22, 22)
	error("Coudert: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function23, 23)
	error("Coudert: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function24, 24)
	error("Coudert: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function25, 25)
	error("Coudert: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function26, 26)
	error("Coudert: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function27, 27)
	error("Coudert: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function28, 28)
	error("Coudert: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function29, 29)
	error("Coudert: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function30, 30)
	error("Coudert: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function31, 31)
	error("Coudert: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function32, 32)
	error("Coudert: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function33, 33)
	error("Coudert: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function34, 34)
	error("Coudert: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function35, 35)
	error("Coudert: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter1, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Coudert, kTimeChapter1, params->param1, 1, setup_chapter1_handler)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityCoudert, kAction292048641, 7);
		getSavePoints()->addData(kEntityCoudert, kAction326348944, 8);
		getSavePoints()->addData(kEntityCoudert, kAction171394341, 2);
		getSavePoints()->addData(kEntityCoudert, kAction154005632, 4);
		getSavePoints()->addData(kEntityCoudert, kAction169557824, 3);
		getSavePoints()->addData(kEntityCoudert, kAction226031488, 5);
		getSavePoints()->addData(kEntityCoudert, kAction339669520, 6);
		getSavePoints()->addData(kEntityCoudert, kAction189750912, 10);
		getSavePoints()->addData(kEntityCoudert, kAction185737168, 12);
		getSavePoints()->addData(kEntityCoudert, kAction185671840, 13);
		getSavePoints()->addData(kEntityCoudert, kAction205033696, 15);
		getSavePoints()->addData(kEntityCoudert, kAction157026693, 14);
		getSavePoints()->addData(kEntityCoudert, kAction189026624, 11);
		getSavePoints()->addData(kEntityCoudert, kAction168254872, 17);
		getSavePoints()->addData(kEntityCoudert, kAction201431954, 18);
		getSavePoints()->addData(kEntityCoudert, kAction188570113, 19);

		ENTITY_PARAM(0, 1) = 0;
		ENTITY_PARAM(0, 2) = 1;

		getData()->position = kPosition_1500;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarRedSleeping;

		getObjects()->updateLocation2(kObject111, kLocation1);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_chapter1_handler();
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function37, 37)
	error("Coudert: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function38, 38)
	error("Coudert: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function39, 39)
	error("Coudert: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter1_handler, 40)
	error("Coudert: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function41, 41)
	error("Coudert: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter2, 42)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function18));
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityCoudert);

		getData()->position = kPosition_1500;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 5) = 0;
		ENTITY_PARAM(0, 6) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 2) = 0;
		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 5) = 0;
		ENTITY_PARAM(1, 6) = 0;
		ENTITY_PARAM(1, 7) = 0;
		ENTITY_PARAM(1, 8) = 0;

		ENTITY_PARAM(2, 4) = 0;

		getObjects()->updateLocation2(kObject111, kLocation5);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function43();
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function43, 43)
	error("Coudert: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter3, 44)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function18));
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityCoudert);

		getData()->position = kPosition_1500;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 5) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 2) = 0;
		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 4) = 0;
		ENTITY_PARAM(1, 5) = 0;
		ENTITY_PARAM(1, 6) = 0;
		ENTITY_PARAM(1, 7) = 0;
		ENTITY_PARAM(1, 8) = 0;

		ENTITY_PARAM(2, 4) = 0;
		ENTITY_PARAM(2, 5) = 0;

		getObjects()->updateLocation2(kObject111, kLocation6);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function45();
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function45, 45)
	error("Coudert: callback function 45 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function46, 46)
	error("Coudert: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function47, 47)
	error("Coudert: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function48, 48)
	error("Coudert: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function49, 49)
	error("Coudert: callback function 49 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function50, 50)
	error("Coudert: callback function 50 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function51, 51)
	error("Coudert: callback function 51 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter4, 52)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function18));
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityCoudert);

		getData()->position = kPosition_1500;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 5) = 0;
		ENTITY_PARAM(0, 6) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 5) = 0;
		ENTITY_PARAM(1, 6) = 0;
		ENTITY_PARAM(1, 7) = 0;
		ENTITY_PARAM(1, 8) = 0;

		ENTITY_PARAM(2, 3) = 0;
		ENTITY_PARAM(2, 4) = 0;

		getObjects()->updateLocation2(kObject111, kLocation10);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			ENTITY_PARAM(1, 2) = 1;
			setup_function53();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function53, 53)
	error("Coudert: callback function 53 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function54, 54)
	error("Coudert: callback function 54 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function55, 55)
	error("Coudert: callback function 55 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function56, 56)
	error("Coudert: callback function 56 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter5, 57)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function58();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityCoudert);

		getData()->position = kPosition_3969;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function58, 58)
	if (savepoint.action == kAction70549068)
		setup_function59();
}

IMPLEMENT_FUNCTION(Coudert, function59, 59)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->position = kPosition_7500;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarRedSleeping;

		getSound()->playSound(kEntityCoudert, "Jac5010"); // Situation is under control, please remain in your compartment

		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_2000);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->drawSequenceLeft(kEntityCoudert, "627K");
			setup_function60();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function60, 60)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function61();
		break;

	case kAction155991520:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function10), 225);
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function61, 61)
	error("Coudert: callback function 61 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function62, 62)
	error("Coudert: callback function 62 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Coudert, 63)

} // End of namespace LastExpress
