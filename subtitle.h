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

#ifndef LASTEXPRESS_SUBTITLE_H
#define LASTEXPRESS_SUBTITLE_H

#include "common/str.h"

namespace LastExpress {

class ResourceManager;

class Subtitle {
public:
	Subtitle(ResourceManager *resource);
	~Subtitle();

	bool load(const Common::String &name);
	void render(Graphics::Surface *surface, uint16 currentTime);

private:	
	struct SubtitleData {
		uint16 start;			//!< display start time
		uint16 stop;			//!< display stop time
		uint16 topSize;			//!< top line length
		uint16 bottomSize;		//!< bottom line length
		uint16* top;			//!< top line (UTF-16 string)
		uint16* bottom;			//!< bottom line (UTF-16 string)

		SubtitleData() : top(NULL), bottom(NULL) {}
		~SubtitleData() {
			if (top)
				free(top);
			if (bottom)
				free(bottom);
		}
	};

	ResourceManager *_resource;

	Common::Array<SubtitleData> _subtitles;
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_SUBTITLE_H