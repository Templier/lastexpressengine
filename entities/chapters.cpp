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

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savegame.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

Chapters::Chapters(LastExpressEngine *engine) : Entity(engine, kEntityChapters) {
	ADD_CALLBACK_FUNCTION(Chapters, savegame);
	ADD_CALLBACK_FUNCTION(Chapters, function2);
	ADD_CALLBACK_FUNCTION(Chapters, function3);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1);
	ADD_CALLBACK_FUNCTION(Chapters, function5);
	ADD_CALLBACK_FUNCTION(Chapters, function6);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1_init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1_handler);
	ADD_CALLBACK_FUNCTION(Chapters, function9);
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

IMPLEMENT_FUNCTION_II(Chapters, savegame, 1)
	CALL_SAVEGAME(kEntityChapters)
}

IMPLEMENT_FUNCTION_SI(Chapters, function2, 2)
	error("Chapters: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_S(Chapters, function3, 3)
	error("Chapters: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter1, 4)
	if (savepoint->action == kActionDefault) {
		getSavePoints()->addData(kEntityChapters, kAction171843264, 0);
		setup_chapter1_init();
	}
}

IMPLEMENT_FUNCTION(Chapters, function5, 5)
	error("Chapters: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function6, 6)
	error("Chapters: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter1_init, 7)
	if (savepoint->action != kActionDefault)
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

	for (uint i = 1; i < 9; i++) {
		getObjects()->updateLocation2((ObjectIndex)i, kLocation2);
	}

	for (uint i = 32; i < 40; i++) {
		getObjects()->updateLocation2((ObjectIndex)i, kLocation2);
	}

	CURRENT_PARAM(1) = 40;

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

IMPLEMENT_FUNCTION(Chapters, chapter1_handler, 8)
	switch (savepoint->action) {
	default:
		error("Chapters: callback function 8 not implemented!");
		break;

	case kActionDefault:
		CURRENT_PARAM(2) = 225 * (4 * random(5) + 20);
		break;


	case kAction17:
		if (CURRENT_PARAM(3))
			break;

		getState()->time = kTimeChapter1;
		getState()->timeDelta = 3;
		CURRENT_PARAM(3) = 1;
		break;
	}
}

IMPLEMENT_FUNCTION(Chapters, function9, 9)
	if (savepoint->action == kActionDefault) {
		// Reset sound cache
		if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
			getSound()->reset(kEntityChapters);
			ENTITY_PARAM(0, 2) = 0;
			ENTITY_PARAM(0, 3) = 0;
		}

		getSound()->playSound(kEntityNone, "MUS008", 16, 0);
		getInventory()->unselectItem();

		while (getSound()->isFileInQueue("MUS008"))
			getSound()->unknownFunction1();

		setup_chapter2();
	}
}

IMPLEMENT_FUNCTION(Chapters, chapter2, 10)
	switch (savepoint->action) {
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
		call(new ENTITY_SETUP_DEFAULT(Chapters, setup_savegame), 1, 0);
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

IMPLEMENT_FUNCTION(Chapters, chapter2_init, 11)
	if (savepoint->action != kActionDefault)
		return;

	getProgress().field_8 = 1;
	getProgress().field_18 = 1;
	getProgress().field_50 = 1;
	getProgress().event_found_corpse = 1;

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

	CURRENT_PARAM(1) = 40;

	getSavePoints()->push(kEntityChapters, kEntityTables0, kAction103798704, 0);
	getSavePoints()->push(kEntityChapters, kEntityTables1, kAction103798704, 0);
	getSavePoints()->push(kEntityChapters, kEntityTables2, kAction103798704, 0);
	getSavePoints()->push(kEntityChapters, kEntityTables3, kAction103798704, 0);
	getSavePoints()->push(kEntityChapters, kEntityTables4, kAction103798704, 0);

	getObjects()->update(kObjectCompartment1, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);
	getObjects()->update(kObjectOutside, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

	// Reset sound cache
	if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
		getSound()->reset(kEntityChapters);
		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
	}

	getAction()->playAnimation(kEventTrainPassing);

	if (getInventory()->hasItem(kItemScarf))
		getLogic()->loadScene(41);
	else
		getLogic()->loadSceneFromData(3, 79, -1);

	setup_chapter2_handler();
}

IMPLEMENT_FUNCTION(Chapters, chapter2_handler, 12)
	error("Chapters: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter3, 13)
	if (savepoint->action == kActionDefault) {
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

IMPLEMENT_FUNCTION(Chapters, chapter3_init, 14)
	error("Chapters: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter3_handler, 15)
	error("Chapters: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function16, 16)
	error("Chapters: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter4, 17)
	switch (savepoint->action) {
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
		call(new ENTITY_SETUP_DEFAULT(Chapters, setup_savegame), 1, 0);
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

IMPLEMENT_FUNCTION(Chapters, chapter4_init, 18)
	error("Chapters: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter4_handler, 19)
	error("Chapters: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter5, 20)
	if (savepoint->action == kActionDefault) {
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

IMPLEMENT_FUNCTION(Chapters, chapter5_init, 21)
	error("Chapters: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter5_handler, 22)
	error("Chapters: callback function 22 not implemented!");
}

} // End of namespace LastExpress
