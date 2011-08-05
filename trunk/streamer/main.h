/*
    SA-MP Streamer Plugin v2.5.2
    Copyright © 2010 Incognito

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef _WIN32
	#include <windows.h>
#endif
#include <algorithm>
#include <bitset>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <set>
#include <stdarg.h>
#include <string>
#include <string.h>
#include <vector>
#include <boost/intrusive_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

#define PLUGIN_VERSION "2.5.2"

#define INVALID_GENERIC_ID (0xFFFF)
#define INVALID_PICKUP_ID (-1)
#define MAX_INTERIORS (20)
#define MAX_PLAYERS (500)
#define PLAYER_STATE_NONE (0)
#define PLAYER_STATE_WASTED (7)
#define STREAMER_TYPE_OBJECT (0)
#define STREAMER_TYPE_PICKUP (1)
#define STREAMER_TYPE_CP (2)
#define STREAMER_TYPE_RACE_CP (3)
#define STREAMER_TYPE_MAP_ICON (4)
#define STREAMER_TYPE_3D_TEXT_LABEL (5)
#define STREAMER_TYPE_AREA (6)

typedef void (* logprintf_t)(const char *, ...);

extern logprintf_t logprintf;
