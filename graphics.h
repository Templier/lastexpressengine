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

#ifndef LASTEXPRESS_GRAPHICS_H
#define LASTEXPRESS_GRAPHICS_H

#include "graphics/pixelformat.h"
#include "graphics/surface.h"

namespace LastExpress {

class GraphicsManager {
public:
	GraphicsManager(Graphics::PixelFormat format);
	~GraphicsManager();

	// Update the screen
	void update();

	// Signal a change to the screen, will cause the planes to be remerged
	void change();

	// Clear all screen parts
	void clear();

	// FIXME this is there for animation until we change it to use the graphic surface here instead of its private ones.
	Graphics::Surface _screen;					// Actual screen surface

	// Accessors
	Graphics::Surface *getBackgroundA() { return &_backgroundA; }
	Graphics::Surface *getBackgroundC() { return &_backgroundC; }
	Graphics::Surface *getOverlay() { return &_overlay; }

private:
	Graphics::Surface _backgroundA;				// Background A
	Graphics::Surface _backgroundC;				// Background C
	Graphics::Surface _overlay;					// Overlay

	void mergePlanes();
	void updateScreen();

	bool _changed;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_GRAPHICS_H
