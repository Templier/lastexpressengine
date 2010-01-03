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

#include "lastexpress/entities/gendarmes.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Gendarmes::Gendarmes(LastExpressEngine *engine) : Entity(engine, kEntityGendarmes) {
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter1);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, nullfunc);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter2);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter3);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter4);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter5);
}

void Gendarmes::nullfunc(SavePoint *savepoint) {
	error("Gendarmes: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Gendarmes, chapter1, 2) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		_data->getData()->field_495 = EntityData::kField495_0;
		break;

	case kActionNone:
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters()->param1) {
				_data->getCurrentParameters()->param1 = 1;
				// call function 11
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Gendarmes, chapter2, 14) {
}

IMPLEMENT_FUNCTION(Gendarmes, chapter3, 15) {
}

IMPLEMENT_FUNCTION(Gendarmes, chapter4, 16) {
}

IMPLEMENT_FUNCTION(Gendarmes, chapter5, 17) {
}

} // End of namespace LastExpress
