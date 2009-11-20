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

#include "common/array.h"
#include "common/func.h"

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

#include "common/list.h"
#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;

class SavePoints : Common::Serializable {
public:
	enum EntityIndex {
		kNone,
		kAnna,
		kAugust,
		kMertens,
		kCoudert,
		kPascale,				// 5
		kServers0,
		kServers1,
		kCooks,
		kVerges,
		kTatiana,				// 10
		kVassili,
		kAlexei,
		kAbbot,
		kMilos,
		kVesna,					// 15
		kIvo,
		kSalko,
		kKronos,
		kKahina,
		kFrancois,				// 20
		kMmeBoutarel,
		kBoutarel,
		kRebecca,
		kSophie,
		kMahmud,				// 25
		kYasmin,
		kHadija,
		kAlouan,
		kGendarmes,
		kMax,					// 30
		kChapters,
		kTrain,
		kTables0,
		kTables1,
		kTables2,				// 35
		kTables3,
		kTables4,
		kTables5,
		kEntity39
	};

	enum SavePointsAction {
		kActionNone = 0,
		kActionDefault = 12
	};

	struct SavePoint {
		EntityIndex entity;
		uint32 action;
		uint32 time;
		uint32 field_C;

		SavePoint() {
			entity = kNone;
			action = 0;
			time = 0;
			field_C = 0;
		}
	};	

	struct SavePointData {
		EntityIndex entity;
		uint32 field_4;
		uint32 field_8;
		uint32 field_C;

		SavePointData() {
			entity = kNone;
			field_4 = 0;
			field_8 = 0;
			field_C = 0;
		}
	};	

	typedef Common::Functor1<SavePoint*, void> Callback;

	SavePoints(LastExpressEngine *engine);
	~SavePoints();
	
	// Savepoints
	void push(uint32 time, EntityIndex entity, uint32 action, uint32 field_C);
	void pushAll(uint32 time, uint32 action, uint32 field_C);
	void process();
	void reset();

	// Data
	void addData(SavePoints::EntityIndex entity, uint32 field_4, uint32 field_C);

	// Callbacks
	void setCallback(uint index, Callback* callback);
	Callback *getCallback(EntityIndex entity);
	void call(int field_8, EntityIndex entity, int action, int field_C);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &s);

private:
	static const uint32 _savePointsMaxSize = 128;

	LastExpressEngine *_engine;

	Common::List<SavePoint> _savepoints;	///< could be a queue, but we need to be able to iterate on the items
	Common::Array<SavePointData> _data;
	Callback* _callbacks[40];

	SavePoint pop();
	bool updateEntity(SavePoint point);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SAVEPOINT_H
