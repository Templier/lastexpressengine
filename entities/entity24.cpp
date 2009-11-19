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

#include "lastexpress/entities/entity24.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Entity24::Entity24(LastExpressEngine *engine) : Entity(engine, SavePoints::kEntity24) {
	ADD_CALLBACK_FUNCTION(Entity24, nullfunc);
	ADD_CALLBACK_FUNCTION(Entity24, nullfunc);
	ADD_CALLBACK_FUNCTION(Entity24, nullfunc);
	ADD_CALLBACK_FUNCTION(Entity24, chapter1);
	ADD_CALLBACK_FUNCTION(Entity24, nullfunc);
	ADD_CALLBACK_FUNCTION(Entity24, chapter2);
	ADD_CALLBACK_FUNCTION(Entity24, chapter3);
	ADD_CALLBACK_FUNCTION(Entity24, chapter4);
	ADD_CALLBACK_FUNCTION(Entity24, nullfunc);
	ADD_CALLBACK_FUNCTION(Entity24, chapter5);
	ADD_CALLBACK_FUNCTION(Entity24, nullfunc);
	ADD_NULL_FUNCTION();
}

void Entity24::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Entity24: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Entity24, chapter1, 4) {
}

IMPLEMENT_FUNCTION(Entity24, chapter2, 6) {
}

IMPLEMENT_FUNCTION(Entity24, chapter3, 7) {
}

IMPLEMENT_FUNCTION(Entity24, chapter4, 8) {
}

IMPLEMENT_FUNCTION(Entity24, chapter5, 10){
}

IMPLEMENT_NULL_FUNCTION(Entity24, 12)

} // End of namespace LastExpress
