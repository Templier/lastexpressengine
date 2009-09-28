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

#ifndef LASTEXPRESS_HPFARCHIVE_H
#define LASTEXPRESS_HPFARCHIVE_H

#include "common/archive.h"
#include "common/hash-str.h"
#include "common/hashmap.h"
#include "common/str.h"
#include "common/list.h"
#include "common/file.h"

///////////////////////////////////////////////////////////////////////////
//
//

namespace LastExpress {

class HPFArchive : public Common::Archive {
public:

	HPFArchive(const Common::String &path);
	~HPFArchive();

	bool hasFile(const Common::String &name);
	int listMembers(Common::ArchiveMemberList &list);
	Common::ArchiveMemberPtr getMember(const Common::String &name);
	Common::SeekableReadStream *createReadStreamForMember(const Common::String &name) const;

private:	
	static const unsigned int _archiveNameSize = 12;
	static const unsigned int _archiveSectorSize = 2048;

	// File entry
	struct HPFEntry {
		//char name[12];		//!< Name of the entry
		uint32 offset;			//!< Offset (in sectors of 2048 bytes)
		uint32 size; 			//!< Size (in sectors of 2048 bytes)
		uint16 isOnHD; 		    //!< File is always on HD (1: true; 0: false)
	};

	typedef Common::HashMap<Common::String, HPFEntry, Common::IgnoreCase_Hash, Common::IgnoreCase_EqualTo> FileMap;
		
	FileMap _files;							//!< List of files
	Common::SeekableReadStream *_archive;	//!< Archive file
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_HPFARCHIVE_H