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

#include "lastexpress/cursor.h"
#include "lastexpress/lastexpress.h"

#include "graphics/cursorman.h"

namespace LastExpress {

Cursor::Cursor() : _current(kCursorMAX) {}

bool Cursor::load(Common::SeekableReadStream *stream) {
	if (!stream)
		return false;

	// Load the whole file to memory
	Common::MemoryReadStream *data = stream->readStream(stream->size());
	delete stream;
	if (!data)
		return false;

	// Read the hotspot data
	for (int i = 0; i < kCursorMAX; i++) {
		_cursors[i].hotspotX = data->readUint16LE();
		_cursors[i].hotspotY = data->readUint16LE();
		debugC(15, kLastExpressDebugCursor | kLastExpressDebugAll,
			"Cursor %d hotspot x: %d, hotspot y: %d",
			i, _cursors[i].hotspotX, _cursors[i].hotspotY);
	}

	// Read the pixel data
	for (int i = 0; i < kCursorMAX; i++)
		for (int pix = 0; pix < 32 * 32; pix++)
			_cursors[i].image[pix] = data->readUint16LE();

	delete data;
	return true;
}

void Cursor::show(bool visible) {
	CursorMan.showMouse(visible);
}

bool Cursor::checkStyle(CursorStyle style) {
	if ((int)style < 0 || (int)style >= kCursorMAX) {
		debugC(2, kLastExpressDebugGraphics, "Trying to use an invalid cursor style: was %d, max %d", (int)style, kCursorMAX);
		return false;
	}

	return true;
}

bool Cursor::setStyle(CursorStyle style) {
	if (!checkStyle(style))
		return false;

	if (style == _current)
		return true;

	debugC(10, kLastExpressDebugCursor | kLastExpressDebugAll, "Cursor: setting style: %d", style);

	// Save the new cursor
	_current = style;

	// Reuse the screen pixel format
	Graphics::PixelFormat pf = g_system->getScreenFormat();
	CursorMan.replaceCursor((const byte *)getCursorImage(_current), 32, 32,
		_cursors[_current].hotspotX, _cursors[_current].hotspotY, 0, 1, &pf);

	return true;
}

uint16 *Cursor::getCursorImage(CursorStyle style) {
	if (!checkStyle(style))
		return NULL;
	return _cursors[style].image;
}


Icon::Icon(Cursor::CursorStyle style) : _style(style), _brightness(100) {}

void Icon::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Icon::setBrightness(uint8 brightness) {
	_brightness = brightness;
}

Common::Rect Icon::draw(Graphics::Surface *surface) {
	uint16 *image = ((LastExpressEngine *)g_engine)->getCursor()->getCursorImage((Cursor::CursorStyle)_style);
	if (!image)
		return Common::Rect();

	// TODO adjust brightness. The original game seems to be using a table for that (at least in the highlighting case)
	for (int j = 0; j < 32; j++) {
		uint16 *s = (uint16 *)surface->getBasePtr(_x, _y + j);
		for (int i = 0; i < 32; i++) {
			if (_brightness == 100)
				*s = *image;
			else
				// HACK change color to show highlight
				*s = (*image & 0x739C) >> 1;

			// Update the image and surface pointers
			image++;
			s++;
		}
	}

	return Common::Rect(_x, _y, _x + 32, _y + 32);
}

} // End of namespace LastExpress
