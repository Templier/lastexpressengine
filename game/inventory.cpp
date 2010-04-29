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

#include "lastexpress/game/inventory.h"

#include "lastexpress/data/cursor.h"
#include "lastexpress/data/scene.h"
#include "lastexpress/data/snd.h"

#include "lastexpress/game/logic.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"


#define drawItem(x, y, index, brightness) { Icon icon((CursorStyle)(index)); icon.setPosition(x, y); icon.setBrightness(brightness); _engine->getGraphicsManager()->draw(&icon, GraphicsManager::kBackgroundInventory); }

namespace LastExpress {

Inventory::Inventory(LastExpressEngine *engine) : _engine(engine), _selectedItem(kItemNone), _highlightedItem(kItemNone), _opened(false), _visible(false),
	_showingHourGlass(false), _blinkingEgg(false), _blinkingTime(0), _blinkingInterval(_defaultBlinkingInterval), _blinkingBrightness(100), _itemScene(NULL) {

	_inventoryRect = Common::Rect(0, 0, 32, 32);
	_menuRect = Common::Rect(608, 448, 640, 480);
	_selectedRect = Common::Rect(44, 0, 76, 32);
}

Inventory::~Inventory() {
	delete _itemScene;
}

//////////////////////////////////////////////////////////////////////////
// Inventory handling
//////////////////////////////////////////////////////////////////////////

// Init inventory contents
void Inventory::init() {
	// ID
	_entries[kItemMatchBox].item_id = kCursorMatchBox;
	_entries[kItemTelegram].item_id = kCursorTelegram;
	_entries[kItemPassengerList].item_id = kCursorPassengerList;
	_entries[kItemArticle].item_id = kCursorArticle;
	_entries[kItemScarf].item_id = kCursorScarf;
	_entries[kItemPaper].item_id = kCursorPaper;
	_entries[kItemParchemin].item_id = kCursorParchemin;
	_entries[kItemMatch].item_id = kCursorMatch;
	_entries[kItemWhistle].item_id = kCursorWhistle;
	_entries[kItemKey].item_id = kCursorKey;
	_entries[kItemBomb].item_id = kCursorBomb;
	_entries[kItemFirebird].item_id = kCursorFirebird;
	_entries[kItemBriefcase].item_id = kCursorBriefcase;
	_entries[kItemCorpse].item_id = kCursorCorpse;

	// Selectable
	_entries[kItemMatchBox].is_selectable = 1;
	_entries[kItemMatch].is_selectable = 1;
	_entries[kItemTelegram].is_selectable = 1;
	_entries[kItemWhistle].is_selectable = 1;
	_entries[kItemKey].is_selectable = 1;
	_entries[kItemFirebird].is_selectable = 1;
	_entries[kItemBriefcase].is_selectable = 1;
	_entries[kItemCorpse].is_selectable = 1;
	_entries[kItemPassengerList].is_selectable = 1;

	// Autoselection
	_entries[kItem2].no_autoselect = 0;
	_entries[kItem3].no_autoselect = 0;
	_entries[kItem5].no_autoselect = 0;
	_entries[kItem7].no_autoselect = 0;
	_entries[kItem9].no_autoselect = 0;
	_entries[kItem11].no_autoselect = 0;
	_entries[kItemBeetle].no_autoselect = 0;
	_entries[kItem17].no_autoselect = 0;
	_entries[kItemFirebird].no_autoselect = 0;
	_entries[kItemBriefcase].no_autoselect = 0;
	_entries[kItemCorpse].no_autoselect = 0;
	_entries[kItemGreenJacket].no_autoselect = 0;
	_entries[kItem22].no_autoselect = 0;

	// Scene
	_entries[kItemMatchBox].scene_id = 31;
	_entries[kItemTelegram].scene_id = 32;
	_entries[kItemPassengerList].scene_id = 33;
	_entries[kItemScarf].scene_id = 34;
	_entries[kItemParchemin].scene_id = 35;
	_entries[kItemArticle].scene_id = 36;
	_entries[kItemPaper].scene_id = 37;
	_entries[kItemFirebird].scene_id = 38;
	_entries[kItemBriefcase].scene_id = 39;

	// Has item
	_entries[kItemTelegram].has_item = 1;
	_entries[kItemArticle].has_item = 1;

	_selectedItem = kItemNone;
}

// FIXME we need to draw cursors with full background opacity so that whatever is in the background is erased
// this saved us clearing some part of the background when switching between states

// TODO if we draw inventory objects on screen, we need to load a new scene.
// Signal that the inventory has taken over the screen and stop processing mouse events after we have been called
bool Inventory::handleMouseEvent(Common::Event ev) {

	// Do not show inventory when on the menu screen
	if (getLogic()->isShowingMenu() || !_visible)
		return false;

	// Flag to know whether to restore the current cursor or not
	bool insideInventory = false;

	// Egg (menu)
	if (_menuRect.contains(ev.mouse)) {
		insideInventory = true;
		_engine->getCursor()->setStyle(kCursorNormal);

		// If clicked, show the menu
		if (ev.type == Common::EVENT_LBUTTONDOWN) {
			playSfxStream("LIB039");
			getLogic()->showMenu(true);

			// TODO can we return directly or do we need to make sure the state will be "valid" when we come back from the menu
			return true;
		} else {
			// Highlight if needed
			if (_highlightedItem != getLogic()->getGameId() + 39) {
				_highlightedItem = (InventoryItem)(getLogic()->getGameId() + 39);
				drawItem(608, 448, _highlightedItem, 100)

				askForRedraw();
			}
		}
	} else {
		// remove highlight if needed
		if (_highlightedItem == getLogic()->getGameId() + 39) {
			drawItem(608, 448, _highlightedItem, 50)
			_highlightedItem = kItemNone;
			askForRedraw();
		}
	}

	// Portrait (inventory)
	if (_inventoryRect.contains(ev.mouse)) {
		insideInventory = true;
		_engine->getCursor()->setStyle(kCursorNormal);

		// If clicked, show pressed state and display inventory
		if (ev.type == Common::EVENT_LBUTTONDOWN) {
			open();
		} else {
			// Highlight if needed
			if (_highlightedItem != (InventoryItem)getProgress().portrait && !_opened) {
				_highlightedItem = (InventoryItem)getProgress().portrait;
				drawItem(0, 0, getProgress().portrait, 100)

				askForRedraw();
			}
		}
	} else {
		// remove highlight if needed
		if (_highlightedItem == (InventoryItem)getProgress().portrait && !_opened) {
			drawItem(0, 0, getProgress().portrait, 50)
			_highlightedItem = kItemNone;
			askForRedraw();
		}
	}

	// If the inventory is open, check all items rect to see if we need to highlight one / handle click
	if (_opened) {

		// Always show normal cursor when the inventory is opened
		insideInventory = true;
		_engine->getCursor()->setStyle(kCursorNormal);

		bool selected = false;

		// Iterate over items
		int16 y = 44;
		for (int i = 1; i < 32; i++) {
			if (!hasItem((InventoryItem)i))
				continue;

			if (Common::Rect(0, y, 32, 32 + y).contains(ev.mouse)) {

				// If released with an item highlighted, show this item
				if (ev.type == Common::EVENT_LBUTTONUP) {
					if (_entries[i].is_selectable) {
						selected = true;
						_selectedItem = (InventoryItem)i;
						drawItem(44, 0, getEntry(_selectedItem)->item_id, 100)
					}

					examine((InventoryItem)i);
					break;
				} else {
					if (_highlightedItem != i) {
						drawItem(0, y, _entries[i].item_id, 100)
						_highlightedItem = (InventoryItem)i;
						askForRedraw();
					}
				}
			} else {
				// Remove highlight if necessary
				if (_highlightedItem == i) {
					drawItem(0, y, _entries[i].item_id, 50)
					_highlightedItem = kItemNone;
					askForRedraw();
				}
			}

			y += 40;
		}

		// Right button is released: we need to close the inventory
		if (ev.type == Common::EVENT_LBUTTONUP) {

			// Not on a selectable item: unselect the current item
			if (!selected)
				unselectItem();

			close();
		}
	}

	// Selected item
	if (_selectedItem != kItemNone && _selectedRect.contains(ev.mouse)) {
		insideInventory = true;

		// Show magnifier icon
		_engine->getCursor()->setStyle(kCursorMagnifier);

		if (ev.type == Common::EVENT_LBUTTONDOWN) {
			examine((InventoryItem)_selectedItem);
		}
	}

	// If the egg is blinking, refresh
	if (_blinkingEgg)
		drawEgg();

	// Restore cursor
	if (!insideInventory)
		_engine->getCursor()->setStyle(getLogic()->getCursorStyle());

	return insideInventory;
}

//////////////////////////////////////////////////////////////////////////
// UI
//////////////////////////////////////////////////////////////////////////
void Inventory::show(bool visible) {
	_visible = visible;

	clearBg(GraphicsManager::kBackgroundInventory);
	askForRedraw();

	if (!visible)
		return;

	// Show portrait (first draw, cannot be highlighted)
	drawItem(0, 0, getProgress().portrait, 50)

	// Show selected item
	if (_selectedItem != kItemNone)
		drawItem(44, 0, _selectedItem, 100)

	drawEgg();
}

void Inventory::setPortrait(InventoryItem item) {
	getProgress().portrait = item;
	drawItem(0, 0, getProgress().portrait, 50);
}

void Inventory::blinkEgg(bool enabled) {
	_blinkingEgg = enabled;

	// Reset state
	_showingHourGlass = false;

	// Show egg at full brightness for first step if blinking
	if (_blinkingEgg)
		drawItem(608, 448, getLogic()->getGameId() + 39, _blinkingBrightness)
	else {
		// Reset values
		_blinkingBrightness = 100;
		_blinkingInterval = _defaultBlinkingInterval;
		drawItem(608, 448, getLogic()->getGameId() + 39, 50) // normal egg state
	}

	askForRedraw();
}

void Inventory::showHourGlass(bool enabled) {
	_showingHourGlass = enabled;

	// Reset state
	_blinkingEgg = false;

	// Show/Hide hour glass and ask for redraw
	if (_showingHourGlass)
		drawItem(608, 448, kCursorHourGlass, 100)
	else
		drawItem(608, 448, getLogic()->getGameId() + 39, 100) // normal egg state

	askForRedraw();
}

// Show an item scene
void Inventory::showItem(InventoryItem item) {
	uint32 scene = getEntry(item)->scene_id;
	if (!scene )
		return;

	if (!getState()->sceneUseBackup) {
		getState()->sceneBackup = getState()->scene;
		getState()->sceneUseBackup = 1;
	}

	getLogic()->loadScene(scene);
}

//////////////////////////////////////////////////////////////////////////
// Items
//////////////////////////////////////////////////////////////////////////
Inventory::InventoryEntry *Inventory::getEntry(InventoryItem item) {
	if (item >= kPortraitOriginal)
		error("Inventory::getEntry: Invalid inventory item!");

	return &_entries[item];
}

void Inventory::addItem(InventoryItem item) {
	if (hasItem(item))
		return;

	getEntry(item)->has_item = 1;
	getEntry(item)->location = kLocationNone;

	// Autoselect item if necessary
	if (!getEntry(item)->no_autoselect) {
		_selectedItem = (InventoryItem)getEntry(item)->item_id;
		drawItem(44, 0, _selectedItem, 100)
		askForRedraw();
	}
}

void Inventory::removeItem(InventoryItem item, ObjectLocation newLocation) {
	if (!hasItem(item))
		return;

	getEntry(item)->has_item = 0;
	getEntry(item)->location = newLocation;

	if (getEntry(item)->item_id == _selectedItem) {
		_selectedItem = kItemNone;
		_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundInventory, Common::Rect(44, 0, 44 + 32, 32));
		askForRedraw();
	}
}

bool Inventory::hasItem(InventoryItem item) {
	if (getEntry(item)->has_item)
			return true;

	return false;
}

void Inventory::selectItem(InventoryItem item) {
	_selectedItem = item;

	drawItem(44, 0, getEntry(_selectedItem)->item_id, 100)
	askForRedraw();
}

void Inventory::unselectItem() {
	_selectedItem = kItemNone;

	_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundInventory, Common::Rect(44, 0, 44 + 32, 32));
	askForRedraw();
}

void Inventory::setLocationAndProcess(InventoryItem item, ObjectLocation location) {
	if (item >= kPortraitOriginal)
		return;

	if (getEntry(item)->location == location)
		return;

	getEntry(item)->location = location;

	if (isItemSceneParameter(item)) {
		if (getFlags()->flag_0)
			getLogic()->processScene();
	}
}

//////////////////////////////////////////////////////////////////////////
// Serializable
//////////////////////////////////////////////////////////////////////////
void Inventory::saveLoadWithSerializer(Common::Serializer &s) {
	// TODO implement
}

//////////////////////////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////////////////////////
InventoryItem Inventory::getFirstExaminableItem() {

	int index = 0;
	InventoryEntry entry = _entries[index];
	while (!entry.has_item || !entry.no_autoselect || !entry.scene_id) {
		index++;
		entry = _entries[index];

		if (index >= kPortraitOriginal)
			return kItemNone;
	}

	return (InventoryItem)index;
}

bool Inventory::isItemSceneParameter(InventoryItem item) {
	loadSceneObject(scene, getState()->scene);

	switch(scene.getHeader()->type) {
	default:
		return false;

	case Scene::kTypeItem:
		if (scene.getHeader()->param1 == item)
			return true;
		break;

	case Scene::kTypeItem2:
		if (scene.getHeader()->param1 == item || scene.getHeader()->param2 == item)
			return true;
		break;

	case Scene::kTypeEntityItem:
		if (scene.getHeader()->param2 == item)
			return true;
		break;

	case Scene::kTypeItem3:
		if (scene.getHeader()->param1 == item || scene.getHeader()->param2 == item || scene.getHeader()->param3 == item)
			return true;
		break;

	case Scene::kType8:
		if (scene.getHeader()->param2 == item)
			return true;
		break;
	}

	return false;
}

// Examine an inventory item
void Inventory::examine(InventoryItem item) {
	uint32 index = getEntry(item)->scene_id;
	if (!index)
		return;

	/*if (!getState()->sceneUseBackup ||
		(getState()->sceneBackup2 && getFirstExaminableItem() == _selectedItem))
		flag = 1;*/

	if (!getState()->sceneUseBackup) {
		getState()->sceneBackup = getState()->scene;
		getState()->sceneUseBackup = 1;

		getLogic()->loadScene(index);
	} else {

		if (!getState()->sceneBackup2)
			return;

		if (getFirstExaminableItem() == _selectedItem) {
			index = getState()->sceneBackup2;
			getState()->sceneBackup2 = 0;
			getLogic()->loadScene(index);
		}
	}
}

void Inventory::drawEgg() {
	// Blinking egg: we need to blink the egg for delta time, with the blinking getting faster until it's always lit.
	if (_blinkingEgg) {
		drawItem(608, 448, getLogic()->getGameId() + 39, _blinkingBrightness)

		// TODO if delta time > _blinkingInterval, update egg & ask for redraw then adjust blinking time and remaining time
		warning("Inventory::drawEgg - blinking not implemented!");

		// Reset values and stop blinking
		if (_blinkingTime == 0)
			blinkEgg(false);

		askForRedraw();
	} else {
		// TODO do not draw if not needed (ie no blink and already drawn)
		drawItem(608, 448, getLogic()->getGameId() + 39, 50)
	}
}

// Close inventory: clear items and reset icon
void Inventory::open() {
	_opened = true;

	// Show selected state
	drawItem(0, 0, getProgress().portrait + 1, 100)

	int16 y = 44;

	// Iterate over items
	for (uint i = 1; i < 32; i++) {
		if (_entries[i].has_item) {
			drawItem(0, y, _entries[i].item_id, 50)
			y += 40;
		}
	}

	askForRedraw();
}

// Close inventory: clear items and reset icon
void Inventory::close() {
	_opened = false;

	// Fallback to unselected state
	drawItem(0, 0, getProgress().portrait, 100)

	// Erase rectangle for all inventory items
	int count = 0;
	for (uint i = 1; i < 32; i++) {
		if (_entries[i].has_item) {
			count++;
		}
	}

	_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundInventory, Common::Rect(0, 44, 32, 44 + 44 * (int16)count));

	askForRedraw();
}

Common::Rect Inventory::getItemRect(int16 index) {
	return Common::Rect(0, (32 + 12) * (index + 1), 32, (32 + 12) * (index + 2)); // space between items = 12px
}

} // End of namespace LastExpress
