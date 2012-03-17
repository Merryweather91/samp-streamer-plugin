/*
    SA-MP Streamer Plugin v2.6
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

#ifndef EVENTS_H
#define EVENTS_H

class Events
{
public:
	bool OnPlayerConnect(int playerid);
	bool OnPlayerDisconnect(int playerid, int reason);
	bool OnPlayerPickUpPickup(int playerid, int pickupid);
	bool OnPlayerEnterCheckpoint(int playerid);
	bool OnPlayerLeaveCheckpoint(int playerid);
	bool OnPlayerEnterRaceCheckpoint(int playerid);
	bool OnPlayerLeaveRaceCheckpoint(int playerid);

	inline void setInterface(AMX *amx)
	{
		interface = amx;
	}
private:
	AMX *interface;
};

#endif
