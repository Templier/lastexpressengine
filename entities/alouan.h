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

#ifndef LASTEXPRESS_ALOUAN_H
#define LASTEXPRESS_ALOUAN_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class Alouan : public Entity {
public:
	Alouan(LastExpressEngine *engine);
	~Alouan() {};

	// Setup
	DECLARE_FUNCTION(reset)
	DECLARE_FUNCTION_SI(enterExitCompartment)
	DECLARE_FUNCTION_S(playSound)
	DECLARE_FUNCTION_I(updateFromTime)
	DECLARE_FUNCTION_II(updateEntity)
	DECLARE_FUNCTION(compartment6)
	DECLARE_FUNCTION(compartment8)
	DECLARE_FUNCTION(compartment6to8)
	DECLARE_FUNCTION(compartment8to6)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(chapter1Handler)
	DECLARE_FUNCTION(function12)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter2Handler)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(chapter3Handler)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(chapter4Handler)
	DECLARE_FUNCTION(function19)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(chapter5Handler)
	DECLARE_FUNCTION(function22)
	DECLARE_FUNCTION(function23)
	DECLARE_NULL_FUNCTION()
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ALOUAN_H
