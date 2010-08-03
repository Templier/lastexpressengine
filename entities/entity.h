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

#ifndef LASTEXPRESS_ENTITY_H
#define LASTEXPRESS_ENTITY_H

#include "lastexpress/shared.h"

#include "lastexpress/game/sound.h"

#include "common/array.h"
#include "common/func.h"
#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;
class Sequence;
class SequenceFrame;
struct SavePoint;

class EntityData : Common::Serializable {
public:

	struct EntityParameters {
	};

	struct EntityParametersIIII : EntityParameters {
		int param1;
		int param2;
		int param3;
		int param4;
		int param5;
		int param6;
		int param7;
		int param8;

		EntityParametersIIII() {
			param1 = 0;
			param2 = 0;
			param3 = 0;
			param4 = 0;
			param5 = 0;
			param6 = 0;
			param7 = 0;
			param8 = 0;
		}

		bool hasNonNullParameter() {
			return param1 || param2 || param3 || param4 || param5 || param6 || param7 || param8;
		}
	};

	struct EntityParametersSIII : EntityParameters {
		char seq[12];
		int param4;
		int param5;
		int param6;
		int param7;
		int param8;

		EntityParametersSIII() {
			memset(&seq, 0, 12);
			param4 = 0;
			param5 = 0;
			param6 = 0;
			param7 = 0;
			param8 = 0;
		}
	};

	struct EntityParametersSIIS : EntityParameters {
		char seq1[12];
		int param4;
		int param5;
		char seq2[12];

		EntityParametersSIIS() {
			memset(&seq1, 0, 12);
			param4 = 0;
			param5 = 0;
			memset(&seq2, 0, 12);
		}
	};

	struct EntityParametersISSI : EntityParameters {
		int param1;
		char seq1[12];
		char seq2[12];
		int param8;

		EntityParametersISSI() {
			param1 = 0;
			memset(&seq1, 0, 12);
			memset(&seq2, 0, 12);
			param8 = 0;
		}
	};

	struct EntityParametersISII : EntityParameters {
		int param1;
		char seq[12];
		int param5;
		int param6;
		int param7;
		int param8;

		EntityParametersISII() {
			param1 = 0;
			memset(&seq, 0, 12);
			param5 = 0;
			param6 = 0;
			param7 = 0;
			param8 = 0;
		}
	};

	struct EntityParametersSSII : EntityParameters {
		char seq1[12];
		char seq2[12];
		int param7;
		int param8;

		EntityParametersSSII() {
			memset(&seq1, 0, 12);
			memset(&seq2, 0, 12);
			param7 = 0;
			param8 = 0;
		}
	};

	struct EntityParametersIISS : EntityParameters {
		int param1;
		int param2;
		char seq1[12];
		char seq2[12];

		EntityParametersIISS() {
			param1 = 0;
			param2 = 0;
			memset(&seq1, 0, 12);
			memset(&seq2, 0, 12);
		}
	};

	struct EntityParametersIISI : EntityParameters {
		int param1;
		int param2;
		char seq1[12];
		int param6;
		int param7;
		int param8;

		EntityParametersIISI() {
			param1 = 0;
			param2 = 0;
			memset(&seq1, 0, 12);
			param6 = 0;
			param7 = 0;
			param8 = 0;
		}
	};

	struct EntityParametersIIIS : EntityParameters {
		int param1;
		int param2;
		int param3;
		char seq[12];
		int param7;
		int param8;

		EntityParametersIIIS() {
			param1 = 0;
			param2 = 0;
			param3 = 0;
			memset(&seq, 0, 12);
			param7 = 0;
			param8 = 0;
		}
	};

	struct EntityCallParameters {
		EntityParameters* parameters[4];

		EntityCallParameters() {
			create();
		}

		~EntityCallParameters() {
			clear();
		}


		// We default to int parameters
		void create() {
			for (int i = 0; i < 4; i++)
				parameters[i] = new EntityParametersIIII();
		}

		void clear() {
			for (int i = 0; i < 4; i++)
				delete parameters[i];
		}


	};

	struct EntityCallData {
		byte callbacks[16];
		byte current_call;
		EntityPosition entityPosition;  // word
		Posture posture;				// word
		CarIndex car;					// word
		byte field_497;
		EntityIndex entity;             // byte
		InventoryItem inventoryItem;	// byte
		EntityDirection direction;		// byte
		int16 field_49B;
		int16 currentFrame;
		int16 currentFrame2;
		int16 field_4A1;
		int16 field_4A3;
		ClothesIndex clothes;			    // byte
		Position position;
		CarIndex car2;                      // byte
		bool doProcessEntity;               // byte
		bool field_4A9;	                    // byte
		bool field_4AA;                     // byte
		EntityDirection directionSwitch;
		Common::String sequenceName;        // char[13]
		Common::String sequenceName2;       // char[13]
		Common::String sequenceNamePrefix;  // char[7]
		Common::String sequenceNameCopy;    // char[13]
		SequenceFrame *frame;
		SequenceFrame *frame1;
		Sequence *sequence;
		Sequence *sequence2;
		Sequence *sequence3;

		/**
		 * Default constructor.
		 */
		EntityCallData() {
			memset(&callbacks, 0, 16 * sizeof(byte));
			current_call = 0;
			entityPosition = kPositionNone;
			posture = kPostureStanding;
			car = kCarNone;
			field_497 = 0;
			entity = kEntityNone;
			inventoryItem = kItemNone;
			direction = kDirectionNone;
			field_49B = 0;
			currentFrame = 0;
			currentFrame2 = 0;
			field_4A1 = 0;
			field_4A3 = 30;
			clothes = kClothesDefault;
			position = 0;
			car2 = kCarNone;
			doProcessEntity = false;
			field_4A9 = false;
			field_4AA = false;
			directionSwitch = kDirectionNone;
			frame = NULL;
			frame1 = NULL;
			sequence = NULL;
			sequence2 = NULL;
			sequence3 = NULL;
		}

		/**
		 * Convert this object into a string representation.
		 *
		 * @return A string representation of this object.
		 */
		Common::String toString() {
			Common::String str = "";

			str += Common::String::printf("Entity position: %d    - Posture: %d       - Car: %d\n", entityPosition, posture, car);
			str += Common::String::printf("Entity: %d             - Item: %d          - Direction: %d\n", entity, inventoryItem, direction);
			str += Common::String::printf("Clothes: %d            - Position: %d      - Direction switch: %d\n", clothes, position, directionSwitch);
			str += "\n";
			str += Common::String::printf("field_497: %02d        - field_49B: %i     - field_4A1: %i\n", field_497, field_49B, field_4A1);
			str += Common::String::printf("field_4A9: %02d        - field_4AA: %i     - Car 2: %d\n", field_4A9, field_4AA, car2);
			str += "\n";
			str += "Sequence: " + sequenceName + "    - Sequence 2: " + sequenceName2 + "\n";
			str += "Sequence prefix: " + sequenceNamePrefix + "    - Sequence copy: " + sequenceNameCopy + "\n";
			str += Common::String::printf("Current frame: %i    - Current frame 2: %i       - Process entity: %d\n", currentFrame, currentFrame2, doProcessEntity);

			return str;
		}
	};

	EntityData() {}

	EntityCallData 	  *getCallData() { return &_data; }

	EntityParameters  *getParameters(int callback, int index) { return _parameters[callback].parameters[index]; }
	EntityParameters  *getCurrentParameters(int index = 0) { return getParameters(_data.current_call, index); }
	void 			   resetCurrentParameters();

	int 			   getCallback(int callback) { return _data.callbacks[callback]; }
	int				   getCurrentCallback() { return getCallback(_data.current_call); }
	void 			   setCallback(int callback, byte index) { _data.callbacks[callback] = index; }
	void 			   setCurrentCallback(byte index) { setCallback(_data.current_call, index); }

	// Serializable
	void 			   saveLoadWithSerializer(Common::Serializer &ser);

private:

	EntityCallData 		 _data;
	EntityCallParameters _parameters[9];
};

class Entity : Common::Serializable {
public:

	typedef Common::Functor1<const SavePoint&, void> Callback;

	Entity(LastExpressEngine *engine, EntityIndex index);
	virtual ~Entity();

	// Accessors
	EntityData *getParamData() { return _data; }
	EntityData::EntityCallData *getData() { return _data->getCallData(); }

	// Callbacks
	int getCallback() { return _data->getCallback(_data->getCallData()->current_call + 8); }
	void setCallback(byte index) { _data->setCallback(_data->getCallData()->current_call + 8, index); }

	// Setup
	void setup(ChapterIndex index);

	virtual void setup_chapter1(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter2(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter3(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter4(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter5(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser) { _data->saveLoadWithSerializer(ser); }

	void nullfunction(const SavePoint &savepoint) {}

protected:
	LastExpressEngine* _engine;

	EntityIndex				  _entityIndex;
	EntityData 				 *_data;
	Common::Array<Callback *> _callbacks;

	/**
	 * Saves the game
	 *
	 * @param savepoint The savepoint
	 *                   - SavegameType
	 *                   - EventIndex
	 */
	void savegame(const SavePoint &savepoint);

	/**
	 * Play sound
	 *
	 * @param savepoint The savepoint
	 *                    - Sound filename
	 * @param resetItem true to reset item.
	 * @param flag      sound flag
	 */
	void playSound(const SavePoint &savepoint, bool resetItem = false, SoundManager::FlagType flag = SoundManager::kFlagInvalid);

	/**
	 * Draws the entity
	 *
	 * @param savepoint 	 The savepoint
	 *                         - Sequence
	 *                         - ExcuseMe flag
	 * @param handleExcuseMe true to handle excuseMeCath action
	 */
	void draw(const SavePoint &savepoint, bool handleExcuseMe = false);

	/**
	 * Draws the entity along with another one
	 *
	 * @param savepoint The savepoint.
	 *                    - Sequence 1
	 *                    - Sequence 2
	 *                    - EntityIndex
	 */
	void draw2(const SavePoint &savepoint);

	/**
	 * Updates parameter 2 using ticks value
	 *
	 * @param savepoint The savepoint
	 *                    - Number of ticks to add
	 */
	void updateFromTicks(const SavePoint &savepoint);

	/**
	 * Updates parameter 2 using time value
	 *
	 * @param savepoint The savepoint.
	 *                    - Time to add
	 */
	void updateFromTime(const SavePoint &savepoint);

	/**
	 * Resets an entity
	 *
	 * @param savepoint    The savepoint.
	 * @param resetClothes true to reset clothes.
	 */
	void reset(const SavePoint &savepoint, bool resetClothes = false);

	/**
	 * Process callback action when the entity direction is not kDirectionRight
	 *
	 * @param savepoint The savepoint.
	 */
	void callbackActionOnDirection(const SavePoint &savepoint);

	void savepointCheckFields11(const SavePoint &savepoint);

	/**
	 * Updates the entity
	 *
	 * @param savepoint 	 The savepoint.
	 *                        - CarIndex
	 *                        - EntityPosition
	 * @param handleExcuseMe true to handle the kActionExcuseMe/kActionExcuseMeCath actions.
	 */
	void updateEntity(const SavePoint &savepoint, bool handleExcuseMe = false);

	/**
	 * Call a specific savepoint (or draw sequence in default case)
	 *
	 * @param savepoint 	 The savepoint.
	 *                         - Sequence to draw in default case
	 *                         - EntityIndex
	 *                         - ActionIndex
	 *                         - Sequence for the savepoint
	 * @param handleExcuseMe true to handle excuse me.
	 */
	void callSavepoint(const SavePoint &savepoint, bool handleExcuseMe = false);

	/**
	 * Handles entering/exiting a compartment.
	 *
	 * @param savepoint   The savepoint.
	 * @param position1   The first position.
	 * @param position2   The second position.
	 * @param car 		  The car.
	 * @param compartment The compartment.
	 * @param alternate   true to use the alternate version of SceneManager::loadSceneFromObject()
	 */
	void enterExitCompartment(const SavePoint &savepoint, EntityPosition position1 = kPositionNone, EntityPosition position2 = kPositionNone, CarIndex car = kCarNone, ObjectIndex compartment = kObjectNone, bool alternate = false, bool updatePosture = false);

	/**
	 * Updates the position
	 *
	 * @param savepoint 	 The savepoint
	 *                        - Sequence name
	 *                        - CarIndex
	 *                        - Position
	 * @param handleExcuseMe true to handle excuseMe actions
	 */
	void updatePosition(const SavePoint &savepoint, bool handleExcuseMe = false);
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_H
