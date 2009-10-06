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

#include "lastexpress/lastexpress.h"
#include "lastexpress/saveload.h"

namespace LastExpress {

class Sequence;

class Logic {
private:
	// Start menu events
	enum StartMenuEvent {
		kCase1 = 1,
		kCredits = 2,
		kQuit = 3,
		kCase4 = 4,
		kSwitchSaveGame = 6,
		kRewind = 7,
		kFastForward = 8,
		kParis = 10,
		kStrastBourg = 11,
		kMunich = 12,
		kVienna = 13,
		kBudapest = 14,
		kBelgrade = 15,
		kEnding = 16,
		kVolumeDown = 17,
		kVolumeUp = 18,
		kBrightnessDown = 19,
		kBrightnessUp = 20
	};

	// Tooltips sequence (helpnewr.seq)
	enum StartMenuTooltips {
		kInsertCd1,
		kInsertCd2,
		kIsertCd3,
		kContinueGame,
		kReplayGame,
		kPlayRewoundGame,
		kViewGameEnding,
		kStartAnotherGame,
		kVolumeUp,
		kVolumeDown,
		kBrightnessUp,
		kBrightnessDown,
		kQuit,
		kRewindParis,
		kFastForwardStrasbourg,
		kRewindStrasbourg,
		kRewindMunich,
		kFastForwardMunich,		
		kFastForwardVienna,
		kRewindVienna,
		kRewindBudapest,
		kFastForwardBudapest,
		kFastForwardBelgrade,
		kRewindBelgrade,
		kFastForwardEnding,
		kSwitchBlueGame,
		kSwitchRedGame,
		kSwitchGoldGame,
		kSwitchGreenGame,
		kSwitchTealGame,
		kSwitchPurpleGame,
		kPlayNewGame,
		kCredits,
		kFastForward,
		kRewind
	};

	enum StartMenuButtons {
		kVolumeDownPushed,
		kVolumeDown,
		kVolume,
		kVolumeUp,
		kVolumeUpPushed,
		kBrightnessDownPushed,
		kBrightnessDown,
		kBrightness,
		kBrightnessUp,
		kBrightnessUpPushed,
		kQuit,
		kQuitPushed
	};

	// State
	struct RunState {
		bool hasShownIntro;
		bool hasShownStartScreen;

		RunState() {
			hasShownIntro = false;
			hasShownStartScreen = false;
		}
	};


public:
	Logic(LastExpressEngine *engine);
	~Logic();

	void showMainMenu();
	

	// TODO inventory (needs gamestate & new Cursor function)

private:
	LastExpressEngine *_engine;

	RunState *_runState;	//<! State of the game session (this data won't be stored in savegames)

	// Savegames	
	SaveLoad::SavegameId _savegameId;
	SaveLoad::GameState _gameState;

	// Helper functions
	Sequence* getAcornHighlight(SaveLoad::SavegameId id);
	bool HandleStartMenuEvent(StartMenuEvent event, byte clickStatus);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_LOGIC_H