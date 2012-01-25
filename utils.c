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

#include "tesvsavefile.h"

static bool everPrinted = false;

void die(const char *format, ...)
{
    va_list vargs;

    va_start(vargs, format);
    fprintf(stderr, "(\033[31mE\033[0m) ");
    vfprintf(stderr, format, vargs);
    fprintf(stderr, "\n");

    exit(EXIT_FAILURE);
}

void writePPM(const char *path, const uint8_t *bytes, uint32_t width, uint32_t height)
{
    FILE *f = fopen(path, "wb");

    if(!f)
        die("can't open %s for writing !", path);

    fprintf(f, "P6\n%u %u\n255\n", width, height);
    fwrite(bytes, 3, width * height, f);

    fclose(f);
}

void usage(const char *argv, int status)
{
    printf("usage: %s [options] file\n"
           "    -h\t\tShow help\n"
           "    -S FILE\tSave screenshot to FILE (PPM format)\n"
           "    -P\t\tShow informations about the player\n"
           "    -p\t\tList plugins\n"
           "    -s\t\tDump miscellaneous stats\n", argv);

    exit(status);
}

void dumpPlayerInfos(const TESVSaveFile *file)
{
    if(everPrinted)
        putchar('\n');

    printf("Player informations:\n  Name: %s\n  Level: %u\n  Race: %s\n  Location: %s\n",
           file->header.playerName, file->header.level, file->header.raceEditorID, file->header.playerLocation);

    everPrinted = true;
}

void dumpPlugins(const TESVSaveFile *file)
{
    size_t i = 0;

    if(everPrinted)
        putchar('\n');

    puts("Plugins:");

    for(; i < file->pluginInfo.pluginCount; ++i)
        printf("  %s\n", file->pluginInfo.plugins[i]);

    everPrinted = true;
}

void dumpStats(const TESVSaveFile *file)
{
    size_t i = 0;

    if(everPrinted)
        putchar('\n');

    for(; i < file->globalDatas.miscStats->count; ++i)
        printf("  %s: %d\n", file->globalDatas.miscStats->stats[i].name, file->globalDatas.miscStats->stats[i].value);

    everPrinted = true;
}
