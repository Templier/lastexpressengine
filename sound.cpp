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
#include "lastexpress/sound.h"

#include "sound/mixer.h"

namespace LastExpress {

Sound::Sound(ResourceManager *resource) : _resource(resource) {}

Sound::~Sound() {

}

// TODO handle LNK and NIS files
bool Sound::load(const Common::String &name)
{
	// Get a stream to the file
	if (!_resource->hasFile(name)) {
		debugC(2, kLastExpressDebugSound, "Error opening sound: %s", name.c_str());
		return false;
	}

	debugC(2, kLastExpressDebugVideo, "Loading sound: %s", name.c_str());
	Common::SeekableReadStream *stream = _resource->createReadStreamForMember(name);	

	// Read the sound header
	_header.size = stream->readUint32LE();
	_header.count = stream->readUint16LE();

	// Using MS IMA ADPCM reduces sound corruption a lot, but there are still some problems
	// Maybe we need to have our own ADPCM decoding :(
	_audio = Audio::makeADPCMStream(stream, false, _header.size, Audio::kADPCMMSIma, 44100, 1, _soundBlockSize, 0);

	return true;
}

void Sound::play(Audio::Mixer *mixer) {
	Audio::SoundHandle sound_handle;
	mixer->playInputStream(Audio::Mixer::kPlainSoundType, &sound_handle, _audio);
}

Audio::AudioStream* Sound::getAudioStream() {
	return _audio;
}

} // End of namespace LastExpress