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

#include "lastexpress/entities/salko.h"

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

Salko::Salko(LastExpressEngine *engine) : Entity(engine, kEntitySalko) {
	ADD_CALLBACK_FUNCTION(Salko, reset);
	ADD_CALLBACK_FUNCTION(Salko, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Salko, draw);
	ADD_CALLBACK_FUNCTION(Salko, updateEntity);
	ADD_CALLBACK_FUNCTION(Salko, updateFromTime);
	ADD_CALLBACK_FUNCTION(Salko, savegame);
	ADD_CALLBACK_FUNCTION(Salko, function7);
	ADD_CALLBACK_FUNCTION(Salko, function8);
	ADD_CALLBACK_FUNCTION(Salko, chapter1);
	ADD_CALLBACK_FUNCTION(Salko, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Salko, function11);
	ADD_CALLBACK_FUNCTION(Salko, chapter2);
	ADD_CALLBACK_FUNCTION(Salko, function13);
	ADD_CALLBACK_FUNCTION(Salko, chapter3);
	ADD_CALLBACK_FUNCTION(Salko, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Salko, function16);
	ADD_CALLBACK_FUNCTION(Salko, function17);
	ADD_CALLBACK_FUNCTION(Salko, chapter4);
	ADD_CALLBACK_FUNCTION(Salko, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Salko, function20);
	ADD_CALLBACK_FUNCTION(Salko, function21);
	ADD_CALLBACK_FUNCTION(Salko, function22);
	ADD_CALLBACK_FUNCTION(Salko, chapter5);
	ADD_CALLBACK_FUNCTION(Salko, chapter5Handler);
	ADD_NULL_FUNCTION();
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Salko, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Salko, enterExitCompartment, 2)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_NOSETUP(Salko, draw, 3)
	Entity::draw(savepoint);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(Salko, updateEntity, 4)
	Entity::updateEntity(savepoint);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_I(Salko, updateFromTime, 5)
	Entity::updateFromTime(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Salko, savegame, 6)
	Entity::savegame(savepoint);
}

// Parameters:
// - Car
// - EntityPosition
IMPLEMENT_FUNCTION_II(Salko, function7, 7)
	error("Salko: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Salko, function8, 8)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_2740;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter1, 9)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_4691;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter1Handler, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		getData()->entityPosition = getEntityData(kEntityIvo)->entityPosition;
		getData()->location = getEntityData(kEntityIvo)->location;
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->clearSequences(kEntitySalko);
			setup_function8();
		}
		break;

	case kAction125242096:
		setCallback(1);
		call(new ENTITY_SETUP(Salko, setup_function7), kCarRedSleeping, kPosition_2740);
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function11, 11)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_2740;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;

		getEntities()->clearSequences(kEntitySalko);
		getObjects()->update(kObjectCompartmentH, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Salko, chapter2, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntitySalko);

		getData()->entityPosition = kPosition_2740;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;

	case kAction136184016:
		setCallback(1);
		call(new ENTITY_SETUP(Salko, setup_function13));
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function13, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Salko, setup_enterExitCompartment), "612DH", kObjectCompartmentH);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Salko, setup_updateEntity), kCarRestaurant, kPosition_850);
			break;

		case 2:
			getSavePoints()->push(kEntitySalko, kEntityIvo, kAction102675536);
			getEntities()->clearSequences(kEntitySalko);
			break;

		case 3:
			getEntities()->drawSequenceLeft(kEntitySalko, "BLANK");
			getData()->location = kLocationInsideCompartment;

			setup_function8();
			break;
		}
		break;

	case kAction125242096:
		setCallback(3);
		call(new ENTITY_SETUP(Salko, setup_function7), kCarRedSleeping, kPosition_2740);
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter3, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntitySalko);

		getData()->entityPosition = kPosition_2740;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter3Handler, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time < kTime2200500) {
			UPDATE_PARAM(params->param1, getState()->time, 81000);

			setCallback(1);
			call(new ENTITY_SETUP(Salko, setup_function16));
		}
		break;

	case kActionCallback:
		if (getCallback() == 1)
			params->param1 = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function16, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->hasValidFrame(kEntitySalko) && getEntities()->isDistanceBetweenEntities(kEntitySalko, kEntityPlayer, 5000)) {
			getSavePoints()->push(kEntitySalko, kEntityMax, kAction158007856);

			setCallback(3);
			call(new ENTITY_SETUP(Salko, setup_updateFromTime), 75);
			break;
		}

label_callback3:
		UPDATE_PARAM(params->param1, getState()->time, 4500);

		getSavePoints()->push(kEntitySalko, kEntitySalko, kAction101169464);
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Salko, setup_enterExitCompartment), "612DH", kObjectCompartmentH);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->location = kLocationOutsideCompartment;

			if (getData()->entityPosition < kPosition_2087)
				getData()->entityPosition = kPosition_2088;

			setCallback(2);
			call(new ENTITY_SETUP(Salko, setup_updateEntity), kCarRedSleeping, kPosition_4070);
			break;

		case 2:
			break;

		case 3:
			getSavePoints()->push(kEntitySalko, kEntitySalko, kAction101169464);
			goto label_callback3;

		case 4:
			getEntities()->exitCompartment(kEntitySalko, kObjectCompartmentF, true);

			setCallback(5);
			call(new ENTITY_SETUP(Salko, setup_updateEntity), kCarRedSleeping, kPosition_9460);
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Salko, setup_updateFromTime), 4500);
			break;

		case 6:
			setCallback(7);
			call(new ENTITY_SETUP(Salko, setup_updateEntity), kCarRedSleeping, kPosition_2740);
			break;

		case 7:
			setCallback(8);
			call(new ENTITY_SETUP_SIIS(Salko, setup_enterExitCompartment), "612Ch", kObjectCompartmentH);
			break;

		case 8:
			getData()->location = kLocationInsideCompartment;
			getData()->entityPosition = kPosition_2740;
			getEntities()->clearSequences(kEntitySalko);

			CALLBACK_ACTION();
			break;
		}
		break;

	case kAction101169464:
		setCallback(4);
		call(new ENTITY_SETUP_SIIS(Salko, setup_enterExitCompartment), "612Bf", kObjectCompartmentF);
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function17, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_6470;
		getData()->location = kLocationOutsideCompartment;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		setCallback(1);
		call(new ENTITY_SETUP(Salko, setup_updateEntity), kCarGreenSleeping, kPosition_2740);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Salko, setup_enterExitCompartment), "612Ch", kObjectCompartmentH);
			break;

		case 2:
			getEntities()->clearSequences(kEntitySalko);
			getData()->entityPosition = kPosition_2740;
			getData()->location = kLocationInsideCompartment;
			getSavePoints()->push(kEntitySalko, kEntityMilos, kAction157691176);

			setup_chapter3Handler();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter4, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntitySalko);

		getData()->entityPosition = kPosition_5420;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter4Handler, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->drawSequenceLeft(kEntitySalko, "BLANK");

			getData()->location = kLocationInsideCompartment;

			setup_function20();
		}
		break;

	case kAction125242096:
		setCallback(1);
		call(new ENTITY_SETUP(Salko, setup_function7), kCarRedSleeping, kPosition_2740);
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->location = kLocationOutsideCompartment;
			if (getData()->entityPosition < kPosition_2087)
				getData()->entityPosition = kPosition_2088;

			setCallback(2);
			call(new ENTITY_SETUP(Salko, setup_updateEntity), kCarRestaurant, kPosition_850);
			break;

		case 2:
			getEntities()->clearSequences(kEntitySalko);
			setup_function21();
			break;
		}
		break;

	case kAction55996766:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Salko, setup_enterExitCompartment), "612Dh", kObjectCompartmentH);
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function21, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime2422800 && !params->param1) {
			params->param1 = 1;
			setCallback(1);
			call(new ENTITY_SETUP(Salko, setup_updateEntity), kCarRedSleeping, kPosition_2740);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Salko, setup_enterExitCompartment), "612Ch", kObjectCompartmentH);
			break;

		case 2:
			setup_function22();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, function22, 22)
	if (savepoint.action == kActionDefault) {
		getEntities()->clearSequences(kEntitySalko);
		getObjects()->update(kObjectCompartmentH, kEntityPlayer, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_2740;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter5, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntitySalko);

		getData()->entityPosition = kPosition_9460;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Salko, chapter5Handler, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (getSound()->isBuffered("MUS050"))
				getSound()->processEntry("MUS050");

			getAction()->playAnimation(kEventCathSalkoTrainTopFight);

			setCallback(2);
			call(new ENTITY_SETUP(Salko, setup_savegame), kSavegameTypeTime, kTimeNone);
			break;

		case 2:
			params->param1 = getFight()->setup(kFightSalko);

			if (params->param1 == Fight::kFightEndWin) {
				getState()->time += 1800;
				setCallback(3);
				call(new ENTITY_SETUP(Salko, setup_savegame), kSavegameTypeEvent, kEventCathSalkoTrainTopWin);
			} else {
				getLogic()->gameOver(kSavegameTypeIndex, 0, kSceneNone, params->param1 == Fight::kFightEndLost);
			}
			break;

		case 3:
			getAction()->playAnimation(kEventCathSalkoTrainTopWin);
			getSavePoints()->push(kEntitySalko, kEntityVesna, kAction134427424);

			getScenes()->loadSceneFromPosition(kCarRestaurant, 10);
			setup_nullfunction();
			break;
		}
		break;

	case kAction167992577:
		setCallback(1);
		call(new ENTITY_SETUP(Salko, setup_savegame), kSavegameTypeEvent, kEventCathSalkoTrainTopFight);
		break;
	}
}

IMPLEMENT_NULL_FUNCTION(Salko, 25)

} // End of namespace LastExpress
