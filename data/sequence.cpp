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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

// Based on Deniz Oezmen's code: http://oezmen.eu/

#include "lastexpress/data/sequence.h"

#include "lastexpress/debug.h"

namespace LastExpress {

void FrameInfo::read(Common::SeekableReadStream *in, uint16 decompOffset) {
	// Save the current position
	uint32 basePos = in->pos();

	dataOffset = in->readUint32LE();
	unknown = in->readUint32LE();
	paletteOffset = in->readUint32LE();
	xPos1 = in->readUint32LE();
	yPos1 = in->readUint32LE();
	xPos2 = in->readUint32LE();
	yPos2 = in->readUint32LE();
	initialSkip = in->readUint32LE();
	decompressedEndOffset = in->readUint32LE();

	// Read the compression type
	in->seek(basePos + decompOffset);
	compressionType = in->readByte();

	/*
	unknown = in->readUint32LE();
	//warning("frame, val 0: 0x%04x %d", unknown, unknown);
	unknown = in->readUint32LE();
	//warning("frame, val 1: 0x%04x %d", unknown, unknown);
	compressionType = in->readByte();
	//warning("frame, comptype: 0x%04x %d", compressionType, compressionType);
	unknown = in->readByte();
	//warning("frame, val 2: 0x%04x %d", unknown, unknown);
	unknown = in->readUint16LE();
	//warning("frame, val 2: 0x%04x %d", unknown, unknown);

	// Sequence information
	header->unknown4 = _stream->readUint32LE();
	header->unknown5 = _stream->readUint32LE();
	header->compressionType = _stream->readByte();
	header->unknown7 = _stream->readByte();
	header->unknown8 = _stream->readUint16LE();
	header->unknown9 = _stream->readUint32LE();
	header->unknown10 = _stream->readUint32LE();
	header->unknown11 = _stream->readUint32LE();
	header->unknown12 = _stream->readUint32LE();
	header->unknown13 = _stream->readUint32LE();

	// decomp?
	for (int i = 3; i < 8; i++) {
		unknown = in->readUint32LE();
		//warning("frame, val %d: 0x%04x %d", n, i, unknown, unknown);
		if (i == 5 || i == 7)
			assert (unknown == 0);
	}
	*/
}


// AnimFrame

AnimFrame::AnimFrame(Common::SeekableReadStream *in, FrameInfo *f) : _palette(NULL) {
	_palSize = 1;
	// TODO: use just the needed rectangle
	_image.create(640, 480, 1);

	debugC(6, kLastExpressDebugGraphics, "    Offsets: data=%d, unknown=%d, palette=%d", f->dataOffset, f->unknown, f->paletteOffset);
	debugC(6, kLastExpressDebugGraphics, "    Position: (%d, %d) - (%d, %d)", f->xPos1, f->yPos1, f->xPos2, f->yPos2);
	debugC(6, kLastExpressDebugGraphics, "    Initial Skip: %d", f->initialSkip);
	debugC(6, kLastExpressDebugGraphics, "    Decompressed end offset: %d", f->decompressedEndOffset);
	debugC(6, kLastExpressDebugGraphics, "    Compression type: %u\n", f->compressionType);

	switch (f->compressionType) {
	case 0:
		// Empty frame
		break;
	case 3:
		decomp3(in, f);
		break;
	case 4:
		decomp4(in, f);
		break;
	case 5:
		decomp5(in, f);
		break;
	case 7:
		decomp7(in, f);
		break;
	case 255:
		decompFF(in, f);
		break;
	default:
		error("Unknown frame compression: %d", f->compressionType);
	}

	readPalette(in, f);
	_rect = Common::Rect(f->xPos1, f->yPos1, f->xPos2, f->yPos2);
	//_rect.debugPrint(0, "Frame rect:");
}

AnimFrame::~AnimFrame() {
	_image.free();
	delete[] _palette;
}

Common::Rect AnimFrame::draw(Graphics::Surface *s) {
	byte *inp = (byte *)_image.pixels;
	uint16 *outp = (uint16 *)s->pixels;
	for (int i = 0; i < 640 * 480; i++, inp++, outp++) {
		if (*inp)
			*outp = _palette[*inp];
	}
	return _rect;
}

void AnimFrame::readPalette(Common::SeekableReadStream *in, FrameInfo *f) {
	// Read the palette
	in->seek(f->paletteOffset);
	_palette = new uint16[_palSize];
	for (uint32 i = 0; i < _palSize; i++) {
		_palette[i] = in->readUint16LE();
	}
}

void AnimFrame::decomp3(Common::SeekableReadStream *in, FrameInfo *f) {
	decomp34(in, f, 0x7, 3);
}

void AnimFrame::decomp4(Common::SeekableReadStream *in, FrameInfo *f) {
	decomp34(in, f, 0xf, 4);
}

void AnimFrame::decomp34(Common::SeekableReadStream *in, FrameInfo *f, byte mask, byte shift) {
	byte *p = (byte *)_image.getBasePtr(0, 0);

	uint32 skip = f->initialSkip / 2;
	uint32 size = f->decompressedEndOffset / 2;
	//warning("skip: %d, %d", skip % 640, skip / 640);
	//warning("size: %d, %d", size % 640, size / 640);
	//assert (f->yPos1 == skip / 640);
	//assert (f->yPos2 == size / 640);

	uint32 numBlanks = 640 - (f->xPos2 - f->xPos1);

	in->seek(f->dataOffset);
	for (uint32 out = skip; out < size; ) {
		uint16 opcode = in->readByte();

		if (opcode & 0x80) {
			if (opcode & 0x40) {
				opcode &= 0x3f;
				out += numBlanks + opcode + 1;
			} else {
				opcode &= 0x3f;
				if (opcode & 0x20) {
					opcode = ((opcode & 0x1f) << 8) + in->readByte();
					if (opcode & 0x1000) {
						out += opcode & 0xfff;
						continue;
					}
				}
				out += opcode + 2;
			}
		} else {
			byte value = opcode & mask;
			opcode >>= shift;
			if (_palSize <= value)
				_palSize = value + 1;
			if (!opcode)
				opcode = in->readByte();
			for (int i = 0; i < opcode; i++, out++) {
				p[out] = value;
			}
		}
	}
}

void AnimFrame::decomp5(Common::SeekableReadStream *in, FrameInfo *f) {
	byte *p = (byte *)_image.getBasePtr(0, 0);

	uint32 skip = f->initialSkip / 2;
	uint32 size = f->decompressedEndOffset / 2;
	//warning("skip: %d, %d", skip % 640, skip / 640);
	//warning("size: %d, %d", size % 640, size / 640);
	//assert (f->yPos1 == skip / 640);
	//assert (f->yPos2 == size / 640);

	in->seek(f->dataOffset);
	for (uint32 out = skip; out < size; ) {
		uint16 opcode = in->readByte();
		if (!(opcode & 0x1f)) {
			opcode = (opcode << 3) + in->readByte();
			if (opcode & 0x400) {
				// skip these 10 bits
				out += (opcode & 0x3ff);
			} else {
				out += opcode + 2;
			}
		} else {
			byte value = opcode & 0x1f;
			opcode >>= 5;
			if (_palSize <= value)
				_palSize = value + 1;
			if (!opcode)
				opcode = in->readByte();
			for (int i = 0; i < opcode; i++, out++) {
				p[out] = value;
			}
		}
	}
}

void AnimFrame::decomp7(Common::SeekableReadStream *in, FrameInfo *f) {
	byte *p = (byte *)_image.getBasePtr(0, 0);

	uint32 skip = f->initialSkip / 2;
	uint32 size = f->decompressedEndOffset / 2;
	//warning("skip: %d, %d", skip % 640, skip / 640);
	//warning("size: %d, %d", size % 640, size / 640);
	//assert (f->yPos1 == skip / 640);
	//assert (f->yPos2 == size / 640);

	uint32 numBlanks = 640 - (f->xPos2 - f->xPos1);

	in->seek(f->dataOffset);
	for (uint32 out = skip; out < size; ) {
		uint16 opcode = in->readByte();
		if (opcode & 0x80) {
			if (opcode & 0x40) {
				if (opcode & 0x20) {
					opcode &= 0x1f;
					out += numBlanks + opcode + 1;
				} else {
					opcode &= 0x1f;
					if (opcode & 0x10) {
						opcode = ((opcode & 0xf) << 8) + in->readByte();
						if (opcode & 0x800) {
							// skip these 11 bits
							out += (opcode & 0x7ff);
							continue;
						}
					}

					// skip these 4 bits
					out += opcode + 2;
				}
			} else {
				opcode &= 0x3f;
				byte value = in->readByte();
				if (_palSize <= value)
					_palSize = value + 1;
				for (int i = 0; i < opcode; i++, out++) {
					p[out] = value;
				}
			}
		} else {
			if (_palSize <= opcode)
				_palSize = opcode + 1;
			// set the given value
			p[out] = opcode;
			out++;
		}
	}
}

void AnimFrame::decompFF(Common::SeekableReadStream *in, FrameInfo *f) {
	byte *p = (byte *)_image.getBasePtr(0, 0);

	uint32 skip = f->initialSkip / 2;
	uint32 size = f->decompressedEndOffset / 2;

	in->seek(f->dataOffset);
	for (uint32 out = skip; out < size; ) {
		uint16 opcode = in->readByte();

		if (opcode < 0x80) {
			if (_palSize <= opcode)
				_palSize = opcode + 1;
			// set the given value
			p[out] = opcode;
			out++;
		} else {
			if (opcode < 0xf0) {
				if (opcode < 0xe0) {
					// copy old part
					uint32 old = out + ((opcode & 0x7) << 8) + in->readByte() - 2048;
					opcode = ((opcode >> 3) & 0xf) + 3;
					for (int i = 0; i < opcode; i++, out++, old++) {
						p[out] = p[old];
					}
				} else {
					opcode = (opcode & 0xf) + 1;
					byte value = in->readByte();
					if (_palSize <= value)
						_palSize = value + 1;
					for (int i = 0; i < opcode; i++, out++) {
						p[out] = value;
					}
				}
			} else {
				out += ((opcode & 0xf) << 8) + in->readByte();
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//  SEQUENCE
//////////////////////////////////////////////////////////////////////////

Sequence::Sequence() : _stream(NULL) {
}

Sequence::~Sequence() {
	reset();
}

void Sequence::reset() {
	_frames.clear();
	delete _stream;
	_stream = NULL;
}

bool Sequence::load(Common::SeekableReadStream *stream) {
	if (!stream)
		return false;

	// Reset data
	reset();

	// Copy stream for later decoding of sequence
	_stream = stream;

	// Read header to get the number of frames
	uint32 numframes = _stream->readUint32LE();
	uint32 unknown = _stream->readUint32LE();
	debugC(3, kLastExpressDebugGraphics, "Number of frames in sequence: %d / unknown=0x%x", numframes, unknown);

	// Store frames information
	for (uint i = 0; i < numframes; i++) {

		// Move stream to start of frame
		_stream->seek(_sequenceHeaderSize + i * _sequenceFrameSize, SEEK_SET);
		if (_stream->eos()) {
			error("Couldn't seek to the current frame data");
			return false;
		}

		// Check if there is enough data
		if ((unsigned)(_stream->size() - _stream->pos()) < _sequenceFrameSize) {
			error("The sequence frame does not have a valid header");
			return false;
		}

		FrameInfo info;
		info.read(_stream, _compressionOffsetSEQ);
		_frames.push_back(info);
	}

	return true;
}

uint32 Sequence::count() {
	return _frames.size();
}

AnimFrame *Sequence::getFrame(uint32 index) {
	if (_frames.size() == 0) {
		warning("Trying to decode a sequence before loading its data");
		return NULL;
	}

	if (index > _frames.size() - 1) {
		warning("Invalid sequence frame requested: %d, max %d", index, _frames.size() - 1);
		return NULL;
	}

	// Skip "invalid" frames
	if (_frames[index].compressionType == 0)
		return NULL; // FIXME is this error handled correctly in all cases?

	debugC(4, kLastExpressDebugGraphics, "Decoding frame %d / %d", index, _frames.size() - 1);

	return new AnimFrame(_stream, &_frames[index]);
}


// SequencePlayer

SequencePlayer::SequencePlayer(Sequence *sequence) :
	_sequence(sequence), _currentFrame(0) {
}

SequencePlayer::~SequencePlayer() {
	delete _sequence;
}

bool SequencePlayer::processTime() {
	// TODO: Just increase the current frame when it's the appropiate time
	if (_currentFrame < _sequence->count()) {
		_currentFrame++;
		return true;
	} else
		return true;
}

bool SequencePlayer::hasEnded() {
	return _currentFrame >= _sequence->count();
}

Common::Rect SequencePlayer::draw(Graphics::Surface *surface) {
	if (hasEnded())
		return Common::Rect();

	AnimFrame *f = _sequence->getFrame(_currentFrame);
	if (!f)
		return Common::Rect();

	Common::Rect rect = f->draw(surface);

	delete f;

	return rect;
}

bool SequencePlayer::setFrame(uint32 frame) {
	if (frame < _sequence->count()) {
		_currentFrame = frame;
		return true;
	} else
		return false;
}

} // End of namespace LastExpress
