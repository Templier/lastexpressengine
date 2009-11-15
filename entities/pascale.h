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

#include "lastexpress/game/logic.h"

#include "lastexpress/lastexpress.h"

namespace LastExpress {

class LastExpressEngine;

class Pascale : public Entity {
public:
	Pascale(LastExpressEngine *engine);

	// Setup	
	DECLARE_FUNCTION(Pascale, chapter1, 12)
	DECLARE_FUNCTION(Pascale, chapter2, 20)
	DECLARE_FUNCTION(Pascale, chapter3, 21)
	DECLARE_FUNCTION(Pascale, chapter4, 25)
	DECLARE_FUNCTION(Pascale, chapter5, 31)
	DECLARE_FUNCTION_NULL(34)

	void nullfunc(SavePoints::SavePoint *savepoint);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_PASCALE_H
