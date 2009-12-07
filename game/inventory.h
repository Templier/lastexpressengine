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

#ifndef LASTEXPRESS_INVENTORY_H
#define LASTEXPRESS_INVENTORY_H

/*
	Inventory entry (32 entries)
	----------------------------

		byte {1}        - Item ID (set to 0 for "undefined" items)
		byte {1}        - Scene ID
		byte {1}        - ??
		byte {1}        - Selectable (1 if item is selectable, 0 otherwise)
		byte {1}        - Is item in inventory (set to 1 for telegram and article)
		byte {1}        - Auto selection (1 for no auto selection, 0 otherwise)
		byte {1}        - Location

*/

#include "lastexpress/shared.h"

#include "common/events.h"
#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;
class Scene;

class Inventory : Common::Serializable {
public:
	
	// Entry
	struct InventoryEntry {
		byte item_id;
		byte scene_id;
		byte field_2;
		byte is_selectable;
		byte has_item;
		byte no_autoselect;
		ObjectLocation location;

		InventoryEntry() {
			item_id = 0;
			scene_id = 0;
			field_2 = 0;
			is_selectable = 0;
			has_item = 0;
			no_autoselect = 1; 
			location = kLocationNone;
		}
	};

	Inventory(LastExpressEngine *engine);
	~Inventory();

	void init();

	// Inventory contents
	void addItem(InventoryItem item);
	void removeItem(InventoryItem item, ObjectLocation newLocation = kLocationNone);
	bool hasItem(InventoryItem item);	
	void selectItem(InventoryItem item);
	void unselectItem();
	InventoryItem getSelectedItem() { return _selectedItem; }

	InventoryEntry *getEntry(InventoryItem item);
	InventoryEntry *getSelectedEntry() { return getEntry(_selectedItem); }

	InventoryItem getFirstExaminableItem();
	void setLocationAndProcess(InventoryItem item, ObjectLocation location);

	// UI Control
	void show(bool visible);
	void blinkEgg(bool enabled);
	void showHourGlass(bool enabled);
	void setPortrait(InventoryItem item);
	void showItem(InventoryItem item);

	// Handle inventory UI events.
	bool handleMouseEvent(Common::Event ev);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

private:
	static const uint32 _defaultBlinkingInterval = 250; ///< Default blinking interval in ms

	LastExpressEngine *_engine;

	InventoryEntry _entries[32];
	InventoryItem _selectedItem;
	InventoryItem _highlightedItem;
	bool _opened;
	bool _visible;
	
	bool _showingHourGlass;
	bool _blinkingEgg;
	uint32 _blinkingTime;
	uint32 _blinkingInterval;
	int _blinkingBrightness;

	Scene *_itemScene;

	// Important rects
	Common::Rect _inventoryRect;
	Common::Rect _menuRect;
	Common::Rect _selectedRect;

	void open();
	void close();
	void examine(InventoryItem item);
	void drawEgg();	
	Common::Rect getItemRect(int16 index);

	bool isItemSceneParameter(InventoryItem item);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_INVENTORY_H
