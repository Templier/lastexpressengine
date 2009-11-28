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

#ifndef LASTEXPRESS_SAVEPOINT_H
#define LASTEXPRESS_SAVEPOINT_H

#include "common/array.h"
#include "common/func.h"

/*
	Savepoint format
	----------------

	Save point: max: 127 - FIFO list (ie. goes back and overwrites first save point when full)
		uint32 {4}      - index of function pointer inside savePointFunctions array
		uint32 {4}      - action
		uint32 {4}      - time
		uint32 {4}      - 0 or 1 ?

	?? array: 16 bytes
		uint32 {4}		- ??
		uint32 {4}		- ??
		uint32 {4}		- ??
		uint32 {4}		- function pointer to ??

*/

#include "common/list.h"
#include "common/serializer.h"

namespace LastExpress {

class LastExpressEngine;

class SavePoints : Common::Serializable {
public:
	enum EntityIndex {
		kEntityNone,
		kEntityAnna,
		kEntityAugust,
		kEntityMertens,
		kEntityCoudert,
		kEntityPascale,				// 5
		kEntityServers0,
		kEntityServers1,
		kEntityCooks,
		kEntityVerges,
		kEntityTatiana,				// 10
		kEntityVassili,
		kEntityAlexei,
		kEntityAbbot,
		kEntityMilos,
		kEntityVesna,				// 15
		kEntityIvo,
		kEntitySalko,
		kEntityKronos,
		kEntityKahina,
		kEntityFrancois,			// 20
		kEntityMmeBoutarel,
		kEntityBoutarel,
		kEntityRebecca,
		kEntitySophie,
		kEntityMahmud,				// 25
		kEntityYasmin,
		kEntityHadija,
		kEntityAlouan,
		kEntityGendarmes,
		kEntityMax,					// 30
		kEntityChapters,
		kEntityTrain,
		kEntityTables0,
		kEntityTables1,
		kEntityTables2,				// 35
		kEntityTables3,
		kEntityTables4,
		kEntityTables5,
		kEntity39
	};

	enum ActionIndex {
		kActionNone = 0,
		kAction3 = 3,
		kAction8 = 8,
		kAction9 = 9,
		kActionDefault = 12,
		kAction17 = 17,
		kAction18 = 18,

		// Entity-specific actions
		kAction101824388 = 101824388,	// Pascale
		kAction124190740 = 124190740,	// Vesna
		kAction136059947 = 136059947,	// Pascale
		kAction154005632 = 154005632,	// Coudert
		kAction157026693 = 157026693,	// Coudert
		kAction157691176 = 157691176,	// Milos
		kAction158610240 = 158610240,
		kAction158617345 = 158617345,	// Verges
		kAction167854368 = 167854368,	// Verges
		kAction167992577 = 167992577,
		kAction168187490 = 168187490,	// Verges
		kAction168254872 = 168254872,	// Coudert
		kAction168255788 = 168255788,	// Verges
		kAction168646401 = 168646401,
		kAction169300225 = 169300225,		
		kAction169557824 = 169557824,	// Coudert
		kAction169633856 = 169633856,	// Mertens
		kAction169773228 = 169773228,
		kAction170483072 = 170483072,	// Mahmud
		kAction171394341 = 171394341,	// Coudert / Mertens		
		kAction171843264 = 171843264,	// Chapters
		kAction185671840 = 185671840,	// Coudert
		kAction185737168 = 185737168,	// Coudert
		kAction188570113 = 188570113,	// Coudert
		kAction188635520 = 188635520,	// Mertens
		kAction188893625 = 188893625,	// Servers 0
		kAction189026624 = 189026624,	// Coudert
		kAction189688608 = 189688608,	// Servers 1
		kAction189750912 = 189750912,	// Coudert
		kAction190082817 = 190082817,	// Mertens
		kAction190346110 = 190346110,
		kAction190605184 = 190605184,	// Pascale
		kAction191001984 = 191001984,	
		kAction191070912 = 191070912,	// Train
		kAction191198209 = 191198209, 	// Tatiana
		kAction191337656 = 191337656,	// Verges
		kAction191350523 = 191350523,	// Train
		kAction191604416 = 191604416,	// Pascale
		kAction192637492 = 192637492,
		kAction201431954 = 201431954,	// Coudert / Mertens / Verges
		kAction201959744 = 201959744,
		kAction202613084 = 202613084,	// Train
		kAction202621266 = 202621266,
		kAction202884544 = 202884544,
		kAction203073664 = 203073664,	// Abbot
		kAction203078272 = 203078272,
		kAction203339360 = 203339360,	// Train
		kAction203419131 = 203419131,	// Train
		kAction203520448 = 203520448, 	// Boutarel
		kAction203863200 = 203863200,	// Train
		kAction204379649 = 204379649,	// Mertens
		kAction204704037 = 204704037,	// Servers 0
		kAction205033696 = 205033696,	// Coudert
		kAction205034665 = 205034665,
		kAction205294778 = 205294778,
		kAction207330561 = 207330561,	// Servers 0
		kAction207769280 = 207769280,	// Pascale
		kAction208228224 = 208228224,	// Milos
		kAction218128129 = 218128129,	// Servers 0
		kAction218586752 = 218586752,	// Servers 0
		kAction218983616 = 218983616,	// Servers 0
		kAction219377792 = 219377792,	// Servers 1
		kAction222746496 = 222746496,	// Train
		kAction223002560 = 223002560,	// Servers 1
		kAction223262556 = 223262556,	// Pascale
		kAction223712416 = 223712416,	// Servers 0
		kAction224122407 = 224122407,	// Mertens
		kAction224253538 = 224253538,	// Rebecca
		kAction224309120 = 224309120,
		kAction225056224 = 225056224,	// Train
		kAction225358684 = 225358684,
		kAction225367984 = 225367984,
		kAction226031488 = 226031488,	// Coudert / Verges		
		kAction236237423 = 236237423,	// Servers 1
		kAction237485916 = 237485916,	// Servers 0
		kAction237889408 = 237889408,	// Boutarel
		kAction238732837 = 238732837,	// Mertens
		kAction238936000 = 238936000,	// Anna
		kAction239072064 = 239072064,	// Pascale
		kAction242526416 = 242526416,	// Mme Boutarel
		kAction252568704 = 252568704,	// Servers 0
		kAction256200848 = 256200848,	// Servers 1
		kAction257489762 = 257489762,	// Pascale
		kAction258136010 = 258136010,	// Servers 1
		kAction269436673 = 269436673,	// Mertens
		kAction269479296 = 269479296,	// Pascale
		kAction269485588 = 269485588,	// Servers 1
		kAction269624833 = 269624833,	// Mertens
		kAction270068760 = 270068760,	// Servers 0
		kAction270410280 = 270410280, 	// Servers 0
		kAction270751616 = 270751616,
		kAction272177921 = 272177921,
		kAction286403504 = 286403504,	// Servers 0
		kAction286534136 = 286534136,	// Servers 0
		kAction291662081 = 291662081,	// Anna
		kAction291721418 = 291721418,	// Servers 1
		kAction292048641 = 292048641,	// Coudert
		kAction292758554 = 292758554,	// Servers 0
		kAction302203328 = 302203328,	// Servers 1
		kAction302614416 = 302614416,	// Mertens
		kAction302996448 = 302996448,	// Servers 1
		kAction303343617 = 303343617,	// Mertens
		kAction304061224 = 304061224,	// Servers 0
		kAction326144276 = 326144276,	// Servers 1
		kAction326348944 = 326348944,	// Coudert
		kAction337548856 = 337548856,	// Servers 0
		kAction338494260 = 338494260,	// Train
		kAction339669520 = 339669520,	// Coudert / Verges		
		kAction352703104 = 352703104,	// Pascale
		kAction352768896 = 352768896,	// Pascale




		kActionEnd
	};

	struct SavePoint {
		EntityIndex entity1;
		ActionIndex action;
		EntityIndex entity2;
		uint32 field_C;

		SavePoint() {
			entity1 = kEntityNone;
			action = kActionNone;
			entity2 = kEntityNone;
			field_C = 0;
		}
	};	

	struct SavePointData {
		EntityIndex entity1;
		ActionIndex action;
		EntityIndex entity2;
		uint32 field_C;

		SavePointData() {
			entity1 = kEntityNone;
			action = kActionNone;
			entity2 = kEntityNone;
			field_C = 0;
		}
	};	

	typedef Common::Functor1<SavePoint*, void> Callback;

	SavePoints(LastExpressEngine *engine);
	~SavePoints();
	
	// Savepoints
	void push(EntityIndex entity2, EntityIndex entity1, ActionIndex action, uint32 field_C);
	void pushAll(EntityIndex entity, ActionIndex action, uint32 field_C);
	void process();
	void reset();

	// Data
	void addData(EntityIndex entity, ActionIndex action, uint32 field_C);

	// Callbacks
	void setCallback(EntityIndex index, Callback* callback);
	Callback *getCallback(EntityIndex entity);
	void call(EntityIndex entity2, EntityIndex entity1, ActionIndex action, int field_C);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &s);

private:
	static const uint32 _savePointsMaxSize = 128;

	LastExpressEngine *_engine;

	Common::List<SavePoint> _savepoints;	///< could be a queue, but we need to be able to iterate on the items
	Common::Array<SavePointData> _data;
	Callback* _callbacks[40];

	SavePoint pop();
	bool updateEntity(SavePoint point);
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SAVEPOINT_H
