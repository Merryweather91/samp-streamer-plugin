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

#include "Main.h"

bool Events::OnPlayerConnect(int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p == core->getData()->players.end())
		{
			Player player;
			player.activeCheckpoint = 0;
			player.activeRaceCheckpoint = 0;
			player.idleUpdate = false;
			player.interiorID = 0;
			player.playerID = playerid;
			player.position.setZero();
			player.visibleCell = SharedCell(new Cell());
			player.visibleCheckpoint = 0;
			player.visibleRaceCheckpoint = 0;
			player.visibleObjects = core->getStreamer()->getVisibleItems(STREAMER_TYPE_OBJECT);
			player.visibleTextLabels = core->getStreamer()->getVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL);
			player.worldID = 0;
			core->getData()->players.insert(std::make_pair(playerid, player));
		}
	}
	return true;
}

bool Events::OnPlayerDisconnect(int playerid, int reason)
{
	core->getData()->players.erase(playerid);
	return true;
}

bool Events::OnPlayerPickUpPickup(int playerid, int pickupid)
{
	for (boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.begin(); i != core->getStreamer()->internalPickups.end(); ++i)
	{
		if (i->second == pickupid)
		{
			boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.find(i->first);
			if (p != core->getData()->pickups.end())
			{
				if (p->second->amx != interface)
				{
					break;
				}
			}
			int pickupid = i->first;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerPickUpDynamicPickup", &index))
				{
					amx_Push(*a, pickupid);
					amx_Push(*a, playerid);
					amx_Exec(*a, NULL, index);
				}
			}
			break;
		}
	}
	return true;
}

bool Events::OnPlayerEnterCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint != p->second.visibleCheckpoint)
		{
			int checkpointid = p->second.visibleCheckpoint;
			p->second.activeCheckpoint = checkpointid;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerEnterDynamicCP", &index))
				{
					amx_Push(*a, checkpointid);
					amx_Push(*a, playerid);
					amx_Exec(*a, NULL, index);
				}
			}
		}
	}
	return true;
}

bool Events::OnPlayerLeaveCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint == p->second.visibleCheckpoint)
		{
			int checkpointid = p->second.activeCheckpoint;
			p->second.activeCheckpoint = 0;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicCP", &index))
				{
					amx_Push(*a, checkpointid);
					amx_Push(*a, playerid);
					amx_Exec(*a, NULL, index);
				}
			}
		}
	}
	return true;
}

bool Events::OnPlayerEnterRaceCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint != p->second.visibleRaceCheckpoint)
		{
			int checkpointid = p->second.visibleRaceCheckpoint;
			p->second.activeRaceCheckpoint = checkpointid;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerEnterDynamicRaceCP", &index))
				{
					amx_Push(*a, checkpointid);
					amx_Push(*a, playerid);
					amx_Exec(*a, NULL, index);
				}
			}
		}
	}
	return true;
}

bool Events::OnPlayerLeaveRaceCheckpoint(int playerid)
{
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint == p->second.visibleRaceCheckpoint)
		{
			int checkpointid = p->second.activeRaceCheckpoint;
			p->second.activeRaceCheckpoint = 0;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicRaceCP", &index))
				{
					amx_Push(*a, checkpointid);
					amx_Push(*a, playerid);
					amx_Exec(*a, NULL, index);
				}
			}
		}
	}
	return true;
}
