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
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Boutarel::Boutarel(LastExpressEngine *engine) : Entity(engine, kEntityBoutarel) {
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter1);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter2);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter3);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter4);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, chapter5);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(Boutarel, nullfunc);
	ADD_NULL_FUNCTION();
}

void Boutarel::nullfunc(SavePoint *savepoint) {
	error("Boutarel: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Boutarel, chapter1, 19) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault: 
		getSavePoints()->addData(kEntityBoutarel, kAction203520448, 0);
		getSavePoints()->addData(kEntityBoutarel, kAction237889408, 1);

		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject42, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_1750;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
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

IMPLEMENT_FUNCTION(Boutarel, chapter2, 23) {
}

IMPLEMENT_FUNCTION(Boutarel, chapter3, 26) {
}

IMPLEMENT_FUNCTION(Boutarel, chapter4, 31) {
}

IMPLEMENT_FUNCTION(Boutarel, chapter5, 36) {
}

IMPLEMENT_NULL_FUNCTION(Boutarel, 39)

} // End of namespace LastExpress
