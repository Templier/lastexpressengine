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

#include "lastexpress/entities/kronos.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Kronos::Kronos(LastExpressEngine *engine) : Entity(engine, kEntityKronos) {
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, chapter1);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, chapter2);
	ADD_CALLBACK_FUNCTION(Kronos, chapter3);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, nullfunc);
	ADD_CALLBACK_FUNCTION(Kronos, chapter4);
	ADD_CALLBACK_FUNCTION(Kronos, chapter5);
}

void Kronos::nullfunc(SavePoint *savepoint) {
	error("Kronos: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Kronos, chapter1, 7) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCeiling, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_6000;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_2;		

		break;

	case kActionNone:
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters()->param1) {
				_data->getCurrentParameters()->param1 = 1;
				// call function 8
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Kronos, chapter2, 12) {
}

IMPLEMENT_FUNCTION(Kronos, chapter3, 13) {
}

IMPLEMENT_FUNCTION(Kronos, chapter4, 24) {
}

IMPLEMENT_FUNCTION(Kronos, chapter5, 25) {
}

} // End of namespace LastExpress
