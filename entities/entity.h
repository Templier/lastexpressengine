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

#include "lastexpress/game/inventory.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "common/serializer.h"

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// Callbacks
#define ENTITY_CALLBACK(class, name, pointer) \
	Common::Functor1Mem<SavePoints::SavePoint*, void, class>(pointer, &class::name)

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
	void setup_nullfunction(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);

#define DECLARE_FUNCTION(name) \
	void name(SavePoints::SavePoint *savepoint); \
	void setup_##name(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);

#define DECLARE_FUNCTION_SEQ2(name) \
	void name(SavePoints::SavePoint *savepoint); \
	void setup_##name(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);

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
	void class::name(SavePoints::SavePoint *savepoint)

#define IMPLEMENT_SETUP(class, callback_class, name, index) \
	void class::setup_##name(int param1, int param2, int param3, int param4) { \
		BEGIN_SETUP(callback_class, name, index) \
		END_SETUP() \
	 }

// setup with one int parameter
#define IMPLEMENT_FUNCTION_INT(class, name, index) \
	void class::setup_##name(int param1, int param2, int param3, int param4) { \
	BEGIN_SETUP(class, name, index) \
	_data->getCurrentParameters(0)->param1 = param1; \
	END_SETUP() \
	} \
	void class::name(SavePoints::SavePoint *savepoint)

// setup with two int parameters
#define IMPLEMENT_FUNCTION_INT2(class, name, index) \
	void class::setup_##name(int param1, int param2, int param3, int param4) { \
		BEGIN_SETUP(class, name, index) \
		_data->getCurrentParameters(0)->param1 = param1; \
		_data->getCurrentParameters(0)->param2 = param2; \
		END_SETUP() \
	} \
	void class::name(SavePoints::SavePoint *savepoint)
	
#define IMPLEMENT_FUNCTION_SEQ2(class, name, index) \
	void class::setup_##name(char* seq1, int param2, int param3, char* seq2) { \
		BEGIN_SETUP(class, name, index) \
		strncpy(&_data->getCurrentParameters(0)->seq1, seq1, 12); \
		_data->getCurrentParameters(0)->param2 = param2; \
		_data->getCurrentParameters(0)->param3 = param3; \
		strncpy(&_data->getCurrentParameters(0)->seq2, seq2, 12); \
		END_SETUP() \
	} \
	void class::name(SavePoints::SavePoint *savepoint)
	
//////////////////////////////////////////////////////////////////////////
// Setup helpers
#define BEGIN_SETUP(class, name, index) \
		_engine->getGameState()->getGameSavePoints()->setCallback(_entityIndex, new ENTITY_CALLBACK(class, name, this)); \
		_data->setCurrentCallback(index); \
		_data->resetCurrentParameters();

#define END_SETUP() \
		_engine->getGameState()->getGameSavePoints()->call(_entityIndex, _entityIndex, SavePoints::kActionDefault, 0);


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

class LastExpressEngine;

class EntityData : Common::Serializable {
public:
	
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

	struct EntityParametersSeq2 : EntityParameters {
		char seq1[12];
		int param2;
		int param3;
		char seq2[12];

		EntityParametersSeq2() {
			memset(&seq1, 0, 12);
			param2 = 0;
			param3 = 0;
			memset(&seq2, 0, 12);			
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
		// int ??
		// int16 ??
		// byte ??
		byte current_call;
		int16 field_491; // ?? (numScenes)
		int16 field_493;
		int16 field_495; // ?? (field 13) (entity index?)
		Inventory::InventoryItem inventoryItem;
		byte field_49A;
		byte field_49B;
		byte field_49D;
		byte field_4A1;	
		int16 field_4A3;
		byte field_4A5;
		byte field_4A8;	

		EntityCallData() {
			current_call = 0;
			field_491 = 0;
			field_493 = 0;
			field_495 = 0;
			inventoryItem = Inventory::kNoItem;
			field_49A = 0;
			field_49B = 0;
			field_49D = 0;
			field_4A1 = 0;
			field_4A3 = 30;
			field_4A5 = 0;
			field_4A8 = 0;
		}
	};

	EntityData() {}

	EntityCallData 	  *getData() { return &_data; }

	EntityParameters  *getParameters(int callback, int index) { return _parameters[callback].parameters[index]; }	
	EntityParameters  *getCurrentParameters(int index) { return getParameters(_data.current_call, index); }
	void 			   setParameters(int callback, int index, EntityParameters* parameters);
	void 			   resetCurrentParameters();

	int 			   getCallback(int callback) { return _data.callbacks[callback]; }
	int				   getCurrentCallback() { return getCallback(_data.current_call); }
	void 			   setCallback(int callback, int index) { _data.callbacks[callback] = index; }
	void 			   setCurrentCallback(int index) { setCallback(_data.current_call, index); }
	int			   	   getNextCallback() { return getCallback(getCurrentCallback() + 8); }
	void			   setNextCallback(int index) { setCallback(getCurrentCallback() + 8, index); }

	// Serializable
	void 			   saveLoadWithSerializer(Common::Serializer &ser);

private:
	
	EntityCallData 		 _data;
	EntityCallParameters _parameters[9];
};

class Entity : Common::Serializable {
public:
	Entity(LastExpressEngine *engine, SavePoints::EntityIndex index);
	virtual ~Entity();

	// Accessors
	EntityData *getData() { return _data; }

	// Setup
	void setup(State::ChapterIndex index);

	virtual void setup_chapter1(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter2(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter3(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter4(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter5(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;

	// Empty function
	void nullfunction(SavePoints::SavePoint *savepoint) {}

	// Serializable
 	void saveLoadWithSerializer(Common::Serializer &ser) { _data->saveLoadWithSerializer(ser); }

protected:
	LastExpressEngine* _engine;

	SavePoints::EntityIndex				  _entityIndex;
	EntityData 							 *_data;
	Common::Array<SavePoints::Callback *> _callbacks;
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_H
