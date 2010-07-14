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

#include "lastexpress/entities/gendarmes.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Gendarmes::Gendarmes(LastExpressEngine *engine) : Entity(engine, kEntityGendarmes) {
	ADD_CALLBACK_FUNCTION(Gendarmes, function1);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter1);
	ADD_CALLBACK_FUNCTION(Gendarmes, arrestDraw);
	ADD_CALLBACK_FUNCTION(Gendarmes, arrestPlaysound);
	ADD_CALLBACK_FUNCTION(Gendarmes, arrestPlaysound16);
	ADD_CALLBACK_FUNCTION(Gendarmes, function6);
	ADD_CALLBACK_FUNCTION(Gendarmes, savegame);
	ADD_CALLBACK_FUNCTION(Gendarmes, function8);
	ADD_CALLBACK_FUNCTION(Gendarmes, function9);
	ADD_CALLBACK_FUNCTION(Gendarmes, function10);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Gendarmes, function12);
	ADD_CALLBACK_FUNCTION(Gendarmes, function13);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter2);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter3);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter4);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter5);
}

IMPLEMENT_FUNCTION(Gendarmes, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION(Gendarmes, chapter1, 2)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1_handler);
		break;

	case kActionDefault:
		getData()->car = kCarNone;
		break;
	}
}

IMPLEMENT_FUNCTION_S(Gendarmes, arrestDraw, 3)
	arrest(savepoint);
}

IMPLEMENT_FUNCTION_S(Gendarmes, arrestPlaysound, 4)
	arrest(savepoint, true);
}

IMPLEMENT_FUNCTION_S(Gendarmes, arrestPlaysound16, 5)
	arrest(savepoint, true, 16);
}

IMPLEMENT_FUNCTION_I(Gendarmes, function6, 6)
	error("Gendarmes: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_II(Gendarmes, savegame, 7)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(Gendarmes, function8, 8)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->checkEntity(kEntityGendarmes, (CarIndex)params->param1, (EntityData::Field491Value)params->param2)) {
			CALLBACK_ACTION();
			break;
		}
		// fallback to action 17

	case kAction17:
		if (!ENTITY_PARAM(0, 1) && getEntities()->checkSequence0(kEntityGendarmes)) {
			getSound()->playSound(kEntityNone, "MUS007");
			ENTITY_PARAM(0, 1) = 1;
		}

		if (getEntities()->checkFields9(kEntityGendarmes, kEntityNone, 1750)
		 && getEntityData(kEntityNone)->field_493 == 0) {
			if (!getEntities()->isPlayerPosition(kCarRedSleeping, 22) || getEntities()->checkFields9(kEntityGendarmes, kEntityNone, 250)) {
				setCallback(1);
				call(new ENTITY_SETUP(Gendarmes, setup_savegame), kSavegameType2, kEventGendarmesArrestation);
			}
		}
		break;

	case kActionDefault:
		if (getEntities()->checkEntity(kEntityGendarmes, (CarIndex)params->param1, (EntityData::Field491Value)params->param2))
			CALLBACK_ACTION();
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventGendarmesArrestation);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverPolice1, true);
		}
		break;
	}
}

// Parameters:
// - CarIndex
// - Field491
IMPLEMENT_FUNCTION_IISS(Gendarmes, function9, 9)
	error("Gendarmes: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION_III(Gendarmes, function10, 10)
	error("Gendarmes: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Gendarmes, chapter1_handler, 11)
	if (savepoint.action == kAction169499649) {
		getSavePoints()->push(kEntityGendarmes, kEntityMertens, kAction190082817);
		setup_function12();
	}
}

IMPLEMENT_FUNCTION(Gendarmes, function12, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getData()->field_491 = EntityData::kField491_540;
		getData()->field_493 = EntityData::kField493_0;
		getData()->car = kCarGreenSleeping;

		getProgress().field_14 = 29;

		setCallback(1);
		call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarGreenSleeping, EntityData::kField491_5540);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			setCallback(2);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarGreenSleeping, EntityData::kField491_5790, "d", "A");
			break;

		case 2:
			setCallback(3);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarGreenSleeping, EntityData::kField491_6220);
			break;

		case 3:
			setCallback(4);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarGreenSleeping, EntityData::kField491_6470, "c", "B");
			break;

		case 4:
			setCallback(5);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarGreenSleeping, EntityData::kField491_7250);
			break;

		case 5:
			setCallback(6);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarGreenSleeping, EntityData::kField491_7500, "b", "C");
			break;

		case 6:
			setCallback(7);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarGreenSleeping, EntityData::kField491_7950);
			break;

		case 7:
			setCallback(8);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarGreenSleeping, EntityData::kField491_8200, "a", "NODIALOG");
			break;

		case 8:
			setCallback(9);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarGreenSleeping, EntityData::kField491_9460);
			break;

		case 9:
			if (getEntityData(kEntityNone)->car == kCarGreenSleeping) {
				getProgress().field_14 = 0;
				getEntities()->prepareSequences(kEntityGendarmes);
				getSavePoints()->push(kEntityGendarmes, kEntityVerges, kAction168710784);
				setup_function13();
				break;
			}

			setCallback(10);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarRedSleeping, EntityData::kField491_2490);
			break;

		case 10:
			setCallback(11);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarRedSleeping, EntityData::kField491_2740, "h", "NODIALOG");
			break;

		case 11:
			setCallback(12);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarRedSleeping, EntityData::kField491_3820);
			break;

		case 12:
			setCallback(13);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarRedSleeping, EntityData::kField491_4070, "f", "E");
			break;

		case 13:
			setCallback(14);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarRedSleeping, EntityData::kField491_4590);
			break;

		case 14:
			setCallback(15);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarRedSleeping, EntityData::kField491_4840, "e", "F");
			break;

		case 15:
			setCallback(16);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarRedSleeping, EntityData::kField491_5540);
			break;

		case 16:
			setCallback(17);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarRedSleeping, EntityData::kField491_5790, "d", "G");
			break;

		case 17:
			setCallback(18);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarRedSleeping, EntityData::kField491_6220);
			break;

		case 18:
			setCallback(19);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarRedSleeping, EntityData::kField491_6470, "c", "H");
			break;

		case 19:
			setCallback(20);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarRedSleeping, EntityData::kField491_7250);
			break;

		case 20:
			setCallback(21);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarRedSleeping, EntityData::kField491_7500, "b", "J");
			break;

		case 21:
			setCallback(22);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarRedSleeping, EntityData::kField491_7950);
			break;

		case 22:
			setCallback(23);
			call(new ENTITY_SETUP_IISS(Gendarmes, setup_function9), kCarRedSleeping, EntityData::kField491_8200, "a", "NODIALOG");
			break;

		case 23:
			setCallback(24);
			call(new ENTITY_SETUP(Gendarmes, setup_function8), kCarRedSleeping, EntityData::kField491_9460);
			break;

		case 24:
			getProgress().field_14 = 0;
			getEntities()->prepareSequences(kEntityGendarmes);
			getSavePoints()->push(kEntityGendarmes, kEntityVerges, kAction168710784);
			setup_function13();
			break;
		}		
		break;
	}
}

IMPLEMENT_FUNCTION(Gendarmes, function13, 13)
	if (savepoint.action == kActionDefault)
		getData()->car = kCarNone;
}

IMPLEMENT_FUNCTION(Gendarmes, chapter2, 14)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityGendarmes);
}

IMPLEMENT_FUNCTION(Gendarmes, chapter3, 15)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityGendarmes);
}

IMPLEMENT_FUNCTION(Gendarmes, chapter4, 16)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityGendarmes);
}

IMPLEMENT_FUNCTION(Gendarmes, chapter5, 17)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityGendarmes);
}

void Gendarmes::arrest(const SavePoint &savepoint, bool shouldPlaySound, int a3) {
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS);

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
	case kAction17:
		if (!ENTITY_PARAM(0, 1) && getEntities()->checkSequence0(kEntityGendarmes)) {
			getSound()->playSound(kEntityNone, "MUS007");
			ENTITY_PARAM(0, 1) = 1;
		}

		if (getEntities()->checkFields9(kEntityGendarmes, kEntityNone, 1000) && !getEntityData(kEntityNone)->field_493) {
			setCallback(1);
			call(new ENTITY_SETUP(Gendarmes, setup_savegame), kSavegameType2, kEventGendarmesArrestation);
		}
		break;

	case kActionExitCompartment:
		CALLBACK_ACTION();
		break;

	case kActionDefault:
		if (!shouldPlaySound)
			getEntities()->drawSequenceRight(kEntityGendarmes, params->seq1);
		else
			getSound()->playSound(kEntityGendarmes, params->seq1, a3);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventGendarmesArrestation);
			getLogic()->gameOver(kTimeType0, kTime1, kSceneGameOverPolice1, true);
		}
		break;
	}
}

} // End of namespace LastExpress
