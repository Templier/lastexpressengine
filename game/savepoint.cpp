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

#include "lastexpress/game/savepoint.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"


namespace LastExpress {

SavePoints::SavePoints(LastExpressEngine *engine) : _engine(engine) {
	for (int i = 0; i < 40; i++)
		_callbacks[i] = NULL;
}

SavePoints::~SavePoints() {
	for (int i = 0; i < 40; i++)
		delete _callbacks[i];
}

//////////////////////////////////////////////////////////////////////////
// Savepoints
//////////////////////////////////////////////////////////////////////////
void SavePoints::push(EntityIndex entity2, EntityIndex entity1, ActionIndex action, uint32 param) {

	if (_savepoints.size() >= _savePointsMaxSize)
		return;

	SavePoint point;
	point.entity1 = entity1;
	point.action = action;
	point.entity2 = entity2;
	point.param.intValue = param;

	_savepoints.push_back(point);
}

SavePoints::SavePoint SavePoints::pop() {
	SavePoint point = _savepoints.front();
	_savepoints.pop_front();
	return point;
}


void SavePoints::pushAll(EntityIndex entity, ActionIndex action, uint32 param) {
	for (uint32 index = 1; index < 40; index++) {
		if ((EntityIndex)index != entity)
			push(entity, (EntityIndex)index, action, param);
	}
}

// Process all savepoints
void SavePoints::process() {
	// TODO add check for another global var
	while (_savepoints.size() > 0) {
		SavePoint point = pop();
		
		if (updateEntity(point)) {

			// Call requested callback
			Callback *callback = getCallback(point.entity1);
			if (callback)
				(*callback)(&point);
		}
	}
}

void SavePoints::reset() {
	_savepoints.empty();
}

//////////////////////////////////////////////////////////////////////////
// Data
//////////////////////////////////////////////////////////////////////////
void SavePoints::addData(SavePoints::EntityIndex entity, ActionIndex action, uint32 param) {
	if (_data.size() >= _savePointsMaxSize)
		return;

	SavePointData data;
	data.entity1 = entity;
	data.action = action;
	data.param = param;

	_data.push_back(data);
}

//////////////////////////////////////////////////////////////////////////
// Callbacks
//////////////////////////////////////////////////////////////////////////
void SavePoints::setCallback(EntityIndex index, SavePoints::Callback* callback) {
	assert(index < 40);

	// Clear previous callback
	delete _callbacks[index];

	_callbacks[index] = callback;
}

SavePoints::Callback *SavePoints::getCallback(EntityIndex index) {
	assert(index < 40);

	return _callbacks[index];
}

void SavePoints::call(EntityIndex entity2, EntityIndex entity1, ActionIndex action, uint32 param) {
	SavePoint point;
	point.entity1 = entity1;
	point.action = action;
	point.entity2 = entity2;
	point.param.intValue = param;

	Callback *callback = getCallback(entity1);
	if (callback)
		(*callback)(&point);
}

void SavePoints::call(EntityIndex entity2, EntityIndex entity1, ActionIndex action, char* param) {
	SavePoint point;
	point.entity1 = entity1;
	point.action = action;
	point.entity2 = entity2;
	strcpy((char *)&point.param.charValue, param);

	Callback *callback = getCallback(entity1);
	if (callback)
		(*callback)(&point);
}

//////////////////////////////////////////////////////////////////////////
// Misc
//////////////////////////////////////////////////////////////////////////
bool SavePoints::updateEntity(SavePoint point) {
	for (uint i = 0; i < _data.size(); i++) {
		if (_data[i].entity1 == point.entity1 && _data[i].action == point.action) {

			// FIXME this looks pretty bad :(
			error("SavePoints::updateEntity: not implemented!");
			//*(&getEntities()->getData(_data[i].entity)->callback_data[8].entries[0].field_0 + _data[i].param) = 1;

			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// Serializable
//////////////////////////////////////////////////////////////////////////
void SavePoints::saveLoadWithSerializer(Common::Serializer &s) {

	// Serialize savepoint data
	uint32 dataSize = (s.isLoading() ? _savePointsMaxSize : _data.size());
	for (uint i = 0; i < dataSize; i++) {
		if (s.isLoading()) {
			SavePointData data;
			_data.push_back(data);
		}

		s.syncAsUint32LE(_data[i].entity1);
		s.syncAsUint32LE(_data[i].action);
		s.syncAsUint32LE(_data[i].entity2);
		s.syncAsUint32LE(_data[i].param);
	}

	// Skip uninitialized data if any
	s.skip((_savePointsMaxSize - dataSize) * 16);
	
	// Number of savepoints
	uint32 count = _savepoints.size();
	s.syncAsUint32LE(count);

	// Savepoints
	if (s.isLoading()) {
		for (uint i= 0; i < count; i++) {
			SavePoint point;
			s.syncAsUint32LE(point.entity1);
			s.syncAsUint32LE(point.action);
			s.syncAsUint32LE(point.entity2);
			s.syncAsUint32LE(point.param.intValue);

			_savepoints.push_back(point);

			if (_savepoints.size() >= _savePointsMaxSize)
				break;
		}
	} else {
		for (Common::List<SavePoint>::iterator it = _savepoints.begin(); it != _savepoints.end(); ++it) {
			s.syncAsUint32LE((*it).entity1);
			s.syncAsUint32LE((*it).action);
			s.syncAsUint32LE((*it).entity2);
			s.syncAsUint32LE((*it).param.intValue);
		}
	}
}

} // End of namespace LastExpress
