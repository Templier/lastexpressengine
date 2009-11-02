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

	return sh;
}

SceneHotspot *SceneHotspot::load(Common::SeekableReadStream *stream) {
	// Check that we have data to read
	uint16 left = stream->readUint16LE();

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
	hs->location = stream->readByte();
	hs->action = stream->readByte();
	hs->param = stream->readByte();
	hs->unknown11 = stream->readByte();
	hs->unknown12 = stream->readByte();
	hs->cursor = stream->readByte();
	hs->next = stream->readUint16LE();
	hs->unknown16 = stream->readUint16LE();

	debugC(9, kLastExpressDebugScenes, "\thotspot: rect=(%d, %d)x(%d,%d) scene=%d location=%02d action=%02d param=%02d cursor=%02d",
									   hs->rect.left, hs->rect.top, hs->rect.right, hs->rect.bottom, hs->scene, hs->location, hs->action, hs->param, hs->cursor);
	debugC(9, kLastExpressDebugScenes, "\t         next=%d offset=%d uA=%d u11=%02d u12=%02d u16=%d", 
									   hs->next, hs->offset, hs->unknownA, hs->unknown11, hs->unknown12, hs->unknown16);

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

	debugC(9, kLastExpressDebugScenes, "\nScene:  name=%s, sig=%02d, count=%d, unk11=%d", header->name, header->sig, header->count, header->unknown11);
	debugC(9, kLastExpressDebugScenes, "\tunk13=%02d, unk16=%02d, soundId=%02d, unk18=%02d", header->unknown13, header->unknown16, header->soundId, header->unknown18);
	debugC(9, kLastExpressDebugScenes, "\tunk19=%02d, hotspotOffset=%02d, unk22=%02d, unk23=%02d\n", header->unknown19, header->offsetHotspot, header->unknown22, header->unknown23);


	// Read all hotspots
	if (header->offsetHotspot != 0) {
		stream->seek(header->offsetHotspot, SEEK_SET);		
		while (1) {
			SceneHotspot *hotspot = SceneHotspot::load(stream);

			if (!hotspot)
				break;

			s->_hotspots.push_back(hotspot);
			
			if (hotspot->next == 0)
				break;

			stream->seek(hotspot->next, SEEK_SET);
		}
	}

	return s;
}

bool Scene::checkHotSpot(Common::Point coord, SceneHotspot **hotspot) {
	bool found = false;

	for (uint i = 0; i < _hotspots.size(); i++) {
		if (_hotspots[i]->rect.contains(coord)) {
			found = true;
			*hotspot = _hotspots[i];
			break;
		}
	}

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
