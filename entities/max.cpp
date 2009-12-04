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

#include "lastexpress/entities/max.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Max::Max(LastExpressEngine *engine) : Entity(engine, SavePoints::kEntityMax) {
	ADD_CALLBACK_FUNCTION(Max, function1);
	ADD_CALLBACK_FUNCTION(Max, function2);
	ADD_CALLBACK_FUNCTION(Max, function3);
	ADD_CALLBACK_FUNCTION(Max, function4);
	ADD_CALLBACK_FUNCTION(Max, savegame);
	ADD_CALLBACK_FUNCTION(Max, function6);
	ADD_CALLBACK_FUNCTION(Max, function7);
	ADD_CALLBACK_FUNCTION(Max, function8);
	ADD_CALLBACK_FUNCTION(Max, function9);
	ADD_CALLBACK_FUNCTION(Max, chapter1);
	ADD_CALLBACK_FUNCTION(Max, chapter2);
	ADD_CALLBACK_FUNCTION(Max, chapter3);
	ADD_CALLBACK_FUNCTION(Max, function13);
	ADD_CALLBACK_FUNCTION(Max, freeFromCage);
	ADD_CALLBACK_FUNCTION(Max, function15);
	ADD_CALLBACK_FUNCTION(Max, chapter4);
	ADD_CALLBACK_FUNCTION(Max, function17);
	ADD_CALLBACK_FUNCTION(Max, chapter5);
}

IMPLEMENT_FUNCTION(Max, function1, 1) {
	FUNCTION_1_IMPLEMENTATION(SavePoints::kEntityMax)
}

IMPLEMENT_FUNCTION_SEQ(Max, function2, 2) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kAction2: 
		CALL_PREVIOUS_SAVEPOINT(SavePoints::kEntityMax)
		break;

	case SavePoints::kActionDefault: 
		getSound()->playSound(SavePoints::kEntityMax, ((EntityData::EntityParametersSeq*)_data->getCurrentParameters())->seq1, -1 , 0);		
		break;
	}
}

// There doesn't seem to be a setup part for function 3 (no idea why), so we skip that part too
void Max::function3(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kAction3: 
		CALL_PREVIOUS_SAVEPOINT(SavePoints::kEntityMax)
		break;

	case SavePoints::kActionDefault: 
		getEntities()->storeSequenceName(SavePoints::kEntityMax, ((EntityData::EntityParametersSeq*)_data->getCurrentParameters())->seq1);
		break;
	}
}

IMPLEMENT_FUNCTION_SEQ_INT(Max, function4, 4) {
	EntityData::EntityParametersSeq *params = (EntityData::EntityParametersSeq*)_data->getCurrentParameters();

	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kAction3: 
		getEntities()->updateFields1(SavePoints::kEntityMax, (SavePoints::EntityIndex)params->param2);

		CALL_PREVIOUS_SAVEPOINT(SavePoints::kEntityMax)
		break;

	case SavePoints::kActionDefault: 
		getEntities()->storeSequenceName(SavePoints::kEntityMax, params->seq1);
		getEntities()->updateFields0(SavePoints::kEntityMax, (SavePoints::EntityIndex)params->param2);
		break;
	}
}

IMPLEMENT_FUNCTION_INT2(Max, savegame, 5) {
	CALL_SAVEGAME(SavePoints::kEntityMax)
}

IMPLEMENT_FUNCTION(Max, function6, 6) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		if (_data->getCurrentParameters()->param2) {
			if (_data->getCurrentParameters()->param2 > (int)getState()->time)
				break;
			
			_data->getCurrentParameters()->param2 = EntityData::kParameterTime;
		} else {
			_data->getCurrentParameters()->param2 = _data->getCurrentParameters()->param1 + getState()->time;
		}

		getSound()->playSound(SavePoints::kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		_data->getCurrentParameters()->param2 = 0;
		break;

	case SavePoints::kActionDefault: 
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		break;

	case SavePoints::kAction71277948:
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Max, setup_function7));
		break;

	case SavePoints::kAction158007856:
		getSound()->playSound(SavePoints::kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function7, 7) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		if (_data->getCurrentParameters()->param2) {
			if (_data->getCurrentParameters()->param2 > (int)getState()->time)
				break;

			_data->getCurrentParameters()->param2 = EntityData::kParameterTime;
		} else {
			_data->getCurrentParameters()->param2 = _data->getCurrentParameters()->param1 + getState()->time;
		}

		getSound()->playSound(SavePoints::kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		_data->getCurrentParameters()->param2 = 0;
		break;

	case SavePoints::kAction8: 
	case SavePoints::kAction9: 
		getObjects()->update(Objects::kObjectCompartmentF, SavePoints::kEntityMax, 1, Cursor::kCursorNormal, 0);
		getObjects()->update(Objects::kObject53, SavePoints::kEntityMax, 1, Cursor::kCursorNormal, 0);

		_data->setNextCallback((savepoint->action == SavePoints::kAction8) ? 1 : 2);
		call(new ENTITY_SETUP(Max, setup_function2, char*, int, int, char*), (savepoint->action == SavePoints::kAction8) ? "LIB012" : "LIB013");
		break;

	case SavePoints::kActionDefault: 
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);

		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 4;

		getObjects()->update(Objects::kObjectCompartmentF, SavePoints::kEntityMax, 1, Cursor::kCursorHandKnock, 9);
		getObjects()->update(Objects::kObject53, SavePoints::kEntityMax, 1, Cursor::kCursorHandKnock, 9);
		break;

	case SavePoints::kAction17: 
		if (getEntities()->checkFields4(4, 56) || getEntities()->checkFields4(4, 78))
			getSound()->playSound(SavePoints::kEntityMax, "Max1120");
		break;

	case SavePoints::kAction18: 
		switch (_data->getNextCallback()) {
		case 0:
		default:
			break;

		case 1:
		case 2:
			_data->setNextCallback(3);
			call(new ENTITY_SETUP(Max, setup_function2, char*, int, int, char*), "Max1122");
			break;

		case 3:
			getObjects()->update(Objects::kObjectCompartmentF, SavePoints::kEntityMax, 1, Cursor::kCursorHandKnock, 9);
			getObjects()->update(Objects::kObject53, SavePoints::kEntityMax, 1, Cursor::kCursorHandKnock, 9);
			break;
		}
		break;

	case SavePoints::kAction101687594: 
		getEntities()->drawSequences(SavePoints::kEntityMax);

		CALL_PREVIOUS_SAVEPOINT(SavePoints::kEntityMax)
		break;

	case SavePoints::kAction122358304: 
	case SavePoints::kActionMaxFreeFromCage: 
		getSavePoints()->push(SavePoints::kEntityMax, SavePoints::kEntityMax, SavePoints::kActionMaxFreeFromCage, 0);
		getObjects()->update(Objects::kObjectCompartmentF, SavePoints::kEntityNone, 0, Cursor::kCursorHandKnock, 9);
		getObjects()->update(Objects::kObject53, SavePoints::kEntityNone, 0, Cursor::kCursorHandKnock, 9);

		CALL_PREVIOUS_SAVEPOINT(SavePoints::kEntityMax)
		break;

	case SavePoints::kAction158007856: 
		getSound()->playSound(SavePoints::kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function8, 8) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		if (!_data->getCurrentParameters(0)->param3) {
			_data->getCurrentParameters(0)->param3 = _data->getCurrentParameters(0)->param2 + getState()->time;

			if (_data->getCurrentParameters(0)->param3 == 0)
				break;

		} else if (_data->getCurrentParameters(0)->param3 < (int)getState()->time) {
			_data->getCurrentParameters(0)->param3 = EntityData::kParameterTime;			
		}

		getSound()->playSound(SavePoints::kEntityMax, "Max3101");
		_data->getCurrentParameters()->param2 = 255 * ( 4 * random(20) + 40);
		_data->getCurrentParameters()->param3 = 0;
		break;

	case SavePoints::kAction9: 		
		if (_data->getCurrentParameters()->param1) {
			_data->setNextCallback(1);
			call(new ENTITY_SETUP_DEFAULT(Max, setup_savegame), 2, Action::kCathMaxLickHand);
			break;
		}

		getAction()->playAnimation(Action::kCathMaxLickHand);
		getLogic()->processScene();
		
		_data->getCurrentParameters()->param1 = 1;
		break;

	case SavePoints::kActionDefault: 
		_data->getCurrentParameters()->param2 = 255 * ( 4 * random(20) + 40);
		
		getObjects()->update(Objects::kCageMax, SavePoints::kEntityMax, 0, Cursor::kCursorNormal, 9);
		getEntities()->drawSequences(SavePoints::kEntityMax);

		_data->getData()->field_491 = 8000;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 6;

		getSound()->playSound(SavePoints::kEntityMax, "Max3101");
		break;

	case SavePoints::kAction18:
		if (_data->getNextCallback() != 1)
			break;

		getSound()->playSound(SavePoints::kEntityNone, "LIB026");
		getAction()->playAnimation(Action::kCathMaxFree);
		getLogic()->loadSceneFromData(6, 92, 255);
		getObjects()->update(Objects::kCageMax, SavePoints::kEntityNone, 0, Cursor::kCursorNormal, 9);
		setup_function9();
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function9, 9) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		if (_data->getCurrentParameters()->param2 == EntityData::kParameterTime)
			break;

		if (!getEntities()->checkSequence0(SavePoints::kEntityMax) || !_data->getCurrentParameters()->param2) {
			
			_data->getCurrentParameters()->param2 = getState()->time;

			if (_data->getCurrentParameters()->param2)
				break;
		} else {
			_data->getCurrentParameters()->param2 = EntityData::kParameterTime;
		}

		if (getProgress().chapter = 3)
			setup_function15();
			
		if (getProgress().chapter = 4)
			setup_function17();
		break;

	//////////////////////////////////////////////////////////////////////////
	// Draw Max outside of cage
	case SavePoints::kActionDefault: 
		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 0;
		_data->getData()->field_495 = 4;

		getEntities()->drawSequence(SavePoints::kEntityMax, "630Af");
		getEntities()->updateFields2(SavePoints::kEntityMax, SavePoints::kEntityTables4);

		_data->getCurrentParameters()->param1 = getState()->time + 2700;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter1, 10) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters()->param1) {
				_data->getCurrentParameters()->param1 = 1;
				setup_function6();
			}
		}
		break;

	case SavePoints::kActionDefault: 
		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 4;
		_data->getData()->field_4A5 = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter2, 11) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		setup_function6();
		break;

	case SavePoints::kActionDefault: 
		getEntities()->drawSequences(SavePoints::kEntityMax);
		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 4;
		_data->getData()->field_4A5 = 0;
		_data->getData()->inventoryItem = Inventory::kNoItem;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter3, 12) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		setup_function13();
		break;

	case SavePoints::kActionDefault: 
		getEntities()->drawSequences(SavePoints::kEntityMax);
		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 4;
		_data->getData()->field_4A5 = 0;
		_data->getData()->inventoryItem = Inventory::kNoItem;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function13, 13) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		if (_data->getCurrentParameters()->param2) {
			_data->getData()->field_491 = getEntityData(SavePoints::kEntityCoudert)->field_491;
			break;
		}

		if (_data->getCurrentParameters()->param3) {
			if (_data->getCurrentParameters()->param3 > (int)getState()->time)
				break;

			_data->getCurrentParameters()->param3 = EntityData::kParameterTime;
		} else {
			_data->getCurrentParameters()->param3 = _data->getCurrentParameters()->param1 + getState()->time;
		}

		getSound()->playSound(SavePoints::kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		_data->getCurrentParameters()->param3 = 0;
		break;

	case SavePoints::kActionDefault: 
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);

		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 4;
		break;

	case SavePoints::kAction71277948: 
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Max, setup_function7));
		break;

	case SavePoints::kAction122358304: 
		_data->getCurrentParameters()->param2 = 1;
		break;

	case SavePoints::kActionMaxFreeFromCage:
		setup_freeFromCage();
		break;

	case SavePoints::kAction158007856: 
		if (_data->getCurrentParameters()->param2)
			break;

		getSound()->playSound(SavePoints::kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		break;
	}
}

IMPLEMENT_FUNCTION(Max, freeFromCage, 14) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 		
		break;

	case SavePoints::kAction2: 	
		getSound()->playSound(SavePoints::kEntityMax, "Max1122");
		break;

	//////////////////////////////////////////////////////////////////////////
	// Save game after freeing Max from his cage
	case SavePoints::kAction9:
		if (getEvent(Action::kCathMaxCage)) {
			if (getEvent(Action::kCathMaxFree)) {
				_data->setNextCallback(2);
				call(new ENTITY_SETUP_DEFAULT(Max, setup_savegame), 2, Action::kCathMaxFree);
			}

		} else {
			_data->setNextCallback(1);
			call(new ENTITY_SETUP_DEFAULT(Max, setup_savegame), 2, Action::kCathMaxCage);
		}
		break;

	case SavePoints::kActionDefault: 
		getObjects()->update(Objects::kCageMax, SavePoints::kEntityMax, 0, Cursor::kCursorNormal, 9);

		_data->getData()->field_491 = 8000;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 6;

		getSound()->playSound(SavePoints::kEntityMax, "Max1122");
		break;

	//////////////////////////////////////////////////////////////////////////
	// Play animation for Max in the cage and after opening it
	case SavePoints::kAction18: 	
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(Action::kCathMaxCage);
			getLogic()->processScene();
			break;

		case 2:
			getSound()->playSound(SavePoints::kEntityNone, "LIB026");
			getAction()->playAnimation(Action::kCathMaxFree);
			getLogic()->loadSceneFromData(6, 92, 255);
			getObjects()->update(Objects::kCageMax, SavePoints::kEntityNone, 0, Cursor::kCursorNormal, 9);
			setup_function9();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function15, 15) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		if (_data->getCurrentParameters()->param2) {
			_data->getData()->field_491 = getEntityData(SavePoints::kEntityCoudert)->field_491;
			_data->getData()->field_495 = getEntityData(SavePoints::kEntityCoudert)->field_495;
		}

		if (!_data->getCurrentParameters()->param1) {
			if (!_data->getCurrentParameters()->param3) {
				_data->getCurrentParameters()->param3 = getState()->time + 900;
				
				if (!_data->getCurrentParameters()->param3) {
					getSavePoints()->push(SavePoints::kEntityMax, SavePoints::kEntityCoudert, SavePoints::kAction157026693);					
					break;
				}
			}
			
			_data->getData()->current_call = getState()->time;

			if (_data->getCurrentParameters()->param3 < (int)getState()->time) {
				_data->getCurrentParameters()->param3 = EntityData::kParameterTime;

				getSavePoints()->push(SavePoints::kEntityMax, SavePoints::kEntityCoudert, SavePoints::kAction157026693);				
			}
		}
		break;

	case SavePoints::kActionDefault: 
		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 0;
		_data->getData()->field_495 = 4;

		getSound()->playSound(SavePoints::kEntityMax, "Max3010");

		_data->setNextCallback(1);
		call(new ENTITY_SETUP(Max, setup_function4, char*, int, int, char*), "630Bf", SavePoints::kEntityTables4);
		break;

	case SavePoints::kAction18: 
		if (_data->getNextCallback() == 1) {
			getEntities()->drawSequence(SavePoints::kEntityMax, "630Af");
			getEntities()->updateFields2(SavePoints::kEntityMax, SavePoints::kEntityTables4);
			getSavePoints()->push(SavePoints::kEntityMax, SavePoints::kEntityAnna, SavePoints::kAction156622016);
		}
		break;

	case SavePoints::kAction122358304: 
		(savepoint->entity2 == SavePoints::kEntityAnna) ? _data->getCurrentParameters()->param1 = 1 : _data->getCurrentParameters()->param2 = 1;
		getEntities()->updateFields3(SavePoints::kEntityMax, SavePoints::kEntityTables4);
		getEntities()->drawSequence(SavePoints::kEntityMax, "BLANK");
		break;

	case SavePoints::kActionMaxFreeFromCage: 
		getEntities()->updateFields3(SavePoints::kEntityMax, SavePoints::kEntityTables4);
		setup_function8();
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter4, 16) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		setup_function8();
		break;

	case SavePoints::kActionDefault: 
		getEntities()->drawSequences(SavePoints::kEntityMax);
		_data->getData()->field_491 = 8000;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 6;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function17, 17) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		if (_data->getCurrentParameters()->param1) {
			_data->getData()->field_491 = getEntityData(SavePoints::kEntityCoudert)->field_491;
			_data->getData()->field_495 = getEntityData(SavePoints::kEntityCoudert)->field_495;
		}
		break;

	case SavePoints::kActionDefault: 
		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 0;
		_data->getData()->field_495 = 4;

		getEntities()->drawSequence(SavePoints::kEntityMax, "630Af");
		getSavePoints()->push(SavePoints::kEntityMax, SavePoints::kEntityCoudert, SavePoints::kAction157026693);
		break;

	case SavePoints::kAction122358304: 
		_data->getCurrentParameters()->param1 = 1;
		getEntities()->updateFields3(SavePoints::kEntityMax, SavePoints::kEntityTables4);
		getEntities()->drawSequence(SavePoints::kEntityMax, "BLANK");
		break;

	case SavePoints::kActionMaxFreeFromCage: 
		getEntities()->updateFields3(SavePoints::kEntityMax, SavePoints::kEntityTables4);
		setup_function8();
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter5, 18) {
	if (savepoint->action == SavePoints::kActionDefault) {
		getEntities()->drawSequences(SavePoints::kEntityMax);
		_data->getData()->field_491 = 0;
		_data->getData()->field_493 = 0;
		_data->getData()->field_495 = 0;
		getObjects()->update(Objects::kCageMax, SavePoints::kEntityNone, 0, Cursor::kCursorNormal, 9);
	}
}

} // End of namespace LastExpress
