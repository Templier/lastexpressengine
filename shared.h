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
	kTime0                    = 0,
	kTime1                    = 1,
	kTimeCityParis            = 1037700,
	kTime1039500              = 1039500,
	kTimeStartGame            = 1061100,

	// Chapter 1
	kTimeChapter1             = 1062000,
	kTime1071000              = 1071000,
	kTimeParisEpernay         = 1075500,
	kTime1080000              = 1080000,
	kTime1084500              = 1084500,
	kTime1089000              = 1089000,
	kTime1093500              = 1093500,
	kTime1096200              = 1096200,
	kTime1098000              = 1098000,
	kTime1102500              = 1102500,
	kTime1107000              = 1107000,
	kTime1134000              = 1134000,
	kTime1138500              = 1138500,
	kTimeEnterEpernay         = 1147500,
	kTimeCityEpernay          = 1148400,
	kTimeExitEpernay          = 1150200,
	kTime1156500              = 1156500,
	kTime1161000              = 1161000,
	kTime1162800              = 1162800,
	kTime1165500              = 1165500,
	kTime1167300              = 1167300,
	kTimeEnterChalons         = 1170000,
	kTimeCityChalons          = 1170900,
	kTimeExitChalons          = 1173600,
	kTime1174500              = 1174500,
	kTime1179000              = 1179000,
	kTime1183500              = 1183500,
	kTime1184400              = 1184400,
	kTime1188000              = 1188000,
	kTime1189800              = 1189800,
	kTime1197000              = 1197000,
	kTime1201500              = 1201500,
	kTime1206000              = 1206000,
	kTime1215000              = 1215000,
	kTIme1225800              = 1225800,
	kTimeCityBarLeDuc         = 1228500,
	kTimeExitBarLeDuc         = 1231200,
	kTime1242000              = 1242000,
	kTime1260000              = 1260000,
	kTimeCityNancy            = 1303200,
	kTimeExitNancy            = 1307700,
	kTime1323000              = 1323000,
	kTimeCityLuneville        = 1335600,
	kTimeExitLuneville        = 1338300,
	kTimeCityAvricourt        = 1359900,
	kTimeExitAvricourt        = 1363500,
	kTimeCityDeutschAvricourt = 1367100,
	kTimeExitDeutschAvricourt = 1370700,
	kTimeBedTime              = 1404000,
	kTimeEnterStrasbourg      = 1424700,
	kTime1458000              = 1458000,
	kTime1489500              = 1489500,
	kTimeCityStrasbourg       = 1490400,
	kTimeExitStrasbourg       = 1493100,
	kTimeChapter1End          = 1494000,
	kTime1503000              = 1503000,
	kTime1512000              = 1512000,
	kTimeCityBadenOos         = 1539000,
	kTimeExitBadenOos         = 1541700,
	kTimeCityKarlsruhe        = 1563300,
	kTimeCityStuttgart        = 1656000,
	kTimeChapter1End2         = 1647000,
	kTimeChapter1End3         = 1674000,
	kTimeCityGeislingen       = 1713600,
	kTimeCityUlm              = 1739700,

	// Chapter 2
	kTimeChapter2             = 1750500,
	kTime1759500              = 1759500,
	kTime1755000              = 1755000,
	kTime1764000              = 1764000,
	kTime1773000              = 1773000,
	kTime1777500              = 1777500,
	kTime1782000              = 1782000,
	kTime1786500              = 1786500,
	kTime1791000              = 1791000,
	kTime1800000              = 1800000,
	kTimeCityAugsburg         = 1809900,
	kTime1818000              = 1818000,
	kTime1818900              = 1818900,
	kTime1822500              = 1822500,
	kTime1836000              = 1836000,
	kTimeCityMunich           = 1852200,

	// Chapter 3
	kTimeChapter3             = 1944000,
	kTime1953000              = 1953000,
	kTime1966500              = 1966500,
	kTime1971000              = 1971000,
	kTimeCitySalzbourg        = 1984500,
	kTime1989000              = 1989000,
	kTime1993500              = 1993500,
	kTime2016000              = 2016000,
	kTimeCityAttnangPuchheim  = 2049300,
	kTime2052000              = 2052000,
	kTime2061000              = 2061000,
	kTime2062800              = 2062800,
	kTime2070000              = 2070000,
	kTimeCityWels             = 2075400,
	kTime2079000              = 2079000,
	kTime2088000              = 2088000,
	kTime2097000              = 2097000,
	kTimeCityLinz             = 2101500,
	kTime2106000              = 2106000,
	kTime2110500              = 2110500,
	kTime2133000              = 2133000,
	kTimeCityAmstetten        = 2154600,
	kTime2160000              = 2160000,
	kTime2200500              = 2200500,
	kTime2250000              = 2250000,
	kTime2259000              = 2259000,
	kTimeCityVienna           = 2268000,

	// Chapter 4
	kTimeChapter4             = 2353500,
	kTime2354400              = 2354400,
	kTime2358000              = 2358000,
	kTime2362500              = 2362500,
	kTime2361600              = 2361600,
	kTime2367000              = 2367000,
	kTime2385000              = 2385000,
	kTimeCityPoszony          = 2383200,
	kTime3289500              = 3289500,
	kTime2403000              = 2403000,
	kTime2407500              = 2407500,
	kTime2410200              = 2410200,
	kTime2412000              = 2412000,
	kTime2415600              = 2415600,
	kTimeCityGalanta          = 2418300,
	kTime2422800              = 2422800,
	kTime2425500              = 2425500,
	kTime2457000              = 2457000,
	kTime2479500              = 2479500,
	kTime2488500              = 2488500,
	kTime2511000              = 2511000,
	kTime2511900              = 2511900,
	kTimeCityBudapest         = 2551500,

	// Chapter 5
	kTimeChapter5             = 2844000,
	kTimeTrainStopped         = 2898000,
	kTime2907000              = 2907000,
	kTime2916000              = 2916000,
	kTimeCityBelgrade         = 2952000,
	kTimeTrainStopped2        = 2943000,
	kTimeCityNish             = 3205800,
	kTimeCityTzaribrod        = 3492000,
	kTimeCitySofia            = 3690000,
	kTimeCityAdrianople       = 4320900,
	kTimeCityConstantinople   = 4941000,

	// Bug in original game?
	kTimeEnd                  = 15803100,

	kTimeInvalid              = 2147483647
};

enum TimeType {
	kTimeType0 = 0,
	kTimeTypeTime = 1,
	kTimeTypeEvent = 2,
	kTimeType3 = 3
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
	kChapter1   = 1,
	kChapter2   = 2,
	kChapter3   = 3,
	kChapter4   = 4,
	kChapter5   = 5
};

//////////////////////////////////////////////////////////////////////////
// Index of scenes
//////////////////////////////////////////////////////////////////////////
enum SceneIndex {
	kSceneNone                    = 0,
	kSceneMenu                    = 1,

	// Inventory
	kSceneMatchbox                = 31,
	kSceneTelegram                = 32,
	kScenePassengerList           = 33,
	kSceneScarf                   = 34,
	kSceneParchemin               = 35,
	kSceneArticle                 = 36,
	kScenePaper                   = 37,
	kSceneFirebird                = 38,
	kSceneBriefcase               = 39,

	// Normal scenes
	kSceneDefault                 = 40,
	kScene41                      = 41,
	kSceneCompartmentCorpse       = 42,     // Tyler compartment with corpse on floor

	// Fight
	kSceneFightMilos              = 43,
	kSceneFightMilosBedOpened     = 44,
	kSceneFightAnna               = 45,
	kSceneFightIvo                = 46,
	kSceneFightSalko              = 47,
	kSceneFightVesna              = 48,

	kSceneEuropeMap               = 49,

	// Game over
	kSceneGameOverStopPolice      = 50,
	kSceneGameOverTrainStopped    = 51,
	kSceneGameOverTrainStopped2   = 52,
	kSceneGameOverTrainExplosion  = 53,
	kSceneGameOverTrainExplosion2 = 54,
	kSceneGameOverBloodJacket     = 55,
	kSceneGameOverPolice          = 56,
	kSceneGameOverPolice1         = 57,
	kSceneGameOverAnnaDied        = 58,
	kSceneGameOverVienna          = 59,
	kSceneGameOverVienna1         = 60,
	kSceneGameOverVienna2         = 61,
	kSceneGameOverAlarm           = 62,
	kSceneGameOverPolice2         = 63,
	kSceneGameOverAlarm2          = 64,

	// Start screen
	kSceneStartScreen             = 65,

	kSceneBeetle                  = 128,

	kSceneFightDefault            = 820,

	kSceneStopProcessing          = 0xfffffffe,
	kSceneInvalid                 = 0xffffffff
};

//////////////////////////////////////////////////////////////////////////
// Jacket
//////////////////////////////////////////////////////////////////////////
enum JacketType {
	kJacketOriginal   = 0,
	kJacketBlood      = 1,
	kJacketGreen      = 2
};

//////////////////////////////////////////////////////////////////////////
// City
//////////////////////////////////////////////////////////////////////////
enum CityIndex {
	kCityEpernay,
	kCityChalons,
	kCityBarleduc,
	kCityNancy,
	kCityLuneville,
	kCityAvricourt,                // 5
	kCityDeutschAvricourt,
	kCityStrasbourg,
	kCityBadenOos,
	kCitySalzbourg,
	kCityAttnangPuchheim,          // 10
	kCityWels,
	kCityLinz,
	kCityVienna,
	kCityPoszony,
	kCityGalanta,                  // 15
	kCityPolice
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

enum SavegameType {
	kSavegameType0 = 0,
	kSavegameType1 = 1,
	kSavegameType2 = 2,
	kSavegameTypeAuto = 4,
	kSavegameTypeTickInterval = 5
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
	kCursorPortrait,                      // 32
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
	kCursorProcess = 128,
	kCursorKeepValue = 255
};

//////////////////////////////////////////////////////////////////////////
// Position - should be between 0 & 100
//////////////////////////////////////////////////////////////////////////
typedef unsigned char Position;

//////////////////////////////////////////////////////////////////////////
// EntityPosition
//////////////////////////////////////////////////////////////////////////
enum EntityPosition {
	kPositionNone     = 0,
	kPosition_1     = 1,
	kPosition_3     = 3,
	kPosition_4     = 4,
	kPosition_500   = 500,
	kPosition_540   = 540,
	kPosition_750   = 750,
	kPosition_849   = 849,
	kPosition_850   = 850,
	kPosition_851   = 851,
	kPosition_1200  = 1200,
	kPosition_1430  = 1430,
	kPosition_1500  = 1500,
	kPosition_1540  = 1540,
	kPosition_1750  = 1750,
	kPosition_2000  = 2000,
	kPosition_2087  = 2087,
	kPosition_2086  = 2086,
	kPosition_2088  = 2088,
	kPosition_2110  = 2110,
	kPosition_2300  = 2300,
	kPosition_2410  = 2410,
	kPosition_2436  = 2436,
	kPosition_2490  = 2490,
	kPosition_2500  = 2500,
	kPosition_2587  = 2587,
	kPosition_2588  = 2588,
	kPosition_2690  = 2690,
	kPosition_2740  = 2740,
	kPosition_2830  = 2830,
	kPosition_2980  = 2980,
	kPosition_3050  = 3050,
	kPosition_3110  = 3110,
	kPosition_3390  = 3390,
	kPosition_3450  = 3450,
	kPosition_3500  = 3500,
	kPosition_3650  = 3650,
	kPosition_3760  = 3760,
	kPosition_3820  = 3820,
	kPosition_3890  = 3890,
	kPosition_3969  = 3969,
	kPosition_3970  = 3970,
	kPosition_4070  = 4070,
	kPosition_4100  = 4100,
	kPosition_4455  = 4455,
	kPosition_4460  = 4460,
	kPosition_4500  = 4500,
	kPosition_4590  = 4590,
	kPosition_4680  = 4680,
	kPosition_4689  = 4689,
	kPosition_4690  = 4690,
	kPosition_4691  = 4691,
	kPosition_4770  = 4470,
	kPosition_4840  = 4840,
	kPosition_5000  = 5000,
	kPosition_5090  = 5090,
	kPosition_5140  = 5140,
	kPosition_5419  = 5419,
	kPosition_5420  = 5420,
	kPosition_5440  = 5440,
	kPosition_5500  = 5500,
	kPosition_5540  = 5540,
	kPosition_5610  = 5610,
	kPosition_5790  = 5790,
	kPosition_5800  = 5800,
	kPosition_5810  = 5810,
	kPosition_5900  = 5900,
	kPosition_6000  = 6000,
	kPosition_6130  = 6130,
	kPosition_6160  = 6160,
	kPosition_6220  = 6220,
	kPosition_6410  = 6410,
	kPosition_6460  = 6460,
	kPosition_6470  = 6470,
	kPosition_6471  = 6471,
	kPosition_6800  = 6800,
	kPosition_6850  = 6850,
	kPosition_7000  = 7000,
	kPosition_7160  = 7160,
	kPosition_7250  = 7250,
	kPosition_7320  = 7320,
	kPosition_7500  = 7500,
	kPosition_7510  = 7510,
	kPosition_7850  = 7850,
	kPosition_7870  = 7870,
	kPosition_7900  = 7900,
	kPosition_7950  = 7950,
	kPosition_8000  = 8000,
	kPosition_8012  = 8012,
	kPosition_8013  = 8013,
	kPosition_8160  = 8160,
	kPosition_8200  = 8200,
	kPosition_8500  = 8500,
	kPosition_8512  = 8512,
	kPosition_8513  = 8513,
	kPosition_8514  = 8514,
	kPosition_8800  = 8800,
	kPosition_9020  = 9020,
	kPosition_9269  = 9269,
	kPosition_9250  = 9250,
	kPosition_9270  = 9270,
	kPosition_9271  = 9271,
	kPosition_9460  = 9460,
	kPosition_9500  = 9500,
	kPosition_30000 = 30000
};

//////////////////////////////////////////////////////////////////////////
// Field493
//////////////////////////////////////////////////////////////////////////
enum EntityField493 {
	kField493_0 = 0,
	kField493_1 = 1,
	kField493_2 = 2,
	kField493_3 = 3,
	kField493_4 = 4
};

//////////////////////////////////////////////////////////////////////////
// Car
//////////////////////////////////////////////////////////////////////////
enum CarIndex {
	kCarNone = 0,
	kCarBaggageRear = 1,
	kCarKronos = 2,
	kCarGreenSleeping = 3,
	kCarRedSleeping = 4,
	kCarRestaurant = 5,
	kCarBaggage = 6,
	kCarCoalTender = 7,
	kCarLocomotive = 8,
	kCar9 = 9
};

//////////////////////////////////////////////////////////////////////////
// Clothes
//////////////////////////////////////////////////////////////////////////
enum ClothesIndex {
	kClothesDefault = 0,
	kClothes1 = 1,
	kClothes2 = 2,
	kClothes3 = 3,

	kClothesInvalid
};

//////////////////////////////////////////////////////////////////////////
// Location of objects
//////////////////////////////////////////////////////////////////////////
enum ObjectLocation {
	kLocationNone = 0,
	kLocation1    = 1, // Floor?
	kLocation2    = 2, // Bed ?
	kLocation3    = 3,
	kLocation4    = 4, // Window ?
	kLocation5    = 5,
	kLocation6    = 6,
	kLocation7    = 7,
	kLocation10   = 10,
	kLocation11   = 11
};

//////////////////////////////////////////////////////////////////////////
// Entity direction
//////////////////////////////////////////////////////////////////////////
enum EntityDirection {
	kDirectionNone   = 0,
	kDirectionUp     = 1,
	kDirectionDown   = 2,
	kDirectionLeft   = 3,
	kDirectionRight  = 4,
	kDirectionSwitch = 5
};

//////////////////////////////////////////////////////////////////////////
// Combat
//////////////////////////////////////////////////////////////////////////
enum FightType {
	kFightMilos   = 2001,
	kFightAnna    = 2002,
	kFightIvo     = 2003,
	kFightSalko   = 2004,
	kFightVesna   = 2005
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
	kPortraitOriginal  = 32,
	kPortraitGreen     = 34,
	kPortraitYellow    = 36,

	kItemInvalid  = 128,

	kItem146 = 146
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
	kObjectOutsideTylerCompartment,
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
	kObjectTrainTimeTable,
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
	kObjectOutsideBetweenCompartments,
	kObjectOutsideAnnaCompartment,     // 45
	kObject46,
	kObject47,
	kObject48, // might be the egg
	kObject49,
	kObject50,                          // 50
	kObject51,
	kObject52,
	kObject53,
	kObject54,
	kObjectRestaurantCar,               // 55
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
	kObjectMax
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
	kEntity39,

	kEntitySteam = 255
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
	kActionNone            = 0,
	kAction1               = 1,
	kAction2               = 2,
	kActionExitCompartment = 3,
	kAction4               = 4,
	kActionExcuseMeCath    = 5,
	kActionExcuseMe        = 6,
	kAction8               = 8,
	kAction9               = 9,
	kAction10              = 10,
	kAction11              = 11,
	kActionDefault         = 12,
	kAction16              = 16,
	kActionDrawScene              = 17,
	kActionCallback        = 18,

	/////////////////////////////
	// Abbot
	/////////////////////////////
	kAction101169422 = 101169422,
	kAction104060776 = 104060776,
	kAction135600432 = 135600432,
	kAction157159392 = 157159392,
	kAction158480160 = 158480160,
	kAction192054567 = 192054567,
	kAction203073664 = 203073664,
	kAction222609266 = 222609266,

	/////////////////////////////
	// Alexei
	/////////////////////////////
	kAction135664192 = 135664192,

	/////////////////////////////
	// Alouan
	/////////////////////////////
	kAction189489753 = 189489753,
	kAction190219584 = 190219584,    // Francois

	/////////////////////////////
	// Anna
	/////////////////////////////
	kAction136702400 = 136702400,
	kAction157370960 = 157370960,
	kAction189299008 = 189299008,
	kAction191668032 = 191668032,	// some action during or before concert?
	kAction201437056 = 201437056,
	kAction235856512 = 235856512,
	kAction238936000 = 238936000,
	kAction291662081 = 291662081,

	/////////////////////////////
	// August
	/////////////////////////////
	kAction123793792 = 123793792,
	kAction168046720 = 168046720,
	kAction168627977 = 168627977,
	kAction203859488 = 203859488,
	kAction219522616 = 219522616,    // Servers0
	kAction225182640 = 225182640,

	/////////////////////////////
	// Boutarel
	/////////////////////////////
	kAction203520448 = 203520448,
	kAction237889408 = 237889408,

	/////////////////////////////
	// Chapters
	/////////////////////////////
	kAction135800432 = 135800432,
	kActionChapter3  = 139122728,
	kAction169629818 = 169629818,
	kAction171843264 = 171843264,

	/////////////////////////////
	// Cooks
	/////////////////////////////
	kAction101632192 = 101632192,
	kAction224849280 = 224849280,
	kAction236976550 = 236976550,

	/////////////////////////////
	// Coudert
	/////////////////////////////
	kAction154005632 = 154005632,
	kAction155991520 = 155991520,
	kAction157026693 = 157026693,
	kAction168253822 = 168253822,
	kAction168254872 = 168254872,
	kAction169557824 = 169557824,
	kAction171394341 = 171394341,    // Coudert / Mertens
	kAction185671840 = 185671840,
	kAction185737168 = 185737168,
	kAction188570113 = 188570113,
	kAction189026624 = 189026624,
	kAction189750912 = 189750912,
	kAction201431954 = 201431954,    // Coudert / Mertens / Verges
	kAction201439712 = 201439712,
	kAction205033696 = 205033696,
	kAction205346192 = 205346192,    // Coudert / Francois
	kAction225932896 = 225932896,
	kAction226031488 = 226031488,    // Coudert / Verges
	kAction292048641 = 292048641,
	kAction305159806 = 305159806,
	kAction326348944 = 326348944,
	kAction339669520 = 339669520,    // Coudert / Verges

	/////////////////////////////
	// Francois
	/////////////////////////////
	kAction100901266 = 100901266,
	kAction100957716 = 100957716,
	kAction101107728 = 101107728,

	/////////////////////////////
	// Gendarmes
	/////////////////////////////
	kAction168710784 = 168710784,
	kAction169499649 = 169499649,

	/////////////////////////////
	// Kahina
	/////////////////////////////
	kAction137503360 = 137503360,

	/////////////////////////////
	// Kronos
	/////////////////////////////
	kAction137685712 = 137685712,
	kAction171849314 = 171849314,

	/////////////////////////////
	// Mahmud
	/////////////////////////////
	kAction102227384 = 102227384,    // Mahmud / Mertens
	kAction156567128 = 156567128,
	kAction170483072 = 170483072,
	kAction225563840 = 225563840,

	/////////////////////////////
	// Max
	/////////////////////////////
	kAction71277948  = 71277948,
	kAction158007856 = 158007856,
	kAction101687594 = 101687594,
	kAction122358304 = 122358304,    // also Servers1/Boutarel?
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
	kAction88652208 = 88652208,      // Milos/Coudert
	kAction122865568 = 122865568,
	kAction123852928 = 123852928,
	kAction123199584 = 123199584,    // Milos/Coudert
	kAction157691176 = 157691176,
	kAction208228224 = 208228224,
	kAction221683008 = 221683008,
	kAction259125998 = 259125998,

	/////////////////////////////
	// Mme Boutarel
	/////////////////////////////
	kAction102484312 = 102484312,
	kAction102752636 = 102752636,
	kAction134289824 = 134289824,
	kAction168986720 = 168986720,
	kAction202221040 = 202221040,
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
	kAction55996766  = 55996766,
	kAction102675536 = 102675536,    // Ivo
	kAction136184016 = 136184016,

	/////////////////////////////
	// Servers 0
	/////////////////////////////
	kAction170016384 = 170016384,
	kAction188893625 = 188893625,
	kAction204704037 = 204704037,
	kAction207330561 = 207330561,
	kAction218128129 = 218128129,
	kAction218586752 = 218586752,
	kAction218983616 = 218983616,
	kAction223712416 = 223712416,
	kAction237485916 = 237485916,
	kAction252568704 = 252568704,
	kAction268773672 = 268773672,
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
	kAction101106391 = 101106391,
	kAction122288808 = 122288808,    // Servers1/Boutarel
	kAction123712592 = 123712592,    // Servers1/Ivo
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
	kAction124973510 = 124973510,
	kAction169360385 = 169360385,
	kAction191198209 = 191198209,
	kAction290869168 = 290869168,

	/////////////////////////////
	// Train
	/////////////////////////////
	kAction191070912 = 191070912,
	kActionTrainStopRunning = 191350523,
	kAction202613084 = 202613084,
	kAction203339360 = 203339360,
	kActionTrainStartRunning = 203419131,
	kAction203863200 = 203863200,
	kAction222746496 = 222746496,
	kActionBreakCeiling = 225056224,
	kAction290410610 = 290410610,
	kActionJumpDownCeiling = 338494260,

	/////////////////////////////
	// Verges
	/////////////////////////////
	kAction125233040 = 125233040,   // Verges / Abbot
	kAction158617345 = 158617345,
	kAction167854368 = 167854368,
	kAction168187490 = 168187490,
	kAction168255788 = 168255788,
	kAction191337656 = 191337656,

	/////////////////////////////
	// Vassili
	/////////////////////////////
	kAction122732000 = 122732000,
	kAction168459827 = 168459827,
	kAction191477936 = 191477936,

	/////////////////////////////
	// Vesna
	/////////////////////////////
	kAction124190740 = 124190740,
	kAction134427424 = 134427424,
	kAction135024800 = 135024800,
	kAction137165825 = 137165825,
	kAction190412928 = 190412928,
	kAction204832737 = 204832737,

	/////////////////////////////
	// Misc
	/////////////////////////////
	kAction158610240 = 158610240,
	kAction167992577 = 167992577,
	kAction168646401 = 168646401,
	kAction169300225 = 169300225,
	kAction169773228 = 169773228,
	kActionEndChapter = 190346110,
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
	kAction226078300 = 226078300, // Whistle

	kActionEnd
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SHARED_H
