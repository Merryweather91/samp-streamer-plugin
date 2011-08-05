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
#include "Invoke.h"
#include "Streamer.h"

Streamer * streamer;

void Streamer::processAreas(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells)
{
	std::map<int, bool> callbackMap;
	for (std::vector<Grid::SharedCell>::const_iterator s = playerCells.begin(); s != playerCells.end(); ++s)
	{
		for (boost::unordered_map<int, Core::SharedArea>::const_iterator a = (* s)->areas.begin(); a != (* s)->areas.end(); ++a)
		{
			bool check = false, display = false;
			if (checkPlayer(a->second->interiors, player.interiorID, a->second->players, player.playerID, a->second->worlds, player.worldID))
			{
				boost::unordered_set<int>::iterator f = player.disabledAreas.find(a->first);
				if (f == player.disabledAreas.end())
				{
					check = true;
				}
			}
			if (check)
			{
				switch (a->second->type)
				{
					case 0:
					{
						if (a->second->attach)
						{
							if (core->findDistance2D(player.x, player.y, a->second->attach->x, a->second->attach->y) <= a->second->size)
							{
								display = true;
							}
						}
						else
						{
							if (core->findDistance2D(player.x, player.y, a->second->x1, a->second->y1) <= a->second->size)
							{
								display = true;
							}
						}
					}
					break;
					case 1:
					{
						display = core->checkArea2D(player.x, player.y, a->second->x1, a->second->y1, a->second->x2, a->second->y2);
					}
					break;
					case 2:
					{
						if (a->second->attach)
						{
							if (core->findDistance3D(player.x, player.y, player.z, a->second->attach->x, a->second->attach->y, a->second->attach->z) <= a->second->size)
							{
								display = true;
							}
						}
						else
						{
							if (core->findDistance3D(player.x, player.y, player.z, a->second->x1, a->second->y1, a->second->z1) <= a->second->size)
							{
								display = true;
							}
						}
					}
					break;
					case 3:
					{
						display = core->checkArea3D(player.x, player.y, player.z, a->second->x1, a->second->y1, a->second->z1, a->second->x2, a->second->y2, a->second->z2);
					}
					break;
				}
			}
			boost::unordered_set<int>::iterator f = player.visibleAreas.find(a->first);
			if (display)
			{
				if (f == player.visibleAreas.end())
				{
					player.visibleAreas.insert(a->first);
					callbackMap.insert(std::make_pair(a->first, true));
				}
				player.visibleCells.insert((* s)->id);
			}
			else
			{
				if (f != player.visibleAreas.end())
				{
					player.visibleAreas.quick_erase(f);
					callbackMap.insert(std::make_pair(a->first, false));
				}
			}
		}
	}
	for (std::map<int, bool>::iterator c = callbackMap.begin(); c != callbackMap.end(); ++c)
	{
		if (c->second)
		{
			for (std::list<AMX *>::iterator a = invoke->amx_list.begin(); a != invoke->amx_list.end(); ++a)
			{
				if (!amx_FindPublic(* a, "OnPlayerEnterDynamicArea", &invoke->amx_idx))
				{
					amx_Push(* a, c->first);
					amx_Push(* a, player.playerID);
					amx_Exec(* a, NULL, invoke->amx_idx);
				}
			}
		}
		else
		{
			for (std::list<AMX *>::iterator a = invoke->amx_list.begin(); a != invoke->amx_list.end(); ++a)
			{
				if (!amx_FindPublic(* a, "OnPlayerLeaveDynamicArea", &invoke->amx_idx))
				{
					amx_Push(* a, c->first);
					amx_Push(* a, player.playerID);
					amx_Exec(* a, NULL, invoke->amx_idx);
				}
			}
		}
	}
}

void Streamer::processCheckpoints(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells)
{
	std::multimap<float, Core::SharedCheckpoint> discoveredCheckpoints;
	for (std::vector<Grid::SharedCell>::const_iterator s = playerCells.begin(); s != playerCells.end(); ++s)
	{
		for (boost::unordered_map<int, Core::SharedCheckpoint>::const_iterator c = (* s)->checkpoints.begin(); c != (* s)->checkpoints.end(); ++c)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(c->second->interiors, player.interiorID, c->second->players, player.playerID, c->second->worlds, player.worldID))
			{
				boost::unordered_set<int>::iterator f = player.disabledCheckpoints.find(c->first);
				if (f == player.disabledCheckpoints.end())
				{
					distance = core->findDistance3D(player.x, player.y, player.z, c->second->x, c->second->y, c->second->z);
				}
			}
			if (distance <= c->second->distance)
			{
				discoveredCheckpoints.insert(std::make_pair(distance, c->second));
				player.visibleCells.insert((* s)->id);
			}
			else
			{
				if (c->first == player.visibleCheckpoint)
				{
					invoke->callNative(&PAWN::DisablePlayerCheckpoint, player.playerID);
					player.activeCheckpoint = 0;
					player.visibleCheckpoint = 0;
				}
			}
		}
	}
	if (!discoveredCheckpoints.empty())
	{
		std::multimap<float, Core::SharedCheckpoint>::iterator d = discoveredCheckpoints.begin();
		if (d->second->checkpointID != player.visibleCheckpoint)
		{
			if (player.visibleCheckpoint)
			{
				invoke->callNative(&PAWN::DisablePlayerCheckpoint, player.playerID);
				player.activeCheckpoint = 0;
			}
			invoke->callNative(&PAWN::SetPlayerCheckpoint, player.playerID, d->second->x, d->second->y, d->second->z, d->second->size);
			player.visibleCheckpoint = d->second->checkpointID;
		}
	}
}

void Streamer::processMapIcons(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells)
{
	std::multimap<float, Core::SharedMapIcon> discoveredMapIcons;
	for (std::vector<Grid::SharedCell>::const_iterator s = playerCells.begin(); s != playerCells.end(); ++s)
	{
		for (boost::unordered_map<int, Core::SharedMapIcon>::const_iterator m = (* s)->mapIcons.begin(); m != (* s)->mapIcons.end(); ++m)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(m->second->interiors, player.interiorID, m->second->players, player.playerID, m->second->worlds, player.worldID))
			{
				distance = core->findDistance3D(player.x, player.y, player.z, m->second->x, m->second->y, m->second->z);
			}
			boost::unordered_map<int, int>::iterator f = player.internalMapIcons.find(m->first);
			if (distance <= m->second->distance)
			{
				if (f == player.internalMapIcons.end())
				{
					discoveredMapIcons.insert(std::make_pair(distance, m->second));
				}
				player.visibleCells.insert((* s)->id);
			}
			else
			{
				if (f != player.internalMapIcons.end())
				{
					invoke->callNative(&PAWN::RemovePlayerMapIcon, player.playerID, f->second);
					player.sortedInternalMapIcons.erase(f->second);
					player.internalMapIcons.quick_erase(f);
				}
			}
		}
	}
	for (std::multimap<float, Core::SharedMapIcon>::iterator d = discoveredMapIcons.begin(); d != discoveredMapIcons.end(); ++d)
	{
		if (player.internalMapIcons.size() == core->global.visibleMapIcons)
		{
			break;
		}
		int internalID = 0;
		for (std::set<int>::iterator i = player.sortedInternalMapIcons.begin(); i != player.sortedInternalMapIcons.end(); ++i)
		{
			if (* i != internalID)
			{
				break;
			}
			++internalID;
		}
		invoke->callNative(&PAWN::SetPlayerMapIcon, player.playerID, internalID, d->second->x, d->second->y, d->second->z, d->second->type, d->second->color, d->second->style);
		player.internalMapIcons.insert(std::make_pair(d->second->mapIconID, internalID));
		player.sortedInternalMapIcons.insert(internalID);
	}
}

void Streamer::processObjects(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells)
{
	std::multimap<float, Core::SharedObject> discoveredObjects, existingObjects;
	for (std::vector<Grid::SharedCell>::const_iterator s = playerCells.begin(); s != playerCells.end(); ++s)
	{
		for (boost::unordered_map<int, Core::SharedObject>::const_iterator o = (* s)->objects.begin(); o != (* s)->objects.end(); ++o)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(o->second->interiors, player.interiorID, o->second->players, player.playerID, o->second->worlds, player.worldID))
			{
				distance = core->findDistance3D(player.x, player.y, player.z, o->second->x, o->second->y, o->second->z);
			}
			boost::unordered_map<int, int>::iterator f = player.internalObjects.find(o->first);
			if (distance <= o->second->distance)
			{
				if (f == player.internalObjects.end())
				{
					discoveredObjects.insert(std::make_pair(distance, o->second));
				}
				else
				{
					existingObjects.insert(std::make_pair(distance, o->second));
				}
				player.visibleCells.insert((* s)->id);
			}
			else
			{
				if (f != player.internalObjects.end())
				{
					invoke->callNative(&PAWN::DestroyPlayerObject, player.playerID, f->second);
					player.internalObjects.quick_erase(f);
				}
			}
		}
	}
	for (std::multimap<float, Core::SharedObject>::iterator d = discoveredObjects.begin(); d != discoveredObjects.end(); ++d)
	{
		if (player.internalObjects.size() == player.visibleObjects)
		{
			std::multimap<float, Core::SharedObject>::reverse_iterator e = existingObjects.rbegin();
			if (e != existingObjects.rend())
			{
				if (d->first < e->first)
				{
					boost::unordered_map<int, int>::iterator f = player.internalObjects.find(e->second->objectID);
					if (f != player.internalObjects.end())
					{
						invoke->callNative(&PAWN::DestroyPlayerObject, player.playerID, f->second);
						player.internalObjects.quick_erase(f);
					}
					existingObjects.erase(--e.base());
				}
			}
		}
		if (player.internalObjects.size() == core->global.visibleObjects)
		{
			player.visibleObjects = player.internalObjects.size();
			break;
		}
		int internalID = invoke->callNative(&PAWN::CreatePlayerObject, player.playerID, d->second->modelID, d->second->x, d->second->y, d->second->z, d->second->rX, d->second->rY, d->second->rZ, d->second->drawDistance);
		if (internalID == INVALID_GENERIC_ID)
		{
			player.visibleObjects = player.internalObjects.size();
			break;
		}
		if (d->second->move)
		{
			invoke->callNative(&PAWN::MovePlayerObject, player.playerID, internalID, d->second->move->x, d->second->move->y, d->second->move->z, d->second->move->speed);
		}
		player.internalObjects.insert(std::make_pair(d->second->objectID, internalID));
	}
}

void Streamer::processPickups(const std::set<Grid::SharedCell, Grid::Cell> & totalCells)
{
	std::vector<Core::SharedPickup> discoveredPickups;
	for (std::set<Grid::SharedCell, Grid::Cell>::const_iterator s = totalCells.begin(); s != totalCells.end(); ++s)
	{
		for (boost::unordered_map<int, Core::SharedPickup>::const_iterator p = (* s)->pickups.begin(); p != (* s)->pickups.end(); ++p)
		{
			bool display = false;
			for (std::vector<Data::Player>::iterator q = core->players.begin(); q != core->players.end(); ++q)
			{
				if (checkPlayer(p->second->interiors, q->interiorID, p->second->players, q->playerID, p->second->worldID, q->worldID))
				{
					if (core->findDistance3D(q->x, q->y, q->z, p->second->x, p->second->y, p->second->z) <= p->second->distance)
					{
						display = true;
						break;
					}
				}
			}
			boost::unordered_map<int, int>::iterator f = core->global.internalPickups.find(p->first);
			if (display)
			{
				if (f == core->global.internalPickups.end())
				{
					discoveredPickups.push_back(p->second);
				}
				core->global.visibleCells.insert((* s)->id);
			}
			else
			{
				if (f != core->global.internalPickups.end())
				{
					invoke->callNative(&PAWN::DestroyPickup, f->second);
					core->global.internalPickups.quick_erase(f);
				}
			}
		}
	}
	for (std::vector<Core::SharedPickup>::iterator d = discoveredPickups.begin(); d != discoveredPickups.end(); ++d)
	{
		if (core->global.internalPickups.size() == core->global.visiblePickups)
		{
			break;
		}
		int internalID = invoke->callNative(&PAWN::CreatePickup, (* d)->modelID, (* d)->type, (* d)->x, (* d)->y, (* d)->z, (* d)->worldID);
		if (internalID == INVALID_PICKUP_ID)
		{
			break;
		}
		core->global.internalPickups.insert(std::make_pair((* d)->pickupID, internalID));
	}
}

void Streamer::processRaceCheckpoints(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells)
{
	std::multimap<float, Core::SharedRaceCheckpoint> discoveredRaceCheckpoints;
	for (std::vector<Grid::SharedCell>::const_iterator s = playerCells.begin(); s != playerCells.end(); ++s)
	{
		for (boost::unordered_map<int, Core::SharedRaceCheckpoint>::const_iterator r = (* s)->raceCheckpoints.begin(); r != (* s)->raceCheckpoints.end(); ++r)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(r->second->interiors, player.interiorID, r->second->players, player.playerID, r->second->worlds, player.worldID))
			{
				boost::unordered_set<int>::iterator f = player.disabledRaceCheckpoints.find(r->first);
				if (f == player.disabledRaceCheckpoints.end())
				{
					distance = core->findDistance3D(player.x, player.y, player.z, r->second->x, r->second->y, r->second->z);
				}
			}
			if (distance <= r->second->distance)
			{
				discoveredRaceCheckpoints.insert(std::make_pair(distance, r->second));
				player.visibleCells.insert((* s)->id);
			}
			else
			{
				if (r->first == player.visibleRaceCheckpoint)
				{
					invoke->callNative(&PAWN::DisablePlayerRaceCheckpoint, player.playerID);
					player.activeRaceCheckpoint = 0;
					player.visibleRaceCheckpoint = 0;
				}
			}
		}
	}
	if (!discoveredRaceCheckpoints.empty())
	{
		std::multimap<float, Core::SharedRaceCheckpoint>::iterator d = discoveredRaceCheckpoints.begin();
		if (d->second->checkpointID != player.visibleRaceCheckpoint)
		{
			if (player.visibleRaceCheckpoint)
			{
				invoke->callNative(&PAWN::DisablePlayerRaceCheckpoint, player.playerID);
				player.activeRaceCheckpoint = 0;
			}
			invoke->callNative(&PAWN::SetPlayerRaceCheckpoint, player.playerID, d->second->type, d->second->x, d->second->y, d->second->z, d->second->nextX, d->second->nextY, d->second->nextZ, d->second->size);
			player.visibleRaceCheckpoint = d->second->checkpointID;
		}
	}
}

void Streamer::processTextLabels(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells)
{
	std::multimap<float, Core::SharedTextLabel> discoveredTextLabels;
	for (std::vector<Grid::SharedCell>::const_iterator s = playerCells.begin(); s != playerCells.end(); ++s)
	{
		for (boost::unordered_map<int, Core::SharedTextLabel>::const_iterator t = (* s)->textLabels.begin(); t != (* s)->textLabels.end(); ++t)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(t->second->interiors, player.interiorID, t->second->players, player.playerID, t->second->worlds, player.worldID))
			{
				if (t->second->attach)
				{
					distance = core->findDistance3D(player.x, player.y, player.z, t->second->attach->x, t->second->attach->y, t->second->attach->z);
				}
				else
				{
					distance = core->findDistance3D(player.x, player.y, player.z, t->second->x, t->second->y, t->second->z);
				}
			}
			boost::unordered_map<int, int>::iterator f = player.internalTextLabels.find(t->first);
			if (distance <= t->second->distance)
			{
				if (f == player.internalTextLabels.end())
				{
					discoveredTextLabels.insert(std::make_pair(distance, t->second));
				}
				player.visibleCells.insert((* s)->id);
			}
			else
			{
				if (f != player.internalTextLabels.end())
				{
					invoke->callNative(&PAWN::DeletePlayer3DTextLabel, player.playerID, f->second);
					player.internalTextLabels.quick_erase(f);
				}
			}
		}
	}
	for (std::multimap<float, Core::SharedTextLabel>::iterator d = discoveredTextLabels.begin(); d != discoveredTextLabels.end(); ++d)
	{
		if (player.internalTextLabels.size() == core->global.visibleTextLabels)
		{
			break;
		}
		int internalID = invoke->callNative(&PAWN::CreatePlayer3DTextLabel, player.playerID, d->second->text.c_str(), d->second->color, d->second->x, d->second->y, d->second->z, d->second->drawDistance, (d->second->attach ? d->second->attach->player : INVALID_GENERIC_ID), (d->second->attach ? d->second->attach->vehicle : INVALID_GENERIC_ID), d->second->testLOS);
		if (internalID == INVALID_GENERIC_ID)
		{
			break;
		}
		player.internalTextLabels.insert(std::make_pair(d->second->textLabelID, internalID));
	}
}

void Streamer::updateMovingAreas()
{
	for (boost::unordered_set<Core::SharedArea>::iterator m = core->movingAreas.begin(); m != core->movingAreas.end(); ++m)
	{
		boost::unordered_map<int, Core::SharedArea>::iterator a = core->areas.find((* m)->areaID);
		if (a != core->areas.end())
		{
			if (a->second->attach)
			{
				bool adjust = false;
				if (a->second->attach->player != INVALID_GENERIC_ID)
				{
					if (invoke->callNative(&PAWN::GetPlayerPos, a->second->attach->player, &a->second->attach->x, &a->second->attach->y, &a->second->attach->z))
					{
						adjust = true;
					}
				}
				else if (a->second->attach->vehicle != INVALID_GENERIC_ID)
				{
					if (invoke->callNative(&PAWN::GetVehiclePos, a->second->attach->vehicle, &a->second->attach->x, &a->second->attach->y, &a->second->attach->z))
					{
						adjust = true;
					}
				}
				if (adjust)
				{
					if (a->second->cellID)
					{
						grid->removeArea(a->second, true);
					}
				}
				else
				{
					a->second->attach->x = std::numeric_limits<float>::infinity();
					a->second->attach->y = std::numeric_limits<float>::infinity();
					a->second->attach->z = std::numeric_limits<float>::infinity();
				}
			}
		}
	}
}

void Streamer::updateMovingObjects()
{
	std::vector<Core::SharedObject> callbackVector;
	for (boost::unordered_set<Core::SharedObject>::iterator m = core->movingObjects.begin(); m != core->movingObjects.end(); ++m)
	{
		boost::unordered_map<int, Core::SharedObject>::iterator o = core->objects.find((* m)->objectID);
		if (o != core->objects.end())
		{
			if (o->second->move)
			{
				int timeElapsed = core->obtainCurrentTime() - o->second->move->startTime;
				if (timeElapsed < o->second->move->duration)
				{
					o->second->x = o->second->move->startX + (o->second->move->offsetX * timeElapsed);
					o->second->y = o->second->move->startY + (o->second->move->offsetY * timeElapsed);
					o->second->z = o->second->move->startZ + (o->second->move->offsetZ * timeElapsed);
				}
				else
				{
					o->second->x = o->second->move->x;
					o->second->y = o->second->move->y;
					o->second->z = o->second->move->z;
					o->second->move.reset();
					callbackVector.push_back(o->second);
				}
				if (o->second->cellID)
				{
					grid->removeObject(o->second, true);
				}
			}
		}
	}
	for (std::vector<Core::SharedObject>::iterator c = callbackVector.begin(); c != callbackVector.end(); ++c)
	{
		core->movingObjects.erase(* c);
		for (std::list<AMX *>::iterator a = invoke->amx_list.begin(); a != invoke->amx_list.end(); ++a)
		{
			if (!amx_FindPublic(* a, "OnDynamicObjectMoved", &invoke->amx_idx))
			{
				amx_Push(* a, (* c)->objectID);
				amx_Exec(* a, NULL, invoke->amx_idx);
			}
		}
	}
}

void Streamer::updateMovingTextLabels()
{
	for (boost::unordered_set<Core::SharedTextLabel>::iterator m = core->movingTextLabels.begin(); m != core->movingTextLabels.end(); ++m)
	{
		boost::unordered_map<int, Core::SharedTextLabel>::iterator t = core->textLabels.find((* m)->textLabelID);
		if (t != core->textLabels.end())
		{
			bool adjust = false;
			if (t->second->attach)
			{
				if (t->second->attach->player != INVALID_GENERIC_ID)
				{
					if (invoke->callNative(&PAWN::GetPlayerPos, t->second->attach->player, &t->second->attach->x, &t->second->attach->y, &t->second->attach->z))
					{
						adjust = true;
					}
				}
				else if (t->second->attach->vehicle != INVALID_GENERIC_ID)
				{
					if (invoke->callNative(&PAWN::GetVehiclePos, t->second->attach->vehicle, &t->second->attach->x, &t->second->attach->y, &t->second->attach->z))
					{
						adjust = true;
					}
				}
				if (adjust)
				{
					if (t->second->cellID)
					{
						grid->removeTextLabel(t->second, true);
					}
				}
				else
				{
					t->second->attach->x = std::numeric_limits<float>::infinity();
					t->second->attach->y = std::numeric_limits<float>::infinity();
					t->second->attach->z = std::numeric_limits<float>::infinity();
				}
			}
		}
	}
}
