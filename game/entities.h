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
class Sequence;

class Entities : Common::Serializable {
public:
	Entities(LastExpressEngine *engine);
	~Entities();

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

	void setup(bool isFirstChapter, EntityIndex entity);
	void setupChapter(ChapterIndex chapter);
	void reset();

	// Update & drawing

	/**
	 * Reset an entity state
	 *
	 * @param entity entity index
	 * @note remember to call the function pointer (we do not pass it our implementation)
	 */
	void resetState(EntityIndex entity);
	void updateFields() const;
	void updateSequences();
	void updateCallbacks();

	EntityIndex canInteractWith(const Common::Point &point) const;
	bool compare(EntityIndex entity1, EntityIndex entity2);

	/**
	 * Update an entity current sequence frame (and related fields)
	 *
	 * @param entity entity index
	 */
	void updateFrame(EntityIndex entity) const;
	void updatePosition(EntityIndex entity, CarIndex car, Position position, bool processScene = false);
	void enterCompartment(EntityIndex entity, ObjectIndex compartment, bool useCompartment1 = false);
	void exitCompartment(EntityIndex entity, ObjectIndex compartment, bool useCompartment1 = false);

	// Sequences
	void drawSequenceLeft(EntityIndex index, const char* sequence);
	void drawSequenceRight(EntityIndex index, const char* sequence);
	void clearSequences(EntityIndex index);

	bool updateEntity(EntityIndex entity, CarIndex car, EntityPosition position);
	bool hasValidFrame(EntityIndex entity) const;

	// Accessors
	Entity *get(EntityIndex entity);
	EntityData::EntityCallData *getData(EntityIndex entity) const;
	int getPosition(CarIndex car, Position position) { int index = 100 * car + position; assert(index < _positionsCount); return _positions[index]; }
	int getCompartments(int index) { assert(index < _compartmentsCount); return _compartments[index]; }
	int getCompartments1(int index) { assert(index < _compartmentsCount); return _compartments1[index]; }

	// Scene
	void loadSceneFromEntityPosition(CarIndex car, EntityPosition position, bool alternate = false) const;

	//////////////////////////////////////////////////////////////////////////
	// Checks
	//////////////////////////////////////////////////////////////////////////

	/**
	 * Query if 'entity' is sitting.
	 *
	 * @param entity   The entity.
	 * @param car 	   The car.
	 * @param position The position.
	 *
	 * @return true if sitting, false if not.
	 */
	bool isSitting(EntityIndex entity, CarIndex car, EntityPosition position) const;

	bool checkFields2(ObjectIndex object) const;

	/**
	 * Query if 'entity' is sitting in compartment cars.
	 *
	 * @param entity The entity.
	 *
	 * @return true if sitting in compartment cars, false if not.
	 */
	bool isSittingInCompartmentCars(EntityIndex entity) const;

	/**
	 * Query if the player is in the specified position
	 *
	 * @param car       The car.
	 * @param position  The position.
	 * @return true if player is in that position, false if not.
	 */
	bool isPlayerPosition(CarIndex car, Position position) const;

	/**
	 * Query if 'entity' is sitting or standing.
	 *
	 * @param entity The entity.
	 * @param car    The car.
	 *
	 * @return true if sitting or standing, false if not.
	 */
	bool isSittingOrStanding(EntityIndex entity, CarIndex car) const;

	/**
	 * Query if 'entity' is in green car entrance. 
	 *
	 * @param entity The entity. 
	 *
	 * @return true if in the green car entrance, false if not. 
	 */
	bool isInGreenCarEntrance(EntityIndex entity) const;

	/**
	 * Query if the player is in a specific car
	 *
	 * @param car The car. 
	 *
	 * @return true if player is in the car, false if not. 
	 */
	bool isPlayerInCar(CarIndex car) const;

	/**
	 * Query if 'entity' is going in the up or down direction.
	 *
	 * @param entity The entity.
	 *
	 * @return true if direction is up or down, false if not.
	 */
	bool isDirectionUpOrDown(EntityIndex entity) const;

	bool checkFields9(EntityIndex entity1, EntityIndex entity2, int absValue) const;
	bool checkFields10(EntityIndex entity) const;

	/**
	 * Query if there is somebody standing in restaurant or salon.
	 *
	 * @return true if somebody is standing in the restaurant or salon, false if not.
	 */
	bool isSomebodyStandingInRestaurantOrSalon() const;

	/**
	 * Query if 'entity' is in the salon.
	 *
	 * @param entity The entity.
	 *
	 * @return true if in the salon, false if not.
	 */
	bool isInSalon(EntityIndex entity) const;

	/**
	 * Query if 'entity' is in the restaurant.
	 *
	 * @param entity The entity.
	 *
	 * @return true if in the restaurant, false if not.
	 */
	bool isInRestaurant(EntityIndex entity) const;

	/**
	 * Query if 'entity' is in Kronos salon.
	 *
	 * @param entity The entity.
	 *
	 * @return true if in Kronos salon, false if not.
	 */
	bool isInKronosSalon(EntityIndex entity) const;

	bool checkFields15() const;
	bool checkFields16() const;

	/**
	 * Query if 'entity' is in the kitchen.
	 *
	 * @param entity The entity.
	 *
	 * @return true if in the kitchen, false if not.
	 */
	bool isInKitchen(EntityIndex entity) const;

	/**
	 * Query if nobody is sitting at that position.
	 *
	 * @param car 	   The car.
	 * @param position The position.
	 *
	 * @return true if nobody is sitting, false if not.
	 */
	bool isNobodySitting(CarIndex car, EntityPosition position) const;

	bool checkFields19(EntityIndex entity, CarIndex car, EntityPosition position) const;

	/**
	 * Query if 'entity' is in the baggage car entrance.
	 *
	 * @param entity The entity.
	 *
	 * @return true if in the baggage car entrance, false if not.
	 */
	bool isInBaggageCarEntrance(EntityIndex entity) const;

	/**
	 * Query if 'entity' is in the baggage car.
	 *
	 * @param entity The entity.
	 *
	 * @return true if in the baggage car, false if not.
	 */
	bool isInBaggageCar(EntityIndex entity) const;

	/**
	 * Query if 'entity' is in Kronos sanctum.
	 *
	 * @param entity The entity.
	 *
	 * @return true if in Kronos sanctum, false if not.
	 */
	bool isInKronosSanctum(EntityIndex entity) const;

	/**
	 * Query if 'entity' is in Kronos car entrance.
	 *
	 * @param entity The entity.
	 *
	 * @return true if in Kronos car entrance, false if not.
	 */
	bool isInKronosCarEntrance(EntityIndex entity) const;

	/**
	 * Check distance from position.
	 *
	 * @param entity   The entity.
	 * @param position The position.
	 * @param distance The distance.
	 *
	 * @return true if distance is bigger, false otherwise.
	 */
	bool checkDistanceFromPosition(EntityIndex entity, EntityPosition position, int distance) const;

	bool isWalkingOppositeToPlayer(EntityIndex entity) const;

	/**
	 * Query if 'entity' is female.
	 *
	 * @param entity The entity.
	 *
	 * @return true if female, false if not.
	 */
	static bool isFemale(EntityIndex entity);

	/**
	 * Query if 'entity' is married.
	 *
	 * @param entity The entity.
	 *
	 * @return true if married, false if not.
	 */
	static bool isMarried(EntityIndex entity);

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

	void drawSequenceInternal(EntityIndex entity, const char* sequence, EntityDirection direction);
	void drawSequencesInternal(EntityIndex entity, EntityDirection direction, bool loadSequence);
	void loadSequence2(EntityIndex entity, Common::String sequenceName, Common::String sequenceName2, int16 field30, bool loadSequence);

	void clearEntitySequenceData(EntityData::EntityCallData * data, EntityDirection direction);
	void computeCurrentFrame(EntityIndex entity);
	int getCurrentFrame(EntityIndex entity, Sequence *sequence, EntityPosition position, bool doProcessing);
	void processFrame(EntityIndex entity, bool keepPreviousFrame, bool dontPlaySound);
	void drawNextSequence(EntityIndex entity);
	void updateEntityPosition(EntityIndex entity);
	void copySequenceData(EntityIndex entity);

	bool changeCar(EntityData::EntityCallData * data, EntityIndex entity, CarIndex car, EntityPosition position, bool increment, EntityPosition newPosition, CarIndex newCar);

	void getSequenceName(EntityIndex entity, EntityDirection direction, Common::String &sequence1, Common::String &sequence2) const;

	void updatePositionsEnter(EntityIndex entity, CarIndex car, Position position1, Position position2, Position position3, Position position4);
	void updatePositionsExit(EntityIndex entity, CarIndex car, Position position1, Position position2);

	void resetSequences(EntityIndex entity) const;

	bool checkPosition(EntityPosition position) const;
	bool checkSequenceFromPosition(EntityIndex entity) const;
	EntityPosition getEntityPositionFromCurrentPosition() const;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITIES_H
