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

#include "lastexpress/entities/vassili.h"

#include "lastexpress/entities/anna.h"
#include "lastexpress/entities/coudert.h"

#include "lastexpress/game/action.h"
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

Vassili::Vassili(LastExpressEngine *engine) : Entity(engine, kEntityVassili) {
	ADD_CALLBACK_FUNCTION(Vassili, function1);
	ADD_CALLBACK_FUNCTION(Vassili, draw);
	ADD_CALLBACK_FUNCTION(Vassili, savegame);
	ADD_CALLBACK_FUNCTION(Vassili, chapter1);
	ADD_CALLBACK_FUNCTION(Vassili, function5);
	ADD_CALLBACK_FUNCTION(Vassili, function6);
	ADD_CALLBACK_FUNCTION(Vassili, function7);
	ADD_CALLBACK_FUNCTION(Vassili, function8);
	ADD_CALLBACK_FUNCTION(Vassili, function9);
	ADD_CALLBACK_FUNCTION(Vassili, seizure);
	ADD_CALLBACK_FUNCTION(Vassili, drawInBed);
	ADD_CALLBACK_FUNCTION(Vassili, chapter2);
	ADD_CALLBACK_FUNCTION(Vassili, sleeping);
	ADD_CALLBACK_FUNCTION(Vassili, chapter3);
	ADD_CALLBACK_FUNCTION(Vassili, stealEgg);
	ADD_CALLBACK_FUNCTION(Vassili, chapter4);
	ADD_CALLBACK_FUNCTION(Vassili, function17);
	ADD_CALLBACK_FUNCTION(Vassili, chapter5);
}

IMPLEMENT_FUNCTION(Vassili, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Vassili, draw, 2)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_II(Vassili, savegame, 3)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION(Vassili, chapter1, 4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(5)
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject40, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, function5, 5)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1) {
			_data->getData()->field_491 = getEntities()->getData(kEntityTatiana)->getData()->field_491;
			_data->getData()->field_493 = getEntities()->getData(kEntityTatiana)->getData()->field_493;
		} else {
			//if (params->param3) {
			//	if (params->param3 >= (int)getState()->time)
			//		break;
			//	params->param3 = EntityData::kParamTime;
			//} else {
			//	params->param3 = (int)getState()->time + 450;
			//	if (params->param3 == 0)
			//		return;
			//	if (params->param3 >= (int)getState()->time)
			//		break;
			//	params->param3 = EntityData::kParamTime;
			//}

			// TODO adapt UPDATE_FROM_TIME
			error("Vassili: callback function 5 not implemented!");

			//if (!params->param2 && getObjects()->get(kObjectCompartmentA).location == kLocation1) {
			//	params->param2 = 1;
			//	getEntities()->drawSequenceLeft(kEntityVassili, "303A");
			//	getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
			//}
			break;
		}
		break;

	case kActionDefault:
		params->param1 = 1;
		break;

	case kAction122732000:
		setup_function6();
		break;

	case kAction168459827:
		params->param1 = 0;
		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, function6, 6)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		// TODO adapt UPDATE_FROM_TICKS
		error("Vassili: callback function 6 not implemented!");
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_8200;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		params->param1 = 5 * (3 * random(25) + 15);

		getEntities()->drawSequenceLeft(kEntityVassili, "303A");
		break;

	case kAction18:
		if (_data->getNextCallback() != 1)
			break;

		getEntities()->drawSequenceLeft(kEntityVassili, "303C");
		params->param1 = 5 * (3 * random(25) + 15);
		params->param2 = 1;

		// TODO: Call shared part with kActionNone
		error("Vassili: callback function 6 not implemented!");
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, function7, 7)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1 != EntityData::kParamTime
		 && getState()->time > kTimeVassili) {
			 if (getState()->time <= kTimeVassili2) {
				 if (getEntities()->checkFields7(kCarRedSleeping) || !params->param1) {
					 params->param1 = getState()->time + 150;
					 if (params->param1) {
						 setup_function8();
						 break;
					 }
				 }

				 if (params->param1 >= (int)getState()->time)
					 break;
			 }

			 params->param1 = EntityData::kParamTime;
			 setup_function8();
		}
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_8200;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->car = kCarRedSleeping;

		getEntities()->prepareSequences(kEntityVassili);
		if (getEntities()->checkFields1(kEntityNone, kCarRedSleeping, EntityData::kField491_8200))
			getLogic()->loadSceneFromObject(kObjectCompartmentA);

		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		break;

	case kAction339669520:
		setup_function9();
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, function8, 8)
	switch (savepoint.action) {
	default:
		break;

	case kAction2:
		setup_function9();
		break;

	case kActionDefault:
		if (!getEntities()->checkFields5(kEntityNone, kCarRedSleeping)) {
			getSound()->playSound(kEntityNone, "BUMP");
			getLogic()->loadSceneFromPosition(kCarRedSleeping, (getEntities()->getData(kEntityNone)->getData()->car <= kCarRedSleeping) ? 1 : 40);
		}

		getSavePoints()->push(kEntityVassili, kEntityAnna, kAction226031488);
		getSavePoints()->push(kEntityVassili, kEntityVerges, kAction226031488);
		getSavePoints()->push(kEntityVassili, kEntityCoudert, kAction226031488);
		getSound()->playSound(kEntityVassili, "VAS1027", 16);
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, function9, 9)
	switch (savepoint.action) {
	default:
		break;

	case kAction2:
		if (!getEntities()->checkFields9(kEntityVassili, kEntityNone, 2500))
			getSound()->playSound(kEntityNone, "BUMP");

		setup_seizure();
		break;

	case kActionDefault:
	case kAction17:
		if ((getObjects()->get(kObjectCompartmentA).location == kLocation2 && getEntities()->isPlayerPosition(kCarRedSleeping, 17))
		|| getEntities()->isPlayerPosition(kCarRedSleeping, 18)
		|| getEntities()->isPlayerPosition(kCarRedSleeping, 37)
		|| getEntities()->isPlayerPosition(kCarRedSleeping, 38)
		|| getEntities()->isPlayerPosition(kCarRedSleeping, 41)) {

			if (savepoint.action == kAction17)
				getSound()->processEntry(kEntityVassili);

			setup_seizure();
		} else {
			if (savepoint.action == kActionDefault)
				getSound()->playSound(kEntityVassili, "VAS1028", 16);
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, seizure, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		// Check that we have removed the body from the train and changed jacket
		if (!getProgress().event_corpse_moved_from_floor) {
			getAction()->playAnimation(kEventMertensCorpseFloor);
			getLogic()->gameOver(kTimeType0, kTime0, kSceneNone, false);
			break;
		}

		if (!getProgress().event_corpse_thrown) {
			getAction()->playAnimation(kEventMertensCorpseBed);
			getLogic()->gameOver(kTimeType0, kTime0, kSceneNone, false);
			break;
		}

		if (getProgress().jacket == kJacketOriginal) {
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime0, kSceneNone, false);
			break;
		}

		// Setup Anna & Coudert
		RESET_ENTITY_STATE(kEntityAnna, Anna, setup_function37);
		RESET_ENTITY_STATE(kEntityCoudert, Coudert, setup_function38);

		_data->setNextCallback(1);
		call(new ENTITY_SETUP(Vassili, setup_savegame), 2, kEventVassiliSeizure);
		break;

	case kAction18:
		if (_data->getNextCallback() != 1)
			break;

		_data->getData()->field_493 = EntityData::kField493_1;
		getAction()->playAnimation(kEventVassiliSeizure);

        getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
        getObjects()->update(kObjectCompartment1, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
        getProgress().field_18 = 2;

        getSavePoints()->push(kEntityVassili, kEntityAnna, kAction191477936, 0);
        getSavePoints()->push(kEntityVassili, kEntityVerges, kAction191477936, 0);
        getSavePoints()->push(kEntityVassili, kEntityCoudert, kAction191477936, 0);
        getLogic()->loadSceneFromObject(kObjectCompartmentA);

        setup_drawInBed();
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, drawInBed, 11)
	if (savepoint.action == kActionDefault)
		getEntities()->drawSequenceLeft(kEntityVassili, "303A");
}

IMPLEMENT_FUNCTION(Vassili, chapter2, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_sleeping();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityVassili);

		_data->getData()->field_491 = EntityData::kField491_8200;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->car = kCarRedSleeping;
		_data->getData()->clothes = kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->updateLocation2(kObjectCompartmentA, kLocation1);
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, sleeping, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->checkFields1(kEntityNone, kCarRedSleeping, EntityData::kField491_8200)) {
			UPDATE_PARAM_FROM_TICKS(3, params->param1);

			_data->setNextCallback(1);
			call(new ENTITY_SETUP_SIIS(Vassili, setup_draw), "303B");
		} else {
			params->param3 = 0;
			if (params->param2)
				getEntities()->drawSequenceLeft(kEntityVassili, "303A");
		}
		break;

	case kActionDefault:
		params->param5 = 5 * (3 * random(25) + 15);
		getEntities()->drawSequenceLeft(kEntityVassili, "303A");
		break;

	case kAction18:
		if (_data->getNextCallback() != 1)
			break;

		getEntities()->drawSequenceLeft(kEntityVassili, "303C");
		params->param1 = 5 * (3 * random(25) + 15);
		params->param2 = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, chapter3, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_stealEgg();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityVassili);

		_data->getData()->field_491 = EntityData::kField491_8200;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->car = kCarRedSleeping;
		_data->getData()->clothes = kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, stealEgg, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->checkFields1(kEntityNone, kCarRedSleeping, EntityData::kField491_8200)) {
			UPDATE_PARAM_FROM_TICKS(3, params->param1);

			_data->setNextCallback(1);
			call(new ENTITY_SETUP_SIIS(Vassili, setup_draw), "303B");
		} else {
			params->param3 = 0;
			if (params->param2)
				getEntities()->drawSequenceLeft(kEntityVassili, "303A");
		}
		break;

	case kAction9:
		_data->setNextCallback(2);
		call(new ENTITY_SETUP(Vassili, setup_savegame), 2, kEventVassiliCompartmentStealEgg);
		break;

	case kActionDefault:
		params->param5 = 5 * (3 * random(25) + 15);
		getEntities()->drawSequenceLeft(kEntityVassili, "303A");
		break;

	case kAction17:
		if (getEntities()->checkFields1(kEntityNone, kCarRedSleeping, EntityData::kField491_7850)
		 && getInventory()->hasItem(kItemFirebird)
		 && !getEvent(kEventVassiliCompartmentStealEgg))
			getObjects()->update(kObject48, kEntityVassili, kLocationNone, kCursorNormal, kCursorHand);
		else
			getObjects()->update(kObject48, kEntityNone, kLocationNone, kCursorNormal, kCursorHand);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceLeft(kEntityVassili, "303C");
			params->param1 = 5 * (3 * random(25) + 15);
			params->param2 = 1;
			break;

		case 2:
			getAction()->playAnimation(kEventVassiliCompartmentStealEgg);
			getLogic()->loadSceneFromPosition(kCarRedSleeping, 67);
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, chapter4, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function17();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityVassili);

		_data->getData()->field_491 = EntityData::kField491_8200;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->car = kCarRedSleeping;
		_data->getData()->clothes = kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->updateLocation2(kObjectCompartmentA, kLocation1);
		break;
	}
}

// Looks identical to sleeping (#13)
IMPLEMENT_FUNCTION(Vassili, function17, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->checkFields1(kEntityNone, kCarRedSleeping, EntityData::kField491_8200)) {
			UPDATE_PARAM_FROM_TICKS(3, params->param1);

			_data->setNextCallback(1);
			call(new ENTITY_SETUP_SIIS(Vassili, setup_draw), "303B");
		} else {
			params->param3 = 0;
			if (params->param2)
				getEntities()->drawSequenceLeft(kEntityVassili, "303A");
		}
		break;

	case kActionDefault:
		params->param5 = 5 * (3 * random(25) + 15);
		getEntities()->drawSequenceLeft(kEntityVassili, "303A");
		break;

	case kAction18:
		if (_data->getNextCallback() != 1)
			break;

		getEntities()->drawSequenceLeft(kEntityVassili, "303C");
		params->param1 = 5 * (3 * random(25) + 15);
		params->param2 = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, chapter5, 18)
	if (savepoint.action == kActionDefault) {
		getEntities()->prepareSequences(kEntityVassili);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->car = kCarRestaurant;
		_data->getData()->clothes = kClothesDefault;
		_data->getData()->inventoryItem = kItemNone;
	}
}

} // End of namespace LastExpress
