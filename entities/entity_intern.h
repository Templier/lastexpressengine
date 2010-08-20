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

#include "lastexpress/entities/entity_functions.h"

#define LOBYTE(w)           ((unsigned char)(((unsigned long)(w)) & 0xff))

//////////////////////////////////////////////////////////////////////////
// Callbacks
#define ENTITY_CALLBACK(class, name, pointer) \
	Common::Functor1Mem<const SavePoint&, void, class>(pointer, &class::name)

#define ENTITY_SETUP(class, name) \
	Functor4Mem<uint, uint, uint, uint, void, class>(this, &class::name)

#define ENTITY_SETUP_SIII(class, name) \
	Functor4Mem<const char*, uint, uint, uint, void, class>(this, &class::name)

#define ENTITY_SETUP_SIIS(class, name) \
	Functor4Mem<const char*, uint, uint, const char*, void, class>(this, &class::name)

#define ENTITY_SETUP_SSII(class, name) \
	Functor4Mem<const char*, const char*, uint, uint, void, class>(this, &class::name)

#define ENTITY_SETUP_ISSI(class, name) \
	Functor4Mem<uint, const char*, const char*, uint, void, class>(this, &class::name)

#define ENTITY_SETUP_ISII(class, name) \
	Functor4Mem<uint, const char*, uint, uint, void, class>(this, &class::name)

#define ENTITY_SETUP_IISS(class, name) \
	Functor4Mem<uint, uint, const char*, const char*, void, class>(this, &class::name)

#define ENTITY_SETUP_IISI(class, name) \
	Functor4Mem<uint, uint, const char*, uint, void, class>(this, &class::name)

#define ENTITY_SETUP_IIIS(class, name) \
	Functor4Mem<uint, uint, uint, const char*, void, class>(this, &class::name)

#define ADD_CALLBACK_FUNCTION(class, name) \
	_callbacks.push_back(new ENTITY_CALLBACK(class, name, this));

#define ADD_NULL_FUNCTION() \
	_callbacks.push_back(new ENTITY_CALLBACK(Entity, nullfunction, this));

//////////////////////////////////////////////////////////////////////////
// Declaration

// We have special macros that call the internal macros, so that we don't "lose" parameter
// information, in case we want to change the generated code later
//
// S: char*   /    I: uint

#define DECLARE_NULL_FUNCTION() \
	void setup_nullfunction(uint param1 = 0, uint param2 = 0, uint param3 = 0, uint param4 = 0);

#define DECLARE_FUNCTION_NOSETUP(name) \
	void name(const SavePoint &savepoint);

#define DECLARE_FUNCTION(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(uint param1 = 0, uint param2 = 0, uint param3 = 0, uint param4 = 0);

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
	void setup_##name(const char* seq1, uint param2 = 0, uint param3 = 0, const char* seq2 = 0);

#define DECLARE_FUNCTION_IS(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(uint param1, const char* seq, uint param2 = 0, uint param3 = 0);

#define DECLARE_FUNCTION_ISS(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(uint param1, const char* seq1 = 0, const char* seq2 = 0, uint param4 = 0);

#define DECLARE_FUNCTION_IIS(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(uint param1, uint param2, const char* seq, uint param3);

#define DECLARE_FUNCTION_IISS(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(uint param1, uint param2, const char* seq1, const char* seq2 = 0);

#define DECLARE_FUNCTION_SIII(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(const char* seq, uint param2, uint param3, uint param4);

#define DECLARE_FUNCTION_SS(name) \
	_DECLARE_FUNCTION_SSII(name)

#define DECLARE_FUNCTION_SSI(name) \
	_DECLARE_FUNCTION_SSII(name)

// uinternal macros
#define _DECLARE_FUNCTION_SSII(name) \
	void name(const SavePoint &savepoint); \
	void setup_##name(const char* seq1, const char* seq2, uint param3 = 0, uint param4 = 0);

//////////////////////////////////////////////////////////////////////////
// Call function
#define DECLARE_CALL_FUNCTION(id, class, type1, type2, type3, type4) \
	typedef Functor4Mem<type1, type2, type3, type4, void, class> SetupFunction_##id; \
	void call(SetupFunction_##id *func, type1 param1 = 0, type2 param2 = 0, type3 param3 = 0, type4 param4 = 0) { \
		getData()->currentCall++; \
		(*func)(param1, param2, param3, param4); \
		delete func; \
	}

//////////////////////////////////////////////////////////////////////////
// Implementation

#define IMPLEMENT_SETUP(class, callback_class, name, index) \
	void class::setup_##name(uint, uint, uint, uint) { \
	BEGIN_SETUP(callback_class, name, index, EntityData::EntityParametersIIII) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::setup_" #name "()"); \
	END_SETUP() \
	 }

// Expose parameters and check validity
#define EXPOSE_PARAMS(type) \
	type *params = (type*)_data->getCurrentParameters(); \
	if (!params) \
		error("Trying to call an entity function with invalid parameters!"); \

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
	EXPOSE_PARAMS(EntityData::EntityParametersIIII) \
	//debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "() - action: %s", ACTION_NAME(savepoint.action));

// setup with one uint parameter
#define IMPLEMENT_FUNCTION_I(class, name, index) \
	void class::setup_##name(uint param1, uint, uint, uint) { \
	BEGIN_SETUP(class, name, index, EntityData::EntityParametersIIII) \
	EntityData::EntityParametersIIII *params = (EntityData::EntityParametersIIII*)_data->getCurrentParameters(); \
	params->param1 = param1; \
	END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIIII) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%d) - action: %s", params->param1, ACTION_NAME(savepoint.action));

// setup with two uint parameters
#define IMPLEMENT_FUNCTION_II(class, name, index) \
	void class::setup_##name(uint param1, uint param2, uint, uint) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersIIII) \
		EntityData::EntityParametersIIII *params = (EntityData::EntityParametersIIII*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		params->param2 = param2; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIIII) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%d, %d) - action: %s", params->param1, params->param2, ACTION_NAME(savepoint.action));

// setup with three uint parameters
#define IMPLEMENT_FUNCTION_III(class, name, index) \
	void class::setup_##name(uint param1, uint param2, uint param3, uint) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersIIII) \
		EntityData::EntityParametersIIII *params = (EntityData::EntityParametersIIII*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		params->param2 = param2; \
		params->param3 = param3; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIIII) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%d, %d, %d) - action: %s", params->param1, params->param2, params->param3, ACTION_NAME(savepoint.action));

// setup with on char* parameter
#define IMPLEMENT_FUNCTION_S(class, name, index) \
	void class::setup_##name(const char* seq1, uint, uint, const char*) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersSIIS) \
		EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%s) - action: %s", (char *)&params->seq1, ACTION_NAME(savepoint.action));

// setup with on char* parameter and one uint
#define IMPLEMENT_FUNCTION_SI(class, name, index) \
	void class::setup_##name(const char* seq1, uint param4, uint, const char*) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersSIIS) \
		EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		params->param4 = param4; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%s, %d) - action: %s", (char *)&params->seq1, params->param4, ACTION_NAME(savepoint.action));

// setup with on char* parameter and two uints
#define IMPLEMENT_FUNCTION_SII(class, name, index) \
	void class::setup_##name(const char* seq1, uint param4, uint param5, const char*) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersSIIS) \
		EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		params->param4 = param4; \
		params->param5 = param5; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%s, %d, %d) - action: %s", (char *)&params->seq1, params->param4, params->param5, ACTION_NAME(savepoint.action));

// setup with on char* parameter and three uints
#define IMPLEMENT_FUNCTION_SIII(class, name, index) \
	void class::setup_##name(const char* seq, uint param4, uint param5, uint param6) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersSIII) \
		EntityData::EntityParametersSIII *params = (EntityData::EntityParametersSIII*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq, seq, 12); \
		params->param4 = param4; \
		params->param5 = param5; \
		params->param6 = param6; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSIII) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%s, %d, %d, %d) - action: %s", (char *)&params->seq, params->param4, params->param5, params->param6, ACTION_NAME(savepoint.action));

#define IMPLEMENT_FUNCTION_SIIS(class, name, index) \
	void class::setup_##name(const char* seq1, uint param4, uint param5, const char* seq2) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersSIIS) \
		EntityData::EntityParametersSIIS *params = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		params->param4 = param4; \
		params->param5 = param5; \
		strncpy((char *)&params->seq2, seq2, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%s, %d, %d, %s) - action: %s", (char *)&params->seq1, params->param4, params->param5, (char *)&params->seq2, ACTION_NAME(savepoint.action));

#define IMPLEMENT_FUNCTION_SS(class, name, index) \
	void class::setup_##name(const char* seq1, const char* seq2, uint, uint) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersSSII) \
		EntityData::EntityParametersSSII *params = (EntityData::EntityParametersSSII*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		strncpy((char *)&params->seq2, seq2, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSSII) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%s, %s) - action: %s", (char *)&params->seq1, (char *)&params->seq2, ACTION_NAME(savepoint.action));

#define IMPLEMENT_FUNCTION_SSI(class, name, index) \
	void class::setup_##name(const char* seq1, const char* seq2, uint param7, uint) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersSSII) \
		EntityData::EntityParametersSSII *params = (EntityData::EntityParametersSSII*)_data->getCurrentParameters(); \
		strncpy((char *)&params->seq1, seq1, 12); \
		strncpy((char *)&params->seq2, seq2, 12); \
		params->param7 = param7; \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersSSII) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%s, %s, %d) - action: %s", (char *)&params->seq1, (char *)&params->seq2, params->param7, ACTION_NAME(savepoint.action));

#define IMPLEMENT_FUNCTION_IS(class, name, index) \
	void class::setup_##name(uint param1, const char* seq, uint, uint) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersISII) \
		EntityData::EntityParametersISII *params = (EntityData::EntityParametersISII*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		strncpy((char *)&params->seq, seq, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersISII) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%d, %s) - action: %s", params->param1, (char *)&params->seq, ACTION_NAME(savepoint.action));

#define IMPLEMENT_FUNCTION_ISS(class, name, index) \
	void class::setup_##name(uint param1, const char* seq1, const char* seq2, uint) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersISSI) \
		EntityData::EntityParametersISSI *params = (EntityData::EntityParametersISSI*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		strncpy((char *)&params->seq1, seq1, 12); \
		strncpy((char *)&params->seq2, seq2, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersISSI) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%d, %s, %s) - action: %s", params->param1, (char *)&params->seq1, (char *)&params->seq2, ACTION_NAME(savepoint.action));

#define IMPLEMENT_FUNCTION_IIS(class, name, index) \
	void class::setup_##name(uint param1, uint param2, const char* seq, uint) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersIISI) \
		EntityData::EntityParametersIISI *params = (EntityData::EntityParametersIISI*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		params->param2 = param2; \
		strncpy((char *)&params->seq, seq, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIISI) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%d, %d, %s) - action: %s", params->param1, params->param2, (char *)&params->seq, ACTION_NAME(savepoint.action));

#define IMPLEMENT_FUNCTION_IISS(class, name, index) \
	void class::setup_##name(uint param1, uint param2, const char* seq1, const char* seq2) { \
		BEGIN_SETUP(class, name, index, EntityData::EntityParametersIISS) \
		EntityData::EntityParametersIISS *params = (EntityData::EntityParametersIISS*)_data->getCurrentParameters(); \
		params->param1 = param1; \
		params->param2 = param2; \
		strncpy((char *)&params->seq1, seq1, 12); \
		strncpy((char *)&params->seq2, seq2, 12); \
		END_SETUP() \
	} \
	IMPLEMENT_CALL(class, name, index) \
	EXPOSE_PARAMS(EntityData::EntityParametersIISS) \
	debugC(6, kLastExpressDebugLogic, "Entity: " #class "::" #name "(%d, %d, %s, %s) - action: %s", params->param1, params->param2, (char *)&params->seq1, (char *)&params->seq2, ACTION_NAME(savepoint.action));

//////////////////////////////////////////////////////////////////////////
// Setup helpers
#define BEGIN_SETUP(class, name, index, type) \
		_engine->getGameLogic()->getGameState()->getGameSavePoints()->setCallback(_entityIndex, new ENTITY_CALLBACK(class, name, this)); \
		_data->setCurrentCallback(index); \
		_data->resetCurrentParameters<type>();

#define END_SETUP() \
		_engine->getGameLogic()->getGameState()->getGameSavePoints()->call(_entityIndex, _entityIndex, kActionDefault);

} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_INTERN_H
