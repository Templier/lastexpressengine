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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef LASTEXPRESS_SCENEMANAGER_H
#define LASTEXPRESS_SCENEMANAGER_H

#include "lastexpress/data/scene.h"

#include "common/hashmap.h"
#include "common/hash-str.h"
#include "common/list.h"

namespace LastExpress {

class LastExpressEngine;
class SceneLoader;
class Sequence;
class SequenceFrame;

class SceneManager {
public:
	enum CheckPositionType {
		kCheckPositionType0,
		kCheckPositionType1,
		kCheckPositionLookingAtDoors,
		kCheckPositionLookingAtClock
	};

	SceneManager(LastExpressEngine *engine);
	~SceneManager();

	
	// Datafile
	void loadSceneDataFile(ArchiveIndex archive);

	// Scene cache
	Scene *get(SceneIndex sceneIndex);

	// Scene loading
	void setScene(SceneIndex sceneIndex);
	void loadScene(SceneIndex sceneIndex);
	void loadSceneFromObject(ObjectIndex object, bool alternate = false);
	void loadSceneFromItem(InventoryItem item);
	void loadSceneFromItemPosition(InventoryItem item);
	void loadSceneFromPosition(CarIndex car, Position position, int param3 = -1);

	// Scene drawing & processing
	void drawScene(SceneIndex sceneIndex);
	void processScene();
	SceneIndex processIndex(SceneIndex sceneIndex);

	// Checks
	bool checkPosition(SceneIndex sceneIndex, CheckPositionType type) const;
	bool checkCurrentPosition(bool doCheckOtherCars) const;

	// Train
	void updateDoorsAndClock();
	void resetDoorsAndClock();

	// Sequence queue
	void drawFrames(bool refreshScreen);
	void addToQueue(SequenceFrame *frame);
	void removeFromQueue(SequenceFrame *frame);
	void removeAndRedraw(SequenceFrame *frame, bool doRedraw);
	void resetQueue();
	void setCoordinates(SequenceFrame *frame);

	// Helpers
	SceneIndex getSceneIndexFromPosition(CarIndex car, Position position, int param3 = -1);

	void setFlagDrawSequences() { _flagDrawSequences = true; }

private:
	struct SceneCache_EqualTo {
		bool operator()(const SceneIndex& x, const SceneIndex& y) const { return x == y; }
	};

	struct SceneCache_Hash {
		uint operator()(const SceneIndex& x) const { return x; }
	};

	typedef Common::HashMap<SceneIndex, Scene *, SceneCache_Hash, SceneCache_EqualTo> SceneCache;

	LastExpressEngine *_engine;

	SceneLoader       *_sceneLoader;     ///< Scene loader
	Scene             *_currentScene;    ///< Current scene

	Common::Rect coordinates;

	// Flags
	bool _flagNoEntity;
	bool _flagDrawEntities;
	bool _flagDrawSequences;
	bool _flagCoordinates;

	// Scene cache
	SceneCache _scenes;
	void purgeSceneCache();

	// Train sequences
	Common::Array<Sequence *> _doors;

	Sequence *_clockHours;
	Sequence *_clockMinutes;

	uint _hoursIndex;
	uint _minutesIndex;

	// Sequence queue
	Common::List<SequenceFrame *> _queue;

	// Scene processing
	void preProcessScene(SceneIndex *index);
	void postProcessScene();
	
	
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SCENEMANAGER_H
