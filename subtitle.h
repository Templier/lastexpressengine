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

#include "lastexpress/font.h"
#include "lastexpress/resource.h"

namespace LastExpress {

class Subtitle {
public:
	Subtitle();
	~Subtitle();

	bool load(Common::SeekableReadStream *in);
	void show(Font &font);

private:
	uint16 _timeStart;		//!< display start time
	uint16 _timeStop;		//!< display stop time

	uint16 _topLength;		//!< top line length
	uint16 *_topText;		//!< bottom line length

	uint16 _bottomLength;	//!< top line (UTF-16 string)
	uint16 *_bottomText;	//!< bottom line (UTF-16 string)
};

class SubtitleManager {
public:
	SubtitleManager(ResourceManager *resource);

	bool load(const Common::String &name);
	bool show(Font &font, uint16 index);

	// TODO add function bool show(uint16 currentTime);

	uint32 count();

private:
	ResourceManager *_resource;

	Common::Array<Subtitle> _subtitles;
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_SUBTITLE_H
