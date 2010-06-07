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

#include "lastexpress/entities/gendarmes.h"

#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Gendarmes::Gendarmes(LastExpressEngine *engine) : Entity(engine, kEntityGendarmes) {
	ADD_CALLBACK_FUNCTION(Gendarmes, function1);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter1);
	ADD_CALLBACK_FUNCTION(Gendarmes, function3);
	ADD_CALLBACK_FUNCTION(Gendarmes, function4);
	ADD_CALLBACK_FUNCTION(Gendarmes, function5);
	ADD_CALLBACK_FUNCTION(Gendarmes, function6);
	ADD_CALLBACK_FUNCTION(Gendarmes, savegame);
	ADD_CALLBACK_FUNCTION(Gendarmes, function8);
	ADD_CALLBACK_FUNCTION(Gendarmes, function9);
	ADD_CALLBACK_FUNCTION(Gendarmes, function10);
	ADD_CALLBACK_FUNCTION(Gendarmes, function11);
	ADD_CALLBACK_FUNCTION(Gendarmes, function12);
	ADD_CALLBACK_FUNCTION(Gendarmes, function13);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter2);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter3);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter4);
	ADD_CALLBACK_FUNCTION(Gendarmes, chapter5);
}

IMPLEMENT_FUNCTION(Gendarmes, function1, 1)
	Entity::function1(savepoint);
}

IMPLEMENT_FUNCTION(Gendarmes, chapter1, 2)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(11)
		break;

	case kActionDefault:
		getData()->car = kCarNone;
		break;
	}
}

IMPLEMENT_FUNCTION_S(Gendarmes, function3, 3)
	error("Gendarmes: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_S(Gendarmes, function4, 4)
	error("Gendarmes: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_S(Gendarmes, function5, 5)
	error("Gendarmes: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_I(Gendarmes, function6, 6)
	error("Gendarmes: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_II(Gendarmes, savegame, 7)
	Entity::savegame(savepoint);
}

IMPLEMENT_FUNCTION_II(Gendarmes, function8, 8)
	error("Gendarmes: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_IISS(Gendarmes, function9, 9)
	error("Gendarmes: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION_III(Gendarmes, function10, 10)
	error("Gendarmes: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION(Gendarmes, function11, 11)
	if (savepoint.action == kActionDefault) {
		getSavePoints()->push(kEntityGendarmes, kEntityMertens, kAction190082817);
		setup_function12();
	}
}

IMPLEMENT_FUNCTION(Gendarmes, function12, 12)
	error("Gendarmes: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION(Gendarmes, function13, 13)
	if (savepoint.action == kActionDefault)
		getData()->car = kCarNone;
}

IMPLEMENT_FUNCTION(Gendarmes, chapter2, 14)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityGendarmes);
}

IMPLEMENT_FUNCTION(Gendarmes, chapter3, 15)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityGendarmes);
}

IMPLEMENT_FUNCTION(Gendarmes, chapter4, 16)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityGendarmes);
}

IMPLEMENT_FUNCTION(Gendarmes, chapter5, 17)
	if (savepoint.action == kActionDefault)
		getEntities()->prepareSequences(kEntityGendarmes);
}

} // End of namespace LastExpress
