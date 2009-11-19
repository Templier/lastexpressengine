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

#include "lastexpress/entities/hadija.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Hadija::Hadija(LastExpressEngine *engine) : Entity(engine, SavePoints::kHadija) {
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, chapter1);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, chapter2);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, chapter3);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, chapter4);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, chapter5);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_CALLBACK_FUNCTION(Hadija, nullfunc);
	ADD_NULL_FUNCTION();
}

void Hadija::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Hadija: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Hadija, chapter1, 10) {
}

IMPLEMENT_FUNCTION(Hadija, chapter2, 13) {
}

IMPLEMENT_FUNCTION(Hadija, chapter3, 15) {
}

IMPLEMENT_FUNCTION(Hadija, chapter4, 17) {
}

IMPLEMENT_FUNCTION(Hadija, chapter5, 20) {
}

IMPLEMENT_NULL_FUNCTION(Hadija, 24)

} // End of namespace LastExpress
