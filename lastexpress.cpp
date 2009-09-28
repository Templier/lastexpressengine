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

#include "common/config-manager.h"
#include "common/events.h"
#include "sound/mixer.h"

#include "lastexpress/lastexpress.h"

namespace LastExpress {

LastExpressEngine::LastExpressEngine(OSystem *syst, const ADGameDescription *gd) :
	Engine(syst), _gameDescription(gd), _debugger(NULL), _resources(NULL) {

	// Adding the default directories
	SearchMan.addSubDirectoryMatching(_gameDataDir, "data");

	// Initialize the custom debug levels
	Common::addDebugChannel(kLastExpressDebugAll, "All", "Debug everything");
	Common::addDebugChannel(kLastExpressDebugVideo, "Video", "Debug video playback");
	Common::addDebugChannel(kLastExpressDebugResource, "Resource", "Debug resouce management");	
	Common::addDebugChannel(kLastExpressDebugCursor, "Cursor", "Debug cursor decompression / switching");
	Common::addDebugChannel(kLastExpressDebugSound, "Sound", "Debug sound playback");
	Common::addDebugChannel(kLastExpressDebugSubtitle, "Subtitle", "Debug subtitles");
}

LastExpressEngine::~LastExpressEngine() {
	// Delete the remaining objects
	delete _debugger;
	delete _resources;
	delete _graphics;
}

Common::Error LastExpressEngine::run() {
	Common::Error err;
	err = init();
	if (err != Common::kNoError)
		return err;

	return go();
}

Common::Error LastExpressEngine::init() {

	// Initialize the graphics
	Graphics::PixelFormat format(2, 5, 6, 5, 0, 11, 5, 0, 0);
	initGraphics(640, 480, true, &format);
	_pixelFormat = _system->getScreenFormat();

	// We do not support 256 colors mode
	if (_pixelFormat.bytesPerPixel == 1)
		return Common::kUnsupportedColorMode;

	// Create debugger. It requires GFX to be initialized
	_debugger = new Debugger(this);

	// Start all managers
	_resources = new ResourceManager(this);
	_graphics = new GraphicsManager(this);

	//////////////////////////////////////////////////////////////////////////////
	// DEBUG
	Background *background = _resources->loadBackground("clock01.bg");
	background->render(&_graphics->_background);
	_graphics->updateScreen(&_graphics->_background);
	_graphics->update();
        
	//Subtitle *subtitle = _resources->loadSubtitle("xvas3.sbe");
	//subtitle->render(&_graphics->_foreground, 0);
	//_graphics->updateScreen(&_graphics->_foreground);
	//_graphics->update();

	//Sound *sound = _resources->loadSound("mus001.snd");
	//sound->play(_system->getMixer());

	Animation *sequence = _resources->loadSequence("jlinetl.seq"); //line1.seq");
	for (uint32 i = 0; i < sequence->getNumberOfFrames(); i++) {
		sequence->renderFrame(&_graphics->_foreground, i);
		_graphics->mergeFgAndBg();
		_graphics->updateScreen(&_graphics->_foreground);
		_graphics->update();
	}
	//////////////////////////////////////////////////////////////////////////////

	return Common::kNoError;
}

Common::Error LastExpressEngine::go() {

	while (!shouldQuit()) {
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
					if (!_debugger->isAttached())
						_debugger->attach();																
				break;

			case Common::EVENT_MAINMENU:
				// Closing the GMM

			case Common::EVENT_MOUSEMOVE:
				break;

			case Common::EVENT_LBUTTONDOWN:			
				break;

			case Common::EVENT_RBUTTONDOWN:
				break;

			case Common::EVENT_QUIT:
				quitGame();
				break;

			default:
				break;
			}
		}

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
	snprintf(buf_output, buf_output_size, "%s", buf_input);
}

uint32 LastExpressEngine::getFlags() const {
	return _gameDescription->flags;
}

} // End of namespace LastExpress