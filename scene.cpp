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

#include "lastexpress/scene.h"

#include "lastexpress/background.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

// SceneHeader

class SceneHeader {
public:
	static SceneHeader *load(Common::SeekableReadStream *stream);

private:
	SceneHeader() {}

public: // XXX
	char name[8];     // 0
	byte sig;         // 8
	uint16 count;     // 9
	uint16 unknown11; // 11
	uint16 unknown13; // 13
	byte unknown15;   // 15
	byte unknown16;
	byte soundId;
	byte unknown18;
	byte unknown19;
	uint16 offsetHotspot;
	byte unknown22;
	byte unknown23;
};

SceneHeader *SceneHeader::load(Common::SeekableReadStream *stream) {
	SceneHeader *sh = new SceneHeader();
	if (!sh)
		return NULL;

	stream->read(&sh->name, sizeof(sh->name));
	sh->sig = stream->readByte();
	sh->count = stream->readUint16LE();;
	sh->unknown11 = stream->readUint16LE();
	sh->unknown13 = stream->readUint16LE();
	sh->unknown15 = stream->readByte();
	sh->unknown16 = stream->readByte();
	sh->soundId = stream->readByte();
	sh->unknown18 = stream->readByte();
	sh->unknown19 = stream->readByte();
	sh->offsetHotspot = stream->readUint16LE();
	sh->unknown22 = stream->readByte();
	sh->unknown23 = stream->readByte();

	debugC(9, kLastExpressDebugScenes, "\nScene:  name=%s, sig=%02d, count=%d, unk11=%d", sh->name, sh->sig, sh->count, sh->unknown11);
	debugC(9, kLastExpressDebugScenes, "\tunk13=%02d, unk16=%02d, soundId=%02d, unk18=%02d", sh->unknown13, sh->unknown16, sh->soundId, sh->unknown18);
	debugC(9, kLastExpressDebugScenes, "\tunk19=%02d, hotspotOffset=%02d, unk22=%02d, unk23=%02d", sh->unknown19, sh->offsetHotspot, sh->unknown22, sh->unknown23);

	return sh;
}


// SceneHotspot

class SceneHotspot {
public:
	static SceneHotspot *load(Common::SeekableReadStream *stream);

private:
	SceneHotspot() {}

public: //XXX
	Common::Rect rect;
	uint16 offset;
	uint16 unknownA;
	uint16 scene;
	byte unknownE;
	byte event;
	byte action;
	byte unknown11;	
	uint16 unknown12;
	uint16 unknown14;
	uint16 unknown16;
};

SceneHotspot *SceneHotspot::load(Common::SeekableReadStream *stream) {
	// Check that we have data to read
	uint16 left = stream->readUint16LE();
	if (left == 0)
		return NULL;

	SceneHotspot *hs = new SceneHotspot();
	if (!hs)
		return NULL;

	// Rect
	hs->rect.left = left;
	hs->rect.right = stream->readUint16LE();
	hs->rect.top = stream->readUint16LE();
	hs->rect.bottom = stream->readUint16LE();

	hs->offset = stream->readUint16LE();
	hs->unknownA = stream->readUint16LE();
	hs->scene = stream->readUint16LE();
	hs->unknownE = stream->readByte();
	hs->event = stream->readByte();
	
	// Check that this is a valid hotspot
	if (hs->event == 0 || hs->event > 44) {
		delete hs;
		return NULL;
	}

	hs->action = stream->readByte();
	hs->unknown11 = stream->readByte();
	hs->unknown12 = stream->readUint16LE();
	hs->unknown14 = stream->readUint16LE();
	hs->unknown16 = stream->readUint16LE();

	debugC(9, kLastExpressDebugScenes, "\thotspot: Rect=(%d, %d)x(%d,%d) event=%02d offset=%d action=%03d scene=%d uA=%d uE=%02d u11=%02d u12=%d u14=%d u16=%d",
									   hs->rect.left, hs->rect.top, hs->rect.right, hs->rect.bottom, hs->event, hs->action, hs->scene, hs->unknownA,
									   hs->unknownE, hs->unknown11, hs->unknown12, hs->unknown14, hs->unknown16);

	return hs;
}


// Scene

Scene::~Scene() {
	// Free the hotspots
	for (uint i = 0; i < _hotspots.size(); i++)
		delete _hotspots[i];
}

Scene *Scene::load(Common::SeekableReadStream *stream, SceneHeader *header) {
	Scene *s = new Scene(header);
	if (!s)
		return NULL;

	// Read all hotspots
	if (header->offsetHotspot != 0) {
		stream->seek(header->offsetHotspot, SEEK_SET);
		SceneHotspot *hotspot = SceneHotspot::load(stream);
		while (hotspot) {
			s->_hotspots.push_back(hotspot);
			hotspot = SceneHotspot::load(stream);
		}
	}

	return s;
}

bool Scene::checkHotSpot(Common::Point coord, byte *eventId) {
	// TODO: Iterate over scene rectangles?

	uint16 unknown = 0;
	byte id = 0;
	bool found = false;
	for (uint i = 0; i < _hotspots.size(); i++) {
		if (_hotspots[i]->rect.contains(coord)) {
			if (unknown <= _hotspots[i]->unknown14) {
				found = true;
				unknown = _hotspots[i]->unknown14;
				id = _hotspots[i]->event;
			}
		}
	}

	*eventId = id;
	return found;
}

Common::Rect Scene::draw(Graphics::Surface *surface) {
	// Safety checks
	Common::String name(_header->name);
	name.trim();
	if (name.empty()) {
		error("This scene is not a valid drawing scene: %s", name);		
	}

	// Load background
	Background *background = ((LastExpressEngine *)g_engine)->getResMan()->loadBackground(name);
	Common::Rect rect;
	if (background) {
		rect = background->draw(surface);
		delete background;
	}

	return rect;
}


// SceneManager

SceneManager::SceneManager() : _stream(NULL) {}

SceneManager::~SceneManager() {
	delete _stream;

	// Free the headers
	for (uint i = 0; i < _headers.size(); i++)
		delete _headers[i];
}

bool SceneManager::load(Common::SeekableReadStream *stream) {
	if (!stream)
		return false;

	delete _stream;
	_stream = stream;

	// Read the number of scenes (the first entry is a dummy one)
	_stream->seek(9, SEEK_SET);
	uint32 numScenes = _stream->readUint32LE();
	debugC(2, kLastExpressDebugScenes, "   found %d entries", numScenes);

	if (numScenes > 2500)
		return false;

	// Go to first scene (each header is 24 bytes long)
	_stream->seek(24, SEEK_SET);

	// Read all the chunks
	for (uint32 i = 0; i < numScenes; ++i) {
		SceneHeader *header = SceneHeader::load(_stream);
		if (!header)
			break;
		_headers.push_back(header);
	}

	return true;
}

Scene *SceneManager::getScene(uint16 index) {
	if (_headers.empty())
		return NULL;

	if (index == 0 || index > _headers.size())
		return NULL;

	return Scene::load(_stream, _headers[index - 1]);
}

} // End of namespace LastExpress
