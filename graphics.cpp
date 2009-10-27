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

#include "lastexpress/graphics.h"

#include "common/system.h"

namespace LastExpress {

GraphicsManager::GraphicsManager(Graphics::PixelFormat format) : _changed(false) {

	_screen.create(640, 480, format.bytesPerPixel);

	// Create the game surfaces
	_backgroundA.create(640, 480, format.bytesPerPixel);
	_backgroundC.create(640, 480, format.bytesPerPixel);
	_overlay.create(640, 480, format.bytesPerPixel);
	_inventory.create(640, 480, format.bytesPerPixel);

	clear(kBackgroundAll);
}

GraphicsManager::~GraphicsManager() {
	// Free the game surfaces
	_screen.free();
	_backgroundA.free();
	_backgroundC.free();
	_overlay.free();
	_inventory.free();
}

void GraphicsManager::update() {
	// Update the screen if needed and reset the status
	if (_changed) {
		mergePlanes();
		updateScreen();
		_changed = false;
	}
}

void GraphicsManager::change() {
	_changed = true;
}

void GraphicsManager::clear(BackgroundType type) {
	clear(type, Common::Rect(640, 480));
}

void GraphicsManager::clear(BackgroundType type, Common::Rect rect) {
	switch (type) {
		default:
			error("GraphicsManager::clear() - Unknown background type: %d", type);
			break;

		case kBackgroundA:
		case kBackgroundC:
		case kBackgroundOverlay:
		case kBackgroundInventory:
			getSurface(type)->fillRect(rect, 0);
			break;

		case kBackgroundAll:
			_backgroundA.fillRect(rect, 0);
			_backgroundC.fillRect(rect, 0);
			_overlay.fillRect(rect, 0);
			_inventory.fillRect(rect, 0);
			break;
	}
}

bool GraphicsManager::draw(Drawable *drawable, BackgroundType type, bool transition) {
	// TODO store rect for later use
	Common::Rect rect = drawable->draw(getSurface(type));

	return (!rect.isEmpty());
}

bool GraphicsManager::draw(Drawable *drawable, uint index, BackgroundType type, bool transition) {
	// TODO store rect for later use
	Common::Rect rect = drawable->draw(getSurface(type), index);

	return (!rect.isEmpty());
}

bool GraphicsManager::draw(Drawable *drawable, int x, int y, BackgroundType type, bool transition) {
	// TODO store rect for later use
	Common::Rect rect = drawable->draw(getSurface(type), x, y);

	return (!rect.isEmpty());
}

Graphics::Surface *GraphicsManager::getSurface(BackgroundType type) {
	switch (type) {
		default:
			error("GraphicsManager::getSurface() - Unknown surface type: %d", type);
			break;

		case kBackgroundA:
			return &_backgroundA;
			break;

		case kBackgroundC:
			return &_backgroundC;
			break;

		case kBackgroundOverlay:
			return &_overlay;
			break;

		case kBackgroundInventory:
			return &_inventory;
			break;

		case kBackgroundAll:
			error("GraphicsManager::getSurface() - cannot return a surface for kBackgroundAll!");
			break;
	}
}

// TODO optimize to only merge dirty rects
void GraphicsManager::mergePlanes() {
	// Clear screen surface
	_screen.fillRect(Common::Rect(640, 480), 0);

	uint16 *screen = (uint16 *)_screen.pixels;
	uint16 *inventory = (uint16 *)_inventory.pixels;
	uint16 *overlay = (uint16 *)_overlay.pixels;
	uint16 *backgroundC = (uint16 *)_backgroundC.pixels;
	uint16 *backgroundA = (uint16 *)_backgroundA.pixels;

	for (int i = 0; i < 640 * 480; i++) {

		if (*(inventory))
			*(screen) = *(inventory);
		else if (*(overlay))
			*(screen) = *(overlay);
		else if (*(backgroundA))
			*(screen) = *(backgroundA);
		else
			*(screen) = *(backgroundC);

		inventory++;
		screen++;
		overlay++;
		backgroundA++;
		backgroundC++;
	}
}

void GraphicsManager::updateScreen() {
	g_system->fillScreen(0);
	g_system->copyRectToScreen((byte *)_screen.getBasePtr(0, 0), 640 * 2, 0, 0, 640, 480);
}

} // End of namespace LastExpress
