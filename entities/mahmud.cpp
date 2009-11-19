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

Mahmud::Mahmud(LastExpressEngine *engine) : Entity(engine, SavePoints::kMahmud) {
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter1);
	ADD_CALLBACK_FUNCTION(Mahmud, nullfunc);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter2);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter3);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter4);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter5);
}

void Mahmud::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Mahmud: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, chapter1, 15) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kMahmud, 170483072, 0);

		getObjects()->update(Objects::kObjectCompartment4, SavePoints::kNone, 3, 10, 9);
		getObjects()->update(Objects::kObject20, SavePoints::kNone, 3, 10, 9);

		_data.field_491 = 540;
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

IMPLEMENT_FUNCTION(Mahmud, chapter2, 17) {
}

IMPLEMENT_FUNCTION(Mahmud, chapter3, 18) {
}

IMPLEMENT_FUNCTION(Mahmud, chapter4, 19) {
}

IMPLEMENT_FUNCTION(Mahmud, chapter5, 20) {
}

} // End of namespace LastExpress
