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

#include "lastexpress/logic.h"

#include "lastexpress/animation.h"
#include "lastexpress/inventory.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/menu.h"
#include "lastexpress/resource.h"
#include "lastexpress/scene.h"

#include "common/EventRecorder.h"

namespace LastExpress {

enum Animations {
	//kAnimationDynamiteBoom = 114,	// :D
	//kAnimationCorridorBlood = 123,
	//kAnimationFoundCorpse = 125,
	//kAnimationFoundCorpseBed = 126,

	kAnimationGreenJacket = 256,
	kAnimationScarf = 257,
	kAnimationScarfOriginal = 258
};

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
	{"1006",	750},
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
	{"1017",	870},
	{"1017A",	0},
	{"1019",	120},
	{"1019D",	120},
	{"1020",	120},	// 20
	{"1022",	525},
	{"1022A",	180},
	{"1022AD",	210},
	{"1022B",	210},
	{"1022C",	210},
	{"1023",	135},
	{"1025",	945},
	{"1028",	300},
	{"1030",	390},
	{"1031",	375},	// 30
	{"1032",	1050},
	{"1033",	945},
	{"1034",	495},
	{"1035",	1230},
	{"1037",	1425},
	{"1038",	195},
	{"1038A",	405},
	{"1039",	600},
	{"1040",	945},
	{"1041",	510},	// 40
	{"1042",	540},
	{"1043",	855},
	{"1044",	645},
	{"1046",	0},
	{"1047",	0},
	{"1047A",	0},
	{"1059",	1005},
	{"1060",	255},
	{"1063",	0},
	{"1101",	255},	// 50
	{"1102",	1320},
	{"1103",	210},
	{"1104",	120},
	{"1105",	1350},
	{"1106",	315},
	{"1106A",	315},
	{"1106D",	315},
	{"1107",	1},
	{"1107A",	660},
	{"1108",	300},	// 60
	{"1109",	1305},
	{"1110",	300},
	{"1112",	0},
	{"1115",	0},
	{"1115A",	0},
	{"1115B",	0},
	{"1115C",	0},
	{"1115D",	0},
	{"1115E",	0},
	{"1115F",	0},		// 70
	{"1115G",	0},
	{"1115H",	0},
	{"1116",	0},
	{"1117",	0},
	{"1118",	105},
	{"1202",	510},
	{"1202A",	510},
	{"1203",	720},
	{"1204",	120},
	{"1205",	465},	// 80
	{"1206",	690},
	{"1206A",	450},
	{"1208",	465},
	{"1210",	1020},
	{"1211",	600},
	{"1212",	435},
	{"1213",	525},
	{"1213A",	150},
	{"1215",	390},
	{"1216",	0},		// 90
	{"1219",	240},
	{"1222",	1095},
	{"1223",	0},
	{"1224",	720},
	{"1225",	1005},
	{"1227",	840},
	{"1227A",	840},
	{"1303",	450},
	{"1303N",	450},
	{"1304",	450},	// 100
	{"1304N",	450},
	{"1305",	630},
	{"1309",	0},
	{"1311",	1710},
	{"1312",	240},
	{"1312D",	240},
	{"1313",	930},
	{"1315",	1035},
	{"1315A",	1035},
	{"1401",	540},	// 110
	{"1402",	150},
	{"1402B",	150},
	{"1403",	90},
	{"1404",	885},
	{"1404A",	0},
	{"1405",	135},
	{"1406",	1665},
	{"1501",	285},
	{"1501A",	285},
	{"1502",	165},	// 120
	{"1502A",	165},
	{"1502D",	165},
	{"1503",	0},
	{"1504",	0},
	{"1505",	0},
	{"1505A",	0},
	{"1506",	300},
	{"1506A",	180},
	{"1508",	0},
	{"1509",	450},	// 130
	{"1509S",	450},
	{"1509A",	450},
	{"1509AS",	450},
	{"1509N",	450},
	{"1509SN",	450},
	{"1509AN",	450},
	{"1509BN",	450},
	{"1511",	150},
	{"1511A",	150},
	{"1511B",	90},	// 140
	{"1511BA",	90},
	{"1511C",	135},
	{"1511D",	105},
	{"1930",	0},
	{"1511E",	150},
	{"1512",	165},
	{"1513",	180},
	{"1517",	0},
	{"1517A",	165},
	{"1518",	165},	// 150
	{"1518A",	165},
	{"1518B",	165},
	{"1591",	450},
	{"1592",	450},
	{"1593",	450},
	{"1594",	450},
	{"1595",	450},
	{"1596",	450},
	{"1601",	0},
	{"1603",	0},		// 160
	{"1606B",	315},
	{"1607A",	0},
	{"1610",	0},
	{"1611",	0},
	{"1612",	0},
	{"1615",	0},
	{"1619",	0},
	{"1620",	120},
	{"1621",	105},
	{"1622",	105},	// 170
	{"1629",	450},
	{"1630",	450},
	{"1631",	525},
	{"1632",	0},
	{"1633",	615},
	{"1634",	180},
	{"1702",	180},
	{"1702DD",	180},
	{"1702NU",	180},
	{"1702ND",	180},	// 180
	{"1704",	300},
	{"1704D",	300},
	{"1705",	195},
	{"1705D",	195},
	{"1706",	195},
	{"1706DD",	195},
	{"1706ND",	195},
	{"1706NU",	195},
	{"1901",	135},
	{"1902",	1410},	// 190
	{"1903",	0},
	{"1904",	1920},
	{"1908",	600},
	{"1908A",	195},
	{"1908B",	105},
	{"1908C",	165},
	{"1908CD",	0},
	{"1909A",	150},
	{"1909B",	150},
	{"1909C",	150},	// 200
	{"1910A",	180},
	{"1910B",	180},
	{"1910C",	180},
	{"1911A",	90},
	{"1911B",	90},
	{"1911C",	90},
	{"1912",	0},
	{"1913",	0},
	{"1917",	0},
	{"1918",	390},	// 210
	{"1919",	360},
	{"1919A",	105},
	{"1920",	75},
	{"1922",	75},
	{"1923",	150},
	{"8001",	120},
	{"8001A",	120},
	{"8002",	120},
	{"8002A",	120},
	{"8002B",	120},	// 220
	{"8003",	105},
	{"8003A",	105},
	{"8004",	105},
	{"8004A",	105},
	{"8005",	270},
	{"8005B",	270},
	{"8010",	270},
	{"8013",	120},
	{"8013A",	120},
	{"8014",	165},	// 230
	{"8014A",	165},
	{"8014R",	165},
	{"8014AR",	165},
	{"8015",	150},
	{"8015A",	150},
	{"8015R",	150},
	{"8015AR",	150},
	{"8017",	120},
	{"8017A",	120},
	{"8017R",	120},	// 240
	{"8017AR",	120},
	{"8017N",	90},
	{"8023",	135},
	{"8023A",	135},
	{"8023M",	135},
	{"8024",	150},
	{"8024A",	180},
	{"8024M",	180},
	{"8025",	150},
	{"8025A",	150},	// 250
	{"8025M",	150},
	{"8027",	75},
	{"8028",	75},
	{"8029",	120},
	{"8029A",	120},
	{"8031",	375},
	{"8032",	0},
	{"8032A",	0},
	{"8033",	105},
	{"8035",	195},	// 260
	{"8035A",	120},
	{"8035B",	180},
	{"8035C",	135},
	{"8036",	105},
	{"8037",	195},
	{"8037A",	195},
	{"8040",	240},
	{"8040A",	240},
	{"8041",	195},
	{"8041A",	195},	// 270
	{"8042",	600},
	{"8042A",	600}
};

Logic::Logic(LastExpressEngine *engine) : _engine(engine) {
	_menu = new Menu(engine);
	_inventory = new Inventory(engine);

	// Get those from savegame
	_gameState = new SaveLoad::GameState();

	// Init inventory
	_inventory->init();

	g_eventRec.registerRandomSource(_random, "lastexpress");

	// HACK set specific cursor style for inventory testing
	_engine->getCursor()->show(true);
	_runState.cursorStyle = Cursor::kCursorTurnLeft;
	_engine->getCursor()->setStyle(_runState.cursorStyle);

	// HACK add more items for testing
	_inventory->addItem(Inventory::kMatchBox);
	_inventory->addItem(Inventory::kPassengerList);
	_inventory->addItem(Inventory::kScarf);
	_inventory->addItem(Inventory::kWhistle);
	_inventory->addItem(Inventory::kArticle);
	_inventory->addItem(Inventory::kBomb);
	_inventory->addItem(Inventory::kKey);
}

Logic::~Logic() {
	delete _gameState;
	delete _menu;
	delete _inventory;
}

//////////////////////////////////////////////////////////////////////////
// Menu handling
//////////////////////////////////////////////////////////////////////////

// Show main menu
void Logic::showMenu(bool visible) {

	if (!visible) {
		_inventory->show(true);
		_runState.showingMenu = false;
		return;
	}

	// Hide inventory
	_inventory->show(false);

	// TODO: load scene and set current scene
	_runState.showingMenu = true;
	_gameState->currentScene = _menu->getSceneIndex();
	_menu->showMenu();

	// TODO reset showingMenu to false when starting/returning to a game and show inventory

	// TODO: move to shared method
	// Init the first savegame if needed
	if (!SaveLoad::isSavegamePresent(kGameBlue))
		SaveLoad::initSavegame(kGameBlue);
}

bool Logic::handleMouseEvent(Common::Event ev) {
	if (_gameState->currentScene == 0) {
		// FIXME: allow inventory to show
		_gameState->currentScene = 1;
		_inventory->show(true);		

		return true;
	}

	// Special case for the main menu scene
	if (isShowingMenu()) {
		return _menu->handleStartMenuEvent(ev);
	}

	// FIXME: check hitbox & event from scene data
	_inventory->handleMouseEvent(ev);

	return true;
}

// Switch to the next savegame
void Logic::switchGame() {
	// Switch back to blue game is the current game is not started
	if (!_runState.gameStarted) {
		_runState.gameId = kGameBlue;
	} else {
		_runState.gameId = (GameId)((_runState.gameId + 1) % 6);
	}

	// Init savegame if needed
	if (!SaveLoad::isSavegamePresent(_runState.gameId))
		SaveLoad::initSavegame(_runState.gameId);

	// Reset run state
	_runState.gameStarted = false;

	// TODO load data from savegame, adjust volume & luminosity, etc...
	//////////////////////////////////////////////////////////////////////////
	// HACK for debug
	if (_runState.gameId == kGameBlue) {
		_gameState->time = 2383200;
		_runState.gameStarted = true;
	}
	//////////////////////////////////////////////////////////////////////////

	// Redraw all menu elements
	showMenu(true);
}

// Play an animation and add delta time to global game time
void Logic::playAnimation(int index) {
	assert(index > 0 || index < sizeof(animationList));

	//bool unknown = false;
	//if (index >= 212)
	//	unknown = true;

	// Show inventory & hourglass
	_inventory->show(true);
	_inventory->showHourGlass(true);

	Animation animation;
	if (animation.load(_engine->getResMan()->getFileStream(Common::String(animationList[index].filename) + ".nis")))
		animation.play();

	_inventory->showHourGlass(false);

	// TODO add delta time to game time

}


//////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////
void Logic::action_pickGreenJacket() {
	_gameState->progress.jacketType = SaveLoad::kGreenJacket;
	_inventory->addItem(Inventory::kMatchBox);

	// 1 unknown functions calls
	playAnimation(kAnimationGreenJacket);

	_inventory->setPortrait(Inventory::kPortraitGreen);
}

void Logic::action_pickScarf() {
	if (_gameState->progress.jacketType == SaveLoad::kOriginalJacket)
		playAnimation(kAnimationScarf);
	else
		playAnimation(kAnimationScarfOriginal);

	// TODO Add scarf to inventory + other stuff
}

//////////////////////////////////////////////////////////////////////////
// Soundbites
//////////////////////////////////////////////////////////////////////////
Common::String Logic::sound_excuseMe() {
	switch(_random.getRandomNumber(3)) {
	case 0:
		return "CAT1126B";
	case 1:
		return "CAT1126C";
	case 2:
		return "CAT1126D";
	}

	return "CAT1126B";
}

Common::String Logic::sound_justChecking() {
	switch(_random.getRandomNumber(4)) {
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

Common::String Logic::sound_wrongDoor() {
	switch(_random.getRandomNumber(5)) {
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

Common::String Logic::sound_justAMinute() {
	switch(_random.getRandomNumber(3)) {
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
