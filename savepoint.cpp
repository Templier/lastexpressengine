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

#include "lastexpress/savepoint.h"

namespace LastExpress {

SavePoints::SavePoints() {
	for (int i = 0; i < 40; i++)
		_callbacks[i] = NULL;
}

SavePoints::~SavePoints() {
}

//////////////////////////////////////////////////////////////////////////
// Savepoints
//////////////////////////////////////////////////////////////////////////
void SavePoints::push(uint32 time, uint32 index, uint32 action, uint32 field_C) {

	if (_savepoints.size() >= _savePointsMaxSize)
		return;

	SavePoint point;
	point.index = index;
	point.action = action;
	point.time = time;
	point.field_C = field_C;

	_savepoints.push_back(point);
}

SavePoints::SavePoint SavePoints::pop() {
	SavePoint point = _savepoints.front();
	_savepoints.pop_front();
	return point;
}


void SavePoints::pushAll(uint32 time,uint32 action, uint32 field_C) {
	for (uint32 index = 1; index < 40; index++) {
		if (index != time)
			push(time, index, action, field_C);
	}
}

// Process all savepoints
void SavePoints::process() {
	// TODO add check for another global var
	while (_savepoints.size() > 0) {
		SavePoint point = pop();
		
		if (updateGameState(point)) {

			// Call requested callback
			Callback *callback = getCallback(point.index);
			if (callback)
				(*callback)(point);
		}
	}
}

void SavePoints::reset() {
	_savepoints.empty();
}

//////////////////////////////////////////////////////////////////////////
// Data
//////////////////////////////////////////////////////////////////////////
void SavePoints::addData(uint32 index, uint32 field_4, uint32 field_C) {
	if (_data.size() >= _savePointsMaxSize)
		return;

	SavePointData data;
	data.index = index;
	data.field_4 = field_4;
	data.field_C = field_C;

	_data.push_back(data);
}

//////////////////////////////////////////////////////////////////////////
// Callbacks
//////////////////////////////////////////////////////////////////////////
void SavePoints::setCallback(uint index, SavePoints::Callback* callback) {
	assert(index < 40);

	_callbacks[index] = callback;
}

SavePoints::Callback *SavePoints::getCallback(uint index) {
	assert(index < 40);

	return _callbacks[index];
}

void SavePoints::call(int field_8, int index, int action, int field_C) {
	SavePoint point;
	point.index = index;
	point.action = action;
	point.time = field_8;
	point.field_C = field_C;

	Callback *callback = getCallback(index);
	if (callback)
		(*callback)(point);
}

//////////////////////////////////////////////////////////////////////////
// Misc
//////////////////////////////////////////////////////////////////////////
bool SavePoints::updateGameState(SavePoints::SavePoint point) {
	for (uint i = 0; i < _data.size(); i++) {
		if (_data[i].index == point.index && _data[i].field_4 == point.action) {

			// TODO update game state

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

		s.syncAsUint32LE(_data[i].index);
		s.syncAsUint32LE(_data[i].field_4);
		s.syncAsUint32LE(_data[i].field_8);
		s.syncAsUint32LE(_data[i].field_C);
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
			s.syncAsUint32LE(point.index);
			s.syncAsUint32LE(point.action);
			s.syncAsUint32LE(point.time);
			s.syncAsUint32LE(point.field_C);

			_savepoints.push_back(point);

			if (_savepoints.size() >= _savePointsMaxSize)
				break;
		}
	} else {
		for (Common::List<SavePoint>::iterator it = _savepoints.begin(); it != _savepoints.end(); ++it) {
			s.syncAsUint32LE((*it).index);
			s.syncAsUint32LE((*it).action);
			s.syncAsUint32LE((*it).time);
			s.syncAsUint32LE((*it).field_C);
		}
	}
}

} // End of namespace LastExpress
