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

#include "lastexpress/entities/coudert.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Coudert::Coudert(LastExpressEngine *engine) : Entity(engine, kEntityCoudert) {
	ADD_CALLBACK_FUNCTION(Coudert, reset);
	ADD_CALLBACK_FUNCTION(Coudert, bloodJacket);
	ADD_CALLBACK_FUNCTION(Coudert, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Coudert, function4);
	ADD_CALLBACK_FUNCTION(Coudert, function5);
	ADD_CALLBACK_FUNCTION(Coudert, playSound);
	ADD_CALLBACK_FUNCTION(Coudert, playSound16);
	ADD_CALLBACK_FUNCTION(Coudert, savegame);
	ADD_CALLBACK_FUNCTION(Coudert, function9);
	ADD_CALLBACK_FUNCTION(Coudert, function10);
	ADD_CALLBACK_FUNCTION(Coudert, function11);
	ADD_CALLBACK_FUNCTION(Coudert, excuseMe);
	ADD_CALLBACK_FUNCTION(Coudert, function13);
	ADD_CALLBACK_FUNCTION(Coudert, function14);
	ADD_CALLBACK_FUNCTION(Coudert, function15);
	ADD_CALLBACK_FUNCTION(Coudert, function16);
	ADD_CALLBACK_FUNCTION(Coudert, function17);
	ADD_CALLBACK_FUNCTION(Coudert, function18);
	ADD_CALLBACK_FUNCTION(Coudert, function19);
	ADD_CALLBACK_FUNCTION(Coudert, function20);
	ADD_CALLBACK_FUNCTION(Coudert, function21);
	ADD_CALLBACK_FUNCTION(Coudert, function22);
	ADD_CALLBACK_FUNCTION(Coudert, function23);
	ADD_CALLBACK_FUNCTION(Coudert, function24);
	ADD_CALLBACK_FUNCTION(Coudert, function25);
	ADD_CALLBACK_FUNCTION(Coudert, function26);
	ADD_CALLBACK_FUNCTION(Coudert, function27);
	ADD_CALLBACK_FUNCTION(Coudert, function28);
	ADD_CALLBACK_FUNCTION(Coudert, function29);
	ADD_CALLBACK_FUNCTION(Coudert, function30);
	ADD_CALLBACK_FUNCTION(Coudert, function31);
	ADD_CALLBACK_FUNCTION(Coudert, function32);
	ADD_CALLBACK_FUNCTION(Coudert, function33);
	ADD_CALLBACK_FUNCTION(Coudert, function34);
	ADD_CALLBACK_FUNCTION(Coudert, function35);
	ADD_CALLBACK_FUNCTION(Coudert, chapter1);
	ADD_CALLBACK_FUNCTION(Coudert, function37);
	ADD_CALLBACK_FUNCTION(Coudert, function38);
	ADD_CALLBACK_FUNCTION(Coudert, function39);
	ADD_CALLBACK_FUNCTION(Coudert, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Coudert, function41);
	ADD_CALLBACK_FUNCTION(Coudert, chapter2);
	ADD_CALLBACK_FUNCTION(Coudert, function43);
	ADD_CALLBACK_FUNCTION(Coudert, chapter3);
	ADD_CALLBACK_FUNCTION(Coudert, function45);
	ADD_CALLBACK_FUNCTION(Coudert, function46);
	ADD_CALLBACK_FUNCTION(Coudert, function47);
	ADD_CALLBACK_FUNCTION(Coudert, function48);
	ADD_CALLBACK_FUNCTION(Coudert, function49);
	ADD_CALLBACK_FUNCTION(Coudert, function50);
	ADD_CALLBACK_FUNCTION(Coudert, function51);
	ADD_CALLBACK_FUNCTION(Coudert, chapter4);
	ADD_CALLBACK_FUNCTION(Coudert, function53);
	ADD_CALLBACK_FUNCTION(Coudert, function54);
	ADD_CALLBACK_FUNCTION(Coudert, function55);
	ADD_CALLBACK_FUNCTION(Coudert, function56);
	ADD_CALLBACK_FUNCTION(Coudert, chapter5);
	ADD_CALLBACK_FUNCTION(Coudert, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Coudert, function59);
	ADD_CALLBACK_FUNCTION(Coudert, function60);
	ADD_CALLBACK_FUNCTION(Coudert, function61);
	ADD_CALLBACK_FUNCTION(Coudert, function62);
	ADD_NULL_FUNCTION();
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Coudert, reset, 1)
	Entity::reset(savepoint, true);
}

IMPLEMENT_FUNCTION_S(Coudert, bloodJacket, 2)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().jacket == kJacketBlood
		 && getEntities()->checkFields9(kEntityCoudert, kEntityNone, 1000)
		 && !getEntities()->isEntitySittingInCompartmentCars()
		 && !getEntities()->checkFields10()) {
			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventMertensBloodJacket); /* BUG: is this a bug in the original? */
		}
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityCoudert, (char *)&params->seq1);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Coudert, enterExitCompartment, 3)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().jacket == kJacketBlood
		 && getEntities()->checkFields9(kEntityCoudert, kEntityNone, 1000)
		 && !getEntities()->isEntitySittingInCompartmentCars()
		 && !getEntities()->checkFields10()) {
			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventMertensBloodJacket); /* BUG: is this a bug in the original? */
		}
		return;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverBloodJacket, true);
		}
		return;
	}

	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION(Coudert, function4, 4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getData()->direction != kDirectionRight) {
			CALLBACK_ACTION();
			break;
		}

		if (getProgress().jacket == kJacketBlood
		 && getEntities()->checkFields9(kEntityCoudert, kEntityNone, 1000)
		 && !getEntities()->isEntitySittingInCompartmentCars()
		 && !getEntities()->checkFields10()) {
			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventMertensBloodJacket);
		}
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION();
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

IMPLEMENT_FUNCTION_SIII(Coudert, function5, 5)
	error("Coudert: callback function 5 not implemented!");
}

/**
 * Play a sound
 *
 * @param seq1 The sound name
 */
IMPLEMENT_FUNCTION_S(Coudert, playSound, 6)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().jacket == kJacketBlood
		 && getEntities()->checkFields9(kEntityCoudert, kEntityNone, 1000)
		 && !getEntities()->isEntitySittingInCompartmentCars()
		 && !getEntities()->checkFields10()) {
			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventMertensBloodJacket);
		}
		break;

	case kAction2:
		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getSound()->playSound(kEntityCoudert, (char *)&params->seq1);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

/**
 * Play a sound
 *
 * @param seq1 The sound name
 */
IMPLEMENT_FUNCTION_NOSETUP(Coudert, playSound16, 7)
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS);

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().jacket == kJacketBlood
		 && getEntities()->checkFields9(kEntityCoudert, kEntityNone, 1000)
		 && !getEntities()->isEntitySittingInCompartmentCars()
		 && !getEntities()->checkFields10()) {
			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventMertensBloodJacket);
		}
		break;

	case kAction2:
		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getSound()->playSound(kEntityCoudert, (char *)&params->seq1, 16);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Coudert, savegame, 8)
	Entity::savegame(savepoint);
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - CarIndex
//  - EntityPosition
IMPLEMENT_FUNCTION_II(Coudert, function9, 9)
	error("Coudert: callback function 9 not implemented!");
}


//////////////////////////////////////////////////////////////////////////
// Parameters
//  - Time
IMPLEMENT_FUNCTION_I(Coudert, function10, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().jacket == kJacketBlood
		 && getEntities()->checkFields9(kEntityCoudert, kEntityNone, 1000)
		 && !getEntities()->isEntitySittingInCompartmentCars()
		 && !getEntities()->checkFields10()) {
			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventMertensBloodJacket);
			break;
		}

		UPDATE_PARAM(params->param2, getState()->time, params->param1);

		CALLBACK_ACTION();
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - TimeTicks
IMPLEMENT_FUNCTION_I(Coudert, function11, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().jacket == kJacketBlood
		 && getEntities()->checkFields9(kEntityCoudert, kEntityNone, 1000)
		 && !getEntities()->isEntitySittingInCompartmentCars()
		 && !getEntities()->checkFields10()) {
			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventMertensBloodJacket);
			break;
		}

		UPDATE_PARAM(params->param2, getState()->timeTicks, params->param1);

		CALLBACK_ACTION();
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - EntityIndex
IMPLEMENT_FUNCTION_I(Coudert, excuseMe, 12)
	if (savepoint.action != kActionDefault)
		return;

	if (getSound()->isBuffered(kEntityCoudert)) {
		CALLBACK_ACTION();
		return;
	}


	if (isDay()) {
		if (getEntities()->isFemale((EntityIndex)params->param1)) {
			getSound()->playSound(kEntityCoudert, getEntities()->isMarried((EntityIndex)params->param1) ? "JAC1112C" : "JAC1112F");
		} else {
			if (!params->param1 && getProgress().field_18 == 2) {
				switch (random(4)) {
				default:
					break;

				case 0:
					getSound()->playSound(kEntityCoudert, "JAC1013");
					break;

				case 1:
					getSound()->playSound(kEntityCoudert, "JAC1013A");
					break;

				case 2:
					getSound()->playSound(kEntityCoudert, "JAC1113");
					break;

				case 3:
					getSound()->playSound(kEntityCoudert, "JAC1113A");
					break;
				}
			} else {
				getSound()->playSound(kEntityCoudert, "JAC1112D");
			}
		}
	} else {
		if (getEntities()->isFemale((EntityIndex)params->param1))
			getSound()->playSound(kEntityCoudert, getEntities()->isMarried((EntityIndex)params->param1) ? "JAC1112B" : "JAC1112G");
		else
			getSound()->playSound(kEntityCoudert, "JAC1112E");
	}

	CALLBACK_ACTION();
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - bool
//  - EntityIndex
IMPLEMENT_FUNCTION_II(Coudert, function13, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().jacket == kJacketBlood
		 && getEntities()->checkFields9(kEntityCoudert, kEntityNone, 1000)
		 && !getEntities()->isEntitySittingInCompartmentCars()
		 && !getEntities()->checkFields10()) {
			setCallback(3);
			call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventMertensBloodJacket);
			break;
		}

		if (!params->param2 && !params->param3) {

			if (!params->param4) {
				params->param4 = getState()->timeTicks + 75;

				if (!params->param4) {
					getData()->inventoryItem = kItemNone;
					setCallback(4);
					call(new ENTITY_SETUP(Coudert, setup_function19), true);
					break;
				}
			}

			if (params->param4 < (int)getState()->timeTicks) {
				params->param4 = kTimeInvalid;

				getData()->inventoryItem = kItemNone;
				setCallback(4);
				call(new ENTITY_SETUP(Coudert, setup_function19), true);
				break;
			}
		}

		UPDATE_PARAM(params->param5, getState()->timeTicks, 225);

		getData()->inventoryItem = kItemNone;
		setCallback(5);
		call(new ENTITY_SETUP(Coudert, setup_function19), true);
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;

		setCallback(9);
		call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventCoudertAskTylerCompartment);
		break;

	case kAction11:
		++params->param3;

		setCallback(8);
		call(new ENTITY_SETUP(Coudert, setup_excuseMe), savepoint.entity2);
		break;

	case kActionDefault:
		if (params->param2)
			params->param3 = 1;

		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_excuseMe), params->param2);
		break;

	case kAction16:
		--params->param3;

		if (params->param2 && !params->param3) {
			getData()->inventoryItem = kItemNone;
			setCallback(7);
			call(new ENTITY_SETUP(Coudert, setup_function19), true);
		}
		break;

	case kActionDrawScene:
		if (!params->param3) {
			getData()->inventoryItem = kItemNone;
			setCallback(6);
			call(new ENTITY_SETUP(Coudert, setup_function19), true);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Coudert, setup_function17), true);
			break;

		case 2:
			if (getProgress().chapter == kChapter1 && !getProgress().eventCorpseFound && !getEvent(kEventCoudertAskTylerCompartment))
				getData()->inventoryItem = kItemInvalid;

			getEntities()->drawSequenceLeft(kEntityCoudert, params->param1 ? "667I" : "667H");
			break;

		case 3:
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverBloodJacket, true);
			// BUG: the original game continues executing code here
			break;

		case 4:
		case 5:
		case 6:
		case 7:
			CALLBACK_ACTION();
			break;

		case 9:
			getAction()->playAnimation(kEventCoudertAskTylerCompartment);
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 25);
			break;
		}
		break;

	case kAction201439712:
		getEntities()->drawSequenceLeft(kEntityCoudert, "627K");
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Paramaters
//  - EntityIndex
IMPLEMENT_FUNCTION_I(Coudert, function14, 14)
	error("Coudert: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function15, 15)
	error("Coudert: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function16, 16)
	error("Coudert: callback function 16 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - bool
IMPLEMENT_FUNCTION_I(Coudert, function17, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getScenes()->loadSceneFromItemPosition(kItem5);

		if (ENTITY_PARAM(2, 1)) {
			ENTITY_PARAM(2, 1) = 0;
			CALLBACK_ACTION();
			break;
		}

		if (params->param1) {
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_bloodJacket), "627H");
			break;
		}

		if (params->param2) {
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_bloodJacket), "627C");
			break;
		}

		setCallback(3);
		call(new ENTITY_SETUP_SIIS(Coudert, setup_bloodJacket), "627F");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
		case 3:
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function18, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (ENTITY_PARAM(0, 6) || ENTITY_PARAM(0, 8)
		 || ENTITY_PARAM(1, 1) || ENTITY_PARAM(1, 2) || ENTITY_PARAM(1, 3) || ENTITY_PARAM(1, 5) || ENTITY_PARAM(1, 6) || ENTITY_PARAM(1, 7) || ENTITY_PARAM(1, 8)
		 || ENTITY_PARAM(2, 4) || ENTITY_PARAM(2, 6)) {
			getInventory()->setLocationAndProcess(kItem5, kLocation1);

			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_540);
			break;
		}

		if (ENTITY_PARAM(0, 3) || ENTITY_PARAM(0, 5) || ENTITY_PARAM(0, 4)) {
			getEntities()->drawSequenceLeft(kEntityCoudert, "627K");
			getScenes()->loadSceneFromItemPosition(kItem5);

			CALLBACK_ACTION();
			break;
		}

		getEntities()->drawSequenceRight(kEntityCoudert, ENTITY_PARAM(0, 2) ? "627A" : "627D");
		getScenes()->loadSceneFromItemPosition(kItem5);

		if (getEntities()->isPlayerPosition(kCarRedSleeping, 68)) {
			if (!getSound()->isBuffered(kEntityCoudert))
				getSound()->playSound(kEntityCoudert, "JAC1111");

			getScenes()->loadSceneFromPosition(kCarRedSleeping, 25);
		}

		setCallback(3);
		call(new ENTITY_SETUP(Coudert, setup_function4));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->clearSequences(kEntityCoudert);
			ENTITY_PARAM(2, 1) = 1;

			setCallback(2);
			call(new ENTITY_SETUP(Coudert, setup_function10), 75);
			break;

		case 2:
			CALLBACK_ACTION();
			break;

		case 3:
			getEntities()->drawSequenceLeft(kEntityCoudert, ENTITY_PARAM(0, 2) ? "627B" : "627E");
			ENTITY_PARAM(0, 1) = 0;
			getSavePoints()->push(kEntityCoudert, kEntityCoudert, kActionDrawScene);

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - bool
IMPLEMENT_FUNCTION_I(Coudert, function19, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (ENTITY_PARAM(0, 6) || ENTITY_PARAM(0, 8)
		 || ENTITY_PARAM(1, 1) || ENTITY_PARAM(1, 2) || ENTITY_PARAM(1, 3) || ENTITY_PARAM(1, 5) || ENTITY_PARAM(1, 6) || ENTITY_PARAM(1, 7) || ENTITY_PARAM(1, 8)
		 || ENTITY_PARAM(2, 4) || ENTITY_PARAM(2, 6)) {
			getInventory()->setLocationAndProcess(kItem5, kLocation1);
			ENTITY_PARAM(2, 1) = 1;
			CALLBACK_ACTION();
			break;
		}

		if (ENTITY_PARAM(0, 3) || ENTITY_PARAM(0, 5) || ENTITY_PARAM(0, 4)) {
			getScenes()->loadSceneFromItemPosition(kItem5);
			ENTITY_PARAM(2, 1);
			CALLBACK_ACTION();
			break;
		}

		if (params->param1)
			getEntities()->drawSequenceRight(kEntityCoudert, "697H");
		else
			getEntities()->drawSequenceRight(kEntityCoudert, ENTITY_PARAM(0, 2) ? "627A" : "627D");

		getScenes()->loadSceneFromItemPosition(kItem5);

		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function4));
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->drawSequenceLeft(kEntityCoudert, ENTITY_PARAM(0, 2) ? "627B" : "627E");
			ENTITY_PARAM(0, 1) = 0;

			CALLBACK_ACTION();
		}
		break;
	}
}

IMPLEMENT_FUNCTION_II(Coudert, function20, 20)
	error("Coudert: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function21, 21)
	error("Coudert: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function22, 22)
	error("Coudert: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_4070);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_enterExitCompartment), "627Vf", kObjectCompartmentF);
			break;

		case 2:
			getEntities()->drawSequenceLeft(kEntityCoudert, "627Wf");
			getEntities()->enterCompartment(kEntityCoudert, kObjectCompartmentF, true);
			getSavePoints()->push(kEntityCoudert, kEntityMax, kAction158007856);

			setCallback(3);
			call(new ENTITY_SETUP(Coudert, setup_function10), 150);
			break;

		case 3:
			getEntities()->exitCompartment(kEntityCoudert, kObjectCompartmentF, true);
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function24, 24)
	error("Coudert: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function25, 25)
	error("Coudert: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function26, 26)
	error("Coudert: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function27, 27)
	error("Coudert: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function28, 28)
	error("Coudert: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function29, 29)
	error("Coudert: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function30, 30)
	error("Coudert: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function31, 31)
	error("Coudert: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function32, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function16));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_9460);
			break;

		case 2:
			getEntities()->clearSequences(kEntityCoudert);
			setCallback(3);
			call(new ENTITY_SETUP(Coudert, setup_function10), 900);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_2000);
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP(Coudert, setup_function18));
			break;

		case 5:
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function33, 33)
	error("Coudert: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function34, 34)
	error("Coudert: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function35, 35)
	error("Coudert: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter1, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Coudert, kTimeChapter1, params->param1, 1, setup_chapter1Handler)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityCoudert, kAction292048641, 7);
		getSavePoints()->addData(kEntityCoudert, kAction326348944, 8);
		getSavePoints()->addData(kEntityCoudert, kAction171394341, 2);
		getSavePoints()->addData(kEntityCoudert, kAction154005632, 4);
		getSavePoints()->addData(kEntityCoudert, kAction169557824, 3);
		getSavePoints()->addData(kEntityCoudert, kAction226031488, 5);
		getSavePoints()->addData(kEntityCoudert, kAction339669520, 6);
		getSavePoints()->addData(kEntityCoudert, kAction189750912, 10);
		getSavePoints()->addData(kEntityCoudert, kAction185737168, 12);
		getSavePoints()->addData(kEntityCoudert, kAction185671840, 13);
		getSavePoints()->addData(kEntityCoudert, kAction205033696, 15);
		getSavePoints()->addData(kEntityCoudert, kAction157026693, 14);
		getSavePoints()->addData(kEntityCoudert, kAction189026624, 11);
		getSavePoints()->addData(kEntityCoudert, kAction168254872, 17);
		getSavePoints()->addData(kEntityCoudert, kAction201431954, 18);
		getSavePoints()->addData(kEntityCoudert, kAction188570113, 19);

		ENTITY_PARAM(0, 1) = 0;
		ENTITY_PARAM(0, 2) = 1;

		getData()->entityPosition = kPosition_1500;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRedSleeping;

		getObjects()->updateLocation2(kObject111, kLocation1);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_chapter1Handler();
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function37, 37)
	error("Coudert: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function38, 38)
switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->car = kCarRedSleeping;
		getData()->entityPosition = kPosition_8200;
		getData()->posture = kPostureSitting;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			ENTITY_PARAM(0, 6) = 0;
			ENTITY_PARAM(0, 7) = 0;

			setCallback(2);
			call(new ENTITY_SETUP(Coudert, setup_function18));
			break;

		case 2:
			setup_chapter1Handler();
			break;
		}
		break;

	case kAction191477936:
		getData()->entityPosition = kPosition_4070;
		getData()->posture = kPostureStanding;
		getObjects()->update(kObjectCompartment4, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_2000);
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function39, 39)
	error("Coudert: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter1Handler, 40)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (ENTITY_PARAM(2, 3)) {
			ENTITY_PARAM(0, 1) = 1;
			ENTITY_PARAM(0, 3) = 0;
			ENTITY_PARAM(0, 4) = 0;
			ENTITY_PARAM(0, 5) = 0;
			ENTITY_PARAM(0, 8) = 0;

			ENTITY_PARAM(1, 1) = 0;

			ENTITY_PARAM(2, 1) = 0;
			ENTITY_PARAM(2, 2) = 0;

			getEntities()->drawSequenceLeft(kEntityCoudert, "697F");

			params->param1 = 1;
			params->param2 = 1;

			ENTITY_PARAM(2, 3) = 0;
		}

		getData()->inventoryItem = (getProgress().eventCorpseFound || getEvent(kEventCoudertAskTylerCompartment)) ? kItemNone : kItemInvalid;

		if (ENTITY_PARAM(0, 8)) {
			getData()->inventoryItem = kItemNone;

			setCallback(4);
			call(new ENTITY_SETUP(Coudert, setup_function15), true);
			break;
		}

label_callback_4:
		if (ENTITY_PARAM(1, 1)) {
			getData()->inventoryItem = kItemNone;

			setCallback(5);
			call(new ENTITY_SETUP(Coudert, setup_function15), false);
			break;
		}

label_callback_5:
		if (ENTITY_PARAM(0, 6) || ENTITY_PARAM(0, 7)) {
			getData()->inventoryItem = kItemNone;
			setup_function37();
			break;
		}

		if (ENTITY_PARAM(0, 3)) {
			getData()->inventoryItem = kItemNone;

			setCallback(6);
			call(new ENTITY_SETUP(Coudert, setup_function14), kEntityVerges);
			break;
		}

label_callback_6:
		if (ENTITY_PARAM(0, 5)) {
			getData()->inventoryItem = kItemNone;

			setCallback(7);
			call(new ENTITY_SETUP(Coudert, setup_function14), kEntityMertens);
			break;
		}

label_callback_7:
		if (ENTITY_PARAM(0, 4)) {
			getData()->inventoryItem = kItemNone;

			setCallback(8);
			call(new ENTITY_SETUP(Coudert, setup_function14), kEntityMmeBoutarel);
			break;
		}

label_callback_8:
		if (ENTITY_PARAM(2, 2)) {
			getData()->inventoryItem = kItemNone;

			setCallback(9);
			call(new ENTITY_SETUP(Coudert, setup_function39));
			break;
		}

label_callback_9:
		if (ENTITY_PARAM(0, 1) && !getSound()->isBuffered(kEntityCoudert))
			getSound()->playSound(kEntityCoudert, random(2) ? "JAC1065" : "JAC1065A");

		if (getState()->time > kTime1107000 && !ENTITY_PARAM(0, 1) && !getEvent(kEventVassiliSeizure)) {
			getData()->inventoryItem = kItemNone;

			setCallback(10);
			call(new ENTITY_SETUP(Coudert, setup_function41));
			break;
		}

label_callback_10:
		if (getState()->time > kTime1189800 && !ENTITY_PARAM(0, 1) && !ENTITY_PARAM(2, 1)) {
			UPDATE_PARAM_FUNCTION(params->param3, getState()->time, 2700, label_coudert_object);

			ENTITY_PARAM(0, 2) = 1;
			ENTITY_PARAM(0, 1) = 1;

			getEntities()->drawSequenceLeft(kEntityCoudert, "697F");

			params->param3 = 0;
		}

label_coudert_object:
		if (!ENTITY_PARAM(0, 2))
			break;

		TIME_CHECK_OBJECT(kTime1107000, params->param4, kObject111, kLocation2);
		TIME_CHECK_OBJECT(kTime1161000, params->param5, kObject111, kLocation3);
		TIME_CHECK_OBJECT(kTime1206000, params->param6, kObject111, kLocation4);
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;

		setCallback(11);
		call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventCoudertAskTylerCompartment);
		break;

	case kAction11:
		if (!ENTITY_PARAM(0, 1) && !ENTITY_PARAM(2, 1)) {
			getData()->inventoryItem = kItemNone;

			setCallback(13);
			call(new ENTITY_SETUP(Coudert, setup_function13), savepoint.param.intValue, savepoint.entity2);
		}
		break;

	case kActionDefault:
		getData()->car = kCarRedSleeping;
		getData()->entityPosition = kPosition_1500;
		getData()->posture = kPostureStanding;

		getScenes()->loadSceneFromItemPosition(kItem5);
		break;

	case kActionDrawScene:
		if (!ENTITY_PARAM(2, 1) && !ENTITY_PARAM(0, 1)) {

			if (!getEntities()->isPlayerPosition(kCarRedSleeping, 1) && !getEntities()->isPlayerPosition(kCarRedSleeping, 23))
				break;

			if (getProgress().jacket == kJacketBlood) {
				setCallback(1);
				call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameType2, kEventCoudertBloodJacket);
			} else {
				setCallback(getEntities()->isPlayerPosition(kCarRedSleeping, 1) ? 2 : 3);
				call(new ENTITY_SETUP(Coudert, setup_function13), true, kEntityNone);
			}
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverBloodJacket, true);
			break;

		case 4:
			goto label_callback_4;

		case 5:
			goto label_callback_5;

		case 6:
			goto label_callback_6;

		case 7:
			goto label_callback_7;

		case 8:
			goto label_callback_8;

		case 9:
			goto label_callback_9;

		case 10:
			params->param1 = 1;
			goto label_callback_10;

		case 11:
			getAction()->playAnimation(kEventCoudertAskTylerCompartment);
			getEntities()->drawSequenceRight(kEntityCoudert, ENTITY_PARAM(0, 2) ? "627A" : "627D");
			getScenes()->loadSceneFromItemPosition(kItem5);

			ENTITY_PARAM(0, 1) = 0;

			getScenes()->loadSceneFromPosition(kCarRedSleeping, 25);

			setCallback(12);
			call(new ENTITY_SETUP(Coudert, setup_function4));
			break;

		case 12:
			getEntities()->drawSequenceLeft(kEntityCoudert, ENTITY_PARAM(0, 2) ? "627B" : "627E");
			break;

		case 14:
			setCallback(15);
			call(new ENTITY_SETUP(Coudert, setup_function18));
			break;
		}
		break;

	case kAction168253822:
		if (!ENTITY_PARAM(2, 1) && !ENTITY_PARAM(0, 1)) {
			getData()->inventoryItem = kItemNone;
			getSound()->playSound(kEntityCoudert, "JAC1120");

			setCallback(14);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_bloodJacket), "697D");
		}
		break;

	case kAction225358684:
		if (!ENTITY_PARAM(0, 1)) {
			getData()->inventoryItem = kItemNone;
			setCallback(16);
			call(new ENTITY_SETUP(Coudert, setup_function30), savepoint.param.intValue);
		}
		break;

	case kAction225932896:
		if (!ENTITY_PARAM(2, 1) && !ENTITY_PARAM(0, 1))
			getSavePoints()->push(kEntityCoudert, kEntityFrancois, kAction205346192);
		break;

	case kAction305159806:
		if (!ENTITY_PARAM(2, 1) && !ENTITY_PARAM(0, 1)) {
			getData()->inventoryItem = kItemNone;
			setCallback(17);
			call(new ENTITY_SETUP(Coudert, setup_function31), savepoint.param.intValue);
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function41, 41)
	error("Coudert: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter2, 42)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function18));
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityCoudert);

		getData()->entityPosition = kPosition_1500;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 5) = 0;
		ENTITY_PARAM(0, 6) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 2) = 0;
		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 5) = 0;
		ENTITY_PARAM(1, 6) = 0;
		ENTITY_PARAM(1, 7) = 0;
		ENTITY_PARAM(1, 8) = 0;

		ENTITY_PARAM(2, 4) = 0;

		getObjects()->updateLocation2(kObject111, kLocation5);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function43();
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function43, 43)
	error("Coudert: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter3, 44)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function18));
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityCoudert);

		getData()->entityPosition = kPosition_1500;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 5) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 2) = 0;
		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 4) = 0;
		ENTITY_PARAM(1, 5) = 0;
		ENTITY_PARAM(1, 6) = 0;
		ENTITY_PARAM(1, 7) = 0;
		ENTITY_PARAM(1, 8) = 0;

		ENTITY_PARAM(2, 4) = 0;
		ENTITY_PARAM(2, 5) = 0;

		getObjects()->updateLocation2(kObject111, kLocation6);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function45();
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function45, 45)
	error("Coudert: callback function 45 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function46, 46)
	error("Coudert: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION_I(Coudert, function47, 47)
	error("Coudert: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function48, 48)
	error("Coudert: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function49, 49)
	error("Coudert: callback function 49 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function50, 50)
	error("Coudert: callback function 50 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function51, 51)
	error("Coudert: callback function 51 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter4, 52)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function18));
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityCoudert);

		getData()->entityPosition = kPosition_1500;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 4) = 0;
		ENTITY_PARAM(0, 5) = 0;
		ENTITY_PARAM(0, 6) = 0;
		ENTITY_PARAM(0, 8) = 0;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 5) = 0;
		ENTITY_PARAM(1, 6) = 0;
		ENTITY_PARAM(1, 7) = 0;
		ENTITY_PARAM(1, 8) = 0;

		ENTITY_PARAM(2, 3) = 0;
		ENTITY_PARAM(2, 4) = 0;

		getObjects()->updateLocation2(kObject111, kLocation10);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			ENTITY_PARAM(1, 2) = 1;
			setup_function53();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function53, 53)
	error("Coudert: callback function 53 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function54, 54)
	error("Coudert: callback function 54 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function55, 55)
	error("Coudert: callback function 55 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function56, 56)
	error("Coudert: callback function 56 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, chapter5, 57)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityCoudert);

		getData()->entityPosition = kPosition_3969;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, chapter5Handler, 58)
	if (savepoint.action == kActionProceedChapter5)
		setup_function59();
}

IMPLEMENT_FUNCTION(Coudert, function59, 59)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_7500;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRedSleeping;

		getSound()->playSound(kEntityCoudert, "Jac5010"); // Situation is under control, please remain in your compartment

		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_2000);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->drawSequenceLeft(kEntityCoudert, "627K");
			setup_function60();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function60, 60)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function61();
		break;

	case kAction155991520:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function10), 225);
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function61, 61)
	error("Coudert: callback function 61 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function62, 62)
	error("Coudert: callback function 62 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Coudert, 63)

} // End of namespace LastExpress
