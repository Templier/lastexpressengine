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

#include "common/stream.h"
#include "common/endian.h"
#include "common/fs.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

const Common::String archiveDemoPath("DEMO.HPF");
const Common::String archiveHDPath("HD.HPF");
const Common::String archiveCD1Path("CD1.HPF");
const Common::String archiveCD2Path("CD2.HPF");
const Common::String archiveCD3Path("CD3.HPF");

const Common::String fontName("FONT.DAT");
const Common::String cursorsName("CURSORS.TBM");

ResourceManager::ResourceManager(LastExpressEngine *engine) : _engine(engine) {

	// Load stable archives (DEMO or HD archives)
	if (_engine->getFlags() & ADGF_DEMO) {
		_archives.push_back(new HPFArchive(archiveDemoPath));
	} else {
		_archives.push_back(new HPFArchive(archiveHDPath));

		// TODO: there are lots of duplicated files in CD archives: we need to handle load/unload of cd archives 
		// FIXME: load CD archives on-the-fly?
		_archives.push_back(new HPFArchive(archiveCD1Path));
		//_archives.push_back(new HPFArchive(archiveCD2Path));
		//_archives.push_back(new HPFArchive(archiveCD3Path));
	}
}

ResourceManager::~ResourceManager() {
}

//////////////////////////////////////////////////////////////////////////
// Archive functions
//////////////////////////////////////////////////////////////////////////
bool ResourceManager::hasFile(const Common::String &name) {
	for (Common::Array<HPFArchive*>::iterator it = _archives.begin(); it != _archives.end(); ++it) {
		if ((*it)->hasFile(name))
			return true;
	}

	return false;
}

int ResourceManager::listMembers(Common::ArchiveMemberList &list) {
	int count = 0;

	for (Common::Array<HPFArchive*>::iterator it = _archives.begin(); it != _archives.end(); ++it) {
		
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
	for (Common::Array<HPFArchive* const>::iterator it = _archives.begin(); it != _archives.end(); ++it) {

		Common::SeekableReadStream *stream = (*it)->createReadStreamForMember(name);

		if (stream)
			return stream;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Data handling
//////////////////////////////////////////////////////////////////////////
Background *ResourceManager::loadBackground(const Common::String &name) {

	Background* background = new Background(this);
	
	if (!background->load(name))
		return NULL;

	return background;
}

Sound *ResourceManager::loadSound(const Common::String &name) {

	Sound* sound = new Sound(this);

	if (!sound->load(name))
		return NULL;

	return sound;
}

Subtitle *ResourceManager::loadSubtitle(const Common::String &name) {

	Subtitle* subtitle = new Subtitle(this);

	if (!subtitle->load(name))
		return NULL;

	return subtitle;
}

Animation *ResourceManager::loadSequence(const Common::String &name) {

	Animation* sequence = new Animation(_engine);

	if (!sequence->loadSequence(name))
		return NULL;

	return sequence;
}

Animation *ResourceManager::loadAnimation(const Common::String &name) {

	Animation* animation = new Animation(_engine);

	if (!animation->loadAnimation(name))
		return NULL;

	return animation;
}

} // End of namespace LastExpress