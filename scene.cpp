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
#include "lastexpress/debug.h"
#include "lastexpress/resource.h"

#include "common/debug.h"
#include "common/stream.h"

namespace LastExpress {

Scene::Scene(ResourceManager *resource) : _resource(resource), _stream(NULL) {}

Scene::~Scene() {
	delete _stream;
}

bool Scene::load(Common::SeekableReadStream *stream) {
	if (!stream)
		return false;

	delete _stream;
	_stream = stream;

	// Read the number of scenes (the first entry is a dummy one)
	stream->seek(9, SEEK_SET);
	uint32 numScenes = stream->readUint32LE();
	debugC(2, kLastExpressDebugScenes, "   found %d entries", numScenes);

	if (numScenes > 2500)
		return false;

	// Go to first scene
	stream->seek(_headerSize, SEEK_SET);

	// Read all the chunks
	for (uint32 i = 0; i < numScenes; ++i) {

		SceneEntry scene;

		stream->read(&scene.name, sizeof(scene.name));
		scene.sig = stream->readByte();
		scene.count = stream->readUint16LE();;
		scene.unknown11 = stream->readUint16LE();
		scene.unknown13 = stream->readUint16LE();
		scene.unknown15 = stream->readByte();
		scene.unknown16 = stream->readByte();
		scene.unknown17 = stream->readByte();
		scene.unknown18 = stream->readByte();
		scene.unknown19 = stream->readByte();
		scene.offsetHotspot = stream->readUint16LE();
		scene.unknown22 = stream->readByte();
		scene.unknown23 = stream->readByte();

		_scenes.push_back(scene);
	}

	return true;
}

bool Scene::setScene(uint16 index) {
	_currentScene = index;
	return true;
}

Common::Rect Scene::draw(Graphics::Surface *surface) {
	if (_currentScene == 0 || _currentScene > 2500) // max number of scenes
		_currentScene = 1;

	SceneEntry scene = _scenes[_currentScene - 1];

#ifdef _DEBUG
	debugC(9, kLastExpressDebugScenes, "\nScene:  name=%s, sig=%02d, count=%d, unk11=%d", scene.name, scene.sig, scene.count, scene.unknown11);
	debugC(9, kLastExpressDebugScenes, "\tunk13=%02d, unk16=%02d, unk17=%02d, unk18=%02d", scene.unknown13, scene.unknown16, scene.unknown17, scene.unknown18);
	debugC(9, kLastExpressDebugScenes, "\tunk19=%02d, hotspotOffset=%02d, unk22=%02d, unk23=%02d", scene.unknown19, scene.offsetHotspot, scene.unknown22, scene.unknown23);

	// Read all hotspots
	if (scene.offsetHotspot != 0) {
		_stream->seek(scene.offsetHotspot, SEEK_SET);
		SceneHotspot hotspot;
		while (readHotspot(&hotspot))
			debugC(9, kLastExpressDebugScenes, "\thotspot: Rect=(%d, %d)x(%d,%d) event=%02d", hotspot.rect.left, hotspot.rect.top, hotspot.rect.right, hotspot.rect.bottom, hotspot.eventId);
	}
#endif

	// Safety checks
	Common::String name(scene.name);
	name.trim();
	if (name.empty()) {
		debugC(2, kLastExpressDebugScenes, "This scene is not a valid root scene: %i", _currentScene);
		return Common::Rect();
	}

	// Load background
	Background *background = _resource->loadBackground(name);
	Common::Rect rect;
	if (background) {
		rect = background->draw(surface);
		delete background;
	}

	return rect;
}

bool Scene::checkHotSpot(uint index, Common::Point coord, byte *eventId) {
	// Reset values
	*eventId = 0;

	SceneEntry entry = _scenes[index - 1];	// we don't store the first entry (only stores the number of scenes)

	// TODO: Iterate over scene rectangles
	if (entry.offsetHotspot == 0)
		return false;

	_stream->seek(entry.offsetHotspot, SEEK_SET);

	uint16 unknown = 0;
	byte id = 0;
	bool found = false;
	SceneHotspot hotspot;
	while(readHotspot(&hotspot)) {
		if (hotspot.rect.contains(coord)) {
			if (unknown <= hotspot.unknown14) {
				found = true;
				unknown = hotspot.unknown14;
				id = hotspot.eventId;
			}
		}
	}

	if (found) {
		*eventId = id;
		return true;
	}

	return false;
}

// Read hotpost information
bool Scene::readHotspot(SceneHotspot *hotspot) {

	// Check that we have data to read
	uint16 left = _stream->readUint16LE();
	if (left == 0)
		return false;

	// Rect
	hotspot->rect.left = left;
	hotspot->rect.right = _stream->readUint16LE();
	hotspot->rect.top = _stream->readUint16LE();
	hotspot->rect.bottom = _stream->readUint16LE();

	hotspot->offset = _stream->readUint16LE();
	hotspot->unknown10 = _stream->readUint16LE();
	hotspot->unknown12 = _stream->readUint16LE();
	hotspot->unknown14 = _stream->readByte();
	hotspot->eventId = _stream->readByte();
	hotspot->unknown17 = _stream->readUint16LE();
	hotspot->unknown19 = _stream->readUint16LE();
	hotspot->unknown21 = _stream->readUint16LE();
	hotspot->unknown23 = _stream->readUint16LE();

	return true;
}

//Scene::SceneEntry *Scene::getEntry(uint sceneIndex) {
//	if (_scenes.empty())
//		return NULL;
//
//	if (sceneIndex < 0 || sceneIndex > _scenes.size())
//		return NULL;
//
//	return &_scenes[sceneIndex];
//}

} // End of namespace LastExpress
