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
	    byte {1}    - camera position (used to get the proper sequences to show)
	    byte {1}    - type
	    byte {1}    - param1
	    byte {1}    - param2
	    byte {1}    - param3
	    uint32 {4}  - Offset to hotspot info struct

	    probably contains cursor type too / scene index : 0 - 2500 (max)

	hotspot info (24 bytes)
	    uint16 {2}  - left
	    uint16 {2}  - right
	    uint16 {2}  - top
	    uint16 {2}  - bottom
	    uint16 {2}  - scene coords data
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

	coords data (9 bytes)
	    uint32 {4}    - ??
	    uint32 {4}    - ??
	    byte {1}       - ??
	   uint32 {4}     - offset to next coords data structure

*/

#include "lastexpress/drawable.h"

#include "common/array.h"
#include "common/stream.h"

namespace LastExpress {

class SceneHeader {
public:
	static SceneHeader *load(Common::SeekableReadStream *stream);

private:
	SceneHeader() {}

public:
	char name[8];
	byte sig;
	uint16 count;
	uint16 field_11;
	uint16 field_13;
	byte position;
	byte type;
	byte param1;
	byte param2;
	byte param3;
	uint32 hotspot;
};

class SceneHotspot {
public:
	enum Action {
		kActionInventory = 1,
		kActionSavePoint = 2,
		kActionPlaySound = 3,
		kActionPlayMusic = 4,
		kActionKnockOnDoor = 5,
		kActionCompartment = 6,
		kActionPlaySounds = 7,
		kActionPlayAnimation = 8,
		kActionOpenCloseObject = 9,
		kAction10 = 10,
		kActionSetItemLocation = 11,
		kAction12 = 12,
		kActionPickItem = 13,
		kActionDropItem = 14,
		kAction15 = 15,
		kActionEnterCompartment = 16,
		kActionGetOutsideTrain = 18,
		kActionSlip = 19,
		kActionGetInsideTrain = 20,
		kActionClimbUpTrain = 21,
		kActionClimbDownTrain = 22,
		kActionJumpUpDownTrain = 23,
		kActionUnbound = 24,
		kAction25 = 25,
		kAction26 = 26,
		kAction27 = 27,
		kActionConcertSitCough = 28,
		kAction29 = 29,
		kActionCatchBeetle = 30,
		kActionExitCompartment = 31,
		kAction32 = 32,
		KActionUseWhistle = 33,
		kActionOpenMatchBox = 34,
		kActionOpenBed = 35,
		kActionDialog = 37,
		kActionEggBox = 38,
		kAction39 = 39,
		kActionBed = 40,
		kAction41 = 41,
		kAction42 = 42,
		kActionSwitchChapter = 43,
		kAction44 = 44
	};

	struct SceneCoord {
		uint32 field_0;
		uint32 field_4;
		byte field_8;
		uint32 next;
	};

	Common::Rect rect;
	uint16 coord;
	uint16 unknownA;
	uint16 scene;
	byte location;
	byte action;
	byte param1;
	byte param2;
	byte param3;
	byte cursor;
	uint32 next;

	SceneHotspot() {}
	static SceneHotspot *load(Common::SeekableReadStream *stream);

	bool isInside(const Common::Point &point);

private:
	Common::Array<SceneCoord *> _coords;
};

class Scene : public Drawable {
public:

	// Scenes
	enum Type {
		// PreProcess
		kTypeEntity = 1,
		kTypeItem = 2,
		kTypeItem2 = 3,
		kTypeEntityItem = 4,
		kTypeItem3 = 5,
		kType6 = 6,
		kType7 = 7,
		kType8 = 8,

		// PostProcess
		kTypeList = 128,
		kTypeSavePointChapter = 129,
		kTypeLoadBeetleSequences = 130,
		kTypeGameOver = 131,
		kTypeReadText = 132,
		kType133 = 133
	};

	Scene();
	~Scene();

	static bool load(Scene *scene, Common::SeekableReadStream *stream, SceneHeader *header);
	static Scene *get(Common::SeekableReadStream *stream, SceneHeader *header);

	bool checkHotSpot(const Common::Point &coord, SceneHotspot **hotspot);
	Common::Rect draw(Graphics::Surface *surface);

	SceneHeader* getHeader();
	Common::Array<SceneHotspot *> *getHotspots() { return &_hotspots; }
	SceneHotspot *getHotspot(uint index = 0);

private:
	SceneHeader *_header;
	Common::Array<SceneHotspot *> _hotspots;

	void clear();
};

class SceneManager {
public:
	SceneManager();
	~SceneManager();

	bool load(Common::SeekableReadStream *stream);
	Scene *getScene(int index);
	bool loadScene(Scene *scene, int index);

private:
	Common::SeekableReadStream *_stream;
	Common::Array<SceneHeader *> _headers;

	void clear();
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SCENE_H
