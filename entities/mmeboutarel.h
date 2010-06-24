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

#ifndef LASTEXPRESS_MMEBOUTAREL_H
#define LASTEXPRESS_MMEBOUTAREL_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class MmeBoutarel : public Entity {
public:
	MmeBoutarel(LastExpressEngine *engine);
	~MmeBoutarel() {};

	// Setup
	DECLARE_FUNCTION(function1)
	DECLARE_FUNCTION_S(playSound)
	DECLARE_FUNCTION_S(draw)
	DECLARE_FUNCTION_I(updateFromTime)
	DECLARE_FUNCTION_SI(enterExitCompartment)
	DECLARE_FUNCTION_SI(function6)
	DECLARE_FUNCTION_II(function7)
	DECLARE_FUNCTION_S(function8)
	DECLARE_FUNCTION(function9)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(function11)
	DECLARE_FUNCTION(chapter1_handler)
	DECLARE_FUNCTION(function13)
	DECLARE_FUNCTION(function14)
	DECLARE_FUNCTION(function15)
	DECLARE_FUNCTION(function16)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(function18)
	DECLARE_FUNCTION(function19)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(function21)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(function23)
	DECLARE_FUNCTION(function24)
	DECLARE_FUNCTION(function25)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(function27)
	DECLARE_FUNCTION(function28)
	DECLARE_NULL_FUNCTION()

private:
	DECLARE_CALL_FUNCTION(iiii, MmeBoutarel, int, int, int, int)
	DECLARE_CALL_FUNCTION(siis, MmeBoutarel, const char*, int, int, const char*)
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_MMEBOUTAREL_H
