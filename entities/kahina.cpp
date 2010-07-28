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

#include "lastexpress/entities/kahina.h"

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

Kahina::Kahina(LastExpressEngine *engine) : Entity(engine, kEntityKahina) {
	ADD_CALLBACK_FUNCTION(Kahina, reset);
	ADD_CALLBACK_FUNCTION(Kahina, playSound);
	ADD_CALLBACK_FUNCTION(Kahina, savegame);
	ADD_CALLBACK_FUNCTION(Kahina, updateFromTime);
	ADD_CALLBACK_FUNCTION(Kahina, updateFromTicks);
	ADD_CALLBACK_FUNCTION(Kahina, function6);
	ADD_CALLBACK_FUNCTION(Kahina, function7);
	ADD_CALLBACK_FUNCTION(Kahina, function8);
	ADD_CALLBACK_FUNCTION(Kahina, enterExitCompartment);
	ADD_CALLBACK_FUNCTION(Kahina, chapter1);
	ADD_CALLBACK_FUNCTION(Kahina, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Kahina, function12);
	ADD_CALLBACK_FUNCTION(Kahina, function13);
	ADD_CALLBACK_FUNCTION(Kahina, function14);
	ADD_CALLBACK_FUNCTION(Kahina, function15);
	ADD_CALLBACK_FUNCTION(Kahina, chapter2);
	ADD_CALLBACK_FUNCTION(Kahina, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Kahina, chapter3);
	ADD_CALLBACK_FUNCTION(Kahina, function19);
	ADD_CALLBACK_FUNCTION(Kahina, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Kahina, function21);
	ADD_CALLBACK_FUNCTION(Kahina, function22);
	ADD_CALLBACK_FUNCTION(Kahina, function23);
	ADD_CALLBACK_FUNCTION(Kahina, function24);
	ADD_CALLBACK_FUNCTION(Kahina, function25);
	ADD_CALLBACK_FUNCTION(Kahina, function26);
	ADD_CALLBACK_FUNCTION(Kahina, function27);
	ADD_CALLBACK_FUNCTION(Kahina, chapter4);
	ADD_CALLBACK_FUNCTION(Kahina, chapter5);
}

IMPLEMENT_FUNCTION(Kahina, reset, 1)
	Entity::reset(savepoint);
}

IMPLEMENT_FUNCTION_S(Kahina, playSound, 2)
	Entity::playSound(savepoint);
}

IMPLEMENT_FUNCTION_II(Kahina, savegame, 3)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_I(Kahina, updateFromTime, 4)
	if (savepoint.action == kAction137503360) {
		ENTITY_PARAM(0, 2) = 1;
		CALLBACK_ACTION()
	}

	Entity::updateFromTime(savepoint);
}

IMPLEMENT_FUNCTION_NOSETUP(Kahina, updateFromTicks, 5)
	Entity::updateFromTicks(savepoint);
}

IMPLEMENT_FUNCTION_I(Kahina, function6, 6)
	error("Kahina: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_II(Kahina, function7, 7)
	error("Kahina: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION_II(Kahina, function8, 8)
	error("Kahina: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Kahina, enterExitCompartment, 9)
	Entity::enterExitCompartment(savepoint);
}

IMPLEMENT_FUNCTION(Kahina, chapter1, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		TIME_CHECK_CHAPTER1(setup_chapter1Handler);
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartmentKronos, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		getData()->entityPosition = kPosition_5000;
		getData()->field_493 = kField493_0;
		getData()->car = kCarKronos;

		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, chapter1Handler, 11)
	if (savepoint.action != kActionNone)
		return;

	if (getState()->time > kTime1107000 && !params->param1 && getProgress().jacket) {
		getSavePoints()->push(kEntityKahina, kEntityMertens, kAction238732837);
		params->param1 = 1;
	}

	if (getProgress().eventMertensChronosInvitation)
		setup_function12();
}

IMPLEMENT_FUNCTION(Kahina, function12, 12)
	error("Kahina: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function13, 13)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().field_14 || getState()->time >= kTime1201500 || params->param2 == kTimeInvalid || params->param1 >= (int)getState()->time)
			break;

		if (getState()->time <= kTime1197000) {
			if (!getEntities()->checkFields7(kCarGreenSleeping) || !params->param2) {
				params->param2 = getState()->time;

				if (!getState()->time)
					goto label_callback;
			}

			if (params->param2 >= (int)getState()->time)
				break;
		}

		params->param2 = kTimeInvalid;

label_callback:
		setCallback(1);
		call(new ENTITY_SETUP(Kahina, setup_function15));
		break;

	case kActionDefault:
		getData()->car = kCarKronos;
		getData()->entityPosition = kPosition_5000;
		getData()->field_493 = kField493_0;

		getObjects()->update(kObjectCompartmentKronos, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

		params->param1 = getState()->time + 1800;
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, function14, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionExitCompartment:
		getEntities()->exitCompartment(kEntityKahina, kObjectCompartmentF, true);
		CALLBACK_ACTION()
		break;

	case kAction4:
		getEntities()->exitCompartment(kEntityKahina, kObjectCompartmentF, true);
		CALLBACK_ACTION()
		break;

	case kActionDefault:
		getEntities()->drawSequenceRight(kEntityKahina, "616Cf");
		getEntities()->enterCompartment(kEntityKahina, kObjectCompartmentF, true);
		getSavePoints()->push(kEntityKahina, kEntityMax, kAction158007856);
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, function15, 15)
	error("Kahina: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter2, 16)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter2Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityKahina);

		getData()->entityPosition = kPosition_6000;
		getData()->field_493 = kField493_0;
		getData()->car = kCarKronos;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorHandKnock, kCursorHand);

		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, chapter2Handler, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1) {
			if (!params->param2)
				params->param2 = getState()->time + 9000;

			if (params->param2 < (int)getState()->time) {
				params->param1 = 1;
				params->param2 = 0;
			}
		}

		if (getEvent(kEventKahinaAskSpeakFirebird) && getEvent(kEventKronosConversationFirebird) && getEntities()->checkFields5(kEntityNone, kCarKronos)) {
			if (!params->param3)
				params->param3 = getState()->time + 900;

			if (params->param3 < (int)getState()->time) {
				params->param3 = kTimeInvalid;

				setCallback(1);
				call(new ENTITY_SETUP(Kahina, setup_savegame), kSavegameType2, kEventKronosConversationFirebird);
				break;
			}
		}

label_callback_3:
		if (getState()->time > kTime1845000 && getEvent(kEventKronosConversationFirebird) && getEntities()->checkFields14()) {
			getObjects()->update(kObjectCompartmentKronos, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
			getScenes()->loadSceneFromPosition(kCarKronos, 87);
		}
		break;

	case kAction8:
	case kAction9:
		if (getEvent(kEventKronosConversationFirebird))
			break;

		if (getEvent(kEventKahinaAskSpeakFirebird)) {
			if (getSound()->isBuffered(kEntityKahina))
				getSound()->processEntry(kEntityKahina);

			if (savepoint.action == kAction8)
				getSound()->playSound(kEntityNone, "LIB012");

			setCallback(4);
			call(new ENTITY_SETUP(Kahina, setup_savegame), kSavegameType2, kEventKronosConversationFirebird);
			break;
		}

		if (getEvent(kEventMilosCompartmentVisitAugust) || getEvent(kEventTatianaGivePoem) || getEvent(kEventTatianaBreakfastGivePoem)) {
			if (savepoint.action == kAction8)
				getSound()->playSound(kEntityNone, "LIB012");

			setCallback(7);
			call(new ENTITY_SETUP(Kahina, setup_savegame), kSavegameType2, kEventKahinaAskSpeakFirebird);
			break;
		}

		if (params->param1) {
			if (savepoint.action == kAction8)
				getSound()->playSound(kEntityNone, "LIB012");

			getAction()->playAnimation(kEventKahinaAskSpeak);
			getScenes()->processScene();

			getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(8);
			call(new ENTITY_SETUP_SIIS(Kahina, setup_playSound), "KRO3003");
		} else {
			getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorNormal, kCursorNormal);

			setCallback(savepoint.action == kAction8 ? 9 : 10);
			call(new ENTITY_SETUP_SIIS(Kahina, setup_playSound), savepoint.action == kAction8 ? "LIB012" : "LIB013");
		}
		break;

	case kActionDefault:
		params->param1 = 1;
		getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorHandKnock, kCursorHand);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
		case 4:
			getAction()->playAnimation(kEventKronosConversationFirebird);
			getObjects()->update(kObjectCompartmentKronos, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
			getScenes()->loadSceneFromPosition(kCarKronos, 80, 1);

			setCallback(getCallback() == 1 ? 2 : 5);
			call(new ENTITY_SETUP(Kahina, setup_updateFromTime), 900);
			break;

		case 2:
		case 5:
			setCallback(getCallback() == 2 ? 3 : 6);
			call(new ENTITY_SETUP_SIIS(Kahina, setup_playSound), "KRO3005");
			break;

		case 3:
			goto label_callback_3;

		case 7:
			getAction()->playAnimation(kEventKahinaAskSpeakFirebird);
			getScenes()->loadSceneFromPosition(kCarKronos, 81);
			getSound()->playSound(kEntityKahina, "KRO3004");
			break;

		case 8:
		case 9:
		case 10:
			getObjects()->update(kObjectCompartmentKronos, kEntityKahina, kLocation1, kCursorHandKnock, kCursorHand);
			if (getCallback() == 8)
				params->param1 = 0;
			break;
		}
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, chapter3, 18)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		setup_chapter3Handler();
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityKahina);

		getData()->entityPosition = kPosition_5000;
		getData()->field_493 = kField493_0;
		getData()->car = kCarKronos;
		getData()->clothes = kClothesDefault;
		getData()->inventoryItem = kItemNone;

		break;
	}
}

IMPLEMENT_FUNCTION_II(Kahina, function19, 19)
	error("Kahina: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter3Handler, 20)
	error("Kahina: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function21, 21)
	error("Kahina: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function22, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (params->param1) {
			ObjectLocation location = getInventory()->getEntry(kItemFirebird)->location;

			if (ENTITY_PARAM(0, 3) || location == kLocation3 || location == kLocation7) {
				setCallback(1);
				call(new ENTITY_SETUP(Kahina, setup_function25));
			} else if (location == kLocation2 || location == kLocation1) {
				setCallback(2);
				call(new ENTITY_SETUP(Kahina, setup_function26));
			}
		}
		break;

	case kActionDefault:
		getData()->car = kCarKronos;
		getData()->entityPosition = kPosition_5000;
		getData()->field_493 = kField493_0;
		break;

	case kActionDrawScene:
		if (getData()->car > kCarGreenSleeping || (getData()->car == kCarGreenSleeping && getData()->entityPosition > kPosition_2740))
			params->param1 = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Kahina, function23, 23)
	error("Kahina: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function24, 24)
	error("Kahina: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function25, 25)
	error("Kahina: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function26, 26)
	error("Kahina: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, function27, 27)
	error("Kahina: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(Kahina, chapter4, 28)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityKahina);
}

IMPLEMENT_FUNCTION(Kahina, chapter5, 29)
	if (savepoint.action == kActionDefault)
		getEntities()->clearSequences(kEntityKahina);
}

} // End of namespace LastExpress
