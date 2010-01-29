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

#include "lastexpress/entities/francois.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Francois::Francois(LastExpressEngine *engine) : Entity(engine, kEntityFrancois) {
	ADD_CALLBACK_FUNCTION(Francois, function1);
	ADD_CALLBACK_FUNCTION(Francois, function2);
	ADD_CALLBACK_FUNCTION(Francois, function3);
	ADD_CALLBACK_FUNCTION(Francois, function4);
	ADD_CALLBACK_FUNCTION(Francois, function5);
	ADD_CALLBACK_FUNCTION(Francois, function6);
	ADD_CALLBACK_FUNCTION(Francois, function7);
	ADD_CALLBACK_FUNCTION(Francois, function8);
	ADD_CALLBACK_FUNCTION(Francois, function9);
	ADD_CALLBACK_FUNCTION(Francois, function10);
	ADD_CALLBACK_FUNCTION(Francois, function11);
	ADD_CALLBACK_FUNCTION(Francois, function12);
	ADD_CALLBACK_FUNCTION(Francois, function13);
	ADD_CALLBACK_FUNCTION(Francois, function14);
	ADD_CALLBACK_FUNCTION(Francois, function15);
	ADD_CALLBACK_FUNCTION(Francois, function16);
	ADD_CALLBACK_FUNCTION(Francois, chapter1);
	ADD_CALLBACK_FUNCTION(Francois, function18);
	ADD_CALLBACK_FUNCTION(Francois, function19);
	ADD_CALLBACK_FUNCTION(Francois, function20);
	ADD_CALLBACK_FUNCTION(Francois, chapter2);
	ADD_CALLBACK_FUNCTION(Francois, function22);
	ADD_CALLBACK_FUNCTION(Francois, function23);
	ADD_CALLBACK_FUNCTION(Francois, chapter3);
	ADD_CALLBACK_FUNCTION(Francois, function25);
	ADD_CALLBACK_FUNCTION(Francois, chapter4);
	ADD_CALLBACK_FUNCTION(Francois, function27);
	ADD_CALLBACK_FUNCTION(Francois, chapter5);
	ADD_CALLBACK_FUNCTION(Francois, function29);
	ADD_CALLBACK_FUNCTION(Francois, function30);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Francois, function1, 1) {
	error("Francois: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_I(Francois, function2, 2) {
	error("Francois: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_S(Francois, function3, 3) {
	error("Francois: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Francois, function4, 4) {
	error("Francois: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Francois, function5, 5) {
	error("Francois: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_S(Francois, function6, 6) {
	error("Francois: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_II(Francois, function7, 7) {
	error("Francois: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_II(Francois, function8, 8) {
	error("Francois: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function9, 9) {
	error("Francois: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function10, 10) {
	error("Francois: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION_I(Francois, function11, 11) {
	error("Francois: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function12, 12) {
	error("Francois: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function13, 13) {
	error("Francois: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION_IIS(Francois, function14, 14) {
	error("Francois: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function15, 15) {
	error("Francois: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function16, 16) {
	error("Francois: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, chapter1, 17) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_5790;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;		

		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(18)
		break;
	}
}

IMPLEMENT_FUNCTION(Francois, function18, 18) {
	error("Francois: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function19, 19) {
	error("Francois: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function20, 20) {
	error("Francois: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, chapter2, 21) {
	error("Francois: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function22, 22) {
	error("Francois: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function23, 23) {
	error("Francois: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, chapter3, 24) {
	error("Francois: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function25, 25) {
	error("Francois: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, chapter4, 26) {
	error("Francois: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function27, 27) {
	error("Francois: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, chapter5, 28) {
	error("Francois: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function29, 29) {
	error("Francois: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function30, 30) {
	error("Francois: callback function 30 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Francois, 31)

} // End of namespace LastExpress
