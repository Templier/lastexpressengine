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

#include "lastexpress/game/object.h"
#include "lastexpress/game/state.h"
#include "lastexpress/game/savepoint.h"

#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;

class Entities : Common::Serializable {
public:
	Entities(LastExpressEngine *engine);
	~Entities();

	void setup(State::ChapterIndex chapter);

	void reset(SavePoints::EntityIndex entity);

	// Update & drawing
	void updateFields();	
	void setupSequences();
	void setupCallbacks();

	// Sequences
	void storeSequenceName(SavePoints::EntityIndex entity, const char* sequence);
	void drawSequence(SavePoints::EntityIndex entity, const char* sequence);
	void drawSequences(SavePoints::EntityIndex entity);	

	// Accessors
	Entity *get(SavePoints::EntityIndex entity);
	EntityData *getData(SavePoints::EntityIndex entity);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

	// Checks
	bool checkEntity(SavePoints::EntityIndex entity, int field495, int field491);
	bool compare(SavePoints::EntityIndex entity1, SavePoints::EntityIndex entity2);	

	bool checkFields1(SavePoints::EntityIndex entity, int field495, int field491);
	bool checkFields2(Objects::ObjectIndex object);
	bool checkFields3(SavePoints::EntityIndex entity);
	bool checkFields4(int field495, int field15);
	bool checkFields5(SavePoints::EntityIndex entity, int field495);
	bool checkFields6(SavePoints::EntityIndex entity);
	bool checkFields7(int field495);
	bool checkFields8(SavePoints::EntityIndex entity);
	bool checkFields9(SavePoints::EntityIndex entity1, SavePoints::EntityIndex entity2, int value);
	bool checkFields10(SavePoints::EntityIndex entity);

private:
	LastExpressEngine	    *_engine;
	EntityData 			    *_header;
	Common::Array<Entity *>  _entities;	

	void executeCallbacks();
	void processEntity(SavePoints::EntityIndex entity);	
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITIES_H
