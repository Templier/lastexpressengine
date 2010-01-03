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

#include "lastexpress/game/object.h"

#include "lastexpress/game/logic.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Objects::Objects(LastExpressEngine *engine) : _engine(engine) {}


const Objects::Object Objects::get(ObjectIndex index) {
	assert(index < 128);

	return _objects[index];
}

void Objects::update(ObjectIndex index, EntityIndex entity, ObjectLocation location, CursorStyle cursor, CursorStyle cursor2) {
	if (index >= 128)
		return;

	Object *object = &_objects[index];

	// Store original location
	ObjectLocation original_location = object->location;

	// Update entity
	object->entity = entity;
	object->location = location;

	if (cursor != kCursorKeepValue || cursor2 != kCursorKeepValue) {
		if (cursor != kCursorKeepValue)
			object->cursor = cursor;
		if (cursor2 != kCursorKeepValue)
			object->cursor2 = cursor2;

		getLogic()->updateCursor();
	}

	// Compartments
	if (original_location != location && (original_location == kLocation2 || location == kLocation2))
		if ((index >= kObjectCompartment1 && index <= kObjectCompartment8)
	     || (index >= kObjectCompartmentA && index <= kObjectCompartmentF)) {
		 	getLogic()->updateTrainClock();
		}
}

void Objects::updateLocation2(ObjectIndex index, ObjectLocation location2) {
	if (index >= 128)
		return;

	_objects[index].location2 = location2;
}

//////////////////////////////////////////////////////////////////////////
// Serializable
//////////////////////////////////////////////////////////////////////////
void Objects::saveLoadWithSerializer(Common::Serializer &ser) {

}

} // End of namespace LastExpress
