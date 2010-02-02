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

	// Setup
	DECLARE_FUNCTION_II(savegame)
	DECLARE_FUNCTION_SI(function2)
	DECLARE_FUNCTION_S(function3)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(function5)
	DECLARE_FUNCTION(function6)
	DECLARE_FUNCTION(chapter1_init)
	DECLARE_FUNCTION(chapter1_handler)
	DECLARE_FUNCTION(function9)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter2_init)
	DECLARE_FUNCTION(chapter2_handler)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(chapter3_init)
	DECLARE_FUNCTION(chapter3_handler)
	DECLARE_FUNCTION(function16)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(chapter4_init)
	DECLARE_FUNCTION(chapter4_handler)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(chapter5_init)
	DECLARE_FUNCTION(chapter5_handler)

private:
	DECLARE_CALL_FUNCTION(default, Chapters, int, int, int, int)
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_CHAPTERS_H
