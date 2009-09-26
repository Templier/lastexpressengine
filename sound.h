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

#ifndef LASTEXPRESS_SOUND_H
#define LASTEXPRESS_SOUND_H

namespace LastExpress {

class ResourceManager;

class Sound {
public:
	Sound(ResourceManager *resource);
	~Sound();

	bool load(const Common::String &name);
	void play();

private:
	struct SndHeader {
		uint32 size;			//!< data size
		uint16 count;			//!< number of blocks
	};

	struct SndBlock {
		int16 sample;			//!< initial sample
		uint16 index;			//!< initial index
		uint16 unused;			//!< unused (00)
		uint16* samples;		//!< IMA ADPCM sample codes
	};

	ResourceManager *_resource;

	SndHeader _header;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SOUND_H