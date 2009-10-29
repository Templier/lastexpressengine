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

/*
	Animation format (.NIS)

	uint32 {4}    - Number of chunks

	// for each chunk
		uint16 {2}    - Type
		uint16 {2}    - Tag
		uint32 {4}    - Size of chunk
		byte {x}      - Data (for "data" chunks: backgrounds, overlay & audio data)
*/

#include "lastexpress/drawable.h"

#include "common/stream.h"

namespace LastExpress {

class AnimFrame;
class AppendableSound;

class Animation : public Drawable {
public:
	Animation();
	~Animation();

	bool load(Common::SeekableReadStream *stream);
	bool process();
	bool hasEnded();
	Common::Rect draw(Graphics::Surface *surface);
	void play();

private:
	static const uint32 _soundBlockSize = 739;

	// despite their size field, info chunks don't have a payload
	enum ChunkType {
		kChunkTypeUnknown1			= 0x0001,
		kChunkTypeUnknown2			= 0x0002,
		kChunkTypeAudioInfo			= 0x0003,
		kChunkTypeUnknown4			= 0x0004,
		kChunkTypeUnknown5			= 0x0005,
		kChunkTypeBackground1       = 0x000a,
		kChunkTypeSelectBackground1 = 0x000b,
		kChunkTypeBackground2       = 0x000c,
		kChunkTypeSelectBackground2 = 0x000d,
		kChunkTypeOverlay           = 0x0014,
		kChunkTypeUpdate			= 0x0015,
		kChunkTypeUpdateTransition	= 0x0016,
		kChunkTypeUnknown1e         = 0x001e,
		kChunkTypeUnknown1f         = 0x001f,
		kChunkTypeAudioData         = 0x0020,
		kChunkTypeAudioEnd          = 0x0063
	};

	struct Chunk {
		ChunkType type;
		uint16 frame;
		uint32 size;
	};

	void reset();
	AnimFrame *processChunkFrame(Common::SeekableReadStream *in, Chunk *c);
	void processChunkAudio(Common::SeekableReadStream *in, Chunk *c);

	Common::SeekableReadStream *_stream;
	Common::Array<Chunk> _chunks;
	Common::Array<Chunk>::iterator _currentChunk;
	AnimFrame *_overlay, *_background1, *_background2;
	byte _backgroundCurrent;
	AppendableSound *_audio;

	uint32 _startTime;
	bool _changed;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ANIMATION_H
