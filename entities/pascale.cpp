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

#include "lastexpress/entities/pascale.h"

#include "lastexpress/game/object.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Pascale::Pascale(LastExpressEngine *engine) : Entity(engine, SavePoints::kPascale) {
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, chapter1);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, chapter2);
	CALLBACK_FUNCTION(Pascale, chapter3);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, chapter4);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, chapter5);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION(Pascale, nullfunc);
	CALLBACK_FUNCTION_NULL();
}

void Pascale::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Pascale: callback function not implemented!");
}

void Pascale::chapter1(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionDefault: 
		getSavePoints()->addData(SavePoints::kPascale, 239072064, 0);
		getSavePoints()->addData(SavePoints::kPascale, 257489762, 2);
		getSavePoints()->addData(SavePoints::kPascale, 207769280, 6);
		getSavePoints()->addData(SavePoints::kPascale, 101824388, 7);
		getSavePoints()->addData(SavePoints::kPascale, 136059947, 8);
		getSavePoints()->addData(SavePoints::kPascale, 223262556, 1);
		getSavePoints()->addData(SavePoints::kPascale, 269479296, 3);
		getSavePoints()->addData(SavePoints::kPascale, 352703104, 4);
		getSavePoints()->addData(SavePoints::kPascale, 352768896, 5);
		getSavePoints()->addData(SavePoints::kPascale, 191604416, 10);
		getSavePoints()->addData(SavePoints::kPascale, 190605184, 11);

		_data.field_491 = 5900;
		_data.field_493 = 0;
		_data.field_495 = 5;
		break;

	case SavePoints::kActionNone: 
		// call function
 		break;
	}
}

void Pascale::chapter2(SavePoints::SavePoint *savepoint) {
}

void Pascale::chapter3(SavePoints::SavePoint *savepoint) {
}

void Pascale::chapter4(SavePoints::SavePoint *savepoint) {
}

void Pascale::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
