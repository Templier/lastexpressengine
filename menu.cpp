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

#include "lastexpress/menu.h"

// Data
#include "lastexpress/animation.h"
#include "lastexpress/background.h"
#include "lastexpress/cursor.h"
#include "lastexpress/logic.h"
#include "lastexpress/scene.h"
#include "lastexpress/sound.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// DATA
//////////////////////////////////////////////////////////////////////////

// Train line times
const uint32 trainLineTimes[31] = { 1037700, // Paris
									1148400,
									1170900,
									1228500,
									1303200,
									1335600,
									1359900,
									1367100,
								    1490400, // Strasbourg
									1539000,
									1563300,
									1656000,
									1713600,
									1739700,
									1809900,
								    1852200, // Munich
									1984500,
									2049300,
									2075400,
									2101500,
									2154600,
								    2268000, // Vienna
									2383200,
									2418300,
								    2551500, // Budapest
									2952000, // Belgrade
									3205800,
									3492000,
									3690000,
									4320900,
								    4941000 /* Constantinople */ };

const uint32 trainCitiesIndex[31] = {0, // Paris
									 9, // Epernay
									 11, // Chalons
									 16, // Bar Le Duc
									 21, // Nancy
									 25, // Luneville
									 35, // Avricourt
									 37, // Deutsch Avricourt
									 40, // Strasbourg
									 53, // Baden Oos
									 56, // Karlsruhe
									 60, // Stuttgart
									 63, // Geislingen
									 66, // Ulm
									 68, // Augsburg
									 73, // Munich
									 84, // Salzbourg
									 89, // Attnang-Puchheim
									 97, // Wels
									 100, // Linz
									 104, // Amstetten
									 111, // Vienna
									 120, // Poszony
									 124, // Galanta
									 132, // Budapest
									 148, // Belgrade
									 /* Line 1 ends at 150 - line 2 begins at 0 */
									 157, // Nish
									 165, // Tzaribrod
									 174, // Sofia
									 198, // Adrianople
									 210  /* Constantinople */};

//////////////////////////////////////////////////////////////////////////

Menu::Menu(LastExpressEngine *engine) : _engine(engine) {
	_showStartScreen = true;
	_creditsSequenceIndex = 0;
	_isShowingCredits = false;

	_scene = new Scene(_engine->getResource());
}

Menu::~Menu() {
	delete _scene;
}

// Show the intro and load the main menu scene
//
// The main menu screen is a background plus 8 overlay elements
// .text:00448590 (EN)
void Menu::showMenu() {
	// Clear screen
	_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundAll);

	// Load all menu-related data
	loadData();

	// If no blue savegame exists, this might be the first time we start the game, so we show the full intro
	if (_showStartScreen) {
		_engine->getCursor()->show(false);
		if (!SaveLoad::isSavegameValid(SaveLoad::kSavegameBlue)) {
			Animation animation;

			// Show Broderbrund logo
			if (animation.loadFile("1930.nis"))
				animation.process();

			// Play intro music
			playMusic("MUS001.SND");

			// Show The Smoking Car logo
			if (animation.loadFile("1931.nis"))
				animation.process();

			_showStartScreen = false;
		} else {
			playMusic("mus018.snd");

			showScene(_scene, 65, GraphicsManager::kBackgroundC);
			askForRedraw(); redrawScreen();
			//_engine->_system->delayMillis(1000);

			_showStartScreen = false;
		}
	}

	// Set Cursor type
	_engine->getCursor()->setStyle(Cursor::kCursorNormal);
	_engine->getCursor()->show(true);

	// Load scene
	showScene(_scene, getSceneIndex(), GraphicsManager::kBackgroundC);
	drawElements();

	// Init time
	_currentTime = getState()->time;

	askForRedraw();
}

// Get menu scene index
uint32 Menu::getSceneIndex() {
	// TODO Do check for DWORD at text:004ADF70 < 0x1030EC

	// + 1 = normal menu with open egg / clock
	// + 2 = shield menu, when no savegame exists (no game has been started)
	return (SaveLoad::isSavegameValid(getGameId())) ? getGameId() * 5 + 1 : getGameId() * 5 + 2;
}

// Handle events
bool Menu::handleStartMenuEvent(Common::Event ev) {

	// Special case if we are showing credits (only allow left & right-click)
	if (_isShowingCredits) {
		// Interrupt on right click
		switch(ev.type) {
			case Common::EVENT_RBUTTONDOWN:
				_isShowingCredits = false;	// Will cause credits to stop & reset overlays
			case Common::EVENT_LBUTTONDOWN:
				showCredits();
				askForRedraw();
			default:
				return true;
		}
	}

	// Process event (check hit box / etc.)
	static Menu::StartMenuEvent event;
	if (!_scene->checkHotSpot(getState()->currentScene, ev.mouse, (byte *)&event)) {
		clearBg(GraphicsManager::kBackgroundOverlay);
		askForRedraw();
		return true;
	}

	bool clicked = (ev.type == Common::EVENT_LBUTTONDOWN);
	clearBg(GraphicsManager::kBackgroundOverlay);

	switch(event) {
	default:
		break;

	case kEventCase4:
		// TODO reset time variable (and fall down to kEventContinue)

	case kEventContinue:
		// TODO Check for cd archive: reload the proper archive here if running in single cd mode
		if (!_engine->getLogic()->isGameStarted()) {
			drawSeqFrame(&_seqEggButtons, kButtonShield, GraphicsManager::kBackgroundOverlay);
			drawSeqFrame(&_seqTooltips, kTooltipPlayNewGame, GraphicsManager::kBackgroundOverlay);
		} else {
			drawSeqFrame(&_seqEggButtons, kButtonContinue, GraphicsManager::kBackgroundOverlay);

			// FIXME: using different global in original game -> find out what they do
			if (_currentTime == getState()->time) { // will break since we adjust the game time with rewind/forward/cities
				// TODO check if game is finished
				//if (isGameFinished())
				//	_seqTooltips.showFrameOverlay(kTooltipViewGameEnding);
				//else
					drawSeqFrame(&_seqTooltips, kTooltipContinueGame, GraphicsManager::kBackgroundOverlay);
			} else {
				drawSeqFrame(&_seqTooltips, kTooltipContinueRewoundGame, GraphicsManager::kBackgroundOverlay);
			}
		}

		if (!clicked)
			break;

		playSfx("LIB046.snd");

		// TODO: to implement in logic...
		//  - load new data file
		//  - show intro if new game
		//  - Reset save game & "save points"
		//  - etc.
		{
			getState()->currentScene = 255; // HACK to not show menu after we are finished
			clearBg(GraphicsManager::kBackgroundAll);

			showScene(_scene, 5 * getGameId() + 3, GraphicsManager::kBackgroundC);
			askForRedraw(); redrawScreen();
			_engine->_system->delayMillis(1000);

			showScene(_scene, 5 * getGameId() + 4, GraphicsManager::kBackgroundC);
			askForRedraw(); redrawScreen();
			_engine->_system->delayMillis(1000);

			showScene(_scene, 5 * getGameId() + 5, GraphicsManager::kBackgroundC);
			askForRedraw(); redrawScreen();
			_engine->_system->delayMillis(1000);

			// Show intro
			Animation animation;
			if (animation.loadFile("1601.nis"))
				animation.process();

			clearBg(GraphicsManager::kBackgroundAll);

			// Reset scene
			getState()->currentScene = 0;
			_engine->getLogic()->showMenu(false);
		}



		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventCredits:
		if (clicked) {
			drawSeqFrame(&_seqTooltips, kButtonCreditsPushed, GraphicsManager::kBackgroundOverlay);
			playSfx("LIB046.snd");
			_isShowingCredits = true;
			_creditsSequenceIndex = 0;
			showCredits();
		} else {
			drawSeqFrame(&_seqEggButtons, kButtonCredits, GraphicsManager::kBackgroundOverlay);
			drawSeqFrame(&_seqTooltips, kTooltipCredits, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventQuitGame:
		drawSeqFrame(&_seqTooltips, kTooltipQuit, GraphicsManager::kBackgroundOverlay);

		if (clicked) {
			drawSeqFrame(&_seqButtons, kButtonQuitPushed, GraphicsManager::kBackgroundOverlay);
			playSfx("LIB046.snd");

			//TODO some stuff... see disasm
			return false;
		} else {
			drawSeqFrame(&_seqButtons, kButtonQuit, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventSwitchSaveGame:
		if (clicked) {
			drawSeqFrame(&_seqAcorn, 1, GraphicsManager::kBackgroundOverlay);
			playSfx("LIB046.snd");
			_engine->getLogic()->switchGame();
			// the menu should have been reset & redrawn, so don't do anything else here
		} else {
			drawSeqFrame(&_seqAcorn, 0, GraphicsManager::kBackgroundOverlay);

			if (!SaveLoad::isSavegameValid(getNextGameId())) {
				if (_engine->getLogic()->isGameStarted())
					drawSeqFrame(&_seqTooltips, kTooltipStartAnotherGame, GraphicsManager::kBackgroundOverlay)
				else
					drawSeqFrame(&_seqTooltips, kTooltipSwitchBlueGame, GraphicsManager::kBackgroundOverlay);
			} else {
				// Stupid tooltips ids are not in order, so we can't just increment them...
				switch(getGameId()) {
					case SaveLoad::kSavegameBlue:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchRedGame, GraphicsManager::kBackgroundOverlay);
						break;

					case SaveLoad::kSavegameRed:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchGreenGame, GraphicsManager::kBackgroundOverlay);
						break;

					case SaveLoad::kSavegameGreen:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchPurpleGame, GraphicsManager::kBackgroundOverlay);
						break;

					case SaveLoad::kSavegamePurple:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchTealGame, GraphicsManager::kBackgroundOverlay);
						break;

					case SaveLoad::kSavegameTeal:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchGoldGame, GraphicsManager::kBackgroundOverlay);
						break;

					case SaveLoad::kSavegameGold:
						drawSeqFrame(&_seqTooltips, kTooltipSwitchBlueGame, GraphicsManager::kBackgroundOverlay);
						break;
				}
			}
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventRewindGame:
		// TODO check that we can actually rewind
		//if (_currentTime <= getState()->time)
		if (clicked) {
			drawSeqFrame(&_seqEggButtons, kButtonRewindPushed, GraphicsManager::kBackgroundOverlay);
			playSfx("LIB046.snd");
			// TODO rewind clock
			//goToTime(XXX + 8);
		} else {
			drawSeqFrame(&_seqEggButtons, kButtonRewind, GraphicsManager::kBackgroundOverlay);
			drawSeqFrame(&_seqTooltips, kTooltipRewind, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventForwardGame:
		// TODO check that we can actually rewind
		if (_currentTime == getState()->time)
			break;

		if (clicked) {
			drawSeqFrame(&_seqEggButtons, kButtonForwardPushed, GraphicsManager::kBackgroundOverlay);
			playSfx("LIB046.snd");

			// TODO advance clock
			//goToTime(32 * ??? + XXX + 8);

		} else {
			drawSeqFrame(&_seqEggButtons, kButtonForward, GraphicsManager::kBackgroundOverlay);
			drawSeqFrame(&_seqTooltips, kTooltipFastForward, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventParis:
		moveToCity(kParis, kTimeParis, kTooltipRewindParis, kTooltipRewindParis, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventStrasBourg:
		moveToCity(kStrasbourg, kTimeStrasbourg, kTooltipRewindStrasbourg, kTooltipForwardStrasbourg, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventMunich:
		moveToCity(kMunich, kTimeMunich, kTooltipRewindMunich, kTooltipForwardMunich, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventVienna:
		moveToCity(kVienna, kTimeVienna, kTooltipRewindVienna, kTooltipForwardVienna, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventBudapest:
		moveToCity(kBudapest, kTimeBudapest, kTooltipRewindBudapest, kTooltipForwardBudapest, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventBelgrade:
		moveToCity(kBelgrade, kTimeBelgrade, kTooltipRewindBelgrade, kTooltipForwardBelgrade, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventConstantinople:
		moveToCity(kConstantinople, kTimeEnding, kTooltipForwardConstantinople, kTooltipForwardConstantinople, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventDecreaseVolume:
		// Cannot decrease volume further
		if (getVolume() == 0) {
			drawSeqFrame(&_seqButtons, kButtonVolume, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSeqFrame(&_seqTooltips, kTooltipVolumeDown, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			drawSeqFrame(&_seqButtons, kButtonVolumeDownPushed, GraphicsManager::kBackgroundOverlay);
			playSfx("LIB046.snd");
			setVolume(getVolume() - 1);
		} else {
			drawSeqFrame(&_seqButtons, kButtonVolumeDown, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventIncreaseVolume:
		// Cannot increase volume further
		if (getVolume() >= 7) {
			drawSeqFrame(&_seqButtons, kButtonVolume, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSeqFrame(&_seqTooltips, kTooltipVolumeUp, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			drawSeqFrame(&_seqButtons, kButtonVolumeUpPushed, GraphicsManager::kBackgroundOverlay);
			playSfx("LIB046.snd");
			setVolume(getVolume() + 1);
		} else {
			drawSeqFrame(&_seqButtons, kButtonVolumeUp, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventDecreaseBrightness:
		// Cannot increase brightness further
		if (getBrightness() == 0) {
			drawSeqFrame(&_seqButtons, kButtonBrightness, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSeqFrame(&_seqTooltips, kTooltipBrightnessDown, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			drawSeqFrame(&_seqButtons, kButtonBrightnessDownPushed, GraphicsManager::kBackgroundOverlay);
			playSfx("LIB046.snd");

			setBrightness(getBrightness() + 1);
		} else {
			drawSeqFrame(&_seqButtons, kButtonBrightnessDown, GraphicsManager::kBackgroundOverlay);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventIncreaseBrightness:
		// Cannot increase brightness further
		if (getBrightness() >= 6) {
			drawSeqFrame(&_seqButtons, kButtonBrightness, GraphicsManager::kBackgroundOverlay);
			break;
		}

		drawSeqFrame(&_seqTooltips, kTooltipBrightnessUp, GraphicsManager::kBackgroundOverlay);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			drawSeqFrame(&_seqButtons, kButtonBrightnessUpPushed, GraphicsManager::kBackgroundOverlay);
			playSfx("LIB046.snd");
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
		loaded &= _seqAcorn.loadFile(getAcornSequenceName(SaveLoad::kSavegameBlue));
	assert(loaded == true);

	// Check if we loaded sequences before
	if (_seqTooltips.count() > 0)
		return;

	// Load all static data
	loaded  &= _seqHour.loadFile("egghour.seq");
	loaded  &= _seqMinutes.loadFile("eggmin.seq");
	loaded  &= _seqSun.loadFile("sun.seq");
	loaded  &= _seqDate.loadFile("datenew.seq");

	loaded  &= _seqTooltips.loadFile("helpnewr.seq");
	loaded  &= _seqEggButtons.loadFile("buttns.seq");
	loaded  &= _seqButtons.loadFile("quit.seq");
	loaded  &= _seqCityStart.loadFile("jlinetl.seq");
	loaded  &= _seqCities.loadFile("jlinecen.seq");
	loaded  &= _seqCityEnd.loadFile("jlinebr.seq");
	loaded  &= _seqLine1.loadFile("line1.seq");
	loaded  &= _seqLine2.loadFile("line2.seq");

	loaded  &= _seqCredits.loadFile("credits.seq");

	// Load scene
	loaded &= _scene->loadScene(1);

	// We cannot proceed unless all files loaded properly
	assert(loaded == true);
}

// Get the sequence name to use for the acorn highlight, depending of the currently loaded savegame
Common::String Menu::getAcornSequenceName(SaveLoad::SavegameId id) {

	// end of text:00449d80 (also sets up the main menu scene)

	// TODO replace with string array and access by index?
	Common::String name = "";
	switch (id) {
	default:
	case SaveLoad::kSavegameBlue:
		name = "aconblu3.seq";
		break;

	case SaveLoad::kSavegameRed:
		name = "aconred.seq";
		break;

	case SaveLoad::kSavegameGreen:
		name = "acongren.seq";
		break;

	case SaveLoad::kSavegamePurple:
		name = "aconpurp.seq";
		break;

	case SaveLoad::kSavegameTeal:
		name = "aconteal.seq";
		break;

	case SaveLoad::kSavegameGold:
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
	if (!SaveLoad::isSavegameValid(getGameId()))
		return;

	clearBg(GraphicsManager::kBackgroundA);

	drawClock(_currentTime);
	drawTrainLine(_currentTime);
}

// Draw the clock hands at the time
void Menu::drawClock(uint32 time) {
	// 7:14 p.m. on July 24, 1914 (= 1037700)
	// 7:30 p.m. on July 26, 1914 (= 4941000)

	// 360 degrees = 1296000 (360*60*60) minutes of arc
	// 129600 / 24 = 54000
	// 54000 / 60 = 900

	// FIXME the hours are not moving along with minutes as in-game

	// Calculate each sequence index from the current time
	uint32 hours = time % 1296000 / 54000;
	uint32 index_minutes = time % 54000 / 900 % 60 % 60;
	uint32 index_hour = 5 * (index_minutes / 60 + hours % 12) % 60;
	uint32 index_sun = 5 * (index_minutes / 60 + hours) % 120;
	uint32 index_date = 18 * time / 1296000;
	if (hours == 23)
		index_date += 18 * index_minutes / 60;

	// Draw each element
	drawSeqFrame(&_seqHour, index_hour, GraphicsManager::kBackgroundA);
	drawSeqFrame(&_seqMinutes, index_minutes, GraphicsManager::kBackgroundA);
	drawSeqFrame(&_seqSun, index_sun, GraphicsManager::kBackgroundA);
	drawSeqFrame(&_seqDate, index_date, GraphicsManager::kBackgroundA);
}

// Draw the train line at the time
//  line1: 150 frames (=> Belgrade)
//  line2: 61 frames (=> Constantinople)
// text:0042E710
void Menu::drawTrainLine(uint32 time) {
	uint ixTime;

	// Get index of the closest train line time to the current time
	for (ixTime = 0; ixTime < sizeof(trainLineTimes) - 1; ixTime++)
		if (_currentTime <= trainLineTimes[ixTime])
			break;

	// Get index of city
	uint32 index = trainCitiesIndex[ixTime - 1];	// NOTE: disasm is accessing cities array starting from index -1 (= 0) - ie they have two 0 at the start of the array

	// FIXME do some stuff on index... as right now we jump from cities to cities

	if (index >= _seqLine1.count()) { // we passed Belgrade
		drawSeqFrame(&_seqLine1, _seqLine1.count() - 1, GraphicsManager::kBackgroundA);
		drawSeqFrame(&_seqLine2, index, GraphicsManager::kBackgroundA);
	} else {
		drawSeqFrame(&_seqLine1, index, GraphicsManager::kBackgroundA);
		// no need to draw from line2
	}
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
	//;getState()->time = time;		// need to use targetTime var, as modifying the global state will prevent us from going into the other direction later

	// Nothing to do if the menu time is already set to the correct value
	// FIXME can this really happen?
	if (_currentTime == time)
		return;

	int direction = 1;
	int speed = 1;

	if (_currentTime <= time) {
		playSfx("LIB042.SND");
	} else {
		playSfx("LIB041.SND");
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
	_engine->getSfxStream()->stop();
}

void Menu::moveToCity(CityOverlay city, CityTime time, StartMenuTooltips tooltipRewind, StartMenuTooltips tooltipForward, bool clicked) {
	// TODO Check if we have access (there seems to be more checks on some internal times) - probably : current_time (menu only) / game time / some other?
	if (getState()->time < (uint32)time || _currentTime == (uint32)time) {
		return;
	}

	// Show city overlay
	switch (city) {
	case kParis:
		drawSeqFrame(&_seqCityStart, 0, GraphicsManager::kBackgroundOverlay);
		break;

	case kConstantinople:
		drawSeqFrame(&_seqCityEnd, 0, GraphicsManager::kBackgroundOverlay);
		break;

	default:
		drawSeqFrame(&_seqCities, city, GraphicsManager::kBackgroundOverlay);
	}

	if (clicked) {
		playSfx("LIB046.snd");
		goToTime(time);
		// TODO set some global var to 1
	} else {
		if (_currentTime < (uint32)time)			// For start city (Paris) and end city, this will always be true
			drawSeqFrame(&_seqTooltips, tooltipForward, GraphicsManager::kBackgroundOverlay)
		else
			drawSeqFrame(&_seqTooltips, tooltipRewind, GraphicsManager::kBackgroundOverlay);
	}
}

//////////////////////////////////////////////////////////////////////////
// Sound / Brightness
//////////////////////////////////////////////////////////////////////////

// Get current volume (converted to in-game value)
int Menu::getVolume() {
	int volume = _engine->_mixer->getVolumeForSoundType(Audio::Mixer::kPlainSoundType);

	// Convert to in-game value [0-7]
	volume *= 7.0 / Audio::Mixer::kMaxMixerVolume;

	return volume;
}

// Set the volume (converts to ScummVM values)
void Menu::setVolume(int volume) {
	getState()->volume = volume;

	// Clamp volume
	int value = volume * Audio::Mixer::kMaxMixerVolume / 7.0;
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
