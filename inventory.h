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
		byte {1}        - 1 if item is "selectable"
		byte {1}        - ?? set to 1 for matchbox, match, telegram, whistle, key, firebird, briefcase, corpse, passengerlist
		byte {1}        - Is item in inventory (set to 1 for telegram and article)
		byte {1}        - No autoselect set to 1 (including entry 0 and excepting last entry) and set to 0 for XXXX(several entries), firebird, briefcase, corpse
		byte {1}        - ?? set to 0

*/

#include "lastexpress/scene.h"

#include "common/events.h"
#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;

class Inventory : Common::Serializable {
public:
	// Items (same id as cursors) FIXME: do we need to duplicate those?
	enum InventoryItem {
		// Special
		kNoItem = 0,

		// Items
		kMatchBox = 16,
		kTelegram = 17,
		kPassengerList = 18,
		kArticle = 19,
		kScarf = 20,
		kPaper = 21,
		kParchemin = 22,
		kMatch = 23,
		kWhistle = 24,
		kKey = 25,
		kBomb = 26,
		kFirebird = 27,
		kBriefcase = 28,
		kCorpse = 29,

		// Portraits
		kPortraitNormal = 32,
		kPortraitGreen = 34,
		kPortraitYellow = 36
	};

	// Index of items in inventory data
	enum InventoryDataIndex {
		kIndexMatchBox = 1,
		kIndexTelegram = 4,
		kIndexPassengerList = 6,
		kIndexArticle = 24,
		kIndexScarf = 8,
		kIndexPaper = 23,
		kIndexParchemin = 10,
		kIndexMatch = 12,
		kIndexWhistle = 13,
		kIndexKey = 15,
		kIndexBomb = 16,
		kIndexFirebird = 18,
		kIndexBriefcase = 19,
		kIndexCorpse = 20
	};

	// Entry
	struct InventoryEntry {
		byte item_id;
		byte scene_id;
		byte field_2;
		byte is_selectable;
		byte has_item;
		byte no_autoselect;
		byte location;

		InventoryEntry() {
			item_id = 0;
			scene_id = 0;
			field_2 = 0;
			is_selectable = 0;
			has_item = 0;
			no_autoselect = 1; 
			location = 0;
		}
	};

	Inventory(LastExpressEngine *engine);
	~Inventory();

	void init();

	// Handle inventory UI events.
	bool handleMouseEvent(Common::Event ev);

	// Inventory contents
	void addItem(InventoryItem item);
	void removeItem(InventoryItem item);
	bool hasItem(InventoryItem item);
	InventoryEntry *getItem(InventoryItem item);
	InventoryEntry *getEntry(int index);
	InventoryItem getSelectedItem() { return (InventoryItem)getEntry(_selectedItem)->item_id; }
	int getSelectedIndex() { return _selectedItem; }
	void selectItem(int index) { _selectedItem = index; } // needed or can we use InventoryItem as param?

	// UI Control
	void show(bool visible);
	void blinkEgg(bool enabled);
	void showHourGlass(bool enabled);
	void setPortrait(InventoryItem item);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

private:
	static const uint32 _defaultBlinkingInterval = 250; ///< Default blinking interval in ms

	LastExpressEngine *_engine;

	InventoryEntry _entries[32];
	int _selectedItem;
	bool _opened;
	bool _visible;
	InventoryItem _highlightedItem;

	bool _showingHourGlass;
	bool _blinkingEgg;
	uint32 _blinkingTime;
	uint32 _blinkingInterval;
	int _blinkingBrightness;

	// Important rects
	Common::Rect _inventoryRect;
	Common::Rect _menuRect;
	Common::Rect _selectedRect;

	void open();
	void close();
	void examine(InventoryItem item);
	void drawEgg();	
	Common::Rect getItemRect(int index);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_INVENTORY_H
