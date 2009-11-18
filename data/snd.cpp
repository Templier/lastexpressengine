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

// Based on the Xentax Wiki documentation:
// http://wiki.xentax.com/index.php/The_Last_Express_SND

#include "lastexpress/data/snd.h"

#include "lastexpress/debug.h"

#include "sound/adpcm.h"
#include "sound/audiostream.h"

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// Sound
//////////////////////////////////////////////////////////////////////////
SimpleSound::SimpleSound() {}

SimpleSound::~SimpleSound() {
	stop();
}

// Stop the sound
void SimpleSound::stop() {
	g_system->getMixer()->stopHandle(_handle);
}

void SimpleSound::loadHeader(Common::SeekableReadStream *in) {
	_size = in->readUint32LE();
	_blocks = in->readUint16LE();
	debugC(5, kLastExpressDebugSound, "    sound header data: size=\"%d\", %d blocks", _size, _blocks);

	assert (_size % _blocks == 0);
	_blockSize = _size / _blocks;
}

Audio::AudioStream *SimpleSound::makeDecoder(Common::SeekableReadStream *in, uint32 size) const {
	return Audio::makeADPCMStream(in, true, size, Audio::kADPCMMSIma, 44100, 1, _blockSize);
}

void SimpleSound::play(Audio::AudioStream *as) {
	g_system->getMixer()->playInputStream(Audio::Mixer::kPlainSoundType, &_handle, as);
}

//////////////////////////////////////////////////////////////////////////
// StreamedSound
//////////////////////////////////////////////////////////////////////////
StreamedSound::StreamedSound() {}
StreamedSound::~StreamedSound() {}

bool StreamedSound::load(Common::SeekableReadStream *stream) {
	if (!stream)
		return false;

	g_system->getMixer()->stopHandle(_handle);

	loadHeader(stream);

	// Start decoding the input stream
	Audio::AudioStream *as = makeDecoder(stream, _size);

	// Start playing the decoded audio stream
	play(as);

	return true;
}

//////////////////////////////////////////////////////////////////////////
// StreamedSound
//////////////////////////////////////////////////////////////////////////
AppendableSound::AppendableSound() : SimpleSound() {
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