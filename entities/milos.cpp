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
	ADD_CALLBACK_FUNCTION(Milos, function3);
	ADD_CALLBACK_FUNCTION(Milos, function4);
	ADD_CALLBACK_FUNCTION(Milos, function5);
	ADD_CALLBACK_FUNCTION(Milos, playSound);
	ADD_CALLBACK_FUNCTION(Milos, playSound16);
	ADD_CALLBACK_FUNCTION(Milos, savegame);
	ADD_CALLBACK_FUNCTION(Milos, updateFromTime);
	ADD_CALLBACK_FUNCTION(Milos, enterCompartementDialog);
	ADD_CALLBACK_FUNCTION(Milos, function11);
	ADD_CALLBACK_FUNCTION(Milos, chapter1);
	ADD_CALLBACK_FUNCTION(Milos, function13);
	ADD_CALLBACK_FUNCTION(Milos, function14);
	ADD_CALLBACK_FUNCTION(Milos, function15);
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
	ADD_CALLBACK_FUNCTION(Milos, drawSequences);
}

IMPLEMENT_FUNCTION(Milos, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Milos, draw, 2)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SI(Milos, function3, 3)
	Entity::updateFields(savepoint);
}

// Seems to be exactly the same as the previous function
IMPLEMENT_FUNCTION_SI(Milos, function4, 4)
	Entity::updateFields(savepoint);
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

IMPLEMENT_FUNCTION_II(Milos, enterCompartementDialog, 10)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
	case kActionDefault:
		if (getEntities()->checkEntity(kEntityMilos, (EntityData::Field495Value)CURRENT_PARAM(1), (EntityData::Field491Value)CURRENT_PARAM(2)))
			CALL_PREVIOUS_SAVEPOINT()
		break;

	case kAction5:
	case kAction6:
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

IMPLEMENT_FUNCTION_I(Milos, function11, 11)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		error("Milos: callback function 11 not implemented!");
		break;

	case kAction8:
	case kAction9:
		getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorNormal, kCursorNormal);

		if (CURRENT_PARAM(2)) {			
			if (getInventory()->hasItem(kItemPassengerList)) {
				_data->setNextCallback(10);
				call(new ENTITY_SETUP_SIIS(Milos, setup_playSound), (random(2) ? "CAT1504" : getSound()->wrongDoorCath()));
			} else {
				_data->setNextCallback(11);
				call(new ENTITY_SETUP_SIIS(Milos, setup_playSound), getSound()->wrongDoorCath());
			}
		} else {
			if (savepoint->action == kAction8) {
				_data->setNextCallback(7);
				call(new ENTITY_SETUP_SIIS(Milos, setup_playSound), "LIB012");
			} else {
				_data->setNextCallback(8);
				call(new ENTITY_SETUP_SIIS(Milos, setup_playSound), "LIB013");
			}
		}
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);
		break;

	case kAction17:
		if (CURRENT_PARAM(3) || CURRENT_PARAM(2)) {
			getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);
			CURRENT_PARAM(3) = 0;
			CURRENT_PARAM(2) = 0;
		}
		break;

	case kAction18:
		switch(_data->getNextCallback()) {
		default:
			break;

		case 1:
			_data->getData()->field_493 = EntityData::kField493_0;
			_data->setNextCallback(2);
			call(new ENTITY_SETUP(Milos, setup_enterCompartementDialog), 3, 8200);
			break;

		case 2:
			_data->setNextCallback(3);
			call(new ENTITY_SETUP(Milos, setup_function14));
			break;

		case 3:
			if (getProgress().field_14 == 14)
				getProgress().field_14 = 0;

			CURRENT_PARAM(6) = 1;
			_data->setNextCallback(4);
			call(new ENTITY_SETUP(Milos, setup_enterCompartementDialog), 4, 3050);
			break;

		case 4:
			_data->setNextCallback(5);
			call(new ENTITY_SETUP_SIIS(Milos, setup_function3), "609Bg", 38);
			break;

		case 5:
			_data->getData()->field_493 = EntityData::kField493_1;
			getEntities()->drawSequences(kEntityMilos);
			getSavePoints()->push(kEntityMilos, kEntityVesna, kAction101687594);
			getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);
			break;

		case 6:
			getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);
			break;

		case 7:
		case 8:
			_data->setNextCallback(9);
			// Milos asking: "Yeah? Who is it?"
			call(new ENTITY_SETUP_SIIS(Milos, setup_playSound), "MIL1117A");
			break;

		case 9:
			getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorTalk, kCursorNormal);
			CURRENT_PARAM(2) = 1;
			break;

		case 10:
		case 11:
			CURRENT_PARAM(2) = 0;
			CURRENT_PARAM(3) = 1;
			break;

		case 12:
			getEntities()->drawSequenceLeft(kEntityMilos, "611Cg");
			getEntities()->updateField1000_4(kEntityMilos, kObjectCompartmentG);
			getSavePoints()->push(kEntityMilos, kEntityCoudert, kAction88652208);
			break;

		case 13:
			getEntities()->updateField1000_5(kEntityMilos, kObjectCompartmentG);
			_data->getData()->field_493 = EntityData::kField493_1;
			getEntities()->drawSequences(kEntityMilos);
			getObjects()->update(kObjectCompartmentG, kEntityMilos, kLocation3, kCursorHandKnock, kCursorHand);
			CURRENT_PARAM(5) = 0;
			break;

		}
		break;

	case kAction122865568:
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->setNextCallback(12);
		call(new ENTITY_SETUP_SIIS(Milos, setup_function3), "611Bg", 38);
		break;

	case kAction123852928:
		CURRENT_PARAM(1) = 13;
		call(new ENTITY_SETUP_SIIS(Milos, setup_function3), "611Dg", 38);
		break;

	case kAction221683008:
		CURRENT_PARAM(5) = 1;
		getSavePoints()->push(kEntityMilos, kEntityCoudert, kAction123199584);
		break;
	}
}

IMPLEMENT_FUNCTION(Milos, chapter1, 12)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(15)
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject46, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_4689;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;

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

IMPLEMENT_FUNCTION(Milos, function15, 15)
	error("Milos: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function16, 16)
	error("Milos: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function17, 17)
	error("Milos: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function18, 18)
	error("Milos: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, chapter2, 19)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function20();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityMilos);

		_data->getData()->field_491 = EntityData::kField491_4689;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;

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
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		if (getState()->events[kEventMilosCompartmentVisitAugust])
			setup_function24();
		else
			setup_function23();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityMilos);

		_data->getData()->clothes = EntityData::kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

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
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function29();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityMilos);

		_data->getData()->field_491 = EntityData::kField491_3050;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_4;
		_data->getData()->inventoryItem = kItemNone;

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
	error("Milos: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, function32, 32)
	if (savepoint->action == kActionDefault) {
		getEntities()->drawSequences(kEntityMilos);
		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);

		_data->getData()->field_491 = EntityData::kField491_540;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_7;
		_data->getData()->inventoryItem = kItemNone;
	}
}

IMPLEMENT_FUNCTION(Milos, chapter5, 33)
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function34();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityMilos);

		_data->getData()->field_491 = EntityData::kField491_540;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_7;
		_data->getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION(Milos, function34, 34)
	error("Milos: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Milos, drawSequences, 35)
	if (savepoint->action == kActionDefault) {
		getEntities()->drawSequences(kEntityMilos);
	}
}

} // End of namespace LastExpress
