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

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savegame.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"
#include "lastexpress/game/sound.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Mertens::Mertens(LastExpressEngine *engine) : Entity(engine, kEntityMertens) {
	ADD_CALLBACK_FUNCTION(Mertens, function1);
	ADD_CALLBACK_FUNCTION(Mertens, function2);
	ADD_CALLBACK_FUNCTION(Mertens, function3);
	ADD_CALLBACK_FUNCTION(Mertens, function4);
	ADD_CALLBACK_FUNCTION(Mertens, function5);
	ADD_CALLBACK_FUNCTION(Mertens, function6);
	ADD_CALLBACK_FUNCTION(Mertens, function7);
	ADD_CALLBACK_FUNCTION(Mertens, function8);
	ADD_CALLBACK_FUNCTION(Mertens, savegame);
	ADD_CALLBACK_FUNCTION(Mertens, function10);
	ADD_CALLBACK_FUNCTION(Mertens, function11);
	ADD_CALLBACK_FUNCTION(Mertens, bonsoir);
	ADD_CALLBACK_FUNCTION(Mertens, function13);
	ADD_CALLBACK_FUNCTION(Mertens, function14);
	ADD_CALLBACK_FUNCTION(Mertens, function15);
	ADD_CALLBACK_FUNCTION(Mertens, function16);
	ADD_CALLBACK_FUNCTION(Mertens, function17);
	ADD_CALLBACK_FUNCTION(Mertens, function18);
	ADD_CALLBACK_FUNCTION(Mertens, function19);
	ADD_CALLBACK_FUNCTION(Mertens, function20);
	ADD_CALLBACK_FUNCTION(Mertens, function21);
	ADD_CALLBACK_FUNCTION(Mertens, function22);
	ADD_CALLBACK_FUNCTION(Mertens, function23);
	ADD_CALLBACK_FUNCTION(Mertens, function24);
	ADD_CALLBACK_FUNCTION(Mertens, function25);
	ADD_CALLBACK_FUNCTION(Mertens, function26);
	ADD_CALLBACK_FUNCTION(Mertens, function27);
	ADD_CALLBACK_FUNCTION(Mertens, function28);
	ADD_CALLBACK_FUNCTION(Mertens, function29);
	ADD_CALLBACK_FUNCTION(Mertens, function30);
	ADD_CALLBACK_FUNCTION(Mertens, function31);
	ADD_CALLBACK_FUNCTION(Mertens, function32);
	ADD_CALLBACK_FUNCTION(Mertens, function33);
	ADD_CALLBACK_FUNCTION(Mertens, chapter1);
	ADD_CALLBACK_FUNCTION(Mertens, function35);
	ADD_CALLBACK_FUNCTION(Mertens, function36);
	ADD_CALLBACK_FUNCTION(Mertens, function37);
	ADD_CALLBACK_FUNCTION(Mertens, function38);
	ADD_CALLBACK_FUNCTION(Mertens, function39);
	ADD_CALLBACK_FUNCTION(Mertens, function40);
	ADD_CALLBACK_FUNCTION(Mertens, function41);
	ADD_CALLBACK_FUNCTION(Mertens, function42);
	ADD_CALLBACK_FUNCTION(Mertens, chapter2);
	ADD_CALLBACK_FUNCTION(Mertens, function44);
	ADD_CALLBACK_FUNCTION(Mertens, chapter3);
	ADD_CALLBACK_FUNCTION(Mertens, function46);
	ADD_CALLBACK_FUNCTION(Mertens, chapter4);
	ADD_CALLBACK_FUNCTION(Mertens, function48);
	ADD_CALLBACK_FUNCTION(Mertens, function49);
	ADD_CALLBACK_FUNCTION(Mertens, chapter5);
	ADD_CALLBACK_FUNCTION(Mertens, function51);
	ADD_CALLBACK_FUNCTION(Mertens, function52);
	ADD_CALLBACK_FUNCTION(Mertens, function53);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(Mertens, function1, 1)
	error("Mertens: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_S(Mertens, function2, 2)
	error("Mertens: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Mertens, function3, 3)
	error("Mertens: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Mertens, function4, 4)
	error("Mertens: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_SIII(Mertens, function5, 5)
	error("Mertens: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function6, 6)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		if (_data->getData()->direction != 4) {
			CALL_PREVIOUS_SAVEPOINT()
			break;
		}

		if (getProgress().jacket == kJacketOriginal
		 && getEntities()->checkFields9(kEntityMertens, kEntityNone, 1000)
		 && !getEntities()->checkFields3(kEntityNone)
		 && !getEntities()->checkFields10(kEntityNone)) {
			 _data->setNextCallback(1);
			 call(new ENTITY_SETUP_DEFAULT(Mertens, setup_savegame), 2, kEventMertensBloodJacket);
		}
		break;

	case kAction3:
		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kAction18:
		if (_data->getNextCallback() == 1) {
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kTimeType0, 1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

IMPLEMENT_FUNCTION_S(Mertens, function7, 7)
	error("Mertens: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_S(Mertens, function8, 8)
	error("Mertens: callback function  8 not implemented!");
}

IMPLEMENT_FUNCTION_II(Mertens, savegame, 9)
	CALL_SAVEGAME()
}

IMPLEMENT_FUNCTION_II(Mertens, function10, 10)
	error("Mertens: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION_I(Mertens, function11, 11)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		if (getProgress().jacket == kJacketOriginal
			&& getEntities()->checkFields9(kEntityMertens, kEntityNone, 1000)
			&& !getEntities()->checkFields3(kEntityNone)
			&& !getEntities()->checkFields10(kEntityNone)) {
				_data->setNextCallback(1);
				call(new ENTITY_SETUP_DEFAULT(Mertens, setup_savegame), 2, kEventMertensBloodJacket);
				break;
		}

		UPDATE_PARAM_FROM_TIME(2, 1)

		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kAction18:
		if (_data->getNextCallback() == 1) {
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kTimeType0, 1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

IMPLEMENT_FUNCTION_I(Mertens, bonsoir, 12)
	error("Mertens: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_II(Mertens, function13, 13)
	error("Mertens: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION_I(Mertens, function14, 14)
	error("Mertens: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION_I(Mertens, function15, 15)
	error("Mertens: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION_I(Mertens, function16, 16)
	error("Mertens: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function17, 17)
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		// FIXME: Check that we are using the correct parameter struct
		if (ENTITY_PARAM(0, 6) || ((EntityData::EntityParametersIIII*)_data->getParameters(8, 1))->hasNonNullParameter()) {

			getInventory()->setLocationAndProcess(kItem7, kLocation1);

			_data->setNextCallback(1);
			call(new ENTITY_SETUP_DEFAULT(Mertens, setup_function10), 3, 540);

		} else {

			if (ENTITY_PARAM(0, 8)) {

				getEntities()->drawSequenceLeft(kEntityMertens, "601K");
				getLogic()->loadSceneFromItem(kItem7);

				ENTITY_PARAM(2, 1) = 1;
				CALL_PREVIOUS_SAVEPOINT()

			} else {	// Mertens sits on his chair at the back of the train
				if (getInventory()->hasItem(kItemPassengerList) || ENTITY_PARAM(0, 2))
					getEntities()->drawSequenceRight(kEntityMertens, "601A");
				else {	// Got the passenger list, Mertens is looking for it before sitting
					ENTITY_PARAM(0, 2) = 1;
					getSound()->playSound(kEntityMertens, "CON1058", -1, 75);
					getEntities()->drawSequenceRight(kEntityMertens, "601D");
				}

				getLogic()->loadSceneFromItem(kItem7);

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
			ENTITY_PARAM(2, 1) = 1;
			_data->setNextCallback(2);
			call(new ENTITY_SETUP_DEFAULT(Mertens, setup_function11), 75);
			break;

		case 2:
			CALL_PREVIOUS_SAVEPOINT()
			break;

		case 3:
			if (!ENTITY_PARAM(0, 3)
			 && !getInventory()->hasItem(kItemPassengerList)
			 && ENTITY_PARAM(0, 2)) {
				 getSavePoints()->push(kEntityMertens, kEntityVerges, kAction158617345);
				 ENTITY_PARAM(0, 3) = 1;
			}

			getEntities()->drawSequenceLeft(kEntityMertens, "601B");

			ENTITY_PARAM(0, 1) = 0;
			_data->getData()->inventoryItem = kItemNone;

			getSavePoints()->push(kEntityMertens, kEntityMertens, kAction17);

			CALL_PREVIOUS_SAVEPOINT()
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function18, 18)
	error("Mertens: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function19, 19)
	error("Mertens: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function20, 20)
	error("Mertens: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION_II(Mertens, function21, 21)
	error("Mertens: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function22, 22)
	error("Mertens: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function23, 23)
	error("Mertens: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function24, 24)
	error("Mertens: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function25, 25)
	error("Mertens: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION_I(Mertens, function26, 26)
	error("Mertens: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION_I(Mertens, function27, 27)
	error("Mertens: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION_S(Mertens, function28, 28)
	error("Mertens: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION_SS(Mertens, function29, 29)
	error("Mertens: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION_I(Mertens, function30, 30)
	error("Mertens: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION_I(Mertens, function31, 31)
	error("Mertens: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function32, 32)
	error("Mertens: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function33, 33)
	error("Mertens: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter1, 34)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(41)
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

		ENTITY_PARAM(0, 1) = 0;

		_data->getData()->field_491 = EntityData::kField491_9460;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_3;

		break;
	}

}

IMPLEMENT_FUNCTION(Mertens, function35, 35)
	error("Mertens: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function36, 36)
	error("Mertens: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function37, 37)
	error("Mertens: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function38, 38)
	error("Mertens: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function39, 39)
	error("Mertens: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function40, 40)
	error("Mertens: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function41, 41)
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

IMPLEMENT_FUNCTION(Mertens, function42, 42)
	error("Mertens: callback function 42 not implemented!");

}

IMPLEMENT_FUNCTION(Mertens, chapter2, 43)
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
		_data->getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 6) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(0, 1) = 0;
		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 5) = 0;
		ENTITY_PARAM(0, 6) = 0;
		ENTITY_PARAM(0, 7) = 0;
		break;

	case kAction18:
		if (_data->getNextCallback() == 1)
			setup_function44();
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function44, 44)
	error("Mertens: callback function 44 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter3, 45)
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
		_data->getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 6) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 2) = 0;
		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 4) = 0;
		ENTITY_PARAM(1, 5) = 0;
		ENTITY_PARAM(1, 6) = 0;
		ENTITY_PARAM(1, 7) = 0;

		ENTITY_PARAM(2, 3) = 0;
		break;

	case kAction18:
		if (_data->getNextCallback() == 1)
			setup_function46();
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function46, 46)
	error("Mertens: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter4, 47)
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
		_data->getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 6) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 2) = 0;
		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 4) = 0;
		ENTITY_PARAM(1, 5) = 0;
		ENTITY_PARAM(1, 6) = 0;
		ENTITY_PARAM(1, 7) = 0;

		ENTITY_PARAM(2, 4) = 0;
		break;

	case kAction18:
		if (_data->getNextCallback() == 1)
			setup_function48();
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function48, 48)
	error("Mertens: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function49, 49)
	error("Mertens: callback function 49 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter5, 50)
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
		_data->getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function51, 51)
	if (savepoint->action == kAction70549068)
		setup_function52();
}

IMPLEMENT_FUNCTION(Mertens, function52, 52)
	error("Mertens: callback function 52 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function53, 53)
	error("Mertens: callback function 53 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Mertens, 54)

} // End of namespace LastExpress
