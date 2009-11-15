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

#include "lastexpress/entities/rebecca.h"

#include "lastexpress/game/items.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Rebecca::Rebecca(LastExpressEngine *engine) : Entity(engine, SavePoints::kRebecca) {
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, chapter1);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, chapter2);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, chapter3);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, chapter4);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);	
	CALLBACK_FUNCTION(Rebecca, chapter5);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION(Rebecca, nullfunc);
	CALLBACK_FUNCTION_NULL();
}

void Rebecca::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Rebecca: callback function not implemented!");
}

void Rebecca::chapter1(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kRebecca, 224253538, 0);

		getItems()->update(36, 0, 0, 10, 9);
		getItems()->update(52, 0, 0, 10, 9);
		getItems()->update(44, 0, 0, 255, 255);

		getItems()->updateField4(110, 1);

		_data.field_491 = 2830;
		_data.field_493 = 1;
		_data.field_495 = 5;

		_data.callback_data[8].entries[0].field_4 = 1;
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

void Rebecca::chapter2(SavePoints::SavePoint *savepoint) {
}

void Rebecca::chapter3(SavePoints::SavePoint *savepoint) {
}

void Rebecca::chapter4(SavePoints::SavePoint *savepoint) {
}

void Rebecca::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
