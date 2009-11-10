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
void SavePoints::push(uint32 field_8, uint32 index, uint32 field_4, uint32 field_C) {

	if (_savepoints.size() >= 128)
		return;

	SavePoint point;
	point.index = index;
	point.field_4 = field_4;
	point.field_8 = field_8;
	point.field_C = field_C;

	_savepoints.push(point);
}

void SavePoints::pushAll(uint32 field_8,uint32 field_4, uint32 field_C) {
	for (uint32 index = 1; index < 40; index++) {
		if (index != field_8)
			push(field_8, index, field_4, field_C);
	}
}

// Process all savepoints
void SavePoints::process() {
	// TODO add check for another global var
	while (_savepoints.size() > 0) {
		SavePoint point = _savepoints.pop();
		
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
	if (_data.size() >= 128)
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

void SavePoints::call(int field_8, int index, int field_4, int field_C) {
	SavePoint point;
	point.index = index;
	point.field_4 = field_4;
	point.field_8 = field_8;
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
		if (_data[i].index == point.index && _data[i].field_4 == point.field_4) {

			// TODO update game state

			return true;
		}
	}
	return false;
}


} // End of namespace LastExpress
