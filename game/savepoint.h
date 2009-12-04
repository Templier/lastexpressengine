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

#ifndef LASTEXPRESS_SAVEPOINT_H
#define LASTEXPRESS_SAVEPOINT_H

#include "lastexpress/entities/entity.h"

#include "common/array.h"
#include "common/list.h"
#include "common/serializer.h"

/*
	Savepoint format
	----------------

	Save point: max: 127 - FIFO list (ie. goes back and overwrites first save point when full)
		uint32 {4}      - index of function pointer inside savePointFunctions array
		uint32 {4}      - action
		uint32 {4}      - time
		uint32 {4}      - 0 or 1 ?

	?? array: 16 bytes
		uint32 {4}		- ??
		uint32 {4}		- ??
		uint32 {4}		- ??
		uint32 {4}		- function pointer to ??

*/

namespace LastExpress {

class LastExpressEngine;

struct SavePoint {
	Entity::EntityIndex entity1;
	Entity::ActionIndex action;
	Entity::EntityIndex entity2;
	union {
		uint32 intValue;
		char charValue[4];
	} param;

	SavePoint() {
		entity1 = Entity::kEntityNone;
		action = Entity::kActionNone;
		entity2 = Entity::kEntityNone;
		param.intValue = 0;
	}
};	

class SavePoints : Common::Serializable {
public:

	struct SavePointData {
		Entity::EntityIndex entity1;
		Entity::ActionIndex action;
		Entity::EntityIndex entity2;
		uint32 param;

		SavePointData() {
			entity1 = Entity::kEntityNone;
			action = Entity::kActionNone;
			entity2 = Entity::kEntityNone;
			param = 0;
		}
	};

	SavePoints(LastExpressEngine *engine);
	~SavePoints();
	
	// Savepoints
	void push(Entity::EntityIndex entity2, Entity::EntityIndex entity1, Entity::ActionIndex action, uint32 param = 0);
	void pushAll(Entity::EntityIndex entity, Entity::ActionIndex action, uint32 param = 0);
	void process();
	void reset();

	// Data
	void addData(Entity::EntityIndex entity, Entity::ActionIndex action, uint32 param);

	// Callbacks
	void setCallback(Entity::EntityIndex index, Entity::Callback* callback);
	Entity::Callback *getCallback(Entity::EntityIndex entity);
	void call(Entity::EntityIndex entity2, Entity::EntityIndex entity1, Entity::ActionIndex action, uint32 param = 0);
	void call(Entity::EntityIndex entity2, Entity::EntityIndex entity1, Entity::ActionIndex action, char* param);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &s);

private:
	static const uint32 _savePointsMaxSize = 128;

	LastExpressEngine *_engine;

	Common::List<SavePoint> _savepoints;	///< could be a queue, but we need to be able to iterate on the items
	Common::Array<SavePointData> _data;
	Entity::Callback* _callbacks[40];

	SavePoint pop();
	bool updateEntity(SavePoint point);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SAVEPOINT_H
