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

#ifndef LASTEXPRESS_SOPHIE_H
#define LASTEXPRESS_SOPHIE_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class Sophie : public Entity {
public:
	Sophie(LastExpressEngine *engine);
	~Sophie() {};

	// Setup
	DECLARE_FUNCTION(reset)
	DECLARE_FUNCTION_II(function2)
	DECLARE_FUNCTION(chapters_handler)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(function5)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(function9)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(chapter5Handler)
	DECLARE_NULL_FUNCTION()

private:
	DECLARE_CALL_FUNCTION(iiii, Sophie, int, int, int, int)
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SOPHIE_H
