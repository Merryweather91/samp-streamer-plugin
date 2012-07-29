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

#include "player.h"

#include "core.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <Eigen/Core>

#include <bitset>

Player::Player(int playerID) : playerID(playerID)
{
	activeCheckpoint = 0;
	activeRaceCheckpoint = 0;
	enabledItems.set();
	interiorID = 0;
	position.setZero();
	updateWhenIdle = false;
	visibleCell = SharedCell(new Cell());
	visibleCheckpoint = 0;
	visibleRaceCheckpoint = 0;
	visibleObjects = core->getStreamer()->getVisibleItems(STREAMER_TYPE_OBJECT);
	visibleTextLabels = core->getStreamer()->getVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL);
	worldID = 0;
}
