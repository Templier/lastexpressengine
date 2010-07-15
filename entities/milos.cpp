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

#include "lastexpress/entities/milos.h"

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

Milos::Milos(LastExpressEngine *engine) : Entity(engine, kEntityMilos) {
	ADD_CALLBACK_FUNCTION(Milos, function1);
	ADD_CALLBACK_FUNCTION(Milos, draw);
	ADD_CALLBACK_FUNCTION(Milos, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Milos, enterExitCompartment2);
	ADD_CALLBACK_FUNCTION(Milos, function5);
	ADD_CALLBACK_FUNCTION(Milos, playSound);
	ADD_CALLBACK_FUNCTION(Milos, playSound16);
	ADD_CALLBACK_FUNCTION(Milos, savegame);
	ADD_CALLBACK_FUNCTION(Milos, updateFromTime);
	ADD_CALLBACK_FUNCTION(Milos, enterCompartmentDialog);
	ADD_CALLBACK_FUNCTION(Milos, function11);
	ADD_CALLBACK_FUNCTION(Milos, chapter1);
	ADD_CALLBACK_FUNCTION(Milos, function13);
	ADD_CALLBACK_FUNCTION(Milos, function14);
	ADD_CALLBACK_FUNCTION(Milos, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Milos, function16);
	ADD_CALLBACK_FUNCTION(Milos, function17);
	ADD_CALLBACK_FUNCTION(Milos, function18);
	ADD_CALLBACK_FUNCTION(Milos, chapter2);
	ADD_CALLBACK_FUNCTION(Milos, function20);
	ADD_CALLBACK_FUNCTION(Milos, function21);
	ADD_CALLBACK_FUNCTION(Milos, chapter3);
	ADD_CALLBACK_FUNCTION(Milos, function23);
	ADD_CALLBACK_FUNCTION(Milos, function24);
	ADD_CALLBACK_FUNCTION(Milos, function25);
	ADD_CALLBACK_FUNCTION(Milos, function26);
	ADD_CALLBACK_FUNCTION(Milos, function27);
	ADD_CALLBACK_FUNCTION(Milos, chapter4);
	ADD_CALLBACK_FUNCTION(Milos, function29);
	ADD_CALLBACK_FUNCTION(Milos, function30);
	ADD_CALLBACK_FUNCTION(Milos, function31);
	ADD_CALLBACK_FUNCTION(Milos, function32);
	ADD_CALLBACK_FUNCTION(Milos, chapter5);
	ADD_CALLBACK_FUNCTION(Milos, function34);
	ADD_CALLBACK_FUNCTION(Milos, prepareSequences);
}

IMPLEMENT_FUNCTION(Milos, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Milos, draw, 2)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SI(Milos, enterExitCompartment, 3)
	Entity::enterExitCompartment(savepoint);
}

// Seems to be exactly the same as the previous function
IMPLEMENT_FUNCTION_SI(Milos, enterExitCompartment2, 4)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION(Milos, function5, 5)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_S(Milos, playSound, 6)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_S(Milos, playSound16, 7)
	Entity::playSound(savepoint, false, 16);
}

IMPLEMENT_FUNCTION_II(Milos, savegame, 8)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_I(Milos, updateFromTime, 9)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_II(Milos, enterCompartmentDialog, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
	case kActionDefault:
		if (getEntities()->checkEntity(kEntityMilos, (CarIndex)params->param1, (EntityPosition)params->param2))
			CALLBACK_ACTION()
		break;

	case kActionExcuseMeCath:
	case kActionExcuseMe:
		if (getEvent(kEventMilosTylerCompartmentDefeat)) {
			// Robert saying: "Milos"
			switch(random(3)) {
			default:
			case 0:
				getSound()->playSound(kEntityNone, "CAT1014");
				break;

			case 1:
				getSound()->playSound(kEntityNone, "CAT1014A");
				break;

			case 2:
				getSound()->playSound(kEntityNone, "CAT1014B");
				break;
			}
		} else {
			getSound()->excuseMeCath();
		}
		break;
	}
}

//
IMPLEMENT_FUNCTION_I(Milos, function11, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		error("Milos: callback function 11 not implemented!");
		break;

	case kAction8:
	case kAction9:
		getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorNormal, kCursorNormal);

		if (params->param2) {
			if (getInventory()->hasItem(kItemPassengerList)) {
				setCallback(10);
				call(new ENTITY_SETUP_SIIS(Milos, setup_playSound), (random(2) ? "CAT1504" : getSound()->wrongDoorCath()));
			} else {
				setCallback(11);
				call(new ENTITY_SETUP_SIIS(Milos, setup_playSound), getSound()->wrongDoorCath());
			}
		} else {
			if (savepoint.action == kAction8) {
				setCallback(7);
				call(new ENTITY_SETUP_SIIS(Milos, setup_playSound), "LIB012");
			} else {
				setCallback(8);
				call(new ENTITY_SETUP_SIIS(Milos, setup_playSound), "LIB013");
			}
		}
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);
		break;

	case kAction17:
		if (params->param3 || params->param2) {
			getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);
			params->param3 = 0;
			params->param2 = 0;
		}
		break;

	case kActionCallback:
		switch(getCallback()) {
		default:
			break;

		case 1:
			getData()->field_493 = EntityData::kField493_0;
			setCallback(2);
			call(new ENTITY_SETUP(Milos, setup_enterCompartmentDialog), 3, 8200);
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Milos, setup_function14));
			break;

		case 3:
			if (getProgress().field_14 == 14)
				getProgress().field_14 = 0;

			params->param6 = 1;
			setCallback(4);
			call(new ENTITY_SETUP(Milos, setup_enterCompartmentDialog), kCarRedSleeping, 3050);
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP_SIIS(Milos, setup_enterExitCompartment), "609Bg", kObjectCompartmentG);
			break;

		case 5:
			getData()->field_493 = EntityData::kField493_1;
			getEntities()->prepareSequences(kEntityMilos);
			getSavePoints()->push(kEntityMilos, kEntityVesna, kAction101687594);
			getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);
			break;

		case 6:
			getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);
			break;

		case 7:
		case 8:
			setCallback(9);
			// Milos asking: "Yeah? Who is it?"
			call(new ENTITY_SETUP_SIIS(Milos, setup_playSound), "MIL1117A");
			break;

		case 9:
			getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorTalk, kCursorNormal);
			params->param2 = 1;
			break;

		case 10:
		case 11:
			params->param2 = 0;
			params->param3 = 1;
			break;

		case 12:
			getEntities()->drawSequenceLeft(kEntityMilos, "611Cg");
			getEntities()->enterCompartment(kEntityMilos, kObjectCompartmentG, false);
			getSavePoints()->push(kEntityMilos, kEntityCoudert, kAction88652208);
			break;

		case 13:
			getEntities()->exitCompartment(kEntityMilos, kObjectCompartmentG, false);
			getData()->field_493 = EntityData::kField493_1;
			getEntities()->prepareSequences(kEntityMilos);
			getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);
			params->param5 = 0;
			break;

		}
		break;

	case kAction122865568:
		getData()->field_493 = EntityData::kField493_0;
		setCallback(12);
		call(new ENTITY_SETUP_SIIS(Milos, setup_enterExitCompartment), "611Bg", kObjectCompartmentG);
		break;

	case kAction123852928:
		params->param1 = 13;
		call(new ENTITY_SETUP_SIIS(Milos, setup_enterExitCompartment), "611Dg", kObjectCompartmentG);
		break;

	case kAction221683008:
		params->param5 = 1;
		getSavePoints()->push(kEntityMilos, kEntityCoudert, kAction123199584);
		break;
	}
}

IMPLEMENT_FUNCTION(Milos, chapter1, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject46, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		getData()->position = kPosition_4689;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;

		getSavePoints()->addData(kEntityMilos, kAction157691176, 0);
		getSavePoints()->addData(kEntityMilos, kAction208228224, 2);
		getSavePoints()->addData(kEntityMilos, kAction259125998, 3);
		break;
	}
}

IMPLEMENT_FUNCTION(Milos, function13, 13)
	error("Milos: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function14, 14)
	error("Milos: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, chapter1_handler, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeMilos1_0 && !params->param3) {
			params->param3 = 1;
			getSavePoints()->push(kEntityMilos, kEntityServers1, kAction223002560);
		}

		if (getState()->time > kTimeMilos1_1 && getEntities()->checkFields11()) {
			setup_function16();
			break;
		}

		if (getEntities()->isPlayerPosition(kCarRestaurant, 61) && !params->param1) {
			UPDATE_PARAM_FUNCTION(params->param4, getState()->timeTicks, 45, label_checkNextPosition);

			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Milos, setup_draw), "009C");
			break;
		}

label_checkNextPosition:
		if (getEntities()->isPlayerPosition(kCarRestaurant, 70) && !params->param2) {
			UPDATE_PARAM(params->param5, getState()->timeTicks, 45);

			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Milos, setup_draw), "009C");
		}
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityMilos, kEntityTables2, kAction136455232);
		getEntities()->drawSequenceLeft(kEntityMilos, "009A");
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceLeft(kEntityMilos, "009A");
			params->param1 = 1;
			break;

		case 2:
			getEntities()->drawSequenceLeft(kEntityMilos, "009A");
			params->param2 = 1;
			break;
		}
		break;
	}

}

IMPLEMENT_FUNCTION(Milos, function16, 16)
	error("Milos: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function17, 17)
	if (savepoint.action == kActionDefault) {
		setCallback(1);
		call(new ENTITY_SETUP(Milos, setup_function11), kTimeBedTime);
	}
}

IMPLEMENT_FUNCTION(Milos, function18, 18)
	if (savepoint.action == kActionDefault) {
		getData()->position = kPosition_3050;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;

		getEntities()->prepareSequences(kEntityMilos);
		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
	}
}

IMPLEMENT_FUNCTION(Milos, chapter2, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function20();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityMilos);

		getData()->position = kPosition_4689;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRestaurant;

		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject46, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		break;
	}
}

IMPLEMENT_FUNCTION(Milos, function20, 20)
	error("Milos: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function21, 21)
	error("Milos: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, chapter3, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->events[kEventMilosCompartmentVisitAugust])
			setup_function24();
		else
			setup_function23();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityMilos);

		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);

		ENTITY_PARAM(0, 1) = 0;
		ENTITY_PARAM(0, 4) = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Milos, function23, 23)
	error("Milos: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function24, 24)
	error("Milos: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function25, 25)
	error("Milos: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION_I(Milos, function26, 26)
	error("Milos: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION_II(Milos, function27, 27)
	error("Milos: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, chapter4, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function29();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityMilos);

		getData()->position = kPosition_3050;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarRedSleeping;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Milos, function29, 29)
	error("Milos: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function30, 30)
	error("Milos: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function31, 31)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Milos, setup_enterExitCompartment), "609CG", kObjectCompartmentG);
		break;

	case kActionCallback:
		switch (getCallback()) {
		case 1:
			getData()->field_493 = EntityData::kField493_0;
			getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

			setCallback(2);
			call(new ENTITY_SETUP(Milos, setup_enterCompartmentDialog), kCarGreenSleeping, kPosition_540);
			break;

		case 2:
			setup_function32();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Milos, function32, 32)
	if (savepoint.action == kActionDefault) {
		getEntities()->prepareSequences(kEntityMilos);
		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		getData()->position = kPosition_540;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarCoalTender;
		getData()->inventoryItem = kItemNone;
	}
}

IMPLEMENT_FUNCTION(Milos, chapter5, 33)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function34();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityMilos);

		getData()->position = kPosition_540;
		getData()->field_493 = EntityData::kField493_1;
		getData()->car = kCarCoalTender;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Milos, function34, 34)
	error("Milos: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, prepareSequences, 35)
	if (savepoint.action == kActionDefault) {
		getEntities()->prepareSequences(kEntityMilos);
	}
}

} // End of namespace LastExpress
