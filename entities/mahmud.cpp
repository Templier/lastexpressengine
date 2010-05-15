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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, function1, 1)
	Entity::function1(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_NOSETUP(Mahmud, draw, 2)
	Entity::draw(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(Mahmud, function3, 3)
	Entity::updateFields(savepoint);
}

//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(Mahmud, playSound, 5)
	Entity::playSound(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(Mahmud, playSoundMertens, 6)
	Entity::playSound(savepoint, false, getEntities()->getSoundValue(kEntityMertens));
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_NOSETUP(Mahmud, updateFromTime, 7)
	Entity::updateFromTime(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(Mahmud, savegame, 8)
	Entity::savegame(savepoint);
}

//////////////////////////////////////////////////////////////////////////
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

	case kActionExcuseMeCath:
		if (getInventory()->hasItem(kItemPassengerList))
			getSound()->playSound(kEntityNone, (random(2) == 0 ? "CAT1025A" : "CAT1025"));
		else
			getSound()->excuseMeCath();
		break;

	case kActionExcuseMe:
		getSound()->excuseMe(kEntityMahmud);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
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
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Ed", kObjectCompartment4);
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
				getLogic()->gameOver(kTimeType0, kTime0, (getProgress().chapter == kChapter1) ? kSceneGameOverPolice1 : kSceneGameOverPolice2, true);
			}
		} else {
			getAction()->handleOtherCompartment((ObjectIndex)savepoint.param.intValue, 0, 0);

			loadSceneObject(currentScene, getState()->scene);
			switch (currentScene.getHeader()->position) {
			default:
				break;

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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, function11, 11)
	switch (savepoint.action) {
	default:
		break;

	case kAction8:
	case kAction9: {
		getSound()->playSound(kEntityNone, (savepoint.action == kAction8 ? "LIB012" : "LIB013"));

		if (!getSound()->isBuffered(kEntityMahmud)) {
			params->param1++;

			getSound()->playSound(kEntityMahmud, (params->param1 == 1 ? "MAH1170E" : (params->param1 == 2 ? "MAH1173B" : "MAH1174")));
		}

		loadSceneObject(currentScene, getState()->scene);
		switch (currentScene.getHeader()->position) {
		default:
			break;

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
		break;
		}

	case kActionDefault:
		getSavePoints()->push(kEntityMahmud, kEntityMertens, kAction102227384);
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Ad", kObjectCompartment4);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			_data->getData()->field_493 = EntityData::kField493_0;
			getObjects()->update(kObjectCompartment4, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
			getEntities()->drawSequenceLeft(kEntityMahmud, "614Kd");
			getEntities()->updateField1000_4(kEntityMahmud, kObjectCompartment4);

			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "MAH1170A");
			break;

		case 2:
			_data->setNextCallback(3);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSoundMertens), "MAH1170B");
			break;

		case 3:
			_data->setNextCallback(4);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "MAH1170C");
			break;

		case 4:
			_data->setNextCallback(5);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSoundMertens), "MAH1170D");
			break;

		case 5:
			_data->setNextCallback(6);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "MAH1170E");
			break;

		case 6:
			_data->setNextCallback(7);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSoundMertens), "MAH1170F");
			break;

		case 7:
			_data->setNextCallback(8);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Ld", kObjectCompartment4);
			break;

		case 8:
			getSavePoints()->push(kEntityMahmud, kEntityMertens, kAction156567128);
			getEntities()->drawSequenceLeft(kEntityMahmud, "614Bd");
			getEntities()->updateField1000_4(kEntityMahmud, kObjectCompartment4);

			_data->setNextCallback(9);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "MAH1170G");
			break;

		case 9:
			_data->setNextCallback(10);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSoundMertens), "MAH1170H");
			break;

		case 10:
			getObjects()->update(kObjectCompartment5, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment6, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment7, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment8, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			break;

		case 11:
			getEntities()->updateField1000_5(kEntityMahmud, kObjectCompartment4);
			_data->getData()->field_493 = EntityData::kField493_1;

			getEntities()->prepareSequences(kEntityMahmud);
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);

			CALL_PREVIOUS_SAVEPOINT();
			break;
		}
		break;

	case kAction123852928:
		if (getSound()->isBuffered(kEntityMahmud))
			getSound()->processEntry(kEntityMahmud);

		getObjects()->update(kObjectCompartment5, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment6, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment7, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment8, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);

		_data->setNextCallback(11);
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Cd", kObjectCompartment4);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// TODO: factorize code between function12 & function13
IMPLEMENT_FUNCTION(Mahmud, function12, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Gd", kObjectCompartment4);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			_data->getData()->field_493 = EntityData::kField493_0;
			getObjects()->update(kObjectCompartment4, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

			_data->setNextCallback(2);
			call(new ENTITY_SETUP(Mahmud, setup_function9), EntityData::kField495_3, EntityData::kField491_4070);
			break;

		case 2:
			_data->setNextCallback(3);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Ff", kObjectCompartment6);
			break;

		case 3:
			_data->getData()->field_493 = EntityData::kField493_1;
			getEntities()->prepareSequences(kEntityMahmud);

			_data->setNextCallback(4);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "Har1105");
			break;

		case 4:
			_data->setNextCallback(5);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Gf", kObjectCompartment6);
			break;

		case 5:
			_data->getData()->field_493 = EntityData::kField493_0;

			_data->setNextCallback(6);
			call(new ENTITY_SETUP(Mahmud, setup_function9), EntityData::kField495_3, EntityData::kField491_5790);
			break;

		case 6:
			_data->setNextCallback(7);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Fd", kObjectCompartment4);
			break;

		case 7:
			_data->getData()->field_493 = EntityData::kField493_1;
			getEntities()->prepareSequences(kEntityMahmud);

			CALL_PREVIOUS_SAVEPOINT();
			break;

		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, function13, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Gd", kObjectCompartment4);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			_data->getData()->field_493 = EntityData::kField493_0;
			getObjects()->update(kObjectCompartment4, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

			_data->setNextCallback(2);
			call(new ENTITY_SETUP(Mahmud, setup_function9), EntityData::kField495_3, EntityData::kField491_2740);
			break;

		case 2:
			_data->setNextCallback(3);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Fh", kObjectCompartment8);
			break;

		case 3:
			_data->getData()->field_493 = EntityData::kField493_1;
			getEntities()->prepareSequences(kEntityMahmud);

			_data->setNextCallback(4);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "Har1107");
			break;

		case 4:
			_data->setNextCallback(5);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Gh", kObjectCompartment8);
			break;

		case 5:
			_data->getData()->field_493 = EntityData::kField493_0;

			_data->setNextCallback(6);
			call(new ENTITY_SETUP(Mahmud, setup_function9), EntityData::kField495_3, EntityData::kField491_5790);
			break;

		case 6:
			_data->setNextCallback(7);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_function3), "614Fd", kObjectCompartment4);
			break;

		case 7:
			_data->getData()->field_493 = EntityData::kField493_1;
			getEntities()->prepareSequences(kEntityMahmud);

			CALL_PREVIOUS_SAVEPOINT();
			break;

		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, function14, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (ENTITY_PARAM(0, 1)) {
			params->param2 = 1;
			getSavePoints()->push(kEntityMahmud, kEntityMertens, kAction204379649);
			ENTITY_PARAM(0, 1) = 0;
		}

		if (!params->param2 && getProgress().chapter == kChapter1) {

			if (getState()->time > kTimeMahmud1 && !params->param6) {
				params->param6 = 1;

				_data->setNextCallback(1);
				call(new ENTITY_SETUP(Mahmud, setup_function13));
				break;
			}

			if (!getSound()->isFileInQueue("HAR1104", true) && getState()->time > kTimeMahmud && !params->param7) {
				params->param7 = 1;

				_data->setNextCallback(2);
				call(new ENTITY_SETUP(Mahmud, setup_function12));
				break;
			}
		}

		if (params->param5) {
			UPDATE_PARAM_FROM_TICKS(8, 75);

			params->param4 = 1;
			params->param5 = 0;
			params->param8 = 0;

			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorNormal, kCursorNormal);
		} else {
			params->param8 = 0;
		}
		break;

	case kAction8:
	case kAction9:
		if (params->param5) {
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorNormal, kCursorNormal);

			if (getProgress().jacket == kJacketOriginal
			 || getEvent(kEventMahmudWrongDoor) || getEvent(kEventMahmudWrongDoorOriginalJacket) || getEvent(kEventMahmudWrongDoorDay)) {

				 // Check if we have the passenger list
				 if (getInventory()->hasItem(kItemPassengerList)) {
					 _data->setNextCallback(6);
					call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), random(2) == 0 ? "CAT1501" : getSound()->wrongDoorCath());
				 } else {
					 _data->setNextCallback(7);
					call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), getSound()->wrongDoorCath());
				 }
			} else {
				_data->setNextCallback(savepoint.action == kAction8 ? 8 : 9);
				call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), savepoint.action == kAction8 ? "LIB012" : "LIB013");
			}
		} else {
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation1, kCursorNormal, kCursorNormal);

			_data->setNextCallback(savepoint.action == kAction8 ? 3 : 4);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), savepoint.action == kAction8 ? "LIB012" : "LIB013");
		}
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_5790;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_3;

		getEntities()->prepareSequences(kEntityMahmud);
		params->param3 = 1;

		getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
		break;

	case kAction17:
		if (params->param4 || params->param5) {
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			params->param4 = 0;
			params->param5 = 0;
		}
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			return;

		case 1:
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);

			params->param4 = 0;
			params->param5 = 0;

			if (!getSound()->isFileInQueue("HAR1104", true) && getState()->time > kTimeMahmud && !params->param7) {
				params->param7 = 1;
				_data->setNextCallback(2);
				call(new ENTITY_SETUP(Mahmud, setup_function12));
			}
			break;

		case 2:
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);

			params->param4 = 0;
			params->param5 = 0;
			params->param8 = 0;
			break;

		case 3:
		case 4:
			_data->setNextCallback(5);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "MAH1175");
			break;

		case 5: {
			CursorStyle cursor = kCursorHand;
			CursorStyle cursor2 = kCursorHandKnock;

			if (getProgress().jacket == kJacketOriginal
			 || getEvent(kEventMahmudWrongDoor)
			 || getEvent(kEventMahmudWrongDoorOriginalJacket)
			 || getEvent(kEventMahmudWrongDoorDay)) {
				cursor = kCursorNormal;
				cursor2 = kCursorTalk;
			}

			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation1, cursor, cursor2);
			params->param5 = 1;
			break;
			}

		case 6:
		case 7:
			params->param4 = 1;
			break;

		case 8:
		case 9:
			_data->setNextCallback(10);
			call(new ENTITY_SETUP(Mahmud, setup_savegame), 2, kEventMahmudWrongDoor);
			return;

		case 10:
			getAction()->playAnimation((getProgress().jacket == kJacketGreen) ? (isDay() ? kEventMahmudWrongDoorDay : kEventMahmudWrongDoor) : kEventMahmudWrongDoorOriginalJacket);
			getSound()->playSound(kEntityNone, "LIB015");
			getLogic()->processScene();

			params->param4 = 1;
			break;

		case 11:
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);

			params->param4 = 0;
			params->param5 = 0;
			break;

		case 12:
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);

			params->param2 = 0;
			params->param4 = 0;
			params->param5 = 0;
			break;
		}
		break;

	case kAction225563840:
		_data->setNextCallback(12);
		call(new ENTITY_SETUP(Mahmud, setup_function11));
		break;

	case kAction290410610:
		params->param3 = (params->param3 < 1) ? 1 : 0;
		_data->setNextCallback(11);
		call(new ENTITY_SETUP(Mahmud, setup_function10), savepoint.param.intValue, params->param3);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, function16, 16)
	if (savepoint.action != kActionDefault)
		return;

	_data->getData()->field_491 = EntityData::kField491_5790;
	_data->getData()->field_493 = EntityData::kField493_1;
	_data->getData()->field_495 = EntityData::kField495_3;

	getObjects()->update(kObjectCompartment4, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
	getEntities()->prepareSequences(kEntityMahmud);
}

//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, chapter5, 20)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityMahmud);
}

} // End of namespace LastExpress
