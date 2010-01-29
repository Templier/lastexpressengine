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

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Kahina::Kahina(LastExpressEngine *engine) : Entity(engine, kEntityKahina) {
	ADD_CALLBACK_FUNCTION(Kahina, function1);
	ADD_CALLBACK_FUNCTION(Kahina, function2);
	ADD_CALLBACK_FUNCTION(Kahina, function3);
	ADD_CALLBACK_FUNCTION(Kahina, function4);
	ADD_CALLBACK_FUNCTION(Kahina, function5);
	ADD_CALLBACK_FUNCTION(Kahina, function6);
	ADD_CALLBACK_FUNCTION(Kahina, function7);
	ADD_CALLBACK_FUNCTION(Kahina, function8);
	ADD_CALLBACK_FUNCTION(Kahina, function9);
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

IMPLEMENT_FUNCTION(Kahina, function1, 1) {
	error("Kahina: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_S(Kahina, function2, 2) {
	error("Kahina: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_II(Kahina, function3, 3) {
	error("Kahina: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_I(Kahina, function4, 4) {
	error("Kahina: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Kahina, function5, 5) {
	error("Kahina: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_I(Kahina, function6, 6) {
	error("Kahina: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_II(Kahina, function7, 7) {
	error("Kahina: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_II(Kahina, function8, 8) {
	error("Kahina: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Kahina, function9, 9) {
	error("Kahina: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter1, 10) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentKronos, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_5000;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_2;		

		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(11)
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, function11, 11) {
	error("Kahina: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function12, 12) {
	error("Kahina: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function13, 13) {
	error("Kahina: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function14, 14) {
	error("Kahina: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function15, 15) {
	error("Kahina: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter2, 16) {
	error("Kahina: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function17, 17) {
	error("Kahina: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter3, 18) {
	error("Kahina: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION_II(Kahina, function19, 19) {
	error("Kahina: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function20, 20) {
	error("Kahina: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function21, 21) {
	error("Kahina: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function22, 22) {
	error("Kahina: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function23, 23) {
	error("Kahina: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function24, 24) {
	error("Kahina: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function25, 25) {
	error("Kahina: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function26, 26) {
	error("Kahina: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function27, 27) {
	error("Kahina: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter4, 28) {
	error("Kahina: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter5, 29) {
	error("Kahina: callback function 29 not implemented!");
}

} // End of namespace LastExpress
