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

#ifndef LASTEXPRESS_COUDERT_H
#define LASTEXPRESS_COUDERT_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class Coudert : public Entity {
public:
	Coudert(LastExpressEngine *engine);
	~Coudert() {};

	// Setup
	DECLARE_FUNCTION(reset)
	DECLARE_FUNCTION_S(bloodJacket)
	DECLARE_FUNCTION_SI(enterExitCompartment)
	DECLARE_FUNCTION(callbackActionOnDirection)
	DECLARE_FUNCTION_SIII(enterExitCompartment2)
	DECLARE_FUNCTION_S(playSound)
	DECLARE_FUNCTION_NOSETUP(playSound16)
	DECLARE_FUNCTION_II(savegame)
	DECLARE_FUNCTION_II(function9)
	DECLARE_FUNCTION_I(function10)
	DECLARE_FUNCTION_I(function11)
	DECLARE_FUNCTION_I(excuseMe)
	DECLARE_FUNCTION_II(function13)
	DECLARE_FUNCTION_I(function14)
	DECLARE_FUNCTION_I(function15)
	DECLARE_FUNCTION(function16)
	DECLARE_FUNCTION_I(function17)
	DECLARE_FUNCTION(function18)
	DECLARE_FUNCTION_I(function19)
	DECLARE_FUNCTION_II(function20)
	DECLARE_FUNCTION(function21)
	DECLARE_FUNCTION(function22)
	DECLARE_FUNCTION(function23)
	DECLARE_FUNCTION(visitCompartmentF)
	DECLARE_FUNCTION(function25)
	DECLARE_FUNCTION(function26)
	DECLARE_FUNCTION(function27)
	DECLARE_FUNCTION(visitCompartmentB)
	DECLARE_FUNCTION(visitCompartmentA)
	DECLARE_FUNCTION_I(function30)
	DECLARE_FUNCTION_I(function31)
	DECLARE_FUNCTION(function32)
	DECLARE_FUNCTION(function33)
	DECLARE_FUNCTION_I(function34)
	DECLARE_FUNCTION_I(function35)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(function37)
	DECLARE_FUNCTION(function38)
	DECLARE_FUNCTION(function39)
	DECLARE_FUNCTION(chapter1Handler)
	DECLARE_FUNCTION(function41)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(function43)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(function45)
	DECLARE_FUNCTION(function46)
	DECLARE_FUNCTION_I(function47)
	DECLARE_FUNCTION(function48)
	DECLARE_FUNCTION(function49)
	DECLARE_FUNCTION(function50)
	DECLARE_FUNCTION(function51)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(function53)
	DECLARE_FUNCTION(function54)
	DECLARE_FUNCTION(function55)
	DECLARE_FUNCTION(function56)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(chapter5Handler)
	DECLARE_FUNCTION(function59)
	DECLARE_FUNCTION(function60)
	DECLARE_FUNCTION(function61)
	DECLARE_FUNCTION(function62)
	DECLARE_NULL_FUNCTION()

private:
	void visitCompartment(const SavePoint &savepoint, EntityPosition position, const char* seq1, ObjectIndex compartment, const char* seq2, const char* seq3, EntityPosition sittingPosition, ObjectIndex object, const char* seq4);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_COUDERT_H
