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

#ifndef LASTEXPRESS_SEQUENCE_H
#define LASTEXPRESS_SEQUENCE_H

#include "common/stream.h"
#include "graphics/surface.h"

#include "lastexpress/resource.h"

namespace LastExpress {

struct FrameInfo {
	void read(Common::SeekableReadStream *in, uint16 decompOffset);

	uint32 dataOffset;					//!< Data offset (from beginning of file)
	uint32 unknown;						//!< FIXME: unknown data
	uint32 paletteOffset;				//!< Palette offset (from beginning of file)
	uint32 xPos1;						//!< Top-left X coordinate
	uint32 yPos1;						//!< Top-left Y coordinate
	uint32 xPos2;						//!< Bottom-right X coordinate
	uint32 yPos2;						//!< Bottom-right Y coordinate
	uint32 initialSkip;					//!< Initial offset of decompressed data (doubled, since each pixel occupies one color word)
	uint32 decompressedEndOffset;		//!< End of data after decompression

	// NIS frame headers end here. SEQ frame headers have additional 32 bytes of
	// data, notably the compression type at the position outlined above in
	// CompPos_SEQ

	byte compressionType;				//!< Type of frame compression (0x03, 0x04, 0x05, 0x07, 0xFF)
};

class AnimFrame {
public:
	AnimFrame(Common::SeekableReadStream *in, FrameInfo *f);
	~AnimFrame();
	void paint(Graphics::Surface *s);

private:
	void decomp3(Common::SeekableReadStream *in, FrameInfo *f);
	void decomp4(Common::SeekableReadStream *in, FrameInfo *f);
	void decomp34(Common::SeekableReadStream *in, FrameInfo *f, byte mask, byte shift);
	void decomp5(Common::SeekableReadStream *in, FrameInfo *f);
	void decomp7(Common::SeekableReadStream *in, FrameInfo *f);
	void decompFF(Common::SeekableReadStream *in, FrameInfo *f);
	void readPalette(Common::SeekableReadStream *in, FrameInfo *f);

	Graphics::Surface _image;
	uint16 _palSize;
	uint16 *_palette;
};

class Sequence {
public:
	Sequence(ResourceManager *resource);
	~Sequence();

	bool load(const Common::String &name);	
	bool show(uint32 index);

	uint32 count();

	// TODO add getter for frame info
	//FrameInfo *getFrameInfo(uint32 index);

private:
	static const uint32 _sequenceHeaderSize = 8;
	static const uint32 _sequenceFrameSize = 68;
	static const uint32 _compressionOffsetSEQ = 0x002c;
	static const uint32 _compressionOffsetNIS = 0x0124;

	void reset();
	AnimFrame *decodeFrame(Common::SeekableReadStream *in, uint32 numFrame);

	ResourceManager *_resource;
	Common::Array<FrameInfo> _frames;

	Common::SeekableReadStream *_stream;

	uint32 _unknown;
};

} // End of LastExpress namespace

#endif // LASTEXPRESS_SEQUENCE_H
