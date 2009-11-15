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

#include "lastexpress/entities/verges.h"

#include "lastexpress/game/items.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Verges::Verges(LastExpressEngine *engine) : Entity(engine, SavePoints::kVerges) {
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, chapter1);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, chapter2);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, chapter3);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, chapter4);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, chapter5);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
	CALLBACK_FUNCTION(Verges, nullfunc);
}

void Verges::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Verges: callback function not implemented!");
}

void Verges::chapter1(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kVerges, 191337656, 0);
		getSavePoints()->addData(SavePoints::kVerges, 226031488, 1);
		getSavePoints()->addData(SavePoints::kVerges, 339669520, 1);
		getSavePoints()->addData(SavePoints::kVerges, 167854368, 4);
		getSavePoints()->addData(SavePoints::kVerges, 158617345, 2);
		getSavePoints()->addData(SavePoints::kVerges, 168255788, 3);
		getSavePoints()->addData(SavePoints::kVerges, 201431954, 5);
		getSavePoints()->addData(SavePoints::kVerges, 168187490, 6);

		getItems()->update(104, 9, 0, 0, 9);
		getItems()->update(105, 9, 0, 0, 9);

		_data.field_491 = 5000;
		_data.field_493 = 0;
		_data.field_495 = 6;
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

void Verges::chapter2(SavePoints::SavePoint *savepoint) {
}

void Verges::chapter3(SavePoints::SavePoint *savepoint) {
}

void Verges::chapter4(SavePoints::SavePoint *savepoint) {
}

void Verges::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
