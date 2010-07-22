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

#include "lastexpress/entities/verges.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Verges::Verges(LastExpressEngine *engine) : Entity(engine, kEntityVerges) {
	ADD_CALLBACK_FUNCTION(Verges, function1);
	ADD_CALLBACK_FUNCTION(Verges, draw);
	ADD_CALLBACK_FUNCTION(Verges, function3);
	ADD_CALLBACK_FUNCTION(Verges, playSound);
	ADD_CALLBACK_FUNCTION(Verges, playSound16);
	ADD_CALLBACK_FUNCTION(Verges, function6);
	ADD_CALLBACK_FUNCTION(Verges, savegame);
	ADD_CALLBACK_FUNCTION(Verges, checkEntity);
	ADD_CALLBACK_FUNCTION(Verges, function9);
	ADD_CALLBACK_FUNCTION(Verges, function10);
	ADD_CALLBACK_FUNCTION(Verges, function11);
	ADD_CALLBACK_FUNCTION(Verges, function12);
	ADD_CALLBACK_FUNCTION(Verges, function13);
	ADD_CALLBACK_FUNCTION(Verges, updateFromTime);
	ADD_CALLBACK_FUNCTION(Verges, function15);
	ADD_CALLBACK_FUNCTION(Verges, function16);
	ADD_CALLBACK_FUNCTION(Verges, function17);
	ADD_CALLBACK_FUNCTION(Verges, chapter1);
	ADD_CALLBACK_FUNCTION(Verges, function19);
	ADD_CALLBACK_FUNCTION(Verges, function20);
	ADD_CALLBACK_FUNCTION(Verges, function21);
	ADD_CALLBACK_FUNCTION(Verges, function22);
	ADD_CALLBACK_FUNCTION(Verges, function23);
	ADD_CALLBACK_FUNCTION(Verges, policeGettingOffTrain);
	ADD_CALLBACK_FUNCTION(Verges, function25);
	ADD_CALLBACK_FUNCTION(Verges, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Verges, chapter2);
	ADD_CALLBACK_FUNCTION(Verges, function28);
	ADD_CALLBACK_FUNCTION(Verges, chapter3);
	ADD_CALLBACK_FUNCTION(Verges, function30);
	ADD_CALLBACK_FUNCTION(Verges, function31);
	ADD_CALLBACK_FUNCTION(Verges, function32);
	ADD_CALLBACK_FUNCTION(Verges, function33);
	ADD_CALLBACK_FUNCTION(Verges, function34);
	ADD_CALLBACK_FUNCTION(Verges, function35);
	ADD_CALLBACK_FUNCTION(Verges, chapter4);
	ADD_CALLBACK_FUNCTION(Verges, function37);
	ADD_CALLBACK_FUNCTION(Verges, function38);
	ADD_CALLBACK_FUNCTION(Verges, chapter5);
	ADD_CALLBACK_FUNCTION(Verges, function40);
	ADD_CALLBACK_FUNCTION(Verges, function41);
	ADD_CALLBACK_FUNCTION(Verges, function42);
}

IMPLEMENT_FUNCTION(Verges, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Verges, draw, 2)
	Entity::draw(savepoint, true);
}

IMPLEMENT_FUNCTION(Verges, function3, 3)
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
			getSound()->excuseMe(kEntityVerges);
			params->param1 = 1;
		}
		break;
	}
}

IMPLEMENT_FUNCTION_S(Verges, playSound, 4)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Verges, playSound16, 5)
	Entity::playSound(savepoint, false, 16);
}

IMPLEMENT_FUNCTION(Verges, function6, 6)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION_II(Verges, savegame, 7)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(Verges, checkEntity, 8)
	if (savepoint.action == kActionExcuseMeCath) {
		if (!getSound()->isBuffered(kEntityVerges))
			getSound()->playSound(kEntityNone, "TRA1113", getEntities()->getSoundValue(kEntityVerges));

		return;
	}

	Entity::checkEntity(savepoint, true);
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - Sound name
IMPLEMENT_FUNCTION_S(Verges, function9, 9)
switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObject104, kEntityNone, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityNone, kLocationNone, kCursorNormal, kCursorHand);

		if (getEntities()->checkFields21(kEntityNone) || getEntities()->checkFields17(kEntityNone)) {
			getAction()->playAnimation(getEntities()->checkFields21(kEntityNone) ? kEventVergesBagageCarOffLimits : kEventVergesCanIHelpYou);
			getSound()->playSound(kEntityNone, "BUMP");
			getScenes()->loadSceneFromPosition(kCarRestaurant, 65);
		}

		getScenes()->loadSceneFromItemPosition(kItem9);
		getData()->car = kCarRestaurant;
		getData()->entityPosition = kPosition_5900;

		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function6));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->entityPosition = kPosition_5800;
			getData()->field_493 = kField493_0;

			getSound()->playSound(kEntityVerges, (char *)&params->seq1);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Verges, setup_draw), "813DD");
			break;

		case 2:
			if (!getSound()->isBuffered(kEntityVerges))
				getSound()->playSound(kEntityVerges, (char *)&params->seq1);

			getEntities()->drawSequenceRight(kEntityVerges, "813DS");

			if (getEntities()->checkFields13(kEntityNone))
				getEntities()->updateEntity(kEntityVerges);

			setCallback(3);
			call(new ENTITY_SETUP(Verges, setup_function3));
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP_IISI(Verges, setup_function10), kCarGreenSleeping, kPosition_540, (char *)&params->seq1);
			break;

		case 4:
			getEntities()->clearSequences(kEntityVerges);

			setCallback(5);
			call(new ENTITY_SETUP(Verges, setup_updateFromTime), 225);
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 6:
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - CarIndex
//  - EntityPosition
//  - Sound name
IMPLEMENT_FUNCTION_IIS(Verges, function10, 10)
	error("Verges: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function11, 11)
	error("Verges: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function12, 12)
	error("Verges: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_I(Verges, function13, 13)
	error("Verges: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION_I(Verges, updateFromTime, 14)
	Entity::updateFromTime(savepoint);
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - EntityIndex
//  - Sound name
IMPLEMENT_FUNCTION_IS(Verges, function15, 15)
	error("Verges: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION_ISS(Verges, function16, 16)
	error("Verges: callback function 16 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Verges, function17, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function12));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_checkEntity), kCarGreenSleeping, kPosition_2000);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kEntityMertens, "TRA1291");
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 4:
			ENTITY_PARAM(0, 3) = 0;
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, chapter1, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityVerges, kAction191337656, 0);
		getSavePoints()->addData(kEntityVerges, kAction226031488, 1);
		getSavePoints()->addData(kEntityVerges, kAction339669520, 1);
		getSavePoints()->addData(kEntityVerges, kAction167854368, 4);
		getSavePoints()->addData(kEntityVerges, kAction158617345, 2);
		getSavePoints()->addData(kEntityVerges, kAction168255788, 3);
		getSavePoints()->addData(kEntityVerges, kAction201431954, 5);
		getSavePoints()->addData(kEntityVerges, kAction168187490, 6);

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		getData()->entityPosition = kPosition_5000;
		getData()->field_493 = kField493_0;
		getData()->car = kCarBaggage;
		break;
	}
}

IMPLEMENT_FUNCTION_NOSETUP(Verges, function19, 19)
	error("Verges: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function20, 20)
	error("Verges: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function21, 21)
	error("Verges: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function22, 22)
	error("Verges: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getScenes()->loadSceneFromItemPosition(kItem9);

		getData()->entityPosition = kPosition_8200;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		break;

	case kAction191477936:
		getData()->entityPosition = kPosition_8200;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRedSleeping;

		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function11));
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, policeGettingOffTrain, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->checkFields9(kEntityVerges, kEntityNone, 1000) && !getEntityData(kEntityNone)->field_493) {
			setCallback(1);
			call(new ENTITY_SETUP(Verges, setup_savegame), kSavegameType2, kEventGendarmesArrestation);
		}
		break;

	case kAction2:
		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getSound()->playSound(kEntityVerges, "POL1101", 16);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getSound()->processEntry(kEntityVerges);
			getAction()->playAnimation(kEventGendarmesArrestation);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverPolice1, true);
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function25, 25)
	error("Verges: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter1_handler, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (ENTITY_PARAM(0, 6)) {
			params->param1 = 1;
			params->param2 = 1;
			params->param3 = 1;
			params->param4 = 1;
			params->param5 = 1;
			params->param6 = 1;

			ENTITY_PARAM(0, 6) = 0;
		}

		if (ENTITY_PARAM(0, 2)) {
			setCallback(1);
			call(new ENTITY_SETUP(Verges, setup_function23));
			break;
		}

label_callback1:
		if (getEntities()->checkFields20(kEntityNone)) {
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_function13), 0);
			break;
		}

label_callback2:
		if (ENTITY_PARAM(0, 7)) {
			setCallback(3);
			call(new ENTITY_SETUP(Verges, setup_function25));
			break;
		}

label_callback3:
		if (params->param6)
			goto label_callback12;

		TIME_CHECK_CALLBACK_S(Verges, kTimeChapter1, params->param7, 4, setup_function9, "TRA1001");

label_callback4:
		TIME_CHECK_CALLBACK(Verges, kTime1089000, params->param8, 5, setup_function12);

		params->param8 = 1;

		if (!params->param5) {
			setCallback(5);
			call(new ENTITY_SETUP(Verges, setup_function12));
			break;
		}

label_callback8:
		TIME_CHECK_CALLBACK_S(Verges, kTime1107000, ENTITY_PARAM(1, 1), 9, setup_function9, "TRA1001A");

label_callback9:
		TIME_CHECK_CALLBACK_S(Verges, kTime1134000, ENTITY_PARAM(1, 2), 10, setup_function9, "TRA1002");

label_callback10:
		TIME_CHECK_CALLBACK_S(Verges, kTime1165500, ENTITY_PARAM(1, 3), 11, setup_function9, "TRA1003");

label_callback11:
		TIME_CHECK_CALLBACK_S(Verges, kTIme1225800, ENTITY_PARAM(1, 4), 12, setup_function9, "TRA1004");

label_callback12:
		if (ENTITY_PARAM(0, 5) && !params->param2) {
			setCallback(13);
			call(new ENTITY_SETUP(Verges, setup_function21));
			break;
		}

label_callback13:
		if (getInventory()->hasItem(kItemPassengerList) && !params->param4 && (getState()->time < kTime1134000 || getState()->time > kTime1156500)) {
			setCallback(14);
			call(new ENTITY_SETUP(Verges, setup_function20));
			break;
		}

label_callback14:
		if (ENTITY_PARAM(0, 3) && !params->param4 && (getState()->time < kTime1134000 || getState()->time > kTime1156500)) {
			setCallback(15);
			call(new ENTITY_SETUP(Verges, setup_function17));
			break;
		}

label_callback15:
		if (ENTITY_PARAM(0, 1) && !params->param5) {
			if (getState()->time < kTime1134000 || getState()->time > kTime1156500) {
				setCallback(16);
				call(new ENTITY_SETUP(Verges, setup_function22));
			}
		}
		break;

	case kAction9:
		setCallback(17);
		call(new ENTITY_SETUP(Verges, setup_function13), savepoint.param.intValue < 106 ? true : false);
		break;

	case kActionDefault:
		getData()->car = kCarBaggage;
		getData()->entityPosition = kPosition_5000;
		getData()->field_493 = kField493_0;

		getEntities()->clearSequences(kEntityVerges);
		getInventory()->setLocationAndProcess(kItem9, kLocation1);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			goto label_callback1;

		case 2:
			goto label_callback2;

		case 3:
			goto label_callback3;

		case 4:
			goto label_callback4;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP(Verges, setup_checkEntity), kCarGreenSleeping, kPosition_2000);
			break;

		case 6:
			setCallback(7);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kCarGreenSleeping, "TRA1202");
			break;

		case 7:
			setCallback(8);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 8:
			goto label_callback8;

		case 9:
			goto label_callback9;

		case 10:
			goto label_callback10;

		case 11:
			goto label_callback11;

		case 12:
			goto label_callback12;

		case 13:
			params->param2 = 1;
			goto label_callback13;

		case 14:
			params->param3 = 1;
			goto label_callback14;

		case 15:
			params->param4 = 1;
			goto label_callback15;

		case 16:
			params->param5 = 1;
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, chapter2, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function28();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVerges);

		getData()->entityPosition = kPosition_5000;
		getData()->field_493 = kField493_0;
		getData()->car = kCarBaggage;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		ENTITY_PARAM(0, 3) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function28, 28)
	error("Verges: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter3, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function23();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVerges);

		getData()->entityPosition = kPosition_540;
		getData()->field_493 = kField493_0;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 4) = 0;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Parameters
//  - sequence name
IMPLEMENT_FUNCTION_S(Verges, function30, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function12));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_checkEntity), kCarRedSleeping, kPosition_2000);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kEntityCoudert, params->seq1);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 4:
			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function31, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Verges, setup_function12));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Verges, setup_checkEntity), kCarRedSleeping, kPosition_2000);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP_ISII(Verges, setup_function15), kEntityCoudert, "TRA3015");
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP(Verges, setup_function11));
			break;

		case 4:
			getProgress().field_48 = 1;
			ENTITY_PARAM(0, 4) = 0;

			CALLBACK_ACTION();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function32, 32)
	error("Verges: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function33, 33)
	error("Verges: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function34, 34)
	error("Verges: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function35, 35)
	error("Verges: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter4, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function37();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVerges);

		getData()->entityPosition = kPosition_5000;
		getData()->field_493 = kField493_0;
		getData()->car = kCarBaggage;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityVerges, kLocationNone, kCursorNormal, kCursorHand);

		ENTITY_PARAM(0, 3) = 0;
		ENTITY_PARAM(0, 6) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function37, 37)
	error("Verges: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function38, 38)
	error("Verges: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, chapter5, 39)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function40();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVerges);

		getData()->entityPosition = kPosition_3650;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject104, kEntityNone, kLocationNone, kCursorNormal, kCursorHand);
		getObjects()->update(kObject105, kEntityNone, kLocationNone, kCursorNormal, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Verges, function40, 40)
	error("Verges: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function41, 41)
	error("Verges: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Verges, function42, 42)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityVerges);
}

} // End of namespace LastExpress
