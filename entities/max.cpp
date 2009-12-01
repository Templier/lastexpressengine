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

#include "lastexpress/entities/max.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Max::Max(LastExpressEngine *engine) : Entity(engine, SavePoints::kEntityMax) {
	ADD_CALLBACK_FUNCTION(Max, function1);
	ADD_CALLBACK_FUNCTION(Max, function2);
	ADD_CALLBACK_FUNCTION(Max, function3);
	ADD_CALLBACK_FUNCTION(Max, function4);
	ADD_CALLBACK_FUNCTION(Max, savegame);
	ADD_CALLBACK_FUNCTION(Max, function6);
	ADD_CALLBACK_FUNCTION(Max, function7);
	ADD_CALLBACK_FUNCTION(Max, function8);
	ADD_CALLBACK_FUNCTION(Max, function9);
	ADD_CALLBACK_FUNCTION(Max, chapter1);
	ADD_CALLBACK_FUNCTION(Max, chapter2);
	ADD_CALLBACK_FUNCTION(Max, chapter3);
	ADD_CALLBACK_FUNCTION(Max, function13);
	ADD_CALLBACK_FUNCTION(Max, function14);
	ADD_CALLBACK_FUNCTION(Max, function15);
	ADD_CALLBACK_FUNCTION(Max, chapter4);
	ADD_CALLBACK_FUNCTION(Max, function17);
	ADD_CALLBACK_FUNCTION(Max, chapter5);
}

IMPLEMENT_FUNCTION(Max, function1, 1) {
	FUNCTION_1_IMPLEMENTATION(SavePoints::kEntityMax)
}

IMPLEMENT_FUNCTION_SEQ(Max, function2, 2) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kAction2: 
		CALL_PREVIOUS_SAVEPOINT(SavePoints::kEntityMax)
		break;

	case SavePoints::kActionDefault: 
		getSound()->playSound(SavePoints::kEntityMax, ((EntityData::EntityParametersSeq*)_data->getCurrentParameters(0))->seq1, -1 , 0);		
		break;
	}
}

// There doesn't seem to be a setup part for function 3 (no idea why), so we skip that part too
void Max::function3(SavePoints::SavePoint *savepoint) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kAction3: 
		CALL_PREVIOUS_SAVEPOINT(SavePoints::kEntityMax)
		break;

	case SavePoints::kActionDefault: 
		getEntities()->storeSequenceName(SavePoints::kEntityMax, ((EntityData::EntityParametersSeq*)_data->getCurrentParameters(0))->seq1);
		break;
	}
}

IMPLEMENT_FUNCTION_SEQ_INT(Max, function4, 4) {
	EntityData::EntityParametersSeq *params = (EntityData::EntityParametersSeq*)_data->getCurrentParameters(0);

	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kAction3: 
		getEntities()->updateFields1(SavePoints::kEntityMax, (SavePoints::EntityIndex)params->param2);

		CALL_PREVIOUS_SAVEPOINT(SavePoints::kEntityMax)
		break;

	case SavePoints::kActionDefault: 
		getEntities()->storeSequenceName(SavePoints::kEntityMax, params->seq1);
		getEntities()->updateFields0(SavePoints::kEntityMax, (SavePoints::EntityIndex)params->param2);
		break;
	}
}

IMPLEMENT_FUNCTION_INT2(Max, savegame, 5) {
	CALL_SAVEGAME(SavePoints::kEntityMax)
}

IMPLEMENT_FUNCTION(Max, function6, 6) {
}

IMPLEMENT_FUNCTION(Max, function7, 7) {
}

IMPLEMENT_FUNCTION(Max, function8, 8) {
}

IMPLEMENT_FUNCTION(Max, function9, 9) {
}

IMPLEMENT_FUNCTION(Max, chapter1, 10) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		if (getState()->time > 1062000) {
			if (!_data->getCurrentParameters(0)->param1) {
				_data->getCurrentParameters(0)->param1 = 1;
				setup_function6();
			}
		}
		break;

	case SavePoints::kActionDefault: 
		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 4;
		_data->getData()->field_4A5 = 0;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter2, 11) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		setup_function6();
		break;

	case SavePoints::kActionDefault: 
		getEntities()->drawSequences(SavePoints::kEntityMax);
		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 4;
		_data->getData()->field_4A5 = 0;
		_data->getData()->inventoryItem = Inventory::kNoItem;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, chapter3, 12) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		setup_function13();
		break;

	case SavePoints::kActionDefault: 
		getEntities()->drawSequences(SavePoints::kEntityMax);
		_data->getData()->field_491 = 4070;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 4;
		_data->getData()->field_4A5 = 0;
		_data->getData()->inventoryItem = Inventory::kNoItem;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function13, 13) {
}

IMPLEMENT_FUNCTION(Max, function14, 14) {
}

IMPLEMENT_FUNCTION(Max, function15, 15) {
}

IMPLEMENT_FUNCTION(Max, chapter4, 16) {
	switch (savepoint->action) {
	default:
		break;

	case SavePoints::kActionNone: 
		setup_function8();
		break;

	case SavePoints::kActionDefault: 
		getEntities()->drawSequences(SavePoints::kEntityMax);
		_data->getData()->field_491 = 8000;
		_data->getData()->field_493 = 1;
		_data->getData()->field_495 = 6;
		break;
	}
}

IMPLEMENT_FUNCTION(Max, function17, 17) {
}

IMPLEMENT_FUNCTION(Max, chapter5, 18) {
	if (savepoint->action == SavePoints::kActionDefault) {
		getEntities()->drawSequences(SavePoints::kEntityMax);
		_data->getData()->field_491 = 0;
		_data->getData()->field_493 = 0;
		_data->getData()->field_495 = 0;
		getObjects()->update(Objects::kObject109, SavePoints::kEntityNone, 0, Cursor::kCursorNormal, 9);
	}
}

} // End of namespace LastExpress
