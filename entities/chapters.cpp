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

#include "lastexpress/game/object.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Chapters::Chapters(LastExpressEngine *engine) : Entity(engine, SavePoints::kChapters) {
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, chapter1);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, chapter1_init);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, chapter2);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, chapter3);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, chapter4);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, chapter5);
	CALLBACK_FUNCTION(Chapters, nullfunc);
	CALLBACK_FUNCTION(Chapters, nullfunc);
}

void Chapters::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Chapters: callback function not implemented!");
}

void Chapters::chapter1(SavePoints::SavePoint *savepoint) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	getSavePoints()->addData(SavePoints::kChapters, 171843264, 0);
	setup_chapter1_init();
}

void Chapters::chapter1_init(SavePoints::SavePoint *savepoint) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	getProgress().chapter = Logic::kChapter1;
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

	getObjects()->update(1, SavePoints::kNone, 0, 10, 9);
	getObjects()->update(9, SavePoints::kNone, 0, 255, 255);

	for (uint i = 1; i < 9; i++) {
		getObjects()->updateField4(i, 2);
	}

	for (uint i = 32; i < 40; i++) {
		getObjects()->updateField4(i, 2);
	}

	getCallData().entries[0].field_0 = 40;

	getObjects()->updateField4(25, 1);
	getObjects()->updateField4(23, 1);
	getObjects()->updateField4(98, 1);
	getObjects()->updateField4(55, 1);

	getObjects()->update(25, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(23, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(24, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(28, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(56, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(54, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(55, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(59, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(66, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(64, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(65, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(69, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(98, SavePoints::kNone, 0, 0, 1);
	getObjects()->update(26, SavePoints::kNone, 1, 0, 9);
	getObjects()->update(27, SavePoints::kNone, 1, 0, 9);
	getObjects()->update(101, SavePoints::kNone, 1, 10, 9);

	// TODO call another function
}

void Chapters::chapter2(SavePoints::SavePoint *savepoint) {

}

void Chapters::chapter3(SavePoints::SavePoint *savepoint) {

}

void Chapters::chapter4(SavePoints::SavePoint *savepoint) {

}

void Chapters::chapter5(SavePoints::SavePoint *savepoint) {

}

} // End of namespace LastExpress
