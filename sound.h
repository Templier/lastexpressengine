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

#ifndef LASTEXPRESS_SOUND_H
#define LASTEXPRESS_SOUND_H

#include "common/stream.h"
#include "sound/mixer.h"

namespace Audio {
	class AudioStream;
	class AppendableAudioStream;
}

namespace LastExpress {

class ResourceManager;

class Sound {
public:
	Sound();
	virtual ~Sound();

protected:
	void loadHeader(Common::SeekableReadStream *in);
	Audio::AudioStream *makeDecoder(Common::SeekableReadStream *in, uint32 size) const;
	void play(Audio::AudioStream *as);

	uint32 _size;					//!< data size
									//!<  - NIS: size of all blocks, including those located in the matching LNK file
									//!<  - LNK: size of the LNK file itself, including the header
									//!<  - SND: size of all blocks
	uint16 _blocks;					//!< number of blocks
	uint32 _blockSize;
	Audio::SoundHandle _handle;
};

class StreamedSound : public Sound {
public:
	StreamedSound(ResourceManager *resource);
	~StreamedSound();

	bool load(const Common::String &name);

private:
	ResourceManager *_resource;
	byte *_data;
};

class AppendableSound : public Sound {
public:
	AppendableSound();
	~AppendableSound();

	void queueBuffer(byte *data, uint32 size);
	void queueBuffer(Common::SeekableReadStream *bufferIn);
	void finish();

private:
	Audio::AppendableAudioStream *_as;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SOUND_H