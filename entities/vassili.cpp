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

#include "lastexpress/entities/vassili.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Vassili::Vassili(LastExpressEngine *engine) : Entity(engine, kEntityVassili) {
	ADD_CALLBACK_FUNCTION(Vassili, function1);
	ADD_CALLBACK_FUNCTION(Vassili, function2);
	ADD_CALLBACK_FUNCTION(Vassili, function3);
	ADD_CALLBACK_FUNCTION(Vassili, chapter1);
	ADD_CALLBACK_FUNCTION(Vassili, function5);
	ADD_CALLBACK_FUNCTION(Vassili, function6);
	ADD_CALLBACK_FUNCTION(Vassili, function7);
	ADD_CALLBACK_FUNCTION(Vassili, function8);
	ADD_CALLBACK_FUNCTION(Vassili, function9);
	ADD_CALLBACK_FUNCTION(Vassili, function10);
	ADD_CALLBACK_FUNCTION(Vassili, function11);
	ADD_CALLBACK_FUNCTION(Vassili, chapter2);
	ADD_CALLBACK_FUNCTION(Vassili, function13);
	ADD_CALLBACK_FUNCTION(Vassili, chapter3);
	ADD_CALLBACK_FUNCTION(Vassili, function15);
	ADD_CALLBACK_FUNCTION(Vassili, chapter4);
	ADD_CALLBACK_FUNCTION(Vassili, function17);
	ADD_CALLBACK_FUNCTION(Vassili, chapter5);
}

IMPLEMENT_FUNCTION(Vassili, function1, 1) {
	error("Vassili: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_S(Vassili, function2, 2) {
	error("Vassili: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_II(Vassili, function3, 3) {
	error("Vassili: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, chapter1, 4) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject40, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(5)
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, function5, 5) {
	error("Vassili: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, function6, 6) {
	error("Vassili: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, function7, 7) {
	error("Vassili: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, function8, 8) {
	error("Vassili: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, function9, 9) {
	error("Vassili: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, function10, 10) {
	error("Vassili: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, function11, 11) {
	error("Vassili: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, chapter2, 12) {
	error("Vassili: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, function13, 13) {
	error("Vassili: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, chapter3, 14) {
	error("Vassili: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, function15, 15) {
	error("Vassili: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, chapter4, 16) {
	error("Vassili: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, function17, 17) {
	error("Vassili: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Vassili, chapter5, 18) {
	error("Vassili: callback function 18 not implemented!");
}

} // End of namespace LastExpress
