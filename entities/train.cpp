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

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"
#include "lastexpress/game/sound.h"

#include "lastexpress/lastexpress.h"
#include "lastexpress/helpers.h"

namespace LastExpress {

Train::Train(LastExpressEngine *engine) : Entity(engine, SavePoints::kTrain) {
	ADD_CALLBACK_FUNCTION(Train, execute);
	ADD_CALLBACK_FUNCTION(Train, chapter1);
	ADD_CALLBACK_FUNCTION(Train, chapter2);
	ADD_CALLBACK_FUNCTION(Train, chapter3);
	ADD_CALLBACK_FUNCTION(Train, chapter4);
	ADD_CALLBACK_FUNCTION(Train, chapter5);
	ADD_CALLBACK_FUNCTION(Train, harem);
	ADD_CALLBACK_FUNCTION(Train, process);
}

IMPLEMENT_FUNCTION_INT2(Train, execute, 1) {

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

IMPLEMENT_FUNCTION_INT2(Train, harem, 7) {
	error("Train: harem callback function not implemented!");
}

IMPLEMENT_FUNCTION(Train, process, 8) {

	EntityData::EntityParametersSeq1 *parameters1 = (EntityData::EntityParametersSeq1*)_data->getCurrentParameters(1);

	// Notes:
	//  - setting current callback + 8: will be used as an action index for case 18	
	
	switch (savepoint->action) {
	default:
		break;	

	case 0: {
		// Play smoke animation
		if ((getEntities()->checkFields7(3) || getEntities()->checkFields7(4)) 
		  && _data->getCurrentParameters(0)->param4
		  && !_data->getCurrentParameters(0)->param5) {

		  _data->getCurrentParameters(0)->param4 -= 1;

		  if (!_data->getCurrentParameters(0)->param4 && getProgress().jacket == State::kGreenJacket) {
			  getAction()->playAnimation(isDay() ? Action::kCathSmokeDay : Action::kCathSmokeNight);
			  _data->getCurrentParameters(0)->param5 = 1;
			  getLogic()->processScene();
		  }			
		}

		if (_data->getCurrentParameters(0)->param6) {
		
			if (_data->getCurrentParameters(1)->param7) {
				_data->getCurrentParameters(1)->param7 = getState()->time + 900;

				if (_data->getCurrentParameters(1)->param7 >= (int)getState()->time)
					goto label_skip;

				//_data->getCurrentParameters(1)->param7 = 0x7FFFFFFF;	// what does it do?		
			}
		
			getLogic()->loadSceneFromData(5, 58, 255);			
		}

		_data->getCurrentParameters(1)->param7 = 0;

label_skip:
		if (_data->getCurrentParameters(0)->param7) {
			if (!_data->getCurrentParameters(1)->param8) {
				_data->getCurrentParameters(1)->param8 = getState()->time + 4500;
				// FIXME not sure what it is checking here, resetting param8 & param7 in some case (overflow?)
			}

			if (_data->getCurrentParameters(1)->param8 < (int)getState()->time) {
				// FIXME it seems to be setting param8 to 0x7FFFFFFF and then to 0 ?
				_data->getCurrentParameters(0)->param7 = 0;
				_data->getCurrentParameters(1)->param8 = 0;
			}
		}

		Objects::ObjectIndex param8 = (Objects::ObjectIndex)_data->getParameters(8, 0)->param8;
		if (param8) {
			// TODO check if sound is cached (crap, we don't support that, so fail as a check...)
			getObjects()->update(param8, getObjects()->get(param8).entity, 3, Cursor::kCursorHandKnock, 9);
			_data->getParameters(8, 0)->param8 = 0;
		}
		
		// Play clock sound
		if (_data->getCurrentParameters(0)->param6) {
			getSound()->playSound(SavePoints::kNone, "ZFX1001", -1, 0);
		}

		break;
	}

	case 8:
	case 9:
		if (savepoint->field_C == 5 || savepoint->field_C == 6 || savepoint->field_C == 7 || savepoint->field_C == 8) {
			_data->setCallback(_data->getCurrentCallback() + 8, savepoint->action == 8 ? 3 : 4);
			call(new ENTITY_SETUP_DEFAULT(Train, setup_harem), savepoint->field_C, savepoint->action);
		}
		break;

	case SavePoints::kActionDefault:
		_data->getCurrentParameters(8)->param1 = 1;		
		if (getProgress().chapter < State::kChapter5) {
			getObjects()->update(Objects::kObjectCompartment5, SavePoints::kTrain, 3, Cursor::kCursorHandKnock, 9);
			getObjects()->update(Objects::kObjectCompartment6, SavePoints::kTrain, 3, Cursor::kCursorHandKnock, 9);
			getObjects()->update(Objects::kObjectCompartment7, SavePoints::kTrain, 3, Cursor::kCursorHandKnock, 9);
			getObjects()->update(Objects::kObjectCompartment8, SavePoints::kTrain, 3, Cursor::kCursorHandKnock, 9);
		}
		_data->getData()->field_491 = 30000;
		break;

	case 17:
		_data->getData()->field_495 = getEntityData(SavePoints::kNone)->field_495;

		// Play clock sound
		if (getEntities()->checkFields4(5, 81)) {
			_data->getCurrentParameters(0)->param6 = 1;
			getSound()->playSound(SavePoints::kNone, "ZFX1001", -1, 0);
		} else {
			_data->getCurrentParameters(0)->param6 = 0;
		}

		// Draw moving background behind windows
		if (_data->getCurrentParameters(0)->param3) {
			if (getEntityData(SavePoints::kNone)->field_495 != _data->getCurrentParameters(0)->param1 || isDay() != (_data->getCurrentParameters(0)->param2 > 0)) {
				switch (getEntityData(SavePoints::kNone)->field_495) {
				default:
					getEntities()->drawSequences(SavePoints::kTrain);
					break;

				case 1:
				case 6:
					if (getProgress().is_nighttime)
						getEntities()->drawSequence(SavePoints::kTrain, "B1WNM");
					else
						getEntities()->drawSequence(SavePoints::kTrain, isDay() ? "B1WNM" : "B1WND");
					break;

				case 3:
				case 4:
					if (getProgress().is_nighttime)
						getEntities()->drawSequence(SavePoints::kTrain, "S1WNM");
					else
						getEntities()->drawSequence(SavePoints::kTrain, isDay() ? "S1WNM" : "S1WND");
					break;

				case 5:
					getEntities()->drawSequence(SavePoints::kTrain, isDay() ? "RCWNN" : "RCWND");
					break;
				}

				// Set parameters so we do not get called twice
				_data->getCurrentParameters(0)->param1 = getEntityData(SavePoints::kNone)->field_495;
				_data->getCurrentParameters(0)->param2 = isDay();
			}
		}

		if (!_data->getCurrentParameters(0)->param5) {
			_data->getCurrentParameters(0)->param4 = 2700;	// this is the sound file name
			//_data->getCurrentParameters(0)->param5 = 0;
		}

		if (getProgress().jacket == State::kOriginalJacket) {
			if (getEntities()->checkFields4(4, 18)) {
				_data->setCallback(_data->getCurrentCallback() + 8, 1);
				call(new ENTITY_SETUP_DEFAULT(Train, setup_execute), 2, 123);
				break;
			}

			if (getEntities()->checkFields4(3, 22)) {
				_data->setCallback(_data->getCurrentCallback() + 8, 2);
				call(new ENTITY_SETUP_DEFAULT(Train, setup_execute), 2, 123);
				break;
			}
		}	

		resetParam8();
		break;


	case 18: {
		int action = _data->getCallback(_data->getCurrentCallback() + 8);
		switch(action) {
		default:
			break;

		case 1:
		case 2:
			getAction()->playAnimation(action == 1 ? Action::kCoudertBloodJacket : Action::kMertensBloodJacket);
			getLogic()->gameOver(0, 1, 55, true);
			resetParam8();
			break;

		case 5:
			getAction()->playAnimation(Action::kLocomotiveConductorsDiscovered);
			getLogic()->gameOver(0, 1, 63, true);
			break;

		case 6:
			getAction()->playAnimation(Action::kCathBreakCeiling);
			getObjects()->update(Objects::kObjectCeiling, SavePoints::kNone, 2, Cursor::kCursorKeepValue, 255);
			getLogic()->processScene();
			break;

		case 7:
			getAction()->playAnimation(Action::kCathJumpDownCeiling);
			getLogic()->loadSceneFromData(2, 89, 255);
			break;

		case 8:
			getAction()->playAnimation(Action::kCloseMatchbox);
			getLogic()->loadSceneFromData(5, 51, 255);
			break;
		}
		break;
	}
		
	case 191070912:
		_data->getParameters(8, 0)->param7 = savepoint->field_C;
		break;

	case 191350523:
		_data->getCurrentParameters(0)->param3 = 0;
		getEntities()->drawSequences(SavePoints::kTrain);
		break;

	case 202613084:
		_data->setCallback(_data->getCurrentCallback() + 8, 8);
		call(new ENTITY_SETUP_DEFAULT(Train, setup_execute), 2, 259);
		break;

	case 203339360:
		if (!_data->getCurrentParameters(0)->param7) {
			_data->setCallback(_data->getCurrentCallback() + 8, 5);
			call(new ENTITY_SETUP_DEFAULT(Train, setup_execute), 2, 148);
		} else {
			_data->getCurrentParameters(0)->param7 = 1;
			getAction()->playAnimation(Action::kLocomotiveConductorsLook);
			getLogic()->loadSceneFromData(7, 2, 255);
		}
		break;

	case 203419131:
		if (!_data->getCurrentParameters(0)->param3) {
			_data->getCurrentParameters(0)->param1 = 0;
			_data->getCurrentParameters(0)->param3 = 1;
			getSavePoints()->push(32, SavePoints::kTrain, 17, 0);
		}
		break;

	case 203863200:
		if (savepoint->field_C) {
			_data->getCurrentParameters(0)->param8 = 1;
			// We use strcpy here because we stored a char value in field_C (see in action.cpp for action 42)
			// we also store non-null int values inside field_C in several places, so that sucks a bit...
			strcpy((char *)&parameters1->param4, (char *)savepoint->field_C);	// this is the sound file name
		}
		break;

	case 222746496:
		switch(savepoint->field_C) {
		default:
			break;

		case 1:
		case 2:
		case 32:
		case 33:
			parameters1->param1 = (savepoint->field_C == 1 || savepoint->field_C == 2) ? 3 : 4;
			parameters1->param2 = (savepoint->field_C == 1 || savepoint->field_C == 32) ? 8200 : 7500;
			parameters1->param3 = 7850;
			break;

		case 3:
		case 4:
		case 34:
		case 35:
			parameters1->param1 = (savepoint->field_C == 1 || savepoint->field_C == 2) ? 3 : 4;
			parameters1->param2 = (savepoint->field_C == 3 || savepoint->field_C == 34) ? 6470 : 5790;
			parameters1->param3 = 6130;
			break;

		case 5:
		case 6:
		case 36:
		case 37:
			parameters1->param1 = (savepoint->field_C == 1 || savepoint->field_C == 2) ? 3 : 4;
			parameters1->param2 = (savepoint->field_C == 5 || savepoint->field_C == 36) ? 4840 : 4070;
			parameters1->param3 = 4455;
			break;

		case 7:
		case 8:
		case 38:
		case 39:
			parameters1->param1 = (savepoint->field_C == 1 || savepoint->field_C == 2) ? 3 : 4;
			parameters1->param2 = (savepoint->field_C == 7 || savepoint->field_C == 38) ? 3050 : 2740;
			parameters1->param3 = 0;
			break;
		}
		break;

	case 225056224:
		_data->setCallback(_data->getCurrentCallback() + 8, 6);		
		call(new ENTITY_SETUP_DEFAULT(Train, setup_execute), 2, 252);
		break;

	case 338494260:
		_data->setCallback(_data->getCurrentCallback() + 8, 7);
		call(new ENTITY_SETUP_DEFAULT(Train, setup_execute), 2, 253);
		break;
	}
}

void Train::resetParam8() {
	EntityData::EntityParametersSeq1 *parameters1 = (EntityData::EntityParametersSeq1*)_data->getCurrentParameters(1);
	if (_data->getCurrentParameters(0)->param8
		&& getEntities()->checkFields1(SavePoints::kNone, parameters1->param1, parameters1->param2)
		&& getEntities()->checkFields1(SavePoints::kNone, parameters1->param1, parameters1->param3)) {
			// loads a file in the sound cache (param4)
			_data->getCurrentParameters(0)->param8 = 0;
	}
}

} // End of namespace LastExpress
