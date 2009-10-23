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

#include "lastexpress/savegame.h"
#include "lastexpress/scene.h"

#include "common/events.h"

namespace LastExpress {

class LastExpressEngine;

class Inventory {
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
		kCorpse = 29
	};

	Inventory(LastExpressEngine *engine);
	~Inventory();

	void init(SaveLoad::GameState *state);

	// Handle inventory UI events.
	void handleMouseEvent(Common::Event ev);

	// Inventory contents
	void addItem(InventoryItem item);
	void removeItem(InventoryItem item);
	bool hasItem(InventoryItem item);

	// UI Control
	void show(bool visible);
	void blinkEgg(bool enabled);
	void showHourGlass(bool enabled);

private:
	static const uint32 _defaultBlinkingInterval = 250;	//<! Default blinking interval in ms

	// Index if items in inventory data
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

	LastExpressEngine *_engine;

	// State
	bool _opened;
	InventoryItem _highlightedItem;

	bool _showingHourGlass;
	bool _blinkingEgg;
	uint32 _blinkingTime;
	uint32 _blinkingInterval;
	int _blinkingBrightness;

	// Items scene
	Scene _scene;

	// Important rects
	Common::Rect _inventoryRect;
	Common::Rect _menuRect;
	Common::Rect _selectedRect;

	void open();
	void close();
	void examine(InventoryItem item);
	void drawEgg();
	SaveLoad::InventoryEntry *getEntry(InventoryItem item);
	Common::Rect getItemRect(int index);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_INVENTORY_H
