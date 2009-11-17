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

#include "lastexpress/entities/train.h"

#include "lastexpress/game/object.h"

#include "lastexpress/helpers.h"

namespace LastExpress {

Train::Train(LastExpressEngine *engine) : Entity(engine, SavePoints::kTrain) {
	CALLBACK_FUNCTION(Train, nullfunc);
	CALLBACK_FUNCTION(Train, chapter1);
	CALLBACK_FUNCTION(Train, chapter2);
	CALLBACK_FUNCTION(Train, chapter3);
	CALLBACK_FUNCTION(Train, chapter4);
	CALLBACK_FUNCTION(Train, chapter5);
	CALLBACK_FUNCTION(Train, harem);
	CALLBACK_FUNCTION(Train, process);
}

void Train::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Train: callback function not implemented!");
}

void Train::chapter1(SavePoints::SavePoint *savepoint) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	setup_process();
}

void Train::chapter2(SavePoints::SavePoint *savepoint) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	setup_process();
}

void Train::chapter3(SavePoints::SavePoint *savepoint) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	setup_process();
}

void Train::chapter4(SavePoints::SavePoint *savepoint) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	setup_process();
}

void Train::chapter5(SavePoints::SavePoint *savepoint) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	setup_process();
}

void Train::harem(SavePoints::SavePoint *savepoint) {
	error("Train: harem callback function not implemented!");
}

void Train::process(SavePoints::SavePoint *savepoint) {
	
	switch (savepoint->action) {
	case SavePoints::kActionDefault:
		getCallData().entries[8].field_0 = 1;
		if (getProgress().chapter < Logic::kChapter5) {
			getObjects()->update(5, SavePoints::kTrain, 3, 10, 9);
			getObjects()->update(6, SavePoints::kTrain, 3, 10, 9);
			getObjects()->update(7, SavePoints::kTrain, 3, 10, 9);
			getObjects()->update(8, SavePoints::kTrain, 3, 10, 9);
		}
		_data.field_491 = 30000;
		break;

	default:
		error("Train: process callback function not implemented for action %d", savepoint->action);
	}
}

} // End of namespace LastExpress
