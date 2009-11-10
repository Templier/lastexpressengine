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

#include "lastexpress/entity.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/logic.h"

namespace LastExpress {

Entities::Entities(LastExpressEngine *engine) : _engine(engine) {}


const Entities::Entity Entities::get(uint index) {
	assert(index < 128);

	return _entities[index];
}

void Entities::update(uint index, byte field_0, byte location, byte cursor, byte field_3) {
	if (index >= 128)
		return;

	Entity *entity = &_entities[index];

	// Store original location
	byte original_location = entity->location;

	// Update entity
	entity->field_0 = field_0;
	entity->location = location;
	if (cursor != 255)
		entity->cursor = cursor;
	if (field_3 != 255)
		entity->field_3 = field_3;

	if (cursor != 255 || field_3 != 255) {
		// TODO redraw some stuff on the scene
	}

	// TODO set a global var

	if (original_location != location && (original_location == 2 || location == 2))
		if ((index > 0 && index < 9)
	     || (index > 31 && index < 40)) {
		 	_engine->getLogic()->updateTrainClock();
		}
}

//////////////////////////////////////////////////////////////////////////
// Serializable
//////////////////////////////////////////////////////////////////////////
void Entities::saveLoadWithSerializer(Common::Serializer &ser) {

}

} // End of namespace LastExpress
