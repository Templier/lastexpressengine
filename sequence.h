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

/*
	Sequence format (.SEQ / .NIS (frame header & data only))

	uint32 {4}    - Number of frames in sequence

	frames headers:
	// for each frame
		uint32 {4}    - Data offset (from beginning of file)
		uint32 {4}    - Unknown
		uint32 {4}    - Palette offset (from beginning of file)
		uint32 {4}    - Top-left X coordinate
		uint32 {4}    - Top-left Y coordinate
		uint32 {4}    - Bottom-right X coordinate
		uint32 {4}    - Bottom-right Y coordinate
		uint32 {4}    - Initial offset of decompressed data (doubled, since each pixel occupies one color word)
		uint32 {4}    - End of data after decompression

		(for SEQ files only)
		uint32 {4}    - Unknown
		uint32 {4}    - Unknown
		byte {1}      - Compression type
		byte {1}      - Unknown
		uint16 {2}    - Unknown
		uint32 {4}    - Unknown
		uint32 {4}    - Unknown
		uint32 {4}    - Unknown
		uint16 {2}    - Set to 1 in some places
		uint32 {4}    - Unknown
		uint32 {4}    - Unknown

		(for NIS files: found at 0x124)
		byte {1}	  - Compression type

	palette	data:
		uint16 {x}    - palette data (max size: 256)

	data
		byte {x}      - compressed image data
*/

#include "lastexpress/drawable.h"

#include "common/stream.h"

namespace LastExpress {

struct FrameInfo {
	void read(Common::SeekableReadStream *in, uint16 decompOffset);

	uint32 dataOffset;					///< Data offset (from beginning of file)
	uint32 unknown;						///< FIXME: unknown data
	uint32 paletteOffset;				///< Palette offset (from beginning of file)
	uint32 xPos1;						///< Top-left X coordinate
	uint32 yPos1;						///< Top-left Y coordinate
	uint32 xPos2;						///< Bottom-right X coordinate
	uint32 yPos2;						///< Bottom-right Y coordinate
	uint32 initialSkip;					///< Initial offset of decompressed data (doubled, since each pixel occupies one color word)
	uint32 decompressedEndOffset;		///< End of data after decompression

	// NIS frame headers end here. SEQ frame headers have additional 32 bytes of
	// data, notably the compression type at the position outlined above in
	// CompPos_SEQ

	byte compressionType;				///< Type of frame compression (0x03, 0x04, 0x05, 0x07, 0xFF)
};

class AnimFrame : public Drawable {
public:
	AnimFrame(Common::SeekableReadStream *in, FrameInfo *f);
	~AnimFrame();
	Common::Rect draw(Graphics::Surface *s);

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
	Common::Rect _rect;
};

class Sequence {
public:
	Sequence();
	~Sequence();

	bool load(Common::SeekableReadStream *stream);
	uint32 count();
	AnimFrame *getFrame(uint32 index);

	// TODO add getter for frame info (when we know what all the unknown entries are for)
	//FrameInfo *getFrameInfo(uint32 index);

	// TODO add option to cache decoded frames (for the start menu for example, we don't want to decode again on buttons mouseover)

private:
	static const uint32 _sequenceHeaderSize = 8;
	static const uint32 _sequenceFrameSize = 68;
	static const uint32 _compressionOffsetSEQ = 0x002c;
	static const uint32 _compressionOffsetNIS = 0x0124;

	void reset();

	Common::Array<FrameInfo> _frames;
	Common::SeekableReadStream *_stream;
	AnimFrame* _currentFrame;
	uint32 _currentIndex;
};

class SequencePlayer : public Drawable {
public:
	SequencePlayer(Sequence *sequence);
	~SequencePlayer();

	bool processTime();
	bool hasEnded();
	Common::Rect draw(Graphics::Surface *surface);
	// TODO: options to go to a concrete frame, play forwards, play backwards...

private:
	Sequence *_sequence;
	uint32 _currentFrame;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SEQUENCE_H
