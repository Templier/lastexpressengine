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
		byte callbacks[9];
		uint32 field_489;
		uint16 field_48D;
		byte field_48F;
		byte current_call;
		EntityPosition entityPosition;
		EntityField493 field_493;
		CarIndex car;					// word
		byte field_497;
		EntityIndex entity;             // byte
		InventoryItem inventoryItem;	// byte
		EntityDirection direction;		// byte
		int16 field_49B;
		int16 currentFrame2;
		int16 currentFrame3;
		int16 field_4A1;
		int16 field_4A3;
		ClothesIndex clothes;			// byte
		Position position;
		CarIndex car2;                  // byte
		bool doProcessEntity;			// byte
		byte field_4A9;
		byte field_4AA;
		EntityDirection directionSwitch;
		Common::String sequenceName2;        // char[9]
		uint32 field_4B5;
		Common::String sequenceName3;        // char[9]
		uint32 field_4C2;
		Common::String sequenceName;         // char[6]
		byte field_4CC;
		Common::String sequenceNameCopy;     // char[9]
		uint32 field_4D6;
		SequenceFrame *frame;
		SequenceFrame *frame1;
		Sequence *sequence2;
		Sequence *sequence3;
		Sequence *sequence4;

		EntityCallData() {
			memset(&callbacks, 0, 9 * sizeof(byte));
			field_489 = 0;
			field_48D = 0;
			field_48F = 0;
			current_call = 0;
			entityPosition = kPositionNone;
			field_493 = kField493_0;
			car = kCarNone;
			field_497 = 0;
			entity = kEntityNone;
			inventoryItem = kItemNone;
			direction = kDirectionNone;
			field_49B = 0;
			currentFrame2 = 0;
			currentFrame3 = 0;
			field_4A1 = 0;
			field_4A3 = 30;
			clothes = kClothesDefault;
			position = 0;
			car2 = kCarNone;
			doProcessEntity = false;
			field_4A9 = 0;
			field_4AA = 0;
			directionSwitch = kDirectionNone;

			field_4B5 = 0;
			field_4C2 = 0;

			field_4CC = 0;
			field_4D6 = 0;

			frame = NULL;
			frame1 = NULL;
			sequence2 = NULL;
			sequence3 = NULL;
			sequence4 = NULL;
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
	int getCallback() { return _data->getCallback(_data->getCurrentCallback() + 8); }
	void setCallback(byte index) { _data->setCallback(_data->getCurrentCallback() + 8, index); }

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

	// Shared functions
	void savegame(const SavePoint &savepoint);
	void playSound(const SavePoint &savepoint, bool resetItem = false, int param3 = -1);
	void draw(const SavePoint &savepoint, bool handleExcuseMe = false);
	void draw2(const SavePoint &savepoint);
	void updateFromTicks(const SavePoint &savepoint);
	void updateFromTime(const SavePoint &savepoint);

	void function1(const SavePoint &savepoint);
	void function1Clothes(const SavePoint &savepoint);
	void savepointDirection(const SavePoint &savepoint);
	void savepointCheckFields11(const SavePoint &savepoint);
	void checkEntity(const SavePoint &savepoint, bool handleExcuseMe = false);
	void savepointCall(const SavePoint &savepoint, bool handleExcuseMe = false);
	void enterExitCompartment(const SavePoint &savepoint, EntityPosition position1 = kPositionNone, EntityPosition position2 = kPositionNone, CarIndex car = kCarNone, ObjectIndex compartment = kObjectNone, bool alternate = false);
	void updatePosition(const SavePoint &savepoint, bool handleExcuseMe = false);
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_H
