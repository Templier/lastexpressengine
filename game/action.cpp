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
#include "lastexpress/entities/anna.h"
#include "lastexpress/entities/entity.h"

#include "lastexpress/game/beetle.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/logic.h"
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

Action::Action(LastExpressEngine *engine) : _engine(engine) {
	ADD_ACTION(dummy);
	ADD_ACTION(inventory);
	ADD_ACTION(savePoint);
	ADD_ACTION(playSound);
	ADD_ACTION(playMusic);
	ADD_ACTION(knock);
	ADD_ACTION(compartment);
	ADD_ACTION(playSounds);
	ADD_ACTION(playAnimation);
	ADD_ACTION(openCloseObject);
	ADD_ACTION(10);
	ADD_ACTION(setItemLocation);
	ADD_ACTION(12);
	ADD_ACTION(pickItem);
	ADD_ACTION(dropItem);
	ADD_ACTION(dummy);
	ADD_ACTION(enterCompartment);
	ADD_ACTION(dummy);
	ADD_ACTION(getOutsideTrain);
	ADD_ACTION(slip);
	ADD_ACTION(getInsideTrain);
	ADD_ACTION(climbUpTrain);
	ADD_ACTION(climbDownTrain);
	ADD_ACTION(jumpUpDownTrain);
	ADD_ACTION(unbound);
	ADD_ACTION(25);
	ADD_ACTION(26);
	ADD_ACTION(27);
	ADD_ACTION(concertSitCough);
	ADD_ACTION(29);
	ADD_ACTION(catchBeetle);
	ADD_ACTION(exitCompartment);
	ADD_ACTION(32);
	ADD_ACTION(useWhistle);
	ADD_ACTION(openMatchBox);
	ADD_ACTION(openBed);
	ADD_ACTION(dummy);
	ADD_ACTION(dialog);
	ADD_ACTION(eggBox);
	ADD_ACTION(39);
	ADD_ACTION(bed);
	ADD_ACTION(41);
	ADD_ACTION(42);
	ADD_ACTION(dummy);
	ADD_ACTION(44);
}

Action::~Action() {	
	for (uint i = 0; i < _actions.size(); i++)
		delete _actions[i];
}

//////////////////////////////////////////////////////////////////////////
// Processing hotspot
//////////////////////////////////////////////////////////////////////////
void Action::processHotspot(SceneHotspot *hotspot) {
	if (!hotspot || !hotspot->action || hotspot->action >= _actions.size())
		return;

	(*_actions[hotspot->action])(hotspot);
}

//////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(dummy) {
	error("Action::action_dummy: Function should never be called!");
}

IMPLEMENT_ACTION(inventory) {
	if (!getState()->sceneUseBackup)
		return;

	int index = 0;
	if (getState()->sceneBackup2) {
		index = getState()->sceneBackup2;
		getState()->sceneBackup2 = 0;
	} else {
		getState()->sceneUseBackup = 0;
		index = getState()->sceneBackup;

		Scene *backup = _engine->getScene(getState()->sceneBackup);

		if (getState()->field1000[backup->getHeader()->field_15 + 100 * backup->getHeader()->field_13])
			index = getLogic()->processIndex(getState()->sceneBackup);

		delete backup;
	}

	getLogic()->loadScene(index);	

	if (!getInventory()->getSelectedItem())
		return;

	if (!getInventory()->getSelectedEntry()->is_selectable || (!getState()->sceneBackup2 && getInventory()->getFirstExaminableItem()))
		getInventory()->selectItem(getInventory()->getFirstExaminableItem());
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(savePoint) {
	getSavePoints()->push(SavePoints::kEntityNone, (SavePoints::EntityIndex)hotspot->param1, (SavePoints::ActionIndex)hotspot->param2, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(playSound) {
	if (hotspot->param2)
		getSound()->playSoundEvent(0, hotspot->param1, hotspot->param2);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(playMusic) {
	if (hotspot->param1 != 50 || getProgress().chapter == State::kChapter5)
		getSound()->playMusic(SavePoints::kEntityNone, hotspot->param1, 16, hotspot->param2);	
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(knock) {
	Objects::ObjectIndex object = (Objects::ObjectIndex)hotspot->param1;
	
	if (object >= 128)
		return;
	
	if (getObjects()->get(object).entity)
		getSavePoints()->push(SavePoints::kEntityNone, getObjects()->get(object).entity, SavePoints::kAction8, object);
	else
		getSound()->playSoundEvent(0, 12, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(compartment) {
	Objects::ObjectIndex object = (Objects::ObjectIndex)hotspot->param1;

	if (object >= 128)
		return;
	
	if (getObjects()->get(object).entity) {
		getSavePoints()->push(SavePoints::kEntityNone, getObjects()->get(object).entity, SavePoints::kAction9, object);
		hotspot->scene = 0;
		return;
	}

	if (handleOtherCompartment(object, 1, 1)) {
		hotspot->scene = 0;
		return;
	}

	byte location = getObjects()->get(object).location;
	if (location == 1 || location == 3 || getEntities()->checkFields2(object)) {

		// FIXME check again, this might be wrong (and simplify expression)
		if (location != 1 || getEntities()->checkFields2(object) || (getInventory()->getSelectedItem() != Inventory::kKey
		&& (location != 1 || !getInventory()->hasItem(Inventory::kKey) 
		|| getInventory()->getSelectedItem() != Inventory::kFirebird || getInventory()->getSelectedItem() != Inventory::kBriefcase))) {
				getSound()->playSoundEvent(0, 13, 0);
				hotspot->scene = 0;
				return;
		}

		getSound()->playSoundEvent(0, 32, 0);

		if ((object >= 1 && object <= 3) || (object >= 32 && object <= 37))
			getObjects()->update(object, SavePoints::kEntityNone, 0, Cursor::kCursorHandKnock, 9);

		getSound()->playSoundEvent(0, 15, 22);
		getInventory()->unselectItem();

		return;
	}

	if (hotspot->action != 16 || getInventory()->getSelectedItem() != Inventory::kKey) {
		if (object == 109) {
			getSound()->playSoundEvent(0, 26, 0);
		} else {
			getSound()->playSoundEvent(0, 14, 0);
			getSound()->playSoundEvent(0, 15, 22);
		}
		return;
	}

	getObjects()->update(Objects::kObjectCompartment1, SavePoints::kEntityNone, 1, Cursor::kCursorHandKnock, 9);
	getSound()->playSoundEvent(0, 16, 0);
	getInventory()->unselectItem();
	hotspot->scene = 0;
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(playSounds) {
	getSound()->playSoundEvent(0, hotspot->param1, 0);
	getSound()->playSoundEvent(0, hotspot->param3, hotspot->param2);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(playAnimation) {
	if (getEvent(hotspot->param1))
		return;

	playAnimation(hotspot->param1);

	if (!hotspot->scene)
		getLogic()->processScene();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(openCloseObject) {
	Objects::ObjectIndex object = (Objects::ObjectIndex)hotspot->param1;
	byte location = hotspot->param2;

	if (object >= 128)
		return;
	
	getObjects()->update(object, getObjects()->get(object).entity, location, Cursor::kCursorKeepValue, 255);

	bool isNotWindow = ((object < 9  || object > 16) && (object < 40 || object > 47));

	switch (location) {
	case 1:
		if (isNotWindow)
			getSound()->playSoundEvent(0, 24, 0);
		else
			getSound()->playSoundEvent(0, 21, 0);
		break;

	case 2:
		if (isNotWindow)
			getSound()->playSoundEvent(0, 36, 0);
		else
			getSound()->playSoundEvent(0, 20, 0);
		break;

	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(10) {
	Objects::ObjectIndex object = (Objects::ObjectIndex)hotspot->param1;

	if (object >= 128)
		return;

	getObjects()->updateField4(object, hotspot->param2);

	if (object != 112 /* TODO: or LIB096 does not exist -> is it needed, say if the HPF is not loaded or something */) {
		if (object == 1)
			getSound()->playSoundEvent(0, 73, 0);
	} else {
		getSound()->playSoundEvent(0, 96, 0);	
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(setItemLocation) {
	Inventory::InventoryItem item = (Inventory::InventoryItem)hotspot->param1;
	Inventory::InventoryEntry* entry = getInventory()->getEntry(item);

	if (!entry->has_item)
		return;

	entry->location = hotspot->param2;

	if (item == Inventory::kCorpse) {
		byte corpseLocation = getInventory()->getEntry(Inventory::kCorpse)->location;

		if (corpseLocation == kCorpseLocation3 || corpseLocation == kCorpseLocationWindow)
			getProgress().field_8 = 1;
		else
			getProgress().field_8 = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(12) {
	Objects::ObjectIndex object = (Objects::ObjectIndex)hotspot->param1;

	if (object >= 128)
		return;

	if (getObjects()->get(object).entity)
		getSavePoints()->push(SavePoints::kEntityNone, getObjects()->get(object).entity, SavePoints::kAction8, object);

}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(pickItem) {
	Inventory::InventoryItem item = (Inventory::InventoryItem)hotspot->param1;
	Inventory::InventoryEntry* entry = getInventory()->getEntry(item);
	byte location = hotspot->param2;
	bool process = (hotspot->scene == 0);

	if (item >= 32 || !entry->location)
		return;

	// Special case for corpse
	if (item == Inventory::kCorpse) {
		pickCorpse(location, process);		
		return;
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
		return;

	case Inventory::kParchemin:
		if (location != 2)
			break;

		getInventory()->addItem(Inventory::kParchemin);
		getInventory()->getEntry(Inventory::kItem11)->location = 1;
		getSound()->playSoundEvent(0, 9, 0);
		break;

	case Inventory::kBomb:
		getEntities()->reset(SavePoints::kEntityAbbot);
		((Abbot*)getEntities()->get(SavePoints::kEntityAbbot))->setup_pickBomb();
		break;

	case Inventory::kBriefcase:
		getSound()->playSoundEvent(0, 83, 0);
		break;

	default:
		break;
	}

	// Load item scene
	if (getInventory()->getEntry(item)->scene_id) {
		if (!getState()->sceneUseBackup) {
			getState()->sceneUseBackup = 1;
			getState()->sceneBackup = (hotspot->scene ? hotspot->scene : getState()->scene);
		}

		getLogic()->loadScene(getInventory()->getEntry(item)->scene_id);
		hotspot->scene = 0;
	}

	// Select item
	if (getInventory()->getEntry(item)->is_selectable) {
		getInventory()->selectItem(item);
		_engine->getCursor()->setStyle((Cursor::CursorStyle)getInventory()->getEntry(item)->item_id);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(dropItem) {
	Inventory::InventoryItem item = (Inventory::InventoryItem)hotspot->param1;
	byte location = hotspot->param2;
	bool process = (hotspot->scene == 0);

	if (item >= 32)
		return;

	if (!getInventory()->hasItem(item))
		return;

	if (location < 1)
		return;

	// Handle actions
	if (item == Inventory::kBriefcase) {
		getSound()->playSoundEvent(0, 82, 0);

		if (location == 2) {
			if (!getProgress().field_58) {
				getLogic()->savegame(1, 0, 0);
				getProgress().field_58 = 1;
			}

			if (getInventory()->getEntry(Inventory::kParchemin)->location == 2) {
				getInventory()->addItem(Inventory::kParchemin);
				getInventory()->getEntry(Inventory::kItem11)->location = 11;
				getSound()->playSoundEvent(0, 9, 0);
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

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(enterCompartment) {
	if (getObjects()->get(Objects::kObjectCompartment1).location == 1 || getObjects()->get(Objects::kObjectCompartment1).location == 3 || getInventory()->getSelectedItem() == Inventory::kKey) {
		action_compartment(hotspot);
		return;
	}

	if (getProgress().event_found_corpse) {
		if (hotspot->action != 16 || getInventory()->getEntry(Inventory::kBriefcase)->location != 2) {
			action_compartment(hotspot);
		} else {				
			getSound()->playSoundEvent(0, 14, 0);
			getSound()->playSoundEvent(0, 15, 22);

			if (getProgress().field_78) {
				getSound()->playSound(SavePoints::kEntityNone, "MUS003", 16, 0);
				getProgress().field_78 = 0;
			}
			
			getLogic()->loadSceneFromData(3, 77, 255);			
			hotspot->scene = 0;
		}
	} else {
		getLogic()->savegame(1, 0, 0);
		getSound()->playSound(SavePoints::kEntityNone, "LIB014", -1, 0);		
		playAnimation(kCathFindCorpse);
		getSound()->playSound(SavePoints::kEntityNone, "LIB015", -1, 0);
		getProgress().event_found_corpse = 1;
		hotspot->scene = 42; // Tyler compartment with corpse on floor
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(getOutsideTrain) {
	byte action = hotspot->param1;

	if ((getEvent(kCathLookOutsideWindowDay) || getEvent(kCathLookOutsideWindowNight) || getObjects()->get(Objects::kObjectCompartment1).field_4)
	  && getProgress().field_50
	  && (action != 45 || (!getEntities()->checkFields1(SavePoints::kEntityRebecca, 4, 4840) && getObjects()->get(Objects::kObject44).location == 2))
	  && getInventory()->getSelectedItem() != Inventory::kFirebird
	  && getInventory()->getSelectedItem() != Inventory::kBriefcase) {

		switch (action) {
		default:
			return;

		case 9:
			getEvent(kCathLookOutsideWindowDay) = 1;
			playAnimation(isDay() ? kCathGoOutsideTylerCompartmentDay : kCathGoOutsideTylerCompartmentNight);
			getProgress().field_C8 = 1;
			break;

		case 44:
			getEvent(kCathLookOutsideWindowDay) = 1;
			playAnimation(isDay() ? kCathGoOutsideDay : kCathGoOutsideNight);
			getProgress().field_C8 = 1;
			break;

		case 45:
			getEvent(kCathLookOutsideWindowDay) = 1;
			playAnimation(isDay() ? kCathGetInsideDay : kCathGetInsideNight);
			if (!hotspot->scene)
				getLogic()->processScene();
			break;
		}
	} else {
		if (action == 9 || action == 44 || action == 45) {
			playAnimation(isDay() ? kCathLookOutsideWindowDay : kCathLookOutsideWindowNight);
			getLogic()->processScene();
			hotspot->scene = 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(slip) {
	switch(hotspot->param1) {
	default:
		return;

	case 9:
		playAnimation(isDay() ? kCathSlipTylerCompartmentDay : kCathSlipTylerCompartmentNight); 
		break;

	case 44:
		playAnimation(isDay() ? kCathSlipDay : kCathSlipNight);
		break;
	}

	getProgress().field_C8 = 0;

	if (!hotspot->scene)
		getLogic()->processScene();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(getInsideTrain) {
	switch (hotspot->param1) {
	default:
		return;

	case 9:
		playAnimation(isDay() ? kCathGetInsideTylerCompartmentDay : kCathGetInsideTylerCompartmentNight); 
		break;

	case 44:
		playAnimation(isDay() ? kCathGetInsideDay : kCathGetInsideNight);
		break;

	case 45:
		playAnimation(kCathGettingInsideAnnaCompartment);
		break;
	}

	if (!hotspot->scene)
		getLogic()->processScene();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(climbUpTrain) {
	byte action = hotspot->param1;

	if (action != 1 && action != 2)
		return;

	switch (getProgress().chapter) {
	default:
		break;

	case 2:
	case 3:
		if (action == 2)
			playAnimation(kCathClimbUpTrainGreenJacket);

		playAnimation(kCathTopTrainGreenJacket);
		break;

	case 5:
		if (action == 2)
			playAnimation(getProgress().is_nighttime ? kCathClimbUpTrainNoJacketNight : kCathClimbUpTrainNoJacketDay);

		playAnimation(getProgress().is_nighttime ? kCathTopTrainNoJacketNight : kCathTopTrainNoJacketDay);
		break;
	}

	if (!hotspot->scene)
		getLogic()->processScene();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(climbDownTrain) {
	Events evt = kInvalid;
	switch (getProgress().chapter) {
	default:
		return;

	case 2:
	case 3:
		evt = kCathClimbDownTrainGreenJacket;
		break;

	case 5:
		evt = (getProgress().is_nighttime ? kCathClimbDownTrainNoJacketNight : kCathClimbDownTrainNoJacketDay);
		break;
	}

	playAnimation(evt);
	if (evt == kCathClimbDownTrainNoJacketDay)
		getSound()->playSoundEvent(0, 37, 0);

	if (!hotspot->scene)
		getLogic()->processScene();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(jumpUpDownTrain) {
	switch (hotspot->param1) {
	case 1:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityChapters, SavePoints::kAction225056224, 0);
		break;

	case 2:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityChapters, SavePoints::kAction338494260, 0);
		break;

	case 3:
		if (getInventory()->getSelectedItem() == Inventory::kBriefcase) {
			getInventory()->removeItem(Inventory::kBriefcase, 3);
			getSound()->playSoundEvent(0, 82, 0);
			getInventory()->unselectItem();
		}	

		// Show animation with or without briefcase
		playAnimation((getInventory()->getEntry(Inventory::kBriefcase)->location - 3) ? kCathJumpUpCeilingBriefcase : kCathJumpUpCeiling);

		if (!hotspot->scene)
			getLogic()->processScene();

		break;

	case 4:
		if (getProgress().chapter == State::kChapter1)
			getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityKronos, SavePoints::kAction202621266, 0);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(unbound) {
	byte action = hotspot->param1;

	switch (action) {
	default:
		break;

	case 1:
		playAnimation(kCathStruggleWithBonds);
		if (hotspot->scene)
			getLogic()->processScene();
		break;

	case 2:
		playAnimation(kCathBurnRope);
		if (hotspot->scene)
			getLogic()->processScene();
		break;

	case 3:
		if (getEvent(kCathBurnRope)) {
			playAnimation(kCathRemoveBonds);
			getProgress().field_84 = 0;
			getLogic()->loadSceneFromData(1, 89, 255);
			hotspot->scene = 0;				
		}
		break;

	case 4:
		if (!getEvent(kCathStruggleWithBonds2)) {
			playAnimation(kCathStruggleWithBonds2);
			getSound()->playSoundEvent(0, 101, 0);
			getInventory()->setLocationAndProcess(Inventory::kMatch, 2);
			if (!hotspot->scene)
				getLogic()->processScene();
		}
		break;

	case 5:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityIvo, SavePoints::kAction192637492, 0);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(25) {
	switch(hotspot->param1) {
	default:
		break;

	case 1:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityAnna, SavePoints::kAction272177921, 0);
		break;

	case 2:
		getSound()->playSound(SavePoints::kEntityNone, "MUS021", 16, 0);
		break;

	case 3:
		getSound()->playSoundEvent(0, 43, 0);
		if (!getInventory()->hasItem(Inventory::kKey)) {
			if (!getEvent(kAnnaBagageArgument)) {
				getEntities()->reset(SavePoints::kEntityAnna);
				((Anna*)getEntities()->get(SavePoints::kEntityAnna))->setup_bagage();
				hotspot->scene = 0;
			}
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(26) {
	switch(hotspot->param1) {
	default:
		break;

	case 1:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityChapters, SavePoints::kAction158610240, 0);
		break;

	case 2:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityChapters, SavePoints::kAction225367984, 0);
		getInventory()->unselectItem();
		hotspot->scene = 0;
		break;

	case 3:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityChapters, SavePoints::kAction191001984, 0);
		hotspot->scene = 0;
		break;

	case 4:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityChapters, SavePoints::kAction201959744, 0);
		hotspot->scene = 0;
		break;

	case 5:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityChapters, SavePoints::kAction169300225, 0);
		hotspot->scene = 0;
		break;
	}	
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(27) {
	getSound()->playSoundEvent(0, 31, 0);

	switch (getEntityData(SavePoints::kEntityNone)->field_495) {
	default:
		break;

	case 3:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityMertens, SavePoints::kAction225358684, hotspot->param1);
		break;

	case 4:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityCoudert, SavePoints::kAction225358684, hotspot->param1);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(concertSitCough) {
	switch(hotspot->param1) {
	default:
		return;

	case 1:
		playAnimation(kConcertSit);
		break;

	case 2:
		playAnimation(kConcertCough);
		break;
	}

	if (!hotspot->scene)
		getLogic()->processScene();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(29) {
	getProgress().field_C = 1;
	getSound()->playSoundEvent(0, hotspot->param1, hotspot->param2);
	getSound()->playMusic(SavePoints::kEntityNone, hotspot->param3, 16, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(catchBeetle) {
	if (!getBeetle()->isLoaded())
		return;

	if (getBeetle()->catchBeetle()) {
		getBeetle()->unload();
		getInventory()->getEntry(Inventory::kBeetle)->location = 1;
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityChapters, SavePoints::kAction202613084, 0);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(exitCompartment) {
	if (!getProgress().field_30 && getProgress().jacket != 0) {
		getLogic()->savegame(1, 0, 0);
		getProgress().field_30 = 1;
	}

	getObjects()->updateField4(Objects::kObjectCompartment1, hotspot->param2);

	// fall to case enterCompartment action
	action_enterCompartment(hotspot);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(32) {
	switch(hotspot->param1) {
	default:
		break;

	case 1:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntitySalko, SavePoints::kAction167992577, 0);
		break;

	case 2:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityVesna, SavePoints::kAction202884544, 0);
		break;

	case 3:
		if (getProgress().chapter == State::kChapter5) {
			getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityAbbot, SavePoints::kAction168646401, 0);
			getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityMilos, SavePoints::kAction168646401, 0);
		} else {
			getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityTrain, SavePoints::kAction203339360, 0);
		}
		hotspot->scene = 0;
		break;

	case 4:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityMilos, SavePoints::kAction169773228, 0);
		break;

	case 5:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityVesna, SavePoints::kAction167992577, 0);
		break;

	case 6:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityAugust, SavePoints::kAction203078272, 0);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(useWhistle) {
	Events evt = kInvalid;

	switch (hotspot->param1) {
	default:
		break;

	case 1:
		if (getEvent(kKronosBringFirebird)) {
			getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityAnna, SavePoints::kAction205294778, 0);
			break;
		}

		if (getEntities()->checkFields1(SavePoints::kEntityNone, 3, 8200)) {
			evt = kCathOpenEgg;

			Scene *scene = _engine->getScene(hotspot->scene);

			if (scene->getHotspot())
				hotspot->scene = scene->getHotspot()->scene;

			delete scene;
		} else {
			evt = kCathOpenEggNoBackground;
		}
		getProgress().is_egg_open = 1;
		break;

	case 2:
		if (getEvent(kKronosBringFirebird)) {
			getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityAnna, SavePoints::kAction224309120, 0);
			break;
		}

		evt = (getEntities()->checkFields1(SavePoints::kEntityNone, 3, 8200)) ? kCathCloseEgg : kCathCloseEggNoBackground;
		getProgress().is_egg_open = 0;
		break;

	case 3:
		if (getEvent(kKronosBringFirebird)) {
			getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityAnna, SavePoints::kAction270751616, 0);
			break;
		}

		evt = (getEntities()->checkFields1(SavePoints::kEntityNone, 3, 8200)) ? kCathUseWhistleOpenEgg : kCathUseWhistleOpenEggNoBackground;
		break;

	}	

	if (evt != kInvalid) {
		playAnimation(evt);
		if (!hotspot->scene)
			getLogic()->processScene();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(openMatchBox) {
	// If the match is already in the inventory, do nothing
	if (!getInventory()->getEntry(Inventory::kMatch)->location
		|| getInventory()->getEntry(Inventory::kMatch)->has_item)
		return;

	getInventory()->addItem(Inventory::kMatch);
	getSound()->playSoundEvent(0, 102, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(openBed) {
	getSound()->playSoundEvent(0, 59, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(dialog) {
	getSound()->playDialog(SavePoints::kEntityTables4, (SavePoints::EntityIndex)hotspot->param1, 16, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(eggBox) {
	getSound()->playSoundEvent(0, 43, 0);
	if (getProgress().field_7C) {
		getSound()->playSound(SavePoints::kEntityNone, "MUS003", 16, 0);
		getProgress().field_7C = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(39) {
	getSound()->playSoundEvent(0, 24, 0);
	if (getProgress().field_80) {
		getSound()->playSound(SavePoints::kEntityNone, "MUS003", 16, 0);
		getProgress().field_80 = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(bed) {
	getSound()->playSoundEvent(0, 85, 0);
	// falls to case 12
	action_12(hotspot);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(41) {
	byte id = 0;
	switch (getProgress().chapter) {
	case State::kChapter1:
		id = hotspot->param1;
		break;

	case State::kChapter2:
	case State::kChapter3:
		id = hotspot->param2;
		break;

	case State::kChapter4:
	case State::kChapter5:
		id = hotspot->param3;
		break;
	}

	if (id)
		getSound()->playMusic(SavePoints::kEntityNone, id, 16, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(42) {
	int value = 0;
	switch (getProgress().chapter) {
	default:
		break;

	case State::kChapter1:
		value = 1;
		break;

	case State::kChapter2:
	case State::kChapter3:
		value = 2;
		break;

	case State::kChapter4:
	case State::kChapter5:
		value = 4;
		break;
	}

	if (hotspot->param3 & value) {					
		getSound()->playMusic(SavePoints::kEntityNone, hotspot->param1, 16, 0);

		char filename[6];
		sprintf((char*)&filename, "MUS%03d", hotspot->param1);	
		//getSavePoints()->call(SavePoints::kNone, SavePoints::kTrain, SavePoints::kAction203863200, (int)&filename);
		error("Action::action_42: missing savepoints call (action = kAction203863200)!");
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityTrain, SavePoints::kAction222746496, hotspot->param2);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(44) {
	switch (hotspot->param1) {
	default:
		break;

	case 1:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityRebecca, SavePoints::kAction205034665, 0);
		break;

	case 2:
		getSavePoints()->push(SavePoints::kEntityNone, SavePoints::kEntityChapters, SavePoints::kAction225358684, 0);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////
void Action::pickGreenJacket(bool process) {
	getProgress().jacket = State::kGreenJacket;
	getInventory()->addItem(Inventory::kMatchBox);

	getObjects()->update(Objects::kObjectOutside, SavePoints::kEntityNone, 2,  Cursor::kCursorKeepValue, 255);	
	playAnimation(kPickGreenJacket);

	getInventory()->setPortrait(Inventory::kPortraitGreen);

	if (process)
		getLogic()->processScene();
}

void Action::pickScarf(bool process) {
	if (getProgress().jacket == State::kOriginalJacket)
		playAnimation(kPickScarfGreen);
	else
		playAnimation(kPickScarfOriginal);

	if (process)
		getLogic()->processScene();
}

void Action::pickCorpse(byte bedPosition, bool process) {

	switch(getInventory()->getEntry(Inventory::kCorpse)->location) {
	// Floor
	case kCorpseLocationFloor:
		if (bedPosition != 4) {
			if (getProgress().jacket == State::kOriginalJacket)
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
		if (getProgress().jacket == State::kOriginalJacket)
			playAnimation(kCorpsePickBedOriginal);
		else
			playAnimation(kCorpsePickBedGreen);

		break;

	// No way to pick the corpse
	default:		
		break;
	}

	if (process)
		getLogic()->processScene();

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
		if (getProgress().jacket == State::kOriginalJacket)
			playAnimation(kCorpseDropFloorOriginal);
		else
			playAnimation(kCorpseDropFloorGreen);

		break;

	case 2:	// Bed
		if (getProgress().jacket == State::kOriginalJacket)
			playAnimation(kCorpseDropBedOriginal);
		else
			playAnimation(kCorpseDropBedGreen);

		break;

	case 4: // Window
		// Say goodbye to an old friend
		getInventory()->getEntry(Inventory::kCorpse)->location = 0;
		getProgress().field_20 = 1;

		if (getState()->time <= 1138500) {

			if (getProgress().jacket == State::kOriginalJacket)
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
		getLogic()->processScene();
}

bool Action::handleOtherCompartment(Objects::ObjectIndex object, byte param2, byte param3) {

	if (getEntityData(SavePoints::kEntityNone)->field_493 || ((object < 2 || object > 8) && (object < 32 || object > 39)))
		return false;

	//////////////////////////////////////////////////////////////////////////
	// Gendarmes
	if (getEntityData(SavePoints::kEntityNone)->field_495 == getEntityData(SavePoints::kEntityGendarmes)->field_495
	&& !getEntityData(SavePoints::kEntityGendarmes)->field_493
	&& !getEntities()->compare(SavePoints::kEntityNone, SavePoints::kEntityGendarmes)) {
		if (param2) {
			if (getObjects()->get(object).location == 1 || getObjects()->get(object).location == 3 || getEntities()->checkFields2(object)) {
				getSound()->playSoundEvent(SavePoints::kEntityNone, 13, 0);
			} else {
				getSound()->playSoundEvent(SavePoints::kEntityNone, 14, 0);
				getSound()->playSoundEvent(SavePoints::kEntityNone, 15, 3);
			}
		}

		if (param3)
			getLogic()->loadSceneFromObject(object);

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// Mertens




	//////////////////////////////////////////////////////////////////////////
	// Coudert

	//if (param3)
	//	getLogic()->loadSceneFromObject2(object);
		
	error("Action::handleOtherCompartment: not implemented!");

	return false;
}

//////////////////////////////////////////////////////////////////////////
// Cursors
//////////////////////////////////////////////////////////////////////////
Cursor::CursorStyle Action::getCursor(byte action, Objects::ObjectIndex object, byte param2, byte param3, byte cursor)
{
	// Simple cursor style
	if (cursor != 128)
		return (Cursor::CursorStyle)cursor;

	warning("================================= OBJECT %03d =================================", object);

	switch (action) {
	default:
		return Cursor::kCursorNormal;

	case SceneHotspot::kActionInventory:
		if (!getState()->sceneBackup2 && (getEvent(Action::kKronosBringFirebird) || getProgress().is_egg_open))				
			return Cursor::kCursorNormal;
		else
			return Cursor::kCursorBackward;		

	case SceneHotspot::kActionKnockOnDoor:
		if (object >= 128)
			return Cursor::kCursorNormal;
		else
			return (Cursor::CursorStyle)getObjects()->get(object).cursor;

	case SceneHotspot::kAction12:
		if (object >= 128)
			return Cursor::kCursorNormal;

		if (getObjects()->get(object).entity)
			return (Cursor::CursorStyle)getObjects()->get(object).cursor;
		else
			return Cursor::kCursorNormal;

	case SceneHotspot::kActionPickItem:
		if (object >= 32)
			return Cursor::kCursorNormal;

		if ((!getInventory()->getSelectedItem() || getInventory()->getSelectedEntry()->no_autoselect)
			&& (object != 21 || getProgress().field_8 == 1))
			return Cursor::kCursorHand;
		else
			return Cursor::kCursorNormal;			

	case SceneHotspot::kActionDropItem:
		if (object >= 32)
			return Cursor::kCursorNormal;

		if (getInventory()->getSelectedItem() != (Inventory::InventoryItem)object)
			return Cursor::kCursorNormal;

		if (object == 20 && param2 == 4 && !getProgress().field_50)
			return Cursor::kCursorNormal;

		if (object == 18  && param2 == 1 && getProgress().field_5C)
			return Cursor::kCursorNormal;

		return (Cursor::CursorStyle)getInventory()->getSelectedEntry()->item_id;

	case SceneHotspot::kAction15:
		if (object >= 128)
			return Cursor::kCursorNormal;

		if (*(&getProgress().field_0 + object) == param2)
			return (Cursor::CursorStyle)param3;

		return Cursor::kCursorNormal; 

	case SceneHotspot::kActionEnterCompartment:
		if ((getInventory()->getSelectedItem() != Inventory::kKey || getObjects()->get(Objects::kObjectCompartment1).location)
		&& (getObjects()->get(Objects::kObjectCompartment1).location != 1 || !getInventory()->hasItem(Inventory::kKey)
		 ||	(getInventory()->getSelectedItem() != Inventory::kFirebird && getInventory()->getSelectedItem() != Inventory::kBriefcase)))
			goto LABEL_KEY;

		return (Cursor::CursorStyle)getInventory()->getEntry(Inventory::kKey)->item_id; // TODO is that always the same as Cursor::kCursorKey

	case SceneHotspot::kActionGetOutsideTrain:
		if (getProgress().jacket != State::kGreenJacket)
			return Cursor::kCursorNormal;

		if ((getEvent(Action::kCathLookOutsideWindowDay) || getEvent(Action::kCathLookOutsideWindowDay) || getObjects()->get(Objects::kObjectCompartment1).field_4 == 1)
			&& getProgress().field_50
			&& (object != 45 || (getEntities()->checkFields1(SavePoints::kEntityRebecca, 4, 4840) && getObjects()->get(Objects::kObject44).location == 2))
			&& getInventory()->getSelectedItem() != Inventory::kBriefcase && getInventory()->getSelectedItem() != Inventory::kFirebird)
			return Cursor::kCursorForward; 

		// FIXME convert to something readable
		return (Cursor::CursorStyle)((((getObjects()->get(Objects::kObjectCompartment1).field_4 - 1) < 1) - 1) & 11); 

	case SceneHotspot::kActionSlip:
		// FIXME convert to something readable
		return (Cursor::CursorStyle)(((getProgress().field_C8 < 1) - 1) & 7); 

	case SceneHotspot::kActionClimbUpTrain:
		if (getProgress().field_50
			&& (getProgress().chapter == State::kChapter2 || getProgress().chapter == State::kChapter3 || getProgress().chapter == State::kChapter5)
			&& getInventory()->getSelectedItem() != Inventory::kFirebird 
			&& getInventory()->getSelectedItem() != Inventory::kBriefcase)
			return Cursor::kCursorUp;

		return Cursor::kCursorNormal; 

	case SceneHotspot::kActionJumpUpDownTrain:
		if (object != 1)
			return Cursor::kCursorNormal; 

		// FIXME convert to something readable
		return (Cursor::CursorStyle)(-(getObjects()->get(Objects::kObjectCeiling).location < 1) & 9);

	case SceneHotspot::kActionUnbound:
		if (param2 != 2)
			return Cursor::kCursorNormal; 

		if (getEvent(Action::kCathBurnRope) || !getEvent(Action::kCathStruggleWithBonds2))
			return Cursor::kCursorNormal; 

		return Cursor::kCursorHand; 

	case SceneHotspot::kActionCatchBeetle:	
		if (!getBeetle()->isLoaded())
			return Cursor::kCursorNormal; 

		if (!getBeetle()->isCatchable())
			return Cursor::kCursorNormal; 

		if (getInventory()->getSelectedItem() == Inventory::kMatchBox && getInventory()->hasItem(Inventory::kMatch))
			return (Cursor::CursorStyle)getInventory()->getEntry(Inventory::kMatchBox)->item_id;

		return Cursor::kCursorHandPointer;

	case SceneHotspot::KActionUseWhistle:
		if (object != 3)
			return Cursor::kCursorNormal; 

		if (getInventory()->getSelectedItem() == Inventory::kWhistle)
			return Cursor::kCursorWhistle;
		else
			return Cursor::kCursorNormal; 

	case SceneHotspot::kActionOpenBed:
		if (getProgress().chapter < State::kChapter2)
			return Cursor::kCursorHand;

		return Cursor::kCursorNormal;

	case SceneHotspot::kActionDialog:
		if (getSound()->getDialogName((SavePoints::EntityIndex)object))
			return Cursor::kCursorHandPointer; 

		return Cursor::kCursorNormal;

	case SceneHotspot::kActionBed:
		if (getProgress().field_18 == 2 && !getProgress().field_E4
			&& (getState()->time > 1404000 
			|| (getProgress().event_august_met && getProgress().field_CC 
			&& (!getProgress().field_24 || getProgress().field_3C))))
			return Cursor::kCursorSleep;

		return Cursor::kCursorNormal;

LABEL_KEY:
	case SceneHotspot::kActionCompartment:
	case SceneHotspot::kActionExitCompartment:
		if (object >= 128)
			return Cursor::kCursorNormal;

		if (getInventory()->getSelectedItem() != Inventory::kKey
		|| getObjects()->get(object).entity 
		|| getObjects()->get(object).location != 1 
		|| !getObjects()->get(object).field_3
		|| getEntities()->checkFields3(SavePoints::kEntityNone)
		|| getEntities()->checkFields2(object))
			return (Cursor::CursorStyle)getObjects()->get(object).field_3;
		else
			return (Cursor::CursorStyle)getInventory()->getEntry(Inventory::kKey)->item_id;
	}
}

//////////////////////////////////////////////////////////////////////////
// Animation
//////////////////////////////////////////////////////////////////////////

// Play an animation and add delta time to global game time
void Action::playAnimation(int index) {
	assert(index > 0 || (uint)index < sizeof(animationList));

	// FIXME NIS animations need to be passed one more parameter than currently

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
