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

#include "lastexpress/entities/chapters.h"

#include "lastexpress/entities/abbot.h"
#include "lastexpress/entities/alexei.h"
#include "lastexpress/entities/alouan.h"
#include "lastexpress/entities/anna.h"
#include "lastexpress/entities/august.h"
#include "lastexpress/entities/boutarel.h"
#include "lastexpress/entities/coudert.h"
#include "lastexpress/entities/cooks.h"
#include "lastexpress/entities/francois.h"
#include "lastexpress/entities/gendarmes.h"
#include "lastexpress/entities/hadija.h"
#include "lastexpress/entities/ivo.h"
#include "lastexpress/entities/kahina.h"
#include "lastexpress/entities/kronos.h"
#include "lastexpress/entities/mahmud.h"
#include "lastexpress/entities/max.h"
#include "lastexpress/entities/mertens.h"
#include "lastexpress/entities/milos.h"
#include "lastexpress/entities/mmeboutarel.h"
#include "lastexpress/entities/pascale.h"
#include "lastexpress/entities/rebecca.h"
#include "lastexpress/entities/salko.h"
#include "lastexpress/entities/servers0.h"
#include "lastexpress/entities/servers1.h"
#include "lastexpress/entities/sophie.h"
#include "lastexpress/entities/tatiana.h"
#include "lastexpress/entities/vassili.h"
#include "lastexpress/entities/verges.h"
#include "lastexpress/entities/vesna.h"
#include "lastexpress/entities/yasmin.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/menu.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

Chapters::Chapters(LastExpressEngine *engine) : Entity(engine, kEntityChapters) {
	ADD_CALLBACK_FUNCTION(Chapters, savegame);
	ADD_CALLBACK_FUNCTION(Chapters, enterStation);
	ADD_CALLBACK_FUNCTION(Chapters, exitStation);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1);
	ADD_CALLBACK_FUNCTION(Chapters, resetMainEntities);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1End);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1Init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1Handler);
	ADD_CALLBACK_FUNCTION(Chapters, chapter1Next);
	ADD_CALLBACK_FUNCTION(Chapters, chapter2);
	ADD_CALLBACK_FUNCTION(Chapters, chapter2Init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter2Handler);
	ADD_CALLBACK_FUNCTION(Chapters, chapter3);
	ADD_CALLBACK_FUNCTION(Chapters, chapter3Init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter3Handler);
	ADD_CALLBACK_FUNCTION(Chapters, viennaEvents);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4Init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4Handler);
	ADD_CALLBACK_FUNCTION(Chapters, chapter5);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4Init);
	ADD_CALLBACK_FUNCTION(Chapters, chapter4Handler);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_II(1, Chapters, savegame, SavegameType, uint32)
	Entity::savegame(savepoint);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_SI(2, Chapters, enterStation, CityIndex)
	enterExitStation(savepoint, true);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION_S(3, Chapters, exitStation)
	enterExitStation(savepoint, false);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(4, Chapters, chapter1)
	if (savepoint.action == kActionDefault) {
		getSavePoints()->addData(kEntityChapters, kAction171843264, 0);
		setup_chapter1Init();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(5, Chapters, resetMainEntities)
	if (savepoint.action != kActionDefault)
		return;

	RESET_ENTITY_STATE(kEntityAbbot, Abbot, setup_reset);
	RESET_ENTITY_STATE(kEntityAlexei, Alexei, setup_reset);
	RESET_ENTITY_STATE(kEntityAlouan, Alouan, setup_reset);
	RESET_ENTITY_STATE(kEntityAnna, Anna, setup_reset);
	RESET_ENTITY_STATE(kEntityAugust, August, setup_reset);
	RESET_ENTITY_STATE(kEntityMertens, Mertens, setup_reset);
	RESET_ENTITY_STATE(kEntityCoudert, Coudert, setup_reset);
	RESET_ENTITY_STATE(kEntityFrancois, Francois, setup_reset);
	RESET_ENTITY_STATE(kEntityHadija, Hadija, setup_reset);
	RESET_ENTITY_STATE(kEntityIvo, Ivo, setup_reset);
	RESET_ENTITY_STATE(kEntityKahina, Kahina, setup_reset);
	RESET_ENTITY_STATE(kEntityMmeBoutarel, MmeBoutarel, setup_reset);
	RESET_ENTITY_STATE(kEntityMahmud, Mahmud, setup_reset);
	RESET_ENTITY_STATE(kEntityMax, Max, setup_reset);
	RESET_ENTITY_STATE(kEntityMilos, Milos, setup_reset);
	RESET_ENTITY_STATE(kEntityBoutarel, Boutarel, setup_reset);
	RESET_ENTITY_STATE(kEntityGendarmes, Gendarmes, setup_reset);
	RESET_ENTITY_STATE(kEntityRebecca, Rebecca, setup_reset);
	RESET_ENTITY_STATE(kEntitySalko, Salko, setup_reset);
	RESET_ENTITY_STATE(kEntitySophie, Sophie, setup_reset);
	RESET_ENTITY_STATE(kEntityTatiana, Tatiana, setup_reset);
	RESET_ENTITY_STATE(kEntityVerges, Verges, setup_reset);
	RESET_ENTITY_STATE(kEntityVassili, Vassili, setup_reset);
	RESET_ENTITY_STATE(kEntityVesna, Vesna, setup_reset);
	RESET_ENTITY_STATE(kEntityYasmin, Yasmin, setup_reset);

	CALLBACK_ACTION();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(6,Chapters, chapter1End)
	switch (savepoint.action) {
	default:
		break;

	case kAction2:
		getSound()->playSound(kEntityChapters, "MUS0009", SoundManager::kFlagDefault);
		break;

	case kActionKnock:
		if (!getSound()->isBuffered("LIB012", true))
			getSound()->playSound(kEntityPlayer, "LIB012");
		break;

	case kActionOpenDoor:
		if (params->param1) {
			getEntities()->clearSequences(kEntityChapters);
			getSound()->processEntry(kEntityChapters);
			getSound()->playSound(kEntityPlayer, "LIB014");
			getSound()->resetState();

			ENTITY_PARAM(0, 4) = 7;

			getSound()->playSteam(kCityPolice);

			getAction()->playAnimation(kEventCathDream);

			getState()->timeDelta = 3;
			getProgress().field_18 = 1;
			getProgress().field_84 = 0;

			getObjects()->update(kObject63, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);

			getScenes()->loadScene(kScene41);

			CALLBACK_ACTION();
		} else {
			getSound()->playSound(kEntityPlayer, "LIB014");
			getSound()->playSound(kEntityPlayer, "LIB015", SoundManager::kFlagDefault, 15);

			if (!getSound()->isBuffered(kEntityChapters))
				getSound()->playSound(kEntityChapters, "MUS009", SoundManager::kFlagDefault);

			getScenes()->loadSceneFromPosition(kCarLocomotive, 38);

			getObjects()->update(kObject63, kEntityChapters, kObjectLocationNone, kCursorHandKnock, kCursorHand);

			params->param1 = 1;
		}
		break;

	case kActionDefault:
		RESET_ENTITY_STATE(kEntityPascale, Pascale, setup_function19);
		RESET_ENTITY_STATE(kEntityServers0, Servers0, setup_function22);
		RESET_ENTITY_STATE(kEntityServers1, Servers1, setup_function16);
		RESET_ENTITY_STATE(kEntityCooks, Cooks, setup_function7);

		RESET_ENTITY_STATE(kEntityMertens, Mertens, setup_function42);
		RESET_ENTITY_STATE(kEntityCoudert, Coudert, setup_chapter1Handler);
		RESET_ENTITY_STATE(kEntityVerges,  Verges, setup_chapter1Handler);

		getSavePoints()->push(kEntityChapters, kEntityMertens, kAction201431954);
		getSavePoints()->push(kEntityChapters, kEntityCoudert, kAction201431954);
		getSavePoints()->push(kEntityChapters, kEntityVerges, kAction201431954);

		RESET_ENTITY_STATE(kEntityKronos, Kronos, setup_function10);
		RESET_ENTITY_STATE(kEntityKahina, Kahina, setup_function13);
		RESET_ENTITY_STATE(kEntityAnna, Anna, setup_function34);
		RESET_ENTITY_STATE(kEntityAugust, August, setup_function34);
		RESET_ENTITY_STATE(kEntityTatiana, Tatiana, setup_function24);
		RESET_ENTITY_STATE(kEntityVassili, Vassili, setup_function7);
		RESET_ENTITY_STATE(kEntityAlexei, Alexei, setup_function26);
		RESET_ENTITY_STATE(kEntityMilos, Milos, setup_function18);
		RESET_ENTITY_STATE(kEntityVesna, Vesna, setup_function15);
		RESET_ENTITY_STATE(kEntityIvo, Ivo, setup_function17);
		RESET_ENTITY_STATE(kEntitySalko, Salko, setup_function11);
		RESET_ENTITY_STATE(kEntityFrancois, Francois, setup_function20);
		RESET_ENTITY_STATE(kEntityMmeBoutarel, MmeBoutarel, setup_function16);
		RESET_ENTITY_STATE(kEntityBoutarel, Boutarel, setup_function22);
		RESET_ENTITY_STATE(kEntityRebecca, Rebecca, setup_function27);
		RESET_ENTITY_STATE(kEntitySophie, Sophie, setup_function5);
		RESET_ENTITY_STATE(kEntityMahmud, Mahmud, setup_resetChapter);
		RESET_ENTITY_STATE(kEntityYasmin, Yasmin, setup_function10);
		RESET_ENTITY_STATE(kEntityHadija, Hadija, setup_function12);
		RESET_ENTITY_STATE(kEntityHadija, Alouan, setup_function12);

		if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
			getSound()->removeFromQueue(kEntityChapters);

			ENTITY_PARAM(0, 2) = 0;
			ENTITY_PARAM(0, 3) = 0;
		}

		getSound()->processEntries();

		if (getSound()->isBuffered("CON1505"))
			getSound()->processEntry("CON1505");

		if (getSound()->isBuffered("AUG1057"))
			getSound()->processEntry("AUG1057");

		if (getSound()->isBuffered("ZFX1005"))
			getSound()->processEntry("ZFX1005");

		if (getSound()->isBuffered("ZFX1006"))
			getSound()->processEntry("ZFX1006");

		if (getSound()->isBuffered("ZFX1007"))
			getSound()->processEntry("ZFX1007");

		if (getSound()->isBuffered("ZFX1007A"))
			getSound()->processEntry("ZFX1007A");

		if (getSound()->isBuffered("ZFX1007B"))
			getSound()->processEntry("ZFX1007B");


		getSound()->playSound(kEntityPlayer, "MUS008", SoundManager::kFlagDefault);
		getInventory()->unselectItem();

		// FIXME add event pump ?
		while (getSound()->isBuffered("MUS008"))
			getSound()->updateQueue();

		getProgress().field_84 = true;

		getScenes()->loadSceneFromPosition(kCarLocomotive, 75);
		getInventory()->show();

		getState()->time = kTime1492200;
		getProgress().field_18 = 4;
		getState()->timeDelta = 0;

		getObjects()->update(kObject63, kEntityChapters, kObjectLocationNone, kCursorNormal, kCursorHand);
		getSavePoints()->push(kEntityChapters, kEntityTrain, kActionTrainStopRunning);

		getProgress().isTrainRunning = false;

		setCallback(1);
		setup_savegame(kSavegameTypeTime, kTimeNone);
		break;

	case kAction225358684:
		params->param2++;

		if (params->param2 >= 3) {

			if (!getSound()->isBuffered("LIB031", true))
				getSound()->playSound(kEntityPlayer, "LIB031");

			if (params->param2 == 3) {
				getData()->car = kCarGreenSleeping;
				getEntities()->drawSequenceLeft(kEntityChapters, "JUGL");
			}
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(7, Chapters, chapter1Init)
	if (savepoint.action != kActionDefault)
		return;

	getProgress().chapter = kChapter1;
	getSound()->resetState();

	getState()->time = kTimeChapter1;
	getState()->timeDelta = 0;
	getProgress().isTrainRunning = true;
	getProgress().portrait = kPortraitOriginal;
	getProgress().field_18 = 1;

	// Setup inventory & items location
	getInventory()->addItem(kItemTelegram);
	getInventory()->addItem(kItemArticle);

	getInventory()->setLocationAndProcess(kItemScarf, kObjectLocation1);
	getInventory()->setLocationAndProcess(kItemParchemin, kObjectLocation1);
	getInventory()->setLocationAndProcess(kItemGreenJacket, kObjectLocation1);
	getInventory()->setLocationAndProcess(kItemCorpse, kObjectLocation1);
	getInventory()->setLocationAndProcess(kItemPassengerList, kObjectLocation1);
	getInventory()->setLocationAndProcess(kItem5, kObjectLocation1);
	getInventory()->setLocationAndProcess(kItem7, kObjectLocation1);
	getInventory()->setLocationAndProcess(kItem3, kObjectLocation1);
	getInventory()->setLocationAndProcess(kItemMatch, kObjectLocation1);
	getInventory()->setLocationAndProcess(kItem22, kObjectLocation1);
	getInventory()->setLocationAndProcess(kItemPaper, kObjectLocation1);

	getProgress().field_7C = 1;

	getObjects()->update(kObjectCompartment1, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
	getObjects()->update(kObjectOutsideTylerCompartment, kEntityPlayer, kObjectLocationNone, kCursorKeepValue, kCursorKeepValue);

	for (uint i = kObjectCompartment1; i <= kObjectCompartment8; i++) {
		getObjects()->updateLocation2((ObjectIndex)i, kObjectLocation2);
	}

	for (uint i = kObjectCompartmentA; i <= kObjectCompartmentH; i++) {
		getObjects()->updateLocation2((ObjectIndex)i, kObjectLocation2);
	}

	params->param1 = 40;

	getObjects()->updateLocation2(kObject25, kObjectLocation1);
	getObjects()->updateLocation2(kObjectTrainTimeTable, kObjectLocation1);
	getObjects()->updateLocation2(kObject98, kObjectLocation1);
	getObjects()->updateLocation2(kObjectRestaurantCar, kObjectLocation1);

	getObjects()->update(kObject25, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObjectTrainTimeTable, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObjectRedSleepingCar, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject28, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject56, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject54, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObjectRestaurantCar, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject59, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject66, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject64, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject65, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject69, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObject98, kEntityPlayer, kObjectLocationNone, kCursorNormal, kCursorForward);
	getObjects()->update(kObjectHandleOutsideLeft, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorHandKnock);
	getObjects()->update(kObjectHandleOutsideRight, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorHandKnock);
	getObjects()->update(kObject101, kEntityPlayer, kObjectLocation1, kCursorHandKnock, kCursorHand);

	setup_chapter1Handler();
}

//////////////////////////////////////////////////////////////////////////
#define PLAY_STEAM() { \
	getSound()->resetState(); \
	getSound()->playSteam((CityIndex)ENTITY_PARAM(0, 4)); \
	ENTITY_PARAM(0, 2) = 0; \
	}

IMPLEMENT_FUNCTION(8, Chapters, chapter1Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!getProgress().isTrainRunning || getState()->time >= kTime1458000)
			goto label_processStations;

		UPDATE_PARAM_PROC(params->param6, getState()->timeTicks, params->param2)
			// Play sound FX
			getSound()->playLocomotiveSound();

			params->param2 = 225 * (4 * rnd(5) + 20);
			params->param6 = 0;
		UPDATE_PARAM_PROC_END

label_processStations:
		// Process stations
		TIME_CHECK_SAVEGAME(kTime1039500, params->param7, 1, kSavegameTypeTime, kTimeNone);

label_enter_epernay:
		// Entering Epernay station
		TIME_CHECK_ENTERSTATION(kTimeEnterEpernay, params->param8, 1, "Epernay", kCityEpernay);

label_exit_epernay:
		// Exiting Epernay station
		TIME_CHECK_EXITSTATION_2(kTimeExitEpernay, CURRENT_PARAMS(1, 1), params->param4, 3, "Epernay");

label_epernay_police:
		TIME_CHECK_EXITSTATION_0(params->param5, ENTITY_PARAM(0, 2), 4, "Unschedu");

label_enter_chalons:
		if (getState()->time > kTimeEnterChalons && !CURRENT_PARAMS(1, 2)) {
			CURRENT_PARAMS(1, 2) = 1;
			getProgress().field_18 = 2;
		}

		// Skip to callback 18 checks
		if (params->param1)
			goto label_exit_strasbourg;

		// Entering Chalons station
		TIME_CHECK_ENTERSTATION(kTimeEnterChalons, CURRENT_PARAMS(1, 3), 5, "Chalons", kCityChalons);

label_exit_chalons:
		// Exiting Chalons station
		TIME_CHECK_EXITSTATION(kTimeExitChalons, CURRENT_PARAMS(1, 4), 6, "Chalons");

label_enter_barleduc:
		// Entering Bar-Le-Duc station
		TIME_CHECK_ENTERSTATION(kTimeCityBarLeDuc, CURRENT_PARAMS(1, 5), 7, "BarLeDuc", kCityBarleduc);

label_exit_barleduc:
		// Exiting Bar-Le-Duc station
		TIME_CHECK_EXITSTATION(kTimeExitBarLeDuc, CURRENT_PARAMS(1, 6), 8, "BarLeDuc");

label_enter_nancy:
		if (getState()->time > kTime1260000 && !CURRENT_PARAMS(1, 7)) {
			CURRENT_PARAMS(1, 7) = 1;
			getState()->timeDelta = 1;
		}

		// Entering Nancy station
		TIME_CHECK_ENTERSTATION(kTimeCityNancy, CURRENT_PARAMS(1, 8), 9, "Nancy", kCityNancy);

label_exit_nancy:
		// Exiting Nancy station
		TIME_CHECK_EXITSTATION(kTimeExitNancy, CURRENT_PARAMS(2, 1), 10, "Nancy");

label_enter_luneville:
		// Entering Luneville station
		TIME_CHECK_ENTERSTATION(kTimeCityLuneville, CURRENT_PARAMS(2, 2), 11, "Luneville", kCityLuneville);

label_exit_luneville:
		// Exiting Luneville station
		TIME_CHECK_EXITSTATION(kTimeExitLuneville, CURRENT_PARAMS(2, 3), 12, "Luneville");

label_enter_avricourt:
		// Entering Avricourt station
		TIME_CHECK_ENTERSTATION(kTimeCityAvricourt, CURRENT_PARAMS(2, 4), 13, "Avricourt", kCityAvricourt);

label_exit_avricourt:
		// Exiting Avricourt station
		TIME_CHECK_EXITSTATION(kTimeExitAvricourt, CURRENT_PARAMS(2, 5), 14, "Avricourt");

label_enter_deutschavricourt:
		// Entering Deutsch-Avricourt station
		TIME_CHECK_ENTERSTATION(kTimeCityDeutschAvricourt, CURRENT_PARAMS(2, 6), 15, "DeutschA", kCityDeutschAvricourt);

label_exit_deutschavricourt:
		// Exiting Avricourt station
		TIME_CHECK_EXITSTATION(kTimeExitDeutschAvricourt, CURRENT_PARAMS(2, 7), 16, "DeutschA");

label_enter_strasbourg:
		TIME_CHECK_SAVEGAME(kTimeCityStrasbourg, CURRENT_PARAMS(2, 8), 17, kSavegameTypeTime, kTimeNone);

label_exit_strasbourg:
		// Exiting Strasbourg station
		TIME_CHECK_EXITSTATION(kTimeExitStrasbourg, CURRENT_PARAMS(3, 1), 19, "Strasbou");

label_enter_badenoos:
		// Entering Baden Oos station
		TIME_CHECK_ENTERSTATION(kTimeCityBadenOos, CURRENT_PARAMS(3, 2), 20, "BadenOos", kCityBadenOos);

label_exit_badenoos:
		// Exiting Baden Oos station
		TIME_CHECK_EXITSTATION(kTimeExitBadenOos, CURRENT_PARAMS(3, 3), 21, "BadenOos");

label_chapter1_next:
		if (getState()->time > kTimeChapter1End3 && ! CURRENT_PARAMS(3, 4)) {
			CURRENT_PARAMS(3, 4) = 1;
			setup_chapter1Next();
		}
		break;

	case kAction2:
		if (ENTITY_PARAM(0, 2)) {

			getSavePoints()->push(kEntityChapters, kEntityTrain, kActionTrainStopRunning);

			if (getEntityData(kEntityPlayer)->location != kLocationOutsideTrain) {
				PLAY_STEAM();
				break;
			}

			if (getEntities()->isOutsideAlexeiWindow()) {
				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);
				PLAY_STEAM();
				break;
			}

			if (getEntities()->isOutsideAnnaWindow()) {
				getScenes()->loadSceneFromPosition(kCarRedSleeping, 49);
				PLAY_STEAM();
				break;
			}

			CarIndex car = getEntityData(kEntityPlayer)->car;
			if (car < kCarRedSleeping || car > kCarCoalTender) {
				if (car < kCarBaggageRear || car > kCarGreenSleeping) {
					PLAY_STEAM();
					break;
				}

				if (getEntities()->isPlayerPosition(kCarGreenSleeping, 98)) {
					getSound()->playSound(kEntityPlayer, "LIB015");
					getScenes()->loadSceneFromPosition(kCarGreenSleeping, 71);
					PLAY_STEAM();
					break;
				}

				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 82);
				PLAY_STEAM();
				break;
			}

			getScenes()->loadSceneFromPosition(kCarRestaurant, 82);
			PLAY_STEAM();
			break;
		}

		if (ENTITY_PARAM(0, 3)) {
			getSound()->resetState();
			ENTITY_PARAM(0, 3) = 0;

			if (params->param4) {
				getSavePoints()->push(kEntityChapters, getProgress().field_24 ? kEntityVerges : kEntityMertens, getProgress().field_24 ? kAction168187490 : kAction224122407);
				params->param4 = 0;
			}
		}
		break;

	case kActionDefault:
		params->param2 = 225 * (4 * rnd(5) + 20);
		break;

	case kActionDrawScene:
		if (!params->param3) {
			if (getEntities()->isPlayerPosition(kCarGreenSleeping, 1)) {
				getState()->time = kTimeChapter1;
				getState()->timeDelta = 3;
				params->param3 = 1;
			}
		}
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			goto label_enter_epernay;

		case 2:
			goto label_exit_epernay;

		case 3:
			goto label_epernay_police;

		case 4:
			params->param5 = 0;
			goto label_enter_chalons;

		case 5:
			goto label_exit_chalons;

		case 6:
			goto label_enter_barleduc;

		case 7:
			goto label_exit_barleduc;

		case 8:
			goto label_enter_nancy;

		case 9:
			goto label_exit_nancy;

		case 10:
			goto label_enter_luneville;

		case 11:
			goto label_exit_luneville;

		case 12:
			goto label_enter_avricourt;

		case 13:
			goto label_exit_avricourt;

		case 14:
			goto label_enter_deutschavricourt;

		case 15:
			goto label_exit_deutschavricourt;

		case 16:
			getState()->time = kTimeEnterStrasbourg;
			goto label_enter_strasbourg;

		case 17:
			getProgress().field_18 = 1;
			setCallback(18);
			setup_enterStation("Strasbou", kCityStrasbourg);
			break;

		case 18:
			goto label_exit_strasbourg;

		case 19:
			getState()->timeDelta = 1;
			goto label_enter_badenoos;

		case 20:
			goto label_exit_badenoos;

		case 21:
			goto label_chapter1_next;

		case 22:
			params->param5 = 1;
			break;

		case 23:
			params->param1 = 1;
			break;
		}
		break;

	case kAction169629818:
		setCallback(22);
		setup_enterStation("Unschedu", kCityPolice);
		break;

	case kActionEndChapter:
		getProgress().field_18 = 3;

		if (getState()->time >= kTimeChapter1End) {
			setup_chapter1Next();
		} else {
			setCallback(23);
			setup_chapter1End();
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(9, Chapters, chapter1Next)
	if (savepoint.action == kActionDefault) {
		// Reset sound cache
		if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
			getSound()->removeFromQueue(kEntityChapters);
			ENTITY_PARAM(0, 2) = 0;
			ENTITY_PARAM(0, 3) = 0;
		}

		getSound()->playSound(kEntityPlayer, "MUS008", SoundManager::kFlagDefault);
		getInventory()->unselectItem();

		while (getSound()->isBuffered("MUS008"))
			getSound()->updateQueue();

		setup_chapter2();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(10, Chapters, chapter2)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		// Setup for chapter 2 in case it hasn't been done before
		if (getProgress().chapter != kChapter2) {
			getProgress().chapter = kChapter2;
			getEntities()->setupChapter(kChapter2);
		}

		// Set game time & delta
		getState()->time = kTimeChapter2;
		getState()->timeDelta = 5;

		// Save game
		setCallback(1);
		setup_savegame(kSavegameTypeTime, kTimeNone);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			if (!_engine->getResourceManager()->loadArchive(kArchiveCd2)) {
				getMenu()->show(false, kSavegameTypeIndex, 0);
				return;
			}

			// Load scene data
			getScenes()->loadSceneDataFile(kArchiveCd2);
			setup_chapter2Init();
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(11, Chapters, chapter2Init)
	if (savepoint.action != kActionDefault)
		return;

	getProgress().eventCorpseMovedFromFloor = true;
	getProgress().field_18 = 1;
	getProgress().isTrainRunning = true;
	getProgress().eventCorpseFound = true;

	// Switch to green jacket/portrait
	getProgress().jacket = kJacketGreen;
	getProgress().portrait = kPortraitGreen;

	// Setup inventory & items location
	getInventory()->addItem(kItemGreenJacket);

	getObjects()->update(kObjectHandleOutsideLeft, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorHand);
	getObjects()->update(kObjectHandleOutsideRight, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorHand);

	getInventory()->setLocationAndProcess(kItemBeetle, kObjectLocation3);
	getInventory()->setLocationAndProcess(kItem3, kObjectLocation1);

	for (uint i = 1; i < 9; i++) {
		getObjects()->updateLocation2((ObjectIndex)i, kObjectLocation2);
	}

	for (uint i = 33; i < 40; i++) {
		getObjects()->updateLocation2((ObjectIndex)i, kObjectLocation2);
	}

	params->param1 = 40;

	getSavePoints()->push(kEntityChapters, kEntityTables0, kActionDrawTablesWithChairs);
	getSavePoints()->push(kEntityChapters, kEntityTables1, kActionDrawTablesWithChairs);
	getSavePoints()->push(kEntityChapters, kEntityTables2, kActionDrawTablesWithChairs);
	getSavePoints()->push(kEntityChapters, kEntityTables3, kActionDrawTablesWithChairs);
	getSavePoints()->push(kEntityChapters, kEntityTables4, kActionDrawTablesWithChairs);

	getObjects()->update(kObjectCompartment1, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
	getObjects()->update(kObjectOutsideTylerCompartment, kEntityPlayer, kObjectLocationNone, kCursorKeepValue, kCursorKeepValue);

	// Reset sound cache
	if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
		getSound()->removeFromQueue(kEntityChapters);
		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
	}

	getAction()->playAnimation(kEventTrainPassing);

	if (getInventory()->hasItem(kItemScarf))
		getScenes()->loadScene(kScene41);
	else
		getScenes()->loadSceneFromPosition(kCarGreenSleeping, 79);

	setup_chapter2Handler();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(12, Chapters, chapter2Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (!getProgress().isTrainRunning)
			break;

		UPDATE_PARAM(params->param2, getState()->timeTicks, params->param1);

		getSound()->playLocomotiveSound();

		params->param1 = 225 * (4 * rnd(5) + 20);
		params->param2 = 0;
		break;

	case kActionDefault:
		params->param1 = 225 * (4 * rnd(5) + 20);
		break;

	case kActionChapter3:
		setup_chapter3();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(13, Chapters, chapter3)
	if (savepoint.action == kActionDefault) {
		// Setup for chapter 3 in case it hasn't been done before
		if (getProgress().chapter != kChapter3) {
			getProgress().chapter = kChapter3;
			getEntities()->setupChapter(kChapter3);
		}

		// Set game time & delta
		getState()->time = kTimeChapter3;
		getState()->timeDelta = 5;

		setup_chapter3Init();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(14, Chapters, chapter3Init)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getSavePoints()->push(kEntityChapters, kEntityTables0, kActionDrawTablesWithChairs);
		getSavePoints()->push(kEntityChapters, kEntityTables1, kActionDrawTablesWithChairs);
		getSavePoints()->push(kEntityChapters, kEntityTables2, kActionDrawTablesWithChairs);
		getSavePoints()->push(kEntityChapters, kEntityTables3, kActionDrawTablesWithChairs);
		getSavePoints()->push(kEntityChapters, kEntityTables4, kActionDrawTablesWithChairs);
		getSavePoints()->push(kEntityChapters, kEntityTables5, kActionDrawTablesWithChairs);

		getProgress().isTrainRunning = true;

		getObjects()->update(kObjectHandleOutsideLeft, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorHand);
		getObjects()->update(kObjectHandleOutsideRight, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorHand);
		getInventory()->setLocationAndProcess(kItemBriefcase, kObjectLocation1);
		getInventory()->setLocationAndProcess(kItem3, kObjectLocation1);
		getObjects()->updateLocation2(kObjectCompartment1, kObjectLocation2);
		getObjects()->update(kObject107, kEntityPlayer, kObjectLocation3, kCursorKeepValue, kCursorKeepValue);

		if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
			getSound()->removeFromQueue(kEntityChapters);
			ENTITY_PARAM(0, 2) = 0;
			ENTITY_PARAM(0, 3) = 0;
		}

		getScenes()->loadSceneFromPosition(kCarRestaurant, 60);
		getInventory()->show();

		setCallback(1);
		setup_savegame(kSavegameTypeTime, kTimeNone);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_chapter3Handler();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(15, Chapters, chapter3Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().isTrainRunning) {
			UPDATE_PARAM_PROC(params->param4, getState()->timeTicks, params->param1)
				getSound()->playLocomotiveSound();

				params->param1 = 225 * (4 * rnd(5) + 20);
				params->param4 = 0;
			UPDATE_PARAM_PROC_END
		}

		UPDATE_PARAM_PROC(params->param5, getState()->timeTicks, params->param2)
			switch (rnd(2)) {
			default:
				break;

			case 0:
				getSound()->playSound(kEntityPlayer, "ZFX1008", (SoundManager::FlagType)(rnd(15) + 2));
				break;

			case 1:
				getSound()->playSound(kEntityPlayer, "ZFX1009", (SoundManager::FlagType)(rnd(15) + 2));
				break;
			}

			params->param2 = 225 * (4 * rnd(6) + 8);
			params->param5 = 0;
		UPDATE_PARAM_PROC_END

		TIME_CHECK_ENTERSTATION(kTimeEnterSalzbourg, params->param6, 1, "Salzburg", kCitySalzbourg);

label_callback_1:
		TIME_CHECK_EXITSTATION(kTimeExitSalzbourg, params->param7, 2, "Salzburg");

label_callback_2:
		TIME_CHECK_ENTERSTATION(kTimeEnterAttnangPuchheim, params->param8, 3, "Attnang", kCityAttnangPuchheim);

label_callback_3:
		TIME_CHECK_EXITSTATION(kTimeExitAttnangPuchheim, CURRENT_PARAMS(1, 1), 4, "Attnang");

label_callback_4:
		TIME_CHECK_ENTERSTATION(kTimeEnterWels, CURRENT_PARAMS(1, 2), 5, "Wels", kCityWels);

label_callback_5:
		TIME_CHECK_EXITSTATION(kTimeEnterWels, CURRENT_PARAMS(1, 3), 6, "Wels");

label_callback_6:
		TIME_CHECK_ENTERSTATION(kTimeEnterLinz, CURRENT_PARAMS(1, 4), 7, "Linz", kCityLinz);

label_callback_7:
		TIME_CHECK_EXITSTATION(kTimeCityLinz, CURRENT_PARAMS(1, 5), 8, "Linz");

label_callback_8:
		if (getState()->time > kTime2187000 && !CURRENT_PARAMS(1, 6)) {
			CURRENT_PARAMS(1, 6) = 1;
			getState()->timeDelta = 5;
		}

		TIME_CHECK_ENTERSTATION(kTimeCityVienna, CURRENT_PARAMS(1, 7), 9, "Vienna", kCityVienna);
		break;

	case kAction2:
		if (ENTITY_PARAM(0, 2)) {
			getSavePoints()->push(kEntityChapters, kEntityTrain, kActionTrainStopRunning);

			if (getEntityData(kEntityPlayer)->location == kLocationOutsideTrain) {

				if (getEntities()->isOutsideAlexeiWindow()) {
					getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);
				} else if (getEntities()->isOutsideAnnaWindow()) {
					getScenes()->loadSceneFromPosition(kCarRedSleeping, 49);
				} else {
					CarIndex car = getEntityData(kEntityPlayer)->car;

					if (car < kCarRedSleeping || car > kCarCoalTender) {
						if (car >= kCarBaggageRear && car <= kCarGreenSleeping) {
							if (getEntities()->isPlayerPosition(kCarGreenSleeping, 98)) {
								getSound()->playSound(kEntityPlayer, "LIB015");
								getScenes()->loadSceneFromPosition(kCarGreenSleeping, 71);
							} else {
								getScenes()->loadSceneFromPosition(kCarGreenSleeping, 82);
							}
						}
					} else {
						getScenes()->loadSceneFromPosition(kCarRestaurant, 82);
					}
				}
			}

			getSound()->resetState();
			getSound()->playSteam((CityIndex)ENTITY_PARAM(0, 4));

			ENTITY_PARAM(0, 2) = 0;
			if (params->param1)
				setup_viennaEvents();

			break;
		}

		if (ENTITY_PARAM(0, 3)) {
			getSound()->resetState();
			ENTITY_PARAM(0, 3) = 0;
		}
		break;

	case kActionDefault:
		params->param1 = 225 * (4 * rnd(5) + 20);
		params->param2 = 225 * (4 * rnd(6) + 8);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			goto label_callback_1;

		case 2:
			goto label_callback_2;

		case 3:
			goto label_callback_3;

		case 4:
			goto label_callback_4;

		case 5:
			goto label_callback_5;

		case 6:
			goto label_callback_6;

		case 7:
			goto label_callback_7;

		case 8:
			goto label_callback_8;

		case 9:
			params->param3 = 1;
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(16, Chapters, viennaEvents)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			getAction()->playAnimation(kEventViennaAugustUnloadGuns);
			if (getEvent(kEventConcertLeaveWithBriefcase))
				getLogic()->gameOver(kSavegameTypeTime, kTime2187000, kSceneNone, true);
			else if (getEvent(kEventCathJumpDownCeiling))
				getLogic()->gameOver(kSavegameTypeEvent, kEventCathJumpDownCeiling, kSceneNone, true);
			else
				getLogic()->gameOver(kSavegameTypeTime, kTime2155500, kSceneNone, true);
			break;

		case 2:
			getAction()->playAnimation(kEventViennaKronosFirebird);
			if (getEvent(kEventKronosBringEggCeiling))
				getLogic()->gameOver(kSavegameTypeEvent2, kEventKronosBringEggCeiling, kSceneGameOverVienna1, true);
			else if (getEvent(kEventKronosBringEgg)) {
				if (getEvent(kEventKronosBringEggCeiling))
					getLogic()->gameOver(kSavegameTypeEvent2, kEventKronosBringEggCeiling, kSceneGameOverVienna1, true);
				else
					getLogic()->gameOver(kSavegameTypeTime, kTime2155500, kSceneGameOverVienna1, true);
			} else {
				if (getProgress().field_C0) {
					if (getEvent(kEventKronosReturnBriefcase))
						getLogic()->gameOver(kSavegameTypeTime, getProgress().field_C0, kSceneGameOverVienna2, true);
					else
						getLogic()->gameOver(kSavegameTypeTime, kTime2155500, kSceneGameOverVienna2, true);
				} else {
					if (getEvent(kEventKronosReturnBriefcase))
						getLogic()->gameOver(kSavegameTypeEvent, kEventKronosReturnBriefcase, kSceneGameOverVienna, true);
					else
						getLogic()->gameOver(kSavegameTypeTime, kTime2155500, kSceneGameOverVienna, true);
				}
			}
			break;

		case 3:
			getAction()->playAnimation(kEventVergesAnnaDead);
			getLogic()->gameOver(kSavegameTypeTime, kTime2250000, kSceneGameOverAnnaDied, true);
			break;

		case 4:
			getAction()->playAnimation(kEventViennaContinueGame);
			setup_chapter4();
			break;
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(17, Chapters, chapter4)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		// Setup for chapter 4 in case it hasn't been done before
		if (getProgress().chapter != kChapter4) {
			getProgress().chapter = kChapter4;
			getEntities()->setupChapter(kChapter4);
		}

		// Set game time & delta
		getState()->time = kTimeChapter4;
		getState()->timeDelta = 5;

		// Save game
		setCallback(1);
		setup_savegame(kSavegameTypeTime, kTimeNone);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			if (!_engine->getResourceManager()->loadArchive(kArchiveCd3)) {
				getMenu()->show(false, kSavegameTypeIndex, 0);
				return;
			}

			// Load scene data
			getScenes()->loadSceneDataFile(kArchiveCd3);
			setup_chapter4Init();
		}
		break;

	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(18, Chapters, chapter4Init)
	if (savepoint.action != kActionDefault)
		return;

	getSound()->processEntries();
	getSound()->resetState();

	getProgress().isTrainRunning = true;

	getObjects()->update(kObjectHandleOutsideLeft, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorHand);
	getObjects()->update(kObjectHandleOutsideRight, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorHand);

	getSavePoints()->push(kEntityChapters, kEntityTrain, kActionTrainStartRunning);
	getSavePoints()->push(kEntityChapters, kEntityTables0, kActionDrawTablesWithChairs);
	getSavePoints()->push(kEntityChapters, kEntityTables1, kActionDrawTablesWithChairs);
	getSavePoints()->push(kEntityChapters, kEntityTables2, kActionDrawTablesWithChairs);
	getSavePoints()->push(kEntityChapters, kEntityTables3, kActionDrawTablesWithChairs);
	getSavePoints()->push(kEntityChapters, kEntityTables4, kActionDrawTablesWithChairs);
	getSavePoints()->push(kEntityChapters, kEntityTables5, kActionDrawTablesWithChairs);

	getScenes()->loadSceneFromItemPosition(kItem3);

	getInventory()->setLocationAndProcess(kItemBomb, kObjectLocation1);

	if (getInventory()->get(kItemBeetle)->location == kObjectLocation3)
		getScenes()->loadSceneFromItemPosition(kItemBeetle);

	getObjects()->updateLocation2(kObject25, kObjectLocation2);
	getObjects()->update(kObject107, kEntityPlayer, kObjectLocation3, kCursorKeepValue, kCursorKeepValue);

	if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
		getSound()->removeFromQueue(kEntityChapters);
		ENTITY_PARAM(0, 2) = 0;
		ENTITY_PARAM(0, 3) = 0;
	}

	if (getInventory()->hasItem(kItemFirebird))
		getScenes()->loadSceneFromPosition(kCarGreenSleeping, 76);
	else
		getScenes()->loadSceneFromPosition(kCarRestaurant, 69);

	getInventory()->show();
	setup_chapter4Handler();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(19, Chapters, chapter4Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getProgress().isTrainRunning) {
			UPDATE_PARAM_PROC(params->param6, getState()->timeTicks, params->param4);
				getSound()->playLocomotiveSound();

				params->param4 = 225 * (4 * rnd(5) + 20);
				params->param6 = 0;
			UPDATE_PARAM_PROC_END
		}

		UPDATE_PARAM_PROC(params->param7, getState()->timeTicks, params->param5)
			switch (rnd(2)) {
			default:
				break;

			case 0:
				getSound()->playSound(kEntityPlayer, "ZFX1008", (SoundManager::FlagType)(rnd(15) + 2));
				break;

			case 1:
				getSound()->playSound(kEntityPlayer, "ZFX1009", (SoundManager::FlagType)(rnd(15) + 2));
				break;
			}

			params->param5 = 225 * (4 * rnd(6) + 8);
			params->param7 = 0;
		UPDATE_PARAM_PROC_END

		TIME_CHECK_ENTERSTATION(kTimeEnterPoszony, params->param8, 1, "Pozsony", kCityPoszony);

label_exitPozsony:
		TIME_CHECK_EXITSTATION(kTimeExitPoszony, CURRENT_PARAMS(1, 1), 2, "Pozsony");

label_enterGalanta:
		if (getObjects()->get(kObjectCompartment1).location2 == kObjectLocation1) {
			if (getState()->time > kTime2403000 && !CURRENT_PARAMS(1, 2)) {
				CURRENT_PARAMS(1, 2) = 1;
				getProgress().field_18 = 2;
			}
		}

		if (params->param1)
			goto label_callback_4;

		TIME_CHECK_ENTERSTATION(kTimeEnterGalanta, CURRENT_PARAMS(1, 3), 3, "Galanta", kCityGalanta);

label_exitGalanta:
		TIME_CHECK_EXITSTATION(kTimeExitGalanta, CURRENT_PARAMS(1, 4), 4, "Galanta");

label_callback_4:
		if (getState()->time > kTime2470500 && !CURRENT_PARAMS(1, 5)) {
			CURRENT_PARAMS(1, 5) = 1;

			if (getProgress().field_18 == 2)
				getState()->timeDelta = 1;
		}

		if (getState()->time > kTime2506500 && !CURRENT_PARAMS(1, 6)) {
			CURRENT_PARAMS(1, 6) = 1;

			if (getProgress().field_18 == 2)
				getProgress().field_18 = 1;
		}

		if (getState()->time > kTime2520000 && !CURRENT_PARAMS(1, 7)) {
			CURRENT_PARAMS(1, 7) = 1;

			if (!params->param2 && !params->param3) {
				setCallback(5);
				setup_savegame(kSavegameTypeEvent, kEventTrainExplosionBridge);
			}
		}
		break;

	case kAction2:
		if (ENTITY_PARAM(0, 2)) {

			getSavePoints()->push(kEntityChapters, kEntityTrain, kActionTrainStopRunning);

			if (getEntityData(kEntityPlayer)->location != kLocationOutsideTrain) {
				PLAY_STEAM();
				break;
			}

			if (getEntities()->isOutsideAlexeiWindow()) {
				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);
				PLAY_STEAM();
				break;
			}

			if (getEntities()->isOutsideAnnaWindow()) {
				getScenes()->loadSceneFromPosition(kCarRedSleeping, 49);
				PLAY_STEAM();
				break;
			}

			CarIndex car = getEntityData(kEntityPlayer)->car;
			if (car < kCarRedSleeping || car > kCarCoalTender) {
				if (car < kCarBaggageRear || car > kCarGreenSleeping) {
					PLAY_STEAM();
					break;
				}

				if (getEntities()->isPlayerPosition(kCarGreenSleeping, 98)) {
					getSound()->playSound(kEntityPlayer, "LIB015");
					getScenes()->loadSceneFromPosition(kCarGreenSleeping, 71);
					PLAY_STEAM();
					break;
				}

				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 82);
				PLAY_STEAM();
				break;
			}

			getScenes()->loadSceneFromPosition(kCarRestaurant, 82);
			PLAY_STEAM();
			break;
		}

		if (ENTITY_PARAM(0, 3)) {
			getSound()->resetState();
			ENTITY_PARAM(0, 3) = 0;
		} else if (!params->param2 && !params->param3) {
			getSound()->playSound(kEntityChapters, "ZFX1001");
		}
		break;

	case kActionExitCompartment:
		getEntities()->clearSequences(kEntityChapters);

		setCallback(11);
		setup_savegame(kSavegameTypeTime, kTimeNone);
		break;

	case kActionDefault:
		params->param4 = 225 * (4 * rnd(5) + 20);
		params->param5 = 225 * (4 * rnd(6) + 8);
		break;

	case kActionCallback:
		switch (getCallback()) {
		default:
			break;

		case 1:
			goto label_exitPozsony;

		case 2:
			goto label_enterGalanta;

		case 3:
			goto label_exitGalanta;

		case 4:
			goto label_callback_4;

		case 5:
			if (getSound()->isBuffered(kEntityChapters))
				getSound()->removeFromQueue(kEntityChapters);

			getAction()->playAnimation(kEventTrainExplosionBridge);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneNone, true);
			break;

		case 6:
			getSound()->processEntries();
			getAction()->playAnimation(kEventTylerCastleDream);
			getSound()->resetState();

			getProgress().field_18 = 1;

			getScenes()->loadScene(kScene41);
			getSavePoints()->push(kEntityChapters, kEntityTatiana, kAction169360385);

			getState()->timeDelta = 1;
			getState()->time = kTime2511900;

			getInventory()->setLocationAndProcess(kItem2, kObjectLocation1);
			getScenes()->loadSceneFromItemPosition(kItem22);

			getData()->car = kCarRedSleeping;
			getData()->entityPosition = kPosition_1500;
			getData()->location = kLocationInsideCompartment;

			getSound()->playSound(kEntityChapters, "ZFX1001");
			break;

		case 7:
			getAction()->playAnimation(kEventTrainExplosionBridge);
			getLogic()->gameOver(kSavegameTypeTime, kTime2430000, kSceneNone, true);
			break;

		case 8:
			getSound()->playSound(kEntityPlayer, "MUS022");

			if (getState()->time < kTime2517300)
				getState()->time = kTime2517300;
			break;

		case 9:
			getAction()->playAnimation(kEventCathDefusingBomb);
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 73);
			break;

		case 10:
			getAction()->playAnimation(kEventDefuseBomb);
			RESET_ENTITY_STATE(kEntityAbbot, Abbot, setup_function48);
			getSavePoints()->push(kEntityChapters, kEntityAnna, kAction191001984);
			getSavePoints()->push(kEntityChapters, kEntityCoudert, kAction191001984);
			getScenes()->loadSceneFromItemPosition(kItem2);

			getInventory()->get(kItem2)->location = kObjectLocationNone;
			params->param2 = 1;

			getScenes()->loadSceneFromPosition(kCarRedSleeping, 2);
			break;

		case 11:
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 74);
			getSound()->playSound(kEntityTrain, "ZFX4001", SoundManager::kFlagDefault);
			getLogic()->gameOver(kSavegameTypeIndex, 1, kSceneNone, true);
			break;
		}
		break;

	case kActionChapter5:
		setup_chapter5();
		break;

	case kAction156435676:
		getSavePoints()->push(kEntityChapters, kEntityTatiana, kAction169360385);
		getSavePoints()->push(kEntityChapters, kEntityCoudert, kAction201431954);
		getSavePoints()->push(kEntityChapters, kEntityVerges, kAction201431954);

		getState()->timeDelta = 1;
		getState()->time = kTime2511900;

		getInventory()->setLocationAndProcess(kItem2, kObjectLocation1);

		getData()->car = kCarRedSleeping;
		getData()->entityPosition = kPosition_1500;
		getData()->location = kLocationInsideCompartment;

		getSound()->playSound(kEntityChapters, "ZFX1001");
		break;

	case kAction158610240:
		setCallback(8);
		setup_savegame(kSavegameTypeTime, kTimeNone);
		break;

	case kAction169300225:
		if (getState()->time < kTime2519100)
			getState()->time = kTime2519100;

		params->param3 = 1;

		getEntities()->drawSequenceRight(kEntityChapters, "BOMB");
		break;

	case kAction190346110:
		getProgress().field_18 = 3;

		params->param1 = 1;

		if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
			getSound()->removeFromQueue(kEntityChapters);

			ENTITY_PARAM(0, 2) = 0;
			ENTITY_PARAM(0, 3) = 0;
		}

		getSound()->playSound(kEntityPlayer, "MUS008", SoundManager::kFlagDefault);
		getInventory()->unselectItem();

		while (getSound()->isBuffered("MUS008"))
			getSound()->updateQueue();

		if (getInventory()->hasItem(kItemBomb)) {
			RESET_ENTITY_STATE(kEntityAlexei, Alexei, setup_function47);
			RESET_ENTITY_STATE(kEntityAnna, Anna, setup_function68);
			RESET_ENTITY_STATE(kEntityAugust, August, setup_function65);
			RESET_ENTITY_STATE(kEntityMertens, Mertens, setup_function48);
			RESET_ENTITY_STATE(kEntityCoudert, Coudert, setup_function53);
			RESET_ENTITY_STATE(kEntityServers0, Servers0, setup_chapter4Handler);
			RESET_ENTITY_STATE(kEntityServers1, Servers1, setup_chapter4Handler);
			RESET_ENTITY_STATE(kEntityPascale, Pascale, setup_chapter4Handler);
			RESET_ENTITY_STATE(kEntityVerges, Verges, setup_chapter4Handler);
			RESET_ENTITY_STATE(kEntityTatiana, Tatiana, setup_function49);
			RESET_ENTITY_STATE(kEntityAbbot, Abbot, setup_function44);
			RESET_ENTITY_STATE(kEntityMilos, Milos, setup_function32);
			RESET_ENTITY_STATE(kEntityVesna, Vesna, setup_function27);
			RESET_ENTITY_STATE(kEntityIvo, Ivo, setup_function29);
			RESET_ENTITY_STATE(kEntitySalko, Salko, setup_function22);
			RESET_ENTITY_STATE(kEntityMmeBoutarel, MmeBoutarel, setup_function25);
			RESET_ENTITY_STATE(kEntityBoutarel, Boutarel, setup_function35);
			RESET_ENTITY_STATE(kEntityRebecca, Rebecca, setup_function45);
			RESET_ENTITY_STATE(kEntitySophie, Sophie, setup_function9);
			RESET_ENTITY_STATE(kEntityYasmin, Yasmin, setup_function17);
			RESET_ENTITY_STATE(kEntityHadija, Hadija, setup_function19);
			RESET_ENTITY_STATE(kEntityAlouan, Alouan, setup_function19);
			RESET_ENTITY_STATE(kEntityMax, Max, setup_chapter4Handler);
			getSavePoints()->push(kEntityChapters, kEntityAnna, kAction201431954);
			getSavePoints()->push(kEntityChapters, kEntityMertens, kAction201431954);
			getSavePoints()->push(kEntityChapters, kEntityCoudert, kAction201431954);
			getSavePoints()->push(kEntityChapters, kEntityServers0, kAction201431954);
			getSavePoints()->push(kEntityChapters, kEntityServers1, kAction201431954);
			getSavePoints()->push(kEntityChapters, kEntityPascale, kAction201431954);
			getSavePoints()->push(kEntityChapters, kEntityVerges, kAction201431954);

			setCallback(6);
			setup_savegame(kSavegameTypeEvent, kEventTylerCastleDream);
		} else {
			getState()->time = kTime2520000;

			setCallback(7);
			setup_savegame(kSavegameTypeEvent, kEventTrainExplosionBridge);
		}
		break;

	case kAction191001984:
		getState()->time = kTime2520000;

		if (getSound()->isBuffered(kEntityChapters))
			getSound()->removeFromQueue(kEntityChapters);

		getEntities()->clearSequences(kEntityChapters);
		getInventory()->removeItem(kItemTelegram);

		getState()->timeDelta = 5;

		setCallback(10);
		setup_savegame(kSavegameTypeEvent, kEventDefuseBomb);
		break;

	case kAction201959744:
		if (getSound()->isBuffered(kEntityChapters))
			getSound()->removeFromQueue(kEntityChapters);

		getSound()->playSound(kEntityTrain, "ZFX4001", SoundManager::kFlagDefault);

		getLogic()->gameOver(kSavegameTypeIndex, 0, kSceneNone, true);
		break;

	case kAction225367984:
		setCallback(9);
		setup_savegame(kSavegameTypeEvent, kEventCathDefusingBomb);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(20, Chapters, chapter5)
	if (savepoint.action == kActionDefault) {
		// Setup for chapter 5 in case it hasn't been done before
		if (getProgress().chapter != kChapter5) {
			getProgress().chapter = kChapter5;
			getEntities()->setupChapter(kChapter5);
		}

		// Set game time & delta
		getState()->time = kTimeChapter5;
		getState()->timeDelta = 2;

		setup_chapter5Init();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(21, Chapters, chapter5Init)
	switch (savepoint.action) {
	default:
		break;

	case kActionDefault:
		getEntities()->clearSequences(kEntityTables0);
		getEntities()->clearSequences(kEntityTables1);
		getEntities()->clearSequences(kEntityTables2);
		getEntities()->clearSequences(kEntityTables3);
		getEntities()->clearSequences(kEntityTables4);
		getEntities()->clearSequences(kEntityTables5);

		getProgress().isTrainRunning = true;

		getObjects()->update(kObjectHandleOutsideLeft, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorHand);
		getObjects()->update(kObjectHandleOutsideRight, kEntityPlayer, kObjectLocation1, kCursorNormal, kCursorHand);
		getObjects()->update(kObjectCompartment1, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment2, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment3, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment4, kEntityPlayer, kObjectLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment5, kEntityPlayer, kObjectLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment6, kEntityPlayer, kObjectLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment7, kEntityPlayer, kObjectLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartment8, kEntityPlayer, kObjectLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentA, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentB, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentC, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentD, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentE, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentF, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentG, kEntityPlayer, kObjectLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectCompartmentH, kEntityPlayer, kObjectLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleBathroom, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleInsideBathroom, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectKitchen, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject20, kEntityPlayer, kObjectLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject21, kEntityPlayer, kObjectLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject22, kEntityPlayer, kObjectLocation3, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject48, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject49, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject50, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject51, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject52, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject53, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleOutsideLeft, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObjectHandleOutsideRight, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);

		getProgress().field_18 = 1;
		getProgress().field_84 = 1;
		getProgress().portrait = kCursorPortraitYellow;

		getInventory()->unselectItem();

		getInventory()->removeItem(kItemKey);
		getInventory()->removeItem(kItemBomb);
		getInventory()->removeItem(kItemMatch);

		if (getInventory()->hasItem(kItemFirebird)) {
			getInventory()->removeItem(kItemFirebird);
			getInventory()->setLocationAndProcess(kItemFirebird, kObjectLocation3);

			if (getInventory()->hasItem(kItemWhistle)) {
				getInventory()->removeItem(kItemWhistle);
				getInventory()->setLocationAndProcess(kItemWhistle, kObjectLocation3);
			}
		}

		getObjects()->update(kObject93, kEntityPlayer, kObjectLocation2, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject94, kEntityPlayer, kObjectLocationNone, kCursorKeepValue, kCursorKeepValue);
		getObjects()->update(kObject101, kEntityPlayer, kObjectLocationNone, kCursorHandKnock, kCursorHand);

		getObjects()->updateLocation2(kObject98, kObjectLocation2);
		getObjects()->updateLocation2(kObjectRestaurantCar, kObjectLocation2);

		if (ENTITY_PARAM(0, 2) || ENTITY_PARAM(0, 3)) {
			getSound()->removeFromQueue(kEntityChapters);
			ENTITY_PARAM(0, 2) = 0;
			ENTITY_PARAM(0, 3) = 0;
		}

		getScenes()->loadSceneFromPosition(kCarBaggageRear, 95);
		getInventory()->show();

		setCallback(1);
		setup_savegame(kSavegameTypeTime, kTimeNone);
		break;

	case kActionCallback:
		if (getCallback() == 1)
			setup_chapter5Handler();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_FUNCTION(22, Chapters, chapter5Handler)
	switch (savepoint.action) {
	default:
		break;

	case kActionNone:
		if (getState()->time > kTime2907000 && !params->param2) {
			params->param2 = 1;

			if (!getProgress().isNightTime) {
				getSound()->playSound(kEntityChapters, "ARRIVE", SoundManager::kFlag8);
				getSound()->processEntries();
			}
		}

		if (getState()->time > kTimeTrainStopped2 && !params->param3) {
			params->param3 = 1;

			if (!getEvent(kEventLocomotiveMilos) && !getEvent(kEventLocomotiveMilosNight)) {
				getSound()->playSound(kEntityChapters, "ARRIVE", SoundManager::kFlag8);
				getSound()->processEntries();
			}
		}
		break;

	case kAction2:
		if (getState()->time <= kTimeTrainStopped2) {
			setCallback(1);
			setup_savegame(kSavegameTypeEvent, kEventTrainStopped);
		} else {
			getLogic()->gameOver(kSavegameTypeTime, kTimeTrainStopped2, kSceneGameOverTrainStopped, true);
		}
		break;

	case kActionDefault:
		params->param1 = 225 * (4 * rnd(10) + 20);
		break;

	case kActionCallback:
		if (getCallback() == 1) {
			getAction()->playAnimation(kEventTrainStopped);
			getLogic()->gameOver(kSavegameTypeTime, kTimeTrainStopped, kSceneGameOverTrainStopped, true);
		}
		break;

	case kAction135800432:
		getProgress().isNightTime = true;
		getState()->time = kTime2916000;

		if (getSound()->isBuffered(kEntityChapters))
			getSound()->removeFromQueue(kEntityChapters);
		break;
	}
}


//////////////////////////////////////////////////////////////////////////
// Private functions
//////////////////////////////////////////////////////////////////////////
void Chapters::enterExitStation(const SavePoint &savepoint, bool isEnteringStation) {
	if (savepoint.action == kActionDefault) {
		if (!ENTITY_PARAM(0, 2) && !ENTITY_PARAM(0, 3)) {
			enterExitHelper(isEnteringStation);
			return;
		}

		getSound()->removeFromQueue(kEntityChapters);

		if (!ENTITY_PARAM(0, 2)) {
			if (ENTITY_PARAM(0, 3))
				ENTITY_PARAM(0, 3) = 0;

			enterExitHelper(isEnteringStation);
			return;
		}

		getSavePoints()->push(kEntityChapters, kEntityTrain, kActionTrainStopRunning);

		if (getEntityData(kEntityPlayer)->location != kLocationOutsideTrain) {
			ENTITY_PARAM(0, 2) = 0;
			enterExitHelper(isEnteringStation);
			return;
		}

		// Green sleeping car
		if (getEntities()->isOutsideAlexeiWindow()) {
			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 49);
			ENTITY_PARAM(0, 2) = 0;
			enterExitHelper(isEnteringStation);
			return;
		}

		// Red sleeping car
		if (getEntities()->isOutsideAnnaWindow()) {
			getScenes()->loadSceneFromPosition(kCarRedSleeping, 49);
			ENTITY_PARAM(0, 2) = 0;
			enterExitHelper(isEnteringStation);
			return;
		}

		// Other cars
		if (getEntityData(kEntityPlayer)->car < kCarRedSleeping || getEntityData(kEntityPlayer)->car > kCarCoalTender) {

			if (getEntityData(kEntityPlayer)->car < kCarBaggageRear || getEntityData(kEntityPlayer)->car > kCarGreenSleeping) {
				ENTITY_PARAM(0, 2) = 0;
				enterExitHelper(isEnteringStation);
				return;
			}

			if (getEntities()->isPlayerPosition(kCarGreenSleeping, 98)) {
				getSound()->playSound(kEntityPlayer, "LIB015");
				getScenes()->loadSceneFromPosition(kCarGreenSleeping, 71);
				ENTITY_PARAM(0, 2) = 0;
				enterExitHelper(isEnteringStation);
				return;
			}

			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 82);
			ENTITY_PARAM(0, 2) = 0;
			enterExitHelper(isEnteringStation);
			return;
		}

		getScenes()->loadSceneFromPosition(kCarRestaurant, 82);
		ENTITY_PARAM(0, 2) = 0;
		enterExitHelper(isEnteringStation);
	}
}

//////////////////////////////////////////////////////////////////////////
void Chapters::enterExitHelper(bool isEnteringStation) {
	EXPOSE_PARAMS(EntityData::EntityParametersSIIS);

	getSound()->playSound(kEntityChapters, isEnteringStation ? "ARRIVE" : "DEPART", SoundManager::kFlag8);
	getSound()->processEntries();

	getObjects()->update(kObjectHandleOutsideLeft, kEntityPlayer, kObjectLocation1, kCursorNormal, isEnteringStation ? kCursorNormal : kCursorHand);
	getObjects()->update(kObjectHandleOutsideRight, kEntityPlayer, kObjectLocation1, kCursorNormal, isEnteringStation ? kCursorNormal : kCursorHand);

	getProgress().isTrainRunning = isEnteringStation ? false : true;

	if (isEnteringStation) {
		ENTITY_PARAM(0, 2) = 1;
		ENTITY_PARAM(0, 4) = params->param4;
	} else {
		getSavePoints()->push(kEntityChapters, kEntityTrain, kActionTrainStartRunning);
		ENTITY_PARAM(0, 3) = 1;
	}

	CALLBACK_ACTION();
}

} // End of namespace LastExpress
