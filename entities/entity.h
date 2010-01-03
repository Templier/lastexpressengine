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
#include "common/func.h"

namespace LastExpress {

class LastExpressEngine;
class Sequence;
struct SavePoint;

//////////////////////////////////////////////////////////////////////////
// Callbacks
#define ENTITY_CALLBACK(class, name, pointer) \
	Common::Functor1Mem<SavePoint*, void, class>(pointer, &class::name)

#define ENTITY_SETUP_DEFAULT(class, name) \
	Functor4Mem<int, int, int, int, void, class>(this, &class::name)

#define ENTITY_SETUP(class, name, type1, type2, type3, type4) \
	Functor4Mem<type1, type2, type3, type4, void, class>(this, &class::name)

#define ADD_CALLBACK_FUNCTION(class, name) \
	_callbacks.push_back(new ENTITY_CALLBACK(class, name, this));

#define ADD_NULL_FUNCTION() \
	_callbacks.push_back(new ENTITY_CALLBACK(Entity, nullfunction, this));

//////////////////////////////////////////////////////////////////////////
// Declaration
#define DECLARE_NULL_FUNCTION() \
	void setup_nullfunction(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0); \

#define DECLARE_FUNCTION(name) \
	void name(SavePoint *savepoint); \
	void setup_##name(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);

#define DECLARE_FUNCTION_SEQ(name) \
	void name(SavePoint *savepoint); \
	void setup_##name(const char* seq1, int param2 = 0, int param3 = 0, const char* seq2 = 0);

//////////////////////////////////////////////////////////////////////////
// Call function
#define DECLARE_CALL_FUNCTION(id, class, type1, type2, type3, type4) \
	typedef Functor4Mem<type1, type2, type3, type4, void, class> SetupFunction_##id; \
	void call(SetupFunction_##id *func, type1 param1 = 0, type2 param2 = 0, type3 param3 = 0, type4 param4 = 0) { \
		_data->getData()->current_call++; \
		(*func)(param1, param2, param3, param4); \
		delete func; \
	}

//////////////////////////////////////////////////////////////////////////
// Implementation

// nullfunction call
#define IMPLEMENT_NULL_FUNCTION(class, index) \
	IMPLEMENT_SETUP(class, Entity, nullfunction, index)

// simple setup with no parameters
#define IMPLEMENT_FUNCTION(class, name, index) \
	IMPLEMENT_SETUP(class, class, name, index) \
	void class::name(SavePoint *savepoint)

#define IMPLEMENT_SETUP(class, callback_class, name, index) \
	void class::setup_##name(int param1, int param2, int param3, int param4) { \
		BEGIN_SETUP(callback_class, name, index) \
		END_SETUP() \
	 }

// setup with one int parameter
#define IMPLEMENT_FUNCTION_INT(class, name, index) \
	void class::setup_##name(int param1, int param2, int param3, int param4) { \
	BEGIN_SETUP(class, name, index) \
	_data->getCurrentParameters()->param1 = param1; \
	END_SETUP() \
	} \
	void class::name(SavePoint *savepoint)

// setup with two int parameters
#define IMPLEMENT_FUNCTION_INT2(class, name, index) \
	void class::setup_##name(int param1, int param2, int param3, int param4) { \
		BEGIN_SETUP(class, name, index) \
		_data->getCurrentParameters()->param1 = param1; \
		_data->getCurrentParameters()->param2 = param2; \
		END_SETUP() \
	} \
	void class::name(SavePoint *savepoint)

#define IMPLEMENT_FUNCTION_SEQ(class, name, index) \
	void class::setup_##name(const char* seq1, int param2, int param3, const char* seq2) { \
		BEGIN_SETUP(class, name, index) \
		strncpy((char *)&((EntityData::EntityParametersSeq*)_data->getCurrentParameters())->seq1, seq1, 12); \
		END_SETUP() \
	} \
	void class::name(SavePoint *savepoint)

#define IMPLEMENT_FUNCTION_SEQ_INT(class, name, index) \
	void class::setup_##name(const char* seq1, int param2, int param3, const char* seq2) { \
		BEGIN_SETUP(class, name, index) \
		EntityData::EntityParametersSeq *params = (EntityData::EntityParametersSeq*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		params->param2 = param2; \
		END_SETUP() \
	} \
	void class::name(SavePoint *savepoint)

#define IMPLEMENT_FUNCTION_SEQ2(class, name, index) \
	void class::setup_##name(const char* seq1, int param2, int param3, const char* seq2) { \
		BEGIN_SETUP(class, name, index) \
		EntityData::EntityParametersSeq *params = (EntityData::EntityParametersSeq*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		params->param2 = param2; \
		params->param3 = param3; \
		strncpy((char *)&params->seq2, seq2, 12); \
		END_SETUP() \
	} \
	void class::name(SavePoint *savepoint)

//////////////////////////////////////////////////////////////////////////
// Setup helpers
#define BEGIN_SETUP(class, name, index) \
		_engine->getGameState()->getGameSavePoints()->setCallback(_entityIndex, new ENTITY_CALLBACK(class, name, this)); \
		_data->setCurrentCallback(index); \
		_data->resetCurrentParameters();

#define END_SETUP() \
		_engine->getGameState()->getGameSavePoints()->call(_entityIndex, _entityIndex, kActionDefault);


//////////////////////////////////////////////////////////////////////////
// Function logic
#define CALL_PREVIOUS_SAVEPOINT(entity) \
	_data->getData()->current_call--; \
	getSavePoints()->setCallback(entity, _callbacks[_data->getCurrentCallback()]); \
	getSavePoints()->call(entity, entity, kAction18);

#define FUNCTION_1_IMPLEMENTATION(entity) \
	switch (savepoint->action) { \
	default: \
		break; \
	case kActionNone: \
		if (getEntities()->checkEntity(entity, EntityData::kField495_3, (EntityData::Field491Value)_data->getCurrentParameters()->param1)) \
			_data->getCurrentParameters()->param1 = (_data->getCurrentParameters()->param1 == 10000) ? 0 : 10000; \
		break; \
	case kActionDefault:  \
		_data->getData()->field_491 = EntityData::kField491_0; \
		_data->getData()->field_493 = EntityData::kField493_0; \
		_data->getData()->field_495 = EntityData::kField495_3; \
		_data->getCurrentParameters()->param1 = 10000; \
		break; \
	}

#define CALL_SAVEGAME(entity) \
	switch (savepoint->action) { \
	default: \
		break; \
	case kActionNone: \
		CALL_PREVIOUS_SAVEPOINT(entity) \
		break; \
	case kActionDefault: \
		save(entity, _data->getCurrentParameters()->param1, (EventIndex)_data->getCurrentParameters()->param2); \
		CALL_PREVIOUS_SAVEPOINT(entity) \
		break; \
	}

//////////////////////////////////////////////////////////////////////////
// Functors class for setup functions
template<class Arg1, class Arg2, class Arg3, class Arg4, class Result>
struct QuaternaryFunction {
	typedef Arg1 FirstArgumentType;
	typedef Arg2 SecondArgumentType;
	typedef Arg3 ThirdArgumentType;
	typedef Arg4 FourthArgumentType;
	typedef Result ResultType;
};

template<class Arg1, class Arg2, class Arg3, class Arg4, class Res>
struct Functor4 : public QuaternaryFunction<Arg1, Arg2, Arg3, Arg4, Res> {
	virtual ~Functor4() {}

	virtual bool isValid() const = 0;
	virtual Res operator()(Arg1, Arg2, Arg3, Arg4) const = 0;
};

template<class Arg1, class Arg2, class Arg3, class Arg4, class Res, class T>
class Functor4Mem : public Functor4<Arg1, Arg2, Arg3, Arg4, Res> {
public:
	typedef Res (T::*FuncType)(Arg1, Arg2, Arg3, Arg4);

	Functor4Mem(T *t, const FuncType &func) : _t(t), _func(func) {}

	bool isValid() const { return _func != 0 && _t != 0; }
	Res operator()(Arg1 v1, Arg2 v2, Arg3 v3, Arg4 v4) const {
		return (_t->*_func)(v1, v2, v3, v4);
	}
private:
	mutable T *_t;
	const FuncType _func;
};

class EntityData : Common::Serializable {
public:

	enum Field491Value {
		kField491_0     = 0,
		kField491_1	    = 1,
		kField491_540   = 540,
		kField491_850   = 850,
		kField491_1500  = 1500,
		kField491_1750  = 1750,
		kField491_2740  = 2740,
		kField491_2830  = 2830,
		kField491_3050  = 3050,
		kField491_3969  = 3969,
		kField491_3970  = 3970,
		kField491_4070  = 4070,
		kField491_4689  = 4689,
		kField491_4691  = 4691,
		kField491_4840  = 4840,
		kField491_5000  = 5000,
		kField491_5419  = 5419,
		kField491_5790  = 5790,
		kField491_5900  = 5900,
		kField491_6000  = 6000,
		kField491_6470  = 6470,
		kField491_7500  = 7500,
		kField491_8000  = 8000,
		kField491_8200  = 8200,
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
		kField495_6 = 6
	};

	enum ParameterValue {
		kParamTime = 2147483647
	};

	struct EntityParameters {
		int param1;
		int param2;
		int param3;
		int param4;
		int param5;
		int param6;
		int param7;
		int param8;

		EntityParameters() {
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

	struct EntityParametersSeq : EntityParameters {
		char seq1[12];
		int param2;
		int param3;
		char seq2[12];

		EntityParametersSeq() {
			memset(&seq1, 0, 12);
			param2 = 0;
			param3 = 0;
			memset(&seq2, 0, 12);
		}
	};

	struct EntityParametersSeq1 : EntityParameters {
		int param1;
		int param2;
		int param3;
		char param4[12];
		int param7;
		int param8;

		EntityParametersSeq1() {
			param1 = 0;
			param2 = 0;
			param3 = 0;
			memset(&param4, 0, 12);
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

		void create() {
			for (int i = 0; i < 4; i++)
				parameters[i] = new EntityParameters();
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
		byte field_49A;
		int16 field_49B;
		int16 field_49D;

		int16 field_4A1;
		int16 field_4A3;
		byte field_4A5;
		byte field_4A8;

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
			inventoryItem = (InventoryItem)0;
			field_49A = 0;
			field_49B = 0;
			field_49D = 0;

			field_4A1 = 0;
			field_4A3 = 30;
			field_4A5 = 0;
			field_4A8 = 0;

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
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_H
