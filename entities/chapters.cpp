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
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1_init);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, chapter2);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, chapter3);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, chapter5);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
	ADD_CALLBACK_FUNCTION(Chapters, nullfunc);
}

void Chapters::nullfunc(SavePoint *savepoint) {
	error("Chapters: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter1, 4) {
	if (savepoint->action != kActionDefault)
		return;

	getSavePoints()->addData(kEntityChapters, kAction171843264, 0);
	setup_chapter1_init();
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

	_data->getCurrentParameters()->param1 = 40;

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

IMPLEMENT_FUNCTION(Chapters, chapter2, 10) {

}

IMPLEMENT_FUNCTION(Chapters, chapter3, 13) {

}

IMPLEMENT_FUNCTION(Chapters, chapter4, 17) {

}

IMPLEMENT_FUNCTION(Chapters, chapter5, 20) {

}

} // End of namespace LastExpress
