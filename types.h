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

#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "datatypes.h"

typedef struct
{
    uint32_t low, high;
} Filetime;

typedef struct
{
    uint32_t version;						// 7 or 8.
    uint32_t saveNumber;					// Counter storing the number of saves made.
    char *playerName;						// Name of the player.
    uint32_t level;							// Level of the player.
    char *playerLocation;					// Location of the player.
    char *gameDate;							// Date of the game at the time of saving.
    char *raceEditorID;						// A string that describes the player in the race editor, somehow.

    uint16_t unknown1;
    uint32_t unknown2, unknown3;

    Filetime filetime;

    uint32_t shotWidth, shotHeight;			// Dimensions of the screenshot.
} Header;

typedef struct
{
    uint8_t pluginCount;
    char **plugins;							// plugins[pluginCount]
} PluginInfo;

typedef struct
{
    uint32_t formIDArrayCount, unknownTable3Offset, globalDataTable1Offset,
    globalDataTable2Offset, changeFormsOffset, globalDataTable3Offset,
    globalDataTable1Count, globalDataTable2Count, globalDataTable3Count,
    changeFormCount, unused[15];
} FileLocationTable;

typedef struct
{
    uint32_t type, length;
    uint8_t *data;							// data[length]
} GlobalData;

typedef struct
{
    uint8_t byte0, byte1, byte2;
} RefID;

typedef struct
{
    RefID formID;
    uint32_t changeFlags;
    uint8_t type;
    uint8_t version;
    void *length1, *length2;
    uint8_t *data;							// data[*length1];
} ChangeForm;

/*typedef struct
{
    uint32_t count;
    wchar_t **unknown;						// unknown[count]
} Unknown3Table;*/

typedef struct
{
    FILE *file;								// File.
    char magic[14];							// Magic constant byte set, should be TESV_SAVEGAME.
    uint32_t headerSize;					// Size of the header.
    Header header;
    uint8_t *screenshotData; 				// Bytes the screenshot is composed of.
    uint8_t formVersion;					// Depends on the version of Skyrim.

    uint32_t pluginInfoSize;
    PluginInfo pluginInfo;

    FileLocationTable fileLocationTable;	// That must be used by developers to jump quickly to relevant datas.

    struct
    {
    	MiscStats *miscStats;
    } globalDatas;

    ChangeForm *changeForms;				// changeForms[fileLocationTable.changeFormCount]

    uint32_t formIDArrayCount;
    uint32_t *formIDArray;					// formIDArray[formIDArrayCount]

    /*uint32_t unknown2TableCount;
    uint32_t *unknown2Table;				// unknown2Table[unknown2TableCount]

    uint32_t unknown3TableSize;
    Unknown3Table unknown3Table;*/
} TESVSaveFile;

#endif
