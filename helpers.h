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
#define loadFile(name) load(_engine->getResMan()->getFileStream(name))
#define playMusic(name) _engine->getMusicStream()->load(_engine->getResMan()->getFileStream(name));
#define playSfx(name) _engine->getSfxStream()->load(_engine->getResMan()->getFileStream(name));

// Logic subclasses
#define getProgress() _engine->getLogic()->getGameState()->progress

//////////////////////////////////////////////////////////////////////////
// Graphics
//////////////////////////////////////////////////////////////////////////
#define clearBg(type) _engine->getGraphicsManager()->clear(type)
#define showScene(index, type) { Scene *s = _engine->getScene(index); _engine->getGraphicsManager()->draw(s, type); delete s; }

#define askForRedraw() _engine->getGraphicsManager()->change();
#define redrawScreen() _engine->getGraphicsManager()->update(); _engine->_system->updateScreen();

#endif // LASTEXPRESS_HELPERS_H
