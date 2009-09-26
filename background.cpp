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

Background::Background(ResourceManager *resource) : _resource(resource), _pixels(NULL), _size(0) {}

Background::~Background() {
	cleanup();
}

void Background::cleanup() {
	_size = 0;
	if (_pixels)
		free(_pixels);
}

// Ex: clock01.bg
bool Background::load(const Common::String &name)
{
	cleanup();

	// Get a stream for the background file
	if (!_resource->hasFile(name)) {
		debugC(2, kLastExpressDebugVideo, "Error opening background: %s", name.c_str());
		return false;
	}

	debugC(2, kLastExpressDebugVideo, "Loading background: %s", name.c_str());

	Common::SeekableReadStream *stream = _resource->createReadStreamForMember(name);
	
	// Load Background header
	_header.posX = stream->readUint32LE();
	_header.posY = stream->readUint32LE();
	_header.width = stream->readUint32LE();
	_header.height = stream->readUint32LE();
	_header.redSize = stream->readUint32LE();
	_header.blueSize = stream->readUint32LE();
	_header.greenSize = stream->readUint32LE();

	debugC(3, kLastExpressDebugVideo, "Background Info: (%d, %d) - (%d x %d) - (%d, %d, %d)", 
		   _header.posX, _header.posY, _header.width, _header.height, _header.redSize, _header.blueSize, _header.greenSize);

	// Load and decompress Background channel data
	byte *redData, *blueData, *greenData;
	byte *redBuffer, *blueBuffer, *greenBuffer;	// temporary buffer to hold decompressed data

	redData = (byte*)malloc(_header.redSize);
	blueData = (byte*)malloc(_header.blueSize);
	greenData = (byte*)malloc(_header.greenSize);

	uint32 bufferSize = sizeof(byte) * _header.width * _header.height;
	redBuffer = (byte*)malloc(bufferSize);
	blueBuffer = (byte*)malloc(bufferSize);
	greenBuffer = (byte*)malloc(bufferSize);

	// Read compressed data
	stream->read(redData, sizeof(byte) * _header.redSize);
	stream->read(blueData, sizeof(byte) * _header.blueSize);
	stream->read(greenData, sizeof(byte) * _header.greenSize);

	// Decompress the data
	decompress(redData, sizeof(byte) * _header.redSize, redBuffer, bufferSize);
	decompress(blueData, sizeof(byte) * _header.blueSize, blueBuffer, bufferSize);
	decompress(greenData, sizeof(byte) * _header.greenSize, greenBuffer, bufferSize);

	// Save to pixel buffer
	_size = sizeof(byte) * _header.width * _header.height * 3;
	_pixels = (byte*)malloc(_size);
	memset(_pixels, 0, _size);
	for (uint32 x = 0; x < _header.width - 1; ++x) {
		for (uint32 y = 0; y < _header.height - 1; ++y) {		
			int i = y * _header.width + x;

			_pixels[i] = redBuffer[i];
			_pixels[i+1] = greenBuffer[i];
			_pixels[i+2] = blueBuffer[i];
		}
	}

	free(redData);
	free(blueData);
	free(greenData);

	free(redBuffer);
	free(blueBuffer);
	free(greenBuffer);

	return true;
}

void Background::render(Graphics::Surface *surface) {
	if (!_pixels)
		return;

	Common::Rect rect(_header.posX, _header.posY, _header.width, _header.height);

	// Clear rect on surface
	surface->fillRect(rect, 0);

	// Copy background to surface
	memcpy(surface->getBasePtr(_header.posX, _header.posY), _pixels, _size);	
}

void Background::decompress(byte* src, uint32 srcSize, byte* dst, uint32 dstSize) {
	// Init destination buffer
	memset(dst, 0, dstSize);

	uint32 srcPos = 0;
	uint32 dstPos = 0;

	while (srcPos <= srcSize) {
		if (src[srcPos] < 0x80) {
			// direct decompression
			uint16 length = (src[srcPos] >> 5) + 1;
			char data = src[srcPos] << 3;

			++srcPos;

			for (uint32 i = 0; i < length; ++i)
			{
				if (dstPos > dstSize)
					return;

				dst[dstPos] = data;
				++dstPos;
			}
		} else {
			// buffer back reference, 4096 byte window			
			if (srcPos == srcSize)
				return;

			// Offset: src[srcPos] et src[srcPos+1] as a big endian uint16 (plus zeroing the first bit)
			//uint16 offset = (src[srcPos] << 8) + src[srcPos+1];
			//uint16 length = (offset >> 12) + 3;
			//uint32 position = dstPos - 4096 + (offset & 0x0fff); //((src[srcPos] & 0x0f) << 8) + src[srcPos + 1];
			uint16 length = ((src[srcPos] & 0x7f) >> 4) + 3;
			uint32 position = dstPos - 4096 + ((src[srcPos] & 0x0f) << 8) + src[srcPos + 1];

			srcPos = srcPos + 2;

			if (position < 0)
				return;

			for (uint32 i = position; i <= position + length - 1; ++i)
			{
				if ((dstPos > dstSize - 1) || (i > dstSize - 1))
					return;

				dst[dstPos] = dst[i];
				++dstPos;
			}
		}
	}
}

} // End of namespace LastExpress