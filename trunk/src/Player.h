/*
    SA-MP Streamer Plugin v2.6.1
    Copyright © 2012 Incognito

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

#ifndef PLAYER_H
#define PLAYER_H

#include "cell.h"
#include "common.h"
#include "identifier.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <Eigen/Core>

#include <bitset>

struct Player
{
	Player(int playerID);

	int activeCheckpoint;
	int activeRaceCheckpoint;
	int interiorID;
	int playerID;
	Eigen::Vector3f position;
	int references;
	bool updateWhenIdle;
	SharedCell visibleCell;
	int visibleCheckpoint;
	int visibleRaceCheckpoint;
	std::size_t visibleObjects;
	std::size_t visibleTextLabels;
	int worldID;

	boost::unordered_set<int> disabledAreas;
	boost::unordered_set<int> disabledCheckpoints;
	boost::unordered_set<int> disabledRaceCheckpoints;

	std::bitset<STREAMER_MAX_TYPES> enabledItems;

	boost::unordered_set<int> internalAreas;
	boost::unordered_map<int, int> internalMapIcons;
	boost::unordered_map<int, int> internalObjects;
	boost::unordered_map<int, int> internalTextLabels;

	Identifier mapIconIdentifier;
};

#endif
