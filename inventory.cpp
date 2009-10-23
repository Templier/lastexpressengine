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

#define drawItem(x, y, index) _engine->getGraphicsManager()->draw(_engine->getCursor(), x, y, index, GraphicsManager::kBackgroundInventory)
#define drawItemBrightness(x, y, index, brightness) _engine->getGraphicsManager()->draw(_engine->getCursor(), x, y, index, GraphicsManager::kBackgroundInventory, brightness)

namespace LastExpress {

Inventory::Inventory(LastExpressEngine *engine) : _engine(engine),
	_showingHourGlass(false), _blinkingEgg(false), _blinkingTime(0), _blinkingBrightness(100), _blinkingInterval(_defaultBlinkingInterval),
	_opened(false), _scene(engine->getResource()) {

	_inventoryRect = Common::Rect(0, 0, 32, 32);
	_menuRect = Common::Rect(608, 448, 640, 480);
	_selectedRect = Common::Rect(44, 0, 76, 32);

	// Load scene data
	_scene.loadScene(1);
}

Inventory::~Inventory() {}

//////////////////////////////////////////////////////////////////////////
// Inventory handling
//////////////////////////////////////////////////////////////////////////

// Init inventory contents
void Inventory::init(SaveLoad::GameState *state) {

	// item_id
	state->inventory[kIndexMatchBox].item_id = kMatchBox;
	state->inventory[kIndexTelegram].item_id = kTelegram;
	state->inventory[kIndexPassengerList].item_id = kPassengerList;
	state->inventory[kIndexArticle].item_id = kArticle;
	state->inventory[kIndexScarf].item_id = kScarf;
	state->inventory[kIndexPaper].item_id = kPaper;
	state->inventory[kIndexParchemin].item_id = kParchemin;
	state->inventory[kIndexMatch].item_id = kMatch;
	state->inventory[kIndexWhistle].item_id = kWhistle;
	state->inventory[kIndexKey].item_id = kKey;
	state->inventory[kIndexBomb].item_id = kBomb;
	state->inventory[kIndexFirebird].item_id = kFirebird;
	state->inventory[kIndexBriefcase].item_id = kBriefcase;
	state->inventory[kIndexCorpse].item_id = kCorpse;

	// is_selectable
	state->inventory[kIndexMatchBox].is_selectable = 1;
	state->inventory[kIndexMatch].is_selectable = 1;
	state->inventory[kIndexTelegram].is_selectable = 1;
	state->inventory[kIndexWhistle].is_selectable = 1;
	state->inventory[kIndexKey].is_selectable = 1;
	state->inventory[kIndexFirebird].is_selectable = 1;
	state->inventory[kIndexBriefcase].is_selectable = 1;
	state->inventory[kIndexCorpse].is_selectable = 1;
	state->inventory[kIndexPassengerList].is_selectable = 1;

	// ??
	state->inventory[2].field_5 = 0;
	state->inventory[3].field_5 = 0;
	state->inventory[5].field_5 = 0;
	state->inventory[7].field_5 = 0;
	state->inventory[9].field_5 = 0;
	state->inventory[11].field_5 = 0;
	state->inventory[14].field_5 = 0;
	state->inventory[17].field_5 = 0;
	state->inventory[kIndexFirebird].field_5 = 0;
	state->inventory[kIndexBriefcase].field_5 = 0;
	state->inventory[kIndexCorpse].field_5 = 0;
	state->inventory[21].field_5 = 0;
	state->inventory[22].field_5 = 0;

	// scene_id
	state->inventory[kIndexMatchBox].scene_id = 31;
	state->inventory[kIndexTelegram].scene_id = 32;
	state->inventory[kIndexPassengerList].scene_id = 33;
	state->inventory[kIndexScarf].scene_id = 34;
	state->inventory[kIndexParchemin].scene_id = 35;
	state->inventory[kIndexArticle].scene_id = 36;
	state->inventory[kIndexPaper].scene_id = 37;
	state->inventory[kIndexFirebird].scene_id = 38;
	state->inventory[kIndexBriefcase].scene_id = 39;

	// has_item
	state->inventory[kIndexTelegram].has_item = 1;
	state->inventory[kIndexArticle].has_item = 1;
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
			if (_highlightedItem != getGameId() + 39) {
				_highlightedItem = (InventoryItem)(getGameId() + 39);
				drawItem(608, 448, _highlightedItem);

				askForRedraw();
			}
		}
	} else {
		// remove hightlight if needed
		if (_highlightedItem == getGameId() + 39) {
			drawItemBrightness(608, 448, _highlightedItem, 50);
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
				drawItem(0, 0, getProgress().portraitType);

				askForRedraw();
			}
		}
	} else {
		// remove hightlight if needed
		if (_highlightedItem == (InventoryItem)getProgress().portraitType && !_opened) {
			drawItemBrightness(0, 0, getProgress().portraitType, 50);
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
			if (getState()->inventory[i].has_item) {
				if (Common::Rect(0, y, 32, 32 + y).contains(ev.mouse)) {

					// If released with an item highlighted, show this item
					if (ev.type == Common::EVENT_LBUTTONUP) {
						if (getState()->inventory[i].is_selectable) {
							selected = true;
							getState()->selectedItem = (InventoryItem)getState()->inventory[i].item_id;
							drawItem(44, 0, getState()->selectedItem);
						}

						examine((InventoryItem)getState()->inventory[i].item_id);
						break;
					} else {
						if (_highlightedItem != getState()->inventory[i].item_id) {
							drawItem(0, y, getState()->inventory[i].item_id);
							_highlightedItem = (InventoryItem)getState()->inventory[i].item_id;
							askForRedraw();
						}
					}
				} else {
					// Remove hightlight if necessary
					if (_highlightedItem == (InventoryItem)getState()->inventory[i].item_id) {
						drawItemBrightness(0, y, getState()->inventory[i].item_id, 50);
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
				getState()->selectedItem = kNoItem;
				_engine->getGraphicsManager()->clear(GraphicsManager::kBackgroundInventory, Common::Rect(44, 0, 44 + 32, 32));
			}
			close();
			askForRedraw();
		}
	}

	// Selected item
	if (getState()->selectedItem != kNoItem && _selectedRect.contains(ev.mouse)) {
		insideInventory = true;
		// Show magnifier icon
		_engine->getCursor()->setStyle(Cursor::kCursorMagnifier);

		if (ev.type == Common::EVENT_LBUTTONDOWN) {
			examine((InventoryItem)getState()->selectedItem);
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
	drawItemBrightness(0, 0, getProgress().portraitType, 50);

	// Show selected item
	if (getState()->selectedItem != kNoItem)
		drawItem(44, 0, getState()->selectedItem);

	drawEgg();
}

void Inventory::blinkEgg(bool enabled) {
	_blinkingEgg = enabled;

	// Reset state
	_showingHourGlass = false;

	// Show egg at full brightness for first step if blinking
	if (_blinkingEgg)
		drawItemBrightness(608, 448, getGameId() + 39, _blinkingBrightness);
	else {
		// Reset values
		_blinkingBrightness = 100;
		_blinkingInterval = _defaultBlinkingInterval;
		drawItemBrightness(608, 448, getGameId() + 39, 50);	// normal egg state
	}

	askForRedraw();
}

void Inventory::showHourGlass(bool enabled) {
	_showingHourGlass = enabled;

	// Reset state
	_blinkingEgg = false;

	// Show/Hide hour glass and ask for redraw
	if (_showingHourGlass)
		drawItem(608, 448, Cursor::kCursorHourGlass);
	else
		drawItem(608, 448, getGameId() + 39); // normal egg state

	askForRedraw();
}

//////////////////////////////////////////////////////////////////////////
// Items
//////////////////////////////////////////////////////////////////////////
void Inventory::addItem(InventoryItem item) {
	if (hasItem(item))
		return;

	getEntry(item)->has_item = 1;
}

void Inventory::removeItem(InventoryItem item) {
	if (!hasItem(item))
		return;

	getEntry(item)->has_item = 0;
}

bool Inventory::hasItem(InventoryItem item) {
	if (getEntry(item)->has_item)
			return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////////////////////////
SaveLoad::InventoryEntry *Inventory::getEntry(InventoryItem item) {
	for (uint i = 0; i < 32; i++) {
		if (getState()->inventory[i].item_id == (byte)item)
			return &getState()->inventory[i];
	}

	// Should never get invalid item
	error("Invalid inventory item id: %D", item);
}

// Examine an inventory item
void Inventory::examine(InventoryItem item) {

	uint32 sceneId = getEntry(item)->scene_id;

	if (sceneId != 0)
		showScene(&_scene, sceneId, GraphicsManager::kBackgroundOverlay);

	// TODO implement
}

void Inventory::drawEgg() {
	// Blinking egg: we need to blink the egg for delta time, with the blinking getting faster until it's always lit.
	if (_blinkingEgg) {
		drawItemBrightness(608, 448, getGameId() + 39, _blinkingBrightness);

		// TODO if delta time > _blinkingInterval, update egg & ask for redraw then adjust blinking time and remaining time

		// Reset values and stop blinking
		if (_blinkingTime == 0)
			blinkEgg(false);

		askForRedraw();
	} else {
		drawItemBrightness(608, 448, getGameId() + 39, 50);
	}
}

// Close inventory: clear items and reset icon
void Inventory::open() {
	_opened = true;

	// Show selected state
	drawItem(0, 0, getProgress().portraitType + 1);

	uint y = 44;

	// Iterate over items
	for (uint i = 1; i < 32; i++) {
		if (getState()->inventory[i].has_item) {
			drawItemBrightness(0, y, getState()->inventory[i].item_id, 50);
			y += 40;
		}
	}

	askForRedraw();
}

// Close inventory: clear items and reset icon
void Inventory::close() {
	_opened = false;

	// Fallback to unselected state
	drawItem(0, 0, getProgress().portraitType);

	// Erase rectangle for all inventory items
	int count = 0;
	for (uint i = 1; i < 32; i++) {
		if (getState()->inventory[i].has_item) {
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
