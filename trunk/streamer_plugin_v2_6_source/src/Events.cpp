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

#include "Main.h"
#include "Events.h"

static Events events;

Events::Events()
{
	this->Register();
}

bool Events::OnPlayerConnect(int playerid)
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
	return true;
}

bool Events::OnPlayerDisconnect(int playerid, int reason)
{
	core->getData()->players.erase(playerid);
	return true;
}

bool Events::OnPlayerPickUpPickup(int playerid, int pickupid)
{
	for (boost::unordered_map<int, int>::iterator p = core->getStreamer()->internalPickups.begin(); p != core->getStreamer()->internalPickups.end(); ++p)
	{
		if (p->second == pickupid)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerPickUpDynamicPickup", &index))
				{
					amx_Push(*a, p->first);
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
			int checkpointID = p->second.visibleCheckpoint;
			p->second.activeCheckpoint = checkpointID;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerEnterDynamicCP", &index))
				{
					amx_Push(*a, checkpointID);
					amx_Push(*a, p->first);
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
			int checkpointID = p->second.activeCheckpoint;
			p->second.activeCheckpoint = 0;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicCP", &index))
				{
					amx_Push(*a, checkpointID);
					amx_Push(*a, p->first);
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
			int raceCheckpointID = p->second.visibleRaceCheckpoint;
			p->second.activeRaceCheckpoint = raceCheckpointID;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerEnterDynamicRaceCP", &index))
				{
					amx_Push(*a, raceCheckpointID);
					amx_Push(*a, p->first);
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
			int raceCheckpointID = p->second.activeRaceCheckpoint;
			p->second.activeRaceCheckpoint = 0;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicRaceCP", &index))
				{
					amx_Push(*a, raceCheckpointID);
					amx_Push(*a, p->first);
					amx_Exec(*a, NULL, index);
				}
			}
		}
	}
	return true;
}
