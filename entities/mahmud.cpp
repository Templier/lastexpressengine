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

#include "lastexpress/entities/mahmud.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Mahmud::Mahmud(LastExpressEngine *engine) : Entity(engine, kEntityMahmud) {
	ADD_CALLBACK_FUNCTION(Mahmud, function1);
	ADD_CALLBACK_FUNCTION(Mahmud, function2);
	ADD_CALLBACK_FUNCTION(Mahmud, function3);
	ADD_CALLBACK_FUNCTION(Mahmud, function4);
	ADD_CALLBACK_FUNCTION(Mahmud, function5);
	ADD_CALLBACK_FUNCTION(Mahmud, function6);
	ADD_CALLBACK_FUNCTION(Mahmud, function7);
	ADD_CALLBACK_FUNCTION(Mahmud, function8);
	ADD_CALLBACK_FUNCTION(Mahmud, function9);
	ADD_CALLBACK_FUNCTION(Mahmud, function10);
	ADD_CALLBACK_FUNCTION(Mahmud, function11);
	ADD_CALLBACK_FUNCTION(Mahmud, function12);
	ADD_CALLBACK_FUNCTION(Mahmud, function13);
	ADD_CALLBACK_FUNCTION(Mahmud, function14);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter1);
	ADD_CALLBACK_FUNCTION(Mahmud, function16);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter2);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter3);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter4);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter5);
}

IMPLEMENT_FUNCTION(Mahmud, function1, 1) {
	error("Mahmud: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Mahmud, function2, 2) {
	error("Mahmud: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Mahmud, function3, 3) {
	error("Mahmud: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_SIII(Mahmud, function4, 4) {
	error("Mahmud: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_S(Mahmud, function5, 5) {
	error("Mahmud: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_S(Mahmud, function6, 6) {
	error("Mahmud: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_NOSETUP(Mahmud, function7, 7) {
	error("Mahmud: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_II(Mahmud, function8, 8) {
	error("Mahmud: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_II(Mahmud, function9, 9) {
	error("Mahmud: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION_II(Mahmud, function10, 10) {
	error("Mahmud: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, function11, 11) {
	error("Mahmud: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, function12, 12) {
	error("Mahmud: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, function13, 13) {
	error("Mahmud: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, function14, 14) {
	error("Mahmud: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, chapter1, 15) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityMahmud, kAction170483072, 0);

		getObjects()->update(kObjectCompartment4, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject20, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_540;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_3;
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(14)
		break;
	}
}

IMPLEMENT_FUNCTION(Mahmud, function16, 16) {
	error("Mahmud: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, chapter2, 17) {
	error("Mahmud: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, chapter3, 18) {
	error("Mahmud: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, chapter4, 19) {
	error("Mahmud: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, chapter5, 20) {
	error("Mahmud: callback function 20 not implemented!");
}

} // End of namespace LastExpress
