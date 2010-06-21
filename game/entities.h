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

#include "common/rect.h"
#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;

class Entities : Common::Serializable {
public:
	Entities(LastExpressEngine *engine);
	~Entities();

	void setup(ChapterIndex chapter);
	void reset();

	// Update & drawing

	/**
	 * Reset an entity state
	 *
	 * @param entityIndex entity index
	 * @note remember to call the function pointer (we do not pass it our implementation)
	 */
	void resetState(EntityIndex entity);
	void updateFields() const;
	void updateSequences();
	void updateCallbacks();

	EntityIndex canInteractWith(const Common::Point &point) const;

	/**
	 * Update an entity current sequence frame (and related fields)
	 *
	 * @param entityIndex entity index
	 */
	void updateEntity(EntityIndex entity) const;

	void updatePosition(EntityIndex entity, CarIndex car, Position position, bool processScene = false);

	void enterCompartment(EntityIndex entity, ObjectIndex compartment, bool useFirstCompartments = true);
	void exitCompartment(EntityIndex entity, ObjectIndex compartment, bool useFirstCompartments = true);

	// Sequences
	void drawSequenceLeft(EntityIndex index, const char* sequence);
	void drawSequenceRight(EntityIndex index, const char* sequence);
	void prepareSequences(EntityIndex index);

	bool checkSequence0(EntityIndex entity) const;

	// Accessors
	Entity *get(EntityIndex entity);
	EntityData::EntityCallData *getData(EntityIndex entity) const;
	int getPosition(int index) { assert(index < _positionsCount); return _positions[index]; }
	int getCompartments(int index) { assert(index < _compartmentsCount); return _compartments[index]; }
	int getCompartments1(int index) { assert(index < _compartmentsCount); return _compartments1[index]; }

	int count() const { return _entities.size(); }

	// Scene
	void loadSceneFromField491(CarIndex car, EntityData::Field491Value field491, bool alternate = false) const;

	// Sound
	uint getSoundValue(EntityIndex index) const;

	// Checks
	bool checkEntity(EntityIndex entity, CarIndex car, EntityData::Field491Value field491);
	bool compare(EntityIndex entity1, EntityIndex entity2);

	bool checkFields1(EntityIndex entity, CarIndex car, EntityData::Field491Value field491) const;
	bool checkFields2(ObjectIndex object) const;
	bool checkFields3(EntityIndex entity) const;

	/**
	 * Check if the player is in the specified position
	 * @param car 		The car.
	 * @param position  The position.
	 * @return true if player is in that position, false if not.
	*/
	bool isPlayerPosition(CarIndex car, Position position) const;
	bool checkFields5(EntityIndex entity, CarIndex car) const;
	bool checkFields6(EntityIndex entity) const;
	bool checkFields7(CarIndex car) const;
	bool isDirectionUpOrDown(EntityIndex entity) const;
	bool checkFields9(EntityIndex entity1, EntityIndex entity2, int absValue) const;
	bool checkFields10(EntityIndex entity) const;
	bool checkFields11() const;
	bool checkFields12(EntityIndex entity) const;
	bool checkFields13(EntityIndex entity) const;
	bool checkFields14(EntityIndex entity) const;
	bool checkFields15() const;
	bool checkFields16() const;
	bool checkFields17(EntityIndex entity) const;
	bool checkFields18(CarIndex car, EntityData::Field491Value field491) const;
	bool checkFields19(EntityIndex entity, CarIndex car, EntityData::Field491Value field491) const;
	bool checkFields20(EntityIndex entity) const;
	bool checkFields21(EntityIndex entity) const;
	bool checkFields22(EntityIndex entity) const;
	bool checkFields23(EntityIndex entity) const;
	bool checkFields24(EntityIndex entity, EntityData::Field491Value field491, int absValue) const;
	bool checkFields25(EntityIndex entity) const;

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

private:
	static const int _compartmentsCount = 16;
	static const int _positionsCount = 100 * 10;  // 100 positions per train car

	LastExpressEngine	    *_engine;
	EntityData 			    *_header;
	Common::Array<Entity *>  _entities;

	// Compartments & positions
	uint _compartments[_compartmentsCount];
	uint _compartments1[_compartmentsCount];
	uint _positions[_positionsCount];

	void executeCallbacks();
	void processEntity(EntityIndex entity);

	void drawSequenceInternal(EntityIndex index, const char* sequence, EntityDirection direction);
	void drawSequencesInternal(EntityIndex index, EntityDirection direction, bool unknown);

	void getSequenceName(EntityIndex index, EntityDirection direction, char *sequence1, char *sequence2) const;

	void updatePositionsEnter(EntityIndex entity, CarIndex car, Position position1, Position position2, Position position3, Position position4);
	void updatePositionsExit(EntityIndex entity, CarIndex car, Position position1, Position position2);

	void resetSequences(EntityIndex entity) const;

	bool checkField491(EntityData::Field491Value field491) const;
	bool checkSequenceFromPosition(EntityIndex entity) const;
	EntityData::Field491Value getField491FromCurrentPosition() const;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITIES_H
