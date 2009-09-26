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
 
#include "engines/advancedDetector.h"
#include "engines/engine.h"
#include "graphics/surface.h"

#include "lastexpress/debug.h"
#include "lastexpress/resource.h"
 
namespace LastExpress {
 
enum {
	kLastExpressDebugAll = 1 << 0,
	kLastExpressDebugVideo = 1 << 1,
	kLastExpressDebugResource = 1 << 2,
	kLastExpressDebugCursor = 1 << 3,
	kLastExpressDebugSound = 1 << 4,
	kLastExpressDebugSubtitle = 1 << 5,	
	// the current limitation is 32 debug levels (1 << 31 is the last one)
};
 
class LastExpressEngine : public Engine {
public:
	LastExpressEngine(OSystem *syst, const ADGameDescription *gd);
	~LastExpressEngine();

protected:

	// Engine APIs
	Common::Error run();
	virtual void errorString(const char *buf_input, char *buf_output, int buf_output_size);

	virtual bool hasFeature(EngineFeature f) const;

	virtual Debugger *getDebugger() { return _debugger; }

	friend class Debugger;

private:
	const ADGameDescription *_gameDescription;
	Debugger *_debugger;
	ResourceManager *_resource;

	Common::Error init();
	Common::Error go();
};
 
} // End of namespace LastExpress
 
#endif // LASTEXPRESS_H