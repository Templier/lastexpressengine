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

#include "lastexpress/entities/alexei.h"

#include "lastexpress/game/items.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Alexei::Alexei(LastExpressEngine *engine) : Entity(engine, Entity::kAlexei) {
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, chapter1);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, chapter2);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);	
	CALLBACK_FUNCTION(Alexei, chapter3);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, chapter4);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, nullfunc);
	CALLBACK_FUNCTION(Alexei, chapter5);
}

void Alexei::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Alexei: callback function not implemented!");
}

void Alexei::chapter1(SavePoints::SavePoint *savepoint) {
}

void Alexei::chapter2(SavePoints::SavePoint *savepoint) {
}

void Alexei::chapter3(SavePoints::SavePoint *savepoint) {
}

void Alexei::chapter4(SavePoints::SavePoint *savepoint) {
}

void Alexei::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
