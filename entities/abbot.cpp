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

#include "lastexpress/entities/abbot.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Abbot::Abbot(LastExpressEngine *engine) : Entity(engine, kEntityAbbot) {
	ADD_CALLBACK_FUNCTION(Abbot, function1);
	ADD_CALLBACK_FUNCTION(Abbot, draw);
	ADD_CALLBACK_FUNCTION(Abbot, function3);
	ADD_CALLBACK_FUNCTION(Abbot, function4);
	ADD_CALLBACK_FUNCTION(Abbot, function5);
	ADD_CALLBACK_FUNCTION(Abbot, draw2);
	ADD_CALLBACK_FUNCTION(Abbot, updateFromTime);
	ADD_CALLBACK_FUNCTION(Abbot, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Abbot, playSound);
	ADD_CALLBACK_FUNCTION(Abbot, savegame);
	ADD_CALLBACK_FUNCTION(Abbot, function11);
	ADD_CALLBACK_FUNCTION(Abbot, function12);
	ADD_CALLBACK_FUNCTION(Abbot, function13);
	ADD_CALLBACK_FUNCTION(Abbot, function14);
	ADD_CALLBACK_FUNCTION(Abbot, chapter1);
	ADD_CALLBACK_FUNCTION(Abbot, chapter2);
	ADD_CALLBACK_FUNCTION(Abbot, chapter3);
	ADD_CALLBACK_FUNCTION(Abbot, function18);
	ADD_CALLBACK_FUNCTION(Abbot, function19);
	ADD_CALLBACK_FUNCTION(Abbot, function20);
	ADD_CALLBACK_FUNCTION(Abbot, function21);
	ADD_CALLBACK_FUNCTION(Abbot, function22);
	ADD_CALLBACK_FUNCTION(Abbot, function23);
	ADD_CALLBACK_FUNCTION(Abbot, function24);
	ADD_CALLBACK_FUNCTION(Abbot, function25);
	ADD_CALLBACK_FUNCTION(Abbot, function26);
	ADD_CALLBACK_FUNCTION(Abbot, function27);
	ADD_CALLBACK_FUNCTION(Abbot, function28);
	ADD_CALLBACK_FUNCTION(Abbot, function29);
	ADD_CALLBACK_FUNCTION(Abbot, function30);
	ADD_CALLBACK_FUNCTION(Abbot, function31);
	ADD_CALLBACK_FUNCTION(Abbot, function32);
	ADD_CALLBACK_FUNCTION(Abbot, function33);
	ADD_CALLBACK_FUNCTION(Abbot, function34);
	ADD_CALLBACK_FUNCTION(Abbot, function35);
	ADD_CALLBACK_FUNCTION(Abbot, function36);
	ADD_CALLBACK_FUNCTION(Abbot, function37);
	ADD_CALLBACK_FUNCTION(Abbot, function38);
	ADD_CALLBACK_FUNCTION(Abbot, chapter4);
	ADD_CALLBACK_FUNCTION(Abbot, function40);
	ADD_CALLBACK_FUNCTION(Abbot, function41);
	ADD_CALLBACK_FUNCTION(Abbot, function42);
	ADD_CALLBACK_FUNCTION(Abbot, function43);
	ADD_CALLBACK_FUNCTION(Abbot, function44);
	ADD_CALLBACK_FUNCTION(Abbot, function45);
	ADD_CALLBACK_FUNCTION(Abbot, function46);
	ADD_CALLBACK_FUNCTION(Abbot, function47);
	ADD_CALLBACK_FUNCTION(Abbot, function48);
	ADD_CALLBACK_FUNCTION(Abbot, pickBomb);
	ADD_CALLBACK_FUNCTION(Abbot, chapter5);
	ADD_CALLBACK_FUNCTION(Abbot, function51);
	ADD_CALLBACK_FUNCTION(Abbot, function52);
	ADD_CALLBACK_FUNCTION(Abbot, function53);
}

IMPLEMENT_FUNCTION(Abbot, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION_S(Abbot, draw, 2)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_SI(Abbot, function3, 3)
	Entity::updateFields(savepoint);
}

IMPLEMENT_FUNCTION_SI(Abbot, function4, 4)
	switch (savepoint.action) {
	default:
		break;

	case kAction3:
		getEntities()->updateFields1(kEntityAbbot, (ObjectIndex)params->param2);
		_data->getData()->field_491 = EntityData::kField491_6470;
		_data->getData()->field_493 = EntityData::kField493_1;

		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityAbbot, params->seq1);
		getEntities()->updateFields0(kEntityAbbot, (ObjectIndex)params->param2);

		_data->getData()->field_493 = EntityData::kField493_1;
		if (getEntities()->checkFields1(kEntityNone, EntityData::kField495_4, EntityData::kField491_6470)
		 || getEntities()->checkFields1(kEntityNone, EntityData::kField495_4, EntityData::kField491_6130)) {
			getAction()->playAnimation(isDay() ? kEventCathTurningDay : kEventCathTurningNight);
			getSound()->playSound(kEntityNone, "BUMP");
			getLogic()->loadSceneFromObject2(kObjectCompartmentC);
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function5, 5)
	Entity::savepointDirection(savepoint);
}

IMPLEMENT_FUNCTION_SSI(Abbot, draw2, 6)
	Entity::draw2(savepoint);
}

IMPLEMENT_FUNCTION_I(Abbot, updateFromTime, 7)
	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_I(Abbot, updateFromTicks, 8)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION_S(Abbot, playSound, 9)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_II(Abbot, savegame, 10)
	Entity::savegame(savepoint);
}

// Parameters:
//  - EntityData::Field495Value
//  - EntityData::Field491Value
IMPLEMENT_FUNCTION_II(Abbot, function11, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->checkEntity(kEntityAbbot, (EntityData::Field495Value)params->param1, (EntityData::Field491Value)params->param2))
			CALL_PREVIOUS_SAVEPOINT()
		break;

	case kActionExcuseMeCath:
		if (getEntities()->checkFields4(EntityData::kField495_3, 18) || getEntities()->checkFields4(EntityData::kField495_4, 18)) {
			getSound()->excuseMe(kEntityAbbot);
		} else {
			if (getEvent(kEventAbbotIntroduction))
				getSound()->playSound(kEntityNone, "CAT1013");
			else
				getSound()->excuseMeCath();
		}
		break;

	case kActionExcuseMe:
		getSound()->excuseMe(kEntityAbbot);
		break;

	case kActionDefault:
		if (getEntities()->checkEntity(kEntityAbbot, (EntityData::Field495Value)params->param1, (EntityData::Field491Value)params->param2))
			CALL_PREVIOUS_SAVEPOINT()
		break;
	}
}

IMPLEMENT_FUNCTION_SIIS(Abbot, function12, 12)
	Entity::savepointCall(savepoint);
}

IMPLEMENT_FUNCTION_SII(Abbot, function13, 13)
	Entity::updateField1000(savepoint);
}

IMPLEMENT_FUNCTION(Abbot, function14, 14)
	Entity::savepointCheckFields11(savepoint);
}

IMPLEMENT_FUNCTION(Abbot, chapter1, 15)
	if (savepoint.action == kActionDefault)
		getSavePoints()->addData(kEntityAbbot, kAction203073664, 0);
}

IMPLEMENT_FUNCTION(Abbot, chapter2, 16)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityAbbot);
}

IMPLEMENT_FUNCTION(Abbot, chapter3, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function18();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAbbot);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;
		_data->getData()->clothes = EntityData::kClothesDefault;

		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function18, 18)
	switch (savepoint.action) {
	default:
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			_data->getData()->field_491 = EntityData::kField491_5800;
			_data->getData()->field_493 = EntityData::kField493_0;

			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_draw), "804DD");
			break;

		case 2:
			getSavePoints()->push(kEntityAbbot, kEntityCooks, kAction236976550);
			getEntities()->drawSequenceRight(kEntityAbbot, "804DS");

			if (getEntities()->checkFields13(kEntityNone))
				getEntities()->updateEntity(kEntityAbbot);

			_data->setNextCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function5));
			break;

		case 3:
			_data->setNextCallback(4);
			call(new ENTITY_SETUP(Abbot, setup_function11), EntityData::kField495_4, EntityData::kField491_6470);
			break;

		case 4:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

			_data->setNextCallback(5);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_function3), "617AC", 34);
			break;

		case 5:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			_data->getData()->field_491 = EntityData::kField491_6470;
			_data->getData()->field_493 = EntityData::kField493_1;

			setup_function19();
			break;
		}
		break;

	case kAction192054567:
		_data->setNextCallback(1);
        call(new ENTITY_SETUP(Abbot, setup_function14));
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function19, 19)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeAbbot) {
			if (!params->param1) {
				params->param1 = 1;
				_data->setNextCallback(3);
				call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "MrB3010");
			}
		}
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAbbot, "508A");
		getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122358304);

		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "Abb3010");
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			_data->setNextCallback(2);
			call(new ENTITY_SETUP(Abbot, setup_updateFromTime), 900);
			break;

		case 2:
			getEntities()->drawSequenceLeft(kEntityAbbot, "508B");
			break;

		case 3:
			getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122288808);
			setup_function20();
			break;
		}
	}
}

IMPLEMENT_FUNCTION(Abbot, function20, 20)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeAbbot2)
			if (getEntities()->checkFields13(kEntityBoutarel))
				setup_function21();
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAbbot, "509A");
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function21, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_draw), "509B");
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject50, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_function3), "617Mc", 34);
			break;

		case 2:
			_data->getData()->field_493 = EntityData::kField493_0;

			_data->setNextCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function11), EntityData::kField495_5, EntityData::kField491_850);
			break;

		case 3:
			_data->setNextCallback(4);
			call(new ENTITY_SETUP(Abbot, setup_function14));
			break;

		case 4:
			_data->getData()->field_491 = EntityData::kField491_1540;
			_data->getData()->field_493 = EntityData::kField493_0;

			_data->setNextCallback(5);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_draw), "804US");
			break;

		case 5:
			getEntities()->drawSequenceRight(kEntityAbbot, "029J");
			if (getEntities()->checkFields12(kEntityNone))
				getEntities()->updateEntity(kEntityAbbot);

			_data->setNextCallback(6);
			call(new ENTITY_SETUP(Abbot, setup_function5));
			break;

		case 6:
			getEntities()->drawSequenceLeft(kEntityAbbot, "029H");
			getSavePoints()->push(kEntityAbbot, kEntityPascale, kAction207769280);
			break;

		case 7:
			setup_function22();
			break;
		}
		break;

	case kAction122288808:
		getSavePoints()->push(kEntityAbbot, kEntityTables4, kAction136455232);
		_data->getData()->field_493 = EntityData::kField493_1;

		_data->setNextCallback(7);
        call(new ENTITY_SETUP_SIIS(Abbot, setup_draw), "029B");
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function22, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeAbbot3) {
			if (!params->param1) {
				params->param1 = 1;
				getSavePoints()->push(kEntityAbbot, kEntityServers0, kAction218586752);
			}
		}

		if (getState()->time > kTimeAbbot4) {
			if (getEntities()->checkFields11()) {
				_data->getData()->inventoryItem = kItemNone;

				setup_function23();
			}
		}
		break;

	case kAction1:
		_data->getData()->inventoryItem = kItemNone;

		_data->setNextCallback(1);
		call(new ENTITY_SETUP(Abbot, setup_savegame), 2, kEventAbbotIntroduction);
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAbbot, "029E");
		if (!getEvent(kEventAbbotIntroduction))
			_data->getData()->inventoryItem = (InventoryItem)kCursorProcess;
		break;

	case kAction18:
		if (_data->getNextCallback() != 1)
			break;

		getAction()->playAnimation(kEventAbbotIntroduction);
		getSound()->playSound(kEntityNone, "LIB036");
		getLogic()->loadSceneFromPosition(EntityData::kField495_5, 61);
		break;

	case kAction122288808:
		getEntities()->drawSequenceLeft(kEntityAbbot, "029E");
		break;

	case kAction122358304:
		getEntities()->drawSequenceLeft(kEntityAbbot, "BLANK");
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function23, 23)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		_data->getData()->field_493 = EntityData::kField493_0;
		getEntities()->updateField1000ProcessScene(kEntityAbbot, 5, 67);

		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_function12), "029F", kEntityTables4, kAction103798704, "029G");
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getEntities()->updateField1000(kEntityAbbot, 5, 67);
			getSavePoints()->push(kEntityAbbot, kEntityServers0, kAction270068760);
			getSavePoints()->push(kEntityAbbot, kEntityAnna, kAction238936000);
			getEntities()->drawSequenceRight(kEntityAbbot, "804DS");

			if (getEntities()->checkFields13(kEntityNone))
				getEntities()->updateEntity(kEntityAbbot);

			_data->setNextCallback(2);
			call(new ENTITY_SETUP(Abbot, setup_function5));
			break;

		case 2:
			_data->setNextCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function11), EntityData::kField495_4, EntityData::kField491_6470);
			break;

		case 3:
			_data->setNextCallback(4);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_function4), "617Cc", 34);
			break;

		case 4:
			_data->getData()->field_493 = EntityData::kField493_1;

			setup_function24();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function24, 24)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FROM_TIME(1, 900);

		setup_function25();
		break;

	case kAction8:
	case kAction9:
		getObjects()->update(kObjectCompartmentC, kEntityAbbot, kLocation1, kCursorNormal, kCursorNormal);
		getObjects()->update(kObject50, kEntityAbbot, kLocation1, kCursorNormal, kCursorNormal);

		if (savepoint.action == kAction8) {
			_data->setNextCallback(1);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "LIB012");
		} else {
			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "LIB013");
		}
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAbbot);
		getObjects()->update(kObjectCompartmentC, kEntityAbbot, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityAbbot, kLocationNone, kCursorHandKnock, kCursorHand);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
		case 2:
			_data->setNextCallback(3);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "Abb3001");
			break;

		case 3:
			getObjects()->update(kObjectCompartmentC, kEntityAbbot, kLocation1, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject50, kEntityAbbot, kLocation1, kCursorHandKnock, kCursorHand);
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function25, 25)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_function3), "617Dc", 34);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			_data->getData()->field_493 = EntityData::kField493_0;
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObject50, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

			_data->setNextCallback(2);
			call(new ENTITY_SETUP(Abbot, setup_function11), EntityData::kField495_5,  EntityData::kField491_850);
			break;

		case 2:
			_data->setNextCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function14));
			break;

		case 3:
			_data->getData()->field_491 = EntityData::kField491_1540;
			_data->getData()->field_493 = EntityData::kField493_0;

			_data->setNextCallback(4);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_function13), "115A", 5, 56);
			break;

		case 4:
			_data->getData()->field_493 = EntityData::kField493_1;
			getLogic()->loadSceneFromItem(kItem3);

			setup_function26();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function26, 26)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FROM_TIME(2, 4500);

		if (getEntities()->checkFields11())
			setup_function27();
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAbbot, kEntityKronos, kAction157159392);
		getEntities()->drawSequenceLeft(kEntityAbbot, "115B");
		break;

	case kAction101169422:
		params->param1 = 1;
		break;

	}
}

IMPLEMENT_FUNCTION(Abbot, function27, 27)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		_data->setNextCallback(1);
		call(new ENTITY_SETUP(Abbot, setup_function14));
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			_data->getData()->field_493 = EntityData::kField493_0;

			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_function13), "115C", 5, 56);
			break;

		case 2:
			getInventory()->setLocationAndProcess(kItem3, kLocation1);

			_data->setNextCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function11), EntityData::kField495_4, EntityData::kField491_6470);
			break;

		case 3:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

			_data->setNextCallback(4);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_function3), "617Ac", 34);
			break;

		case 4:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			_data->getData()->field_491 = EntityData::kField491_6470;
			_data->getData()->field_493 = EntityData::kField493_1;

			setup_function28();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function28, 28)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeTables2) {
			if (!params->param1) {
				params->param1 = 1;
				_data->setNextCallback(1);
				call(new ENTITY_SETUP(Abbot, setup_function29));
			}
		}
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122358304);
		getEntities()->drawSequenceLeft(kEntityAbbot, "508A");

		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "abb3013");
		break;

	case kAction18:
		if (_data->getNextCallback() == 1)
			getEntities()->drawSequenceLeft(kEntityAbbot, "508B");
		break;

	case kAction222609266:
		setup_function30();
	}
}

IMPLEMENT_FUNCTION(Abbot, function29, 29)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122288808);
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_function3), "617Bc", 34);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);

			_data->setNextCallback(2);
			call(new ENTITY_SETUP(Abbot, setup_function11), EntityData::kField495_4, EntityData::kField491_9460);
			break;

		case 2:
			_data->setNextCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_updateFromTicks), 450);
			break;

		case 3:
			_data->setNextCallback(4);
			call(new ENTITY_SETUP(Abbot, setup_function11), EntityData::kField495_3, EntityData::kField491_540);
			break;

		case 4:
			_data->setNextCallback(5);
			call(new ENTITY_SETUP(Abbot, setup_updateFromTime), 225);
			break;

		case 5:
			_data->setNextCallback(6);
			call(new ENTITY_SETUP(Abbot, setup_function11), EntityData::kField495_4, EntityData::kField491_6470);
			break;

		case 6:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

			_data->setNextCallback(7);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_function3), "617Ac", 34);
			break;

		case 7:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122358304);
			getEntities()->drawSequenceLeft(kEntityAbbot, "508B");

			CALL_PREVIOUS_SAVEPOINT();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function30, 30)
switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "Abb3030");
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getSavePoints()->push(kEntityAbbot, kEntityBoutarel, kAction122288808);
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation1, kCursorKeepValue, kCursorKeepValue);

			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_function3), "617Bc", 34);
			break;

		case 2:
			getObjects()->update(kObjectCompartmentC, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			_data->getData()->field_493 = EntityData::kField493_0;

			_data->setNextCallback(3);
			call(new ENTITY_SETUP(Abbot, setup_function11), EntityData::kField495_5, EntityData::kField491_850);
			break;

		case 3:
			_data->setNextCallback(4);
			call(new ENTITY_SETUP(Abbot, setup_function14));
			break;

		case 4:
			_data->getData()->field_491 = EntityData::kField491_1540;
			_data->getData()->field_493 = EntityData::kField493_0;

			_data->setNextCallback(5);
			call(new ENTITY_SETUP_SIIS(Abbot, setup_function13), "115A", 5, 56);
			break;

		case 5:
			getLogic()->loadSceneFromItem(kItem3);
			_data->getData()->field_493 = EntityData::kField493_1;

			setup_function31();
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function31, 31)
	error("Abbot: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function32, 32)
	error("Abbot: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function33, 33)
	error("Abbot: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function34, 34)
	error("Abbot: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function35, 35)
	error("Abbot: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function36, 36)
	error("Abbot: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function37, 37)
	error("Abbot: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function38, 38)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityAbbot, "508A");

		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Abbot, setup_playSound), "Abb3014A");
		break;

	case kAction18:
		if (_data->getNextCallback() == 1)
			getEntities()->drawSequenceLeft(kEntityAbbot, "508B");
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, chapter4, 39)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function41();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAbbot);

		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		ENTITY_PARAM(0, 1) = 0;

		break;
	}
}

IMPLEMENT_FUNCTION_II(Abbot, function40, 40)
	error("Abbot: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function41, 41)
	error("Abbot: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function42, 42)
	error("Abbot: callback function 42 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function43, 43)
	error("Abbot: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function44, 44)
	error("Abbot: callback function 44 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function45, 45)
	error("Abbot: callback function 45 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function46, 46)
	error("Abbot: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function47, 47)
	error("Abbot: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, function48, 48)
	error("Abbot: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, pickBomb, 49)
	error("Abbot::pickBomb: callback 49 function not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, chapter5, 50)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function51();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAbbot);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;
		_data->getData()->clothes = EntityData::kClothesDefault;

		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function51, 51)
	if (savepoint.action == kAction70549068)
		setup_function52();
}

IMPLEMENT_FUNCTION(Abbot, function52, 52)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityAbbot);

		_data->getData()->field_491 = EntityData::kField491_0;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_0;
		break;

	case kAction135600432:
		setup_function53();
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, function53, 53)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getInventory()->setLocationAndProcess(kItem25, kLocation1);
		getSavePoints()->push(kEntityAbbot, kEntityAnna, kAction158480160);
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventLocomotiveAbbotGetSomeRest);
			getLogic()->processScene();
			break;

		case 2:
			getAction()->playAnimation(kEventLocomotiveAbbotShoveling);
			getLogic()->processScene();
			break;
		}
		break;

	case kAction168646401:
		if (!getEvent(kEventLocomotiveAbbotGetSomeRest)) {
			_data->setNextCallback(1);
			call(new ENTITY_SETUP(Abbot, setup_savegame), 2, kEventLocomotiveAbbotGetSomeRest);
			break;
		}

		if (!getEvent(kEventLocomotiveAbbotShoveling)) {
			_data->setNextCallback(2);
			call(new ENTITY_SETUP(Abbot, setup_savegame), 2, kEventLocomotiveAbbotShoveling);
			break;
		}

		getAction()->playAnimation(kEventLocomotiveAbbotShoveling);
		getLogic()->processScene();
		break;
	}
}

} // End of namespace LastExpress
