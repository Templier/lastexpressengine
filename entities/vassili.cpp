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
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, chapter1);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, chapter2);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, chapter3);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, chapter4);
	ADD_CALLBACK_FUNCTION(Vassili, nullfunc);
	ADD_CALLBACK_FUNCTION(Vassili, chapter5);
}

void Vassili::nullfunc(SavePoint *savepoint) {
	error("Vassili: callback function not implemented!");
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
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters()->param1) {
				_data->getCurrentParameters()->param1 = 1;
				// call function 5
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, chapter2, 12) {
}

IMPLEMENT_FUNCTION(Vassili, chapter3, 14) {
}

IMPLEMENT_FUNCTION(Vassili, chapter4, 16) {
}

IMPLEMENT_FUNCTION(Vassili, chapter5, 18) {
}

} // End of namespace LastExpress
