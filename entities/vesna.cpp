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

#include "lastexpress/entities/vesna.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Vesna::Vesna(LastExpressEngine *engine) : Entity(engine, kEntityVesna) {
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, chapter1);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, chapter2);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, chapter3);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, chapter4);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, chapter5);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_CALLBACK_FUNCTION(Vesna, nullfunc);
	ADD_NULL_FUNCTION();
}

void Vesna::nullfunc(SavePoint *savepoint) {
	error("Vesna: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, chapter1, 12) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityVesna, kAction124190740, 0);

		_data->getData()->field_491 = EntityData::kField491_4689;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		break;

	case kActionNone:
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters()->param1) {
				_data->getCurrentParameters()->param1 = 1;
				// call function 13
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter2, 16) {
}

IMPLEMENT_FUNCTION(Vesna, chapter3, 19) {
}

IMPLEMENT_FUNCTION(Vesna, chapter4, 24) {
}

IMPLEMENT_FUNCTION(Vesna, chapter5, 28) {
}

IMPLEMENT_NULL_FUNCTION(Vesna, 31)

} // End of namespace LastExpress
