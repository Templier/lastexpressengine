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

#include "lastexpress/game/sound.h"

#include "lastexpress/data/snd.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

// Letters & messages
const char *messages[24] = {
	"",
	"TXT1001",  // 1
	"TXT1001A", // 2
	"TXT1011",  // 3
	"TXT1012",  // 4
	"TXT1013",  // 5
	"TXT1014",  // 6
	"TXT1020",  // 7
	"TXT1030",  // 8
	"END1009B", // 50
	"END1046",  // 51
	"END1047",  // 52
	"END1112",  // 53
	"END1112A", // 54
	"END1503",  // 55
	"END1505A", // 56
	"END1505B", // 57
	"END1610",  // 58
	"END1612A", // 59
	"END1612C", // 61
	"END1612D", // 62
	"ENDALRM1", // 63
	"ENDALRM2", // 64
	"ENDALRM3"  // 65
};

Sound::Sound(LastExpressEngine *engine) : _engine(engine) {
	_sfx = new StreamedSound();
	_music = new StreamedSound();
}

Sound::~Sound() {
	delete _sfx;
	delete _music;
}

//////////////////////////////////////////////////////////////////////////
// Sound queue management
//////////////////////////////////////////////////////////////////////////

void Sound::reset(EntityIndex entity) {
	error("SoundManager::reset: not implemented!");
}

bool Sound::isBuffered(EntityIndex entityIndex) {
	warning("SoundManager::isBuffered: not implemented!");
	return false;
}

bool Sound::isFileInQueue(const char* filename) {
	warning("SoundManager::isFileInQueue: not implemented!");
	return false;
}

void Sound::unknownFunction1() {
	error("SoundManager::unknownFunction1: not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Game-related functions
//////////////////////////////////////////////////////////////////////////

void Sound::playSound(EntityIndex entity, const char *filename, int a3, byte a4) {
	warning("Sound::playSound: no implemented!");

	playSfxStream(filename);
}

void Sound::playMusic(EntityIndex entity, byte id, int a3, byte a4) {
	char filename[7];
	sprintf((char *)&filename, "MUS%03d", id);

	playSound(entity, filename, a3, a4);
}

void Sound::playSoundEvent(int index, byte action, byte a3) {
	char sound_name[7];
	int values[5];

	// TODO:
	// - check entities (0 against current)
	// - check index against entity values
	// - more checks

	int _action = (int)action;

	switch (action) {
	case 36:
	case 37:
		warning("Dialog::playSoundEvent: action not implemented (%d)", action);

	case 150:
	case 156:
	case 162:
	case 168:
	case 188:
	case 198:
		_action += 1 + random(5);
		break;

	case 174:
	case 184:
	case 194:
		_action += 1 + random(3);
		break;

	case 180:
		_action += 1 + random(4);
		break;

	case 246:
		values[0] = 0;
		values[1] = 104;
		values[2] = 105;
		values[3] = 106;
		values[4] = 116;
		_action = values[random(5)];
		break;

	case 247:
		values[0] = 11;
		values[1] = 123;
		values[2] = 124;
		_action = values[random(3)];
		break;

	case 248:
		values[0] = 0;
		values[1] = 103;
		values[2] = 108;
		values[3] = 109;
		_action = values[random(4)];
		break;

	case 249:
		values[0] = 0;
		values[1] = 56;
		values[2] = 112;
		values[3] = 113;
		_action = values[random(4)];
		break;

	case 250:
		values[0] = 0;
		values[1] = 107;
		values[2] = 115;
		values[3] = 117;
		_action = values[random(4)];
		break;

	case 251:
		values[0] = 0;
		values[1] = 11;
		values[2] = 56;
		values[3] = 113;
		_action = values[random(4)];
		break;

	case 252:
		values[0] = 0;
		values[1] = 6;
		values[2] = 109;
		values[3] = 121;
		_action = values[random(4)];
		break;

	case 254:
		values[0] = 0;
		values[1] = 104;
		values[2] = 120;
		values[3] = 121;
		_action = values[random(4)];
		break;

	case 255:
		values[0] = 0;
		values[1] = 106;
		values[2] = 115;
		_action = values[random(3)];
		break;

	default:
		break;
	}

	if (_action) {
		sprintf((char *)&sound_name, "LIB%03d", _action);

		if (_engine->getResourceManager()->hasFile(Common::String((char*)&sound_name) + ".snd"))
			playSfxStream((char*)&sound_name);
	}
}

void Sound::playDialog(EntityIndex entity, EntityIndex entityDialog, int a3, byte a4) {
	playSound(entity, getDialogName(entityDialog), a3, a4);
}

const char *Sound::getDialogName(EntityIndex entity) {
	switch (entity) {
	case kEntityAnna:
		if (getEvent(kEventAnnaDialogGoToJerusalem))
			return "XANN12";

		if (getEvent(kEventLocomotiveRestartTrain))
			return "XANN11";

		if (getEvent(kEventAnnaBagageTies) || getEvent(kEventAnnaBagageTies2) || getEvent(kEventAnnaBagageTies3) || getEvent(kEventAnnaBagageTies4))
			return "XANN10";

		if (getEvent(kEventAnnaTired) || getEvent(kEventAnnaTiredKiss))
			return "XANN9";

		if (getEvent(kEventAnnaBagageArgument))
			return "XANN8";

		if (getEvent(kEventKronosVisit))
			return "XANN7";

		if (getEvent(kEventAbbotIntroduction))
			return "XANN6A";

		if (getEvent(kEventVassiliSeizure))
			return "XANN6";

		if (getEvent(kEventAugustPresentAnna) || getEvent(kEventAugustPresentAnnaFirstIntroduction))
			return "XANN5";

		if (getProgress().field_60)
			return "XANN4";

		if (getEvent(kEventAnnaGiveScarf) || getEvent(kEventAnnaGiveScarfDiner) || getEvent(kEventAnnaGiveScarfSalon)
		 || getEvent(kEventAnnaGiveScarfMonogram) || getEvent(kEventAnnaGiveScarfDinerMonogram) || getEvent(kEventAnnaGiveScarfSalonMonogram))
			return "XANN3";

		if (getEvent(kEventDinerMindJoin))
			return "XANN2";

		if (getEvent(kEventGotALight) || getEvent(kEventGotALightD))
			return "XANN1";

		break;

	case kEntityAugust:
		if (getEvent(kEventAugustTalkCigar))
			return "XAUG6";

		if (getEvent(kEventAugustBringBriefcase))
			return "XAUG5";

		// Getting closer to Vienna...
		if (getState()->time > 2200500 && !getEvent(kEventAugustMerchandise))
			return "XAUG4A";

		if (getEvent(kEventAugustMerchandise))
			return "XAUG4";

		if (getEvent(kEventDinerAugust) || getEvent(kEventDinerAugustAlexeiBackground) || getEvent(kEventMeetAugustTylerCompartment)
		 || getEvent(kEventMeetAugustTylerCompartmentBed) || getEvent(kEventMeetAugustHisCompartment) || getEvent(kEventMeetAugustHisCompartmentBed))
			return "XAUG3";

		if (getEvent(kEventAugustPresentAnnaFirstIntroduction))
			return "XAUG2";

		if (getProgress().event_mertens_august_waiting)
			return "XAUG1";

		break;

	case kEntityTatiana:
		if (getEvent(kEventTatianaTylerCompartment))
			return "XTAT6";

		if (getEvent(kEventTatianaCompartmentStealEgg))
			return "XTAT5";

		if (getEvent(kEventTatianaGivePoem))
			return "XTAT3";

		if (getProgress().field_64)
			return "XTAT1";

		break;

	case kEntityVassili:
		if (getEvent(kEventCathFreePassengers))
			return "XVAS4";

		if (getEvent(kEventVassiliCompartmentStealEgg))
			return "XVAS3";

		if (getEvent(kEventAbbotIntroduction))
			return "XVAS2";

		if (getEvent(kEventVassiliSeizure))
			return "XVAS1A";

		if (getProgress().field_64)
			return "XVAS1";

		break;

	case kEntityAlexei:
		if (getProgress().field_88)
			return "XALX6";

		if (getProgress().field_8C)
			return "XALX5";

		if (getProgress().field_90)
			return "XALX4A";

		if (getProgress().field_68)
			return "XALX4";

		if (getEvent(kEventAlexeiSalonPoem))
			return "XALX3";

		if (getEvent(kEventAlexeiSalonVassili))
			return "XALX2";

		if (getEvent(kEventAlexeiDiner) || getEvent(kEventAlexeiDinerOriginalJacket))
			return "XALX1";

		break;

	case kEntityAbbot:
		if (getEvent(kEventAbbotDrinkDefuse))
			return "XABB4";

		if (getEvent(kEventAbbotInvitationDrink) || getEvent(kEventDefuseBomb))
			return "XABB3";

		if (getEvent(kEventAbbotWrongCompartment) || getEvent(kEventAbbotWrongCompartmentBed))
			return "XABB2";

		if (getEvent(kEventAbbotIntroduction))
			return "XABB1";

		break;

	case kEntityMilos:
		if (getEvent(kEventLocomotiveMilos) || getEvent(kEventLocomotiveMilosNight))
			return "XMIL5";

		if (getEvent(kEventMilosCompartmentVisitTyler) && (getProgress().chapter == kChapter3 || getProgress().chapter == kChapter4))
			return "XMIL4";

		if (getEvent(kEventMilosCorridorThanks) || getProgress().chapter == kChapter5)
			return "XMIL3";

		if (getEvent(kEventMilosCompartmentVisitAugust))
			return "XMIL2";

		if (getEvent(kEventMilosTylerCompartmentDefeat))
			return "XMIL1";

		break;

	case kEntityVesna:
		if (getProgress().field_94)
			return "XVES2";

		if (getProgress().field_98)
			return "XVES1";

		break;

	case kEntityKronos:
		if (getEvent(kEventKronosReturnBriefcase))
			return "XKRO6";

		if (getEvent(kEventKronosBringEggCeiling) || getEvent(kEventKronosBringEgg))
			return "XKRO5";

		if (getEvent(kEventKronosConversation) || getEvent(kEventKronosConversationFirebird)) {
			ObjectLocation location = getInventory()->getEntry(kItemFirebird)->location;
			if (location != kLocation6 && location != kLocation5 && location != kLocation2 && location != kLocation1)
				return "XKRO4A";
		}

		if (getEvent(kEventKronosConversationFirebird))
			return "XKRO4";

		if (getEvent(kEventKronosConversation)) {
			if (!getEvent(kEventMilosCompartmentVisitAugust))
				return "XKRO3";
			else
				return "XKRO2";
		}

		if (getProgress().event_mertens_chronos_invitation)
			return "XKRO1";

		break;

	case kEntityFrancois:
		if (getProgress().field_9C)
			return "XFRA3";

		if (getProgress().field_A0
		 || getEvent(kEventFrancoisWhistle) || getEvent(kEventFrancoisWhistleD)
		 || getEvent(kEventFrancoisWhistleNight) || getEvent(kEventFrancoisWhistleNightD))
			return "XFRA2";

		if (getState()->time > 1075500) // Between Paris and Epernay
			return "XFRA1";

		break;

	case kEntityMmeBoutarel:
		if (getProgress().field_A4)
			return "XMME4";

		if (getProgress().field_A8)
			return "XMME3";

		if (getProgress().field_A0)
			return "XMME2";

		if (getProgress().field_AC)
			return "XMME1";

		break;

	case kEntityBoutarel:
		if (getProgress().event_met_boutarel)
			return "XMRB1";

		break;

	case kEntityRebecca:
		if (getProgress().field_B4)
			return "XREB1A";

		if (getProgress().field_B8)
			return "XREB1";

		break;

	case kEntitySophie:
		if (getProgress().field_B0)
			return "XSOP2";

		if (getProgress().field_BC)
			return "XSOP1B";

		if (getProgress().field_B4)
			return "XSOP1A";

		if (getProgress().field_B8)
			return "XSOP1";

		break;

	case kEntityMahmud:
		if (getProgress().field_C4)
			return "XMAH1";

		break;

	case kEntityYasmin:
		if (getProgress().event_met_yasmin)
			return "XHAR2";

		break;

	case kEntityHadija:
		if (getProgress().event_met_hadija)
			return "XHAR1";

		break;

	case kEntityAlouan:
		if (getProgress().field_DC)
			return "XHAR3";

		break;

	case kEntityGendarmes:
		if (getProgress().field_E0)
			return "XHAR4";

		break;

	case kEntityChapters:
		if (getEvent(kEventCathDream) || getEvent(kEventCathWakingUp))
			return "XTYL3";

		return "XTYL1";

	default:
		break;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
// Letters & Messages
//////////////////////////////////////////////////////////////////////////
const char *Sound::readText(int id) {
	// names are stored in sequence in the array but id is [1;8] - [50;64]
	return messages[id <= 8 ? id : id - 41];
}

//////////////////////////////////////////////////////////////////////////
// Sound bites
//////////////////////////////////////////////////////////////////////////
void Sound::excuseMe(EntityIndex entity, int param2, int param3) {
	if (entity == kEntityNone || entity == kEntityChapters || entity == kEntityTrain)
		return;

	if (param2 == 20 || param2 == 30)
		return;

	if (entity == kEntityFrancois && getEntityData(kEntityFrancois)->field_4A3 == 30)
		return;

	if (!param3) {
		error("Sound::excuseMe: not implemented!");
	}

	switch (entity) {
	default:
		break;

	case kEntityAnna:
		playSound(kEntityNone, "ANN1107A", param3, 0);
		break;

	case kEntityAugust:
		switch(random(4)) {
		default:
			break;

		case 0:
			playSound(kEntityNone, "AUG1100A", param3, 0);
			break;

		case 1:
			playSound(kEntityNone, "AUG1100B", param3, 0);
			break;

		case 2:
			playSound(kEntityNone, "AUG1100C", param3, 0);
			break;

		case 3:
			playSound(kEntityNone, "AUG1100D", param3, 0);
			break;
		}
		break;

	case kEntityMertens:
		if (testParameter(param2)) {
			playSound(kEntityNone, (random(2) ? "CON1111" : "CON1111A"), param3, 0);
		} else {
			if (param2 || getProgress().jacket != kJacketGreen || !random(2)) {
				switch(random(3)) {
				default:
					break;

				case 0:
					playSound(kEntityNone, "CON1110A", param3, 0);
					break;

				case 1:
					playSound(kEntityNone, "CON1110C", param3, 0);
					break;

				case 2:
					playSound(kEntityNone, "CON1110", param3, 0);
					break;
				}
			} else {
				if (isDay()) {
					playSound(kEntityNone, (getProgress().field_18 == 2 ? "CON1110F" : "CON1110E"));
				} else {
					playSound(kEntityNone, "CON1110D");
				}
			}
		}
		break;

	case kEntityCoudert:
		if (testParameter(param2)) {
			playSound(kEntityNone, "JAC1111D", param3, 0);
		} else {
			if (param2 || getProgress().jacket != kJacketGreen || !random(2)) {
				switch(random(4)) {
				default:
					break;

				case 0:
					playSound(kEntityNone, "JAC1111", param3, 0);
					break;

				case 1:
					playSound(kEntityNone, "JAC1111A", param3, 0);
					break;

				case 2:
					playSound(kEntityNone, "JAC1111B", param3, 0);
					break;

				case 3:
					playSound(kEntityNone, "JAC1111C", param3, 0);
					break;
				}
			} else {
				playSound(kEntityNone, "JAC1113B", param3, 0);
			}
		}
		break;

	case kEntityPascale:
		playSound(kEntityNone, (random(2) ? "HDE1002" : "HED1002A"), param3, 0);
		break;

	case kEntityServers0:
	case kEntityServers1:
		switch(random(3)) {
		default:
			break;

		case 0:
			playSound(kEntityNone, (entity == kEntityServers0) ? "WAT1002" : "WAT1003", param3, 0);
			break;

		case 1:
			playSound(kEntityNone, (entity == kEntityServers0) ? "WAT1002A" : "WAT1003A", param3, 0);
			break;

		case 2:
			playSound(kEntityNone, (entity == kEntityServers0) ? "WAT1002B" : "WAT1003B", param3, 0);
			break;
		}
		break;

	case kEntityVerges:
		if (testParameter(param2)) {
			playSound(kEntityNone, (random(2) ? "TRA1113A" : "TRA1113B"));
		} else {
			playSound(kEntityNone, "TRA1112", param3, 0);
		}
		break;

	case kEntityTatiana:
		playSound(kEntityNone, (random(2) ? "TAT1102A" : "TAT1102B"), param3, 0);
		break;

	case kEntityAlexei:
		playSound(kEntityNone, (random(2) ? "ALX1099C" : "ALX1099D"), param3, 0);
		break;

	case kEntityAbbot:
		if (testParameter(param2)) {
			playSound(kEntityNone, "ABB3002C", param3, 0);
		} else {
			switch(random(3)) {
			default:
				break;

			case 0:
				playSound(kEntityNone, "ABB3002", param3, 0);
				break;

			case 1:
				playSound(kEntityNone, "ABB3002A", param3, 0);
				break;

			case 2:
				playSound(kEntityNone, "ABB3002B", param3, 0);
				break;
			}
		}
		break;

	case kEntityVesna:
		switch(random(3)) {
		default:
			break;

		case 0:
			playSound(kEntityNone, "VES1109A", param3, 0);
			break;

		case 1:
			playSound(kEntityNone, "VES1109B", param3, 0);
			break;

		case 2:
			playSound(kEntityNone, "VES1109C", param3, 0);
			break;
		}
		break;

	case kEntityKahina:
		playSound(kEntityNone, (random(2) ? "KAH1001" : "KAH1001A"), param3, 0);
		break;

	case kEntityFrancois:
	case kEntityMmeBoutarel:
		switch(random(4)) {
		default:
			break;

		case 0:
			playSound(kEntityNone, (entity == kEntityFrancois) ? "FRA1001" : "MME1103A", param3, 0);
			break;

		case 1:
			playSound(kEntityNone, (entity == kEntityFrancois) ? "FRA1001A" : "MME1103B", param3, 0);
			break;

		case 2:
			playSound(kEntityNone, (entity == kEntityFrancois) ? "FRA1001B" : "MME1103C", param3, 0);
			break;

		case 3:
			playSound(kEntityNone, (entity == kEntityFrancois) ? "FRA1001C" : "MME1103D", param3, 0);
			break;
		}
		break;

	case kEntityBoutarel:
		playSound(kEntityNone, "MRB1104", param3, 0);
		if (param3 > 2)
			getProgress().event_met_boutarel = 1;
		break;

	case kEntityRebecca:
		playSound(kEntityNone, (random(2) ? "REB1106" : "REB110A"), param3, 0);
		break;

	case kEntitySophie: {
		bool param2Test = testParameter(param2);
		switch(random(3)) {
		default:
			break;

		case 0:
			playSound(kEntityNone, "SOP1105", param3, 0);
			break;

		case 1:
			playSound(kEntityNone, param2Test ? "SOP1105C" : "SOP1105A", param3, 0);
			break;

		case 2:
			playSound(kEntityNone, param2Test ? "SOP1105D" : "SOP1105B", param3, 0);
			break;
		}
		break;
	}

	case kEntityMahmud:
		playSound(kEntityNone, "MAH1101", param3, 0);
		break;

	case kEntityYasmin:
		playSound(kEntityNone, "HAR1002", param3, 0);
		if (param3 > 2)
			getProgress().event_met_yasmin = 1;
		break;

	case kEntityHadija:
		playSound(kEntityNone, (random(2) ? "HAR1001" : "HAR1001A"), param3, 0);
		if (param3 > 2)
			getProgress().event_met_hadija = 1;
		break;

	case kEntityAlouan:
		playSound(kEntityNone, "HAR1004", param3, 0);
		break;
	}
}

const char *Sound::excuseMeCath() {
	switch(random(3)) {
	case 0:
		return "CAT1126B";
	case 1:
		return "CAT1126C";
	case 2:
		return "CAT1126D";
	}

	return "CAT1126B";
}

const char *Sound::justCheckingCath() {
	switch(random(4)) {
	case 0:
		return "CAT5001";
	case 1:
		return "CAT5001A";
	case 2:
		return "CAT5001B";
	case 3:
		return "CAT5001C";
	}

	return "CAT5001";
}

const char *Sound::wrongDoorCath() {
	switch(random(5)) {
	case 0:
		return "CAT1125";
	case 1:
		return "CAT1125A";
	case 2:
		return "CAT1125B";
	case 3:
		return "CAT1125C";
	case 4:
		return "CAT1125D";
	}

	return "CAT1125";
}

const char *Sound::justAMinuteCath() {
	switch(random(3)) {
	case 0:
		return "CAT1520";
	case 1:
		return "CAT1521";
	case 2:
		return "CAT1125";    // ?? is this a bug in the original?
	}

	return "CAT1520";
}

//////////////////////////////////////////////////////////////////////////
// Tests
//////////////////////////////////////////////////////////////////////////
bool Sound::testParameter(int param) {
	return (param == 1 || param == 10 || param == 15 || param == 19 || param == 21 || param == 23 || param == 24 || param == 26 || param == 27 || param == 28);
}

} // End of namespace LastExpress
