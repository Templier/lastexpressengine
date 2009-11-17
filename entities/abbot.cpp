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

#include "lastexpress/game/object.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Abbot::Abbot(LastExpressEngine *engine) : Entity(engine, SavePoints::kAbbot) {
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, chapter1);
	CALLBACK_FUNCTION(Abbot, chapter2);
	CALLBACK_FUNCTION(Abbot, chapter3);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, chapter4);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, pickBomb);
	CALLBACK_FUNCTION(Abbot, chapter5);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
	CALLBACK_FUNCTION(Abbot, nullfunc);
}

void Abbot::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Abbot: callback function not implemented!");
}

void Abbot::chapter1(SavePoints::SavePoint *savepoint) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	getSavePoints()->addData(SavePoints::kAbbot, 203073664, 0);
}

void Abbot::chapter2(SavePoints::SavePoint *savepoint) {
}

void Abbot::chapter3(SavePoints::SavePoint *savepoint) {
}

void Abbot::chapter4(SavePoints::SavePoint *savepoint) {
}

void Abbot::pickBomb(SavePoints::SavePoint *savepoint) {
	error("Abbot::pickBomb: callback function not implemented!");
}

void Abbot::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
