/*
 *  Copyright (c) 2012, Antoine Balestrat <antoine.balestrat@gmail.com>
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

#include "tesvsavefile.h"
#include "datatypes.h"

static void loadHeader(TESVSaveFile *savefile)
{
    uint16_t sz;
    Header *header = &savefile->header;

    fread(&header->version, 4, 1, savefile->file);

    if(header->version < 7 || header->version > 8)
        die("header version %d is not supported !", header->version);

    fread(&header->saveNumber, 4, 1, savefile->file);

    fread(&sz, 2, 1, savefile->file);
    header->playerName = calloc(1, sz + 1);
    fread(header->playerName, sz, 1, savefile->file);

    fread(&header->level, 4, 1, savefile->file);

    fread(&sz, 2, 1, savefile->file);
    header->playerLocation = calloc(1, sz + 1);
    fread(header->playerLocation, sz, 1, savefile->file);

    fread(&sz, 2, 1, savefile->file);
    header->gameDate = calloc(1, sz + 1);
    fread(header->gameDate, sz, 1, savefile->file);

    fread(&sz, 2, 1, savefile->file);
    header->raceEditorID = calloc(1, sz + 1);
    fread(header->raceEditorID, sz, 1, savefile->file);

    fread(&header->unknown1, 2, 1, savefile->file);
    fread(&header->unknown2, 4, 1, savefile->file);
    fread(&header->unknown3, 4, 1, savefile->file);

    fread(&header->filetime.low, 4, 1, savefile->file); // Need some doc : what's first, low or high ?
    fread(&header->filetime.high, 4, 1, savefile->file);

    fread(&header->shotWidth, 4, 1, savefile->file);
    fread(&header->shotHeight, 4, 1, savefile->file);
}

static void loadPluginInfo(TESVSaveFile *savefile)
{
    size_t i = 0;
    PluginInfo *pI = &savefile->pluginInfo;

    fread(&pI->pluginCount, 1, 1, savefile->file);

    pI->plugins = malloc(pI->pluginCount * sizeof(*pI->plugins));

    for(; i < pI->pluginCount; ++i)
    {
        uint16_t sz;

        fread(&sz, 2, 1, savefile->file);
        pI->plugins[i] = calloc(1, sz + 1);
        fread(pI->plugins[i], sz, 1, savefile->file);
    }
}

static void loadFileLocationTable(TESVSaveFile *savefile)
{
    FileLocationTable *flt = &savefile->fileLocationTable;

    fread(&flt->formIDArrayCount, 4, 1, savefile->file);
    fread(&flt->unknownTable3Offset, 4, 1, savefile->file);
    fread(&flt->globalDataTable1Offset, 4, 1, savefile->file);
    fread(&flt->globalDataTable2Offset, 4, 1, savefile->file);
    fread(&flt->changeFormsOffset, 4, 1, savefile->file);
    fread(&flt->globalDataTable3Offset, 4, 1, savefile->file);
    fread(&flt->globalDataTable1Count, 4, 1, savefile->file);
    fread(&flt->globalDataTable2Count, 4, 1, savefile->file);
    fread(&flt->globalDataTable3Count, 4, 1, savefile->file);
    fread(&flt->changeFormCount, 4, 1, savefile->file);
    fread(&flt->unused, 4, 15, savefile->file);
}

static void loadGlobalDataTable(TESVSaveFile *savefile, size_t sz)
{
    size_t i = 0;

    for(; i < sz; ++i)
    {
        uint32_t type, length;
        uint8_t *data;

        fread(&type, 4, 1, savefile->file);
        fread(&length, 4, 1, savefile->file);
        data = malloc(length);
        fread(data, 1, length, savefile->file);

        if(type == 0)
        {
            savefile->globalDatas.miscStats = mkMiscStats(data);
        }

        free(data);

        // TODO: add more cases when more data types are documented.
    }
}

void loadtesv(TESVSaveFile *savefile, const char *location)
{
    uint32_t shotSz = 0;

    savefile->file = fopen(location, "rb");

    if(!savefile->file)
        die("can't open %s for reading !", location);

    memset(savefile->magic, 0, sizeof(savefile->magic));
    fread(savefile->magic, 13, 1, savefile->file);

    if(strcmp(savefile->magic, "TESV_SAVEGAME"))
        die("not a TESV save file (magic is %s) !", savefile->magic);

    fread(&savefile->headerSize, 4, 1, savefile->file);

    loadHeader(savefile);

    shotSz = 3 * savefile->header.shotWidth * savefile->header.shotHeight;
    savefile->screenshotData = malloc(shotSz);

    fread(savefile->screenshotData, shotSz, 1, savefile->file);

    fread(&savefile->formVersion, 1, 1, savefile->file);
    fread(&savefile->pluginInfoSize, 4, 1, savefile->file);

    loadPluginInfo(savefile);
    loadFileLocationTable(savefile);

    loadGlobalDataTable(savefile, 24);
}

void freetesv(TESVSaveFile *savefile)
{
    size_t i = 0;
    MiscStats *ms = savefile->globalDatas.miscStats;

    fclose(savefile->file);

    free(savefile->header.playerName);
    free(savefile->header.playerLocation);
    free(savefile->header.gameDate);
    free(savefile->header.raceEditorID);

    for(; i < savefile->pluginInfo.pluginCount; ++i)
        free(savefile->pluginInfo.plugins[i]);

    free(savefile->pluginInfo.plugins);
    free(savefile->screenshotData);

    for(i = 0; i < ms->count; ++i)
        free(ms->stats[i].name);

    free(ms->stats);
    free(ms);

}
