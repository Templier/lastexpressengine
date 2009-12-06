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

Max::Max(LastExpressEngine *engine) : Entity(engine, kEntityMax) {
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
	FUNCTION_1_IMPLEMENTATION(kEntityMax)
}

IMPLEMENT_FUNCTION_SEQ(Max, function2, 2) {
	switch (savepoint->action) {
	default:
		break;

	case kAction2: 
		CALL_PREVIOUS_SAVEPOINT(kEntityMax)
		break;

	case kActionDefault: 
		getSound()->playSound(kEntityMax, ((EntityData::EntityParametersSeq*)_data->getCurrentParameters())->seq1, -1 , 0);		
		break;
	}
}

// There doesn't seem to be a setup part for function 3 (no idea why), so we skip that part too
void Max::function3(SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case kAction3: 
		CALL_PREVIOUS_SAVEPOINT(kEntityMax)
		break;

	case kActionDefault: 
		getEntities()->storeSequenceName(kEntityMax, ((EntityData::EntityParametersSeq*)_data->getCurrentParameters())->seq1);
		break;
	}
}

IMPLEMENT_FUNCTION_SEQ_INT(Max, function4, 4) {
	EntityData::EntityParametersSeq *params = (EntityData::EntityParametersSeq*)_data->getCurrentParameters();

	switch (savepoint->action) {
	default:
		break;

	case kAction3: 
		getEntities()->updateFields1(kEntityMax, (Entity::EntityIndex)params->param2);

		CALL_PREVIOUS_SAVEPOINT(kEntityMax)
		break;

	case kActionDefault: 
		getEntities()->storeSequenceName(kEntityMax, params->seq1);
		getEntities()->updateFields0(kEntityMax, (Entity::EntityIndex)params->param2);
		break;
	}
}

IMPLEMENT_FUNCTION_INT2(Max, savegame, 5) {
	CALL_SAVEGAME(kEntityMax)
}

IMPLEMENT_FUNCTION(Max, function6, 6) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		if (_data->getCurrentParameters()->param2) {
			if (_data->getCurrentParameters()->param2 > (int)getState()->time)
				break;
			
			_data->getCurrentParameters()->param2 = EntityData::kParamTime;
		} else {
			_data->getCurrentParameters()->param2 = _data->getCurrentParameters()->param1 + getState()->time;
		}

		getSound()->playSound(kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		_data->getCurrentParameters()->param2 = 0;
		break;

	case kActionDefault: 
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		break;

	case kAction71277948:
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Max, setup_function7));
		break;

	case kAction158007856:
		getSound()->playSound(kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function7, 7) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		if (_data->getCurrentParameters()->param2) {
			if (_data->getCurrentParameters()->param2 > (int)getState()->time)
				break;

			_data->getCurrentParameters()->param2 = EntityData::kParamTime;
		} else {
			_data->getCurrentParameters()->param2 = _data->getCurrentParameters()->param1 + getState()->time;
		}

		getSound()->playSound(kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * (4 * random(20) + 40);
		_data->getCurrentParameters()->param2 = 0;
		break;

	case kAction8: 
	case kAction9: 
		getObjects()->update(Objects::kObjectCompartmentF, kEntityMax, kLocation1, Cursor::kCursorNormal, Cursor::kCursorNormal);
		getObjects()->update(Objects::kObject53, kEntityMax, kLocation1, Cursor::kCursorNormal, Cursor::kCursorNormal);

		_data->setNextCallback((savepoint->action == kAction8) ? 1 : 2);
		call(new ENTITY_SETUP(Max, setup_function2, char*, int, int, char*), (savepoint->action == kAction8) ? "LIB012" : "LIB013");
		break;

	case kActionDefault: 
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);

		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;

		getObjects()->update(Objects::kObjectCompartmentF, kEntityMax, kLocation1, Cursor::kCursorHandKnock, Cursor::kCursorHand);
		getObjects()->update(Objects::kObject53, kEntityMax, kLocation1, Cursor::kCursorHandKnock, Cursor::kCursorHand);
		break;

	case kAction17: 
		if (getEntities()->checkFields4(EntityData::kField495_4, 56) || getEntities()->checkFields4(EntityData::kField495_4, 78))
			getSound()->playSound(kEntityMax, "Max1120");
		break;

	case kAction18: 
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
			getObjects()->update(Objects::kObjectCompartmentF, kEntityMax, kLocation1, Cursor::kCursorHandKnock, Cursor::kCursorHand);
			getObjects()->update(Objects::kObject53, kEntityMax, kLocation1, Cursor::kCursorHandKnock, Cursor::kCursorHand);
			break;
		}
		break;

	case kAction101687594: 
		getEntities()->drawSequences(kEntityMax);

		CALL_PREVIOUS_SAVEPOINT(kEntityMax)
		break;

	case kAction122358304: 
	case kActionMaxFreeFromCage: 
		getSavePoints()->push(kEntityMax, kEntityMax, kActionMaxFreeFromCage, 0);
		getObjects()->update(Objects::kObjectCompartmentF, kEntityNone, kNoLocation, Cursor::kCursorHandKnock, Cursor::kCursorHand);
		getObjects()->update(Objects::kObject53, kEntityNone, kNoLocation, Cursor::kCursorHandKnock, Cursor::kCursorHand);

		CALL_PREVIOUS_SAVEPOINT(kEntityMax)
		break;

	case kAction158007856: 
		getSound()->playSound(kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function8, 8) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		if (!_data->getCurrentParameters(0)->param3) {
			_data->getCurrentParameters(0)->param3 = _data->getCurrentParameters(0)->param2 + getState()->time;

			if (_data->getCurrentParameters(0)->param3 == 0)
				break;

		} else if (_data->getCurrentParameters(0)->param3 < (int)getState()->time) {
			_data->getCurrentParameters(0)->param3 = EntityData::kParamTime;			
		}

		getSound()->playSound(kEntityMax, "Max3101");
		_data->getCurrentParameters()->param2 = 255 * ( 4 * random(20) + 40);
		_data->getCurrentParameters()->param3 = 0;
		break;

	case kAction9: 		
		if (_data->getCurrentParameters()->param1) {
			_data->setNextCallback(1);
			call(new ENTITY_SETUP_DEFAULT(Max, setup_savegame), 2, Action::kCathMaxLickHand);
			break;
		}

		getAction()->playAnimation(Action::kCathMaxLickHand);
		getLogic()->processScene();
		
		_data->getCurrentParameters()->param1 = 1;
		break;

	case kActionDefault: 
		_data->getCurrentParameters()->param2 = 255 * ( 4 * random(20) + 40);
		
		getObjects()->update(Objects::kCageMax, kEntityMax, kNoLocation, Cursor::kCursorNormal, Cursor::kCursorHand);
		getEntities()->drawSequences(kEntityMax);

		_data->getData()->field_491 = EntityData::kField491_8000;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_6;

		getSound()->playSound(kEntityMax, "Max3101");
		break;

	case kAction18:
		if (_data->getNextCallback() != 1)
			break;

		getSound()->playSound(kEntityNone, "LIB026");
		getAction()->playAnimation(Action::kCathMaxFree);
		getLogic()->loadSceneFromData(6, 92, 255);
		getObjects()->update(Objects::kCageMax, kEntityNone, kNoLocation, Cursor::kCursorNormal, Cursor::kCursorHand);
		setup_function9();
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function9, 9) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		if (_data->getCurrentParameters()->param2 == EntityData::kParamTime)
			break;

		if (!getEntities()->checkSequence0(kEntityMax) || !_data->getCurrentParameters()->param2) {
			
			_data->getCurrentParameters()->param2 = getState()->time;

			if (_data->getCurrentParameters()->param2)
				break;
		} else {
			_data->getCurrentParameters()->param2 = EntityData::kParamTime;
		}

		if (getProgress().chapter = 3)
			setup_function15();
			
		if (getProgress().chapter = 4)
			setup_function17();
		break;

	//////////////////////////////////////////////////////////////////////////
	// Draw Max outside of cage
	case kActionDefault: 
		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_4;

		getEntities()->drawSequence(kEntityMax, "630Af");
		getEntities()->updateFields2(kEntityMax, kEntityTables4);

		_data->getCurrentParameters()->param1 = getState()->time + 2700;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter1, 10) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters()->param1) {
				_data->getCurrentParameters()->param1 = 1;
				setup_function6();
			}
		}
		break;

	case kActionDefault: 
		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->field_4A5 = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter2, 11) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		setup_function6();
		break;

	case kActionDefault: 
		getEntities()->drawSequences(kEntityMax);
		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->field_4A5 = 0;
		_data->getData()->inventoryItem = kNoItem;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter3, 12) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		setup_function13();
		break;

	case kActionDefault: 
		getEntities()->drawSequences(kEntityMax);
		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->field_4A5 = 0;
		_data->getData()->inventoryItem = kNoItem;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function13, 13) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		if (_data->getCurrentParameters()->param2) {
			_data->getData()->field_491 = getEntityData(kEntityCoudert)->field_491;
			break;
		}

		if (_data->getCurrentParameters()->param3) {
			if (_data->getCurrentParameters()->param3 > (int)getState()->time)
				break;

			_data->getCurrentParameters()->param3 = EntityData::kParamTime;
		} else {
			_data->getCurrentParameters()->param3 = _data->getCurrentParameters()->param1 + getState()->time;
		}

		getSound()->playSound(kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		_data->getCurrentParameters()->param3 = 0;
		break;

	case kActionDefault: 
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);

		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		break;

	case kAction71277948: 
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Max, setup_function7));
		break;

	case kAction122358304: 
		_data->getCurrentParameters()->param2 = 1;
		break;

	case kActionMaxFreeFromCage:
		setup_freeFromCage();
		break;

	case kAction158007856: 
		if (_data->getCurrentParameters()->param2)
			break;

		getSound()->playSound(kEntityMax, "Max1122");
		_data->getCurrentParameters()->param1 = 255 * ( 4 * random(20) + 40);
		break;
	}
}

IMPLEMENT_FUNCTION(Max, freeFromCage, 14) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 		
		break;

	case kAction2: 	
		getSound()->playSound(kEntityMax, "Max1122");
		break;

	//////////////////////////////////////////////////////////////////////////
	// Save game after freeing Max from his cage
	case kAction9:
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

	case kActionDefault: 
		getObjects()->update(Objects::kCageMax, kEntityMax, kNoLocation, Cursor::kCursorNormal, Cursor::kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_8000;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_6;

		getSound()->playSound(kEntityMax, "Max1122");
		break;

	//////////////////////////////////////////////////////////////////////////
	// Play animation for Max in the cage and after opening it
	case kAction18: 	
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(Action::kCathMaxCage);
			getLogic()->processScene();
			break;

		case 2:
			getSound()->playSound(kEntityNone, "LIB026");
			getAction()->playAnimation(Action::kCathMaxFree);
			getLogic()->loadSceneFromData(6, 92, 255);
			getObjects()->update(Objects::kCageMax, kEntityNone, kNoLocation, Cursor::kCursorNormal, Cursor::kCursorHand);
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

	case kActionNone: 
		if (_data->getCurrentParameters()->param2) {
			_data->getData()->field_491 = getEntityData(kEntityCoudert)->field_491;
			_data->getData()->field_495 = getEntityData(kEntityCoudert)->field_495;
		}

		if (!_data->getCurrentParameters()->param1) {
			if (!_data->getCurrentParameters()->param3) {
				_data->getCurrentParameters()->param3 = getState()->time + 900;
				
				if (!_data->getCurrentParameters()->param3) {
					getSavePoints()->push(kEntityMax, kEntityCoudert, kAction157026693);					
					break;
				}
			}
			
			_data->getData()->current_call = getState()->time;

			if (_data->getCurrentParameters()->param3 < (int)getState()->time) {
				_data->getCurrentParameters()->param3 = EntityData::kParamTime;

				getSavePoints()->push(kEntityMax, kEntityCoudert, kAction157026693);				
			}
		}
		break;

	case kActionDefault: 
		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_4;

		getSound()->playSound(kEntityMax, "Max3010");

		_data->setNextCallback(1);
		call(new ENTITY_SETUP(Max, setup_function4, char*, int, int, char*), "630Bf", kEntityTables4);
		break;

	case kAction18: 
		if (_data->getNextCallback() == 1) {
			getEntities()->drawSequence(kEntityMax, "630Af");
			getEntities()->updateFields2(kEntityMax, kEntityTables4);
			getSavePoints()->push(kEntityMax, kEntityAnna, kAction156622016);
		}
		break;

	case kAction122358304: 
		(savepoint->entity2 == kEntityAnna) ? _data->getCurrentParameters()->param1 = 1 : _data->getCurrentParameters()->param2 = 1;
		getEntities()->updateFields3(kEntityMax, kEntityTables4);
		getEntities()->drawSequence(kEntityMax, "BLANK");
		break;

	case kActionMaxFreeFromCage: 
		getEntities()->updateFields3(kEntityMax, kEntityTables4);
		setup_function8();
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter4, 16) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		setup_function8();
		break;

	case kActionDefault: 
		getEntities()->drawSequences(kEntityMax);
		_data->getData()->field_491 = EntityData::kField491_8000;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_6;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function17, 17) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		if (_data->getCurrentParameters()->param1) {
			_data->getData()->field_491 = getEntityData(kEntityCoudert)->field_491;
			_data->getData()->field_495 = getEntityData(kEntityCoudert)->field_495;
		}
		break;

	case kActionDefault: 
		_data->getData()->field_491 = EntityData::kField491_4070;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_4;

		getEntities()->drawSequence(kEntityMax, "630Af");
		getSavePoints()->push(kEntityMax, kEntityCoudert, kAction157026693);
		break;

	case kAction122358304: 
		_data->getCurrentParameters()->param1 = 1;
		getEntities()->updateFields3(kEntityMax, kEntityTables4);
		getEntities()->drawSequence(kEntityMax, "BLANK");
		break;

	case kActionMaxFreeFromCage: 
		getEntities()->updateFields3(kEntityMax, kEntityTables4);
		setup_function8();
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter5, 18) {
	if (savepoint->action == kActionDefault) {
		getEntities()->drawSequences(kEntityMax);
		_data->getData()->field_491 = EntityData::kField491_0;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_0;
		getObjects()->update(Objects::kCageMax, kEntityNone, kNoLocation, Cursor::kCursorNormal, Cursor::kCursorHand);
	}
}

} // End of namespace LastExpress
