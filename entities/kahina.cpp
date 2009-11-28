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

#include "lastexpress/entities/kahina.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Kahina::Kahina(LastExpressEngine *engine) : Entity(engine, SavePoints::kEntityKahina) {
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, chapter1);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, chapter2);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, chapter3);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, nullfunc);
	ADD_CALLBACK_FUNCTION(Kahina, chapter4);
	ADD_CALLBACK_FUNCTION(Kahina, chapter5);
}

void Kahina::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Kahina: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter1, 10) {
}

IMPLEMENT_FUNCTION(Kahina, chapter2, 16) {
}

IMPLEMENT_FUNCTION(Kahina, chapter3, 18) {
}

IMPLEMENT_FUNCTION(Kahina, chapter4, 28) {
}

IMPLEMENT_FUNCTION(Kahina, chapter5, 29) {
}

} // End of namespace LastExpress
