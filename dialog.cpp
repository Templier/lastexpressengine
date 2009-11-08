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

#include "lastexpress/dialog.h"

#include "lastexpress/action.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/logic.h"

namespace LastExpress {

Dialog::Dialog(LastExpressEngine *engine) : _engine(engine) {}

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

		if (getEvent(Action::kAnnaGiveScarf) || getEvent(Action::kAnnaGiveScarfDiner) || getEvent(Action::kAnnaGiveScarfRestaurant)
		 || getEvent(Action::kAnnaGiveScarfMonogram) || getEvent(Action::kAnnaGiveScarfDinerMonogram) || getEvent(Action::kAnnaGiveScarfRestaurantMonogram))
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

		if (getProgress().field_6C)
			return "XAUG1";

		break;

	case kDialogTatiana:
	/*	if (getEvent(Action::))
			return "";*/
	case kDialogVassili:
	case kDialogAlexei:
	case kDialogAbbot:
	case kDialogMilos:
	case kDialogVesna:
	case kDialogKronos:
	case kDialogFrancois:
	case kDialogMadameBoutarel:
	case kDialog22:
	case kDialogRebecca:
	case kDialogSophie:
	case kDialogMahmud:
	case kDialogHarem2:
	case kDialogHarem1:
	case kDialogHarem3:
	case kDialogHarem4:
	case kDialogTyler:
		error("Dialog::getDialog: unsupported dialog id (%d)", id);

	default:
		return NULL;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
// Sound bites
//////////////////////////////////////////////////////////////////////////
const char *Dialog::excuseMe() {
	switch(_engine->getRandom().getRandomNumber(3)) {
	case 0:
		return "CAT1126B";
	case 1:
		return "CAT1126C";
	case 2:
		return "CAT1126D";
	}

	return "CAT1126B";
}

const char *Dialog::justChecking() {
	switch(_engine->getRandom().getRandomNumber(4)) {
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

const char *Dialog::wrongDoor() {
	switch(_engine->getRandom().getRandomNumber(5)) {
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

const char *Dialog::justAMinute() {
	switch(_engine->getRandom().getRandomNumber(3)) {
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
