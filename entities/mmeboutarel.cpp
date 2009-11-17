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

#include "lastexpress/entities/mmeboutarel.h"

#include "lastexpress/game/object.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

MmeBoutarel::MmeBoutarel(LastExpressEngine *engine) : Entity(engine, SavePoints::kMmeBoutarel) {
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);	
	CALLBACK_FUNCTION(MmeBoutarel, chapter1);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);	
	CALLBACK_FUNCTION(MmeBoutarel, chapter2);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, chapter3);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, chapter4);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, chapter5);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION(MmeBoutarel, nullfunc);
	CALLBACK_FUNCTION_NULL();
}

void MmeBoutarel::nullfunc(SavePoints::SavePoint *savepoint) {
	error("MmeBoutarel: callback function not implemented!");
}

void MmeBoutarel::chapter1(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kMmeBoutarel, 242526416, 0);
		
		getObjects()->update(35, SavePoints::kNone, 2, 0, 0);
		getObjects()->update(51, SavePoints::kNone, 0, 10, 9);

		_data.field_491 = 5790;
		_data.field_493 = 1;
		_data.field_495 = 4;
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

void MmeBoutarel::chapter2(SavePoints::SavePoint *savepoint) {
}

void MmeBoutarel::chapter3(SavePoints::SavePoint *savepoint) {
}

void MmeBoutarel::chapter4(SavePoints::SavePoint *savepoint) {
}

void MmeBoutarel::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
