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

namespace LastExpress {

static const PlainGameDescriptor lastExpressGames[] = {
	// Games
	{"lastexpress", "The Last Express"},
	{"lastexpress-demo", "The Last Express (Demo)"},
	{0, 0}
};

static const ADGameDescription gameDescriptions[] = {

	// The Last Express
	{
		"lastexpress",
		"",
		{
			{"HD.HPF",  0, "2d331459e0e68cf277ef4e4043750413", 29865984},
			{"CD1.HPF", 0, "8c86db47304033fcff32c69fddd5a920", 525522944},
			{"CD2.HPF", 0, "58aa26e782d10ec5d2231e539d2fe6a2", 669581312},
			{"CD3.HPF", 0, "00554fbf78a2ad391d98578fbbbe1c48", 641128448},
		},
		Common::EN_ANY,
		Common::kPlatformWindows,
		ADGF_NO_FLAGS,
		Common::GUIO_NONE
	},

	// The Last Express
	{
		"lastexpress",
		"",
		{
			{"HD.HPF",  0, "c14c6d685d9bf8705d9f659062e6c5c2", 29505536},
			{"CD1.HPF", 0, "b4277b22bc5cd6ad3b00c2ec04d4645d", 522924032},
			{"CD2.HPF", 0, "8c9610aa4cb707ab51f61c30feb22c1a", 665710592},
			{"CD3.HPF", 0, "411c1bab57b3e8da4fb359c5b40ef5d7", 640884736},
		},
		Common::FR_FRA,
		Common::kPlatformWindows,
		ADGF_NO_FLAGS,
		Common::GUIO_NONE
	},

	// The Last Express (Demo)
	{
		"lastexpress-demo",
		"",
		{
			{"Demo.HPF",  0, "baf3b1f64155d34872896e61c3d3cb78", 58191872},				
		},
		Common::EN_ANY,
		Common::kPlatformWindows,
		ADGF_NO_FLAGS,
		Common::GUIO_NONE
	},
	AD_TABLE_END_MARKER
};

static const ADParams detectionParams = {
	// Pointer to ADGameDescription or its superset structure
	(const byte *)gameDescriptions,
	// Size of that superset structure
	sizeof(ADGameDescription),
	// Number of bytes to compute MD5 sum for
	5000,
	// List of all engine targets
	lastExpressGames,
	// Structure for autoupgrading obsolete targets
	0,
	// Name of single gameid (optional)
	"lastexpress",
	// List of files for file-based fallback detection (optional)
	0,
	// Flags
	0,
	// Additional GUI options (for every game}
	Common::GUIO_NOSUBTITLES | Common::GUIO_NOSFX
};


class LastExpressMetaEngine : public AdvancedMetaEngine {
public:
	LastExpressMetaEngine() : AdvancedMetaEngine(detectionParams) {}

	const char *getName() const {
		return "LastExpress Engine";
	}

	const char *getOriginalCopyright() const {
		return "LastExpress Engine (C) 1997 Smoking Car Productions";
	}

	bool createInstance(OSystem *syst, Engine **engine, const ADGameDescription *gd) const;
};

bool LastExpressMetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *gd) const {
	if (gd) {
		*engine = new LastExpressEngine(syst, (const ADGameDescription *)gd);
	}
	return gd != 0;
}

} // End of namespace LastExpress

#if PLUGIN_ENABLED_DYNAMIC(LASTEXPRESS)
	REGISTER_PLUGIN_DYNAMIC(LASTEXPRESS, PLUGIN_TYPE_ENGINE, LastExpress::LastExpressMetaEngine);
#else
	REGISTER_PLUGIN_STATIC(LASTEXPRESS, PLUGIN_TYPE_ENGINE, LastExpress::LastExpressMetaEngine);
#endif