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

#include "lastexpress/entities/yasmin.h"

#include "lastexpress/game/items.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Yasmin::Yasmin(LastExpressEngine *engine) : Entity(engine, Entity::kYasmin) {
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, chapter1);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, chapter2);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, chapter3);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, chapter4);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, chapter5);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION(Yasmin, nullfunc);
	CALLBACK_FUNCTION_NULL();
}

void Yasmin::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Yasmin: callback function not implemented!");
}

void Yasmin::chapter1(SavePoints::SavePoint *savepoint) {
}

void Yasmin::chapter2(SavePoints::SavePoint *savepoint) {
}

void Yasmin::chapter3(SavePoints::SavePoint *savepoint) {
}

void Yasmin::chapter4(SavePoints::SavePoint *savepoint) {
}

void Yasmin::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
