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

#define SAVEGAME_BLOOD_JACKET() \
	if (getProgress().jacket == kJacketBlood \
		&& getEntities()->isDistanceBetweenEntities(kEntityCoudert, kEntityPlayer, 1000) \
		&& !getEntities()->isInsideCompartments(kEntityPlayer) \
		&& !getEntities()->checkFields10(kEntityPlayer)) { \
		setCallback(1); \
		call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameTypeEvent, kEventMertensBloodJacket); \
	}

Coudert::Coudert(LastExpressEngine *engine) : Entity(engine, kEntityCoudert) {
	ADD_CALLBACK_FUNCTION(Coudert, reset);
	ADD_CALLBACK_FUNCTION(Coudert, bloodJacket);
	ADD_CALLBACK_FUNCTION(Coudert, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Coudert, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Coudert, enterExitCompartment2);
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
	ADD_CALLBACK_FUNCTION(Coudert, visitCompartmentF);
	ADD_CALLBACK_FUNCTION(Coudert, function25);
	ADD_CALLBACK_FUNCTION(Coudert, function26);
	ADD_CALLBACK_FUNCTION(Coudert, function27);
	ADD_CALLBACK_FUNCTION(Coudert, visitCompartmentB);
	ADD_CALLBACK_FUNCTION(Coudert, visitCompartmentA);
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
		SAVEGAME_BLOOD_JACKET();
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
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
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
		SAVEGAME_BLOOD_JACKET();
		return;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
		}
		return;
	}

	Entity::enterExitCompartment(savepoint);
}

/**
 * Process callback action when the entity direction is not kDirectionRight
 */
IMPLEMENT_FUNCTION(Coudert, callbackActionOnDirection, 4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getData()->direction != kDirectionRight) {
			CALLBACK_ACTION();
			break;
		}

		SAVEGAME_BLOOD_JACKET();
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION();
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 * @param param5 The entity position 1
 * @param param6 The entity position 2
 */
IMPLEMENT_FUNCTION_SIII(Coudert, enterExitCompartment2, 5)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		SAVEGAME_BLOOD_JACKET();
		return;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
		}
		return;
	}

	Entity::enterExitCompartment(savepoint, (EntityPosition)params->param5, (EntityPosition)params->param6, kCarRedSleeping, (ObjectIndex)params->param4, false);
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
		SAVEGAME_BLOOD_JACKET();
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
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
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
		SAVEGAME_BLOOD_JACKET();
		break;

	case kAction2:
		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getSound()->playSound(kEntityCoudert, (char *)&params->seq1, SoundManager::kFlagDefault);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
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
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param3 && getEntities()->isDistanceBetweenEntities(kEntityCoudert, kEntityPlayer, 2000))
			getData()->inventoryItem = kItemInvalid;
		else
			getData()->inventoryItem = kItemNone;

		if (getProgress().jacket != kJacketBlood
		 || !getEntities()->isDistanceBetweenEntities(kEntityCoudert, kEntityPlayer, 1000)
		 || getEntities()->isInsideCompartments(kEntityPlayer)
		 || getEntities()->checkFields10(kEntityPlayer)) {
			if (getEntities()->updateEntity(kEntityCoudert, (CarIndex)params->param1, (EntityPosition)params->param2)) {
				getData()->inventoryItem = kItemNone;

				CALLBACK_ACTION();
			}
			break;
		}

		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameTypeEvent, kEventMertensBloodJacket);
		break;

	case kAction1:
		params->param3 = 0;
		getData()->inventoryItem = kItemNone;

		setCallback(2);
		call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameTypeEvent, kEventCoudertAskTylerCompartment);
		break;

	case kActionExcuseMeCath:
		if (getData()->clothes == kClothes1)
			getSound()->playSound(kEntityPlayer, "ZFX1003", getSound()->getSoundFlag(kEntityCoudert));
		else if (!getSound()->isBuffered(kEntityCoudert))
			getSound()->playSound(kEntityPlayer, "JAC1112", getSound()->getSoundFlag(kEntityCoudert));
		break;

	case kActionExcuseMe:
		if (getData()->clothes == kClothes1)
			getSound()->playSound(kEntityPlayer, "ZFX1003", getSound()->getSoundFlag(kEntityCoudert));
		else
			getSound()->excuseMe(kEntityCoudert);
		break;

	case kActionDefault:
		if (!getProgress().eventCorpseFound && !getEvent(kEventCoudertAskTylerCompartment))
			params->param3 = kItemInvalid;

		if (getEntities()->updateEntity(kEntityCoudert, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION();
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
			break;

		case 2:
			getAction()->playAnimation(kEventCoudertAskTylerCompartment);

			if (getData()->direction != kDirectionUp)
				getEntities()->loadSceneFromEntityPosition(getData()->car, (EntityPosition)(getData()->entityPosition + 750));
			else
				getEntities()->loadSceneFromEntityPosition(getData()->car, (EntityPosition)(getData()->entityPosition - 750), true);
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - Time
IMPLEMENT_FUNCTION_I(Coudert, function10, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		SAVEGAME_BLOOD_JACKET();

		UPDATE_PARAM(params->param2, getState()->time, params->param1);

		CALLBACK_ACTION();
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
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
		SAVEGAME_BLOOD_JACKET();

		UPDATE_PARAM(params->param2, getState()->timeTicks, params->param1);

		CALLBACK_ACTION();
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
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


	if (isNight()) {
		if (Entities::isFemale((EntityIndex)params->param1)) {
			getSound()->playSound(kEntityCoudert, Entities::isMarried((EntityIndex)params->param1) ? "JAC1112C" : "JAC1112F");
		} else {
			if (!params->param1 && getProgress().field_18 == 2) {
				switch (rnd(4)) {
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
		if (Entities::isFemale((EntityIndex)params->param1))
			getSound()->playSound(kEntityCoudert, Entities::isMarried((EntityIndex)params->param1) ? "JAC1112B" : "JAC1112G");
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
		SAVEGAME_BLOOD_JACKET();

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

			if (params->param4 < getState()->timeTicks) {
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
		call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameTypeEvent, kEventCoudertAskTylerCompartment);
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
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
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
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		SAVEGAME_BLOOD_JACKET();
		break;

	case kActionDefault:
		if (ENTITY_PARAM(2, 1)) {
			ENTITY_PARAM(2, 1) = 0;

			setCallback(3);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_1500);
		} else {
			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_function10), 15);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityCoudert, (EntityIndex)params->param1, kAction202558662);

			setCallback(2);
			call(new ENTITY_SETUP(Coudert, setup_function17), false);
			break;

		case 2:
			getSavePoints()->push(kEntityCoudert, (EntityIndex)params->param1, kAction155853632);
			getEntities()->drawSequenceLeft(kEntityCoudert, "627K");
			break;

		case 3:
			getSavePoints()->push(kEntityCoudert, (EntityIndex)params->param1, kAction202558662);
			getSavePoints()->push(kEntityCoudert, (EntityIndex)params->param1, kAction155853632);
			getEntities()->drawSequenceLeft(kEntityCoudert, "627K");
			getScenes()->loadSceneFromItemPosition(kItem5);
			break;

		case 4:
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
			break;

		case 5:
			CALLBACK_ACTION();
			break;
		}
		break;

	case kAction125499160:
		switch (params->param1) {
		default:
			break;

		case kEntityVerges:
			ENTITY_PARAM(0, 3) = 0;
			break;

		case kEntityMmeBoutarel:
			ENTITY_PARAM(0, 4) = 0;
			break;

		case kEntityMertens:
			ENTITY_PARAM(0, 5) = 0;
			break;
		}

		setCallback(5);
		call(new ENTITY_SETUP(Coudert, setup_function19), false);
		break;
	}
}

IMPLEMENT_FUNCTION_I(Coudert, function15, 15)
	error("Coudert: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function16, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (ENTITY_PARAM(2, 1)) {
			ENTITY_PARAM(2, 1) = 0;
			getInventory()->setLocationAndProcess(kItem5, kLocation1);

			CALLBACK_ACTION();
			break;
		}

		setCallback(ENTITY_PARAM(0, 2) ? 1 : 2);
		call(new ENTITY_SETUP_SIIS(Coudert, setup_bloodJacket), ENTITY_PARAM(0, 2) ? "627C" : "627F");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			getInventory()->setLocationAndProcess(kItem5, kLocation1);
			if (!getEntities()->isPlayerPosition(kCarRedSleeping, 2))
				getData()->entityPosition = kPosition_2088;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
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
		call(new ENTITY_SETUP(Coudert, setup_callbackActionOnDirection));
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
			ENTITY_PARAM(2, 1) = 1;
			CALLBACK_ACTION();
			break;
		}

		if (params->param1)
			getEntities()->drawSequenceRight(kEntityCoudert, "697H");
		else
			getEntities()->drawSequenceRight(kEntityCoudert, ENTITY_PARAM(0, 2) ? "627A" : "627D");

		getScenes()->loadSceneFromItemPosition(kItem5);

		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_callbackActionOnDirection));
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

/**
 * ??
 *
 * @param param1 The first object index
 * @param param2 The second object index
 */
IMPLEMENT_FUNCTION_II(Coudert, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!CURRENT_PARAMS(1, 3))
			CURRENT_PARAMS(1, 3) = getState()->time + 300;

		if (CURRENT_PARAMS(1, 3) < getState()->time) {
			CURRENT_PARAMS(1, 3) = kTimeInvalid;

			getSound()->playSound(kEntityPlayer, "ZFX1004", getSound()->getSoundFlag(kEntityCoudert));
		}

		UPDATE_PARAM(CURRENT_PARAMS(1, 4), getState()->time, 900);

		getObjects()->updateLocation2((ObjectIndex)params->param1, kLocation1);

		if (params->param4 != kLocation2)
			getObjects()->update((ObjectIndex)params->param1, (EntityIndex)params->param3, (ObjectLocation)params->param4, (CursorStyle)params->param5, (CursorStyle)params->param6);

		if (params->param2)
			getObjects()->update((ObjectIndex)params->param2, (EntityIndex)params->param7, (ObjectLocation)params->param8, (CursorStyle)CURRENT_PARAMS(1, 1), (CursorStyle)CURRENT_PARAMS(1, 2));

		CALLBACK_ACTION();
		break;

	case kActionKnock:
	case kActionOpenDoor:
		getObjects()->update((ObjectIndex)params->param1, kEntityCoudert, kLocation1, kCursorNormal, kCursorNormal);
		if (params->param2)
			getObjects()->update((ObjectIndex)params->param2, kEntityCoudert, kLocation1, kCursorNormal, kCursorNormal);

		setCallback(savepoint.action == kActionKnock ? 1 : 2);
		call(new ENTITY_SETUP_SIIS(Coudert, setup_playSound), savepoint.action == kActionKnock ? "LIB012" : "LIB013");
		break;

	case kActionDefault:
		params->param3 = getObjects()->get((ObjectIndex)params->param1).entity;
		params->param4 = getObjects()->get((ObjectIndex)params->param1).location;
		params->param5 = getObjects()->get((ObjectIndex)params->param1).cursor;
		params->param6 = getObjects()->get((ObjectIndex)params->param1).cursor2;

		if (params->param2) {
			params->param7 = getObjects()->get((ObjectIndex)params->param2).entity;
			params->param8 = getObjects()->get((ObjectIndex)params->param2).location;
			CURRENT_PARAMS(1, 1) = getObjects()->get((ObjectIndex)params->param2).cursor;
			CURRENT_PARAMS(1, 2) = getObjects()->get((ObjectIndex)params->param2).cursor2;

			getObjects()->update((ObjectIndex)params->param2, kEntityCoudert, kLocation1, kCursorHandKnock, kCursorHand);
		}

		if (params->param4 != kLocation2)
			getObjects()->update((ObjectIndex)params->param1, kEntityCoudert, kLocation1, kCursorHandKnock, kCursorHand);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			if (params->param1 == kObjectCompartmentA || params->param1 == kObjectCompartmentC
			 || params->param1 == kObjectCompartmentG || params->param1 == kObjectCompartmentH) {
				setCallback(3);
				call(new ENTITY_SETUP_SIIS(Coudert, setup_playSound), "Jac1001B");
			} else {
				setCallback(4);
				call(new ENTITY_SETUP_SIIS(Coudert, setup_playSound), "Jac1001A");
			}
			break;

		case 3:
		case 4:
			getObjects()->update((ObjectIndex)params->param1, kEntityCoudert, kLocation1, kCursorHandKnock, kCursorHand);

			if (params->param2)
				getObjects()->update((ObjectIndex)params->param2, kEntityCoudert, kLocation1, kCursorHandKnock, kCursorHand);
			break;
		}
		break;
	}
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

IMPLEMENT_FUNCTION(Coudert, visitCompartmentF, 24)
	visitCompartment(savepoint, kPosition_4070, "627Vf", kObjectCompartmentF, "627Wf", "627Zf", kPosition_4455, kObject53, "697Af");
}

IMPLEMENT_FUNCTION(Coudert, function25, 25)
	error("Coudert: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function26, 26)
	error("Coudert: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Coudert, function27, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param1) {
			UPDATE_PARAM(params->param2, getState()->timeTicks, 75);

			setCallback(3);
			call(new ENTITY_SETUP_SIII(Coudert, setup_enterExitCompartment2), "627Rc", kObjectCompartmentC, kPosition_6470, kPosition_6130);
		}
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_6470);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_enterExitCompartment), "627Mc", kObjectCompartmentC);
			break;

		case 2:
			getSavePoints()->push(kEntityCoudert, kEntityBoutarel, kAction221683008);
			getEntities()->drawSequenceLeft(kEntityCoudert, "627Nc");
			getEntities()->enterCompartment(kEntityCoudert, kObjectCompartmentC, true);
			break;

		case 3:
			getEntities()->exitCompartment(kEntityCoudert, kObjectCompartmentC, true);
			getData()->location = kLocationInsideCompartment;
			getEntities()->clearSequences(kEntityCoudert);

			setCallback(4);
			call(new ENTITY_SETUP(Coudert, setup_function20), kObjectCompartmentC, kObject50);
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_enterExitCompartment), "627Sc", kObjectCompartmentC);
			break;

		case 5:
			getData()->location = kLocationOutsideCompartment;
			CALLBACK_ACTION();
			break;

		case 6:
			getSavePoints()->push(kEntityCoudert, kEntityBoutarel, kAction122865568);
			break;

		case 7:
			getEntities()->exitCompartment(kEntityCoudert, kObjectCompartmentC, true);
			getData()->location = kLocationInsideCompartment;
			getEntities()->clearSequences(kEntityCoudert);

			setCallback(8);
			call(new ENTITY_SETUP(Coudert, setup_function20), kObjectCompartmentC, kObject50);
			break;

		case 8:
			getSound()->playSound(kEntityCoudert, "JAC1013");

			setCallback(9);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_enterExitCompartment), "627Uc", kObjectCompartmentC);
			break;

		case 9:
			getData()->location = kLocationOutsideCompartment;
			getSavePoints()->push(kEntityCoudert, kEntityBoutarel, kAction123852928);

			CALLBACK_ACTION();
			break;
		}
		break;

	case kAction88652208:
		setCallback(7);
		call(new ENTITY_SETUP_SIII(Coudert, setup_enterExitCompartment2), "627Rc", kObjectCompartmentC, kPosition_6470, kPosition_6130);
		break;

	case kAction123199584:
		params->param1 = 1;

		setCallback(6);
		call(new ENTITY_SETUP_SIIS(Coudert, setup_playSound), "JAC1012");
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, visitCompartmentB, 28)
	visitCompartment(savepoint, kPosition_7500, "627Vb", kObjectCompartmentB, "627Wb", "627Zb", kPosition_7850, kObject49, "697Ab");
}

IMPLEMENT_FUNCTION(Coudert, visitCompartmentA, 29)
	visitCompartment(savepoint, kPosition_8200, "627Ma", kObjectCompartmentA, "627Na", "627Ra", kPosition_7850, kObject48, "627Sa");
}

/**
 * ???
 *
 * @param param1 The compartment 
 */
IMPLEMENT_FUNCTION_I(Coudert, function30, 30)	
	// Expose parameters as IIIIIS and ignore the default exposed parameters
	EntityData::EntityParametersI5S  *parameters  = (EntityData::EntityParametersI5S*)_data->getCurrentParameters();
	EntityData::EntityParametersSIIS *parameters1 = (EntityData::EntityParametersSIIS*)_data->getCurrentParameters(1);

	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		switch (parameters->param1) {
		default:
			CALLBACK_ACTION();
			// Stop processing here
			return;

		case kObjectCompartmentA:
			parameters->param2 = kPosition_8200;
			parameters->param3 = kPosition_7850;
			strcpy((char *)&parameters->seq, "627Ma");
			strcpy((char *)&parameters1->seq1, "627Na");
			break;

		case kObjectCompartmentB:
			parameters->param2 = kPosition_7500;
			parameters->param3 = kPosition_7850;
			parameters->param4 = true;
			strcpy((char *)&parameters->seq, "627Vb");
			strcpy((char *)&parameters1->seq1, "627Wb");
			break;

		case kObjectCompartmentC:
			parameters->param2 = kPosition_6470;
			parameters->param3 = kPosition_6130;
			strcpy((char *)&parameters->seq, "627Mc");
			strcpy((char *)&parameters1->seq1, "627Nc");
			break;

		case kObjectCompartmentD:
			parameters->param2 = kPosition_5790;
			parameters->param3 = kPosition_6130;
			parameters->param4 = true;
			strcpy((char *)&parameters->seq, "627Vd");
			strcpy((char *)&parameters1->seq1, "627Wd");
			break;

		case kObjectCompartmentE:
			parameters->param2 = kPosition_4840;
			parameters->param3 = kPosition_4455;
			parameters->param4 = true;
			strcpy((char *)&parameters->seq, "627Me");
			strcpy((char *)&parameters1->seq1, "627Ne");
			break;

		case kObjectCompartmentF:
			parameters->param2 = kPosition_4070;
			parameters->param3 = kPosition_4455;
			parameters->param4 = true;
			strcpy((char *)&parameters->seq, "627Vf");
			strcpy((char *)&parameters1->seq1, "627Wf");
			break;
		}

		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function16));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, (EntityPosition)parameters->param2);
			break;

		case 2:
			if (getEntities()->checkFields19(kEntityPlayer, kCarRedSleeping, (EntityPosition)parameters->param3)
			 || ((parameters->param1 == kObjectCompartmentE || parameters->param1 == kObjectCompartmentF) && getEntities()->isOutsideAnnaWindow())) {
				getObjects()->update((ObjectIndex)parameters->param1, kEntityPlayer, getObjects()->get((ObjectIndex)parameters->param1).location, kCursorNormal, kCursorNormal);
				parameters->param5 = true;
			}

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_enterExitCompartment), (char *)&parameters->seq, (ObjectIndex)parameters->param1);
			break;

		case 3:
			getEntities()->drawSequenceLeft(kEntityCoudert, (char *)&parameters1->seq1);
			getEntities()->enterCompartment(kEntityCoudert, (ObjectIndex)parameters->param1, true);

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_playSound), parameters->param4 ? "JAC3020" : "JAC3021");
			break;

		case 4:
			if (parameters->param5)
				getObjects()->update((ObjectIndex)parameters->param1, kEntityPlayer, getObjects()->get((ObjectIndex)parameters->param1).location, kCursorHandKnock, kCursorHand);
			
			getEntities()->exitCompartment(kEntityCoudert, (ObjectIndex)parameters->param1, true);

			setCallback(5);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_2000);
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Coudert, setup_function18));
			break;

		case 6:
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION_I(Coudert, function31, 31)
	switch (savepoint.action) {
	default:
		break;

	case kAction2:
		setCallback(3);
		call(new ENTITY_SETUP(Coudert, setup_function19), true);
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Coudert, setup_bloodJacket), "627G");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (getSound()->isBuffered(kEntityCoudert)) {
				getEntities()->drawSequenceLeft(kEntityCoudert, "627K");
			} else {
				setCallback(2);
				call(new ENTITY_SETUP(Coudert, setup_function19), true);
			}
			break;

		case 2:
		case 3:
			CALLBACK_ACTION();
			break;
		}
		break;
	}
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
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (ENTITY_PARAM(0, 3) || ENTITY_PARAM(0, 4) || ENTITY_PARAM(0, 5) || ENTITY_PARAM(0, 6) || ENTITY_PARAM(0, 7)
		 || ENTITY_PARAM(1, 2) || ENTITY_PARAM(1, 7)
		 || ENTITY_PARAM(2, 2)) {
			ENTITY_PARAM(2, 6) = 1;

			if (ENTITY_PARAM(0, 3) || ENTITY_PARAM(0, 4) || ENTITY_PARAM(0, 5)) {
				setCallback(1);
				call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_1500);
			} else {
				setCallback(5);
				call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_540);
			}
		} else {
			CALLBACK_ACTION();
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			ENTITY_PARAM(2, 1) = 1;
			if (ENTITY_PARAM(0, 3)) {
				setCallback(2);
				call(new ENTITY_SETUP(Coudert, setup_function14), kEntityVerges);

				break;
			}
			// Fallback to next case

		case 2:
			if (ENTITY_PARAM(0, 5)) {
				setCallback(3);
				call(new ENTITY_SETUP(Coudert, setup_function14), kEntityMertens);

				break;
			}
			// Fallback to next case

		case 3:
			if (ENTITY_PARAM(0, 4)) {
				setCallback(4);
				call(new ENTITY_SETUP(Coudert, setup_function14), kEntityMmeBoutarel);

				break;
			}
			// Fallback to next case

		case 4:
			ENTITY_PARAM(2, 6) = 0;

			CALLBACK_ACTION();
			break;

		case 5:
			getEntities()->clearSequences(kEntityCoudert);

			setCallback(6);
			call(new ENTITY_SETUP(Coudert, setup_function10), 75);
			break;

		case 6:
			if (ENTITY_PARAM(0, 6) || ENTITY_PARAM(0, 7)) {
				setCallback(7);
				call(new ENTITY_SETUP(Coudert, setup_function37));

				break;
			}
			// Fallback to next case

		case 7:
			if (ENTITY_PARAM(2, 2)) {
				setCallback(8);
				call(new ENTITY_SETUP(Coudert, setup_function39));

				break;
			}
			// Fallback to next case

		case 8:
			if (ENTITY_PARAM(1, 2)) {
				setCallback(9);
				call(new ENTITY_SETUP(Coudert, setup_function55));

				break;
			}
			// Fallback to next case

		case 9:
			if (ENTITY_PARAM(1, 7)) {
				setCallback(10);
				call(new ENTITY_SETUP(Coudert, setup_function34), false);

				break;
			}
			// Fallback to next case

		case 10:
			ENTITY_PARAM(2, 6) = 0;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
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
		getData()->location = kLocationOutsideCompartment;
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
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (getSound()->isBuffered(kEntityCoudert))
			getSound()->processEntry(kEntityCoudert);

		if (ENTITY_PARAM(0, 7)) {
			getData()->entityPosition = kPosition_8200;

			setCallback(4);
			call(new ENTITY_SETUP_SIII(Coudert, setup_enterExitCompartment2), "698Ha", kObjectCompartmentA, kPosition_8200, kPosition_7850);
		} else {
			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_function16));
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_5790);
			break;

		case 2:
			getSavePoints()->push(kEntityCoudert, kEntityAnna, kAction238358920);
			setCallback(3);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_8200);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP_SIII(Coudert, setup_enterExitCompartment2), "698Ha", kObjectCompartmentA, kPosition_8200, kPosition_7850);
			break;

		case 4:
			getObjects()->update(kObjectCompartmentA, kEntityPlayer, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getData()->location = kLocationInsideCompartment;
			getEntities()->clearSequences(kEntityCoudert);
			setup_function38();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Coudert, function38, 38)
switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->car = kCarRedSleeping;
		getData()->entityPosition = kPosition_8200;
		getData()->location = kLocationInsideCompartment;
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
		getData()->location = kLocationOutsideCompartment;
		getObjects()->update(kObjectCompartment4, kEntityPlayer, kLocationNone, kCursorHandKnock, kCursorHand);

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
			getSound()->playSound(kEntityCoudert, rnd(2) ? "JAC1065" : "JAC1065A");

		if (getState()->time > kTime1107000 && !ENTITY_PARAM(0, 1) && !getEvent(kEventVassiliSeizure)) {
			getData()->inventoryItem = kItemNone;

			setCallback(10);
			call(new ENTITY_SETUP(Coudert, setup_function41));
			break;
		}

label_callback_10:
		if (getState()->time > kTime1189800 && !ENTITY_PARAM(0, 1) && !ENTITY_PARAM(2, 1)) {
			UPDATE_PARAM_GOTO(params->param3, getState()->time, 2700, label_coudert_object);

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
		call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameTypeEvent, kEventCoudertAskTylerCompartment);
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
		getData()->location = kLocationOutsideCompartment;

		getScenes()->loadSceneFromItemPosition(kItem5);
		break;

	case kActionDrawScene:
		if (!ENTITY_PARAM(2, 1) && !ENTITY_PARAM(0, 1)) {

			if (!getEntities()->isPlayerPosition(kCarRedSleeping, 1) && !getEntities()->isPlayerPosition(kCarRedSleeping, 23))
				break;

			if (getProgress().jacket == kJacketBlood) {
				setCallback(1);
				call(new ENTITY_SETUP(Coudert, setup_savegame), kSavegameTypeEvent, kEventCoudertBloodJacket);
			} else {
				setCallback(getEntities()->isPlayerPosition(kCarRedSleeping, 1) ? 2 : 3);
				call(new ENTITY_SETUP(Coudert, setup_function13), true, kEntityPlayer);
			}
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventCoudertBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
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
			call(new ENTITY_SETUP(Coudert, setup_callbackActionOnDirection));
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
			call(new ENTITY_SETUP(Coudert, setup_visitCompartmentA));
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Coudert, setup_function33));
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Coudert, setup_visitCompartmentB));
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP(Coudert, setup_function33));
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Coudert, setup_function27));
			break;

		case 6:
			getSavePoints()->push(kEntityCoudert, kEntityRebecca, kAction285528346);

			setCallback(7);
			call(new ENTITY_SETUP(Coudert, setup_function33));
			break;

		case 7:
			setCallback(8);
			call(new ENTITY_SETUP(Coudert, setup_function26));
			break;

		case 8:
			setCallback(9);
			call(new ENTITY_SETUP(Coudert, setup_function33));
			break;

		case 9:
			setCallback(10);
			call(new ENTITY_SETUP(Coudert, setup_function25));
			break;

		case 10:
			setCallback(11);
			call(new ENTITY_SETUP(Coudert, setup_function33));
			break;

		case 11:
			setCallback(12);
			call(new ENTITY_SETUP(Coudert, setup_function23));
			break;

		case 12:
			setCallback(13);
			call(new ENTITY_SETUP(Coudert, setup_function33));
			break;

		case 13:
			setCallback(14);
			call(new ENTITY_SETUP(Coudert, setup_function22));
			break;

		case 14:
			setCallback(15);
			call(new ENTITY_SETUP(Coudert, setup_function33));
			break;

		case 15:
			setCallback(16);
			call(new ENTITY_SETUP(Coudert, setup_function21));
			break;

		case 16:
			setCallback(17);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_2000);
			break;

		case 17:
			setCallback(18);
			call(new ENTITY_SETUP(Coudert, setup_function18));
			break;

		case 18:
			getSavePoints()->push(kEntityCoudert, kEntityMilos, kAction208228224);

			CALLBACK_ACTION();
			break;
		}
		break;
	}
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
		getData()->location = kLocationOutsideCompartment;
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
		getData()->location = kLocationOutsideCompartment;
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
			getSound()->playSound(kEntityCoudert, "Ann3148A");
			setCallback(2);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_4070);
			break;

		case 2:
			getSound()->playSound(kEntityCoudert, rnd(2) ? "Ann3148B" : "Ann3148");
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_enterExitCompartment), "627Xf", kObjectCompartmentF);
			break;

		case 3:
			getSavePoints()->push(kEntityCoudert, kEntityAnna, kAction192063264);
			setCallback(4);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_2000);
			break;

		case 4:
			ENTITY_PARAM(1, 8) = 0;
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
		getData()->location = kLocationOutsideCompartment;
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
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (getEntities()->hasValidFrame(kEntityCoudert)) {
			getData()->location = kLocationOutsideCompartment;

			setCallback(1);
			call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_540);
		} else {
			getData()->car = kCarLocomotive;
			getData()->entityPosition = kPosition_540;
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->clearSequences(kEntityCoudert);
			getData()->car = kCarLocomotive;
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Coudert, setup_function18));
			break;

		case 3:
			CALLBACK_ACTION();
			break;
		}
		break;

	case kAction191001984:
		getData()->car = kCarRedSleeping;
		setCallback(2);
		call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, kPosition_1500);
	}
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
		getData()->location = kLocationInsideCompartment;
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
		getData()->location = kLocationOutsideCompartment;
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

void Coudert::visitCompartment(const SavePoint &savepoint, EntityPosition position, const char* seq1, ObjectIndex compartment, const char* seq2, const char* seq3, EntityPosition sittingPosition, ObjectIndex object, const char* seq4) {
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)

	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Coudert, setup_function9), kCarRedSleeping, position);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_enterExitCompartment), seq1, compartment);
			break;

		case 2:
			getEntities()->drawSequenceLeft(kEntityCoudert, seq2);
			getEntities()->enterCompartment(kEntityCoudert, compartment, true);

			setCallback(3);
			call(new ENTITY_SETUP(Coudert, setup_function10), 150);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP_SIII(Coudert, setup_enterExitCompartment2), seq3, compartment, position, sittingPosition);
			break;

		case 4:
			getEntities()->exitCompartment(kEntityCoudert, compartment, true);
			getData()->location = kLocationInsideCompartment;
			getEntities()->clearSequences(kEntityCoudert);

			setCallback(5);
			call(new ENTITY_SETUP(Coudert, setup_function20), compartment, object);
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP_SIIS(Coudert, setup_enterExitCompartment), seq4, compartment);
			break;

		case 6:
			getData()->location = kLocationOutsideCompartment;
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

} // End of namespace LastExpress
