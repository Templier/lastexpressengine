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

#ifndef LASTEXPRESS_SERVERS1_H
#define LASTEXPRESS_SERVERS1_H

#include "lastexpress/entities/entity.h"
#include "lastexpress/entities/entity_intern.h"

namespace LastExpress {

class LastExpressEngine;

class Servers1 : public Entity {
public:
	Servers1(LastExpressEngine *engine);
	~Servers1() {};

	// Setup
	DECLARE_FUNCTION_NOSETUP(updateFromTime)
	DECLARE_FUNCTION_S(draw)
	DECLARE_FUNCTION_SIII(updatePosition)
	DECLARE_FUNCTION(function4)
	DECLARE_FUNCTION_SIIS(callSavepoint)
	DECLARE_FUNCTION_S(playSound)
	DECLARE_FUNCTION(function7)
	DECLARE_FUNCTION(chapter1)
	DECLARE_FUNCTION(function9)
	DECLARE_FUNCTION(function10)
	DECLARE_FUNCTION(function11)
	DECLARE_FUNCTION(function12)
	DECLARE_FUNCTION(function13)
	DECLARE_FUNCTION(chapter1Handler)
	DECLARE_FUNCTION(function15)
	DECLARE_FUNCTION(function16)
	DECLARE_FUNCTION(chapter2)
	DECLARE_FUNCTION(chapter2Handler)
	DECLARE_FUNCTION(function19)
	DECLARE_FUNCTION(function20)
	DECLARE_FUNCTION(function21)
	DECLARE_FUNCTION(chapter3)
	DECLARE_FUNCTION(chapter3Handler)
	DECLARE_FUNCTION(function24)
	DECLARE_FUNCTION(chapter4)
	DECLARE_FUNCTION(chapter4Handler)
	DECLARE_FUNCTION(function27)
	DECLARE_FUNCTION(function28)
	DECLARE_FUNCTION(function29)
	DECLARE_FUNCTION(chapter5)
	DECLARE_FUNCTION(chapter5Handler)
	DECLARE_NULL_FUNCTION()

private:
	DECLARE_CALL_FUNCTION(siis, Servers1, const char*, int, int, const char*)
	DECLARE_CALL_FUNCTION(iiii, Servers1, int, int, int, int)

	void serveTable(const SavePoint &savepoint, const char* seq1, EntityIndex entity, const char* seq2, const char* seq3, const char* seq4, int *parameter, bool updatePosition = true, int *parameter2 = NULL);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SERVERS1_H
