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

#ifndef LASTEXPRESS_MAX_H
#define LASTEXPRESS_MAX_H

#include "lastexpress/entities/entity.h"

namespace LastExpress {

class LastExpressEngine;

class Max : public Entity {
public:
	Max(LastExpressEngine *engine);
	
	DECLARE_FUNCTION(function1)
	DECLARE_FUNCTION_SEQ(function2)
	// There doesn't seem to be a setup part for function 3 (no idea why), so we skip that part too
	void function3(SavePoints::SavePoint *savepoint);
	DECLARE_FUNCTION_SEQ(function4)
	DECLARE_FUNCTION(savegame)
	DECLARE_FUNCTION(function6)
	DECLARE_FUNCTION(function7)
	DECLARE_FUNCTION(function8)
	DECLARE_FUNCTION(function9)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(function13)
	DECLARE_FUNCTION(freeFromCage)
	DECLARE_FUNCTION(function15)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(function17)
	DECLARE_FUNCTION(chapter5)

private:	
	DECLARE_CALL_FUNCTION(default, Max, int, int, int, int)
	DECLARE_CALL_FUNCTION(char, Max, char*, int, int, char*)
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_MAX_H
