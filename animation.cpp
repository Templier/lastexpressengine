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

// Based on Deniz Oezmen's code: http://oezmen.eu/

#include "lastexpress/animation.h"

#include "lastexpress/debug.h"
#include "lastexpress/sequence.h"
#include "lastexpress/sound.h"

#include "common/events.h"
#include "engines/engine.h"

namespace LastExpress {

Animation::Animation() : _stream(NULL),	_background1(NULL), _background2(NULL), _backgroundCurrent(0), _audio(NULL) {
}

Animation::~Animation() {
	reset();
}

void Animation::reset() {
	delete _background1;
	_background1 = NULL;
	delete _background2;
	_background2 = NULL;
	delete _audio;
	_audio = NULL;

	_backgroundCurrent = 0;
	_chunks.clear();

	delete _stream;
}

bool Animation::load(Common::SeekableReadStream *stream) {
	if (!stream)
		return false;

	reset();

	// Keep stream for later decoding of animation
	_stream = stream;

	// Read header to get the number of chunks
	uint32 numChunks = _stream->readUint32LE();
	debugC(3, kLastExpressDebugGraphics, "Number of chunks in NIS file: %d", numChunks);

	// Check if there is enough data
	if (_stream->size() - _stream->pos() < (signed)(numChunks * sizeof(Chunk))) {
		debugC(2, kLastExpressDebugGraphics, "NIS file seems to be corrupted!");
		return false;
	}

	// Read all the chunks
	for (uint32 i = 0; i < numChunks; ++i) {

		Chunk chunk;
		chunk.type = (typesChunk)_stream->readUint16LE();
		chunk.tag  = _stream->readUint16LE();
		chunk.size = _stream->readUint32LE();

		_chunks.push_back(chunk);

		//debugC(9, kLastExpressDebugGraphics, "Chunk Entry: type 0x%.4x, tag=%d, size=%d", chunk.type, chunk.tag, chunk.size);
	}

	return true;
}

bool Animation::draw() {
	if (_stream == NULL || _chunks.size() == 0) {
		debugC(2, kLastExpressDebugGraphics, "Trying to show an animation before loading data!");
		return false;
	}

	uint32 frameNumber = 0;

	// Process each chunk
	for (Common::Array<Chunk>::iterator c = _chunks.begin(); c != _chunks.end(); ++c) {

		switch(c->type) {
		//TODO: some info chunks are probably subtitle/sync related
		case kChunkTypeUnknown1:
		case kChunkTypeUnknown2:
		case kChunkTypeUnknown5:
			debugC(9, kLastExpressDebugGraphics, "  info chunk: type 0x%.4x (size %d)", c->type, c->size);
			assert (c->tag == 0);
			//TODO: c->size?
			break;

		case kChunkTypeAudioInfo:
			debugC(9, kLastExpressDebugGraphics, "  audio info: %d blocks", c->size);
			assert (c->tag == 0);
			//TODO: save the size?
			_audio = new AppendableSound();
			break;

		case kChunkTypeUnknown4:
			debugC(9, kLastExpressDebugGraphics, "  info block 4: %d blocks", c->size);
			assert (c->tag == 0 && c->size == 0);
			//TODO unknown type of chunk
			break;

		case kChunkTypeBackgroundFrameA:
			debugC(9, kLastExpressDebugGraphics, "  frame A (background type 0x%.4x, %d bytes, tag %d)", c->type, c->size, c->tag);
			delete _background1;
			_background1 = processChunkFrame(_stream, c);
			break;

		case kChunkTypeSelectBackgroundA:
			debugC(9, kLastExpressDebugGraphics, "  frame info: select background A");
			assert (c->tag == 0 && c->size == 0);
			_backgroundCurrent = 1;
			break;

		case kChunkTypeBackgroundFrameC:
			debugC(9, kLastExpressDebugGraphics, "  frame C (background type 0x%.4x, %d bytes, tag %d)", c->type, c->size, c->tag);
			delete _background2;
			_background2 = processChunkFrame(_stream, c);
			break;

		case kChunkTypeSelectBackgroundC:
			debugC(9, kLastExpressDebugGraphics, "  frame info: select background C");
			assert (c->tag == 0 && c->size == 0);
			_backgroundCurrent = 2;
			break;

		case kChunkTypeOverlayFrame: {
			debugC(9, kLastExpressDebugGraphics, "  frame #%.4d (overlay, %d bytes, tag %d)", frameNumber, c->size, c->tag);
			processOverlayFrame(_stream, c);
			frameNumber++;

			// Handle right-click to interrupt animations
			Common::Event ev;
			g_engine->getEventManager()->pollEvent(ev);
			if (ev.type == Common::EVENT_RBUTTONDOWN) {
				// Stop audio
				_audio->finish();

				// TODO start LNK file sound

				return true;
			}

			//FIXME: implement proper syncing + subtitles
			g_engine->_system->delayMillis(50);

			break;
		}


		case kChunkTypeUnknown15:
		case kChunkTypeUnknown16:
			debugC(9, kLastExpressDebugGraphics, "  info chunk: type 0x%.4x (tag %d)", c->type, c->tag);
			assert (c->size == 0);
			//TODO: c->tag?
			break;

		case kChunkTypeAudioData:
			debugC(9, kLastExpressDebugGraphics, "  audio (%d blocks, %d bytes, tag %d)", c->size/_soundBlockSize, c->size, c->tag);
			processChunkAudio(_stream, c);
			break;

		case kChunkTypeAudioEnd:
			debugC(9, kLastExpressDebugGraphics, "  audio end: %d blocks", c->tag);
			assert (c->size == 0);
			_audio->finish();
			//TODO: we need to start the linked sound (.LNK) after the audio from the animation ends
			break;

		default:
			error("  UNKNOWN chunk type=%x tag=%x size=%d", c->type, c->tag, c->size);
			break;
		}
	}

	return true;
}

void Animation::processOverlayFrame(Common::SeekableReadStream *in, Chunk *c) {
	// Create a temporary surface to merge the overlay with the background
	Graphics::Surface *s = new Graphics::Surface;
	s->create(640, 480, 2);

	// Paint the background
	if (_backgroundCurrent == 1 && _background1)
		_background1->draw(s);
	else if (_backgroundCurrent == 2 && _background2)
		_background2->draw(s);

	// Read the overlay frame
	AnimFrame *f = processChunkFrame(in, c);

	// Paint the overlay
	f->draw(s);

	// Free the overlay frame
	delete f;

	// XXX: Update the screen
	g_system->copyRectToScreen((byte *)s->pixels, s->pitch, 0, 0, s->w, s->h);
	g_system->updateScreen();

	// Free the temporary surface
	s->free();
	delete s;
}

AnimFrame *Animation::processChunkFrame(Common::SeekableReadStream *in, Chunk *c) {
	assert (c->tag == 0);

	// Create a temporary chunk buffer
	Common::MemoryReadStream *str = in->readStream(c->size);

	// Read the frame information
	FrameInfo i;
	i.read(str, 0x124);

	// Decode the frame
	AnimFrame *f = new AnimFrame(str, &i);

	// Delete the temporary chunk buffer
	delete str;

	return f;
}

void Animation::processChunkAudio(Common::SeekableReadStream *in, Chunk *c) {
	// Skip the Snd header, to queue just the audio blocks
	uint32 size = c->size;
	if ((c->size % 739) != 0) {
		warning("Start ADPCM: %d, %d", in->readUint32LE(), in->readUint16LE());
		size -= 6;
	}

	// Append the current chunk to the Snd
	_audio->queueBuffer(in->readStream(size));
}

} // End of namespace LastExpress
