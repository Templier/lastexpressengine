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

#include "lastexpress/entities/servers0.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

#define HANDLE_TABLE(index, param, callback, function) \
	if (ENTITY_PARAM(index, param)) { \
		setCallback(callback); \
		call(new ENTITY_SETUP(Servers0, function)); \
		break; \
	}

Servers0::Servers0(LastExpressEngine *engine) : Entity(engine, kEntityServers0) {
	ADD_CALLBACK_FUNCTION(Servers0, callSavepoint);
	ADD_CALLBACK_FUNCTION(Servers0, updateFromTime);
	ADD_CALLBACK_FUNCTION(Servers0, draw);
	ADD_CALLBACK_FUNCTION(Servers0, updatePosition);
	ADD_CALLBACK_FUNCTION(Servers0, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Servers0, playSound);
	ADD_CALLBACK_FUNCTION(Servers0, function7);
	ADD_CALLBACK_FUNCTION(Servers0, function8);
	ADD_CALLBACK_FUNCTION(Servers0, function9);
	ADD_CALLBACK_FUNCTION(Servers0, function10);
	ADD_CALLBACK_FUNCTION(Servers0, chapter1);
	ADD_CALLBACK_FUNCTION(Servers0, function12);
	ADD_CALLBACK_FUNCTION(Servers0, function13);
	ADD_CALLBACK_FUNCTION(Servers0, function14);
	ADD_CALLBACK_FUNCTION(Servers0, function15);
	ADD_CALLBACK_FUNCTION(Servers0, function16);
	ADD_CALLBACK_FUNCTION(Servers0, function17);
	ADD_CALLBACK_FUNCTION(Servers0, function18);
	ADD_CALLBACK_FUNCTION(Servers0, function19);
	ADD_CALLBACK_FUNCTION(Servers0, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Servers0, function21);
	ADD_CALLBACK_FUNCTION(Servers0, function22);
	ADD_CALLBACK_FUNCTION(Servers0, chapter2);
	ADD_CALLBACK_FUNCTION(Servers0, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Servers0, function25);
	ADD_CALLBACK_FUNCTION(Servers0, function26);
	ADD_CALLBACK_FUNCTION(Servers0, chapter3);
	ADD_CALLBACK_FUNCTION(Servers0, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Servers0, augustAnnaDateOrder);
	ADD_CALLBACK_FUNCTION(Servers0, function30);
	ADD_CALLBACK_FUNCTION(Servers0, chapter4);
	ADD_CALLBACK_FUNCTION(Servers0, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Servers0, augustOrderSteak);
	ADD_CALLBACK_FUNCTION(Servers0, augustServeDuck);
	ADD_CALLBACK_FUNCTION(Servers0, function35);
	ADD_CALLBACK_FUNCTION(Servers0, chapter5);
	ADD_CALLBACK_FUNCTION(Servers0, chapter5Handler);
	ADD_NULL_FUNCTION();
}

/**
 * Call a savepoint (or draw sequence in default case)
 *
 * @param seq1   The sequence to draw in the default case
 * @param param4 The entity
 * @param param5 The action
 * @param seq1   The sequence name for the savepoint
 */
IMPLEMENT_FUNCTION_SIIS(Servers0, callSavepoint, 1)
	Entity::callSavepoint(savepoint, true);
}

/**
 * Updates parameter 2 using time value
 *
 * @param param1 The time to add
 */
IMPLEMENT_FUNCTION_NOSETUP(Servers0, updateFromTime, 2)
	Entity::updateFromTime(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Servers0, draw, 3)
	Entity::draw(savepoint, true);
}

/**
 * Updates the position
 *
 * @param seq1   The sequence to draw
 * @param param4 The car
 * @param param5 The entity position
 */
IMPLEMENT_FUNCTION_NOSETUP(Servers0, updatePosition, 4)
	Entity::updatePosition(savepoint, true);
}

/**
 * Process callback action when the entity direction is not kDirectionRight
 */
IMPLEMENT_FUNCTION_NOSETUP(Servers0, callbackActionOnDirection, 5)
	EXPOSE_PARAMS(EntityData::EntityParametersIIII);

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getData()->direction != kDirectionRight)
			CALLBACK_ACTION();
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION();
 		break;

	case kActionExcuseMeCath:
		if (!params->param1) {
			getSound()->excuseMe(kEntityServers0);
			params->param1 = 1;
		}
		break;
	}
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Servers0, playSound, 6)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION(Servers0, function7, 7)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5800;
		getData()->posture = kPostureStanding;

		ENTITY_PARAM(0, 3) = 0;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "911");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->clearSequences(kEntityServers0);
			getSavePoints()->push(kEntityServers0, kEntityRebecca, kAction123712592);
			break;

		case 2:
			getEntities()->clearSequences(kEntityServers0);
			getData()->entityPosition = kPosition_5900;
			CALLBACK_ACTION();
			break;
		}
		break;

	case kAction136702400:
		setCallback(2);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "913");
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function8, 8)
	serveTable(savepoint, "911", kEntityTables3, "010L", "010M", "913", &ENTITY_PARAM(1, 2));
}

IMPLEMENT_FUNCTION(Servers0, function9, 9)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5800;
		getData()->posture = kPostureStanding;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "915");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityServers0, kEntityAbbot, kAction122358304);
			getEntities()->drawSequenceLeft(kEntityServers0, "029D");

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_playSound), getProgress().chapter == kChapter3 ? "Abb3016" : "Abb4001");
			break;

		case 2:
			getSavePoints()->push(kEntityServers0, kEntityAbbot, kAction122288808);

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "917");
			break;

		case 3:
			getData()->entityPosition = kPosition_5900;
			getEntities()->clearSequences(kEntityServers0);
			ENTITY_PARAM(2, 2) = 0;
			ENTITY_PARAM(1, 6) = 0;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function10, 10)
	serveTable(savepoint, "916", kEntityTables4, "014E", "014F", "918", &ENTITY_PARAM(2, 3), false);
}

IMPLEMENT_FUNCTION(Servers0, chapter1, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter1Handler();
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityServers0, kAction270410280, 0);
		getSavePoints()->addData(kEntityServers0, kAction304061224, 1);
		getSavePoints()->addData(kEntityServers0, kAction252568704, 10);
		getSavePoints()->addData(kEntityServers0, kAction286534136, 11);
		getSavePoints()->addData(kEntityServers0, kAction218983616, 12);
		getSavePoints()->addData(kEntityServers0, kAction218586752, 13);
		getSavePoints()->addData(kEntityServers0, kAction207330561, 14);
		getSavePoints()->addData(kEntityServers0, kAction286403504, 16);
		getSavePoints()->addData(kEntityServers0, kAction218128129, 17);
		getSavePoints()->addData(kEntityServers0, kAction270068760, 18);
		getSavePoints()->addData(kEntityServers0, kAction223712416, 2);
		getSavePoints()->addData(kEntityServers0, kAction237485916, 5);
		getSavePoints()->addData(kEntityServers0, kAction188893625, 8);
		getSavePoints()->addData(kEntityServers0, kAction204704037, 6);
		getSavePoints()->addData(kEntityServers0, kAction292758554, 7);
		getSavePoints()->addData(kEntityServers0, kAction337548856, 9);

		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function12, 12)
	handleServer(savepoint, "907", kEntityAnna, kAction268773672, &ENTITY_PARAM(0, 1));
}

IMPLEMENT_FUNCTION(Servers0, function13, 13)
	handleServer(savepoint, "911", kEntityAugust, kAction268773672, &ENTITY_PARAM(0, 2), "010F");
}

IMPLEMENT_FUNCTION(Servers0, function14, 14)
	handleServer(savepoint, "908", kEntityAnna, kAction170016384, &ENTITY_PARAM(0, 4));
}

IMPLEMENT_FUNCTION(Servers0, function15, 15)
	handleServer(savepoint, "912", kEntityAugust, kAction170016384, &ENTITY_PARAM(0, 5));
}

IMPLEMENT_FUNCTION(Servers0, function16, 16)
	serveTable(savepoint, "907", kEntityTables0, "001N", "001P", "909", &ENTITY_PARAM(0, 6));
}

IMPLEMENT_FUNCTION(Servers0, function17, 17)
	serveTable(savepoint, "915", kEntityTables4, "014E", "014F", "917", &ENTITY_PARAM(1, 1), true, false, 67);
}

IMPLEMENT_FUNCTION(Servers0, function18, 18)
	serveTable(savepoint, "911", kEntityTables3, "010L", "010H", "913", &ENTITY_PARAM(0, 7));
}

IMPLEMENT_FUNCTION(Servers0, function19, 19)
	serveTable(savepoint, "911", kEntityTables3, "010L", "010M", "913", &ENTITY_PARAM(0, 8), true, true);
}

IMPLEMENT_FUNCTION(Servers0, chapter1Handler, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param2) {
			UPDATE_PARAM_GOTO(params->param3, getState()->time, 2700, label_continue);

			ENTITY_PARAM(0, 4) = 1;
			params->param2 = 0;
		}

label_continue:
		if (params->param1) {
			UPDATE_PARAM_GOTO(params->param4, getState()->time, 4500, label_continue2);

			ENTITY_PARAM(0, 5) = 1;
			params->param1 = 0;
		}

label_continue2:
		if (!getEntities()->isInKitchen(kEntityServers0) && !getEntities()->isSomebodyStandingInRestaurantOrSalon())
			break;

		HANDLE_TABLE(0, 1, 1, setup_function12);
		HANDLE_TABLE(0, 2, 2, setup_function13);
		HANDLE_TABLE(0, 3, 3, setup_function7);
		HANDLE_TABLE(0, 4, 4, setup_function14);
		HANDLE_TABLE(0, 5, 5, setup_function15);
		HANDLE_TABLE(0, 6, 6, setup_function16);
		HANDLE_TABLE(1, 1, 7, setup_function17);
		HANDLE_TABLE(0, 7, 8, setup_function18);
		HANDLE_TABLE(0, 8, 9, setup_function19);
		HANDLE_TABLE(1, 2, 10, setup_function8);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 10:
			getSavePoints()->push(kEntityServers0, kEntityPascale, kAction352703104);
			setup_function21();
			break;

		case 11:
		case 12:
			getEntities()->clearSequences(kEntityServers0);
			getData()->entityPosition = kPosition_5900;

			if (getCallback() == 11)
				params->param2 = 1;
			else
				params->param1 = 1;
			break;

		case 13:
		case 14:
			getEntities()->clearSequences(kEntityServers0);
			getData()->entityPosition = kPosition_5900;
			break;
		}
		break;

	case kAction136702400:
		setCallback(savepoint.entity2 == kEntityAnna ? 13 : 14);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), savepoint.entity2 == kEntityAnna ? "909" : "913");
		break;

	case kAction203859488:
		setCallback(savepoint.entity2 == kEntityAnna ? 11 : 12);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), savepoint.entity2 == kEntityAnna ? "910" : "913");
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function21, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5900;
		break;

	case kAction101632192:
		setup_function22();
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function22, 22)
	if (savepoint.action == kActionDefault) {
		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;

		getEntities()->clearSequences(kEntityServers0);
	}
}

IMPLEMENT_FUNCTION(Servers0, chapter2, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityServers0);

		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(1, 3) = 0;
		ENTITY_PARAM(1, 4) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, chapter2Handler, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!getEntities()->isInKitchen(kEntityServers0) || !getEntities()->isSomebodyStandingInRestaurantOrSalon())
			break;

		HANDLE_TABLE(1, 3, 1, setup_function25);
		HANDLE_TABLE(1, 4, 2, setup_function26);
 		break;

	case kActionCallback:
		if (getCallback() == 1)
			HANDLE_TABLE(1, 4, 2, setup_function26);
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function25, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5800;
		getData()->posture = kPostureStanding;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "957");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityServers0, kEntityAugust, kAction123712592);
			getEntities()->drawSequenceLeft(kEntityServers0, "BLANK");
			break;

		case 2:
			getData()->entityPosition = kPosition_5900;
			getEntities()->clearSequences(kEntityServers0);
			ENTITY_PARAM(1, 3) = 0;

			CALLBACK_ACTION();
			break;
		}
		break;

	case kAction219522616:
		setCallback(2);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "959");
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function26, 26)
	serveTable(savepoint, "957", kEntityTables0, "016E", "016D", "959", &ENTITY_PARAM(1, 4));
}

IMPLEMENT_FUNCTION(Servers0, chapter3, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityServers0);

		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(1, 2) = 0;
		ENTITY_PARAM(1, 5) = 0;
		ENTITY_PARAM(1, 6) = 0;
		ENTITY_PARAM(2, 3) = 0;
		ENTITY_PARAM(2, 4) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, chapter3Handler, 28)
	error("Servers0: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, augustAnnaDateOrder, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5800;
		getData()->posture = kPostureStanding;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "911");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityServers0, kEntityAnna, kAction122358304);
			getEntities()->drawSequenceLeft(kEntityServers0, "026D");

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_playSound), "Ann3138");
			break;

		case 2:
			getSavePoints()->push(kEntityServers0, kEntityAnna, kAction122288808);

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "913");
			break;

		case 3:
			getData()->entityPosition = kPosition_5900;
			getEntities()->clearSequences(kEntityServers0);
			ENTITY_PARAM(1, 5) = 0;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function30, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5800;
		getData()->posture = kPostureStanding;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "916");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityServers0, kEntityAbbot, kAction122358304);
			getEntities()->drawSequenceLeft(kEntityServers0, "029D");

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_playSound), "Abb3016a");
			break;

		case 2:
			getSavePoints()->push(kEntityServers0, kEntityAbbot, kAction122288808);

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "918");
			break;

		case 3:
			getData()->entityPosition = kPosition_5900;
			getEntities()->clearSequences(kEntityServers0);
			ENTITY_PARAM(2, 4) = 0;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, chapter4, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityServers0);

		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(1, 7) = 0;
		ENTITY_PARAM(1, 8) = 0;
		ENTITY_PARAM(2, 1) = 0;
		ENTITY_PARAM(2, 2) = 0;
		ENTITY_PARAM(2, 3) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, chapter4Handler, 32)
	error("Servers0: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Servers0, augustOrderSteak, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "911");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceLeft(kEntityServers0, "010F3");
			getEntities()->drawSequenceLeft(kEntityAugust, "010D3");

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_playSound), "AUG4002");
			break;

		case 2:
			getSavePoints()->push(kEntityServers0, kEntityAugust, kAction122288808);

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "913");
			break;

		case 3:
			getData()->entityPosition = kPosition_5900;
			getEntities()->clearSequences(kEntityServers0);
			ENTITY_PARAM(1, 7) = 0;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, augustServeDuck, 34)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "912");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityServers0, kEntityAugust, kAction122358304);
			getSound()->playSound(kEntityServers0, "AUG1053");

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "010G3");
			break;

		case 2:
			getSavePoints()->push(kEntityServers0, kEntityAugust, kAction201964801);

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), "914");
			break;

		case 3:
			getData()->entityPosition = kPosition_5900;
			getEntities()->clearSequences(kEntityServers0);
			ENTITY_PARAM(1, 8) = 0;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, function35, 35)
	serveTable(savepoint, "911", kEntityTables3, "010L", "010M", "914", &ENTITY_PARAM(2, 1), false, true);
}

IMPLEMENT_FUNCTION(Servers0, chapter5, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityServers0);

		getData()->entityPosition = kPosition_3969;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Servers0, chapter5Handler, 37)
	if (savepoint.action == kActionProceedChapter5)
		setup_nullfunction();
}

IMPLEMENT_NULL_FUNCTION(Servers0, 38)

void Servers0::handleServer(const SavePoint &savepoint, const char* name, EntityIndex entity, ActionIndex action, int *parameter, const char* name2) {
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5800;
		getData()->posture = kPostureStanding;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), name);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			// Prepare or draw sequences depending of value of string
			if (strcmp(name2, ""))
				getEntities()->clearSequences(kEntityServers0);
			else
				getEntities()->drawSequenceLeft(kEntityServers0, name2);

			getSavePoints()->push(kEntityServers0, entity, action);
			*parameter = 0;

			CALLBACK_ACTION();
		}
		break;
	}
}

void Servers0::serveTable(const SavePoint &savepoint, const char* seq1, EntityIndex entity, const char* seq2, const char* seq3, const char* seq4, int *parameter, bool shouldUpdatePosition, bool pushSavepoint, Position position) {
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (shouldUpdatePosition) {
			getData()->entityPosition = kPosition_5800;
			getData()->posture = kPostureStanding;
		}

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), seq1);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (position)
				getEntities()->updatePositionEnter(kEntityServers0, kCarRestaurant, position);

			getSavePoints()->push(kEntityServers0, entity, kAction136455232);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_callSavepoint), seq2, entity, kActionDrawTablesWithChairs, seq3);
			break;

		case 2:
			if (position)
				getEntities()->updatePositionExit(kEntityServers0, kCarRestaurant, position);

			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Servers0, setup_draw), seq4);
			break;

		case 3:
			getData()->entityPosition = kPosition_5900;

			// Special case for functions 19 & 35
			if (pushSavepoint)
				getSavePoints()->push(kEntityServers0, kEntityRebecca, kAction224253538);

			getEntities()->clearSequences(kEntityServers0);
			*parameter = 0;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

} // End of namespace LastExpress
