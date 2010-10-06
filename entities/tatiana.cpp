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
	ADD_CALLBACK_FUNCTION(Tatiana, callbackActionOnDirection);
	ADD_CALLBACK_FUNCTION(Tatiana, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Tatiana, updateFromTime);
	ADD_CALLBACK_FUNCTION(Tatiana, callbackActionRestaurantOrSalon);
	ADD_CALLBACK_FUNCTION(Tatiana, savegame);
	ADD_CALLBACK_FUNCTION(Tatiana, updateEntity);
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(1, Tatiana, reset)
	Entity::reset(savepoint, true);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(2, Tatiana, playSound)
	Entity::playSound(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(3, Tatiana, draw)
	Entity::draw(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SII(4, Tatiana, updatePosition, CarIndex, Position)
	Entity::updatePosition(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(5, Tatiana, enterExitCompartment, ObjectIndex)
	Entity::enterExitCompartment(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(6, Tatiana, enterExitCompartment2, ObjectIndex)
	Entity::enterExitCompartment(savepoint, kPosition_7500, kPosition_7850, kCarRedSleeping, kObjectCompartmentB);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SIIS(7, Tatiana, callSavepoint, EntityIndex, ActionIndex)
	Entity::callSavepoint(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(8, Tatiana, callbackActionOnDirection)
	Entity::callbackActionOnDirection(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_NOSETUP(9, Tatiana, updateFromTicks)
	Entity::updateFromTicks(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(10, Tatiana, updateFromTime, uint32)
	Entity::updateFromTime(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(11, Tatiana, callbackActionRestaurantOrSalon)
	Entity::callbackActionRestaurantOrSalon(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(12, Tatiana, savegame, SavegameType, uint32)
	Entity::savegame(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(13, Tatiana, updateEntity, CarIndex, EntityPosition)
	if (savepoint.action == kActionExcuseMeCath) {
		if (getEvent(kEventTatianaAskMatchSpeakRussian) || getEvent(kEventTatianaAskMatch) || getEvent(kEventVassiliSeizure)) {
			getSound()->playSound(kEntityPlayer, rnd(2) ? "CAT1010" : "CAT1010A");
		} else {
			getSound()->excuseMeCath();
		}
		return;
	}

	Entity::updateEntity(savepoint, true);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(14, Tatiana, function14)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityTatiana, kEntityCoudert, kAction326348944);
		getEntities()->drawSequenceLeft(kEntityTatiana, getProgress().chapter == kChapter1 ? "603Fb" : "673Fb");
		getEntities()->enterCompartment(kEntityTatiana, kObjectCompartmentB, true);
		break;

	case kActionCallback:
		if (getCallback() == 1 || getCallback() == 2) {
			getEntities()->exitCompartment(kEntityTatiana, kObjectCompartmentB, true);
			getData()->location = kLocationInsideCompartment;
			getEntities()->clearSequences(kEntityTatiana);

			CALLBACK_ACTION();
		}
		break;

	case kAction69239528:
		setCallback(getProgress().chapter == kChapter1 ? 1 : 2);
		setup_enterExitCompartment2(getProgress().chapter == kChapter1 ? "603Db" : "673Db", kObjectCompartmentB);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(15, Tatiana, function15)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(getProgress().chapter == kChapter1 ? 1 : 2);
		setup_enterExitCompartment2(getProgress().chapter == kChapter1 ? "603Bb" : "673Bb", kObjectCompartmentB);
		break;

	case kActionCallback:
		if (getCallback() == 1 || getCallback() == 2) {
			getData()->location = kLocationOutsideCompartment;
			getSavePoints()->push(kEntityTatiana, kEntityCoudert, kAction292048641);

			getEntities()->drawSequenceLeft(kEntityTatiana, getProgress().chapter == kChapter1 ? "603Fb" : "673Fb");
			getEntities()->enterCompartment(kEntityTatiana, kObjectCompartmentB, true);
		}
		break;

	case kAction69239528:
		getEntities()->exitCompartment(kEntityTatiana, kObjectCompartmentB, true);
		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);

		CALLBACK_ACTION();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_I(16, Tatiana, function16, uint32)
	error("Tatiana: callback function 16 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(17, Tatiana, chapter1)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getSavePoints()->addData(kEntityTatiana, kAction191198209, 0);

		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject41, kEntityPlayer, kObjectLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->entityPosition = kPosition_5419;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(18, Tatiana, function18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param1) {

			if (getState()->time > kTime1143000 && !params->param2) {
				params->param2 = 1;
				getEntities()->drawSequenceRight(kEntityTatiana, "806DS");
				params->param1 = 1;
			}

			if (!params->param1) {
				UPDATE_PARAM_PROC(params->param3, getState()->time, 4500)
					getEntities()->drawSequenceRight(kEntityTatiana, "806DS");
					params->param1 = 1;
				UPDATE_PARAM_PROC_END
			}
		}

		if (getData()->entityPosition <= kPosition_2330) {
			getSavePoints()->push(kEntityTatiana, kEntityAlexei, kAction157159392);
			getEntities()->clearSequences(kEntityTatiana);

			CALLBACK_ACTION();
		}
		break;

	case kActionExitCompartment:
		getSavePoints()->push(kEntityTatiana, kEntityAlexei, kAction188784532);

		CALLBACK_ACTION();
		break;

	case kActionDefault:
		if (getEntities()->isInSalon(kEntityPlayer)) {
			getEntities()->drawSequenceRight(kEntityTatiana, "806DS");
			params->param1 = 1;
		} else {
			getEntities()->clearSequences(kEntityTatiana);
		}
		break;

	case kActionDrawScene:
		if (!params->param1 && getEntities()->isInSalon(kEntityPlayer)) {
			getEntities()->drawSequenceRight(kEntityTatiana, "806DS");
			getEntities()->updateFrame(kEntityTatiana);
			params->param1 = 1;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(19, Tatiana, chapter1Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getSound()->isBuffered(kEntityTatiana) || !params->param4 || params->param3 == 2 || getSound()->isBuffered("TAT1066"))
			goto label_tatiana_chapter1_2;

		UPDATE_PARAM_PROC(params->param5, getState()->timeTicks, 450)
			getSound()->playSound(kEntityTatiana, params->param3 ? "TAT1069B" : "TAT1069A");
			getProgress().field_64 = 1;
			params->param3++;
			params->param5 = 0;
		UPDATE_PARAM_PROC_END

		if (getEntities()->isPlayerPosition(kCarRestaurant, 71)) {
			UPDATE_PARAM_PROC(params->param6, getState()->timeTicks, 75)
				getSound()->playSound(kEntityTatiana, params->param3 ? "TAT1069B" : "TAT1069A");
				getProgress().field_64 = 1;
				params->param3++;
				params->param6 = 0;
			UPDATE_PARAM_PROC_END
		}

label_tatiana_chapter1_2:
		TIME_CHECK_SAVEPOINT(kTime1084500, params->param7, kEntityTatiana, kEntityPascale, kAction257489762);

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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(20, Tatiana, function20)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_callbackActionRestaurantOrSalon();
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->location = kLocationOutsideCompartment;
			getSavePoints()->push(kEntityTatiana, kEntityAugust, kAction223183000);
			getEntities()->updatePositionEnter(kEntityTatiana, kCarRestaurant, 67);
			getSound()->playSound(kEntityTatiana, "TAT1070");

			setCallback(2);
			setup_callSavepoint("014C", kEntityTables4, kActionDrawTablesWithChairs, "014D");
			break;

		case 2:
			getEntities()->updatePositionExit(kEntityTatiana, kCarRestaurant, 67);
			getSavePoints()->push(kEntityTatiana, kEntityServers0, kAction188893625);

			setCallback(3);
			setup_function18();
			break;

		case 3:
			getSavePoints()->push(kEntityTatiana, kEntityAugust, kAction268620864);
			setup_function21();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(21, Tatiana, function21)
	error("Tatiana: callback function 21 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(22, Tatiana, function22)
	error("Tatiana: callback function 22 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(23, Tatiana, function23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_updateEntity(kCarRedSleeping, kPosition_7500);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_function14();
			break;

		case 2:
			setup_function24();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(24, Tatiana, function24)
	if (savepoint.action == kActionDefault) {

		getData()->entityPosition = kPosition_7500;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObject25, kEntityPlayer, kObjectLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObjectTrainTimeTable, kEntityPlayer, kObjectLocationNone, kCursorKeepValue, kCursorKeepValue);

		getEntities()->updatePositionExit(kEntityTatiana, kCarGreenSleeping, 70);
		getEntities()->updatePositionExit(kEntityTatiana, kCarGreenSleeping, 71);
		getEntities()->clearSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject41, kEntityPlayer, kObjectLocationNone, kCursorKeepValue, kCursorKeepValue);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(25, Tatiana, chapter2)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject41, kEntityPlayer, kObjectLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->entityPosition = kPosition_5420;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes2;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(26, Tatiana, chapter2Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime1800000 && params->param1 && getEntities()->isSomebodyInsideRestaurantOrSalon()) {
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(27, Tatiana, function27)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(getEvent(kEventTatianaGivePoem) ? 1 : 2);
		setup_savegame(kSavegameTypeEvent, getEvent(kEventTatianaGivePoem) ? kEventTatianaBreakfastAlexei : kEventTatianaBreakfast);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			RESET_ENTITY_STATE(kEntityAlexei, Alexei, setup_function30);
			getAction()->playAnimation(kEventTatianaBreakfastAlexei);
			getInventory()->addItem(kItemParchemin);
			getInventory()->setLocationAndProcess(kItem11, kObjectLocation1);
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(28, Tatiana, function28)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->inventoryItem = kItemNone;
		getData()->location = kLocationOutsideCompartment;

		getSavePoints()->push(kEntityTatiana, kEntityTables5, kActionDrawTablesWithChairs, "024D");
		getSavePoints()->push(kEntityTatiana, kEntityAlexei, kAction236053296, (getEvent(kEventTatianaBreakfastAlexei) || getEvent(kEventTatianaBreakfast)) ? 69 : 0);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function29();
		break;

	case kAction123857088:
		getEntities()->drawSequenceLeft(kEntityTatiana, "018G");

		setCallback(1);
		setup_updateFromTime(1800);
		break;

	case kAction156444784:
		getData()->location = kLocationInsideCompartment;
		getEntities()->drawSequenceLeft(kEntityTatiana, "BLANK");
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(29, Tatiana, function29)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_callbackActionRestaurantOrSalon();
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getData()->location = kLocationOutsideCompartment;
			getEntities()->updatePositionEnter(kEntityTatiana, kCarRestaurant, 63);

			setCallback(2);
			setup_callSavepoint("018H", kEntityTables1, kActionDrawTablesWithChairs, "018A");
			break;

		case 2:
			getEntities()->updatePositionExit(kEntityTatiana, kCarRestaurant, 63);
			getSavePoints()->push(kEntityTatiana, kEntityServers1, kAction302203328);
			getEntities()->drawSequenceRight(kEntityTatiana, "805DS");

			if (getEntities()->isInRestaurant(kEntityPlayer))
				getEntities()->updateFrame(kEntityTatiana);

			setCallback(3);
			setup_callbackActionOnDirection();
			break;

		case 3:
			setup_function30();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(30, Tatiana, function30)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_updateEntity(kCarRedSleeping, kPosition_7500);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_function14();
			break;

		case 2:
			setCallback(3);
			setup_function16(kTimeEnd);
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(31, Tatiana, chapter3)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_1750;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothes2;
		getData()->inventoryItem = kItemNone;

		// Update inventory
		getInventory()->get(kItemFirebird)->location = kObjectLocation2;

		if (getEvent(kEventTatianaBreakfastGivePoem) || (getEvent(kEventTatianaGivePoem) && !getEvent(kEventTatianaBreakfastAlexei)))
			getInventory()->get(kItemParchemin)->location = kObjectLocation2;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(32, Tatiana, chapter3Handler)
	EntityData::EntityParametersI5S  *parameters = (EntityData::EntityParametersI5S*)_data->getCurrentParameters();
	EntityData::EntityParametersSIII *parameters1 = (EntityData::EntityParametersSIII*)_data->getCurrentParameters(1);

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!parameters->param2 && !parameters->param5) {
			parameters->param1 -= getState()->timeDelta;

			if (getState()->timeDelta > parameters->param1) {

				getEntities()->drawSequenceLeft(kEntityTatiana, (char *)&parameters1->seq);
				getSound()->playSound(kEntityTatiana, (char *)&parameters->seq);

				if (parameters->param3 == 4 && getEntities()->isInSalon(kEntityPlayer))
					getProgress().field_90 = 1;

				parameters->param2 = 1;
			}
		}

		if (parameters->param4 && parameters->param5) {
			UPDATE_PARAM_CHECK(parameters->param4, getState()->time, 6300)
				if (getEntities()->isSomebodyInsideRestaurantOrSalon()) {
					getData()->location = kLocationOutsideCompartment;

					setCallback(1);
					setup_updatePosition("110E", kCarRestaurant, 52);
				}
			}
		}
		break;

	case  kAction2:
		parameters->param2 = 0;
		++parameters->param3;

		switch (parameters->param3) {
		default:
			parameters->param5 = 1;
			break;

		case 1:
			parameters->param1 = 900;
			getEntities()->drawSequenceLeft(kEntityTatiana, "110A");
			strcpy((char *)&parameters->seq, "Tat3160B");
			strcpy((char *)&parameters1->seq, "110A");
			break;

		case 2:
			parameters->param1 = 9000;
			strcpy((char *)&parameters->seq, "Tat3160C");
			strcpy((char *)&parameters1->seq, "110C");
			break;

		case 3:
			parameters->param1 = 13500;
			getEntities()->drawSequenceLeft(kEntityTatiana, "110B");
			strcpy((char *)&parameters->seq, "Tat3160D");
			strcpy((char *)&parameters1->seq, "110D");
			break;

		case 4:
			parameters->param1 = 9000;
			getEntities()->drawSequenceLeft(kEntityTatiana, "110B");
			strcpy((char *)&parameters->seq, "Tat3160E");
			strcpy((char *)&parameters1->seq, "110D");
			break;

		case 5:
			parameters->param1 = 4500;
			getEntities()->drawSequenceLeft(kEntityTatiana, "110B");
			strcpy((char *)&parameters->seq, "Tat3160G");
			strcpy((char *)&parameters1->seq, "110D");
			break;

		case 6:
			parameters->param1 = 4500;
			getEntities()->drawSequenceLeft(kEntityTatiana, "110B");
			strcpy((char *)&parameters->seq, "Tat3160B");
			break;
		}
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityTatiana, kEntityAlexei, kAction122358304);
		getSavePoints()->push(kEntityTatiana, kEntityKronos, kAction157159392);
		getEntities()->drawSequenceLeft(kEntityTatiana, "110C");
		getSound()->playSound(kEntityTatiana, "Tat3160A");

		parameters->param2 = 1;
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getSavePoints()->push(kEntityTatiana, kEntityAlexei, kAction122288808);
			setup_function33();
		}
		break;

	case kAction101169422:
		parameters->param4 = 1;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(33, Tatiana, function33)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);
		setCallback(1);
		setup_updateFromTime(75);
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			setCallback(2);
			setup_updateEntity(kCarRedSleeping, kPosition_7500);
			break;

		case 2:
			setCallback(3);
			setup_function14();
			break;

		case 3:
			setup_function34();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(34, Tatiana, function34)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function16(kTime2097000);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getInventory()->get(kItemFirebird)->location = kObjectLocation1;
			if (getEntities()->checkFields19(kEntityPlayer, kCarRedSleeping, kPosition_7850))
				getScenes()->loadSceneFromObject(kObjectCompartmentB);

			getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject49, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
			setup_function15();
			break;

		case 2:
			setCallback(3);
			setup_updateEntity(kCarKronos, kPosition_9270);
			break;

		case 3:
			setup_function35();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(35, Tatiana, function35)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param1
		 && getInventory()->hasItem(kItemFirebird)
		 && getEntities()->checkFields19(kEntityPlayer, kCarRedSleeping, kPosition_7850)
		 && (getState()->time < kTime2133000 || getProgress().field_40)) {
			setCallback(1);
			setup_function41();
			break;
		}

label_callback_1:
		if (getState()->time > kTime2133000) {
			if (getData()->car >= kCarRedSleeping || (getData()->car == kCarGreenSleeping && getData()->entityPosition > kPosition_5790))
				setup_function36();
		}
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getEntities()->clearSequences(kEntityTatiana);

		getData()->car = kCarKronos;
		getData()->entityPosition = kPosition_6000;
		getData()->location = kLocationInsideCompartment;
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			params->param1 = 1;
			goto label_callback_1;
		}
		break;

	case kAction191668032:
		setup_function36();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(36, Tatiana, function36)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->car = kCarGreenSleeping;
		getData()->entityPosition = kPosition_850;
		getData()->location = kLocationOutsideCompartment;

		setCallback(1);
		setup_updateEntity(kCarGreenSleeping, kPosition_7500);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			if (!getEntities()->checkFields19(kEntityPlayer, kCarGreenSleeping, kPosition_7850) || getEntities()->isInsideCompartment(kEntityPlayer, kCarRedSleeping, kPosition_8200)) {
				setCallback(2);
				setup_function14();
				break;
			}

			if (getInventory()->hasItem(kItemFirebird)) {
				getAction()->playAnimation(kEventTatianaCompartmentStealEgg);
				getInventory()->removeItem(kItemFirebird);
				getInventory()->get(kItemFirebird)->location = kObjectLocation2;
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(37, Tatiana, function37)
	error("Tatiana: callback function 37 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(38, Tatiana, function38)
	error("Tatiana: callback function 38 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(39, Tatiana, function39)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param1 && getEntities()->isDistanceBetweenEntities(kEntityTatiana, kEntityPlayer, 1000)) {
			params->param1 = 1;
			getSound()->playSound(kEntityTatiana, "Tat3164");	// Tatiana weeping
		}
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(40, Tatiana, function40)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->isInsideTrainCar(kEntityPlayer, kCarKronos)
		 || getData()->car != getEntityData(kEntityPlayer)->car
		 || getEntities()->updateEntity(kEntityTatiana, kCarKronos, kPosition_9270))
			CALLBACK_ACTION();
		break;

	case kActionExcuseMe:
		if (getEvent(kEventTatianaAskMatchSpeakRussian) || getEvent(kEventTatianaAskMatch) || getEvent(kEventVassiliSeizure))
			getSound()->playSound(kEntityPlayer, rnd(2) ? "CAT1001A" : "CAT1010");
		else
			getSound()->excuseMeCath();
		break;

	case kActionDefault:
		if (getEntities()->updateEntity(kEntityTatiana, kCarKronos, kPosition_9270))
			CALLBACK_ACTION();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(41, Tatiana, function41)
	error("Tatiana: callback function 41 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(42, Tatiana, function42)
	if (savepoint.action == kActionExcuseMeCath || savepoint.action == kActionExcuseMe) {
		getSound()->playSound(kEntityPlayer, "Tat3124", getSound()->getSoundFlag(kEntityTatiana));
		return;
	}

	Entity::updateEntity(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(43, Tatiana, chapter4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);

		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_7500;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothes2;
		getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 1) = 0;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(44, Tatiana, chapter4Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_function16(kTime2362500);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_function45();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(45, Tatiana, function45)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_enterExitCompartment("673Bb", kObjectCompartmentB);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
			getData()->location = kLocationOutsideCompartment;

			setCallback(1);
			setup_updateEntity(kCarGreenSleeping, kPosition_540);
			break;

		case 2:
			if (getEntities()->isInGreenCarEntrance(kEntityPlayer)) {
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(46, Tatiana, function46)
	error("Tatiana: callback function 46 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(47, Tatiana, function47)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		setCallback(1);
		setup_updateEntity(kCarRedSleeping, kPosition_7500);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			setup_enterExitCompartment2("673Db", kObjectCompartmentB);
			break;

		case 2:
			getData()->location = kLocationInsideCompartment;
			getEntities()->clearSequences(kEntityTatiana);

			setCallback(3);
			setup_function16(kTime2407500);
			break;

		case 3:
		case 4:
			if (ENTITY_PARAM(0, 1) && getObjects()->get(kObjectCompartment1).location2 == kObjectLocation1) {
				setup_function48();
			} else {
				setCallback(4);
				setup_function16(900);
			}
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(48, Tatiana, function48)
	error("Tatiana: callback function 48 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(49, Tatiana, function49)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_7500;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);
		break;

	case kAction169360385:
		setup_function50();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(50, Tatiana, function50)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime2520000 && !params->param1) {
			params->param1 = 1;
			setup_function51();
		}
		break;

	case kAction2:
		getSound()->playSound(kEntityTatiana, "Tat4166");
		break;

	case kActionKnock:
		if (!getSound()->isBuffered("LIB012", true))
			getSound()->playSound(kEntityPlayer, "LIB012");
		break;

	case kActionOpenDoor:
		getSound()->playSound(kEntityPlayer, "LIB014");

		setCallback(1);
		setup_savegame(kSavegameTypeEvent, kEventVassiliDeadAlexei);
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_8200;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject48, kEntityTatiana, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentA, kEntityTatiana, kObjectLocationNone, kCursorHandKnock, kCursorHand);

		if (!getSound()->isBuffered(kEntityTatiana))
			getSound()->playSound(kEntityTatiana, "Tat4166");
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			if (getSound()->isBuffered("MUS013"))
				getSound()->processEntry("MUS013");

			getAction()->playAnimation(kEventVassiliDeadAlexei);
			getSavePoints()->push(kEntityTatiana, kEntityAbbot, kAction104060776);
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 38);

			setup_function51();
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(51, Tatiana, function51)
	if (savepoint.action == kActionDefault) {
		getObjects()->update(kObjectCompartmentA, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorNormal);
		getObjects()->update(kObject48, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorNormal);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(52, Tatiana, chapter5)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter5Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTatiana);

		getData()->entityPosition = kPosition_3969;
		getData()->location = kLocationInsideCompartment;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(53, Tatiana, chapter5Handler)
	if (savepoint.action == kActionProceedChapter5)
		setup_function54();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(54, Tatiana, function54)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!params->param2) {
			switch (params->param1) {
			default:
				break;

			case 0:
				getSound()->playSound(kEntityTatiana, "Tat5167A");
				params->param2 = 1;
				break;

			case 1:
				getSound()->playSound(kEntityTatiana, "Tat5167B");
				params->param2 = 1;
				break;

			case 2:
				getSound()->playSound(kEntityTatiana, "Tat5167C");
				params->param2 = 1;
				break;

			case 3:
				getSound()->playSound(kEntityTatiana, "Tat5167D");
				params->param2 = 1;
				break;
			}
		}

		if (params->param1 > 3) {
			UPDATE_PARAM(params->param3, getState()->timeTicks, 225);

			params->param1 = 0;
			params->param3 = 0;
		}
		break;

	case kAction1:
		getData()->inventoryItem = kItemNone;

		setCallback(1);
		setup_savegame(kSavegameTypeEvent, kEventTatianaVassiliTalk);
		break;

	case kAction2:
		++params->param1;
		params->param2 = 0;
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityTatiana, "033A");
		getData()->inventoryItem = kItemInvalid;
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			if (getSound()->isBuffered("MUS050"))
				getSound()->processEntry("MUS050");

			if (getSound()->isBuffered(kEntityTatiana))
				getSound()->processEntry(kEntityTatiana);

			getAction()->playAnimation(isNight() ? kEventTatianaVassiliTalkNight : kEventTatianaVassiliTalk);
			getScenes()->processScene();

			params->param1 = 4;
			params->param2 = 0;
			params->param3 = 0;
		}
		break;

	case kAction203078272:
		getEntities()->drawSequenceLeft(kEntityTatiana, "033E");
		break;

	case kAction236060709:
		getData()->inventoryItem = kItemNone;
		setup_function55();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(55, Tatiana, function55)
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
