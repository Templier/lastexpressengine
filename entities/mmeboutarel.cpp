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

#include "lastexpress/entities/mmeboutarel.h"

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

MmeBoutarel::MmeBoutarel(LastExpressEngine *engine) : Entity(engine, kEntityMmeBoutarel) {
	ADD_CALLBACK_FUNCTION(MmeBoutarel, reset);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, playSound);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, draw);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, updateFromTime);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, updateEntity);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function8);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function9);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter1);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function11);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter1Handler);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function13);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function14);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function15);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function16);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter2);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter2Handler);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function19);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter3);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter3Handler);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter4);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter4Handler);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function24);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function25);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter5);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, chapter5Handler);
	ADD_CALLBACK_FUNCTION(MmeBoutarel, function28);
	ADD_NULL_FUNCTION();
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(MmeBoutarel, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(MmeBoutarel, playSound, 2)
	Entity::playSound(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(MmeBoutarel, draw, 3)
	Entity::draw(savepoint);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_I(MmeBoutarel, updateFromTime, 4)
	Entity::updateFromTime(savepoint);
}

/**
 * Handles entering/exiting a compartment.
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(MmeBoutarel, enterExitCompartment, 5)
	Entity::enterExitCompartment(savepoint);
}

/**
 * Handles entering/exiting a compartment and updates position/play animation
 *
 * @param seq1   The sequence to draw
 * @param param4 The compartment
 */
IMPLEMENT_FUNCTION_SI(MmeBoutarel, enterExitCompartment2, 6)
	Entity::enterExitCompartment(savepoint, kPosition_5790, kPosition_6130, kCarRedSleeping, kObjectCompartmentD, true);
}

/**
 * Updates the entity
 *
 * @param param1 The car
 * @param param2 The entity position
 */
IMPLEMENT_FUNCTION_II(MmeBoutarel, updateEntity, 7)
	if (savepoint.action == kActionExcuseMeCath) {
		getInventory()->hasItem(kItemPassengerList) ? getSound()->playSound(kEntityNone, "CAT1021") : getSound()->excuseMeCath();

		return;
	}

	Entity::updateEntity(savepoint, true);
}

IMPLEMENT_FUNCTION_S(MmeBoutarel, function8, 8)
	error("MmeBoutarel: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function9, 9)
	error("MmeBoutarel: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter1, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityMmeBoutarel, kAction242526416, 0);

		getObjects()->update(kObjectCompartmentD, kEntityNone, kLocation2, kCursorNormal, kCursorNormal);
		getObjects()->update(kObject51, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, function11, 11)
	error("MmeBoutarel: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter1Handler, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		params->param1 = 1;
		getEntities()->drawSequenceLeft(kEntityMmeBoutarel, "501");
		break;

	case kActionDrawScene:
		if (getEntities()->isPlayerPosition(kCarRedSleeping, 44)) {
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(MmeBoutarel, setup_draw), "502B");
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceLeft(kEntityMmeBoutarel, "502A");
			break;

		case 2:
			getEntities()->drawSequenceLeft(kEntityMmeBoutarel, "606Qd");
			getEntities()->enterCompartment(kEntityMmeBoutarel, kObjectCompartmentD);
			break;

		case 3:
			getData()->posture = kPostureSitting;
			params->param1 = 1;
			getEntities()->clearSequences(kEntityMmeBoutarel);
			setup_function13();
			break;
		}
		break;

	case kAction102484312:
		getEntities()->drawSequenceLeft(kEntityMmeBoutarel, "501");
		params->param1 = 1;
		break;

	case kAction134289824:
		getEntities()->drawSequenceLeft(kEntityMmeBoutarel, "502A");
		params->param1 = 0;
		break;

	case kAction168986720:
		getSavePoints()->push(kEntityMmeBoutarel, kEntityFrancois, kAction102752636);
		getSound()->playSound(kEntityMmeBoutarel, "MME1036");
		getEntities()->exitCompartment(kEntityMmeBoutarel, kObjectCompartmentD);

		setCallback(3);
		call(new ENTITY_SETUP_SIIS(MmeBoutarel, setup_enterExitCompartment), "606Fd", kObjectCompartmentD);
		break;

	case kAction202221040:
		getObjects()->update(kObjectCompartmentD, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getData()->posture = kPostureStanding;

		getSound()->playSound(kEntityMmeBoutarel, "MME1035A");

		if (getEntities()->hasValidFrame(kEntityMmeBoutarel) || getEntities()->checkFields9(kEntityMmeBoutarel, kEntityNone, 2000) )
			getProgress().field_AC = 1;

		setCallback(2);
		call(new ENTITY_SETUP_SIIS(MmeBoutarel, setup_enterExitCompartment), "606Ed", kObjectCompartmentD);
		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, function13, 13)
	error("MmeBoutarel: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function14, 14)
	error("MmeBoutarel: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function15, 15)
	error("MmeBoutarel: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function16, 16)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentD, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject51, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getEntities()->clearSequences(kEntityMmeBoutarel);
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter2, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityMmeBoutarel);

		getData()->entityPosition = kPosition_4689;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentD, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject51, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject43, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter2Handler, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (getEntities()->isEntitySitting(kEntityFrancois, kCarRedSleeping, kPosition_5790)) {
				getObjects()->update(kObjectCompartmentD, kEntityNone, kLocationNone, kCursorNormal, kCursorNormal);

				setCallback(2);
				call(new ENTITY_SETUP_SIIS(MmeBoutarel, setup_enterExitCompartment2), "606Ad", kObjectCompartmentD);
			} else {
				getEntities()->drawSequenceLeft(kEntityMmeBoutarel, "606Md");
				getEntities()->enterCompartment(kEntityMmeBoutarel, kObjectCompartmentD, true);
			}
			break;

		case 2:
		case 3:
			getObjects()->update(kObjectCompartmentD, kEntityNone, kLocation2, kCursorNormal, kCursorNormal);
			getData()->posture = kPostureSitting;
			setup_function19();
			break;
		}
		break;

	case kAction100901266:
		setCallback(1);
		call(new ENTITY_SETUP(MmeBoutarel, setup_updateEntity), kCarRedSleeping, kPosition_5790);
		break;

	case kAction100957716:
		getEntities()->exitCompartment(kEntityMmeBoutarel, kObjectCompartmentD, true);
		getObjects()->update(kObjectCompartmentD, kEntityNone, kLocationNone, kCursorNormal, kCursorNormal);

		setCallback(3);
		call(new ENTITY_SETUP_SIIS(MmeBoutarel, setup_enterExitCompartment2), "606Ad", kObjectCompartmentD);
		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, function19, 19)
	error("MmeBoutarel: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter3, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityMmeBoutarel);

		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter3Handler, 21)
	error("MmeBoutarel: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter4, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityMmeBoutarel);

		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter4Handler, 23)
	error("MmeBoutarel: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function24, 24)
	error("MmeBoutarel: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(MmeBoutarel, function25, 25)
	if (savepoint.action == kActionDefault) {
		getEntities()->clearSequences(kEntityMmeBoutarel);

		getData()->entityPosition = kPosition_5790;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentD, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject51, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter5, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityMmeBoutarel);

		getData()->entityPosition = kPosition_3969;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(MmeBoutarel, chapter5Handler, 27)
	if (savepoint.action == kActionProceedChapter5)
		setup_function28();
}

IMPLEMENT_FUNCTION(MmeBoutarel, function28, 28)
	error("MmeBoutarel: callback function 28 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(MmeBoutarel, 29)

} // End of namespace LastExpress
