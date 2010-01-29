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

#include "lastexpress/entities/milos.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Milos::Milos(LastExpressEngine *engine) : Entity(engine, kEntityMilos) {
	ADD_CALLBACK_FUNCTION(Milos, function1);
	ADD_CALLBACK_FUNCTION(Milos, function2);
	ADD_CALLBACK_FUNCTION(Milos, function3);
	ADD_CALLBACK_FUNCTION(Milos, function4);
	ADD_CALLBACK_FUNCTION(Milos, function5);
	ADD_CALLBACK_FUNCTION(Milos, function6);
	ADD_CALLBACK_FUNCTION(Milos, function7);
	ADD_CALLBACK_FUNCTION(Milos, function8);
	ADD_CALLBACK_FUNCTION(Milos, function9);
	ADD_CALLBACK_FUNCTION(Milos, function10);
	ADD_CALLBACK_FUNCTION(Milos, function11);
	ADD_CALLBACK_FUNCTION(Milos, chapter1);
	ADD_CALLBACK_FUNCTION(Milos, function13);
	ADD_CALLBACK_FUNCTION(Milos, function14);
	ADD_CALLBACK_FUNCTION(Milos, function15);
	ADD_CALLBACK_FUNCTION(Milos, function16);
	ADD_CALLBACK_FUNCTION(Milos, function17);
	ADD_CALLBACK_FUNCTION(Milos, function18);
	ADD_CALLBACK_FUNCTION(Milos, chapter2);
	ADD_CALLBACK_FUNCTION(Milos, function20);
	ADD_CALLBACK_FUNCTION(Milos, function21);
	ADD_CALLBACK_FUNCTION(Milos, chapter3);
	ADD_CALLBACK_FUNCTION(Milos, function23);
	ADD_CALLBACK_FUNCTION(Milos, function24);
	ADD_CALLBACK_FUNCTION(Milos, function25);
	ADD_CALLBACK_FUNCTION(Milos, function26);
	ADD_CALLBACK_FUNCTION(Milos, function27);
	ADD_CALLBACK_FUNCTION(Milos, chapter4);
	ADD_CALLBACK_FUNCTION(Milos, function29);
	ADD_CALLBACK_FUNCTION(Milos, function30);
	ADD_CALLBACK_FUNCTION(Milos, function31);
	ADD_CALLBACK_FUNCTION(Milos, function32);
	ADD_CALLBACK_FUNCTION(Milos, chapter5);
	ADD_CALLBACK_FUNCTION(Milos, function34);
	ADD_CALLBACK_FUNCTION(Milos, function35);
}

IMPLEMENT_FUNCTION(Milos, function1, 1) {
	error("Milos: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_S(Milos, function2, 2) {
	error("Milos: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Milos, function3, 3) {
	error("Milos: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Milos, function4, 4) {
	error("Milos: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function5, 5) {
	error("Milos: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_S(Milos, function6, 6) {
	error("Milos: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_S(Milos, function7, 7) {
	error("Milos: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_II(Milos, function8, 8) {
	error("Milos: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_I(Milos, function9, 9) {
	error("Milos: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION_II(Milos, function10, 10) {
	error("Milos: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION_I(Milos, function11, 11) {
	error("Milos: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, chapter1, 12) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityMilos, kAction157691176, 0);
		getSavePoints()->addData(kEntityMilos, kAction208228224, 2);
		getSavePoints()->addData(kEntityMilos, kAction259125998, 3);

		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject46, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_4689;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(13) // FIXME check call number
		break;
	}
}

IMPLEMENT_FUNCTION(Milos, function13, 13) {
	error("Milos: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function14, 14) {
	error("Milos: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function15, 15) {
	error("Milos: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function16, 16) {
	error("Milos: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function17, 17) {
	error("Milos: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function18, 18) {
	error("Milos: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, chapter2, 19) {
	error("Milos: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function20, 20) {
	error("Milos: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function21, 21) {
	error("Milos: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, chapter3, 22) {
	error("Milos: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function23, 23) {
	error("Milos: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function24, 24) {
	error("Milos: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function25, 25) {
	error("Milos: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION_I(Milos, function26, 26) {
	error("Milos: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION_II(Milos, function27, 27) {
	error("Milos: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, chapter4, 28) {
	error("Milos: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function29, 29) {
	error("Milos: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function30, 30) {
	error("Milos: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function31, 31) {
	error("Milos: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function32, 32) {
	error("Milos: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, chapter5, 33) {
	error("Milos: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function34, 34) {
	error("Milos: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function35, 35) {
	error("Milos: callback function 35 not implemented!");
}

} // End of namespace LastExpress
