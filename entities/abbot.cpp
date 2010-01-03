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

#include "lastexpress/entities/abbot.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Abbot::Abbot(LastExpressEngine *engine) : Entity(engine, kEntityAbbot) {
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, chapter1);
	ADD_CALLBACK_FUNCTION(Abbot, chapter2);
	ADD_CALLBACK_FUNCTION(Abbot, chapter3);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, chapter4);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, pickBomb);
	ADD_CALLBACK_FUNCTION(Abbot, chapter5);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
	ADD_CALLBACK_FUNCTION(Abbot, nullfunc);
}

void Abbot::nullfunc(SavePoint *savepoint) {
	error("Abbot: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, chapter1, 15) {
	if (savepoint->action != kActionDefault)
		return;

	getSavePoints()->addData(kEntityAbbot, kAction203073664, 0);
}

IMPLEMENT_FUNCTION(Abbot, chapter2, 16) {
	if (savepoint->action != kActionDefault)
		return;

	getEntities()->drawSequences(kEntityAbbot);
}

IMPLEMENT_FUNCTION(Abbot, chapter3, 17) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityAbbot);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kNoItem;
		_data->getData()->field_4A5 = 0;

		break;

	case kActionNone:
		// call function 18
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, chapter4, 39) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityAbbot);

		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kNoItem;
		
		_data->getParameters(8, 0)->param1 = 0;

		break;

	case kActionNone:
		// call function 41
		break;
	}
}

IMPLEMENT_FUNCTION(Abbot, pickBomb, 49) {
	error("Abbot::pickBomb: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, chapter5, 50) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityAbbot);

		_data->getData()->field_491 = EntityData::kField491_3969;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kNoItem;
		_data->getData()->field_4A5 = 0;

		break;

	case kActionNone:
		// call function 51
		break;
	}
}

} // End of namespace LastExpress
