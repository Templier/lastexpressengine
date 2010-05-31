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

#include "lastexpress/entities/kahina.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Kahina::Kahina(LastExpressEngine *engine) : Entity(engine, kEntityKahina) {
	ADD_CALLBACK_FUNCTION(Kahina, function1);
	ADD_CALLBACK_FUNCTION(Kahina, playSound);
	ADD_CALLBACK_FUNCTION(Kahina, savegame);
	ADD_CALLBACK_FUNCTION(Kahina, updateFromTime);
	ADD_CALLBACK_FUNCTION(Kahina, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Kahina, function6);
	ADD_CALLBACK_FUNCTION(Kahina, function7);
	ADD_CALLBACK_FUNCTION(Kahina, function8);
	ADD_CALLBACK_FUNCTION(Kahina, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Kahina, chapter1);
	ADD_CALLBACK_FUNCTION(Kahina, function11);
	ADD_CALLBACK_FUNCTION(Kahina, function12);
	ADD_CALLBACK_FUNCTION(Kahina, function13);
	ADD_CALLBACK_FUNCTION(Kahina, function14);
	ADD_CALLBACK_FUNCTION(Kahina, function15);
	ADD_CALLBACK_FUNCTION(Kahina, chapter2);
	ADD_CALLBACK_FUNCTION(Kahina, function17);
	ADD_CALLBACK_FUNCTION(Kahina, chapter3);
	ADD_CALLBACK_FUNCTION(Kahina, function19);
	ADD_CALLBACK_FUNCTION(Kahina, function20);
	ADD_CALLBACK_FUNCTION(Kahina, function21);
	ADD_CALLBACK_FUNCTION(Kahina, function22);
	ADD_CALLBACK_FUNCTION(Kahina, function23);
	ADD_CALLBACK_FUNCTION(Kahina, function24);
	ADD_CALLBACK_FUNCTION(Kahina, function25);
	ADD_CALLBACK_FUNCTION(Kahina, function26);
	ADD_CALLBACK_FUNCTION(Kahina, function27);
	ADD_CALLBACK_FUNCTION(Kahina, chapter4);
	ADD_CALLBACK_FUNCTION(Kahina, chapter5);
}

IMPLEMENT_FUNCTION(Kahina, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Kahina, playSound, 2)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_II(Kahina, savegame, 3)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_I(Kahina, updateFromTime, 4)
	if (savepoint.action == kAction137503360) {
		ENTITY_PARAM(0, 2) = 1;
		CALLBACK_ACTION()
	}

	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Kahina, updateFromTicks, 5)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION_I(Kahina, function6, 6)
	error("Kahina: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_II(Kahina, function7, 7)
	error("Kahina: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_II(Kahina, function8, 8)
	error("Kahina: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Kahina, enterExitCompartment, 9)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION(Kahina, chapter1, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(11)
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentKronos, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->field_491 = EntityData::kField491_5000;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarKronos;

		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, function11, 11)
	if (savepoint.action != kActionNone)
		return;

	if (getState()->time > kTimeKahina && !params->param1 && getProgress().jacket) {
		getSavePoints()->push(kEntityKahina, kEntityMertens, kAction238732837);
		params->param1 = 1;
	}

	if (getProgress().event_mertens_chronos_invitation)
		setup_function12();
}

IMPLEMENT_FUNCTION(Kahina, function12, 12)
	error("Kahina: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function13, 13)
	error("Kahina: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function14, 14)
	error("Kahina: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function15, 15)
	error("Kahina: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter2, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function17();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityKahina);

		getData()->field_491 = EntityData::kField491_6000;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarKronos;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, function17, 17)
	error("Kahina: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter3, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function20();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityKahina);

		getData()->field_491 = EntityData::kField491_5000;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarKronos;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION_II(Kahina, function19, 19)
	error("Kahina: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function20, 20)
	error("Kahina: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function21, 21)
	error("Kahina: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function22, 22)
	error("Kahina: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function23, 23)
	error("Kahina: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function24, 24)
	error("Kahina: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function25, 25)
	error("Kahina: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function26, 26)
	error("Kahina: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function27, 27)
	error("Kahina: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter4, 28)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityKahina);
}

IMPLEMENT_FUNCTION(Kahina, chapter5, 29)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityKahina);
}

} // End of namespace LastExpress
