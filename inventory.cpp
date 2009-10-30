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
#define getProgress() _engine->getLogic()->getGameState()->progress

namespace LastExpress {

Inventory::Inventory(LastExpressEngine *engine) : _engine(engine),
	_showingHourGlass(false), _blinkingEgg(false), _blinkingTime(0), _blinkingBrightness(100), _blinkingInterval(_defaultBlinkingInterval),
	_opened(false) {

	_inventoryRect = Common::Rect(0, 0, 32, 32);
	_menuRect = Common::Rect(608, 448, 640, 480);
	_selectedRect = Common::Rect(44, 0, 76, 32);
}

Inventory::~Inventory() {}

//////////////////////////////////////////////////////////////////////////
// Inventory handling
//////////////////////////////////////////////////////////////////////////

// Init inventory contents
void Inventory::init() {
	// item_id
	_entries[kIndexMatchBox].item_id = kMatchBox;
	_entries[kIndexTelegram].item_id = kTelegram;
	_entries[kIndexPassengerList].item_id = kPassengerList;
	_entries[kIndexArticle].item_id = kArticle;
	_entries[kIndexScarf].item_id = kScarf;
	_entries[kIndexPaper].item_id = kPaper;
	_entries[kIndexParchemin].item_id = kParchemin;
	_entries[kIndexMatch].item_id = kMatch;
	_entries[kIndexWhistle].item_id = kWhistle;
	_entries[kIndexKey].item_id = kKey;
	_entries[kIndexBomb].item_id = kBomb;
	_entries[kIndexFirebird].item_id = kFirebird;
	_entries[kIndexBriefcase].item_id = kBriefcase;
	_entries[kIndexCorpse].item_id = kCorpse;

	// is_selectable
	_entries[kIndexMatchBox].is_selectable = 1;
	_entries[kIndexMatch].is_selectable = 1;
	_entries[kIndexTelegram].is_selectable = 1;
	_entries[kIndexWhistle].is_selectable = 1;
	_entries[kIndexKey].is_selectable = 1;
	_entries[kIndexFirebird].is_selectable = 1;
	_entries[kIndexBriefcase].is_selectable = 1;
	_entries[kIndexCorpse].is_selectable = 1;
	_entries[kIndexPassengerList].is_selectable = 1;

	// ??
	_entries[2].no_autoselect = 0;
	_entries[3].no_autoselect = 0;
	_entries[5].no_autoselect = 0;
	_entries[7].no_autoselect = 0;
	_entries[9].no_autoselect = 0;
	_entries[11].no_autoselect = 0;
	_entries[14].no_autoselect = 0;
	_entries[17].no_autoselect = 0;
	_entries[kIndexFirebird].no_autoselect = 0;
	_entries[kIndexBriefcase].no_autoselect = 0;
	_entries[kIndexCorpse].no_autoselect = 0;
	_entries[21].no_autoselect = 0;
	_entries[22].no_autoselect = 0;

	// scene_id
	_entries[kIndexMatchBox].scene_id = 31;
	_entries[kIndexTelegram].scene_id = 32;
	_entries[kIndexPassengerList].scene_id = 33;
	_entries[kIndexScarf].scene_id = 34;
	_entries[kIndexParchemin].scene_id = 35;
	_entries[kIndexArticle].scene_id = 36;
	_entries[kIndexPaper].scene_id = 37;
	_entries[kIndexFirebird].scene_id = 38;
	_entries[kIndexBriefcase].scene_id = 39;

	// has_item
	_entries[kIndexTelegram].has_item = 1;
	_entries[kIndexArticle].has_item = 1;

	_selectedItem = 0;
}

// FIXME we need to draw cursors with full background opacity so that whatever is in the background is erased
// this saved us clearing some part of the background when switching between states

// TODO if we draw inventory objects on screen, we need to load a new scene.
// Signal that the inventory has taken over the screen and stop processing mouse events after we have been called
void Inventory::handleMouseEvent(Common::Event ev) {

	// Do not show inventory when on the menu screen
	if (_engine->getLogic()->isShowingMenu())
		return;

	// Flag to know whether to restore the current cursor or not
	bool insideInventory = false;

	// Egg (menu)
	if (_menuRect.contains(ev.mouse)) {
		insideInventory = true;
		_engine->getCursor()->setStyle(Cursor::kCursorNormal);

		// If clicked, show the menu
		if (ev.type == Common::EVENT_LBUTTONDOWN) {
			playSfx("LIB039.SND");
			_engine->getLogic()->showMenu(true);

			// TODO can we return directly or do we need to make sure the state will be "valid" when we come back from the menu
			return;
		} else {
			// Highlight if needed
			if (_highlightedItem != _engine->getLogic()->getGameId() + 39) {
				_highlightedItem = (InventoryItem)(_engine->getLogic()->getGameId() + 39);
				drawItem(608, 448, _highlightedItem, 100)

				askForRedraw();
			}
		}
	} else {
		// remove hightlight if needed
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
			if (_highlightedItem != (InventoryItem)getProgress().portraitType && !_opened) {
				_highlightedItem = (InventoryItem)getProgress().portraitType;
				drawItem(0, 0, getProgress().portraitType, 100)

				askForRedraw();
			}
		}
	} else {
		// remove hightlight if needed
		if (_highlightedItem == (InventoryItem)getProgress().portraitType && !_opened) {
			drawItem(0, 0, getProgress().portraitType, 50)
			_highlightedItem = kNoItem;
			askForRedraw();
		}
	}

	// If the inventory is open, check all items rect to see if we need to higlight one / handle click
	if (_opened) {

		// Always show normal cursor when the inventory is opened
		insideInventory = true;
		_engine->getCursor()->setStyle(Cursor::kCursorNormal);

		bool selected = false;

		// Iterate over items
		int y = 44;
		for (uint i = 1; i < 32; i++) {
			if (_entries[i].has_item) {
				if (Common::Rect(0, y, 32, 32 + y).contains(ev.mouse)) {

					// If released with an item highlighted, show this item
					if (ev.type == Common::EVENT_LBUTTONUP) {
						if (_entries[i].is_selectable) {
							selected = true;
							_selectedItem = (InventoryItem)_entries[i].item_id;
							drawItem(44, 0, _selectedItem, 100)
						}

						examine((InventoryItem)_entries[i].item_id);
						break;
					} else {
						if (_highlightedItem != _entries[i].item_id) {
							drawItem(0, y, _entries[i].item_id, 100)
							_highlightedItem = (InventoryItem)_entries[i].item_id;
							askForRedraw();
						}
					}
				} else {
					// Remove hightlight if necessary
					if (_highlightedItem == (InventoryItem)_entries[i].item_id) {
						drawItem(0, y, _entries[i].item_id, 50)
						_highlightedItem = kNoItem;
						askForRedraw();
					}
				}

				y += 40;
			}
		}

		// Right button is released: we need to close the inventory
		if (ev.type == Common::EVENT_LBUTTONUP) {

			// Not on a selectable item: deselect the current item
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
}

void Inventory::show(bool visible) {
	clearBg(GraphicsManager::kBackgroundInventory);
	askForRedraw();

	if (!visible)
		return;

	// Show portrait (first draw, cannot be highlighted)
	drawItem(0, 0, getProgress().portraitType, 50)

	// Show selected item
	if (_selectedItem != kNoItem)
		drawItem(44, 0, _selectedItem, 100)

	drawEgg();
}

void Inventory::setPortrait(InventoryItem item) {
	getProgress().portraitType = item;
	drawItem(0, 0, getProgress().portraitType, 50);
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
void Inventory::addItem(InventoryItem item) {
	if (hasItem(item))
		return;

	getEntry(item)->has_item = 1;
	getEntry(item)->field_6 = 0;

	// Autoselect item if necessary
	if (!getEntry(item)->no_autoselect) {
		_selectedItem = getEntry(item)->item_id;
		drawItem(44, 0, _selectedItem, 100)
		askForRedraw();
	}
}

void Inventory::removeItem(InventoryItem item) {
	if (!hasItem(item))
		return;

	getEntry(item)->has_item = 0;
	getEntry(item)->field_6 = 0;

	if (getEntry(item)->item_id == _selectedItem) {
		_selectedItem = kNoItem;
		_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundInventory, Common::Rect(44, 0, 44 + 32, 32));
		askForRedraw();
	}
}

bool Inventory::hasItem(InventoryItem item) {
	if (getEntry(item)->has_item)
			return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////////////////////////
Inventory::InventoryEntry *Inventory::getEntry(InventoryItem item) {
	for (uint i = 0; i < 32; i++) {
		if (_entries[i].item_id == (byte)item)
			return &_entries[i];
	}

	// Should never get invalid item
	error("Invalid inventory item id: %D", item);
}

// Examine an inventory item
void Inventory::examine(InventoryItem item) {
	uint32 sceneId = getEntry(item)->scene_id;

	if (sceneId != 0) {
		Scene *s = _engine->getScene(sceneId);
		_engine->getGraphicsManager()->draw(s, GraphicsManager::kBackgroundOverlay);
		delete s;
	}

	// TODO implement
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
	drawItem(0, 0, getProgress().portraitType + 1, 100)

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
	drawItem(0, 0, getProgress().portraitType, 100)

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
