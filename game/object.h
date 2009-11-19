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

#ifndef LASTEXPRESS_OBJECT_H
#define LASTEXPRESS_OBJECT_H

#include "lastexpress/game/savepoint.h"

#include "common/serializer.h"
#include "common/system.h"

namespace LastExpress {

class LastExpressEngine;

class Objects : Common::Serializable {
public:
	enum ObjectIndex {
		kObjectNone,
		kObjectCompartment1,
		kObjectCompartment2,
		kObjectCompartment3,
		kObjectCompartment4,
		kObjectCompartment5,				// 5
		kObjectCompartment6,
		kObjectCompartment7,
		kObjectCompartment8,
		kObjectOutside,
		kObject10,							// 10
		kObject11,
		kObject12,
		kObject13,
		kObject14,
		kObject15,							// 15
		kObject16,
		kObjectHandleBathroom,
		kObjectHandleInsideBathroom,
		kObjectKitchen,
		kObject20,							// 20
		kObject21,
		kObject22,
		kObjectGreenSleepingCar,
		kObjectRedSleepingCar,
		kObject25,							// 25
		kObjectHandleOutsideLeft,
		kObjectHandleOutsideRight,
		kObject28,
		kObject29,
		kObject30,							// 30
		kObject31,
		kObjectCompartmentA,
		kObjectCompartmentB,
		kObjectCompartmentC,
		kObjectCompartmentD,			 	// 35
		kObjectCompartmentE,
		kObjectCompartmentF,
		kObjectCompartmentG,
		kObjectCompartmentH,
		kObject40,						    // 40
		kObject41,
		kObject42,
		kObject43,
		kObject44,
		kObject45,							// 45
		kObject46,
		kObject47,
		kObject48,
		kObject49,
		kObject50,							// 50
		kObject51,
		kObject52,
		kObject53,
		kObject54,
		kObjectRestaurantCar = 55,			// 55
		kObject56,
		kObject57,
		kObject58,
		kObject59,
		kObject60,							// 60
		kObject61,
		kObject62,
		kObject63,
		kObject64,
		kObject65,							// 65
		kObject66,
		kObject67,
		kObject68,
		kObject69,
		kObject70,							// 70
		kObject71,
		kObject72,
		kObject73,
		kObject74,
		kObjectCompartmentKronos,			// 75
		kObject76,
		kObject77,
		kObject78,
		kObject79,
		kObject80,							// 80
		kObject81,
		kObject82,
		kObject83,
		kObject84,
		kObject85,							// 85
		kObject86,
		kObject87,
		kObject88,
		kObject89,
		kObject90,							// 90
		kObject91,
		kObject92,
		kObject93,
		kObject94,
		kObject95,							// 95
		kObject96,
		kObject97,
		kObject98,
		kObject99,
		kObject100,							// 100
		kObject101,
		kObject102,
		kObject103,
		kObject104,
		kObject105,							// 105
		kObject106,
		kObject107,
		kObject108,
		kObject109,
		kObject110,							// 110
		kObject111,
		kObject112,
		kObject113,
		kObject114,
		kObject115,							// 115
		kObject116,
		kObject117,
		kObject118,
		kObject119,
		kObject120,							// 120
		kObject121,
		kObject122,
		kObject123,
		kObject124,
		kObject125,							// 125
		kObject126,
		kObject127,
		kObject128
	};

	struct Object {
		SavePoints::EntityIndex entity;
		byte location;
		byte cursor;
		byte field_3;
		byte field_4;

		Object() {
			entity = SavePoints::kNone;
			location = 0;
			cursor = 10;
			field_3 = 9;
			field_4 = 0;
		}
	};
	
	Objects(LastExpressEngine *engine);

	const Object get(ObjectIndex index);
	void update(ObjectIndex index, SavePoints::EntityIndex entity, byte location, byte cursor, byte field_3);
	void updateField4(ObjectIndex index, byte value);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &ser);

private:
	LastExpressEngine* _engine;

	Object _objects[128];
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_OBJECT_H
