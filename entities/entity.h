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

#ifndef LASTEXPRESS_ENTITY_H
#define LASTEXPRESS_ENTITY_H

#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"

#include "common/serializer.h"

namespace LastExpress {

#define MAKE_CALLBACK(class, name, pointer) \
	new Common::Functor1Mem<SavePoints::SavePoint*, void, class>(pointer, &class::name)

#define CALLBACK_FUNCTION(class, name) \
	_callbacks.push_back(MAKE_CALLBACK(class, name, this));

#define CALLBACK_FUNCTION_NULL() \
	_callbacks.push_back(MAKE_CALLBACK(Entity, nullfunction, this));

#define DECLARE_FUNCTION(class, name, index) \
	void name(SavePoints::SavePoint *savepoint); \
	DECLARE_SETUP(class, name, index)

#define DECLARE_FUNCTION_NULL(index)  \
	DECLARE_SETUP(Entity, nullfunction, index)

#define DECLARE_SETUP(class, name, index) \
	void setup_##name(char* sequence = 0, int param2 = 0, int param3 = 0, int param4 = 0) { \
	_engine->getLogic()->getGameSavePoints()->setCallback(_entityIndex, MAKE_CALLBACK(class, name, this)); \
	_data.callbacks[_data.current_call] = index; \
	memset(&_data.callback_data[_data.current_call], 0, sizeof(Entity::EntityData)); \
	_engine->getLogic()->getGameSavePoints()->call(_entityIndex, _entityIndex, SavePoints::kActionDefault, 0); \
}

class LastExpressEngine;

class Entity {
public:
	struct EntityCallbackDataEntry {
		int field_0;
		int field_4;
		int field_8;
		int field_C;
		int field_10;
		int field_14;
		int field_18;
		int field_1C;

		EntityCallbackDataEntry() {
			field_0 = 0;
			field_4 = 0;
			field_8 = 0;
			field_C = 0;
			field_10 = 0;
			field_14 = 0;
			field_18 = 0;
			field_1C = 0;
		}
	};

	struct EntityCallbackData {
		EntityCallbackDataEntry entries[4];
	};

	struct EntityData {
		EntityCallbackData callback_data[9];
		byte callbacks[9];
		// int ??
		// int16 ??
		// byte ??
		byte current_call;
		int16 field_491; // ?? (numScenes)
		int16 field_493;
		int16 field_495; // ?? (field 13) (entity index?)
		byte inventoryItem;
		int16 field_4A3;
		byte field_4A5;

		EntityData() {
			current_call = 0;
			field_491 = 0;
			field_493 = 0;
			field_495 = 0;
			inventoryItem = 0;
			field_4A3 = 30;
			field_4A5 = 0;
		}
	};

	typedef void (*SetupFunction)(char* name, int param2, int param3, int param4);

	Entity(LastExpressEngine *engine, SavePoints::EntityIndex index);
	virtual ~Entity();

	// Accessors
	EntityData *getData() { return &_data; }

	// Setup
	void setup(Logic::ChapterIndex index);

	virtual void setup_chapter1(char* name = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter2(char* name = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter3(char* name = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter4(char* name = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter5(char* name = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;

	// Calls
	void call(SetupFunction function, char* name, int param2, int param3, int param4);

	// Empty function
	void nullfunction(SavePoints::SavePoint *savepoint) {}

protected:
	LastExpressEngine* _engine;

	SavePoints::EntityIndex _entityIndex;
	EntityData _data;
	Common::Array<SavePoints::Callback *> _callbacks;
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_H
