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

Train::Train(LastExpressEngine *engine) : Entity(engine, kEntityTrain) {
	ADD_CALLBACK_FUNCTION(Train, savegame);
	ADD_CALLBACK_FUNCTION(Train, chapter1);
	ADD_CALLBACK_FUNCTION(Train, chapter2);
	ADD_CALLBACK_FUNCTION(Train, chapter3);
	ADD_CALLBACK_FUNCTION(Train, chapter4);
	ADD_CALLBACK_FUNCTION(Train, chapter5);
	ADD_CALLBACK_FUNCTION(Train, harem);
	ADD_CALLBACK_FUNCTION(Train, process);
}

IMPLEMENT_FUNCTION_INT2(Train, savegame, 1) {
	switch (savepoint->action) {
	default:
		break;	

	case kActionNone:
		CALL_PREVIOUS_SAVEPOINT(kEntityTrain)
		break;

	case kActionDefault:
		save(kEntityTrain, _data->getCurrentParameters()->param1, (Action::EventIndex)_data->getCurrentParameters()->param2);

		CALL_PREVIOUS_SAVEPOINT(kEntityTrain)
		break;
	}
}

IMPLEMENT_FUNCTION(Train, chapter1, 2) {
	if (savepoint->action != kActionDefault)
		return;

	setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter2, 3) {
	if (savepoint->action != kActionDefault)
		return;

	setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter3, 4) {
	if (savepoint->action != kActionDefault)
		return;

	setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter4, 5) {
	if (savepoint->action != kActionDefault)
		return;

	setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter5, 6) {
	if (savepoint->action != kActionDefault)
		return;

	setup_process();
}

IMPLEMENT_FUNCTION_INT2(Train, harem, 7) {
	if (savepoint->action != kActionDefault)
		return;

	switch (_data->getCurrentParameters()->param1) {
	case 5:
		_data->getCurrentParameters()->param3 = EntityData::kField491_4840;
		break;

	case 6:
		_data->getCurrentParameters()->param3 = EntityData::kField491_4070;
		break;

	case 7:
		_data->getCurrentParameters()->param3 = EntityData::kField491_3050;
		break;

	case 8:
		_data->getCurrentParameters()->param3 = EntityData::kField491_2740;
		break;
	}

	_data->getCurrentParameters()->param4 = getEntities()->checkFields1(kEntityAlouan, EntityData::kField495_3, (EntityData::Field491Value)_data->getCurrentParameters()->param3);
	_data->getCurrentParameters()->param5 = (_data->getParameters(8, 0)->param7 - _data->getCurrentParameters()->param3) <= 0;
	_data->getCurrentParameters()->param6 = getEntities()->checkFields1(kEntityYasmin, EntityData::kField495_3, (EntityData::Field491Value)_data->getCurrentParameters()->param3);
	_data->getCurrentParameters()->param7 = getEntities()->checkFields1(kEntityHadija, EntityData::kField495_3, (EntityData::Field491Value)_data->getCurrentParameters()->param3);

	getObjects()->update((Objects::ObjectIndex)_data->getCurrentParameters()->param1, kEntityTrain, kLocation3, Cursor::kCursorNormal, Cursor::kCursorNormal);
	getSound()->playSound(kEntityTables5, (_data->getCurrentParameters()->param2 == 8) ? "LIB012" : "LIB013", 16);


	error("Train::harem: implementation is incomplete!");

	// TODO finish implementation

	if (!_data->getCurrentParameters()->param4 || !_data->getCurrentParameters()->param5)
		return;

	if (!_data->getCurrentParameters()->param6 || !_data->getCurrentParameters()->param7)
		return;
}

IMPLEMENT_FUNCTION(Train, process, 8) {

	EntityData::EntityParametersSeq1 *parameters1 = (EntityData::EntityParametersSeq1*)_data->getCurrentParameters(1);

	switch (savepoint->action) {
	default:
		break;	

	case kActionNone:
		// Play smoke animation
		if ((getEntities()->checkFields7(EntityData::kField495_3) || getEntities()->checkFields7(EntityData::kField495_4)) 
		  && _data->getCurrentParameters()->param4
		  && !_data->getCurrentParameters()->param5) {

		  _data->getCurrentParameters()->param4 -= 1;

		  if (!_data->getCurrentParameters()->param4 && getProgress().jacket == State::kGreenJacket) {

			  getAction()->playAnimation(isDay() ? Action::kCathSmokeDay : Action::kCathSmokeNight);
			  _data->getCurrentParameters()->param5 = 1;
			  getLogic()->processScene();

		  }			
		}

		if (_data->getCurrentParameters()->param6) {
		
			if (_data->getCurrentParameters(1)->param7) {
				_data->getCurrentParameters(1)->param7 = getState()->time + 900;

				if (_data->getCurrentParameters(1)->param7 >= (int)getState()->time)
					goto label_skip;

				_data->getCurrentParameters(1)->param7 = EntityData::kParamTime;
			}
		
			getLogic()->loadSceneFromData(5, 58, 255);			
		}

		_data->getCurrentParameters(1)->param7 = 0;

label_skip:
		// FIXME make sense of all this crap
		if (_data->getCurrentParameters()->param7) {
			if (!_data->getCurrentParameters(1)->param8) {
				_data->getCurrentParameters(1)->param8 = getState()->time + 4500;

				if (_data->getCurrentParameters(1)->param8) {
					_data->getCurrentParameters()->param7 = 0;
					_data->getCurrentParameters(1)->param8 = 0;
				}
			}

			if (_data->getCurrentParameters(1)->param8 && _data->getCurrentParameters(1)->param8 < (int)getState()->time) {
				//_data->getCurrentParameters(1)->param8 = EntityData::kParameterTime;
				_data->getCurrentParameters()->param7 = 0;
				_data->getCurrentParameters(1)->param8 = 0;
				// Why does it sets it back to 0?
			}
		}
		
		if (_data->getParameters(8, 0)->param8) {
			Objects::ObjectIndex param8 = (Objects::ObjectIndex)_data->getParameters(8, 0)->param8;

			// TODO check if sound is cached
			getObjects()->update(param8, getObjects()->get(param8).entity, kLocation3, Cursor::kCursorHandKnock, Cursor::kCursorHand);
			_data->getParameters(8, 0)->param8 = 0;
		}
		
		// Play clock sound
		if (_data->getCurrentParameters()->param6) {
			getSound()->playSound(kEntityNone, "ZFX1001");
		}

		break;

	case kAction8:
	case kAction9:
		if (savepoint->param.intValue == 5 || savepoint->param.intValue == 6 || savepoint->param.intValue == 7 || savepoint->param.intValue == 8) {
			_data->setNextCallback(savepoint->action == 8 ? 3 : 4);
			call(new ENTITY_SETUP_DEFAULT(Train, setup_harem), savepoint->param.intValue, savepoint->action);
		}
		break;

	case kActionDefault:
		_data->getCurrentParameters(8)->param1 = 1;		
		if (getProgress().chapter < State::kChapter5) {
			getObjects()->update(Objects::kObjectCompartment5, kEntityTrain, kLocation3, Cursor::kCursorHandKnock, Cursor::kCursorHand);
			getObjects()->update(Objects::kObjectCompartment6, kEntityTrain, kLocation3, Cursor::kCursorHandKnock, Cursor::kCursorHand);
			getObjects()->update(Objects::kObjectCompartment7, kEntityTrain, kLocation3, Cursor::kCursorHandKnock, Cursor::kCursorHand);
			getObjects()->update(Objects::kObjectCompartment8, kEntityTrain, kLocation3, Cursor::kCursorHandKnock, Cursor::kCursorHand);
		}
		_data->getData()->field_491 = EntityData::kField491_30000;
		break;

	case kAction17:
		_data->getData()->field_495 = getEntityData(kEntityNone)->field_495;

		// Play clock sound
		if (getEntities()->checkFields4(EntityData::kField495_5, 81)) {
			_data->getCurrentParameters()->param6 = 1;
			getSound()->playSound(kEntityNone, "ZFX1001");
		} else {
			_data->getCurrentParameters()->param6 = 0;
		}

		// Draw moving background behind windows
		if (_data->getCurrentParameters()->param3) {
			if (getEntityData(kEntityNone)->field_495 != _data->getCurrentParameters()->param1 || isDay() != (_data->getCurrentParameters()->param2 > 0)) {
				switch (getEntityData(kEntityNone)->field_495) {
				default:
					getEntities()->drawSequences(kEntityTrain);
					break;

				case EntityData::kField493_1:
				case EntityData::kField495_6:
					if (getProgress().is_nighttime)
						getEntities()->drawSequence(kEntityTrain, "B1WNM");
					else
						getEntities()->drawSequence(kEntityTrain, isDay() ? "B1WNM" : "B1WND");
					break;

				case EntityData::kField495_3:
				case EntityData::kField495_4:
					if (getProgress().is_nighttime)
						getEntities()->drawSequence(kEntityTrain, "S1WNM");
					else
						getEntities()->drawSequence(kEntityTrain, isDay() ? "S1WNM" : "S1WND");
					break;

				case EntityData::kField495_5:
					getEntities()->drawSequence(kEntityTrain, isDay() ? "RCWNN" : "RCWND");
					break;
				}

				// Set parameters so we do not get called twice
				_data->getCurrentParameters()->param1 = getEntityData(kEntityNone)->field_495;
				_data->getCurrentParameters()->param2 = isDay();
			}
		}

		if (!_data->getCurrentParameters()->param5) {
			_data->getCurrentParameters()->param4 = 2700;	// this is the sound file name
			_data->getCurrentParameters()->param5 = 0;
		}

		if (getProgress().jacket == State::kOriginalJacket) {
			if (getEntities()->checkFields4(EntityData::kField495_4, 18)) {
				_data->setNextCallback(1);
				call(new ENTITY_SETUP_DEFAULT(Train, setup_savegame), 2, Action::kMertensBloodJacket);
				break;
			}

			if (getEntities()->checkFields4(EntityData::kField495_3, 22)) {
				_data->setNextCallback(2);
				call(new ENTITY_SETUP_DEFAULT(Train, setup_savegame), 2, Action::kMertensBloodJacket);
				break;
			}
		}	

		resetParam8();
		break;


	case kAction18: {
		int action = _data->getNextCallback();
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
			getObjects()->update(Objects::kObjectCeiling, kEntityNone, kLocation2, Cursor::kCursorKeepValue, Cursor::kCursorKeepValue);
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
		
	case kAction191070912:
		_data->getParameters(8, 0)->param7 = savepoint->param.intValue;
		break;

	case kAction191350523:
		_data->getCurrentParameters()->param3 = 0;
		getEntities()->drawSequences(kEntityTrain);
		break;

	case kAction202613084:
		_data->setNextCallback(8);
		call(new ENTITY_SETUP_DEFAULT(Train, setup_savegame), 2, Action::kCloseMatchbox);
		break;

	case kAction203339360:
		if (!_data->getCurrentParameters()->param7) {
			_data->setNextCallback(5);
			call(new ENTITY_SETUP_DEFAULT(Train, setup_savegame), 2, Action::kLocomotiveConductorsDiscovered);
		} else {
			_data->getCurrentParameters()->param7 = 1;
			getAction()->playAnimation(Action::kLocomotiveConductorsLook);
			getLogic()->loadSceneFromData(7, 2, 255);
		}
		break;

	case kAction203419131:
		if (!_data->getCurrentParameters()->param3) {
			_data->getCurrentParameters()->param1 = 0;
			_data->getCurrentParameters()->param3 = 1;
			getSavePoints()->push(kEntityTrain, kEntityTrain, kAction17);
		}
		break;

	case kAction203863200:
		if (savepoint->param.charValue) {
			_data->getCurrentParameters()->param8 = 1;
			strcpy((char *)&parameters1->param4, savepoint->param.charValue);	// this is the sound file name
		}
		break;

	case kAction222746496:
		switch(savepoint->param.intValue) {
		default:
			break;

		case Objects::kObjectCompartment1:
		case Objects::kObjectCompartment2:
		case Objects::kObjectCompartmentA:
		case Objects::kObjectCompartmentB:
			parameters1->param1 = (savepoint->param.intValue == Objects::kObjectCompartment1 || savepoint->param.intValue == Objects::kObjectCompartment2) ? 3 : 4;
			parameters1->param2 = (savepoint->param.intValue == Objects::kObjectCompartment1 || savepoint->param.intValue == Objects::kObjectCompartmentA) ? EntityData::kField491_8200 : EntityData::kField491_7500;
			parameters1->param3 = 7850;
			break;

		case Objects::kObjectCompartment3:
		case Objects::kObjectCompartment4:
		case Objects::kObjectCompartmentC:
		case Objects::kObjectCompartmentD:
			parameters1->param1 = (savepoint->param.intValue == Objects::kObjectCompartment1 || savepoint->param.intValue == Objects::kObjectCompartment2) ? 3 : 4;
			parameters1->param2 = (savepoint->param.intValue == Objects::kObjectCompartment3 || savepoint->param.intValue == Objects::kObjectCompartmentC) ? EntityData::kField491_6470 : EntityData::kField491_5790;
			parameters1->param3 = 6130;
			break;

		case Objects::kObjectCompartment5:
		case Objects::kObjectCompartment6:
		case Objects::kObjectCompartmentE:
		case Objects::kObjectCompartmentF:
			parameters1->param1 = (savepoint->param.intValue == Objects::kObjectCompartment1 || savepoint->param.intValue == Objects::kObjectCompartment2) ? 3 : 4;
			parameters1->param2 = (savepoint->param.intValue == Objects::kObjectCompartment5 || savepoint->param.intValue == Objects::kObjectCompartmentE) ? EntityData::kField491_4840 : EntityData::kField491_4070;
			parameters1->param3 = 4455;
			break;

		case Objects::kObjectCompartment7:
		case Objects::kObjectCompartment8:
		case Objects::kObjectCompartmentG:
		case Objects::kObjectCompartmentH:
			parameters1->param1 = (savepoint->param.intValue == Objects::kObjectCompartment1 || savepoint->param.intValue == Objects::kObjectCompartment2) ? 3 : 4;
			parameters1->param2 = (savepoint->param.intValue == Objects::kObjectCompartment7 || savepoint->param.intValue == Objects::kObjectCompartmentG) ? EntityData::kField491_3050 : EntityData::kField491_2740;
			parameters1->param3 = 0;
			break;
		}
		break;

	case kActionBreakCeiling:
		_data->setNextCallback(6);		
		call(new ENTITY_SETUP_DEFAULT(Train, setup_savegame), 2, Action::kCathBreakCeiling);
		break;

	case kActionJumpDownCeiling:
		_data->setNextCallback(7);
		call(new ENTITY_SETUP_DEFAULT(Train, setup_savegame), 2, Action::kCathJumpDownCeiling);
		break;
	}
}

void Train::resetParam8() {
	EntityData::EntityParametersSeq1 *parameters1 = (EntityData::EntityParametersSeq1*)_data->getCurrentParameters(1);
	if (_data->getCurrentParameters()->param8
		&& getEntities()->checkFields1(kEntityNone, (EntityData::Field495Value)parameters1->param1, (EntityData::Field491Value)parameters1->param2)
		&& getEntities()->checkFields1(kEntityNone, (EntityData::Field495Value)parameters1->param1, (EntityData::Field491Value)parameters1->param3)) {
			// loads a file in the sound cache (param4)
			_data->getCurrentParameters()->param8 = 0;
	}
}

} // End of namespace LastExpress
