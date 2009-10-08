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
#include "lastexpress/sequence.h"
#include "lastexpress/sound.h"

#include "lastexpress/debug.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

#include "graphics/cursorman.h"

namespace LastExpress {

Menu::Menu(LastExpressEngine *engine) : _engine(engine) {
	// FIXME: skip intro
	_showStartScreen = false;
	_creditsSequenceIndex = 0;
	_isShowingCredits = false;
}

Menu::~Menu() {}

// Show the intro and load the main menu scene
//
// The main menu screen is a background plus 8 overlay elements
// .text:00448590 (EN)
void Menu::showMenu() {

	//Scene scene(_engine->_resource);
	//scene.load(1);
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

			// FIXME load data from scene: sceneIndex = 65
			// Show Start screen
			Background background;
			if (background.loadFile("autoplay.bg"))
				background.show();

			_showStartScreen = false;
		}
	}

	// Set Cursor type
	_engine->getCursor()->setStyle(Cursor::CursorNormal);
	_engine->getCursor()->show(true);

	// Load all menu-related sequences
	loadSequences();

	// TODO Load Main menu scene (sceneIndex = 5 * savegame id (+ 1/2)) - see text:00449d80
	Background background;
	if (background.loadFile("clock01.bg"))
		background.show();

	// FIXME set properly
	_engine->getLogic()->getGameState()->currentScene = 1;
	_engine->getLogic()->getGameState()->currentTime = 1759500;

	// Draw default elements
	drawClock(_engine->getLogic()->getGameState()->currentTime);
	drawTrainLine(_engine->getLogic()->getGameState()->currentTime);
}

// Handle events
bool Menu::handleStartMenuEvent(Common::Event ev) {

	// TODO Process event (check hitbox / etc.)
	// coordinates: ev.mouse.x, ev.mouse.y
	//bool clicked = (ev.type == Common::EVENT_LBUTTONDOWN);
	
	//////////////////////////////////////////////////////////////////////////
	// DEBUG
	if (ev.type == Common::EVENT_MOUSEMOVE)
		return true;

	static Menu::StartMenuEvent event = (Menu::StartMenuEvent)-1;
	static bool clicked = true;
	event = (Menu::StartMenuEvent)((event + 1) % 21);
	clicked = !clicked;
	//////////////////////////////////////////////////////////////////////////

	// Special case if we are showing credits (only allow left-click & right-click)
	if (_isShowingCredits) {
		// Interrupt on right click
		if (ev.type == Common::EVENT_RBUTTONDOWN)
			_isShowingCredits = false;				// Will cause credits to stop & reset overlays

		showCredits();
		return true;
	}
	
	switch(event) {
	default:
		hideOverlays();
		return true;

	case kEventCase1:
	case kEventCase4:
		// FIXME: understand code...
		return true;

	//////////////////////////////////////////////////////////////////////////
	case kEventCredits:
		if (clicked) {
			_seqEggButtons.show(kButtonCreditsPushed);			
			playSfx("LIB046.snd");
			hideOverlays();
			_isShowingCredits = true;
			_creditsSequenceIndex = 0;
			showCredits();			
		} else {
			_seqEggButtons.show(kButtonCredits);
			_seqTooltips.show(kTooltipCredits);
		}
		return true;

	//////////////////////////////////////////////////////////////////////////
	case kEventQuitGame:
		_seqTooltips.show(kTooltipQuit);
		
		if (clicked) {
			_seqButtons.show(kButtonQuitPushed);	
			playSfx("LIB046.snd");

			//TODO some stuff... see disasm
			return false;
		} else {
			_seqButtons.show(kButtonQuit);		
			return true;
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventSwitchSaveGame:
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventRewindGame:
		// TODO check that we can actually rewind
		if (clicked) {
			_seqEggButtons.show(kButtonRewindPushed);
			hideOverlays();
			playSfx("LIB046.snd");

			// TODO rewind clock

		} else {
			_seqEggButtons.show(kButtonRewind);
			_seqTooltips.show(kTooltipRewind);
		}
		return true;

	//////////////////////////////////////////////////////////////////////////
	case kEventForwardGame:
		// TODO check that we can actually rewind
		if (clicked) {
			_seqEggButtons.show(kButtonForwardPushed);
			hideOverlays();
			playSfx("LIB046.snd");

			// TODO advance clock

		} else {
			_seqEggButtons.show(kButtonForward);
			_seqTooltips.show(kTooltipFastForward);
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
			_seqButtons.show(kButtonVolume);
			hideOverlays();
			return true;
		}

		_seqTooltips.show(kTooltipVolumeDown);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			_seqButtons.show(kButtonVolumeDownPushed);
			playSfx("LIB046.snd");
			setVolume(getVolume() - 1);
		} else {
			_seqButtons.show(kButtonVolumeDown);			
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventIncreaseVolume:
		// Cannot increase volume further
		if (getVolume() >= 7) {
			_seqButtons.show(kButtonVolume);
			hideOverlays();
			return true;
		}

		_seqTooltips.show(kTooltipVolumeUp);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			_seqButtons.show(kButtonVolumeUpPushed);
			playSfx("LIB046.snd");
			setVolume(getVolume() + 1);
		} else {
			_seqButtons.show(kButtonVolumeUp);			
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventDecreaseBrightness:
		// Cannot increase brightness further
		if (getBrightness() == 0) {
			_seqButtons.show(kButtonBrightness);
			hideOverlays();
			return true;
		}

		_seqTooltips.show(kTooltipBrightnessDown);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			_seqButtons.show(kButtonBrightnessDownPushed);
			playSfx("LIB046.snd");

			setBrightness(getBrightness() + 1);
		} else {
			_seqButtons.show(kButtonBrightnessDown);			
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case kEventIncreaseBrightness:
		// Cannot increase brightness further
		if (getBrightness() >= 6) {
			_seqButtons.show(kButtonBrightness);
			hideOverlays();
			return true;
		}

		_seqTooltips.show(kTooltipBrightnessUp);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			_seqButtons.show(kButtonBrightnessUpPushed);
			playSfx("LIB046.snd");
			setBrightness(getBrightness() + 1);
		} else {
			_seqButtons.show(kButtonBrightnessUp);			
		}
		break;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////

void Menu::loadSequences() {
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

	// Calculate each sequence index from the current time
	uint32 hours = time % 1296000 / 54000;
	uint32 index_minutes = time % 54000 / 900 % 60 % 60;
	uint32 index_hour = 5 * (index_minutes / 60 + hours % 12) % 60;	
	uint32 index_sun = 5 * (index_minutes / 60 + hours) % 120;
	uint32 index_date = 18 * time / 1296000;
	if (hours == 23)
		index_date += 18 * index_minutes / 60;

	// Draw each element
	_seqHour.show(index_hour);
	_seqMinutes.show(index_minutes);
	_seqSun.show(index_sun);
	_seqDate.show(index_date);
}

// Draw the train line at the time
void Menu::drawTrainLine(uint32 time) {

}

// Hide all overlay frames on the start menu (tooltips, highlights)
void Menu::hideOverlays() {
	// TODO implement: get back graphics class and use several surface for background / elements / overlay
	// hiding overlays will consist in dropping the surface contents, and just refreshing the screen using the untouched other surfaces
}

// Show credits overlay
void Menu::showCredits() {
	if (!_isShowingCredits || _creditsSequenceIndex > _seqCredits.count() - 1) {
		_isShowingCredits = false;
		hideOverlays();
		return;
	}

	_seqCredits.show(_creditsSequenceIndex);
	_creditsSequenceIndex++;
}

//////////////////////////////////////////////////////////////////////////
// Time
//////////////////////////////////////////////////////////////////////////

uint32 Menu::getCurrentTime() {
	// FIXME this is the time as showed on the menu, which might be different from the max time attained in the game by the player

	// return current time as if we already rewinded
	return _engine->getLogic()->getGameState()->currentTime; 
	
}

uint32 Menu::getMaxGameTime() {
	// FIXME check disasm
	// DEBUG value
	return _engine->getLogic()->getGameState()->currentTime + 54360; 
}

void Menu::goToTime(uint32 time) {
	// TODO implement modifying the current game time
	// + adjusting elements on screen : clock + train line
}

void Menu::moveToCity(CityOverlay city, CityTime time, StartMenuTooltips tooltipRewind, StartMenuTooltips tooltipForward, bool clicked) {
	// TODO Check if we have access (there seems to be more checks on some internal times) - probably : current_time / max_game_time / some other?
	if (getMaxGameTime() < (uint32)time || getCurrentTime() == (uint32)time) {
		hideOverlays();
		return;
	}

	// Show city overlay
	switch (city) {
	case kParis:
		_seqCityStart.show(0);
		break;

	case kEnding:
		_seqCityEnd.show(0);
		break;

	default:
		_seqCities.show(city);
	}	

	if (clicked) {
		hideOverlays();
		playSfx("LIB046.snd");
		goToTime(time);
		// TODO set some global var to 1
	} else {
		if (getCurrentTime() < (uint32)time)			// For start city (Paris) and end city, this will always be true
			_seqTooltips.show(tooltipForward);
		else
			_seqTooltips.show(tooltipRewind);
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
	_engine->getLogic()->getGameState()->volume = volume;	

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
	return _engine->getLogic()->getGameState()->brightness;
}

void Menu::setBrightness(int brightness) {
	_engine->getLogic()->getGameState()->brightness = brightness;

	// TODO: write to savegame
	// TODO: reload all graphics and adjust for the new brightness (or not :D)
}

} // End of namespace LastExpress
