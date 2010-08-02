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
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Vassili::Vassili(LastExpressEngine *engine) : Entity(engine, kEntityVassili) {
	ADD_CALLBACK_FUNCTION(Vassili, reset);
	ADD_CALLBACK_FUNCTION(Vassili, draw);
	ADD_CALLBACK_FUNCTION(Vassili, savegame);
	ADD_CALLBACK_FUNCTION(Vassili, chapter1);
	ADD_CALLBACK_FUNCTION(Vassili, chapter1Handler);
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
	ADD_CALLBACK_FUNCTION(Vassili, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Vassili, chapter5);
}

/**
 * Resets the entity
 */
IMPLEMENT_FUNCTION(Vassili, reset, 1)
	Entity::reset(savepoint);
}

/**
 * Draws the entity
 *
 * @param seq1 The sequence to draw
 */
IMPLEMENT_FUNCTION_S(Vassili, draw, 2)
	Entity::draw(savepoint);
}

/**
 * Save the game
 *
 * @param param1 The SavegameType for the savegame
 * @param param2 The EventIndex for the savegame
 */
IMPLEMENT_FUNCTION_II(Vassili, savegame, 3)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION(Vassili, chapter1, 4)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject40, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, chapter1Handler, 5)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1) {
			getData()->entityPosition = getEntityData(kEntityTatiana)->entityPosition;
			getData()->posture = getEntityData(kEntityTatiana)->posture;
		} else {
			if (params->param3 && params->param3 >= (int)getState()->time) {
				break;
			}else {
				params->param3 = (int)getState()->time + 450;
				if (params->param3 == 0)
					break;
			}

			if (!params->param2 && getObjects()->get(kObjectCompartmentA).location == kLocation1) {
				params->param2 = 1;
				getEntities()->drawSequenceLeft(kEntityVassili, "303A");
				getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
			}
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
		if (getEntities()->isSitting(kEntityNone, kCarRedSleeping, kPosition_8200)) {

			UPDATE_PARAM_FUNCTION(params->param3, getState()->timeTicks, params->param1, label_function7);

			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Vassili, setup_draw), "303B");
			break;
		}

		params->param3 = 0;
		if (params->param2)
			getEntities()->drawSequenceLeft(kEntityVassili, "303A");

label_function7:
		if (params->param4 != kTimeInvalid && getState()->time > kTime1489500) {

			if (getState()->time <= kTime1503000) {

				if (getEntities()->isSitting(kEntityNone, kCarRedSleeping, kPosition_8200) || !params->param4) {

					params->param4 = getState()->time;
					if (!params->param4) {
						setup_function7();
						break;
					}
				}

				if (params->param4 >= (int)getState()->time)
					break;
			}

			params->param4 = kTimeInvalid;
			setup_function7();
		}
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_8200;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;

		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		params->param1 = 5 * (3 * random(25) + 15);

		getEntities()->drawSequenceLeft(kEntityVassili, "303A");
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getEntities()->drawSequenceLeft(kEntityVassili, "303C");
			params->param1 = 5 * (3 * random(25) + 15);
			params->param2 = 1;

			// Shared part with kActionNone
			goto label_function7;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, function7, 7)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1 != kTimeInvalid && getState()->time > kTime1503000) {

			 if (getState()->time <= kTime1512000) {
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

			 params->param1 = kTimeInvalid;
			 setup_function8();
		}
		break;

	case kActionDefault:
		getData()->entityPosition = kPosition_8200;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;

		getEntities()->clearSequences(kEntityVassili);
		if (getEntities()->isSitting(kEntityNone, kCarRedSleeping, kPosition_8200))
			getScenes()->loadSceneFromObject(kObjectCompartmentA);

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
		if (!getEntities()->isSittingOrStanding(kEntityNone, kCarRedSleeping)) {
			getSound()->playSound(kEntityNone, "BUMP");
			getScenes()->loadSceneFromPosition(kCarRedSleeping, (getEntityData(kEntityNone)->car <= kCarRedSleeping) ? 1 : 40);
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
	case kActionDrawScene:
		if ((getObjects()->get(kObjectCompartmentA).location == kLocation2 && getEntities()->isPlayerPosition(kCarRedSleeping, 17))
		|| getEntities()->isPlayerPosition(kCarRedSleeping, 18)
		|| getEntities()->isPlayerPosition(kCarRedSleeping, 37)
		|| getEntities()->isPlayerPosition(kCarRedSleeping, 38)
		|| getEntities()->isPlayerPosition(kCarRedSleeping, 41)) {

			if (savepoint.action == kActionDrawScene)
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
		if (!getProgress().eventCorpseMovedFromFloor) {
			getAction()->playAnimation(kEventMertensCorpseFloor);
			getLogic()->gameOver(kTimeType0, kTime0, kSceneNone, false);
			break;
		}

		if (!getProgress().eventCorpseThrown) {
			getAction()->playAnimation(kEventMertensCorpseBed);
			getLogic()->gameOver(kTimeType0, kTime0, kSceneNone, false);
			break;
		}

		if (getProgress().jacket == kJacketBlood) {
			getAction()->playAnimation(kEventMertensBloodJacket);
			getLogic()->gameOver(kTimeType0, kTime0, kSceneNone, false);
			break;
		}

		// Setup Anna & Coudert
		RESET_ENTITY_STATE(kEntityAnna, Anna, setup_function37);
		RESET_ENTITY_STATE(kEntityCoudert, Coudert, setup_function38);

		setCallback(1);
		call(new ENTITY_SETUP(Vassili, setup_savegame), kSavegameType2, kEventVassiliSeizure);
		break;

	case kActionCallback:
		if (getCallback() != 1)
			break;

		getData()->posture = kPostureSitting;
		getAction()->playAnimation(kEventVassiliSeizure);

        getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
        getObjects()->update(kObjectCompartment1, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
        getProgress().field_18 = 2;

        getSavePoints()->push(kEntityVassili, kEntityAnna, kAction191477936);
        getSavePoints()->push(kEntityVassili, kEntityVerges, kAction191477936);
        getSavePoints()->push(kEntityVassili, kEntityCoudert, kAction191477936);
        getScenes()->loadSceneFromObject(kObjectCompartmentA);

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
		getEntities()->clearSequences(kEntityVassili);

		getData()->entityPosition = kPosition_8200;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

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
		if (getEntities()->isSitting(kEntityNone, kCarRedSleeping, kPosition_8200)) {
			UPDATE_PARAM(params->param3, getState()->timeTicks, params->param1);

			setCallback(1);
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

	case kActionCallback:
		if (getCallback() != 1)
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
		getEntities()->clearSequences(kEntityVassili);

		getData()->entityPosition = kPosition_8200;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, stealEgg, 15)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->isSitting(kEntityNone, kCarRedSleeping, kPosition_8200)) {
			UPDATE_PARAM(params->param3, getState()->timeTicks, params->param1);

			setCallback(1);
			call(new ENTITY_SETUP_SIIS(Vassili, setup_draw), "303B");
		} else {
			params->param3 = 0;
			if (params->param2)
				getEntities()->drawSequenceLeft(kEntityVassili, "303A");
		}
		break;

	case kAction9:
		setCallback(2);
		call(new ENTITY_SETUP(Vassili, setup_savegame), kSavegameType2, kEventVassiliCompartmentStealEgg);
		break;

	case kActionDefault:
		params->param5 = 5 * (3 * random(25) + 15);
		getEntities()->drawSequenceLeft(kEntityVassili, "303A");
		break;

	case kActionDrawScene:
		if (getEntities()->isSitting(kEntityNone, kCarRedSleeping, kPosition_7850)
		 && getInventory()->hasItem(kItemFirebird)
		 && !getEvent(kEventVassiliCompartmentStealEgg))
			getObjects()->update(kObject48, kEntityVassili, kLocationNone, kCursorNormal, kCursorHand);
		else
			getObjects()->update(kObject48, kEntityNone, kLocationNone, kCursorNormal, kCursorHand);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getEntities()->drawSequenceLeft(kEntityVassili, "303C");
			params->param1 = 5 * (3 * random(25) + 15);
			params->param2 = 1;
			break;

		case 2:
			getAction()->playAnimation(kEventVassiliCompartmentStealEgg);
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 67);
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
		setup_chapter4Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityVassili);

		getData()->entityPosition = kPosition_8200;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRedSleeping;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->updateLocation2(kObjectCompartmentA, kLocation1);
		break;
	}
}

// Looks identical to sleeping (#13)
IMPLEMENT_FUNCTION(Vassili, chapter4Handler, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getEntities()->isSitting(kEntityNone, kCarRedSleeping, kPosition_8200)) {
			UPDATE_PARAM(params->param3, getState()->timeTicks, params->param1);

			setCallback(1);
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

	case kActionCallback:
		if (getCallback() != 1)
			break;

		getEntities()->drawSequenceLeft(kEntityVassili, "303C");
		params->param1 = 5 * (3 * random(25) + 15);
		params->param2 = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Vassili, chapter5, 18)
	if (savepoint.action == kActionDefault) {
		getEntities()->clearSequences(kEntityVassili);

		getData()->entityPosition = kPosition_3969;
		getData()->posture = kPostureSitting;
		getData()->car = kCarRestaurant;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;
	}
}

} // End of namespace LastExpress
