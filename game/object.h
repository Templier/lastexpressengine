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

#ifndef LASTEXPRESS_OBJECT_H
#define LASTEXPRESS_OBJECT_H

#include "common/serializer.h"
#include "common/system.h"

namespace LastExpress {

class LastExpressEngine;

class Objects : Common::Serializable {
public:
	struct Object {
		byte field_0;
		byte location;
		byte cursor;
		byte field_3;
		byte field_4;

		Object() {
			field_0 = 0;
			location = 0;
			cursor = 10;
			field_3 = 9;
			field_4 = 0;
		}
	};
	
	Objects(LastExpressEngine *engine);

	const Object get(uint index);
	void update(uint index, byte field_0, byte location, byte cursor, byte field_3);
	void updateField4(uint index, byte value);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

private:
	LastExpressEngine* _engine;

	Object _items[128];
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_OBJECT_H
