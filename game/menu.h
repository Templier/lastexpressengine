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

	void show(bool savegame, TimeType type, uint32 time);

	// Event handling
	void eventMouse(const Common::Event &ev);
	void eventTick(const Common::Event &ev);

	bool isShown() const { return _isShowingMenu; }

	GameId getGameId() const { return _gameId; }

private:
	enum CityButton {
		kParis = 0,
		kStrasbourg = 1,
		kMunich = 2,
		kVienna = 3,
		kBudapest = 4,
		kBelgrade = 5,
		kConstantinople = 6
	};

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

	GameId _gameId;

	// Indicator to know if we need to show the start animation when showMenu is called
	bool _hasShownStartScreen;
	bool _hasShownIntro;

	bool _isShowingCredits;
	bool _isGameStarted;
	bool _isShowingMenu;

	uint32 _creditsSequenceIndex;

	void loadData();
	void handleEvent(const Common::Event &ev);

	//////////////////////////////////////////////////////////////////////////
	// Overlays & elements
	Clock *_clock;
	TrainLine *_trainLine;

	void checkHotspots();
	void drawElements();
	void moveToCity(CityButton city, bool clicked);
	void switchGame();
	void showCredits();
	Common::String getAcornSequenceName(GameId id) const;

	//////////////////////////////////////////////////////////////////////////
	// Misc
	SceneIndex getSceneIndex() const;
	bool isGameFinished() const;
	
	//////////////////////////////////////////////////////////////////////////
	// Time
	uint32 _currentIndex; // current savegame entry
	uint32 _currentTime;  // current game time
	
	uint32 _index;
	uint32 _index2;
	uint32 _time;
	uint32 _delta;

	void initTime(TimeType type, uint32 time);
	void updateTime(uint32 time);
	void adjustIndex(uint32 time1, uint32 time2, bool searchEntry);	
	void goToTime(uint32 time);	
	void setTime();
	void forwardTime();
	void rewindTime();
	void updateFromTime();
	bool hasTimeDelta() { return (_currentTime - _time) >= 1; }

	// Sound/Brightness related
	uint32 getVolume() const;
	void setVolume(uint32 volume) const;
	uint32 getBrightness() const;
	void setBrightness(uint32 brightness) const;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_MENU_H
