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

#include "lastexpress/entities/coudert.h"

#include "lastexpress/game/items.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Coudert::Coudert(LastExpressEngine *engine) : Entity(engine, SavePoints::kCoudert) {
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, chapter1);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, chapter2);
	CALLBACK_FUNCTION(Coudert, nullfunc);	
	CALLBACK_FUNCTION(Coudert, chapter3);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, chapter4);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, chapter5);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION(Coudert, nullfunc);
	CALLBACK_FUNCTION_NULL();
}

void Coudert::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Coudert: callback function not implemented!");
}

void Coudert::chapter1(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kCoudert, 292048641, 7);
		getSavePoints()->addData(SavePoints::kCoudert, 326348944, 8);
		getSavePoints()->addData(SavePoints::kCoudert, 171394341, 2);
		getSavePoints()->addData(SavePoints::kCoudert, 154005632, 4);
		getSavePoints()->addData(SavePoints::kCoudert, 169557824, 3);
		getSavePoints()->addData(SavePoints::kCoudert, 226031488, 5);
		getSavePoints()->addData(SavePoints::kCoudert, 339669520, 6);
		getSavePoints()->addData(SavePoints::kCoudert, 189750912, 10);
		getSavePoints()->addData(SavePoints::kCoudert, 185737168, 12);
		getSavePoints()->addData(SavePoints::kCoudert, 185671840, 13);
		getSavePoints()->addData(SavePoints::kCoudert, 205033696, 15);
		getSavePoints()->addData(SavePoints::kCoudert, 157026693, 14);
		getSavePoints()->addData(SavePoints::kCoudert, 189026624, 11);
		getSavePoints()->addData(SavePoints::kCoudert, 168254872, 17);
		getSavePoints()->addData(SavePoints::kCoudert, 201431954, 18);
		getSavePoints()->addData(SavePoints::kCoudert, 188570113, 19);

		_data.callback_data[8].entries[0].field_0 = 0;
		_data.callback_data[8].entries[0].field_4 = 1;

		_data.field_491 = 1500;
		_data.field_493 = 0;
		_data.field_495 = 4;

		getItems()->updateField4(111, 1);
		break;

	case 18:
		//if (_data.callbacks[_data.current_call + 8] == 1)
			// call function
		break;

	case SavePoints::kActionNone: 
		if (getState()->time > 1062000) {
			if (!getCallData().entries[0].field_0) {
				getCallData().entries[0].field_0 = 1;
				_data.callbacks[_data.current_call + 8] = 1;				
				// call function call(, 0, 0, 0, 0);
			}
		}
		break;
	}
}

void Coudert::chapter2(SavePoints::SavePoint *savepoint) {
}

void Coudert::chapter3(SavePoints::SavePoint *savepoint) {
}

void Coudert::chapter4(SavePoints::SavePoint *savepoint) {
}

void Coudert::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
