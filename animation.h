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

#include "common/array.h"
#include "common/stream.h"

#include "lastexpress/resource.h"

namespace LastExpress {

class AnimFrame;
class AppendableSound;

struct Chunk {
	uint16 type;
	uint16 tag;
	uint32 size;
};

class Animation {
public:
	Animation(ResourceManager *resource);
	~Animation();

	bool load(const Common::String &name);
	bool show();

private:
	static const uint32 _soundBlockSize = 739;	

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
	
	void reset();	
	AnimFrame *processChunkFrame(Common::SeekableReadStream *in, Chunk *c);
	void processOverlayFrame(Common::SeekableReadStream *in, Chunk *c);
	void processChunkAudio(Common::SeekableReadStream *in, Chunk *c);

	ResourceManager *_resource;
	Common::SeekableReadStream *_stream;
	Common::Array<Chunk> _chunks;
	AnimFrame *_background1, *_background2;
	byte _backgroundCurrent;
	AppendableSound *_audio;
};

} // End of Express namespace

#endif // LASTEXPRESS_ANIMATION_H
