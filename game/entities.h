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

#include "lastexpress/shared.h"

#include "common/serializer.h"


namespace LastExpress {

class LastExpressEngine;

class Entities : Common::Serializable {
public:
	Entities(LastExpressEngine *engine);
	~Entities();

	void setup(ChapterIndex chapter);

	void reset();
	void resetEntity(EntityIndex entity);

	// Update & drawing
	void resetEntityState(EntityIndex entity);
	void updateFields();
	void setupSequences();
	void setupCallbacks();

	void updateField1000(EntityIndex entity, int index, int value);
	void updateField1000ProcessScene(EntityIndex entity, int index, int value);

	void updateFields0(EntityIndex entity1, ObjectIndex entity2);
	void updateFields1(EntityIndex entity1, ObjectIndex entity2);
	void updateFields2(EntityIndex entity1, ObjectIndex entity2);
	void updateFields3(EntityIndex entity1, ObjectIndex entity2);

	// Sequences
	void drawSequenceLeft(EntityIndex index, const char* sequence);
	void drawSequenceRight(EntityIndex index, const char* sequence);
	void drawSequences(EntityIndex index);

	bool checkSequence0(EntityIndex entity);

	// Accessors
	Entity *get(EntityIndex entity);
	EntityData *getData(EntityIndex entity);

	int count() const { return _entities.size(); }

	// Sound
	int getSoundValue(EntityIndex index);

	// Checks
	bool checkEntity(EntityIndex entity, EntityData::Field495Value field495, EntityData::Field491Value field491);
	bool compare(EntityIndex entity1, EntityIndex entity2);

	bool checkFields1(EntityIndex entity, EntityData::Field495Value field495, EntityData::Field491Value field491);
	bool checkFields2(ObjectIndex object);
	bool checkFields3(EntityIndex entity);
	bool checkFields4(EntityData::Field495Value field495, int position);
	bool checkFields5(EntityIndex entity, EntityData::Field495Value field495);
	bool checkFields6(EntityIndex entity);
	bool checkFields7(EntityData::Field495Value field495);
	bool isDirectionUpOrDown(EntityIndex entity);
	bool checkFields9(EntityIndex entity1, EntityIndex entity2, int value);
	bool checkFields10(EntityIndex entity);
	bool checkFields11();
	bool checkFields12(EntityIndex entity);
	bool checkFields13(EntityIndex entity);
	bool checkFields14(EntityIndex entity);
	bool checkFields15();
	bool checkFields16();
	bool checkFields17(EntityIndex entity);
	bool checkFields18(EntityData::Field495Value field495, EntityData::Field491Value field491);
	bool checkFields19(EntityIndex entity, EntityData::Field495Value field495, EntityData::Field491Value field491);
	bool checkFields20(EntityIndex entity);
	bool checkFields21(EntityIndex entity);
	bool checkFields22(EntityIndex entity);
	bool checkFields23(EntityIndex entity);
	bool checkFields24(EntityIndex entity, EntityData::Field491Value field491, unsigned int absValue);
	bool checkFields25(EntityIndex entity);


	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

private:
	LastExpressEngine	    *_engine;
	EntityData 			    *_header;
	Common::Array<Entity *>  _entities;

	void executeCallbacks();
	void processEntity(EntityIndex entity);

	void drawSequenceInternal(EntityIndex index, const char* sequence, EntityDirection direction);
	void drawSequencesInternal(EntityIndex index, EntityDirection direction, bool unknown);

	void getSequenceName(EntityIndex index, EntityDirection direction, char *sequence1, char *sequence2);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITIES_H
