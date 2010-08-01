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

#include "lastexpress/entities/francois.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Francois::Francois(LastExpressEngine *engine) : Entity(engine, kEntityFrancois) {
	ADD_CALLBACK_FUNCTION(Francois, reset);
	ADD_CALLBACK_FUNCTION(Francois, updateFromTime);
	ADD_CALLBACK_FUNCTION(Francois, draw);
	ADD_CALLBACK_FUNCTION(Francois, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Francois, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(Francois, playSound);
	ADD_CALLBACK_FUNCTION(Francois, savegame);
	ADD_CALLBACK_FUNCTION(Francois, function8);
	ADD_CALLBACK_FUNCTION(Francois, function9);
	ADD_CALLBACK_FUNCTION(Francois, function10);
	ADD_CALLBACK_FUNCTION(Francois, function11);
	ADD_CALLBACK_FUNCTION(Francois, function12);
	ADD_CALLBACK_FUNCTION(Francois, function13);
	ADD_CALLBACK_FUNCTION(Francois, function14);
	ADD_CALLBACK_FUNCTION(Francois, function15);
	ADD_CALLBACK_FUNCTION(Francois, function16);
	ADD_CALLBACK_FUNCTION(Francois, chapter1);
	ADD_CALLBACK_FUNCTION(Francois, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Francois, function19);
	ADD_CALLBACK_FUNCTION(Francois, function20);
	ADD_CALLBACK_FUNCTION(Francois, chapter2);
	ADD_CALLBACK_FUNCTION(Francois, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Francois, function23);
	ADD_CALLBACK_FUNCTION(Francois, chapter3);
	ADD_CALLBACK_FUNCTION(Francois, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Francois, chapter4);
	ADD_CALLBACK_FUNCTION(Francois, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Francois, chapter5);
	ADD_CALLBACK_FUNCTION(Francois, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Francois, function30);
	ADD_NULL_FUNCTION();
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Francois, reset, 1)
	Entity::reset(savepoint, true);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_I(Francois, updateFromTime, 2)
	Entity::updateFromTime(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Francois, draw, 3)
	Entity::draw(savepoint);
}

/**
 * Handles entering/exiting a compartment. 
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Francois, enterExitCompartment, 4)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Handles entering/exiting a compartment and updates position/play animation
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(Francois, enterExitCompartment2, 5)
	Entity::enterExitCompartment(savepoint, kPosition_5790, kPosition_6130, kCarRedSleeping, kObjectCompartmentD, true);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Francois, playSound, 6)
	Entity::playSound(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Francois, savegame, 7)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(Francois, function8, 8)
	error("Francois: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function9, 9)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (getObjects()->get(kObjectCompartmentD).location == kLocation2) {
			getObjects()->update(kObjectCompartmentD, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
			getSavePoints()->push(kEntityFrancois, kEntityMmeBoutarel, kAction134289824);
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Francois, setup_enterExitCompartment), "605Cd", kObjectCompartmentD);
		} else {
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Francois, setup_enterExitCompartment), "605Ed", kObjectCompartmentD);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentD, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			break;

		case 2:
			getData()->posture = kPostureStanding;
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Francois, function10, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (getObjects()->get(kObjectCompartmentD).location == kLocation2) {
			getObjects()->update(kObjectCompartmentD, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Francois, setup_enterExitCompartment), "605Bd", kObjectCompartmentD);
		} else {
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Francois, setup_enterExitCompartment), "605Dd", kObjectCompartmentD);
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentD, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getSavePoints()->push(kEntityFrancois, kEntityMmeBoutarel, kAction102484312);
			break;

		case 2:
			getData()->posture = kPostureSitting;
			getEntities()->clearSequences(kEntityFrancois);

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION_I(Francois, function11, 11)
	error("Francois: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function12, 12)
	error("Francois: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function13, 13)
	error("Francois: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION_IIS(Francois, function14, 14)
	error("Francois: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function15, 15)
	error("Francois: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, function16, 16)
	error("Francois: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, chapter1, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		break;
	}
}

IMPLEMENT_FUNCTION(Francois, chapter1Handler, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime1161000 && !params->param1) {
			params->param1 = 1;
			setCallback(1);
			call(new ENTITY_SETUP(Francois, setup_function11), kTime1093500);
		}
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function19();
		break;
	}
}

IMPLEMENT_FUNCTION(Francois, function19, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CALLBACK(Francois, kTime1161000, params->param1, 2, setup_function12);
		break;

	case kAction101107728:
		setCallback(1);
		call(new ENTITY_SETUP(Francois, setup_function16));
		break;
	}
}

IMPLEMENT_FUNCTION(Francois, function20, 20)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;

		getEntities()->clearSequences(kEntityFrancois);
	}
}

IMPLEMENT_FUNCTION(Francois, chapter2, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityFrancois);

		getData()->entityPosition = kPosition_4689;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Francois, chapter2Handler, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Francois, setup_enterExitCompartment), "605Id", kObjectCompartmentD);
			break;

		case 2:
			getObjects()->update(kObjectCompartmentD, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getSavePoints()->push(kEntityFrancois, kEntityMmeBoutarel, kAction100957716);
			getData()->entityPosition = kPosition_5790;
			getData()->posture = kPostureSitting;
			getEntities()->clearSequences(kEntityFrancois);
			setup_function23();
			break;
		}
		break;

	case kAction100901266:
		setCallback(1);
		call(new ENTITY_SETUP(Francois, setup_function8), kCarRedSleeping, kPosition_5790);
		break;
	}
}

IMPLEMENT_FUNCTION(Francois, function23, 23)
	error("Francois: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, chapter3, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityFrancois);

		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Francois, chapter3Handler, 25)
	error("Francois: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Francois, chapter4, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityFrancois);

		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Francois, chapter4Handler, 27)
	if (savepoint.action == kAction101107728) {
		setCallback(1);
		call(new ENTITY_SETUP(Francois, setup_function16));
	}
}

IMPLEMENT_FUNCTION(Francois, chapter5, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityFrancois);

		getData()->entityPosition = kPosition_3969;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Francois, chapter5Handler, 29)
	if (savepoint.action == kActionProceedChapter5) {
		if (!getInventory()->hasItem(kItemWhistle)
		  && getInventory()->getEntry(kItemWhistle)->location != kLocation3)
		  getInventory()->setLocationAndProcess(kItemWhistle, kLocation1);

		setup_function30();
	}
}

IMPLEMENT_FUNCTION(Francois, function30, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;

	case kAction135800432:
		setup_nullfunction();
		break;
	}
}

IMPLEMENT_NULL_FUNCTION(Francois, 31)

} // End of namespace LastExpress
