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

#include "lastexpress/entities/boutarel.h"

#include "lastexpress/game/object.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Boutarel::Boutarel(LastExpressEngine *engine) : Entity(engine, SavePoints::kBoutarel) {
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, chapter1);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, chapter2);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, chapter3);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, chapter4);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, chapter5);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION(Boutarel, nullfunc);
	CALLBACK_FUNCTION_NULL();
}

void Boutarel::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Boutarel: callback function not implemented!");
}

void Boutarel::chapter1(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kBoutarel, 203520448, 0);
		getSavePoints()->addData(SavePoints::kBoutarel, 237889408, 1);

		getObjects()->update(34, SavePoints::kNone, 0, 10, 9);
		getObjects()->update(50, SavePoints::kNone, 0, 10, 9);
		getObjects()->update(42, SavePoints::kNone, 0, 255, 255);

		_data.field_491 = 1750;
		_data.field_493 = 1;
		_data.field_495 = 5;
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

void Boutarel::chapter2(SavePoints::SavePoint *savepoint) {
}

void Boutarel::chapter3(SavePoints::SavePoint *savepoint) {
}

void Boutarel::chapter4(SavePoints::SavePoint *savepoint) {
}

void Boutarel::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
