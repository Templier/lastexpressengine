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

#include "lastexpress/entities/servers1.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Servers1::Servers1(LastExpressEngine *engine) : Entity(engine, kEntityServers1) {
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, chapter1);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, chapter2);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, chapter3);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, chapter4);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers1, chapter5);
	ADD_CALLBACK_FUNCTION(Servers1, nullfunc);
	ADD_NULL_FUNCTION()
}

void Servers1::nullfunc(SavePoint *savepoint) {
	error("Servers1: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, chapter1, 8) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault: 
		getSavePoints()->addData(kEntityServers1, kAction302203328, 5);
		getSavePoints()->addData(kEntityServers1, kAction189688608, 6);
		getSavePoints()->addData(kEntityServers1, kAction236237423, 7);
		getSavePoints()->addData(kEntityServers1, kAction219377792, 8);
		getSavePoints()->addData(kEntityServers1, kAction291721418, 10);
		getSavePoints()->addData(kEntityServers1, kAction258136010, 11);
		getSavePoints()->addData(kEntityServers1, kAction302996448, 2);
		getSavePoints()->addData(kEntityServers1, kAction223002560, 0);
		getSavePoints()->addData(kEntityServers1, kAction256200848, 9);
		getSavePoints()->addData(kEntityServers1, kAction269485588, 3);
		getSavePoints()->addData(kEntityServers1, kAction326144276, 4);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		break;

	case kActionNone: 
		// call function
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, chapter2, 17) {
}

IMPLEMENT_FUNCTION(Servers1, chapter3, 22) {
}

IMPLEMENT_FUNCTION(Servers1, chapter4, 25) {
}

IMPLEMENT_FUNCTION(Servers1, chapter5, 30) {
}

IMPLEMENT_NULL_FUNCTION(Servers1, 32)

} // End of namespace LastExpress
