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
#include "lastexpress/data/cursor.h"
#include "lastexpress/data/snd.h"
#include "lastexpress/data/scene.h"

#include "lastexpress/entities/abbot.h"
#include "lastexpress/entities/anna.h"
#include "lastexpress/entities/entity.h"

#include "lastexpress/game/beetle.h"
#include "lastexpress/game/entities.h"
#include "lastexpress/game/inventory.h"
#include "lastexpress/game/logic.h"
#include "lastexpress/game/object.h"
#include "lastexpress/game/savegame.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

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
	{"1002",    255},
	{"1002D",   255},
	{"1003",    0},
	{"1005",    195},
	{"1006",    750},   // 5
	{"1006A",   750},
	{"1008",    765},
	{"1008N",   765},
	{"1008A",   750},
	{"1008AN",  750},   // 10
	{"1009",    0},
	{"1011",    1005},
	{"1011A",   780},
	{"1012",    300},
	{"1013",    285},
	{"1017",    870},   // 15
	{"1017A",   0},     // Not in the data files?
	{"1019",    120},
	{"1019D",   120},
	{"1020",    120},   // 20
	{"1022",    525},
	{"1022A",   180},
	{"1022AD",  210},
	{"1022B",   210},
	{"1022C",   210},   // 25
	{"1023",    135},
	{"1025",    945},
	{"1028",    300},
	{"1030",    390},
	{"1031",    375},   // 30
	{"1032",    1050},
	{"1033",    945},
	{"1034",    495},
	{"1035",    1230},
	{"1037",    1425},  // 35
	{"1038",    195},
	{"1038A",   405},
	{"1039",    600},
	{"1040",    945},
	{"1041",    510},   // 40
	{"1042",    540},
	{"1043",    855},
	{"1044",    645},
	{"1046",    0},
	{"1047",    0},     // 45
	{"1047A",   0},
	{"1059",    1005},
	{"1060",    255},
	{"1063",    0},
	{"1101",    255},   // 50
	{"1102",    1320},
	{"1103",    210},
	{"1104",    120},
	{"1105",    1350},
	{"1106",    315},   // 55
	{"1106A",   315},
	{"1106D",   315},
	{"1107",    1},
	{"1107A",   660},
	{"1108",    300},   // 60
	{"1109",    1305},
	{"1110",    300},
	{"1112",    0},
	{"1115",    0},
	{"1115A",   0},     // 65
	{"1115B",   0},
	{"1115C",   0},
	{"1115D",   0},
	{"1115E",   0},
	{"1115F",   0},     // 70
	{"1115G",   0},
	{"1115H",   0},
	{"1116",    0},
	{"1117",    0},
	{"1118",    105},   // 75
	{"1202",    510},
	{"1202A",   510},
	{"1203",    720},
	{"1204",    120},
	{"1205",    465},   // 80
	{"1206",    690},
	{"1206A",   450},
	{"1208",    465},
	{"1210",    1020},
	{"1211",    600},   // 85
	{"1212",    435},
	{"1213",    525},
	{"1213A",   150},
	{"1215",    390},
	{"1216",    0},     // 90
	{"1219",    240},
	{"1222",    1095},
	{"1223",    0},
	{"1224",    720},
	{"1225",    1005},  // 95
	{"1227",    840},
	{"1227A",   840},
	{"1303",    450},
	{"1303N",   450},
	{"1304",    450},   // 100
	{"1304N",   450},
	{"1305",    630},
	{"1309",    0},
	{"1311",    1710},
	{"1312",    240},   // 105
	{"1312D",   240},
	{"1313",    930},
	{"1315",    1035},
	{"1315A",   1035},
	{"1401",    540},   // 110
	{"1402",    150},
	{"1402B",   150},
	{"1403",    90},
	{"1404",    885},
	{"1404A",   0},     // 115
	{"1405",    135},
	{"1406",    1665},
	{"1501",    285},
	{"1501A",   285},
	{"1502",    165},   // 120
	{"1502A",   165},
	{"1502D",   165},
	{"1503",    0},
	{"1504",    0},
	{"1505",    0},     // 125
	{"1505A",   0},
	{"1506",    300},
	{"1506A",   180},
	{"1508",    0},
	{"1509",    450},   // 130
	{"1509S",   450},
	{"1509A",   450},
	{"1509AS",  450},
	{"1509N",   450},
	{"1509SN",  450},   // 135
	{"1509AN",  450},
	{"1509BN",  450},
	{"1511",    150},
	{"1511A",   150},
	{"1511B",   90},    // 140
	{"1511BA",  90},
	{"1511C",   135},
	{"1511D",   105},
	{"1930",    0},
	{"1511E",   150},   // 145
	{"1512",    165},
	{"1513",    180},
	{"1517",    0},
	{"1517A",   165},
	{"1518",    165},   // 150
	{"1518A",   165},
	{"1518B",   165},
	{"1591",    450},
	{"1592",    450},
	{"1593",    450},   // 155
	{"1594",    450},
	{"1595",    450},
	{"1596",    450},
	{"1601",    0},
	{"1603",    0},     // 160
	{"1606B",   315},
	{"1607A",   0},
	{"1610",    0},
	{"1611",    0},
	{"1612",    0},     // 165
	{"1615",    0},
	{"1619",    0},
	{"1620",    120},
	{"1621",    105},
	{"1622",    105},   // 170
	{"1629",    450},
	{"1630",    450},
	{"1631",    525},
	{"1632",    0},
	{"1633",    615},   // 175
	{"1634",    180},
	{"1702",    180},
	{"1702DD",  180},
	{"1702NU",  180},
	{"1702ND",  180},   // 180
	{"1704",    300},
	{"1704D",   300},
	{"1705",    195},
	{"1705D",   195},
	{"1706",    195},   // 185
	{"1706DD",  195},
	{"1706ND",  195},
	{"1706NU",  195},
	{"1901",    135},
	{"1902",    1410},  // 190
	{"1903",    0},
	{"1904",    1920},
	{"1908",    600},
	{"1908A",   195},
	{"1908B",   105},   // 195
	{"1908C",   165},
	{"1908CD",  0},
	{"1909A",   150},
	{"1909B",   150},
	{"1909C",   150},   // 200
	{"1910A",   180},
	{"1910B",   180},
	{"1910C",   180},
	{"1911A",   90},
	{"1911B",   90},    // 205
	{"1911C",   90},
	{"1912",    0},
	{"1913",    0},
	{"1917",    0},
	{"1918",    390},   // 210
	{"1919",    360},
	{"1919A",   105},
	{"1920",    75},
	{"1922",    75},
	{"1923",    150},   // 215
	{"8001",    120},
	{"8001A",   120},
	{"8002",    120},
	{"8002A",   120},
	{"8002B",   120},   // 220
	{"8003",    105},
	{"8003A",   105},
	{"8004",    105},
	{"8004A",   105},
	{"8005",    270},   // 225
	{"8005B",   270},
	{"8010",    270},
	{"8013",    120},
	{"8013A",   120},
	{"8014",    165},   // 230
	{"8014A",   165},
	{"8014R",   165},
	{"8014AR",  165},
	{"8015",    150},
	{"8015A",   150},   // 235
	{"8015R",   150},
	{"8015AR",  150},
	{"8017",    120},
	{"8017A",   120},
	{"8017R",   120},   // 240
	{"8017AR",  120},
	{"8017N",   90},
	{"8023",    135},
	{"8023A",   135},
	{"8023M",   135},   // 245
	{"8024",    150},
	{"8024A",   180},
	{"8024M",   180},
	{"8025",    150},
	{"8025A",   150},   // 250
	{"8025M",   150},
	{"8027",    75},
	{"8028",    75},
	{"8029",    120},
	{"8029A",   120},   // 255
	{"8031",    375},
	{"8032",    0},
	{"8032A",   0},
	{"8033",    105},
	{"8035",    195},   // 260
	{"8035A",   120},
	{"8035B",   180},
	{"8035C",   135},
	{"8036",    105},
	{"8037",    195},   // 265
	{"8037A",   195},
	{"8040",    240},
	{"8040A",   240},
	{"8041",    195},
	{"8041A",   195},   // 270
	{"8042",    600},
	{"8042A",   600}
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

		loadSceneObject(backup, getState()->sceneBackup);

		if (getState()->field1000[backup.getHeader()->position + 100 * backup.getHeader()->field_13])
			index = getLogic()->processIndex(getState()->sceneBackup);
	}

	getLogic()->loadScene(index);

	if (!getInventory()->getSelectedItem())
		return;

	if (!getInventory()->getSelectedEntry()->is_selectable || (!getState()->sceneBackup2 && getInventory()->getFirstExaminableItem()))
		getInventory()->selectItem(getInventory()->getFirstExaminableItem());
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(savePoint) {
	getSavePoints()->push(kEntityNone, (EntityIndex)hotspot->param1, (ActionIndex)hotspot->param2);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(playSound) {
	if (hotspot->param2)
		getSound()->playSoundEvent(0, hotspot->param1, hotspot->param2);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(playMusic) {
	if (hotspot->param1 != 50 || getProgress().chapter == kChapter5)
		getSound()->playMusic(kEntityNone, hotspot->param1, 16, hotspot->param2);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(knock) {
	ObjectIndex object = (ObjectIndex)hotspot->param1;

	if (object >= kObjectMax)
		return;

	if (getObjects()->get(object).entity) {
		getSavePoints()->push(kEntityNone, getObjects()->get(object).entity, kAction8, object);
	} else {
		if (!getSound()->isFileInQueue("LIB012"))
			getSound()->playSoundEvent(0, 12, 0);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(compartment) {
	ObjectIndex object = (ObjectIndex)hotspot->param1;

	if (object >= kObjectMax)
		return;

	if (getObjects()->get(object).entity) {
		getSavePoints()->push(kEntityNone, getObjects()->get(object).entity, kAction9, object);
		hotspot->scene = 0;
		return;
	}

	if (handleOtherCompartment(object, 1, 1)) {
		hotspot->scene = 0;
		return;
	}

	ObjectLocation location = getObjects()->get(object).location;
	if (location == 1 || location == 3 || getEntities()->checkFields2(object)) {

		// FIXME check again, this might be wrong (and simplify expression)
		if (location != 1 || getEntities()->checkFields2(object) || (getInventory()->getSelectedItem() != kItemKey
		&& (location != 1 || !getInventory()->hasItem(kItemKey)
		|| getInventory()->getSelectedItem() != kItemFirebird || getInventory()->getSelectedItem() != kItemBriefcase))) {
				getSound()->playSoundEvent(0, 13, 0);
				hotspot->scene = 0;
				return;
		}

		getSound()->playSoundEvent(0, 32, 0);

		if ((object >= 1 && object <= 3) || (object >= 32 && object <= 37))
			getObjects()->update(object, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		getSound()->playSoundEvent(0, 15, 22);
		getInventory()->unselectItem();

		return;
	}

	if (hotspot->action != 16 || getInventory()->getSelectedItem() != kItemKey) {
		if (object == 109) {
			getSound()->playSoundEvent(0, 26, 0);
		} else {
			getSound()->playSoundEvent(0, 14, 0);
			getSound()->playSoundEvent(0, 15, 22);
		}
		return;
	}

	getObjects()->update(kObjectCompartment1, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
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
	ObjectIndex object = (ObjectIndex)hotspot->param1;
	ObjectLocation location = (ObjectLocation)hotspot->param2;

	if (object >= kObjectMax)
		return;

	getObjects()->update(object, getObjects()->get(object).entity, location, kCursorKeepValue, kCursorKeepValue);

	bool isNotWindow = ((object < 9  || object > 16) && (object < 40 || object > 47));

	switch (location) {
	case kLocation1:
		if (isNotWindow)
			getSound()->playSoundEvent(0, 24, 0);
		else
			getSound()->playSoundEvent(0, 21, 0);
		break;

	case kLocation2:
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
	ObjectIndex object = (ObjectIndex)hotspot->param1;

	if (object >= kObjectMax)
		return;

	getObjects()->updateLocation2(object, (ObjectLocation)hotspot->param2);

	if (object != kObject112 /* TODO: or LIB096 does not exist -> is it needed, say if the HPF is not loaded or something */) {
		if (object == 1)
			getSound()->playSoundEvent(0, 73, 0);
	} else {
		getSound()->playSoundEvent(0, 96, 0);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(setItemLocation) {
	InventoryItem item = (InventoryItem)hotspot->param1;
	Inventory::InventoryEntry* entry = getInventory()->getEntry(item);

	if (!entry->has_item)
		return;

	entry->location = (ObjectLocation)hotspot->param2;

	if (item == kItemCorpse) {
		ObjectLocation corpseLocation = getInventory()->getEntry(kItemCorpse)->location;

		if (corpseLocation == kLocation3 || corpseLocation == kLocation4)
			getProgress().field_8 = 1;
		else
			getProgress().field_8 = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(12) {
	ObjectIndex object = (ObjectIndex)hotspot->param1;

	if (object >= kObjectMax)
		return;

	if (getObjects()->get(object).entity)
		getSavePoints()->push(kEntityNone, getObjects()->get(object).entity, kAction8, object);

}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(pickItem) {
	InventoryItem item = (InventoryItem)hotspot->param1;
	Inventory::InventoryEntry* entry = getInventory()->getEntry(item);
	byte location = hotspot->param2;
	bool process = (hotspot->scene == 0);

	if (item >= kPortraitOriginal || !entry->location)
		return;

	// Special case for corpse
	if (item == kItemCorpse) {
		pickCorpse(location, process);
		return;
	}

	// Add and process items
	getInventory()->addItem(item);

	switch (item) {
	case kItemGreenJacket:
		pickGreenJacket(process);
		break;

	case kItemScarf:
		pickScarf(process);

		// stop processing
		return;

	case kItemParchemin:
		if (location != kLocation2)
			break;

		getInventory()->addItem(kItemParchemin);
		getInventory()->getEntry(kItem11)->location = kLocation1;
		getSound()->playSoundEvent(0, 9, 0);
		break;

	case kItemBomb:
		getEntities()->resetEntityState(kEntityAbbot);
		((Abbot*)getEntities()->get(kEntityAbbot))->setup_pickBomb();
		break;

	case kItemBriefcase:
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
		_engine->getCursor()->setStyle((CursorStyle)getInventory()->getEntry(item)->item_id);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(dropItem) {
	InventoryItem item = (InventoryItem)hotspot->param1;
	ObjectLocation location = (ObjectLocation)hotspot->param2;
	bool process = (hotspot->scene == 0);

	if (item >= kPortraitOriginal)
		return;

	if (!getInventory()->hasItem(item))
		return;

	if (location < kLocation1)
		return;

	// Handle actions
	if (item == kItemBriefcase) {
		getSound()->playSoundEvent(0, 82, 0);

		if (location == kLocation2) {
			if (!getProgress().field_58) {
				save(kEntityNone, 0, kEventNone);
				getProgress().field_58 = 1;
			}

			if (getInventory()->getEntry(kItemParchemin)->location == kLocation2) {
				getInventory()->addItem(kItemParchemin);
				getInventory()->getEntry(kItem11)->location = kLocation11;
				getSound()->playSoundEvent(0, 9, 0);
			}
		}
	}

	// Update item location
	getInventory()->removeItem(item, location);

	if (item == kItemCorpse)
		dropCorpse(process);

	// Unselect item
	getInventory()->unselectItem();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(enterCompartment) {
	if (getObjects()->get(kObjectCompartment1).location == 1 || getObjects()->get(kObjectCompartment1).location == 3 || getInventory()->getSelectedItem() == kItemKey) {
		action_compartment(hotspot);
		return;
	}

	if (getProgress().event_found_corpse) {
		if (hotspot->action != 16 || getInventory()->getEntry(kItemBriefcase)->location != 2) {
			action_compartment(hotspot);
		} else {
			getSound()->playSoundEvent(0, 14, 0);
			getSound()->playSoundEvent(0, 15, 22);

			if (getProgress().field_78) {
				getSound()->playSound(kEntityNone, "MUS003", 16, 0);
				getProgress().field_78 = 0;
			}

			getLogic()->loadSceneFromData(3, 77, 255);
			hotspot->scene = 0;
		}
	} else {
		save(kEntityNone, 0, kEventNone);
		getSound()->playSound(kEntityNone, "LIB014");
		playAnimation(kEventCathFindCorpse);
		getSound()->playSound(kEntityNone, "LIB015");
		getProgress().event_found_corpse = 1;
		hotspot->scene = 42; // Tyler compartment with corpse on floor
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(getOutsideTrain) {
	byte action = hotspot->param1;

	if ((getEvent(kEventCathLookOutsideWindowDay) || getEvent(kEventCathLookOutsideWindowNight) || getObjects()->get(kObjectCompartment1).location2)
	  && getProgress().field_50
	  && (action != 45 || (!getEntities()->checkFields1(kEntityRebecca, EntityData::kField495_4, EntityData::kField491_4840) && getObjects()->get(kObject44).location == 2))
	  && getInventory()->getSelectedItem() != kItemFirebird
	  && getInventory()->getSelectedItem() != kItemBriefcase) {

		switch (action) {
		default:
			return;

		case 9:
			getEvent(kEventCathLookOutsideWindowDay) = 1;
			playAnimation(isDay() ? kEventCathGoOutsideTylerCompartmentDay : kEventCathGoOutsideTylerCompartmentNight);
			getProgress().field_C8 = 1;
			break;

		case 44:
			getEvent(kEventCathLookOutsideWindowDay) = 1;
			playAnimation(isDay() ? kEventCathGoOutsideDay : kEventCathGoOutsideNight);
			getProgress().field_C8 = 1;
			break;

		case 45:
			getEvent(kEventCathLookOutsideWindowDay) = 1;
			playAnimation(isDay() ? kEventCathGetInsideDay : kEventCathGetInsideNight);
			if (!hotspot->scene)
				getLogic()->processScene();
			break;
		}
	} else {
		if (action == 9 || action == 44 || action == 45) {
			playAnimation(isDay() ? kEventCathLookOutsideWindowDay : kEventCathLookOutsideWindowNight);
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
		playAnimation(isDay() ? kEventCathSlipTylerCompartmentDay : kEventCathSlipTylerCompartmentNight);
		break;

	case 44:
		playAnimation(isDay() ? kEventCathSlipDay : kEventCathSlipNight);
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
		playAnimation(isDay() ? kEventCathGetInsideTylerCompartmentDay : kEventCathGetInsideTylerCompartmentNight);
		break;

	case 44:
		playAnimation(isDay() ? kEventCathGetInsideDay : kEventCathGetInsideNight);
		break;

	case 45:
		playAnimation(kEventCathGettingInsideAnnaCompartment);
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
			playAnimation(kEventCathClimbUpTrainGreenJacket);

		playAnimation(kEventCathTopTrainGreenJacket);
		break;

	case 5:
		if (action == 2)
			playAnimation(getProgress().is_nighttime ? kEventCathClimbUpTrainNoJacketNight : kEventCathClimbUpTrainNoJacketDay);

		playAnimation(getProgress().is_nighttime ? kEventCathTopTrainNoJacketNight : kEventCathTopTrainNoJacketDay);
		break;
	}

	if (!hotspot->scene)
		getLogic()->processScene();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(climbDownTrain) {
	EventIndex evt = kEventNone;
	switch (getProgress().chapter) {
	default:
		return;

	case 2:
	case 3:
		evt = kEventCathClimbDownTrainGreenJacket;
		break;

	case 5:
		evt = (getProgress().is_nighttime ? kEventCathClimbDownTrainNoJacketNight : kEventCathClimbDownTrainNoJacketDay);
		break;
	}

	playAnimation(evt);
	if (evt == kEventCathClimbDownTrainNoJacketDay)
		getSound()->playSoundEvent(0, 37, 0);

	if (!hotspot->scene)
		getLogic()->processScene();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(jumpUpDownTrain) {
	switch (hotspot->param1) {
	case 1:
		getSavePoints()->push(kEntityNone, kEntityChapters, kActionBreakCeiling);
		break;

	case 2:
		getSavePoints()->push(kEntityNone, kEntityChapters, kActionJumpDownCeiling);
		break;

	case 3:
		if (getInventory()->getSelectedItem() == kItemBriefcase) {
			getInventory()->removeItem(kItemBriefcase, kLocation3);
			getSound()->playSoundEvent(0, 82, 0);
			getInventory()->unselectItem();
		}

		// Show animation with or without briefcase
		playAnimation((getInventory()->getEntry(kItemBriefcase)->location - 3) ? kEventCathJumpUpCeilingBriefcase : kEventCathJumpUpCeiling);

		if (!hotspot->scene)
			getLogic()->processScene();

		break;

	case 4:
		if (getProgress().chapter == kChapter1)
			getSavePoints()->push(kEntityNone, kEntityKronos, kAction202621266);
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
		playAnimation(kEventCathStruggleWithBonds);
		if (hotspot->scene)
			getLogic()->processScene();
		break;

	case 2:
		playAnimation(kEventCathBurnRope);
		if (hotspot->scene)
			getLogic()->processScene();
		break;

	case 3:
		if (getEvent(kEventCathBurnRope)) {
			playAnimation(kEventCathRemoveBonds);
			getProgress().field_84 = 0;
			getLogic()->loadSceneFromData(1, 89, 255);
			hotspot->scene = 0;
		}
		break;

	case 4:
		if (!getEvent(kEventCathStruggleWithBonds2)) {
			playAnimation(kEventCathStruggleWithBonds2);
			getSound()->playSoundEvent(0, 101, 0);
			getInventory()->setLocationAndProcess(kItemMatch, kLocation2);
			if (!hotspot->scene)
				getLogic()->processScene();
		}
		break;

	case 5:
		getSavePoints()->push(kEntityNone, kEntityIvo, kAction192637492);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(25) {
	switch(hotspot->param1) {
	default:
		break;

	case 1:
		getSavePoints()->push(kEntityNone, kEntityAnna, kAction272177921);
		break;

	case 2:
		getSound()->playSound(kEntityNone, "MUS021", 16, 0);
		break;

	case 3:
		getSound()->playSoundEvent(0, 43, 0);
		if (!getInventory()->hasItem(kItemKey)) {
			if (!getEvent(kEventAnnaBagageArgument)) {
				getEntities()->resetEntityState(kEntityAnna);
				((Anna*)getEntities()->get(kEntityAnna))->setup_bagage();
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
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction158610240);
		break;

	case 2:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction225367984);
		getInventory()->unselectItem();
		hotspot->scene = 0;
		break;

	case 3:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction191001984);
		hotspot->scene = 0;
		break;

	case 4:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction201959744);
		hotspot->scene = 0;
		break;

	case 5:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction169300225);
		hotspot->scene = 0;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(27) {
	getSound()->playSoundEvent(0, 31, 0);

	switch (getEntityData(kEntityNone)->field_495) {
	default:
		break;

	case 3:
		getSavePoints()->push(kEntityNone, kEntityMertens, kAction225358684, hotspot->param1);
		break;

	case 4:
		getSavePoints()->push(kEntityNone, kEntityCoudert, kAction225358684, hotspot->param1);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(concertSitCough) {
	switch(hotspot->param1) {
	default:
		return;

	case 1:
		playAnimation(kEventConcertSit);
		break;

	case 2:
		playAnimation(kEventConcertCough);
		break;
	}

	if (!hotspot->scene)
		getLogic()->processScene();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(29) {
	getProgress().field_C = 1;
	getSound()->playSoundEvent(0, hotspot->param1, hotspot->param2);
	getSound()->playMusic(kEntityNone, hotspot->param3, 16, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(catchBeetle) {
	if (!getBeetle()->isLoaded())
		return;

	if (getBeetle()->catchBeetle()) {
		getBeetle()->unload();
		getInventory()->getEntry(kItemBeetle)->location = kLocation1;
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction202613084);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(exitCompartment) {
	if (!getProgress().field_30 && getProgress().jacket != 0) {
		save(kEntityNone, 0, kEventNone);
		getProgress().field_30 = 1;
	}

	getObjects()->updateLocation2(kObjectCompartment1, (ObjectLocation)hotspot->param2);

	// fall to case enterCompartment action
	action_enterCompartment(hotspot);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(32) {
	switch(hotspot->param1) {
	default:
		break;

	case 1:
		getSavePoints()->push(kEntityNone, kEntitySalko, kAction167992577);
		break;

	case 2:
		getSavePoints()->push(kEntityNone, kEntityVesna, kAction202884544);
		break;

	case 3:
		if (getProgress().chapter == kChapter5) {
			getSavePoints()->push(kEntityNone, kEntityAbbot, kAction168646401);
			getSavePoints()->push(kEntityNone, kEntityMilos, kAction168646401);
		} else {
			getSavePoints()->push(kEntityNone, kEntityTrain, kAction203339360);
		}
		hotspot->scene = 0;
		break;

	case 4:
		getSavePoints()->push(kEntityNone, kEntityMilos, kAction169773228);
		break;

	case 5:
		getSavePoints()->push(kEntityNone, kEntityVesna, kAction167992577);
		break;

	case 6:
		getSavePoints()->push(kEntityNone, kEntityAugust, kAction203078272);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(useWhistle) {
	EventIndex evt = kEventNone;

	switch (hotspot->param1) {
	default:
		break;

	case 1:
		if (getEvent(kEventKronosBringFirebird)) {
			getSavePoints()->push(kEntityNone, kEntityAnna, kAction205294778);
			break;
		}

		if (getEntities()->checkFields1(kEntityNone, EntityData::kField495_3, EntityData::kField491_8200)) {
			evt = kEventCathOpenEgg;

			loadSceneObject(scene, hotspot->scene);

			if (scene.getHotspot())
				hotspot->scene = scene.getHotspot()->scene;
		} else {
			evt = kEventCathOpenEggNoBackground;
		}
		getProgress().is_egg_open = 1;
		break;

	case 2:
		if (getEvent(kEventKronosBringFirebird)) {
			getSavePoints()->push(kEntityNone, kEntityAnna, kAction224309120);
			break;
		}

		evt = (getEntities()->checkFields1(kEntityNone, EntityData::kField495_3, EntityData::kField491_8200)) ? kEventCathCloseEgg : kEventCathCloseEggNoBackground;
		getProgress().is_egg_open = 0;
		break;

	case 3:
		if (getEvent(kEventKronosBringFirebird)) {
			getSavePoints()->push(kEntityNone, kEntityAnna, kAction270751616);
			break;
		}

		evt = (getEntities()->checkFields1(kEntityNone, EntityData::kField495_3, EntityData::kField491_8200)) ? kEventCathUseWhistleOpenEgg : kEventCathUseWhistleOpenEggNoBackground;
		break;

	}

	if (evt != kEventNone) {
		playAnimation(evt);
		if (!hotspot->scene)
			getLogic()->processScene();
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(openMatchBox) {
	// If the match is already in the inventory, do nothing
	if (!getInventory()->getEntry(kItemMatch)->location
		|| getInventory()->getEntry(kItemMatch)->has_item)
		return;

	getInventory()->addItem(kItemMatch);
	getSound()->playSoundEvent(0, 102, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(openBed) {
	getSound()->playSoundEvent(0, 59, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(dialog) {
	getSound()->playDialog(kEntityTables4, (EntityIndex)hotspot->param1, 16, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(eggBox) {
	getSound()->playSoundEvent(0, 43, 0);
	if (getProgress().field_7C) {
		getSound()->playSound(kEntityNone, "MUS003", 16, 0);
		getProgress().field_7C = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(39) {
	getSound()->playSoundEvent(0, 24, 0);
	if (getProgress().field_80) {
		getSound()->playSound(kEntityNone, "MUS003", 16, 0);
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
	case kChapter1:
		id = hotspot->param1;
		break;

	case kChapter2:
	case kChapter3:
		id = hotspot->param2;
		break;

	case kChapter4:
	case kChapter5:
		id = hotspot->param3;
		break;
	}

	if (id)
		getSound()->playMusic(kEntityNone, id, 16, 0);
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(42) {
	int value = 0;
	switch (getProgress().chapter) {
	default:
		break;

	case kChapter1:
		value = 1;
		break;

	case kChapter2:
	case kChapter3:
		value = 2;
		break;

	case kChapter4:
	case kChapter5:
		value = 4;
		break;
	}

	if (hotspot->param3 & value) {
		getSound()->playMusic(kEntityNone, hotspot->param1, 16, 0);

		char filename[6];
		sprintf((char*)&filename, "MUS%03d", hotspot->param1);
		getSavePoints()->call(kEntityNone, kEntityTrain, kAction203863200, (char *)&filename);
		getSavePoints()->push(kEntityNone, kEntityTrain, kAction222746496, hotspot->param2);
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(44) {
	switch (hotspot->param1) {
	default:
		break;

	case 1:
		getSavePoints()->push(kEntityNone, kEntityRebecca, kAction205034665);
		break;

	case 2:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction225358684);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////
void Action::pickGreenJacket(bool process) {
	getProgress().jacket = kJacketGreen;
	getInventory()->addItem(kItemMatchBox);

	getObjects()->update(kObjectOutside, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
	playAnimation(kEventPickGreenJacket);

	getInventory()->setPortrait(kPortraitGreen);

	if (process)
		getLogic()->processScene();
}

void Action::pickScarf(bool process) {
	if (getProgress().jacket == kJacketOriginal)
		playAnimation(kEventPickScarfGreen);
	else
		playAnimation(kEventPickScarfOriginal);

	if (process)
		getLogic()->processScene();
}

void Action::pickCorpse(byte bedPosition, bool process) {

	switch(getInventory()->getEntry(kItemCorpse)->location) {
	// Floor
	case kLocation1:
		if (bedPosition != 4) {
			if (getProgress().jacket == kJacketOriginal)
				playAnimation(kEventCorpsePickFloorOriginal);
			else
				playAnimation(kEventCorpsePickFloorGreen);

			break;
		}

		playAnimation(kEventCorpsePickFloorOpenedBedOriginal);
		getInventory()->getEntry(kItemCorpse)->location = kLocation5;
		break;

	// Bed
	case kLocation2:
		if (getProgress().jacket == kJacketOriginal)
			playAnimation(kEventCorpsePickBedOriginal);
		else
			playAnimation(kEventCorpsePickBedGreen);

		break;

	// No way to pick the corpse
	default:
		break;
	}

	if (process)
		getLogic()->processScene();

	// Add corpse to inventory
	if (bedPosition != 4) { // bed position
		getInventory()->addItem(kItemCorpse);
		getInventory()->selectItem(kItemCorpse);
		_engine->getCursor()->setStyle(kCursorCorpse);
	}
}

void Action::dropCorpse(bool process) {
	switch(getInventory()->getEntry(kItemCorpse)->location) {
	default:
		break;

	case kLocation1:	// Floor
		if (getProgress().jacket == kJacketOriginal)
			playAnimation(kEventCorpseDropFloorOriginal);
		else
			playAnimation(kEventCorpseDropFloorGreen);

		break;

	case kLocation2:	// Bed
		if (getProgress().jacket == kJacketOriginal)
			playAnimation(kEventCorpseDropBedOriginal);
		else
			playAnimation(kEventCorpseDropBedGreen);

		break;

	case kLocation4: // Window
		// Say goodbye to an old friend
		getInventory()->getEntry(kItemCorpse)->location = kLocationNone;
		getProgress().field_20 = 1;

		if (getState()->time <= 1138500) {

			if (getProgress().jacket == kJacketOriginal)
				playAnimation(kEventCorpseDropWindowOriginal);
			else
				playAnimation(kEventCorpseDropWindowGreen);

			getProgress().field_24 = 1;
		} else {
			playAnimation(kEventCorpseDropBridge);
		}

		getProgress().field_8 = 1;
		break;
	}

	if (process)
		getLogic()->processScene();
}

bool Action::handleOtherCompartment(ObjectIndex object, byte param2, byte param3) {

	// Only handle compartments
	if (getEntityData(kEntityNone)->field_493
	|| ((object < kObjectCompartment2 || object > kObjectCompartment8) && (object < kObjectCompartmentA || object > kObjectCompartmentH)))
		return false;

	//////////////////////////////////////////////////////////////////////////
	// Gendarmes
	if (getEntityData(kEntityNone)->field_495 == getEntityData(kEntityGendarmes)->field_495
	&& !getEntityData(kEntityGendarmes)->field_493
	&& !getEntities()->compare(kEntityNone, kEntityGendarmes)) {
		playCompartmentSoundEvents(kEntityNone, object, param2, param3, true);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// Mertens
	if (getEntityData(kEntityNone)->field_493 == EntityData::kField493_3
	 && getEntityData(kEntityMertens)->field_495 == EntityData::kField495_3
	 && !getEntityData(kEntityMertens)->field_493
	 && !((EntityData::EntityParametersIIII*)getEntities()->getData(kEntityMertens)->getParameters(8, 0))->param1) {

		 error("Action::handleOtherCompartment: not implemented!");

		 return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// Coudert
	if (getEntityData(kEntityNone)->field_493 != EntityData::kField493_4
	 || !getEntityData(kEntityCoudert)->field_495
	 || getEntityData(kEntityCoudert)->field_493
	 || ((EntityData::EntityParametersIIII*)getEntities()->getData(kEntityCoudert)->getParameters(8, 0))->param1)
	 return false;

	if (!getEntities()->compare(kEntityNone, kEntityCoudert)) {
		error("Action::handleOtherCompartment: not implemented!");
	}

	// Direction = Up
	if (!getEntities()->compare(kEntityNone, kEntityCoudert)
	&& getEntityData(kEntityCoudert)->direction == kDirectionUp
	&& getEntityData(kEntityCoudert)->field_491 < getEntityData(kEntityNone)->field_491) {
		playCompartmentSoundEvents(kEntityCoudert, object, param2, param3, true);

		return true;
	}

	// Direction = down
	if (!getEntities()->compare(kEntityNone, kEntityCoudert)
	&& getEntityData(kEntityCoudert)->direction == kDirectionDown
	&& getEntityData(kEntityCoudert)->field_491 > getEntityData(kEntityNone)->field_491) {
		playCompartmentSoundEvents(kEntityCoudert, object, param2, param3, false);

		return true;
	}

	return false;
}

void Action::playCompartmentSoundEvents(EntityIndex entityIndex, ObjectIndex object, byte param2, byte param3, bool loadSceneFunction) {
	if (param2) {
		if (getObjects()->get(object).location == 1 || getObjects()->get(object).location == 3 || getEntities()->checkFields2(object)) {
			getSound()->playSoundEvent(kEntityNone, 13, 0);
		} else {
			getSound()->playSoundEvent(kEntityNone, 14, 0);
			getSound()->playSoundEvent(kEntityNone, 15, 3);
		}
	}

	if (entityIndex != kEntityNone) {
		// HmHmmm...
		if (!getSound()->isBuffered(entityIndex))
			getSound()->playSound(entityIndex, (random(2)) ? "JAC1000" : "JAC1000A");
	}

	if (param3) {
		if (loadSceneFunction)
			getLogic()->loadSceneFromObject(object);
		else
			getLogic()->loadSceneFromObject2(object);
	}
}

//////////////////////////////////////////////////////////////////////////
// Cursors
//////////////////////////////////////////////////////////////////////////
CursorStyle Action::getCursor(byte action, ObjectIndex object, byte param2, byte param3, byte cursor)
{
	// Simple cursor style
	if (cursor != kCursorProcess)
		return (CursorStyle)cursor;

	//warning("================================= OBJECT %03d =================================", object);

	switch (action) {
	default:
		return kCursorNormal;

	case SceneHotspot::kActionInventory:
		if (!getState()->sceneBackup2 && (getEvent(kEventKronosBringFirebird) || getProgress().is_egg_open))
			return kCursorNormal;
		else
			return kCursorBackward;

	case SceneHotspot::kActionKnockOnDoor:
		if (object >= kObjectMax)
			return kCursorNormal;
		else
			return (CursorStyle)getObjects()->get(object).cursor;

	case SceneHotspot::kAction12:
		if (object >= kObjectMax)
			return kCursorNormal;

		if (getObjects()->get(object).entity)
			return (CursorStyle)getObjects()->get(object).cursor;
		else
			return kCursorNormal;

	case SceneHotspot::kActionPickItem:
		if (object >= kObjectCompartmentA)
			return kCursorNormal;

		if ((!getInventory()->getSelectedItem() || getInventory()->getSelectedEntry()->no_autoselect)
		 && (object != kObject21 || getProgress().field_8 == 1))
			return kCursorHand;
		else
			return kCursorNormal;

	case SceneHotspot::kActionDropItem:
		if (object >= kObjectCompartmentA)
			return kCursorNormal;

		if (getInventory()->getSelectedItem() != (InventoryItem)object)
			return kCursorNormal;

		if (object == kObject20 && param2 == 4 && !getProgress().field_50)
			return kCursorNormal;

		if (object == kObjectHandleInsideBathroom  && param2 == 1 && getProgress().field_5C)
			return kCursorNormal;

		return (CursorStyle)getInventory()->getSelectedEntry()->item_id;

	case SceneHotspot::kAction15:
		if (object >= kObjectMax)
			return kCursorNormal;

		if (*(&getProgress().field_0 + object) == param2)
			return (CursorStyle)param3;

		return kCursorNormal;

	case SceneHotspot::kActionEnterCompartment:
		if ((getInventory()->getSelectedItem() != kItemKey || getObjects()->get(kObjectCompartment1).location)
		&& (getObjects()->get(kObjectCompartment1).location != 1 || !getInventory()->hasItem(kItemKey)
		 ||	(getInventory()->getSelectedItem() != kItemFirebird && getInventory()->getSelectedItem() != kItemBriefcase)))
			goto LABEL_KEY;

		return (CursorStyle)getInventory()->getEntry(kItemKey)->item_id; // TODO is that always the same as kCursorKey ?

	case SceneHotspot::kActionGetOutsideTrain:
		if (getProgress().jacket != kJacketGreen)
			return kCursorNormal;

		if ((getEvent(kEventCathLookOutsideWindowDay) || getEvent(kEventCathLookOutsideWindowDay) || getObjects()->get(kObjectCompartment1).location2 == kLocation1)
			&& getProgress().field_50
			&& (object != kObject45 || (getEntities()->checkFields1(kEntityRebecca, EntityData::kField495_4, EntityData::kField491_4840) && getObjects()->get(kObject44).location == 2))
			&& getInventory()->getSelectedItem() != kItemBriefcase && getInventory()->getSelectedItem() != kItemFirebird)
			return kCursorForward;

		// FIXME convert to something readable
		return (CursorStyle)((((getObjects()->get(kObjectCompartment1).location2 - 1) < 1) - 1) & 11);

	case SceneHotspot::kActionSlip:
		// FIXME convert to something readable
		return (CursorStyle)(((getProgress().field_C8 < 1) - 1) & 7);

	case SceneHotspot::kActionClimbUpTrain:
		if (getProgress().field_50
			&& (getProgress().chapter == kChapter2 || getProgress().chapter == kChapter3 || getProgress().chapter == kChapter5)
			&& getInventory()->getSelectedItem() != kItemFirebird
			&& getInventory()->getSelectedItem() != kItemBriefcase)
			return kCursorUp;

		return kCursorNormal;

	case SceneHotspot::kActionJumpUpDownTrain:
		if (object != kObjectCompartment1)
			return kCursorNormal;

		// FIXME convert to something readable
		return (CursorStyle)(-(getObjects()->get(kObjectCeiling).location < 1) & 9);

	case SceneHotspot::kActionUnbound:
		if (param2 != 2)
			return kCursorNormal;

		if (getEvent(kEventCathBurnRope) || !getEvent(kEventCathStruggleWithBonds2))
			return kCursorNormal;

		return kCursorHand;

	case SceneHotspot::kActionCatchBeetle:
		if (!getBeetle()->isLoaded())
			return kCursorNormal;

		if (!getBeetle()->isCatchable())
			return kCursorNormal;

		if (getInventory()->getSelectedItem() == kItemMatchBox && getInventory()->hasItem(kItemMatch))
			return (CursorStyle)getInventory()->getEntry(kItemMatchBox)->item_id;

		return kCursorHandPointer;

	case SceneHotspot::KActionUseWhistle:
		if (object != 3)
			return kCursorNormal;

		if (getInventory()->getSelectedItem() == kItemWhistle)
			return kCursorWhistle;
		else
			return kCursorNormal;

	case SceneHotspot::kActionOpenBed:
		if (getProgress().chapter < kChapter2)
			return kCursorHand;

		return kCursorNormal;

	case SceneHotspot::kActionDialog:
		if (getSound()->getDialogName((EntityIndex)object))
			return kCursorHandPointer;

		return kCursorNormal;

	case SceneHotspot::kActionBed:
		if (getProgress().field_18 == 2 && !getProgress().field_E4
			&& (getState()->time > 1404000
			|| (getProgress().event_august_met && getProgress().field_CC
			&& (!getProgress().field_24 || getProgress().field_3C))))
			return kCursorSleep;

		return kCursorNormal;

LABEL_KEY:
	case SceneHotspot::kActionCompartment:
	case SceneHotspot::kActionExitCompartment:
		if (object >= kObjectMax)
			return kCursorNormal;

		if (getInventory()->getSelectedItem() != kItemKey
		|| getObjects()->get(object).entity
		|| getObjects()->get(object).location != 1
		|| !getObjects()->get(object).cursor2
		|| getEntities()->checkFields3(kEntityNone)
		|| getEntities()->checkFields2(object))
			return (CursorStyle)getObjects()->get(object).cursor2;
		else
			return (CursorStyle)getInventory()->getEntry(kItemKey)->item_id;
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
