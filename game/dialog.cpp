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

#include "lastexpress/game/dialog.h"

#include "lastexpress/game/action.h"
#include "lastexpress/game/logic.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

// Letters & messages
const char *messages[24] = {
	"",
	"TXT1001",	// 1
	"TXT1001A",	// 2
	"TXT1011",	// 3
	"TXT1012",	// 4
	"TXT1013",	// 5
	"TXT1014",	// 6
	"TXT1020",	// 7
	"TXT1030",	// 8
	"END1009B",	// 50
	"END1046",	// 51
	"END1047",	// 52
	"END1112",	// 53
	"END1112A",	// 54
	"END1503",	// 55
	"END1505A",	// 56
	"END1505B",	// 57
	"END1610",	// 58
	"END1612A",	// 59
	"END1612C", // 61
	"END1612D", // 62
	"ENDALRM1", // 63
	"ENDALRM2", // 64
	"ENDALRM3"  // 65
};

Dialog::Dialog(LastExpressEngine *engine) : _engine(engine), sound_name(NULL) {}

Dialog::~Dialog() {
	delete[] sound_name;
}

const char *Dialog::getSound(int index, byte action, byte a3) {
	delete[] sound_name;
	sound_name = new char[7];

	int values[5];

	// TODO:
	// - check entities (0 against current)
	// - check index against entity values
	// - more checks

	switch (action) {
	case 36:
	case 37:
		error("Dialog::getSound: action not implemented (%d)", action);

	case 150:
	case 156:
	case 162:
	case 168:
	case 188:
	case 198:
		action += 1 + random(5);
		break;

	case 174:
	case 184:
	case 194:
		action += 1 + random(3);
		break;

	case 180:
		action += 1 + random(4);
		break;

	case 246:
		values[0] = 0;
		values[1] = 104;
		values[2] = 105;
		values[3] = 106;
		values[4] = 116;
		action = values[random(5)];
		break;

	case 247:
		values[0] = 11;
		values[1] = 123;
		values[2] = 124;
		action = values[random(3)];
		break;

	case 248:
		values[0] = 0;
		values[1] = 103;
		values[2] = 108;
		values[3] = 109;
		action = values[random(4)];
		break;

	case 249:
		values[0] = 0;
		values[1] = 56;
		values[2] = 112;
		values[3] = 113;
		action = values[random(4)];
		break;

	case 250:
		values[0] = 0;
		values[1] = 107;
		values[2] = 115;
		values[3] = 117;
		action = values[random(4)];
		break;

	case 251:
		values[0] = 0;
		values[1] = 11;
		values[2] = 56;
		values[3] = 113;
		action = values[random(4)];
		break;

	case 252:
		values[0] = 0;
		values[1] = 6;
		values[2] = 109;
		values[3] = 121;
		action = values[random(4)];
		break;

	case 254:
		values[0] = 0;
		values[1] = 104;
		values[2] = 120;
		values[3] = 121;
		action = values[random(4)];
		break;

	case 255:
		values[0] = 0;
		values[1] = 106;
		values[2] = 115;
		action = values[random(3)];
		break;

	default:
		break;		
	}

	if (!action)
		return "";

	sprintf(sound_name, "LIB%03d", action);

	return sound_name;
}

const char *Dialog::getDialog(DialogId id) {
	switch (id) {
	case kDialogAnna:
		if (getEvent(Action::kAnnaDialogGoToJerusalem))
			return "XANN12";

		if (getEvent(Action::kLocomotiveRestartTrain))
			return "XANN11";

		if (getEvent(Action::kAnnaBagageTies) || getEvent(Action::kAnnaBagageTies2) || getEvent(Action::kAnnaBagageTies3) || getEvent(Action::kAnnaBagageTies4))
			return "XANN10";

		if (getEvent(Action::kAnnaTired) || getEvent(Action::kAnnaTiredKiss))
			return "XANN9";

		if (getEvent(Action::kAnnaBagageArgument))
			return "XANN8";

		if (getEvent(Action::kKronosVisit))
			return "XANN7";

		if (getEvent(Action::kAbbotIntroduction))
			return "XANN6A";

		if (getEvent(Action::kVassiliSeizure))
			return "XANN6";

		if (getEvent(Action::kAugustPresentAnna) || getEvent(Action::kAugustPresentAnnaFirstIntroduction))
			return "XANN5";

		if (getProgress().field_60)
			return "XANN4";

		if (getEvent(Action::kAnnaGiveScarf) || getEvent(Action::kAnnaGiveScarfDiner) || getEvent(Action::kAnnaGiveScarfSalon)
		 || getEvent(Action::kAnnaGiveScarfMonogram) || getEvent(Action::kAnnaGiveScarfDinerMonogram) || getEvent(Action::kAnnaGiveScarfSalonMonogram))
			return "XANN3";

		if (getEvent(Action::kDinerMindJoin))
			return "XANN2";

		if (getEvent(Action::kGotALight) || getEvent(Action::kGotALightD))
			return "XANN1";

		break;

	case kDialogAugust:
		if (getEvent(Action::kAugustTalkCigar))
			return "XAUG6";

		if (getEvent(Action::kAugustBringBriefcase))
			return "XAUG5";

		// Getting closer to Vienna...
		if (getState()->time > 2200500 && !getEvent(Action::kAugustMerchandise))
			return "XAUG4A";

		if (getEvent(Action::kAugustMerchandise))
			return "XAUG4";

		if (getEvent(Action::kDinerAugust) || getEvent(Action::kDinerAugustAlexeiBackground) || getEvent(Action::kMeetAugustTylerCompartment)
		 || getEvent(Action::kMeetAugustTylerCompartmentBed) || getEvent(Action::kMeetAugustHisCompartment) || getEvent(Action::kMeetAugustHisCompartmentBed))
			return "XAUG3";

		if (getEvent(Action::kAugustPresentAnnaFirstIntroduction))
			return "XAUG2";

		if (getProgress().event_mertens_august_waiting)
			return "XAUG1";

		break;

	case kDialogTatiana:
		if (getEvent(Action::kTatianaTylerCompartment))
			return "XTAT6";

		if (getEvent(Action::kTatianaCompartmentStealEgg))
			return "XTAT5";

		if (getEvent(Action::kTatianaGivePoem))
			return "XTAT3";

		if (getProgress().field_64)
			return "XTAT1";

		break;

	case kDialogVassili:
		if (getEvent(Action::kCathFreePassengers))
			return "XVAS4";

		if (getEvent(Action::kVassiliCompartmentStealEgg))
			return "XVAS3";

		if (getEvent(Action::kAbbotIntroduction))
			return "XVAS2";

		if (getEvent(Action::kVassiliSeizure))
			return "XVAS1A";

		if (getProgress().field_64)
			return "XVAS1";

		break;

	case kDialogAlexei:
		if (getProgress().field_88)
			return "XALX6";

		if (getProgress().field_8C)
			return "XALX5";

		if (getProgress().field_90)
			return "XALX4A";

		if (getProgress().field_68)
			return "XALX4";

		if (getEvent(Action::kAlexeiSalonPoem))
			return "XALX3";

		if (getEvent(Action::kAlexeiSalonVassili))
			return "XALX2";

		if (getEvent(Action::kAlexeiDiner) || getEvent(Action::kAlexeiDinerOriginalJacket))
			return "XALX1";

		break;

	case kDialogAbbot:
		if (getEvent(Action::kAbbotDrinkDefuse))
			return "XABB4";

		if (getEvent(Action::kAbbotInvitationDrink) || getEvent(Action::kDefuseBomb))
			return "XABB3";

		if (getEvent(Action::kAbbotWrongCompartment) || getEvent(Action::kAbbotWrongCompartmentBed))
			return "XABB2";

		if (getEvent(Action::kAbbotIntroduction))
			return "XABB1";

		break;

	case kDialogMilos:
		if (getEvent(Action::kLocomotiveMilos) || getEvent(Action::kLocomotiveMilosNight))
			return "XMIL5";

		if (getEvent(Action::kMilosCompartmentVisitTyler) && (getProgress().index == 3 || getProgress().index == 4))
			return "XMIL4";

		if (getEvent(Action::kMilosCorridorThanks) || getProgress().index == 5)
			return "XMIL3";

		if (getEvent(Action::kMilosCompartmentVisitAugust))
			return "XMIL2";

		if (getEvent(Action::kMilosTylerCompartmentDefeat))
			return "XMIL1";

		break;

	case kDialogVesna:
		if (getProgress().field_94)
			return "XVES2";

		if (getProgress().field_98)
			return "XVES1";

		break;

	case kDialogKronos:
		if (getEvent(Action::kKronosReturnBriefcase))
			return "XKRO6";

		if (getEvent(Action::kKronosBringEggCeiling) || getEvent(Action::kKronosBringEgg))
			return "XKRO5";

		if (getEvent(Action::kKronosConversation) || getEvent(Action::kKronosConversationFirebird)) {
			byte location = getInventory()->getItem(Inventory::kFirebird)->location;
			if (location != 6 && location != 5 && location != 2 && location != 1)
				return "XKRO4A";
		}

		if (getEvent(Action::kKronosConversationFirebird))
			return "XKRO4";

		if (getEvent(Action::kKronosConversation)) {
			if (!getEvent(Action::kMilosCompartmentVisitAugust))	
				return "XKRO3";
			else
				return "XKRO2";
		}

		if (getProgress().event_mertens_chronos_invitation)
			return "XKRO1";

		break;

	case kDialogFrancois:
		if (getProgress().field_9C)
			return "XFRA3";

		if (getProgress().field_A0 
		 || getEvent(Action::kFrancoisWhistle) || getEvent(Action::kFrancoisWhistleD)
		 || getEvent(Action::kFrancoisWhistleNight) || getEvent(Action::kFrancoisWhistleNightD))
			return "XFRA2";

		if (getState()->time > 1075500) // Between Paris and Epernay
			return "XFRA1";

		break;

	case kDialogMadameBoutarel:
		if (getProgress().field_A4)
			return "XMME4";

		if (getProgress().field_A8)
			return "XMME3";

		if (getProgress().field_A0)
			return "XMME2";

		if (getProgress().field_AC)
			return "XMME1";

		break;

	case kDialog22:
		if (getProgress().field_D0)
			return "XMRB1";

		break;

	case kDialogRebecca:
		if (getProgress().field_B4)
			return "XREB1A";

		if (getProgress().field_B8)
			return "XREB1";

		break;

	case kDialogSophie:
		if (getProgress().field_B0)
			return "XSOP2";

		if (getProgress().field_BC)
			return "XSOP1B";

		if (getProgress().field_B4)
			return "XSOP1A";

		if (getProgress().field_B8)
			return "XSOP1";

		break;

	case kDialogMahmud:
		if (getProgress().field_C4)
			return "XMAH1";

		break;

	case kDialogHarem2:
		if (getProgress().field_D8)
			return "XHAR2";

		break;

	case kDialogHarem1:
		if (getProgress().field_D4)
			return "XHAR1";

		break;

	case kDialogHarem3:
		if (getProgress().field_DC)
			return "XHAR3";

		break;

	case kDialogHarem4:
		if (getProgress().field_E0)
			return "XHAR4";

		break;

	case kDialogTyler:
		if (getEvent(Action::kCathDream) || getEvent(Action::kCathWakingUp))
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
const char *Dialog::readText(int id) {
	// names are stored in sequence in the array but id is [1;8] - [50;64]
	return messages[id <= 8 ? id : id - 41];
}

//////////////////////////////////////////////////////////////////////////
// Sound bites
//////////////////////////////////////////////////////////////////////////
const char *Dialog::excuseMeCath() {
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

const char *Dialog::justCheckingCath() {
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

const char *Dialog::wrongDoorCath() {
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

const char *Dialog::justAMinuteCath() {
	switch(random(3)) {
	case 0:
		return "CAT1520";
	case 1:
		return "CAT1521";
	case 2:
		return "CAT1125";	// ?? is this a bug in the original?
	}

	return "CAT1520";
}


} // End of namespace LastExpress
