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

#include "lastexpress/inventory.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/logic.h"
#include "lastexpress/resource.h"
#include "lastexpress/sound.h"

#define drawItem(x, y, index, brightness) { Icon icon((Cursor::CursorStyle)(index)); icon.setPosition(x, y); icon.setBrightness(brightness); _engine->getGraphicsManager()->draw(&icon, GraphicsManager::kBackgroundInventory); }

namespace LastExpress {

Inventory::Inventory(LastExpressEngine *engine) : _engine(engine),
	_showingHourGlass(false), _blinkingEgg(false), _blinkingTime(0), _blinkingBrightness(100), _blinkingInterval(_defaultBlinkingInterval),
	_opened(false), _selectedItem(kNoItem), _itemScene(NULL) {

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
	_entries[kMatchBox].item_id = Cursor::kCursorMatchBox;
	_entries[kTelegram].item_id = Cursor::kCursorTelegram;
	_entries[kPassengerList].item_id = Cursor::kCursorPassengerList;
	_entries[kArticle].item_id = Cursor::kCursorArticle;
	_entries[kScarf].item_id = Cursor::kCursorScarf;
	_entries[kPaper].item_id = Cursor::kCursorPaper;
	_entries[kParchemin].item_id = Cursor::kCursorParchemin;
	_entries[kMatch].item_id = Cursor::kCursorMatch;
	_entries[kWhistle].item_id = Cursor::kCursorWhistle;
	_entries[kKey].item_id = Cursor::kCursorKey;
	_entries[kBomb].item_id = Cursor::kCursorBomb;
	_entries[kFirebird].item_id = Cursor::kCursorFirebird;
	_entries[kBriefcase].item_id = Cursor::kCursorBriefcase;
	_entries[kCorpse].item_id = Cursor::kCursorCorpse;

	// Selectable
	_entries[kMatchBox].is_selectable = 1;
	_entries[kMatch].is_selectable = 1;
	_entries[kTelegram].is_selectable = 1;
	_entries[kWhistle].is_selectable = 1;
	_entries[kKey].is_selectable = 1;
	_entries[kFirebird].is_selectable = 1;
	_entries[kBriefcase].is_selectable = 1;
	_entries[kCorpse].is_selectable = 1;
	_entries[kPassengerList].is_selectable = 1;

	// Autoselection
	_entries[kItem2].no_autoselect = 0;
	_entries[kItem3].no_autoselect = 0;
	_entries[kItem5].no_autoselect = 0;
	_entries[kItem7].no_autoselect = 0;
	_entries[kItem9].no_autoselect = 0;
	_entries[kItem11].no_autoselect = 0;
	_entries[kBeetle].no_autoselect = 0;
	_entries[kItem17].no_autoselect = 0;
	_entries[kFirebird].no_autoselect = 0;
	_entries[kBriefcase].no_autoselect = 0;
	_entries[kCorpse].no_autoselect = 0;
	_entries[kItem21].no_autoselect = 0;
	_entries[kItem22].no_autoselect = 0;

	// Scene
	_entries[kMatchBox].scene_id = 31;
	_entries[kTelegram].scene_id = 32;
	_entries[kPassengerList].scene_id = 33;
	_entries[kScarf].scene_id = 34;
	_entries[kParchemin].scene_id = 35;
	_entries[kArticle].scene_id = 36;
	_entries[kPaper].scene_id = 37;
	_entries[kFirebird].scene_id = 38;
	_entries[kBriefcase].scene_id = 39;

	// Has item
	_entries[kTelegram].has_item = 1;
	_entries[kArticle].has_item = 1;

	_selectedItem = kNoItem;
}

// FIXME we need to draw cursors with full background opacity so that whatever is in the background is erased
// this saved us clearing some part of the background when switching between states

// TODO if we draw inventory objects on screen, we need to load a new scene.
// Signal that the inventory has taken over the screen and stop processing mouse events after we have been called
bool Inventory::handleMouseEvent(Common::Event ev) {

	// Do not show inventory when on the menu screen
	if (_engine->getLogic()->isShowingMenu() || !_visible)
		return false;

	// Flag to know whether to restore the current cursor or not
	bool insideInventory = false;

	// Egg (menu)
	if (_menuRect.contains(ev.mouse)) {
		insideInventory = true;
		_engine->getCursor()->setStyle(Cursor::kCursorNormal);

		// If clicked, show the menu
		if (ev.type == Common::EVENT_LBUTTONDOWN) {
			playSfx("LIB039");
			_engine->getLogic()->showMenu(true);

			// TODO can we return directly or do we need to make sure the state will be "valid" when we come back from the menu
			return true;
		} else {
			// Highlight if needed
			if (_highlightedItem != _engine->getLogic()->getGameId() + 39) {
				_highlightedItem = (InventoryItem)(_engine->getLogic()->getGameId() + 39);
				drawItem(608, 448, _highlightedItem, 100)

				askForRedraw();
			}
		}
	} else {
		// remove highlight if needed
		if (_highlightedItem == _engine->getLogic()->getGameId() + 39) {
			drawItem(608, 448, _highlightedItem, 50)
			_highlightedItem = kNoItem;
			askForRedraw();
		}
	}

	// Portrait (inventory)
	if (_inventoryRect.contains(ev.mouse)) {
		insideInventory = true;
		_engine->getCursor()->setStyle(Cursor::kCursorNormal);

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
			_highlightedItem = kNoItem;
			askForRedraw();
		}
	}

	// If the inventory is open, check all items rect to see if we need to highlight one / handle click
	if (_opened) {

		// Always show normal cursor when the inventory is opened
		insideInventory = true;
		_engine->getCursor()->setStyle(Cursor::kCursorNormal);

		bool selected = false;

		// Iterate over items
		int y = 44;
		for (int i = 1; i < 32; i++) {
			if (!hasItem((InventoryItem)i))
				continue;
			
			if (Common::Rect(0, y, 32, 32 + y).contains(ev.mouse)) {

				// If released with an item highlighted, show this item
				if (ev.type == Common::EVENT_LBUTTONUP) {
					if (_entries[i].is_selectable) {
						selected = true;
						_selectedItem = (InventoryItem)i;
						drawItem(44, 0, getItem(_selectedItem)->item_id, 100)
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
					_highlightedItem = kNoItem;
					askForRedraw();
				}
			}

			y += 40;			
		}

		// Right button is released: we need to close the inventory
		if (ev.type == Common::EVENT_LBUTTONUP) {

			// Not on a selectable item: de-select the current item
			if (!selected) {
				_selectedItem = kNoItem;
				_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundInventory, Common::Rect(44, 0, 44 + 32, 32));
			}
			close();
			askForRedraw();
		}
	}

	// Selected item
	if (_selectedItem != kNoItem && _selectedRect.contains(ev.mouse)) {
		insideInventory = true;

		// Show magnifier icon
		_engine->getCursor()->setStyle(Cursor::kCursorMagnifier);

		if (ev.type == Common::EVENT_LBUTTONDOWN) {
			examine((InventoryItem)_selectedItem);
		}
	}

	// If the egg is blinking, refresh
	if (_blinkingEgg)
		drawEgg();

	// Restore cursor
	if (!insideInventory)
		_engine->getCursor()->setStyle(_engine->getLogic()->getCursorStyle());

	return insideInventory;
}

void Inventory::show(bool visible) {
	_visible = visible;

	clearBg(GraphicsManager::kBackgroundInventory);
	askForRedraw();

	if (!visible)
		return;

	// Show portrait (first draw, cannot be highlighted)
	drawItem(0, 0, getProgress().portrait, 50)

	// Show selected item
	if (_selectedItem != kNoItem)
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
		drawItem(608, 448, _engine->getLogic()->getGameId() + 39, _blinkingBrightness)
	else {
		// Reset values
		_blinkingBrightness = 100;
		_blinkingInterval = _defaultBlinkingInterval;
		drawItem(608, 448, _engine->getLogic()->getGameId() + 39, 50) // normal egg state
	}

	askForRedraw();
}

void Inventory::showHourGlass(bool enabled) {
	_showingHourGlass = enabled;

	// Reset state
	_blinkingEgg = false;

	// Show/Hide hour glass and ask for redraw
	if (_showingHourGlass)
		drawItem(608, 448, Cursor::kCursorHourGlass, 100)
	else
		drawItem(608, 448, _engine->getLogic()->getGameId() + 39, 100) // normal egg state

	askForRedraw();
}

//////////////////////////////////////////////////////////////////////////
// Items
//////////////////////////////////////////////////////////////////////////
Inventory::InventoryEntry *Inventory::getItem(InventoryItem item) {
	assert(item < 32);

	return &_entries[item];
}

void Inventory::addItem(InventoryItem item) {
	if (hasItem(item))
		return;

	getItem(item)->has_item = 1;
	getItem(item)->location = 0;

	// Autoselect item if necessary
	if (!getItem(item)->no_autoselect) {
		_selectedItem = (InventoryItem)getItem(item)->item_id;
		drawItem(44, 0, _selectedItem, 100)
		askForRedraw();
	}
}

void Inventory::removeItem(InventoryItem item) {
	if (!hasItem(item))
		return;

	getItem(item)->has_item = 0;
	getItem(item)->location = 0;

	if (getItem(item)->item_id == _selectedItem) {
		_selectedItem = kNoItem;
		_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundInventory, Common::Rect(44, 0, 44 + 32, 32));
		askForRedraw();
	}
}

bool Inventory::hasItem(InventoryItem item) {
	if (getItem(item)->has_item)
			return true;

	return false;
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
// Examine an inventory item
void Inventory::examine(InventoryItem item) {
	uint32 sceneId = getItem(item)->scene_id;

	if (sceneId != 0)
		_engine->getLogic()->setScene(sceneId);
}

void Inventory::drawEgg() {
	// Blinking egg: we need to blink the egg for delta time, with the blinking getting faster until it's always lit.
	if (_blinkingEgg) {
		drawItem(608, 448, _engine->getLogic()->getGameId() + 39, _blinkingBrightness)

		// TODO if delta time > _blinkingInterval, update egg & ask for redraw then adjust blinking time and remaining time

		// Reset values and stop blinking
		if (_blinkingTime == 0)
			blinkEgg(false);

		askForRedraw();
	} else {
		drawItem(608, 448, _engine->getLogic()->getGameId() + 39, 50)
	}
}

// Close inventory: clear items and reset icon
void Inventory::open() {
	_opened = true;

	// Show selected state
	drawItem(0, 0, getProgress().portrait + 1, 100)

	uint y = 44;

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

	_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundInventory, Common::Rect(0, 44, 32, 44 + 44 * count));

	askForRedraw();
}

Common::Rect Inventory::getItemRect(int index) {
	return Common::Rect(0, (32 + 12) * (index + 1), 32, (32 + 12) * (index + 2)); // space between items = 12px
}

} // End of namespace LastExpress
