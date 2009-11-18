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

#ifndef LASTEXPRESS_ENTITIES_H
#define LASTEXPRESS_ENTITIES_H

/*
	Entities
	--------

	The entities structure contains 40 Entity_t structures for each entity

*/

#include "lastexpress/entities/entity.h"

#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"

#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;

class Entities : Common::Serializable {
public:
	Entities(LastExpressEngine *engine);
	~Entities();

	void setup(Logic::ChapterIndex chapter);
	void load(int callbackIndex);

	void reset(SavePoints::EntityIndex entity, Entity::SetupFunction function);

	// Accessors
	Entity::EntityData* getEntityData(uint index);

	// Serializable
	void serialize(Common::Serializer &ser, Entity::EntityData *data);
	void saveLoadWithSerializer(Common::Serializer &ser);

	// Checks
	bool checkFields1(SavePoints::EntityIndex entity, int field495, int field491);
	bool checkFields2(byte object);
	bool checkFields3(SavePoints::EntityIndex entity);

private:
	LastExpressEngine* _engine;

	Entity::EntityData _header;
	Common::Array<Entity *> _entities;	
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITIES_H
