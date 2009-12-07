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

#ifndef LASTEXPRESS_ACTION_H
#define LASTEXPRESS_ACTION_H

#include "lastexpress/shared.h"

#include "common/func.h"
#include "common/system.h"

namespace LastExpress {

#define DECLARE_ACTION(name) \
	void action_##name(SceneHotspot *hotspot)

#define ADD_ACTION(name) \
	_actions.push_back(new Common::Functor1Mem<SceneHotspot*, void, Action>(this, &Action::action_##name));

#define IMPLEMENT_ACTION(name) \
	void Action::action_##name(SceneHotspot *hotspot)

class LastExpressEngine;
class SceneHotspot;

class Action {
public:
	Action(LastExpressEngine *engine);
	~Action();

	// Hotspot action
	void processHotspot(SceneHotspot *hotspot);
	
	// Cursor
	CursorStyle getCursor(byte action, ObjectIndex object, byte param2, byte param3, byte cursor);

	// Animation
	void playAnimation(int index);

private:
	typedef Common::Functor1<SceneHotspot*, void> ActionFunctor;
	
	LastExpressEngine* _engine;
	Common::Array<ActionFunctor *> _actions; 

	// Each action is of the form action_<name>(SceneHotspot *hotspot)
	//   - a pointer to each action is added to the _actions array
	//   - processHotspot simply calls the proper function given by the hotspot->action value
	//
	// Note: even though there are 44 actions, only 41 are used in processHotspot
	
	DECLARE_ACTION(inventory);
	DECLARE_ACTION(savePoint);
	DECLARE_ACTION(playSound);
	DECLARE_ACTION(playMusic);
	DECLARE_ACTION(knock);
	DECLARE_ACTION(compartment);
	DECLARE_ACTION(playSounds);
	DECLARE_ACTION(playAnimation);
	DECLARE_ACTION(openCloseObject);
	DECLARE_ACTION(10);
	DECLARE_ACTION(setItemLocation);
	DECLARE_ACTION(12);
	DECLARE_ACTION(pickItem);
	DECLARE_ACTION(dropItem);
	DECLARE_ACTION(enterCompartment);
	DECLARE_ACTION(getOutsideTrain);
	DECLARE_ACTION(slip);
	DECLARE_ACTION(getInsideTrain);
	DECLARE_ACTION(climbUpTrain);
	DECLARE_ACTION(climbDownTrain);
	DECLARE_ACTION(jumpUpDownTrain);
	DECLARE_ACTION(unbound);
	DECLARE_ACTION(25);
	DECLARE_ACTION(26);
	DECLARE_ACTION(27);
	DECLARE_ACTION(concertSitCough);
	DECLARE_ACTION(29);
	DECLARE_ACTION(catchBeetle);
	DECLARE_ACTION(exitCompartment);
	DECLARE_ACTION(32);
	DECLARE_ACTION(useWhistle);
	DECLARE_ACTION(openMatchBox);
	DECLARE_ACTION(openBed);
	DECLARE_ACTION(dialog);
	DECLARE_ACTION(eggBox);
	DECLARE_ACTION(39);
	DECLARE_ACTION(bed);
	DECLARE_ACTION(41);
	DECLARE_ACTION(42);
	DECLARE_ACTION(44);

	// Special dummy function
	DECLARE_ACTION(dummy);

	// Helpers
	void pickGreenJacket(bool process);
	void pickScarf(bool process);
	void pickCorpse(byte bedPosition, bool process);
	void dropCorpse(bool process);
	bool handleOtherCompartment(ObjectIndex object, byte param2, byte param3);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_ACTION_H
