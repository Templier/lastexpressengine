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

#ifndef LASTEXPRESS_PASCALE_H
#define LASTEXPRESS_PASCALE_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class Pascale : public Entity {
public:
	Pascale(LastExpressEngine *engine);
	~Pascale() {};

	// Setup
	DECLARE_FUNCTION_S(draw)
	DECLARE_FUNCTION(callbackActionRestaurantOrSalon)
	DECLARE_FUNCTION(callbackActionOnDirection)
	DECLARE_FUNCTION_I(updateFromTime)
	DECLARE_FUNCTION_NOSETUP(updatePosition)
	DECLARE_FUNCTION_S(playSound)
	DECLARE_FUNCTION_NOSETUP(draw2)
	DECLARE_FUNCTION(function8)
	DECLARE_FUNCTION(sitSophieAndRebecca)
	DECLARE_FUNCTION(function10)
	DECLARE_FUNCTION(function11)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(getMessageFromAugustToTyler)
	DECLARE_FUNCTION(sitAnna)
	DECLARE_FUNCTION(function15)
	DECLARE_FUNCTION(function16)
	DECLARE_FUNCTION(chapter1Handler)
	DECLARE_FUNCTION(function18)
	DECLARE_FUNCTION(function19)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(chapter3Handler)
	DECLARE_FUNCTION(function23)
	DECLARE_FUNCTION(function24)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(chapter4Handler)
	DECLARE_FUNCTION(function27)
	DECLARE_FUNCTION(function28)
	DECLARE_FUNCTION(function29)
	DECLARE_FUNCTION(function30)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(chapter5Handler)
	DECLARE_FUNCTION(function33)
	DECLARE_NULL_FUNCTION()

private:
	DECLARE_CALL_FUNCTION(iiii, Pascale, int, int, int, int)
	DECLARE_CALL_FUNCTION(siis, Pascale, const char *, int, int, const char *)
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_PASCALE_H
