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

Chapters::Chapters(LastExpressEngine *engine) : Entity(engine, SavePoints::kChapters) {
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

void Chapters::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Chapters: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Chapters, chapter1, 4) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	getSavePoints()->addData(SavePoints::kChapters, 171843264, 0);
	setup_chapter1_init();
}

IMPLEMENT_FUNCTION(Chapters, chapter1_init, 7) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	getProgress().chapter = State::kChapter1;
	// TODO function call modifying an unknown global var
	getState()->time = 1061100;
	getState()->timeDelta = 0;
	getProgress().field_50 = 1;
	getProgress().portrait = Inventory::kPortraitOriginal;
	getProgress().field_18 = 1;
	getProgress().field_7C = 1;

	// Setup inventory & items location
	getInventory()->addItem(Inventory::kTelegram);
	getInventory()->addItem(Inventory::kArticle);

	getInventory()->setLocationAndProcess(Inventory::kScarf, 1);
	getInventory()->setLocationAndProcess(Inventory::kParchemin, 1);
	getInventory()->setLocationAndProcess(Inventory::kGreenJacket, 1);
	getInventory()->setLocationAndProcess(Inventory::kCorpse, 1);
	getInventory()->setLocationAndProcess(Inventory::kPassengerList, 1);
	getInventory()->setLocationAndProcess(Inventory::kItem5, 1);
	getInventory()->setLocationAndProcess(Inventory::kItem7, 1);
	getInventory()->setLocationAndProcess(Inventory::kItem3, 1);
	getInventory()->setLocationAndProcess(Inventory::kMatch, 1);
	getInventory()->setLocationAndProcess(Inventory::kItem22, 1);
	getInventory()->setLocationAndProcess(Inventory::kPaper, 1);

	getObjects()->update(Objects::kObjectCompartment1, SavePoints::kNone, 0, Cursor::kCursorHandKnock, 9);
	getObjects()->update(Objects::kObjectOutside, SavePoints::kNone, 0, Cursor::kCursorKeepValue, 255);

	for (uint i = 1; i < 9; i++) {
		getObjects()->updateField4((Objects::ObjectIndex)i, 2);
	}

	for (uint i = 32; i < 40; i++) {
		getObjects()->updateField4((Objects::ObjectIndex)i, 2);
	}

	getCallData().entries[0].field_0 = 40;

	getObjects()->updateField4(Objects::kObject25, 1);
	getObjects()->updateField4(Objects::kObjectGreenSleepingCar, 1);
	getObjects()->updateField4(Objects::kObject98, 1);
	getObjects()->updateField4(Objects::kObjectRestaurantCar, 1);

	getObjects()->update(Objects::kObject25, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObjectGreenSleepingCar, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObjectRedSleepingCar, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObject28, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObject56, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObject54, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObjectRestaurantCar, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObject59, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObject66, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObject64, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObject65, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObject69, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObject98, SavePoints::kNone, 0, Cursor::kCursorNormal, 1);
	getObjects()->update(Objects::kObjectHandleOutsideLeft, SavePoints::kNone, 1, Cursor::kCursorNormal, 9);
	getObjects()->update(Objects::kObjectHandleOutsideRight, SavePoints::kNone, 1, Cursor::kCursorNormal, 9);
	getObjects()->update(Objects::kObject101, SavePoints::kNone, 1, Cursor::kCursorHandKnock, 9);

	// TODO call another function
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
