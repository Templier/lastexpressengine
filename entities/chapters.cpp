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

#include "lastexpress/game/items.h"

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

	getItems()->update(1, 0, 0, 10, 9);
	getItems()->update(9, 0, 0, 255, 255);

	for (uint i = 1; i < 9; i++) {
		getItems()->updateField4(i, 2);
	}

	for (uint i = 32; i < 40; i++) {
		getItems()->updateField4(i, 2);
	}

	getCallData().entries[0].field_0 = 40;

	getItems()->updateField4(25, 1);
	getItems()->updateField4(23, 1);
	getItems()->updateField4(98, 1);
	getItems()->updateField4(55, 1);

	getItems()->update(25, 0, 0, 0, 1);
	getItems()->update(23, 0, 0, 0, 1);
	getItems()->update(24, 0, 0, 0, 1);
	getItems()->update(28, 0, 0, 0, 1);
	getItems()->update(56, 0, 0, 0, 1);
	getItems()->update(54, 0, 0, 0, 1);
	getItems()->update(55, 0, 0, 0, 1);
	getItems()->update(59, 0, 0, 0, 1);
	getItems()->update(66, 0, 0, 0, 1);
	getItems()->update(64, 0, 0, 0, 1);
	getItems()->update(65, 0, 0, 0, 1);
	getItems()->update(69, 0, 0, 0, 1);
	getItems()->update(98, 0, 0, 0, 1);
	getItems()->update(26, 0, 1, 0, 9);
	getItems()->update(27, 0, 1, 0, 9);
	getItems()->update(101, 0, 1, 10, 9);

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
