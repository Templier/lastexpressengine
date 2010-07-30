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

#include "lastexpress/entities/tatiana.h"

#include "lastexpress/entities/alexei.h"

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

Tatiana::Tatiana(LastExpressEngine *engine) : Entity(engine, kEntityTatiana) {
	ADD_CALLBACK_FUNCTION(Tatiana, reset);
	ADD_CALLBACK_FUNCTION(Tatiana, playSound);
	ADD_CALLBACK_FUNCTION(Tatiana, draw);
	ADD_CALLBACK_FUNCTION(Tatiana, updatePosition);
	ADD_CALLBACK_FUNCTION(Tatiana, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Tatiana, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(Tatiana, callSavepoint);
	ADD_CALLBACK_FUNCTION(Tatiana, function8);
	ADD_CALLBACK_FUNCTION(Tatiana, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Tatiana, updateFromTime);
	ADD_CALLBACK_FUNCTION(Tatiana, function11);
	ADD_CALLBACK_FUNCTION(Tatiana, savegame);
	ADD_CALLBACK_FUNCTION(Tatiana, checkEntity);
	ADD_CALLBACK_FUNCTION(Tatiana, function14);
	ADD_CALLBACK_FUNCTION(Tatiana, function15);
	ADD_CALLBACK_FUNCTION(Tatiana, function16);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter1);
	ADD_CALLBACK_FUNCTION(Tatiana, function18);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Tatiana, function20);
	ADD_CALLBACK_FUNCTION(Tatiana, function21);
	ADD_CALLBACK_FUNCTION(Tatiana, function22);
	ADD_CALLBACK_FUNCTION(Tatiana, function23);
	ADD_CALLBACK_FUNCTION(Tatiana, function24);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter2);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Tatiana, function27);
	ADD_CALLBACK_FUNCTION(Tatiana, function28);
	ADD_CALLBACK_FUNCTION(Tatiana, function29);
	ADD_CALLBACK_FUNCTION(Tatiana, function30);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter3);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Tatiana, function33);
	ADD_CALLBACK_FUNCTION(Tatiana, function34);
	ADD_CALLBACK_FUNCTION(Tatiana, function35);
	ADD_CALLBACK_FUNCTION(Tatiana, function36);
	ADD_CALLBACK_FUNCTION(Tatiana, function37);
	ADD_CALLBACK_FUNCTION(Tatiana, function38);
	ADD_CALLBACK_FUNCTION(Tatiana, function39);
	ADD_CALLBACK_FUNCTION(Tatiana, function40);
	ADD_CALLBACK_FUNCTION(Tatiana, function41);
	ADD_CALLBACK_FUNCTION(Tatiana, function42);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter4);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Tatiana, function45);
	ADD_CALLBACK_FUNCTION(Tatiana, function46);
	ADD_CALLBACK_FUNCTION(Tatiana, function47);
	ADD_CALLBACK_FUNCTION(Tatiana, function48);
	ADD_CALLBACK_FUNCTION(Tatiana, function49);
	ADD_CALLBACK_FUNCTION(Tatiana, function50);
	ADD_CALLBACK_FUNCTION(Tatiana, function51);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter5);
	ADD_CALLBACK_FUNCTION(Tatiana, chapter5Handler);
	ADD_CALLBACK_FUNCTION(Tatiana, function54);
	ADD_CALLBACK_FUNCTION(Tatiana, function55);
}

IMPLEMENT_FUNCTION(Tatiana, reset, 1)
	Entity::reset(savepoint, true);
}

IMPLEMENT_FUNCTION_S(Tatiana, playSound, 2)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_S(Tatiana, draw, 3)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SII(Tatiana, updatePosition, 4)
	Entity::updatePosition(savepoint);
}

IMPLEMENT_FUNCTION_SI(Tatiana, enterExitCompartment, 5)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION_SI(Tatiana, enterExitCompartment2, 6)
	Entity::enterExitCompartment(savepoint, kPosition_7500, kPosition_7850, kCarRedSleeping, kObjectCompartmentB);
}

IMPLEMENT_FUNCTION_SIIS(Tatiana, callSavepoint, 7)
	Entity::callSavepoint(savepoint);
}

IMPLEMENT_FUNCTION(Tatiana, function8, 8)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Tatiana, updateFromTicks, 9)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION_I(Tatiana, updateFromTime, 10)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION(Tatiana, function11, 11)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION_II(Tatiana, savegame, 12)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(Tatiana, checkEntity, 13)
	if (savepoint.action == kActionExcuseMeCath) {
		if (getEvent(kEventTatianaAskMatchSpeakRussian) || getEvent(kEventTatianaAskMatch) || getEvent(kEventVassiliSeizure)) {
			getSound()->playSound(kEntityNone, random(2) ? "CAT1010" : "CAT1010A");
		} else {
			getSound()->excuseMeCath();
		}
		return;
	}

	Entity::checkEntity(savepoint, true);
}

IMPLEMENT_FUNCTION(Tatiana, function14, 14)
	error("Tatiana: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function15, 15)
	error("Tatiana: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION_I(Tatiana, function16, 16)
	error("Tatiana: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, chapter1, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityTatiana, kAction191198209, 0);

		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject41, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->entityPosition = kPosition_5419;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function18, 18)
	error("Tatiana: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, chapter1Handler, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getSound()->isBuffered(kEntityTatiana) || !params->param4 || params->param3 == 2 || getSound()->isBuffered("TAT1066"))
			goto label_tatiana_chapter1_2;

		UPDATE_PARAM_FUNCTION(params->param5, getState()->timeTicks, 450, label_tatiana_chapter1_1);
		getSound()->playSound(kEntityTatiana, params->param3 ? "TAT1069B" : "TAT1069A");
		getProgress().field_64 = 1;
		params->param3++;
		params->param5 = 0;

label_tatiana_chapter1_1:
		if (getEntities()->isPlayerPosition(kCarRestaurant, 71)) {
			UPDATE_PARAM_FUNCTION(params->param6, getState()->timeTicks, 75, label_tatiana_chapter1_2);

			getSound()->playSound(kEntityTatiana, params->param3 ? "TAT1069B" : "TAT1069A");
			getProgress().field_64 = 1;
			params->param3++;
			params->param6 = 0;
		}

label_tatiana_chapter1_2:
		if (getState()->time > kTime1084500 && !params->param7) {
			params->param7 = 1;
			getSavePoints()->push(kEntityTatiana, kEntityPascale, kAction257489762);
		}

		if (params->param1) {
			UPDATE_PARAM(params->param8, getState()->timeTicks, 90);
			getScenes()->loadSceneFromPosition(kCarRestaurant, 65);
		} else {
			params->param8 = 0;
		}
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityTatiana, kEntityTables4, kAction136455232);
		getEntities()->drawSequenceLeft(kEntityTatiana, "014A");
		break;

	case kActionDrawScene:
		params->param1 = getEntities()->isPlayerPosition(kCarRestaurant, 67) ? 1 : 0;
		params->param4 = getEntities()->isPlayerPosition(kCarRestaurant, 69)
		              || getEntities()->isPlayerPosition(kCarRestaurant, 70)
		              || getEntities()->isPlayerPosition(kCarRestaurant, 71);
		break;

	case kAction122288808:
		getEntities()->drawSequenceLeft(kEntityTatiana, "014A");
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityTatiana, "BLANK");
		break;

	case kAction124973510:
		setup_function20();
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function20, 20)
	error("Tatiana: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function21, 21)
	error("Tatiana: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function22, 22)
	error("Tatiana: callback function 22 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Tatiana, setup_checkEntity), kCarRedSleeping, kPosition_7500);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Tatiana, setup_function14));
			break;

		case 2:
			setup_function24();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function24, 24)
	if (savepoint.action == kActionDefault) {

		getData()->entityPosition = kPosition_7500;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObject25, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectTrainTimeTable, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getEntities()->updatePosition(kEntityTatiana, kCarGreenSleeping, 70);
		getEntities()->updatePosition(kEntityTatiana, kCarGreenSleeping, 71);
		getEntities()->clearSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject41, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
	}
}

IMPLEMENT_FUNCTION(Tatiana, chapter2, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject41, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->entityPosition = kPosition_5420;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes2;
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, chapter2Handler, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime1800000 && params->param1 && getEntities()->checkFields11()) {
			getData()->inventoryItem = kItemNone;
			setup_function28();
		}
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;
		setup_function28();
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityTatiana, "024A");
		getSavePoints()->push(kEntityTatiana, kEntityTables5, kAction136455232);
		getData()->inventoryItem = kItemInvalid;
		break;

	case kActionDrawScene:
		if (getEntities()->isPlayerPosition(kCarRestaurant, 64) || getEntities()->isPlayerPosition(kCarRestaurant, 65)) {
			getData()->inventoryItem = kItemNone;
			setup_function27();
		}
		break;

	case kAction290869168:
		params->param1 = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function27, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(getEvent(kEventTatianaGivePoem) ? 1 : 2);
		call(new ENTITY_SETUP(Tatiana, setup_savegame), kSavegameType2, getEvent(kEventTatianaGivePoem) ? kEventTatianaBreakfastAlexei : kEventTatianaBreakfast);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			RESET_ENTITY_STATE(kEntityAlexei, Alexei, setup_function30);
			getAction()->playAnimation(kEventTatianaBreakfastAlexei);
			getInventory()->addItem(kItemParchemin);
			getInventory()->setLocationAndProcess(kItem11, kLocation1);
			setup_function28();
			break;

		case 2:
			RESET_ENTITY_STATE(kEntityAlexei, Alexei, setup_function30);
			getAction()->playAnimation(kEventTatianaBreakfast);
			if (getInventory()->hasItem(kItemParchemin)) {
				getAction()->playAnimation(kEventTatianaBreakfastGivePoem);
				getInventory()->removeItem(kItemParchemin);
			} else {
				getAction()->playAnimation(kEventTatianaAlexei);
			}
			setup_function28();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function28, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->inventoryItem = kItemNone;
		getData()->field_493 = kField493_0;

		getSavePoints()->push(kEntityTatiana, kEntityTables5, kAction103798704, "024D");
		getSavePoints()->push(kEntityTatiana, kEntityAlexei, kAction236053296, (getEvent(kEventTatianaBreakfastAlexei) || getEvent(kEventTatianaBreakfast)) ? 69 : 0);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function29();
		break;

	case kAction123857088:
		getEntities()->drawSequenceLeft(kEntityTatiana, "018G");

		setCallback(1);
		call(new ENTITY_SETUP(Tatiana, setup_updateFromTime), 1800);
		break;

	case kAction156444784:
		getData()->field_493 = kField493_1;
		getEntities()->drawSequenceLeft(kEntityTatiana, "BLANK");
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function29, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Tatiana, setup_function11));
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->field_493 = kField493_0;
			getEntities()->updatePosition(kEntityTatiana, kCarRestaurant, 63, true);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Tatiana, setup_callSavepoint), "018H", kEntityTables1, kAction103798704, "018A");
			break;

		case 2:
			getEntities()->updatePosition(kEntityTatiana, kCarRestaurant, 63);
			getSavePoints()->push(kEntityTatiana, kEntityServers1, kAction302203328);
			getEntities()->drawSequenceRight(kEntityTatiana, "805DS");

			if (getEntities()->checkFields13())
				getEntities()->updateEntity(kEntityTatiana);

			setCallback(3);
			call(new ENTITY_SETUP(Tatiana, setup_function8));
			break;

		case 3:
			setup_function30();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function30, 30)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Tatiana, setup_checkEntity), kCarRedSleeping, kPosition_7500);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Tatiana, setup_function14));
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Tatiana, setup_function16), kTimeEnd);
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, chapter3, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_1750;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes2;
		getData()->inventoryItem = kItemNone;

		// Update inventory
		getInventory()->getEntry(kItemFirebird)->location = kLocation2;

		if (getEvent(kEventTatianaBreakfastGivePoem) || (getEvent(kEventTatianaGivePoem) && !getEvent(kEventTatianaBreakfastAlexei)))
			getInventory()->getEntry(kItemParchemin)->location = kLocation2;

		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, chapter3Handler, 32)
	error("Tatiana: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function33, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);
		setCallback(1);
		call(new ENTITY_SETUP(Tatiana, setup_updateFromTime), 75);
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			call(new ENTITY_SETUP(Tatiana, setup_checkEntity), kCarRedSleeping, kPosition_7500);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Tatiana, setup_function14));
			break;

		case 3:
			setup_function34();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function34, 34)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Tatiana, setup_function16), kTime2097000);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getInventory()->getEntry(kItemFirebird)->location = kLocation1;
			if (getEntities()->checkFields19(kEntityNone, kCarRedSleeping, kPosition_7850))
				getScenes()->loadSceneFromObject(kObjectCompartmentB);

			getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject49, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
			call(new ENTITY_SETUP(Tatiana, setup_function15));
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Tatiana, setup_checkEntity), kCarKronos, kPosition_9270);
			break;

		case 3:
			setup_function35();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function35, 35)
	error("Tatiana: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function36, 36)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->car = kCarGreenSleeping;
		getData()->entityPosition = kPosition_850;
		getData()->field_493 = kField493_0;

		setCallback(1);
		call(new ENTITY_SETUP(Tatiana, setup_checkEntity), kCarGreenSleeping, kPosition_7500);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (!getEntities()->checkFields19(kEntityNone, kCarGreenSleeping, kPosition_7850) || getEntities()->checkFields1(kEntityNone, kCarRedSleeping, kPosition_8200)) {
				setCallback(2);
				call(new ENTITY_SETUP(Tatiana, setup_function14));
				break;
			}

			if (getInventory()->hasItem(kItemFirebird)) {
				getAction()->playAnimation(kEventTatianaCompartmentStealEgg);
				getInventory()->removeItem(kItemFirebird);
				getInventory()->getEntry(kItemFirebird)->location = kLocation2;
			} else {
				getAction()->playAnimation(kEventTatianaCompartment);
			}

			getScenes()->loadSceneFromObject(kObjectCompartmentB);
			break;

		case 2:
			setup_function37();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function37, 37)
	error("Tatiana: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function38, 38)
	error("Tatiana: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function39, 39)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param1 && getEntities()->checkFields9(kEntityTatiana, kEntityNone, 1000)) {
			params->param1 = 1;
			getSound()->playSound(kEntityTatiana, "Tat3164");	// Tatiana weeping
		}
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function40, 40)
	error("Tatiana: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function41, 41)
	error("Tatiana: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function42, 42)
	if (savepoint.action == kActionExcuseMeCath || savepoint.action == kActionExcuseMe) {
		getSound()->playSound(kEntityNone, "Tat3124", getEntities()->getSoundValue(kEntityTatiana));
		return;
	}

	Entity::checkEntity(savepoint);
}

IMPLEMENT_FUNCTION(Tatiana, chapter4, 43)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_7500;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothes2;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 1) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, chapter4Handler, 44)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Tatiana, setup_function16), kTime2362500);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function45();
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function45, 45)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Tatiana, setup_enterExitCompartment), "673Bb", kObjectCompartmentB);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentB, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
			getData()->field_493 = kField493_0;

			setCallback(1);
			call(new ENTITY_SETUP(Tatiana, setup_checkEntity), kCarGreenSleeping, kPosition_540);
			break;

		case 2:
			if (getEntities()->checkFields6()) {
				getSound()->excuseMe(kEntityTatiana);

				if (getEntities()->isPlayerPosition(kCarGreenSleeping, 62))
					getScenes()->loadSceneFromPosition(kCarGreenSleeping, 72);
			}

			getSavePoints()->push(kEntityTatiana, kEntityAlexei, kAction123712592);
			setup_function46();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function46, 46)
	error("Tatiana: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function47, 47)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		call(new ENTITY_SETUP(Tatiana, setup_checkEntity), kCarRedSleeping, kPosition_7500);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Tatiana, setup_enterExitCompartment2), "673Db", kObjectCompartmentB);
			break;

		case 2:
			getData()->field_493 = kField493_1;
			getEntities()->clearSequences(kEntityTatiana);

			setCallback(3);
			call(new ENTITY_SETUP(Tatiana, setup_function16), kTime2407500);
			break;

		case 3:
		case 4:
			if (ENTITY_PARAM(0, 1) && getObjects()->get(kObjectCompartment1).location2 == kLocation1) {
				setup_function48();
			} else {
				setCallback(4);
				call(new ENTITY_SETUP(Tatiana, setup_function16), 900);
			}
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function48, 48)
	error("Tatiana: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function49, 49)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_7500;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		break;

	case kAction169360385:
		setup_function50();
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, function50, 50)
	error("Tatiana: callback function 50 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function51, 51)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocation1, kCursorNormal, kCursorNormal);
		getObjects()->update(kObject48, kEntityNone, kLocation1, kCursorNormal, kCursorNormal);
	}
}

IMPLEMENT_FUNCTION(Tatiana, chapter5, 52)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);

		getData()->entityPosition = kPosition_3969;
		getData()->field_493 = kField493_1;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

IMPLEMENT_FUNCTION(Tatiana, chapter5Handler, 53)
	if (savepoint.action == kActionProceedChapter5)
		setup_function54();
}

IMPLEMENT_FUNCTION(Tatiana, function54, 54)
	error("Tatiana: callback function 54 not implemented!");
}

IMPLEMENT_FUNCTION(Tatiana, function55, 55)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);
		// fall back to next action

	case kActionDrawScene:
		if (getEntities()->isPlayerPosition(kCarRestaurant, 72))
			getScenes()->loadSceneFromPosition(kCarRestaurant, 86);
		break;
	}
}

} // End of namespace LastExpress
