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

#ifndef LASTEXPRESS_ACTION_H
#define LASTEXPRESS_ACTION_H

#include "common/system.h"

namespace LastExpress {

class LastExpressEngine;

class Action {
public:
	// Events with D at the end means that Cath is on the right of the "scene" (D = Droite)
	enum Events {
		kInvalid = 0,
		kGotALight = 1,
		kGotALightD = 2,
		kDinerMindJoin = 3,
		kDinerAugustOriginalJacket = 4,
		kDinerAugust = 5,
		kDinerAugustAlexeiBackground = 6,
		kMeetAugustTylerCompartment = 7,
		kMeetAugustTylerCompartmentBed = 8,
		kMeetAugustHisCompartment = 9,
		kMeetAugustHisCompartmentBed = 10,
		kAugustFindCorpse = 11,
		kAugustPresentAnna = 12,
		kAugustPresentAnnaFirstIntroduction = 13,
		kAnnaIntroductionRejected = 14,
		kAnnaConversationGoodNight = 15,
		kAnnaVisitToCompartmentGun = 16,
		kInvalid_17 = 17,
		kAnnaGoodNight = 18,
		kAnnaGoodNightInverse = 19,
		kAugustGoodMorning = 20,
		kAugustMerchandise = 21,
		kAugustTalkGold = 22,
		kAugustTalkGoldDay = 23,
		kAugustTalkCompartmentDoor = 24,
		kAugustTalkCompartmentDoorBlueRedingote = 25,
		kAugustLunch = 26,
		kKronosVisit = 27,
		kAnnaSearchingCompartment = 28,
		kAugustBringEgg = 29,
		kAugustBringBriefcase = 30,
		kAugustTalkCigar = 31,
		kAnnaBagageArgument = 32,
		kAnnaBagagePart2 = 33,
		kAnnaConversation_34 = 34,
		kAugustDrink = 35,
		kAnnaTired = 36,
		kAnnaTiredKiss = 37,
		kAnnaBagageTies = 38,
		kAnnaBagageTies2 = 39,
		kAnnaBagageTies3 = 40,
		kAnnaBagageTies4 = 41,
		/*k = 42,
		k = 43,
		k = 44,
		k = 45,
		k = 46,
		k = 47,
		k = 48,
		k = 49,
		k = 50,
		k = 51,
		k = 52,
		k = 53,
		k = 54,
		k = 55,
		k = 56,
		k = 57,
		k = 58,
		k = 59,
		k = 60,
		k = 61,
		k = 62,
		k = 63,
		k = 64,
		k = 65,
		k = 66,
		k = 67,
		k = 68,
		k = 69,
		k = 70,
		k = 71,
		k = 72,
		k = 73,
		k = 74,
		k = 75,
		k = 76,
		k = 77,
		k = 78,
		k = 79,
		k = 80,
		k = 81,
		k = 82,
		k = 83, */
		kVassiliSeizure = 84,
		/*k = 85,
		k = 86,
		k = 87,
		k = 88,
		k = 89,
		k = 90,	
		k = 91,
		k = 92,
		k = 93,
		k = 94,
		k = 95,
		k = 96,
		k = 97,
		k = 98,
		k = 99,
		k = 100,
		k = 101,
		k = 102,
		k = 103,
		k = 104,
		k = 105,
		k = 106,
		k = 107,
		k = 108,
		k = 109, */
		kAbbotIntroduction = 110,
		/*k = 111,
		k = 112,
		k = 113,
		k = 114,
		k = 115,
		k = 116,
		k = 117,
		k = 118,
		k = 119, */
		kMertensChronosInvitation = 120,
		kMertensChronosInvitationCompartment = 121,
		kMertensChronosInvitationClosedWindows = 122,
		kMertensBloodJacket = 123,	
		kCoudertBloodJacket = 124,
		kMertensCorpseFloor = 125,
		kMertensCorpseBed = 126,
		kMertensDontMakeBed = 127,
		kInvalid_128 = 128,
		kGendarmesArrestation = 129,
		kVergesSuitcase = 130,
		/*k = 131,
		k = 132,
		k = 133,
		k = 134,
		k = 135,
		k = 136,
		k = 137,
		k = 138,
		k = 139,
		k = 140,
		k = 141,
		k = 142,
		k = 143, */
		kIntroBroderbrund = 144,
		/*k = 145,
		k = 146,
		k = 147,
		k = 148,
		k = 149,
		k = 150,
		k = 151,
		k = 152,
		k = 153,
		k = 154,
		k = 155,
		k = 156,
		k = 157,
		k = 158,*/
		kIntro = 159,
		kDream = 160,
		kCorpseDropBridge = 161,
		//k = 162,
		kVergesAnnaDead = 163,
		/*k = 164,
		k = 165,
		k = 166,
		k = 167,
		k = 168,
		k = 169,
		k = 170,
		k = 171,
		k = 172,
		k = 173,
		k = 174,
		k = 175,
		k = 176,
		k = 177,
		k = 178,
		k = 179,
		k = 180, */
		kFrancoisShowBeetle = 181,
		kFrancoisShowBeetleD = 182,
		kFrancoisTradeWhistle = 183,
		kFrancoisTradeWhistleD = 184,
		kFrancoisShowEgg = 185,
		kFrancoisShowEggD = 186,
		kFrancoisShowEggNight = 187,
		kFrancoisShowEggNightD = 188, 
		kKronosBringFirebird = 189,
		kKronosOpenFirebird = 190,	
		kFinalSequence = 191,
		kLocomotiveRestartTrain = 192,
		kLocomotiveOldBridge = 193,
		kLocomotiveAbbotGetSomeRest = 194,
		kLocomotiveAbbotShoveling = 195,
		kLocomotiveMilosShovelingDay = 196,
		kLocomotiveMilosShovelingNight = 197,
		kAnnaGiveScarf = 198,
		kAnnaGiveScarfDiner = 199,
		kAnnaGiveScarfRestaurant = 200,
		kAnnaGiveScarfMonogram = 201,
		kAnnaGiveScarfDinerMonogram = 202,
		kAnnaGiveScarfRestaurantMonogram = 203,
		kAnnaAskScarf = 204,
		kAnnaAskScarfDiner = 205,
		kAnnaAskScarfRestaurant = 206,
		kAugustArrivalInMunich = 207,
		kAnnaDialogGoToJerusalem = 208,
		/*k = 209,
		k = 210,
		k = 211,
		k = 212,
		k = 213,
		k = 214,
		k = 215, */
		kCorpseDropFloorOriginal = 216,
		kCorpseDropFloorGreen = 217,
		kpCorpsePickFloorOriginal = 218,
		kpCorpsePickFloorGreen = 219,
		kpCorpsePickFloorOpenedBedOriginal = 220,
		kpCorpsePickBedOriginal = 221,
		kpCorpsePickBedGreen = 222,
		kCorpseDropBedOriginal = 223,
		kCorpseDropBedGreen = 224,
		kCorpseDropWindowOriginal = 225,
		kCorpseDropWindowGreen = 226,
		/*k = 227,
		k = 228,
		k = 229,
		k = 230,
		k = 231,
		k = 232,
		k = 233,
		k = 234,
		k = 235,
		k = 236,
		k = 237,
		k = 238,
		k = 239,
		k = 240,
		k = 241,
		k = 242,
		k = 243,
		k = 244,
		k = 245,
		k = 246,
		k = 247,
		k = 248,
		k = 249,
		k = 250,
		k = 251,
		k = 252,
		k = 253,
		k = 254,
		k = 255,*/
		kPickGreenJacket = 256,
		kPickScarfGreen = 257,
		kPickScarfOriginal = 258,
		kCloseMatchbox = 259,
		kCathStruggleWithBonds = 260,
		kCathBurnRope = 261,
		kCathRemoveBonds = 262,
		kCathStruggleWithBonds2 = 263,
		/*k = 264,
		k = 265,
		k = 266,
		k = 267,
		k = 268,
		k = 269,
		k = 270, */
		kCathUseWhistleOpenEgg = 271,
		kCathUseWhistleOpenEggNoBackground = 272		
	};

	Action(LastExpressEngine *engine);

	void pickGreenJacket();
	void pickScarf();
	void pickCorpse(byte bedPosition);
	void dropCorpse();

	void playAnimation(int index);

private:
	LastExpressEngine* _engine;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ACTION_H
