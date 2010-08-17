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

#ifndef LASTEXPRESS_ALEXEI_H
#define LASTEXPRESS_ALEXEI_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class Alexei : public Entity {
public:
	Alexei(LastExpressEngine *engine);
	~Alexei() {};

	// Setup
	DECLARE_FUNCTION(reset)
	DECLARE_FUNCTION_S(playSound)
	DECLARE_FUNCTION_I(updateFromTicks)
	DECLARE_FUNCTION_S(draw)
	DECLARE_FUNCTION_SII(updatePosition)
	DECLARE_FUNCTION_SI(enterExitCompartment)
	DECLARE_FUNCTION(callbackActionOnDirection)
	DECLARE_FUNCTION_SIIS(callSavepoint)
	DECLARE_FUNCTION_II(savegame)
	DECLARE_FUNCTION_II(updateEntity)
	DECLARE_FUNCTION_NOSETUP(draw2)
	DECLARE_FUNCTION(callbackActionRestaurantOrSalon)
	DECLARE_FUNCTION(function13)
	DECLARE_FUNCTION(function14)
	DECLARE_FUNCTION(function15)
	DECLARE_FUNCTION_IS(function16)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(chapter1Handler)
	DECLARE_FUNCTION(function19)
	DECLARE_FUNCTION(function20)
	DECLARE_FUNCTION(function21)
	DECLARE_FUNCTION(function22)
	DECLARE_FUNCTION(function23)
	DECLARE_FUNCTION(function24)
	DECLARE_FUNCTION(function25)
	DECLARE_FUNCTION(function26)
	DECLARE_FUNCTION(function27)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter2Handler)
	DECLARE_FUNCTION(function30)
	DECLARE_FUNCTION(function31)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(chapter3Handler)
	DECLARE_FUNCTION(function34)
	DECLARE_FUNCTION(function35)
	DECLARE_FUNCTION(function36)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(chapter4Handler)
	DECLARE_FUNCTION(function39)
	DECLARE_FUNCTION(function40)
	DECLARE_FUNCTION(function41)
	DECLARE_FUNCTION(function42)
	DECLARE_FUNCTION(function43)
	DECLARE_FUNCTION(function44)
	DECLARE_FUNCTION(function45)
	DECLARE_FUNCTION(function46)
	DECLARE_FUNCTION(function47)
	DECLARE_FUNCTION(chapter5)

private:
	DECLARE_CALL_FUNCTION(iiii, Alexei, uint, uint, uint, uint)
	DECLARE_CALL_FUNCTION(siis, Alexei, const char *, uint, uint, const char *)
	DECLARE_CALL_FUNCTION(isii, Alexei, uint, const char *, uint, uint)
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ALEXEI_H
