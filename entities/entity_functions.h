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

#ifndef LASTEXPRESS_ENTITY_FUNCTIONS_H
#define LASTEXPRESS_ENTITY_FUNCTIONS_H

//////////////////////////////////////////////////////////////////////////
// Misc
//////////////////////////////////////////////////////////////////////////
#define RESET_ENTITY_STATE(entity, class, function) \
	getEntities()->resetState(entity); \
	((class*)getEntities()->get(entity))->function();

//////////////////////////////////////////////////////////////////////////
// Parameters macros (for default IIII parameters)
//////////////////////////////////////////////////////////////////////////
#define CURRENT_PARAMS(index, id) \
	((EntityData::EntityParametersIIII*)_data->getCurrentParameters(index))->param##id

#define ENTITY_PARAM(index, id) \
	((EntityData::EntityParametersIIII*)_data->getParameters(8, index))->param##id

//////////////////////////////////////////////////////////////////////////
// Time check macros
//////////////////////////////////////////////////////////////////////////
#define TIME_CHECK_CHAPTER1(function) \
	TIME_CHECK(kTimeChapter1, params->param1, function)

#define TIME_CHECK(timeValue, parameter, function) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		function(); \
	}

#define TIME_CHECK_SAVEPOINT(timeValue, parameter, entity1, entity2, action) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		getSavePoints()->push(entity1, entity2, action); \
	}

#define TIME_CHECK_CALLBACK(class, timeValue, parameter, callback, function) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		setCallback(callback); \
		call(new ENTITY_SETUP(class, function)); \
		break; \
	}

#define TIME_CHECK_CALLBACK_I(class, timeValue, parameter, callback, function, param1) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		setCallback(callback); \
		call(new ENTITY_SETUP(class, function), param1); \
		break; \
	}

#define TIME_CHECK_CALLBACK_S(class, timeValue, parameter, callback, function, seq) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		setCallback(callback); \
		call(new ENTITY_SETUP_SIIS(class, function), seq); \
		break; \
	}

#define TIME_CHECK_CALLBACK_SII(class, timeValue, parameter, callback, function, seq, param1, param2) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		setCallback(callback); \
		call(new ENTITY_SETUP_SIIS(class, function), seq, param1, param2); \
		break; \
	}

#define TIME_CHECK_CALLBACK_ACTION(class, timeValue, parameter) \
	if ((int)getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		CALLBACK_ACTION() \
		break; \
	}

#define TIME_CHECK_SAVEGAME(class, timeValue, parameter, callback, type, event) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		setCallback(callback); \
		call(new ENTITY_SETUP(class, setup_savegame), type, event); \
		break; \
	}

#define TIME_CHECK_ENTERSTATION(class, timeValue, parameter, callback, name, param2) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		setCallback(callback); \
		call(new ENTITY_SETUP_SIIS(class, setup_enterStation), name, param2); \
		break; \
	}

#define TIME_CHECK_EXITSTATION(class, timeValue, parameter, callback, name) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		setCallback(callback); \
		call(new ENTITY_SETUP_SIIS(class, setup_exitStation), name); \
		break; \
	}

#define TIME_CHECK_EXITSTATION_2(class, timeValue, parameter1, parameter2, callback, name) \
	if (getState()->time > timeValue && !parameter1) { \
		parameter1 = 1; \
		parameter2 = 1; \
		setCallback(callback); \
		call(new ENTITY_SETUP_SIIS(class, setup_exitStation), name); \
		break; \
	}

#define TIME_CHECK_EXITSTATION_0(class, parameter1, parameter2, callback, name) \
	if (parameter1 && !parameter2) { \
		setCallback(callback); \
		call(new ENTITY_SETUP_SIIS(class, setup_exitStation), name); \
		break; \
	}

#define TIME_CHECK_PLAYSOUND(class, timeValue, parameter, callback, sound) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		setCallback(callback); \
		call(new ENTITY_SETUP_SIIS(class, setup_playSound), sound); \
		break; \
	}

#define TIME_CHECK_PLAYSOUND_UPDATEPOSITION(class, timeValue, parameter, callback, sound, position) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		getData()->entityPosition = position; \
		setCallback(callback); \
		call(new ENTITY_SETUP_SIIS(class, setup_playSound), sound); \
		break; \
	}

#define TIME_CHECK_OBJECT(timeValue, parameter, object, location) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		getObjects()->updateLocation2(object, location); \
	}

#define TIME_CHECK_POSITION(timeValue, parameter, position) \
	if (getState()->time > timeValue && !parameter) { \
		parameter = 1; \
		getData()->entityPosition = position; \
	}

//////////////////////////////////////////////////////////////////////////
// Helpers
//////////////////////////////////////////////////////////////////////////
#define CALLBACK_ACTION() { \
	if (getData()->currentCall == 0) \
		error("CALLBACK_ACTION: currentCall is already 0, cannot proceed!"); \
	getData()->currentCall--; \
	getSavePoints()->setCallback(_entityIndex, _callbacks[_data->getCurrentCallback()]); \
	getSavePoints()->call(_entityIndex, _entityIndex, kActionCallback); \
	}

#define UPDATE_PARAM(parameter, type, value) { \
	if (!parameter) \
		parameter = (int)type + (int)value; \
	if (parameter >= (int)type) \
		break; \
	parameter = kTimeInvalid; \
}

#define UPDATE_PARAM_GOTO(parameter, type, value, label) { \
	if (!parameter) \
		parameter = (int)type + (int)value; \
	if (parameter >= (int)type) \
		goto label; \
	parameter = kTimeInvalid; \
}


// Go from one compartment to another (or the same one if no optional args are passed
#define COMPARTMENT_TO(class, compartmentFrom, positionFrom, sequenceFrom, sequenceTo) \
	switch (savepoint.action) { \
	default: \
		break; \
	case kActionDefault: \
		getData()->entityPosition = positionFrom; \
		setCallback(1); \
		call(new ENTITY_SETUP_SIIS(class, setup_enterExitCompartment), sequenceFrom, compartmentFrom); \
		break; \
	case kActionCallback: \
		switch (getCallback()) { \
		default: \
			break; \
		case 1: \
			setCallback(2); \
			call(new ENTITY_SETUP_SIIS(class, setup_enterExitCompartment), sequenceTo, compartmentFrom); \
			break; \
		case 2: \
			getData()->entityPosition = positionFrom; \
			getEntities()->clearSequences(_entityIndex); \
			CALLBACK_ACTION() \
		} \
		break; \
	}

#define COMPARTMENT_FROM_TO(class, compartmentFrom, positionFrom, sequenceFrom, compartmentTo, positionTo, sequenceTo) \
	switch (savepoint.action) { \
	default: \
		break; \
	case kActionDefault: \
		getData()->entityPosition = positionFrom; \
		getData()->posture = kPostureStanding; \
		setCallback(1); \
		call(new ENTITY_SETUP_SIIS(class, setup_enterExitCompartment), sequenceFrom, compartmentFrom); \
		break; \
	case kActionCallback: \
		switch (getCallback()) { \
		default: \
			break; \
		case 1: \
			setCallback(2); \
			call(new ENTITY_SETUP(class, setup_updateEntity), kCarGreenSleeping, positionTo); \
			break; \
		case 2: \
			setCallback(3); \
			call(new ENTITY_SETUP_SIIS(class, setup_enterExitCompartment), sequenceTo, compartmentTo); \
			break; \
		case 3: \
			getData()->posture = kPostureSitting; \
			getEntities()->clearSequences(_entityIndex); \
			CALLBACK_ACTION() \
			break; \
		} \
		break; \
	}


#endif // LASTEXPRESS_ENTITY_FUNCTIONS_H
