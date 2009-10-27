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

#include "lastexpress/resource.h"
#include "lastexpress/background.h"
#include "lastexpress/lastexpress.h"

#include "common/debug.h"

namespace LastExpress {

const Common::String archiveDemoPath("DEMO.HPF");
const Common::String archiveHDPath("HD.HPF");
const Common::String archiveCD1Path("CD1.HPF");
const Common::String archiveCD2Path("CD2.HPF");
const Common::String archiveCD3Path("CD3.HPF");

ResourceManager::ResourceManager(LastExpressEngine *engine) : _engine(engine) {
}

ResourceManager::~ResourceManager() {
	reset();
}

// Load a specific archive collection
//  - type is ignored in the demo version
//  - use ArchiveAll to load all three cds
//  - HD.hpf is always loaded along with the selected archive(s)
//  - will remove all other archives
bool ResourceManager::loadArchive(ArchiveType type) {
	// Unload all archives
	reset();

	// Demo version
	if (_engine->getFlags() & ADGF_DEMO)
		return loadArchive(archiveDemoPath);

	bool loadedOk = true;

	// Load HD
	loadedOk &= loadArchive(archiveHDPath);

	switch(type) {
	case kArchiveCd1:
		return loadedOk && loadArchive(archiveCD1Path);

	case kArchiveCd2:
		return loadedOk && loadArchive(archiveCD2Path);

	case kArchiveCd3:
		return loadedOk && loadArchive(archiveCD3Path);

	case kArchiveAll:
	default:
		loadedOk &= loadArchive(archiveCD1Path);
		loadedOk &= loadArchive(archiveCD2Path);
		loadedOk &= loadArchive(archiveCD3Path);
		break;
	}

	return loadedOk;
}

void ResourceManager::reset() {
	// Free the loaded archives
	for (Common::Array<HPFArchive *>::iterator it = _archives.begin(); it != _archives.end(); ++it) {
		delete (*it);
	}
	_archives.clear();
}

bool ResourceManager::loadArchive(const Common::String &name) {
	HPFArchive *archive = new HPFArchive(name);

	if (archive->count() == 0) {
		debugC(2, kLastExpressDebugResource, "Error opening archive: %s", name.c_str());
		return false;
	}

	_archives.push_back(archive);

	return true;
}

// Get a stream to file in the archive
//  - same as createReadStreamForMember except it checks if the file exists and will assert / output a debug message if not
Common::SeekableReadStream *ResourceManager::getFileStream(const Common::String &name) {

	// Check if the file exits in the archive
	if (!hasFile(name)) {
#ifdef _DEBUG
		error("Error opening file: %s", name.c_str());
#else
		debugC(2, kLastExpressDebugResource, "Error opening file: %s", name.c_str());
#endif
		return false;
	}

	debugC(2, kLastExpressDebugResource, "Opening file: %s", name.c_str());

	return createReadStreamForMember(name);
}

//////////////////////////////////////////////////////////////////////////
// Archive functions
//////////////////////////////////////////////////////////////////////////
bool ResourceManager::hasFile(const Common::String &name) {
	for (Common::Array<HPFArchive *>::iterator it = _archives.begin(); it != _archives.end(); ++it) {
		if ((*it)->hasFile(name))
			return true;
	}

	return false;
}

int ResourceManager::listMembers(Common::ArchiveMemberList &list) {
	int count = 0;

	for (Common::Array<HPFArchive *>::iterator it = _archives.begin(); it != _archives.end(); ++it) {

		Common::ArchiveMemberList members;
		count += (*it)->listMembers(members);

		list.insert(list.end(), members.begin(), members.end());
	}

	return count;
}

Common::ArchiveMemberPtr ResourceManager::getMember(const Common::String &name) {
	if (!hasFile(name))
		return Common::ArchiveMemberPtr();

	return Common::ArchiveMemberPtr(new Common::GenericArchiveMember(name, this));
}

Common::SeekableReadStream *ResourceManager::createReadStreamForMember(const Common::String &name) const {
	for (Common::Array<HPFArchive * const>::iterator it = _archives.begin(); it != _archives.end(); ++it) {

		Common::SeekableReadStream *stream = (*it)->createReadStreamForMember(name);

		if (stream)
			return stream;
	}

	return NULL;
}


// Resource loading

Background *ResourceManager::loadBackground(const Common::String &name) {
	// Open the resource
	Common::SeekableReadStream *stream = createReadStreamForMember(name + ".BG");
	if (!stream)
		return NULL;

	// Create the new background
	Background *bg = new Background;
	if (!bg) {
		delete stream;
		return NULL;
	}

	// Load the data
	if (!bg->load(stream)) {
		delete bg;
		return NULL;
	}

	return bg;
}

} // End of namespace LastExpress
