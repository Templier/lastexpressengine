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

#include "lastexpress/lastexpress.h"

#include "lastexpress/data/cursor.h"
#include "lastexpress/data/font.h"

#include "lastexpress/game/logic.h"
#include "lastexpress/game/menu.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/state.h"
#include "lastexpress/game/sound.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/resource.h"

#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "common/EventRecorder.h"

#include "engines/util.h"

const char *g_actionNames[] = {"None", "Action1", "Action2", "ExitCompartment", "Action4", "ExcuseMeCath", "ExcuseMe", "INVALID", "Knock", "OpenDoor", "Action10", "Action11", "Default", "INVALID", "INVALID", "INVALID", "Action16", "DrawScene", "Callback"};
const char *g_directionNames[] = { "None", "Up", "Down", "Left", "Right", "Switch"};
const char *g_entityNames[] = { "Player", "Anna", "August", "Mertens", "Coudert", "Pascale", "Servers0", "Servers1", "Cooks", "Verges", "Tatiana", "Vassili", "Alexei", "Abbot", "Milos", "Vesna", "Ivo", "Salko", "Kronos", "Kahina", "Francois", "MmeBoutarel", "Boutarel", "Rebecca", "Sophie", "Mahmud", "Yasmin", "Hadija", "Alouan", "Gendarmes", "Max", "Chapters", "Train", "Tables0", "Tables1", "Tables2", "Tables3", "Tables4", "Tables5", "Entity39"};


namespace LastExpress {

LastExpressEngine::LastExpressEngine(OSystem *syst, const ADGameDescription *gd) :
    Engine(syst), _gameDescription(gd), _debugger(NULL), _cursor(NULL),
    _font(NULL), _logic(NULL), _menu(NULL), _frameCounter(0), _lastFrameCount(0),
	_graphicsMan(NULL), _resMan(NULL), _sceneMan(NULL), _soundMan(NULL),
	eventMouse(NULL), eventTick(NULL), eventMouseBackup(NULL), eventTickBackup(NULL) {

	// Adding the default directories
	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "data");

	// Initialize the custom debug levels
	DebugMan.addDebugChannel(kLastExpressDebugAll, "All", "Debug everything");
	DebugMan.addDebugChannel(kLastExpressDebugGraphics, "Graphics", "Debug graphics & animation/sequence playback");
	DebugMan.addDebugChannel(kLastExpressDebugResource, "Resource", "Debug resource management");
	DebugMan.addDebugChannel(kLastExpressDebugCursor, "Cursor", "Debug cursor handling");
	DebugMan.addDebugChannel(kLastExpressDebugSound, "Sound", "Debug sound playback");
	DebugMan.addDebugChannel(kLastExpressDebugSubtitle, "Subtitle", "Debug subtitles");
	DebugMan.addDebugChannel(kLastExpressDebugSavegame, "Savegame", "Debug savegames");
	DebugMan.addDebugChannel(kLastExpressDebugLogic, "Logic", "Debug logic");
	DebugMan.addDebugChannel(kLastExpressDebugScenes, "Scenes", "Debug scenes & hotspots");
	DebugMan.addDebugChannel(kLastExpressDebugUnknown, "Unknown", "Debug unknown data");

	g_eventRec.registerRandomSource(_random, "lastexpress");
}

LastExpressEngine::~LastExpressEngine() {
	_timer->removeTimerProc(&soundTimer);

	// Delete the remaining objects
	delete _cursor;
	delete _font;
	delete _logic;
	delete _menu;
	delete _graphicsMan;
	delete _resMan;
	delete _sceneMan;
	delete _soundMan;
	delete _debugger;

	// Cleanup event handlers
	SAFE_DELETE(eventMouse);
	SAFE_DELETE(eventTick);
	SAFE_DELETE(eventMouseBackup);
	SAFE_DELETE(eventTickBackup);

	// Zero passed pointers
	_gameDescription = NULL;
}

// TODO: which error should we return when some game files are missing/corrupted?
Common::Error LastExpressEngine::run() {
	// Initialize the graphics
	const Graphics::PixelFormat dataPixelFormat(2, 5, 5, 5, 0, 10, 5, 0, 0);
	initGraphics(640, 480, true, &dataPixelFormat);

	// We do not support color conversion
	if (_system->getScreenFormat() != dataPixelFormat)
		return Common::kUnsupportedColorMode;

	// Create debugger. It requires GFX to be initialized
	_debugger = new Debugger(this);

	// Start the resource and graphics managers
	_resMan = new ResourceManager(isDemo());
	if (!_resMan->loadArchive(kArchiveCd1))
		return Common::kNoGameDataFoundError;

	_graphicsMan = new GraphicsManager();

	// Load the cursor data
	_cursor = _resMan->loadCursor();
	if (!_cursor)
		return Common::kNoGameDataFoundError;

	// Load the font data
	_font = _resMan->loadFont();
	if (!_font)
		return Common::kNoGameDataFoundError;

	// Start scene manager
	_sceneMan = new SceneManager(this);
	_sceneMan->loadSceneDataFile(kArchiveCd1);

	// Game logic
	_logic = new Logic(this);

	// Start sound manager and setup timer
	_soundMan = new SoundManager(this);
	_timer->installTimerProc(&soundTimer, 17, this);

	// Menu
	_menu = new Menu(this);
	_menu->show(false, kSavegameTypeIndex, 0);

	while (!shouldQuit()) {
		_soundMan->updateQueue();
		_soundMan->updateSubtitles();

		if (handleEvents())
			continue;
	}

	return Common::kNoError;
}

void LastExpressEngine::pollEvents() {
	Common::Event ev;
	_eventMan->pollEvent(ev);

	switch (ev.type) {

	case Common::EVENT_LBUTTONUP:
		getGameLogic()->getGameState()->getGameFlags()->mouseLeftClick = true;
		break;

	case Common::EVENT_RBUTTONUP:
		getGameLogic()->getGameState()->getGameFlags()->mouseRightClick = true;
		break;

	default:
		break;
	}
}

bool LastExpressEngine::handleEvents() {
	// Make sure all the subsystems have been initialized
	if (!_debugger || !_graphicsMan)
		error("LastExpressEngine::handleEvents: called before the required subsystems have been initialized!");

	// Execute stored commands
	if (_debugger->hasCommand()) {
		_debugger->callCommand();

		// re-attach the debugger
		_debugger->attach();
	}

	// Show the debugger if required
	_debugger->onFrame();

	// Handle input
	Common::Event ev;
	while (_eventMan->pollEvent(ev)) {
		switch (ev.type) {

		case Common::EVENT_KEYDOWN:
			// CTRL-D: Attach the debugger
			if ((ev.kbd.flags & Common::KBD_CTRL) && ev.kbd.keycode == Common::KEYCODE_d)
				_debugger->attach();

			//// DEBUG: Quit game on escape
			//if (ev.kbd.keycode == Common::KEYCODE_ESCAPE)
			//	quitGame();

			break;

		case Common::EVENT_MAINMENU:
			// Closing the GMM

		case Common::EVENT_LBUTTONUP:
			getGameLogic()->getGameState()->getGameFlags()->mouseLeftClick = true;

			// Adjust frameInterval flag
			if (_frameCounter < _lastFrameCount + 30)
				getGameLogic()->getGameState()->getGameFlags()->frameInterval = true;
			_lastFrameCount = _frameCounter;

			if (eventMouse && eventMouse->isValid())
				(*eventMouse)(ev);
			break;

		case Common::EVENT_RBUTTONUP:
			getGameLogic()->getGameState()->getGameFlags()->mouseRightClick = true;
			if (eventMouse && eventMouse->isValid())
				(*eventMouse)(ev);
			break;

		case Common::EVENT_MOUSEMOVE:
			if (eventMouse && eventMouse->isValid())
				(*eventMouse)(ev);
			break;

		case Common::EVENT_QUIT:
			quitGame();
			break;

		default:
			break;
		}
	}

	// Game tick event
	if (eventTick && eventTick->isValid())
		(*eventTick)(ev);

	// Update the screen
	_graphicsMan->update();
	_system->updateScreen();
	_system->delayMillis(50);

	// The event loop may have triggered the quit status. In this case,
	// stop the execution.
	if (shouldQuit()) {
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////
/// Timer
///////////////////////////////////////////////////////////////////////////////////
void LastExpressEngine::soundTimer(void *refCon) {
	((LastExpressEngine *)refCon)->handleSoundTimer();
}

void LastExpressEngine::handleSoundTimer() {
	if (_frameCounter & 1)
		if (_soundMan)
			_soundMan->handleTimer();

	_frameCounter++;
}

///////////////////////////////////////////////////////////////////////////////////
/// Event Handling
///////////////////////////////////////////////////////////////////////////////////
void LastExpressEngine::backupEventHandlers() {
	eventMouseBackup = eventMouse;
	eventTickBackup = eventTick;
}

void LastExpressEngine::restoreEventHandlers() {
	if (eventMouseBackup == NULL || eventTickBackup == NULL)
		error("LastExpressEngine::restoreEventHandlers: restore called before backing up the event handlers!");

	eventMouse = eventMouseBackup;
	eventTick = eventTickBackup;
}

void LastExpressEngine::setEventHandlers(EventHandler::EventFunction *mouse, EventHandler::EventFunction *tick) {
	eventMouse = mouse;
	eventTick = tick;
}

///////////////////////////////////////////////////////////////////////////////////
/// Misc Engine
///////////////////////////////////////////////////////////////////////////////////
bool LastExpressEngine::hasFeature(EngineFeature f) const {
	return (f == kSupportsRTL);
}

void LastExpressEngine::errorString(const char *buf_input, char *buf_output, int buf_output_size) {
	snprintf(buf_output, (uint)buf_output_size, "%s", buf_input);
}

} // End of namespace LastExpress
