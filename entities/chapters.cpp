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

#include "lastexpress/entities/chapters.h"

#include "lastexpress/entities/abbot.h"
#include "lastexpress/entities/alexei.h"
#include "lastexpress/entities/alouan.h"
#include "lastexpress/entities/anna.h"
#include "lastexpress/entities/august.h"
#include "lastexpress/entities/boutarel.h"
#include "lastexpress/entities/coudert.h"
#include "lastexpress/entities/francois.h"
#include "lastexpress/entities/gendarmes.h"
#include "lastexpress/entities/hadija.h"
#include "lastexpress/entities/ivo.h"
#include "lastexpress/entities/kahina.h"
#include "lastexpress/entities/mahmud.h"
#include "lastexpress/entities/max.h"
#include "lastexpress/entities/mertens.h"
#include "lastexpress/entities/milos.h"
#include "lastexpress/entities/mmeboutarel.h"
#include "lastexpress/entities/rebecca.h"
#include "lastexpress/entities/salko.h"
#include "lastexpress/entities/sophie.h"
#include "lastexpress/entities/tatiana.h"
#include "lastexpress/entities/vassili.h"
#include "lastexpress/entities/verges.h"
#include "lastexpress/entities/vesna.h"
#include "lastexpress/entities/yasmin.h"

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
#include "lastexpress/resource.h"

namespace LastExpress {

Chapters::Chapters(LastExpressEngine *engine) : Entity(engine, kEntityChapters) {
	ADD_CALLBACK_FUNCTION(Chapters, savegame);
	ADD_CALLBACK_FUNCTION(Chapters, enterStation);
	ADD_CALLBACK_FUNCTION(Chapters, exitStation);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1);
	ADD_CALLBACK_FUNCTION(Chapters, resetMainEntities);
	ADD_CALLBACK_FUNCTION(Chapters, function6);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1_init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1_end);
	ADD_CALLBACK_FUNCTION(Chapters, chapter2);
	ADD_CALLBACK_FUNCTION(Chapters, chapter2_init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter2_handler);
	ADD_CALLBACK_FUNCTION(Chapters, chapter3);
	ADD_CALLBACK_FUNCTION(Chapters, chapter3_init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter3_handler);
	ADD_CALLBACK_FUNCTION(Chapters, function16);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4_init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4_handler);
	ADD_CALLBACK_FUNCTION(Chapters, chapter5);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4_init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4_handler);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(Chapters, savegame, 1)
	Entity::savegame(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(Chapters, enterStation, 2)
	error("Chapters: callback function 2 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(Chapters, exitStation, 3)
	error("Chapters: callback function 3 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter1, 4)
	if (savepoint.action == kActionDefault) {
		getSavePoints()->addData(kEntityChapters, kAction171843264, 0);
		setup_chapter1_init();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, resetMainEntities, 5)
	if (savepoint.action != kActionDefault)
		return;

	RESET_ENTITY_STATE(kEntityAbbot, Abbot, setup_function1);
	RESET_ENTITY_STATE(kEntityAlexei, Alexei, setup_function1);
	RESET_ENTITY_STATE(kEntityAlouan, Alouan, setup_function1);
	RESET_ENTITY_STATE(kEntityAnna, Anna, setup_function1);
	RESET_ENTITY_STATE(kEntityAugust, August, setup_function1);
	RESET_ENTITY_STATE(kEntityMertens, Mertens, setup_function1);
	RESET_ENTITY_STATE(kEntityCoudert, Coudert, setup_function1);
	RESET_ENTITY_STATE(kEntityFrancois, Francois, setup_function1);
	RESET_ENTITY_STATE(kEntityHadija, Hadija, setup_function1);
	RESET_ENTITY_STATE(kEntityIvo, Ivo, setup_function1);
	RESET_ENTITY_STATE(kEntityKahina, Kahina, setup_function1);
	RESET_ENTITY_STATE(kEntityMmeBoutarel, MmeBoutarel, setup_function1);
	RESET_ENTITY_STATE(kEntityMahmud, Mahmud, setup_function1);
	RESET_ENTITY_STATE(kEntityMax, Max, setup_function1);
	RESET_ENTITY_STATE(kEntityMilos, Milos, setup_function1);
	RESET_ENTITY_STATE(kEntityBoutarel, Boutarel, setup_function1);
	RESET_ENTITY_STATE(kEntityGendarmes, Gendarmes, setup_function1);
	RESET_ENTITY_STATE(kEntityRebecca, Rebecca, setup_function1);
	RESET_ENTITY_STATE(kEntitySalko, Salko, setup_function1);
	RESET_ENTITY_STATE(kEntitySophie, Sophie, setup_function1);
	RESET_ENTITY_STATE(kEntityTatiana, Tatiana, setup_function1);
	RESET_ENTITY_STATE(kEntityVerges, Verges, setup_function1);
	RESET_ENTITY_STATE(kEntityVassili, Vassili, setup_function1);
	RESET_ENTITY_STATE(kEntityVesna, Vesna, setup_function1);
	RESET_ENTITY_STATE(kEntityYasmin, Yasmin, setup_function1);

	CALL_PREVIOUS_SAVEPOINT();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, function6, 6)
	error("Chapters: callback function 6 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter1_init, 7)
	if (savepoint.action != kActionDefault)
		return;

	getProgress().chapter = kChapter1;
	getSound()->resetState();

	getState()->time = kTimeChapter1;
	getState()->timeDelta = 0;
	getProgress().field_50 = 1;
	getProgress().portrait = kPortraitOriginal;
	getProgress().field_18 = 1;
	getProgress().field_7C = 1;

	// Setup inventory & items location
	getInventory()->addItem(kItemTelegram);
	getInventory()->addItem(kItemArticle);

	getInventory()->setLocationAndProcess(kItemScarf, kLocation1);
	getInventory()->setLocationAndProcess(kItemParchemin, kLocation1);
	getInventory()->setLocationAndProcess(kItemGreenJacket, kLocation1);
	getInventory()->setLocationAndProcess(kItemCorpse, kLocation1);
	getInventory()->setLocationAndProcess(kItemPassengerList, kLocation1);
	getInventory()->setLocationAndProcess(kItem5, kLocation1);
	getInventory()->setLocationAndProcess(kItem7, kLocation1);
	getInventory()->setLocationAndProcess(kItem3, kLocation1);
	getInventory()->setLocationAndProcess(kItemMatch, kLocation1);
	getInventory()->setLocationAndProcess(kItem22, kLocation1);
	getInventory()->setLocationAndProcess(kItemPaper, kLocation1);

	getObjects()->update(kObjectCompartment1, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
	getObjects()->update(kObjectOutside, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

	for (uint i = kObjectCompartment1; i <= kObjectCompartment8; i++) {
		getObjects()->updateLocation2((ObjectIndex)i, kLocation2);
	}

	for (uint i = kObjectCompartmentA; i <= kObjectCompartmentH; i++) {
		getObjects()->updateLocation2((ObjectIndex)i, kLocation2);
	}

	params->param1 = 40;

	getObjects()->updateLocation2(kObject25, kLocation1);
	getObjects()->updateLocation2(kObjectGreenSleepingCar, kLocation1);
	getObjects()->updateLocation2(kObject98, kLocation1);
	getObjects()->updateLocation2(kObjectRestaurantCar, kLocation1);

	getObjects()->update(kObject25, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObjectGreenSleepingCar, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObjectRedSleepingCar, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject28, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject56, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject54, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObjectRestaurantCar, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject59, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject66, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject64, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject65, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject69, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject98, kEntityNone, kLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObjectHandleOutsideLeft, kEntityNone, kLocation1, kCursorNormal, kCursorHandKnock);
	getObjects()->update(kObjectHandleOutsideRight, kEntityNone, kLocation1, kCursorNormal, kCursorHandKnock);
	getObjects()->update(kObject101, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);

	setup_chapter1_handler();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter1_handler, 8)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
label_callback_1:
label_callback_2:
label_callback_3:
label_callback_4:
label_callback_5:
label_callback_6:
label_callback_7:
label_callback_8:
label_callback_9:
label_callback_10:
label_callback_11:
label_callback_12:
label_callback_13:
label_callback_14:
label_callback_15:
label_callback_16:
label_callback_18:
label_callback_19:
label_callback_20:
label_callback_21:
		error("Chapters::chapter1_handler: action kActionNone not implemented!");
		break;

	case kAction2:
		error("Chapters::chapter1_handler: action kAction2 not implemented!");
		break;

	case kActionDefault:
		params->param2 = 225 * (4 * random(5) + 20);
		break;

	case kAction17:
		if (params->param3)
			break;

		if (getEntities()->isPlayerPosition(kCarGreenSleeping, 1)) {
			getState()->time = kTimeChapter1;
			getState()->timeDelta = 3;
			params->param3 = 1;
		}
		break;

	case kAction18:
		switch (_data->getNextCallback()) {
		default:
			break;

		case 1:
			goto label_callback_1;

		case 2:
			goto label_callback_2;

		case 3:
			goto label_callback_3;

		case 4:
			params->param5 = 0;
			goto label_callback_4;

		case 5:
			goto label_callback_5;

		case 6:
			goto label_callback_6;

		case 7:
			goto label_callback_7;

		case 8:
			goto label_callback_8;

		case 9:
			goto label_callback_9;

		case 10:
			goto label_callback_10;

		case 11:
			goto label_callback_11;

		case 12:
			goto label_callback_12;

		case 13:
			goto label_callback_13;

		case 14:
			goto label_callback_14;

		case 15:
			goto label_callback_15;

		case 16:
			getState()->time = kTimeChapter1_0;
			goto label_callback_16;

		case 17:
			getProgress().field_18 = 1;
			_data->setNextCallback(18);
			call(new ENTITY_SETUP_SIIS(Chapters, setup_enterStation), "Strasbou", 7);
			break;

		case 18:
			goto label_callback_18;

		case 19:
			getState()->timeDelta = 1;
			goto label_callback_19;

		case 20:
			goto label_callback_20;

		case 21:
			goto label_callback_21;

		case 22:
			params->param5 = 1;
			break;

		case 23:
			params->param1 = 1;
			break;
		}
		break;

	case kAction169629818:
		_data->setNextCallback(22);
		call(new ENTITY_SETUP_SIIS(Chapters, setup_enterStation), "Unschedu", 16);
		break;

	case kAction190346110:
		getProgress().field_18 = 3;

		if (getState()->time >= kTimeChapter1_1) {
			setup_chapter1_end();
		} else {
			_data->setNextCallback(23);
			call(new ENTITY_SETUP(Chapters, setup_function6));
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter1_end, 9)
	if (savepoint.action == kActionDefault) {
		// Reset sound cache
		if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
			getSound()->removeFromQueue(kEntityChapters);
			ENTITY_PARAM(0, 2) = 0;
			ENTITY_PARAM(0, 3) = 0;
		}

		getSound()->playSound(kEntityNone, "MUS008", 16);
		getInventory()->unselectItem();

		while (getSound()->isFileInQueue("MUS008"))
			getSound()->unknownFunction1();

		setup_chapter2();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter2, 10)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		// Setup for chapter 2 in case it hasn't been done before
		if (getProgress().chapter != kChapter2) {
			getProgress().chapter = kChapter2;
			getEntities()->setup(kChapter2);
		}

		// Set game time & delta
		getState()->time = kTimeChapter2;
		getState()->timeDelta = 5;

		// Save game
		_data->setNextCallback(1);
		call(new ENTITY_SETUP(Chapters, setup_savegame), 1, kEventNone);
		break;

	case kAction18:
		if (_data->getNextCallback() == 1) {
			if (!_engine->getResourceManager()->loadArchive(kArchiveCd2)) {
				getLogic()->showMenu(true);
				return;
			}

			// Load scene data
			getLogic()->loadSceneDataFile(kArchiveCd2);
			setup_chapter2_init();
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter2_init, 11)
	if (savepoint.action != kActionDefault)
		return;

	getProgress().event_corpse_moved_from_floor = 1;
	getProgress().field_18 = 1;
	getProgress().field_50 = 1;
	getProgress().event_corpse_found = 1;

	// Switch to green jacket/portrait
	getProgress().jacket = kJacketGreen;
	getProgress().portrait = kPortraitGreen;

	// Setup inventory & items location
	getInventory()->addItem(kItemGreenJacket);

	getObjects()->update(kObjectHandleOutsideLeft, kEntityNone, kLocation1, kCursorNormal, kCursorHand);
	getObjects()->update(kObjectHandleOutsideRight, kEntityNone, kLocation1, kCursorNormal, kCursorHand);

	getInventory()->setLocationAndProcess(kItemBeetle, kLocation3);
	getInventory()->setLocationAndProcess(kItem3, kLocation1);

	for (uint i = 1; i < 9; i++) {
		getObjects()->updateLocation2((ObjectIndex)i, kLocation2);
	}

	for (uint i = 33; i < 40; i++) {
		getObjects()->updateLocation2((ObjectIndex)i, kLocation2);
	}

	params->param1 = 40;

	getSavePoints()->push(kEntityChapters, kEntityTables0, kAction103798704);
	getSavePoints()->push(kEntityChapters, kEntityTables1, kAction103798704);
	getSavePoints()->push(kEntityChapters, kEntityTables2, kAction103798704);
	getSavePoints()->push(kEntityChapters, kEntityTables3, kAction103798704);
	getSavePoints()->push(kEntityChapters, kEntityTables4, kAction103798704);

	getObjects()->update(kObjectCompartment1, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
	getObjects()->update(kObjectOutside, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

	// Reset sound cache
	if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
		getSound()->removeFromQueue(kEntityChapters);
		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
	}

	getAction()->playAnimation(kEventTrainPassing);

	if (getInventory()->hasItem(kItemScarf))
		getLogic()->loadScene(kScene41);
	else
		getLogic()->loadSceneFromPosition(kCarGreenSleeping, 79);

	setup_chapter2_handler();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter2_handler, 12)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!getProgress().field_50)
			break;

		UPDATE_PARAM_FROM_TICKS(2, params->param1);

		switch (random(5)) {
		default:
			break;

		case 1:
			getSound()->playSound(kEntityNone, "ZFX1005", random(15) + 2);
			break;

		case 2:
			getSound()->playSound(kEntityNone, "ZFX1006", random(15) + 2);
			break;

		case 3:
			getSound()->playSound(kEntityNone, "ZFX1007A", random(15) + 2);
			break;

		case 4:
			getSound()->playSound(kEntityNone, "ZFX1007B", random(15) + 2);
			break;
		}

		params->param1 = 225 * (4 * random(5) + 20);
		params->param2 = 0;
		break;

	case kActionDefault:
		params->param1 = 225 * (4 * random(5) + 20);
		break;

	case kActionChapter3:
		setup_chapter3();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter3, 13)
	if (savepoint.action == kActionDefault) {
		// Setup for chapter 3 in case it hasn't been done before
		if (getProgress().chapter != kChapter3) {
			getProgress().chapter = kChapter3;
			getEntities()->setup(kChapter3);
		}

		// Set game time & delta
		getState()->time = kTimeChapter3;
		getState()->timeDelta = 5;

		setup_chapter3_init();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter3_init, 14)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityChapters, kEntityTables0, kAction103798704);
		getSavePoints()->push(kEntityChapters, kEntityTables1, kAction103798704);
		getSavePoints()->push(kEntityChapters, kEntityTables2, kAction103798704);
		getSavePoints()->push(kEntityChapters, kEntityTables3, kAction103798704);
		getSavePoints()->push(kEntityChapters, kEntityTables4, kAction103798704);
		getSavePoints()->push(kEntityChapters, kEntityTables5, kAction103798704);

		getProgress().field_50 = 1;

		getObjects()->update(kObjectHandleOutsideLeft, kEntityNone, kLocation1, kCursorNormal, kCursorHand);
		getObjects()->update(kObjectHandleOutsideRight, kEntityNone, kLocation1, kCursorNormal, kCursorHand);
		getInventory()->setLocationAndProcess(kItemBriefcase, kLocation1);
		getInventory()->setLocationAndProcess(kItem3, kLocation1);
		getObjects()->updateLocation2(kObjectCompartment1, kLocation2);
		getObjects()->update(kObject107, kEntityNone, kLocation3, kCursorKeepValue, kCursorKeepValue);

		if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
			getSound()->removeFromQueue(kEntityChapters);
			ENTITY_PARAM(0, 2) = 0;
			ENTITY_PARAM(0, 3) = 0;
		}

		getLogic()->loadSceneFromPosition(kCarRestaurant, 60);
		getInventory()->show(true);

		_data->setNextCallback(1);
		call(new ENTITY_SETUP(Chapters, setup_savegame), 1, kEventNone);
		break;

	case kAction18:
		if (_data->getNextCallback() == 1)
			setup_chapter3_handler();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter3_handler, 15)
	error("Chapters: callback function chapter3_handler not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, function16, 16)
	error("Chapters: callback function 16 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter4, 17)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		// Setup for chapter 4 in case it hasn't been done before
		if (getProgress().chapter != kChapter4) {
			getProgress().chapter = kChapter4;
			getEntities()->setup(kChapter4);
		}

		// Set game time & delta
		getState()->time = kTimeChapter4;
		getState()->timeDelta = 5;

		// Save game
		_data->setNextCallback(1);
		call(new ENTITY_SETUP(Chapters, setup_savegame), 1, kEventNone);
		break;

	case kAction18:
		if (_data->getNextCallback() == 1) {
			if (!_engine->getResourceManager()->loadArchive(kArchiveCd3)) {
				getLogic()->showMenu(true);
				return;
			}

			// Load scene data
			getLogic()->loadSceneDataFile(kArchiveCd3);
			setup_chapter4_init();
		}
		break;

	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter4_init, 18)
	if (savepoint.action != kActionDefault)
		return;

	getSound()->unknownFunction3();
	getSound()->resetState();

	getProgress().field_50 = 1;

	getObjects()->update(kObjectHandleOutsideLeft, kEntityNone, kLocation1, kCursorNormal, kCursorHand);
	getObjects()->update(kObjectHandleOutsideRight, kEntityNone, kLocation1, kCursorNormal, kCursorHand);

	getSavePoints()->push(kEntityChapters, kEntityTrain, kAction203419131);
	getSavePoints()->push(kEntityChapters, kEntityTables0, kAction103798704);
	getSavePoints()->push(kEntityChapters, kEntityTables1, kAction103798704);
	getSavePoints()->push(kEntityChapters, kEntityTables2, kAction103798704);
	getSavePoints()->push(kEntityChapters, kEntityTables3, kAction103798704);
	getSavePoints()->push(kEntityChapters, kEntityTables4, kAction103798704);
	getSavePoints()->push(kEntityChapters, kEntityTables5, kAction103798704);

	getLogic()->loadSceneFromItem(kItem3);

	getInventory()->setLocationAndProcess(kItemBomb, kLocation1);

	if (getInventory()->getEntry(kItemBeetle)->location == kLocation3)
		getLogic()->loadSceneFromItem(kItemBeetle);

	getObjects()->updateLocation2(kObject25, kLocation2);
	getObjects()->update(kObject107, kEntityNone, kLocation3, kCursorKeepValue, kCursorKeepValue);

	if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
		getSound()->removeFromQueue(kEntityChapters);
		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
	}

	if (getInventory()->hasItem(kItemFirebird))
		getLogic()->loadSceneFromPosition(kCarGreenSleeping, 76);
	else
		getLogic()->loadSceneFromPosition(kCarRestaurant, 69);

	getInventory()->show(true);
	setup_chapter4_handler();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter4_handler, 19)
	error("Chapters: callback function 19 not implemented!");
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter5, 20)
	if (savepoint.action == kActionDefault) {
		// Setup for chapter 5 in case it hasn't been done before
		if (getProgress().chapter != kChapter5) {
			getProgress().chapter = kChapter5;
			getEntities()->setup(kChapter5);
		}

		// Set game time & delta
		getState()->time = kTimeChapter5;
		getState()->timeDelta = 2;

		setup_chapter5_init();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter5_init, 21)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->prepareSequences(kEntityTables0);
		getEntities()->prepareSequences(kEntityTables1);
		getEntities()->prepareSequences(kEntityTables2);
		getEntities()->prepareSequences(kEntityTables3);
		getEntities()->prepareSequences(kEntityTables4);
		getEntities()->prepareSequences(kEntityTables5);

		getProgress().field_50 = 1;

		getObjects()->update(kObjectHandleOutsideLeft, kEntityNone, kLocation1, kCursorNormal, kCursorHand);
		getObjects()->update(kObjectHandleOutsideRight, kEntityNone, kLocation1, kCursorNormal, kCursorHand);
		getObjects()->update(kObjectCompartment1, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment2, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment3, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment4, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment5, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment6, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment7, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment8, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentA, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentB, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentC, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentD, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentE, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentF, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentG, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentH, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleBathroom, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectKitchen, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject20, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject21, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject22, kEntityNone, kLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject48, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject51, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject53, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleOutsideLeft, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleOutsideRight, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		getProgress().field_18 = 1;
		getProgress().field_84 = 1;
		getProgress().portrait = kCursorPortraitYellow;

		getInventory()->unselectItem();

		getInventory()->removeItem(kItemKey);
		getInventory()->removeItem(kItemBomb);
		getInventory()->removeItem(kItemMatch);

		if (getInventory()->hasItem(kItemFirebird)) {
			getInventory()->removeItem(kItemFirebird);
			getInventory()->setLocationAndProcess(kItemFirebird, kLocation3);

			if (getInventory()->hasItem(kItemWhistle)) {
				getInventory()->removeItem(kItemWhistle);
				getInventory()->setLocationAndProcess(kItemWhistle, kLocation3);
			}
		}

		getObjects()->update(kObject93, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject94, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject101, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		getObjects()->updateLocation2(kObject98, kLocation2);
		getObjects()->updateLocation2(kObjectRestaurantCar, kLocation2);

		if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
			getSound()->removeFromQueue(kEntityChapters);
			ENTITY_PARAM(0, 2) = 0;
			ENTITY_PARAM(0, 3) = 0;
		}

		getLogic()->loadSceneFromPosition(kCarBaggageRear, 95);
		getInventory()->show(true);

		_data->setNextCallback(1);
		call(new ENTITY_SETUP(Chapters, setup_savegame), 1, kEventNone);
		break;

	case kAction18:
		if (_data->getNextCallback() == 1)
			setup_chapter5_handler();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(Chapters, chapter5_handler, 22)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTimeChapter5_0) {
			if (!params->param2) {
				params->param2 = 1;

				if (!getProgress().is_nighttime) {
					getSound()->playSound(kEntityChapters, "ARRIVE", 8);
					getSound()->unknownFunction3();
				}
			}
		}

		if (getState()->time > kTimeTrainStopped2) {
			if (!params->param3) {
				params->param3 = 1;

				if (!getEvent(kEventLocomotiveMilos) && !getEvent(kEventLocomotiveMilosNight)) {
					getSound()->playSound(kEntityChapters, "ARRIVE", 8);
					getSound()->unknownFunction3();
				}
			}
		}
		break;

	case kAction2:
		if (getState()->time <= kTimeTrainStopped2) {
			_data->setNextCallback(1);
			call(new ENTITY_SETUP(Chapters, setup_savegame), 2, kEventTrainStopped);
		} else {
			getLogic()->gameOver(kTimeType1, kTimeTrainStopped2, kSceneGameOverTrainStopped, true);
		}
		break;

	case kActionDefault:
		params->param1 = 225 * (4 * random(10) + 20);
		break;

	case kAction18:
		if (_data->getNextCallback() == 1) {
			getAction()->playAnimation(kEventTrainStopped);
			getLogic()->gameOver(kTimeType1, kTimeTrainStopped, kSceneGameOverTrainStopped, true);
		}
		break;

	case kAction135800432:
		getProgress().is_nighttime = 1;
		getState()->time = kTimeChapter5_1;

		if (getSound()->isBuffered(kEntityChapters))
			getSound()->removeFromQueue(kEntityChapters);
		break;
	}
}

} // End of namespace LastExpress
