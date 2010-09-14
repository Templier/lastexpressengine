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

#ifndef LASTEXPRESS_KRONOS_H
#define LASTEXPRESS_KRONOS_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class Kronos : public Entity {
public:
	Kronos(LastExpressEngine *engine);
	~Kronos() {};

	// Setup
	DECLARE_FUNCTION(reset)
	DECLARE_FUNCTION_II(savegame)
	DECLARE_FUNCTION_II(function3)
	DECLARE_FUNCTION_NOSETUP(playSound)
	DECLARE_FUNCTION_NOSETUP(updateFromTime)
	DECLARE_FUNCTION_NOSETUP(updateFromTicks)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(chapter1Handler)
	DECLARE_FUNCTION(function9)
	DECLARE_FUNCTION(function10)
	DECLARE_FUNCTION(function11)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(chapter3Handler)
	DECLARE_FUNCTION(function15)
	DECLARE_FUNCTION(function16)
	DECLARE_FUNCTION(function17)
	DECLARE_FUNCTION(function18)
	DECLARE_FUNCTION(function19)
	DECLARE_FUNCTION(function20)
	DECLARE_FUNCTION(function21)
	DECLARE_FUNCTION(function22)
	DECLARE_FUNCTION(function23)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(chapter5)
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_KRONOS_H
