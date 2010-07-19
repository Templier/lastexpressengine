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

#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savegame.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

#define getNextGameId() (GameId)((_gameId + 1) % 6)

namespace LastExpress {

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
static const struct {
	uint8 frame;
	TimeValue time;
} trainCities[31] = {
	{0, kTimeCityParis},
	{9, kTimeCityEpernay},
	{11, kTimeCityChalons},
	{16, kTimeCityBarLeDuc},
	{21, kTimeCityNancy},
	{25, kTimeCityLuneville},
	{35, kTimeCityAvricourt},
	{37, kTimeCityDeutschAvricourt},
	{40, kTimeCityStrasbourg},
	{53, kTimeCityBadenOos},
	{56, kTimeCityKarlsruhe},
	{60, kTimeCityStuttgart},
	{63, kTimeCityGeislingen},
	{66, kTimeCityUlm},
	{68, kTimeCityAugsburg},
	{73, kTimeCityMunich},
	{84, kTimeCitySalzbourg},
	{89, kTimeCityAttnangPuchheim},
	{97, kTimeCityWels},
	{100, kTimeCityLinz},
	{104, kTimeCityAmstetten},
	{111, kTimeCityVienna},
	{120, kTimeCityPoszony},
	{124, kTimeCityGalanta},
	{132, kTimeCityBudapest},
	{148, kTimeCityBelgrade},
	/* Line 1 ends at 150 - line 2 begins at 0 */
	{157, kTimeCityNish},
	{165, kTimeCityTzaribrod},
	{174, kTimeCitySofia},
	{198, kTimeCityAdrianople},
	{210, kTimeCityConstantinople}};

static const struct {
	TimeValue time;
	StartMenuTooltips rewind;
	StartMenuTooltips forward;
} cityButtonsInfo[7] = {
	{kTimeCityParis, kTooltipRewindParis, kTooltipRewindParis},
	{kTimeCityStrasbourg, kTooltipRewindStrasbourg, kTooltipForwardStrasbourg},
	{kTimeCityMunich, kTooltipRewindMunich, kTooltipForwardMunich},
	{kTimeCityVienna, kTooltipRewindVienna, kTooltipForwardVienna},
	{kTimeCityBudapest, kTooltipRewindBudapest, kTooltipForwardBudapest},
	{kTimeCityBelgrade, kTooltipRewindBelgrade, kTooltipForwardBelgrade},
	{kTimeCityConstantinople, kTooltipForwardConstantinople, kTooltipForwardConstantinople}
};

//////////////////////////////////////////////////////////////////////////
// Clock
//////////////////////////////////////////////////////////////////////////
class Clock {
public:
	Clock(LastExpressEngine *engine);
	~Clock();

	void draw(uint32 time);
	void clear();

private:
	LastExpressEngine *_engine;

	// Frames
	SequenceFrame *_frameMinutes;
	SequenceFrame *_frameHour;
	SequenceFrame *_frameSun;
	SequenceFrame *_frameDate;
};

Clock::Clock(LastExpressEngine *engine) : _engine(engine), _frameMinutes(NULL), _frameHour(NULL), _frameSun(NULL), _frameDate(NULL) {
	_frameMinutes = new SequenceFrame(loadSequence("eggmin.seq"), 0, true);
	_frameHour = new SequenceFrame(loadSequence("egghour.seq"), 0, true);
	_frameSun = new SequenceFrame(loadSequence("sun.seq"), 0, true);
	_frameDate = new SequenceFrame(loadSequence("datenew.seq"), 0, true);
}

Clock::~Clock() {
	delete _frameMinutes;
	delete _frameHour;
	delete _frameSun;
	delete _frameDate;

	// Zero passed pointers
	_engine = NULL;
}

void Clock::clear() {
	getScenes()->removeAndRedraw(&_frameMinutes, false);
	getScenes()->removeAndRedraw(&_frameHour, false);
	getScenes()->removeAndRedraw(&_frameSun, false);
	getScenes()->removeAndRedraw(&_frameDate, false);
}

void Clock::draw(uint32 time) {
	assert(time >= kTimeCityParis && time <= kTimeCityConstantinople);

	// Check that sequences have been loaded
	if (!_frameMinutes || !_frameHour || !_frameSun || !_frameDate)
		error("Clock::process: clock sequences have not been loaded correctly!");

	// Clear existing frames
	clear();

	// Game starts at: 1037700 = 7:13 p.m. on July 24, 1914
	// Game ends at:   4941000 = 7:30 p.m. on July 26, 1914
	// Game lasts for: 3903300 = 2 days + 17 mins = 2897 mins

	// 15 = 1 second
	// 15 * 60 = 900 = 1 minute
	// 900 * 60 = 54000 = 1 hour
	// 54000 * 24 = 1296000 = 1 day

	// Calculate each sequence index from the current time
	uint8 hour = (uint8)((time % 1296000) / 54000);
	uint8 minute =  (uint8)((time % 54000) / 900);
	uint32 index_date = 18 * time / 1296000;
	if (hour == 23)
		index_date += 18 * minute / 60;

	// Set sequences frames
	_frameMinutes->setFrame(minute);
	_frameHour->setFrame((5 * hour + minute / 12) % 60);
	_frameSun->setFrame((5 * hour + minute / 12) % 120);
	_frameDate->setFrame(index_date);

	// Adjust z-order and queue
	_frameMinutes->getInfo()->location = 1;
	_frameHour->getInfo()->location = 1;
	_frameSun->getInfo()->location = 1;
	_frameDate->getInfo()->location = 1;

	getScenes()->addToQueue(_frameMinutes);
	getScenes()->addToQueue(_frameHour);
	getScenes()->addToQueue(_frameSun);
	getScenes()->addToQueue(_frameDate);
}

//////////////////////////////////////////////////////////////////////////
// TrainLine
//////////////////////////////////////////////////////////////////////////
class TrainLine {
public:
	TrainLine(LastExpressEngine *engine);
	~TrainLine();

	void draw(uint32 time);
	void clear();

private:
	LastExpressEngine *_engine;

	// Frames
	SequenceFrame *_frameLine1;
	SequenceFrame *_frameLine2;
};

TrainLine::TrainLine(LastExpressEngine *engine) : _engine(engine), _frameLine1(NULL), _frameLine2(NULL) {
	_frameLine1 = new SequenceFrame(loadSequence("line1.seq"), 0, true);
	_frameLine2 = new SequenceFrame(loadSequence("line2.seq"), 0, true);
}

TrainLine::~TrainLine() {
	delete _frameLine1;
	delete _frameLine2;

	// Zero passed pointers
	_engine = NULL;
}

void TrainLine::clear() {
	getScenes()->removeAndRedraw(&_frameLine1, false);
	getScenes()->removeAndRedraw(&_frameLine2, false);
}

// Draw the train line at the time
//  line1: 150 frames (=> Belgrade)
//  line2: 61 frames (=> Constantinople)
void TrainLine::draw(uint32 time) {
	assert(time >= kTimeCityParis && time <= kTimeCityConstantinople);

	// Check that sequences have been loaded
	if (!_frameLine1 || !_frameLine2)
		error("TrainLine::process: Line sequences have not been loaded correctly!");

	// Clear existing frames
	clear();

	// Get the index of the last city the train has visited
	uint index = 0;
	for (uint i = 0; i < ARRAYSIZE(trainCities); i++)
		if ((uint32)trainCities[i].time <= time)
			index = i;

	uint16 frame;
	if (time > (uint32)trainCities[index].time) {
		// Interpolate linearly to use a frame between the cities
		uint8 diffFrames = trainCities[index + 1].frame - trainCities[index].frame;
		uint diffTimeCities = (trainCities[index + 1].time - trainCities[index].time);
		uint traveledTime = (time - trainCities[index].time);
		frame = (uint16)(trainCities[index].frame + (traveledTime * diffFrames) / diffTimeCities);
	} else {
		// Exactly on the city
		frame = trainCities[index].frame;
	}

	// Set frame, z-order and queue
	if (frame < 150) {
		_frameLine1->setFrame(frame);

		_frameLine1->getInfo()->location = 1;
		getScenes()->addToQueue(_frameLine1);
	} else {
		// We passed Belgrade
		_frameLine1->setFrame(149);
		_frameLine2->setFrame(frame - 150);

		_frameLine1->getInfo()->location = 1;
		_frameLine2->getInfo()->location = 1;

		getScenes()->addToQueue(_frameLine1);
		getScenes()->addToQueue(_frameLine2);
	}
}


//////////////////////////////////////////////////////////////////////////
// Menu
//////////////////////////////////////////////////////////////////////////
Menu::Menu(LastExpressEngine *engine) : _engine(engine),
	_seqTooltips(NULL), _seqEggButtons(NULL), _seqButtons(NULL), _seqCredits(NULL), _seqAcorn(NULL),
	_gameId(kGameBlue), _hasShownStartScreen(false), _hasShownIntro(false),
	_isShowingCredits(false), _isGameStarted(false), _isShowingMenu(false),
	_clock(NULL), _trainLine(NULL), _checkHotspotsTicks(15), _lastHotspot(NULL), _mouseFlags(Common::EVENT_INVALID),
	_currentIndex(0), _currentTime(0), _index(0), _index2(0), _time(0), _delta(0), _handleTimeDelta(false) {

	_creditsSequenceIndex = 0;
	for (int i = 0; i < 7; i++)
		_cityButtonFrames[i] = NULL;

	_clock = new Clock(_engine);
	_trainLine = new TrainLine(_engine);
}

Menu::~Menu() {
	delete _clock;
	delete _trainLine;

	for (int i = 0; i < 7; i++)
		delete _cityButtonFrames[i];

	SAFE_DELETE(_seqTooltips);
	SAFE_DELETE(_seqEggButtons);
	SAFE_DELETE(_seqButtons);
	SAFE_DELETE(_seqCredits);
	SAFE_DELETE(_seqAcorn);

	_lastHotspot = NULL;

	// Zero passed pointers
	_engine = NULL;
}

//////////////////////////////////////////////////////////////////////////
// Handle events
void Menu::eventMouse(const Common::Event &ev) {
	//if (!getFlags()->shouldRedraw)
	//	return;

	bool redraw = true;
	getFlags()->shouldRedraw = false;

	// Update coordinates
	setCoords(ev.mouse);
	_mouseFlags = ev.type;

	if (_isShowingCredits) {
		error("Menu::eventMouse: not implemented!");
	} else {
		// Check for hotspots
		SceneHotspot *hotspot = NULL;
		getScenes()->get(getState()->scene)->checkHotSpot(ev.mouse, &hotspot);

		if (_lastHotspot != hotspot || ev.type == Common::EVENT_LBUTTONUP) {
			_lastHotspot = hotspot;

			if (ev.type == Common::EVENT_MOUSEMOVE) { /* todo check event type */
				if (!_handleTimeDelta && hasTimeDelta())
					setTime();
			}

			if (hotspot) {
				redraw = handleEvent((StartMenuAction)hotspot->action, ev.type);
				getFlags()->mouseRightClick = false;
				getFlags()->mouseLeftClick = false;
			} else {
				hideOverlays();
			}
		}
	}

	if (redraw) {
		getFlags()->shouldRedraw = true;
		askForRedraw();
	}
}

void Menu::eventTick(const Common::Event&) {
	if (hasTimeDelta())
		adjustTime();
	else if (_handleTimeDelta)
		_handleTimeDelta = false;

	// Check hotspots
	if (!--_checkHotspotsTicks) {
		checkHotspots();
		_checkHotspotsTicks = 15;
	}
}

//////////////////////////////////////////////////////////////////////////
// Show the intro and load the main menu scene
void Menu::show(bool doSavegame, TimeType type, uint32 time) {

	if (_isShowingMenu)
		return;

	_isShowingMenu = true;
	getEntities()->reset();

	// If no blue savegame exists, this might be the first time we start the game, so we show the full intro
	if (!SaveLoad::isSavegameValid(kGameBlue)) {
		if (!_hasShownIntro) {

			// Show Broderbrund logo
			Animation animation;
			if (animation.load(getArchive("1930.nis")))
				animation.play();

			// Play intro music
			getSound()->playSoundWithSubtitles("MUS001.SND", 83886096, kEntityNone);

			// Show The Smoking Car logo
			if (animation.load(getArchive("1931.nis")))
				animation.play();

			_hasShownIntro = true;
		}
	} else {
		// Only show the quick intro
		if (!_hasShownStartScreen) {
			getSound()->playSoundWithSubtitles("MUS018.SND", 83886096, kEntityNone);
			getScenes()->loadScene(kSceneStartScreen);

			// FIXME: Original game waits 60 frames and loops Sound::unknownFunction1 unless the right button is pressed
		}
	}

	_hasShownStartScreen = true;

	initGame(doSavegame, type, time);
	// Init savegame
	// FIXME: getSavegame()->init(savegame, type, time);

	// Setup sound
	getSound()->unknownFunction4();
	getSound()->setupQueue(11, 13);
	if (getSound()->isBuffered("TIMER"))
		getSound()->removeFromQueue("TIMER");

	// TODO more initialization
	// TODO Init flags

	// Set Cursor type
	_engine->getCursor()->setStyle(kCursorNormal);
	_engine->getCursor()->show(true);

	// Load all menu-related data
	loadData();


	//_currentTime = getState()->time;

	// Load main scene
	getState()->scene = getSceneIndex();
	_engine->getGraphicsManager()->draw(getScenes()->get(getState()->scene), GraphicsManager::kBackgroundC);
	//drawElements();

	askForRedraw();

	// Set event handlers
	SET_EVENT_HANDLERS(Menu, this);
}

bool Menu::handleEvent(StartMenuAction action, Common::EventType type) {
	// Special case if we are showing credits (only allow left & right-click)
	//if (_isShowingCredits) {
	//	// Interrupt on right click
	//	switch(type) {
	//		case Common::EVENT_RBUTTONUP:
	//			_isShowingCredits = false; // Will cause credits to stop & reset overlays

	//		// Fall through to hide/show credits
	//		case Common::EVENT_LBUTTONUP:
	//			showCredits();
	//			askForRedraw();
	//			return;

	//		default:
	//			return;
	//	}
	//}

	bool clicked = (type == Common::EVENT_LBUTTONUP);
	clearBg(GraphicsManager::kBackgroundOverlay);

	switch(action) {
	default:
		break;

	case kMenuCase4:
		// TODO reset time variable (and fall down to kMenuContinue)

	case kMenuContinue:
		// TODO Check for cd archive: reload the proper archive here if running in single cd mode
		if (!_isGameStarted) {
			drawSequenceFrame(_seqEggButtons, kButtonShield, GraphicsManager::kBackgroundOverlay);
			drawSequenceFrame(_seqTooltips, kTooltipPlayNewGame, GraphicsManager::kBackgroundOverlay);
		} else {
			drawSequenceFrame(_seqEggButtons, kButtonContinue, GraphicsManager::kBackgroundOverlay);

			// FIXME: using different global in original game -> find out what they do
			if (_currentTime == getState()->time) { // will break since we adjust the game time with rewind/forward/cities
				// TODO check if game is finished
				//if (isGameFinished())
					//_seqTooltips.showFrameOverlay(kTooltipViewGameEnding);
				//else
					drawSequenceFrame(_seqTooltips, kTooltipContinueGame, GraphicsManager::kBackgroundOverlay);
			} else {
				drawSequenceFrame(_seqTooltips, kTooltipContinueRewoundGame, GraphicsManager::kBackgroundOverlay);
			}
		}

		if (!clicked)
			break;

		clearBg(GraphicsManager::kBackgroundOverlay);

		playSfxStream("LIB046.SND");

		// Setup new game
		getSavePoints()->reset();
		setLogicEventHandlers();

		// TODO: sound entry loop

		if (!getFlags()->mouseRightClick) {
			getScenes()->loadScene((SceneIndex)(5 * _gameId + 3));

			if (!getFlags()->mouseRightClick) {
				getScenes()->loadScene((SceneIndex)(5 * _gameId + 4));

				if (!getFlags()->mouseRightClick) {
					getScenes()->loadScene((SceneIndex)(5 * _gameId + 5));

					if (!getFlags()->mouseRightClick) {
						// TODO more soundcache events

						// Show intro
						Animation animation;
						if (animation.load(getArchive("1601.nis")))
							animation.play();

						getEvent(kEventIntro) = 1;
					}
				}
			}
		}

		if (!getEvent(kEventIntro))	{
			getEvent(kEventIntro) = 1;

			// TODO sound loop
		}

		// Setup game
		getFlags()->isGameRunning = true;
		startGame();

		if (!_isShowingMenu)
			getInventory()->show();

		return false;

	//////////////////////////////////////////////////////////////////////////
	case kMenuCredits:
		if (clicked) {
			drawSequenceFrame(_seqTooltips, kButtonCreditsPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046.SND");
			_isShowingCredits = true;
			_creditsSequenceIndex = 0;
			showCredits();
		} else {
			drawSequenceFrame(_seqEggButtons, kButtonCredits, GraphicsManager::kBackgroundOverlay);
			drawSequenceFrame(_seqTooltips, kTooltipCredits, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuQuitGame:
		drawSequenceFrame(_seqTooltips, kTooltipQuit, GraphicsManager::kBackgroundOverlay);

		if (clicked) {
			drawSequenceFrame(_seqButtons, kButtonQuitPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046.SND");

			error("Menu::handleEvent / kMenuQuitGame: implementation not finished!");

			// return false;
		} else {
			drawSequenceFrame(_seqButtons, kButtonQuit, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuSwitchSaveGame:
		if (clicked) {
			drawSequenceFrame(_seqAcorn, 1, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046.SND");
			switchGame();
			// the menu should have been reset & redrawn, so don't do anything else here
		} else {
			drawSequenceFrame(_seqAcorn, 0, GraphicsManager::kBackgroundOverlay);

			if (!SaveLoad::isSavegameValid(getNextGameId())) {
				if (_isGameStarted)
					drawSequenceFrame(_seqTooltips, kTooltipStartAnotherGame, GraphicsManager::kBackgroundOverlay)
				else
					drawSequenceFrame(_seqTooltips, kTooltipSwitchBlueGame, GraphicsManager::kBackgroundOverlay);
			} else {
				// Stupid tooltips ids are not in order, so we can't just increment them...
				switch(_gameId) {
					case kGameBlue:
						drawSequenceFrame(_seqTooltips, kTooltipSwitchRedGame, GraphicsManager::kBackgroundOverlay);
						break;

					case kGameRed:
						drawSequenceFrame(_seqTooltips, kTooltipSwitchGreenGame, GraphicsManager::kBackgroundOverlay);
						break;

					case kGameGreen:
						drawSequenceFrame(_seqTooltips, kTooltipSwitchPurpleGame, GraphicsManager::kBackgroundOverlay);
						break;

					case kGamePurple:
						drawSequenceFrame(_seqTooltips, kTooltipSwitchTealGame, GraphicsManager::kBackgroundOverlay);
						break;

					case kGameTeal:
						drawSequenceFrame(_seqTooltips, kTooltipSwitchGoldGame, GraphicsManager::kBackgroundOverlay);
						break;

					case kGameGold:
						drawSequenceFrame(_seqTooltips, kTooltipSwitchBlueGame, GraphicsManager::kBackgroundOverlay);
						break;
				}
			}
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuRewindGame:
		// TODO check that we can actually rewind
		//if (_currentTime <= getState()->time)
		if (clicked) {
			drawSequenceFrame(_seqEggButtons, kButtonRewindPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046.SND");
			// TODO rewind clock
			//goToTime(XXX + 8);
		} else {
			drawSequenceFrame(_seqEggButtons, kButtonRewind, GraphicsManager::kBackgroundOverlay);
			drawSequenceFrame(_seqTooltips, kTooltipRewind, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuForwardGame:
		// TODO check that we can actually rewind
		if (_currentTime == getState()->time)
			break;

		if (clicked) {
			drawSequenceFrame(_seqEggButtons, kButtonForwardPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046.SND");

			// TODO advance clock
			//goToTime(32 * ??? + XXX + 8);

		} else {
			drawSequenceFrame(_seqEggButtons, kButtonForward, GraphicsManager::kBackgroundOverlay);
			drawSequenceFrame(_seqTooltips, kTooltipFastForward, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuParis:
		moveToCity(kParis, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuStrasBourg:
		moveToCity(kStrasbourg, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuMunich:
		moveToCity(kMunich, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuVienna:
		moveToCity(kVienna, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuBudapest:
		moveToCity(kBudapest, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuBelgrade:
		moveToCity(kBelgrade, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuConstantinople:
		moveToCity(kConstantinople, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuDecreaseVolume:
		// Cannot decrease volume further
		if (getVolume() == 0) {
			drawSequenceFrame(_seqButtons, kButtonVolume, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSequenceFrame(_seqTooltips, kTooltipVolumeDown, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			drawSequenceFrame(_seqButtons, kButtonVolumeDownPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046.SND");
			setVolume(getVolume() - 1);
		} else {
			drawSequenceFrame(_seqButtons, kButtonVolumeDown, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuIncreaseVolume:
		// Cannot increase volume further
		if (getVolume() >= 7) {
			drawSequenceFrame(_seqButtons, kButtonVolume, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSequenceFrame(_seqTooltips, kTooltipVolumeUp, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			drawSequenceFrame(_seqButtons, kButtonVolumeUpPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046.SND");
			setVolume(getVolume() + 1);
		} else {
			drawSequenceFrame(_seqButtons, kButtonVolumeUp, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuDecreaseBrightness:
		// Cannot increase brightness further
		if (getBrightness() == 0) {
			drawSequenceFrame(_seqButtons, kButtonBrightness, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSequenceFrame(_seqTooltips, kTooltipBrightnessDown, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			drawSequenceFrame(_seqButtons, kButtonBrightnessDownPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046.SND");

			setBrightness(getBrightness() - 1);
		} else {
			drawSequenceFrame(_seqButtons, kButtonBrightnessDown, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kMenuIncreaseBrightness:
		// Cannot increase brightness further
		if (getBrightness() >= 6) {
			drawSequenceFrame(_seqButtons, kButtonBrightness, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSequenceFrame(_seqTooltips, kTooltipBrightnessUp, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			drawSequenceFrame(_seqButtons, kButtonBrightnessUpPushed, GraphicsManager::kBackgroundOverlay);
			playSfxStream("LIB046.SND");
			setBrightness(getBrightness() + 1);
		} else {
			drawSequenceFrame(_seqButtons, kButtonBrightnessUp, GraphicsManager::kBackgroundOverlay);
		}
		break;
	}

	return true;
}

void Menu::setLogicEventHandlers() {
	SET_EVENT_HANDLERS(Logic, getLogic());
	clear();
	_isShowingMenu = false;
}

//////////////////////////////////////////////////////////////////////////
// Game-related
//////////////////////////////////////////////////////////////////////////
void Menu::initGame(bool doSavegame, TimeType type, uint32 time) {
	warning("Menu::initGame: not implemented!");

	if (time >= kTimeStartGame) {
		_currentTime = time;
		_time = time;
		_clock->draw(time);
		_trainLine->draw(time);

		initTime(type, time);
	}
}

void Menu::startGame() {
	// TODO: we need to reset the current scene
	getState()->scene = kSceneDefault;

	getEntities()->setup(true, kEntityNone);
	warning("Menu::startGame: not implemented!");
}

// Switch to the next savegame
void Menu::switchGame() {
	// Switch back to blue game is the current game is not started
	if (!_isGameStarted) {
		_gameId = kGameBlue;
	} else {
		_gameId = getNextGameId();
	}

	// Initialize savegame if needed
	if (!SaveLoad::isSavegamePresent(_gameId))
		SaveLoad::initSavegame(_gameId);

	// Reset run state
	_isGameStarted = false;

	// TODO load data from savegame, adjust volume & luminosity, etc...
	//////////////////////////////////////////////////////////////////////////
	// HACK for debug
	if (_gameId == kGameBlue) {
		getState()->time = kTimeCityPoszony;
		_isGameStarted = true;
	}
	//////////////////////////////////////////////////////////////////////////

	// Redraw all menu elements
	show(false, kTimeType0, 0);
}

bool Menu::isGameFinished() const {
	SaveLoad::SavegameEntryHeader *data = getSaveLoad()->getEntry(_index);

	if (_index2 != _index)
		return false;

	if (data->type != SaveLoad::kHeaderType2)
		return false;

	return (data->event == kEventAnnaKilled
		 || data->event == kEventKronosHostageAnnaNoFirebird
		 || data->event == kEventKahinaPunch
		 || data->event == kEventKahinaPunchBlue
		 || data->event == kEventKahinaPunchYellow
		 || data->event == kEventKahinaPunchSuite
		 || data->event == kEventKahinaPunchSuite2
		 || data->event == kEventKahinaPunchSuite3
		 || data->event == kEventKahinaPunchCar
		 || data->event == kEventKahinaPunchSuite4
		 || data->event == kEventKahinaPunchSuite5
		 || data->event == kEventKahinaPunchRestaurant
		 || data->event == kEventKronosGiveFirebird
		 || data->event == kEventAugustFindCorpse
		 || data->event == kEventMertensBloodJacket
		 || data->event == kEventMertensCorpseFloor
		 || data->event == kEventMertensCorpseBed
		 || data->event == kEventCoudertBloodJacket
		 || data->event == kEventGendarmesArrestation
		 || data->event == kEventAbbotDrinkGiveDetonator
		 || data->event == kEventMilosCorpseFloor
		 || data->event == kEventLocomotiveAnnaStopsTrain
		 || data->event == kEventTrainStopped
		 || data->event == kEventCathVesnaRestaurantKilled
		 || data->event == kEventCathVesnaTrainTopKilled
		 || data->event == kEventLocomotiveConductorsDiscovered
		 || data->event == kEventViennaAugustUnloadGuns
		 || data->event == kEventViennaKronosFirebird
		 || data->event == kEventVergesAnnaDead
		 || data->event == kEventTrainExplosionBridge
		 || data->event == kEventKronosBringNothing);
}

//////////////////////////////////////////////////////////////////////////
// Overlays & elements
//////////////////////////////////////////////////////////////////////////
void Menu::checkHotspots() {
	if (!_isShowingMenu)
		return;

	if (!getFlags()->shouldRedraw)
		return;

	if (_isShowingCredits)
		return;

	SceneHotspot *hotspot = NULL;
	getScenes()->get(getState()->scene)->checkHotSpot(getCoords(), &hotspot);

	if (hotspot)
		handleEvent((StartMenuAction)hotspot->action, _mouseFlags);
	else
		hideOverlays();
}

void Menu::hideOverlays() {
	_lastHotspot = NULL;

	// Hide all menu overlays
	for (MenuFrames::iterator it = _frames.begin(); it != _frames.end(); it++)
		showFrame(it->_key, -1, false);

	getScenes()->drawFrames(true);
}

void Menu::showFrame(StartMenuOverlay overlayType, int index, bool redraw) {
	if (index == -1) {
		getScenes()->removeFromQueue(_frames[overlayType]);
	} else {
		// Check that the overlay is valid or not already showing
		if (!_frames[overlayType])
			return;

		if (_frames[overlayType]->getFrame() == (uint32)index)
			return;

		// Remove the frame and add a new one with the proper index
		getScenes()->removeFromQueue(_frames[overlayType]);
		_frames[overlayType]->setFrame(index);
		getScenes()->addToQueue(_frames[overlayType]);
	}

	if (redraw)
			getScenes()->drawFrames(true);
}

// Remove all frames from the queue
void Menu::clear() {
	for (MenuFrames::iterator it = _frames.begin(); it != _frames.end(); it++)
		getScenes()->removeAndRedraw(&it->_value, false);
}

// Show credits overlay
void Menu::showCredits() {
	clearBg(GraphicsManager::kBackgroundOverlay);

	if (!_isShowingCredits || _creditsSequenceIndex > _seqCredits->count() - 1) {
		_isShowingCredits = false;
		return;
	}

	drawSequenceFrame(_seqCredits, _creditsSequenceIndex, GraphicsManager::kBackgroundA);
	_creditsSequenceIndex++;
}

//////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////
void Menu::loadData() {
	bool loaded = true;

	// Special case: acorn highlight needs to be reloaded when showing the menu again in case we switched games
	// FIXME: rewrite to prevent leak
	if (SaveLoad::isSavegameValid(getNextGameId()))
		_seqAcorn = loadSequence(getAcornSequenceName(getNextGameId()));
	else
		_seqAcorn = loadSequence(getAcornSequenceName(kGameBlue));
	assert(loaded == true);

	// Check if we loaded sequences before
	if (_seqTooltips && _seqTooltips->count() > 0)
		return;

	// Load all static data
	_seqTooltips = loadSequence("helpnewr.seq");
	_seqEggButtons = loadSequence("buttns.seq");
	_seqButtons = loadSequence("quit.seq");

	_seqCredits = loadSequence("credits.seq");

	// Load the city buttons
	Sequence s("jlinetl.seq");
	loaded &= s.load(getArchive("jlinetl.seq"));
	_cityButtonFrames[0] = s.getFrame(0);

	loaded &= s.load(getArchive("jlinecen.seq"));
	for (int i = 0; i < 5; i++)
		_cityButtonFrames[i + 1] = s.getFrame((uint32)i);

	loaded &= s.load(getArchive("jlinebr.seq"));
	_cityButtonFrames[6] = s.getFrame(0);

	// We cannot proceed unless all files loaded properly
	assert(loaded == true);

	// FIXME: rewrite rest of function
	_frames[kOverlayTooltip] = new SequenceFrame(_seqTooltips);
	_frames[kOverlayEggButtons] = new SequenceFrame(_seqEggButtons);
	_frames[kOverlayButtons] = new SequenceFrame(_seqButtons);
	_frames[kOverlayAcorn] = new SequenceFrame(_seqAcorn);

	_frames[kOverlayCredits] = new SequenceFrame(_seqCredits);
}

// Get the sequence name to use for the acorn highlight, depending of the currently loaded savegame
Common::String Menu::getAcornSequenceName(GameId id) const {

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

// Get menu scene index
LastExpress::SceneIndex Menu::getSceneIndex() const {
	// TODO Do check for DWORD at text:004ADF70 < 0x1030EC

	// + 1 = normal menu with open egg / clock
	// + 2 = shield menu, when no savegame exists (no game has been started)
	return (SceneIndex)(SaveLoad::isSavegameValid(_gameId) ? _gameId * 5 + 1 : _gameId * 5 + 2);
}

//////////////////////////////////////////////////////////////////////////
// Time
//////////////////////////////////////////////////////////////////////////
void Menu::initTime(TimeType type, uint32 time) {
	if (!time)
		return;

	// The savegame entry index
	uint32 entryIndex = 0;

	switch (type) {
	default:
		break;

	case kTimeType0:
		entryIndex = (_index <= time) ? 1 : _index - time;
		break;

	case kTimeTypeTime:
		if (time < kTimeStartGame)
			break;

		entryIndex = _index;
		if (!entryIndex)
			break;

		// Iterate through existing entries
		do {
			if (getSaveLoad()->getEntry(entryIndex)->time <= time)
				break;

			entryIndex--;
		} while (entryIndex);
		break;

	case kTimeTypeEvent:
		entryIndex = _index;
		if (!entryIndex)
			break;

		do {
			if (getSaveLoad()->getEntry(entryIndex)->event == (EventIndex)time)
				break;

			entryIndex--;
		} while (entryIndex);
		break;

	case kTimeType3:
		// TODO rewrite in a more legible way
		if (_index > 1) {
			uint32 index = _index;
			do {
				if (getSaveLoad()->getEntry(index)->event == (EventIndex)time)
					break;

				index--;
			} while (index > 1);

			entryIndex = index - 1;
		} else {
			entryIndex = _index - 1;
		}
		break;
	}

	if (entryIndex) {
		_currentIndex = entryIndex;
		updateTime(getSaveLoad()->getEntry(entryIndex)->time);
	}
}

void Menu::updateTime(uint32 time) {
	if (_currentTime == _time)
		_delta = 0;

	_currentTime = time;

	if (_time != time) {
		if (getSound()->isBuffered(kEntityChapters))
			getSound()->removeFromQueue(kEntityChapters);

		getSound()->playSoundWithSubtitles((_currentTime >= _time) ? "LIB042.SND" : "LIB041.SND", 50855952, kEntityChapters);
		adjustIndex(_currentTime, _time, false);
	}
}

void Menu::adjustIndex(uint32 time1, uint32 time2, bool searchEntry) {
	uint32 index = 0;
	int32 timeDelta = -1;

	if (time1 != time2) {

		index = _index;

		if (time2 >= time1) {
			if (searchEntry) {
				uint32 currentIndex = _index;

				if ((int32)_index >= 0) {
					do {
						// Calculate new delta
						int32 newDelta = time1 - getSaveLoad()->getEntry(currentIndex)->time;

						if (newDelta >= 0 && timeDelta >= newDelta) {
							timeDelta = newDelta;
							index = currentIndex;
						}

						--currentIndex;
					} while ((int32)currentIndex >= 0);
				}
			} else {
				index = _index - 1;
			}
		} else {
			if (searchEntry) {
				uint32 currentIndex = _index;

				if (_index2 >= _index) {
					do {
						// Calculate new delta
						int32 newDelta = getSaveLoad()->getEntry(currentIndex)->time - time1;

						if (newDelta >= 0 && timeDelta > newDelta) {
							timeDelta = newDelta;
							index = currentIndex;
						}

						++currentIndex;
					} while (currentIndex >= _index2);
				}
			} else {
				index = _index + 1;
			}
		}

		_index = index;
		checkHotspots();
	}

	if (_index == _currentIndex) {
		if (getProgress().chapter != getSaveLoad()->getEntry(index)->chapter)
			getProgress().chapter = getSaveLoad()->getEntry(_index)->chapter;
	}
}

void Menu::goToTime(uint32 time) {

	uint32 entryIndex = 0;
	uint32 deltaTime = ABS((int)(getSaveLoad()->getEntry(0)->time - time));
	uint32 index = 0;

	do {
		uint32 deltaTime2 = ABS((int)(getSaveLoad()->getEntry(index)->time - time));
		if (deltaTime2 < deltaTime) {
			deltaTime = deltaTime2;
			entryIndex = index;
		}

		++index;
	} while (_index2 >= index);

	_currentIndex = entryIndex;
	updateTime(getSaveLoad()->getEntry(entryIndex)->time);
}

void Menu::setTime() {
	_currentIndex = _index;
	_currentTime = getSaveLoad()->getEntry(_currentIndex)->time;

	if (_time == _currentTime)
		adjustTime();
}

void Menu::forwardTime() {
	if (_index2 <= _index)
		return;

	_currentIndex = _index2;
	updateTime(getSaveLoad()->getEntry(_currentIndex)->time);
}

void Menu::rewindTime() {
	if (!_index)
		return;

	_currentIndex = 0;
	updateTime(getSaveLoad()->getEntry(_currentIndex)->time);
}

void Menu::adjustTime() {
	uint32 originalTime = _time;

	// Adjust time delta
	uint32 timeDelta = (_delta >= 90) ? 9 : (9 * _delta + 89) / 90;

	if (_currentTime < _time) {
		_time -= 900 * timeDelta;

		if (_time >= _currentTime)
			_time = _currentTime;
	} else {
		_time += 900 * timeDelta;

		if (_time < _currentTime)
			_time = _currentTime;
	}

	if (_currentTime == _time && getSound()->isBuffered(kEntityChapters))
		getSound()->removeFromQueue(kEntityChapters);

	_clock->draw(_time);
	_trainLine->draw(_time);
	getScenes()->drawFrames(true);

	adjustIndex(_time, originalTime, true);

	++_delta;
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
		playSfxStream("LIB046.SND");
		goToTime(time);
		// TODO set some global var to 1
	} else {
		StartMenuTooltips tooltip;
		if (_currentTime < time)
			tooltip = cityButtonsInfo[city].forward;
		else
			tooltip = cityButtonsInfo[city].rewind;
		drawSequenceFrame(_seqTooltips, tooltip, GraphicsManager::kBackgroundOverlay)
	}
}

//////////////////////////////////////////////////////////////////////////
// Sound / Brightness
//////////////////////////////////////////////////////////////////////////

// Get current volume (converted to in-game value)
uint32 Menu::getVolume() const {
	uint32 volume = (uint32)_engine->_mixer->getVolumeForSoundType(Audio::Mixer::kPlainSoundType);

	// Convert to in-game value [0-7]
	volume = (uint32)(volume * (7.0f / Audio::Mixer::kMaxMixerVolume));

	return volume;
}

// Set the volume (converts to ScummVM values)
void Menu::setVolume(uint32 volume) const {
	getState()->volume = volume;

	// Clamp volume
	uint32 value = volume * Audio::Mixer::kMaxMixerVolume / 7;

	if (value > Audio::Mixer::kMaxMixerVolume)
		value = Audio::Mixer::kMaxMixerVolume;

	_engine->_mixer->setVolumeForSoundType(Audio::Mixer::kPlainSoundType, (int32)value);

	// TODO: write to savegame ?
}

uint32 Menu::getBrightness() const {
	return getState()->brightness;
}

void Menu::setBrightness(uint32 brightness) const {
	getState()->brightness = brightness;

	// TODO: write to savegame
	// TODO: reload all graphics and adjust for the new brightness (or not :D)
}

} // End of namespace LastExpress
