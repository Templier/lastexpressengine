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
#include "lastexpress/game/savegame.h"
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

IMPLEMENT_FUNCTION_II(Train, savegame, 1)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		CALL_PREVIOUS_SAVEPOINT()
		break;

	case kActionDefault:
		save(kEntityTrain, params->param1, (EventIndex)params->param2);

		CALL_PREVIOUS_SAVEPOINT()
		break;
	}
}

IMPLEMENT_FUNCTION(Train, chapter1, 2)
	if (savepoint.action == kActionDefault)
		setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter2, 3)
	if (savepoint.action == kActionDefault)
		setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter3, 4)
	if (savepoint.action == kActionDefault)
		setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter4, 5)
	if (savepoint.action == kActionDefault)
		setup_process();
}

IMPLEMENT_FUNCTION(Train, chapter5, 6)
	if (savepoint.action == kActionDefault)
		setup_process();
}


void Train::handleCompartementAction() {
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)

	if (params->param8)
		getSavePoints()->push(kEntityTrain, kEntityMahmud, kAction290410610, (uint32)params->param1);

	getAction()->handleOtherCompartment((ObjectIndex)params->param1, 0, ENTITY_PARAM(0, 8) ? 0 : 1);

	ENTITY_PARAM(0, 8) = params->param1;

	CALL_PREVIOUS_SAVEPOINT();
}

IMPLEMENT_FUNCTION_II(Train, harem, 7)
	if (savepoint.action != kActionDefault)
		return;

	switch (params->param1) {
	default:
		error("Train::harem: Invalid value for parameter 1: %d", params->param1);
		break;

	case 5:
		params->param3 = EntityData::kField491_4840;
		break;

	case 6:
		params->param3 = EntityData::kField491_4070;
		break;

	case 7:
		params->param3 = EntityData::kField491_3050;
		break;

	case 8:
		params->param3 = EntityData::kField491_2740;
		break;
	}

	params->param4 = getEntities()->checkFields1(kEntityAlouan, EntityData::kField495_3, (EntityData::Field491Value)params->param3);
	params->param5 = (ENTITY_PARAM(0, 7) - params->param3) <= 0;
	params->param6 = getEntities()->checkFields1(kEntityYasmin, EntityData::kField495_3, (EntityData::Field491Value)params->param3);
	params->param7 = getEntities()->checkFields1(kEntityHadija, EntityData::kField495_3, (EntityData::Field491Value)params->param3);

	getObjects()->update((ObjectIndex)params->param1, kEntityTrain, kLocation3, kCursorNormal, kCursorNormal);

	// Knock / closed door sound
	getSound()->playSound(kEntityTables5, (params->param2 == 8) ? "LIB012" : "LIB013", 16);

	if (params->param4 && params->param5) {

		ENTITY_PARAM(0, 5) += 1;

		switch (ENTITY_PARAM(0, 5)) {
		default:
			params->param8 = 1;
			break;

		case 1:
			getSound()->playSound(kEntityTables5, "Har1014", 16, 15);
			break;

		case 2:
			getSound()->playSound(kEntityTables5, "Har1013", 16, 15);
			getSound()->playSound(kEntityTables5, "Har1016", 16, 150);
			break;

		case 3:
			getSound()->playSound(kEntityTables5, "Har1015A", 16, 15);
			getSound()->playSound(kEntityTables5, "Har1015", 16, 150);
			break;
		}

		// Update progress
		getProgress().field_DC = 1;
		getProgress().field_E0 = 1;

		handleCompartementAction();

		// Done with it!
		return;
	}

	if (params->param6 && params->param7) {

		ENTITY_PARAM(0, 6) += 1;

		switch(ENTITY_PARAM(0, 6)) {
		default:
			params->param8 = 1;
			break;

		case 1:
			getSound()->playSound(kEntityTables5, "Har1014", 16, 15);
			break;

		case 2:
			getSound()->playSound(kEntityTables5, "Har1013", 16, 15);
			break;

		case 3:
			getSound()->playSound(kEntityTables5, "Har1013A", 16, 15);
			break;
		}

		handleCompartementAction();
		return;
	}

	if (!params->param5 && params->param6) {

		ENTITY_PARAM(0, 3) += 1;

		switch(ENTITY_PARAM(0, 3)) {
		default:
			params->param8 = 1;
			break;

		case 1:
			getSound()->playSound(kEntityTables5, "Har1012", 16, 15);
			break;

		case 2:
			getSound()->playSound(kEntityTables5, "Har1012A", 16, 15);
			break;
		}

		handleCompartementAction();
		return;
	}

	if (!params->param5 && !params->param6) {

		if (params->param4) {
			ENTITY_PARAM(0, 1) += 1;

			if (ENTITY_PARAM(0, 1) <= 1)
				getSound()->playSound(kEntityTables5, "Har1014", 16, 15);
			else
				params->param8 = 1;

			getProgress().field_DC = 1;

			handleCompartementAction();
			return;
		}

		if (params->param7) {
			ENTITY_PARAM(0, 4) += 1;

			if (ENTITY_PARAM(0, 4) <= 1) {
				getSound()->playSound(kEntityTables5, "Har1011", 16, 15);
				handleCompartementAction();
				return;
			}
		}

		params->param8 = 1;
		handleCompartementAction();
		return;
	}

	ENTITY_PARAM(0, 2) += 1;

	switch (ENTITY_PARAM(0, 2)) {
	default:
		params->param8 = 1;
		break;

	case 1:
		getSound()->playSound(kEntityTables5, "Har1013", 16, 15);
		break;

	case 2:
		getSound()->playSound(kEntityTables5, "Har1013A", 16, 15);
		break;
	}

	getProgress().field_E0 = 1;

	handleCompartementAction();
}

IMPLEMENT_FUNCTION(Train, process, 8)

	EntityData::EntityParametersIIIS *parameters1 = (EntityData::EntityParametersIIIS*)_data->getCurrentParameters(1);

	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		// Play smoke animation
		if ((getEntities()->checkFields7(EntityData::kField495_3) || getEntities()->checkFields7(EntityData::kField495_4))
		  && params->param4
		  && !params->param5) {

		  params->param4 -= 1;

		  if (!params->param4 && getProgress().jacket == kJacketGreen) {

			  getAction()->playAnimation(isDay() ? kEventCathSmokeDay : kEventCathSmokeNight);
			  params->param5 = 1;
			  getLogic()->processScene();

		  }
		}

		if (params->param6) {

			if (params->param7) {
				parameters1->param7 = (int)getState()->time + 900;

				if (parameters1->param7 >= (int)getState()->time)
					goto label_skip;

				parameters1->param7 = EntityData::kParamTime;
			}

			getLogic()->loadSceneFromData(5, 58, 255);
		}

		parameters1->param7 = 0;

label_skip:
		// FIXME make sense of all this crap
		if (params->param7) {
			if (!parameters1->param8) {
				parameters1->param8 = (int)getState()->time + 4500;

				if (parameters1->param8) {
					params->param7 = 0;
					parameters1->param8 = 0;
				}
			}

			if (parameters1->param8 && parameters1->param8 < (int)getState()->time) {
				//_data->getCurrentParameters(1)->param8 = EntityData::kParameterTime;
				params->param7 = 0;
				parameters1->param8 = 0;
				// Why does it sets it back to 0?
			}
		}

		if (ENTITY_PARAM(0, 8)) {
			ObjectIndex param8 = (ObjectIndex)ENTITY_PARAM(0, 8);

			// TODO check if sound is cached
			getObjects()->update(param8, getObjects()->get(param8).entity, kLocation3, kCursorHandKnock, kCursorHand);
			ENTITY_PARAM(0, 8) = 0;
		}

		// Play clock sound
		if (params->param6) {
			if (!getSound()->isFileInQueue("ZFX1001"))
				getSound()->playSound(kEntityNone, "ZFX1001");
		}

		break;

	case kAction8:
	case kAction9:
		if (savepoint.param.intValue == 5 || savepoint.param.intValue == 6 || savepoint.param.intValue == 7 || savepoint.param.intValue == 8) {
			_data->setNextCallback(savepoint.action == 8 ? 3 : 4);
			call(new ENTITY_SETUP(Train, setup_harem), (int)savepoint.param.intValue, savepoint.action);
		}
		break;

	case kActionDefault:
		CURRENT_PARAMS(8, 1) = 1;
		if (getProgress().chapter < kChapter5) {
			getObjects()->update(kObjectCompartment5, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment6, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment7, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
			getObjects()->update(kObjectCompartment8, kEntityTrain, kLocation3, kCursorHandKnock, kCursorHand);
		}
		_data->getData()->field_491 = EntityData::kField491_30000;
		break;

	case kAction17:
		_data->getData()->field_495 = getEntityData(kEntityNone)->field_495;

		// Play clock sound
		if (getEntities()->checkFields4(EntityData::kField495_5, 81)) {
			params->param6 = 1;
			getSound()->playSound(kEntityNone, "ZFX1001");
		} else {
			params->param6 = 0;
		}

		// Draw moving background behind windows
		// TODO change boolean check
		if (params->param3) {
			if (getEntityData(kEntityNone)->field_495 != params->param1 || isDay() != (params->param2 > 0)) {
				switch (getEntityData(kEntityNone)->field_495) {
				default:
					getEntities()->prepareSequences(kEntityTrain);
					break;

				case EntityData::kField495_1:
				case EntityData::kField495_6:
					if (getProgress().is_nighttime)
						getEntities()->drawSequenceLeft(kEntityTrain, "B1WNM");
					else
						getEntities()->drawSequenceLeft(kEntityTrain, isDay() ? "B1WNM" : "B1WND");
					break;

				case EntityData::kField495_3:
				case EntityData::kField495_4:
					if (getProgress().is_nighttime)
						getEntities()->drawSequenceLeft(kEntityTrain, "S1WNM");
					else
						getEntities()->drawSequenceLeft(kEntityTrain, isDay() ? "S1WNM" : "S1WND");
					break;

				case EntityData::kField495_5:
					getEntities()->drawSequenceLeft(kEntityTrain, isDay() ? "RCWNN" : "RCWND");
					break;
				}

				// Set parameters so we do not get called twice
				params->param1 = getEntityData(kEntityNone)->field_495;
				params->param2 = isDay();
			}
		}

		if (!params->param5) {
			params->param4 = 2700;	// this is the sound file name
			params->param5 = 0;
		}

		if (getProgress().jacket == kJacketOriginal) {
			if (getEntities()->checkFields4(EntityData::kField495_4, 18)) {
				_data->setNextCallback(1);
				call(new ENTITY_SETUP(Train, setup_savegame), 2, kEventMertensBloodJacket);
				break;
			}

			if (getEntities()->checkFields4(EntityData::kField495_3, 22)) {
				_data->setNextCallback(2);
				call(new ENTITY_SETUP(Train, setup_savegame), 2, kEventMertensBloodJacket);
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
			getAction()->playAnimation(action == 1 ? kEventCoudertBloodJacket : kEventMertensBloodJacket);
			getLogic()->gameOver(kTimeType0, 1, kSceneGameOverBloodJacket, true);
			resetParam8();
			break;

		case 5:
			getAction()->playAnimation(kEventLocomotiveConductorsDiscovered);
			getLogic()->gameOver(kTimeType0, 1, kSceneGameOverPolice, true);
			break;

		case 6:
			getAction()->playAnimation(kEventCathBreakCeiling);
			getObjects()->update(kObjectCeiling, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
			getLogic()->processScene();
			break;

		case 7:
			getAction()->playAnimation(kEventCathJumpDownCeiling);
			getLogic()->loadSceneFromData(2, 89, 255);
			break;

		case 8:
			getAction()->playAnimation(kEventCloseMatchbox);
			getLogic()->loadSceneFromData(5, 51, 255);
			break;
		}
		break;
	}

	case kAction191070912:
		ENTITY_PARAM(0, 7) = (int)savepoint.param.intValue;
		break;

	case kAction191350523:
		params->param3 = 0;
		getEntities()->prepareSequences(kEntityTrain);
		break;

	case kAction202613084:
		_data->setNextCallback(8);
		call(new ENTITY_SETUP(Train, setup_savegame), 2, kEventCloseMatchbox);
		break;

	case kAction203339360:
		if (!params->param7) {
			_data->setNextCallback(5);
			call(new ENTITY_SETUP(Train, setup_savegame), 2, kEventLocomotiveConductorsDiscovered);
		} else {
			params->param7 = 1;
			getAction()->playAnimation(kEventLocomotiveConductorsLook);
			getLogic()->loadSceneFromData(7, 2, 255);
		}
		break;

	case kAction203419131:
		if (!params->param3) {
			params->param1 = 0;
			params->param3 = 1;
			getSavePoints()->push(kEntityTrain, kEntityTrain, kAction17);
		}
		break;

	case kAction203863200:
		if (!strcmp(savepoint.param.charValue, "")) {
			params->param8 = 1;
			strcpy((char *)&parameters1->seq, savepoint.param.charValue);	// this is the sound file name
		}
		break;

	case kAction222746496:
		switch(savepoint.param.intValue) {
		default:
			break;

		case kObjectCompartment1:
		case kObjectCompartment2:
		case kObjectCompartmentA:
		case kObjectCompartmentB:
			parameters1->param1 = (savepoint.param.intValue == kObjectCompartment1 || savepoint.param.intValue == kObjectCompartment2) ? 3 : 4;
			parameters1->param2 = (savepoint.param.intValue == kObjectCompartment1 || savepoint.param.intValue == kObjectCompartmentA) ? EntityData::kField491_8200 : EntityData::kField491_7500;
			parameters1->param3 = 7850;
			break;

		case kObjectCompartment3:
		case kObjectCompartment4:
		case kObjectCompartmentC:
		case kObjectCompartmentD:
			parameters1->param1 = (savepoint.param.intValue == kObjectCompartment1 || savepoint.param.intValue == kObjectCompartment2) ? 3 : 4;
			parameters1->param2 = (savepoint.param.intValue == kObjectCompartment3 || savepoint.param.intValue == kObjectCompartmentC) ? EntityData::kField491_6470 : EntityData::kField491_5790;
			parameters1->param3 = 6130;
			break;

		case kObjectCompartment5:
		case kObjectCompartment6:
		case kObjectCompartmentE:
		case kObjectCompartmentF:
			parameters1->param1 = (savepoint.param.intValue == kObjectCompartment1 || savepoint.param.intValue == kObjectCompartment2) ? 3 : 4;
			parameters1->param2 = (savepoint.param.intValue == kObjectCompartment5 || savepoint.param.intValue == kObjectCompartmentE) ? EntityData::kField491_4840 : EntityData::kField491_4070;
			parameters1->param3 = 4455;
			break;

		case kObjectCompartment7:
		case kObjectCompartment8:
		case kObjectCompartmentG:
		case kObjectCompartmentH:
			parameters1->param1 = (savepoint.param.intValue == kObjectCompartment1 || savepoint.param.intValue == kObjectCompartment2) ? 3 : 4;
			parameters1->param2 = (savepoint.param.intValue == kObjectCompartment7 || savepoint.param.intValue == kObjectCompartmentG) ? EntityData::kField491_3050 : EntityData::kField491_2740;
			parameters1->param3 = 0;
			break;
		}
		break;

	case kActionBreakCeiling:
		_data->setNextCallback(6);
		call(new ENTITY_SETUP(Train, setup_savegame), 2, kEventCathBreakCeiling);
		break;

	case kActionJumpDownCeiling:
		_data->setNextCallback(7);
		call(new ENTITY_SETUP(Train, setup_savegame), 2, kEventCathJumpDownCeiling);
		break;
	}
}

void Train::resetParam8() {
	EXPOSE_PARAMS(EntityData::EntityParametersIIII)
	EntityData::EntityParametersIIIS *params2 = (EntityData::EntityParametersIIIS*)_data->getCurrentParameters(1);

	if (params->param8
		&& getEntities()->checkFields1(kEntityNone, (EntityData::Field495Value)params2->param1, (EntityData::Field491Value)params2->param2)
		&& getEntities()->checkFields1(kEntityNone, (EntityData::Field495Value)params2->param1, (EntityData::Field491Value)params2->param3)) {
			// loads a file in the sound cache (param4)
			params->param8 = 0;
	}
}

} // End of namespace LastExpress
