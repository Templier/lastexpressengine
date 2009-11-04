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
SceneHeader *SceneHeader::load(Common::SeekableReadStream *stream) {
	SceneHeader *sh = new SceneHeader();
	if (!sh)
		return NULL;

	stream->read(&sh->name, sizeof(sh->name));
	sh->sig = stream->readByte();
	sh->count = stream->readUint16LE();;
	sh->field_11 = stream->readUint16LE();
	sh->field_13 = stream->readUint16LE();
	sh->field_15 = stream->readByte();
	sh->type = stream->readByte();
	sh->param1 = stream->readByte();
	sh->param2 = stream->readByte();
	sh->field_19 = stream->readByte();
	sh->hotspot = stream->readUint32LE();

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
	hs->param1 = stream->readByte();
	hs->param2 = stream->readByte();
	hs->unknown12 = stream->readByte();
	hs->cursor = stream->readByte();
	hs->next = stream->readUint32LE();

	debugC(9, kLastExpressDebugScenes, "\thotspot: scene=%d location=%02d action=%02d param1=%02d param2=%02d cursor=%02d rect=(%d, %d)x(%d,%d)",
									   hs->scene, hs->location, hs->action, hs->param1, hs->param2, hs->cursor, hs->rect.left, hs->rect.top, hs->rect.right, hs->rect.bottom);
	debugC(9, kLastExpressDebugScenes, "\t         uA=%d u12=%02d, next=%d offset=%d ", 
									   hs->unknownA, hs->unknown12, hs->next, hs->offset);

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

	debugC(9, kLastExpressDebugScenes, "Scene:  name=%s, sig=%02d, count=%d, field_11=%d", header->name, header->sig, header->count, header->field_11);
	debugC(9, kLastExpressDebugScenes, "\tfield_13=%02d, type=%02d, param1=%02d, param2=%02d", header->field_13, header->type, header->param1, header->param2);
	debugC(9, kLastExpressDebugScenes, "\tfield_19=%02d, hotspot=%d\n", header->field_19, header->hotspot);

	// Read all hotspots
	if (header->hotspot != 0) {
		stream->seek(header->hotspot, SEEK_SET);		
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

	debugC(9, kLastExpressDebugScenes, "Loading scene %d", index);
	return Scene::load(_stream, _headers[index - 1]);
}

} // End of namespace LastExpress
