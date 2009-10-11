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

#include "lastexpress/debug.h"

#include "common/debug.h"
#include "common/stream.h"

namespace LastExpress {

Scene::Scene() {}
Scene::~Scene() {}

bool Scene::load(Common::SeekableReadStream *stream) {
	//if (cdIndex < 0 || cdIndex > 3)	{
	//	debugC(2, kLastExpressDebugScenes, "Scene::load - Invalid scene file index: %i", cdIndex);
	//	return false;
	//}

	//Common::String name(Common::String::printf("CD%iTRAIN.DAT", cdIndex));

	//// Get a stream for the background file
	//if (!_resource->hasFile(name)) {
	//	debugC(2, kLastExpressDebugScenes, "Scene::load - Error opening scene file: %s", name.c_str());
	//	return false;
	//}

	//debugC(2, kLastExpressDebugScenes, "=================================================================");
	//debugC(2, kLastExpressDebugScenes, "Loading scene data: %s", name.c_str());

	//Common::SeekableReadStream *stream = _resource->createReadStreamForMember(name);

	// Read the number of scenes (the first entry is a dummy one)
	stream->seek(9, SEEK_SET);
	uint32 numScenes = stream->readUint32LE();
	debugC(2, kLastExpressDebugScenes, "   found %d entries", numScenes);

	// Go to first scene
	stream->seek(24, SEEK_SET);

	// Read all the chunks
	for (uint32 i = 0; i < numScenes; ++i) {

		SceneEntry scene;

		stream->read(&scene.name, sizeof(scene.name));
		scene.sig = stream->readByte();
		scene.count = stream->readUint16LE();;
		scene.rect = (Common::Rect*)stream->readUint32LE();
		scene.eventType = stream->readByte();
		scene.unknown16 = stream->readByte();
		scene.unknown17 = stream->readByte();
		scene.unknown18 = stream->readByte();
		scene.unknown19 = stream->readByte();
		scene.unknown20 = stream->readByte();
		scene.unknown21 = stream->readByte();
		scene.unknown22 = stream->readByte();
		scene.unknown23 = stream->readByte();

		_scenes.push_back(scene);

		debugC(9, kLastExpressDebugScenes, "\n    Scene: name=%s, sig=%02d, count=%d, Rect=%d", scene.name, scene.sig, scene.count, scene.rect);
		debugC(9, kLastExpressDebugScenes, "           evt=%02d, unk16=%02d, unk17=%02d, unk18=%02d", scene.eventType, scene.unknown16, scene.unknown17, scene.unknown18);
		debugC(9, kLastExpressDebugScenes, "           unk19=%02d, unk20=%02d, unk21=%02d, unk22=%02d, unk23=%02d", scene.unknown19, scene.unknown20, scene.unknown21, scene.unknown22, scene.unknown23);
	}

	delete stream;

	return true;
}

Scene::SceneEntry* Scene::getEntry(uint sceneIndex) {
	if (_scenes.empty())
		return NULL;

	if (sceneIndex < 0 || sceneIndex > _scenes.size())
		return NULL;

	return &_scenes[sceneIndex];
}

} // End of namespace LastExpress
