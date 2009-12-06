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

#include "lastexpress/entities/mmeboutarel.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/state.h"
#include "lastexpress/game/savepoint.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

MmeBoutarel::MmeBoutarel(LastExpressEngine *engine) : Entity(engine, kEntityMmeBoutarel) {
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);	
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter1);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);	
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter2);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter3);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter4);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter5);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	ADD_NULL_FUNCTION();
}

void MmeBoutarel::nullfunc(SavePoint *savepoint) {
	error("MmeBoutarel: callback function not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter1, 10) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault: 
		getSavePoints()->addData(kEntityMmeBoutarel, kAction242526416, 0);
		
		getObjects()->update(Objects::kObjectCompartmentD, kEntityNone, kLocation2, Cursor::kCursorNormal, Cursor::kCursorNormal);
		getObjects()->update(Objects::kObject51, kEntityNone, kLocationNone, Cursor::kCursorHandKnock, Cursor::kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_5790;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
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

IMPLEMENT_FUNCTION(MmeBoutarel, chapter2, 17) {
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter3, 20) {
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter4, 22) {
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter5, 26) {
}

IMPLEMENT_NULL_FUNCTION(MmeBoutarel, 29)

} // End of namespace LastExpress
