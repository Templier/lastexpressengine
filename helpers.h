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

#ifndef LASTEXPRESS_HELPERS_H
#define LASTEXPRESS_HELPERS_H

//////////////////////////////////////////////////////////////////////////
// Misc helpers
//////////////////////////////////////////////////////////////////////////
// Engine subclasses
#define getLogic() _engine->getGameLogic()

// Logic
#define getAction() getLogic()->getGameAction()
#define getBeetle() getLogic()->getGameBeetle()
#define getFight() getLogic()->getGameFight()
#define getEntities() getLogic()->getGameEntities()
#define getSaveLoad() getLogic()->getGameSaveLoad()

// State
#define getState() getLogic()->getGameState()->getGameState()
#define getEvent(id) getState()->events[id]
#define getFlags() getLogic()->getGameState()->getGameFlags()
#define getInventory() getLogic()->getGameState()->getGameInventory()
#define getObjects() getLogic()->getGameState()->getGameObjects()
#define getProgress() getState()->progress
#define getSavePoints() getLogic()->getGameState()->getGameSavePoints()
#define getGlobalTimer() getLogic()->getGameState()->getTimer()
#define setGlobalTimer(timer) getLogic()->getGameState()->setTimer(timer)
#define getCoords() getLogic()->getGameState()->getCoordinates()

// Misc
#define getEntityData(entity) getEntities()->getData(entity)

// Scenes
#define getScenes() _engine->getSceneManager()
#define loadSceneObject(name, sceneId) Scene name; getScenes()->loadScene(&name, (SceneIndex)sceneId);

// Utilities
#define getSound() _engine->getSoundManager()
#define playMusicStream(name) getSound()->getMusicStream()->load(_engine->getResourceManager()->getFileStream(name));
#define playSfxStream(name) getSound()->getSfxStream()->load(_engine->getResourceManager()->getFileStream(Common::String(name)));

#define loadFile(name) load(_engine->getResourceManager()->getFileStream(name))

// Misc
#define save(entity, type, event) getSaveLoad()->saveGame(type, entity, event)
#define random(value) _engine->getRandom().getRandomNumber(value - 1)
#define isDay() getLogic()->getGameState()->isDayTime()

//////////////////////////////////////////////////////////////////////////
// Graphics
//////////////////////////////////////////////////////////////////////////

// Sequences
#define newSequence(name) new Sequence(_engine->getResourceManager()->getFileStream(name))
#define drawSequenceFrame(drawable, index, type) { \
	AnimFrame *frame = (drawable)->getFrame((index)); \
	_engine->getGraphicsManager()->draw((frame), (type)); \
	delete frame; }

#define clearBg(type) _engine->getGraphicsManager()->clear(type)
#define showScene(index, type) { loadSceneObject(s, index); _engine->getGraphicsManager()->draw(&s, type); }

#define askForRedraw() _engine->getGraphicsManager()->change();
#define redrawScreen() _engine->getGraphicsManager()->update(); _engine->_system->updateScreen();

// Used to delete entity sequences
#define SAFE_DELETE(_p) { if(_p) { delete _p; _p=NULL; } }

#endif // LASTEXPRESS_HELPERS_H
