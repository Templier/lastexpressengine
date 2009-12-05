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

#include "lastexpress/entities/servers0.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Servers0::Servers0(LastExpressEngine *engine) : Entity(engine, kEntityServers0) {
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, chapter1);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, chapter2);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, chapter3);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, chapter4);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_CALLBACK_FUNCTION(Servers0, chapter5);
	ADD_CALLBACK_FUNCTION(Servers0, nullfunc);
	ADD_NULL_FUNCTION();
}

void Servers0::nullfunc(SavePoint *savepoint) {
	error("Servers0: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, chapter1, 11) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault: 
		getSavePoints()->addData(kEntityServers0, kAction270410280, 0);
		getSavePoints()->addData(kEntityServers0, kAction304061224, 1);
		getSavePoints()->addData(kEntityServers0, kAction252568704, 10);
		getSavePoints()->addData(kEntityServers0, kAction286534136, 11);
		getSavePoints()->addData(kEntityServers0, kAction218983616, 12);
		getSavePoints()->addData(kEntityServers0, kAction218586752, 13);
		getSavePoints()->addData(kEntityServers0, kAction207330561, 14);
		getSavePoints()->addData(kEntityServers0, kAction286403504, 16);
		getSavePoints()->addData(kEntityServers0, kAction218128129, 17);
		getSavePoints()->addData(kEntityServers0, kAction270068760, 18);
		getSavePoints()->addData(kEntityServers0, kAction223712416, 2);
		getSavePoints()->addData(kEntityServers0, kAction237485916, 5);
		getSavePoints()->addData(kEntityServers0, kAction188893625, 8);
		getSavePoints()->addData(kEntityServers0, kAction204704037, 6);
		getSavePoints()->addData(kEntityServers0, kAction292758554, 7);
		getSavePoints()->addData(kEntityServers0, kAction337548856, 9);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		break;

	case kActionNone: 
		// call function
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, chapter2, 23) {
}

IMPLEMENT_FUNCTION(Servers0, chapter3, 27) {
}

IMPLEMENT_FUNCTION(Servers0, chapter4, 31) {
}

IMPLEMENT_FUNCTION(Servers0, chapter5, 36) {
}

IMPLEMENT_NULL_FUNCTION(Servers0, 38)

} // End of namespace LastExpress
