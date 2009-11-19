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
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Train::Train(LastExpressEngine *engine) : Entity(engine, SavePoints::kTrain) {
	ADD_CALLBACK_FUNCTION(Train, nullfunc);
	ADD_CALLBACK_FUNCTION(Train, chapter1);
	ADD_CALLBACK_FUNCTION(Train, chapter2);
	ADD_CALLBACK_FUNCTION(Train, chapter3);
	ADD_CALLBACK_FUNCTION(Train, chapter4);
	ADD_CALLBACK_FUNCTION(Train, chapter5);
	ADD_CALLBACK_FUNCTION(Train, harem);
	ADD_CALLBACK_FUNCTION(Train, process);
}

void Train::nullfunc(SavePoints::SavePoint *savepoint) {
	error("Train: callback function not implemented!");
}

IMPLEMENT_FUNCTION(Train, chapter1, 2) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter2, 3) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter3, 4) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter4, 5) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter5, 6) {
	if (savepoint->action != SavePoints::kActionDefault)
		return;

	setup_process();
}

IMPLEMENT_FUNCTION(Train, harem, 7) {
	error("Train: harem callback function not implemented!");
}

IMPLEMENT_FUNCTION(Train, process, 8) {
	
	switch (savepoint->action) {
	case SavePoints::kActionDefault:
		getCallData().entries[8].field_0 = 1;
		if (getProgress().chapter < State::kChapter5) {
			getObjects()->update(Objects::kObjectCompartment5, SavePoints::kTrain, 3, 10, 9);
			getObjects()->update(Objects::kObjectCompartment6, SavePoints::kTrain, 3, 10, 9);
			getObjects()->update(Objects::kObjectCompartment7, SavePoints::kTrain, 3, 10, 9);
			getObjects()->update(Objects::kObjectCompartment8, SavePoints::kTrain, 3, 10, 9);
		}
		_data.field_491 = 30000;
		break;

	default:
		error("Train: process callback function not implemented for action %d", savepoint->action);
	}
}

} // End of namespace LastExpress
