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

#include "lastexpress/game/items.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Entity39::Entity39(LastExpressEngine *engine) : Entity(engine, Entity::kEntity39) {	
	CALLBACK_FUNCTION(Entity39, chapter1);
	CALLBACK_FUNCTION(Entity39, chapter2);
	CALLBACK_FUNCTION(Entity39, chapter3);
	CALLBACK_FUNCTION(Entity39, chapter4);
	CALLBACK_FUNCTION(Entity39, chapter5);
	CALLBACK_FUNCTION(Entity39, process);
}

void Entity39::chapter1(SavePoints::SavePoint *savepoint) {
}

void Entity39::chapter2(SavePoints::SavePoint *savepoint) {
}

void Entity39::chapter3(SavePoints::SavePoint *savepoint) {
}

void Entity39::chapter4(SavePoints::SavePoint *savepoint) {
}

void Entity39::chapter5(SavePoints::SavePoint *savepoint) {
}

void Entity39::process(SavePoints::SavePoint *savepoint) {
	error("Entity39: callback function not implemented!");
}

} // End of namespace LastExpress
