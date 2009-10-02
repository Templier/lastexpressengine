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

Animation::Animation(LastExpressEngine *engine) : _engine(engine), _stream(NULL), _currentFrame(0) {}

void Animation::cleanup() {
	_stream = NULL;
	_currentFrame = 0;
	_headerSequence.numframes = 0;
	_headerSequence.unknown = 0;
	_chunks.clear();
}

uint32 Animation::currentFrame() {
	return _currentFrame;
}

uint32 Animation::totalFrames() {
	if (_stream == NULL)
		return 0;

	return _headerSequence.numframes;
}

/////////////////////////////////////////////////////////////////////
//		ANIMATIONS
/////////////////////////////////////////////////////////////////////
bool Animation::loadAnimation(const Common::String &name) {
	cleanup();

	// Get a stream to the file
	if (!_engine->_resources->hasFile(name)) {
		debugC(2, kLastExpressDebugVideo, "Error opening animation: %s", name.c_str());		
		return false;
	}

	debugC(2, kLastExpressDebugVideo, "Loading animation: %s", name.c_str());
	_stream = _engine->_resources->createReadStreamForMember(name);

	// FIXME Add error handling
	
	// Read header to get the number of chunks
	uint32 numChunks = _stream->readUint32LE();
	debugC(3, kLastExpressDebugVideo, "Number of chunks in NIS file: %d", numChunks);

	// Read all the chunks
	for (uint32 i = 0; i < numChunks; ++i) {		
		
		AnimationChunk chunk;

		chunk.type = (typesChunk)_stream->readUint16LE();
		chunk.tag  = _stream->readUint16LE();
		chunk.size = _stream->readUint32LE();

		_chunks.push_back(chunk);

		//debugC(9, kLastExpressDebugVideo, "Chunk Entry: type 0x%.4x, tag=%d, size=%d", chunk.type, chunk.tag, chunk.size);		
	}

	return true;
}

bool Animation::play() {
	
	if (_stream == NULL || _chunks.size() == 0) {
		debugC(2, kLastExpressDebugVideo, "No animation has been loaded!");
		return false;
	}

	uint32 frameNumber = 0;

	// Process each chunk
	for (Common::Array<AnimationChunk>::iterator it = _chunks.begin(); it != _chunks.end(); ++it) {

		switch(it->type) {
		case kChunkTypeAudioInfo:
			debugC(9, kLastExpressDebugVideo, "  audio info: %d blocks, tag %d", it->size, it->tag);
			break;

		case kChunkTypeBackgroundFrameA:
			debugC(9, kLastExpressDebugVideo, "  frame A (background type 0x%.4x, %d bytes, tag %d)", it->type, it->size, it->tag);			
			renderBackground(it);
			break;
			
  		case kChunkTypeSelectBackgroundA:
			debugC(9, kLastExpressDebugVideo, "  frame info: select background A");
			break;

  		case kChunkTypeBackgroundFrameC:
			debugC(9, kLastExpressDebugVideo, "  frame C (background type 0x%.4x, %d bytes, tag %d)", it->type, it->size, it->tag);
			renderBackground(it);			
			break;

  		case kChunkTypeSelectBackgroundC:
			debugC(9, kLastExpressDebugVideo, "  frame info: select background C");
			break;

  		case kChunkTypeOverlayFrame:
			debugC(9, kLastExpressDebugVideo, "  frame #%.4d (overlay, %d bytes, tag %d)", frameNumber, it->size, it->tag);
			// TODO seek to data & decode frame
			renderBackground(it);
			frameNumber++;
			break;

  		case kChunkTypeAudioData:
			debugC(9, kLastExpressDebugVideo, "  audio (%d blocks, %d bytes, tag %d)", it->size/_soundBlockSize, it->size, it->tag);
			// TODO add to sound buffer
			_stream->seek(it->size, SEEK_CUR);
			break;

  		case kChunkTypeAudioEnd:
			debugC(9, kLastExpressDebugVideo, "  audio end: %d blocks", it->tag);
			break;

		// TODO: some info chunks are probably subtitle related
		default:
			debugC(9, kLastExpressDebugVideo, "  unknown chunk: type 0x%.4x (size %d, tag %d)", it->type, it->size, it->tag);
			break;
		}

		_engine->_system->delayMillis(250);

	}



	return true;
}

void Animation::renderBackground(AnimationChunk *chunk) {
	int startPosition = _stream->pos();
	Common::SeekableSubReadStream substream(_stream, _stream->pos(), _stream->pos() + chunk->size, false);

	// Get compression type
	substream.seek(0x0124, SEEK_SET);
	byte compressionType = substream.readByte();
	substream.seek(0, SEEK_SET);

	// Load chunk header
	FrameHeader header;
	loadFrameHeader(&substream, &header);
	debugC(3, kLastExpressDebugVideo, "    Compression type: %d", compressionType);

	switch (chunk->type) {
	case kChunkTypeBackgroundFrameA:
		renderFrameInternal(&_engine->_graphics->_backgroundA, &substream, &header, compressionType); 
		break;
	case kChunkTypeBackgroundFrameC:
		renderFrameInternal(&_engine->_graphics->_backgroundC, &substream, &header, compressionType); 
		break;
	case kChunkTypeOverlayFrame:
		renderFrameInternal(&_engine->_graphics->_overlay, &substream, &header, compressionType); 
		break;
	}

	_engine->_graphics->MergePlanes();
	_engine->_graphics->updateScreen(&_engine->_graphics->_overlay);
	_engine->_graphics->update();

	_stream->seek(startPosition + chunk->size, SEEK_SET);
}

/////////////////////////////////////////////////////////////////////
//		SEQUENCES
/////////////////////////////////////////////////////////////////////
bool Animation::loadSequence(const Common::String &name) {
	cleanup();

	// Get a stream to the file
	if (!_engine->_resources->hasFile(name)) {
		debugC(2, kLastExpressDebugVideo, "Error opening sequence: %s", name.c_str());
		return false;
	}

	debugC(2, kLastExpressDebugVideo, "Loading sequence: %s", name.c_str());
	_stream = _engine->_resources->createReadStreamForMember(name);

	// FIXME Add error handling

	// Reset current frame
	_currentFrame = 0;

	// Read header to get the number of frames
	_headerSequence.numframes = _stream->readUint32LE();
	_headerSequence.unknown = _stream->readUint32LE();
	debugC(3, kLastExpressDebugVideo, "Number of frames in sequence: %d", _headerSequence.numframes);

#ifdef _DEBUG
	// Show all frames information
	for (uint32 i = 0; i < _headerSequence.numframes; i++) {
		SequenceFrameHeader header;
		loadSequenceFrameHeader(&header, i);
	}
#endif

	return true;
}

// Render a single frame to the surface
// return false to know that no more frames need to be rendered?
bool Animation::renderFrame(uint32 index) {

	if (_stream == NULL || _headerSequence.numframes == 0) {
		debugC(2, kLastExpressDebugVideo, "No sequence has been loaded!");
		return false;
	}

	_currentFrame = index;

	// Check if there are remaining frames to render
	if (_currentFrame > _headerSequence.numframes - 1)
		return false;

	// FIXME: Add error handling

	// Read frame header
	SequenceFrameHeader header;
	if (!loadSequenceFrameHeader(&header, index))
		return false;

	// Check that we have a valid frame
	if (header.compressionType == 0)
		return true;

	return renderFrameInternal(&_engine->_graphics->_overlay, _stream, &(header.frameInfo), header.compressionType);
}

bool Animation::renderFrameInternal(Graphics::Surface *surface, Common::SeekableReadStream *stream, FrameHeader *header, byte compressionType)
{
	// Store palette information	
	uint16 *palette = (uint16*)malloc(_maxPaletteSize);
	stream->seek(header->paletteOffset, SEEK_SET);
	stream->read(palette, _maxPaletteSize);

	// Init surface
	byte *output = (byte*)surface->getBasePtr(0, 0);

	// FIXME: don't do that, and only update portion of screen with image data
	// at this time, we use a special color as the transparent one, but this is crappy
	// also doesn't support dirty rectangles, although it would be nice to have	
	memset(output, 255, _screenWidth * _screenHeight * 2);

	// TODO: add switch to show full sprite or "transition"
	// TODO: would be nice to have a "semi-transparent" sprite instead of checkboarded one (as an engine option?)

	// Decompress frame
	switch (compressionType) {
		case 0x03:
			decompress_03(stream, header, output, palette);
			break;	

		case 0x04:
			decompress_04(stream, header, output, palette);
			break;	

		case 0x05:
			decompress_05(stream, header, output, palette);
			break;	

		case 0x07:
			decompress_07(stream, header, output, palette);
			break;

		case 0xff:
			decompress_ff(stream, header, output, palette);
			break;				
	}

	free(palette);

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Load the header for a sequence frame
bool Animation::loadSequenceFrameHeader(SequenceFrameHeader *header, uint32 index) {

	// Move stream to start of frame
	_stream->seek(sizeof(SequenceHeader) + index * _sequenceFrameSize);
	if (_stream->eos()) {
		debugC(2, kLastExpressDebugVideo, "Error seeking to current frame data!");
		return false;
	}

	// Check if there is enough data
	if (_stream->size() - _stream->pos() < sizeof(SequenceFrameHeader)) {
		debugC(2, kLastExpressDebugVideo, "The frame does not have a valid header!");
		return false;
	}

	debugC(3, kLastExpressDebugVideo, "\n-- Frame information --  %d/%d", index + 1, _headerSequence.numframes);

	// Common frame information
	loadFrameHeader(_stream, &header->frameInfo);
	
	// Sequence information
	header->unknown4 = _stream->readUint32LE();
	header->unknown5 = _stream->readUint32LE();
	header->compressionType = _stream->readByte();
	header->unknown7 = _stream->readByte();
	header->unknown8 = _stream->readByte();
	header->unknown9 = _stream->readByte();
	header->unknown10 = _stream->readUint32LE();
	header->unknown11 = _stream->readUint32LE();
	header->unknown12 = _stream->readUint32LE();
	header->unknown13 = _stream->readUint32LE();
	header->unknown14 = _stream->readUint32LE();
	
	debugC(3, kLastExpressDebugVideo, "    Compression type: %u\n", header->compressionType);

	return true;
}

void Animation::loadFrameHeader(Common::SeekableReadStream *stream, FrameHeader *header) {
	header->dataOffset = stream->readUint32LE();
	header->unknown1 = stream->readUint32LE();
	header->paletteOffset = stream->readUint32LE();
	header->x0 = stream->readUint32LE();
	header->y0 = stream->readUint32LE();
	header->x1 = stream->readUint32LE();
	header->y1 = stream->readUint32LE();
	header->initialSkip = stream->readUint32LE();
	header->decompressedEndOffset = stream->readUint32LE();

	debugC(3, kLastExpressDebugVideo, "    Offsets: data=%d, unknown=%d, palette=%d", header->dataOffset, header->unknown1, header->paletteOffset);
	debugC(3, kLastExpressDebugVideo, "    Position: (%d, %d) - (%d, %d)", header->x0, header->y0, header->x1, header->y1);
	debugC(3, kLastExpressDebugVideo, "    Initial Skip: %d", header->initialSkip);
	debugC(3, kLastExpressDebugVideo, "    Decompressed end offset: %d", header->decompressedEndOffset);
}

// Set a pixel value using the palette
void Animation::setPixel(byte *pixel, uint32 index, byte value, uint16 *palette) {
	
	#define RGB565(r, g, b) ((b >> 3) + ((g >> 2) << 5) + ((r >> 3) << 11))

	uint16 blue  = (palette[value] & 0x1F) << 3;
	uint16 green = ((palette[value] >> 5) & 0x1F) << 3;
	uint16 red   = ((palette[value] >> 10) & 0x1F) << 3;

	uint16 color = RGB565(red, green, blue);

	pixel[index] = color & 0xFF;
	pixel[index + 1] = (color >> 8) & 0xFF;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decompress FrameType 03
void Animation::decompress_03(Common::SeekableReadStream *stream, FrameHeader *header, byte *output, uint16 *palette) {
	uint32 outIndex = 0;	

	// Number of columns to skip
	int numBlanks = (_screenWidth * 2 - 1) - (header->x1 - header->x0);

	// Go to frame data
	stream->seek(header->dataOffset, SEEK_SET);
	outIndex = (header->initialSkip >> 1) * 2;

	byte parity = (outIndex / (_screenWidth * 2) ) & 0x01; 

	while (outIndex < (header->decompressedEndOffset >> 1) * 2)
	{
		byte opcode = stream->readByte();
		if (_stream->eos())
			return;

		if (opcode & 0x80) {

			if (opcode & 0x40) {

				opcode &= 0x3f;

				if ((outIndex & 0x01) != parity) {
					setPixel(output, outIndex, 1, palette);
				}

				outIndex += (numBlanks + opcode + 1) * 2;

				parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

				if ((outIndex & 0x01) != parity) {
					setPixel(output, outIndex, 254, palette);
				}

				outIndex += 2;

			} else { //  (opcode & 0x40)

				opcode &= 0x3F;

				if (opcode & 0x20) {

					opcode = ((opcode & 0x1f) << 8) + stream->readByte();
					if (_stream->eos())
						return;

					if (opcode & 0x1000) {
						outIndex += (opcode & 0x0FFF) * 2;

						parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

						continue;
					}
				} else { // (opcode & 0x20)

					if ((outIndex & 0x01) != parity) {
						setPixel(output, outIndex, 1, palette);
					}

					outIndex += (opcode + 1) * 2;
					parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

					if ((outIndex & 0x01) != parity) {
						setPixel(output, outIndex, 254, palette);
					}

					outIndex += 2;
				}
			}
		} else { //  (opcode & 0x80)

			byte value = opcode & 0x07;
			opcode = opcode >> 3;

			if (opcode == 0) {
				opcode = stream->readByte();
				if (_stream->eos())
					return;
			}

			if ((outIndex & 0x01) == parity) {
				setPixel(output, outIndex, value, palette);

				outIndex += 2;
				opcode--;

				if (opcode == 0)
					continue;
			}

			for (uint32 i = 0; i < (unsigned)(opcode >> 1); i++) {
				setPixel(output, outIndex, value, palette);
				setPixel(output, outIndex + 2, value, palette);
				outIndex += 4;
			}

			if ((opcode & 0x01) != 0) {
				setPixel(output, outIndex, value, palette);
				outIndex += 2;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decompress FrameType 04
void Animation::decompress_04(Common::SeekableReadStream *stream, FrameHeader *header, byte *output, uint16 *palette) {
	// Number of columns to skip
	int numBlanks = (_screenWidth - 1) - (header->x1 - header->x0);

	// Go to frame data
	stream->seek(header->dataOffset, SEEK_SET);

	uint32 outIndex = (header->initialSkip >> 1) * 2;
	byte parity = (outIndex / (_screenWidth * 2) ) & 0x01; 

	while (outIndex < (header->decompressedEndOffset >> 1) * 2)
	{
		byte opcode = stream->readByte();
		if (stream->eos())
			return;

		if (opcode & 0x80) {

			if (opcode & 0x40) {

				opcode &= 0x3f;

				if ((outIndex & 0x01) != parity) {
					setPixel(output, outIndex, 1, palette);
				}

				outIndex += (numBlanks + opcode + 1) * 2;

				parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

				if ((outIndex & 0x01) != parity) {
					setPixel(output, outIndex, 254, palette);
				}

				outIndex += 2;

			} else { //  (opcode & 0x40)

				opcode &= 0x3F;

				if (opcode & 0x20) {

					opcode = ((opcode & 0x1f) << 8) + stream->readByte();
					if (stream->eos())
						return;

					if (opcode & 0x1000) {
						outIndex += (opcode & 0x0FFF) * 2;

						parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

						continue;
					}
				} else { // (opcode & 0x20)

					if ((outIndex & 0x01) != parity) {
						setPixel(output, outIndex, 1, palette);
					}

					outIndex += (opcode + 1) * 2;
					parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

					if ((outIndex & 0x01) != parity) {
						setPixel(output, outIndex, 254, palette);
					}

					outIndex += 2;
				}
			}
		} else { //  (opcode & 0x80)

			byte value = opcode & 0x0F;
			opcode = opcode >> 4;

			if (opcode == 0) {
				opcode = stream->readByte();
				if (stream->eos())
					return;
			}

			if ((outIndex & 0x01) == parity) {
				setPixel(output, outIndex, value, palette);

				outIndex += 2;
				opcode--;

				if (opcode == 0)
					continue;
			}

			for (uint32 i = 0; i < (unsigned)(opcode >> 1); i++) {
				setPixel(output, outIndex, value, palette);
				setPixel(output, outIndex + 2, value, palette);
				outIndex += 4;
			}

			if ((opcode & 0x01) != 0) {
				setPixel(output, outIndex, value, palette);
				outIndex += 2;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decompress FrameType 05
void Animation::decompress_05(Common::SeekableReadStream *stream, FrameHeader *header, byte *output, uint16 *palette) {

	// Go to frame data
	stream->seek(header->dataOffset, SEEK_SET);
	uint32 outIndex = (header->initialSkip >> 1) * 2;

	// Parity
	byte parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

	while (outIndex < (header->decompressedEndOffset >> 1) * 2)
	{
		uint32 opcode = stream->readByte();
		if (stream->eos())
			return;

		if ((opcode & 0x1F) == 0) {

			opcode = (opcode << 3 ) + stream->readByte();
			if (stream->eos())
				return;

			if ((opcode & 0x0400) != 0) {
				outIndex += (opcode & 0x03FF) * 2;

				parity = (outIndex / (_screenWidth * 2) ) & 0x01;  
			} else {

				if ((outIndex & 0x01) != parity) {
					setPixel(output, outIndex, 1, palette);
				}

				outIndex += (opcode + 1) * 2;

				parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

				if ((outIndex & 0x01) != parity) {
					setPixel(output, outIndex, 254, palette);
				}

				outIndex += 2;
			}

		} else { // (opcode & 0x1f)

			byte value = opcode & 0x1F;					
			opcode = (opcode >> 5);

			if (opcode == 0) {
				opcode = stream->readByte();
				if (stream->eos())
					return;
			}

			if ((outIndex & 0x01) == parity) {
				setPixel(output, outIndex, value, palette);

				outIndex += 2;
				opcode--;

				if (opcode == 0)
					continue;
			}
			
			for (uint32 i = 0; i < (opcode >> 1); i++) {
				setPixel(output, outIndex, value, palette);
				setPixel(output, outIndex + 2, value, palette);
				outIndex += 4;
			}

			if ((opcode & 0x01) != 0) {
				setPixel(output, outIndex, value, palette);
				outIndex += 2;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decompress FrameType 07
void Animation::decompress_07(Common::SeekableReadStream *stream, FrameHeader *header, byte *output, uint16 *palette) {

	// Number of columns to skip
	uint32 numBlanks = (_screenWidth - 1) - (header->x1 - header->x0);

	// Go to frame data
	stream->seek(header->dataOffset, SEEK_SET);	

	uint32 outIndex = (header->initialSkip >> 1) * 2;
	byte parity = (outIndex / (_screenWidth * 2) ) & 0x01; 

	while (outIndex < (header->decompressedEndOffset >> 1) * 2)
	{
		uint32 opcode = stream->readByte();
		if (stream->eos())
			return;

		if (opcode & 0x80) {

			if (opcode & 0x40) {

				if (opcode & 0x20) {

					opcode &= 0x1F;

					if ((outIndex & 0x01) != parity) {
						setPixel(output, outIndex, 1, palette);
					}

					outIndex += (numBlanks + opcode + 1) * 2;

					parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

					if ((outIndex & 0x01) != parity) {
						setPixel(output, outIndex, 254, palette);
					}

					outIndex += 2;

				} else {  // (opcode & 0x20)

					opcode &= 0x1F;

					if (opcode & 0x10) {

						opcode = ((opcode & 0x0F) << 8) + stream->readByte();
						if (stream->eos())
							return;

						if (opcode & 0x0800) {
							outIndex += (opcode & 0x07FF) * 2;
							parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

							continue;
						}
					}

					if ((outIndex & 0x01) != parity) {
						setPixel(output, outIndex, 1, palette);
					}

					outIndex += (opcode + 1) * 2;

					parity = (outIndex / (_screenWidth * 2) ) & 0x01;  

					if ((outIndex & 0x01) != parity) {
						setPixel(output, outIndex, 254, palette);
					}

					outIndex += 2;
				}

			} else { // (opcode & 0x40)

				opcode &= 0x3F;
				byte value = stream->readByte();
				if (stream->eos())
					return;
			
				if ((outIndex & 0x01) == parity) {
					setPixel(output, outIndex, value, palette);

					outIndex += 2;
					opcode--;

					if (opcode == 0)
						continue;
				}
				
				for (uint32 i = 0; i < (unsigned)(opcode >> 1); i++) {
					setPixel(output, outIndex, value, palette);
					setPixel(output, outIndex + 2, value, palette);
					outIndex += 4;
				}

				if ((opcode & 0x01) != 0) {
					setPixel(output, outIndex, value, palette);
					outIndex += 2;
				}
			}

		} else { // (opcode & 0x80)
			if ((outIndex & 0x01) != parity) {
				setPixel(output, outIndex, opcode, palette);
			}

			outIndex += 2;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decompress FrameType FF
void Animation::decompress_ff(Common::SeekableReadStream *stream, FrameHeader *header, byte *output, uint16 *palette) {

	// Go to frame data
	stream->seek(header->dataOffset, SEEK_SET);	

	uint32 outIndex = 0;
	uint32 screenSize = _screenWidth * _screenHeight * 2;
	
	while (outIndex < screenSize) {

		uint16 opcode = stream->readUint16LE();
		if (stream->eos())
			return;

		if ((opcode & 0x00FF) < 0x80) {
			// Backtrack on byte
			stream->seek(-1, SEEK_CUR);

			byte value = (opcode & 0x00FF);

			if (outIndex > screenSize - 1)
				return;

			setPixel(output, outIndex, value, palette);
			outIndex += 2;
		} else {
			// No backtrack here

			if ((opcode & 0x00FF) < 0xF0) {

				if ((opcode & 0x00FF) < 0xE0) {
					uint32 pos = outIndex + ((((opcode & 0x0007) >> 8) | (opcode >> 8)) - 2048) * 2; 
					uint32 len = ((opcode & 0x0078) >> 3) + 3;

					if ((pos + len > screenSize) || (outIndex + len > screenSize)) 
						return;

					for (uint32 i = 0; i < (len * 2); i++) {
						output[outIndex] = output[pos];
					}

				} else { // (opcode & 0x00FF) < 0xE0
					byte value = (opcode >> 8);
					uint32 len = (opcode & 0x0F) + 1;

					if (outIndex + len > screenSize)
						return;

					for (uint32 i = 0; i < len; i++) {
						setPixel(output, outIndex, value, palette);
						outIndex += 2;
					}
				}
			} else { // (opcode & 0x00FF) < 0xF0
				outIndex += ((((opcode & 0x00FF) << 8) | (opcode >> 8)) & 0x0FFF) * 2;
			}
		}
	}
}

} // End of namespace LastExpress