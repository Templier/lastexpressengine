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

#include "lastexpress/savegame.h"
#include "lastexpress/sequence.h"

#include "common/events.h"

namespace LastExpress {

class LastExpressEngine;

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
		kEventForwardGame = 8,
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
	bool handleStartMenuEvent(Common::Event ev);

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
		kTooltipForwardStrasbourg,
		kTooltipRewindStrasbourg,
		kTooltipRewindMunich,
		kTooltipForwardMunich,
		kTooltipForwardVienna,
		kTooltipRewindVienna,
		kTooltipRewindBudapest,	// 20
		kTooltipForwardBudapest,
		kTooltipForwardBelgrade,
		kTooltipRewindBelgrade,
		kTooltipForwardEnding,
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

	// Bottom-left buttons (quit.seq)
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

	// Egg buttons (buttns.seq)
	enum StartMenuEggButtons {
		kButtonShield,
		kButtonRewind,
		kButtonRewindPushed,
		kButtonForward,
		kButtonForwardPushed,
		kButtonCredits,
		kButtonCreditsPushed,
		kButtonContinue
	};

	// Overlay on cities (jlinetl.seq - jlinecen.seq - jlinebr.seq)
	enum CityOverlay {
		kParis = 100,			// index on sequence is 0
		kStrasbourg = 0,
		kMunich = 1,
		kVienna = 2,
		kBudapest = 3,
		kBelgrade = 4,
		kEnding = 101			// index on sequence is 0
	};

	// Game time when the train is at a specific city
	enum CityTime {
		kTimeParis = 1037700,
		kTimeStrasbourg = 1490400,
		kTimeMunich = 1852200,
		kTimeVienna = 2268000,
		kTimeBudapest = 2551500,
		kTimeBelgrade = 2952000,
		kTimeEnding = 4941000
	};

	LastExpressEngine *_engine;

	// Sequences
	Sequence _seqHour;
	Sequence _seqMinutes;
	Sequence _seqSun;
	Sequence _seqDate;

	Sequence _seqTooltips;
	Sequence _seqEggButtons;
	Sequence _seqButtons;
	Sequence _seqLine1;
	Sequence _seqLine2;
	Sequence _seqCityStart;
	Sequence _seqCities;
	Sequence _seqCityEnd;

	// TODO might be loaded on-the-fly in the future
	Sequence _seqCredits;
	Sequence _seqAcorn;
	
	// Indicator to know if we need to show the start animation when showMenu is called	
	bool _showStartScreen;
	bool _isShowingCredits;
	uint32 _creditsSequenceIndex;

	void loadSequences();

	// Overlays & elements
	void drawTrainLine(uint32 time);
	void drawClock(uint32 time);
	void hideOverlays();
	Common::String getAcornHighlight(SaveLoad::SavegameId id);
	void showCredits();

	// Game time
	uint32 getCurrentTime();
	uint32 getMaxGameTime();
	void goToTime(uint32 time);
	void moveToCity(CityOverlay city, CityTime time, StartMenuTooltips tooltipRewind, StartMenuTooltips tooltipForward, bool clicked);
	
	// Sound/Brightness related
	int getVolume();
	void setVolume(int volume);
	int getBrightness();
	void setBrightness(int brightness);

};

} // End of namespace LastExpress

#endif // LASTEXPRESS_MENU_H