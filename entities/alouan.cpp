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

#include "lastexpress/entities/alouan.h"

#include "lastexpress/game/object.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Alouan::Alouan(LastExpressEngine *engine) : Entity(engine, SavePoints::kAlouan) {
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, chapter1);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, chapter2);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, chapter3);
	CALLBACK_FUNCTION(Alouan, nullfunc);	
	CALLBACK_FUNCTION(Alouan, chapter4);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, chapter5);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
	CALLBACK_FUNCTION(Alouan, nullfunc);
}

void Alouan::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Alouan: callback function not implemented!");
}

void Alouan::chapter1(SavePoints::SavePoint *savepoint) {
}

void Alouan::chapter2(SavePoints::SavePoint *savepoint) {
}

void Alouan::chapter3(SavePoints::SavePoint *savepoint) {
}

void Alouan::chapter4(SavePoints::SavePoint *savepoint) {
}

void Alouan::chapter5(SavePoints::SavePoint *savepoint) {
}

} // End of namespace LastExpress
