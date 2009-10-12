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

// Based on the Xentax Wiki documentation:
// http://wiki.xentax.com/index.php/The_Last_Express_SBE

#include "lastexpress/subtitle.h"

#include "lastexpress/debug.h"
#include "lastexpress/font.h"
#include "lastexpress/helpers.h"

#include "common/debug.h"

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// Subtitle
//////////////////////////////////////////////////////////////////////////
Subtitle::Subtitle() : _timeStart(0), _timeStop(0),
	_topLength(0), _topText(NULL), _bottomLength(0), _bottomText(NULL) {
}

Subtitle::~Subtitle() {
	reset();
}

void Subtitle::reset() {
	SAFE_DELETE_ARRAY(_topText);
	SAFE_DELETE_ARRAY(_bottomText);
}

void Subtitle::show(Font &font) {	
	font.drawString(100, 100, _topText, _topLength);	
	font.drawString(100, 300, _bottomText, _bottomLength);
}

bool Subtitle::load(Common::SeekableReadStream *in) {
	reset();

	if (!in)
		return false;

	// Read the display times
	_timeStart = in->readUint16LE();
	_timeStop = in->readUint16LE();

	// Read the text lengths
	_topLength = in->readUint16LE();
	_bottomLength = in->readUint16LE();

	// Create the buffers
	if (_topLength) {
		_topText = new uint16[_topLength];		
		if (!_topText)
			return false;
	}
	if (_bottomLength) {
		_bottomText = new uint16[_bottomLength];		
		if (!_bottomText)
			return false;
	}

	// Read the texts
	for (int i = 0; i < _topLength; i++)
		_topText[i] = in->readUint16LE();
	for (int i = 0; i < _bottomLength; i++)
		_bottomText[i] = in->readUint16LE();

	debugC(9, kLastExpressDebugSubtitle, "  %d -> %d:", _timeStart, _timeStop);
	if (_topLength)
		debugC(9, kLastExpressDebugSubtitle, "\t%S", _topText);
	if (_bottomLength)
		debugC(9, kLastExpressDebugSubtitle, "\t%S", _bottomText);

	return true;
}

//////////////////////////////////////////////////////////////////////////
// SubtitleManager
//////////////////////////////////////////////////////////////////////////
SubtitleManager::SubtitleManager() {}

uint32 SubtitleManager::count() {
	return _subtitles.size();
}

bool SubtitleManager::load(Common::SeekableReadStream *stream) {
	if (!stream)
		return false;

	// Read header to get the number of subtitles
	uint32 numSubtitles = stream->readUint16LE();
	if (stream->eos()) {
		debugC(2, kLastExpressDebugSubtitle, "ERROR: Cannot read from subtitle file!");
		return false;
	}
	debugC(3, kLastExpressDebugSubtitle, "Number of subtitles in file: %d", numSubtitles);

	// TODO: Check that stream contain enough data
	//if (stream->size() < (signed)(numSubtitles * sizeof(SubtitleData))) {
	//	debugC(2, kLastExpressDebugSubtitle, "Subtitle file does not contain valid data!");
	//	return false;
	//}

	// Read the list of subtitles
	for (uint i = 0; i < numSubtitles; i++) {
		Subtitle subtitle;
		if (!subtitle.load(stream)) {
			// Failed to read this line
			_subtitles.clear();
			return false;
		}

		_subtitles.push_back(subtitle);
	}

	delete stream;

	return true;
}

bool SubtitleManager::show(Font &font, uint index) {
	if (index > _subtitles.size() - 1) {
		debugC(3, kLastExpressDebugSubtitle, "ERROR: invalid subtitle index (was: %d, max: %d)", index, _subtitles.size() - 1);
		return false;
	}

	_subtitles[index].show(font);

	return true;
}

} // End of namespace LastExpress
