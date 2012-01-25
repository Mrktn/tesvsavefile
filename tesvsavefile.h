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

#ifndef TESV_SAVE_FILE_INCLUDED
#define TESV_SAVE_FILE_INCLUDED

#include <stdarg.h>
#include <string.h>

#include "types.h"

typedef int bool;

#define true 1
#define false 0

/* Utils */
void die(const char*, ...);
void writePPM(const char*, const uint8_t*, uint32_t, uint32_t);
void usage(const char*, int);
void dumpPlayerInfos(const TESVSaveFile*);
void dumpPlugins(const TESVSaveFile*);
void dumpStats(const TESVSaveFile*);

/* uint8 to global datas conversions */
MiscStats *mkMiscStats(const uint8_t*);

#endif
