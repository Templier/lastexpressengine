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

#include "lastexpress/entities/sophie.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Sophie::Sophie(LastExpressEngine *engine) : Entity(engine, SavePoints::kEntitySophie) {
	ADD_CALLBACK_FUNCTION(Sophie, nullfunc);
	ADD_CALLBACK_FUNCTION(Sophie, nullfunc);
	ADD_CALLBACK_FUNCTION(Sophie, nullfunc);
	ADD_CALLBACK_FUNCTION(Sophie, chapter1);
	ADD_CALLBACK_FUNCTION(Sophie, nullfunc);
	ADD_CALLBACK_FUNCTION(Sophie, chapter2);
	ADD_CALLBACK_FUNCTION(Sophie, chapter3);
	ADD_CALLBACK_FUNCTION(Sophie, chapter4);
	ADD_CALLBACK_FUNCTION(Sophie, nullfunc);
	ADD_CALLBACK_FUNCTION(Sophie, chapter5);
	ADD_CALLBACK_FUNCTION(Sophie, nullfunc);
	ADD_NULL_FUNCTION();
}

void Sophie::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Sophie: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Sophie, chapter1, 4) {
}

IMPLEMENT_FUNCTION(Sophie, chapter2, 6) {
}

IMPLEMENT_FUNCTION(Sophie, chapter3, 7) {
}

IMPLEMENT_FUNCTION(Sophie, chapter4, 8) {
}

IMPLEMENT_FUNCTION(Sophie, chapter5, 10){
}

IMPLEMENT_NULL_FUNCTION(Sophie, 12)

} // End of namespace LastExpress
