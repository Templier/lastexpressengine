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

#include "lastexpress/entities/cooks.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

Cooks::Cooks(LastExpressEngine *engine) : Entity(engine, kEntityCooks) {
	ADD_CALLBACK_FUNCTION(Cooks, function1);
	ADD_CALLBACK_FUNCTION(Cooks, function2);
	ADD_CALLBACK_FUNCTION(Cooks, function3);
	ADD_CALLBACK_FUNCTION(Cooks, function4);
	ADD_CALLBACK_FUNCTION(Cooks, chapter1);
	ADD_CALLBACK_FUNCTION(Cooks, function6);
	ADD_CALLBACK_FUNCTION(Cooks, function7);
	ADD_CALLBACK_FUNCTION(Cooks, chapter2);
	ADD_CALLBACK_FUNCTION(Cooks, function9);
	ADD_CALLBACK_FUNCTION(Cooks, chapter3);
	ADD_CALLBACK_FUNCTION(Cooks, function11);
	ADD_CALLBACK_FUNCTION(Cooks, chapter4);
	ADD_CALLBACK_FUNCTION(Cooks, function13);
	ADD_CALLBACK_FUNCTION(Cooks, chapter5);
}

IMPLEMENT_FUNCTION_S(Cooks, function1, 1) {
	error("Cooks: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_S(Cooks, function2, 2) {
	error("Cooks: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION(Cooks, function3, 3) {
	error("Cooks: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION(Cooks, function4, 4) {
	error("Cooks: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION(Cooks, chapter1, 5) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(6)
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;

		getProgress().field_4C = 0;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, function6, 6) {
	error("Cooks: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION(Cooks, function7, 7) {
	error("Cooks: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(Cooks, chapter2, 8) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function9();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityCooks);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		getProgress().field_4C = 1;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, function9, 9) {
	error("Cooks: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION(Cooks, chapter3, 10) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function11();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityCooks);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		getProgress().field_4C = 0;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, function11, 11) {
	error("Cooks: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION(Cooks, chapter4, 12) {
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		setup_function13();
		break;

	case kActionDefault:
		getEntities()->drawSequences(kEntityCooks);

		_data->getData()->field_491 = EntityData::kField491_5900;
		_data->getData()->field_493 = EntityData::kField493_0;
		_data->getData()->field_495 = EntityData::kField495_5;
		_data->getData()->inventoryItem = kItemNone;

		getProgress().field_4C = 1;

		break;
	}
}

IMPLEMENT_FUNCTION(Cooks, function13, 13) {
	error("Cooks: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(Cooks, chapter5, 14) {
	if (savepoint->action == kActionDefault)
		getEntities()->drawSequences(kEntityCooks);
}

} // End of namespace LastExpress
