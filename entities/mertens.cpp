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

#include "lastexpress/entities/mertens.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Mertens::Mertens(LastExpressEngine *engine) : Entity(engine, SavePoints::kMertens) {
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, chapter1);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, chapter2);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, chapter3);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, chapter4);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, chapter5);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_NULL_FUNCTION();
}

void Mertens::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Mertens: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter1, 34) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kMertens, 171394341, 7);
		getSavePoints()->addData(SavePoints::kMertens, 169633856, 9);
		getSavePoints()->addData(SavePoints::kMertens, 238732837, 10);
		getSavePoints()->addData(SavePoints::kMertens, 269624833, 12);
		getSavePoints()->addData(SavePoints::kMertens, 302614416, 11);
		getSavePoints()->addData(SavePoints::kMertens, 190082817, 8);
		getSavePoints()->addData(SavePoints::kMertens, 269436673, 13);
		getSavePoints()->addData(SavePoints::kMertens, 303343617, 14);
		getSavePoints()->addData(SavePoints::kMertens, 224122407, 17);
		getSavePoints()->addData(SavePoints::kMertens, 201431954, 18);
		getSavePoints()->addData(SavePoints::kMertens, 188635520, 19);
		getSavePoints()->addData(SavePoints::kMertens, 204379649, 4);

		_data.callback_data[8].entries[0].field_0 = 0;
		_data.field_491 = 9460;
		_data.field_493 = 0;
		_data.field_495 = 3;
		break;

	case SavePoints::kActionNone: 
		if (getState()->time > 1062000) {
			if (!getCallData().entries[0].field_0) {
				getCallData().entries[0].field_0 = 1;
				// call function
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, chapter2, 43) {
}

IMPLEMENT_FUNCTION(Mertens, chapter3, 45) {
}

IMPLEMENT_FUNCTION(Mertens, chapter4, 47) {
}

IMPLEMENT_FUNCTION(Mertens, chapter5, 50) {
}

IMPLEMENT_NULL_FUNCTION(Mertens, 59)

} // End of namespace LastExpress
