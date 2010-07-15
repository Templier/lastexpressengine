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

#include "lastexpress/entities/august.h"

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

August::August(LastExpressEngine *engine) : Entity(engine, kEntityAugust) {
	ADD_CALLBACK_FUNCTION(August, function1);
	ADD_CALLBACK_FUNCTION(August, updateFromTime);
	ADD_CALLBACK_FUNCTION(August, draw);
	ADD_CALLBACK_FUNCTION(August, updatePosition);
	ADD_CALLBACK_FUNCTION(August, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(August, function6);
	ADD_CALLBACK_FUNCTION(August, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(August, function8);
	ADD_CALLBACK_FUNCTION(August, function9);
	ADD_CALLBACK_FUNCTION(August, function10);
	ADD_CALLBACK_FUNCTION(August, draw2);
	ADD_CALLBACK_FUNCTION(August, playSound);
	ADD_CALLBACK_FUNCTION(August, playSound16);
	ADD_CALLBACK_FUNCTION(August, function14);
	ADD_CALLBACK_FUNCTION(August, savegame);
	ADD_CALLBACK_FUNCTION(August, function16);
	ADD_CALLBACK_FUNCTION(August, function17);
	ADD_CALLBACK_FUNCTION(August, function18);
	ADD_CALLBACK_FUNCTION(August, function19);
	ADD_CALLBACK_FUNCTION(August, function20);
	ADD_CALLBACK_FUNCTION(August, function21);
	ADD_CALLBACK_FUNCTION(August, chapter1);
	ADD_CALLBACK_FUNCTION(August, function23);
	ADD_CALLBACK_FUNCTION(August, dinner);
	ADD_CALLBACK_FUNCTION(August, chapter1_handler);
	ADD_CALLBACK_FUNCTION(August, function26);
	ADD_CALLBACK_FUNCTION(August, function27);
	ADD_CALLBACK_FUNCTION(August, function28);
	ADD_CALLBACK_FUNCTION(August, function29);
	ADD_CALLBACK_FUNCTION(August, restaurant);
	ADD_CALLBACK_FUNCTION(August, function31);
	ADD_CALLBACK_FUNCTION(August, function32);
	ADD_CALLBACK_FUNCTION(August, function33);
	ADD_CALLBACK_FUNCTION(August, function34);
	ADD_CALLBACK_FUNCTION(August, chapter2);
	ADD_CALLBACK_FUNCTION(August, chapter2_handler);
	ADD_CALLBACK_FUNCTION(August, function37);
	ADD_CALLBACK_FUNCTION(August, function38);
	ADD_CALLBACK_FUNCTION(August, function39);
	ADD_CALLBACK_FUNCTION(August, chapter3);
	ADD_CALLBACK_FUNCTION(August, function41);
	ADD_CALLBACK_FUNCTION(August, function42);
	ADD_CALLBACK_FUNCTION(August, chapter3_handler);
	ADD_CALLBACK_FUNCTION(August, function44);
	ADD_CALLBACK_FUNCTION(August, function45);
	ADD_CALLBACK_FUNCTION(August, function46);
	ADD_CALLBACK_FUNCTION(August, function47);
	ADD_CALLBACK_FUNCTION(August, function48);
	ADD_CALLBACK_FUNCTION(August, function49);
	ADD_CALLBACK_FUNCTION(August, function50);
	ADD_CALLBACK_FUNCTION(August, function51);
	ADD_CALLBACK_FUNCTION(August, function52);
	ADD_CALLBACK_FUNCTION(August, function53);
	ADD_CALLBACK_FUNCTION(August, function54);
	ADD_CALLBACK_FUNCTION(August, function55);
	ADD_CALLBACK_FUNCTION(August, function56);
	ADD_CALLBACK_FUNCTION(August, chapter4);
	ADD_CALLBACK_FUNCTION(August, chapter4_handler);
	ADD_CALLBACK_FUNCTION(August, function59);
	ADD_CALLBACK_FUNCTION(August, function60);
	ADD_CALLBACK_FUNCTION(August, function61);
	ADD_CALLBACK_FUNCTION(August, function62);
	ADD_CALLBACK_FUNCTION(August, function63);
	ADD_CALLBACK_FUNCTION(August, function64);
	ADD_CALLBACK_FUNCTION(August, function65);
	ADD_CALLBACK_FUNCTION(August, chapter5);
	ADD_CALLBACK_FUNCTION(August, chapter5_handler);
	ADD_CALLBACK_FUNCTION(August, function68);
	ADD_CALLBACK_FUNCTION(August, function69);
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(August, function1, 1)
	Entity::function1Clothes(savepoint);
}

IMPLEMENT_FUNCTION_I(August, updateFromTime, 2)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_S(August, draw, 3)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SII(August, updatePosition, 4)
	Entity::updatePosition(savepoint);
}

IMPLEMENT_FUNCTION_SI(August, enterExitCompartment, 5)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_SI(August, function6, 6)
	error("August: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_SI(August, enterExitCompartment2, 7)
	if (savepoint.action == kAction4) {
		getEntities()->exitCompartment(kEntityAugust, (ObjectIndex)params->param2);
		CALLBACK_ACTION();
		return;
	}

	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION(August, function8, 8)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_SIIS(August, function9, 9)
	Entity::savepointCall(savepoint);
}

IMPLEMENT_FUNCTION_IIS(August, function10, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		if (!params->param3)
			getSavePoints()->call(kEntityAugust, (EntityIndex)params->param1, (ActionIndex)params->param2, params->seq1);

		CALLBACK_ACTION();
		break;

	case kAction10:
		if (!params->param3) {
			getSavePoints()->call(kEntityAugust, (EntityIndex)params->param1, (ActionIndex)params->param2, params->seq1);
			params->param3 = 1;
		}
		break;
	}
}

IMPLEMENT_FUNCTION_SSI(August, draw2, 11)
	Entity::draw2(savepoint);
}

IMPLEMENT_FUNCTION_S(August, playSound, 12)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_S(August, playSound16, 13)
	Entity::playSound(savepoint, false, 16);
}

IMPLEMENT_FUNCTION(August, function14, 14)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION_II(August, savegame, 15)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(August, function16, 16)
	error("August: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION_I(August, function17, 17)
	error("August: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION_II(August, function18, 18)
	error("August: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION_II(August, function19, 19)
	error("August: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION_I(August, function20, 20)
	error("August: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION_I(August, function21, 21)
	error("August: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(August, chapter1, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject11, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->field_491 = EntityData::kField491_4691;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;

		getProgress().eventMetAugust = 0;
		break;
	}
}

IMPLEMENT_FUNCTION_I(August, function23, 23)
	error("August: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(August, dinner, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(August, setup_savegame), kSavegameType2, kEventDinerAugust);
		break;

	case kActionCallback:
		if (getCallback() == 1) {

			getAction()->playAnimation(getEntities()->checkFields13(kEntityAlexei) ? kEventDinerAugustAlexeiBackground : kEventDinerAugust);
			getProgress().eventMetAugust = 1;
			
			getScenes()->loadSceneFromPosition(kCarRestaurant, 61);

			CALLBACK_ACTION();
		}
		break;
	}
}

IMPLEMENT_FUNCTION(August, chapter1_handler, 25)
	error("August: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(August, function26, 26)
	error("August: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(August, function27, 27)
	error("August: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(August, function28, 28)
	error("August: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(August, function29, 29)
	error("August: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(August, restaurant, 30)
	error("August: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(August, function31, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(August, setup_function16), kCarGreenSleeping, EntityData::kField491_6470);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(August, setup_function19));
			break;

		case 2:
			setCallback(2);
			call(new ENTITY_SETUP(August, setup_function21), kTimeFrancois);
			break;

		case 3:
		case 4:
			if (getProgress().field_14 == 29) {
				setCallback(4);
				call(new ENTITY_SETUP(August, setup_function21), getState()->time + 900);
			} else {
				setup_function32();
			}
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(August, function32, 32)
	error("August: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(August, function33, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(getProgress().eventMetAugust ? 1 : 2);
		call(new ENTITY_SETUP(August, setup_function21), getProgress().eventMetAugust ? getState()->time + 9000 : (uint32)kTimeBedTime);
		break;

	case kActionCallback:
		if (getCallback() == 1 || getCallback() == 2)
			setup_function34();
		break;
	}
}

IMPLEMENT_FUNCTION(August, function34, 34)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!getSound()->isBuffered(kEntityAugust) && getProgress().field_18 != 4)
			getSound()->playSound(kEntityAugust, "AUG1057");    // August snoring
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->field_491 = EntityData::kField491_6470;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarGreenSleeping;

		getEntities()->prepareSequences(kEntityAugust);
		break;
	}
}

IMPLEMENT_FUNCTION(August, chapter2, 35)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2_handler();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAugust);

		getData()->field_491 = EntityData::kField491_3970;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartment3, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject11, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		break;
	}
}

IMPLEMENT_FUNCTION(August, chapter2_handler, 36)
	error("August: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(August, function37, 37)
	error("August: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(August, function38, 38)
	error("August: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION(August, function39, 39)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		if (!ENTITY_PARAM(0, 1))
			getSound()->playSound(kEntityNone, "BUMP");

		setCallback(1);
		call(new ENTITY_SETUP(August, setup_savegame), kSavegameType2, kEventAugustArrivalInMunich);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventAugustArrivalInMunich);
			getSavePoints()->push(kEntityAugust, kEntityChapters, kActionChapter3);
			getEntities()->prepareSequences(kEntityAugust);
		}
		break;
	}
}

IMPLEMENT_FUNCTION(August, chapter3, 40)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3_handler();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAugust);

		getData()->field_491 = EntityData::kField491_6470;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothes1;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION_II(August, function41, 41)
	error("August: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION_III(August, function42, 42)
	error("August: callback function 42 not implemented!");
}

IMPLEMENT_FUNCTION(August, chapter3_handler, 43)
	error("August: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(August, function44, 44)
	error("August: callback function 44 not implemented!");
}

IMPLEMENT_FUNCTION(August, function45, 45)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeAugust_1 && !params->param1) {
			params->param1 = 1;
			getData()->inventoryItem = kItemNone;

			setup_function46();
		}
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;
		getSound()->playSound(kEntityNone, "CAT1002");
		getSound()->playSound(kEntityAugust, "AUG3102", -1, 15);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityNone, kLocation2, kCursorNormal, kCursorNormal);
		getEntities()->drawSequenceLeft(kEntityAugust, "506A2");
		getData()->inventoryItem = kItem146;	// TODO which item is that?
		break;
	}
}

IMPLEMENT_FUNCTION(August, function46, 46)
	error("August: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(August, function47, 47)
	error("August: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(August, function48, 48)
	error("August: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(August, function49, 49)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(August, setup_function20));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(August, setup_function16), kCarKronos, EntityData::kField491_9270);
			break;

		case 2:
			setup_function50();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(August, function50, 50)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getEntities()->prepareSequences(kEntityAugust);

		getData()->field_491 = EntityData::kField491_6000;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarKronos;
		break;

	case kAction191668032:
		setup_function51();
	}
}

IMPLEMENT_FUNCTION(August, function51, 51)
	error("August: callback function 51 not implemented!");
}

IMPLEMENT_FUNCTION(August, function52, 52)
	error("August: callback function 52 not implemented!");
}

IMPLEMENT_FUNCTION(August, function53, 53)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(August, setup_updateFromTime), 2700);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(August, setup_function20));
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(August, setup_function16), kCarRestaurant, EntityData::kField491_850);
			break;

		case 3:
			setup_function54();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(August, function54, 54)
	error("August: callback function 54 not implemented!");
}

IMPLEMENT_FUNCTION(August, function55, 55)
	error("August: callback function 55 not implemented!");
}

IMPLEMENT_FUNCTION(August, function56, 56)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityNone, kLocation2, kCursorNormal, kCursorNormal);
		getEntities()->drawSequenceLeft(kEntityAugust, "507A3");
		break;

	case kAction17:
		if (!params->param1 && getEntities()->isPlayerPosition(kCarGreenSleeping, 43)) {
			setCallback(1);
			call(new ENTITY_SETUP(August, setup_function20));
		}
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			params->param1 = 1;
			getEntities()->drawSequenceLeft(kEntityAugust, "507A3");
		}
		break;
	}
}

IMPLEMENT_FUNCTION(August, chapter4, 57)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4_handler();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAugust);

		getData()->field_491 = EntityData::kField491_6470;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarGreenSleeping;
		getData()->clothes = kClothes2;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartment3, kEntityNone, kLocation2, kCursorNormal, kCursorNormal);

		break;
	}
}

IMPLEMENT_FUNCTION(August, chapter4_handler, 58)
	error("August: callback function 58 not implemented!");
}

IMPLEMENT_FUNCTION(August, function59, 59)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAugust, "010B3");
		getSavePoints()->push(kEntityAugust, kEntityPascale, kAction190605184);
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityAugust, "BLANK");
		break;

	case kAction123793792:
		setup_function60();
		break;
	}
}

IMPLEMENT_FUNCTION(August, function60, 60)
	error("August: callback function 60 not implemented!");
}

IMPLEMENT_FUNCTION(August, function61, 61)
	error("August: callback function 61 not implemented!");
}

IMPLEMENT_FUNCTION(August, function62, 62)
	error("August: callback function 62 not implemented!");
}

IMPLEMENT_FUNCTION(August, function63, 63)
	error("August: callback function 63 not implemented!");
}

IMPLEMENT_FUNCTION(August, function64, 64)
	error("August: callback function 64 not implemented!");
}

IMPLEMENT_FUNCTION(August, function65, 65)
	switch (savepoint.action) {
	default:
		break;

	case kAction2:
		getSound()->playSound(kEntityAugust, "AUG1057");   // August snoring
		break;

	case kActionDefault:
		getData()->field_491 = EntityData::kField491_6470;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarGreenSleeping;

		getEntities()->prepareSequences(kEntityAugust);

		getObjects()->update(kObjectCompartment3, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		if (!getSound()->isBuffered(kEntityAugust))
			getSound()->playSound(kEntityAugust, "AUG1057");   // August snoring
		break;
	}
}

IMPLEMENT_FUNCTION(August, chapter5, 66)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5_handler();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAugust);

		getData()->field_491 = EntityData::kField491_3969;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes2;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(August, chapter5_handler, 67)
	if (savepoint.action == kAction70549068)
		setup_function68();
}

IMPLEMENT_FUNCTION(August, function68, 68)
	error("August: callback function 68 not implemented!");
}

IMPLEMENT_FUNCTION(August, function69, 69)
	error("August: callback function 69 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(August, 70)

} // End of namespace LastExpress
