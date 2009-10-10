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

#include "common/system.h"

/*
	Scene format (CDTRAIN.DAT)

	(text:00484750)
	header (24 bytes)
		char {8}   - entry name (null terminated)
		byte {1}	- 0xCD
		uint16 {2}	- number of scenes (for first entry - always 0 after?)
		uint32 {4}  - pointer to RECT? (seems wrong!)
		byte {1}    - Event type (second part of sequence file name at some point)
		byte {1}    - ?? (see text:004067F0 - used as a switch value)
		byte {1}    - ??
		byte {1}    - ??
		byte {1}    - ??
		byte {1}    - ??
		byte {1}    - ??
		byte {1}    - ??
		byte {1}    - ??

		probably contains cursor type too

	scene index : 0 - 2500 (max)
*/

namespace LastExpress {

class Scene {
public:
	struct SceneEntry {
		char name[8];
		byte sig;
		uint16 count;
		Common::Rect* rect;
		byte eventType;
		byte unknown16;
		byte unknown17;
		byte unknown18;
		byte unknown19;
		byte unknown20;
		byte unknown21;
		byte unknown22;
		byte unknown23;

		SceneEntry() {
			strcpy((char*)&name, "");
			sig = 0;
			count = 0;
			rect = NULL;
			eventType = 0;
			unknown16 = 0;
			unknown17 = 0;
			unknown18 = 0;
			unknown19 = 0;
			unknown20 = 0;
			unknown21 = 0;
			unknown22 = 0;
			unknown23 = 0;
		}
	};

	Scene();
	~Scene();

	bool load(Common::SeekableReadStream *stream);
	SceneEntry* getEntry(uint sceneIndex);

private:
	Common::Array<SceneEntry> _scenes;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SCENE_H
