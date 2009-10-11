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

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/resource.h"
#include "lastexpress/cursor.h"
#include "lastexpress/font.h"
#include "lastexpress/sound.h"
#include "lastexpress/logic.h"

#ifdef LOAD_RESOURCES_LIST
#include "lastexpress/background.h"
#include "lastexpress/subtitle.h"
#include "lastexpress/animation.h"
#include "lastexpress/sequence.h"
#endif

namespace LastExpress {

const Common::String cursorsName("CURSORS.TBM");
const Common::String fontName("FONT.DAT");

LastExpressEngine::LastExpressEngine(OSystem *syst, const ADGameDescription *gd) :
	Engine(syst), _gameDescription(gd), _debugger(NULL), _resource(NULL) {

	// Adding the default directories
	SearchMan.addSubDirectoryMatching(_gameDataDir, "data");

	// Initialize the custom debug levels
	Common::addDebugChannel(kLastExpressDebugAll, "All", "Debug everything");
	Common::addDebugChannel(kLastExpressDebugGraphics, "Graphics", "Debug graphics & animation/sequence playback");
	Common::addDebugChannel(kLastExpressDebugResource, "Resource", "Debug resource management");
	Common::addDebugChannel(kLastExpressDebugCursor, "Cursor", "Debug cursor handling");
	Common::addDebugChannel(kLastExpressDebugSound, "Sound", "Debug sound playback");
	Common::addDebugChannel(kLastExpressDebugSubtitle, "Subtitle", "Debug subtitles");
	Common::addDebugChannel(kLastExpressDebugUnknown, "Unknown", "Debug unknown data");
}

LastExpressEngine::~LastExpressEngine() {
	// Delete the remaining objects
	SAFE_DELETE(_debugger);
	SAFE_DELETE(_resource);
	SAFE_DELETE(_cursor);
	SAFE_DELETE(_font);
	SAFE_DELETE(_sfx);
	SAFE_DELETE(_music);
	SAFE_DELETE(_logic);
	SAFE_DELETE(_graphics);
}

Common::Error LastExpressEngine::run() {
	Common::Error err;
	err = init();
	if (err != Common::kNoError)
		return err;

	return go();
}

// TODO: which error should we return when some game files are missing/corrupted?
Common::Error LastExpressEngine::init() {

	// Initialize the graphics
	Graphics::PixelFormat format(2, 5, 5, 5, 0, 10, 5, 0, 0);
	initGraphics(640, 480, true, &format);
	_pixelFormat = _system->getScreenFormat();

	// We do not support 256 colors mode
	if (_pixelFormat.bytesPerPixel == 1)
		return Common::kUnsupportedColorMode;

	// Create debugger. It requires GFX to be initialized
	_debugger = new Debugger(this);

	// Start managers: resource, graphics, cursor & font
	_resource = new ResourceManager(this);
	if (!_resource->loadArchive(ResourceManager::kArchiveAll))
		return Common::kUnknownError;

	_graphics = new GraphicsManager(_pixelFormat);

	_cursor = new Cursor();
	if (!_cursor->load(_resource->getFileStream(cursorsName)))
		return Common::kUnknownError;

	_font = new Font();
	if (!_font->load(_resource->getFileStream(fontName)))
		return Common::kUnknownError;

	// Initialize cursor
	_cursor->setStyle(Cursor::CursorNormal);

	_sfx = new StreamedSound();
	_music = new StreamedSound();
	_logic = new Logic(this);

	return Common::kNoError;
}

Common::Error LastExpressEngine::go() {

	// DEBUG
	int style = 0;
	_cursor->show(true);

#ifdef LOAD_RESOURCES_LIST
	// Test Backgrounds
	Common::ArchiveMemberList list_bg;
	int num_bg = _resource->listMatchingMembers(list_bg, "*.BG");
	warning("found %d bg's", num_bg);
	Common::ArchiveMemberList::iterator i_bg = list_bg.begin();

	// Test SEQ
	Common::ArchiveMemberList list_seq;
	int n_seq = _resource->listMatchingMembers(list_seq, "*.SEQ");
	warning("found %d seq's", n_seq);
	Common::ArchiveMemberList::iterator i_seq = list_seq.begin();

	// Test NIS
	Common::ArchiveMemberList list_nis;
	int n_nis = _resource->listMatchingMembers(list_nis, "*.NIS");
	warning("found %d nis's", n_nis);
	Common::ArchiveMemberList::iterator i_nis = list_nis.begin();

	// Test subtitles
	Common::ArchiveMemberList list_sbe;
	int n_sbe = _resource->listMatchingMembers(list_sbe, "*.SBE");
	warning("found %d sbe's", n_sbe);
	Common::ArchiveMemberList::iterator i_sbe = list_sbe.begin();

	// Test sound
	Common::ArchiveMemberList list_snd;
	int n_snd = _resource->listMatchingMembers(list_snd, "*.SND");
	warning("found %d snd's", n_snd);
	Common::ArchiveMemberList::iterator i_snd = list_snd.begin();

	debugC(2, kLastExpressDebugResource, "Resource debugging:\n  b: background\n  m: music/sound\n  n: animation\n  s: sequence\n  t: subtitle\n  +/-: cursor");
#endif

	while (!shouldQuit()) {
		// Show the debugger if required
		if (_debugger->isAttached()) {
			_debugger->onFrame();
			if (_debugger->hasCommand()) {
				_debugger->callCommand();

				// re-attach the debugger
				_debugger->attach();
			}
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

				// DEBUG: Quit game on escape
				if (ev.kbd.keycode == Common::KEYCODE_ESCAPE)
					quitGame();

				// DEBUG: cursors
				if (ev.kbd.keycode == Common::KEYCODE_PLUS || ev.kbd.keycode == Common::KEYCODE_KP_PLUS)
					if (_cursor->setStyle((Cursor::CursorStyle)(style+1)))
						style++;

				if (ev.kbd.keycode == Common::KEYCODE_MINUS || ev.kbd.keycode == Common::KEYCODE_KP_MINUS)
					if (_cursor->setStyle((Cursor::CursorStyle)(style-1)))
						style--;

				// DEBUG: time
				if (ev.kbd.keycode == Common::KEYCODE_KP_DIVIDE) {
					_logic->getGameState()->currentTime = _logic->getGameState()->currentTime - 4984;
					_logic->showMenu();
				}

				if (ev.kbd.keycode == Common::KEYCODE_KP_MULTIPLY) {
					_logic->getGameState()->currentTime = _logic->getGameState()->currentTime + 5167;
					_logic->showMenu();
				}

				// Play intro
				if (ev.kbd.keycode == Common::KEYCODE_RETURN || ev.kbd.keycode == Common::KEYCODE_KP_ENTER)
					_logic->showMenu();

#ifdef LOAD_RESOURCES_LIST
				// DEBUG: show data files
				if (ev.kbd.keycode == Common::KEYCODE_b) {
					if (i_bg != list_bg.end()) {
						Background background;
						if (background.load(_resource->getFileStream((*i_bg)->getName()))) {
							background.show();
						}
						i_bg++;
					}
				}

				if (ev.kbd.keycode == Common::KEYCODE_s) {
					if (i_seq != list_seq.end()) {
						Sequence sequence;
						if (sequence.load(_resource->getFileStream((*i_seq)->getName()))) {
							for (uint32 i = 0; i < sequence.count(); i++) {
								if (sequence.show(i))
									_system->delayMillis(200);
							}
						}
						i_seq++;
					}
				}

				if (ev.kbd.keycode == Common::KEYCODE_n) {
					if (i_nis != list_nis.end()) {
						Animation animation;
						if (animation.load(_resource->getFileStream((*i_nis)->getName()))) {
							animation.show();
						}
						i_nis++;
					}
				}

				if (ev.kbd.keycode == Common::KEYCODE_m) {
					if (i_snd != list_snd.end()) {
						_system->getMixer()->stopAll();

						_sfx->load(_resource->getFileStream((*i_snd)->getName()));
						i_snd++;
					}
				}

				if (ev.kbd.keycode == Common::KEYCODE_t) {
					if (i_sbe != list_sbe.end()) {
						SubtitleManager subtitle;
						if (subtitle.load(_resource->getFileStream((*i_sbe)->getName()))) {
							for (uint i = 0; i < subtitle.count(); i++) {
								_system->fillScreen(0);
								subtitle.show(*_font, i);
								_system->delayMillis(250);
							}
						}
						i_sbe++;
					}
				}
#endif
				break;

			case Common::EVENT_MAINMENU:
				// Closing the GMM

			case Common::EVENT_MOUSEMOVE:
			case Common::EVENT_LBUTTONDOWN:
			case Common::EVENT_RBUTTONDOWN:
				_logic->handleMouseEvent(ev);
				break;

			case Common::EVENT_QUIT:
				quitGame();
				break;

			default:
				break;
			}

			_graphics->update();
			_system->updateScreen();
			_system->delayMillis(10);
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

} // End of namespace LastExpress
