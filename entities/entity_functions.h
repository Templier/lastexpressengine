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
// Helpers
//////////////////////////////////////////////////////////////////////////
#define CALL_CHAPTER_ACTION_NONE(id) \
	CALL_CHAPTER_ACTION(id, kTimeChapter1)

#define CALL_CHAPTER_ACTION(id, timeValue) \
	if (getState()->time > timeValue) { \
		if (!params->param1) { \
			params->param1 = 1; \
			setup_function##id(); \
		} \
	}

#define CALL_PREVIOUS_SAVEPOINT() { \
	getData()->current_call--; \
	getSavePoints()->setCallback(_entityIndex, _callbacks[_data->getCurrentCallback()]); \
	getSavePoints()->call(_entityIndex, _entityIndex, kAction18); \
	}

#define UPDATE_PARAM_FROM_TIME(param1, value) \
	if (params->param##param1) { \
		if (params->param##param1 >= (int)getState()->time) \
			break; \
		params->param##param1 = EntityData::kParamTime; \
	} else { \
		params->param##param1 = (int)getState()->time + value; \
		if (params->param##param1 == 0) \
			break; \
		if (params->param##param1 >= (int)getState()->time) \
			break; \
		params->param##param1 = EntityData::kParamTime; \
	}

#define UPDATE_PARAM_FROM_TICKS(param1, value) \
	if (params->param##param1) { \
		if (params->param##param1 >= (int)getState()->timeTicks) \
			break; \
		params->param##param1 = EntityData::kParamTime; \
	} else { \
		params->param##param1 = (int)getState()->timeTicks + value; \
		if (params->param##param1 == 0) \
			break; \
		if (params->param##param1 >= (int)getState()->timeTicks) \
			break; \
		params->param##param1 = EntityData::kParamTime; \
	}

#endif // LASTEXPRESS_ENTITY_FUNCTIONS_H
