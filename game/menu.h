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

#include "lastexpress/data/sequence.h"

#include "lastexpress/eventhandler.h"

#include "lastexpress/shared.h"

#include "common/events.h"

namespace LastExpress {

class LastExpressEngine;
class Scene;

class Clock;
class TrainLine;

class Menu : public EventHandler {
public:
	Menu(LastExpressEngine *engine);
	~Menu();

	void showMenu(bool savegame, TimeType type, uint32 time);

	// Event handling
	void eventMouseClick(Common::Event ev);
	void eventMouseMove(Common::Event ev);

	uint32 getSceneIndex();

	// DEBUG ONLY - TO BE REMOVED
	void setShowStartup(bool show) { _showStartScreen = show; }

private:
	LastExpressEngine *_engine;

	Scene *_scene;          ///< Menu scene

	// Sequences
	Sequence _seqTooltips;
	Sequence _seqEggButtons;
	Sequence _seqButtons;

	// TODO might be loaded on-the-fly in the future
	Sequence _seqCredits;
	Sequence _seqAcorn;

	// Cached decoded frames
	AnimFrame *_cityButtonFrames[7];

	// Indicator to know if we need to show the start animation when showMenu is called
	bool _showStartScreen;
	bool _isShowingCredits;
	uint32 _creditsSequenceIndex;

	void loadData();
	void handleEvent(Common::Event ev);

	// Overlays & elements
	void drawElements();
	Clock *_clock;
	TrainLine *_trainLine;
	Common::String getAcornSequenceName(GameId id);
	void showCredits();

	enum CityButton {
		kParis = 0,
		kStrasbourg = 1,
		kMunich = 2,
		kVienna = 3,
		kBudapest = 4,
		kBelgrade = 5,
		kConstantinople = 6
	};

	// Game time
	uint32 _currentTime; // internal time for the menu (to handle rewind/forward)
	void goToTime(uint32 time);
	void moveToCity(CityButton city, bool clicked);

	// Sound/Brightness related
	int getVolume();
	void setVolume(int volume);
	int getBrightness();
	void setBrightness(int brightness);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_MENU_H
