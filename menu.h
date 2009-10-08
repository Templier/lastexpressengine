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

#ifndef LASTEXPRESS_MENU_H
#define LASTEXPRESS_MENU_H

#include "lastexpress/saveload.h"

namespace LastExpress {

class LastExpressEngine;
class Sequence;

class Menu {
public:
	// Start menu events
	enum StartMenuEvent {
		kEventCase1 = 1,
		kEventCredits = 2,
		kEventQuitGame = 3,
		kEventCase4 = 4,
		kEventSwitchSaveGame = 6,
		kEventRewindGame = 7,
		kEventFastForwardGame = 8,
		kEventParis = 10,
		kEventStrasBourg = 11,
		kEventMunich = 12,
		kEventVienna = 13,
		kEventBudapest = 14,
		kEventBelgrade = 15,
		kEventEnding = 16,
		kEventDecreaseVolume = 17,
		kEventIncreaseVolume = 18,
		kEventDecreaseBrightness = 19,
		kEventIncreaseBrightness = 20
	};

	Menu(LastExpressEngine *engine);
	~Menu();

	void showMenu();
	bool handleStartMenuEvent(StartMenuEvent event, bool clicked);

private:

	// Tooltips sequence (helpnewr.seq)
	enum StartMenuTooltips {
		kTooltipInsertCd1,
		kTooltipInsertCd2,
		kTooltipInsertCd3,
		kTooltipContinueGame,
		kTooltipReplayGame,
		kTooltipPlayRewoundGame,
		kTooltipViewGameEnding,
		kTooltipStartAnotherGame,
		kTooltipVolumeUp,
		kTooltipVolumeDown,
		kTooltipBrightnessUp,	// 10
		kTooltipBrightnessDown,
		kTooltipQuit,
		kTooltipRewindParis,
		kTooltipFastForwardStrasbourg,
		kTooltipRewindStrasbourg,
		kTooltipRewindMunich,
		kTooltipFastForwardMunich,
		kTooltipFastForwardVienna,
		kTooltipRewindVienna,
		kTooltipRewindBudapest,	// 20
		kTooltipFastForwardBudapest,
		kTooltipFastForwardBelgrade,
		kTooltipRewindBelgrade,
		kTooltipFastForwardEnding,
		kTooltipSwitchBlueGame,
		kTooltipSwitchRedGame,
		kTooltipSwitchGoldGame,
		kTooltipSwitchGreenGame,
		kTooltipSwitchTealGame,
		kTooltipSwitchPurpleGame, // 30
		kTooltipPlayNewGame,
		kTooltipCredits,
		kTooltipFastForward,
		kTooltipRewind
	};

	enum StartMenuButtons {
		kButtonVolumeDownPushed,
		kButtonVolumeDown,
		kButtonVolume,
		kButtonVolumeUp,
		kButtonVolumeUpPushed,
		kButtonBrightnessDownPushed,
		kButtonBrightnessDown,
		kButtonBrightness,
		kButtonBrightnessUp,
		kButtonBrightnessUpPushed,
		kButtonQuit,
		kButtonQuitPushed
	};

	enum StartMenuOverlayType {
		kOverlayTooltip,
		kOverlay1,
		kOverlayButtons,
		kOverlay3,
		kOverlay4,
		kOverlay5,
		kOverlay6,
		kOverlay7
	};

	LastExpressEngine *_engine;

	// Indicator to know if we need to show the animation when showMenu is called	
	bool _showStartScreen;

	void loadSequences();
	Common::String getAcornHighlight(SaveLoad::SavegameId id);

	// Overlays & elements
	void hideAllOverlays();
	void hideOverlay(StartMenuOverlayType type);
	void drawTrainLine();
	void drawClock();

	// Sound-related
	void playClickSnd();
	int getVolume();
	void setVolume(int volume);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_MENU_H