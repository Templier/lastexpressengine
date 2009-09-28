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
#include "lastexpress/animation.h"

namespace LastExpress {

Animation::Animation(ResourceManager *resource) : _resource(resource) {}

Animation::~Animation() {

}

uint32 Animation::getNumberOfFrames() {
	return _headerSequence.numframes;
}

bool Animation::loadAnimation(const Common::String &name) {
	return false;
}

bool Animation::loadSequence(const Common::String &name)
{
	// Get a stream to the file
	if (!_resource->hasFile(name)) {
		debugC(2, kLastExpressDebugVideo, "Error opening sequence: %s", name.c_str());
		return false;
	}

	debugC(2, kLastExpressDebugVideo, "Loading sequence: %s", name.c_str());

	_stream = _resource->createReadStreamForMember(name);

	// Read header to get the number of frames
	_headerSequence.numframes = _stream->readUint32LE();
	_headerSequence.unknown = _stream->readUint32LE();
	debugC(3, kLastExpressDebugVideo, "Number of frames in sequence: %d", _headerSequence.numframes);

	return true;
}

void Animation::renderFrame(Graphics::Surface *surface, uint32 index) {

	// Read frame header
	SequenceFrameHeader header;

	// Common frame information
	header.frameInfo.dataOffset = _stream->readUint32LE();
	header.frameInfo.unknown1 = _stream->readUint32LE();
	header.frameInfo.paletteOffset = _stream->readUint32LE();
	header.frameInfo.xPos1 = _stream->readUint32LE();
	header.frameInfo.unknown2 = _stream->readUint32LE();
	header.frameInfo.xPos2 = _stream->readUint32LE();
	header.frameInfo.unknown3 = _stream->readUint32LE();
	header.frameInfo.initialSkip = _stream->readUint32LE();
	header.frameInfo.decompressedSize = _stream->readUint32LE();

	// Sequence information
	header.unknown4 = _stream->readUint32LE();
	header.unknown5 = _stream->readUint32LE();
	header.compressionType = _stream->readByte();
	header.unknown7 = _stream->readByte();
	header.unknown8 = _stream->readByte();
	header.unknown9 = _stream->readByte();
	header.unknown10 = _stream->readUint32LE();
	header.unknown11 = _stream->readUint32LE();
	header.unknown12 = _stream->readUint32LE();
	header.unknown13 = _stream->readUint32LE();
	header.unknown14 = _stream->readUint32LE();

	debugC(3, kLastExpressDebugVideo, "-- Frame information --  %d/%d", index + 1, _headerSequence.numframes);
	debugC(3, kLastExpressDebugVideo, "Offsets: data=%d, unknown=%d, Palette=%d", header.frameInfo.dataOffset, header.frameInfo.unknown1, header.frameInfo.paletteOffset);
	debugC(3, kLastExpressDebugVideo, "Position: x1=%d , unknown=%d, x2=%d , unknown=%d", header.frameInfo.xPos1, header.frameInfo.unknown2, header.frameInfo.xPos2, header.frameInfo.unknown3);
	debugC(3, kLastExpressDebugVideo, "Initial Skip: %d", header.frameInfo.initialSkip);
	debugC(3, kLastExpressDebugVideo, "Decompressed size: %d", header.frameInfo.decompressedSize);
	debugC(3, kLastExpressDebugVideo, "Compression type: %u", header.compressionType);

	// Store palette information
	uint32 paletteSize = (header.frameInfo.dataOffset - header.frameInfo.paletteOffset) * sizeof(byte);
	byte *palette = (byte*)malloc(paletteSize);
	_stream->seek(sizeof(SequenceHeader) + header.frameInfo.paletteOffset, SEEK_SET);
	_stream->read(palette, paletteSize);

	// Decompress frame
	bool isOk = false;
	switch (header.compressionType) {
		case 0x03:
		case 0x04:
		case 0x05:
			break;

		case 0x07:
			isOk = decompress_07(header, (byte*)surface->getBasePtr(0, 0), palette);
			break;

		case 0xff:
			break;				
	}

	if (!isOk)
		debugC(3, kLastExpressDebugVideo, "Error decompressing frame!");

	free(palette);
}

bool Animation::decompress_07(SequenceFrameHeader header, byte *output, byte *palette) {

	memset(output, 255, _screenWidth * _screenHeigh * sizeof(byte) * 2);

	uint32 outIndex = 0;	

	// default number of columns to skip
	uint32 numBlanks = (_screenWidth - 1) - (header.frameInfo.xPos2 - header.frameInfo.xPos1);

	// Go to frame data
	_stream->seek(sizeof(SequenceHeader) + header.frameInfo.dataOffset, SEEK_SET);
	outIndex = header.frameInfo.initialSkip;

	while (outIndex < header.frameInfo.decompressedSize)
	{
		byte opcode = _stream->readByte();
		if (_stream->eos())
			return false;

		if (opcode & 0x80) {

			if (opcode & 0x40) {

				if (opcode & 0x20) {

					byte value = opcode & 0x1f;
					byte nextLine = 2 * (numBlanks + value);					

					output[outIndex] = palette[2];
					outIndex += nextLine + 2;

					output[outIndex] = palette[2]; 
					outIndex += 2;

					if (outIndex >= header.frameInfo.decompressedSize)
						return false;

				} else {  // (opcode & 0x40)

					byte value = opcode & 0x1f;

					if (opcode & 0x10) {

						opcode = ((opcode & 0x0f) << 8) + _stream->readByte();
						if (_stream->eos())
							return false;

						if (opcode & 0x0800) {
							outIndex += 2 * (opcode & 0x7FF);

							if (outIndex >= header.frameInfo.decompressedSize)
								return false;
						}
					} else {

						byte nextIndex = 2 * opcode;

						output[outIndex] = palette[2];
						outIndex += nextIndex + 2;

						output[outIndex] = palette[2];
						outIndex += 2;

						if (outIndex >= header.frameInfo.decompressedSize)
							return false;
					}

				
				}

			} else { // (opcode & 0x40)

				byte numLoops = opcode & 0x3f;

				byte value = _stream->readByte();
				if (_stream->eos())
					return false;

				for (byte i = 0; i < numLoops; i++) {
					if (outIndex >= header.frameInfo.decompressedSize)
						return false;

					output[outIndex] = palette[value * 2];
					outIndex += 2;
				}

			}

		} else { // (opcode & 0x80)

			output[outIndex] = palette[opcode * 2];
			outIndex += 2;

			if (outIndex >= header.frameInfo.decompressedSize)
				return false;
		}
	}

	return true;
}

} // End of namespace LastExpress