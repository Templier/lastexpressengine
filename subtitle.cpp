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
#include "lastexpress/subtitle.h"

namespace LastExpress {

Subtitle::Subtitle(ResourceManager *resource) : _resource(resource) {}

Subtitle::~Subtitle() {

}

bool Subtitle::load(const Common::String &name)
{
	// Get a stream to the file
	if (!_resource->hasFile(name)) {
		debugC(2, kLastExpressDebugSubtitle, "Error opening subtitle: %s", name.c_str());
		return false;
	}

	Common::SeekableReadStream *stream = _resource->createReadStreamForMember(name);

	debugC(2, kLastExpressDebugSubtitle, "Loading subtitle: %s", name.c_str());

	// Read header to get the number of subtitles
	uint32 numSubtitles = stream->readUint16LE();
	debugC(3, kLastExpressDebugSubtitle, "Number of subtitles in file: %d", numSubtitles);

	// Read the list of subtitles
	for (unsigned int i = 0; i < numSubtitles; ++i) {		
		SubtitleData data;

		// Read start & stop times
		data.start = stream->readUint16LE();
		data.stop = stream->readUint16LE();

		// Read subtitles text
		data.topSize = stream->readUint16LE();
		data.bottomSize = stream->readUint16LE();

		if (data.topSize > 0) {
			data.top = (uint16*)malloc(data.topSize * sizeof(char));
			stream->read(data.top, data.topSize);
		}

		if (data.bottomSize > 0) {
			data.bottom = (uint16*)malloc(data.bottomSize * sizeof(char));
			stream->read(data.bottom, data.bottomSize);
		}

		_subtitles.push_back(data);

		// FIXME: UTF-16 strings, really?

		debugC(9, kLastExpressDebugSubtitle, "Subtitle entry: %d -> %d | %S - %S", data.start, data.stop, data.top, data.bottom);		
	}

	return true;
}

void Subtitle::render(Graphics::Surface *surface, uint16 currentTime) {

}


} // End of namespace LastExpress