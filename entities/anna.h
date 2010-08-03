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

#ifndef LASTEXPRESS_ANNA_H
#define LASTEXPRESS_ANNA_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class Anna : public Entity {
public:
	Anna(LastExpressEngine *engine);
	~Anna() {};

	// Setup
	DECLARE_FUNCTION(reset)
	DECLARE_FUNCTION_S(draw)
	DECLARE_FUNCTION_SII(updatePosition)
	DECLARE_FUNCTION_SI(enterExitCompartment)
	DECLARE_FUNCTION(callbackActionOnDirection)
	DECLARE_FUNCTION_SIIS(callSavepoint)
	DECLARE_FUNCTION_S(playSound)
	DECLARE_FUNCTION(callbackActionOnSomebodyStandingInRestaurantOrSalon)
	DECLARE_FUNCTION_II(savegame)
	DECLARE_FUNCTION_II(updateEntity)
	DECLARE_FUNCTION_I(updateFromTime)
	DECLARE_FUNCTION(function12)
	DECLARE_FUNCTION_SSI(draw2)
	DECLARE_FUNCTION_I(updateFromTicks)
	DECLARE_FUNCTION_IS(function15)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION_II(function17)
	DECLARE_FUNCTION_I(function18)
	DECLARE_FUNCTION(chapter1Handler)
	DECLARE_FUNCTION(function20)
	DECLARE_FUNCTION(function21)
	DECLARE_FUNCTION(function22)
	DECLARE_FUNCTION(function23)
	DECLARE_FUNCTION(function24)
	DECLARE_FUNCTION(function25)
	DECLARE_FUNCTION(function26)
	DECLARE_FUNCTION(function27)
	DECLARE_FUNCTION(function28)
	DECLARE_FUNCTION(function29)
	DECLARE_FUNCTION(function30)
	DECLARE_FUNCTION(function31)
	DECLARE_FUNCTION(function32)
	DECLARE_FUNCTION(function33)
	DECLARE_FUNCTION(function34)
	DECLARE_FUNCTION(function35)
	DECLARE_FUNCTION(function36)
	DECLARE_FUNCTION(function37)
	DECLARE_FUNCTION(function38)
	DECLARE_FUNCTION_II(function39)
	DECLARE_FUNCTION(function40)
	DECLARE_FUNCTION(function41)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter2Handler)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION_I(function45)
	DECLARE_FUNCTION(chapter3Handler)
	DECLARE_FUNCTION(function47)
	DECLARE_FUNCTION(function48)
	DECLARE_FUNCTION(leaveTableWithAugust)
	DECLARE_FUNCTION(function50)
	DECLARE_FUNCTION(function51)
	DECLARE_FUNCTION(function52)
	DECLARE_FUNCTION(function53)
	DECLARE_FUNCTION(function54)
	DECLARE_FUNCTION(function55)
	DECLARE_FUNCTION(function56)
	DECLARE_FUNCTION(function57)
	DECLARE_FUNCTION(function58)
	DECLARE_FUNCTION(function59)
	DECLARE_FUNCTION(function60)
	DECLARE_FUNCTION(function61)
	DECLARE_FUNCTION(function62)
	DECLARE_FUNCTION(function63)
	DECLARE_FUNCTION(bagage)
	DECLARE_FUNCTION(function65)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(chapter4Handler)
	DECLARE_FUNCTION(function68)
	DECLARE_FUNCTION(function69)
	DECLARE_FUNCTION(function70)
	DECLARE_FUNCTION(function71)
	DECLARE_FUNCTION_II(function72)
	DECLARE_FUNCTION(function73)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(chapter5Handler)
	DECLARE_FUNCTION(function76)
	DECLARE_FUNCTION(function77)
	DECLARE_FUNCTION(function78)
	DECLARE_FUNCTION(function79)
	DECLARE_FUNCTION(function80)
	DECLARE_FUNCTION(function81)

private:
	DECLARE_CALL_FUNCTION(iiii, Anna, int, int, int, int)
	DECLARE_CALL_FUNCTION(isii, Anna, int, const char*, int, int)
	DECLARE_CALL_FUNCTION(siis, Anna, const char*, int, int, const char*)
	DECLARE_CALL_FUNCTION(ssii, Anna, const char*, const char*, int, int)
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ANNA_H
