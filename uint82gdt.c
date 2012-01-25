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
* Functions that convert raw byte arrays to global data types.
*/

#include <string.h>

#include "tesvsavefile.h"

MiscStats *mkMiscStats(const uint8_t *data)
{
    size_t i = 0;
    MiscStats *miscStats = malloc(sizeof(MiscStats));

    miscStats->count = *((uint32_t*)data);
    data += 4;

    miscStats->stats = malloc(miscStats->count * sizeof(MiscStat));

    for(; i < miscStats->count; ++i)
    {
        uint16_t sz = *((uint16_t*)data);
        data += 2;

        miscStats->stats[i].name = strndup((char*)data, sz);
        data += sz;

        miscStats->stats[i].category = *data++;

        miscStats->stats[i].value = *((int32_t*)data);
        data += 4;
    }

    return miscStats;
}
