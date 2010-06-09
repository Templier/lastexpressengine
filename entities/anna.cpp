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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "lastexpress/entities/anna.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Anna::Anna(LastExpressEngine *engine) : Entity(engine, kEntityAnna) {
	ADD_CALLBACK_FUNCTION(Anna, function1);
	ADD_CALLBACK_FUNCTION(Anna, draw);
	ADD_CALLBACK_FUNCTION(Anna, updatePosition);
	ADD_CALLBACK_FUNCTION(Anna, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Anna, function5);
	ADD_CALLBACK_FUNCTION(Anna, function6);
	ADD_CALLBACK_FUNCTION(Anna, playSound);
	ADD_CALLBACK_FUNCTION(Anna, function8);
	ADD_CALLBACK_FUNCTION(Anna, savegame);
	ADD_CALLBACK_FUNCTION(Anna, function10);
	ADD_CALLBACK_FUNCTION(Anna, updateFromTime);
	ADD_CALLBACK_FUNCTION(Anna, function12);
	ADD_CALLBACK_FUNCTION(Anna, draw2);
	ADD_CALLBACK_FUNCTION(Anna, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Anna, function15);
	ADD_CALLBACK_FUNCTION(Anna, chapter1);
	ADD_CALLBACK_FUNCTION(Anna, function17);
	ADD_CALLBACK_FUNCTION(Anna, function18);
	ADD_CALLBACK_FUNCTION(Anna, function19);
	ADD_CALLBACK_FUNCTION(Anna, function20);
	ADD_CALLBACK_FUNCTION(Anna, function21);
	ADD_CALLBACK_FUNCTION(Anna, function22);
	ADD_CALLBACK_FUNCTION(Anna, function23);
	ADD_CALLBACK_FUNCTION(Anna, function24);
	ADD_CALLBACK_FUNCTION(Anna, function25);
	ADD_CALLBACK_FUNCTION(Anna, function26);
	ADD_CALLBACK_FUNCTION(Anna, function27);
	ADD_CALLBACK_FUNCTION(Anna, function28);
	ADD_CALLBACK_FUNCTION(Anna, function29);
	ADD_CALLBACK_FUNCTION(Anna, function30);
	ADD_CALLBACK_FUNCTION(Anna, function31);
	ADD_CALLBACK_FUNCTION(Anna, function32);
	ADD_CALLBACK_FUNCTION(Anna, function33);
	ADD_CALLBACK_FUNCTION(Anna, function34);
	ADD_CALLBACK_FUNCTION(Anna, function35);
	ADD_CALLBACK_FUNCTION(Anna, function36);
	ADD_CALLBACK_FUNCTION(Anna, function37);
	ADD_CALLBACK_FUNCTION(Anna, function38);
	ADD_CALLBACK_FUNCTION(Anna, function39);
	ADD_CALLBACK_FUNCTION(Anna, function40);
	ADD_CALLBACK_FUNCTION(Anna, function41);
	ADD_CALLBACK_FUNCTION(Anna, chapter2);
	ADD_CALLBACK_FUNCTION(Anna, function43);
	ADD_CALLBACK_FUNCTION(Anna, chapter3);
	ADD_CALLBACK_FUNCTION(Anna, function45);
	ADD_CALLBACK_FUNCTION(Anna, function46);
	ADD_CALLBACK_FUNCTION(Anna, function47);
	ADD_CALLBACK_FUNCTION(Anna, function48);
	ADD_CALLBACK_FUNCTION(Anna, leaveTableWithAugust);
	ADD_CALLBACK_FUNCTION(Anna, function50);
	ADD_CALLBACK_FUNCTION(Anna, function51);
	ADD_CALLBACK_FUNCTION(Anna, function52);
	ADD_CALLBACK_FUNCTION(Anna, function53);
	ADD_CALLBACK_FUNCTION(Anna, function54);
	ADD_CALLBACK_FUNCTION(Anna, function55);
	ADD_CALLBACK_FUNCTION(Anna, function56);
	ADD_CALLBACK_FUNCTION(Anna, function57);
	ADD_CALLBACK_FUNCTION(Anna, function58);
	ADD_CALLBACK_FUNCTION(Anna, function59);
	ADD_CALLBACK_FUNCTION(Anna, function60);
	ADD_CALLBACK_FUNCTION(Anna, function61);
	ADD_CALLBACK_FUNCTION(Anna, function62);
	ADD_CALLBACK_FUNCTION(Anna, function63);
	ADD_CALLBACK_FUNCTION(Anna, bagage);
	ADD_CALLBACK_FUNCTION(Anna, function65);
	ADD_CALLBACK_FUNCTION(Anna, chapter4);
	ADD_CALLBACK_FUNCTION(Anna, function67);
	ADD_CALLBACK_FUNCTION(Anna, function68);
	ADD_CALLBACK_FUNCTION(Anna, function69);
	ADD_CALLBACK_FUNCTION(Anna, function70);
	ADD_CALLBACK_FUNCTION(Anna, function71);
	ADD_CALLBACK_FUNCTION(Anna, function72);
	ADD_CALLBACK_FUNCTION(Anna, function73);
	ADD_CALLBACK_FUNCTION(Anna, chapter5);
	ADD_CALLBACK_FUNCTION(Anna, function75);
	ADD_CALLBACK_FUNCTION(Anna, function76);
	ADD_CALLBACK_FUNCTION(Anna, function77);
	ADD_CALLBACK_FUNCTION(Anna, function78);
	ADD_CALLBACK_FUNCTION(Anna, function79);
	ADD_CALLBACK_FUNCTION(Anna, function80);
	ADD_CALLBACK_FUNCTION(Anna, function81);
}

IMPLEMENT_FUNCTION(Anna, function1, 1)
	Entity::function1Clothes(savepoint);
}

IMPLEMENT_FUNCTION_S(Anna, draw, 2)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SII(Anna, updatePosition, 3)
	Entity::updatePosition(savepoint);
}

IMPLEMENT_FUNCTION_SI(Anna, enterExitCompartment, 4)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION(Anna, function5, 5)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_SIIS(Anna, function6, 6)
	Entity::savepointCall(savepoint);
}

IMPLEMENT_FUNCTION_S(Anna, playSound, 7)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION(Anna, function8, 8)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION_II(Anna, savegame, 9)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(Anna, function10, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionExcuseMeCath:
		if (getEvent(kEventAugustPresentAnna) || getEvent(kEventAugustPresentAnnaFirstIntroduction) || getProgress().chapter >= kChapter2)
			getSound()->playSound(kEntityNone, "CAT1001");
		else
			getSound()->excuseMeCath();
		break;

	case kActionExcuseMe:
		getSound()->excuseMe(kEntityAnna);
		break;

	case kActionNone:
	case kActionDefault:
		if (getEntities()->checkEntity(kEntityAnna, (CarIndex)params->param1, (EntityData::Field491Value)params->param2))
			CALLBACK_ACTION()
		break;
	}
}

IMPLEMENT_FUNCTION_I(Anna, updateFromTime, 11)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION(Anna, function12, 12)
	error("Anna: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_SSI(Anna, draw2, 13)
	Entity::draw2(savepoint);
}

IMPLEMENT_FUNCTION_I(Anna, updateFromTicks, 14)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION_IS(Anna, function15, 15)
	error("Anna: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter1, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(19)
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityAnna, kAction291662081, 0);
		getSavePoints()->addData(kEntityAnna, kAction238936000, 1);

		getObjects()->update(kObjectCompartmentF, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject53, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject45, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

		getData()->field_491 = EntityData::kField491_8200;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothesDefault;

		break;
	}
}

IMPLEMENT_FUNCTION_II(Anna, function17, 17)
	error("Anna: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION_I(Anna, function18, 18)
	error("Anna: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function19, 19)
	error("Anna: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_ISSI(Anna, setup_function15), kTimeAnna, "NONE");
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Anna, setup_enterExitCompartment), "618Bf", kObjectCompartmentF);
			break;

		case 2:
			getData()->field_493 = EntityData::kField493_0;
			getSavePoints()->push(kEntityAnna, kEntityMax, kAction71277948);
			setup_function21();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function21, 21)
	error("Anna: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function22, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAnna, "001A");
		getSavePoints()->push(kEntityAnna, kEntityPascale, kAction223262556);
		break;

	case kAction157370960:
		getData()->field_493 = EntityData::kField493_1;
		setup_function23();
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function23, 23)
	error("Anna: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function24, 24)
	error("Anna: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function25, 25)
	error("Anna: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function26, 26)
	error("Anna: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function27, 27)
	error("Anna: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function28, 28)
	error("Anna: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function29, 29)
	error("Anna: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function30, 30)
	error("Anna: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function31, 31)
	error("Anna: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function32, 32)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function17), kCarRedSleeping, EntityData::kField491_4070);
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Anna, setup_enterExitCompartment), "618Af", kObjectCompartmentF);
			break;

		case 2:
			getEntities()->prepareSequences(kEntityAnna);

			getData()->field_491 = EntityData::kField491_4070;
			getData()->field_493 = EntityData::kField493_1;

			setup_function33();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function33, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAnna, kEntityMax, kAction101687594);

		params->param1 = getState()->time + 4500;
		setCallback(1);
		call(new ENTITY_SETUP_ISSI(Anna, setup_function15), params->param1, "NONE");
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getObjects()->updateLocation2(kObjectCompartmentF, kLocation1);
			setup_function34();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function34, 34)
	error("Anna: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function35, 35)
	error("Anna: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function36, 36)
	error("Anna: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function37, 37)
  switch (savepoint.action) {
  default:
	break;

  case kActionDefault:
	getData()->field_491 = EntityData::kField491_8200;
	getData()->field_493 = EntityData::kField493_0;
	getData()->car = kCarRedSleeping;
	break;

  case kAction191477936:
	setup_function38();
	break;
  }
}

IMPLEMENT_FUNCTION(Anna, function38, 38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->field_491 = EntityData::kField491_7500;

		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "ANN1010");
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getSound()->playSound(kEntityNone, "MUS043");
			setup_function40();
		}
		break;
	}
}

IMPLEMENT_FUNCTION_II(Anna, function39, 39)
	error("Anna: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function40, 40)
	error("Anna: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function41, 41)
	error("Anna: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter2, 42)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function43();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAnna);

		getData()->field_491 = EntityData::kField491_4070;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function43, 43)
	error("Anna: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter3, 44)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function46();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAnna);

		getData()->field_491 = EntityData::kField491_4070;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothes3;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentF, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject45, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject53, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION_I(Anna, function45, 45)
	error("Anna: callback function 45 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function46, 46)
	error("Anna: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function47, 47)
	error("Anna: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function48, 48)
	error("Anna: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, leaveTableWithAugust, 49)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getSavePoints()->push(kEntityAnna, kEntityTables3, kAction103798704, "010M");
		getEntities()->prepareSequences(kEntityAugust);

		CALLBACK_ACTION();
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityTables3, "026J3");
		getEntities()->drawSequenceRight(kEntityAugust, "026J2");
		getEntities()->drawSequenceRight(kEntityAnna, "026J1");
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function50, 50)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Anna, setup_playSound), "ann3141");
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Anna, setup_function8));
			break;

		case 2:
			getData()->field_493 = EntityData::kField493_0;
			setCallback(3);
			call(new ENTITY_SETUP(Anna, setup_leaveTableWithAugust));
			break;

		case 3:
			setup_function51();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function51, 51)
	error("Anna: callback function 51 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function52, 52)
	error("Anna: callback function 52 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function53, 53)
	error("Anna: callback function 53 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function54, 54)
	error("Anna: callback function 54 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function55, 55)
	error("Anna: callback function 55 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function56, 56)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAnna);
		getData()->field_491 = EntityData::kField491_6000;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarKronos;
		break;

	case kAction191668032:
		setup_function57();
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function57, 57)
	error("Anna: callback function 57 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function58, 58)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_savegame), kSavegameType2, kEventAnnaSearchingCompartment);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventAnnaSearchingCompartment);
			getEntities()->prepareSequences(kEntityAnna);
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 8);
			getSound()->playSound(kEntityAnna, "lib015");
			getSavePoints()->push(kEntityAnna, kEntityAugust, kAction122288808);
			setup_function59();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function59, 59)
	error("Anna: callback function 59 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function60, 60)
	error("Anna: callback function 60 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function61, 61)
	error("Anna: callback function 61 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function62, 62)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeAnna_3 && !params->param2) {
			params->param2 = 1;
			getSavePoints()->push(kEntityAnna, kEntityVesna, kAction189299008);
			setup_function63();
		}
		break;

	case kActionDefault:
		getData()->car = kCarBaggage;
		getProgress().field_54 = 1;
		break;

	case kAction235856512:
		params->param1 = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function63, 63)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAnna, kEntityChapters, kAction171843264);
		break;

	// Game over with Anna killed!
	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventAnnaKilled);
			getLogic()->gameOver(kTimeType1, kTimeAnna_2, kSceneGameOverAnnaDied, true);
		}
		break;

	// Anna will get killed...
	case kAction272177921:
		if (getSound()->isBuffered("MUS012"))
			getSound()->unknownFunction2("MUS012");

		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_savegame), kSavegameType2, kEventAnnaKilled);
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, bagage, 64)
	error("Anna: callback function 64 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function65, 65)
	if (savepoint.action == kActionDefault) {
		getData()->field_491 = EntityData::kField491_4070;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothes3;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject45, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

		setCallback(1);
		call(new ENTITY_SETUP_ISSI(Anna, setup_function15), kTimeEnd, "NONE");
	}
}

IMPLEMENT_FUNCTION(Anna, chapter4, 66)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function67();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAnna);

		getData()->field_491 = EntityData::kField491_4070;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothes2;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function67, 67)
	error("Anna: callback function 67 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function68, 68)
	error("Anna: callback function 68 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function69, 69)
	error("Anna: callback function 69 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function70, 70)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_function72), kCarRedSleeping, EntityData::kField491_4070);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Anna, setup_function71));
			break;

		case 2:
			getData()->field_493 = EntityData::kField493_0;
			getEntities()->prepareSequences(kEntityAnna);
			setup_function73();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function71, 71)
	error("Anna: callback function 71 not implemented!");
}

IMPLEMENT_FUNCTION_II(Anna, function72, 72)
	error("Anna: callback function 72 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function73, 73)
	error("Anna: callback function 73 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, chapter5, 74)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function75();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAnna);

		getData()->field_491 = EntityData::kField491_3969;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarBaggageRear;
		getData()->clothes = kClothes3;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObject45, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function75, 75)
	switch (savepoint.action) {
	default:
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			if (getProgress().field_C)
				getAction()->playAnimation(getEvent(kEventAnnaKissTrainHijacked) ? kEventAnnaBagageTies2 : kEventAnnaBagageTies);
			else
				getAction()->playAnimation(getEvent(kEventAnnaKissTrainHijacked) ? kEventAnnaBagageTies3 : kEventAnnaBagageTies4);

			getScenes()->loadSceneFromPosition(kCarBaggage, 8);
			setup_function76();
		}
		break;

	case kAction272177921:
		setCallback(1);
		call(new ENTITY_SETUP(Anna, setup_savegame), kSavegameType2, kEventAnnaBagageTies);
		break;
	}
}

IMPLEMENT_FUNCTION(Anna, function76, 76)
	if (savepoint.action == kAction158480160)
		setup_function77();
}

IMPLEMENT_FUNCTION(Anna, function77, 77)
	error("Anna: callback function 77 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function78, 78)
	error("Anna: callback function 78 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function79, 79)
	error("Anna: callback function 79 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function80, 80)
	error("Anna: callback function 80 not implemented!");
}

IMPLEMENT_FUNCTION(Anna, function81, 81)
	error("Anna: callback function 81 not implemented!");
}

} // End of namespace LastExpress
