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

#include "lastexpress/entities/tables.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Tables::Tables(LastExpressEngine *engine, Entity::EntityIndex id) : Entity(engine, id) {
	_id = id;
	
	ADD_CALLBACK_FUNCTION(Tables, chapter1);
	ADD_CALLBACK_FUNCTION(Tables, chapter2);
	ADD_CALLBACK_FUNCTION(Tables, chapter3);
	ADD_CALLBACK_FUNCTION(Tables, chapter4);
	ADD_CALLBACK_FUNCTION(Tables, chapter5);
	ADD_CALLBACK_FUNCTION(Tables, draw);
}

IMPLEMENT_FUNCTION(Tables, chapter1, 1) {
	if (savepoint->action == kActionDefault)
		setup_draw();
}

IMPLEMENT_FUNCTION(Tables, chapter2, 2) {
	if (savepoint->action == kActionDefault)
		setup_draw();
}

IMPLEMENT_FUNCTION(Tables, chapter3, 3) {
	if (savepoint->action == kActionDefault)
		setup_draw();
}

IMPLEMENT_FUNCTION(Tables, chapter4, 4) {
	if (savepoint->action == kActionDefault)
		setup_draw();
}

IMPLEMENT_FUNCTION(Tables, chapter5, 5) {
	if (savepoint->action == kActionDefault)
		setup_draw();
}

IMPLEMENT_FUNCTION(Tables, draw, 6) {	
	switch (savepoint->action) {
	default:
		break;

	case kActionNone:
		if (_id != kEntityTables2)
			break;

		// TODO sound cache handling
		switch (getProgress().chapter) {
		default:
			break;

		case State::kChapter1:
			if (getState()->time > 1165500)
				if (!_data->getCurrentParameters()->param1)
					_data->getCurrentParameters()->param1 = 1;
			break;

		case State::kChapter3:
			if (getState()->time > 2052000)
				if (!_data->getCurrentParameters()->param2)
					_data->getCurrentParameters()->param2 = 1;
			break;

		case State::kChapter4:
			if (getState()->time > 2488500)
				if (!_data->getCurrentParameters()->param3)
					_data->getCurrentParameters()->param3 = 1;
			break;

		}
		break;

	case kActionDefault:
		_data->getData()->field_491 = EntityData::kField491_3970;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;
		switch(_id) {
		default:
			break;

		case kEntityTables0:
			getEntities()->drawSequence(_id, "001P");
			break;

		case kEntityTables1:
			getEntities()->drawSequence(_id, "005J");
			break;

		case kEntityTables2:
			getEntities()->drawSequence(_id, "009G");
			break;

		case kEntityTables3:
			getEntities()->drawSequence(_id, "010M");
			break;

		case kEntityTables4:
			getEntities()->drawSequence(_id, "014F");
			break;

		case kEntityTables5:
			getEntities()->drawSequence(_id, "024D");
			break;
		}
		
		break;

	case kAction103798704:
		if (savepoint->param.charValue) {
			getEntities()->drawSequence(_id, savepoint->param.charValue);
		} else {
			switch(_id) {
			default:
				break;

			case kEntityTables0:
				getEntities()->drawSequence(_id, "001P");
				break;

			case kEntityTables1:
				getEntities()->drawSequence(_id, "005J");
				break;

			case kEntityTables2:
				getEntities()->drawSequence(_id, "009G");
				break;

			case kEntityTables3:
				getEntities()->drawSequence(_id, "010M");
				break;

			case kEntityTables4:
				getEntities()->drawSequence(_id, "014F");
				break;

			case kEntityTables5:
				getEntities()->drawSequence(_id, "024D");
				break;
			}
		}
		break;

	case kAction136455232:
		getEntities()->drawSequence(_id, "BLANK");
		break;
	}
}


} // End of namespace LastExpress
