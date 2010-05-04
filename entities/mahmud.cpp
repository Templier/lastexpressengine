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

#include "lastexpress/data/scene.h"

#include "lastexpress/entities/mahmud.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Mahmud::Mahmud(LastExpressEngine *engine) : Entity(engine, kEntityMahmud) {
	ADD_CALLBACK_FUNCTION(Mahmud, function1);
	ADD_CALLBACK_FUNCTION(Mahmud, draw);
	ADD_CALLBACK_FUNCTION(Mahmud, function3);
	ADD_CALLBACK_FUNCTION(Mahmud, function4);
	ADD_CALLBACK_FUNCTION(Mahmud, playSound);
	ADD_CALLBACK_FUNCTION(Mahmud, playSoundMertens);
	ADD_CALLBACK_FUNCTION(Mahmud, updateFromTime);
	ADD_CALLBACK_FUNCTION(Mahmud, savegame);
	ADD_CALLBACK_FUNCTION(Mahmud, function9);
	ADD_CALLBACK_FUNCTION(Mahmud, function10);
	ADD_CALLBACK_FUNCTION(Mahmud, function11);
	ADD_CALLBACK_FUNCTION(Mahmud, function12);
	ADD_CALLBACK_FUNCTION(Mahmud, function13);
	ADD_CALLBACK_FUNCTION(Mahmud, function14);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter1);
	ADD_CALLBACK_FUNCTION(Mahmud, function16);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter2);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter3);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter4);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter5);
}

IMPLEMENT_FUNCTION(Mahmud, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Mahmud, draw, 2)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SI(Mahmud, function3, 3)
	Entity::updateFields(savepoint);
}

// param1: sequence
// param2: object index
// param3: game ticks
// param4: object index 
IMPLEMENT_FUNCTION_SIII(Mahmud, function4, 4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FROM_TICKS(5, params->param3);

		if (!getLogic()->checkSceneFields(kSceneNone, false))
			getLogic()->loadSceneFromObject2((ObjectIndex)params->param4);

		break;

	case kAction3:
		getEntities()->updateFields1(kEntityMahmud, (ObjectIndex)params->param2);

		CALL_PREVIOUS_SAVEPOINT();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityMahmud, params->seq);
		getEntities()->updateFields0(kEntityMahmud, (ObjectIndex)params->param2);
		break;
	}
}

IMPLEMENT_FUNCTION_S(Mahmud, playSound, 5)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_S(Mahmud, playSoundMertens, 6)
	Entity::playSound(savepoint, false, getEntities()->getSoundValue(kEntityMertens));
}

IMPLEMENT_FUNCTION_NOSETUP(Mahmud, updateFromTime, 7)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_II(Mahmud, savegame, 8)
	Entity::savegame(savepoint);
}

// param1: field495
// param2: field491
IMPLEMENT_FUNCTION_II(Mahmud, function9, 9)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
	case kActionDefault:
		if (getEntities()->checkEntity(kEntityMahmud, (EntityData::Field495Value)params->param1, (EntityData::Field491Value)params->param2))
			CALL_PREVIOUS_SAVEPOINT();
		break;

	case kAction5:
		if (getInventory()->hasItem(kItemPassengerList))
			getSound()->playSound(kEntityNone, (random(2) == 0 ? "CAT1025A" : "CAT1025"));
		else
			getSound()->excuseMeCath();
		break;

	case kAction6:
		getSound()->excuseMe(kEntityMahmud);
		break;
	}
}

IMPLEMENT_FUNCTION_II(Mahmud, function10, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FROM_TIME(6, 13500);

		getObjects()->update(kObjectCompartment5, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment6, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment7, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment8, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);

		_data->setNextCallback(2);
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Ed", 4);
		break;

	case kAction2:
	case kAction17: {
		if (getSound()->isBuffered(kEntityMahmud))
			break;

		EntityData::Field491Value field491 = getEntities()->getData(kEntityNone)->getData()->field_491;
		if (field491 < 1500 || field491 >= 5790 || (field491 > 4455 && params->param5 != 5)) {
			getObjects()->update(kObjectCompartment5, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment6, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment7, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment8, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);

			_data->setNextCallback(3);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Ed", 4);
		}
		break;
	}

	case kAction8:
	case kAction9:
		if (!getSound()->isFileInQueue((savepoint.action == kAction8) ? "LIB012" : "LIB013"))
			getSound()->playSound(kEntityNone, (savepoint.action == kAction8) ? "LIB012" : "LIB013");

		params->param5 = savepoint.param.intValue;		

		if (!getSound()->isBuffered(kEntityMahmud)) {
			params->param3++;

			switch(params->param3) {
			default:
				getSound()->playSound(kEntityMahmud, params->param2 ? "MAH1170E" : "MAH1173A");
				break;

			case 1:
				getSound()->playSound(kEntityMahmud, "MAH1174");
				break;

			case 2:
				getSound()->playSound(kEntityMahmud, "MAH1173B");
				break;

			case 3:
				params->param4 = 1;
				break;
			}
		}

		if (params->param4) {
			if (getState()->time >= kTimeGameOver) {
				params->param3 = 0;
			} else {
				getSound()->playSound(kEntityTrain, "LIB050", 16);
				getLogic()->gameOver(kTimeType0, 0, (getProgress().chapter == kChapter1) ? kSceneGameOverPolice1 : kSceneGameOverPolice2, true);
			}
		} else {
			getAction()->handleOtherCompartment((ObjectIndex)savepoint.param.intValue, 0, 0);

			loadSceneObject(currentScene, getState()->scene);
			int position = currentScene.getHeader()->position;
			switch (position) {
			default:
				error("Mahmud::function10: invalid scene position (%d)!", position);

			case 55:
				getLogic()->loadSceneFromObject2(kObjectCompartment5);
				break;

			case 56:
				getLogic()->loadSceneFromObject2(kObjectCompartment6);
				break;

			case 57:
				getLogic()->loadSceneFromObject2(kObjectCompartment7);
				break;

			case 58:
				getLogic()->loadSceneFromObject2(kObjectCompartment8);
				break;
			}
		}
		break;

	case kActionDefault:
		getSound()->playSound(kEntityMahmud, params->param2 ? "MAH1170A" : "MAH1173", -1, 45);
		getProgress().field_C4 = 1;

		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIII(Mahmud, setup_function4), "614Dd", kObjectCompartment4, 30, params->param1);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			error("Mahmud::function10: invalid callback value (%d)!", _data->getNextCallback());
			break;

		case 1:
			getObjects()->update(kObjectCompartment5, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment6, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment7, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment8, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);

			_data->getData()->field_493 = EntityData::kField493_0;

			getEntities()->drawSequenceLeft(kEntityMahmud, "614Md");
			getEntities()->updateField1000_4(kEntityMahmud, kObjectCompartment4);
			break;

		case 2:
		case 3:
			getEntities()->updateField1000_5(kEntityMahmud, kObjectCompartment4);
			_data->getData()->field_493 = EntityData::kField493_1;
			getEntities()->prepareSequences(kEntityMahmud);

			CALL_PREVIOUS_SAVEPOINT();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mahmud, function11, 11)
	error("Mahmud: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, function12, 12)
	error("Mahmud: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, function13, 13)
	error("Mahmud: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, function14, 14)
	error("Mahmud: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Mahmud, chapter1, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(14)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityMahmud, kAction170483072, 0);

		_data->getData()->field_491 = EntityData::kField491_540;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_3;

		getObjects()->update(kObjectCompartment4, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject20, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION(Mahmud, function16, 16)
	if (savepoint.action != kActionDefault)
		return;

	_data->getData()->field_491 = EntityData::kField491_5790;
	_data->getData()->field_493 = EntityData::kField493_1;
	_data->getData()->field_495 = EntityData::kField495_3;

	getObjects()->update(kObjectCompartment4, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
	getEntities()->prepareSequences(kEntityMahmud);
}

IMPLEMENT_FUNCTION(Mahmud, chapter2, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function14();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityMahmud);

		_data->getData()->field_491 = EntityData::kField491_5790;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Mahmud, chapter3, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function14();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityMahmud);

		_data->getData()->field_491 = EntityData::kField491_5790;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Mahmud, chapter4, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function14();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityMahmud);

		_data->getData()->field_491 = EntityData::kField491_2740;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;
		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Mahmud, chapter5, 20)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityMahmud);
}

} // End of namespace LastExpress
