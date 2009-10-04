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

#include "sound/adpcm.h"
#include "sound/audiostream.h"

// Based on the Xentax Wiki documentation:
// http://wiki.xentax.com/index.php/The_Last_Express_SND

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// Sound
//////////////////////////////////////////////////////////////////////////
Sound::Sound() {}

Sound::~Sound() {
	// Stop the sound
	g_system->getMixer()->stopHandle(_handle);
}

void Sound::loadHeader(Common::SeekableReadStream *in) {
	_size = in->readUint32LE();
	_blocks = in->readUint16LE();
	debugC(5, kLastExpressDebugSound, "    sound header data: size=\"%d\", %d blocks", _size, _blocks);

	assert (_size % _blocks == 0);
	_blockSize = _size / _blocks;
}

Audio::AudioStream *Sound::makeDecoder(Common::SeekableReadStream *in, uint32 size) const {
	return Audio::makeADPCMStream(in, true, size, Audio::kADPCMMSIma, 44100, 1, _blockSize);
}

void Sound::play(Audio::AudioStream *as) {
	g_system->getMixer()->playInputStream(Audio::Mixer::kPlainSoundType, &_handle, as);
}

//////////////////////////////////////////////////////////////////////////
// StreamedSound
//////////////////////////////////////////////////////////////////////////
StreamedSound::StreamedSound(ResourceManager *resource) : _resource(resource), _data(NULL) {
}

StreamedSound::~StreamedSound() {
	if (_data)
		free(_data);
}

bool StreamedSound::load(const Common::String &name) {

	g_system->getMixer()->stopHandle(_handle);

	// Get a stream to the file
	if (!_resource->hasFile(name)) {
		debugC(2, kLastExpressDebugSound, "Error opening sound: %s", name.c_str());
		return false;
	}

	debugC(2, kLastExpressDebugGraphics, "=================================================================");
	debugC(2, kLastExpressDebugGraphics, "Loading sound: %s", name.c_str());
	Common::SeekableReadStream *stream = _resource->createReadStreamForMember(name);

	loadHeader(stream);

	// Load all sound data to buffer
	if (!_data)
		_data = (byte*)malloc(_size);

	stream->read(_data, _size);
	Common::MemoryReadStream *buffer = new Common::MemoryReadStream(_data, _size);

	// Start decoding the input stream
	Audio::AudioStream *as = makeDecoder(buffer, _size);

	// Start playing the decoded audio stream
	play(as);

	return true;
}

//////////////////////////////////////////////////////////////////////////
// StreamedSound
//////////////////////////////////////////////////////////////////////////
AppendableSound::AppendableSound() : Sound() {
	// Create an audio stream where the decoded chunks will be appended
	// TODO: the ADPCM decoder works in native endianness, so the usage FLAG_LITTLE_ENDIAN will depend on the current platform
	_as = Audio::makeAppendableAudioStream(44100, Audio::Mixer::FLAG_16BITS | Audio::Mixer::FLAG_AUTOFREE | Audio::Mixer::FLAG_LITTLE_ENDIAN);
	_finished = false;

	// Start playing the decoded audio stream
	play(_as);

	// Initialize the block size
	// TODO: get it as an argument?
	_blockSize = 739;
}

AppendableSound::~AppendableSound() {
	finish();
}

bool AppendableSound::endOfSound() {
	return _as->endOfData();
}

void AppendableSound::queueBuffer(byte *data, uint32 size) {
	Common::MemoryReadStream *buffer = new Common::MemoryReadStream(data, size);
	queueBuffer(buffer);
}

void AppendableSound::queueBuffer(Common::SeekableReadStream *bufferIn) {
	assert (_as);

	// Setup the ADPCM decoder
	uint32 sizeIn = bufferIn->size();
	Audio::AudioStream *adpcm = makeDecoder(bufferIn, sizeIn);

	// Setup the output buffer
	uint32 sizeOut = sizeIn * 2;
	byte *bufferOut = new byte[sizeOut * 2];

	// Decode to raw samples
	sizeOut = adpcm->readBuffer((int16 *)bufferOut, sizeOut);
	assert (adpcm->endOfData());
	delete adpcm;

	// Queue the decoded samples
	_as->queueBuffer(bufferOut, sizeOut * 2);
}

void AppendableSound::finish() {
	assert (_as);
	if (!_finished)
		_as->finish();

	_finished = true;
}

} // End of namespace LastExpress
