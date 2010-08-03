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

#include "lastexpress/entities/ivo.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/fight.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Ivo::Ivo(LastExpressEngine *engine) : Entity(engine, kEntityIvo) {
	ADD_CALLBACK_FUNCTION(Ivo, reset);
	ADD_CALLBACK_FUNCTION(Ivo, draw);
	ADD_CALLBACK_FUNCTION(Ivo, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Ivo, updateFromTime);
	ADD_CALLBACK_FUNCTION(Ivo, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Ivo, updateEntity);
	ADD_CALLBACK_FUNCTION(Ivo, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Ivo, playSound);
	ADD_CALLBACK_FUNCTION(Ivo, callbackActionOnSomebodyStandingInRestaurantOrSalon);
	ADD_CALLBACK_FUNCTION(Ivo, savegame);
	ADD_CALLBACK_FUNCTION(Ivo, function11);
	ADD_CALLBACK_FUNCTION(Ivo, sitAtTableWithSalko);
	ADD_CALLBACK_FUNCTION(Ivo, leaveTableWithSalko);
	ADD_CALLBACK_FUNCTION(Ivo, chapter1);
	ADD_CALLBACK_FUNCTION(Ivo, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Ivo, function16);
	ADD_CALLBACK_FUNCTION(Ivo, function17);
	ADD_CALLBACK_FUNCTION(Ivo, chapter2);
	ADD_CALLBACK_FUNCTION(Ivo, function19);
	ADD_CALLBACK_FUNCTION(Ivo, function20);
	ADD_CALLBACK_FUNCTION(Ivo, function21);
	ADD_CALLBACK_FUNCTION(Ivo, chapter3);
	ADD_CALLBACK_FUNCTION(Ivo, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Ivo, chapter4);
	ADD_CALLBACK_FUNCTION(Ivo, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Ivo, function26);
	ADD_CALLBACK_FUNCTION(Ivo, function27);
	ADD_CALLBACK_FUNCTION(Ivo, function28);
	ADD_CALLBACK_FUNCTION(Ivo, function29);
	ADD_CALLBACK_FUNCTION(Ivo, chapter5);
	ADD_CALLBACK_FUNCTION(Ivo, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Ivo, fight);
	ADD_CALLBACK_FUNCTION(Ivo, function33);
	ADD_CALLBACK_FUNCTION(Ivo, function34);
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Ivo, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Ivo, draw, 2)
	Entity::draw(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Ivo, enterExitCompartment, 3)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_I(Ivo, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

/**
 * Updates parameter 2 using ticks value
 *
 * @param param1 The number of ticks to add
 */
IMPLEMENT_FUNCTION_I(Ivo, updateFromTicks, 5)
	Entity::updateFromTicks(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Ivo, updateEntity, 6)
	if (savepoint.action == kActionExcuseMeCath || savepoint.action == kActionExcuseMe) {
		getSound()->playSound(kEntityPlayer, "CAT1127A");
		return;
	}

	Entity::updateEntity(savepoint);
}

/**
 * Process callback action when the entity direction is not kDirectionRight
 */
IMPLEMENT_FUNCTION(Ivo, callbackActionOnDirection, 7)
	Entity::callbackActionOnDirection(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_NOSETUP(Ivo, playSound, 8)
	Entity::playSound(savepoint, true);
}

/**
 * Process callback action when somebody is standing in the restaurant or salon.
 */
IMPLEMENT_FUNCTION(Ivo, callbackActionOnSomebodyStandingInRestaurantOrSalon, 9)
	Entity::callbackActionOnSomebodyStandingInRestaurantOrSalon(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Ivo, savegame, 10)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION(Ivo, function11, 11)
	error("Ivo: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, sitAtTableWithSalko, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->clearSequences(kEntitySalko);
		getSavePoints()->push(kEntityIvo, kEntityTables2, kAction136455232);

		CALLBACK_ACTION()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityIvo, "023A1");
		getEntities()->drawSequenceRight(kEntitySalko, "023A2");
		getEntities()->drawSequenceRight(kEntityTables2, "023A3");
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, leaveTableWithSalko, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getSavePoints()->push(kEntityIvo, kEntityTables2, kActionDrawTablesWithChairs, "009E");
		getEntities()->clearSequences(kEntitySalko);

		CALLBACK_ACTION()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityIvo, "023D1");
		getEntities()->drawSequenceRight(kEntitySalko, "023D2");
		getEntities()->drawSequenceRight(kEntityTables2, "023D3");
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter1, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentH, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject47, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->entityPosition = kPosition_4691;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;

		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter1Handler, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		getData()->entityPosition = getEntityData(kEntityMilos)->entityPosition;
		getData()->posture = getEntityData(kEntityMilos)->posture;
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Ivo, setup_function11));
			break;

		case 2:
			getSavePoints()->push(kEntityIvo, kEntityMilos, kAction135024800);
			setup_function16();
			break;
		}
		break;

	case kAction125242096:
		setCallback(1);
		call(new ENTITY_SETUP(Ivo, setup_updateFromTicks), 75);
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function16, 16)
	error("Ivo: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function17, 17)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_2740;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;

		getEntities()->clearSequences(kEntityIvo);
		getObjects()->update(kObjectCompartmentH, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter2, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK(kTime1777500, params->param1, setup_function19);
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityIvo);

		getData()->entityPosition = kPosition_2740;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentH, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject47, kEntityPlayer, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function19, 19)
	error("Ivo: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function20, 20)
	error("Ivo: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function21, 21)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_2740;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentH, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter3, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityIvo);

		getData()->entityPosition = kPosition_2740;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter3Handler, 23)
	if (savepoint.action == kActionDefault)
		getObjects()->update(kObjectCompartmentH, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
}

IMPLEMENT_FUNCTION(Ivo, chapter4, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter4Handler, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime2361600 && getEntities()->isSomebodyStandingInRestaurantOrSalon()) {
			getData()->posture = kPostureStanding;
			setup_function26();
		}
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityIvo, kEntityTables2, kAction136455232);
		getEntities()->drawSequenceLeft(kEntityIvo, "023B");
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function26, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Ivo, setup_leaveTableWithSalko));
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Ivo, setup_function11));
			break;

		case 2:
			setup_function27();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function27, 27)
	error("Ivo: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Ivo, function28, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime2425500 && !params->param1) {
			params->param1 = 1;
			setCallback(1);
			call(new ENTITY_SETUP(Ivo, setup_updateEntity), kCarRedSleeping, kPosition_2740);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Ivo, setup_enterExitCompartment), "613EH", kObjectCompartmentH);
			break;

		case 2:
			setup_function29();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function29, 29)
	if (savepoint.action == kActionDefault) {
		getEntities()->clearSequences(kEntityIvo);
		getObjects()->update(kObjectCompartmentH, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_2740;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter5, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityIvo);

		getData()->entityPosition = kPosition_540;
		getData()->posture = kPostureSitting;
		getData()->car = kCarBaggageRear;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, chapter5Handler, 31)
	if (savepoint.action == kActionProceedChapter5)
		setup_fight();
}

IMPLEMENT_FUNCTION(Ivo, fight, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->posture = kPostureStanding;
		getData()->entityPosition = kPosition_540;
		getData()->car = kCarBaggageRear;
		getData()->inventoryItem = kItemNone;

		setCallback(1);
		call(new ENTITY_SETUP(Ivo, setup_savegame), kSavegameType2, kEventCathIvoFight);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSound()->playSound(kEntityPlayer, "LIB090");
			getAction()->playAnimation(kEventCathIvoFight);

			setCallback(2);
			call(new ENTITY_SETUP(Ivo, setup_savegame), kSavegameType1, kTime0);
			break;

		case 2:
			params->param1 = getFight()->setup(kFightIvo);
			if (params->param1) {
				getLogic()->gameOver(kTimeType0, kTime0, kSceneNone, true);
			} else {
				getScenes()->loadSceneFromPosition(kCarBaggageRear, 96);
				setup_function33();
			}
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function33, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getState()->time += 1800;

		setCallback(1);
		call(new ENTITY_SETUP(Ivo, setup_savegame), kSavegameType1, kEventNone);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			getObjects()->update(kObject94, kEntityPlayer, kLocation2, kCursorKeepValue, kCursorKeepValue);

		break;

	case kAction135800432:
		setup_function34();
		break;
	}
}

IMPLEMENT_FUNCTION(Ivo, function34, 34)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityIvo);
}

} // End of namespace LastExpress
