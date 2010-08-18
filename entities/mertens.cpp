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
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/state.h"
#include "lastexpress/game/sound.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

#define SAVEGAME_BLOOD_JACKET() \
	if (getProgress().jacket == kJacketBlood \
	 && getEntities()->isDistanceBetweenEntities(kEntityMertens, kEntityPlayer, 1000) \
	 && !getEntities()->isInsideCompartments(kEntityPlayer) \
	 && !getEntities()->checkFields10(kEntityPlayer)) { \
		setCallback(1); \
		call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensBloodJacket); \
	}

Mertens::Mertens(LastExpressEngine *engine) : Entity(engine, kEntityMertens) {
	ADD_CALLBACK_FUNCTION(Mertens, reset);
	ADD_CALLBACK_FUNCTION(Mertens, bloodJacket);
	ADD_CALLBACK_FUNCTION(Mertens, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Mertens, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(Mertens, enterExitCompartment3);
	ADD_CALLBACK_FUNCTION(Mertens, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Mertens, playSound);
	ADD_CALLBACK_FUNCTION(Mertens, playSound16);
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
	ADD_CALLBACK_FUNCTION(Mertens, tylerCompartment);
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
	ADD_CALLBACK_FUNCTION(Mertens, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Mertens, function42);
	ADD_CALLBACK_FUNCTION(Mertens, chapter2);
	ADD_CALLBACK_FUNCTION(Mertens, function44);
	ADD_CALLBACK_FUNCTION(Mertens, chapter3);
	ADD_CALLBACK_FUNCTION(Mertens, function46);
	ADD_CALLBACK_FUNCTION(Mertens, chapter4);
	ADD_CALLBACK_FUNCTION(Mertens, function48);
	ADD_CALLBACK_FUNCTION(Mertens, function49);
	ADD_CALLBACK_FUNCTION(Mertens, chapter5);
	ADD_CALLBACK_FUNCTION(Mertens, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Mertens, function52);
	ADD_CALLBACK_FUNCTION(Mertens, function53);
	ADD_NULL_FUNCTION();
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Mertens, reset, 1)
	Entity::reset(savepoint);
}

IMPLEMENT_FUNCTION_S(Mertens, bloodJacket, 2)
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
		getEntities()->drawSequenceRight(kEntityMertens, (char *)&params->seq1);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventMertensBloodJacket);
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
IMPLEMENT_FUNCTION_SI(Mertens, enterExitCompartment, 3)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		SAVEGAME_BLOOD_JACKET();
		return;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
		}
		return;
	}

	Entity::enterExitCompartment(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Mertens, enterExitCompartment2, 4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		SAVEGAME_BLOOD_JACKET();
		return;

	case kAction4:
		getEntities()->exitCompartment(kEntityMertens, (ObjectIndex)params->param4);
		CALLBACK_ACTION();
		return;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
		}
		return;
	}

	Entity::enterExitCompartment(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 *
 * @note We are not using the shared function due to too many differences
 */
IMPLEMENT_FUNCTION_SIII(Mertens, enterExitCompartment3, 5)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		SAVEGAME_BLOOD_JACKET();
		break;

	case kActionExitCompartment:
		getEntities()->exitCompartment(_entityIndex, (ObjectIndex)params->param4);
		getData()->entityPosition = (EntityPosition)params->param5;
		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(_entityIndex, (char *)&params->seq);
		getEntities()->enterCompartment(_entityIndex, (ObjectIndex)params->param4);
		getData()->entityPosition = (EntityPosition)params->param5;

		if (getEntities()->isInsideCompartment(kEntityPlayer, kCarGreenSleeping, (EntityPosition)params->param5) || getEntities()->isInsideCompartment(kEntityPlayer, kCarGreenSleeping, (EntityPosition)params->param6)) {
			getAction()->playAnimation(isNight() ? kEventCathTurningNight : kEventCathTurningDay);
			getSound()->playSound(kEntityPlayer, "BUMP");
			getScenes()->loadSceneFromObject((ObjectIndex)params->param4);
		}
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

/**
 * Process callback action when the entity direction is not kDirectionRight
 */
IMPLEMENT_FUNCTION(Mertens, callbackActionOnDirection, 6)
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
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Mertens, playSound, 7)
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
		getSound()->playSound(kEntityMertens, (char *)&params->seq1);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Mertens, playSound16, 8)
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
		getSound()->playSound(kEntityMertens, (char *)&params->seq1, SoundManager::kFlagDefault);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventMertensBloodJacket);
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
IMPLEMENT_FUNCTION_II(Mertens, savegame, 9)
	Entity::savegame(savepoint);
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - CarIndex
//  - EntityPosition
IMPLEMENT_FUNCTION_II(Mertens, function10, 10)

#define LOADSCENE_FROM_POSITION() \
	if (getData()->direction != kDirectionUp) { \
		getEntities()->loadSceneFromEntityPosition(getData()->car, (EntityPosition)(getData()->entityPosition + 750)); \
	} else { \
		getEntities()->loadSceneFromEntityPosition(getData()->car, (EntityPosition)(getData()->entityPosition - 750), true); \
	}

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param3 && getEntities()->isDistanceBetweenEntities(kEntityMertens, kEntityPlayer, 2000))
			getData()->inventoryItem = (InventoryItem)(getData()->inventoryItem | kItemInvalid);
		else
			getData()->inventoryItem = (InventoryItem)(getData()->inventoryItem & kItemToggleHigh);

		if (!getEntities()->isDistanceBetweenEntities(kEntityMertens, kEntityPlayer, 1000)
		  || getEntities()->isInsideCompartments(kEntityPlayer)
		  || getEntities()->checkFields10(kEntityPlayer)) {
			if (getEntities()->updateEntity(kEntityMertens, (CarIndex)params->param1, (EntityPosition)params->param2)) {
				getData()->inventoryItem = kItemNone;
				CALLBACK_ACTION();
			}
			break;
		}

		if (getProgress().jacket == kJacketBlood) {
			setCallback(1);
			call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensBloodJacket);
			break;
		}

		if ((ENTITY_PARAM(0, 6) || ENTITY_PARAM(0, 7)) && (!getEvent(kEventKronosConversation) && getProgress().jacket == kJacketGreen)) {
			setCallback(2);
			call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensKronosInvitation);
			break;
		}

		if (ENTITY_PARAM(1, 2) && getProgress().jacket == kJacketGreen && !getProgress().eventMetAugust) {
			setCallback(3);
			call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensAugustWaiting);
			break;
		}

		if (ENTITY_PARAM(2, 4) && getState()->time < kTime2133000) {
			setCallback(4);
			call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensKronosConcertInvitation);
			break;
		}

		if (getEntities()->updateEntity(kEntityMertens, (CarIndex)params->param1, (EntityPosition)params->param2)) {
			getData()->inventoryItem = kItemNone;
			CALLBACK_ACTION();
		}
		break;

	case kAction1:
		params->param3 = 0;
		if (getProgress().eventCorpseFound || getEvent(kEventMertensAskTylerCompartment) || getEvent(kEventMertensAskTylerCompartmentD)) {
			if (ENTITY_PARAM(0, 4) && getProgress().jacket == kJacketGreen && !getEvent(kEventMertensDontMakeBed) && !getProgress().eventCorpseThrown) {
				setCallback(6);
				call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensDontMakeBed);
			}
		} else {
			setCallback(5);
			call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensAskTylerCompartment);
		}
		break;

	case kActionExcuseMeCath:
		getSound()->playSound(kEntityMertens, "CON1110B");
		break;

	case kActionExcuseMe:
		getSound()->excuseMe(kEntityMertens);
		break;

	case kActionDefault:
		if ((!getProgress().eventCorpseFound && !getEvent(kEventMertensAskTylerCompartment) && !getEvent(kEventMertensAskTylerCompartment))
		 || (ENTITY_PARAM(0, 4) && getProgress().jacket == kJacketGreen && !getEvent(kEventMertensDontMakeBed) && !getProgress().eventCorpseThrown))
			params->param3 = 1;

		if (getEntities()->updateEntity(kEntityMertens, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION();
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
			break;

		case 2:
			getAction()->playAnimation(getData()->entityPosition < getEntityData(kEntityPlayer)->entityPosition ? kEventMertensKronosInvitation : kEventMertensKronosInvitationClosedWindows);
			getProgress().eventMertensKronosInvitation = true;

			ENTITY_PARAM(0, 6) = 0;
			ENTITY_PARAM(0, 7) = 0;

			if (params->param1 != 3 || (params->param2 != kPosition_8200 && params->param2 != kPosition_9510)) {
				LOADSCENE_FROM_POSITION();
				break;
			}

			getData()->inventoryItem = kItemNone;

			if (getData()->car == kCarGreenSleeping && getEntities()->checkDistanceFromPosition(kEntityMertens, kPosition_2000, 500))
				getData()->entityPosition = kPosition_2500;

			getEntities()->updateEntity(kEntityMertens, kCarGreenSleeping, kPosition_2000);
			getEntities()->loadSceneFromEntityPosition(getData()->car, (EntityPosition)(getData()->entityPosition + 750));

			CALLBACK_ACTION();
			break;

		case 3:
			getAction()->playAnimation(kEventMertensAugustWaiting);
			getProgress().eventMertensAugustWaiting = true;

			ENTITY_PARAM(1, 2) = 0;

			if (params->param1 == 3 && params->param2 == kPosition_8200) {
				if (getData()->car == kCarGreenSleeping && getEntities()->checkDistanceFromPosition(kEntityMertens, kPosition_2000, 500))
					getData()->entityPosition = kPosition_2500;

				getEntities()->updateEntity(kEntityMertens, kCarGreenSleeping, kPosition_2000);
				getEntities()->loadSceneFromEntityPosition(getData()->car, (EntityPosition)(getData()->entityPosition + 750));

				CALLBACK_ACTION();
				break;
			}

			LOADSCENE_FROM_POSITION();
			break;

		case 4:
			getAction()->playAnimation(kEventMertensKronosConcertInvitation);
			ENTITY_PARAM(2, 4) = 0;

			LOADSCENE_FROM_POSITION();
			break;

		case 5:
			getAction()->playAnimation(getData()->entityPosition < getEntityData(kEntityPlayer)->entityPosition ? kEventMertensAskTylerCompartmentD : kEventMertensAskTylerCompartment);
			LOADSCENE_FROM_POSITION();
			break;

		case 6:
			getAction()->playAnimation(kEventMertensDontMakeBed);
			LOADSCENE_FROM_POSITION();
			ENTITY_PARAM(0, 4) = 0;
			break;
		}
		break;
	}

#undef LOADSCENE_FROM_POSITION
}

IMPLEMENT_FUNCTION_I(Mertens, function11, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		SAVEGAME_BLOOD_JACKET();

		UPDATE_PARAM(params->param2, getState()->time, params->param1)

		CALLBACK_ACTION();
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
		}
		break;
	}
}

/**
 * Says "Bonsoir" to another character
 *
 * @param param1 The entity
 */
IMPLEMENT_FUNCTION_I(Mertens, bonsoir, 12)
	EntityIndex entity = (EntityIndex)params->param1;

	if (savepoint.action == kActionDefault)
		return;

	if (getSound()->isBuffered(kEntityMertens)) {
		CALLBACK_ACTION();
		return;
	}

	if (isNight()) {
		if (Entities::isFemale(entity)) {
			getSound()->playSound(kEntityMertens, rnd(2) ? "CON1112" : "CON1112A");
		} else {
			if (entity || getProgress().field_18 != 2) {
				getSound()->playSound(kEntityMertens, "CON1112F");
			} else {
				switch (rnd(3)) {
				default:
				case 0:
					getSound()->playSound(kEntityMertens, "CON1061");
					break;

				case 1:
					getSound()->playSound(kEntityMertens, "CON1110G");
					break;

				case 2:
					getSound()->playSound(kEntityMertens, "CON1110H");
					break;
				}
			}
		}
	} else {
		if (Entities::isFemale(entity))
			getSound()->playSound(kEntityMertens, rnd(2) ? "CON1112B" : "CON1112C");
		else
			getSound()->playSound(kEntityMertens, "CON1112G");
	}

	CALLBACK_ACTION();
}

/**
 * ??
 *
 * @param param1 true if ??, false otherwise
 * @param param2 The entity
 */
IMPLEMENT_FUNCTION_II(Mertens, function13, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		SAVEGAME_BLOOD_JACKET();

		if (!params->param2 && !params->param3) {
			if (!params->param4)
				params->param4 = getState()->timeTicks + 75;

			if (params->param4 < getState()->timeTicks) {
				params->param4 = kTimeInvalid;

				getData()->inventoryItem = kItemNone;
				setCallback(5);
				call(new ENTITY_SETUP(Mertens, setup_function18));
				break;
			}
		}

		if (!params->param5)
			params->param5 = getState()->timeTicks + 225;

		if (params->param5 < getState()->timeTicks) {
			params->param5 = kTimeInvalid;

			getData()->inventoryItem = kItemNone;
			setCallback(6);
			call(new ENTITY_SETUP(Mertens, setup_function18));
			break;
		}

		getData()->inventoryItem = (getProgress().chapter == kChapter1
		                         && !ENTITY_PARAM(2, 1)
								 && !getProgress().eventCorpseFound
								 && !getEvent(kEventMertensAskTylerCompartment)
								 && !getEvent(kEventMertensAskTylerCompartmentD)) ? kItemMatchBox : kItemNone;
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;
		setCallback(7);
		call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensAskTylerCompartmentD);
		break;

	case kAction11:
		params->param3++;
		setCallback(11);
		call(new ENTITY_SETUP(Mertens, setup_bonsoir), savepoint.entity2);
		break;

	case kActionDefault:
		if (params->param2)
			params->param3 = 1;

		if (!getSound()->isBuffered(kEntityMertens)) {

		}

		setCallback(3);
		call(new ENTITY_SETUP(Mertens, setup_function20));
		break;

	case kAction16:
		params->param3--;

		if (params->param2 && !params->param3) {
			getData()->inventoryItem = kItemNone;
			setCallback(10);
			call(new ENTITY_SETUP(Mertens, setup_function18));
		}
		break;

	case kActionDrawScene:
		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 23) && ENTITY_PARAM(0, 7) && !getEvent(kEventKronosConversation)) {
			setCallback(8);
			call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensKronosInvitation);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Mertens, setup_function20));
			break;

		case 3:
			getEntities()->drawSequenceLeft(kEntityMertens, params->param1 ? "601I" : "601H");
			break;

		case 4:
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneGameOverBloodJacket, true);
			break;

		case 5:
		case 6:
		case 9:
		case 10:
			CALLBACK_ACTION();
			break;

		case 7:
			getAction()->playAnimation(kEventMertensAskTylerCompartmentD);
			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 25);
			break;

		case 8:
			getAction()->playAnimation(kEventMertensKronosInvitation);
			ENTITY_PARAM(0, 6) = 0;
			ENTITY_PARAM(0, 7) = 0;
			getScenes()->processScene();

			if (!params->param3) {
				getData()->inventoryItem = kItemNone;
				setCallback(10);
				call(new ENTITY_SETUP(Mertens, setup_function18));
			}
			break;
		}
		break;
	}
}

// EntityIndex
IMPLEMENT_FUNCTION_I(Mertens, function14, 14)
	error("Mertens: callback function 14 not implemented!");
}

// bool
IMPLEMENT_FUNCTION_I(Mertens, function15, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		ENTITY_PARAM(1, 4) = 0;
		ENTITY_PARAM(1, 5) = 0;

		setCallback(1);
		call(new ENTITY_SETUP(Mertens, setup_function19));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_4070);
			break;

		case 2:
			getSound()->playSound(kEntityMertens, params->param1 ? "CON1059A" : "CON1059");

			setCallback(3);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_7500);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Mertens, setup_enterExitCompartment), "601Xb", kObjectCompartment2);
			break;

		case 4:
			getSavePoints()->push(kEntityMertens, kEntityAlexei, kAction135664192);

			setCallback(5);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_2000);
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Mertens, setup_function17));
			break;

		case 6:
			CALLBACK_ACTION();;
			break;
		}
		break;
	}
}

// bool
IMPLEMENT_FUNCTION_I(Mertens, function16, 16)
	error("Mertens: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function17, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		// FIXME: Check that we are using the correct parameter struct
		if (ENTITY_PARAM(0, 6) || ((EntityData::EntityParametersIIII*)_data->getParameters(8, 1))->hasNonNullParameter()) {
			getInventory()->setLocationAndProcess(kItem7, kLocation1);

			setCallback(1);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_540);
			break;
		}

		if (ENTITY_PARAM(0, 8)) {
			getEntities()->drawSequenceLeft(kEntityMertens, "601K");
			getScenes()->loadSceneFromItemPosition(kItem7);
			ENTITY_PARAM(2, 1) = 1;

			CALLBACK_ACTION();
			break;
		}

		// Mertens sits on his chair at the back of the train
		if (!getInventory()->hasItem(kItemPassengerList) || ENTITY_PARAM(0, 2)) {
			getEntities()->drawSequenceRight(kEntityMertens, "601A");
		} else {
			// Got the passenger list, Mertens is looking for it before sitting
			ENTITY_PARAM(0, 2) = 1;
			getSound()->playSound(kEntityMertens, "CON1058", SoundManager::kFlagInvalid, 75);
			getEntities()->drawSequenceRight(kEntityMertens, "601D");
		}

		getScenes()->loadSceneFromItemPosition(kItem7);

		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 68)) {
			getSound()->playSound(kEntityPlayer, "CON1110");
			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 25);
		}

		setCallback(3);
		call(new ENTITY_SETUP(Mertens, setup_callbackActionOnDirection));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->clearSequences(kEntityMertens);
			ENTITY_PARAM(2, 1) = 1;
			setCallback(2);
			call(new ENTITY_SETUP(Mertens, setup_function11), 75);
			break;

		case 2:
			CALLBACK_ACTION();
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
			getData()->inventoryItem = kItemNone;

			getSavePoints()->push(kEntityMertens, kEntityMertens, kActionDrawScene);

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function18, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (ENTITY_PARAM(0, 6)
		 || ENTITY_PARAM(1, 1)
		 || ENTITY_PARAM(1, 2)
		 || ENTITY_PARAM(1, 3)
		 || ENTITY_PARAM(1, 4)
		 || ENTITY_PARAM(1, 5)
		 || ENTITY_PARAM(1, 6)
		 || ENTITY_PARAM(1, 7)
		 || ENTITY_PARAM(1, 8)) {
			getInventory()->setLocationAndProcess(kItem7, kLocation1);
			ENTITY_PARAM(2, 1) = 1;

			CALLBACK_ACTION();
			break;
		}

		if (ENTITY_PARAM(0, 8)) {
			getScenes()->loadSceneFromItemPosition(kItem7);
			ENTITY_PARAM(2, 1) = 1;

			CALLBACK_ACTION();
			break;
		}

		if (!getInventory()->hasItem(kItemPassengerList) || ENTITY_PARAM(0, 2)) {
			getEntities()->drawSequenceRight(kEntityMertens, "601A");
		} else {
			ENTITY_PARAM(0, 2) = 1;
			getSound()->playSound(kEntityMertens, "CON1058", SoundManager::kFlagInvalid, 75);
			getEntities()->drawSequenceRight(kEntityMertens, "601D");
		}

		getScenes()->loadSceneFromItemPosition(kItem7);

		setCallback(1);
		call(new ENTITY_SETUP(Mertens, setup_callbackActionOnDirection));
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			if (!ENTITY_PARAM(0, 3)
			 && !getInventory()->hasItem(kItemPassengerList)
			 && ENTITY_PARAM(0, 2)) {
				getSavePoints()->push(kEntityMertens, kEntityVerges, kAction158617345);
				ENTITY_PARAM(0, 3) = 1;
			}

			getEntities()->drawSequenceLeft(kEntityMertens, "601B");
			ENTITY_PARAM(0, 1) = 0;
			getData()->inventoryItem = kItemNone;

			CALLBACK_ACTION();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function19, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (ENTITY_PARAM(2, 1)) {
			getInventory()->setLocationAndProcess(kItem7, kLocation1);
			ENTITY_PARAM(2, 1) = 0;
			CALLBACK_ACTION();
		} else {
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Mertens, setup_bloodJacket), "601C");
		}
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getInventory()->setLocationAndProcess(kItem7, kLocation1);

			if (!getEntities()->isPlayerPosition(kCarGreenSleeping, 2))
				getData()->entityPosition = kPosition_2088;

			CALLBACK_ACTION();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getScenes()->loadSceneFromItemPosition(kItem7);

		if (ENTITY_PARAM(2, 1)) {
			ENTITY_PARAM(2, 1) = 0;

			CALLBACK_ACTION();
		} else {
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Mertens, setup_bloodJacket), "601C");
		}
		break;

	case kActionCallback:
		if (getCallback() == 1)
			CALLBACK_ACTION();
		break;
	}
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

IMPLEMENT_FUNCTION_I(Mertens, tylerCompartment, 27)
	error("Mertens: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION_S(Mertens, function28, 28)
	error("Mertens: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION_SS(Mertens, function29, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param7 > 1 && params->param8) {
			getSavePoints()->push(kEntityMertens, kEntityCoudert, kAction125499160);

			setCallback(3);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_2000);
		}
		break;

	case kAction2:
		params->param7++;
		if (params->param7 == 1)
			getSound()->playSound(kEntityMertens, (char *)&params->seq2);
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Mertens, setup_function19));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarRedSleeping, kPosition_1500);
			break;

		case 2:
			getEntities()->drawSequenceLeft(kEntityMertens, "601O");
			getSavePoints()->push(kEntityMertens, kEntityCoudert, kAction154005632);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Mertens, setup_function17));
			break;

		case 4:
			CALLBACK_ACTION();
			break;
		}
		break;

	case kAction155853632:
		params->param8 = 1;
		break;

	case kAction202558662:
		getEntities()->drawSequenceLeft(kEntityMertens, "601L");
		getSound()->playSound(kEntityMertens, (char *)&params->seq1);
		break;
	}
}

IMPLEMENT_FUNCTION_I(Mertens, function30, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		switch (params->param1) {
		default:
			CALLBACK_ACTION();
			return;

		case 1:
			params->param2 = kPosition_8200;

			if (getProgress().field_14) {
				CALLBACK_ACTION();
				return;
			}

			getProgress().field_14 = 3;
			break;

		case 2:
			params->param2 = kPosition_7500;
			break;

		case 3:
			params->param2 = kPosition_6470;
			break;
		}

		setCallback(1);
		call(new ENTITY_SETUP(Mertens, setup_function19));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, params->param2);
			break;

		case 2:
			switch (params->param1) {
			default:
				if (getProgress().field_14 == 3)
					getProgress().field_14 = 0;

				setCallback(8);
				call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_2000);
				break;

			case 1:
				if (getProgress().chapter == kChapter4)
					getSavePoints()->push(kEntityMertens, kEntityTatiana, kAction238790488);

				setCallback(3);
				call(new ENTITY_SETUP(Mertens, setup_tylerCompartment), 3);
				break;

			case 2:
				if (getEntities()->isInsideCompartment(kEntityPlayer, kCarGreenSleeping, kPosition_7500)) {
					getObjects()->update(kObjectCompartment2, kEntityPlayer, getObjects()->get(kObjectCompartment2).location, kCursorNormal, kCursorNormal);
					params->param3 = 1;
				}

				setCallback(4);
				call(new ENTITY_SETUP_SIIS(Mertens, setup_enterExitCompartment), "601Vb", kObjectCompartment2);
				break;

			case 3:
				if (getEntities()->isInsideCompartment(kEntityPlayer, kCarGreenSleeping, kPosition_6470)) {
					getObjects()->update(kObjectCompartment3, kEntityPlayer, getObjects()->get(kObjectCompartment3).location, kCursorNormal, kCursorNormal);
					params->param3 = 1;
				}

				setCallback(6);
				call(new ENTITY_SETUP_SIIS(Mertens, setup_enterExitCompartment), "601Mc", kObjectCompartment3);
				break;
			}
			break;

		case 3:
			if (getProgress().field_14 == 3)
					getProgress().field_14 = 0;

			setCallback(8);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_2000);
			break;

		case 4:
			getEntities()->drawSequenceLeft(kEntityMertens, "601Wb");
			getEntities()->enterCompartment(kEntityMertens, kObjectCompartment2, true);

			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Mertens, setup_playSound), "CON3020");
			break;

		case 5:
			if (params->param3)
				getObjects()->update(kObjectCompartment2, kEntityPlayer, getObjects()->get(kObjectCompartment2).location, kCursorHandKnock, kCursorHand);

			getEntities()->exitCompartment(kEntityMertens, kObjectCompartment2);

			if (getProgress().field_14 == 3)
					getProgress().field_14 = 0;

			setCallback(8);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_2000);
			break;

		case 6:
			getEntities()->drawSequenceLeft(kEntityMertens, "601Nc");
			getEntities()->enterCompartment(kEntityMertens, kObjectCompartment3, true);

			setCallback(7);
			call(new ENTITY_SETUP_SIIS(Mertens, setup_playSound), "CON3020");
			break;

		case 7:
			if (params->param3)
				getObjects()->update(kObjectCompartment3, kEntityPlayer, getObjects()->get(kObjectCompartment3).location, kCursorHandKnock, kCursorHand);

			getEntities()->exitCompartment(kEntityMertens, kObjectCompartment3);

			if (getProgress().field_14 == 3)
					getProgress().field_14 = 0;

			setCallback(8);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_2000);
			break;

		case 8:
			setCallback(9);
			call(new ENTITY_SETUP(Mertens, setup_function17));
			break;

		case 9:
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION_I(Mertens, function31, 31)
	switch (savepoint.action) {
	default:
		break;

	case kAction2:
		setCallback(3);
		call(new ENTITY_SETUP(Mertens, setup_function17));
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Mertens, setup_bloodJacket), "601G");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (getSound()->isBuffered(kEntityMertens)) {
				getEntities()->drawSequenceLeft(kEntityMertens, "601J");
			} else {
				setCallback(2);
				call(new ENTITY_SETUP(Mertens, setup_function17));
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

IMPLEMENT_FUNCTION(Mertens, function32, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Mertens, setup_function19));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_9510);
			break;

		case 2:
			if (getData()->entityPosition >= kPosition_9460) {
				getEntities()->clearSequences(kEntityMertens);
				setCallback(3);
				call(new ENTITY_SETUP(Mertens, setup_function11), 900);
				break;
			}
			// Fallback to next case

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_2000);
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP(Mertens, setup_function17));
			break;

		case 5:
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function33, 33)
	error("Mertens: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter1, 34)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
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

		getData()->entityPosition = kPosition_9460;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarGreenSleeping;

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
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (!ENTITY_PARAM(0, 4)) {
			CALLBACK_ACTION();
			break;
		}

		if (getProgress().field_14 == 29) {
			CALLBACK_ACTION();
		} else {
			setCallback(1);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_8200);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (!ENTITY_PARAM(0, 4)) {
				CALLBACK_ACTION();
				break;
			}

			setCallback(2);
			call(new ENTITY_SETUP(Mertens, setup_tylerCompartment), 0);
			break;

		case 2:
			ENTITY_PARAM(0, 4) = 0;
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function39, 39)
	error("Mertens: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, function40, 40)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		ENTITY_PARAM(1, 3) = 0;
		setCallback(1);
		call(new ENTITY_SETUP(Mertens, setup_function19));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarKronos, kPosition_9460);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Mertens, setup_function11), 1800);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_1500);
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP(Mertens, setup_function17));
			break;

		case 5:
			ENTITY_PARAM(0, 6) = 1;
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, chapter1Handler, 41)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Mertens, setup_function10), kCarGreenSleeping, kPosition_2000);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Mertens, setup_function17));
			break;

		case 2:
			setup_function42();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function42, 42)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (ENTITY_PARAM(2, 3)) {
			ENTITY_PARAM(0, 1) = 1;
			ENTITY_PARAM(0, 6) = 0;
			ENTITY_PARAM(0, 7) = 0;
			ENTITY_PARAM(0, 8) = 0;

			ENTITY_PARAM(1, 1) = 0;
			ENTITY_PARAM(1, 2) = 0;
			ENTITY_PARAM(1, 3) = 0;
			ENTITY_PARAM(1, 4) = 0;
			ENTITY_PARAM(1, 5) = 0;
			ENTITY_PARAM(1, 6) = 0;
			ENTITY_PARAM(1, 7) = 0;

			ENTITY_PARAM(2, 1) = 0; // BUG: is set twice. Maybe a bug?
			ENTITY_PARAM(2, 2) = 0;
			ENTITY_PARAM(2, 3) = 0;

			params->param1 = 1;
			params->param2 = 1;

			getEntities()->drawSequenceLeft(kEntityMertens, "601E");
		}

		if (ENTITY_PARAM(2, 1) || getProgress().eventCorpseFound || getEvent(kEventMertensAskTylerCompartmentD) || getEvent(kEventMertensAskTylerCompartment))
			getData()->inventoryItem = kItemNone;
		else
			getData()->inventoryItem = kItemInvalid;

		if (!params->param2) {
			TIME_CHECK_SAVEPOINT(kTime1125000, params->param3, kEntityMertens, kEntityMahmud, kAction170483072);

			if (params->param4 != kTimeInvalid && getState()->time > kTimeCityChalons) {

				if (getState()->time <= kTime1188000) {
					if ((!getEntities()->isPlayerInCar(kCarGreenSleeping) && !getEntities()->isPlayerInCar(kCarRedSleeping))
					  || getSound()->isBuffered("REB1205")
					  || !getEntities()->isInsideCompartment(kEntityMmeBoutarel, kCarRedSleeping, kPosition_5790)
					  || !params->param4) {
						params->param4 = getState()->time;
					}

					if (params->param4 >= getState()->time)
						break;
				}

				ENTITY_PARAM(0, 4) = kTimeInvalid;
				getData()->inventoryItem = kItemNone;

				setCallback(8);
				call(new ENTITY_SETUP_SSII(Mertens, setup_function29), "CON1210", "CON1210A");
				break;
			}
		}

label_callback_8:
		if (getState()->time > kTime1215000 && !ENTITY_PARAM(0, 1) && !ENTITY_PARAM(2, 1)) {
			if (!params->param5)
				params->param5 = getState()->time + 2700;

			if (params->param5 < getState()->time) {
				getEntities()->drawSequenceLeft(kEntityMertens, "601E");
				ENTITY_PARAM(0, 1) = 1;
				params->param5 = 0;
			}
		}

		if (ENTITY_PARAM(0, 8)) {
			getData()->inventoryItem = kItemNone;
			setCallback(9);
			call(new ENTITY_SETUP(Mertens, setup_function14), kEntityVerges);
			break;
		}

		if (getProgress().field_14 == 29)
			goto label_callback_13;

label_callback_9:
		if (ENTITY_PARAM(1, 6)) {
			getData()->inventoryItem = kItemNone;
			setCallback(10);
			call(new ENTITY_SETUP(Mertens, setup_function16), true);
			break;
		}

label_callback_10:
		if (ENTITY_PARAM(1, 7)) {
			getData()->inventoryItem = kItemNone;
			setCallback(11);
			call(new ENTITY_SETUP(Mertens, setup_function16), false);
			break;
		}

label_callback_11:
		if (ENTITY_PARAM(1, 5)) {
			getData()->inventoryItem = kItemNone;
			setCallback(12);
			call(new ENTITY_SETUP(Mertens, setup_function15), true);
			break;
		}

label_callback_12:
		if (ENTITY_PARAM(1, 4)) {
			getData()->inventoryItem = kItemNone;
			setCallback(13);
			call(new ENTITY_SETUP(Mertens, setup_function15), false);
			break;
		}

label_callback_13:
		if (ENTITY_PARAM(1, 2)) {
			getData()->inventoryItem = kItemNone;
			setCallback(14);
			call(new ENTITY_SETUP(Mertens, setup_function35));
			break;
		}

label_callback_14:
		if (ENTITY_PARAM(0, 6)) {
			getData()->inventoryItem = kItemNone;
			setCallback(15);
			call(new ENTITY_SETUP(Mertens, setup_function36));
			break;
		}

label_callback_15:
		if (ENTITY_PARAM(1, 3)) {
			getData()->inventoryItem = kItemNone;
			setCallback(16);
			call(new ENTITY_SETUP(Mertens, setup_function40));
			break;
		}

label_callback_16:
		if (ENTITY_PARAM(1, 1)) {
			ENTITY_PARAM(1, 1) = 0;
			getData()->inventoryItem = kItemNone;
			setCallback(17);
			call(new ENTITY_SETUP_SIIS(Mertens, setup_function28), "CON1200");
			break;
		}

label_callback_17:
		if (ENTITY_PARAM(2, 2)) {
			ENTITY_PARAM(2, 2) = 0;
			getData()->inventoryItem = kItemNone;
			setCallback(18);
			call(new ENTITY_SETUP(Mertens, setup_function37));
			break;
		}

label_callback_18:
		if (!params->param1 && ENTITY_PARAM(0, 5)) {
			getData()->inventoryItem = kItemNone;
			setCallback(19);
			call(new ENTITY_SETUP(Mertens, setup_function39));
			break;
		}

label_callback_19:
		if (ENTITY_PARAM(0, 1) && !getSound()->isBuffered(kEntityMertens)) {
			if (getProgress().field_18 != 4)
				getSound()->playSound(kEntityMertens, "CON1505");
		}
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;
		setCallback(21);
		call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensAskTylerCompartmentD);
		break;

	case kAction11:
		if (!ENTITY_PARAM(0, 1) && !ENTITY_PARAM(2, 1)) {
			getData()->inventoryItem = kItemNone;
			setCallback(20);
			call(new ENTITY_SETUP(Mertens, setup_function13), savepoint.param.intValue, savepoint.entity2);
		}
		break;

	case kActionDefault:
		getData()->car = kCarGreenSleeping;
		getData()->entityPosition = kPosition_1500;
		getData()->location = kLocationOutsideCompartment;
		getScenes()->loadSceneFromItemPosition(kItem7);
		break;

	case kActionDrawScene:
		if (ENTITY_PARAM(2, 1))
			break;

		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 23) && ENTITY_PARAM(0, 7) && !getEvent(kEventKronosConversation)) {
			setCallback(1);
			call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensKronosInvitation);
			break;
		}

		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 23) && !getProgress().eventMertensKronosInvitation && !getEvent(kEventMertensLastCar) && !getEvent(kEventMertensLastCarOriginalJacket)) {
			setCallback(1);
			call(new ENTITY_SETUP(Mertens, setup_savegame), kSavegameTypeEvent, kEventMertensLastCar);
			break;
		}

label_callback_2_4:
		if ((getEntities()->isPlayerPosition(kCarGreenSleeping, 1) || getEntities()->isPlayerPosition(kCarGreenSleeping, 23)) && !ENTITY_PARAM(0, 1) && !ENTITY_PARAM(2, 1)) {
			getData()->inventoryItem = kItemNone;
			setCallback(getEntities()->isPlayerPosition(kCarGreenSleeping, 1) ? 5 : 6);
			call(new ENTITY_SETUP(Mertens, setup_function13), getEntities()->isPlayerPosition(kCarGreenSleeping, 1), kEntityPlayer);
			break;
		}

label_callback_5_6:
		if (getEntities()->isPlayerInCar(kCarGreenSleeping) && getData()->entityPosition < getEntityData(kEntityPlayer)->entityPosition) {
			if (getProgress().jacket == kJacketOriginal || ENTITY_PARAM(0, 7)) {
				getData()->inventoryItem = kItemNone;
				setCallback(7);
				call(new ENTITY_SETUP(Mertens, setup_function32));
			}
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventMertensKronosInvitation);
			getProgress().eventMertensKronosInvitation = true;
			ENTITY_PARAM(0, 6) = 0;
			ENTITY_PARAM(0, 7) = 0;
			getEntities()->drawSequenceRight(kEntityMertens, "601A");
			getScenes()->loadSceneFromItemPosition(kItem7);
			ENTITY_PARAM(0, 1) = 0;
			getData()->inventoryItem = kItemNone;

			setCallback(2);
			call(new ENTITY_SETUP(Mertens, setup_callbackActionOnDirection));
			break;

		case 2:
		case 4:
			getEntities()->drawSequenceLeft(kEntityMertens, "601B");
			goto label_callback_2_4;

		case 3:
			getAction()->playAnimation(getProgress().jacket == kJacketOriginal ? kEventMertensLastCarOriginalJacket : kEventMertensLastCar);
			getEntities()->drawSequenceRight(kEntityMertens, "601A");
			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 6);
			getScenes()->loadSceneFromItemPosition(kItem7);
			ENTITY_PARAM(0, 1) = 0;
			getData()->inventoryItem = kItemNone;

			setCallback(4);
			call(new ENTITY_SETUP(Mertens, setup_callbackActionOnDirection));
			break;

		case 5:
		case 6:
			goto label_callback_5_6;

		case 8:
			goto label_callback_8;

		case 9:
			goto label_callback_9;

		case 10:
			goto label_callback_10;

		case 11:
			goto label_callback_11;

		case 12:
			goto label_callback_12;

		case 13:
			goto label_callback_13;

		case 14:
			goto label_callback_14;

		case 15:
			goto label_callback_15;

		case 16:
			goto label_callback_16;

		case 17:
			goto label_callback_17;

		case 18:
			goto label_callback_18;

		case 19:
			params->param1 = 1;
			goto label_callback_19;

		case 21:
			getAction()->playAnimation(kEventMertensAskTylerCompartmentD);
			getEntities()->drawSequenceRight(kEntityMertens, "601A");
			getInventory()->get(kItem7)->location = kLocationNone;
			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 25);

			setCallback(22);
			call(new ENTITY_SETUP(Mertens, setup_callbackActionOnDirection));
			break;

		case 22:
			getEntities()->drawSequenceLeft(kEntityMertens, "601B");
			break;
		}
		break;

	case kAction225358684:
		if (!ENTITY_PARAM(0, 1)) {
			getData()->inventoryItem = kItemNone;
			setCallback(23);
			call(new ENTITY_SETUP(Mertens, setup_function30), savepoint.param.intValue);
		}
		break;

	case kAction225932896:
		if (!ENTITY_PARAM(2, 1) && !ENTITY_PARAM(0, 1))
			getSavePoints()->push(kEntityMertens, kEntityFrancois, kAction205346192);
		break;

	case kAction305159806:
		if (!ENTITY_PARAM(2, 1) && !ENTITY_PARAM(0, 1)) {
			getData()->inventoryItem = kItemNone;
			setCallback(24);
			call(new ENTITY_SETUP(Mertens, setup_function31), savepoint.param.intValue);
		}
		break;

	}
}

IMPLEMENT_FUNCTION(Mertens, chapter2, 43)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Mertens, setup_function17));
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityMertens);

		getData()->entityPosition = kPosition_1500;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarGreenSleeping;
		getData()->inventoryItem = kItemNone;

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

	case kActionCallback:
		if (getCallback() == 1)
			setup_function44();
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function44, 44)
	error("Mertens: callback function 44 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter3, 45)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Mertens, setup_function17));
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_1500;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarGreenSleeping;
		getData()->inventoryItem = kItemNone;

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

	case kActionCallback:
		if (getCallback() == 1)
			setup_function46();
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function46, 46)
	error("Mertens: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(Mertens, chapter4, 47)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Mertens, setup_function17));
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityMertens);

		getData()->entityPosition = kPosition_1500;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarGreenSleeping;
		getData()->inventoryItem = kItemNone;

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

	case kActionCallback:
		if (getCallback() == 1)
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
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityMertens);

		getData()->entityPosition = kPosition_3969;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, chapter5Handler, 51)
	if (savepoint.action == kActionProceedChapter5)
		setup_function52();
}

IMPLEMENT_FUNCTION(Mertens, function52, 52)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param2 == kTimeInvalid)
			break;

		if (params->param1 >= getState()->time) {

			if (!getEntities()->isPlayerInCar(kCarRedSleeping) || !params->param2)
				params->param2 = getState()->time;

			if (params->param2 >= getState()->time)
				break;
		}

		params->param2 = kTimeInvalid;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Mertens, setup_playSound), "Mme5010");
		break;

	case kActionDefault:
		getData()->car = kCarRedSleeping;
		getData()->entityPosition = kPosition_5790;
		getData()->location = kLocationInsideCompartment;

		getObjects()->update(kObjectCompartmentD, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);

		params->param1 = getState()->time + 4500;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Mertens, setup_enterExitCompartment), "671Ad", kObjectCompartmentD);
			break;

		case 2:
			getData()->location = kLocationOutsideCompartment;
			getSavePoints()->push(kEntityMertens, kEntityMmeBoutarel, kAction155604840);
			setup_function53();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Mertens, function53, 53)
	error("Mertens: callback function 53 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Mertens, 54)

} // End of namespace LastExpress
