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
const uint32 trainLineTimes[31] = { /* Start */ 1037700 , 1148400, 1170900, 1228500, 1303200, 1335600, 1359900, 1367100,
								  /* Strasbourg */ 1490400, 1539000, 1563300, 1656000, 1713600, 1739700, 1809900,
								  /* Munich */ 1852200, 1984500, 2049300, 2075400, 2101500, 2154600,
								  /* Vienna */ 2268000, 2383200, 2418300,
								  /* Budapest */ 2551500,
								  /* Belgrade */ 2952000, 3205800, 3492000, 3690000, 4320900,
								  /* Constantinople */ 4941000 };

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
}

Menu::~Menu() {
	SAFE_DELETE(_scene);
}

// Show the intro and load the main menu scene
//
// The main menu screen is a background plus 8 overlay elements
// .text:00448590 (EN)
void Menu::showMenu() {

	// Load all menu-related data
	loadData();

	_engine->getCursor()->show(false);

	// If no blue savegame exists, this might be the first time we start the game, so we show the full intro
	if (!SaveLoad::isSavegameValid(SaveLoad::kSavegameBlue)) {
		if (_showStartScreen) {
			Animation animation;

			// Show Broderbrund logo
			if (animation.loadFile("1930.nis"))
				animation.show();

			// Play intro music
			playMusic("MUS001.SND");

			// Show The Smoking Car logo
			if (animation.loadFile("1931.nis"))
				animation.show();

			_showStartScreen = false;
		}
	} else {
		if (_showStartScreen) {
			playMusic("mus018.snd");

			_scene->showScene(C, 65);
			askForRedraw(); redrawScreen();
			_engine->_system->delayMillis(1000);

			_showStartScreen = false;
		}
	}

	// Set Cursor type
	_engine->getCursor()->setStyle(Cursor::CursorNormal);
	_engine->getCursor()->show(true);

	// TODO Load Main menu scene (sceneIndex = 5 * savegame id (+ 1/2)) - see text:00449d80
	_scene->showScene(C, 1);
	getState()->currentScene = 1;

	// Draw default elements
	clearBg(A);
	drawClock(getState()->currentTime);
	drawTrainLine(getState()->currentTime);

	askForRedraw();
}

// Handle events
bool Menu::handleStartMenuEvent(Common::Event ev) {
	clearBgOverlay();

	// Process event (check hit box / etc.)
	static Menu::StartMenuEvent event;
	if (!_scene->checkHotSpot(getState()->currentScene, ev.mouse, (byte*)&event))
		return true;

	// Special case if we are showing credits (only allow left-click & right-click)
	if (_isShowingCredits) {
		// Interrupt on right click
		if (ev.type == Common::EVENT_RBUTTONDOWN)
			_isShowingCredits = false;				// Will cause credits to stop & reset overlays

		showCredits();
		askForRedraw();
		return true;
	}

	bool clicked = (ev.type == Common::EVENT_LBUTTONDOWN);

	switch(event) {
	default:
		break;

	case kEventCase1:
	case kEventCase4:
		// FIXME: understand code...
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventCredits:
		if (clicked) {
			_seqEggButtons.showFrameOverlay(kButtonCreditsPushed);
			playSfx("LIB046.snd");
			_isShowingCredits = true;
			_creditsSequenceIndex = 0;
			showCredits();
		} else {
			_seqEggButtons.showFrameOverlay(kButtonCredits);
			_seqTooltips.showFrameOverlay(kTooltipCredits);
		}
		return true;

	//////////////////////////////////////////////////////////////////////////
	case kEventQuitGame:
		_seqTooltips.showFrameOverlay(kTooltipQuit);

		if (clicked) {
			_seqButtons.showFrameOverlay(kButtonQuitPushed);
			playSfx("LIB046.snd");
			askForRedraw();

			//TODO some stuff... see disasm
			return false;
		} else {
			_seqButtons.showFrameOverlay(kButtonQuit);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventSwitchSaveGame:
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventRewindGame:
		// TODO check that we can actually rewind
		if (clicked) {
			_seqEggButtons.showFrameOverlay(kButtonRewindPushed);
			playSfx("LIB046.snd");

			// TODO rewind clock

		} else {
			_seqEggButtons.showFrameOverlay(kButtonRewind);
			_seqTooltips.showFrameOverlay(kTooltipRewind);
		}
		return true;

	//////////////////////////////////////////////////////////////////////////
	case kEventForwardGame:
		// TODO check that we can actually rewind
		if (clicked) {
			_seqEggButtons.showFrameOverlay(kButtonForwardPushed);
			playSfx("LIB046.snd");

			// TODO advance clock

		} else {
			_seqEggButtons.showFrameOverlay(kButtonForward);
			_seqTooltips.showFrameOverlay(kTooltipFastForward);
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
	case kEventEnding:
		moveToCity(kEnding, kTimeEnding, kTooltipForwardEnding, kTooltipForwardEnding, clicked);
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventDecreaseVolume:
		// Cannot decrease volume further
		if (getVolume() == 0) {
			_seqButtons.showFrameOverlay(kButtonVolume);
			break;
		}

		_seqTooltips.showFrameOverlay(kTooltipVolumeDown);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			_seqButtons.showFrameOverlay(kButtonVolumeDownPushed);
			playSfx("LIB046.snd");
			setVolume(getVolume() - 1);
		} else {
			_seqButtons.showFrameOverlay(kButtonVolumeDown);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventIncreaseVolume:
		// Cannot increase volume further
		if (getVolume() >= 7) {
			_seqButtons.showFrameOverlay(kButtonVolume);
			break;
		}

		_seqTooltips.showFrameOverlay(kTooltipVolumeUp);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			_seqButtons.showFrameOverlay(kButtonVolumeUpPushed);
			playSfx("LIB046.snd");
			setVolume(getVolume() + 1);
		} else {
			_seqButtons.showFrameOverlay(kButtonVolumeUp);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventDecreaseBrightness:
		// Cannot increase brightness further
		if (getBrightness() == 0) {
			_seqButtons.showFrameOverlay(kButtonBrightness);
			break;
		}

		_seqTooltips.showFrameOverlay(kTooltipBrightnessDown);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			_seqButtons.showFrameOverlay(kButtonBrightnessDownPushed);
			playSfx("LIB046.snd");

			setBrightness(getBrightness() + 1);
		} else {
			_seqButtons.showFrameOverlay(kButtonBrightnessDown);
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventIncreaseBrightness:
		// Cannot increase brightness further
		if (getBrightness() >= 6) {
			_seqButtons.showFrameOverlay(kButtonBrightness);
			break;
		}

		_seqTooltips.showFrameOverlay(kTooltipBrightnessUp);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			_seqButtons.showFrameOverlay(kButtonBrightnessUpPushed);
			playSfx("LIB046.snd");
			setBrightness(getBrightness() + 1);
		} else {
			_seqButtons.showFrameOverlay(kButtonBrightnessUp);
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
	// Check if we loaded sequences before
	if (_seqTooltips.count() > 0)
		return;

	bool loaded = true;

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

	loaded  &= _seqAcorn.loadFile(getAcornHighlight(_engine->getLogic()->getSavegameId()));
	loaded  &= _seqCredits.loadFile("credits.seq");

	// Load scene
	_scene = new Scene(_engine->getResource());
	loaded &= _scene->loadScene(1);

	// We cannot proceed unless all files loaded properly
	assert(loaded == true);
}

// Get the sequence name to use for the acorn highlight, depending of the currently loaded savegame
Common::String Menu::getAcornHighlight(SaveLoad::SavegameId id) {

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
	_seqHour.showFrameBg(A, index_hour);
	_seqMinutes.showFrameBg(A, index_minutes);
	_seqSun.showFrameBg(A, index_sun);
	_seqDate.showFrameBg(A, index_date);
}

// Draw the train line at the time
//  line1: 150 frames (=> Belgrade)
//  line2: 61 frames (=> Constantinople)
// text:0042E710
void Menu::drawTrainLine(uint32 time) {
	uint ixTime;

	// Get index of the closest train line time to the current time
	for (ixTime = 0; ixTime < sizeof(trainLineTimes) - 1; ixTime++)
		if (getCurrentTime() <= trainLineTimes[ixTime])
			break;

	// Get index of city
	uint32 index = trainCitiesIndex[ixTime - 1];	// NOTE: disasm is accessing cities array starting from index -1 (= 0) - ie they have two 0 at the start of the array

	// FIXME do some stuff on index... as right now we jump from cities to cities

	if (index >= _seqLine1.count()) { // we passed Belgrade
		_seqLine1.showFrameBg(A, _seqLine1.count() - 1);
		_seqLine2.showFrameBg(A, index);
	} else {
		_seqLine1.showFrameBg(A, index);
		// no need to draw from line2
	}
}

// Show credits overlay
void Menu::showCredits() {
	if (!_isShowingCredits || _creditsSequenceIndex > _seqCredits.count() - 1) {
		_isShowingCredits = false;
		return;
	}

	_seqCredits.showFrameOverlay(_creditsSequenceIndex);
	_creditsSequenceIndex++;
}

//////////////////////////////////////////////////////////////////////////
// Time
//////////////////////////////////////////////////////////////////////////

uint32 Menu::getCurrentTime() {
	// FIXME this is the time as showed on the menu, which might be different from the max time attained in the game by the player

	// return current time as if we already rewinded
	return getState()->currentTime;
}

uint32 Menu::getMaxGameTime() {
	// FIXME check disasm
	// DEBUG value
	return getState()->currentTime + 54360;
}

void Menu::goToTime(uint32 time) {
	// TODO implement modifying the current game time
	// + adjusting elements on screen : clock + train line
}

void Menu::moveToCity(CityOverlay city, CityTime time, StartMenuTooltips tooltipRewind, StartMenuTooltips tooltipForward, bool clicked) {
	// TODO Check if we have access (there seems to be more checks on some internal times) - probably : current_time / max_game_time / some other?
	if (getMaxGameTime() < (uint32)time || getCurrentTime() == (uint32)time) {
		return;
	}

	// Show city overlay
	switch (city) {
	case kParis:
		_seqCityStart.showFrameOverlay(0);
		break;

	case kEnding:
		_seqCityEnd.showFrameOverlay(0);
		break;

	default:
		_seqCities.showFrameOverlay(city);
	}

	if (clicked) {
		playSfx("LIB046.snd");
		goToTime(time);
		// TODO set some global var to 1
	} else {
		if (getCurrentTime() < (uint32)time)			// For start city (Paris) and end city, this will always be true
			_seqTooltips.showFrameOverlay(tooltipForward);
		else
			_seqTooltips.showFrameOverlay(tooltipRewind);
	}
}

//////////////////////////////////////////////////////////////////////////
// Sound / Brightness
//////////////////////////////////////////////////////////////////////////

// Get current volume (converted to in-game value)
int Menu::getVolume() {
	int volume = _engine->_mixer->getVolumeForSoundType(Audio::Mixer::kPlainSoundType);

	// Convert to in-game value [0-7]
	volume *= 7.0/Audio::Mixer::kMaxMixerVolume;

	return volume;
}

// Set the volume (converts to ScummVM values)
void Menu::setVolume(int volume) {
	getState()->volume = volume;

	// Clamp volume
	int value = volume * Audio::Mixer::kMaxMixerVolume/7.0;
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
