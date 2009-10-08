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

#ifndef LASTEXPRESS_RESOURCE_H
#define LASTEXPRESS_RESOURCE_H

#include "common/array.h"
#include "common/str.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/archive.h"

namespace LastExpress {

class ResourceManager : public Common::Archive {
public:
	enum ArchiveType {
		kArchiveCd1,
		kArchiveCd2,
		kArchiveCd3,
		kArchiveAll
	};

	ResourceManager(LastExpressEngine *engine);

	// Loading
	bool loadArchive(ArchiveType type);	
	Common::SeekableReadStream *getFileStream(const Common::String &name);

	// Archive functions
	bool hasFile(const Common::String &name);
	int listMembers(Common::ArchiveMemberList &list);
	Common::ArchiveMemberPtr getMember(const Common::String &name);
	Common::SeekableReadStream *createReadStreamForMember(const Common::String &name) const;

private:
	LastExpressEngine *_engine;

	bool loadArchive(const Common::String &name);

	Common::Array<HPFArchive*> _archives;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_RESOURCE_H
