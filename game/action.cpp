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
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

static const int _animationListSize = 273;

// List of animations
static const struct {
	const char *filename;
	uint16 time;
} animationList[_animationListSize] = {
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
	ADD_ACTION(switchChapter);
	ADD_ACTION(44);
}

Action::~Action() {
	for (int i = 0; i < (int)_actions.size(); i++)
		delete _actions[i];

	// Zero-out passed pointers
	_engine = NULL;
}

//////////////////////////////////////////////////////////////////////////
// Processing hotspot
//////////////////////////////////////////////////////////////////////////
SceneIndex Action::processHotspot(const SceneHotspot &hotspot) {
	if (!hotspot.action || hotspot.action >= _actions.size())
		return kSceneInvalid;

	return (*_actions[hotspot.action])(hotspot);
}

//////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Action 0
IMPLEMENT_ACTION(dummy) {
	error("Action::action_dummy: Function should never be called (hotspot action: %d)!", hotspot.action);
}

//////////////////////////////////////////////////////////////////////////
// Action 1
IMPLEMENT_ACTION(inventory) {
	if (!getState()->sceneUseBackup)
		return kSceneInvalid;

	SceneIndex index = kSceneNone;
	if (getState()->sceneBackup2) {
		index = getState()->sceneBackup2;
		getState()->sceneBackup2 = kSceneNone;
	} else {
		getState()->sceneUseBackup = false;
		index = getState()->sceneBackup;

		Scene *backup = getScenes()->get(getState()->sceneBackup);
		if (getEntities()->getPosition(backup->car, backup->position))
			index = getScenes()->processIndex(getState()->sceneBackup);
	}

	getScenes()->loadScene(index);

	if (!getInventory()->getSelectedItem())
		return kSceneInvalid;

	if (!getInventory()->getSelectedEntry()->isSelectable || (!getState()->sceneBackup2 && getInventory()->getFirstExaminableItem()))
		getInventory()->selectItem(getInventory()->getFirstExaminableItem());

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 2
IMPLEMENT_ACTION(savePoint) {
	getSavePoints()->push(kEntityNone, (EntityIndex)hotspot.param1, (ActionIndex)hotspot.param2);

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 3
IMPLEMENT_ACTION(playSound) {

	// Check that the file is not already buffered
	char filename[8];
	sprintf((char *)&filename, "LIB%03d", hotspot.param1);

	if (hotspot.param2 || !getSound()->isBuffered(filename, true))
		getSound()->playSoundEvent(kEntityNone, hotspot.param1, hotspot.param2);

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 4
IMPLEMENT_ACTION(playMusic) {
	// Check that the file is not already buffered
	char filename[8];
	sprintf((char *)&filename, "MUS%03d", hotspot.param1);

	if (!getSound()->isBuffered(filename) &&
	   (hotspot.param1 != 50 || getProgress().chapter == kChapter5))
		getSound()->playSound(kEntityNone, filename, 16, hotspot.param2);

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 5
IMPLEMENT_ACTION(knock) {
	ObjectIndex object = (ObjectIndex)hotspot.param1;

	if (object >= kObjectMax)
		return kSceneInvalid;

	if (getObjects()->get(object).entity) {
		getSavePoints()->push(kEntityNone, getObjects()->get(object).entity, kAction8, object);
	} else {
		if (!getSound()->isBuffered("LIB012", true))
			getSound()->playSoundEvent(kEntityNone, 12);
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 6
IMPLEMENT_ACTION(compartment) {
	ObjectIndex object = (ObjectIndex)hotspot.param1;

	if (object >= kObjectMax)
		return kSceneInvalid;

	if (getObjects()->get(object).entity) {
		getSavePoints()->push(kEntityNone, getObjects()->get(object).entity, kAction9, object);

		// Stop processing further
		return kSceneNone;
	}

	if (handleOtherCompartment(object, 1, 1)) {
		// Stop processing further
		return kSceneNone;
	}

	ObjectLocation location = getObjects()->get(object).location;
	if (location == 1 || location == 3 || getEntities()->checkFields2(object)) {

		// FIXME check again, this might be wrong (and simplify expression)
		if (location != 1
		 || getEntities()->checkFields2(object)
		 || (getInventory()->getSelectedItem() != kItemKey
		  && (location != 1 || !getInventory()->hasItem(kItemKey)
		   || getInventory()->getSelectedItem() != kItemFirebird
		   || getInventory()->getSelectedItem() != kItemBriefcase))) {
				getSound()->playSoundEvent(kEntityNone, 13);

				// Stop processing further
				return kSceneNone;
		}

		getSound()->playSoundEvent(kEntityNone, 32);

		if ((object >= 1 && object <= 3) || (object >= 32 && object <= 37))
			getObjects()->update(object, kEntityNone, kLocationNone, kCursorHandKnock, kCursorHand);

		getSound()->playSoundEvent(kEntityNone, 15, 22);
		getInventory()->unselectItem();

		return kSceneInvalid;
	}

	if (hotspot.action != 16 || getInventory()->getSelectedItem() != kItemKey) {
		if (object == 109) {
			getSound()->playSoundEvent(kEntityNone, 26);
		} else {
			getSound()->playSoundEvent(kEntityNone, 14);
			getSound()->playSoundEvent(kEntityNone, 15, 22);
		}
		return kSceneInvalid;
	}

	getObjects()->update(kObjectCompartment1, kEntityNone, kLocation1, kCursorHandKnock, kCursorHand);
	getSound()->playSoundEvent(kEntityNone, 16);
	getInventory()->unselectItem();

	// Stop processing further
	return kSceneNone;
}

//////////////////////////////////////////////////////////////////////////
// Action 7
IMPLEMENT_ACTION(playSounds) {
	getSound()->playSoundEvent(kEntityNone, hotspot.param1);
	getSound()->playSoundEvent(kEntityNone, hotspot.param3, hotspot.param2);

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 8
IMPLEMENT_ACTION(playAnimation) {
	if (getEvent(hotspot.param1))
		return kSceneInvalid;

	playAnimation((EventIndex)hotspot.param1);

	if (!hotspot.scene)
		getScenes()->processScene();

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 9
IMPLEMENT_ACTION(openCloseObject) {
	ObjectIndex object = (ObjectIndex)hotspot.param1;
	ObjectLocation location = (ObjectLocation)hotspot.param2;

	if (object >= kObjectMax)
		return kSceneInvalid;

	getObjects()->update(object, getObjects()->get(object).entity, location, kCursorKeepValue, kCursorKeepValue);

	bool isNotWindow = ((object <= kObjectCompartment8  || object >= kObjectHandleBathroom) && (object <= kObjectCompartmentH || object >= kObject48));

	switch (location) {
	case kLocation1:
		if (isNotWindow)
			getSound()->playSoundEvent(kEntityNone, 24);
		else
			getSound()->playSoundEvent(kEntityNone, 21);
		break;

	case kLocation2:
		if (isNotWindow)
			getSound()->playSoundEvent(kEntityNone, 36);
		else
			getSound()->playSoundEvent(kEntityNone, 20);
		break;

	default:
		break;
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 10
IMPLEMENT_ACTION(10) {
	ObjectIndex object = (ObjectIndex)hotspot.param1;

	if (object >= kObjectMax)
		return kSceneInvalid;

	getObjects()->updateLocation2(object, (ObjectLocation)hotspot.param2);

	if (object != kObject112 || getSound()->isBuffered("LIB096")) {
		if (object == 1)
			getSound()->playSoundEvent(kEntityNone, 73);
	} else {
		getSound()->playSoundEvent(kEntityNone, 96);
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 11
IMPLEMENT_ACTION(setItemLocation) {
	InventoryItem item = (InventoryItem)hotspot.param1;
	Inventory::InventoryEntry* entry = getInventory()->getEntry(item);

	if (!entry->isPresent)
		return kSceneInvalid;

	entry->location = (ObjectLocation)hotspot.param2;

	if (item == kItemCorpse) {
		ObjectLocation corpseLocation = getInventory()->getEntry(kItemCorpse)->location;

		if (corpseLocation == kLocation3 || corpseLocation == kLocation4)
			getProgress().eventCorpseMovedFromFloor = 1;
		else
			getProgress().eventCorpseMovedFromFloor = 0;
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 12
IMPLEMENT_ACTION(12) {
	ObjectIndex object = (ObjectIndex)hotspot.param1;

	if (object >= kObjectMax)
		return kSceneInvalid;

	if (getObjects()->get(object).entity)
		getSavePoints()->push(kEntityNone, getObjects()->get(object).entity, kAction8, object);

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 13
IMPLEMENT_ACTION(pickItem) {
	InventoryItem item = (InventoryItem)hotspot.param1;
	Inventory::InventoryEntry* entry = getInventory()->getEntry(item);
	byte location = hotspot.param2;
	bool process = (hotspot.scene == 0);
	SceneIndex continueProcess = kSceneInvalid;

	if (item >= kPortraitOriginal || !entry->location)
		return kSceneInvalid;

	// Special case for corpse
	if (item == kItemCorpse) {
		pickCorpse(location, process);
		return kSceneInvalid;
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
		return kSceneInvalid;

	case kItemParchemin:
		if (location != kLocation2)
			break;

		getInventory()->addItem(kItemParchemin);
		getInventory()->getEntry(kItem11)->location = kLocation1;
		getSound()->playSoundEvent(kEntityNone, 9);
		break;

	case kItemBomb:
		RESET_ENTITY_STATE(kEntityAbbot, Abbot, setup_pickBomb);
		break;

	case kItemBriefcase:
		getSound()->playSoundEvent(kEntityNone, 83);
		break;

	default:
		break;
	}

	// Load item scene
	if (getInventory()->getEntry(item)->scene) {
		if (!getState()->sceneUseBackup) {
			getState()->sceneUseBackup = true;
			getState()->sceneBackup = (hotspot.scene ? hotspot.scene : getState()->scene);
		}

		getScenes()->loadScene(getInventory()->getEntry(item)->scene);

		// do not process further
		continueProcess = kSceneStopProcessing;
	}

	// Select item
	if (getInventory()->getEntry(item)->isSelectable) {
		getInventory()->selectItem(item);
		_engine->getCursor()->setStyle(getInventory()->getEntry(item)->cursor);
	}

	return continueProcess;
}

//////////////////////////////////////////////////////////////////////////
// Action 14
IMPLEMENT_ACTION(dropItem) {
	InventoryItem item = (InventoryItem)hotspot.param1;
	ObjectLocation location = (ObjectLocation)hotspot.param2;
	bool process = (hotspot.scene == kSceneNone);

	if (item >= kPortraitOriginal)
		return kSceneInvalid;

	if (!getInventory()->hasItem(item))
		return kSceneInvalid;

	if (location < kLocation1)
		return kSceneInvalid;

	// Handle actions
	if (item == kItemBriefcase) {
		getSound()->playSoundEvent(kEntityNone, 82);

		if (location == kLocation2) {
			if (!getProgress().field_58) {
				save(kEntityNone, kSavegameType0, kEventNone);
				getProgress().field_58 = 1;
			}

			if (getInventory()->getEntry(kItemParchemin)->location == kLocation2) {
				getInventory()->addItem(kItemParchemin);
				getInventory()->getEntry(kItem11)->location = kLocation11;
				getSound()->playSoundEvent(kEntityNone, 9);
			}
		}
	}

	// Update item location
	getInventory()->removeItem(item, location);

	if (item == kItemCorpse)
		dropCorpse(process);

	// Unselect item
	getInventory()->unselectItem();

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 15: Dummy action

//////////////////////////////////////////////////////////////////////////
// Action 16
IMPLEMENT_ACTION(enterCompartment) {
	if (getObjects()->get(kObjectCompartment1).location == 1 || getObjects()->get(kObjectCompartment1).location == 3 || getInventory()->getSelectedItem() == kItemKey) {
		action_compartment(hotspot);
		return kSceneInvalid;
	}

	if (getProgress().eventCorpseFound) {
		if (hotspot.action != 16 || getInventory()->getEntry(kItemBriefcase)->location != 2) {
			action_compartment(hotspot);
		} else {
			getSound()->playSoundEvent(kEntityNone, 14);
			getSound()->playSoundEvent(kEntityNone, 15, 22);

			if (getProgress().field_78) {
				getSound()->playSound(kEntityNone, "MUS003", 16);
				getProgress().field_78 = 0;
			}

			getScenes()->loadSceneFromPosition(kCarGreenSleeping, 77);
			return kSceneNone;
		}
	} else {
		save(kEntityNone, kSavegameType0, kEventNone);
		getSound()->playSound(kEntityNone, "LIB014");
		playAnimation(kEventCathFindCorpse);
		getSound()->playSound(kEntityNone, "LIB015");
		getProgress().eventCorpseFound = 1;
		return kSceneCompartmentCorpse;
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 17: Dummy action

//////////////////////////////////////////////////////////////////////////
// Action 18
IMPLEMENT_ACTION(getOutsideTrain) {
	ObjectIndex object = (ObjectIndex)hotspot.param1;

	if ((getEvent(kEventCathLookOutsideWindowDay) || getEvent(kEventCathLookOutsideWindowNight) || getObjects()->get(kObjectCompartment1).location2)
	  && getProgress().isTrainRunning
	  && (object != kObjectOutsideAnnaCompartment || (!getEntities()->checkFields1(kEntityRebecca, kCarRedSleeping, kPosition_4840) && getObjects()->get(kObjectOutsideBetweenCompartments).location == kLocation2))
	  && getInventory()->getSelectedItem() != kItemFirebird
	  && getInventory()->getSelectedItem() != kItemBriefcase) {

		switch (object) {
		default:
			return kSceneInvalid;

		case kObjectOutsideTylerCompartment:
			getEvent(kEventCathLookOutsideWindowDay) = 1;
			playAnimation(isDay() ? kEventCathGoOutsideTylerCompartmentDay : kEventCathGoOutsideTylerCompartmentNight);
			getProgress().field_C8 = 1;
			break;

		case kObjectOutsideBetweenCompartments:
			getEvent(kEventCathLookOutsideWindowDay) = 1;
			playAnimation(isDay() ? kEventCathGoOutsideDay : kEventCathGoOutsideNight);
			getProgress().field_C8 = 1;
			break;

		case kObjectOutsideAnnaCompartment:
			getEvent(kEventCathLookOutsideWindowDay) = 1;
			playAnimation(isDay() ? kEventCathGetInsideDay : kEventCathGetInsideNight);
			if (!hotspot.scene)
				getScenes()->processScene();
			break;
		}
	} else {
		if (object == kObjectOutsideTylerCompartment || object == kObjectOutsideBetweenCompartments || object == kObjectOutsideAnnaCompartment) {
			playAnimation(isDay() ? kEventCathLookOutsideWindowDay : kEventCathLookOutsideWindowNight);
			getScenes()->processScene();
			return kSceneNone;
		}
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 19
IMPLEMENT_ACTION(slip) {
	switch((ObjectIndex)hotspot.param1) {
	default:
		return kSceneInvalid;

	case kObjectOutsideTylerCompartment:
		playAnimation(isDay() ? kEventCathSlipTylerCompartmentDay : kEventCathSlipTylerCompartmentNight);
		break;

	case kObjectOutsideBetweenCompartments:
		playAnimation(isDay() ? kEventCathSlipDay : kEventCathSlipNight);
		break;
	}

	getProgress().field_C8 = 0;

	if (!hotspot.scene)
		getScenes()->processScene();

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 20
IMPLEMENT_ACTION(getInsideTrain) {
	switch ((ObjectIndex)hotspot.param1) {
	default:
		return kSceneInvalid;

	case kObjectOutsideTylerCompartment:
		playAnimation(isDay() ? kEventCathGetInsideTylerCompartmentDay : kEventCathGetInsideTylerCompartmentNight);
		break;

	case kObjectOutsideBetweenCompartments:
		playAnimation(isDay() ? kEventCathGetInsideDay : kEventCathGetInsideNight);
		break;

	case kObjectOutsideAnnaCompartment:
		playAnimation(kEventCathGettingInsideAnnaCompartment);
		break;
	}

	if (!hotspot.scene)
		getScenes()->processScene();

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 21
IMPLEMENT_ACTION(climbUpTrain) {
	byte action = hotspot.param1;

	if (action != 1 && action != 2)
		return kSceneInvalid;

	switch (getProgress().chapter) {
	default:
		break;

	case kChapter2:
	case kChapter3:
		if (action == 2)
			playAnimation(kEventCathClimbUpTrainGreenJacket);

		playAnimation(kEventCathTopTrainGreenJacket);
		break;

	case kChapter5:
		if (action == 2)
			playAnimation(getProgress().isNightTime ? kEventCathClimbUpTrainNoJacketNight : kEventCathClimbUpTrainNoJacketDay);

		playAnimation(getProgress().isNightTime ? kEventCathTopTrainNoJacketNight : kEventCathTopTrainNoJacketDay);
		break;
	}

	if (!hotspot.scene)
		getScenes()->processScene();

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 22
IMPLEMENT_ACTION(climbDownTrain) {
	EventIndex evt = kEventNone;
	switch (getProgress().chapter) {
	default:
		return kSceneInvalid;

	case kChapter2:
	case kChapter3:
		evt = kEventCathClimbDownTrainGreenJacket;
		break;

	case kChapter5:
		evt = (getProgress().isNightTime ? kEventCathClimbDownTrainNoJacketNight : kEventCathClimbDownTrainNoJacketDay);
		break;
	}

	playAnimation(evt);
	if (evt == kEventCathClimbDownTrainNoJacketDay)
		getSound()->playSoundEvent(kEntityNone, 37);

	if (!hotspot.scene)
		getScenes()->processScene();

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 23
IMPLEMENT_ACTION(jumpUpDownTrain) {
	switch (hotspot.param1) {
	default:
		error("Action::action_jumpUpDownTrain: Invalid hotspot.param1 value (%d)", hotspot.param1);

	case 1:
		getSavePoints()->push(kEntityNone, kEntityChapters, kActionBreakCeiling);
		break;

	case 2:
		getSavePoints()->push(kEntityNone, kEntityChapters, kActionJumpDownCeiling);
		break;

	case 3:
		if (getInventory()->getSelectedItem() == kItemBriefcase) {
			getInventory()->removeItem(kItemBriefcase, kLocation3);
			getSound()->playSoundEvent(kEntityNone, 82);
			getInventory()->unselectItem();
		}

		// Show animation with or without briefcase
		playAnimation((getInventory()->getEntry(kItemBriefcase)->location - 3) ? kEventCathJumpUpCeilingBriefcase : kEventCathJumpUpCeiling);

		if (!hotspot.scene)
			getScenes()->processScene();

		break;

	case 4:
		if (getProgress().chapter == kChapter1)
			getSavePoints()->push(kEntityNone, kEntityKronos, kAction202621266);
		break;
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 24
IMPLEMENT_ACTION(unbound) {
	byte action = hotspot.param1;

	switch (action) {
	default:
		break;

	case 1:
		playAnimation(kEventCathStruggleWithBonds);
		if (hotspot.scene)
			getScenes()->processScene();
		break;

	case 2:
		playAnimation(kEventCathBurnRope);
		if (hotspot.scene)
			getScenes()->processScene();
		break;

	case 3:
		if (getEvent(kEventCathBurnRope)) {
			playAnimation(kEventCathRemoveBonds);
			getProgress().field_84 = 0;
			getScenes()->loadSceneFromPosition(kCarBaggageRear, 89);
			return kSceneNone;
		}
		break;

	case 4:
		if (!getEvent(kEventCathStruggleWithBonds2)) {
			playAnimation(kEventCathStruggleWithBonds2);
			getSound()->playSoundEvent(kEntityNone, 101);
			getInventory()->setLocationAndProcess(kItemMatch, kLocation2);
			if (!hotspot.scene)
				getScenes()->processScene();
		}
		break;

	case 5:
		getSavePoints()->push(kEntityNone, kEntityIvo, kAction192637492);
		break;
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 25
IMPLEMENT_ACTION(25) {
	switch(hotspot.param1) {
	default:
		break;

	case 1:
		getSavePoints()->push(kEntityNone, kEntityAnna, kAction272177921);
		break;

	case 2:
		if (!getSound()->isBuffered("MUS021"))
			getSound()->playSound(kEntityNone, "MUS021", 16);
		break;

	case 3:
		getSound()->playSoundEvent(kEntityNone, 43);
		if (!getInventory()->hasItem(kItemKey)) {
			if (!getEvent(kEventAnnaBagageArgument)) {
				RESET_ENTITY_STATE(kEntityAnna, Anna, setup_bagage);
				return kSceneNone;
			}
		}
		break;
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 26
IMPLEMENT_ACTION(26) {
	switch(hotspot.param1) {
	default:
		return kSceneInvalid;

	case 1:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction158610240);
		return kSceneInvalid;

	case 2:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction225367984);
		getInventory()->unselectItem();
		break;

	case 3:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction191001984);
		break;

	case 4:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction201959744);
		break;

	case 5:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction169300225);
		break;
	}

	return kSceneNone;
}

//////////////////////////////////////////////////////////////////////////
// Action 27
IMPLEMENT_ACTION(27) {
	if (!getSound()->isBuffered("LIB031", true))
		getSound()->playSoundEvent(kEntityNone, 31);

	switch (getEntityData(kEntityNone)->car) {
	default:
		break;

	case kCarGreenSleeping:
		getSavePoints()->push(kEntityNone, kEntityMertens, kAction225358684, hotspot.param1);
		break;

	case kCarRedSleeping:
		getSavePoints()->push(kEntityNone, kEntityCoudert, kAction225358684, hotspot.param1);
		break;
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 28
IMPLEMENT_ACTION(concertSitCough) {
	switch(hotspot.param1) {
	default:
		return kSceneInvalid;

	case 1:
		playAnimation(kEventConcertSit);
		break;

	case 2:
		playAnimation(kEventConcertCough);
		break;
	}

	if (!hotspot.scene)
		getScenes()->processScene();

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 29
IMPLEMENT_ACTION(29) {
	getProgress().field_C = 1;
	getSound()->playSoundEvent(kEntityNone, hotspot.param1, hotspot.param2);

	char filename[8];
	sprintf((char *)&filename, "MUS%03d", hotspot.param3);

	if (!getSound()->isBuffered(filename))
		getSound()->playSound(kEntityNone, filename, 16);

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 30
IMPLEMENT_ACTION(catchBeetle) {
	if (!getBeetle()->isLoaded())
		return kSceneInvalid;

	if (getBeetle()->catchBeetle()) {
		getBeetle()->unload();
		getInventory()->getEntry(kItemBeetle)->location = kLocation1;
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction202613084);
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 31
IMPLEMENT_ACTION(exitCompartment) {
	if (!getProgress().field_30 && getProgress().jacket != 0) {
		save(kEntityNone, kSavegameType0, kEventNone);
		getProgress().field_30 = 1;
	}

	getObjects()->updateLocation2(kObjectCompartment1, (ObjectLocation)hotspot.param2);

	// fall to case enterCompartment action
	action_enterCompartment(hotspot);

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 32
IMPLEMENT_ACTION(32) {
	switch(hotspot.param1) {
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
		// Stop processing further scenes
		return kSceneNone;

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

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 33
IMPLEMENT_ACTION(useWhistle) {
	EventIndex evt = kEventNone;

	switch (hotspot.param1) {
	default:
		break;

	case 1:
		if (getEvent(kEventKronosBringFirebird)) {
			getSavePoints()->push(kEntityNone, kEntityAnna, kAction205294778);
			break;
		}

		if (getEntities()->checkFields1(kEntityNone, kCarGreenSleeping, kPosition_8200)) {
			evt = kEventCathOpenEgg;

			Scene *scene = getScenes()->get(hotspot.scene);
			if (scene->getHotspots())
				return scene->getHotspot()->scene;

		} else {
			evt = kEventCathOpenEggNoBackground;
		}
		getProgress().isEggOpen = 1;
		break;

	case 2:
		if (getEvent(kEventKronosBringFirebird)) {
			getSavePoints()->push(kEntityNone, kEntityAnna, kAction224309120);
			break;
		}

		evt = (getEntities()->checkFields1(kEntityNone, kCarGreenSleeping, kPosition_8200)) ? kEventCathCloseEgg : kEventCathCloseEggNoBackground;
		getProgress().isEggOpen = 0;
		break;

	case 3:
		if (getEvent(kEventKronosBringFirebird)) {
			getSavePoints()->push(kEntityNone, kEntityAnna, kAction270751616);
			break;
		}

		evt = (getEntities()->checkFields1(kEntityNone, kCarGreenSleeping, kPosition_8200)) ? kEventCathUseWhistleOpenEgg : kEventCathUseWhistleOpenEggNoBackground;
		break;

	}

	if (evt != kEventNone) {
		playAnimation(evt);
		if (!hotspot.scene)
			getScenes()->processScene();
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 34
IMPLEMENT_ACTION(openMatchBox) {
	// If the match is already in the inventory, do nothing
	if (!getInventory()->getEntry(kItemMatch)->location
		|| getInventory()->getEntry(kItemMatch)->isPresent)
		return kSceneInvalid;

	getInventory()->addItem(kItemMatch);
	getSound()->playSoundEvent(kEntityNone, 102);

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 35
IMPLEMENT_ACTION(openBed) {
	getSound()->playSoundEvent(kEntityNone, 59);

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 36: Dummy action

//////////////////////////////////////////////////////////////////////////
// Action 37
IMPLEMENT_ACTION(dialog) {
	getSound()->playDialog(kEntityTables4, (EntityIndex)hotspot.param1, 16, 0);

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 38
IMPLEMENT_ACTION(eggBox) {
	getSound()->playSoundEvent(kEntityNone, 43);
	if (getProgress().field_7C) {

		if (!getSound()->isBuffered("MUS003")) {
			getSound()->playSound(kEntityNone, "MUS003", 16);
			getProgress().field_7C = 0;
		}
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 39
IMPLEMENT_ACTION(39) {
	getSound()->playSoundEvent(kEntityNone, 24);
	if (getProgress().field_80) {
		if (!getSound()->isBuffered("MUS003")) {
			getSound()->playSound(kEntityNone, "MUS003", 16);
			getProgress().field_80 = 0;
		}
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 40
IMPLEMENT_ACTION(bed) {
	getSound()->playSoundEvent(kEntityNone, 85);
	// falls to case 12
	return action_12(hotspot);
}

//////////////////////////////////////////////////////////////////////////
// Action 41
IMPLEMENT_ACTION(41) {
	byte id = 0;
	switch (getProgress().chapter) {
	default:
		error("Action::action_41: Invalid chapter %d", getProgress().chapter);

	case kChapter1:
		id = hotspot.param1;
		break;

	case kChapter2:
	case kChapter3:
		id = hotspot.param2;
		break;

	case kChapter4:
	case kChapter5:
		id = hotspot.param3;
		break;
	}

	if (id) {
		char filename[8];
		sprintf((char *)&filename, "MUS%03d", id);

		if (!getSound()->isBuffered(filename))
			getSound()->playSound(kEntityNone, filename, 16);
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 42
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

	char filename[8];
	sprintf((char *)&filename, "MUS%03d", value);

	if (!getSound()->isBuffered(filename) && hotspot.param3 & value) {
		getSound()->playSound(kEntityNone, filename, 16);

		getSavePoints()->call(kEntityNone, kEntityTrain, kAction203863200, (char *)&filename);
		getSavePoints()->push(kEntityNone, kEntityTrain, kAction222746496, hotspot.param2);
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// // Action 43
IMPLEMENT_ACTION(switchChapter) {
	// Nothing to do here as an hotspot action
	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Action 44
IMPLEMENT_ACTION(44) {
	switch (hotspot.param1) {
	default:
		break;

	case 1:
		getSavePoints()->push(kEntityNone, kEntityRebecca, kAction205034665);
		break;

	case 2:
		getSavePoints()->push(kEntityNone, kEntityChapters, kAction225358684);
		break;
	}

	return kSceneInvalid;
}

//////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////
void Action::pickGreenJacket(bool process) const {
	getProgress().jacket = kJacketGreen;
	getInventory()->addItem(kItemMatchBox);

	getObjects()->update(kObjectOutsideTylerCompartment, kEntityNone, kLocation2, kCursorKeepValue, kCursorKeepValue);
	playAnimation(kEventPickGreenJacket);

	getInventory()->setPortrait(kPortraitGreen);

	if (process)
		getScenes()->processScene();
}

void Action::pickScarf(bool process) const {
	playAnimation(getProgress().jacket == kJacketGreen ? kEventPickScarfGreen : kEventPickScarfOriginal);

	if (process)
		getScenes()->processScene();
}

void Action::pickCorpse(byte bedPosition, bool process) const {

	if (getProgress().jacket == kJacketOriginal)
		getProgress().jacket = kJacketBlood;

	switch(getInventory()->getEntry(kItemCorpse)->location) {
	// No way to pick the corpse
	default:
		break;

	// Floor
	case kLocation1:
		if (bedPosition != 4) {
			playAnimation(getProgress().jacket == kJacketGreen ? kEventCorpsePickFloorGreen : kEventCorpsePickFloorOriginal);
			break;
		}

		if (getProgress().jacket)
			playAnimation(kEventCorpsePickFloorOpenedBedOriginal);

		getInventory()->getEntry(kItemCorpse)->location = kLocation5;
		break;

	// Bed
	case kLocation2:
		playAnimation(getProgress().jacket == kJacketGreen ? kEventCorpsePickFloorGreen : kEventCorpsePickBedOriginal);
		break;
	}

	if (process)
		getScenes()->processScene();

	// Add corpse to inventory
	if (bedPosition != 4) { // bed position
		getInventory()->addItem(kItemCorpse);
		getInventory()->selectItem(kItemCorpse);
		_engine->getCursor()->setStyle(kCursorCorpse);
	}
}

void Action::dropCorpse(bool process) const {
	switch(getInventory()->getEntry(kItemCorpse)->location) {
	default:
		break;

	case kLocation1:	// Floor
		playAnimation(getProgress().jacket == kJacketGreen ? kEventCorpseDropFloorGreen : kEventCorpseDropFloorOriginal);
		break;

	case kLocation2:	// Bed
		playAnimation(getProgress().jacket == kJacketGreen ? kEventCorpseDropBedGreen : kEventCorpseDropBedOriginal);
		break;

	case kLocation4: // Window
		// Say goodbye to an old friend
		getInventory()->getEntry(kItemCorpse)->location = kLocationNone;
		getProgress().eventCorpseThrown = 1;

		if (getState()->time <= kTime1138500) {
			playAnimation(getProgress().jacket == kJacketGreen ? kEventCorpseDropWindowGreen : kEventCorpseDropWindowOriginal);

			getProgress().field_24 = 1;
		} else {
			playAnimation(kEventCorpseDropBridge);
		}

		getProgress().eventCorpseMovedFromFloor = 1;
		break;
	}

	if (process)
		getScenes()->processScene();
}

bool Action::handleOtherCompartment(ObjectIndex object, byte param2, byte param3) const {

	// Only handle compartments
	if (getEntityData(kEntityNone)->field_493
	|| ((object < kObjectCompartment2 || object > kObjectCompartment8) && (object < kObjectCompartmentA || object > kObjectCompartmentH)))
		return false;

	//////////////////////////////////////////////////////////////////////////
	// Gendarmes
	if (getEntityData(kEntityNone)->car == getEntityData(kEntityGendarmes)->car
	&& !getEntityData(kEntityGendarmes)->field_493
	&& !getEntities()->compare(kEntityNone, kEntityGendarmes)) {
		playCompartmentSoundEvents(kEntityNone, object, param2, param3, true);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// Mertens
	if (getEntityData(kEntityNone)->field_493 == kField493_3
	 && getEntityData(kEntityMertens)->car == kCarGreenSleeping
	 && !getEntityData(kEntityMertens)->field_493
	 && !((EntityData::EntityParametersIIII*)getEntities()->get(kEntityMertens)->getParamData()->getParameters(8, 0))->param1)
		 error("Action::handleOtherCompartment: not implemented!");

	//////////////////////////////////////////////////////////////////////////
	// Coudert
	if (getEntityData(kEntityNone)->field_493 != kField493_4
	 || !getEntityData(kEntityCoudert)->car
	 || getEntityData(kEntityCoudert)->field_493
	 || ((EntityData::EntityParametersIIII*)getEntities()->get(kEntityCoudert)->getParamData()->getParameters(8, 0))->param1)
	 return false;

	if (!getEntities()->compare(kEntityNone, kEntityCoudert))
		error("Action::handleOtherCompartment: not implemented!");

	// Direction = Up
	if (!getEntities()->compare(kEntityNone, kEntityCoudert)
	&& getEntityData(kEntityCoudert)->direction == kDirectionUp
	&& getEntityData(kEntityCoudert)->entityPosition < getEntityData(kEntityNone)->entityPosition) {
		playCompartmentSoundEvents(kEntityCoudert, object, param2, param3, true);

		return true;
	}

	// Direction = down
	if (!getEntities()->compare(kEntityNone, kEntityCoudert)
	&& getEntityData(kEntityCoudert)->direction == kDirectionDown
	&& getEntityData(kEntityCoudert)->entityPosition > getEntityData(kEntityNone)->entityPosition) {
		playCompartmentSoundEvents(kEntityCoudert, object, param2, param3, false);

		return true;
	}

	return false;
}

void Action::playCompartmentSoundEvents(EntityIndex entityIndex, ObjectIndex object, byte param2, byte param3, bool loadSceneFunction) const {
	// FIXME missing tons of code here!
	if (param2) {
		if (getObjects()->get(object).location == 1 || getObjects()->get(object).location == 3 || getEntities()->checkFields2(object)) {
			getSound()->playSoundEvent(kEntityNone, 13);
		} else {
			getSound()->playSoundEvent(kEntityNone, 14);
			getSound()->playSoundEvent(kEntityNone, 15, 3);
		}
	}

	if (entityIndex != kEntityNone) {
		// HmHmmm...
		if (!getSound()->isBuffered(entityIndex))
			getSound()->playSound(entityIndex, (random(2)) ? "JAC1000" : "JAC1000A");
	}

	if (param3)
		getScenes()->loadSceneFromObject(object, !loadSceneFunction);
}

//////////////////////////////////////////////////////////////////////////
// Cursors
//////////////////////////////////////////////////////////////////////////
CursorStyle Action::getCursor(const SceneHotspot &hotspot) const {
	// Simple cursor style
	if (hotspot.cursor != kCursorProcess)
		return (CursorStyle)hotspot.cursor;

	ObjectIndex object = (ObjectIndex)hotspot.param1;

	switch (hotspot.action) {
	default:
		return kCursorNormal;

	case SceneHotspot::kActionInventory:
		if (!getState()->sceneBackup2 && (getEvent(kEventKronosBringFirebird) || getProgress().isEggOpen))
			return kCursorNormal;
		else
			return kCursorBackward;

	case SceneHotspot::kActionKnockOnDoor:
		warning("================================= DOOR %03d =================================", object);
		if (object >= kObjectMax)
			return kCursorNormal;
		else
			return (CursorStyle)getObjects()->get(object).cursor;

	case SceneHotspot::kAction12:
		warning("================================= OBJECT %03d =================================", object);
		if (object >= kObjectMax)
			return kCursorNormal;

		if (getObjects()->get(object).entity)
			return (CursorStyle)getObjects()->get(object).cursor;
		else
			return kCursorNormal;

	case SceneHotspot::kActionPickItem:
		warning("================================= ITEM %03d =================================", object);
		if (object >= kObjectCompartmentA)
			return kCursorNormal;

		if ((!getInventory()->getSelectedItem() || getInventory()->getSelectedEntry()->manualSelect)
		 && (object != kObject21 || getProgress().eventCorpseMovedFromFloor == 1))
			return kCursorHand;
		else
			return kCursorNormal;

	case SceneHotspot::kActionDropItem:
		warning("================================= ITEM %03d =================================", object);
		if (object >= kObjectCompartmentA)
			return kCursorNormal;

		if (getInventory()->getSelectedItem() != (InventoryItem)object)
			return kCursorNormal;

		if (object == kObject20 && hotspot.param2 == 4 && !getProgress().isTrainRunning)
			return kCursorNormal;

		if (object == kObjectHandleInsideBathroom  && hotspot.param2 == 1 && getProgress().field_5C)
			return kCursorNormal;

		return (CursorStyle)getInventory()->getSelectedEntry()->cursor;

	case SceneHotspot::kAction15:
		if (object >= kObjectMax)
			return kCursorNormal;

		// TODO check size of object to make sure we don't have an out of bounds access
		if ((&getProgress().field_0)[object] == hotspot.param2)
			return (CursorStyle)hotspot.param3;

		return kCursorNormal;

	case SceneHotspot::kActionEnterCompartment:
		if ((getInventory()->getSelectedItem() != kItemKey || getObjects()->get(kObjectCompartment1).location)
		&& (getObjects()->get(kObjectCompartment1).location != 1 || !getInventory()->hasItem(kItemKey)
		 ||	(getInventory()->getSelectedItem() != kItemFirebird && getInventory()->getSelectedItem() != kItemBriefcase)))
			goto LABEL_KEY;

		return (CursorStyle)getInventory()->getEntry(kItemKey)->cursor; // TODO is that always the same as kCursorKey ?

	case SceneHotspot::kActionGetOutsideTrain:
		if (getProgress().jacket != kJacketGreen)
			return kCursorNormal;

		if ((getEvent(kEventCathLookOutsideWindowDay) || getEvent(kEventCathLookOutsideWindowDay) || getObjects()->get(kObjectCompartment1).location2 == kLocation1)
			&& getProgress().isTrainRunning
			&& (object != kObjectOutsideAnnaCompartment || (getEntities()->checkFields1(kEntityRebecca, kCarRedSleeping, kPosition_4840) && getObjects()->get(kObjectOutsideBetweenCompartments).location == 2))
			&& getInventory()->getSelectedItem() != kItemBriefcase && getInventory()->getSelectedItem() != kItemFirebird)
			return kCursorForward;

		// FIXME convert to something readable
		return (CursorStyle)((((getObjects()->get(kObjectCompartment1).location2 - 1) < 1) - 1) & 11);

	case SceneHotspot::kActionSlip:
		// FIXME convert to something readable
		return (CursorStyle)(((getProgress().field_C8 < 1) - 1) & 7);

	case SceneHotspot::kActionClimbUpTrain:
		if (getProgress().isTrainRunning
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
		if (hotspot.param2 != 2)
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
			return (CursorStyle)getInventory()->getEntry(kItemMatchBox)->cursor;

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
			&& (getState()->time > kTimeBedTime
			|| (getProgress().eventMetAugust && getProgress().field_CC
			&& (!getProgress().field_24 || getProgress().field_3C))))
			return kCursorSleep;

		return kCursorNormal;

LABEL_KEY:
	// Handle compartment action
	case SceneHotspot::kActionCompartment:
	case SceneHotspot::kActionExitCompartment:
		warning("================================= DOOR %03d =================================", object);
		if (object >= kObjectMax)
			return kCursorNormal;

		if (getInventory()->getSelectedItem() != kItemKey
		|| getObjects()->get(object).entity
		|| getObjects()->get(object).location != 1
		|| !getObjects()->get(object).cursor2
		|| getEntities()->checkFields3()
		|| getEntities()->checkFields2(object))
			return (CursorStyle)getObjects()->get(object).cursor2;
		else
			return (CursorStyle)getInventory()->getEntry(kItemKey)->cursor;
	}
}

//////////////////////////////////////////////////////////////////////////
// Animation
//////////////////////////////////////////////////////////////////////////

// Play an animation and add delta time to global game time
void Action::playAnimation(EventIndex index) const {
	if (index >= _animationListSize)
		error("Action::playAnimation: invalid event index (value=%i, max=%i)", index, _animationListSize);

	getFlags()->flag_3 = true;

	// Show inventory & hourglass
	getInventory()->show();
	getInventory()->showHourGlass();

	// TODO: not sure how it is supposed to work
	if (!getFlags()->mouseRightClick) {

		if (getGlobalTimer()) {
			if (getSound()->isBuffered("TIMER")) {
				getSound()->unknownFunction2("TIMER");
				setGlobalTimer(105);
			}
		}

		// TODO adjust screen coordinates for drawing animation
		// TODO compute arg to animation
		bool processSound = false;
		if (index >= kEventCorpseDropFloorOriginal
		 || index == kEventCathWakingUp
		 || index == kEventConcertCough
		 || index == kEventConcertSit
		 || index == kEventConcertLeaveWithBriefcase)
			processSound = true;

		// FIXME NIS animations need to be passed one more parameter than currently
		Animation animation;
		if (animation.load(getArchive(Common::String(animationList[index].filename) + ".nis")))
			animation.play();

		if (getSound()->isBuffered("TIMER"))
			getSound()->removeFromQueue("TIMER");
	}

	// Adjust game time
	getEvent(index) = 1;
	getState()->timeTicks += animationList[index].time;
	getState()->time += animationList[index].time * getState()->timeDelta;
}

} // End of namespace LastExpress
