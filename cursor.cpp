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

#include "lastexpress/debug.h"

#include "graphics/cursorman.h"

namespace LastExpress {

Cursor::Cursor() : _current(kCursorNormal) {}

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

	CursorMan.replaceCursor((const byte *)getCursorImage(_current), 32, 32,
		_cursors[_current].hotspotX, _cursors[_current].hotspotY, 0, 1,
		new Graphics::PixelFormat(2, 5, 5, 5, 0, 10, 5, 0, 0));

	return true;
}

uint16 *Cursor::getCursorImage(CursorStyle style) {
	if (!checkStyle(style))
		return NULL;
	return _cursors[style].image;
}

// Draw a cursor to a surface, as they are also used for the inventory (top-right of the screen)
Common::Rect Cursor::draw(Graphics::Surface *surface, int x, int y, uint style) {
	uint16 *image = getCursorImage((CursorStyle)style);
	if (!image)
		return Common::Rect();

	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 32; i++) {
			surface->fillRect(Common::Rect(x + i, y + j, x + i + 1, y + j + 1), *image);
			image++;
		}
	}

	return Common::Rect(x, y, x+32, y+32);
}

} // End of namespace LastExpress
