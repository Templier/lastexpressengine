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

#ifndef LASTEXPRESS_AUGUST_H
#define LASTEXPRESS_AUGUST_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class August : public Entity {
public:
	August(LastExpressEngine *engine);

	// Setup
	DECLARE_FUNCTION(function1)
	DECLARE_FUNCTION_I(updateFromTime)
	DECLARE_FUNCTION_S(draw)
	DECLARE_FUNCTION_SII(function4)
	DECLARE_FUNCTION_SI(function5)
	DECLARE_FUNCTION_SI(function6)
	DECLARE_FUNCTION_SI(function7)
	DECLARE_FUNCTION(function8)
	DECLARE_FUNCTION_SIIS(function9)
	DECLARE_FUNCTION_IIS(function10)
	DECLARE_FUNCTION_SSI(draw2)
	DECLARE_FUNCTION_S(playSound)
	DECLARE_FUNCTION_S(function13)
	DECLARE_FUNCTION(function14)
	DECLARE_FUNCTION_II(savegame)
	DECLARE_FUNCTION_II(function16)
	DECLARE_FUNCTION_I(function17)
	DECLARE_FUNCTION_II(function18)
	DECLARE_FUNCTION_II(function19)
	DECLARE_FUNCTION_I(function20)
	DECLARE_FUNCTION_I(function21)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION_I(function23)
	DECLARE_FUNCTION(function24)
	DECLARE_FUNCTION(function25)
	DECLARE_FUNCTION(function26)
	DECLARE_FUNCTION(function27)
	DECLARE_FUNCTION(function28)
	DECLARE_FUNCTION(function29)
	DECLARE_FUNCTION(restaurant)
	DECLARE_FUNCTION(function31)
	DECLARE_FUNCTION(function32)
	DECLARE_FUNCTION(function33)
	DECLARE_FUNCTION(function34)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(function36)
	DECLARE_FUNCTION(function37)
	DECLARE_FUNCTION(function38)
	DECLARE_FUNCTION(function39)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION_II(function41)
	DECLARE_FUNCTION_III(function42)
	DECLARE_FUNCTION(function43)
	DECLARE_FUNCTION(function44)
	DECLARE_FUNCTION(function45)
	DECLARE_FUNCTION(function46)
	DECLARE_FUNCTION(function47)
	DECLARE_FUNCTION(function48)
	DECLARE_FUNCTION(function49)
	DECLARE_FUNCTION(function50)
	DECLARE_FUNCTION(function51)
	DECLARE_FUNCTION(function52)
	DECLARE_FUNCTION(function53)
	DECLARE_FUNCTION(function54)
	DECLARE_FUNCTION(function55)
	DECLARE_FUNCTION(function56)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(function58)
	DECLARE_FUNCTION(function59)
	DECLARE_FUNCTION(function60)
	DECLARE_FUNCTION(function61)
	DECLARE_FUNCTION(function62)
	DECLARE_FUNCTION(function63)
	DECLARE_FUNCTION(function64)
	DECLARE_FUNCTION(function65)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(function67)
	DECLARE_FUNCTION(function68)
	DECLARE_FUNCTION(function69)
	DECLARE_NULL_FUNCTION()
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_AUGUST_H
