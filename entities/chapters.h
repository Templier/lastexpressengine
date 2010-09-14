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

#ifndef LASTEXPRESS_CHAPTERS_H
#define LASTEXPRESS_CHAPTERS_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class Chapters : public Entity {
public:
	Chapters(LastExpressEngine *engine);
	~Chapters() {};

	// Setup
	DECLARE_FUNCTION_II(savegame)
	DECLARE_FUNCTION_SI(enterStation)
	DECLARE_FUNCTION_S(exitStation)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(resetMainEntities)
	DECLARE_FUNCTION(function6)
	DECLARE_FUNCTION(chapter1Init)
	DECLARE_FUNCTION(chapter1Handler)
	DECLARE_FUNCTION(chapter1End)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter2Init)
	DECLARE_FUNCTION(chapter2Handler)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(chapter3Init)
	DECLARE_FUNCTION(chapter3Handler)
	DECLARE_FUNCTION(function16)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(chapter4Init)
	DECLARE_FUNCTION(chapter4Handler)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(chapter5Init)
	DECLARE_FUNCTION(chapter5Handler)

private:
	void enterExitStation(const SavePoint &savepoint, bool isEnteringStation);
	void enterExitHelper(const SavePoint &savepoint, bool isEnteringStation);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_CHAPTERS_H
