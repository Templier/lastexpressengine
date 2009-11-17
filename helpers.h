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
// Logic subclasses
#define getSound() _engine->getLogic()->getGameSound()
#define getEntities() _engine->getLogic()->getGameEntities()
#define getEvent(id) getState()->events[id]
#define getObjects() _engine->getLogic()->getGameObjects()
#define getInventory() _engine->getLogic()->getGameInventory()
#define getProgress() getState()->progress
#define getSavePoints() _engine->getLogic()->getGameSavePoints()
#define getState() _engine->getLogic()->getGameState()

// Utilities
#define loadFile(name) load(_engine->getResMan()->getFileStream(name))
#define playMusicStream(name) _engine->getMusicStream()->load(_engine->getResMan()->getFileStream(name));
#define playSfxStream(name) _engine->getSfxStream()->load(_engine->getResMan()->getFileStream(Common::String(name) + ".snd"));
#define playEventSound(index, action, a3) _engine->getLogic()->getGameSound()->playSoundEvent(index, action, a3)
#define playDialog(id) playSfxStream(getSound()->getDialogName((Sound::DialogId)id))

// Misc
#define random(value) _engine->getRandom().getRandomNumber(value)

// Entities
#define getCallData() _data.callback_data[_data.current_call]

//////////////////////////////////////////////////////////////////////////
// Graphics
//////////////////////////////////////////////////////////////////////////
#define clearBg(type) _engine->getGraphicsManager()->clear(type)
#define showScene(index, type) { Scene *s = _engine->getScene(index); _engine->getGraphicsManager()->draw(s, type); delete s; }

#define askForRedraw() _engine->getGraphicsManager()->change();
#define redrawScreen() _engine->getGraphicsManager()->update(); _engine->_system->updateScreen();

#endif // LASTEXPRESS_HELPERS_H
