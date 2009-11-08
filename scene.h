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

#ifndef LASTEXPRESS_SCENE_H
#define LASTEXPRESS_SCENE_H

/*
	Scene format (CDTRAIN.DAT)

	(text:00484750)
	header (24 bytes)
		char {8}    - entry name (null terminated)
		byte {1}    - 0xCD
		uint16 {2}  - number of scenes (for first entry - always 0 after?)
		uint16 {2}  - 11 ??
		uint16 {2}  - 13 ??
		byte {1}    - 15 ??
		byte {1}    - type
		byte {1}    - param1
		byte {1}    - param2
		byte {1}    - 19 ?? (do something if set to -1)
		uint32 {4}  - Offset to hotspot info struct

		probably contains cursor type too / scene index : 0 - 2500 (max)

	hotspot info (24 bytes)
		uint16 {2}  - left
		uint16 {2}  - right
		uint16 {2}  - top
		uint16 {2}  - bottom
		uint16 {2}  - offset to another struct
		uint16 {2}  - unknownA
		uint16 {2}  - scene
		byte {1}    - location;
		byte {1}    - action;
		byte {1}    - param1;
		byte {1}    - param2;
		byte {1}    - param3
		byte {1}    - cursor
		uint16 {2}  - offset to next hotpost
		uint16 {2}  - unknown16

	??? (9 bytes)
		byte {1}
		byte {1}
		byte {1}
		byte {1}
		byte {1}
		byte {1}
		byte {1}
		byte {1}
		byte {1}

*/

#include "lastexpress/drawable.h"

#include "common/stream.h"

namespace LastExpress {

class SceneHeader {
public:
	static SceneHeader *load(Common::SeekableReadStream *stream);

private:
	SceneHeader() {}

public: // XXX
	char name[8];
	byte sig;
	uint16 count;
	uint16 field_11;
	uint16 field_13;
	byte field_15;
	byte type;
	byte param1;
	byte param2;
	byte field_19;
	uint32 hotspot;
};

class SceneHotspot {
public:
	SceneHotspot() {}
	static SceneHotspot *load(Common::SeekableReadStream *stream);

public:
	Common::Rect rect;
	uint16 offset;
	uint16 unknownA;
	uint16 scene;
	byte location;
	byte action;
	byte param1;
	byte param2;	
	byte param3;
	byte cursor;
	uint32 next;
};

class Scene : public Drawable {
public:
	~Scene();

	static Scene *load(Common::SeekableReadStream *stream, SceneHeader *header);
	bool checkHotSpot(Common::Point coord, SceneHotspot **hotspot);
	Common::Rect draw(Graphics::Surface *surface);

	SceneHeader* getHeader() { return _header; }
	Common::Array<SceneHotspot *> *getHotspots() { return &_hotspots; }
	SceneHotspot *getHotspot(int index) { return _hotspots[index]; }

private:
	Scene(SceneHeader *header) : _header(header) {}

	SceneHeader *_header;
	Common::Array<SceneHotspot *> _hotspots;
};

class SceneManager {
public:
	SceneManager();
	~SceneManager();

	bool load(Common::SeekableReadStream *stream);
	Scene *getScene(uint16 index);

private:
	Common::SeekableReadStream *_stream;
	Common::Array<SceneHeader *> _headers;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SCENE_H
