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
#include "lastexpress/game/state.h"

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
	void setup_##name(char* seq1, int param2 = 0, int param3 = 0, char* seq2 = 0);

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
	void class::setup_##name(char* seq1, int param2, int param3, char* seq2) { \
		BEGIN_SETUP(class, name, index) \
		strncpy((char *)&((EntityData::EntityParametersSeq*)_data->getCurrentParameters())->seq1, seq1, 12); \
		END_SETUP() \
	} \
	void class::name(SavePoint *savepoint)
	
#define IMPLEMENT_FUNCTION_SEQ_INT(class, name, index) \
	void class::setup_##name(char* seq1, int param2, int param3, char* seq2) { \
		BEGIN_SETUP(class, name, index) \
		EntityData::EntityParametersSeq *params = (EntityData::EntityParametersSeq*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		params->param2 = param2; \
		END_SETUP() \
	} \
	void class::name(SavePoint *savepoint)

#define IMPLEMENT_FUNCTION_SEQ2(class, name, index) \
	void class::setup_##name(char* seq1, int param2, int param3, char* seq2) { \
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
		if (getEntities()->checkEntity(entity, 3, _data->getCurrentParameters()->param1)) \
			_data->getCurrentParameters()->param1 = (_data->getCurrentParameters()->param1 == 10000) ? 0 : 10000; \
		break; \
	case kActionDefault:  \
		_data->getData()->field_491 = 0; \
		_data->getData()->field_493 = 0; \
		_data->getData()->field_495 = 3; \
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
		save(entity, _data->getCurrentParameters()->param1, (Action::EventIndex)_data->getCurrentParameters()->param2); \
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

	enum ParameterValues {
		kParameterTime = 2147483647
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
		int16 field_491;
		int16 field_493;
		int16 field_495;
		//int16 field_497;
		Inventory::InventoryItem inventoryItem;
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
			field_491 = 0;
			field_493 = 0;
			field_495 = 0;
			//field_497 = 0;
			inventoryItem = Inventory::kNoItem;
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

	typedef Common::Functor1<SavePoint*, void> Callback;

	enum EntityIndex {
		kEntityNone,
		kEntityAnna,
		kEntityAugust,
		kEntityMertens,
		kEntityCoudert,
		kEntityPascale,				// 5
		kEntityServers0,
		kEntityServers1,
		kEntityCooks,
		kEntityVerges,
		kEntityTatiana,				// 10
		kEntityVassili,
		kEntityAlexei,
		kEntityAbbot,
		kEntityMilos,
		kEntityVesna,				// 15
		kEntityIvo,
		kEntitySalko,
		kEntityKronos,
		kEntityKahina,
		kEntityFrancois,			// 20
		kEntityMmeBoutarel,
		kEntityBoutarel,
		kEntityRebecca,
		kEntitySophie,
		kEntityMahmud,				// 25
		kEntityYasmin,
		kEntityHadija,
		kEntityAlouan,
		kEntityGendarmes,
		kEntityMax,					// 30
		kEntityChapters,
		kEntityTrain,
		kEntityTables0,
		kEntityTables1,
		kEntityTables2,				// 35
		kEntityTables3,
		kEntityTables4,
		kEntityTables5,
		kEntity39
	};

	enum ActionIndex {
		kActionNone = 0,
		kAction2 = 2,
		kAction3 = 3,
		kAction5 = 5,
		kAction6 = 6,
		kAction8 = 8,
		kAction9 = 9,
		kActionDefault = 12,
		kAction17 = 17,
		kAction18 = 18,

		/////////////////////////////
		// Abbot
		/////////////////////////////
		kAction203073664 = 203073664,

		/////////////////////////////
		// Anna
		/////////////////////////////
		kAction238936000 = 238936000,
		kAction291662081 = 291662081,

		/////////////////////////////
		// Boutarel
		/////////////////////////////
		kAction203520448 = 203520448,
		kAction237889408 = 237889408,

		/////////////////////////////
		// Chapters
		/////////////////////////////
		kAction171843264 = 171843264,

		/////////////////////////////
		// Coudert
		/////////////////////////////
		kAction154005632 = 154005632,
		kAction157026693 = 157026693,
		kAction168254872 = 168254872,
		kAction169557824 = 169557824,
		kAction171394341 = 171394341,	// Coudert / Mertens
		kAction185671840 = 185671840,
		kAction185737168 = 185737168,
		kAction188570113 = 188570113,
		kAction189026624 = 189026624,
		kAction189750912 = 189750912,
		kAction201431954 = 201431954,	// Coudert / Mertens / Verges
		kAction205033696 = 205033696,
		kAction226031488 = 226031488,	// Coudert / Verges	
		kAction292048641 = 292048641,
		kAction326348944 = 326348944,
		kAction339669520 = 339669520,	// Coudert / Verges

		/////////////////////////////
		// Mahmud
		/////////////////////////////
		kAction170483072 = 170483072,

		/////////////////////////////
		// Max
		/////////////////////////////
		kAction71277948  = 71277948,
		kAction158007856 = 158007856,
		kAction101687594 = 101687594,
		kAction122358304 = 122358304,
		kActionMaxFreeFromCage = 135204609,
		kAction156622016 = 156622016,

		/////////////////////////////
		// Mertens
		/////////////////////////////
		kAction169633856 = 169633856,
		kAction188635520 = 188635520,
		kAction190082817 = 190082817,
		kAction204379649 = 204379649,
		kAction224122407 = 224122407,
		kAction238732837 = 238732837,
		kAction269436673 = 269436673,
		kAction269624833 = 269624833,
		kAction302614416 = 302614416,
		kAction303343617 = 303343617,

		/////////////////////////////
		// Milos
		/////////////////////////////
		kAction157691176 = 157691176,
		kAction208228224 = 208228224,

		/////////////////////////////
		// Mme Boutarel
		/////////////////////////////
		kAction242526416 = 242526416,

		/////////////////////////////
		// Pascale
		/////////////////////////////
		kAction101824388 = 101824388,
		kAction136059947 = 136059947,
		kAction190605184 = 190605184,
		kAction191604416 = 191604416,
		kAction207769280 = 207769280,
		kAction223262556 = 223262556,
		kAction239072064 = 239072064,
		kAction257489762 = 257489762,
		kAction269479296 = 269479296,
		kAction352703104 = 352703104,
		kAction352768896 = 352768896,

		/////////////////////////////
		// Rebecca
		/////////////////////////////
		kAction224253538 = 224253538,

		/////////////////////////////
		// Servers 0
		/////////////////////////////
		kAction188893625 = 188893625,
		kAction204704037 = 204704037,
		kAction207330561 = 207330561,
		kAction218128129 = 218128129,
		kAction218586752 = 218586752,
		kAction218983616 = 218983616,
		kAction223712416 = 223712416,
		kAction237485916 = 237485916,
		kAction252568704 = 252568704,
		kAction270068760 = 270068760,
		kAction270410280 = 270410280,
		kAction286403504 = 286403504,
		kAction286534136 = 286534136,
		kAction292758554 = 292758554,
		kAction304061224 = 304061224,
		kAction337548856 = 337548856,

		/////////////////////////////
		// Servers 1
		/////////////////////////////
		kAction189688608 = 189688608,
		kAction219377792 = 219377792,
		kAction223002560 = 223002560,
		kAction236237423 = 236237423,
		kAction256200848 = 256200848,
		kAction258136010 = 258136010,
		kAction269485588 = 269485588,
		kAction291721418 = 291721418,
		kAction302203328 = 302203328,
		kAction302996448 = 302996448,
		kAction326144276 = 326144276,

		/////////////////////////////
		// Sophie
		/////////////////////////////
		kAction70549068  = 70549068,
		kAction123668192 = 123668192,
		kAction125242096 = 125242096,
		kAction136654208 = 136654208,
		kAction259921280 = 259921280,
		kAction292775040 = 292775040,
	
		/////////////////////////////
		// Tables
		/////////////////////////////
		kAction103798704 = 103798704,
		kAction136455232 = 136455232,

		/////////////////////////////
		// Tatiana
		/////////////////////////////
		kAction191198209 = 191198209,

		/////////////////////////////
		// Train
		/////////////////////////////
		kAction191070912 = 191070912,
		kAction191350523 = 191350523,
		kAction202613084 = 202613084,
		kAction203339360 = 203339360,
		kAction203419131 = 203419131,
		kAction203863200 = 203863200,
		kAction222746496 = 222746496,
		kAction225056224 = 225056224,
		kAction338494260 = 338494260,

		/////////////////////////////
		// Verges
		/////////////////////////////
		kAction158617345 = 158617345,	
		kAction167854368 = 167854368,
		kAction168187490 = 168187490,
		kAction168255788 = 168255788,
		kAction191337656 = 191337656,
		
		/////////////////////////////
		// Vesna
		/////////////////////////////
		kAction124190740 = 124190740,
		
		/////////////////////////////
		// Misc
		/////////////////////////////
		kAction158610240 = 158610240,
		kAction167992577 = 167992577,
		kAction168646401 = 168646401,
		kAction169300225 = 169300225,
		kAction169773228 = 169773228,
		kAction190346110 = 190346110,
		kAction191001984 = 191001984,
		kAction192637492 = 192637492,
		kAction201959744 = 201959744,
		kAction202621266 = 202621266,
		kAction202884544 = 202884544,
		kAction203078272 = 203078272,
		kAction205034665 = 205034665,
		kAction205294778 = 205294778,
		kAction270751616 = 270751616,
		kAction272177921 = 272177921,
		kAction224309120 = 224309120,
		kAction225358684 = 225358684,
		kAction225367984 = 225367984,
		
		kActionEnd
	};

	Entity(LastExpressEngine *engine, EntityIndex index);
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
