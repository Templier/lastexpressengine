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

#include "lastexpress/lastexpress.h"
#include "lastexpress/background.h"

namespace LastExpress {

Background::Background(ResourceManager *resource) : _resource(resource), _data(NULL) {}

Background::~Background() {
	cleanup();
}

void Background::cleanup() {
	SAFE_DELETE_ARRAY(_data);
}

// Ex: clock01.bg
bool Background::load(const Common::String &name) {
	cleanup();

	// Get a stream for the background file
	if (!_resource->hasFile(name)) {
		debugC(2, kLastExpressDebugGraphics, "Error opening background: %s", name.c_str());
		return false;
	}

	debugC(2, kLastExpressDebugGraphics, "=================================================================");
	debugC(2, kLastExpressDebugGraphics, "Loading background: %s", name.c_str());

	Common::SeekableReadStream *stream = _resource->createReadStreamForMember(name);
	
	// Load Background header
	_header.posX = stream->readUint32LE();
	_header.posY = stream->readUint32LE();
	_header.width = stream->readUint32LE();
	_header.height = stream->readUint32LE();
	_header.redSize = stream->readUint32LE();
	_header.blueSize = stream->readUint32LE();
	_header.greenSize = stream->readUint32LE();

	debugC(3, kLastExpressDebugGraphics, "Background Info: (%d, %d) - (%d x %d) - (%d, %d, %d)", 
		   _header.posX, _header.posY, _header.width, _header.height, _header.redSize, _header.blueSize, _header.greenSize);

	// Load and decompress Background channel data
	uint32 numPix = _header.width * _header.height;
	byte *dataR = decodeComponent(stream, _header.redSize, numPix);
	byte *dataB = decodeComponent(stream, _header.blueSize, numPix);
	byte *dataG = decodeComponent(stream, _header.greenSize, numPix);

	// Save to pixel buffer
	// FIXME handle big-endian case
	_data = new uint16[_header.width * _header.height];
	for (uint i = 0; i < _header.width * _header.height; i++)
		_data[i] = (dataR[i] << 10) + (dataG[i] << 5) + dataB[i];

	// Cleanup buffers
	delete[] dataR;
	delete[] dataG;
	delete[] dataB;

	return true;
}

bool Background::show() {
	if (!_data) {
		debugC(2, kLastExpressDebugGraphics, "Trying to show a background before loading data!");
		return false;
	}

	g_system->fillScreen(0);
	g_system->copyRectToScreen((byte *)_data, _header.width * 2, _header.posX, _header.posY, _header.width, _header.height);
	g_system->updateScreen();

	return true;
}

byte *Background::decodeComponent(Common::SeekableReadStream *in, uint32 inSize, uint32 outSize) {
	// Create the destination array
	byte *out = new byte[outSize];
	if (!out)
		return false;

	// Initialize the decoding
	uint32 inPos = 0;
	uint32 outPos = 0;

	// Decode
	while (inPos < inSize) {
		byte inByte = in->readByte();
		inPos++;

		if (inByte < 0x80) {
			// Direct decompression (RLE)
			byte len = (inByte >> 5) + 1;
			byte data = inByte & 0x1f;
			for (int i = 0; i < len && outPos < outSize; i++)
				out[outPos++] = data;
		} else {
			// Buffer back reference, 4096 byte window
			// Take inByte and the following value as a big endian
			// OfsLen while zeroing the first bit
			uint16 ofsLen = ((inByte & 0x7F) << 8) | in->readByte();
			inPos++;

			int32 len = (ofsLen >> 12) + 3;
			int32 hisPos = outPos + (ofsLen & 0x0FFF) - 4096;
			for (int i = 0; i < len && outPos < outSize; i++)
				out[outPos++] = out[hisPos++];
		}
	}

	return out;
}

} // End of namespace LastExpress