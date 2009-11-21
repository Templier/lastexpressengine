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
		uint16 {2}       - hotspot Y

	data:
		(for each cursor)
		uint16 {32*32}   - cursor data
*/

#include "lastexpress/drawable.h"

#include "common/stream.h"

namespace LastExpress {

class Cursor {
public:
	enum CursorStyle {
		kCursorNormal,
		kCursorForward,
		kCursorBackward,
		kCursorTurnRight,
		kCursorTurnLeft,
		kCursorUp,
		kCursorDown,
		kCursorLeft,
		kCursorRight,
		kCursorHand,
		kCursorHandKnock, // 10
		kCursorMagnifier,
		kCursorHandPointer,
		kCursorSleep,
		kCursorTalk,
		kCursorTalk2,     // Need better name

		// Items
		kCursorMatchBox,
		kCursorTelegram,
		kCursorPassengerList,
		kCursorArticle,
		kCursorScarf,     // 20
		kCursorPaper,
		kCursorParchemin,
		kCursorMatch,
		kCursorWhistle,
		kCursorKey,
		kCursorBomb,
		kCursorFirebird,
		kCursorBriefcase,
		kCursorCorpse,

		// Combat
		kCursorPunchLeft, // 30
		kCursorPunchRight,

		// Portraits
		kCursorPortrait,
		kCursorPortraitSelected,
		kCursorPortraitGreen,
		kCursorPortraitGreenSelected,
		kCursorPortraitYellow,
		kCursorPortraitYellowSelected,
		kCursorHourGlass,
		kCursorEggBlue,
		kCursorEggRed,    // 40
		kCursorEggGreen,
		kCursorEggPurple,
		kCursorEggTeal,
		kCursorEggGold,
		kCursorEggClock,
		kCursorNormal2,
		kCursorBlank,
		kCursorMAX,

		// Special
		kCursorKeepValue = 255
	};

	Cursor();

	bool load(Common::SeekableReadStream *stream);
	void show(bool visible);
	bool setStyle(CursorStyle style);
	uint16 *getCursorImage(CursorStyle style);

private:
	// Style
	CursorStyle _current;

	// Cursors data
	struct {
		uint16 image[32 * 32];
		uint16 hotspotX, hotspotY;
	} _cursors[kCursorMAX];

	bool checkStyle(CursorStyle style);
};

class Icon : public Drawable {
public:
	Icon(Cursor::CursorStyle style);

	void setPosition(int x, int y);
	void setBrightness(uint8 brightness);
	Common::Rect draw(Graphics::Surface *surface);

private:
	Cursor::CursorStyle _style;
	int _x, _y;
	uint8 _brightness;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_CURSOR_H
