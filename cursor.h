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

//////////////////////////////////////////////////////////////////////
// Data file: CURSORS.TBM
//
//	-

namespace LastExpress {

class ResourceManager;

class Cursor {
public:
	Cursor(OSystem *system, ResourceManager *resource);
	~Cursor();

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
		CursorTalkZ,		// Need better name
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
		CursorStuff,		// Need better name
		CursorKey,
		CursorClock,
		CursorGold,			// Need better name
		CursorBriefcase,
		CursorCorpse,
		CursorClosedHandLeft,
		CursorClosedHandRight,
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

	bool load();
	void show(bool visible);
	bool setStyle(CursorStyle style);
	CursorStyle getStyle();

private:
	ResourceManager *_resource;
	OSystem *_system;

	// Style
	CursorStyle _current;

	// Cursors data
	byte *_data;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_CURSOR_H
