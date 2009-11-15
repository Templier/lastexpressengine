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

#ifndef LASTEXPRESS_SERVERS0_H
#define LASTEXPRESS_SERVERS0_H

#include "lastexpress/entities/entity.h"

#include "lastexpress/game/logic.h"

#include "lastexpress/lastexpress.h"

namespace LastExpress {

class LastExpressEngine;

class Servers0 : public Entity {
public:
	Servers0(LastExpressEngine *engine);

	// Setup	
	DECLARE_FUNCTION(Servers0, chapter1, 11)
	DECLARE_FUNCTION(Servers0, chapter2, 23)
	DECLARE_FUNCTION(Servers0, chapter3, 27)
	DECLARE_FUNCTION(Servers0, chapter4, 31)
	DECLARE_FUNCTION(Servers0, chapter5, 36)
	DECLARE_FUNCTION_NULL(38)

	void nullfunc(SavePoints::SavePoint *savepoint);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SERVERS0_H
