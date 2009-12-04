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

#include "lastexpress/entities/anna.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Anna::Anna(LastExpressEngine *engine) : Entity(engine, kEntityAnna) {
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, chapter1);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, chapter2);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, chapter3);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, bagage);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, chapter4);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, chapter5);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
	ADD_CALLBACK_FUNCTION(Anna, nullfunc);
}

void Anna::nullfunc(SavePoint *savepoint) {
	error("Anna: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter1, 16) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault: 
		getSavePoints()->addData(kEntityAnna, kAction291662081, 0);
		getSavePoints()->addData(kEntityAnna, kAction238936000, 1);

		getObjects()->update(Objects::kObjectCompartmentF, kEntityNone, 1, Cursor::kCursorHandKnock, 9);
		getObjects()->update(Objects::kObject53, kEntityNone, 1, Cursor::kCursorHandKnock, 9);
		getObjects()->update(Objects::kObject45, kEntityNone, 1, Cursor::kCursorKeepValue, 255);

		_data->getData()->field_491 = 8200;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 3;
		_data->getData()->field_4A5 = 0;
		break;

	case kActionNone: 
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters()->param1) {
				_data->getCurrentParameters()->param1 = 1;
				// call function
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, chapter2, 42) {
}

IMPLEMENT_FUNCTION(Anna, chapter3, 44) {
}

IMPLEMENT_FUNCTION(Anna, bagage, 64) {
}

IMPLEMENT_FUNCTION(Anna, chapter4, 66) {
}

IMPLEMENT_FUNCTION(Anna, chapter5, 74) {
}

} // End of namespace LastExpress
