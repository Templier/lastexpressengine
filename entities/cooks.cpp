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

#include "lastexpress/entities/cooks.h"

#include "lastexpress/game/object.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Cooks::Cooks(LastExpressEngine *engine) : Entity(engine, SavePoints::kCooks) {
	CALLBACK_FUNCTION(Cooks, nullfunc);
	CALLBACK_FUNCTION(Cooks, nullfunc);
	CALLBACK_FUNCTION(Cooks, nullfunc);
	CALLBACK_FUNCTION(Cooks, nullfunc);
	CALLBACK_FUNCTION(Cooks, chapter1);
	CALLBACK_FUNCTION(Cooks, nullfunc);
	CALLBACK_FUNCTION(Cooks, nullfunc);
	CALLBACK_FUNCTION(Cooks, chapter2);
	CALLBACK_FUNCTION(Cooks, nullfunc);
	CALLBACK_FUNCTION(Cooks, chapter3);
	CALLBACK_FUNCTION(Cooks, nullfunc);
	CALLBACK_FUNCTION(Cooks, chapter4);
	CALLBACK_FUNCTION(Cooks, nullfunc);
	CALLBACK_FUNCTION(Cooks, chapter5);
}

void Cooks::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Cooks: callback function not implemented!");
}

void Cooks::chapter1(SavePoints::SavePoint *savepoint) {
}

void Cooks::chapter2(SavePoints::SavePoint *savepoint) {
}

void Cooks::chapter3(SavePoints::SavePoint *savepoint) {
}

void Cooks::chapter4(SavePoints::SavePoint *savepoint) {
}

void Cooks::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
