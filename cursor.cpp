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

#define MAX_CURSOR 48

namespace LastExpress {

Cursor::Cursor() : _current(CursorNormal), _data(NULL) {}

Cursor::~Cursor() {
	delete[] _data;
}

bool Cursor::load(Common::SeekableReadStream *stream) {
	if (!stream)
		return false;

	// Reset data
	delete[] _data;

	// Load cursor data
	_data = new byte[stream->size()];
	if (_data)
		stream->read(_data, stream->size());

	delete stream;

	return true;
}

void Cursor::show(bool visible) {
	CursorMan.showMouse(visible);
}

bool Cursor::setStyle(CursorStyle style) {
	if (!_data) {
		debugC(2, kLastExpressDebugGraphics, "Trying to set cursor style before loading data!");
		return false;
	}

	if ((int)style < 0 || (int)style > MAX_CURSOR - 1) {
		debugC(2, kLastExpressDebugGraphics, "Trying to set an invalid cursor style: was %d, max %d", (int)style, MAX_CURSOR);
		return false;
	}
	debugC(10, kLastExpressDebugCursor | kLastExpressDebugAll, "Cursor: setting style: %d", style);

	// Save the new cursor
	_current = style;

	// Prepare the pixel data
	uint16 pixels[32 * 32];
	byte *fileImage = _data + MAX_CURSOR * 4 + (style * 32 * 32 * 2);
	for(int i = 0; i < 32 * 32; i++, fileImage += 2) {
		pixels[i] = READ_LE_UINT16(fileImage);
		// TODO: transparency: now it makes the black pixels transparent,
		// but there's still 1 unused bit (always 0?)
		//pixels[i] = (READ_LE_UINT16(getStyleImage(style) + (i * 2)) & 0x8000) ? 0 : 0xffff;
		//pixels[i] = (fileImage[1] & 0x80) ? 0 : 0xffff;
	}

	uint16 hotspotX = READ_LE_UINT16(_data + (style * 4));
	uint16 hotspotY = READ_LE_UINT16(_data + (style * 4) + 2);
	debugC(15, kLastExpressDebugCursor | kLastExpressDebugAll, "    hotspot x: %d, hotspot y: %d", hotspotX, hotspotY);

	CursorMan.replaceCursor((const byte *)pixels, 32, 32, hotspotX, hotspotY, 0, 1, new Graphics::PixelFormat(2, 5, 5, 5, 0, 10, 5, 0, 0));

	return true;
}

Cursor::CursorStyle Cursor::getStyle() {
	return _current;
}

} // End of namespace LastExpress
