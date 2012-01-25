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

#include <getopt.h>

#include "tesvsavefile.h"

void loadtesv(TESVSaveFile*, const char*);
void freetesv(TESVSaveFile*);

int main(int argc, char **argv)
{
    int c;
    bool infosPlayer = false, plugins = false, stats = false;
    char *outputPPM = NULL;
    TESVSaveFile file;

    while((c = getopt(argc, argv, "hPpsS:")) != -1)
    {
        switch(c)
        {
        case 'h':
        default:
            usage(*argv, EXIT_SUCCESS);
            break;

        case 'S':
            outputPPM = optarg;
            break;

        case 'P':
            infosPlayer = true;
            break;

        case 'p':
            plugins = true;
            break;

        case 's':
            stats = true;
            break;
        }
    }

    if(optind >= argc)
        usage(*argv, EXIT_FAILURE);

    while(optind < argc)
    {
        loadtesv(&file, argv[optind++]);

        if(outputPPM)
            writePPM(outputPPM, file.screenshotData, file.header.shotWidth, file.header.shotHeight);

        if(infosPlayer)
            dumpPlayerInfos(&file);

        if(plugins)
            dumpPlugins(&file);

        if(stats)
            dumpStats(&file);

        freetesv(&file);
    }

    return EXIT_SUCCESS;
}
