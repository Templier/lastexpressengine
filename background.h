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

#ifndef LASTEXPRESS_BACKGROUND_H
#define LASTEXPRESS_BACKGROUND_H

#include "graphics/surface.h"

#include "lastexpress/resource.h"

namespace LastExpress {

class ResourceManager;

class Background {
public:
	Background(ResourceManager *resource);
	~Background();

	bool load(const Common::String &name);
	void render(Graphics::Surface *surface);

private:
	struct BackgroundHeader {
		uint32 posX;			//!< position X on screen
		uint32 posY;			//!< position Y on screen
		uint32 width;			//!< image width
		uint32 height;			//!< image height
		uint32 redSize;			//!< red color channel data size
		uint32 blueSize;		//!< blue color channel data size
		uint32 greenSize;		//!< green color channel data size
	};

	ResourceManager *_resource;

	BackgroundHeader _header;
	byte *_pixels;
	uint32 _size;

	void cleanup();
	void decompress(byte* data, uint32 dataSize, byte* buffer, uint32 bufferSize);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_BACKGROUND_H