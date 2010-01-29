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

#include "lastexpress/game/inventory.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Chapters::Chapters(LastExpressEngine *engine) : Entity(engine, kEntityChapters) {
	ADD_CALLBACK_FUNCTION(Chapters, function1);
	ADD_CALLBACK_FUNCTION(Chapters, function2);
	ADD_CALLBACK_FUNCTION(Chapters, function3);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1);
	ADD_CALLBACK_FUNCTION(Chapters, function5);
	ADD_CALLBACK_FUNCTION(Chapters, function6);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1_init);
	ADD_CALLBACK_FUNCTION(Chapters, function8);
	ADD_CALLBACK_FUNCTION(Chapters, function9);
	ADD_CALLBACK_FUNCTION(Chapters, chapter2);
	ADD_CALLBACK_FUNCTION(Chapters, function11);
	ADD_CALLBACK_FUNCTION(Chapters, function12);
	ADD_CALLBACK_FUNCTION(Chapters, chapter3);
	ADD_CALLBACK_FUNCTION(Chapters, function14);
	ADD_CALLBACK_FUNCTION(Chapters, function15);
	ADD_CALLBACK_FUNCTION(Chapters, function16);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4);
	ADD_CALLBACK_FUNCTION(Chapters, function18);
	ADD_CALLBACK_FUNCTION(Chapters, function19);
	ADD_CALLBACK_FUNCTION(Chapters, chapter5);
	ADD_CALLBACK_FUNCTION(Chapters, function21);
	ADD_CALLBACK_FUNCTION(Chapters, function22);
}

IMPLEMENT_FUNCTION_II(Chapters, function1, 1) {
	error("Chapters: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_SI(Chapters, function2, 2) {
	error("Chapters: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_S(Chapters, function3, 3) {
	error("Chapters: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter1, 4) {
	if (savepoint->action != kActionDefault)
		return;

	getSavePoints()->addData(kEntityChapters, kAction171843264, 0);
	setup_chapter1_init();
}

IMPLEMENT_FUNCTION(Chapters, function5, 5) {
	error("Chapters: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function6, 6) {
	error("Chapters: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter1_init, 7) {
	if (savepoint->action != kActionDefault)
		return;

	getProgress().chapter = kChapter1;
	// TODO function call modifying an unknown global var
	getState()->time = 1061100;
	getState()->timeDelta = 0;
	getProgress().field_50 = 1;
	getProgress().portrait = kPortraitOriginal;
	getProgress().field_18 = 1;
	getProgress().field_7C = 1;

	// Setup inventory & items location
	getInventory()->addItem(kTelegram);
	getInventory()->addItem(kArticle);

	getInventory()->setLocationAndProcess(kScarf, kLocation1);
	getInventory()->setLocationAndProcess(kParchemin, kLocation1);
	getInventory()->setLocationAndProcess(kGreenJacket, kLocation1);
	getInventory()->setLocationAndProcess(kCorpse, kLocation1);
	getInventory()->setLocationAndProcess(kPassengerList, kLocation1);
	getInventory()->setLocationAndProcess(kItem5, kLocation1);
	getInventory()->setLocationAndProcess(kItem7, kLocation1);
	getInventory()->setLocationAndProcess(kItem3, kLocation1);
	getInventory()->setLocationAndProcess(kMatch, kLocation1);
	getInventory()->setLocationAndProcess(kItem22, kLocation1);
	getInventory()->setLocationAndProcess(kPaper, kLocation1);

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

	// TODO call another function 8
}

IMPLEMENT_FUNCTION(Chapters, function8, 8) {
	error("Chapters: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function9, 9) {
	error("Chapters: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter2, 10) {
	error("Chapters: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function11, 11) {
	error("Chapters: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function12, 12) {
	error("Chapters: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter3, 13) {
	error("Chapters: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function14, 14) {
	error("Chapters: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function15, 15) {
	error("Chapters: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function16, 16) {
	error("Chapters: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter4, 17) {
	error("Chapters: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function18, 18) {
	error("Chapters: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function19, 19) {
	error("Chapters: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter5, 20) {
	error("Chapters: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function21, 21) {
	error("Chapters: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, function22, 22) {
	error("Chapters: callback function 22 not implemented!");
}

} // End of namespace LastExpress
