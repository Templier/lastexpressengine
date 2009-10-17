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
	delete[] _topText;
	delete[] _bottomText;
}

Common::Rect Subtitle::draw(Graphics::Surface *surface, Font *font) {	
	Common::Rect rectTop, rectBottom;
	
	//FIXME find out proper subtitles coordinates (and hope it's hardcoded and not stored in the sequence or animation)
	rectTop = font->drawString(surface, 100, 100, _topText, _topLength);	
	rectBottom = font->drawString(surface, 100, 300, _bottomText, _bottomLength);

	rectTop.extend(rectBottom);

	return rectTop;
}

template<typename T>
T* newArray(size_t n)
{
	if (n <= (size_t)-1 / sizeof(T))
		return new T[n];

	// n is too large
	return NULL;
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
		_topText = newArray<uint16>(_topLength);
		if (!_topText)
			return false;
	}
	if (_bottomLength) {
		_bottomText = newArray<uint16>(_bottomLength);
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
SubtitleManager::SubtitleManager(Font* font) : _font(font) {}

SubtitleManager::~SubtitleManager() {
	reset();	
}

uint32 SubtitleManager::count() {
	return _subtitles.size();
}

void SubtitleManager::reset() {
	for (uint i = 0; i < _subtitles.size(); i++)
		delete _subtitles[i];

	_subtitles.clear();
}

bool SubtitleManager::load(Common::SeekableReadStream *stream) {
	if (!stream)
		return false;

	reset();

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
		Subtitle *subtitle = new Subtitle();
		if (!subtitle->load(stream)) {
			// Failed to read this line
			reset();

			return false;
		}

		_subtitles.push_back(subtitle);
	}

	delete stream;

	return true;
}

Common::Rect SubtitleManager::draw(Graphics::Surface *surface, uint index){
	if (index > _subtitles.size() - 1) {
		debugC(3, kLastExpressDebugSubtitle, "ERROR: invalid subtitle index (was: %d, max: %d)", index, _subtitles.size() - 1);
		return Common::Rect();
	}

	return _subtitles[index]->draw(surface, _font);	
}

} // End of namespace LastExpress
