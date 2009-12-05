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

#include "lastexpress/entities/tatiana.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Tatiana::Tatiana(LastExpressEngine *engine) : Entity(engine, kEntityTatiana) {
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter1);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);	
	ADD_CALLBACK_FUNCTION(Tatiana, chapter2);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);	
	ADD_CALLBACK_FUNCTION(Tatiana, chapter3);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter4);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter5);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
	ADD_CALLBACK_FUNCTION(Tatiana, nullfunc);
}

void Tatiana::nullfunc(SavePoint *savepoint) {
	error("Tatiana: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, chapter1, 17) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault: 
		getSavePoints()->addData(kEntityTatiana, kAction191198209, 0);

		getObjects()->update(Objects::kObjectCompartmentB, kEntityNone, kLocation1, Cursor::kCursorHandKnock, Cursor::kCursorHand);
		getObjects()->update(Objects::kObject49, kEntityNone, kLocation1, Cursor::kCursorHandKnock, Cursor::kCursorHand);
		getObjects()->update(Objects::kObject41, kEntityNone, kNoLocation, Cursor::kCursorKeepValue, Cursor::kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_5419;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
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

IMPLEMENT_FUNCTION(Tatiana, chapter2, 25) {
}

IMPLEMENT_FUNCTION(Tatiana, chapter3, 31) {
}

IMPLEMENT_FUNCTION(Tatiana, chapter4, 43) {
}

IMPLEMENT_FUNCTION(Tatiana, chapter5, 52) {
}

} // End of namespace LastExpress
