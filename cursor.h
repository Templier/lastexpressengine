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

#ifndef LASTEXPRESS_CURSOR_H
#define LASTEXPRESS_CURSOR_H

/*
	Cursor format (CURSORS.TBM)

	style table:
		(for each cursor)
		uint16 {2}       - hotspot X
		uint16 {2}	     - hotspot Y

	data:
		(for each cursor)
		uint16 {32*32}   - cursor data
*/

#include "common/system.h"

namespace LastExpress {

class Cursor {
public:
	enum CursorStyle {
		CursorNormal,
		CursorForward,
		CursorBackward,
		CursorTurnRight,
		CursorTurnLeft,
		CursorUp,
		CursorDown,
		CursorLeft,
		CursorRight,
		CursorHand,
		CursorHandKnock,
		CursorMagnifier,
		CursorHandPointer,
		CursorSleep,
		CursorTalk,
		CursorTalk2,		// Need better name
		CursorMatchBox,
		CursorLetter,
		CursorMessage,
		CursorArticle,
		CursorScarf,
		CursorPaper,		// Need better name
		CursorParchemin,	// Need better name
		CursorMatch,
		Cursorwhistle,
		CursorKey,
		CursorBomb,
		CursorFirebird,
		CursorBriefcase,
		CursorCorpse,
		CursorPunchLeft,
		CursorPunchRight,
		CursorPortraitYellow,
		CursorPortraitYellowSelected,
		CursorPortraitGreenVest,
		CursorPortraitGreenSelected,
		CursorPortrait,
		CursorPortraitSelected,
		CursorWait,
		CursorEggBlue,
		CursorEggRed,
		CursorEggGreen,
		CursorEggPurple,
		CursorEggTeal,
		CursorEggGold,
		CursorEggClock,
		CursorNormal2,
		CursorBlank
	};

	Cursor();
	~Cursor();

	bool load(Common::SeekableReadStream *stream);
	void show(bool visible);
	bool setStyle(CursorStyle style);
	CursorStyle getStyle();

	// TODO: Add function to draw a cursor to a surface, as they are also used for the inventory (top-right of the screen)
	//void draw(Surface* surface, int x, int y, CursorStyle style);

private:
	// Style
	CursorStyle _current;

	// Cursors data
	byte *_data;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_CURSOR_H
