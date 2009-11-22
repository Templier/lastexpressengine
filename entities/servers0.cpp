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

Servers0::Servers0(LastExpressEngine *engine) : Entity(engine, SavePoints::kServers0) {
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

void Servers0::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Servers0: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, chapter1, 11) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kServers0, 270410280, 0);
		getSavePoints()->addData(SavePoints::kServers0, 304061224, 1);
		getSavePoints()->addData(SavePoints::kServers0, 252568704, 10);
		getSavePoints()->addData(SavePoints::kServers0, 286534136, 11);
		getSavePoints()->addData(SavePoints::kServers0, 218983616, 12);
		getSavePoints()->addData(SavePoints::kServers0, 218586752, 13);
		getSavePoints()->addData(SavePoints::kServers0, 207330561, 14);
		getSavePoints()->addData(SavePoints::kServers0, 286403504, 16);
		getSavePoints()->addData(SavePoints::kServers0, 218128129, 17);
		getSavePoints()->addData(SavePoints::kServers0, 270068760, 18);
		getSavePoints()->addData(SavePoints::kServers0, 223712416, 2);
		getSavePoints()->addData(SavePoints::kServers0, 237485916, 5);
		getSavePoints()->addData(SavePoints::kServers0, 188893625, 8);
		getSavePoints()->addData(SavePoints::kServers0, 204704037, 6);
		getSavePoints()->addData(SavePoints::kServers0, 292758554, 7);
		getSavePoints()->addData(SavePoints::kServers0, 337548856, 9);

		_data->getData()->field_491 = 5900;
		_data->getData()->field_493 = 0;
		_data->getData()->field_495 = 5;
		break;

	case SavePoints::kActionNone: 
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
