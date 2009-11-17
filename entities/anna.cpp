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

#include "lastexpress/helpers.h"

namespace LastExpress {

Anna::Anna(LastExpressEngine *engine) : Entity(engine, SavePoints::kAnna) {
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, chapter1);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, chapter2);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, chapter3);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, chapter4);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, chapter5);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
	CALLBACK_FUNCTION(Anna, nullfunc);
}

void Anna::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Anna: callback function not implemented!");
}

void Anna::chapter1(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kAnna, 291662081, 0);
		getSavePoints()->addData(SavePoints::kAnna, 238936000, 1);

		getObjects()->update(37, SavePoints::kNone, 1, 10, 9);
		getObjects()->update(53, SavePoints::kNone, 1, 10, 9);
		getObjects()->update(45, SavePoints::kNone, 1, 255, 255);

		_data.field_491 = 8200;
		_data.field_493 = 1;
		_data.field_495 = 3;
		_data.field_4A5 = 0;
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

void Anna::chapter2(SavePoints::SavePoint *savepoint) {
}

void Anna::chapter3(SavePoints::SavePoint *savepoint) {
}

void Anna::chapter4(SavePoints::SavePoint *savepoint) {
}

void Anna::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
