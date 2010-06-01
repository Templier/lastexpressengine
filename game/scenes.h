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

namespace LastExpress {

class LastExpressEngine;
class SceneLoader;
class Sequence;

class SceneManager {
public:
	enum CheckPositionType {
		kCheckPositionType0,
		kCheckPositionType1,
		kCheckPositionType2
	};

	SceneManager(LastExpressEngine *engine);
	~SceneManager();

	// Datafile
	void loadSceneDataFile(ArchiveIndex archive) const;

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
	bool checkPosition(SceneIndex sceneIndex, CheckPositionType kCheckPositionType0) const;
	bool checkCurrentPosition(bool doCheckOtherCars) const;

	// Train
	void updateTrain();
	void resetTrain();

	// Helpers
	bool loadScene(Scene * const scene, SceneIndex sceneIndex);	
	Scene *getScene(SceneIndex sceneIndex);
	Scene *getCurrentScene() { return _currentScene; }
	SceneIndex getSceneIndexFromPosition(CarIndex car, Position position, int param3 = -1);

private:
	LastExpressEngine *_engine;

	SceneLoader       *_sceneLoader;  ///< Scene loader
	Scene             *_currentScene;    ///< Current scene

	// Flags
	bool _flagNoEntity;
	bool _flagDrawEntities;			

	// Train sequences
	Sequence *_clockHours;
	Sequence *_clockMinutes;
	Common::Array<Sequence *> _doors;

	// Scene processing		
	void preProcessScene(SceneIndex *index);
	void postProcessScene();	
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SCENEMANAGER_H
