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

#include "lastexpress/entities/vesna.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Vesna::Vesna(LastExpressEngine *engine) : Entity(engine, kEntityVesna) {
	ADD_CALLBACK_FUNCTION(Vesna, reset);
	ADD_CALLBACK_FUNCTION(Vesna, playSound);
	ADD_CALLBACK_FUNCTION(Vesna, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Vesna, draw);
	ADD_CALLBACK_FUNCTION(Vesna, updateEntity);
	ADD_CALLBACK_FUNCTION(Vesna, updateFromTime);
	ADD_CALLBACK_FUNCTION(Vesna, updateEntity2);
	ADD_CALLBACK_FUNCTION(Vesna, callbackActionRestaurantOrSalon);
	ADD_CALLBACK_FUNCTION(Vesna, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Vesna, savegame);
	ADD_CALLBACK_FUNCTION(Vesna, function11);
	ADD_CALLBACK_FUNCTION(Vesna, chapter1);
	ADD_CALLBACK_FUNCTION(Vesna, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Vesna, function14);
	ADD_CALLBACK_FUNCTION(Vesna, function15);
	ADD_CALLBACK_FUNCTION(Vesna, chapter2);
	ADD_CALLBACK_FUNCTION(Vesna, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Vesna, function18);
	ADD_CALLBACK_FUNCTION(Vesna, chapter3);
	ADD_CALLBACK_FUNCTION(Vesna, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Vesna, function21);
	ADD_CALLBACK_FUNCTION(Vesna, function22);
	ADD_CALLBACK_FUNCTION(Vesna, function23);
	ADD_CALLBACK_FUNCTION(Vesna, chapter4);
	ADD_CALLBACK_FUNCTION(Vesna, function25);
	ADD_CALLBACK_FUNCTION(Vesna, function26);
	ADD_CALLBACK_FUNCTION(Vesna, function27);
	ADD_CALLBACK_FUNCTION(Vesna, chapter5);
	ADD_CALLBACK_FUNCTION(Vesna, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Vesna, function30);
	ADD_NULL_FUNCTION();
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Vesna, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Vesna, playSound, 2)
	Entity::playSound(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Vesna, enterExitCompartment, 3)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Vesna, draw, 4)
	Entity::draw(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Vesna, updateEntity, 5)
	if (savepoint.action == kActionExcuseMeCath) {
		getSound()->playSound(kEntityPlayer, rnd(2) ? "CAT10150" : "CAT1015A");

		return;
	}

	Entity::updateEntity(savepoint, true);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_I(Vesna, updateFromTime, 6)
	Entity::updateFromTime(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Vesna, updateEntity2, 7)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		params->param3 = 0;

		if (getEntities()->checkFields9(kEntityVesna, kEntityMilos, 500)
		 || (((getData()->direction == kDirectionUp && (getData()->car > getEntityData(kEntityMilos)->car)) || (getData()->car == getEntityData(kEntityMilos)->car && getData()->entityPosition > getEntityData(kEntityMilos)->entityPosition)))
		 || (((getData()->direction == kDirectionDown && (getData()->car < getEntityData(kEntityMilos)->car)) || (getData()->car == getEntityData(kEntityMilos)->car && getData()->entityPosition < getEntityData(kEntityMilos)->entityPosition)))) {
			getData()->field_49B = 0;
			params->param3 = 1;
		}

		if (!params->param3)
			getEntities()->updateEntity(kEntityVesna, (CarIndex)params->param1, (EntityPosition)params->param2);
		break;

	case kActionDefault:
		getEntities()->updateEntity(kEntityVesna, (CarIndex)params->param1, (EntityPosition)params->param2);
		break;

	case kAction123668192:
		CALLBACK_ACTION();
		break;
	}
}

/**
 * Process callback action when somebody is standing in the restaurant or salon.
 */
IMPLEMENT_FUNCTION(Vesna, callbackActionRestaurantOrSalon, 8)
	Entity::callbackActionRestaurantOrSalon(savepoint);
}

/**
 * Process callback action when the entity direction is not kDirectionRight
 */
IMPLEMENT_FUNCTION(Vesna, callbackActionOnDirection, 9)
	Entity::callbackActionOnDirection(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Vesna, savegame, 10)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION(Vesna, function11, 11)
	// Expose parameters as IIIS and ignore the default exposed paremeters
	EntityData::EntityParametersIIIS *parameters = (EntityData::EntityParametersIIIS*)_data->getCurrentParameters(1);

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (parameters->param3) {
			UPDATE_PARAM(parameters->param7, getState()->timeTicks, 75);

			parameters->param2 = 1;
			parameters->param3 = 0;
			getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation1, kCursorNormal, kCursorNormal);
		}

		parameters->param7 = 0;
		break;

	case kActionKnock:
	case kActionOpenDoor:
		if (parameters->param3) {
			getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation3, kCursorNormal, kCursorNormal);

			setCallback(4);
			call(new ENTITY_SETUP_SIIS(Vesna, setup_playSound), getSound()->wrongDoorCath());
			break;
		}

		parameters->param1++;
		switch (parameters->param1) {
		default:
			strcpy((char *)&parameters->seq, "VES1015C");
			parameters->param1 = 0;
			break;

		case 1:
			strcpy((char *)&parameters->seq, "VES1015A");
			break;

		case 2:
			strcpy((char *)&parameters->seq, "VES1015B");
			break;
		}

		getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation3, kCursorNormal, kCursorNormal);

		setCallback(savepoint.action == kActionKnock ? 2 : 1);
		call(new ENTITY_SETUP_SIIS(Vesna, setup_playSound), savepoint.action == kActionKnock ? "LIB012" : "LIB013");
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation3, kCursorHandKnock, kCursorHand);
		break;

	case kActionDrawScene:
		if (parameters->param2 || parameters->param3) {
			getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation1, kCursorHandKnock, kCursorHand);

			parameters->param2 = 0;
			parameters->param3 = 0;
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Vesna, setup_playSound), (char *)&parameters->seq);
			break;

		case 3:
			getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation3, kCursorTalk, kCursorNormal);
			parameters->param3 = 1;
			break;

		case 4:
			parameters->param2 = 1;
			parameters->param3 = 0;
			break;
		}
		break;

	case kAction55996766:
	case kAction101687594:
		CALLBACK_ACTION();
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter1, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityVesna, kAction124190740, 0);

		getData()->entityPosition = kPosition_4689;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter1Handler, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		getData()->entityPosition = getEntityData(kEntityMilos)->entityPosition;
		getData()->posture = getEntityData(kEntityMilos)->posture;
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->clearSequences(kEntityVesna);
			setup_function14();
		}
		break;

	case kAction204832737:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_updateEntity2), kCarRedSleeping, kPosition_3050);
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function14, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_3050;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		break;

	case kAction190412928:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_function11));
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function15, 15)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_3050;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;

		getEntities()->clearSequences(kEntityVesna);
		getObjects()->update(kObjectCompartmentG, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter2, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVesna);

		getData()->entityPosition = kPosition_3050;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter2Handler, 17)
	switch (savepoint.action) {
	default:
		break;

	case kAction135024800:
		setCallback(2);
		call(new ENTITY_SETUP(Vesna, setup_function18));
		break;

	case kAction137165825:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_function11));
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function18, 18)
	error("Vesna: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, chapter3, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVesna);

		getData()->entityPosition = kPosition_3050;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter3Handler, 20)
	error("Vesna: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function21, 21)
	error("Vesna: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function22, 22)
	error("Vesna: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionKnock:
	case kActionOpenDoor:
		getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation3, kCursorNormal, kCursorNormal);
		setCallback(savepoint.action == kActionKnock ? 1 : 2);
		call(new ENTITY_SETUP_SIIS(Vesna, setup_playSound), savepoint.action == kActionKnock ? "LIB012" : "LIB013");
		break;

	case kActionDefault:
		getData()->car = kCarRedSleeping;
		getData()->entityPosition = kPosition_3050;
		getData()->posture = kPostureSitting;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Vesna, setup_playSound), "VES1015A");
			break;

		case 3:
			getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation3, kCursorHandKnock, kCursorHand);
			break;
		}
		break;

	case kAction203663744:
		getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation3, kCursorHandKnock, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter4, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_function11));
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVesna);

		getData()->entityPosition = kPosition_3050;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentG, kEntityVesna, kLocation3, kCursorHandKnock, kCursorHand);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function25();
	}
}

IMPLEMENT_FUNCTION(Vesna, function25, 25)
	error("Vesna: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Vesna, function26, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_callbackActionRestaurantOrSalon));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->car = kCarRestaurant;
			getData()->entityPosition = kPosition_5800;
			getData()->posture = kPostureStanding;

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Vesna, setup_draw), "808DD");
			break;

		case 2:
			getEntities()->drawSequenceRight(kEntityVesna, "808DS");

			if (getEntities()->isInRestaurant(kEntityPlayer))
				getEntities()->updateFrame(kEntityVesna);

			setCallback(3);
			call(new ENTITY_SETUP(Vesna, setup_callbackActionOnDirection));
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Vesna, setup_updateEntity), kCarRedSleeping, kPosition_3050);
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Vesna, setup_enterExitCompartment), "610AG", kObjectCompartmentG);
			break;

		case 5:
			setup_function27();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function27, 27)
	if (savepoint.action == kActionDefault) {
		getEntities()->clearSequences(kEntityVesna);
		getObjects()->update(kObjectCompartmentG, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_3050;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter5, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVesna);

		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, chapter5Handler, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionOpenDoor:
		setCallback(1);
		call(new ENTITY_SETUP(Vesna, setup_savegame), kSavegameTypeEvent, kEventCathVesnaRestaurantKilled);
		break;

	case kActionDefault:
		getObjects()->update(kObject64, kEntityVesna, kLocationNone, kCursorNormal, kCursorForward);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventCathVesnaRestaurantKilled);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneNone, true);
		}
		break;

	case kAction134427424:
		getObjects()->update(kObject64, kEntityPlayer, kLocationNone, kCursorNormal, kCursorForward);
		setup_function30();
		break;
	}
}

IMPLEMENT_FUNCTION(Vesna, function30, 30)
	error("Vesna: callback function 30 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(Vesna, 31)

} // End of namespace LastExpress
