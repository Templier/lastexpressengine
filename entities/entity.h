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

/*
	Entities
	--------

	The entities structure contains a 40 Entity_t structures for each entity
	 - ????
	 - Anna
	 - August
	 - Mertens
	 - Coudert
	 - Pascale
	 - Servers 0
	 - Servers 1
	 - Cooks
	 - Verges
	 - Tatiana				// 10
	 - Vassili
	 - Alexei
	 - Abbot
	 - Milos
	 - Vesna
	 - Ivo
	 - Salko
	 - Kronos
	 - Kahina
	 - Francois				// 20
	 - Mme Boutarek=l
	 - M. Boutarel
	 - Rebecca
	 - ??? (24)
	 - Mahmud
	 - Yasmin
	 - Hadija
	 - Alouan
	 - Gendarmes
	 - Max					// 30
	 - Chapters
	 - Train
	 - Tables 0
	 - Tables 1
	 - Tables 2
	 - Tables 3
	 - Tables 4
	 - Tables 5
	 - ??? (39)

*/

#include "lastexpress/game/savepoint.h"

#include "common/serializer.h"

namespace LastExpress {

#define CALLBACK_FUNCTION(class, name) \
	_callbacks.push_back(new Common::Functor1Mem<SavePoints::SavePoint*, void, ##class>(this, &##class::##name));

#define DECLARE_FUNCTION(class, name, index) \
	void name(SavePoints::SavePoint *savepoint); \
	DECLARE_SETUP(class, name, index)

#define DECLARE_SETUP(class, name, index) \
	void setup_##name() { \
	_engine->getLogic()->getGameSavePoints()->setCallback(_entityIndex, new Common::Functor1Mem<SavePoints::SavePoint*, void, ##class>(this, &##class::##name)); \
	_data.callbacks[_data.current_call] = index; \
	memset(&_data.callback_data[_data.current_call], 0, sizeof(Entity::EntityData)); \
	_engine->getLogic()->getGameSavePoints()->call(_entityIndex, _entityIndex, SavePoints::kActionDefault, 0); \
}

class LastExpressEngine;

// Entities
class Chapters;

class Entity : Common::Serializable {
public:
	enum EntityIndex {
		kChapters = 31
	};

	enum ChapterIndex {
		kCustom = 0,
		kChapter1 = 1,
		kChapter2 = 2,
		kChapter3 = 3,
		kChapter4 = 4,
		kChapter5 = 5
	};

	typedef void (*FunctionPointer)(int param1, int param2, int param3, int param4);

	Entity(LastExpressEngine *engine, EntityIndex index) : _engine(engine), _entityIndex(index) {};
	~Entity();

	// Setup
	void setup(ChapterIndex index);

	virtual void setup_chapter1() = 0;
	virtual void setup_chapter2() = 0;
	virtual void setup_chapter3() = 0;
	virtual void setup_chapter4() = 0;
	virtual void setup_chapter5() = 0;

	// Calls
	void call(FunctionPointer function, int param1, int param2, int param3, int param4);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

protected:
	struct EntityCallbackData {
		int field_0;

		EntityCallbackData() {
			field_0 = 0;
		}
	};

	struct EntityData {
		EntityCallbackData callback_data[9];
		byte callbacks[9];
		// int ??
		// int16 ??
		// byte ??
		byte current_call;
		// byte ?? (numScenes)
		// byte ??
		// byte ?? (field 13)
		// etc.

		EntityData() {
			current_call = 0;
		}
	};

	LastExpressEngine* _engine;

	int _entityIndex;
	EntityData _data;
	Common::Array<SavePoints::Callback *> _callbacks;
};


class Entities : Common::Serializable {
public:
	

	Entities(LastExpressEngine *engine);
	~Entities();

	void setup(Entity::ChapterIndex chapter);
	void load(int callbackIndex);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

private:
	LastExpressEngine* _engine;

	// Entities
	Chapters *_chapters;	
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_H
