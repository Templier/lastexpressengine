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

#include "lastexpress/data/scene.h"

#include "common/events.h"
#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;

class Inventory : Common::Serializable {
public:
	// Index of items in inventory data
	enum InventoryItem {
		kNoItem = 0,

		kMatchBox = 1,
		kItem2 = 2,
		kItem3 = 3,
		kTelegram = 4,
		kItem5 = 5,
		kPassengerList = 6,
		kItem7 = 7,
		kScarf = 8,
		kItem9 = 9,
		kParchemin = 10,
		kItem11 = 11,
		kMatch = 12,
		kWhistle = 13,
		kBeetle = 14,
		kKey = 15,
		kBomb = 16,
		kItem17 = 17,
		kFirebird = 18,
		kBriefcase = 19,
		kCorpse = 20,
		kGreenJacket = 21,
		kItem22 = 22,
		kPaper = 23,
		kArticle = 24,		
		kItem25 = 25,
		kItem26 = 26,
		kItem27 = 27,
		kItem28 = 28,
		kItem29 = 29,
		kItem30 = 30,
		kItem31 = 31,
				
		// Portrait (not an index)
		kPortraitOriginal = 32,		
		kPortraitGreen = 34,		
		kPortraitYellow = 36
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

	// Inventory contents
	void addItem(InventoryItem item);
	void removeItem(InventoryItem item, byte newLocation = 0);
	bool hasItem(InventoryItem item);	
	void selectItem(InventoryItem item);
	void unselectItem();
	InventoryItem getSelectedItem() { return _selectedItem; }

	InventoryEntry *getEntry(InventoryItem item);
	InventoryEntry *getSelectedEntry() { return getEntry(_selectedItem); }

	// UI Control
	void show(bool visible);
	void blinkEgg(bool enabled);
	void showHourGlass(bool enabled);
	void setPortrait(InventoryItem item);

	// Handle inventory UI events.
	bool handleMouseEvent(Common::Event ev);

	void restore();
	void setLocationAndProcess(InventoryItem item, byte newLocation);

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
	Common::Rect getItemRect(int index);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_INVENTORY_H
