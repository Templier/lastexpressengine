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

#include "lastexpress/game/soundmanager.h"

#include "lastexpress/data/snd.h"

namespace LastExpress {

SoundManager::SoundManager(LastExpressEngine *engine) : _engine(engine) {
	_sfx = new StreamedSound();
	_music = new StreamedSound();
}

SoundManager::~SoundManager() {
	delete _sfx;
	delete _music;
}

void SoundManager::reset(EntityIndex entity) {
	error("SoundManager::reset: not implemented!");
}

bool SoundManager::isBuffered(EntityIndex entityIndex) {
	warning("SoundManager::isBuffered: not implemented!");
	return false;
}

bool SoundManager::isFileInQueue(const char* filename) {
	error("SoundManager::isFileInQueue: not implemented!");
}

void SoundManager::unknownFunction1() {
	error("SoundManager::unknownFunction1: not implemented!");
}

} // End of namespace LastExpress
