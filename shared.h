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

#ifndef LASTEXPRESS_SHARED_H
#define LASTEXPRESS_SHARED_H

namespace LastExpress {

//////////////////////////////////////////////////////////////////////////
// Time values
//////////////////////////////////////////////////////////////////////////
enum TimeValue {
	kTimeChapter1 = 1062000,
	kTimeChapter2 = 1750500,
	kTimeChapter3 = 1944000,
	kTimeChapter4 = 2353500,
	kTimeChapter5 = 2844000,

	kTimeGameOver = 2418300
};

enum TimeType {
	kTimeType0 = 0,
	kTimeType1 = 0,
	kTimeType2 = 0,
	kTimeType3 = 0
};

//////////////////////////////////////////////////////////////////////////
// Archive & Chapter ID
//////////////////////////////////////////////////////////////////////////
enum ArchiveIndex {
	kArchiveAll = 0,
	kArchiveCd1 = 1,
	kArchiveCd2 = 2,
	kArchiveCd3 = 3
};

enum ChapterIndex {
	kChapterAll = 0,
	kChapter1 = 1,
	kChapter2 = 2,
	kChapter3 = 3,
	kChapter4 = 4,
	kChapter5 = 5
};

//////////////////////////////////////////////////////////////////////////
// Index of scenes
//////////////////////////////////////////////////////////////////////////

typedef unsigned int SceneIndex;

enum SceneIndexes {
	kSceneNone                = 0,
	kSceneDefault             = 40,
	kSceneFightMilos          = 43,
	kSceneFightMilosBedOpened = 44,
	kSceneFightAnna           = 45,
	kSceneFightIvo            = 46,
	kSceneFightSalko          = 47,
	kSceneFightVesna          = 48,
	kSceneGameOverBloodJacket = 55,
	kSceneGameOverAlarm       = 62,
	kSceneGameOver63          = 63,
	kSceneGameOver64          = 64,
	kSceneMenu                = 65,
	kSceneFightDefault        = 820
};

//////////////////////////////////////////////////////////////////////////
// Jacket
//////////////////////////////////////////////////////////////////////////
enum JacketType {
	kJacketOriginal = 1,
	kJacketGreen = 2
};

//////////////////////////////////////////////////////////////////////////
// Savegame ID
//////////////////////////////////////////////////////////////////////////
enum GameId {
	kGameBlue,
	kGameRed,
	kGameGreen,
	kGamePurple,
	kGameTeal,
	kGameGold
};

//////////////////////////////////////////////////////////////////////////
// Cursor style
//////////////////////////////////////////////////////////////////////////
enum CursorStyle {
	kCursorNormal,
	kCursorForward,
	kCursorBackward,
	kCursorTurnRight,
	kCursorTurnLeft,
	kCursorUp,
	kCursorDown,
	kCursorLeft,
	kCursorRight,
	kCursorHand,
	kCursorHandKnock,                     // 10
	kCursorMagnifier,
	kCursorHandPointer,
	kCursorSleep,
	kCursorTalk,
	kCursorTalk2,     // Need better name

	// Items
	kCursorMatchBox,
	kCursorTelegram,
	kCursorPassengerList,
	kCursorArticle,
	kCursorScarf,     // 20
	kCursorPaper,
	kCursorParchemin,
	kCursorMatch,
	kCursorWhistle,
	kCursorKey,
	kCursorBomb,
	kCursorFirebird,
	kCursorBriefcase,
	kCursorCorpse,

	// Combat
	kCursorPunchLeft,                      // 30
	kCursorPunchRight,

	// Portraits
	kCursorPortrait,
	kCursorPortraitSelected,
	kCursorPortraitGreen,
	kCursorPortraitGreenSelected,
	kCursorPortraitYellow,
	kCursorPortraitYellowSelected,
	kCursorHourGlass,
	kCursorEggBlue,
	kCursorEggRed,                        // 40
	kCursorEggGreen,
	kCursorEggPurple,
	kCursorEggTeal,
	kCursorEggGold,
	kCursorEggClock,
	kCursorNormal2,
	kCursorBlank,
	kCursorMAX,

	// Special
	kCursorKeepValue = 255
};

//////////////////////////////////////////////////////////////////////////
// Location of objects
//////////////////////////////////////////////////////////////////////////
enum ObjectLocation {
	kLocationNone = 0,
	kLocation1 = 1,	// Floor?
	kLocation2 = 2, // Bed ?
	kLocation3 = 3,
	kLocation4 = 4, // Window ?
	kLocation5 = 5,
	kLocation6 = 6,
	kLocation10 = 10,
	kLocation11 = 11
};

//////////////////////////////////////////////////////////////////////////
// Entity direction
//////////////////////////////////////////////////////////////////////////
enum EntityDirection {
	kDirectionNone = 0,
	kDirectionUp = 1,
	kDirectionDown = 2,
	kDirectionLeft = 3,
	kDirectionRight = 4,
	kDirection5 = 5
};

//////////////////////////////////////////////////////////////////////////
// Combat
//////////////////////////////////////////////////////////////////////////
enum FightType {
	kFightMilos = 2001,
	kFightAnna = 2002,
	kFightIvo = 2003,
	kFightSalko = 2004,
	kFightVesna = 2005
};

//////////////////////////////////////////////////////////////////////////
// Index of items in inventory data
//////////////////////////////////////////////////////////////////////////
enum InventoryItem {
	kItemNone,
	kItemMatchBox,
	kItem2,
	kItem3,
	kItemTelegram,
	kItem5,               // 5
	kItemPassengerList,
	kItem7,
	kItemScarf,
	kItem9,
	kItemParchemin,       // 10
	kItem11,
	kItemMatch,
	kItemWhistle,
	kItemBeetle,
	kItemKey,             // 15
	kItemBomb,
	kItem17,
	kItemFirebird,
	kItemBriefcase,
	kItemCorpse,          // 20
	kItemGreenJacket,
	kItem22,
	kItemPaper,
	kItemArticle,
	kItem25,             // 25
	kItem26,
	kItem27,
	kItem28,
	kItem29,
	kItem30,            // 30
	kItem31,

	// Portrait (not an index)
	kPortraitOriginal = 32,
	kPortraitGreen = 34,
	kPortraitYellow = 36
};

//////////////////////////////////////////////////////////////////////////
// Object ID
//////////////////////////////////////////////////////////////////////////
enum ObjectIndex {
	kObjectNone,
	kObjectCompartment1,
	kObjectCompartment2,
	kObjectCompartment3,
	kObjectCompartment4,
	kObjectCompartment5,                 // 5
	kObjectCompartment6,
	kObjectCompartment7,
	kObjectCompartment8,
	kObjectOutside,
	kObject10,                           // 10
	kObject11,
	kObject12,
	kObject13,
	kObject14,
	kObject15,                           // 15
	kObject16,
	kObjectHandleBathroom,
	kObjectHandleInsideBathroom,
	kObjectKitchen,
	kObject20,                          // 20
	kObject21,
	kObject22,
	kObjectGreenSleepingCar,
	kObjectRedSleepingCar,
	kObject25,                          // 25
	kObjectHandleOutsideLeft,
	kObjectHandleOutsideRight,
	kObject28,
	kObject29,
	kObject30,                          // 30
	kObject31,
	kObjectCompartmentA,
	kObjectCompartmentB,
	kObjectCompartmentC,
	kObjectCompartmentD,                // 35
	kObjectCompartmentE,
	kObjectCompartmentF,
	kObjectCompartmentG,
	kObjectCompartmentH,
	kObject40,                          // 40
	kObject41,
	kObject42,
	kObject43,
	kObject44,
	kObject45,                          // 45
	kObject46,
	kObject47,
	kObject48,
	kObject49,
	kObject50,                          // 50
	kObject51,
	kObject52,
	kObject53,
	kObject54,
	kObjectRestaurantCar = 55,          // 55
	kObject56,
	kObject57,
	kObject58,
	kObject59,
	kObject60,                          // 60
	kObject61,
	kObject62,
	kObject63,
	kObject64,
	kObject65,                          // 65
	kObject66,
	kObject67,
	kObject68,
	kObject69,
	kObject70,                          // 70
	kObject71,
	kObject72,
	kObjectCeiling,
	kObject74,
	kObjectCompartmentKronos,           // 75
	kObject76,
	kObject77,
	kObject78,
	kObject79,
	kObject80,                          // 80
	kObject81,
	kObject82,
	kObject83,
	kObject84,
	kObject85,                          // 85
	kObject86,
	kObject87,
	kObject88,
	kObject89,
	kObject90,                          // 90
	kObject91,
	kObject92,
	kObject93,
	kObject94,
	kObject95,                          // 95
	kObject96,
	kObject97,
	kObject98,
	kObject99,
	kObject100,                         // 100
	kObject101,
	kObject102,
	kObject103,
	kObject104,
	kObject105,                         // 105
	kObject106,
	kObject107,
	kObject108,
	kObjectCageMax,
	kObject110,                         // 110
	kObject111,
	kObject112,
	kObject113,
	kObject114,
	kObject115,                         // 115
	kObject116,
	kObject117,
	kObject118,
	kObject119,
	kObject120,                         // 120
	kObject121,
	kObject122,
	kObject123,
	kObject124,
	kObject125,                         // 125
	kObject126,
	kObject127,
	kObject128
};

//////////////////////////////////////////////////////////////////////////
// Entity ID
//////////////////////////////////////////////////////////////////////////
enum EntityIndex {
	kEntityNone,
	kEntityAnna,
	kEntityAugust,
	kEntityMertens,
	kEntityCoudert,
	kEntityPascale,             // 5
	kEntityServers0,
	kEntityServers1,
	kEntityCooks,
	kEntityVerges,
	kEntityTatiana,             // 10
	kEntityVassili,
	kEntityAlexei,
	kEntityAbbot,
	kEntityMilos,
	kEntityVesna,               // 15
	kEntityIvo,
	kEntitySalko,
	kEntityKronos,
	kEntityKahina,
	kEntityFrancois,            // 20
	kEntityMmeBoutarel,
	kEntityBoutarel,
	kEntityRebecca,
	kEntitySophie,
	kEntityMahmud,              // 25
	kEntityYasmin,
	kEntityHadija,
	kEntityAlouan,
	kEntityGendarmes,
	kEntityMax,                 // 30
	kEntityChapters,
	kEntityTrain,
	kEntityTables0,
	kEntityTables1,
	kEntityTables2,             // 35
	kEntityTables3,
	kEntityTables4,
	kEntityTables5,
	kEntity39
};

//////////////////////////////////////////////////////////////////////////
// Events
//   - a single D at the end means that Cath is on the right of the "scene" (D = Down the train, U = Up the train)
//   - DD: during the day, coming down the train
//   - DU: during the day, coming up the train
//   - ND: during the night, coming down the train
//   - NU: during the night, coming up the train
//////////////////////////////////////////////////////////////////////////
enum EventIndex {
	kEventNone = 0,
	kEventGotALight = 1,
	kEventGotALightD = 2,
	kEventDinerMindJoin = 3,
	kEventDinerAugustOriginalJacket = 4,
	kEventDinerAugust = 5,
	kEventDinerAugustAlexeiBackground = 6,
	kEventMeetAugustTylerCompartment = 7,
	kEventMeetAugustTylerCompartmentBed = 8,
	kEventMeetAugustHisCompartment = 9,
	kEventMeetAugustHisCompartmentBed = 10,
	kEventAugustFindCorpse = 11,
	kEventAugustPresentAnna = 12,
	kEventAugustPresentAnnaFirstIntroduction = 13,
	kEventAnnaIntroductionRejected = 14,
	kEventAnnaConversationGoodNight = 15,
	kEventAnnaVisitToCompartmentGun = 16,
	kEventInvalid_17 = 17,
	kEventAnnaGoodNight = 18,
	kEventAnnaGoodNightInverse = 19,
	kEventAugustGoodMorning = 20,
	kEventAugustMerchandise = 21,
	kEventAugustTalkGold = 22,
	kEventAugustTalkGoldDay = 23,
	kEventAugustTalkCompartmentDoor = 24,
	kEventAugustTalkCompartmentDoorBlueRedingote = 25,
	kEventAugustLunch = 26,
	kEventKronosVisit = 27,
	kEventAnnaSearchingCompartment = 28,
	kEventAugustBringEgg = 29,
	kEventAugustBringBriefcase = 30,
	kEventAugustTalkCigar = 31,
	kEventAnnaBagageArgument = 32,
	kEventAnnaBagagePart2 = 33,
	kEventAnnaConversation_34 = 34,
	kEventAugustDrink = 35,
	kEventAnnaTired = 36,
	kEventAnnaTiredKiss = 37,
	kEventAnnaBagageTies = 38,
	kEventAnnaBagageTies2 = 39,
	kEventAnnaBagageTies3 = 40,
	kEventAnnaBagageTies4 = 41,
	kEventAugustUnhookCarsBetrayal = 42,
	kEventAugustUnhookCars = 43,
	kEventLocomotiveAnnaStopsTrain = 44,
	kEventInvalid_45 = 45,
	kEventTrainStopped = 46,
	kEventAnnaKissTrainHijacked = 47,
	kEventTrainHijacked = 48,
	kEventAnnaKilled = 49,
	kEventKronosGoingToInvitation = 50,
	kEventKronosConversation = 51,
	kEventKahinaAskSpeakFirebird = 52,
	kEventKahinaAskSpeak = 53,
	kEventKronosConversationFirebird = 54,
	kEventKahinaGunYellow = 55,
	kEventKahinaGunBlue = 56,
	kEventKahinaGun = 57,
	kEventKronosBringEggCeiling = 58,
	kEventKronosBringEgg = 59,
	kEventKronosBringNothing = 60,
	kEventKronosReturnBriefcase = 61,
	kEventKronosHostageAnna = 62,
	kEventKronosGiveFirebird = 63,
	kEventKahinaPunch = 64,
	kEventKahinaPunchBlue = 65,
	kEventKahinaPunchYellow = 66,
	kEventKahinaPunchSuite = 67,
	kEventKahinaPunchSuite2 = 68,
	kEventKahinaPunchSuite3 = 69,
	kEventKahinaPunchCar = 70,
	kEventKahinaPunchSuite4 = 71,
	kEventKahinaPunchSuite5 = 72,
	kEventKronosHostageAnnaNoFirebird = 73,
	kEventKahinaPunchRestaurant = 74,
	kEventKahinaWrongDoor = 75,
	kEventAlexeiDiner = 76,
	kEventAlexeiDinerOriginalJacket = 77,
	kEventAlexeiSalonVassili = 78,
	kEventAlexeiSalonCath = 79,
	kEventAlexeiSalonPoem = 80,
	kEventTatianaAskMatchSpeakRussian = 81,
	kEventTatianaAskMatch = 82,
	kEventTatianaGivePoem = 83,
	kEventVassiliSeizure = 84,
	kEventTatianaBreakfastAlexei = 85,
	kEventTatianaBreakfast = 86,
	kEventTatianaBreakfastGivePoem = 87,
	kEventTatianaAlexei = 88,
	kEventTatianaCompartmentStealEgg = 89,
	kEventTatianaCompartment = 90,
	kEventVassiliCompartmentStealEgg = 91,
	kEventTatianaTylerCompartment = 92,
	kEventTylerCastleDream= 93,
	kEventVassiliDeadAlexei = 94,
	kEventCathFreePassengers = 95,
	kEventTatianaVassiliTalk = 96,
	kEventTatianaVassiliTalkNight = 97,
	kEventMilosTylerCompartmentVisit = 98,
	kEventMilosTylerCompartmentBedVisit = 99,
	kEventMilosTylerCompartment = 100,
	kEventMilosTylerCompartmentBed = 101,
	kEventMilosTylerCompartmentDefeat = 102,
	kEventMilosCorpseFloor = 103,
	kEventMilosCompartmentVisitAugust = 104,
	kEventMilosCorridorThanks = 105,
	kEventMilosCorridorThanksD = 106,
	kEventMilosCompartmentVisitTyler = 107,
	kEventLocomotiveMilos = 108,
	kEventLocomotiveMilosNight = 109,
	kEventAbbotIntroduction = 110,
	kEventAbbotWrongCompartment = 111,
	kEventAbbotWrongCompartmentBed = 112,
	kEventAbbotInvitationDrink = 113,
	kEventAbbotDrinkGiveDetonator = 114,
	kEventTrainExplosionBridge = 115,
	kEventDefuseBomb = 116,
	kEventAbbotDrinkDefuse = 117,
	kEventMertensLastCar = 118,
	kEventMertensLastCarOriginalJacket = 119,
	kEventMertensChronosInvitation = 120,
	kEventMertensChronosInvitationCompartment = 121,
	kEventMertensChronosInvitationClosedWindows = 122,
	kEventMertensBloodJacket = 123,
	kEventCoudertBloodJacket = 124,
	kEventMertensCorpseFloor = 125,
	kEventMertensCorpseBed = 126,
	kEventMertensDontMakeBed = 127,
	kEventInvalid_128 = 128,
	kEventGendarmesArrestation = 129,
	kEventVergesSuitcase = 130,
	kEventVergesSuitcaseStart = 131,
	kEventVergesSuitcaseOtherEntry = 132,
	kEventVergesSuitcaseOtherEntryStart = 133,
	kEventVergesSuitcaseNight = 134,
	kEventVergesSuitcaseNightStart = 135,
	kEventVergesSuitcaseNightOtherEntry = 136,
	kEventVergesSuitcaseNightOtherEntryStart = 137,
	kEventMertensAskTylerCompartment = 138,
	kEventMertensAskTylerCompartmentD = 139,
	kEventMertensPushCall = 140,
	kEventMertensPushCall2 = 141,
	kEventMertensAugustWaiting = 142,
	kEventMertensAugustWaitingCompartment = 143,
	kEventIntroBroderbrund = 144,
	kEventCoudertAskTylerCompartment = 145,
	kEventMertensKronosConcertInvitation = 146,
	kEventCoudertGoingOutOfVassiliCompartment = 147,
	kEventLocomotiveConductorsDiscovered = 148,
	kEventLocomotiveConductorsLook = 149,
	kEventMahmudWrongDoor = 150,
	kEventMahmudWrongDoorOriginalJacket = 151,
	kEventMahmudWrongDoorDay = 152,
	kEventVergesEscortToDiningCar = 153,
	kEventVergesBagageCarOffLimits = 154,
	kEventVergesCanIHelpYou = 155,
	kEventCoudertBagageCar = 156,
	kEventCathTurningDay = 157,
	kEventCathTurningNight = 158,
	kEventIntro = 159,
	kEventCathDream = 160,
	kEventCorpseDropBridge = 161,
	kEventTrainPassing = 162,
	kEventVergesAnnaDead = 163,
	kEventViennaAugustUnloadGuns = 164,
	kEventViennaKronosFirebird = 165,
	kEventViennaContinueGame = 166,
	kEventCathVesnaRestaurantKilled = 167,
	kEventCathMaxCage = 168,
	kEventCathMaxFree = 169,
	kEventCathMaxLickHand = 170,
	kEventCathIvoFight = 171,
	kEventCathSalkoTrainTopFight = 172,
	kEventCathVesnaTrainTopFight = 173,
	kEventCathVesnaTrainTopKilled = 174,
	kEventCathVesnaTrainTopWin = 175,
	kEventCathSalkoTrainTopWin = 176,
	kEventFrancoisWhistle = 177,
	kEventFrancoisWhistleD = 178,
	kEventFrancoisWhistleNight = 179,
	kEventFrancoisWhistleNightD = 180,
	kEventFrancoisShowBeetle = 181,
	kEventFrancoisShowBeetleD = 182,
	kEventFrancoisTradeWhistle = 183,
	kEventFrancoisTradeWhistleD = 184,
	kEventFrancoisShowEgg = 185,
	kEventFrancoisShowEggD = 186,
	kEventFrancoisShowEggNight = 187,
	kEventFrancoisShowEggNightD = 188,
	kEventKronosBringFirebird = 189,
	kEventKronosOpenFirebird = 190,
	kEventFinalSequence = 191,
	kEventLocomotiveRestartTrain = 192,
	kEventLocomotiveOldBridge = 193,
	kEventLocomotiveAbbotGetSomeRest = 194,
	kEventLocomotiveAbbotShoveling = 195,
	kEventLocomotiveMilosShovelingDay = 196,
	kEventLocomotiveMilosShovelingNight = 197,
	kEventAnnaGiveScarf = 198,
	kEventAnnaGiveScarfDiner = 199,
	kEventAnnaGiveScarfSalon = 200,
	kEventAnnaGiveScarfMonogram = 201,
	kEventAnnaGiveScarfDinerMonogram = 202,
	kEventAnnaGiveScarfSalonMonogram = 203,
	kEventAnnaGiveScarfAsk = 204,
	kEventAnnaGiveScarfDinerAsk = 205,
	kEventAnnaGiveScarfSalonAsk = 206,
	kEventAugustArrivalInMunich = 207,
	kEventAnnaDialogGoToJerusalem = 208,
	kEventConcertStart = 209,
	kEventConcertEnd = 210,
	kEventCathFallingAsleep = 211,
	kEventCathWakingUp = 212,
	kEventConcertCough = 213,
	kEventConcertSit = 214,
	kEventConcertLeaveWithBriefcase = 215,
	kEventCorpseDropFloorOriginal = 216,
	kEventCorpseDropFloorGreen = 217,
	kEventCorpsePickFloorOriginal = 218,
	kEventCorpsePickFloorGreen = 219,
	kEventCorpsePickFloorOpenedBedOriginal = 220,
	kEventCorpsePickBedOriginal = 221,
	kEventCorpsePickBedGreen = 222,
	kEventCorpseDropBedOriginal = 223,
	kEventCorpseDropBedGreen = 224,
	kEventCorpseDropWindowOriginal = 225,
	kEventCorpseDropWindowGreen = 226,
	kEventCathFindCorpse = 227,
	kEventCathLookOutsideWindowDay = 228,
	kEventCathLookOutsideWindowNight = 229,
	kEventCathGoOutsideTylerCompartmentDay = 230,
	kEventCathGoOutsideTylerCompartmentNight = 231,
	kEventCathGoOutsideDay = 232,
	kEventCathGoOutsideNight = 233,
	kEventCathSlipTylerCompartmentDay = 234,
	kEventCathSlipTylerCompartmentNight = 235,
	kEventCathSlipDay = 236,
	kEventCathSlipNight = 237,
	kEventCathGetInsideTylerCompartmentDay = 238,
	kEventCathGetInsideTylerCompartmentNight = 239,
	kEventCathGetInsideDay = 240,
	kEventCathGetInsideNight = 241,
	kEventCathGettingInsideAnnaCompartment = 242,
	kEventCathClimbUpTrainGreenJacket = 243,
	kEventCathClimbUpTrainNoJacketNight = 244,
	kEventCathClimbUpTrainNoJacketDay = 245,
	kEventCathClimbDownTrainGreenJacket = 246,
	kEventCathClimbDownTrainNoJacketNight = 247,
	kEventCathClimbDownTrainNoJacketDay= 248,
	kEventCathTopTrainGreenJacket = 249,
	kEventCathTopTrainNoJacketNight = 250,
	kEventCathTopTrainNoJacketDay = 251,
	kEventCathBreakCeiling = 252,
	kEventCathJumpDownCeiling = 253,
	kEventCathJumpUpCeilingBriefcase = 254,
	kEventCathJumpUpCeiling = 255,
	kEventPickGreenJacket = 256,
	kEventPickScarfGreen = 257,
	kEventPickScarfOriginal = 258,
	kEventCloseMatchbox = 259,
	kEventCathStruggleWithBonds = 260,
	kEventCathBurnRope = 261,
	kEventCathRemoveBonds = 262,
	kEventCathStruggleWithBonds2 = 263,
	kEventCathDefusingBomb = 264,
	kEventCathSmokeNight = 265,
	kEventCathSmokeDay = 266,
	kEventCathOpenEgg = 267,
	kEventCathOpenEggNoBackground = 268,
	kEventCathCloseEgg = 269,
	kEventCathCloseEggNoBackground = 270,
	kEventCathUseWhistleOpenEgg = 271,
	kEventCathUseWhistleOpenEggNoBackground = 272
};

//////////////////////////////////////////////////////////////////////////
// Action ID (used by entity logic)
//////////////////////////////////////////////////////////////////////////
enum ActionIndex {
	kActionNone = 0,
	kAction2 = 2,
	kAction3 = 3,
	kAction5 = 5,
	kAction6 = 6,
	kAction8 = 8,
	kAction9 = 9,
	kActionDefault = 12,
	kAction17 = 17,
	kAction18 = 18,

	/////////////////////////////
	// Abbot
	/////////////////////////////
	kAction203073664 = 203073664,

	/////////////////////////////
	// Anna
	/////////////////////////////
	kAction238936000 = 238936000,
	kAction291662081 = 291662081,

	/////////////////////////////
	// Boutarel
	/////////////////////////////
	kAction203520448 = 203520448,
	kAction237889408 = 237889408,

	/////////////////////////////
	// Chapters
	/////////////////////////////
	kAction171843264 = 171843264,

	/////////////////////////////
	// Coudert
	/////////////////////////////
	kAction154005632 = 154005632,
	kAction157026693 = 157026693,
	kAction168254872 = 168254872,
	kAction169557824 = 169557824,
	kAction171394341 = 171394341,    // Coudert / Mertens
	kAction185671840 = 185671840,
	kAction185737168 = 185737168,
	kAction188570113 = 188570113,
	kAction189026624 = 189026624,
	kAction189750912 = 189750912,
	kAction201431954 = 201431954,    // Coudert / Mertens / Verges
	kAction205033696 = 205033696,
	kAction226031488 = 226031488,    // Coudert / Verges
	kAction292048641 = 292048641,
	kAction326348944 = 326348944,
	kAction339669520 = 339669520,    // Coudert / Verges

	/////////////////////////////
	// Mahmud
	/////////////////////////////
	kAction170483072 = 170483072,

	/////////////////////////////
	// Max
	/////////////////////////////
	kAction71277948  = 71277948,
	kAction158007856 = 158007856,
	kAction101687594 = 101687594,
	kAction122358304 = 122358304,
	kActionMaxFreeFromCage = 135204609,
	kAction156622016 = 156622016,

	/////////////////////////////
	// Mertens
	/////////////////////////////
	kAction169633856 = 169633856,
	kAction188635520 = 188635520,
	kAction190082817 = 190082817,
	kAction204379649 = 204379649,
	kAction224122407 = 224122407,
	kAction238732837 = 238732837,
	kAction269436673 = 269436673,
	kAction269624833 = 269624833,
	kAction302614416 = 302614416,
	kAction303343617 = 303343617,

	/////////////////////////////
	// Milos
	/////////////////////////////
	kAction157691176 = 157691176,
	kAction208228224 = 208228224,
	kAction259125998 = 259125998,

	/////////////////////////////
	// Mme Boutarel
	/////////////////////////////
	kAction242526416 = 242526416,

	/////////////////////////////
	// Pascale
	/////////////////////////////
	kAction101824388 = 101824388,
	kAction136059947 = 136059947,
	kAction190605184 = 190605184,
	kAction191604416 = 191604416,
	kAction207769280 = 207769280,
	kAction223262556 = 223262556,
	kAction239072064 = 239072064,
	kAction257489762 = 257489762,
	kAction269479296 = 269479296,
	kAction352703104 = 352703104,
	kAction352768896 = 352768896,

	/////////////////////////////
	// Rebecca
	/////////////////////////////
	kAction224253538 = 224253538,

	/////////////////////////////
	// Salko
	/////////////////////////////
	kAction136184016 = 136184016,

	/////////////////////////////
	// Servers 0
	/////////////////////////////
	kAction188893625 = 188893625,
	kAction204704037 = 204704037,
	kAction207330561 = 207330561,
	kAction218128129 = 218128129,
	kAction218586752 = 218586752,
	kAction218983616 = 218983616,
	kAction223712416 = 223712416,
	kAction237485916 = 237485916,
	kAction252568704 = 252568704,
	kAction270068760 = 270068760,
	kAction270410280 = 270410280,
	kAction286403504 = 286403504,
	kAction286534136 = 286534136,
	kAction292758554 = 292758554,
	kAction304061224 = 304061224,
	kAction337548856 = 337548856,

	/////////////////////////////
	// Servers 1
	/////////////////////////////
	kAction189688608 = 189688608,
	kAction219377792 = 219377792,
	kAction223002560 = 223002560,
	kAction236237423 = 236237423,
	kAction256200848 = 256200848,
	kAction258136010 = 258136010,
	kAction269485588 = 269485588,
	kAction291721418 = 291721418,
	kAction302203328 = 302203328,
	kAction302996448 = 302996448,
	kAction326144276 = 326144276,

	/////////////////////////////
	// Sophie
	/////////////////////////////
	kAction70549068  = 70549068,
	kAction123668192 = 123668192,
	kAction125242096 = 125242096,
	kAction136654208 = 136654208,
	kAction259921280 = 259921280,
	kAction292775040 = 292775040,

	/////////////////////////////
	// Tables
	/////////////////////////////
	kAction103798704 = 103798704,
	kAction136455232 = 136455232,

	/////////////////////////////
	// Tatiana
	/////////////////////////////
	kAction191198209 = 191198209,

	/////////////////////////////
	// Train
	/////////////////////////////
	kAction191070912 = 191070912,
	kAction191350523 = 191350523,
	kAction202613084 = 202613084,
	kAction203339360 = 203339360,
	kAction203419131 = 203419131,
	kAction203863200 = 203863200,
	kAction222746496 = 222746496,
	kActionBreakCeiling = 225056224,
	kActionJumpDownCeiling = 338494260,

	/////////////////////////////
	// Verges
	/////////////////////////////
	kAction158617345 = 158617345,
	kAction167854368 = 167854368,
	kAction168187490 = 168187490,
	kAction168255788 = 168255788,
	kAction191337656 = 191337656,

	/////////////////////////////
	// Vesna
	/////////////////////////////
	kAction124190740 = 124190740,

	/////////////////////////////
	// Misc
	/////////////////////////////
	kAction158610240 = 158610240,
	kAction167992577 = 167992577,
	kAction168646401 = 168646401,
	kAction169300225 = 169300225,
	kAction169773228 = 169773228,
	kAction190346110 = 190346110,
	kAction191001984 = 191001984,
	kAction192637492 = 192637492,
	kAction201959744 = 201959744,
	kAction202621266 = 202621266,
	kAction202884544 = 202884544,
	kAction203078272 = 203078272,
	kAction205034665 = 205034665,
	kAction205294778 = 205294778,
	kAction270751616 = 270751616,
	kAction272177921 = 272177921,
	kAction224309120 = 224309120,
	kAction225358684 = 225358684,
	kAction225367984 = 225367984,

	kActionEnd
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SHARED_H
