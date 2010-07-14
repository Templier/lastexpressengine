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

	enum Field491Value {
		kField491_0     = 0,
		kField491_1     = 1,
		kField491_3     = 3,
		kField491_4     = 4,
		kField491_540   = 540,
		kField491_750  = 750,
		kField491_850   = 850,
		kField491_851   = 851,
		kField491_1200  = 1200,
		kField491_1430  = 1430,
		kField491_1500  = 1500,
		kField491_1540  = 1540,
		kField491_1750  = 1750,
		kField491_2000  = 2000,
		kField491_2087  = 2087,
		kField491_2086  = 2086,
		kField491_2088  = 2088,
		kField491_2110  = 2110,
		kField491_2300  = 2300,
		kField491_2410  = 2410,
		kField491_2436  = 2436,
		kField491_2490  = 2490,
		kField491_2500  = 2500,
		kField491_2587  = 2587,
		kField491_2690  = 2690,
		kField491_2740  = 2740,
		kField491_2830  = 2830,
		kField491_2980  = 2980,
		kField491_3050  = 3050,
		kField491_3110  = 3110,
		kField491_3390  = 3390,
		kField491_3450  = 3450,
		kField491_3500  = 3500,
		kField491_3650  = 3650,
		kField491_3760  = 3760,
		kField491_3820  = 3820,
		kField491_3890  = 3890,
		kField491_3969  = 3969,
		kField491_3970  = 3970,
		kField491_4070  = 4070,
		kField491_4100  = 4100,
		kField491_4455  = 4455,
		kField491_4460  = 4460,
		kField491_4500  = 4500,
		kField491_4590  = 4590,
		kField491_4680  = 4680,
		kField491_4689  = 4689,
		kField491_4690  = 4690,
		kField491_4691  = 4691,
		kField491_4770  = 4470,
		kField491_4840  = 4840,
		kField491_5000  = 5000,
		kField491_5090  = 5090,
		kField491_5140  = 5140,
		kField491_5419  = 5419,
		kField491_5420  = 5420,
		kField491_5440  = 5440,
		kField491_5500  = 5500,
		kField491_5540  = 5540,
		kField491_5610  = 5610,
		kField491_5790  = 5790,
		kField491_5800  = 5800,
		kField491_5810  = 5810,
		kField491_5900  = 5900,
		kField491_6000  = 6000,
		kField491_6130  = 6130,
		kField491_6160  = 6160,
		kField491_6220  = 6220,
		kField491_6410  = 6410,
		kField491_6460  = 6460,
		kField491_6470  = 6470,
		kField491_6471  = 6471,
		kField491_6800  = 6800,
		kField491_6850  = 6850,
		kField491_7000  = 7000,
		kField491_7160  = 7160,
		kField491_7250  = 7250,
		kField491_7320  = 7320,
		kField491_7500  = 7500,
		kField491_7510  = 7510,
		kField491_7850  = 7850,
		kField491_7870  = 7870,
		kField491_7900  = 7900,
		kField491_7950  = 7950,
		kField491_8000  = 8000,
		kField491_8013  = 8013,
		kField491_8160  = 8160,
		kField491_8200  = 8200,
		kField491_8500  = 8500,
		kField491_8513  = 8513,
		kField491_8514  = 8514,
		kField491_8800  = 8800,
		kField491_9020  = 9020,
		kField491_9269  = 9269,
		kField491_9250  = 9250,
		kField491_9270  = 9270,
		kField491_9460  = 9460,
		kField491_30000 = 30000
	};

	enum Field493Value {
		kField493_0 = 0,
		kField493_1 = 1,
		kField493_2 = 2,
		kField493_3 = 3,
		kField493_4 = 4
	};

	enum ParameterValue {
		kParamTime = 2147483647
	};

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
		int param2;
		int param3;
		int param4;
		int param5;
		int param6;

		EntityParametersSIII() {
			memset(&seq, 0, 12);
			param2 = 0;
			param3 = 0;
			param4 = 0;
			param5 = 0;
			param6 = 0;
		}
	};

	struct EntityParametersSIIS : EntityParameters {
		char seq1[12];
		int param2;
		int param3;
		char seq2[12];

		EntityParametersSIIS() {
			memset(&seq1, 0, 12);
			param2 = 0;
			param3 = 0;
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
		int param2;
		int param3;
		int param4;

		EntityParametersISII() {
			param1 = 0;
			memset(&seq, 0, 12);
			param2 = 0;
			param3 = 0;
			param4 = 0;
		}
	};

	struct EntityParametersSSII : EntityParameters {
		char seq1[12];
		char seq2[12];
		int param3;
		int param4;

		EntityParametersSSII() {
			memset(&seq1, 0, 12);
			memset(&seq2, 0, 12);
			param3 = 0;
			param4 = 0;
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
		int param3;
		int param4;
		int param5;

		EntityParametersIISI() {
			param1 = 0;
			param2 = 0;
			memset(&seq1, 0, 12);
			param3 = 0;
			param4 = 0;
			param5 = 0;
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
		Field491Value field_491;
		Field493Value field_493;
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
		byte position;
		CarIndex car2;                  // byte
		bool doProcessEntity;			// byte
		byte field_4A9;
		byte field_4AA;
		EntityDirection direction2;
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
			field_491 = EntityData::kField491_0;
			field_493 = EntityData::kField493_0;
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
			direction2 = kDirectionNone;
			
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
	void draw(const SavePoint &savepoint);
	void draw2(const SavePoint &savepoint);
	void updateFromTicks(const SavePoint &savepoint);
	void updateFromTime(const SavePoint &savepoint);

	void function1(const SavePoint &savepoint);
	void function1Clothes(const SavePoint &savepoint);
	void savepointDirection(const SavePoint &savepoint);
	void savepointCheckFields11(const SavePoint &savepoint);
	void savepointCheckEntity(const SavePoint &savepoint);
	void savepointCall(const SavePoint &savepoint);
	void enterExitCompartment(const SavePoint &savepoint);
	void updatePosition(const SavePoint &savepoint);
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_H
