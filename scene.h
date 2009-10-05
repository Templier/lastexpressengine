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

#ifndef LASTEXPRESS_SCENE_H
#define LASTEXPRESS_SCENE_H

/*
	Scene format (CDTRAIN.DAT)

	(text:00484750)
	header (24 bytes)
		char {8}   - entry name (null terminated)
		byte {1}	- 0xCD
		uint16 {2}	- number of scenes (for first entry - always 0 after?)
		uint32 {4}  - always null??
		byte {1}    - ?? 
		byte {1}    - ?? (see text:004067F0 - used as a switch value)
		byte {1}    - ??
		byte {1}    - ?? 
		byte {1}    - ?? 
		byte {1}    - ?? 
		byte {1}    - ?? 
		byte {1}    - ?? 
		byte {1}    - ?? 

	scene index : 0 - 2500 (max)
*/


namespace LastExpress {

class ResourceManager;

class Scene {
public:
	Scene(ResourceManager *resource);
	~Scene();

	bool load(int sceneIndex);

private:
	ResourceManager *_resource;
	

};

} // End of namespace LastExpress

#endif // LASTEXPRESS_SCENE_H