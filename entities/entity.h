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

#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;
class Sequence;
struct SavePoint;

class EntityData : Common::Serializable {
public:

	enum Field491Value {
		kField491_0     = 0,
		kField491_1     = 1,
		kField491_3     = 3,
		kField491_4     = 4,
		kField491_540   = 540,
		kField491_850   = 850,
		kField491_1500  = 1500,
		kField491_1540  = 1540,
		kField491_1750  = 1750,
		kField491_2087  = 2087,
		kField491_2436  = 2436,
		kField491_2587  = 2587,
		kField491_2740  = 2740,
		kField491_2830  = 2830,
		kField491_3050  = 3050,
		kField491_3650  = 3650,
		kField491_3969  = 3969,
		kField491_3970  = 3970,
		kField491_4070  = 4070,
		kField491_4689  = 4689,
		kField491_4691  = 4691,
		kField491_4840  = 4840,
		kField491_5000  = 5000,
		kField491_5419  = 5419,
		kField491_5420  = 5420,
		kField491_5790  = 5790,
		kField491_5900  = 5900,
		kField491_6000  = 6000,
		kField491_6130  = 6130,
		kField491_6470  = 6470,
		kField491_7500  = 7500,
		kField491_8000  = 8000,
		kField491_8013  = 8013,
		kField491_8200  = 8200,
		kField491_8513  = 8513,
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

	enum Field495Value {
		kField495_0 = 0,
		kField495_1 = 1,
		kField495_2 = 2,
		kField495_3 = 3,
		kField495_4 = 4,
		kField495_5 = 5,
		kField495_6 = 6,
		kField495_7 = 7,
		kField495_9 = 9
	};

	enum ClothesIndex {
		kClothesDefault = 0,
		kClothes1 = 1,
		kClothes2 = 2,
		kClothes3 = 3
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
		// uint32 ??
		// uint16 ??
		// byte ??
		byte current_call;
		Field491Value field_491;
		Field493Value field_493;
		Field495Value field_495;
		//int16 field_497;
		InventoryItem inventoryItem;
		EntityDirection direction;
		int16 field_49B;
		int16 field_49D;

		int16 field_4A1;
		int16 field_4A3;
		ClothesIndex clothes;
		byte field_4A8;
		byte field_4A9;
		byte field_4AA;
		EntityDirection field_4AB;

		char sequenceName3[9];
		char sequenceName2[9];
		char sequenceName[9];

		Sequence *sequence0;
		Sequence *sequence1;
		Sequence *sequence2;
		Sequence *sequence3;

		EntityCallData() {
			memset(&callbacks, 0, 9 * sizeof(byte));
			current_call = 0;
			field_491 = EntityData::kField491_0;
			field_493 = EntityData::kField493_0;
			field_495 = EntityData::kField495_0;
			//field_497 = 0;
			inventoryItem = kItemNone;
			direction = kDirectionNone;
			field_49B = 0;
			field_49D = 0;

			field_4A1 = 0;
			field_4A3 = 30;
			clothes = EntityData::kClothesDefault;
			field_4A8 = 0;
			field_4A9 = 0;
			field_4AA = 0;
			field_4AB = kDirectionNone;

			memset(&sequenceName3, 0, 9 * sizeof(char));
			memset(&sequenceName2, 0, 9 * sizeof(char));
			memset(&sequenceName, 0, 9 * sizeof(char));

			sequence0 = NULL;
			sequence1 = NULL;
			sequence2 = NULL;
			sequence3 = NULL;
		}
	};

	EntityData() {}

	EntityCallData 	  *getData() { return &_data; }

	EntityParameters  *getParameters(int callback, int index) { return _parameters[callback].parameters[index]; }
	EntityParameters  *getCurrentParameters(int index = 0) { return getParameters(_data.current_call, index); }
	void 			   setParameters(int callback, int index, EntityParameters* parameters);
	void 			   resetCurrentParameters();

	int 			   getCallback(int callback) { return _data.callbacks[callback]; }
	int				   getCurrentCallback() { return getCallback(_data.current_call); }
	void 			   setCallback(int callback, byte index) { _data.callbacks[callback] = index; }
	void 			   setCurrentCallback(byte index) { setCallback(_data.current_call, index); }
	int			   	   getNextCallback() { return getCallback(getCurrentCallback() + 8); }
	void			   setNextCallback(byte index) { setCallback(getCurrentCallback() + 8, index); }

	// Serializable
	void 			   saveLoadWithSerializer(Common::Serializer &ser);

private:

	EntityCallData 		 _data;
	EntityCallParameters _parameters[9];
};

class Entity : Common::Serializable {
public:

	typedef Common::Functor1<SavePoint*, void> Callback;

	Entity(LastExpressEngine *engine, EntityIndex index);
	virtual ~Entity();

	// Accessors
	EntityData *getData() { return _data; }

	// Setup
	void setup(ChapterIndex index);

	virtual void setup_chapter1(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter2(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter3(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter4(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter5(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;

	// Serializable
 	void saveLoadWithSerializer(Common::Serializer &ser) { _data->saveLoadWithSerializer(ser); }

	void nullfunction(SavePoint *savepoint) {}

protected:
	LastExpressEngine* _engine;

	EntityIndex				  _entityIndex;
	EntityData 				 *_data;
	Common::Array<Callback *> _callbacks;

	// Shared functions
	void savegame(SavePoint *savepoint);
	void playSound(SavePoint *savepoint, bool resetItem = false, int param3 = -1);
	void draw(SavePoint *savepoint);
	void draw2(SavePoint *savepoint);
	void updateFromTicks(SavePoint *savepoint);
	void updateFromTime(SavePoint *savepoint);

	void function1(SavePoint *savepoint);
	void savepointDirection(SavePoint *savepoint);
	void savepointCheckFields11(SavePoint *savepoint);
	void savepointCheckEntity(SavePoint *savepoint);
	void savepointCall(SavePoint *savepoint);
	void updateFields(SavePoint *savepoint);
	void updateField1000(SavePoint *savepoint);
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_H
