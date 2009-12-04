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
		kAction2 = 2,
		kAction3 = 3,
		kAction5 = 5,
		kAction6 = 6,
		kAction8 = 8,
		kAction9 = 9,
		kActionDefault = 12,
		kAction17 = 17,
		kAction18 = 18,


		/////////////////////////////
		// Abbot
		/////////////////////////////
		kAction203073664 = 203073664,

		/////////////////////////////
		// Anna
		/////////////////////////////
		kAction238936000 = 238936000,
		kAction291662081 = 291662081,

		/////////////////////////////
		// Boutarel
		/////////////////////////////
		kAction203520448 = 203520448,
		kAction237889408 = 237889408,

		/////////////////////////////
		// Chapters
		/////////////////////////////
		kAction171843264 = 171843264,

		/////////////////////////////
		// Coudert
		/////////////////////////////
		kAction154005632 = 154005632,
		kAction157026693 = 157026693,
		kAction168254872 = 168254872,
		kAction169557824 = 169557824,
		kAction171394341 = 171394341,	// Coudert / Mertens
		kAction185671840 = 185671840,
		kAction185737168 = 185737168,
		kAction188570113 = 188570113,
		kAction189026624 = 189026624,
		kAction189750912 = 189750912,
		kAction201431954 = 201431954,	// Coudert / Mertens / Verges
		kAction205033696 = 205033696,
		kAction226031488 = 226031488,	// Coudert / Verges	
		kAction292048641 = 292048641,
		kAction326348944 = 326348944,
		kAction339669520 = 339669520,	// Coudert / Verges

		/////////////////////////////
		// Mahmud
		/////////////////////////////
		kAction170483072 = 170483072,

		/////////////////////////////
		// Max
		/////////////////////////////
		kAction71277948  = 71277948,
		kAction158007856 = 158007856,
		kAction101687594 = 101687594,
		kAction122358304 = 122358304,
		kActionMaxFreeFromCage = 135204609,
		kAction156622016 = 156622016,

		/////////////////////////////
		// Mertens
		/////////////////////////////
		kAction169633856 = 169633856,
		kAction188635520 = 188635520,
		kAction190082817 = 190082817,
		kAction204379649 = 204379649,
		kAction224122407 = 224122407,
		kAction238732837 = 238732837,
		kAction269436673 = 269436673,
		kAction269624833 = 269624833,
		kAction302614416 = 302614416,
		kAction303343617 = 303343617,

		/////////////////////////////
		// Milos
		/////////////////////////////
		kAction157691176 = 157691176,
		kAction208228224 = 208228224,

		/////////////////////////////
		// Mme Boutarel
		/////////////////////////////
		kAction242526416 = 242526416,

		/////////////////////////////
		// Pascale
		/////////////////////////////
		kAction101824388 = 101824388,
		kAction136059947 = 136059947,
		kAction190605184 = 190605184,
		kAction191604416 = 191604416,
		kAction207769280 = 207769280,
		kAction223262556 = 223262556,
		kAction239072064 = 239072064,
		kAction257489762 = 257489762,
		kAction269479296 = 269479296,
		kAction352703104 = 352703104,
		kAction352768896 = 352768896,

		/////////////////////////////
		// Rebecca
		/////////////////////////////
		kAction224253538 = 224253538,

		/////////////////////////////
		// Servers 0
		/////////////////////////////
		kAction188893625 = 188893625,
		kAction204704037 = 204704037,
		kAction207330561 = 207330561,
		kAction218128129 = 218128129,
		kAction218586752 = 218586752,
		kAction218983616 = 218983616,
		kAction223712416 = 223712416,
		kAction237485916 = 237485916,
		kAction252568704 = 252568704,
		kAction270068760 = 270068760,
		kAction270410280 = 270410280,
		kAction286403504 = 286403504,
		kAction286534136 = 286534136,
		kAction292758554 = 292758554,
		kAction304061224 = 304061224,
		kAction337548856 = 337548856,

		/////////////////////////////
		// Servers 1
		/////////////////////////////
		kAction189688608 = 189688608,
		kAction219377792 = 219377792,
		kAction223002560 = 223002560,
		kAction236237423 = 236237423,
		kAction256200848 = 256200848,
		kAction258136010 = 258136010,
		kAction269485588 = 269485588,
		kAction291721418 = 291721418,
		kAction302203328 = 302203328,
		kAction302996448 = 302996448,
		kAction326144276 = 326144276,

		/////////////////////////////
		// Sophie
		/////////////////////////////
		kAction70549068  = 70549068,
		kAction123668192 = 123668192,
		kAction125242096 = 125242096,
		kAction136654208 = 136654208,
		kAction259921280 = 259921280,
		kAction292775040 = 292775040,
	
		/////////////////////////////
		// Tables
		/////////////////////////////
		kAction103798704 = 103798704,
		kAction136455232 = 136455232,

		/////////////////////////////
		// Tatiana
		/////////////////////////////
		kAction191198209 = 191198209,

		/////////////////////////////
		// Train
		/////////////////////////////
		kAction191070912 = 191070912,
		kAction191350523 = 191350523,
		kAction202613084 = 202613084,
		kAction203339360 = 203339360,
		kAction203419131 = 203419131,
		kAction203863200 = 203863200,
		kAction222746496 = 222746496,
		kAction225056224 = 225056224,
		kAction338494260 = 338494260,

		/////////////////////////////
		// Verges
		/////////////////////////////
		kAction158617345 = 158617345,	
		kAction167854368 = 167854368,
		kAction168187490 = 168187490,
		kAction168255788 = 168255788,
		kAction191337656 = 191337656,
		
		/////////////////////////////
		// Vesna
		/////////////////////////////
		kAction124190740 = 124190740,
		
		/////////////////////////////
		// Misc
		/////////////////////////////
		kAction158610240 = 158610240,
		kAction167992577 = 167992577,
		kAction168646401 = 168646401,
		kAction169300225 = 169300225,
		kAction169773228 = 169773228,
		kAction190346110 = 190346110,
		kAction191001984 = 191001984,
		kAction192637492 = 192637492,
		kAction201959744 = 201959744,
		kAction202621266 = 202621266,
		kAction202884544 = 202884544,
		kAction203078272 = 203078272,
		kAction205034665 = 205034665,
		kAction205294778 = 205294778,
		kAction270751616 = 270751616,
		kAction272177921 = 272177921,
		kAction224309120 = 224309120,
		kAction225358684 = 225358684,
		kAction225367984 = 225367984,
		
		kActionEnd
	};


	struct SavePoint {
		EntityIndex entity1;
		ActionIndex action;
		EntityIndex entity2;
		union {
			uint32 intValue;
			char charValue[4];
		} param;

		SavePoint() {
			entity1 = kEntityNone;
			action = kActionNone;
			entity2 = kEntityNone;
			param.intValue = 0;
		}
	};	

	struct SavePointData {
		EntityIndex entity1;
		ActionIndex action;
		EntityIndex entity2;
		uint32 param;

		SavePointData() {
			entity1 = kEntityNone;
			action = kActionNone;
			entity2 = kEntityNone;
			param = 0;
		}
	};	

	typedef Common::Functor1<SavePoint*, void> Callback;

	SavePoints(LastExpressEngine *engine);
	~SavePoints();
	
	// Savepoints
	void push(EntityIndex entity2, EntityIndex entity1, ActionIndex action, uint32 param = 0);
	void pushAll(EntityIndex entity, ActionIndex action, uint32 param = 0);
	void process();
	void reset();

	// Data
	void addData(EntityIndex entity, ActionIndex action, uint32 param);

	// Callbacks
	void setCallback(EntityIndex index, Callback* callback);
	Callback *getCallback(EntityIndex entity);
	void call(EntityIndex entity2, EntityIndex entity1, ActionIndex action, uint32 param = 0);
	void call(EntityIndex entity2, EntityIndex entity1, ActionIndex action, char* param);

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
