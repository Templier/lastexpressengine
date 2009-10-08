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

#include "lastexpress/logic.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/menu.h"
#include "lastexpress/scene.h"

namespace LastExpress {

Logic::Logic(LastExpressEngine *engine) : _engine(engine) {
	_menu = new Menu(engine);

	// Get those from savegame
	_gameState = new SaveLoad::GameState();
}

Logic::~Logic() {
	if (_gameState)
		delete _gameState;	

	if (_menu)
		delete _menu;	
}

//////////////////////////////////////////////////////////////////////////
// Menu handling
//////////////////////////////////////////////////////////////////////////

// Show main menu
void Logic::showMenu() {
	// TODO: load scene and set current scene

	_menu->showMenu();
}

void Logic::handleMouseEvent(int16 x, int16 y, bool clicked) {
	if (_gameState->currentScene == 0)
		return;

	// FIXME: check hitbox & event from scene data

	// Special case for the main menu scene ??
	if (_gameState->currentScene == (uint32)getMenuSceneIndex(_runState.savegameId)) {
		Menu::StartMenuEvent evt = Menu::kEventDecreaseVolume;
				
		_menu->handleStartMenuEvent(evt, clicked);
	}
}

uint32 Logic::getMenuSceneIndex(SaveLoad::SavegameId savegameId) {
	// TODO Do check for DWORD at text:004ADF70 < 0x1030EC
	return (int)savegameId * 5 + 1; // or 2...
}

} // End of namespace LastExpress
