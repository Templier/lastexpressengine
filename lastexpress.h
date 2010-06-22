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

#ifndef LASTEXPRESS_H
#define LASTEXPRESS_H

#include "lastexpress/debug.h"
#include "lastexpress/eventhandler.h"

#include "common/random.h"
#include "common/timer.h"

#include "engines/advancedDetector.h"
#include "engines/engine.h"

#include "graphics/pixelformat.h"

/**
 * This is the namespace of the LastExpress engine.
 *
 * Status of this engine:
 *  The basic framework for the engine is done and you can navigate through the
 *  train and interact with objects. Some logic for characters and entities has
 *  been implemented, but characters do not appear in-game yet and background
 *  sounds and animations are missing.
 *    - Resources: classes for the resource formats used by the game are mostly
 *      complete (subtitles integration/cursor transparency are missing)
 *    - Display: basic graphic manager functionality is implemented (transitions
 *      and dirty rects handling are missing)
 *    - Menu/Navigation: main menu is almost complete. Navigation and hotspot
 *      handling is also mostly implemented (with remaining bugs)
 *    - Logic: the framework is in place (with helper classes mostly complete),
 *      and some logic has been implemented (it is mostly hardcoded in the original)
 *      The shared entity code for drawing/handling of entities remains to be done.
 *
 * Maintainers:
 * clone2727, jvprat, littleboy
 *
 * Supported games:
 * - The Last Express
 */
namespace LastExpress {

class Cursor;
class Font;
class GraphicsManager;
class Logic;
class Menu;
class ResourceManager;
class SceneManager;
class SoundManager;

class LastExpressEngine : public Engine {
protected:
	// Engine APIs
	Common::Error run();
	virtual void errorString(const char *buf_input, char *buf_output, int buf_output_size);
	virtual bool hasFeature(EngineFeature f) const;
	virtual Debugger *getDebugger() { return _debugger; }

public:
	LastExpressEngine(OSystem *syst, const ADGameDescription *gd);
	~LastExpressEngine();

	// Misc
	Common::RandomSource getRandom() const {return _random; }

	// Game
	Cursor          *getCursor()          const { return _cursor; }
	Font            *getFont()            const { return _font; }	
	Logic           *getGameLogic()       const { return _logic; }
	Menu            *getGameMenu()        const { return _menu; }	

	// Managers
	GraphicsManager *getGraphicsManager() const { return _graphicsMan; }
	ResourceManager *getResourceManager() const { return _resMan; }
	SceneManager    *getSceneManager()    const { return _sceneMan; }
	SoundManager    *getSoundManager()    const { return _soundMan; }

	// Event handling
	bool handleEvents();

	void backupEventHandlers();
	void restoreEventHandlers();
	void setEventHandlers(EventHandler::EventFunction *eventMouseClick, EventHandler::EventFunction *eventTick);

	bool isDemo() const { return (bool)(_gameDescription->flags & ADGF_DEMO); }

protected:
	// Sound Timer
	static void soundTimer(void *ptr);
	void handleSoundTimer();

private:
	const ADGameDescription *_gameDescription;
	Graphics::PixelFormat _pixelFormat;

	// Misc
	Debugger *_debugger;
	Common::RandomSource _random;

	// Game
	Cursor *_cursor;
	Font   *_font;
	Logic  *_logic;
	Menu   *_menu;
	
	// Managers
	GraphicsManager *_graphicsMan;
	ResourceManager *_resMan;
	SceneManager    *_sceneMan;
	SoundManager    *_soundMan;

	// Event handlers
	EventHandler::EventFunction *eventMouseClick;
	EventHandler::EventFunction *eventTick;

	EventHandler::EventFunction *eventMouseClickBackup;
	EventHandler::EventFunction *eventTickBackup;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_H
