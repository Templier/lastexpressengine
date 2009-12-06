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

#include "lastexpress/entities/rebecca.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Rebecca::Rebecca(LastExpressEngine *engine) : Entity(engine, kEntityRebecca) {
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter1);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter2);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter3);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, chapter4);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);	
	ADD_CALLBACK_FUNCTION(Rebecca, chapter5);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_CALLBACK_FUNCTION(Rebecca, nullfunc);
	ADD_NULL_FUNCTION();
}

void Rebecca::nullfunc(SavePoint *savepoint) {
	error("Rebecca: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Rebecca, chapter1, 21) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault: 
		getSavePoints()->addData(kEntityRebecca, kAction224253538, 0);

		getObjects()->update(Objects::kObjectCompartmentE, kEntityNone, kLocationNone, Cursor::kCursorHandKnock, Cursor::kCursorHand);
		getObjects()->update(Objects::kObject52, kEntityNone, kLocationNone, Cursor::kCursorHandKnock, Cursor::kCursorHand);
		getObjects()->update(Objects::kObject44, kEntityNone, kLocationNone, Cursor::kCursorKeepValue, Cursor::kCursorKeepValue);

		getObjects()->updateLocation2(Objects::kObject110, kLocation1);

		_data->getData()->field_491 = EntityData::kField491_2830;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;

		_data->getParameters(8, 0)->param2 = 1;
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

IMPLEMENT_FUNCTION(Rebecca, chapter2, 28) {
}

IMPLEMENT_FUNCTION(Rebecca, chapter3, 32) {
}

IMPLEMENT_FUNCTION(Rebecca, chapter4, 42) {
}

IMPLEMENT_FUNCTION(Rebecca, chapter5, 46) {
}

IMPLEMENT_NULL_FUNCTION(Rebecca, 49)

} // End of namespace LastExpress
