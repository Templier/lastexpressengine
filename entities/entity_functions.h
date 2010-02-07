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
// Parameters macros (for default IIII parameters)
//////////////////////////////////////////////////////////////////////////
#define CURRENT_PARAM(id) \
	((EntityData::EntityParametersIIII*)_data->getCurrentParameters())->param##id

#define CURRENT_PARAMS(index, id) \
	((EntityData::EntityParametersIIII*)_data->getCurrentParameters(index))->param##id

#define ENTITY_PARAM(index, id) \
	((EntityData::EntityParametersIIII*)_data->getParameters(8, index))->param##id


//////////////////////////////////////////////////////////////////////////
// Function logic
//////////////////////////////////////////////////////////////////////////
#define FUNCTION1() \
	switch (savepoint->action) { \
	default: \
		break; \
	case kActionNone: \
		if (getEntities()->checkEntity(_entityIndex, EntityData::kField495_3, (EntityData::Field491Value)CURRENT_PARAM(1))) \
			CURRENT_PARAM(1) = (CURRENT_PARAM(1) == 10000) ? 0 : 10000; \
		break; \
	case kActionDefault:  \
		_data->getData()->field_491 = EntityData::kField491_0; \
		_data->getData()->field_493 = EntityData::kField493_0; \
		_data->getData()->field_495 = EntityData::kField495_3; \
		CURRENT_PARAM(1) = 10000; \
		break; \
	}

#define SAVEGAME() \
	switch (savepoint->action) { \
	default: \
		break; \
	case kActionNone: \
		CALL_PREVIOUS_SAVEPOINT() \
		break; \
	case kActionDefault: \
		save(_entityIndex, params->param1, (EventIndex)params->param2); \
		CALL_PREVIOUS_SAVEPOINT() \
		break; \
	}

#define PLAYSOUND() \
	switch (savepoint->action) { \
	default: \
		break; \
	case kAction2: \
		CALL_PREVIOUS_SAVEPOINT() \
		break; \
	case kActionDefault: \
		getSound()->playSound(_entityIndex, params->seq1); \
		break; \
	}

#define PASSING_RIGHT() \
	switch (savepoint->action) { \
	default: \
		break; \
	case kAction3: \
		CALL_PREVIOUS_SAVEPOINT() \
		break; \
	case kActionDefault: \
		getEntities()->drawSequenceRight(_entityIndex, params->seq1); \
		break; \
	}

#define CROSSING() \
	switch (savepoint->action) { \
	default: \
		break; \
	case kAction3: \
		CALL_PREVIOUS_SAVEPOINT() \
		break; \
	case kActionDefault: \
		getEntities()->drawSequenceRight(_entityIndex, params->seq1); \
		getEntities()->drawSequenceRight((EntityIndex)params->param3, params->seq2); \
		break; \
	}

#define SAVEPOINT_NOTRIGHT() \
	switch (savepoint->action) { \
	default: \
		break; \
	case kAction3: \
		CALL_PREVIOUS_SAVEPOINT() \
		break; \
	case kActionDefault: \
		if (_data->getData()->direction != kDirectionRight) \
			CALL_PREVIOUS_SAVEPOINT() \
		break; \
	}

#define SAVEPOINT_CHECKFIELDS11() \
	switch (savepoint->action) { \
	default: \
		break; \
	case kActionNone: \
	case kActionDefault: \
		if (getEntities()->checkFields11()) \
			CALL_PREVIOUS_SAVEPOINT() \
		break; \
	}

#define UPDATE_FIELDS() \
	switch (savepoint->action) { \
	default: \
		break; \
	case kAction3: \
		getEntities()->updateFields1(_entityIndex, (EntityIndex)params->param2); \
		CALL_PREVIOUS_SAVEPOINT() \
		break; \
	case kActionDefault: \
		getEntities()->drawSequenceRight(_entityIndex, params->seq1); \
		getEntities()->updateFields0(_entityIndex, (EntityIndex)params->param2); \
		break; \
	}

#define UPDATE_FIELD1000() \
	switch (savepoint->action) { \
	default: \
		break; \
	case kAction3: \
		getEntities()->updateField1000(_entityIndex, params->param2, params->param3); \
		CALL_PREVIOUS_SAVEPOINT() \
		break; \
	case kActionDefault: \
		getEntities()->drawSequenceRight(_entityIndex, params->seq1); \
		getEntities()->updateField1000(_entityIndex, params->param2, params->param3); \
		break; \
	}

#define UPDATE_FROMTICKS() \
	switch (savepoint->action) { \
	default: \
		break; \
	case kActionNone: \
		UPDATE_PARAM_FROM_TICKS(2, 1) \
		CALL_PREVIOUS_SAVEPOINT() \
		break; \
	}

//////////////////////////////////////////////////////////////////////////
// Helpers
//////////////////////////////////////////////////////////////////////////
#define CALL_CHAPTER_ACTION_NONE(id) \
	CALL_CHAPTER_ACTION(id, kTimeChapter1)

#define CALL_CHAPTER_ACTION(id, timeValue) \
	if (getState()->time > timeValue) { \
		if (!CURRENT_PARAM(1)) { \
			CURRENT_PARAM(1) = 1; \
			setup_function##id(); \
		} \
	}

#define CALL_PREVIOUS_SAVEPOINT() { \
	_data->getData()->current_call--; \
	getSavePoints()->setCallback(_entityIndex, _callbacks[_data->getCurrentCallback()]); \
	getSavePoints()->call(_entityIndex, _entityIndex, kAction18); \
	}

#define UPDATE_PARAM_FROM_TIME(param1, param2) \
	if (CURRENT_PARAM(param1)) { \
		if (CURRENT_PARAM(param1) > (int)getState()->time) \
			break; \
		CURRENT_PARAM(param1) = EntityData::kParamTime; \
	} else { \
		CURRENT_PARAM(param1) = CURRENT_PARAM(param2) + getState()->time; \
	} \

#define UPDATE_PARAM_FROM_TICKS(param1, param2) \
	if (CURRENT_PARAM(param1)) { \
		if (CURRENT_PARAM(param1) > (int)getState()->timeTicks) \
			break; \
		CURRENT_PARAM(param1) = EntityData::kParamTime; \
	} else { \
		CURRENT_PARAM(param1) = CURRENT_PARAM(param2) + getState()->timeTicks; \
	} \

#endif // LASTEXPRESS_ENTITY_FUNCTIONS_H
