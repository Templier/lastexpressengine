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

#ifndef LASTEXPRESS_VERGES_H
#define LASTEXPRESS_VERGES_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class Verges : public Entity {
public:
	Verges(LastExpressEngine *engine);
	~Verges() {};

	// Setup
	DECLARE_FUNCTION(reset)
	DECLARE_FUNCTION_S(draw)
	DECLARE_FUNCTION(callbackActionOnDirection)
	DECLARE_FUNCTION_S(playSound)
	DECLARE_FUNCTION_NOSETUP(playSound16)
	DECLARE_FUNCTION(callbackActionOnSomebodyStandingInRestaurantOrSalon)
	DECLARE_FUNCTION_II(savegame)
	DECLARE_FUNCTION_II(updateEntity)
	DECLARE_FUNCTION_S(function9)
	DECLARE_FUNCTION_IIS(function10)
	DECLARE_FUNCTION(function11)
	DECLARE_FUNCTION(function12)
	DECLARE_FUNCTION_I(function13)
	DECLARE_FUNCTION_I(updateFromTime)
	DECLARE_FUNCTION_IS(function15)
	DECLARE_FUNCTION_ISS(function16)
	DECLARE_FUNCTION(function17)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION_NOSETUP(talkHarem)
	DECLARE_FUNCTION(talkPassengerList)
	DECLARE_FUNCTION(talkGendarmes)
	DECLARE_FUNCTION(function22)
	DECLARE_FUNCTION(function23)
	DECLARE_FUNCTION(policeGettingOffTrain)
	DECLARE_FUNCTION(function25)
	DECLARE_FUNCTION(chapter1Handler)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter2Handler)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION_S(function30)
	DECLARE_FUNCTION(function31)
	DECLARE_FUNCTION(function32)
	DECLARE_FUNCTION(function33)
	DECLARE_FUNCTION(function34)
	DECLARE_FUNCTION(function35)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(chapter4Handler)
	DECLARE_FUNCTION(function38)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(chapter5Handler)
	DECLARE_FUNCTION(function41)
	DECLARE_FUNCTION(function42)

private:
	DECLARE_CALL_FUNCTION(iiii, Verges, int, int, int, int)
	DECLARE_CALL_FUNCTION(isii, Verges, int, const char *, int, int)
	DECLARE_CALL_FUNCTION(siis, Verges, const char *, int, int, const char *)
	DECLARE_CALL_FUNCTION(iisi, Verges, int, int, const char *, int)

	void talk(const SavePoint &savepoint, const char* sound1, const char* sound2);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_VERGES_H
