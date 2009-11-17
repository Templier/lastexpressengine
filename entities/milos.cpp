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

#include "lastexpress/helpers.h"

namespace LastExpress {

Milos::Milos(LastExpressEngine *engine) : Entity(engine, SavePoints::kMilos) {
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, chapter1);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, chapter2);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, chapter3);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, chapter4);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, chapter5);
	CALLBACK_FUNCTION(Milos, nullfunc);
	CALLBACK_FUNCTION(Milos, nullfunc);
}

void Milos::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Milos: callback function not implemented!");
}

void Milos::chapter1(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kMilos, 157691176, 0);
		getSavePoints()->addData(SavePoints::kMilos, 208228224, 2);

		getObjects()->update(38, 0, 3, 10, 9);
		getObjects()->update(46, 0, 0, 255, 255);

		_data.field_491 = 4689;
		_data.field_493 = 1;
		_data.field_495 = 5;
		break;

	case SavePoints::kActionNone: 
		if (getState()->time > 1062000) {
			if (!getCallData().entries[0].field_0) {
				getCallData().entries[0].field_0 = 1;
				// call function
			}
		}
		break;
	}
}

void Milos::chapter2(SavePoints::SavePoint *savepoint) {
}

void Milos::chapter3(SavePoints::SavePoint *savepoint) {
}

void Milos::chapter4(SavePoints::SavePoint *savepoint) {
}

void Milos::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
