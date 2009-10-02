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
#include "lastexpress/graphics.h"

namespace LastExpress {

GraphicsManager::GraphicsManager(LastExpressEngine *engine) :
	_engine(engine), _changed(false) {

	// Create the game surfaces
	_backgroundA.create(640, 480, _engine->_pixelFormat.bytesPerPixel);
	_backgroundC.create(640, 480, _engine->_pixelFormat.bytesPerPixel);
	_overlay.create(640, 480, _engine->_pixelFormat.bytesPerPixel);
}

GraphicsManager::~GraphicsManager() {
	// Free the game surfaces
	_backgroundA.free();
	_backgroundC.free();
	_overlay.free();	
}

void GraphicsManager::update() {
	// Update the screen if needed and reset the status
	if (_changed) {
		_engine->_system->updateScreen();
		_changed = false;
	}
}

void GraphicsManager::change() {
	_changed = true;
}

void GraphicsManager::MergePlanes() {
	byte *foreground = (byte *)_overlay.getBasePtr(0, 0);
	byte *backgroundA = (byte *)_backgroundA.getBasePtr(0, 0);
	byte *backgroundC = (byte *)_backgroundC.getBasePtr(0, 0);
	for (uint i = 640 * 480 * 2; i; i--) {

		// FIXME we already skip over parts of the image that aren't touched when decoding sequences
		// we might pass a copy of the screen data and let it do its magic

		// Skip transparent color
		if (255 == *(foreground)) {
			if (255 == *(backgroundA))
				*(foreground) = *(backgroundA);
			else
				*(foreground) = *(backgroundC);
		}

		foreground++;
		backgroundA++;
		backgroundC++;
	}
}

void GraphicsManager::updateScreen(Graphics::Surface *source) {
	_engine->_system->copyRectToScreen((byte *)source->getBasePtr(0, 0), 640 * 2, 0, 0, 640, 480);
	change();
}

} // End of Groovie namespace