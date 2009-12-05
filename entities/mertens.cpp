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

#include "lastexpress/entities/mertens.h"

#include "lastexpress/game/entities.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Mertens::Mertens(LastExpressEngine *engine) : Entity(engine, kEntityMertens) {
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);	// 5
	ADD_CALLBACK_FUNCTION(Mertens, function6);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, savegame);
	ADD_CALLBACK_FUNCTION(Mertens, function10);	// 10
	ADD_CALLBACK_FUNCTION(Mertens, function11);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);	// 15
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, function17);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);	// 20
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);	// 25
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);	// 30
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, chapter1);	
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);	// 35
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);	// 40
	ADD_CALLBACK_FUNCTION(Mertens, function41);
	ADD_CALLBACK_FUNCTION(Mertens, function42);
	ADD_CALLBACK_FUNCTION(Mertens, chapter2);
	ADD_CALLBACK_FUNCTION(Mertens, function44);
	ADD_CALLBACK_FUNCTION(Mertens, chapter3);	// 45
	ADD_CALLBACK_FUNCTION(Mertens, function46);
	ADD_CALLBACK_FUNCTION(Mertens, chapter4);
	ADD_CALLBACK_FUNCTION(Mertens, function48);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_CALLBACK_FUNCTION(Mertens, chapter5);	// 50
	ADD_CALLBACK_FUNCTION(Mertens, function51);
	ADD_CALLBACK_FUNCTION(Mertens, function52);
	ADD_CALLBACK_FUNCTION(Mertens, nullfunc);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Mertens, function6, 6) {
	switch (savepoint->action) {
	default:
		break;	

	case kActionNone:
		if (_data->getData()->field_49A != 4) {
			CALL_PREVIOUS_SAVEPOINT(kEntityMertens)
			break;
		}
		
		if (getProgress().jacket == State::kOriginalJacket
		 && getEntities()->checkFields9(kEntityMertens, kEntityNone, 1000)
		 && !getEntities()->checkFields3(kEntityNone)
		 && !getEntities()->checkFields10(kEntityNone)) {
			 _data->setNextCallback(1);
			 call(new ENTITY_SETUP_DEFAULT(Mertens, setup_savegame), 2, Action::kMertensBloodJacket);
		}
		break;

	case kAction3:
		CALL_PREVIOUS_SAVEPOINT(kEntityMertens)
		break;

	case kAction18: 	
		if (_data->getNextCallback() == 1) {
			getAction()->playAnimation(Action::kMertensBloodJacket);
			getLogic()->gameOver(0, 1, 55, true);
		}
		break;
	}
}

IMPLEMENT_FUNCTION_INT2(Mertens, savegame, 9) {
	CALL_SAVEGAME(kEntityMertens)
}

IMPLEMENT_FUNCTION_INT2(Mertens, function10, 10) {
	error("Mertens: callback function not implemented!");
}

IMPLEMENT_FUNCTION_INT(Mertens, function11, 11) {
	switch (savepoint->action) {
	default:
		break;	

	case kActionNone:
		if (getProgress().jacket == State::kOriginalJacket
			&& getEntities()->checkFields9(kEntityMertens, kEntityNone, 1000)
			&& !getEntities()->checkFields3(kEntityNone)
			&& !getEntities()->checkFields10(kEntityNone)) {
				_data->setNextCallback(1);
				call(new ENTITY_SETUP_DEFAULT(Mertens, setup_savegame), 2, Action::kMertensBloodJacket);
				break;
		}

		if (_data->getCurrentParameters()->param2) {
			if (_data->getCurrentParameters()->param2  > (int)getState()->time)
				break;

			_data->getCurrentParameters()->param2 = EntityData::kParamTime;
		} else {
			_data->getCurrentParameters()->param2 = _data->getCurrentParameters()->param1 + getState()->time;
		}

		CALL_PREVIOUS_SAVEPOINT(kEntityMertens)
		break;

	case kAction18: 
		if (_data->getNextCallback() == 1) {
			getAction()->playAnimation(Action::kMertensBloodJacket);
			getLogic()->gameOver(0, 1, 55, true);
		}		
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function17, 17) {
	switch (savepoint->action) {
	default:
		break;	

	case kActionDefault: 
		if (_data->getParameters(8, 0)->param6 || _data->getParameters(8, 1)->hasNonNullParameter()) {

			getInventory()->setLocationAndProcess(Inventory::kItem7, kLocation1);
			
			_data->setNextCallback(1);
			call(new ENTITY_SETUP_DEFAULT(Mertens, setup_function10), 3, 540);

		} else {
			
			if (_data->getParameters(8, 0)->param8) {
				
				getEntities()->drawSequence(kEntityMertens, "601K");
				getLogic()->loadSceneFromItem(Inventory::kItem7);

				_data->getParameters(8, 2)->param1 = 1;
				CALL_PREVIOUS_SAVEPOINT(kEntityMertens)

			} else {	// Mertens sits on his chair at the back of the train
				if (getInventory()->hasItem(Inventory::kPassengerList) || _data->getParameters(8, 0)->param2)
					getEntities()->storeSequenceName(kEntityMertens, "601A");
				else {	// Got the passenger list, Mertens is looking for it before sitting
					_data->getParameters(8, 0)->param2 = 1;
					getSound()->playSound(kEntityMertens, "CON1058", -1, 75);
					getEntities()->storeSequenceName(kEntityMertens, "601D");
				}

				getLogic()->loadSceneFromItem(Inventory::kItem7);

				if (getEntities()->checkFields4(EntityData::kField495_3, 68)) {
					getSound()->playSound(kEntityNone, "CON1110");
					getLogic()->loadSceneFromData(EntityData::kField495_3, 25, 255);
				}

				_data->setNextCallback(3);
				call(new ENTITY_SETUP_DEFAULT(Mertens, setup_function6));
			}

		}
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequences(kEntityMertens);
			_data->getParameters(8, 2)->param1 = 1;
			_data->setNextCallback(2);
			call(new ENTITY_SETUP_DEFAULT(Mertens, setup_function11), 75);
			break;

		case 2:
			CALL_PREVIOUS_SAVEPOINT(kEntityMertens)
			break;

		case 3:
			if (!_data->getParameters(8, 0)->param3
			 && !getInventory()->hasItem(Inventory::kPassengerList)
			 && _data->getParameters(8, 0)->param2) {
				 getSavePoints()->push(kEntityMertens, kEntityVerges, kAction158617345);
				 _data->getParameters(8, 0)->param3 = 1;
			}

			getEntities()->drawSequence(kEntityMertens, "601B");

			_data->getParameters(8, 0)->param1 = 0;
			_data->getData()->inventoryItem = Inventory::kNoItem;

			getSavePoints()->push(kEntityMertens, kEntityMertens, kAction17);

			CALL_PREVIOUS_SAVEPOINT(kEntityMertens)
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, chapter1, 34) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters()->param1) {
				_data->getCurrentParameters()->param1 = 1;
				setup_function41();
			}
		}
		break;

	case kActionDefault: 
		getSavePoints()->addData(kEntityMertens, kAction171394341, 7);
		getSavePoints()->addData(kEntityMertens, kAction169633856, 9);
		getSavePoints()->addData(kEntityMertens, kAction238732837, 10);
		getSavePoints()->addData(kEntityMertens, kAction269624833, 12);
		getSavePoints()->addData(kEntityMertens, kAction302614416, 11);
		getSavePoints()->addData(kEntityMertens, kAction190082817, 8);
		getSavePoints()->addData(kEntityMertens, kAction269436673, 13);
		getSavePoints()->addData(kEntityMertens, kAction303343617, 14);
		getSavePoints()->addData(kEntityMertens, kAction224122407, 17);
		getSavePoints()->addData(kEntityMertens, kAction201431954, 18);
		getSavePoints()->addData(kEntityMertens, kAction188635520, 19);
		getSavePoints()->addData(kEntityMertens, kAction204379649, 4);

		_data->getParameters(8, 0)->param1 = 0;
		_data->getData()->field_491 = EntityData::kField491_9460;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_3;
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function41, 41) {
	switch (savepoint->action) {
	default:
		break;	

	case kActionDefault: 
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Mertens, setup_function10), 3, 2000);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			call(new ENTITY_SETUP_DEFAULT(Mertens, setup_function17));
			break;

		case 2:
			setup_function42();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function42, 42) {
	error("Mertens: callback function not implemented!");

}

IMPLEMENT_FUNCTION(Mertens, chapter2, 43) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Mertens, setup_function17));
		break;

	case kActionDefault: 
		getEntities()->drawSequences(kEntityMertens);

		_data->getData()->field_491 = EntityData::kField491_1500;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_3;
		_data->getData()->inventoryItem = Inventory::kNoItem;

		_data->getParameters(8, 0)->param6 = 0;
		_data->getParameters(8, 0)->param8 = 0;

		_data->getParameters(8, 1)->param1 = 0;
		_data->getParameters(8, 1)->param2 = 0;
		_data->getParameters(8, 1)->param3 = 0;
		_data->getParameters(8, 1)->param4 = 0;
		_data->getParameters(8, 1)->param5 = 0;
		_data->getParameters(8, 1)->param6 = 0;
		_data->getParameters(8, 1)->param7 = 0;
		break;

	case kAction18: 
		if (_data->getNextCallback() == 1)
			setup_function44();
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function44, 44) {
	error("Mertens: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter3, 45) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Mertens, setup_function17));
		break;

	case kActionDefault: 
		_data->getData()->field_491 = EntityData::kField491_1500;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_3;
		_data->getData()->inventoryItem = Inventory::kNoItem;

		_data->getParameters(8, 0)->param6 = 0;
		_data->getParameters(8, 0)->param8 = 0;

		_data->getParameters(8, 1)->param1 = 0;
		_data->getParameters(8, 1)->param2 = 0;
		_data->getParameters(8, 1)->param3 = 0;
		_data->getParameters(8, 1)->param4 = 0;
		_data->getParameters(8, 1)->param5 = 0;
		_data->getParameters(8, 1)->param6 = 0;
		_data->getParameters(8, 1)->param7 = 0;

		_data->getParameters(8, 2)->param3 = 0;		
		break;

	case kAction18: 
		if (_data->getNextCallback() == 1)
			setup_function46();
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function46, 46) {
	error("Mertens: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter4, 47) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_DEFAULT(Mertens, setup_function17));
		break;

	case kActionDefault: 
		getEntities()->drawSequences(kEntityMertens);

		_data->getData()->field_491 = EntityData::kField491_1500;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_3;
		_data->getData()->inventoryItem = Inventory::kNoItem;

		_data->getParameters(8, 0)->param6 = 0;
		_data->getParameters(8, 0)->param8 = 0;

		_data->getParameters(8, 1)->param1 = 0;
		_data->getParameters(8, 1)->param2 = 0;
		_data->getParameters(8, 1)->param3 = 0;
		_data->getParameters(8, 1)->param4 = 0;
		_data->getParameters(8, 1)->param5 = 0;
		_data->getParameters(8, 1)->param6 = 0;
		_data->getParameters(8, 1)->param7 = 0;

		_data->getParameters(8, 2)->param4 = 0;
		break;

	case kAction18: 
		if (_data->getNextCallback() == 1)
			setup_function48();
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function48, 48) {
	error("Mertens: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter5, 50) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone: 
		setup_function51();
		break;

	case kActionDefault: 
		getEntities()->drawSequences(kEntityMertens);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = Inventory::kNoItem;
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function51, 51) {
	if (savepoint->action == 70549068)
		setup_function52();
}

IMPLEMENT_FUNCTION(Mertens, function52, 52) {
	error("Mertens: callback function not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Mertens, 59)

void Mertens::nullfunc(SavePoint *savepoint) {
	error("Mertens: callback function not implemented!");
}

} // End of namespace LastExpress
