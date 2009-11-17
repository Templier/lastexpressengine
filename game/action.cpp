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

#include "lastexpress/game/action.h"

#include "lastexpress/data/animation.h"
#include "lastexpress/data/snd.h"
#include "lastexpress/data/scene.h"

#include "lastexpress/entities/abbot.h"
#include "lastexpress/entities/entity.h"

#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

// List of animations
const static struct {
	const char *filename;
	uint16 time;
} animationList[273] = {
	{"", 0},
	{"1002",	255},
	{"1002D",	255},
	{"1003",	0},
	{"1005",	195},
	{"1006",	750},	// 5
	{"1006A",	750},
	{"1008",	765},
	{"1008N",	765},
	{"1008A",	750},
	{"1008AN",	750},	// 10
	{"1009",	0},
	{"1011",	1005},
	{"1011A",	780},
	{"1012",	300},
	{"1013",	285},
	{"1017",	870},	// 15
	{"1017A",	0},		// Not in the data files?
	{"1019",	120},
	{"1019D",	120},
	{"1020",	120},	// 20
	{"1022",	525},
	{"1022A",	180},
	{"1022AD",	210},
	{"1022B",	210},
	{"1022C",	210},	// 25
	{"1023",	135},
	{"1025",	945},
	{"1028",	300},
	{"1030",	390},
	{"1031",	375},	// 30
	{"1032",	1050},
	{"1033",	945},
	{"1034",	495},
	{"1035",	1230},
	{"1037",	1425},	// 35
	{"1038",	195},
	{"1038A",	405},
	{"1039",	600},
	{"1040",	945},
	{"1041",	510},	// 40
	{"1042",	540},
	{"1043",	855},
	{"1044",	645},
	{"1046",	0},
	{"1047",	0},		// 45
	{"1047A",	0},
	{"1059",	1005},
	{"1060",	255},
	{"1063",	0},
	{"1101",	255},	// 50
	{"1102",	1320},
	{"1103",	210},
	{"1104",	120},
	{"1105",	1350},
	{"1106",	315},	// 55
	{"1106A",	315},
	{"1106D",	315},
	{"1107",	1},
	{"1107A",	660},
	{"1108",	300},	// 60
	{"1109",	1305},
	{"1110",	300},
	{"1112",	0},
	{"1115",	0},
	{"1115A",	0},		// 65
	{"1115B",	0},
	{"1115C",	0},
	{"1115D",	0},
	{"1115E",	0},
	{"1115F",	0},		// 70
	{"1115G",	0},
	{"1115H",	0},
	{"1116",	0},
	{"1117",	0},
	{"1118",	105},	// 75
	{"1202",	510},
	{"1202A",	510},
	{"1203",	720},
	{"1204",	120},
	{"1205",	465},	// 80
	{"1206",	690},
	{"1206A",	450},
	{"1208",	465},
	{"1210",	1020},
	{"1211",	600},	// 85
	{"1212",	435},
	{"1213",	525},
	{"1213A",	150},
	{"1215",	390},
	{"1216",	0},		// 90
	{"1219",	240},
	{"1222",	1095},
	{"1223",	0},
	{"1224",	720},
	{"1225",	1005},	// 95
	{"1227",	840},
	{"1227A",	840},
	{"1303",	450},
	{"1303N",	450},
	{"1304",	450},	// 100
	{"1304N",	450},
	{"1305",	630},
	{"1309",	0},
	{"1311",	1710},
	{"1312",	240},	// 105
	{"1312D",	240},
	{"1313",	930},
	{"1315",	1035},
	{"1315A",	1035},
	{"1401",	540},	// 110
	{"1402",	150},
	{"1402B",	150},
	{"1403",	90},
	{"1404",	885},
	{"1404A",	0},		// 115
	{"1405",	135},
	{"1406",	1665},
	{"1501",	285},
	{"1501A",	285},
	{"1502",	165},	// 120
	{"1502A",	165},
	{"1502D",	165},
	{"1503",	0},
	{"1504",	0},
	{"1505",	0},		// 125
	{"1505A",	0},
	{"1506",	300},
	{"1506A",	180},
	{"1508",	0},
	{"1509",	450},	// 130
	{"1509S",	450},
	{"1509A",	450},
	{"1509AS",	450},
	{"1509N",	450},
	{"1509SN",	450},	// 135
	{"1509AN",	450},
	{"1509BN",	450},
	{"1511",	150},
	{"1511A",	150},
	{"1511B",	90},	// 140
	{"1511BA",	90},
	{"1511C",	135},
	{"1511D",	105},
	{"1930",	0},
	{"1511E",	150},	// 145
	{"1512",	165},
	{"1513",	180},
	{"1517",	0},
	{"1517A",	165},
	{"1518",	165},	// 150
	{"1518A",	165},
	{"1518B",	165},
	{"1591",	450},
	{"1592",	450},
	{"1593",	450},	// 155
	{"1594",	450},
	{"1595",	450},
	{"1596",	450},
	{"1601",	0},
	{"1603",	0},		// 160
	{"1606B",	315},
	{"1607A",	0},
	{"1610",	0},
	{"1611",	0},
	{"1612",	0},		// 165
	{"1615",	0},
	{"1619",	0},
	{"1620",	120},
	{"1621",	105},
	{"1622",	105},	// 170
	{"1629",	450},
	{"1630",	450},
	{"1631",	525},
	{"1632",	0},
	{"1633",	615},	// 175
	{"1634",	180},
	{"1702",	180},
	{"1702DD",	180},
	{"1702NU",	180},
	{"1702ND",	180},	// 180
	{"1704",	300},
	{"1704D",	300},
	{"1705",	195},
	{"1705D",	195},
	{"1706",	195},	// 185
	{"1706DD",	195},
	{"1706ND",	195},
	{"1706NU",	195},
	{"1901",	135},
	{"1902",	1410},	// 190
	{"1903",	0},
	{"1904",	1920},
	{"1908",	600},
	{"1908A",	195},
	{"1908B",	105},	// 195
	{"1908C",	165},
	{"1908CD",	0},
	{"1909A",	150},
	{"1909B",	150},
	{"1909C",	150},	// 200
	{"1910A",	180},
	{"1910B",	180},
	{"1910C",	180},
	{"1911A",	90},
	{"1911B",	90},	// 205
	{"1911C",	90},
	{"1912",	0},
	{"1913",	0},
	{"1917",	0},
	{"1918",	390},	// 210
	{"1919",	360},
	{"1919A",	105},
	{"1920",	75},
	{"1922",	75},
	{"1923",	150},	// 215
	{"8001",	120},
	{"8001A",	120},
	{"8002",	120},
	{"8002A",	120},
	{"8002B",	120},	// 220
	{"8003",	105},
	{"8003A",	105},
	{"8004",	105},
	{"8004A",	105},
	{"8005",	270},	// 225
	{"8005B",	270},
	{"8010",	270},
	{"8013",	120},
	{"8013A",	120},
	{"8014",	165},	// 230
	{"8014A",	165},
	{"8014R",	165},
	{"8014AR",	165},
	{"8015",	150},
	{"8015A",	150},	// 235
	{"8015R",	150},
	{"8015AR",	150},
	{"8017",	120},
	{"8017A",	120},
	{"8017R",	120},	// 240
	{"8017AR",	120},
	{"8017N",	90},
	{"8023",	135},
	{"8023A",	135},
	{"8023M",	135},	// 245
	{"8024",	150},
	{"8024A",	180},
	{"8024M",	180},
	{"8025",	150},
	{"8025A",	150},	// 250
	{"8025M",	150},
	{"8027",	75},
	{"8028",	75},
	{"8029",	120},
	{"8029A",	120},	// 255
	{"8031",	375},
	{"8032",	0},
	{"8032A",	0},
	{"8033",	105},
	{"8035",	195},	// 260
	{"8035A",	120},
	{"8035B",	180},
	{"8035C",	135},
	{"8036",	105},
	{"8037",	195},	// 265
	{"8037A",	195},
	{"8040",	240},
	{"8040A",	240},
	{"8041",	195},
	{"8041A",	195},	// 270
	{"8042",	600},
	{"8042A",	600}
};

Action::Action(LastExpressEngine *engine) : _engine(engine) {}

//////////////////////////////////////////////////////////////////////////
// Action
//////////////////////////////////////////////////////////////////////////
void Action::knockOnDoor(byte item) {
	if (item >= 128)
		return;

	if (getObjects()->get(item).field_0)
		getSavePoints()->push(0, getObjects()->get(item).field_0, 8, item);
	else
		playEventSound(0, 12, 0);
}

void Action::openCloseItem(byte item, byte action) {
	if (item >= 128)
		return;

	getObjects()->update(item, getObjects()->get(item).field_0, action, 255, 255);

	bool isNotWindow = ((item < 9  || item > 16) && (item < 40 || item > 47));

	switch (action) {
	case 1:
		if (isNotWindow)
			playEventSound(0, 24, 0);
		else
			playEventSound(0, 21, 0);
		break;

	case 2:
		if (isNotWindow)
			playEventSound(0, 36, 0);
		else
			playEventSound(0, 20, 0);
		break;

	default:
		break;
	}
}

void Action::action10(byte item, byte field4) {
	if (item >= 128)
		return;

	getObjects()->updateField4(item, field4);

	if (item != 112 /* TODO: or LIB096 does not exist */) {
		if (item == 1)
			playEventSound(0, 73, 0);
	} else {
		playEventSound(0, 96, 0);	
	}
}

void Action::setItemLocation(Inventory::InventoryItem item, byte location) {
	Inventory::InventoryEntry* entry = getInventory()->getEntry(item);

	if (!entry->has_item)
		return;

	entry->location = location;

	if (item == Inventory::kCorpse) {
		byte corpseLocation = getInventory()->getEntry(Inventory::kCorpse)->location;

		if (corpseLocation == kCorpseLocation3 || corpseLocation == kCorpseLocationWindow)
			getProgress().field_8 = 1;
		else
			getProgress().field_8 = 0;
	}
}

bool Action::pickItem(Inventory::InventoryItem item, byte location, bool process) {
	Inventory::InventoryEntry* entry = getInventory()->getEntry(item);

	if (item >= 32 || !entry->location)
		return false;

	// Special case for corpse
	if (item == Inventory::kCorpse) {
		pickCorpse(location, process);		
		return false;
	}

	// Add and process items
	getInventory()->addItem(item);

	switch (item) {
	case Inventory::kGreenJacket:
		pickGreenJacket(process);
		break;

	case Inventory::kScarf:
		pickScarf(process);

		// stop processing
		return false;

	case Inventory::kParchemin:
		if (location != 2)
			break;

		getInventory()->addItem(Inventory::kParchemin);
		getInventory()->getEntry(Inventory::kItem11)->location = 1;
		playEventSound(0, 9, 0);
		break;

	case Inventory::kBomb:
		//getEntities()->reset(SavePoints::kAbbot, &Abbot::setup_pickBomb);
		error("Logic::processHotspot: pickItem case for item bomb is not implemented!");
		break;

	case Inventory::kBriefcase:
		playEventSound(0, 83, 0);
		break;

	default:
		break;
	}

	return true;
}

void Action::dropItem(Inventory::InventoryItem item, byte location, bool process) 
{
	if (item >= 32)
		return;

	if (!getInventory()->hasItem(item))
		return;

	if (location < 1)
		return;

	// Handle actions
	if (item == Inventory::kBriefcase) {
		playEventSound(0, 82, 0);

		if (location == 2) {
			if (!getProgress().field_58) {
				_engine->getLogic()->savegame();
				getProgress().field_58 = 1;
			}

			if (getInventory()->getEntry(Inventory::kParchemin)->location == 2) {
				getInventory()->addItem(Inventory::kParchemin);
				getInventory()->getEntry(Inventory::kItem11)->location = 11;
				playEventSound(0, 9, 0);
			}
		}
	}

	// Update item location
	getInventory()->removeItem(item, location);

	if (item == Inventory::kCorpse)
		dropCorpse(process);

	// Unselect item
	getInventory()->unselectItem();
}

void Action::pickGreenJacket(bool process) {
	getProgress().jacket = Logic::kGreenJacket;
	getInventory()->addItem(Inventory::kMatchBox);

	getObjects()->update(9, 0, 2, 255, 255);	
	playAnimation(kPickGreenJacket);

	getInventory()->setPortrait(Inventory::kPortraitGreen);

	if (process)
		_engine->getLogic()->processScene();
}

void Action::pickScarf(bool process) {
	if (getProgress().jacket == Logic::kOriginalJacket)
		playAnimation(kPickScarfGreen);
	else
		playAnimation(kPickScarfOriginal);

	if (process)
		_engine->getLogic()->processScene();
}

void Action::pickCorpse(byte bedPosition, bool process) {

	switch(getInventory()->getEntry(Inventory::kCorpse)->location) {
	// Floor
	case kCorpseLocationFloor:
		if (bedPosition != 4) {
			if (getProgress().jacket == Logic::kOriginalJacket)
				playAnimation(kCorpsePickFloorOriginal);
			else
				playAnimation(kCorpsePickFloorGreen);

			break;
		}

		playAnimation(kCorpsePickFloorOpenedBedOriginal);
		getInventory()->getEntry(Inventory::kCorpse)->location = 5;
		break;

	// Bed
	case kCorpseLocationBed:	
		if (getProgress().jacket == Logic::kOriginalJacket)
			playAnimation(kCorpsePickBedOriginal);
		else
			playAnimation(kCorpsePickBedGreen);

		break;

	// No way to pick the corpse
	default:		
		break;
	}

	if (process)
		_engine->getLogic()->processScene();

	// Add corpse to inventory
	if (bedPosition != 4) { // bed position
		getInventory()->addItem(Inventory::kCorpse);
		getInventory()->selectItem(Inventory::kCorpse);
		_engine->getCursor()->setStyle(Cursor::kCursorCorpse);
	}
}

void Action::dropCorpse(bool process) {
	switch(getInventory()->getEntry(Inventory::kCorpse)->location) {
	case 1:	// Floor
		if (getProgress().jacket == Logic::kOriginalJacket)
			playAnimation(kCorpseDropFloorOriginal);
		else
			playAnimation(kCorpseDropFloorGreen);

		break;

	case 2:	// Bed
		if (getProgress().jacket == Logic::kOriginalJacket)
			playAnimation(kCorpseDropBedOriginal);
		else
			playAnimation(kCorpseDropBedGreen);

		break;

	case 4: // Window
		// Say goodbye to an old friend
		getInventory()->getEntry(Inventory::kCorpse)->location = 0;
		getProgress().field_20 = 1;

		if (getState()->time <= 1138500) {

			if (getProgress().jacket == Logic::kOriginalJacket)
				playAnimation(kCorpseDropWindowOriginal);
			else
				playAnimation(kCorpseDropWindowGreen);
		
			getProgress().field_24 = 1;
		} else {
			playAnimation(kCorpseDropBridge);
		}

		getProgress().field_8 = 1;
		break;
	}

	if (process)
		_engine->getLogic()->processScene();
}

//////////////////////////////////////////////////////////////////////////
// Cursors
//////////////////////////////////////////////////////////////////////////
Cursor::CursorStyle Action::getCursor(byte action, byte param1, byte param2, byte param3, byte cursor)
{
	// Simple cursor style
	if (cursor != 128)
		return (Cursor::CursorStyle)cursor;

	switch (action) {
	default:
		return Cursor::kCursorNormal;

	case SceneHotspot::kActionInventory:
		if (!getState()->sceneBackup2 && (getEvent(Action::kKronosBringFirebird) || getProgress().field_74))				
			return Cursor::kCursorNormal;
		else
			return Cursor::kCursorBackward;		

	case SceneHotspot::kActionKnockOnDoor:
		if (param1 >= 128)
			return Cursor::kCursorNormal;
		else
			return (Cursor::CursorStyle)getObjects()->get(param1).cursor;

LABEL_KEY:
	case SceneHotspot::kAction6:
	case SceneHotspot::kActionExitCompartment:
		if (param1 >= 128)
			return Cursor::kCursorNormal;

		if (1/* test with savegame data */)
			return Cursor::kCursorForward; // HACK should be extracted from savegame data 
		else
			return Cursor::kCursorKey;


	case SceneHotspot::kAction12:
		if (param1 >= 128)
			return Cursor::kCursorNormal;
		else {
			if (getObjects()->get(param1).field_0)
				return (Cursor::CursorStyle)getObjects()->get(param1).cursor;
			else
				return Cursor::kCursorNormal;
		}

	case SceneHotspot::kActionPickItem:
		if (param1 >= 32)
			return Cursor::kCursorNormal;

		if ((!getInventory()->getSelectedItem() || getInventory()->getSelectedEntry()->no_autoselect)
			&& (param1 != 21 || getProgress().field_8 == 1))
			return Cursor::kCursorHand;
		else
			return Cursor::kCursorNormal;			

	case SceneHotspot::kActionDropItem:
		if (param1 >= 32)
			return Cursor::kCursorNormal;

		if (getInventory()->getSelectedItem() != param1)
			return Cursor::kCursorNormal;

		if (param1 == 20 && param2 == 4 && !getProgress().field_50)
			return Cursor::kCursorNormal;

		if (param1 == 18  && param2 == 1 && getProgress().field_5C)
			return Cursor::kCursorNormal;

		return (Cursor::CursorStyle)getInventory()->getSelectedEntry()->item_id;

	case SceneHotspot::kAction15:
		if (param1 >= 128)
			return Cursor::kCursorNormal;

		if (*(&getProgress().field_0 + param1) == param2)
			return (Cursor::CursorStyle)param3;

		return Cursor::kCursorNormal; 

	case SceneHotspot::kActionEnterCompartment:
		if (getInventory()->getSelectedItem() != Inventory::kKey)
			goto LABEL_KEY;

		// TODO check other savegame struct...

		if (!getInventory()->hasItem(Inventory::kKey))
			goto LABEL_KEY;

		if (getInventory()->getSelectedItem() != Inventory::kFirebird && getInventory()->getSelectedItem() != Inventory::kBriefcase)
			goto LABEL_KEY;

		return Cursor::kCursorKey;

	case SceneHotspot::kActionOutsideTrain:
		if (getProgress().jacket != Logic::kGreenJacket)
			return Cursor::kCursorNormal;

		if ((getEvent(Action::kCathLookOutsideWindowDay) || getEvent(Action::kCathLookOutsideWindowDay) || getObjects()->get(1).field_4)
			&& getProgress().field_50
			&& (param1 != 45 || (1/*function call*/ && getObjects()->get(44).location == 2))
			&& getInventory()->getSelectedItem() != Inventory::kBriefcase
			&& getInventory()->getSelectedItem() != Inventory::kFirebird)
			return Cursor::kCursorForward; 

		return Cursor::kCursorNormal; 

	case SceneHotspot::kAction19:
		error("Action::getCursor: unsupported cursor for action (%02d)", action);

	case SceneHotspot::kActionClimbUpTrain:
		if (getProgress().field_50
			&& (getProgress().chapter == Logic::kChapter2 || getProgress().chapter == Logic::kChapter3 || getProgress().chapter == Logic::kChapter5)
			&& getInventory()->getSelectedItem() != Inventory::kFirebird 
			&& getInventory()->getSelectedItem() != Inventory::kBriefcase)
			return Cursor::kCursorUp;

		return Cursor::kCursorNormal; 

	case SceneHotspot::kActionClimbDownTrain:
		error("Action::getCursor: unsupported cursor for action (%02d)", action);

	case SceneHotspot::kActionUnbound:
		if (param2 != 2)
			return Cursor::kCursorNormal; 

		if (getEvent(Action::kCathBurnRope) || !getEvent(Action::kCathStruggleWithBonds2))
			return Cursor::kCursorNormal; 

		return Cursor::kCursorHand; 

	case SceneHotspot::kActionCatchBeetle:	
		error("Action::getCursor: unsupported cursor for action (%02d)", action);

	case SceneHotspot::KActionUseWhistle:
		if (param1 != 3)
			return Cursor::kCursorNormal; 

		if (getInventory()->getSelectedItem() == Inventory::kWhistle)
			return Cursor::kCursorWhistle;
		else
			return Cursor::kCursorNormal; 

	case SceneHotspot::kActionOpenBed:
		if (getProgress().chapter < Logic::kChapter2)
			return Cursor::kCursorHand;

		return Cursor::kCursorNormal;		

	case SceneHotspot::kActionDialog:
		if (getSound()->getDialogName((Sound::DialogId)param1))
			return Cursor::kCursorHandPointer; 

		return Cursor::kCursorNormal;

	case SceneHotspot::kActionBed:
		if (getProgress().field_18 == 2 && !getProgress().field_E4
			&& (getState()->time > 1404000 
			|| (getProgress().event_august_met && getProgress().field_CC 
			&& (!getProgress().field_24 || getProgress().field_3C))))
			return Cursor::kCursorSleep;

		return Cursor::kCursorNormal;
	}
}

//////////////////////////////////////////////////////////////////////////
// Animation
//////////////////////////////////////////////////////////////////////////

// Play an animation and add delta time to global game time
void Action::playAnimation(int index) {
	assert(index > 0 || (uint)index < sizeof(animationList));

	//bool unknown = false;
	//if (index >= 212)
	//	unknown = true;

	// Show inventory & hourglass
	getInventory()->show(true);
	getInventory()->showHourGlass(true);

	Animation animation;
	if (animation.loadFile(Common::String(animationList[index].filename) + ".nis"))
		animation.play();	

	// Adjust game time
	getEvent(index) = 1;
	getState()->timeTicks += animationList[index].time;
	getState()->time += animationList[index].time * getState()->timeDelta;

	getInventory()->showHourGlass(false);
}


} // End of namespace LastExpress
