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

#include "../main.h"
#include "Core.h"
#include "Grid.h"

Core * core;

Data::Global::Global()
{
	cellSize = 300.0f;
	cellDistance = (cellSize * 1.5f) * (cellSize * 1.5f);
	maxAreas = std::numeric_limits<int>::max();
	maxCheckpoints = std::numeric_limits<int>::max();
	maxMapIcons = std::numeric_limits<int>::max();
	maxObjects = std::numeric_limits<int>::max();
	maxPickups = std::numeric_limits<int>::max();
	maxRaceCheckpoints = std::numeric_limits<int>::max();
	maxTextLabels = std::numeric_limits<int>::max();
	tickCount = 0;
	tickRate = 50;
	visibleMapIcons = 100;
	visibleObjects = 399;
	visiblePickups = 2048;
	visibleTextLabels = 1024;
}

int Core::obtainCurrentTime()
{
	#ifdef WIN32
		return static_cast<int>(GetTickCount());
	#else
		struct timeval time;
		gettimeofday(&time, NULL);
		return static_cast<int>((time.tv_sec * 1000) + (time.tv_usec / 1000));
	#endif
}

