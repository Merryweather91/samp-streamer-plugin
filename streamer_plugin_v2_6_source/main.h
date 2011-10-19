/*
    SA-MP Streamer Plugin v2.6
    Copyright © 2011 Incognito

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


#define PLUGIN_VERSION "2.6"

#define STREAMER_TYPE_OBJECT (0)
#define STREAMER_TYPE_PICKUP (1)
#define STREAMER_TYPE_CP (2)
#define STREAMER_TYPE_RACE_CP (3)
#define STREAMER_TYPE_MAP_ICON (4)
#define STREAMER_TYPE_3D_TEXT_LABEL (5)
#define STREAMER_TYPE_AREA (6)

#define STREAMER_AREA_TYPE_CIRCLE (0)
#define STREAMER_AREA_TYPE_RECTANGLE (1)
#define STREAMER_AREA_TYPE_SPHERE (2)
#define STREAMER_AREA_TYPE_CUBE (3)
#define STREAMER_AREA_TYPE_POLYGON (4)

#define BOOST_CHRONO_HEADER_ONLY

#include <bitset>
#include <cmath>
#include <cstdarg>
#include <cstring>
#include <ctime>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "Libraries/boost/chrono.hpp"
#include "Libraries/boost/geometry.hpp"
#include "Libraries/boost/geometry/geometries/geometries.hpp"
#include "Libraries/boost/intrusive_ptr.hpp"
#include "Libraries/boost/scoped_ptr.hpp"
#include "Libraries/boost/tuple/tuple.hpp"
#include "Libraries/boost/unordered_map.hpp"
#include "Libraries/boost/unordered_set.hpp"
#include "Libraries/boost/variant.hpp"
#include "Libraries/Eigen/Core"
#include "Libraries/sampgdk/sampgdk.h"

#include "Source/Core.h"

extern logprintf_t logprintf;
