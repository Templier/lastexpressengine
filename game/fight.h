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

//////////////////////////////////////////////////////////////////////////
// TODO : objectify!
class Fight : public EventHandler {
public:
	enum FightEndType {
		kFightEndWin  = 0,
		kFightEndLost = 1,
		kFightEndExit    = 2
	};

	Fight(LastExpressEngine *engine);
	~Fight();

	FightEndType setup(FightType type);

	void eventMouseClick(Common::Event ev);
	void eventMouseMove(Common::Event ev);

	void setStopped();
private:
	enum FightSequenceType {
		kFightSequenceType0 = 0,
		kFightSequenceType1 = 1,
		kFightSequenceType2 = 2
	};

	enum FightAction {
		kFightAction1 = 1,
		kFightAction2 = 2,
		kFightAction4 = 4,
		kFightAction101 = 101,
		kFightActionResetFrame = 102,
		kFightAction103 = 103,
		kFightActionWin = 104,
		kFightActionLost = 105,
		kFightAction128 = 128,
		kFightAction131 = 131
	};

	typedef struct Fighter;

	struct Fighter {
		Common::Functor2<Fighter *, FightAction, void> *handleAction;
		Common::Functor1<Fighter *, void> *update;
		Common::Functor2<Fighter *, FightAction, int> *canInteract;
		Fighter* opponent;
		Common::Array<Sequence *> sequences;
		uint32 sequenceIndex;
		Sequence *currentSequence;
		Sequence *currentSequence2;
		uint32 frameIndex;
		uint32 field_24;
		FightAction action;
		uint32 sequenceIndex2;
		int32 countdown;  // countdown before loosing ?
		uint16 field_34;

		Fighter() {
			handleAction = NULL;
			update = NULL;
			canInteract = NULL;

			opponent = NULL;

			action = kFightAction101;

			currentSequence = NULL;
			currentSequence2 = NULL;

			frameIndex = 0;
			field_24 = 0;

			sequenceIndex = 0;
			sequenceIndex2 = 0;

			countdown = 1;

			field_34 = 0;
		}
	};

	// Opponent struct
	struct Opponent : Fighter {
		uint16 field_36;
		uint32 field_38;

		Opponent() : Fighter() {
			field_36 = 0;
			field_38 = 0;
		}
	};

	struct FightData {
		Fighter *player;
		Opponent *opponent;
		int32 index;

		Sequence *sequences[20];
		Common::String names[20];

		bool isRunning;

		FightData() {
			player = new Fighter();
			opponent = new Opponent();

			// Set opponents
			player->opponent = opponent;
			opponent->opponent = player;

			index = 0;

			isRunning = false;
		}
	};

	LastExpressEngine* _engine;
	FightData *_data;
	FightEndType _endType;
	int _state;

	bool _handleTimer;

	// Events
	void handleMouseMove(Common::Event ev, bool unknown);

	// State
	void bailout(FightEndType type);
	

	// Drawing
	void setSequenceAndDraw(Fighter *fighter, uint32 sequenceIndex, FightSequenceType type);
	void draw(Fighter *fighter);

	// Cleanup
	void clear();
	void clearSequences(Fighter *fighter);

	//////////////////////////////////////////////////////////////////////////
	// Loading
	void loadData(FightType type);

	// Shared
	void processFighter(Fighter *fighter);
		
	// Default functions
	void handleAction(Fighter *fighter, FightAction action);
	void update(Fighter *fighter);
	int canInteract(Fighter *fighter, FightAction = (FightAction)0);
	void updateOpponent(Fighter *fighter);

	// Milos
	void loadMilosPlayer();
	void loadMilosOpponent();
	void handleActionMilos(Fighter *fighter, FightAction action);
	void updateMilos(Fighter *fighter);
	int canInteractMilos(Fighter *fighter, FightAction action);
	void handleOpponentActionMilos(Fighter *fighter, FightAction action);
	void updateOpponentMilos(Fighter *fighter);

	// Anna
	void loadAnnaPlayer();
	void loadAnnaOpponent();
	void handleActionAnna(Fighter *fighter, FightAction action);
	void updateOpponentAnna(Fighter *fighter);

	// Ivo
	void loadIvoPlayer();
	void loadIvoOpponent();
	void handleActionIvo(Fighter *fighter, FightAction action);
	void updateIvo(Fighter *fighter);
	int canInteractIvo(Fighter *fighter, FightAction action);
	void handleOpponentActionIvo(Fighter *fighter, FightAction action);
	void updateOpponentIvo(Fighter *fighter);

	// Salko
	void loadSalkoPlayer();
	void loadSalkoOpponent();
	void handleActionSalko(Fighter *fighter, FightAction action);
	void updateSalko(Fighter *fighter);
	int canInteractSalko(Fighter *fighter, FightAction action);
	void handleOpponentActionSalko(Fighter *fighter, FightAction action);
	void updateOpponentSalko(Fighter *fighter);

	// Vesna
	void loadVesnaPlayer();
	void loadVesnaOpponent();
	void handleActionVesna(Fighter *fighter, FightAction action);
	void updateVesna(Fighter *fighter);
	int canInteractVesna(Fighter *fighter, FightAction action);
	void handleOpponentActionVesna(Fighter *fighter, FightAction action);
	void updateOpponentVesna(Fighter *fighter);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_FIGHT_H
