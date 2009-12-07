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

Mahmud::Mahmud(LastExpressEngine *engine) : Entity(engine, kEntityMahmud) {
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

void Mahmud::nullfunc(SavePoint *savepoint) {
	error("Mahmud: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, chapter1, 15) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault: 
		getSavePoints()->addData(kEntityMahmud, kAction170483072, 0);

		getObjects()->update(kObjectCompartment4, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject20, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_540;
		_data->getData()->field_493 = EntityData::kField493_0;
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

IMPLEMENT_FUNCTION(Mahmud, chapter2, 17) {
}

IMPLEMENT_FUNCTION(Mahmud, chapter3, 18) {
}

IMPLEMENT_FUNCTION(Mahmud, chapter4, 19) {
}

IMPLEMENT_FUNCTION(Mahmud, chapter5, 20) {
}

} // End of namespace LastExpress
