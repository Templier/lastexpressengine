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
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Mahmud::Mahmud(LastExpressEngine *engine) : Entity(engine, kEntityMahmud) {
	ADD_CALLBACK_FUNCTION(Mahmud, reset);
	ADD_CALLBACK_FUNCTION(Mahmud, draw);
	ADD_CALLBACK_FUNCTION(Mahmud, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Mahmud, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(Mahmud, playSound);
	ADD_CALLBACK_FUNCTION(Mahmud, playSoundMertens);
	ADD_CALLBACK_FUNCTION(Mahmud, updateFromTime);
	ADD_CALLBACK_FUNCTION(Mahmud, savegame);
	ADD_CALLBACK_FUNCTION(Mahmud, updateEntity);
	ADD_CALLBACK_FUNCTION(Mahmud, function10);
	ADD_CALLBACK_FUNCTION(Mahmud, function11);
	ADD_CALLBACK_FUNCTION(Mahmud, function12);
	ADD_CALLBACK_FUNCTION(Mahmud, function13);
	ADD_CALLBACK_FUNCTION(Mahmud, chapters_handler);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter1);
	ADD_CALLBACK_FUNCTION(Mahmud, resetChapter);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter2);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter3);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter4);
	ADD_CALLBACK_FUNCTION(Mahmud, chapter5);
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Mahmud, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_NOSETUP(Mahmud, draw, 2)
	Entity::draw(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Mahmud, enterExitCompartment, 3)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 * @param param5 The time ticks
 * @param param6 The object for loading the scene
 */
IMPLEMENT_FUNCTION_SIII(Mahmud, enterExitCompartment2, 4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM(params->param7, getState()->timeTicks, params->param5);

		if (!getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionLookingUp))
			getScenes()->loadSceneFromObject((ObjectIndex)params->param6, true);
		break;

	case kActionExitCompartment:
		getEntities()->exitCompartment(kEntityMahmud, (ObjectIndex)params->param4);

		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityMahmud, (char *)&params->seq);
		getEntities()->enterCompartment(kEntityMahmud, (ObjectIndex)params->param4);
		break;
	}
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Mahmud, playSound, 5)
	Entity::playSound(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Mahmud, playSoundMertens, 6)
	Entity::playSound(savepoint, false, getSound()->getSoundFlag(kEntityMertens));
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_NOSETUP(Mahmud, updateFromTime, 7)
	Entity::updateFromTime(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Mahmud, savegame, 8)
	Entity::savegame(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Mahmud, updateEntity, 9)
	if (savepoint.action == kActionExcuseMeCath) {
		if (getInventory()->hasItem(kItemPassengerList))
			getSound()->playSound(kEntityPlayer, rnd(2) ? "CAT1025" : "CAT1025Q");
		else
			getSound()->excuseMeCath();

		return;
	}

	Entity::updateEntity(savepoint, true);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(Mahmud, function10, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM(params->param6, getState()->time, 13500);

		getObjects()->update(kObjectCompartment5, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment6, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment7, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment8, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);

		setCallback(2);
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Ed", kObjectCompartment4);
		break;

	case kAction2:
	case kActionDrawScene:
		if (!getSound()->isBuffered(kEntityMahmud)) {
			EntityPosition position = getEntityData(kEntityPlayer)->entityPosition;
			if (position < kPosition_1500 || position >= kPosition_5790 || (position > kPosition_4455 && params->param5 != 5)) {
				getObjects()->update(kObjectCompartment5, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
				getObjects()->update(kObjectCompartment6, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
				getObjects()->update(kObjectCompartment7, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
				getObjects()->update(kObjectCompartment8, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);

				setCallback(3);
				call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Ed", kObjectCompartment4);
			}
		}
		break;

	case kActionKnock:
	case kActionOpenDoor:
		if (!getSound()->isBuffered((savepoint.action == kActionKnock) ? "LIB012" : "LIB013", true))
			getSound()->playSound(kEntityPlayer, (savepoint.action == kActionKnock) ? "LIB012" : "LIB013");

		params->param5 = savepoint.param.intValue;

		if (!getSound()->isBuffered(kEntityMahmud)) {
			params->param3++;

			switch(params->param3) {
			default:
				params->param4 = 1;
				break;

			case 1:
				getSound()->playSound(kEntityMahmud, "MAH1174");
				break;

			case 2:
				getSound()->playSound(kEntityMahmud, "MAH1173B");
				break;

			case 3:
				getSound()->playSound(kEntityMahmud, params->param2 ? "MAH1170E" : "MAH1173A");
				break;
			}
		}

		if (params->param4) {
			if (getState()->time >= kTimeCityGalanta) {
				params->param3 = 0;
			} else {
				getSound()->playSound(kEntityTrain, "LIB050", SoundManager::kFlagDefault);
				getLogic()->gameOver(kSavegameTypeIndex, 0, (getProgress().chapter == kChapter1) ? kSceneGameOverPolice1 : kSceneGameOverPolice2, true);
			}
			break;
		}

		getAction()->handleOtherCompartment((ObjectIndex)savepoint.param.intValue, false, false);

		switch (getScenes()->get(getState()->scene)->position) {
		default:
			break;

		case 55:
			getScenes()->loadSceneFromObject(kObjectCompartment5, true);
			break;

		case 56:
			getScenes()->loadSceneFromObject(kObjectCompartment6, true);
			break;

		case 57:
			getScenes()->loadSceneFromObject(kObjectCompartment7, true);
			break;

		case 58:
			getScenes()->loadSceneFromObject(kObjectCompartment8, true);
			break;
		}
		break;

	case kActionDefault:
		getSound()->playSound(kEntityMahmud, params->param2 ? "MAH1170A" : "MAH1173", SoundManager::kFlagInvalid, 45);
		getProgress().field_C4 = 1;

		setCallback(1);
		call(new ENTITY_SETUP_SIII(Mahmud, setup_enterExitCompartment2), "614Dd", kObjectCompartment4, 30, params->param1);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartment5, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment6, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment7, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment8, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);

			getData()->posture = kPostureStanding;

			getEntities()->drawSequenceLeft(kEntityMahmud, "614Md");
			getEntities()->enterCompartment(kEntityMahmud, kObjectCompartment4, true);
			break;

		case 2:
		case 3:
			getEntities()->exitCompartment(kEntityMahmud, kObjectCompartment4, true);
			getData()->posture = kPostureSitting;
			getEntities()->clearSequences(kEntityMahmud);

			CALLBACK_ACTION();
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

	case kActionKnock:
	case kActionOpenDoor: {
		getSound()->playSound(kEntityPlayer, (savepoint.action == kActionKnock ? "LIB012" : "LIB013"));

		if (!getSound()->isBuffered(kEntityMahmud)) {
			params->param1++;

			getSound()->playSound(kEntityMahmud, (params->param1 == 1 ? "MAH1170E" : (params->param1 == 2 ? "MAH1173B" : "MAH1174")));
		}

		switch (getScenes()->get(getState()->scene)->position) {
		default:
			break;

		case 55:
			getScenes()->loadSceneFromObject(kObjectCompartment5, true);
			break;

		case 56:
			getScenes()->loadSceneFromObject(kObjectCompartment6, true);
			break;

		case 57:
			getScenes()->loadSceneFromObject(kObjectCompartment7, true);
			break;

		case 58:
			getScenes()->loadSceneFromObject(kObjectCompartment8, true);
			break;
		}
		break;
		}

	case kActionDefault:
		getSavePoints()->push(kEntityMahmud, kEntityMertens, kAction102227384);
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Ad", kObjectCompartment4);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->posture = kPostureStanding;
			getObjects()->update(kObjectCompartment4, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
			getEntities()->drawSequenceLeft(kEntityMahmud, "614Kd");
			getEntities()->enterCompartment(kEntityMahmud, kObjectCompartment4, true);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "MAH1170A");
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSoundMertens), "MAH1170B");
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "MAH1170C");
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSoundMertens), "MAH1170D");
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "MAH1170E");
			break;

		case 6:
			setCallback(7);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSoundMertens), "MAH1170F");
			break;

		case 7:
			setCallback(8);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Ld", kObjectCompartment4);
			break;

		case 8:
			getSavePoints()->push(kEntityMahmud, kEntityMertens, kAction156567128);
			getEntities()->drawSequenceLeft(kEntityMahmud, "614Bd");
			getEntities()->enterCompartment(kEntityMahmud, kObjectCompartment4, true);

			setCallback(9);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "MAH1170G");
			break;

		case 9:
			setCallback(10);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSoundMertens), "MAH1170H");
			break;

		case 10:
			getObjects()->update(kObjectCompartment5, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment6, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment7, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment8, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			break;

		case 11:
			getEntities()->exitCompartment(kEntityMahmud, kObjectCompartment4, true);
			getData()->posture = kPostureSitting;

			getEntities()->clearSequences(kEntityMahmud);
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);

			CALLBACK_ACTION();
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

		setCallback(11);
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Cd", kObjectCompartment4);
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
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Gd", kObjectCompartment4);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->posture = kPostureStanding;
			getObjects()->update(kObjectCompartment4, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);

			setCallback(2);
			call(new ENTITY_SETUP(Mahmud, setup_updateEntity), kCarGreenSleeping, kPosition_4070);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Ff", kObjectCompartment6);
			break;

		case 3:
			getData()->posture = kPostureSitting;
			getEntities()->clearSequences(kEntityMahmud);

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "Har1105");
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Gf", kObjectCompartment6);
			break;

		case 5:
			getData()->posture = kPostureStanding;

			setCallback(6);
			call(new ENTITY_SETUP(Mahmud, setup_updateEntity), kCarGreenSleeping, kPosition_5790);
			break;

		case 6:
			setCallback(7);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Fd", kObjectCompartment4);
			break;

		case 7:
			getData()->posture = kPostureSitting;
			getEntities()->clearSequences(kEntityMahmud);

			CALLBACK_ACTION();
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
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Gd", kObjectCompartment4);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->posture = kPostureStanding;
			getObjects()->update(kObjectCompartment4, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);

			setCallback(2);
			call(new ENTITY_SETUP(Mahmud, setup_updateEntity), kCarGreenSleeping, kPosition_2740);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Fh", kObjectCompartment8);
			break;

		case 3:
			getData()->posture = kPostureSitting;
			getEntities()->clearSequences(kEntityMahmud);

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "Har1107");
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Gh", kObjectCompartment8);
			break;

		case 5:
			getData()->posture = kPostureStanding;

			setCallback(6);
			call(new ENTITY_SETUP(Mahmud, setup_updateEntity), kCarGreenSleeping, kPosition_5790);
			break;

		case 6:
			setCallback(7);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_enterExitCompartment), "614Fd", kObjectCompartment4);
			break;

		case 7:
			getData()->posture = kPostureSitting;
			getEntities()->clearSequences(kEntityMahmud);

			CALLBACK_ACTION();
			break;

		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, chapters_handler, 14)
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

			TIME_CHECK_CALLBACK(Mahmud, kTime1098000, params->param6, 1, setup_function13);

			if (!getSound()->isBuffered("HAR1104") && getState()->time > kTime1167300 && !params->param7) {
				params->param7 = 1;

				setCallback(2);
				call(new ENTITY_SETUP(Mahmud, setup_function12));
				break;
			}
		}

		if (params->param5) {
			UPDATE_PARAM(params->param8, getState()->timeTicks, 75);

			params->param4 = 1;
			params->param5 = 0;

			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorNormal, kCursorNormal);
		}

		params->param8 = 0;
		break;

	case kActionKnock:
	case kActionOpenDoor:
		if (params->param5) {
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorNormal, kCursorNormal);

			if (getProgress().jacket == kJacketBlood || getEvent(kEventMahmudWrongDoor) || getEvent(kEventMahmudWrongDoorOriginalJacket) || getEvent(kEventMahmudWrongDoorDay)) {
				// Check if we have the passenger list
				if (getInventory()->hasItem(kItemPassengerList)) {
					setCallback(6);
					call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), rnd(2) == 0 ? "CAT1501" : getSound()->wrongDoorCath());
				} else {
					setCallback(7);
					call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), getSound()->wrongDoorCath());
				}
			} else {
				setCallback(savepoint.action == kActionKnock ? 8 : 9);
				call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), savepoint.action == kActionKnock ? "LIB012" : "LIB013");
			}
		} else {
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(savepoint.action == kActionKnock ? 3 : 4);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), savepoint.action == kActionKnock ? "LIB012" : "LIB013");
		}
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarGreenSleeping;

		getEntities()->clearSequences(kEntityMahmud);
		params->param3 = 1;

		getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
		break;

	case kActionDrawScene:
		if (params->param4 || params->param5) {
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			params->param4 = 0;
			params->param5 = 0;
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			return;

		case 1:
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			params->param4 = 0;
			params->param5 = 0;

			if (!getSound()->isBuffered("HAR1104") && getState()->time > kTime1167300 && !params->param7) {
				params->param7 = 1;
				setCallback(2);
				call(new ENTITY_SETUP(Mahmud, setup_function12));
				break;
			}

			params->param8 = 0;
			break;

		case 2:
			getObjects()->update(kObjectCompartment4, kEntityMahmud, kLocation3, kCursorHandKnock, kCursorHand);
			params->param4 = 0;
			params->param5 = 0;
			params->param8 = 0;
			break;

		case 3:
		case 4:
			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Mahmud, setup_playSound), "MAH1175");
			break;

		case 5: {
			CursorStyle cursor = kCursorHand;
			CursorStyle cursor2 = kCursorHandKnock;

			if (getProgress().jacket == kJacketBlood
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
			setCallback(10);
			call(new ENTITY_SETUP(Mahmud, setup_savegame), kSavegameTypeEvent, kEventMahmudWrongDoor);
			return;

		case 10:
			getAction()->playAnimation((getProgress().jacket == kJacketGreen) ? (isDay() ? kEventMahmudWrongDoorDay : kEventMahmudWrongDoor) : kEventMahmudWrongDoorOriginalJacket);
			getSound()->playSound(kEntityPlayer, "LIB015");
			getScenes()->processScene();

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
		setCallback(12);
		call(new ENTITY_SETUP(Mahmud, setup_function11));
		break;

	case kAction290410610:
		params->param3 = (params->param3 < 1) ? 1 : 0;
		setCallback(11);
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
		TIME_CHECK_CHAPTER1(setup_chapters_handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityMahmud, kAction170483072, 0);

		getData()->entityPosition = kPosition_540;
		getData()->posture = kPostureStanding;
		getData()->car = kCarGreenSleeping;

		getObjects()->update(kObjectCompartment4, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject20, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, resetChapter, 16)
	if (savepoint.action != kActionDefault)
		return;

	getData()->entityPosition = kPosition_5790;
	getData()->posture = kPostureSitting;
	getData()->car = kCarGreenSleeping;

	getObjects()->update(kObjectCompartment4, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
	getEntities()->clearSequences(kEntityMahmud);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, chapter2, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapters_handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityMahmud);

		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, chapter3, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapters_handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityMahmud);

		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, chapter4, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapters_handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityMahmud);

		getData()->entityPosition = kPosition_2740;
		getData()->posture = kPostureSitting;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Mahmud, chapter5, 20)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityMahmud);
}

} // End of namespace LastExpress
