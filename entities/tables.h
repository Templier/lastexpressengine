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

#ifndef LASTEXPRESS_TABLES_H
#define LASTEXPRESS_TABLES_H

#include "lastexpress/entities/entity.h"

#include "lastexpress/game/logic.h"

#include "lastexpress/lastexpress.h"

namespace LastExpress {

class LastExpressEngine;

class Tables : public Entity {
public:
	Tables(LastExpressEngine *engine, int id);

	// Setup	
	DECLARE_FUNCTION(Tables, chapter1, 1)
	DECLARE_FUNCTION(Tables, chapter2, 2)
	DECLARE_FUNCTION(Tables, chapter3, 3)
	DECLARE_FUNCTION(Tables, chapter4, 4)
	DECLARE_FUNCTION(Tables, chapter5, 5)
	DECLARE_FUNCTION(Tables, draw, 6)

	void nullfunc(SavePoints::SavePoint *savepoint);
	
private:
	int _id;	///< Table entity id
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_TABLES_H
