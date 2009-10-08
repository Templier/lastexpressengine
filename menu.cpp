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
	_showStartScreen = true;	
}

Menu::~Menu() {}

//////////////////////////////////////////////////////////////////////////
// Show the intro and load the main menu scene
//
// The main menu screen is a background plus 8 overlay elements
// .text:00448590
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
	//loadSequences();

	//buttns.seq
	//helpnewr.seq

	// TODO Load Main menu scene (sceneIndex = 5 * savegame id (+ 1/2)) - see text:00449d80
}

//////////////////////////////////////////////////////////////////////////
// Start menu
//////////////////////////////////////////////////////////////////////////

// text:00448b30
bool Menu::handleStartMenuEvent(StartMenuEvent event, bool clicked) {

	// Init overlay sequences (there should be 8 of them)
	Sequence tooltips;
	Sequence buttons;	
	Sequence egg;
	Sequence acorn;

	if (!tooltips.loadFile("helpnewr.seq"))
		return false;
	if (!buttons.loadFile("quit.seq"))
		return false;
	if (!egg.loadFile("buttns.seq"))
		return false;
	//if (!acorn.load(getAcornHighlight(_engine->getLogic()->getSaveGameId())))
	//	return false;

	switch(event) {
	default:
		hideAllOverlays();
		return true;

	case kEventCase1:
	case kEventCase4:
		// FIXME: understand code...
		return true;

	case kEventCredits:
		// TODO: Hide all overlays

		if (clicked) {
			// TODO: Hide tooltips
			playClickSnd();
			
		} else {
			tooltips.show(kTooltipCredits);
		}
		break;


	case kEventQuitGame:
		tooltips.show(kTooltipQuit);
		
		if (clicked) {
			buttons.show(kButtonQuitPushed);	
			playClickSnd();
			return false;
		} else {
			buttons.show(kButtonQuit);		
			return true;
		}
		break;

	case kEventSwitchSaveGame:
	case kEventRewindGame:
	case kEventFastForwardGame:
	case kEventParis:
	case kEventStrasBourg:
	case kEventMunich:
	case kEventVienna:
	case kEventBudapest:
	case kEventBelgrade:
	case kEventEnding:
		break;

	case kEventDecreaseVolume: {
		int volume = getVolume();

		// Cannot decrease volume further
		if (volume == 0) {
			buttons.show(kButtonVolume);
			hideOverlay(kOverlayTooltip);
			return true;
		}

		tooltips.show(kTooltipVolumeDown);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			buttons.show(kButtonVolumeDownPushed);
			playClickSnd();
			setVolume(volume - 1);

			// TODO: write to savegame
		} else {
			buttons.show(kButtonVolumeDown);
			return true;
		}
		break;
	}

	case kEventIncreaseVolume: {
		int volume = getVolume();

		// Cannot increase volume further
		if (volume >= 7) {
			buttons.show(kButtonVolume);
			hideOverlay(kOverlayTooltip);
		}

		tooltips.show(kTooltipVolumeUp);

		// Show highlight on button & adjust volume if needed
		if (clicked) {
			buttons.show(kButtonVolumeUpPushed);
			playClickSnd();
			setVolume(volume + 1);

			// TODO: write to savegame
		} else {
			buttons.show(kButtonVolumeUp);
			return true;
		}
		break;
	}

	case kEventDecreaseBrightness: {
		int luminosity = _engine->getLogic()->getGameState()->luminosity;

		// Cannot increase volume further
		if (luminosity == 0) {
			buttons.show(kButtonBrightness);
			hideOverlay(kOverlayTooltip);
		}

		tooltips.show(kTooltipBrightnessDown);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			buttons.show(kButtonBrightnessDownPushed);
			playClickSnd();
			_engine->getLogic()->getGameState()->luminosity--;

			// TODO: write to savegame
			// TODO: reload all graphics and adjust for the new brightness (not :D)
		} else {
			buttons.show(kButtonBrightnessDown);
			return true;
		}
		break;
	}

	case kEventIncreaseBrightness: {
		int luminosity = _engine->getLogic()->getGameState()->luminosity;

		// Cannot increase volume further
		if (luminosity >= 6) {
			buttons.show(kButtonBrightness);
			hideOverlay(kOverlayTooltip);
		}

		tooltips.show(kTooltipBrightnessUp);

		// Show highlight on button & adjust brightness if needed
		if (clicked) {
			buttons.show(kButtonBrightnessUpPushed);
			playClickSnd();
			_engine->getLogic()->getGameState()->luminosity++;

			// TODO: write to savegame
			// TODO: reload all graphics and adjust for the new brightness (not :D)
		} else {
			buttons.show(kButtonBrightnessUp);
			return true;
		}
		break;
	}
	}

	return false;
}

// Hide all overlay frames on the start menu (tooltips, highlights)
void Menu::hideAllOverlays() {
	for (int i = 0; i < sizeof(StartMenuOverlayType); i++)
		hideOverlay((StartMenuOverlayType)i);
}

// Hide a specific type of overlay
void Menu::hideOverlay(StartMenuOverlayType type) {
	// TODO implement
}


// Get the sequence name to use for the acorn highlight, depending of the currently loaded savegame
Common::String Menu::getAcornHighlight(SaveLoad::SavegameId id) {

	// end of text:00449d80 (also sets up the main menu scene)

	// TODO replace with string array and access by index?
	Common::String name = "";
	switch (id) {
	default:
	case SaveLoad::kSavegameBlue:
		name = "aconblue3.seq";
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
// Sound
//////////////////////////////////////////////////////////////////////////

// Play the click sound (start menu buttons)
void Menu::playClickSnd() {
	playSfx("LIB046.snd");
}

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
}

} // End of namespace LastExpress
