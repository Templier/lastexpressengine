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

#include "lastexpress/game/menu.h"

// Data
#include "lastexpress/data/animation.h"
#include "lastexpress/data/cursor.h"
#include "lastexpress/data/snd.h"
#include "lastexpress/data/scene.h"

#include "lastexpress/game/logic.h"
#include "lastexpress/game/soundmanager.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"
#include "lastexpress/savegame.h"

#define getNextGameId() (GameId)((getLogic()->getGameId() + 1) % 6)
#define drawSeqFrame(drawable, index, type) { \
	AnimFrame *frame = (drawable)->getFrame((index)); \
	_engine->getGraphicsManager()->draw((frame), (type)); \
	delete frame; }

namespace LastExpress {

// Start menu events
enum StartMenuAction {
	kActionContinue = 1,
	kActionCredits = 2,
	kActionQuitGame = 3,
	kActionCase4 = 4,
	kActionSwitchSaveGame = 6,
	kActionRewindGame = 7,
	kActionForwardGame = 8,
	kActionParis = 10,
	kActionStrasBourg = 11,
	kActionMunich = 12,
	kActionVienna = 13,
	kActionBudapest = 14,
	kActionBelgrade = 15,
	kActionConstantinople = 16,
	kActionDecreaseVolume = 17,
	kActionIncreaseVolume = 18,
	kActionDecreaseBrightness = 19,
	kActionIncreaseBrightness = 20
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

// Tooltips sequence (helpnewr.seq)
enum StartMenuTooltips {
	kTooltipInsertCd1,
	kTooltipInsertCd2,
	kTooltipInsertCd3,
	kTooltipContinueGame,
	kTooltipReplayGame,
	kTooltipContinueRewoundGame,
	kTooltipViewGameEnding,
	kTooltipStartAnotherGame,
	kTooltipVolumeUp,
	kTooltipVolumeDown,
	kTooltipBrightnessUp,     // 10
	kTooltipBrightnessDown,
	kTooltipQuit,
	kTooltipRewindParis,
	kTooltipForwardStrasbourg,
	kTooltipRewindStrasbourg,
	kTooltipRewindMunich,
	kTooltipForwardMunich,
	kTooltipForwardVienna,
	kTooltipRewindVienna,
	kTooltipRewindBudapest,   // 20
	kTooltipForwardBudapest,
	kTooltipForwardBelgrade,
	kTooltipRewindBelgrade,
	kTooltipForwardConstantinople,
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

//////////////////////////////////////////////////////////////////////////
// DATA
//////////////////////////////////////////////////////////////////////////

// Information about the cities on the train line
const static struct {
	uint8 frame;
	uint32 time;
} trainCities[31] = {
	{0, 1037700}, // Paris
	{9, 1148400}, // Epernay
	{11, 1170900}, // Chalons
	{16, 1228500}, // Bar Le Duc
	{21, 1303200}, // Nancy
	{25, 1335600}, // Luneville
	{35, 1359900}, // Avricourt
	{37, 1367100}, // Deutsch Avricourt
	{40, 1490400}, // Strasbourg
	{53, 1539000}, // Baden Oos
	{56, 1563300}, // Karlsruhe
	{60, 1656000}, // Stuttgart
	{63, 1713600}, // Geislingen
	{66, 1739700}, // Ulm
	{68, 1809900}, // Augsburg
	{73, 1852200}, // Munich
	{84, 1984500}, // Salzbourg
	{89, 2049300}, // Attnang-Puchheim
	{97, 2075400}, // Wels
	{100, 2101500}, // Linz
	{104, 2154600}, // Amstetten
	{111, 2268000}, // Vienna
	{120, 2383200}, // Poszony
	{124, 2418300}, // Galanta
	{132, 2551500}, // Budapest
	{148, 2952000}, // Belgrade
	/* Line 1 ends at 150 - line 2 begins at 0 */
	{157, 3205800}, // Nish
	{165, 3492000}, // Tzaribrod
	{174, 3690000}, // Sofia
	{198, 4320900}, // Adrianople
	{210, 4941000}}; // Constantinople

const static struct {
	uint32 time;
	StartMenuTooltips rewind;
	StartMenuTooltips forward;
} cityButtonsInfo[7] = {
	{1037700, kTooltipRewindParis, kTooltipRewindParis},
	{1490400, kTooltipRewindStrasbourg, kTooltipForwardStrasbourg},
	{1852200, kTooltipRewindMunich, kTooltipForwardMunich},
	{2268000, kTooltipRewindVienna, kTooltipForwardVienna},
	{2551500, kTooltipRewindBudapest, kTooltipForwardBudapest},
	{2952000, kTooltipRewindBelgrade, kTooltipForwardBelgrade},
	{4941000, kTooltipForwardConstantinople, kTooltipForwardConstantinople}
};


// Menu elements

// Clock

class Clock : public Drawable {
public:
	Clock(LastExpressEngine *engine, uint32 *time);
	~Clock();

	bool load();
	bool process();
	Common::Rect draw(Graphics::Surface *surface);

private:
	LastExpressEngine *_engine;

	uint32 *_time;
	SequencePlayer *_seqHour;
	SequencePlayer *_seqMinutes;
	SequencePlayer *_seqSun;
	SequencePlayer *_seqDate;
};

Clock::Clock(LastExpressEngine *engine, uint32 *time) : _engine(engine), _time(time),
	_seqHour(NULL), _seqMinutes(NULL), _seqSun(NULL), _seqDate(NULL) {}

Clock::~Clock() {
	delete _seqHour;
	delete _seqMinutes;
	delete _seqSun;
	delete _seqDate;
}

bool Clock::load() {
	bool loaded = true;
	Sequence *s = new Sequence;
	loaded &= s->loadFile("egghour.seq");
	_seqHour = new SequencePlayer(s);

	s = new Sequence;
	loaded &= s->loadFile("eggmin.seq");
	_seqMinutes = new SequencePlayer(s);

	s = new Sequence;
	loaded &= s->loadFile("sun.seq");
	_seqSun = new SequencePlayer(s);

	s = new Sequence;
	loaded &= s->loadFile("datenew.seq");
	_seqDate = new SequencePlayer(s);

	return loaded;
}

bool Clock::process() {
	assert(*_time >= 1037700 && *_time <= 4941000);
	// Game starts at: 1037700 = 7:13 p.m. on July 24, 1914
	// Game ends at:   4941000 = 7:30 p.m. on July 26, 1914
	// Game lasts for: 3903300 = 2 days + 17 mins = 2897 mins

	// 15 = 1 second
	// 15 * 60 = 900 = 1 minute
	// 900 * 60 = 54000 = 1 hour
	// 54000 * 24 = 1296000 = 1 day

	// Calculate each sequence index from the current time
	uint8 hour = (uint8)((*_time % 1296000) / 54000);
	uint8 minute =  (uint8)((*_time % 54000) / 900);
	_seqMinutes->setFrame(minute);
	_seqHour->setFrame((5 * hour + minute / 12) % 60);
	_seqSun->setFrame((5 * hour + minute / 12) % 120);

	// TODO: verify index_date (60 frames)
	//uint8 day = *_time / 1296000;
	uint32 index_date = 18 * *_time / 1296000;
	if (hour == 23)
		index_date += 18 * minute / 60;
	_seqDate->setFrame(index_date);

	//warning("%02d:%02d on July %d", hour, minute, day + 24);

	return true;
}

// Draw the clock hands at the time
Common::Rect Clock::draw(Graphics::Surface *surface) {
	// Draw each element
	_seqHour->draw(surface);
	_seqMinutes->draw(surface);
	_seqSun->draw(surface);
	_seqDate->draw(surface);

	return Common::Rect();
}


// TrainLine

class TrainLine : public Drawable {
public:
	TrainLine(LastExpressEngine *engine, uint32 *time);
	~TrainLine();

	bool load();
	bool process();
	Common::Rect draw(Graphics::Surface *surface);

private:
	LastExpressEngine *_engine;

	uint32 *_time;
	SequencePlayer *_seqLine1;
	SequencePlayer *_seqLine2;
	bool _line2Visible;
};

TrainLine::TrainLine(LastExpressEngine *engine, uint32 *time) : _engine(engine),
	_time(time), _seqLine1(NULL), _seqLine2(NULL), _line2Visible(false) {}

TrainLine::~TrainLine() {
	delete _seqLine1;
	delete _seqLine2;
}

bool TrainLine::load() {
	bool loaded = true;
	Sequence *s = new Sequence;
	loaded &= s->loadFile("line1.seq");
	_seqLine1 = new SequencePlayer(s);

	s = new Sequence;
	loaded &= s->loadFile("line2.seq");
	_seqLine2 = new SequencePlayer(s);

	return loaded;
}

// Draw the train line at the time
//  line1: 150 frames (=> Belgrade)
//  line2: 61 frames (=> Constantinople)
// text:0042E710
bool TrainLine::process() {
	assert(*_time >= 1037700 && *_time <= 4941000);

	// Get the index of the last city the train has visited
	uint index = 0;
	for (uint i = 0; i < ARRAYSIZE(trainCities); i++)
		if (trainCities[i].time <= *_time)
			index = i;

	uint16 frame;
	if (*_time > trainCities[index].time) {
		// Interpolate linearly to use a frame between the cities
		uint8 diffFrames = trainCities[index + 1].frame - trainCities[index].frame;
		uint diffTimeCities = (trainCities[index + 1].time - trainCities[index].time);
		uint traveledTime = (*_time - trainCities[index].time);
		frame = (uint16)(trainCities[index].frame + (traveledTime * diffFrames) / diffTimeCities);
	} else {
		// Exactly on the city
		frame = trainCities[index].frame;
	}

	if (frame < 150) {
		_seqLine1->setFrame(frame);
		_line2Visible = false;
	} else {
		// We passed Belgrade
		_seqLine1->setFrame(149);
		_seqLine2->setFrame(frame - 150);
		_line2Visible = true;
	}

	return true;
}

Common::Rect TrainLine::draw(Graphics::Surface *surface) {
	// Draw each element
	_seqLine1->draw(surface);
	if (_line2Visible)
		_seqLine2->draw(surface);

	return Common::Rect();
}


//////////////////////////////////////////////////////////////////////////

Menu::Menu(LastExpressEngine *engine) : _engine(engine), _clock(NULL), _trainLine(NULL) {
	_showStartScreen = true;
	_creditsSequenceIndex = 0;
	_isShowingCredits = false;
	for (int i = 0; i < 7; i++)
		_cityButtonFrames[i] = NULL;

	_clock = new Clock(_engine, &_currentTime);
	_clock->load();
	_trainLine = new TrainLine(_engine, &_currentTime);
	_trainLine->load();
}

Menu::~Menu() {
	delete _clock;
	delete _trainLine;
	for (int i = 0; i < 7; i++)
		delete _cityButtonFrames[i];
}

// Show the intro and load the main menu scene
//
// The main menu screen is a background plus 8 overlay elements
// .text:00448590 (EN)
void Menu::showMenu() {
	// TODO: need to ask graphics manager to transition between current screen and menu
	_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundAll);

	// Load all menu-related data
	loadData();

	// If no blue savegame exists, this might be the first time we start the game, so we show the full intro
	if (_showStartScreen) {
		_engine->getCursor()->show(false);
		if (!SaveLoad::isSavegameValid(kGameBlue)) {
			Animation animation;

			// Show Broderbrund logo
			if (animation.loadFile("1930.nis"))
				animation.play();

			// Play intro music
			playMusicStream("MUS001.SND");

			// Show The Smoking Car logo
			if (animation.loadFile("1931.nis"))
				animation.play();

			_showStartScreen = false;
		} else {
			playMusicStream("mus018.snd");

			showScene(kSceneMenu, GraphicsManager::kBackgroundC);
			askForRedraw(); redrawScreen();
			//_engine->_system->delayMillis(1000);

			_showStartScreen = false;
		}
	}

	// Set Cursor type
	_engine->getCursor()->setStyle(kCursorNormal);
	_engine->getCursor()->show(true);

	// Init time
	_currentTime = getState()->time;

	// Load main scene
	_scene = getSceneObject(getSceneIndex());
	_engine->getGraphicsManager()->draw(_scene, GraphicsManager::kBackgroundC);
	drawElements();

	askForRedraw();
}

// Get menu scene index
uint32 Menu::getSceneIndex() {
	// TODO Do check for DWORD at text:004ADF70 < 0x1030EC

	// + 1 = normal menu with open egg / clock
	// + 2 = shield menu, when no savegame exists (no game has been started)
	return (SaveLoad::isSavegameValid(getLogic()->getGameId())) ? getLogic()->getGameId() * 5 + 1 : getLogic()->getGameId() * 5 + 2;
}

// Handle events
bool Menu::handleStartMenuEvent(Common::Event ev) {
	// Special case if we are showing credits (only allow left & right-click)
	if (_isShowingCredits) {
		// Interrupt on right click
		switch(ev.type) {
			case Common::EVENT_RBUTTONDOWN:
				_isShowingCredits = false; // Will cause credits to stop & reset overlays
			case Common::EVENT_LBUTTONDOWN:
				showCredits();
				askForRedraw();
			default:
				return true;
		}
	}

	// Process event (check hit box / etc.)
	static StartMenuAction action;
	SceneHotspot *hotspot = NULL;
	if (_scene && !_scene->checkHotSpot(ev.mouse, &hotspot)) {
		clearBg(GraphicsManager::kBackgroundOverlay);
		askForRedraw();
		return true;
	}

	if (!hotspot)
		return true;

	action = (StartMenuAction)hotspot->action;

	bool clicked = (ev.type == Common::EVENT_LBUTTONDOWN);
	clearBg(GraphicsManager::kBackgroundOverlay);

	switch(action) {
	default:
		break;

	case kActionCase4:
		// TODO reset time variable (and fall down to kActionContinue)

	case kActionContinue:
		// TODO Check for cd archive: reload the proper archive here if running in single cd mode
		if (!getLogic()->isGameStarted()) {
			drawSeqFrame(&_seqEggButtons, kButtonShield, GraphicsManager::kBackgroundOverlay);
			drawSeqFrame(&_seqTooltips, kTooltipPlayNewGame, GraphicsManager::kBackgroundOverlay);
		} else {
			drawSeqFrame(&_seqEggButtons, kButtonContinue, GraphicsManager::kBackgroundOverlay);

			// FIXME: using different global in original game -> find out what they do
			if (_currentTime == getState()->time) { // will break since we adjust the game time with rewind/forward/cities
				// TODO check if game is finished
				//if (isGameFinished())
					//_seqTooltips.showFrameOverlay(kTooltipViewGameEnding);
				//else
					drawSeqFrame(&_seqTooltips, kTooltipContinueGame, GraphicsManager::kBackgroundOverlay);
			} else {
				drawSeqFrame(&_seqTooltips, kTooltipContinueRewoundGame, GraphicsManager::kBackgroundOverlay);
			}
		}

		if (!clicked)
			break;

		playSfxStream("LIB046");

		// TODO: to implement in logic...
		//  - load new data file
		//  - show intro if new game
		//  - Reset save game & "save points"
		//  - etc.
		{
			getState()->scene = 255; // HACK to not show menu after we are finished
			clearBg(GraphicsManager::kBackgroundAll);

			showScene(5 * getLogic()->getGameId() + 3, GraphicsManager::kBackgroundC);
			askForRedraw(); redrawScreen();
			_engine->_system->delayMillis(1000);

			showScene(5 * getLogic()->getGameId() + 4, GraphicsManager::kBackgroundC);
			askForRedraw(); redrawScreen();
			_engine->_system->delayMillis(1000);

			showScene(5 * getLogic()->getGameId() + 5, GraphicsManager::kBackgroundC);
			askForRedraw(); redrawScreen();
			_engine->_system->delayMillis(1000);

			// Show intro
			Animation animation;
			if (animation.loadFile("1601.nis"))
				animation.play();

			clearBg(GraphicsManager::kBackgroundAll);

			// Reset scene
			getLogic()->startGame();
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionCredits:
		if (clicked) {
			drawSeqFrame(&_seqTooltips, kButtonCreditsPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046");
			_isShowingCredits = true;
			_creditsSequenceIndex = 0;
			showCredits();
		} else {
			drawSeqFrame(&_seqEggButtons, kButtonCredits, GraphicsManager::kBackgroundOverlay);
			drawSeqFrame(&_seqTooltips, kTooltipCredits, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionQuitGame:
		drawSeqFrame(&_seqTooltips, kTooltipQuit, GraphicsManager::kBackgroundOverlay);

		if (clicked) {
			drawSeqFrame(&_seqButtons, kButtonQuitPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046");

			//TODO some stuff... see disasm
			return false;
		} else {
			drawSeqFrame(&_seqButtons, kButtonQuit, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionSwitchSaveGame:
		if (clicked) {
			drawSeqFrame(&_seqAcorn, 1, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046");
			getLogic()->switchGame();
			// the menu should have been reset & redrawn, so don't do anything else here
		} else {
			drawSeqFrame(&_seqAcorn, 0, GraphicsManager::kBackgroundOverlay);

			if (!SaveLoad::isSavegameValid(getNextGameId())) {
				if (getLogic()->isGameStarted())
					drawSeqFrame(&_seqTooltips, kTooltipStartAnotherGame, GraphicsManager::kBackgroundOverlay)
				else
					drawSeqFrame(&_seqTooltips, kTooltipSwitchBlueGame, GraphicsManager::kBackgroundOverlay);
			} else {
				// Stupid tooltips ids are not in order, so we can't just increment them...
				switch(getLogic()->getGameId()) {
					case kGameBlue:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchRedGame, GraphicsManager::kBackgroundOverlay);
						break;

					case kGameRed:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchGreenGame, GraphicsManager::kBackgroundOverlay);
						break;

					case kGameGreen:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchPurpleGame, GraphicsManager::kBackgroundOverlay);
						break;

					case kGamePurple:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchTealGame, GraphicsManager::kBackgroundOverlay);
						break;

					case kGameTeal:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchGoldGame, GraphicsManager::kBackgroundOverlay);
						break;

					case kGameGold:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchBlueGame, GraphicsManager::kBackgroundOverlay);
						break;
				}
			}
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionRewindGame:
		// TODO check that we can actually rewind
		//if (_currentTime <= getState()->time)
		if (clicked) {
			drawSeqFrame(&_seqEggButtons, kButtonRewindPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046");
			// TODO rewind clock
			//goToTime(XXX + 8);
		} else {
			drawSeqFrame(&_seqEggButtons, kButtonRewind, GraphicsManager::kBackgroundOverlay);
			drawSeqFrame(&_seqTooltips, kTooltipRewind, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionForwardGame:
		// TODO check that we can actually rewind
		if (_currentTime == getState()->time)
			break;

		if (clicked) {
			drawSeqFrame(&_seqEggButtons, kButtonForwardPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046");

			// TODO advance clock
			//goToTime(32 * ??? + XXX + 8);

		} else {
			drawSeqFrame(&_seqEggButtons, kButtonForward, GraphicsManager::kBackgroundOverlay);
			drawSeqFrame(&_seqTooltips, kTooltipFastForward, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionParis:
		moveToCity(kParis, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionStrasBourg:
		moveToCity(kStrasbourg, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionMunich:
		moveToCity(kMunich, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionVienna:
		moveToCity(kVienna, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionBudapest:
		moveToCity(kBudapest, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionBelgrade:
		moveToCity(kBelgrade, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionConstantinople:
		moveToCity(kConstantinople, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionDecreaseVolume:
		// Cannot decrease volume further
		if (getVolume() == 0) {
			drawSeqFrame(&_seqButtons, kButtonVolume, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSeqFrame(&_seqTooltips, kTooltipVolumeDown, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			drawSeqFrame(&_seqButtons, kButtonVolumeDownPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046");
			setVolume(getVolume() - 1);
		} else {
			drawSeqFrame(&_seqButtons, kButtonVolumeDown, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionIncreaseVolume:
		// Cannot increase volume further
		if (getVolume() >= 7) {
			drawSeqFrame(&_seqButtons, kButtonVolume, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSeqFrame(&_seqTooltips, kTooltipVolumeUp, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			drawSeqFrame(&_seqButtons, kButtonVolumeUpPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046");
			setVolume(getVolume() + 1);
		} else {
			drawSeqFrame(&_seqButtons, kButtonVolumeUp, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionDecreaseBrightness:
		// Cannot increase brightness further
		if (getBrightness() == 0) {
			drawSeqFrame(&_seqButtons, kButtonBrightness, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSeqFrame(&_seqTooltips, kTooltipBrightnessDown, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			drawSeqFrame(&_seqButtons, kButtonBrightnessDownPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046");

			setBrightness(getBrightness() - 1);
		} else {
			drawSeqFrame(&_seqButtons, kButtonBrightnessDown, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kActionIncreaseBrightness:
		// Cannot increase brightness further
		if (getBrightness() >= 6) {
			drawSeqFrame(&_seqButtons, kButtonBrightness, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSeqFrame(&_seqTooltips, kTooltipBrightnessUp, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			drawSeqFrame(&_seqButtons, kButtonBrightnessUpPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046");
			setBrightness(getBrightness() + 1);
		} else {
			drawSeqFrame(&_seqButtons, kButtonBrightnessUp, GraphicsManager::kBackgroundOverlay);
		}
		break;
	}

	// All cases should break apart from the Quit case, so we can ask for redraw only once here
	askForRedraw();

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////

void Menu::loadData() {
	bool loaded = true;

	// Special case: acorn highlight needs to be reloaded when showing the menu again in case we switched games
	if (SaveLoad::isSavegameValid(getNextGameId()))
		loaded &= _seqAcorn.loadFile(getAcornSequenceName(getNextGameId()));
	else
		loaded &= _seqAcorn.loadFile(getAcornSequenceName(kGameBlue));
	assert(loaded == true);

	// Check if we loaded sequences before
	if (_seqTooltips.count() > 0)
		return;

	// Load all static data
	loaded  &= _seqTooltips.loadFile("helpnewr.seq");
	loaded  &= _seqEggButtons.loadFile("buttns.seq");
	loaded  &= _seqButtons.loadFile("quit.seq");

	loaded  &= _seqCredits.loadFile("credits.seq");

	// Load the city buttons
	Sequence s;
	loaded &= s.loadFile("jlinetl.seq");
	_cityButtonFrames[0] = s.getFrame(0);

	loaded &= s.loadFile("jlinecen.seq");
	for (int i = 0; i < 5; i++)
		_cityButtonFrames[i + 1] = s.getFrame(i);

	loaded &= s.loadFile("jlinebr.seq");
	_cityButtonFrames[6] = s.getFrame(0);

	// We cannot proceed unless all files loaded properly
	assert(loaded == true);
}

// Get the sequence name to use for the acorn highlight, depending of the currently loaded savegame
Common::String Menu::getAcornSequenceName(GameId id) {

	// end of text:00449d80 (also sets up the main menu scene)

	// TODO replace with string array and access by index?
	Common::String name = "";
	switch (id) {
	default:
	case kGameBlue:
		name = "aconblu3.seq";
		break;

	case kGameRed:
		name = "aconred.seq";
		break;

	case kGameGreen:
		name = "acongren.seq";
		break;

	case kGamePurple:
		name = "aconpurp.seq";
		break;

	case kGameTeal:
		name = "aconteal.seq";
		break;

	case kGameGold:
		name = "acongold.seq";
		break;
	}

	return name;
}

//////////////////////////////////////////////////////////////////////////
// Overlays & elements
//////////////////////////////////////////////////////////////////////////

void Menu::drawElements() {
	// Do not draw if the game has not yet started
	if (!SaveLoad::isSavegameValid(getLogic()->getGameId()))
		return;
	if (!getLogic()->isGameStarted())
		return;

	clearBg(GraphicsManager::kBackgroundA);

	_clock->process();
	_trainLine->process();
	_engine->getGraphicsManager()->draw(_clock, GraphicsManager::kBackgroundA);
	_engine->getGraphicsManager()->draw(_trainLine, GraphicsManager::kBackgroundA);
}

// Show credits overlay
void Menu::showCredits() {
	clearBg(GraphicsManager::kBackgroundOverlay);

	if (!_isShowingCredits || _creditsSequenceIndex > _seqCredits.count() - 1) {
		_isShowingCredits = false;
		return;
	}

	drawSeqFrame(&_seqCredits, _creditsSequenceIndex, GraphicsManager::kBackgroundA);
	_creditsSequenceIndex++;
}

//////////////////////////////////////////////////////////////////////////
// Time
//////////////////////////////////////////////////////////////////////////

void Menu::goToTime(uint32 time) {
	// TODO implement modifying the current game time
	// + adjusting elements on screen : clock + train line
	//;getState()->time = time; // need to use targetTime var, as modifying the global state will prevent us from going into the other direction later

	// Nothing to do if the menu time is already set to the correct value
	// FIXME can this really happen?
	if (_currentTime == time)
		return;

	int direction = 1;
	int speed = 1;

	if (_currentTime <= time) {
		playSfxStream("LIB042");
	} else {
		playSfxStream("LIB041");
		direction = -1;
	}

	_engine->getCursor()->show(false);

	while (_currentTime != time) {
		_currentTime = _currentTime + direction * 500 * speed;
		if (speed < 10)
			speed++;

		// Make sure we don't pass destination
		if ((direction == 1 && _currentTime > time) || (direction == -1 && _currentTime < time))
			_currentTime = time;

		drawElements();
		askForRedraw();
		redrawScreen();

		Common::Event ev;
		_engine->getEventManager()->pollEvent(ev);
		if (ev.type == Common::EVENT_RBUTTONDOWN) {
			break;
		}

		//g_system->delayMillis(250);
	}

	// Draw final time
	_currentTime = time;
	drawElements();
	askForRedraw();
	redrawScreen();

	_engine->getCursor()->show(true);

	// Stop sound
	getSoundMgr()->getSfxStream()->stop();
}

void Menu::moveToCity(CityButton city, bool clicked) {
	uint32 time = cityButtonsInfo[city].time;

	// TODO Check if we have access (there seems to be more checks on some internal times) - probably : current_time (menu only) / game time / some other?
	if (getState()->time < time || _currentTime == time) {
		return;
	}

	// Show city overlay
	_engine->getGraphicsManager()->draw(_cityButtonFrames[city], GraphicsManager::kBackgroundOverlay);

	if (clicked) {
		playSfxStream("LIB046");
		goToTime(time);
		// TODO set some global var to 1
	} else {
		StartMenuTooltips tooltip;
		if (_currentTime < time)
			tooltip = cityButtonsInfo[city].forward;
		else
			tooltip = cityButtonsInfo[city].rewind;
		drawSeqFrame(&_seqTooltips, tooltip, GraphicsManager::kBackgroundOverlay)
	}
}

//////////////////////////////////////////////////////////////////////////
// Sound / Brightness
//////////////////////////////////////////////////////////////////////////

// Get current volume (converted to in-game value)
int Menu::getVolume() {
	int volume = _engine->_mixer->getVolumeForSoundType(Audio::Mixer::kPlainSoundType);

	// Convert to in-game value [0-7]
	volume *= 7 / Audio::Mixer::kMaxMixerVolume;

	return volume;
}

// Set the volume (converts to ScummVM values)
void Menu::setVolume(int volume) {
	getState()->volume = volume;

	// Clamp volume
	int value = volume * Audio::Mixer::kMaxMixerVolume / 7;
	if (value < 0)
		value = 0;
	if (value > Audio::Mixer::kMaxMixerVolume)
		value = Audio::Mixer::kMaxMixerVolume;

	_engine->_mixer->setVolumeForSoundType(Audio::Mixer::kPlainSoundType, value);

	// TODO: write to savegame ?
}

int Menu::getBrightness() {
	return getState()->brightness;
}

void Menu::setBrightness(int brightness) {
	getState()->brightness = brightness;

	// TODO: write to savegame
	// TODO: reload all graphics and adjust for the new brightness (or not :D)
}

} // End of namespace LastExpress
