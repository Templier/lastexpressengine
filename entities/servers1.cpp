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

#include "lastexpress/entities/servers1.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Servers1::Servers1(LastExpressEngine *engine) : Entity(engine, kEntityServers1) {
	ADD_CALLBACK_FUNCTION(Servers1, updateFromTime);
	ADD_CALLBACK_FUNCTION(Servers1, draw);
	ADD_CALLBACK_FUNCTION(Servers1, updatePosition);
	ADD_CALLBACK_FUNCTION(Servers1, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Servers1, callSavepoint);
	ADD_CALLBACK_FUNCTION(Servers1, playSound);
	ADD_CALLBACK_FUNCTION(Servers1, function7);
	ADD_CALLBACK_FUNCTION(Servers1, chapter1);
	ADD_CALLBACK_FUNCTION(Servers1, function9);
	ADD_CALLBACK_FUNCTION(Servers1, function10);
	ADD_CALLBACK_FUNCTION(Servers1, function11);
	ADD_CALLBACK_FUNCTION(Servers1, function12);
	ADD_CALLBACK_FUNCTION(Servers1, function13);
	ADD_CALLBACK_FUNCTION(Servers1, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Servers1, function15);
	ADD_CALLBACK_FUNCTION(Servers1, function16);
	ADD_CALLBACK_FUNCTION(Servers1, chapter2);
	ADD_CALLBACK_FUNCTION(Servers1, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Servers1, function19);
	ADD_CALLBACK_FUNCTION(Servers1, function20);
	ADD_CALLBACK_FUNCTION(Servers1, function21);
	ADD_CALLBACK_FUNCTION(Servers1, chapter3);
	ADD_CALLBACK_FUNCTION(Servers1, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Servers1, function24);
	ADD_CALLBACK_FUNCTION(Servers1, chapter4);
	ADD_CALLBACK_FUNCTION(Servers1, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Servers1, function27);
	ADD_CALLBACK_FUNCTION(Servers1, function28);
	ADD_CALLBACK_FUNCTION(Servers1, function29);
	ADD_CALLBACK_FUNCTION(Servers1, chapter5);
	ADD_CALLBACK_FUNCTION(Servers1, chapter5Handler);
	ADD_NULL_FUNCTION()
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_NOSETUP(Servers1, updateFromTime, 1)
	Entity::updateFromTime(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Servers1, draw, 2)
	Entity::draw(savepoint, true);
}

/**
 * Updates the position
 *
 * @param seq1   The sequence to draw
 * @param param4 The car
 * @param param5 The entity position
 */
IMPLEMENT_FUNCTION_SIII(Servers1, updatePosition, 3)
	Entity::updatePosition(savepoint, true);
}

/**
 * Process callback action when the entity direction is not kDirectionRight
 */
IMPLEMENT_FUNCTION(Servers1, callbackActionOnDirection, 4)
	if (savepoint.action == kActionExcuseMeCath) {
		if (!params->param1) {
			getSound()->excuseMe(kEntityServers1);
			params->param1 = 1;
		}
	}

	Entity::callbackActionOnDirection(savepoint);
}

/**
 * Call a savepoint (or draw sequence in default case)
 *
 * @param seq1   The sequence to draw in the default case
 * @param param4 The entity
 * @param param5 The action
 * @param seq1   The sequence name for the savepoint
 */
IMPLEMENT_FUNCTION_SIIS(Servers1, callSavepoint, 5)
	Entity::callSavepoint(savepoint, true);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Servers1, playSound, 6)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION(Servers1, function7, 7)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5800;
		getData()->posture = kPostureStanding;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers1, setup_draw), "924");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityServers1, kEntityBoutarel, kAction122358304);
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Servers1, setup_draw), "008C");
			break;

		case 2:
			getSavePoints()->push(kEntityServers1, kEntityBoutarel, kAction122288808);
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Servers1, setup_draw), "926");
			break;

		case 3:
			getEntities()->clearSequences(kEntityServers1);
			getData()->entityPosition = kPosition_5900;
			ENTITY_PARAM(1, 2) = 0;

			CALLBACK_ACTION()
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, chapter1, 8)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter1Handler();
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityServers1, kAction223002560, 0);
		getSavePoints()->addData(kEntityServers1, kAction302996448, 2);
		getSavePoints()->addData(kEntityServers1, kAction269485588, 3);
		getSavePoints()->addData(kEntityServers1, kAction326144276, 4);
		getSavePoints()->addData(kEntityServers1, kAction302203328, 5);
		getSavePoints()->addData(kEntityServers1, kAction189688608, 6);
		getSavePoints()->addData(kEntityServers1, kAction236237423, 7);
		getSavePoints()->addData(kEntityServers1, kAction219377792, 8);
		getSavePoints()->addData(kEntityServers1, kAction256200848, 9);
		getSavePoints()->addData(kEntityServers1, kAction291721418, 10);
		getSavePoints()->addData(kEntityServers1, kAction258136010, 11);

		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, function9, 9)
	error("Servers1: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function10, 10)
	error("Servers1: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function11, 11)
	error("Servers1: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function12, 12)
	serveTable(savepoint, "923", kEntityTables2, "009F", "009G", "926", &ENTITY_PARAM(0, 4));
}

IMPLEMENT_FUNCTION(Servers1, function13, 13)
	serveTable(savepoint, "923", kEntityTables2, "009F", "009G", "926", &ENTITY_PARAM(0, 5));
}

IMPLEMENT_FUNCTION(Servers1, chapter1Handler, 14)
switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (!getEntities()->isInKitchen(kEntityServers1) || !getEntities()->isSomebodyStandingInRestaurantOrSalon())
			break;

		if (ENTITY_PARAM(0, 1)) {
			setCallback(1);
			call(new ENTITY_SETUP(Servers1, setup_function9));
			break;
		}

		if (ENTITY_PARAM(1, 2)) {
			setCallback(2);
			call(new ENTITY_SETUP(Servers1, setup_function10));
			break;
		}

		if (ENTITY_PARAM(0, 3)) {
			setCallback(3);
			call(new ENTITY_SETUP(Servers1, setup_function11));
			break;
		}

		if (ENTITY_PARAM(0, 4)) {
			setCallback(4);
			call(new ENTITY_SETUP(Servers1, setup_function12));
			break;
		}

		if (ENTITY_PARAM(0, 5)) {
			setCallback(5);
			call(new ENTITY_SETUP(Servers1, setup_function13));
		}
		break;

	case kActionCallback:
		if (getCallback() == 5) {
			getSavePoints()->push(kEntityServers1, kEntityPascale, kAction352768896);
			setup_function15();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, function15, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5900;
		break;

	case kAction101632192:
		setup_function16();
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, function16, 16)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;

		getEntities()->clearSequences(kEntityServers1);
	}
}

IMPLEMENT_FUNCTION(Servers1, chapter2, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityServers1);

		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 6) = 0;
		ENTITY_PARAM(0, 7) = 0;
		ENTITY_PARAM(0, 8) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, chapter2Handler, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!getEntities()->isInKitchen(kEntityServers1) || !getEntities()->isSomebodyStandingInRestaurantOrSalon())
			break;

		if (ENTITY_PARAM(0, 6)) {
			setCallback(1);
			call(new ENTITY_SETUP(Servers1, setup_function19));
			break;
		}

label_callback_1:
		if (ENTITY_PARAM(0, 7)) {
			setCallback(2);
			call(new ENTITY_SETUP(Servers1, setup_function20));
			break;
		}

label_callback_2:
		if (ENTITY_PARAM(0, 8) || ENTITY_PARAM(0, 5)) {
			setCallback(3);
			call(new ENTITY_SETUP(Servers1, setup_function21));
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			goto label_callback_1;

		case 2:
			goto label_callback_2;

		case 4:
			getEntities()->clearSequences(kEntityServers1);
			getData()->entityPosition = kPosition_5900;
			break;
		}
		break;

	case kAction101106391:
		setCallback(4);
		call(new ENTITY_SETUP_SIIS(Servers1, setup_draw), "975");
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, function19, 19)
	error("Servers1: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5800;
		getData()->posture = kPostureStanding;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers1, setup_draw), "973");
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getSavePoints()->push(kEntityServers1, kEntityIvo, kAction123712592);
			getEntities()->drawSequenceLeft(kEntityServers1, "BLANK");
			ENTITY_PARAM(0, 7) = 0;

			CALLBACK_ACTION()
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, function21, 21)
	serveTable(savepoint, "974", kEntityTables2, "009F2", "009G", "976", &ENTITY_PARAM(0, 8), true, &ENTITY_PARAM(0, 5));
}

IMPLEMENT_FUNCTION(Servers1, chapter3, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityServers1);

		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(1, 1) = 0;
		ENTITY_PARAM(1, 2) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, chapter3Handler, 23)
	if (savepoint.action != kActionNone)
		return;

	if (getEntities()->isInKitchen(kEntityServers1) && getEntities()->isSomebodyStandingInRestaurantOrSalon()) {
		if (ENTITY_PARAM(1, 1)) {
			setCallback(1);
			call(new ENTITY_SETUP(Servers1, setup_function24));
		} else if (ENTITY_PARAM(1, 2)) {
			setCallback(2);
			call(new ENTITY_SETUP(Servers1, setup_function7));
		}
	}
}

IMPLEMENT_FUNCTION(Servers1, function24, 24)
	error("Servers1: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, chapter4, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityServers1);

		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		getEntities()->clearSequences(kEntityServers1);

		ENTITY_PARAM(1, 2) = 0;
		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 4) = 0;
		ENTITY_PARAM(1, 5) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, chapter4Handler, 26)
	error("Servers1: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function27, 27)
	error("Servers1: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function28, 28)
	error("Servers1: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, function29, 29)
	error("Servers1: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Servers1, chapter5, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityServers1);

		getData()->entityPosition = kPosition_3969;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers1, chapter5Handler, 31)
	if (savepoint.action == kActionProceedChapter5)
		setup_nullfunction();
}

IMPLEMENT_NULL_FUNCTION(Servers1, 32)

void Servers1::serveTable(const SavePoint &savepoint, const char* seq1, EntityIndex entity, const char* seq2, const char* seq3, const char* seq4, int *parameter, bool updatePosition, int* parameter2) {
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (updatePosition) {
			getData()->entityPosition = kPosition_5800;
			getData()->posture = kPostureStanding;
		}

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers1, setup_draw), seq1);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityServers1, entity, kAction136455232);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Servers1, setup_callSavepoint), seq2, entity, kActionDrawTablesWithChairs, seq3);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Servers1, setup_draw), seq4);
			break;

		case 3:
			getData()->entityPosition = kPosition_5900;
			getEntities()->clearSequences(kEntityServers1);
			*parameter = 0;

			if (parameter2 != NULL)
				*parameter2 = 0;

			CALLBACK_ACTION()
			break;
		}
		break;
	}
}

} // End of namespace LastExpress
