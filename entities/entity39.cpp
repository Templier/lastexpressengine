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

#include "lastexpress/entities/entity39.h"

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Entity39::Entity39(LastExpressEngine *engine) : Entity(engine, SavePoints::kEntity39) {	
	ADD_CALLBACK_FUNCTION(Entity39, chapter1);
	ADD_CALLBACK_FUNCTION(Entity39, chapter2);
	ADD_CALLBACK_FUNCTION(Entity39, chapter3);
	ADD_CALLBACK_FUNCTION(Entity39, chapter4);
	ADD_CALLBACK_FUNCTION(Entity39, chapter5);
	ADD_CALLBACK_FUNCTION(Entity39, process);
}

IMPLEMENT_FUNCTION(Entity39, chapter1, 1) {
}

IMPLEMENT_FUNCTION(Entity39, chapter2, 2) {
}

IMPLEMENT_FUNCTION(Entity39, chapter3, 3) {
}

IMPLEMENT_FUNCTION(Entity39, chapter4, 4) {
}

IMPLEMENT_FUNCTION(Entity39, chapter5, 5) {
}

IMPLEMENT_FUNCTION(Entity39, process, 6) {
	error("Entity39::process callback function not implemented!");
}

} // End of namespace LastExpress
