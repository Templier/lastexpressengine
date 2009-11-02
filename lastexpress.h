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

#include "engines/advancedDetector.h"
#include "engines/engine.h"

namespace LastExpress {

class Cursor;
class Font;
class GraphicsManager;
class Logic;
class ResourceManager;
class Scene;
class SceneManager;
class StreamedSound;

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

	// Accessors
	Cursor *getCursor() const { return _cursor; }
	Font *getFont() const { return _font; }
	Logic *getLogic() const { return _logic; }
	ResourceManager *getResMan() const { return _resMan; }
	StreamedSound *getMusicStream() const { return _music; }
	StreamedSound *getSfxStream() const { return _sfx; }
	GraphicsManager *getGraphicsManager() const { return _graphics; }
	Scene *getScene(uint16 sceneId) const;
	Common::RandomSource getRandom() const {return _random; }

private:
	const ADGameDescription *_gameDescription;
	Graphics::PixelFormat _pixelFormat;
	Cursor *_cursor;
	Debugger *_debugger;
	Font *_font;
	Logic *_logic;
	ResourceManager *_resMan;
	StreamedSound *_music;
	StreamedSound *_sfx;
	GraphicsManager *_graphics;
	SceneManager *_sceneMan;

	Common::RandomSource _random;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_H
