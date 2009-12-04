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
}

IMPLEMENT_FUNCTION(Abbot, chapter3, 17) {
}

IMPLEMENT_FUNCTION(Abbot, chapter4, 39) {
}

IMPLEMENT_FUNCTION(Abbot, pickBomb, 49) {
	error("Abbot::pickBomb: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Abbot, chapter5, 50) {
}

} // End of namespace LastExpress
