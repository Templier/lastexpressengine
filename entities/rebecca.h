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

#ifndef LASTEXPRESS_REBECCA_H
#define LASTEXPRESS_REBECCA_H

#include "lastexpress/entities/entity.h"

#include "lastexpress/game/logic.h"

#include "lastexpress/lastexpress.h"

namespace LastExpress {

class LastExpressEngine;

class Rebecca : public Entity {
public:
	Rebecca(LastExpressEngine *engine);

	// Setup	
	DECLARE_FUNCTION(Rebecca, chapter1, 21)
	DECLARE_FUNCTION(Rebecca, chapter2, 28)
	DECLARE_FUNCTION(Rebecca, chapter3, 32)
	DECLARE_FUNCTION(Rebecca, chapter4, 42)
	DECLARE_FUNCTION(Rebecca, chapter5, 46)
	DECLARE_FUNCTION_NULL(49)

	void nullfunc(SavePoints::SavePoint *savepoint);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_REBECCA_H
