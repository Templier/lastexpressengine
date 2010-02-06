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

#ifndef LASTEXPRESS_FIGHT_H
#define LASTEXPRESS_FIGHT_H

/*
	Fight structure
	---------------


	Fight participant structure
	---------------------------
	uint32 {4}      - function pointer
	uint32 {4}      - pointer to fight structure
	uint32 {4}      - pointer to opponent (fight participant structure)
	uint32 {4}      - array of sequences
	uint32 {4}      - number of sequences
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint32 {4}      - ??
	uint16 {2}      - ??
	uint16 {2}      - ??    - only for opponent structure
	uint32 {4}      - ??    - only for opponent structure

*/

#include "lastexpress/shared.h"

#include "lastexpress/eventhandler.h"

#include "common/array.h"

namespace LastExpress {


class LastExpressEngine;
class Sequence;

class Fight : public EventHandler {
public:

	Fight(LastExpressEngine *engine);
	~Fight();

	bool setup(FightType type);

	void eventMouseClick(Common::Event ev);
	void eventMouseMove(Common::Event ev);	

	void setStopped();

private:
	struct FightCombatant {
		// Function pointer
		//FightData *fight;
		//FightCombatant* opponent;
		Common::Array<Sequence *> sequences;
		// sequences_count

	};

	struct FightOpponent : FightCombatant {
		
	};

	struct FightData {
		FightCombatant *player;
		FightCombatant *opponent;
		//bool hasLost;

		bool isRunning;
	};

	LastExpressEngine* _engine;
	FightData *_data;
	bool _hasLost;


	void loadData(FightType type);

	void handleMouseMove(Common::Event ev, bool unknown);
	
	void clear();
	void clearSequences(FightCombatant *combatant);

};

} // End of namespace LastExpress

#endif // LASTEXPRESS_FIGHT_H
