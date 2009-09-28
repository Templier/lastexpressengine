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

#include "lastexpress/lastexpress.h"
#include "lastexpress/cursor.h"

namespace LastExpress {

Cursor::Cursor(ResourceManager *resource) : _resource(resource) {}

Cursor::~Cursor() {

}

bool Cursor::load(const Common::String &name)
{
	// Get a stream to the file
	if (!_resource->hasFile(name)) {
		debugC(2, kLastExpressDebugSubtitle, "Error opening cursor: %s", name.c_str());
		return false;
	}

	Common::SeekableReadStream *stream = _resource->createReadStreamForMember(name);

	debugC(2, kLastExpressDebugCursor, "Loading cursor data file: %s", name.c_str());

	// Read header to get the number of cursors
	

	return true;
}

void Cursor::render() {

}


} // End of namespace LastExpress