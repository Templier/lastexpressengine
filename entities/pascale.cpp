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

#include "lastexpress/entities/pascale.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Pascale::Pascale(LastExpressEngine *engine) : Entity(engine, SavePoints::kEntityPascale) {
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, chapter1);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, chapter2);
	ADD_CALLBACK_FUNCTION(Pascale, chapter3);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, chapter4);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, chapter5);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_CALLBACK_FUNCTION(Pascale, nullfunc);
	ADD_NULL_FUNCTION();
}

void Pascale::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Pascale: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Pascale, chapter1, 12) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction239072064, 0);
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction257489762, 2);
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction207769280, 6);
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction101824388, 7);
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction136059947, 8);
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction223262556, 1);
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction269479296, 3);
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction352703104, 4);
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction352768896, 5);
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction191604416, 10);
		getSavePoints()->addData(SavePoints::kEntityPascale, SavePoints::kAction190605184, 11);

		_data->getData()->field_491 = 5900;
		_data->getData()->field_493 = 0;
		_data->getData()->field_495 = 5;
		break;

	case SavePoints::kActionNone: 
		// call function
 		break;
	}
}

IMPLEMENT_FUNCTION(Pascale, chapter2, 20) {
}

IMPLEMENT_FUNCTION(Pascale, chapter3, 21) {
}

IMPLEMENT_FUNCTION(Pascale, chapter4, 25) {
}

IMPLEMENT_FUNCTION(Pascale, chapter5, 31) {
}

IMPLEMENT_NULL_FUNCTION(Pascale, 34)

} // End of namespace LastExpress
