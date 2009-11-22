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

#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "common/serializer.h"

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// Callbacks
#define MAKE_CALLBACK(class, name, pointer) \
	new Common::Functor1Mem<SavePoints::SavePoint*, void, class>(pointer, &class::name)

#define ADD_CALLBACK_FUNCTION(class, name) \
	_callbacks.push_back(MAKE_CALLBACK(class, name, this));

#define ADD_NULL_FUNCTION() \
	_callbacks.push_back(MAKE_CALLBACK(Entity, nullfunction, this));

//////////////////////////////////////////////////////////////////////////
// Declaration
#define DECLARE_NULL_FUNCTION() \
	void setup_nullfunction(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);

#define DECLARE_FUNCTION(name) \
	void name(SavePoints::SavePoint *savepoint); \
	void setup_##name(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);

#define DECLARE_FUNCTION_SEQ2(name) \
	void name(SavePoints::SavePoint *savepoint); \
	void setup_##name(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0);

//////////////////////////////////////////////////////////////////////////		   
// Implementation

// nullfunction call
#define IMPLEMENT_NULL_FUNCTION(class, index) \
	IMPLEMENT_SETUP(class, Entity, nullfunction, index)

// simple setup with no parameters
#define IMPLEMENT_FUNCTION(class, name, index) \
	IMPLEMENT_SETUP(class, class, name, index) \
	void class::name(SavePoints::SavePoint *savepoint)

#define IMPLEMENT_SETUP(class, callback_class, name, index) \
	void class::setup_##name(int param1, int param2, int param3, int param4) { \
		BEGIN_SETUP(callback_class, name, index) \
		END_SETUP() \
	 }

// setup with two int parameters
#define IMPLEMENT_FUNCTION_INT2(class, name, index) \
	void class::setup_##name(int param1, int param2, int param3, int param4) { \
		BEGIN_SETUP(class, name, index) \
		_data->getCurrentCallParameters(0)->param1 = param1; \
		_data->getCurrentCallParameters(0)->param2 = param2; \
		END_SETUP() \
	} \
	void class::name(SavePoints::SavePoint *savepoint)
	
#define IMPLEMENT_FUNCTION_SEQ2(class, name, index) \
	void class::setup_##name(char* seq1, int param2, int param3, char* seq2) { \
		BEGIN_SETUP(class, name, index) \
		strncpy(&_data->getCurrentCallParameters(0)->seq1, seq1, 12); \
		_data->getCurrentCallParameters(0)->param2 = param2; \
		_data->getCurrentCallParameters(0)->param3 = param3; \
		strncpy(&_data->getCurrentCallParameters(0)->seq2, seq2, 12); \
		END_SETUP() \
	} \
	void class::name(SavePoints::SavePoint *savepoint)
	
//////////////////////////////////////////////////////////////////////////
// Setup helpers
#define BEGIN_SETUP(class, name, index) \
		_engine->getGameState()->getGameSavePoints()->setCallback(_entityIndex, MAKE_CALLBACK(class, name, this)); \
		_data->setCurrentCallback(index); \
		_data->resetCurrentCallParameters();

#define END_SETUP() \
		_engine->getGameState()->getGameSavePoints()->call(_entityIndex, _entityIndex, SavePoints::kActionDefault, 0);

class LastExpressEngine;

class EntityData : Common::Serializable {
public:
	
	struct EntityCallParametersEntry {
		int param1;
		int param2;
		int param3;
		int param4;
		int param5;
		int param6;
		int param7;
		int param8;

		EntityCallParametersEntry() {
			param1 = 0;
			param2 = 0;
			param3 = 0;
			param4 = 0;
			param5 = 0;
			param6 = 0;
			param7 = 0;
			param8 = 0;
		}
	};

	struct EntityCallParametersEntrySeq2 : EntityCallParametersEntry {
		char seq1[12];
		int param2;
		int param3;
		char seq2[12];

		EntityCallParametersEntrySeq2() {
			memset(&seq1, 0, 12);
			param2 = 0;
			param3 = 0;
			memset(&seq2, 0, 12);			
		}
	};

	struct EntityCallParameters {
		EntityCallParametersEntry* parameters[4];

		EntityCallParameters() {
			create();
		}

		~EntityCallParameters() {
			clear();
		}

		void create() {
			for (int i = 0; i < 4; i++)
				parameters[i] = new EntityCallParametersEntry();
		}

		void clear() {
			for (int i = 0; i < 4; i++)
				delete parameters[i];
		}

		
	};

	struct EntityCallData {		
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

		EntityCallData() {
			current_call = 0;
			field_491 = 0;
			field_493 = 0;
			field_495 = 0;
			inventoryItem = 0;
			field_4A3 = 30;
			field_4A5 = 0;
		}
	};

	EntityData() {}

	EntityCallData 		  	   *getData() { return &_data; }
	EntityCallParametersEntry  *getCallParameters(int callback, int index) { return _parameters[callback].parameters[index]; }	
	EntityCallParametersEntry  *getCurrentCallParameters(int index) { return getCallParameters(_data.current_call, index); }
	void 			 	   		setCallParameters(int callback, int index, EntityCallParametersEntry* parameters);
	void 			 	   		resetCurrentCallParameters();

	int 						getCallback(int callback) { return _data.callbacks[callback]; }
	int							getCurrentCallback() { return getCallback(_data.current_call); }
	void 			 	   		setCallback(int callback, int index) { _data.callbacks[callback] = index; }
	void 			 	   		setCurrentCallback(int index) { setCallback(_data.current_call, index); }

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

private:
	
	EntityCallData 		 _data;
	EntityCallParameters _parameters[9];
};

class Entity : Common::Serializable {
public:
	typedef void (*SetupFunction)(int name, int param2, int param3, int param4);

	Entity(LastExpressEngine *engine, SavePoints::EntityIndex index);
	virtual ~Entity();

	// Accessors
	EntityData *getData() { return _data; }

	// Setup
	void setup(State::ChapterIndex index);

	virtual void setup_chapter1(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter2(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter3(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter4(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;
	virtual void setup_chapter5(int param1 = 0, int param2 = 0, int param3 = 0, int param4 = 0) = 0;

	// Calls
	void call(SetupFunction function, int param1, int param2, int param3, int param4);

	// Empty function
	void nullfunction(SavePoints::SavePoint *savepoint) {}

	// Serializable
 	void saveLoadWithSerializer(Common::Serializer &ser) { _data->saveLoadWithSerializer(ser); }

protected:
	LastExpressEngine* _engine;

	SavePoints::EntityIndex				  _entityIndex;
	EntityData 							 *_data;
	Common::Array<SavePoints::Callback *> _callbacks;
};


} // End of namespace LastExpress

#endif // LASTEXPRESS_ENTITY_H
