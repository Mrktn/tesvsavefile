/*  
 *  Copyright (c) 2012, Antoine Balestrat <merkil@savhon.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

 /*
* At the moment of writing this, the only fully-documented type is MiscStats, so I'll just wait for
* the hackers from uesp.net to document them a bit more.
*/

#ifndef DATATYPES_INCLUDED
#define DATATYPES_INCLUDED

typedef struct
{
	char *name;
	uint8_t category;
	int32_t value;
} MiscStat;

typedef struct
{
	uint32_t count;
	MiscStat *stats;						// stats[count]
} MiscStats;

/*typedef struct
{
	uint32_t unknown0;
	RefID unknown1;
	uint32_t unknown2, unknown3, unknown4, unknown5;
	RefID unknown6;
	uint32_t unknown7;
} PlayerLocation;

typedef struct
{
	void *count0;
	struct
	{
		RefID formID;
		uint16_t unknown;
	} *unknown0;							// unknown0[*count0]
	
	uint32_t count1;
	RefID *unknown1;						// unknown1[count1]
	
	void *count2;
	RefID *unknown2;						// unknown2[*count2]
} TES;

typedef struct
{
	RefID formID;
	float value;
} GlobalVariable;

typedef struct
{
	void *count;
	GlobalVariable *globals;				// globals[*count]
} GlobalVariables;

typedef struct
{
	
} CreatedObjects;*/

#endif
