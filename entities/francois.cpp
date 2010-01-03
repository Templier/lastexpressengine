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

#include "lastexpress/entities/francois.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Francois::Francois(LastExpressEngine *engine) : Entity(engine, kEntityFrancois) {
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, chapter1);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, chapter2);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, chapter3);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, chapter4);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, chapter5);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_CALLBACK_FUNCTION(Francois, nullfunc);
	ADD_NULL_FUNCTION();
}

void Francois::nullfunc(SavePoint *savepoint) {
	error("Francois: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Francois, chapter1, 17) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_5790;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;		

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

IMPLEMENT_FUNCTION(Francois, chapter2, 21) {
}

IMPLEMENT_FUNCTION(Francois, chapter3, 24) {
}

IMPLEMENT_FUNCTION(Francois, chapter4, 26) {
}

IMPLEMENT_FUNCTION(Francois, chapter5, 28) {
}

IMPLEMENT_NULL_FUNCTION(Francois, 31)

} // End of namespace LastExpress
