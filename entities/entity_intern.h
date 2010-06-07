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

#ifndef LASTEXPRESS_ENTITY_INTERN_H
#define LASTEXPRESS_ENTITY_INTERN_H

namespace LastExpress {

#include "common/func.h"

#include "lastexpress/entities/entity_functions.h"

//////////////////////////////////////////////////////////////////////////
// Callbacks
#define ENTITY_CALLBACK(class, name, pointer) \
	Common::Functor1Mem<const SavePoint&, void, class>(pointer, &class::name)

#define ENTITY_SETUP(class, name) \
	Functor4Mem<int, int, int, int, void, class>(this, &class::name)

#define ENTITY_SETUP_SIII(class, name) \
	Functor4Mem<const char*, int, int, int, void, class>(this, &class::name)

#define ENTITY_SETUP_SIIS(class, name) \
	Functor4Mem<const char*, int, int, const char*, void, class>(this, &class::name)

#define ENTITY_SETUP_ISSI(class, name) \
	Functor4Mem<int, const char*, const char*, int, void, class>(this, &class::name)

#define ADD_CALLBACK_FUNCTION(class, name) \
	_callbacks.push_back(new ENTITY_CALLBACK(class, name, this));

#define ADD_NULL_FUNCTION() \
	_callbacks.push_back(new ENTITY_CALLBACK(Entity, nullfunction, this));

//////////////////////////////////////////////////////////////////////////
// Declaration

// We have special macros that call the internal macros, so that we don't "lose" parameter
// information, in case we want to change the generated code later
//
// S: char*   /    I: int

#define DECLARE_NULL_FUNCTION() \
	void setup_nullfunction(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);

#define DECLARE_FUNCTION_NOSETUP(name) \
	void name(const SavePoint &savepoint);

#define DECLARE_FUNCTION(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);

#define DECLARE_FUNCTION_I(name) \
	DECLARE_FUNCTION(name)

#define DECLARE_FUNCTION_II(name) \
	DECLARE_FUNCTION(name)

#define DECLARE_FUNCTION_III(name) \
	DECLARE_FUNCTION(name)

#define DECLARE_FUNCTION_S(name) \
	DECLARE_FUNCTION_SIIS(name)

#define DECLARE_FUNCTION_SI(name) \
	DECLARE_FUNCTION_SIIS(name)

#define DECLARE_FUNCTION_SII(name) \
	DECLARE_FUNCTION_SIIS(name)

#define DECLARE_FUNCTION_SIIS(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(const char* seq1, int param2 = 0, int param3 = 0, const char* seq2 = 0);

#define DECLARE_FUNCTION_IS(name) \
	DECLARE_FUNCTION_ISS(name)

#define DECLARE_FUNCTION_ISS(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(int param1, const char* seq1, const char* seq2 = 0, int param4 = 0);

#define DECLARE_FUNCTION_IIS(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(int param1, int param2, const char* seq1, int param3);

#define DECLARE_FUNCTION_IISS(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(int param1, int param2, const char* seq1, const char* seq2 = 0);

#define DECLARE_FUNCTION_SIII(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(const char* seq1, int param2, int param3, int param4);

#define DECLARE_FUNCTION_SS(name) \
	_DECLARE_FUNCTION_SSII(name)

#define DECLARE_FUNCTION_SSI(name) \
	_DECLARE_FUNCTION_SSII(name)

// Internal macros
#define _DECLARE_FUNCTION_SSII(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(const char* seq1, const char* seq2, int param3 = 0, int param4 = 0);

//////////////////////////////////////////////////////////////////////////
// Call function
#define DECLARE_CALL_FUNCTION(id, class, type1, type2, type3, type4) \
	typedef Functor4Mem<type1, type2, type3, type4, void, class> SetupFunction_##id; \
	void call(SetupFunction_##id *func, type1 param1 = 0, type2 param2 = 0, type3 param3 = 0, type4 param4 = 0) { \
		getData()->current_call++; \
		(*func)(param1, param2, param3, param4); \
		delete func; \
	}

//////////////////////////////////////////////////////////////////////////
// Implementation

#define IMPLEMENT_SETUP(class, callback_class, name, index) \
	void class::setup_##name(int, int, int, int) { \
	BEGIN_SETUP(callback_class, name, index) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "()"); \
	END_SETUP() \
	 }

// Expose parameters and check validity
#define EXPOSE_PARAMS(type) \
	type *params = (type*)_data->getCurrentParameters(); \
	if (!params) \
		error("Trying to call an entity callback function with invalid parameters!");

// Implement call function and check for valid savepoint and parameters
#define IMPLEMENT_CALL(class, name, index) \
	void class::name(const SavePoint &savepoint) {

// nullfunction call
#define IMPLEMENT_NULL_FUNCTION(class, index) \
	IMPLEMENT_SETUP(class, Entity, nullfunction, index)

// function signature without setup (we keep the index for consistency but never use it)
#define IMPLEMENT_FUNCTION_NOSETUP(class, name, index) \
	IMPLEMENT_CALL(class, name, index) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name);

// simple setup with no parameters
#define IMPLEMENT_FUNCTION(class, name, index) \
	IMPLEMENT_SETUP(class, class, name, index) \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)

// setup with one int parameter
#define IMPLEMENT_FUNCTION_I(class, name, index) \
	void class::setup_##name(int param1, int, int, int) { \
	BEGIN_SETUP(class, name, index) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%d)", param1); \
	EntityData::EntityParametersIIII *params = (EntityData::EntityParametersIIII*)_data->getCurrentParameters(); \
	params->param1 = param1; \
	END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)

// setup with two int parameters
#define IMPLEMENT_FUNCTION_II(class, name, index) \
	void class::setup_##name(int param1, int param2, int, int) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%d, %d)", param1, param2); \
		EntityData::EntityParametersIIII *params = (EntityData::EntityParametersIIII*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		params->param2 = param2; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)

// setup with three int parameters
#define IMPLEMENT_FUNCTION_III(class, name, index) \
	void class::setup_##name(int param1, int param2, int param3, int) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%d, %d, %d)", param1, param2, param3); \
		EntityData::EntityParametersIIII *params = (EntityData::EntityParametersIIII*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		params->param2 = param2; \
		params->param3 = param3; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)

// setup with on char* parameter
#define IMPLEMENT_FUNCTION_S(class, name, index) \
	void class::setup_##name(const char* seq1, int, int, const char*) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%s)", seq1); \
		EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS)

// setup with on char* parameter and one int
#define IMPLEMENT_FUNCTION_SI(class, name, index) \
	void class::setup_##name(const char* seq1, int param2, int, const char*) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%s, %d)", seq1, param2); \
		EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		params->param2 = param2; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS)

// setup with on char* parameter and two ints
#define IMPLEMENT_FUNCTION_SII(class, name, index) \
	void class::setup_##name(const char* seq1, int param2, int param3, const char*) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%s, %d, %d)", seq1, param2, param3); \
		EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		params->param2 = param2; \
		params->param3 = param3; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS)

// setup with on char* parameter and three ints
#define IMPLEMENT_FUNCTION_SIII(class, name, index) \
	void class::setup_##name(const char* seq, int param2, int param3, int param4) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%s, %d, %d, %d)", seq, param2, param3, param4); \
		EntityData::EntityParametersSIII *params = (EntityData::EntityParametersSIII*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq, seq, 12); \
		params->param2 = param2; \
		params->param3 = param3; \
		params->param4 = param4; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSIII)

#define IMPLEMENT_FUNCTION_SIIS(class, name, index) \
	void class::setup_##name(const char* seq1, int param2, int param3, const char* seq2) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%s, %d, %d, %s)", seq1, param2, param3, seq2); \
		EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		params->param2 = param2; \
		params->param3 = param3; \
		strncpy((char *)&params->seq2, seq2, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS)

#define IMPLEMENT_FUNCTION_SS(class, name, index) \
	void class::setup_##name(const char* seq1, const char* seq2, int, int) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%s, %s)", seq1, seq2); \
		EntityData::EntityParametersSSII *params = (EntityData::EntityParametersSSII*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		strncpy((char *)&params->seq2, seq2, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSSII)

#define IMPLEMENT_FUNCTION_SSI(class, name, index) \
	void class::setup_##name(const char* seq1, const char* seq2, int param3, int) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%s, %s, %d)", seq1, seq2, param3); \
		EntityData::EntityParametersSSII *params = (EntityData::EntityParametersSSII*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		strncpy((char *)&params->seq2, seq2, 12); \
		params->param3 = param3; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSSII)

#define IMPLEMENT_FUNCTION_IS(class, name, index) \
	void class::setup_##name(int param1, const char* seq1, const char*, int) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%d, %s)", param1, seq1); \
		EntityData::EntityParametersISSI *params = (EntityData::EntityParametersISSI*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		strncpy((char *)&params->seq1, seq1, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersISSI)

#define IMPLEMENT_FUNCTION_ISS(class, name, index) \
	void class::setup_##name(int param1, const char* seq1, const char* seq2, int) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%d, %s, %s)", param1, seq1, seq2); \
		EntityData::EntityParametersISSI *params = (EntityData::EntityParametersISSI*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		strncpy((char *)&params->seq1, seq1, 12); \
		strncpy((char *)&params->seq2, seq2, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersISSI)

#define IMPLEMENT_FUNCTION_IIS(class, name, index) \
	void class::setup_##name(int param1, int param2, const char* seq1, int) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%d, %d, %s)", param1, param2, seq1); \
		EntityData::EntityParametersIISI *params = (EntityData::EntityParametersIISI*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		params->param2 = param2; \
		strncpy((char *)&params->seq1, seq1, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIISI)

#define IMPLEMENT_FUNCTION_IISS(class, name, index) \
	void class::setup_##name(int param1, int param2, const char* seq1, const char* seq2) { \
		BEGIN_SETUP(class, name, index) \
		debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "(%d, %d, %s, %s)", param1, param2, seq1, seq2); \
		EntityData::EntityParametersIISS *params = (EntityData::EntityParametersIISS*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		params->param2 = param2; \
		strncpy((char *)&params->seq1, seq1, 12); \
		strncpy((char *)&params->seq2, seq2, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIISS)

//////////////////////////////////////////////////////////////////////////
// Setup helpers
#define BEGIN_SETUP(class, name, index) \
		_engine->getGameLogic()->getGameState()->getGameSavePoints()->setCallback(_entityIndex, new ENTITY_CALLBACK(class, name, this)); \
		_data->setCurrentCallback(index); \
		_data->resetCurrentParameters();

#define END_SETUP() \
		_engine->getGameLogic()->getGameState()->getGameSavePoints()->call(_entityIndex, _entityIndex, kActionDefault);

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

} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_INTERN_H
