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

#include "lastexpress/entities/milos.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Milos::Milos(LastExpressEngine *engine) : Entity(engine, kEntityMilos) {
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, chapter1);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, chapter2);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, chapter3);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, chapter4);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, chapter5);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
	ADD_CALLBACK_FUNCTION(Milos, nullfunc);
}

void Milos::nullfunc(SavePoint *savepoint) {
	error("Milos: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Milos, chapter1, 12) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault: 
		getSavePoints()->addData(kEntityMilos, kAction157691176, 0);
		getSavePoints()->addData(kEntityMilos, kAction208228224, 2);

		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject46, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_4689;
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

IMPLEMENT_FUNCTION(Milos, chapter2, 19) {
}

IMPLEMENT_FUNCTION(Milos, chapter3, 22) {
}

IMPLEMENT_FUNCTION(Milos, chapter4, 28) {
}

IMPLEMENT_FUNCTION(Milos, chapter5, 33) {
}

} // End of namespace LastExpress
