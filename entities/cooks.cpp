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

#include "lastexpress/entities/cooks.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Cooks::Cooks(LastExpressEngine *engine) : Entity(engine, kEntityCooks) {
	ADD_CALLBACK_FUNCTION(Cooks, draw);
	ADD_CALLBACK_FUNCTION(Cooks, playSound);
	ADD_CALLBACK_FUNCTION(Cooks, function3);
	ADD_CALLBACK_FUNCTION(Cooks, function4);
	ADD_CALLBACK_FUNCTION(Cooks, chapter1);
	ADD_CALLBACK_FUNCTION(Cooks, function6);
	ADD_CALLBACK_FUNCTION(Cooks, function7);
	ADD_CALLBACK_FUNCTION(Cooks, chapter2);
	ADD_CALLBACK_FUNCTION(Cooks, function9);
	ADD_CALLBACK_FUNCTION(Cooks, chapter3);
	ADD_CALLBACK_FUNCTION(Cooks, function11);
	ADD_CALLBACK_FUNCTION(Cooks, chapter4);
	ADD_CALLBACK_FUNCTION(Cooks, function13);
	ADD_CALLBACK_FUNCTION(Cooks, chapter5);
}

IMPLEMENT_FUNCTION_S(Cooks, draw, 1)
	Entity::draw(savepoint);
}

IMPLEMENT_FUNCTION_S(Cooks, playSound, 2)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION(Cooks, function3, 3)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityCooks, "308A");
		getEntities()->updateField1000ProcessScene(kEntityCooks, 5, 75);
		getEntities()->updateField1000ProcessScene(kEntityCooks, 5, 78);

		switch (getProgress().chapter) {
		default:
			getSound()->playSound(kEntityCooks, "KIT1011");
			_data->setNextCallback(3);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_draw), "308B");
			break;

		case kChapter1:
			_data->setNextCallback(1);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "KIT1010");
			break;

		case kChapter3:
			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "KIT1012");
			break;
		}
		break;

	case kAction17:
		if (!getEntities()->checkFields17(kEntityNone)) {
			getEntities()->prepareSequences(kEntityCooks);
			CALL_PREVIOUS_SAVEPOINT()
			break;
		}

		if (getEntities()->checkFields4(EntityData::kField495_5, 46)) {
			getEntities()->drawSequenceLeft(kEntityCooks, "308D");

			if (!getSound()->isBuffered(kEntityCooks)) {
				if (params->param1) {
					if (!getEntities()->checkSequence0(kEntityCooks)) {
						getSound()->playSound(kEntityCooks, "LIB015");
						getEntities()->prepareSequences(kEntityCooks);
						CALL_PREVIOUS_SAVEPOINT()
					}
					break;
				}

				// Kitchen apprentice getting a lesson :D
				getSound()->playSound(kEntityCooks, "KIT1011A");
				params->param1 = 1;
			}
		}

		if (params->param1 && !getEntities()->checkSequence0(kEntityCooks)) {
			getSound()->playSound(kEntityCooks, "LIB015");
			getEntities()->prepareSequences(kEntityCooks);
			CALL_PREVIOUS_SAVEPOINT()
		}
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
		case 2:
			getSound()->playSound(kEntityCooks, "KIT1011");
			_data->setNextCallback(3);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_draw), "308B");
			break;

		case 3:
			getEntities()->drawSequenceLeft(kEntityCooks, "308C");
			getEntities()->updateField1000(kEntityCooks, 5, 75);
			getEntities()->updateField1000(kEntityCooks, 5, 78);
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, function4, 4)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityCooks, "308A");
		getEntities()->updateField1000ProcessScene(kEntityCooks, EntityData::kField495_5, 75);
		getEntities()->updateField1000ProcessScene(kEntityCooks, EntityData::kField495_5, 78);

		switch (getProgress().chapter) {
		default:
			break;

		case kChapter1:
			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
			break;

		case kChapter3:
			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
			break;
		}

		getSound()->playSound(kEntityCooks, "KIT1011");
		_data->setNextCallback(3);
		call(new ENTITY_SETUP_SIIS(Cooks, setup_draw), "308B");
		break;

	case kAction17:
		if (!getEntities()->checkFields17(kEntityNone)) {
			getEntities()->prepareSequences(kEntityCooks);
			CALL_PREVIOUS_SAVEPOINT()
			break;
		}

		if (getEntities()->checkFields4(EntityData::kField495_5, 80)) {
			getEntities()->drawSequenceLeft(kEntityCooks, "308D");

			if (!getSound()->isBuffered(kEntityCooks)) {
				if (params->param1) {
					if (!getEntities()->checkSequence0(kEntityCooks)) {
						getSound()->playSound(kEntityCooks, "LIB015");
						getEntities()->prepareSequences(kEntityCooks);
						CALL_PREVIOUS_SAVEPOINT()
					}
					break;
				}

				// Kitchen apprentice getting a lesson :D
				getSound()->playSound(kEntityCooks, "KIT1011A");
				params->param1 = 1;
			}
		}

		if (params->param1 && !getEntities()->checkSequence0(kEntityCooks)) {
			getSound()->playSound(kEntityCooks, "LIB015");
			getEntities()->prepareSequences(kEntityCooks);
			CALL_PREVIOUS_SAVEPOINT()
		}
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
		case 2:
			getSound()->playSound(kEntityCooks, "KIT1011");
			_data->setNextCallback(3);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_draw), "308B");
			break;

		case 3:
			getEntities()->drawSequenceLeft(kEntityCooks, "308C");
			getEntities()->updateField1000(kEntityCooks, EntityData::kField495_5, 75);
			getEntities()->updateField1000ProcessScene(kEntityCooks, EntityData::kField495_5, 78);
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter1, 5)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(6)
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;

		getProgress().field_4C = 0;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, function6, 6)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FROM_TIME(4, 2);

		// Broken plate sound
		getSound()->playSound(kEntityNone, "LIB122",  getEntities()->getSoundValue(kEntityCooks));
		params->param2 = 225 * (4 * random(30) + 120);
		params->param4 = 0;
		break;

	case kActionDefault:
		params->param1 = 1;
		params->param2 = 225 * (4 * random(30) + 120);
		break;

	case kAction17:
		if (!getEntities()->checkFields17(kEntityNone))
			break;

		if (params->param1) {
			if (getEntities()->checkFields4(EntityData::kField495_5, 73)) {
				_data->setNextCallback(1);
				call(new ENTITY_SETUP(Cooks, setup_function3));
			}
		} else {
			if (params->param3) {
				_data->setNextCallback(2);
				call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
			} else {
				_data->setNextCallback(3);
				call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1012");
			}
		}
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			params->param1 = 0;
			break;

		case 2:
		case 3:
			params->param3 = !params->param3;
			break;
		}
		break;

	case kAction101632192:
		setup_function7();
		break;

	case kAction224849280:
		getProgress().field_4C = 1;
		params->param1 = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, function7, 7)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		// Snoring...
		_data->setNextCallback(1);
		call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "WAT1200");
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_3650;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;

		getEntities()->prepareSequences(kEntityCooks);
		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter2, 8)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function9();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityCooks);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		getProgress().field_4C = 1;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, function9, 9)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FROM_TIME(3, 1);

		// Broken plate sound
		getSound()->playSound(kEntityNone, "LIB122",  getEntities()->getSoundValue(kEntityCooks));
		params->param1 = 225 * (4 * random(30) + 120);
		params->param3 = 0;
		break;

	case kActionDefault:
		params->param1 = 225 * (4 * random(30) + 120);
		break;

	case kAction17:
		if (params->param2) {
			_data->setNextCallback(1);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
		} else {
			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1012");
		}
		break;

	case kAction18:
		if (_data->getNextCallback() == 1 || _data->getNextCallback() == 2)
			params->param2 = !params->param2;
		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter3, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function11();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityCooks);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		getProgress().field_4C = 0;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, function11, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FROM_TIME(4, params->param2);

		// Broken plate sound
		getSound()->playSound(kEntityNone, "LIB122",  getEntities()->getSoundValue(kEntityCooks));
		params->param2 = 225 * (4 * random(30) + 120);
		params->param4 = 0;

update_params:
		if (getState()->time > kTimeCooks) {
			if (!params->param5) {
				params->param1 = 0;
				params->param5 = 1;
			}
		}
		break;

	case kActionDefault:
		params->param1 = 1;
		params->param2 = 225 * (4 * random(30) + 120);
		break;

	case kAction17:
		if (!getEntities()->checkFields17(kEntityNone))
			break;

		if (params->param1) {
			if (getEntities()->checkFields4(EntityData::kField495_5, 80)) {
				_data->setNextCallback(1);
				call(new ENTITY_SETUP(Cooks, setup_function4));
			}
		} else {
			if (params->param3) {
				_data->setNextCallback(2);
				call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
			} else {
				_data->setNextCallback(3);
				call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1012");
			}
		}
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			params->param1 = 0;
			break;

		case 2:
		case 3:
			params->param3 = !params->param3;
			break;
		}
		break;

	case kAction236976550:
		getProgress().field_4C = 1;
		break;

	}
}

IMPLEMENT_FUNCTION(Cooks, chapter4, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_function13();
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityCooks);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		getProgress().field_4C = 1;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, function13, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FROM_TIME(3, 1)

		// Broken plate sound
		getSound()->playSound(kEntityNone, "LIB122",  getEntities()->getSoundValue(kEntityCooks));
		params->param1 = 225 * (4 * random(30) + 120);
		params->param3 = 0;
		break;

	case kActionDefault:
		params->param1 = 225 * (4 * random(30) + 120);
		break;

	case kAction17:
		if (!getEntities()->checkFields17(kEntityNone))
			break;

		// Kitchen background sound
		if (params->param2) {
			_data->setNextCallback(1);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
		} else {
			_data->setNextCallback(2);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1012");
		}
		break;


	case kAction18:
		// Play the next part of background sound
		if (_data->getNextCallback() == 1 || _data->getNextCallback() == 2) {
			params->param2 = !params->param2;
		}
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter5, 14)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityCooks);
}

} // End of namespace LastExpress
