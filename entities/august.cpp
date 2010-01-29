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

#include "lastexpress/entities/august.h"

#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"

namespace LastExpress {

August::August(LastExpressEngine *engine) : Entity(engine, kEntityAugust) {
	ADD_CALLBACK_FUNCTION(August, function1);
	ADD_CALLBACK_FUNCTION(August, function2);
	ADD_CALLBACK_FUNCTION(August, function3);
	ADD_CALLBACK_FUNCTION(August, function4);
	ADD_CALLBACK_FUNCTION(August, function5);
	ADD_CALLBACK_FUNCTION(August, function6);
	ADD_CALLBACK_FUNCTION(August, function7);
	ADD_CALLBACK_FUNCTION(August, function8);
	ADD_CALLBACK_FUNCTION(August, function9);
	ADD_CALLBACK_FUNCTION(August, function10);
	ADD_CALLBACK_FUNCTION(August, function11);
	ADD_CALLBACK_FUNCTION(August, function12);
	ADD_CALLBACK_FUNCTION(August, function13);
	ADD_CALLBACK_FUNCTION(August, function14);
	ADD_CALLBACK_FUNCTION(August, function15);
	ADD_CALLBACK_FUNCTION(August, function16);
	ADD_CALLBACK_FUNCTION(August, function17);
	ADD_CALLBACK_FUNCTION(August, function18);
	ADD_CALLBACK_FUNCTION(August, function19);
	ADD_CALLBACK_FUNCTION(August, function20);
	ADD_CALLBACK_FUNCTION(August, function21);
	ADD_CALLBACK_FUNCTION(August, chapter1);
	ADD_CALLBACK_FUNCTION(August, function23);
	ADD_CALLBACK_FUNCTION(August, function24);
	ADD_CALLBACK_FUNCTION(August, function25);
	ADD_CALLBACK_FUNCTION(August, function26);
	ADD_CALLBACK_FUNCTION(August, function27);
	ADD_CALLBACK_FUNCTION(August, function28);
	ADD_CALLBACK_FUNCTION(August, function29);
	ADD_CALLBACK_FUNCTION(August, restaurant);
	ADD_CALLBACK_FUNCTION(August, function31);
	ADD_CALLBACK_FUNCTION(August, function32);
	ADD_CALLBACK_FUNCTION(August, function33);
	ADD_CALLBACK_FUNCTION(August, function34);
	ADD_CALLBACK_FUNCTION(August, chapter2);	
	ADD_CALLBACK_FUNCTION(August, function36);
	ADD_CALLBACK_FUNCTION(August, function37);
	ADD_CALLBACK_FUNCTION(August, function38);
	ADD_CALLBACK_FUNCTION(August, function39);
	ADD_CALLBACK_FUNCTION(August, chapter3);
	ADD_CALLBACK_FUNCTION(August, function41);
	ADD_CALLBACK_FUNCTION(August, function42);
	ADD_CALLBACK_FUNCTION(August, function43);
	ADD_CALLBACK_FUNCTION(August, function44);
	ADD_CALLBACK_FUNCTION(August, function45);
	ADD_CALLBACK_FUNCTION(August, function46);
	ADD_CALLBACK_FUNCTION(August, function47);
	ADD_CALLBACK_FUNCTION(August, function48);
	ADD_CALLBACK_FUNCTION(August, function49);
	ADD_CALLBACK_FUNCTION(August, function50);
	ADD_CALLBACK_FUNCTION(August, function51);
	ADD_CALLBACK_FUNCTION(August, function52);
	ADD_CALLBACK_FUNCTION(August, function53);
	ADD_CALLBACK_FUNCTION(August, function54);
	ADD_CALLBACK_FUNCTION(August, function55);
	ADD_CALLBACK_FUNCTION(August, function56);
	ADD_CALLBACK_FUNCTION(August, chapter4);
	ADD_CALLBACK_FUNCTION(August, function58);
	ADD_CALLBACK_FUNCTION(August, function59);
	ADD_CALLBACK_FUNCTION(August, function60);
	ADD_CALLBACK_FUNCTION(August, function61);
	ADD_CALLBACK_FUNCTION(August, function62);
	ADD_CALLBACK_FUNCTION(August, function63);
	ADD_CALLBACK_FUNCTION(August, function64);
	ADD_CALLBACK_FUNCTION(August, function65);
	ADD_CALLBACK_FUNCTION(August, chapter5);
	ADD_CALLBACK_FUNCTION(August, function67);
	ADD_CALLBACK_FUNCTION(August, function68);
	ADD_CALLBACK_FUNCTION(August, function69);	
	ADD_NULL_FUNCTION();
}

IMPLEMENT_FUNCTION(August, function1, 1) {
	error("August: callback function 1 not implemented!");
}

IMPLEMENT_FUNCTION_I(August, function2, 2) {
	error("August: callback function 2 not implemented!");
}

IMPLEMENT_FUNCTION_S(August, function3, 3) {
	error("August: callback function 3 not implemented!");
}

IMPLEMENT_FUNCTION_SII(August, function4, 4) {
	error("August: callback function 4 not implemented!");
}

IMPLEMENT_FUNCTION_SI(August, function5, 5) {
	error("August: callback function 5 not implemented!");
}

IMPLEMENT_FUNCTION_SI(August, function6, 6) {
	error("August: callback function 6 not implemented!");
}

IMPLEMENT_FUNCTION_SI(August, function7, 7) {
	error("August: callback function 7 not implemented!");
}

IMPLEMENT_FUNCTION(August, function8, 8) {
	error("August: callback function 8 not implemented!");
}

IMPLEMENT_FUNCTION_SIIS(August, function9, 9) {
	error("August: callback function 9 not implemented!");
}

IMPLEMENT_FUNCTION_IIS(August, function10, 10) {
	error("August: callback function 10 not implemented!");
}

IMPLEMENT_FUNCTION_SSI(August, function11, 11) {
	error("August: callback function 11 not implemented!");
}

IMPLEMENT_FUNCTION_S(August, function12, 12) {
	error("August: callback function 12 not implemented!");
}

IMPLEMENT_FUNCTION_S(August, function13, 13) {
	error("August: callback function 13 not implemented!");
}

IMPLEMENT_FUNCTION(August, function14, 14) {
	error("August: callback function 14 not implemented!");
}

IMPLEMENT_FUNCTION_II(August, function15, 15) {
	error("August: callback function 15 not implemented!");
}

IMPLEMENT_FUNCTION_II(August, function16, 16) {
	error("August: callback function 16 not implemented!");
}

IMPLEMENT_FUNCTION_I(August, function17, 17) {
	error("August: callback function 17 not implemented!");
}

IMPLEMENT_FUNCTION_II(August, function18, 18) {
	error("August: callback function 18 not implemented!");
}

IMPLEMENT_FUNCTION_II(August, function19, 19) {
	error("August: callback function 19 not implemented!");
}

IMPLEMENT_FUNCTION_I(August, function20, 20) {
	error("August: callback function 20 not implemented!");
}

IMPLEMENT_FUNCTION_I(August, function21, 21) {
	error("August: callback function 21 not implemented!");
}

IMPLEMENT_FUNCTION(August, chapter1, 22) {
	switch (savepoint->action) {
	default:
		break;

	case kActionDefault:
		getObjects()->update(kObjectCompartment3, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
		getObjects()->update(kObject11, kEntityNone, kLocationNone, kCursorKeepValue, kCursorKeepValue);

		_data->getData()->field_491 = EntityData::kField491_4691;
		_data->getData()->field_493 = EntityData::kField493_1;
		_data->getData()->field_495 = EntityData::kField495_5;	
		_data->getData()->field_4A5 = 0;

		getProgress().event_august_met = 0;

		break;

	case kActionNone:
		CALL_CHAPTER_ACTION_NONE(25)
		break;
	}
}

IMPLEMENT_FUNCTION_I(August, function23, 23) {
	error("August: callback function 23 not implemented!");
}

IMPLEMENT_FUNCTION(August, function24, 24) {
	error("August: callback function 24 not implemented!");
}

IMPLEMENT_FUNCTION(August, function25, 25) {
	error("August: callback function 25 not implemented!");
}

IMPLEMENT_FUNCTION(August, function26, 26) {
	error("August: callback function 26 not implemented!");
}

IMPLEMENT_FUNCTION(August, function27, 27) {
	error("August: callback function 27 not implemented!");
}

IMPLEMENT_FUNCTION(August, function28, 28) {
	error("August: callback function 28 not implemented!");
}

IMPLEMENT_FUNCTION(August, function29, 29) {
	error("August: callback function 29 not implemented!");
}

IMPLEMENT_FUNCTION(August, restaurant, 30) {
	error("August: callback function 30 not implemented!");
}

IMPLEMENT_FUNCTION(August, function31, 31) {
	error("August: callback function 31 not implemented!");
}

IMPLEMENT_FUNCTION(August, function32, 32) {
	error("August: callback function 32 not implemented!");
}

IMPLEMENT_FUNCTION(August, function33, 33) {
	error("August: callback function 33 not implemented!");
}

IMPLEMENT_FUNCTION(August, function34, 34) {
	error("August: callback function 34 not implemented!");
}

IMPLEMENT_FUNCTION(August, chapter2, 35) {
	error("August: callback function 35 not implemented!");
}

IMPLEMENT_FUNCTION(August, function36, 36) {
	error("August: callback function 36 not implemented!");
}

IMPLEMENT_FUNCTION(August, function37, 37) {
	error("August: callback function 37 not implemented!");
}

IMPLEMENT_FUNCTION(August, function38, 38) {
	error("August: callback function 38 not implemented!");
}

IMPLEMENT_FUNCTION(August, function39, 39) {
	error("August: callback function 39 not implemented!");
}

IMPLEMENT_FUNCTION(August, chapter3, 40) {
	error("August: callback function 40 not implemented!");
}

IMPLEMENT_FUNCTION_II(August, function41, 41) {
	error("August: callback function 41 not implemented!");
}

IMPLEMENT_FUNCTION_III(August, function42, 42) {
	error("August: callback function 42 not implemented!");
}

IMPLEMENT_FUNCTION(August, function43, 43) {
	error("August: callback function 43 not implemented!");
}

IMPLEMENT_FUNCTION(August, function44, 44) {
	error("August: callback function 44 not implemented!");
}

IMPLEMENT_FUNCTION(August, function45, 45) {
	error("August: callback function 45 not implemented!");
}

IMPLEMENT_FUNCTION(August, function46, 46) {
	error("August: callback function 46 not implemented!");
}

IMPLEMENT_FUNCTION(August, function47, 47) {
	error("August: callback function 47 not implemented!");
}

IMPLEMENT_FUNCTION(August, function48, 48) {
	error("August: callback function 48 not implemented!");
}

IMPLEMENT_FUNCTION(August, function49, 49) {
	error("August: callback function 49 not implemented!");
}

IMPLEMENT_FUNCTION(August, function50, 50) {
	error("August: callback function 50 not implemented!");
}

IMPLEMENT_FUNCTION(August, function51, 51) {
	error("August: callback function 51 not implemented!");
}

IMPLEMENT_FUNCTION(August, function52, 52) {
	error("August: callback function 52 not implemented!");
}

IMPLEMENT_FUNCTION(August, function53, 53) {
	error("August: callback function 53 not implemented!");
}

IMPLEMENT_FUNCTION(August, function54, 54) {
	error("August: callback function 54 not implemented!");
}

IMPLEMENT_FUNCTION(August, function55, 55) {
	error("August: callback function 55 not implemented!");
}

IMPLEMENT_FUNCTION(August, function56, 56) {
	error("August: callback function 56 not implemented!");
}

IMPLEMENT_FUNCTION(August, chapter4, 57) {
	error("August: callback function 57 not implemented!");
}

IMPLEMENT_FUNCTION(August, function58, 58) {
	error("August: callback function 58 not implemented!");
}

IMPLEMENT_FUNCTION(August, function59, 59) {
	error("August: callback function 59 not implemented!");
}

IMPLEMENT_FUNCTION(August, function60, 60) {
	error("August: callback function 60 not implemented!");
}

IMPLEMENT_FUNCTION(August, function61, 61) {
	error("August: callback function 61 not implemented!");
}

IMPLEMENT_FUNCTION(August, function62, 62) {
	error("August: callback function 62 not implemented!");
}

IMPLEMENT_FUNCTION(August, function63, 63) {
	error("August: callback function 63 not implemented!");
}

IMPLEMENT_FUNCTION(August, function64, 64) {
	error("August: callback function 64 not implemented!");
}

IMPLEMENT_FUNCTION(August, function65, 65) {
	error("August: callback function 65 not implemented!");
}

IMPLEMENT_FUNCTION(August, chapter5, 66) {
	error("August: callback function 66 not implemented!");
}

IMPLEMENT_FUNCTION(August, function67, 67) {
	error("August: callback function 67 not implemented!");
}

IMPLEMENT_FUNCTION(August, function68, 68) {
	error("August: callback function 68 not implemented!");
}

IMPLEMENT_FUNCTION(August, function69, 69) {
	error("August: callback function 69 not implemented!");
}

IMPLEMENT_NULL_FUNCTION(August, 70)

} // End of namespace LastExpress
