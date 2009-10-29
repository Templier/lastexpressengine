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
		byte {1}    - 16 ?? (see text:004067F0/740 - used as a switch value)
		byte {1}    - 17 ??
		byte {1}    - 18 ??
		byte {1}    - 19 ?? (do something if set to -1)
		uint16 {2}  - Offset to hotspot info struct
		byte {1}    - 22 ??
		byte {1}    - 23 ??

		probably contains cursor type too / scene index : 0 - 2500 (max)

	hotspot info (24 bytes)
		uint16 {2}  - left
		uint16 {2}  - right
		uint16 {2}  - top
		uint16 {2}  - bottom
		uint16 {2}  - offset to another struct
		uint16 {2}  - unknown10
		uint16 {2}  - unknown12
		byte {1}    - unknown14;
		byte {1}    - eventId;
		uint16 {2}  - unknown17
		uint16 {2}  - unknown19
		uint16 {2}  - unknown21
		uint16 {2}  - unknown23

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

class SceneHeader;
class SceneHotspot;

class Scene : public Drawable {
public:
	~Scene();

	static Scene *load(Common::SeekableReadStream *stream, SceneHeader *header);
	bool checkHotSpot(Common::Point coord, byte *eventId);
	Common::Rect draw(Graphics::Surface *surface);

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
	Scene *getScene(uint16 sceneIndex);

private:
	Common::SeekableReadStream *_stream;
	Common::Array<SceneHeader *> _headers;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SCENE_H
