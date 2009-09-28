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

	if (index > _headerSequence.numframes - 1)
		return;

	// TODO: Move stream to start of frame


	// Read frame header
	SequenceFrameHeader header;

	// Common frame information
	header.frameInfo.dataOffset = _stream->readUint32LE();
	header.frameInfo.unknown1 = _stream->readUint32LE();
	header.frameInfo.paletteOffset = _stream->readUint32LE();
	header.frameInfo.x0 = _stream->readUint32LE();
	header.frameInfo.unknown2 = _stream->readUint32LE();
	header.frameInfo.x1 = _stream->readUint32LE();
	header.frameInfo.unknown3 = _stream->readUint32LE();
	header.frameInfo.initialSkip = _stream->readUint32LE();
	header.frameInfo.decompressedEndOffset = _stream->readUint32LE();

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

	debugC(3, kLastExpressDebugVideo, "\n-- Frame information --  %d/%d", index + 1, _headerSequence.numframes);
	debugC(3, kLastExpressDebugVideo, "Offsets: data=%d, unknown=%d, Palette=%d", header.frameInfo.dataOffset, header.frameInfo.unknown1, header.frameInfo.paletteOffset);
	debugC(3, kLastExpressDebugVideo, "Position: x1=%d , unknown=%d, x2=%d , unknown=%d", header.frameInfo.x0, header.frameInfo.unknown2, header.frameInfo.x1, header.frameInfo.unknown3);
	debugC(3, kLastExpressDebugVideo, "Initial Skip: %d", header.frameInfo.initialSkip);
	debugC(3, kLastExpressDebugVideo, "Decompressed size: %d", header.frameInfo.decompressedEndOffset);
	debugC(3, kLastExpressDebugVideo, "Compression type: %u\n", header.compressionType);

	// Store palette information	
	byte *palette = (byte*)malloc(_maxPaletteSize * sizeof(byte));
	_stream->seek(header.frameInfo.paletteOffset, SEEK_SET);
	_stream->read(palette, _maxPaletteSize * sizeof(byte));

	// Init surface
	byte *output = (byte*)surface->getBasePtr(0, 0);
	memset(output, 0, _screenWidth * _screenHeigh * sizeof(byte) * 2);

	// Decompress frame
	switch (header.compressionType) {
		case 0x03:
			decompress_03(header, output, palette);
			break;	

		case 0x04:
			decompress_04(header, output, palette);
			break;	

		case 0x05:
			decompress_05(header, output, palette);
			break;	

		case 0x07:
			decompress_07(header, output, palette);
			break;

		case 0xff:
			decompress_ff(header, output, palette);
			break;				
	}

	free(palette);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decompress FrameType 03
void Animation::decompress_03(SequenceFrameHeader header, byte *output, byte *palette) {
	uint32 outIndex = 0;	

	// Number of columns to skip
	int numBlanks = (_screenWidth - 1) - (header.frameInfo.x1 - header.frameInfo.x0);

	// Go to frame data
	_stream->seek(header.frameInfo.dataOffset, SEEK_SET);
	outIndex = header.frameInfo.initialSkip;

	while (outIndex < header.frameInfo.decompressedEndOffset)
	{
		byte opcode = _stream->readByte();
		if (_stream->eos())
			return;

		if (opcode & 0x80) {

			if (opcode & 0x40) {

				opcode &= 0x3f;
				
				uint32 nextLine = 2 * (numBlanks + opcode);					

				output[outIndex] = palette[2];
				outIndex += nextLine + 2;

				output[outIndex] = palette[2]; 
				outIndex += 2;

				if (outIndex >= header.frameInfo.decompressedEndOffset)
					return;

			} else { //  (opcode & 0x40)

				opcode &= 0x3F;

				if (opcode & 0x20) {

					opcode = ((opcode & 0x1f) << 8) + _stream->readByte();
					if (_stream->eos())
						return;

					if (opcode & 0x1000) {
						outIndex += 2 * (opcode & 0xFFF);

						if (outIndex >= header.frameInfo.decompressedEndOffset)
							return;
					}
				} else {

					uint32 nextIndex = 2 * opcode;

					output[outIndex] = palette[2];
					outIndex += nextIndex + 2;

					output[outIndex] = palette[2];
					outIndex += 2;

					if (outIndex >= header.frameInfo.decompressedEndOffset)
						return;
				}
			}

		} else { //  (opcode & 0x80)

			if (opcode >> 3) {
				opcode = _stream->readByte();

				if (_stream->eos())
					return;
			}

			for (byte i = 0; i < opcode; i++) {
				output[outIndex] = palette[(opcode & 0x7) * 2];
				outIndex += 2;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decompress FrameType 04
void Animation::decompress_04(SequenceFrameHeader header, byte *output, byte *palette) {
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decompress FrameType 05
void Animation::decompress_05(SequenceFrameHeader header, byte *output, byte *palette) {
	uint32 outIndex = 0;





}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decompress FrameType 07
void Animation::decompress_07(SequenceFrameHeader header, byte *output, byte *palette) {
	uint32 outIndex = 0;	

	// Number of columns to skip
	int numBlanks = (_screenWidth - 1) - (header.frameInfo.x1 - header.frameInfo.x0);

	// Go to frame data
	_stream->seek(header.frameInfo.dataOffset, SEEK_SET);
	outIndex = header.frameInfo.initialSkip;

	while (outIndex < header.frameInfo.decompressedEndOffset)
	{
		byte opcode = _stream->readByte();
		if (_stream->eos())
			return;

		if (opcode & 0x80) {

			if (opcode & 0x40) {

				if (opcode & 0x20) {

					//byte value = opcode & 0x1f;
					opcode &= 0x1f;

					uint32 nextLine = 2 * (numBlanks + opcode);					

					output[outIndex] = palette[2];
					outIndex += nextLine + 2;

					output[outIndex] = palette[2]; 
					outIndex += 2;

					if (outIndex >= header.frameInfo.decompressedEndOffset)
						return;

				} else {  // (opcode & 0x40)

					//byte value = opcode & 0x1f;
					opcode &= 0x1f;

					if (opcode & 0x10) {

						opcode = ((opcode & 0x0f) << 8) + _stream->readByte();
						if (_stream->eos())
							return;

						if (opcode & 0x0800) {
							outIndex += 2 * (opcode & 0x7FF);

							if (outIndex >= header.frameInfo.decompressedEndOffset)
								return;
						}
					} else {

						uint32 nextIndex = 2 * opcode;

						output[outIndex] = palette[2];
						outIndex += nextIndex + 2;

						output[outIndex] = palette[2];
						outIndex += 2;

						if (outIndex >= header.frameInfo.decompressedEndOffset)
							return;
					}

				
				}

			} else { // (opcode & 0x40)

				output[outIndex] = palette[opcode * 2];
				outIndex += 2;

				if (outIndex >= header.frameInfo.decompressedEndOffset)
					return;
			}

		} else { // (opcode & 0x80)

			//byte numLoops = opcode & 0x3f;
			opcode &= 0x3f;

			byte value = _stream->readByte();
			if (_stream->eos())
				return;

			for (byte i = 0; i < opcode; i++) {
				if (outIndex >= header.frameInfo.decompressedEndOffset)
					return;

				output[outIndex] = palette[value * 2];
				outIndex += 2;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decompress FrameType FF
void Animation::decompress_ff(SequenceFrameHeader header, byte *output, byte *palette) {

}

} // End of namespace LastExpress