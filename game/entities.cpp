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

#include "lastexpress/game/entities.h"

// Data
#include "lastexpress/data/scene.h"
#include "lastexpress/data/sequence.h"

// Entities
#include "lastexpress/entities/entity.h"

#include "lastexpress/entities/abbot.h"
#include "lastexpress/entities/alexei.h"
#include "lastexpress/entities/alouan.h"
#include "lastexpress/entities/anna.h"
#include "lastexpress/entities/august.h"
#include "lastexpress/entities/boutarel.h"
#include "lastexpress/entities/chapters.h"
#include "lastexpress/entities/cooks.h"
#include "lastexpress/entities/coudert.h"
#include "lastexpress/entities/entity39.h"
#include "lastexpress/entities/francois.h"
#include "lastexpress/entities/gendarmes.h"
#include "lastexpress/entities/hadija.h"
#include "lastexpress/entities/ivo.h"
#include "lastexpress/entities/kahina.h"
#include "lastexpress/entities/kronos.h"
#include "lastexpress/entities/mahmud.h"
#include "lastexpress/entities/max.h"
#include "lastexpress/entities/mertens.h"
#include "lastexpress/entities/milos.h"
#include "lastexpress/entities/mmeboutarel.h"
#include "lastexpress/entities/pascale.h"
#include "lastexpress/entities/rebecca.h"
#include "lastexpress/entities/salko.h"
#include "lastexpress/entities/servers0.h"
#include "lastexpress/entities/servers1.h"
#include "lastexpress/entities/sophie.h"
#include "lastexpress/entities/tables.h"
#include "lastexpress/entities/tatiana.h"
#include "lastexpress/entities/train.h"
#include "lastexpress/entities/vassili.h"
#include "lastexpress/entities/verges.h"
#include "lastexpress/entities/vesna.h"
#include "lastexpress/entities/yasmin.h"

// Game
#include "lastexpress/game/logic.h"
#include "lastexpress/game/savepoint.h"
#include "lastexpress/game/scenes.h"
#include "lastexpress/game/sound.h"
#include "lastexpress/game/state.h"

#include "lastexpress/graphics.h"
#include "lastexpress/helpers.h"
#include "lastexpress/lastexpress.h"
#include "lastexpress/resource.h"

namespace LastExpress {

static const uint soundValues[32] = {
	16,	15,	14,	13,	12,
	11, 11,	10, 10,	9, 9, 8, 8,
	7, 7, 7, 6, 6, 6,
	5, 5, 5, 5,	4, 4, 4, 4,
	3, 3, 3, 3, 3
};

#define STORE_VALUE(data) ((uint)1 << (uint)data)

static const EntityPosition objectsPosition[9] = {kPositionNone,    kPosition_8200,
	                                              kPosition_7500, kPosition_6470,
	                                              kPosition_5790, kPosition_4840,
	                                              kPosition_4070, kPosition_3050,
	                                              kPosition_2740};

static const EntityPosition entityPositions[41] = {
            kPositionNone,    kPosition_851,  kPosition_1430, kPosition_2110, kPositionNone,
            kPosition_2410, kPosition_2980, kPosition_3450, kPosition_3760, kPosition_4100,
            kPosition_4680, kPosition_5140, kPosition_5440, kPosition_5810, kPosition_6410,
            kPosition_6850, kPosition_7160, kPosition_7510, kPosition_8514, kPositionNone,
            kPositionNone,    kPositionNone,    kPosition_2086, kPosition_2690, kPositionNone,
            kPosition_3110, kPosition_3390, kPosition_3890, kPosition_4460, kPosition_4770,
            kPosition_5090, kPosition_5610, kPosition_6160, kPosition_6460, kPosition_6800,
            kPosition_7320, kPosition_7870, kPosition_8160, kPosition_8500, kPosition_9020,
            kPosition_9269};

#define ADD_ENTITY(class) \
	_entities.push_back(new class(engine));

#define COMPUTE_SEQUENCE_NAME(sequenceTo, sequenceFrom) { \
	sequenceTo = sequenceFrom; \
	for (int seqIdx = 0; seqIdx < 8; seqIdx++) \
		sequenceTo.deleteLastChar(); \
	if (checkFields5(entityIndex, kCarGreenSleeping) || checkFields5(entityIndex, kCarGreenSleeping)) { \
		if (data->car < getData(kEntityNone)->car || (data->car == getData(kEntityNone)->car && data->position < getData(kEntityNone)->position)) \
			sequenceTo += "R.SEQ"; \
		else \
			sequenceTo += "F.SEQ"; \
	} else { \
		sequenceTo += ".SEQ"; \
	} \
}

//////////////////////////////////////////////////////////////////////////
// Entities
//////////////////////////////////////////////////////////////////////////
Entities::Entities(LastExpressEngine *engine) : _engine(engine) {
	_header = new EntityData();

	_entities.push_back(NULL);      // Header
	ADD_ENTITY(Anna);
	ADD_ENTITY(August);
	ADD_ENTITY(Mertens);
	ADD_ENTITY(Coudert);
	ADD_ENTITY(Pascale);
	ADD_ENTITY(Servers0);
	ADD_ENTITY(Servers1);
	ADD_ENTITY(Cooks);
	ADD_ENTITY(Verges);
	ADD_ENTITY(Tatiana);
	ADD_ENTITY(Vassili);
	ADD_ENTITY(Alexei);
	ADD_ENTITY(Abbot);
	ADD_ENTITY(Milos);
	ADD_ENTITY(Vesna);
	ADD_ENTITY(Ivo);
	ADD_ENTITY(Salko);
	ADD_ENTITY(Kronos);
	ADD_ENTITY(Kahina);
	ADD_ENTITY(Francois);
	ADD_ENTITY(MmeBoutarel);
	ADD_ENTITY(Boutarel);
	ADD_ENTITY(Rebecca);
	ADD_ENTITY(Sophie);
	ADD_ENTITY(Mahmud);
	ADD_ENTITY(Yasmin);
	ADD_ENTITY(Hadija);
	ADD_ENTITY(Alouan);
	ADD_ENTITY(Gendarmes);
	ADD_ENTITY(Max);
	ADD_ENTITY(Chapters);
	ADD_ENTITY(Train);

	// Special case for tables
	_entities.push_back(new Tables(engine, kEntityTables0));
	_entities.push_back(new Tables(engine, kEntityTables1));
	_entities.push_back(new Tables(engine, kEntityTables2));
	_entities.push_back(new Tables(engine, kEntityTables3));
	_entities.push_back(new Tables(engine, kEntityTables4));
	_entities.push_back(new Tables(engine, kEntityTables5));

	ADD_ENTITY(Entity39);

	// Init compartments & positions
	memset(&_compartments, 0, sizeof(_compartments));
	memset(&_compartments1, 0, sizeof(_compartments1));
	memset(&_positions, 0, sizeof(_positions));
}

Entities::~Entities() {
	delete _header;

	for (int i = 0; i < (int)_entities.size(); i++)
		delete _entities[i];

	// Zero passed pointers
	_engine = NULL;
}

//////////////////////////////////////////////////////////////////////////
// Accessors
//////////////////////////////////////////////////////////////////////////
Entity *Entities::get(EntityIndex entity) {
	assert((uint)entity < _entities.size());

	if (entity == kEntityNone)
		error("Cannot get entity for index == 0!");

	return _entities[entity];
}

EntityData::EntityCallData *Entities::getData(EntityIndex entity) const {
	assert((uint)entity < _entities.size());

	if (entity == kEntityNone)
		return _header->getCallData();

	return _entities[entity]->getData();
}

//////////////////////////////////////////////////////////////////////////
// Savegame
//////////////////////////////////////////////////////////////////////////
void Entities::saveLoadWithSerializer(Common::Serializer &ser) {
	_header->saveLoadWithSerializer(ser);
	for (uint i = 1; i < _entities.size(); i++)
		_entities[i]->saveLoadWithSerializer(ser);
}

//////////////////////////////////////////////////////////////////////////
// Setup
//////////////////////////////////////////////////////////////////////////
void Entities::setup(bool isFirstChapter, EntityIndex entity) {
	setupChapter(isFirstChapter ? kChapter1 : kChapterAll);

	getFlags()->flag_4 = false;
	if (!isFirstChapter && entity)
		getSavePoints()->call(kEntityNone, entity, kActionNone);

	if (!getFlags()->flag_4)
		getScenes()->loadScene(getState()->scene);
}

void Entities::setupChapter(ChapterIndex chapter) {
	if (chapter) {
		// Reset current call, inventory item & draw sequences
		for (uint i = 1; i < _entities.size(); i++) {
			getData((EntityIndex)i)->current_call = 0;
			getData((EntityIndex)i)->inventoryItem = kItemNone;

			prepareSequences((EntityIndex)i);
		}

		// Init compartments & positions
		memset(&_compartments, 0, sizeof(_compartments));
		memset(&_compartments1, 0, sizeof(_compartments1));
		memset(&_positions, 0, sizeof(_positions));

		getSound()->setupQueue(13);
	}

	// we skip the header when doing entity setup
	for (uint i = 1; i < _entities.size(); i++) {
		// Special case of chapters (prevents infinite loop as we will be called from Chapters functions when changing chapters)
		if (i == kEntityChapters && chapter >= 2)
			continue;

		_entities[i]->setup(chapter);
	}
}

void Entities::reset() {
	// Reset header
	delete _header;
	_header = new EntityData();

	for (uint i = 1; i < _entities.size(); i++)
		resetSequences((EntityIndex)i);

	getScenes()->resetDoorsAndClock();
}

//////////////////////////////////////////////////////////////////////////
// State & Sequences
//////////////////////////////////////////////////////////////////////////

EntityIndex Entities::canInteractWith(const Common::Point &point) const {
	if (!getFlags()->isGameRunning)
		return kEntityNone;

	EntityIndex index = kEntityNone;
	int location = 10000;

	// Check if there is an entity we can interact with
	for (uint i = 1; i < _entities.size(); i++) {

		// Skip entities with no current frame
		if (!getData((EntityIndex)i)->frame)
			continue;

		FrameInfo *info =  getData((EntityIndex)i)->frame->getInfo();

		// Skip frames with no data
		if (!info->dataOffset)
			continue;

		// Check the hotspot
		if (info->hotspot.contains(point)) {

			// If closer to us, update with its values
			if (location > info->location) {
				location = info->location;
				index = (EntityIndex)i;
			}
		}
	}

	// Check if we found an entity
	if (!index)
		return kEntityNone;

	// Check that there is an item to interact with
	if (!getData(index)->inventoryItem)
		return kEntityNone;

	return index;
}

void Entities::resetState(EntityIndex entityIndex) {
	getData(entityIndex)->current_call = 0;
	getData(entityIndex)->inventoryItem = kItemNone;

	if (getSound()->isBuffered(entityIndex))
		getSound()->removeFromQueue(entityIndex);

	prepareSequences(entityIndex);

	if (entityIndex == kEntity39)
		entityIndex = kEntityNone;

	if (entityIndex > kEntityChapters)
		return;

	// reset compartments and positions for this entity
	for (int i = 0; i < _positionsCount; i++)
		_positions[i] &= ~STORE_VALUE(entityIndex);

	for (int i = 0; i < _compartmentsCount; i++) {
		_compartments[i] &= ~STORE_VALUE(entityIndex);
		_compartments1[i] &= ~STORE_VALUE(entityIndex);
	}

	getLogic()->updateCursor();
}


void Entities::updateFields() const {
	if (!getFlags()->isGameRunning)
		return;

	for (int i = 0; i < (int)_entities.size(); i++) {

		if (!getSavePoints()->getCallback((EntityIndex)i))
			continue;

		EntityData::EntityCallData *data = getData((EntityIndex)i);
		switch (data->direction) {
		default:
			break;

		case kDirectionUp:
		case kDirectionDown:	// Replaces calls to CheckFields8
			if (data->direction != kDirectionUp || (data->position + data->field_4A3 * 10) >= 10000)
			{
				if (data->direction == kDirectionDown) {
					if (data->position > data->field_4A3 * 10)
						data->position = (EntityPosition)(data->position - data->field_4A3 * 10);
				}
			} else {
				data->position = (EntityPosition)(data->position + data->field_4A3 * 10);
			}
			break;

		case kDirectionLeft:
			data->currentFrame2 += 1;
			break;

		case kDirectionRight:
			data->field_4A1 += 9;
			break;

		case kDirectionSwitch:
			if (data->direction2 == kDirectionRight)
				data->field_4A1 += 9;
			break;

		}
	}
}

void Entities::updateEntity(EntityIndex entityIndex) const {
	Sequence *sequence = NULL;
	int16 *currentFrame = NULL;
	bool found = false;

	if (getData(entityIndex)->direction == kDirectionSwitch) {
		sequence = getData(entityIndex)->sequence3;
		currentFrame = &getData(entityIndex)->currentFrame3;
	} else {
		sequence = getData(entityIndex)->sequence2;
		currentFrame = &getData(entityIndex)->currentFrame2;
	}

	if (!sequence)
		return;

	// Save current values
	int16 oldFrame = *currentFrame;
	int16 field_4A1 = getData(entityIndex)->field_4A1;

	do {
		// Check we do not get past the end
		if (*currentFrame >= (int)sequence->count() - 1)
			break;

		// Get the proper frame
		FrameInfo *info = sequence->getFrameInfo(*currentFrame);

		if (info->field_33 & 8) {
			found = true;
		} else {
			if (info->soundAction == 35)
				found = true;

			getData(entityIndex)->field_4A1 += info->field_30;

			// Progress to the next frame
			++*currentFrame;
		}
	} while (!found);

	// Restore old values
	if (!found) {
		*currentFrame = oldFrame;
		getData(entityIndex)->field_4A1 = field_4A1;
	}
}

void Entities::updateSequences() {
	if (!getFlags()->isGameRunning)
		return;

	// Update the train clock & doors
	getScenes()->updateDoorsAndClock();

	//////////////////////////////////////////////////////////////////////////
	// First pass: Drawing
	//////////////////////////////////////////////////////////////////////////
	for (uint i = 1; i < _entities.size(); i++) {
		EntityIndex entityIndex = (EntityIndex)i;

		if (!getSavePoints()->getCallback(entityIndex))
			continue;

		EntityData::EntityCallData *data = getData(entityIndex);

		if (data->frame) {
			getScenes()->removeFromQueue(data->frame);
			SAFE_DELETE(data->frame);
		}

		if (data->frame1) {
			getScenes()->removeFromQueue(data->frame1);
			SAFE_DELETE(data->frame1);
		}

		if (data->direction == kDirectionSwitch) {

			// Clear sequence 2
			if (data->sequence2)
				SAFE_DELETE(data->sequence2);

			// Replace by sequence 3 if available
			if (data->sequence3) {
				data->sequence2 = data->sequence3;
				data->sequenceName2 = data->sequenceName3;

				data->sequence3 = NULL;
				data->sequenceName3 = "";
			}

			data->direction = data->direction2;
			data->currentFrame2 = -1;
			data->field_49B = 0;
		}

		// Draw sequences
		drawSequencesInternal(entityIndex, data->direction, false);
	}

	//////////////////////////////////////////////////////////////////////////
	// Second pass: Load sequences for next pass
	//////////////////////////////////////////////////////////////////////////
	for (uint i = 1; i < _entities.size(); i++) {
		EntityIndex entityIndex = (EntityIndex)i;

		if (!getSavePoints()->getCallback(entityIndex))
			continue;

		EntityData::EntityCallData *data = getData(entityIndex);
		int field30 = (data->direction == kDirectionLeft ? entityIndex + 35 : 15);

		if (data->sequenceName2 != "" && !data->sequence2) {
			data->sequence2 = new Sequence(getArchive(data->sequenceName2), field30);

			// If sequence 2 was loaded correctly, remove the copied name
			// otherwise, compute new name
			if (data->sequence2) {
				data->sequenceNameCopy = "";
			} else {
				Common::String sequenceName;

				// Left and down directions
				if (data->direction == kDirectionLeft || data->direction == kDirectionRight) {
					COMPUTE_SEQUENCE_NAME(sequenceName, data->sequenceName2);

					// Try loading the sequence
					data->sequence2 = new Sequence(getArchive(sequenceName), field30);
				}

				// Update sequence names
				data->sequenceNameCopy = (data->sequence2 ? "" : data->sequenceName2);
				data->sequenceName2 = (data->sequence2 ? sequenceName : "");
			}
		}

		// Update sequence 3
		if (data->sequenceName3 != "" && !data->sequence3) {

			if (data->car == getData(kEntityNone)->car)
				data->sequence3 = new Sequence(getArchive(data->sequenceName3), field30);

			if (!data->sequence3) {
				Common::String sequenceName;

				// Left and down directions
				if (data->direction2 == kDirectionLeft || data->direction2 == kDirectionRight) {
					COMPUTE_SEQUENCE_NAME(sequenceName, data->sequenceName3);

					// Try loading the sequence
					data->sequence3 = new Sequence(getArchive(sequenceName), field30);
				}

				// Update sequence names
				data->sequenceName3 = (data->sequence3 ? sequenceName : "");
			}
		}
	}
}

void Entities::resetSequences(EntityIndex entityIndex) const {

	// Reset direction
	if (getData(entityIndex)->direction == kDirectionSwitch) {
		getData(entityIndex)->direction = getData(entityIndex)->direction2;
		getData(entityIndex)->field_49B = 0;
		getData(entityIndex)->currentFrame2 = -1;
	}

	// FIXME: in the original engine, the sequence pointers might just be copies,
	// make sure we free the associated memory at some point
	getData(entityIndex)->frame = NULL;
	getData(entityIndex)->frame1 = NULL;

	SAFE_DELETE(getData(entityIndex)->sequence2);
	SAFE_DELETE(getData(entityIndex)->sequence3);
	SAFE_DELETE(getData(entityIndex)->sequence4);

	getData(entityIndex)->field_4A9 = 0;
	getData(entityIndex)->field_4AA = 0;

	strcpy((char*)&getData(entityIndex)->sequenceNameCopy, "");
	strcpy((char*)&getData(entityIndex)->sequenceName2, "");
	strcpy((char*)&getData(entityIndex)->sequenceName3, "");

	// Original engine resets flag to decompress data on the fly (we don't need to do that)
}

//////////////////////////////////////////////////////////////////////////
// Callbacks
//////////////////////////////////////////////////////////////////////////
void Entities::updateCallbacks() {
	if (!getFlags()->isGameRunning)
		return;

	getFlags()->flag_entities_0 = false;

	if (getFlags()->flag_entities_1) {
		executeCallbacks();
		getFlags()->flag_entities_0 = true;
	} else {
		getFlags()->flag_entities_1 = true;
		executeCallbacks();
		getFlags()->flag_entities_1 = false;
	}
}

void Entities::executeCallbacks() {
	for (uint i = 1; i < _entities.size(); i++) {
		if (getFlags()->flag_entities_0)
			break;

		if (getSavePoints()->getCallback((EntityIndex)i))
			processEntity((EntityIndex)i);
	}

	if (getFlags()->flag_entities_0)
		return;

	bool processed = true;
	do {
		for (int i = 1; i < (int)_entities.size(); i++) {
			if (getFlags()->flag_entities_0)
				break;

			if (getSavePoints()->getCallback((EntityIndex)i)) {
				if (getData((EntityIndex)i)->doProcessEntity) {
					processed = false;
					processEntity((EntityIndex)i);
				}
			}
		}
	} while (!processed);
}

//////////////////////////////////////////////////////////////////////////
// Processing
//////////////////////////////////////////////////////////////////////////
#define INCREMENT_DIRECTION_COUNTER() { \
	data->doProcessEntity = false; \
	if (data->direction == kDirectionRight || (data->direction == kDirectionSwitch && data->direction2 == kDirectionRight)) \
		data->field_4A1++; \
	}

void Entities::processEntity(EntityIndex entityIndex) {
	EntityData::EntityCallData *data = getData(entityIndex);
	bool dontClearQueue = false;

	data->doProcessEntity = false;

	if (data->car != getData(kEntityNone)->car && data->direction != kDirectionRight && data->direction != kDirectionSwitch) {

		if (data->position) {
			updatePosition(entityIndex, data->car2, data->position);
			data->car2 = kCarNone;
			data->positionId = 0;
		}

		getScenes()->removeAndRedraw(data->frame, false);
		getScenes()->removeAndRedraw(data->frame1, false);

		INCREMENT_DIRECTION_COUNTER();

		return;
	}

	if (data->frame1) {
		getScenes()->removeAndRedraw(data->frame1, false);

		if (data->frame && data->frame->getInfo()->subType != 3) {
			data->frame->getInfo()->subType = 0;
			getScenes()->setFlagDrawSequences();
		}
	}

	if (data->sequence4)
		SAFE_DELETE(data->sequence4);

	if (!data->frame || !data->direction) {
label_nosequence:
		if (!data->sequence2)
			drawSequencesInternal(entityIndex, data->direction, true);

		data->doProcessEntity = false;
		computeCurrentFrame2(entityIndex);

		if (getFlags()->flag_entities_0 || data->doProcessEntity)
			return;

		if (data->sequence2 && data->currentFrame2 != -1 && (data->currentFrame2 + 1) <= (int32)data->sequence2->count()) {
			processEntitySub(entityIndex, false, true);

			if (!getFlags()->flag_entities_0 && !data->doProcessEntity) {
				INCREMENT_DIRECTION_COUNTER();
				return;
			}
		} else {
			if (data->direction != kDirectionRight || data->field_4A1 <= 100) {

				if (data->direction == kDirectionRight && data->field_4A1 > 100) {
					getSavePoints()->push(kEntityNone, entityIndex, kActionExitCompartment);
					getSavePoints()->process();
				}

				if (getFlags()->flag_entities_0 || !data->doProcessEntity)
					return;

				if (data->position) {
					updatePosition(entityIndex, data->car2, (data->position != 0));
					data->car2 = kCarNone;
					data->positionId = 0;
				}

				INCREMENT_DIRECTION_COUNTER();
			}
		}

		return;
	}

	if (!data->sequence2)
		goto label_nosequence;

	if (data->frame->getInfo()->field_30 > data->field_49B || (data->direction == kDirectionLeft && data->sequence2->count() == 1)) {
		data->field_49B++;
		INCREMENT_DIRECTION_COUNTER();
		return;
	}

	if (data->frame->getInfo()->field_30 > data->field_49B && !data->frame->getInfo()->field_2F) {
		data->field_49B++;
		INCREMENT_DIRECTION_COUNTER();
		return;
	}

	if (data->frame->getInfo()->field_2F == 1)
		dontClearQueue = true;

	// Increment current frame
	data->currentFrame2++;

	if ((data->currentFrame2 + 1) > (int32)data->sequence2->count() || (data->field_4A9 && checkSequenceFromPosition(entityIndex))) {

		if (data->direction == kDirectionLeft) {
			data->currentFrame2 = 0;
		} else {
			dontClearQueue = true;
			processEntitySub2(entityIndex);

			if (getFlags()->flag_entities_0 || data->doProcessEntity)
				return;

			if (!data->sequence3) {
				processEntitySub3(entityIndex);
				data->doProcessEntity = false;
				return;
			}

			copySequenceData3To2(entityIndex);
		}

	}

	processEntitySub(entityIndex, dontClearQueue, false);

	if (!getFlags()->flag_entities_0 && !data->doProcessEntity)
		INCREMENT_DIRECTION_COUNTER();
}

void Entities::computeCurrentFrame2(EntityIndex entityIndex) {
	EntityData::EntityCallData *data = getData(entityIndex);

	if (!data->sequence2) {
		data->currentFrame2 = -1;
		return;
	}

	switch (data->direction) {
	default:
		break;

	case kDirectionNone:
	case kDirectionSwitch:
		data->currentFrame2 = -1;
		break;

	case kDirectionUp:
	case kDirectionDown: {
		loadSceneObject(scene, getState()->scene);

		if (scene.getHeader()->position > 40)
			break;

		switch (scene.getHeader()->position) {
		default:
		case 4:
		case 19:
		case 20:
		case 21:
		case 24:
			break;

		case 1:
		case 18:
		case 22:
		case 40:
			data->currentFrame2 = getCurrentFrame2(entityIndex, data->sequence2, kPositionNone, false);
			break;

		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			error("Entities::computeCurrentFrame2: not implemented!");
			break;

		case 23:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
			error("Entities::computeCurrentFrame2: not implemented!");
			break;
		}

		}
		break;


	case kDirectionLeft:
		if (data->currentFrame2 == -1 || data->currentFrame2 >= (int32)data->sequence2->count()) {
			data->currentFrame2 = 0;
			data->field_49B = 0;
		}
		break;

	case kDirectionRight:
		error("Entities::computeCurrentFrame2: not implemented!");
		break;
	}
}

int Entities::getCurrentFrame2(EntityIndex entity, Sequence *sequence, EntityPosition position, bool doProcessing) {

	if (doProcessing) {
		error("Entities::getCurrentFrame2: not implemented!");
	}

	//if (sequence->getFrameInfo()->position >= )
	warning("Entities::getCurrentFrame2: not implemented!");

	return -1;
}

void Entities::processEntitySub(EntityIndex entityIndex, bool dontClearQueue, bool dontPlaySound) {
	error("Entities::processEntitySub: not implemented!");
}

void Entities::processEntitySub2(EntityIndex entityIndex) {
	error("Entities::processEntitySub2: not implemented!");
}

void Entities::processEntitySub3(EntityIndex entityIndex) {
	error("Entities::processEntitySub2: not implemented!");
}

void Entities::copySequenceData3To2(EntityIndex entityIndex) {
	EntityData::EntityCallData *data = getData(entityIndex);

	if (data->sequence2)
		data->sequence4 = data->sequence2;

	data->sequence2 = data->sequence3;
	data->sequenceName2 = data->sequenceName3;
	data->field_4A9 = data->field_4AA;

	if (data->direction2)
		data->direction = data->direction2;

	// Clear sequence 3
	data->sequence3 = NULL;
	data->sequenceName3 = "";
	data->field_4AA = 0;
	data->direction2 = kDirectionNone;

	if (data->field_4A9) {
		computeCurrentFrame2(entityIndex);

		if (data->currentFrame2 == -1)
			data->currentFrame2 = 0;
	} else {
		data->currentFrame2 = data->currentFrame3;
		data->currentFrame3 = 0;

		if (data->currentFrame2 == -1)
			data->currentFrame2 = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
// Drawing
//////////////////////////////////////////////////////////////////////////
void Entities::drawSequenceLeft(EntityIndex index, const char* sequence) {
	drawSequenceInternal(index, sequence, kDirectionLeft);
}

void Entities::drawSequenceRight(EntityIndex index, const char* sequence) {
	drawSequenceInternal(index, sequence, kDirectionRight);
}

void Entities::prepareSequences(EntityIndex index) {
	debugC(8, kLastExpressDebugLogic, "Prepare sequences for entity %s", ENTITY_NAME(index));

	getScenes()->removeAndRedraw(getData(index)->frame, false);
	getScenes()->removeAndRedraw(getData(index)->frame1, false);

	if (getData(index)->sequence3) {
		SAFE_DELETE(getData(index)->sequence3);
		getData(index)->sequenceName3 = "";
		getData(index)->field_4AA = 0;
		getData(index)->direction2 = kDirectionNone;
	}

	if (getData(index)->sequence2) {
		SAFE_DELETE(getData(index)->sequence2);
		getData(index)->sequenceName2 = "";
		getData(index)->field_4A9 = 0;
		getData(index)->currentFrame2 = -1;
	}

	getData(index)->sequenceName = "";
	getData(index)->direction = kDirectionNone;
	getData(index)->doProcessEntity = true;
}

void Entities::drawSequenceInternal(EntityIndex index, const char* sequence, EntityDirection direction) {
	debugC(8, kLastExpressDebugLogic, "Drawing sequence %s for entity %s with direction %s", sequence, ENTITY_NAME(index), DIRECTION_NAME(direction));

	// Copy sequence name
	getData(index)->sequenceName = sequence;
	getData(index)->sequenceName.toUppercase();
	getData(index)->sequenceName += "-";

	// Reset fields
	getData(index)->field_49B = 0;
	getData(index)->currentFrame2 = 0;
	getData(index)->field_4A1 = 0;

	drawSequencesInternal(index, direction, true);
}

void Entities::drawSequencesInternal(EntityIndex entityIndex, EntityDirection direction, bool unknown) {

	EntityData::EntityCallData *data = getData(entityIndex);

	// Compute value for loading sequence depending on direction
	int16 field30 = (direction == kDirectionLeft ? entityIndex + 35 : 15);

	// First case: different car and not going right: cleanup and return
	if (data->car != getData(kEntityNone)->car && direction != kDirectionRight) {
		clearEntitySequenceData(data, direction);
		return;
	}

	data->direction2 = kDirectionNone;

	// Process sequence names
	Common::String sequenceName;
	Common::String sequenceName1;
	Common::String sequenceName2;
	Common::String sequenceName3;

	getSequenceName(entityIndex, direction, sequenceName1, sequenceName2);

	// No sequence 1: cleanup and return
	if (sequenceName1 == "") {
		clearEntitySequenceData(data, direction);
		return;
	}

	if (sequenceName1 == data->sequenceNameCopy) {
		data->direction = direction;
		return;
	}

	if (direction == kDirectionLeft || direction == kDirectionRight) {
		COMPUTE_SEQUENCE_NAME(sequenceName, sequenceName1);

		if (sequenceName3 == "")
			COMPUTE_SEQUENCE_NAME(sequenceName3, sequenceName2);
	}

	if (!data->frame) {
		data->direction = direction;

		if (sequenceName1 == data->sequenceName2) {
			if (sequenceName2 == "")
				return;

			drawSequencesInternalSub(entityIndex, sequenceName2, sequenceName3, field30, unknown);
			return;
		}

		SAFE_DELETE(data->sequence2);

		if (sequenceName1 != data->sequenceName3) {

			if (unknown) {

				if (data->car == getData(kEntityNone)->car)
					data->sequence2 = new Sequence(getArchive(sequenceName1), field30);

				if (data->sequence2) {
					data->sequenceName2 = sequenceName1;
					data->sequenceNameCopy = "";
				} else {
					if (sequenceName != "")
						data->sequence2 = new Sequence(getArchive(sequenceName), field30);

					data->sequenceName2 = (data->sequence2 ? sequenceName : "");
					data->sequenceNameCopy = (data->sequence2 ? "" : sequenceName1);
				}
			} else {
				data->sequenceName2 = sequenceName1;
			}

			if (sequenceName2 != "") {
				drawSequencesInternalSub(entityIndex, sequenceName2, sequenceName3, field30, unknown);
				return;
			}

			if (!data->sequence3) {
				if (sequenceName2 == "")
					return;

				drawSequencesInternalSub(entityIndex, sequenceName2, sequenceName3, field30, unknown);
				return;
			}

			SAFE_DELETE(data->sequence3);
		} else {
			data->sequence2 = data->sequence3;
			data->sequenceName2 = data->sequenceName3;
			data->sequence3 = NULL;
		}

		data->sequenceName3 = "";

		if (sequenceName2 == "")
			return;

		drawSequencesInternalSub(entityIndex, sequenceName2, sequenceName3, field30, unknown);
		return;
	}

	if (data->sequenceName2 == sequenceName1) {
		error("Entities::drawSequencesInternal: not implemented (2)!");
	} else {
		SAFE_DELETE(data->sequence3);

		data->sequence3 = copySequence(data->sequence2);

		data->sequenceName3 = data->sequenceName2;
		data->field_4AA = data->field_4A9;
		data->field_49B = data->frame->getInfo()->field_30;
		data->currentFrame2 = data->sequence2->count() - 1;
		data->direction = kDirectionSwitch;
		data->direction2 = direction;

		if ((direction != kDirectionUp && direction != kDirectionDown) || data->field_4AA || !data->currentFrame3) {
			data->currentFrame3 = 0;
		} else {
			data->currentFrame3 = getCurrentFrame2(entityIndex, data->sequence3, kPositionNone, false);

			if (data->currentFrame3 == -1)
				prepareSequences(entityIndex);
		}
	}
}

void Entities::drawSequencesInternalSub(EntityIndex entityIndex, Common::String sequenceName, Common::String sequenceName2, int16 field30, bool unknown) {
	EntityData::EntityCallData *data = getData(entityIndex);

	if (data->sequenceName3 == sequenceName)
		return;

	if (data->sequence3)
		SAFE_DELETE(data->sequence3);

	if (unknown) {

		if (data->car == getData(kEntityNone)->car)
			data->sequence3 = new Sequence(getArchive(sequenceName), field30);

		if (data->sequence3) {
			data->sequenceName3 = sequenceName;
		} else {
			if (sequenceName2 != "")
				data->sequence3 = new Sequence(getArchive(sequenceName2), field30);

			data->sequenceName3 = (data->sequence3 ? sequenceName2 : "");
		}
	} else {
		data->sequenceName3 = sequenceName;
	}
}

Sequence *Entities::copySequence(Sequence *sequence) {
	error("Entities::copySequence: not implemented!");
}

void Entities::getSequenceName(EntityIndex index, EntityDirection direction, Common::String &sequence1, Common::String &sequence2) const {
	EntityData::EntityCallData *data = getData(index);
	loadSceneObject(currentScene, getState()->scene);
	Position position = currentScene.getHeader()->position;

	// reset fields
	data->field_4A9 = 0;
	data->field_4AA = 0;

	switch (direction) {
	default:
		break;

	case kDirectionUp:
		switch (position) {
		default:
			error("Entities::getSequenceName: Invalid scene position %d (Direction UP)", position);
			break;

		case 1:
			if (data->position < kPosition_2587)
				sequence1 = Common::String::printf("%02d%01d-01u.seq", index, data->clothes);
			break;

		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			if (data->position >= kPosition_9270)
				break;

			if (data->position >= kPosition_8513) {
				sequence1 = Common::String::printf("%02d%01d-%02deu.seq", index, data->clothes, position);
			} else {
				sequence1 = Common::String::printf("%02d%01d-03u.seq", index, data->clothes);
				sequence2 = Common::String::printf("%02d%01d-%02deu.seq", index, data->clothes, position);
				data->field_4A9 = 1;
			}
			break;

		case 18:
			if (data->position >= kPosition_2436)
				sequence1 = Common::String::printf("%02d%01d-18u.seq", index, data->clothes);
			break;

		case 22:
			if (getData(kEntityNone)->position > data->position)
				sequence1 = Common::String::printf("%02d%01d-22u.seq", index, data->clothes);
			break;

		case 23:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
			if (getData(kEntityNone)->position <= data->position)
				break;

			if (data->position >= kPosition_2087) {
				sequence1 = Common::String::printf("%02d%01d-38u.seq", index, data->clothes);
				data->field_4A9 = 1;
			} else {
				sequence1 = Common::String::printf("%02d%01d-%02deu.seq", index, data->clothes, position);
				sequence2 = Common::String::printf("%02d%01d-38u.seq", index, data->clothes);
				data->field_4AA = 1;
			}
			break;

		case 40:
			if (getData(kEntityNone)->position > data->position)
				sequence1 = Common::String::printf("%02d%01d-40u.seq", index, data->clothes);
			break;
		}
		break;

	case kDirectionDown:
		switch (position) {
		default:
			error("Entities::getSequenceName: Invalid scene position %d (Direction DOWN)", position);
			break;

		case 1:
			if (getData(kEntityNone)->position < data->position)
				sequence1 = Common::String::printf("%02d%01d-01d.seq", index, data->clothes);
			break;

		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			if (getData(kEntityNone)->position >= data->position)
				break;

			if (data->position <= kPosition_8513) {
				sequence1 = Common::String::printf("%02d%01d-03d.seq", index, data->clothes);
				data->field_4A9 = 1;
			} else {
				sequence1 = Common::String::printf("%02d%01d-%02ded.seq", index, data->clothes, position);
				sequence2 = Common::String::printf("%02d%01d-03d.seq", index, data->clothes);
				data->field_4AA = 1;
			}
			break;

		case 18:
			if (getData(kEntityNone)->position < data->position)
				sequence1 = Common::String::printf("%02d%01d-18d.seq", index, data->clothes);
			break;

		case 22:
			if (data->position > kPosition_850)
				sequence1 = Common::String::printf("%02d%01d-22d.seq", index, data->clothes);
			break;

		case 23:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
			if (data->position <= kPosition_850)
				break;

			if (data->position <= kPosition_2087) {
				sequence1 = Common::String::printf("%02d%01d-%02ded.seq", index, data->clothes, position);
			} else {
				sequence1 = Common::String::printf("%02d%01d-38d.seq", index, data->clothes);
				sequence2 = Common::String::printf("%02d%01d-%02ded.seq", index, data->clothes, position);
				data->field_4A9 = 1;
			}
			break;

		case 40:
			if (getData(kEntityNone)->position > kPosition_8013)
				sequence1 = Common::String::printf("%02d%01d-40d.seq", index, data->clothes);
			break;
		}
		break;

	// First part of sequence is already set
	case kDirectionLeft:
	case kDirectionRight:
		sequence1 = Common::String::printf("%s%02d.seq", data->sequenceName.c_str(), position);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
/// Compartments
//////////////////////////////////////////////////////////////////////////
void Entities::enterCompartment(EntityIndex entity, ObjectIndex compartment, bool useFirstCompartments) {
	if (entity > kEntityChapters)
		return;

	switch (compartment) {
	default:
		// Return here so we do not update the compartments
		return;

	case kObjectCompartment1:
		updatePositionsEnter(entity, kCarGreenSleeping, 41, 51, 17, 38);
		break;

	case kObjectCompartment2:
		updatePositionsEnter(entity, kCarGreenSleeping, 42, 52, 15, 36);
		break;

	case kObjectCompartment3:
		updatePositionsEnter(entity, kCarGreenSleeping, 43, 53, 13, 34);
		break;

	case kObjectCompartment4:
		updatePositionsEnter(entity, kCarGreenSleeping, 44, 54, 11, 32);
		break;

	case kObjectCompartment5:
		updatePositionsEnter(entity, kCarGreenSleeping, 45, 55, 9, 30);
		break;

	case kObjectCompartment6:
		updatePositionsEnter(entity, kCarGreenSleeping, 46, 56, 7, 28);
		break;

	case kObjectCompartment7:
		updatePositionsEnter(entity, kCarGreenSleeping, 47, 57, 5, 26);
		break;

	case kObjectCompartment8:
		updatePositionsEnter(entity, kCarGreenSleeping, 48, 58, 3, 25);
		break;

	case kObjectCompartmentA:
		updatePositionsEnter(entity, kCarRedSleeping, 41, 51, 17, 38);
		break;

	case kObjectCompartmentB:
		updatePositionsEnter(entity, kCarRedSleeping, 42, 52, 15, 36);
		break;

	case kObjectCompartmentC:
		updatePositionsEnter(entity, kCarRedSleeping, 43, 53, 13, 34);
		break;

	case kObjectCompartmentD:
		updatePositionsEnter(entity, kCarRedSleeping, 44, 54, 11, 32);
		break;

	case kObjectCompartmentE:
		updatePositionsEnter(entity, kCarRedSleeping, 45, 55, 9, 30);
		break;

	case kObjectCompartmentF:
		updatePositionsEnter(entity, kCarRedSleeping, 46, 56, 7, 28);
		break;

	case kObjectCompartmentG:
		updatePositionsEnter(entity, kCarRedSleeping, 47, 57, 5, 26);
		break;

	case kObjectCompartmentH:
		updatePositionsEnter(entity, kCarRedSleeping, 48, 58, 3, 25);
		break;
	}

	// Update compartments
	int index = (compartment < 32 ? compartment - 1 : compartment - 24);
	if (index >= 16)
		error("Entities::exitCompartment: invalid compartment index!");

	if (useFirstCompartments)
		_compartments[index] |= STORE_VALUE(entity);
	else
		_compartments1[index] |= STORE_VALUE(entity);
}

void Entities::exitCompartment(EntityIndex entity, ObjectIndex compartment, bool useFirstCompartments) {
	if (entity > kEntityChapters)
		return;

	// TODO factorize in one line
	switch (compartment) {
	default:
		// Return here so we do not update the compartments
		return;

	case kObjectCompartment1:
		updatePositionsExit(entity, kCarGreenSleeping, 41, 51);
		break;

	case kObjectCompartment2:
		updatePositionsExit(entity, kCarGreenSleeping, 42, 52);
		break;

	case kObjectCompartment3:
		updatePositionsExit(entity, kCarGreenSleeping, 43, 53);
		break;

	case kObjectCompartment4:
		updatePositionsExit(entity, kCarGreenSleeping, 44, 54);
		break;

	case kObjectCompartment5:
		updatePositionsExit(entity, kCarGreenSleeping, 45, 55);
		break;

	case kObjectCompartment6:
		updatePositionsExit(entity, kCarGreenSleeping, 46, 56);
		break;

	case kObjectCompartment7:
		updatePositionsExit(entity, kCarGreenSleeping, 47, 57);
		break;

	case kObjectCompartment8:
		updatePositionsExit(entity, kCarGreenSleeping, 48, 58);
		break;

	case kObjectCompartmentA:
		updatePositionsExit(entity, kCarRedSleeping, 41, 51);
		break;

	case kObjectCompartmentB:
		updatePositionsExit(entity, kCarRedSleeping, 42, 52);
		break;

	case kObjectCompartmentC:
		updatePositionsExit(entity, kCarRedSleeping, 43, 53);
		break;

	case kObjectCompartmentD:
		updatePositionsExit(entity, kCarRedSleeping, 44, 54);
		break;

	case kObjectCompartmentE:
		updatePositionsExit(entity, kCarRedSleeping, 45, 55);
		break;

	case kObjectCompartmentF:
		updatePositionsExit(entity, kCarRedSleeping, 46, 56);
		break;

	case kObjectCompartmentG:
		updatePositionsExit(entity, kCarRedSleeping, 47, 57);
		break;

	case kObjectCompartmentH:
		updatePositionsExit(entity, kCarRedSleeping, 48, 58);
		break;
	}

	// Update compartments
	int index = (compartment < 32 ? compartment - 1 : compartment - 24);
	if (index >= 16)
		error("Entities::exitCompartment: invalid compartment index!");

	if (useFirstCompartments)
		_compartments[index] &= ~STORE_VALUE(entity);
	else
		_compartments1[index] &= ~STORE_VALUE(entity);
}

void Entities::updatePosition(EntityIndex entity, CarIndex car, Position position, bool processScene) {
	if (entity == kEntity39)
		entity = kEntityNone;

	if (entity > kEntityChapters)
		return;

	_positions[100 * car + position] &= ~STORE_VALUE(entity);

	if (processScene && (isPlayerPosition(car, position) || (car == kCarRestaurant && position == 57 && isPlayerPosition(kCarRestaurant, 50)))) {
		getSound()->excuseMe(entity);
		getScenes()->loadScene(getScenes()->processIndex(getState()->scene));
		getSound()->playSound(kEntityNone, "CAT1127A");
	} else {
		getLogic()->updateCursor();
	}
}

void Entities::updatePositionsEnter(EntityIndex entity, CarIndex car, Position position1, Position position2, Position position3, Position position4) {
	if (entity == kEntity39)
		entity = kEntityNone;

	if (entity > kEntityChapters)
		return;

	_positions[100 * car + position1] |= STORE_VALUE(entity);
	_positions[100 * car + position2] |= STORE_VALUE(entity);

	// FIXME: also checking two DWORD values that do not seem to updated anywhere...
	if (isPlayerPosition(car, position1) || isPlayerPosition(car, position2) || isPlayerPosition(car, position3) || isPlayerPosition(car, position4)) {
		getSound()->excuseMe(entity);
		getScenes()->loadScene(getScenes()->processIndex(getState()->scene));
		getSound()->playSound(kEntityNone, "CAT1127A");
	} else {
		getLogic()->updateCursor();
	}
}

void Entities::updatePositionsExit(EntityIndex entity, CarIndex car, Position position1, Position position2) {
	if (entity == kEntity39)
		entity = kEntityNone;

	if (entity > kEntityChapters)
		return;

	_positions[100 * car + position1] &= ~STORE_VALUE(entity);
	_positions[100 * car + position2] &= ~STORE_VALUE(entity);

	getLogic()->updateCursor();
}

//////////////////////////////////////////////////////////////////////////
// Misc (Sound, etc.)
//////////////////////////////////////////////////////////////////////////
uint Entities::getSoundValue(EntityIndex entity) const {
	if (entity == kEntityNone)
		return 16;

	if (getData(entity)->car != getData(kEntityNone)->car)
		return 0;

	// Compute sound value
	uint ret = 2;

	// Get default value if valid
	int index = abs(getData(entity)->position - getData(kEntityNone)->position) / 230;
	if (index < 32)
		ret = soundValues[index];

	if (getData(entity)->field_493 == kField493_2) {
		if (getData(entity)->car != kCarKronos
		&& !getEntities()->checkFields15()
		&& !getEntities()->checkFields16())
			return 0;

		return ret / 6;
	}

	switch (getData(entity)->car) {
	default:
		break;

	case kCarKronos:
		if (getEntities()->checkFields14(entity) != getEntities()->checkFields14(kEntityNone))
			ret >>= 1;
		break;

	case kCarGreenSleeping:
	case kCarRedSleeping:
		if (getEntities()->checkFields6(kEntityNone) && !getEntities()->checkFields14(entity))
			ret >>= 1;

		if (getData(kEntityNone)->field_493
		&& (getData(entity)->position != kPosition_1 || !getEntities()->checkFields9(kEntityNone, entity, 400)))
			ret >>=1;
		break;

	case kCarRestaurant:
		if (getEntities()->checkFields12(entity) == getEntities()->checkFields12(kEntityNone)
		&& (getEntities()->checkFields13(entity) != getEntities()->checkFields13(kEntityNone)))
			ret >>=1;
		else
			ret >>=2;
		break;
	}

	return ret;
}

void Entities::loadSceneFromEntityPosition(CarIndex car, EntityPosition entityPosition, bool alternate) const {

	// Determine position
	Position position = (alternate ? 1 : 40);
	do {
		if (entityPosition > entityPositions[position]) {
			if (alternate)
				break;

			// For default value, we ignore position 24
			if (position != 24)
				break;
		}

		alternate ? ++position : --position;

	} while (alternate ? position <= 18 : position >= 22);

	// For position outside bounds, use minimal value
	if ((alternate && position > 18) || (alternate && position < 22)) {
		getScenes()->loadSceneFromPosition(car, alternate ? 18 : 22);
		return;
	}

	// Load scene from position
	switch (position) {
	default:
		getScenes()->loadSceneFromPosition(car, (Position)(position + (alternate ? - 1 : 1)));
		break;

	// Alternate
	case 1:
		if (alternate) getScenes()->loadSceneFromPosition(car, 1);
		break;

	case 5:
		if (alternate) getScenes()->loadSceneFromPosition(car, 3);
		break;

	// Default
	case 23:
		if (!alternate) getScenes()->loadSceneFromPosition(car, 25);
		break;

	case 40:
		if (!alternate) getScenes()->loadSceneFromPosition(car, 40);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
//	Checks
//////////////////////////////////////////////////////////////////////////
bool Entities::checkSequence0(EntityIndex entity) const {
	return (getData(entity)->frame && (getData(entity)->frame->getInfo()->subType != 3));
}

bool Entities::compare(EntityIndex entity1, EntityIndex entity2) {
	EntityData::EntityCallData *data1 = getData(entity1);
	EntityData::EntityCallData *data2 = getData(entity2);

	if (data2->car != data1->car
	 || data1->car < kCarGreenSleeping
	 || data1->car > kCarRedSleeping)
		return false;

	error("Entities::compare: not implemented!");
}

bool Entities::checkEntity(EntityIndex entity, CarIndex car, EntityPosition position) {
	EntityData::EntityCallData *data = getData(entity);
	EntityDirection direction = kDirectionNone;
	int delta = 0;
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;

	if (position == kPosition_2000
	 && !isPlayerPosition(kCarGreenSleeping, 1)
	 && !isPlayerPosition(kCarRedSleeping, 2))
		 position = kPosition_1500;

	if (data->direction != kDirectionUp && data->direction != kDirectionDown)
		data->field_497 = 0;

	if (data->field_497) {
		data->field_497--;

		if (data->field_497 == 128)
			data->field_497 = 0;

		if ((data->field_497 & 127) != 8) {
			data->field_49B = 0;
			return false;
		}

		flag1 = true;

		if (data->field_497 & 128)
			flag2 = true;
	}

	if (data->car != car)
		goto label_process_entity;


	// Calculate delta
	delta = abs(data->position - position);
	if (delta < 100 || (position > kPosition_850 && position < kPosition_9270 && delta < 300))
		flag3 = true;

	if (!flag3) {

		if ((getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionType0) && data->direction == kDirectionUp)
		 || (getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionType1) && data->direction == kDirectionDown)) {
			 if (!checkPosition(position) && checkFields9(entity, kEntityNone, 250))
				 flag3 = true;
		}

		if (!flag3)
			goto label_process_entity;
	}

	if (getEntities()->checkSequence0(entity) && getEntities()->checkFields25(entity)) {
		if (!getEntities()->checkPosition(position)) {
			flag3 = false;
			position = (EntityPosition)(getData(kEntityNone)->position + 250 * (data->direction == kDirectionUp ? 1 : -1));
		}
	}

	if (!flag3) {
label_process_entity:

		// Calculate direction
		if (data->car < car)
			direction = kDirectionUp;
		else if (data->car > car)
			direction = kDirectionDown;
		else // same car
			direction = (data->position < position) ? kDirectionUp : kDirectionDown;

		if (!flag1) {
			if (data->direction == direction) {

				if (checkDistanceFromPosition(entity, kPosition_1500, 750) && entity != kEntityFrancois) {
					error("Entities::checkEntity: not implemented (1)!");
				} else {
					if (data->entity) {
						getSavePoints()->push(entity, data->entity, kAction16);
						data->entity = kEntityNone;
					}
				}

				if (checkSequence0(entity)) {
					error("Entities::checkEntity: not implemented (2)!");
				}

				if (data->direction == kDirectionUp) {
					if (data->position + data->field_4A3 < 10000)
						data->position = (EntityPosition)(data->position + data->field_4A3);
				} else {
					if (data->position > data->field_4A3)
						data->position = (EntityPosition)(data->position - data->field_4A3);
				}

				if (data->position < kPosition_9270 || data->direction != kDirectionUp) {

					if (getData(kEntityNone)->car == data->car) {
						getSound()->playSoundEvent(entity, 36);
						getSound()->playSoundEvent(entity, 37, 30);
					}

					data->car = (CarIndex)(data->car - 1);
					data->position = kPosition_9269;

					if (data->car == kCarKronos) {
						if (checkFields6(kEntityNone)) {
							getSound()->playSoundEvent(kEntityNone, 14);
							getSound()->excuseMe(entity, 0, 16);
							getScenes()->loadSceneFromPosition(kCarGreenSleeping, 1);
							getSound()->playSound(kEntityNone, "CAT1127A");
							getSound()->playSoundEvent(kEntityNone, 15);
						}
					}

					if (data->car < car || (data->car == car && data->position < position)) {
						data->car = car;
						data->position = position;
						data->direction = kDirectionNone;
						data->entity = kEntityNone;

						return true;
					}

					if (data->car == kCarKronos) {
						if (checkFields23(kEntityNone)) {
							getSound()->playSoundEvent(kEntityNone, 14);
							getSound()->excuseMe(entity, 0, 16);
							getScenes()->loadSceneFromPosition(kCarGreenSleeping, 62);
							getSound()->playSound(kEntityNone, "CAT1127A");
							getSound()->playSoundEvent(kEntityNone, 15);
						}
					}

					if (data->car == getData(kEntityNone)->car) {
						getSound()->playSoundEvent(entity, 36);
						getSound()->playSoundEvent(entity, 37, 30);
						goto label_checkentity_position;
					}

				} else {
					error("Entities::checkEntity: not implemented (4)!");
				}

label_checkentity_position:
				if (getData(kEntityNone)->car == data->car && !data->field_493) {
					error("Entities::checkEntity: not implemented! (5)");
				}

			} else {
				drawSequencesInternal(entity, direction, true);
			}

			return false;
		}

		//////////////////////////////////////////////////////////////////////////
		// Adjust positions

		// Direction Up
		if (direction == kDirectionUp) {
			if (data->position < (flag2 ? kPosition_8800 : kPosition_9250))
				data->position = (EntityPosition)(data->position + (flag2 ? kPosition_1200 : kPosition_750));

			if (data->car == car && data->position >= position) {
				data->position = position;
				data->direction = kDirectionNone;
				data->entity = kEntityNone;
				return true;
			}

			drawSequencesInternal(entity, direction, true);
			return false;
		}

		// Direction Down
		if (direction == kDirectionDown) {
			if (data->position > (flag2 ? kPosition_1200 : kPosition_750))
				data->position = (EntityPosition)(data->position - (flag2 ? kPosition_1200 : kPosition_750));

			if (data->car == car && data->position <= position) {
				data->position = position;
				data->direction = kDirectionNone;
				data->entity = kEntityNone;
				return true;
			}

			drawSequencesInternal(entity, direction, true);
			return false;
		}
	}

	data->position = position;
	if (data->direction == kDirectionUp || data->direction == kDirectionDown)
		data->direction = kDirectionNone;
	data->entity = kEntityNone;

	return true;
}

bool Entities::checkFields1(EntityIndex entity, CarIndex car, EntityPosition position) const {
	return (getData(entity)->position == position
		 && getData(entity)->field_493 == kField493_1
		 && getData(entity)->car == car);
}

bool Entities::checkFields2(ObjectIndex object) const {

	EntityPosition position = kPositionNone;
	CarIndex car = kCarNone;

	switch (object) {
	default:
		return false;

	case kObjectCompartment1:
	case kObjectCompartment2:
	case kObjectCompartment3:
	case kObjectCompartment4:
	case kObjectCompartment5:
	case kObjectCompartment6:
	case kObjectCompartment7:
	case kObjectCompartment8:
		position = objectsPosition[object];
		car = kCarGreenSleeping;
		if (checkFields1(kEntityNone, car, position))
			return false;
		break;

	case kObjectHandleBathroom:
	case kObjectHandleInsideBathroom:
	case kObjectKitchen:
	case kObject20:
	case kObject21:
	case kObject22:
		position = objectsPosition[object-17];
		car = kCarGreenSleeping;
		break;

	case kObjectCompartmentA:
	case kObjectCompartmentB:
	case kObjectCompartmentC:
	case kObjectCompartmentD:
	case kObjectCompartmentE:
	case kObjectCompartmentF:
	case kObjectCompartmentG:
	case kObjectCompartmentH:
		position = objectsPosition[object-32];
		car = kCarRedSleeping;
		if (checkFields1(kEntityNone, car, position))
			return false;
		break;

	case kObject48:
	case kObject49:
	case kObject50:
	case kObject51:
	case kObject52:
	case kObject53:
		position = objectsPosition[object-48];
		car = kCarRedSleeping;
		break;

	}

	uint index = 1;
	while (!checkFields1((EntityIndex)index, car, position) || index == kEntityVassili) {
		index++;
		if (index >= 40)
			return false;
	}

	return true;
}

bool Entities::checkFields3(EntityIndex entity) const {
	return (getData(entity)->car == kCarGreenSleeping
		 || getData(entity)->car == kCarRedSleeping)
		 && getData(entity)->field_493 == kField493_1;
}

bool Entities::isPlayerPosition(CarIndex car, Position position) const {
	loadSceneObject(scene, getState()->scene);

	return getData(kEntityNone)->car == car && scene.getHeader()->position == position;
}

bool Entities::checkFields5(EntityIndex entity, CarIndex car) const {
	return getData(entity)->car == car && getData(entity)->field_493 < kField493_2;
}

bool Entities::checkFields6(EntityIndex entity) const {
	return checkFields5(entity, kCarGreenSleeping) && getData(entity)->position < kPosition_850;
}

bool Entities::checkFields7(CarIndex car) const {
	return checkFields5(kEntityNone, car) && !getData(kEntityNone)->field_493 && !checkFields6(kEntityNone);
}

bool Entities::isDirectionUpOrDown(EntityIndex entity) const {
	return getData(entity)->direction == kDirectionUp || getData(entity)->direction == kDirectionDown;
}

bool Entities::checkFields9(EntityIndex entity1, EntityIndex entity2, int absValue) const {
	return getData(entity1)->car == getData(entity2)->car
	    && abs(getData(entity1)->position - getData(entity2)->position) <= absValue
		&& (getData(entity1)->field_493 != kField493_2 || getData(entity2)->field_493 != kField493_2);
}

bool Entities::checkFields10(EntityIndex entity) const {
	return getData(entity)->field_493 < kField493_3;
}

bool Entities::checkFields11() const {
	for (uint i = 1; i < _entities.size(); i++) {
		EntityIndex index = (EntityIndex)i;

		if ((!getData(index)->field_493 && checkFields12(index)) || checkFields13(index))
			return false;
	}

	return true;
}

bool Entities::checkFields12(EntityIndex entity) const {
	return checkFields5(entity, kCarRestaurant)
		&& getData(entity)->position >= kPosition_1540
		&& getData(entity)->position <= kPosition_3650;
}

bool Entities::checkFields13(EntityIndex entity) const {
	return checkFields5(entity, kCarRestaurant)
		&& getData(entity)->position >= kPosition_3650
		&& getData(entity)->position <= kPosition_5800;
}

bool Entities::checkFields14(EntityIndex entity) const {
	return checkFields5(entity, kCarKronos)
		&& getData(entity)->position >= kPosition_5500
		&& getData(entity)->position <= kPosition_7500;
}

bool Entities::checkFields15() const {
	return (getData(kEntityNone)->position == kPosition_7500 || getData(kEntityNone)->position == kPosition_8200)
		 && getData(kEntityNone)->field_493 == kField493_2
		 && getData(kEntityNone)->car == kCarGreenSleeping;
}

bool Entities::checkFields16() const {
	return (getData(kEntityNone)->position == kPosition_4070 || getData(kEntityNone)->position == kPosition_4840)
		 && getData(kEntityNone)->field_493 == kField493_2
		 && getData(kEntityNone)->car == kCarRedSleeping;
}

bool Entities::checkFields17(EntityIndex entity) const {
	return checkFields5(entity, kCarRestaurant) && getData(entity)->position > kPosition_5800;
}

bool Entities::checkFields18(CarIndex car, EntityPosition position) const {
	for (uint i = 1; i < _entities.size(); i++) {
		if (checkFields1((EntityIndex)i, car, position))
			return false;
	}
	return true;
}

bool Entities::checkFields19(EntityIndex entity, CarIndex car, EntityPosition position) const {

	if (getData(entity)->car != car ||  getData(entity)->field_493 != kField493_1)
		return false;

	EntityPosition entityPosition = getData(entity)->position;

	// Test values
	if (position == kPosition_4455) {
		if (entityPosition == kPosition_4070 || entityPosition == kPosition_4455 || entityPosition == kPosition_4840)
			return true;

		return false;
	}

	if (position == kPosition_6130) {
		if (entityPosition == kPosition_5790 || entityPosition == kPosition_6130 || entityPosition == kPosition_6470)
			return true;

		return false;
	}

	if (position != kPosition_7850
	 || (entityPosition != kPosition_7500 && entityPosition != kPosition_7850 && entityPosition != kPosition_8200))
		return false;

	return true;
}

bool Entities::checkFields20(EntityIndex entity) const {
	return checkFields5(entity, kCarBaggage)
		&& getData(entity)->position >= kPosition_4500
		&& getData(entity)->position <= kPosition_5500;
}

bool Entities::checkFields21(EntityIndex entity) const {
	return checkFields5(entity, kCarBaggage) && getData(entity)->position < kPosition_4500;
}

bool Entities::checkFields22(EntityIndex entity) const {
	return checkFields5(entity, kCarKronos)
		&& getData(entity)->position >= kPosition_3500
		&& getData(entity)->position <= kPosition_5500;
}

bool Entities::checkFields23(EntityIndex entity) const {
	return checkFields5(entity, kCarKronos) && getData(entity)->position > kPosition_7900;
}

bool Entities::checkDistanceFromPosition(EntityIndex entity, EntityPosition position, int distance) const {
	return distance >= abs(getData(entity)->position - position);
}

bool Entities::checkFields25(EntityIndex entity) const {
	if (getData(entity)->direction == kDirectionUp && getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionType1))
		return true;

	return (getData(entity)->direction == kDirectionDown && getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionType0));
}

bool Entities::checkPosition(EntityPosition position) const {
	Position position1 = 0;
	Position position2 = 0;

	switch (position) {
	default:
		return true;

	case kPosition_1500:
		position1 = 1;
		position2 = 23;
		break;

	case kPosition_2740:
		position1 = 3;
		position2 = 25;
		break;

	case kPosition_3050:
		position1 = 5;
		position2 = 26;
		break;

	case kPosition_4070:
		position1 = 7;
		position2 = 28;
		break;

	case kPosition_4840:
		position1 = 9;
		position2 = 30;
		break;

	case kPosition_5790:
		position1 = 11;
		position2 = 32;
		break;

	case kPosition_6470:
		position1 = 13;
		position2 = 34;
		break;

	case kPosition_7500:
		position1 = 15;
		position2 = 36;
		break;

	case kPosition_8200:
		position1 = 17;
		position2 = 38;
		break;
	}

	if (getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionType0) && entityPositions[position1] >= getEntityData(kEntityNone)->position)
		return true;
	else
		return (getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionType1) && entityPositions[position2] <= getEntityData(kEntityNone)->position);
}

bool Entities::checkSequenceFromPosition(EntityIndex entity) const {
	FrameInfo *info = getEntityData(entity)->sequence2->getFrameInfo(getEntityData(entity)->currentFrame2);

	if (getEntityData(entity)->direction == kDirectionUp)
		return (getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionType0)
			 && info->position + getEntityPositionFromCurrentPosition() > kPosition_8513);

	if (getEntityData(entity)->direction == kDirectionDown)
		return (getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionType1)
			 && info->position + getEntityPositionFromCurrentPosition() < kPosition_2087);

	return false;
}

EntityPosition Entities::getEntityPositionFromCurrentPosition() const {
	// Get the scene position first
	loadSceneObject(scene, getState()->scene);


	if (getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionType0))
		return (EntityPosition)(entityPositions[scene.getHeader()->position] - kPosition_1430);

	if (getScenes()->checkPosition(kSceneNone, SceneManager::kCheckPositionType1))
		return (EntityPosition)(entityPositions[scene.getHeader()->position] - kPosition_9020);

	return kPositionNone;
}

void Entities::clearEntitySequenceData(EntityData::EntityCallData * data, EntityDirection direction) {
	getScenes()->removeAndRedraw(data->frame, false);
	getScenes()->removeAndRedraw(data->frame1, false);

	if (data->sequence2)
		SAFE_DELETE(data->sequence2);

	if (data->sequence3)
		SAFE_DELETE(data->sequence3);

	data->sequenceName2 = "";
	data->sequenceName3 = "";

	data->field_4A9 = 0;
	data->field_4AA = 0;
	data->direction2 = kDirectionNone;

	data->currentFrame2 = -1;
	data->currentFrame3 = 0;

	data->direction = direction;
}

} // End of namespace LastExpress
