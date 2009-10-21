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

#ifndef LASTEXPRESS_LOGIC_H
#define LASTEXPRESS_LOGIC_H

#include "lastexpress/savegame.h"

#include "common/events.h"

namespace LastExpress {

class LastExpressEngine;
class Menu;

class Logic {
public:
	Logic(LastExpressEngine *engine);
	~Logic();

	void showMenu();
	bool handleMouseEvent(Common::Event ev);

	// TODO inventory (needs gamestate & new Cursor function)

	void switchGame();

	// Accessors
	bool isGameStarted() { return _runState.gameStarted; }
	SaveLoad::SavegameId getSavegameId() { return _runState.savegameId; }
	SaveLoad::GameState *getGameState() { return _gameState; }

private:
	// Scenes
	enum Scene {
		kSceneIntroScreen = 65
	};

	// State
	struct RunState {
		SaveLoad::SavegameId savegameId;
		bool gameStarted;

		RunState() {
			gameStarted = false;
			savegameId = SaveLoad::kSavegameBlue;
		}
	};

	LastExpressEngine *_engine;

	RunState _runState;		//<! State of the game session (this data won't be stored in savegames)
	Menu *_menu;			//<! Main menu handling

	// Move to engine?
	SaveLoad::GameState *_gameState;

};

} // End of namespace LastExpress

#endif // LASTEXPRESS_LOGIC_H
