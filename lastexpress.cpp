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
#include "lastexpress/data/scene.h"

#include "lastexpress/game/logic.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/resource.h"

#include "common/EventRecorder.h"

namespace LastExpress {

LastExpressEngine::LastExpressEngine(OSystem *syst, const ADGameDescription *gd) :
    Engine(syst), _gameDescription(gd), _debugger(NULL), _cursor(NULL),
    _font(NULL), _logic(NULL), _graphicsMan(NULL), _resMan(NULL), _sceneMan(NULL) {
	// Adding the default directories
	SearchMan.addSubDirectoryMatching(_gameDataDir, "data");

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
	// Delete the remaining objects
	delete _cursor;
	delete _debugger;
	delete _font;
	delete _graphicsMan;
	delete _logic;
	delete _resMan;
	delete _sceneMan;
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
	_resMan = new ResourceManager((bool)(_gameDescription->flags & ADGF_DEMO));
	if (!_resMan->loadArchive(kArchiveAll))
		return Common::kUnknownError;

	_graphicsMan = new GraphicsManager();

	// Load the cursor data
	_cursor = _resMan->loadCursor();
	if (!_cursor)
		return Common::kUnknownError;

	// Load the font data
	_font = _resMan->loadFont();
	if (!_font)
		return Common::kUnknownError;

	// Start scene manager
	_sceneMan = new SceneManager();

	// Game logic
	_logic = new Logic(this);
	_logic->startGame();

	while (!shouldQuit()) {
		// Execute stored commands
		if (_debugger->hasCommand()) {
			_debugger->callCommand();

			// re-attach the debugger
			_debugger->attach();
		}

		// Show the debugger if required
		if (_debugger->isAttached()) {
			_debugger->onFrame();
		}

		// Handle input
		Common::Event ev;
		while (_eventMan->pollEvent(ev)) {
			switch (ev.type) {

			case Common::EVENT_KEYDOWN:
				// CTRL-D: Attach the debugger
				if ((ev.kbd.flags & Common::KBD_CTRL) && ev.kbd.keycode == Common::KEYCODE_d)
					_debugger->attach();

				// DEBUG: Quit game on escape
				if (ev.kbd.keycode == Common::KEYCODE_ESCAPE)
					quitGame();

				break;

			case Common::EVENT_MAINMENU:
				// Closing the GMM

			case Common::EVENT_MOUSEMOVE:
				_logic->eventMouseMove(ev);
				break;

			case Common::EVENT_LBUTTONDOWN:
			case Common::EVENT_LBUTTONUP:
			case Common::EVENT_RBUTTONDOWN:
				_logic->eventMouseClick(ev);
				break;

			case Common::EVENT_QUIT:
				quitGame();
				break;

			default:
				break;
			}
		}

		// Update the screen
		_graphicsMan->update();
		_system->updateScreen();
		_system->delayMillis(10);

		// The event loop may have triggered the quit status. In this case,
		// stop the execution.
		if (shouldQuit()) {
			continue;
		}
	}

	return Common::kNoError;
}

bool LastExpressEngine::hasFeature(EngineFeature f) const {
	return (f == kSupportsRTL);
}

void LastExpressEngine::errorString(const char *buf_input, char *buf_output, int buf_output_size) {
	snprintf(buf_output, (uint)buf_output_size, "%s", buf_input);
}

} // End of namespace LastExpress
