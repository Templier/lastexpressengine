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

#include "lastexpress/game/object.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Servers1::Servers1(LastExpressEngine *engine) : Entity(engine, SavePoints::kServers1) {
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, chapter1);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, chapter2);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, chapter3);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, chapter4);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION(Servers1, chapter5);
	CALLBACK_FUNCTION(Servers1, nullfunc);
	CALLBACK_FUNCTION_NULL()
}

void Servers1::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Servers1: callback function not implemented!");
}

void Servers1::chapter1(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kServers1, 302203328, 5);
		getSavePoints()->addData(SavePoints::kServers1, 189688608, 6);
		getSavePoints()->addData(SavePoints::kServers1, 236237423, 7);
		getSavePoints()->addData(SavePoints::kServers1, 219377792, 8);
		getSavePoints()->addData(SavePoints::kServers1, 291721418, 10);
		getSavePoints()->addData(SavePoints::kServers1, 258136010, 11);
		getSavePoints()->addData(SavePoints::kServers1, 302996448, 2);
		getSavePoints()->addData(SavePoints::kServers1, 223002560, 0);
		getSavePoints()->addData(SavePoints::kServers1, 256200848, 9);
		getSavePoints()->addData(SavePoints::kServers1, 269485588, 3);
		getSavePoints()->addData(SavePoints::kServers1, 326144276, 4);

		_data.field_491 = 5900;
		_data.field_493 = 0;
		_data.field_495 = 5;
		break;

	case SavePoints::kActionNone: 
		// call function
		break;
	}
}

void Servers1::chapter2(SavePoints::SavePoint *savepoint) {
}

void Servers1::chapter3(SavePoints::SavePoint *savepoint) {
}

void Servers1::chapter4(SavePoints::SavePoint *savepoint) {
}

void Servers1::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
