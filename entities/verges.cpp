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

#include "lastexpress/entities/verges.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Verges::Verges(LastExpressEngine *engine) : Entity(engine, SavePoints::kVerges) {
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, chapter1);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, chapter2);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, chapter3);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, chapter4);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, chapter5);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
	ADD_CALLBACK_FUNCTION(Verges, nullfunc);
}

void Verges::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Verges: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter1, 18) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kVerges, 191337656, 0);
		getSavePoints()->addData(SavePoints::kVerges, 226031488, 1);
		getSavePoints()->addData(SavePoints::kVerges, 339669520, 1);
		getSavePoints()->addData(SavePoints::kVerges, 167854368, 4);
		getSavePoints()->addData(SavePoints::kVerges, 158617345, 2);
		getSavePoints()->addData(SavePoints::kVerges, 168255788, 3);
		getSavePoints()->addData(SavePoints::kVerges, 201431954, 5);
		getSavePoints()->addData(SavePoints::kVerges, 168187490, 6);

		getObjects()->update(Objects::kObject104, SavePoints::kVerges, 0, 0, 9);
		getObjects()->update(Objects::kObject105, SavePoints::kVerges, 0, 0, 9);

		_data.field_491 = 5000;
		_data.field_493 = 0;
		_data.field_495 = 6;
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

IMPLEMENT_FUNCTION(Verges, chapter2, 27) {
}

IMPLEMENT_FUNCTION(Verges, chapter3, 29) {
}

IMPLEMENT_FUNCTION(Verges, chapter4, 36) {
}

IMPLEMENT_FUNCTION(Verges, chapter5, 39) {
}

} // End of namespace LastExpress
