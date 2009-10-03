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

#ifndef LASTEXPRESS_FONT_H
#define LASTEXPRESS_FONT_H

#include "lastexpress/resource.h"

namespace LastExpress {

class ResourceManager;

class Font {
public:
	Font(ResourceManager *resource);
	~Font();

	bool load();
	void drawString(int x, int y, Common::String str);
	void drawString(int x, int y, uint16 *str, uint16 length);

private:	
	ResourceManager *_resource;

	uint16 getCharGlyph(uint16 c);
	byte *getGlyphImg(uint16 g);
	uint8 getGlyphWidth(uint16 g);
	byte *getCharImg(uint16 c);
	uint8 getCharWidth(uint16 c);
	uint16 getStringWidth(Common::String str);
	uint16 getStringWidth(uint16 *str, uint16 length);
	void drawChar(int x, int y, uint16 c);

	// Font data
	uint16 _palette[0x20];
	uint8 _charMap[0x200];
	uint16 _numGlyphs;
	byte *_glyphs;
	uint8 *_glyphWidths;
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_FONT_H