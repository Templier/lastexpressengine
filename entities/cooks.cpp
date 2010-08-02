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
	ADD_CALLBACK_FUNCTION(Cooks, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Cooks, function7);
	ADD_CALLBACK_FUNCTION(Cooks, chapter2);
	ADD_CALLBACK_FUNCTION(Cooks, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Cooks, chapter3);
	ADD_CALLBACK_FUNCTION(Cooks, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Cooks, chapter4);
	ADD_CALLBACK_FUNCTION(Cooks, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Cooks, chapter5);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Cooks, draw, 1)
	Entity::draw(savepoint);
}

/**
 * Plays sound
 *
 * @param param1 The sound filename
 */
IMPLEMENT_FUNCTION_S(Cooks, playSound, 2)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION(Cooks, function3, 3)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequenceLeft(kEntityCooks, "308A");
		getEntities()->updatePosition(kEntityCooks, kCarRestaurant, 75, true);
		getEntities()->updatePosition(kEntityCooks, kCarRestaurant, 78, true);

		switch (getProgress().chapter) {
		default:
			getSound()->playSound(kEntityCooks, "KIT1011");
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_draw), "308B");
			break;

		case kChapter1:
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "KIT1010");
			break;

		case kChapter3:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "KIT1012");
			break;
		}
		break;

	case kActionDrawScene:
		if (!getEntities()->checkFields17()) {
			getEntities()->clearSequences(kEntityCooks);
			CALLBACK_ACTION()
			break;
		}

		if (getEntities()->isPlayerPosition(kCarRestaurant, 46)) {
			getEntities()->drawSequenceLeft(kEntityCooks, "308D");

			if (!getSound()->isBuffered(kEntityCooks)) {
				if (params->param1) {
					if (!getEntities()->hasValidFrame(kEntityCooks)) {
						getSound()->playSound(kEntityCooks, "LIB015");
						getEntities()->clearSequences(kEntityCooks);
						CALLBACK_ACTION()
					}
					break;
				}

				// Kitchen apprentice getting a lesson :D
				getSound()->playSound(kEntityCooks, "KIT1011A");
				params->param1 = 1;
			}
		}

		if (params->param1 && !getEntities()->hasValidFrame(kEntityCooks)) {
			getSound()->playSound(kEntityCooks, "LIB015");
			getEntities()->clearSequences(kEntityCooks);
			CALLBACK_ACTION()
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			getSound()->playSound(kEntityCooks, "KIT1011");
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_draw), "308B");
			break;

		case 3:
			getEntities()->drawSequenceLeft(kEntityCooks, "308C");
			getEntities()->updatePosition(kEntityCooks, kCarRestaurant, 75);
			getEntities()->updatePosition(kEntityCooks, kCarRestaurant, 78);
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
		getEntities()->updatePosition(kEntityCooks, kCarRestaurant, 75, true);
		getEntities()->updatePosition(kEntityCooks, kCarRestaurant, 78, true);

		switch (getProgress().chapter) {
		default:
			break;

		case kChapter1:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
			break;

		case kChapter3:
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
			break;
		}

		getSound()->playSound(kEntityCooks, "KIT1011");
		setCallback(3);
		call(new ENTITY_SETUP_SIIS(Cooks, setup_draw), "308B");
		break;

	case kActionDrawScene:
		if (!getEntities()->checkFields17()) {
			getEntities()->clearSequences(kEntityCooks);
			CALLBACK_ACTION()
			break;
		}

		if (getEntities()->isPlayerPosition(kCarRestaurant, 80)) {
			getEntities()->drawSequenceLeft(kEntityCooks, "308D");

			if (!getSound()->isBuffered(kEntityCooks)) {
				if (params->param1) {
					if (!getEntities()->hasValidFrame(kEntityCooks)) {
						getSound()->playSound(kEntityCooks, "LIB015");
						getEntities()->clearSequences(kEntityCooks);
						CALLBACK_ACTION()
					}
					break;
				}

				// Kitchen apprentice getting a lesson :D
				getSound()->playSound(kEntityCooks, "KIT1011A");
				params->param1 = 1;
			}
		}

		if (params->param1 && !getEntities()->hasValidFrame(kEntityCooks)) {
			getSound()->playSound(kEntityCooks, "LIB015");
			getEntities()->clearSequences(kEntityCooks);
			CALLBACK_ACTION()
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 2:
			getSound()->playSound(kEntityCooks, "KIT1011");
			setCallback(3);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_draw), "308B");
			break;

		case 3:
			getEntities()->drawSequenceLeft(kEntityCooks, "308C");
			getEntities()->updatePosition(kEntityCooks, kCarRestaurant, 75);
			getEntities()->updatePosition(kEntityCooks, kCarRestaurant, 78, true);
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
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;

		getProgress().field_4C = 0;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter1Handler, 6)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM(params->param4, getState()->time, params->param2);

		// Broken plate sound
		getSound()->playSound(kEntityNone, "LIB122",  getSound()->getSoundFlag(kEntityCooks));
		params->param2 = 225 * (4 * random(30) + 120);
		params->param4 = 0;
		break;

	case kActionDefault:
		params->param1 = 1;
		params->param2 = 225 * (4 * random(30) + 120);
		break;

	case kActionDrawScene:
		if (!getEntities()->checkFields17())
			break;

		if (params->param1) {
			if (getEntities()->isPlayerPosition(kCarRestaurant, 73)) {
				setCallback(1);
				call(new ENTITY_SETUP(Cooks, setup_function3));
			}
		} else {
			if (params->param3) {
				setCallback(2);
				call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
			} else {
				setCallback(3);
				call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1012");
			}
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
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
		setCallback(1);
		call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "WAT1200");
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_3650;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;

		getEntities()->clearSequences(kEntityCooks);
		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter2, 8)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityCooks);

		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		getProgress().field_4C = 1;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter2Handler, 9)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM(params->param3, getState()->time, params->param1);

		// Broken plate sound
		getSound()->playSound(kEntityNone, "LIB122",  getSound()->getSoundFlag(kEntityCooks));
		params->param1 = 225 * (4 * random(30) + 120);
		params->param3 = 0;
		break;

	case kActionDefault:
		params->param1 = 225 * (4 * random(30) + 120);
		break;

	case kActionDrawScene:
		if (params->param2) {
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
		} else {
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1012");
		}
		break;

	case kActionCallback:
		if (getCallback() == 1 || getCallback() == 2)
			params->param2 = !params->param2;
		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter3, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityCooks);

		getData()->entityPosition = kPosition_5900;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		getProgress().field_4C = 0;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter3Handler, 11)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM_FUNCTION(params->param4, getState()->time, params->param2, update_params);

		// Broken plate sound
		getSound()->playSound(kEntityNone, "LIB122",  getSound()->getSoundFlag(kEntityCooks));
		params->param2 = 225 * (4 * random(30) + 120);
		params->param4 = 0;

update_params:
		if (getState()->time > kTime2079000 && !params->param5) {
			params->param1 = 0;
			params->param5 = 1;
		}
		break;

	case kActionDefault:
		params->param1 = 1;
		params->param2 = 225 * (4 * random(30) + 120);
		break;

	case kActionDrawScene:
		if (!getEntities()->checkFields17())
			break;

		if (params->param1) {
			if (getEntities()->isPlayerPosition(kCarRestaurant, 80)) {
				setCallback(1);
				call(new ENTITY_SETUP(Cooks, setup_function4));
			}
		} else {
			if (params->param3) {
				setCallback(2);
				call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
			} else {
				setCallback(3);
				call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1012");
			}
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
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
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityCooks);

		getData()->entityPosition = kPosition_5900;
		getData()->posture = kPostureStanding;
		getData()->car = kCarRestaurant;
		getData()->inventoryItem = kItemNone;

		getProgress().field_4C = 1;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter4Handler, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		UPDATE_PARAM(params->param3, getState()->time, params->param1)

		// Broken plate sound
		getSound()->playSound(kEntityNone, "LIB122",  getSound()->getSoundFlag(kEntityCooks));
		params->param1 = 225 * (4 * random(30) + 120);
		params->param3 = 0;
		break;

	case kActionDefault:
		params->param1 = 225 * (4 * random(30) + 120);
		break;

	case kActionDrawScene:
		if (!getEntities()->checkFields17())
			break;

		// Kitchen background sound
		if (params->param2) {
			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1011");
		} else {
			setCallback(2);
			call(new ENTITY_SETUP_SIIS(Cooks, setup_playSound), "ZFX1012");
		}
		break;


	case kActionCallback:
		// Play the next part of background sound
		if (getCallback() == 1 || getCallback() == 2) {
			params->param2 = !params->param2;
		}
	}
}

IMPLEMENT_FUNCTION(Cooks, chapter5, 14)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityCooks);
}

} // End of namespace LastExpress
