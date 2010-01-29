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

#include "lastexpress/entities/abbot.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Abbot::Abbot(LastExpressEngine *engine) : Entity(engine, kEntityAbbot) {
	ADD_CALLBACK_FUNCTION(Abbot, function1);
	ADD_CALLBACK_FUNCTION(Abbot, function2);
	ADD_CALLBACK_FUNCTION(Abbot, function3);
	ADD_CALLBACK_FUNCTION(Abbot, function4);
	ADD_CALLBACK_FUNCTION(Abbot, function5);
	ADD_CALLBACK_FUNCTION(Abbot, function6);
	ADD_CALLBACK_FUNCTION(Abbot, function7);
	ADD_CALLBACK_FUNCTION(Abbot, function8);
	ADD_CALLBACK_FUNCTION(Abbot, function9);
	ADD_CALLBACK_FUNCTION(Abbot, function10);
	ADD_CALLBACK_FUNCTION(Abbot, function11);
	ADD_CALLBACK_FUNCTION(Abbot, function12);
	ADD_CALLBACK_FUNCTION(Abbot, function13);
	ADD_CALLBACK_FUNCTION(Abbot, function14);
	ADD_CALLBACK_FUNCTION(Abbot, chapter1);
	ADD_CALLBACK_FUNCTION(Abbot, chapter2);
	ADD_CALLBACK_FUNCTION(Abbot, chapter3);
	ADD_CALLBACK_FUNCTION(Abbot, function18);
	ADD_CALLBACK_FUNCTION(Abbot, function19);
	ADD_CALLBACK_FUNCTION(Abbot, function20);
	ADD_CALLBACK_FUNCTION(Abbot, function21);
	ADD_CALLBACK_FUNCTION(Abbot, function22);
	ADD_CALLBACK_FUNCTION(Abbot, function23);
	ADD_CALLBACK_FUNCTION(Abbot, function24);
	ADD_CALLBACK_FUNCTION(Abbot, function25);
	ADD_CALLBACK_FUNCTION(Abbot, function26);
	ADD_CALLBACK_FUNCTION(Abbot, function27);
	ADD_CALLBACK_FUNCTION(Abbot, function28);
	ADD_CALLBACK_FUNCTION(Abbot, function29);
	ADD_CALLBACK_FUNCTION(Abbot, function30);
	ADD_CALLBACK_FUNCTION(Abbot, function31);
	ADD_CALLBACK_FUNCTION(Abbot, function32);
	ADD_CALLBACK_FUNCTION(Abbot, function33);
	ADD_CALLBACK_FUNCTION(Abbot, function34);
	ADD_CALLBACK_FUNCTION(Abbot, function35);
	ADD_CALLBACK_FUNCTION(Abbot, function36);
	ADD_CALLBACK_FUNCTION(Abbot, function37);
	ADD_CALLBACK_FUNCTION(Abbot, function38);
	ADD_CALLBACK_FUNCTION(Abbot, chapter4);
	ADD_CALLBACK_FUNCTION(Abbot, function40);
	ADD_CALLBACK_FUNCTION(Abbot, function41);
	ADD_CALLBACK_FUNCTION(Abbot, function42);
	ADD_CALLBACK_FUNCTION(Abbot, function43);
	ADD_CALLBACK_FUNCTION(Abbot, function44);
	ADD_CALLBACK_FUNCTION(Abbot, function45);
	ADD_CALLBACK_FUNCTION(Abbot, function46);
	ADD_CALLBACK_FUNCTION(Abbot, function47);
	ADD_CALLBACK_FUNCTION(Abbot, function48);
	ADD_CALLBACK_FUNCTION(Abbot, pickBomb);
	ADD_CALLBACK_FUNCTION(Abbot, chapter5);
	ADD_CALLBACK_FUNCTION(Abbot, function51);
	ADD_CALLBACK_FUNCTION(Abbot, function52);
	ADD_CALLBACK_FUNCTION(Abbot, function53);
}

IMPLEMENT_FUNCTION(Abbot, function1, 1) {
	error("Abbot: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_S(Abbot, function2, 2) {
	error("Abbot: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Abbot, function3, 3) {
	error("Abbot: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Abbot, function4, 4) {
	error("Abbot: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_I(Abbot, function5, 5) {
	error("Abbot: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_SSI(Abbot, function6, 6) {
	error("Abbot: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_I(Abbot, function7, 7) {
	error("Abbot: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_I(Abbot, function8, 8) {
	error("Abbot: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_S(Abbot, function9, 9) {
	error("Abbot: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION_II(Abbot, function10, 10) {
	error("Abbot: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION_II(Abbot, function11, 11) {
	error("Abbot: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION_SIIS(Abbot, function12, 12) {
	error("Abbot: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_SII(Abbot, function13, 13) {
	error("Abbot: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function14, 14) {
	error("Abbot: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, chapter1, 15) {
	if (savepoint->action != kActionDefault)
		return;

	getSavePoints()->addData(kEntityAbbot, kAction203073664, 0);
}

IMPLEMENT_FUNCTION(Abbot, chapter2, 16) {
	if (savepoint->action != kActionDefault)
		return;

	getEntities()->drawSequences(kEntityAbbot);
}

IMPLEMENT_FUNCTION(Abbot, chapter3, 17) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityAbbot);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kNoItem;
		_data->getData()->field_4A5 = 0;

		break;

	case kActionNone:
		setup_function18();
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function18, 18) {
	error("Abbot: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function19, 19) {
	error("Abbot: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function20, 20) {
	error("Abbot: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function21, 21) {
	error("Abbot: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function22, 22) {
	error("Abbot: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function23, 23) {
	error("Abbot: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function24, 24) {
	error("Abbot: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function25, 25) {
	error("Abbot: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function26, 26) {
	error("Abbot: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function27, 27) {
	error("Abbot: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function28, 28) {
	error("Abbot: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function29, 29) {
	error("Abbot: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function30, 30) {
	error("Abbot: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function31, 31) {
	error("Abbot: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function32, 32) {
	error("Abbot: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function33, 33) {
	error("Abbot: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function34, 34) {
	error("Abbot: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function35, 35) {
	error("Abbot: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function36, 36) {
	error("Abbot: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function37, 37) {
	error("Abbot: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function38, 38) {
	error("Abbot: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, chapter4, 39) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityAbbot);

		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kNoItem;
		
		ENTITY_PARAM(8, 0, 1) = 0;

		break;

	case kActionNone:
		setup_function41();
		break;
	}
}

IMPLEMENT_FUNCTION_II(Abbot, function40, 40) {
	error("Abbot: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function41, 41) {
	error("Abbot: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function42, 42) {
	error("Abbot: callback function 42 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function43, 43) {
	error("Abbot: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function44, 44) {
	error("Abbot: callback function 44 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function45, 45) {
	error("Abbot: callback function 45 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function46, 46) {
	error("Abbot: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function47, 47) {
	error("Abbot: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function48, 48) {
	error("Abbot: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, pickBomb, 49) {
	error("Abbot::pickBomb: callback 49 function not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, chapter5, 50) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityAbbot);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kNoItem;
		_data->getData()->field_4A5 = 0;

		break;

	case kActionNone:
		setup_function51();
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function51, 51) {
	error("Abbot: callback function 51 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function52, 52) {
	error("Abbot: callback function 52 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function53, 53) {
	error("Abbot: callback function 53 not implemented!");
}

} // End of namespace LastExpress
