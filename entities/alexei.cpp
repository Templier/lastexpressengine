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

#include "lastexpress/entities/alexei.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Alexei::Alexei(LastExpressEngine *engine) : Entity(engine, kEntityAlexei) {
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, chapter1);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, chapter2);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, chapter3);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, chapter4);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, nullfunc);
	ADD_CALLBACK_FUNCTION(Alexei, chapter5);
}

void Alexei::nullfunc(SavePoint *savepoint) {
	error("Alexei: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Alexei, chapter1, 17) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment2, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject10, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;		

		break;

	case kActionNone:
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters()->param1) {
				_data->getCurrentParameters()->param1 = 1;
				// call function 18
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Alexei, chapter2, 28) {
}

IMPLEMENT_FUNCTION(Alexei, chapter3, 32) {
}

IMPLEMENT_FUNCTION(Alexei, chapter4, 37) {
}

IMPLEMENT_FUNCTION(Alexei, chapter5, 48) {
}

} // End of namespace LastExpress
