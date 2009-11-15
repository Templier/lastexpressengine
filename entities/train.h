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

#ifndef LASTEXPRESS_TRAIN_H
#define LASTEXPRESS_TRAIN_H

#include "lastexpress/entities/entity.h"

#include "lastexpress/game/logic.h"

#include "lastexpress/lastexpress.h"

namespace LastExpress {

class LastExpressEngine;

class Train : public Entity {
public:
	Train(LastExpressEngine *engine);

	// Setup	
	DECLARE_FUNCTION(Train, chapter1, 2)
	DECLARE_FUNCTION(Train, chapter2, 3)
	DECLARE_FUNCTION(Train, chapter3, 4)
	DECLARE_FUNCTION(Train, chapter4, 5)
	DECLARE_FUNCTION(Train, chapter5, 6)
	DECLARE_FUNCTION(Train, harem, 7)
	DECLARE_FUNCTION(Train, process, 8)

	void nullfunc(SavePoints::SavePoint *savepoint);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_TRAIN_H
