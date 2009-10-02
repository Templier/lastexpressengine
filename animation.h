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

#ifndef LASTEXPRESS_ANIMATION_H
#define LASTEXPRESS_ANIMATION_H

#include "graphics/surface.h"

namespace LastExpress {

class Animation {
public:
	Animation(LastExpressEngine *engine);

	bool loadSequence(const Common::String &name);
	bool loadAnimation(const Common::String &name);

	bool play();
	bool renderFrame(uint32 index);

	uint32 currentFrame();
	uint32 totalFrames();

private:
	static const uint32 _sequenceFrameSize = 68;
	static const uint32 _screenWidth = 640;
	static const uint32 _screenHeight = 480;
	static const uint32 _maxPaletteSize = 256;
	static const uint32 _transparentColor = 255;
	//static const uint32 _lineParBaseCol = _maxPaletteSize - 2;

	static const unsigned int _soundBlockSize = 739;

	// despite their size field, info chunks don't have a payload
	enum typesChunk {
		kChunkTypeUnknown1			= 0x0001,
		kChunkTypeUnknown2			= 0x0002,
		kChunkTypeAudioInfo 		= 0x0003,
		kChunkTypeUnknown4			= 0x0004,
		kChunkTypeUnknown5			= 0x0005,
  		kChunkTypeBackgroundFrameA  = 0x000a,
  		kChunkTypeSelectBackgroundA = 0x000b,
  		kChunkTypeBackgroundFrameC  = 0x000c,
  		kChunkTypeSelectBackgroundC = 0x000d,
  		kChunkTypeOverlayFrame      = 0x0014,
		kChunkTypeUnknown15			= 0x0015,	// might be subtitles
		kChunkTypeUnknown16			= 0x0016,
  		kChunkTypeAudioData         = 0x0020,
  		kChunkTypeAudioEnd          = 0x0063
	};

	struct AnimationHeader {
		uint32 chunksCount;		//!< Number of chunks in the NIS file

		AnimationHeader() : chunksCount(0) {}
	};

	struct AnimationChunk {
		typesChunk type;		//!< Type of chunk
		uint16 tag;				//!< Tag
		uint32 size;			//!< Size of chunk
	};

	struct SequenceHeader {
		uint32 numframes;		//!< data size
		uint32 unknown;			//!< unknown

		SequenceHeader() : numframes(0), unknown(0) {}
	};

	struct FrameHeader {
		uint32 dataOffset;				 //!< Data offset (from beginning of file)
		uint32 unknown1;				
		uint32 paletteOffset;			 //!< Palette offset (from beginning of file)
		uint32 x0;						 //!< Top-left X coordinate
		uint32 y0;						 //!< Top-left Y coordinate
		uint32 x1;						 //!< Bottom-right X coordinate
		uint32 y1;						 //!< Bottom-right Y coordinate
		uint32 initialSkip;				 //!< Initial offset of decompressed data (doubled, since each pixel occupies one color word)
		uint32 decompressedEndOffset;    //!< End of data after decompression

		// NIS frame headers end here. SEQ frame headers have additional 32 bytes of
		// data, notably the compression type at the position outlined above in
		// CompPos_SEQ
	};

	struct SequenceFrameHeader {
		struct FrameHeader frameInfo;
		uint32 unknown4;
		uint32 unknown5;
		byte compressionType;
		byte unknown7;
		byte unknown8;
		byte unknown9;
		uint32 unknown10;
		uint32 unknown11;
		uint32 unknown12;
		uint32 unknown13;
		uint32 unknown14;
	};

	LastExpressEngine *_engine;

	uint32 _currentFrame;
	SequenceHeader _headerSequence;
	Common::Array<AnimationChunk> _chunks;
	
	Common::SeekableReadStream *_stream;

	void cleanup();
	void renderBackground(AnimationChunk *chunk);
	bool renderFrameInternal(Graphics::Surface *surface, Common::SeekableReadStream *stream, FrameHeader *header, byte compressionType);
	bool loadSequenceFrameHeader(SequenceFrameHeader *header, uint32 index);
	void loadFrameHeader(Common::SeekableReadStream *stream, FrameHeader *header);

	// Palette
	void setPixel(byte* pixel, uint32 index, byte value, uint16* palette);

	// Decompression functions
	void decompress_03(Common::SeekableReadStream *stream, FrameHeader *header, byte *output, uint16 *palette);
	void decompress_04(Common::SeekableReadStream *stream, FrameHeader *header, byte *output, uint16 *palette);
	void decompress_05(Common::SeekableReadStream *stream, FrameHeader *header, byte *output, uint16 *palette);
	void decompress_07(Common::SeekableReadStream *stream, FrameHeader *header, byte *output, uint16 *palette);
	void decompress_ff(Common::SeekableReadStream *stream, FrameHeader *header, byte *output, uint16 *palette);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ANIMATION_H