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

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Coudert::Coudert(LastExpressEngine *engine) : Entity(engine, SavePoints::kCoudert) {
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, chapter1);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, chapter2);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);	
	ADD_CALLBACK_FUNCTION(Coudert, chapter3);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, chapter4);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, chapter5);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_CALLBACK_FUNCTION(Coudert, nullfunc);
	ADD_NULL_FUNCTION();
}

void Coudert::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Coudert: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter1, 36) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction292048641, 7);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction326348944, 8);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction171394341, 2);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction154005632, 4);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction169557824, 3);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction226031488, 5);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction339669520, 6);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction189750912, 10);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction185737168, 12);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction185671840, 13);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction205033696, 15);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction157026693, 14);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction189026624, 11);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction168254872, 17);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction201431954, 18);
		getSavePoints()->addData(SavePoints::kCoudert, SavePoints::kAction188570113, 19);

		_data->getParameters(8, 0)->param1 = 0;
		_data->getParameters(8, 0)->param2 = 1;

		_data->getData()->field_491 = 1500;
		_data->getData()->field_493 = 0;
		_data->getData()->field_495 = 4;

		getObjects()->updateField4(Objects::kObject111, 1);
		break;

	case 18:
		//if (_data.callbacks[_data.current_call + 8] == 1)
			// call function
		break;

	case SavePoints::kActionNone: 
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters(0)->param1) {
				_data->getCurrentParameters(0)->param1 = 1;				
				_data->setCallback(_data->getData()->current_call + 8, 1);				
				// call function call(, 0, 0, 0, 0);
			}
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, chapter2, 42) {
}

IMPLEMENT_FUNCTION(Coudert, chapter3, 44) {
}

IMPLEMENT_FUNCTION(Coudert, chapter4, 52) {
}

IMPLEMENT_FUNCTION(Coudert, chapter5, 57) {
}

IMPLEMENT_NULL_FUNCTION(Coudert, 63)

} // End of namespace LastExpress
