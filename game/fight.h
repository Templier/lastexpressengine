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
	uint32 {4}      - player struct
	uint32 {4}      - opponent struct
	uint32 {4}      - hasLost flag

	byte {1}        - isRunning

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

	int getState() { return _state; }

private:	
	enum FightSequenceType {
		kFightSequenceType0 = 0,
		kFightSequenceType1 = 1,
		kFightSequenceType2 = 2
	};

	enum FightAction {
		kFightAction101 = 101,
		kFightAction102 = 102,
		kFightAction103 = 103
	};

	struct FightCombatant {
		// Function pointer
		//FightData *fight;
		FightCombatant* opponent;
		Common::Array<Sequence *> sequences;
		uint32 sequenceIndex;
		Sequence *currentSequence;
		Sequence *currentSequence2;
		uint32 field_20;
		uint32 field_24;
		FightAction action;
		uint32 sequenceIndex2;
		int32 field_30;
		uint16 field_34;

		FightCombatant() {
			// TODO init function pointer to NULL
			//fight = NULL;
			opponent = NULL;

			action = kFightAction101;

			currentSequence = NULL;
			currentSequence2 = NULL;

			field_20 = 0;
			field_24 = 0;

			sequenceIndex = 0;
			sequenceIndex2 = 0;

			field_30 = 1;

			field_34 = 0;
		}
	};

	// Opponent struct
	struct FightOpponent : FightCombatant {
		uint16 field_36;
		uint32 field_38;

		FightOpponent() : FightCombatant() {
			field_36 = 0;
			field_38 = 0;
		}
	};

	struct FightData {
		FightCombatant *player;
		FightOpponent *opponent;
		int32 field_C;



		bool isRunning;

		FightData() {
			player = new FightCombatant();
			opponent = new FightOpponent();

			// Set opponents
			player->opponent = opponent;
			opponent->opponent = player;

			field_C = 0;

			isRunning = false;
		}
	};

	LastExpressEngine* _engine;
	FightData *_data;
	bool _hasLost;
	int _state;

	// Events
	void handleMouseMove(Common::Event ev, bool unknown);

	// State
	void bailout(bool hasLost);

	// Drawing
	void setSequenceAndDraw(FightCombatant *combatant, uint32 sequenceIndex, FightSequenceType type);
	void draw(FightCombatant *combatant);
	
	// Cleanup
	void clear();
	void clearSequences(FightCombatant *combatant);

	// Loading
	void loadData(FightType type);

	void loadMilosPlayer();
	void loadMilosOpponent();
	void loadAnnaPlayer();
	void loadAnnaOpponent();
	void loadIvoPlayer();
	void loadIvoOpponent();
	void loadSalkoPlayer();
	void loadSalkoOpponent();
	void loadVesnaPlayer();
	void loadVesnaOpponent();

};

} // End of namespace LastExpress

#endif // LASTEXPRESS_FIGHT_H
