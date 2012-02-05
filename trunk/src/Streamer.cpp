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

Streamer::Streamer()
{
	averageUpdateTime = 0.0f;
	processingFinalPlayer = false;
	tickCount = 0;
	tickRate = 50;
	velocityBoundaries = boost::make_tuple(0.25f, 25.0f);
	visibleMapIcons = 100;
	visibleObjects = 400;
	visiblePickups = 4096;
	visibleTextLabels = 1024;
}

bool Streamer::setTickRate(std::size_t value)
{
	if (value > 0)
	{
		tickRate = value;
		return true;
	}
	return false;
}

std::size_t Streamer::getVisibleItems(int type)
{
	switch (type)
	{
		case STREAMER_TYPE_OBJECT:
		{
			return visibleObjects;
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			return visiblePickups;
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			return visibleMapIcons;
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			return visibleTextLabels;
		}
		break;
	}
	return 0;
}

bool Streamer::setVisibleItems(int type, std::size_t value)
{
	switch (type)
	{
		case STREAMER_TYPE_OBJECT:
		{
			visibleObjects = value;
			return true;
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			visiblePickups = value;
			return true;
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			visibleMapIcons = value;
			return true;
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			visibleTextLabels = value;
			return true;
		}
		break;
	}
	return false;
}

void Streamer::calculateAverageUpdateTime()
{
	static boost::chrono::steady_clock::time_point currentTime, lastRecordedTime;
	static Eigen::Array<float, 5, 1> recordedTimes = Eigen::Array<float, 5, 1>::Zero();
	currentTime = boost::chrono::steady_clock::now();
	if (lastRecordedTime.time_since_epoch().count())
	{
		if (!(recordedTimes > 0).all())
		{
			boost::chrono::duration<float> elapsedTime = currentTime - lastRecordedTime;
			recordedTimes[(recordedTimes > 0).count()] = elapsedTime.count();
		}
		else
		{
			averageUpdateTime = recordedTimes.mean() * 50.0f;
			recordedTimes.setZero();
		}
	}
	lastRecordedTime = currentTime;
}

void Streamer::startAutomaticUpdate()
{
	if (tickCount >= tickRate)
	{
		calculateAverageUpdateTime();
		processActiveItems();
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			processingFinalPlayer = isLastPlayer(p, core->getData()->players);
			performPlayerUpdate(p->second, true);
		}
		processingFinalPlayer = false;
		tickCount = 0;
	}
	if (!core->getData()->interfaces.empty())
	{
		++tickCount;
	}
}

void Streamer::startManualUpdate(Player &player)
{
	processActiveItems();
	performPlayerUpdate(player, false);
}

void Streamer::performPlayerUpdate(Player &player, bool automatic)
{
	bool playerIsIdle = false;
	Eigen::Vector3f position = player.position;
	if (automatic)
	{
		int state = GetPlayerState(player.playerID);
		if (state == PLAYER_STATE_NONE || state == PLAYER_STATE_WASTED)
		{
			return;
		}
		player.interiorID = GetPlayerInterior(player.playerID);
		player.worldID = GetPlayerVirtualWorld(player.playerID);
		GetPlayerPos(player.playerID, &player.position[0], &player.position[1], &player.position[2]);
		if (player.position != position)
		{
			position = player.position;
			Eigen::Vector3f velocity = Eigen::Vector3f::Zero();
			if (state == PLAYER_STATE_ONFOOT)
			{
				GetPlayerVelocity(player.playerID, &velocity[0], &velocity[1], &velocity[2]);
			}
			else
			{
				GetVehicleVelocity(GetPlayerVehicleID(player.playerID), &velocity[0], &velocity[1], &velocity[2]);
			}
			float velocityNorm = velocity.squaredNorm();
			if (velocityNorm >= velocityBoundaries.get<0>() && velocityNorm <= velocityBoundaries.get<1>())
			{
				player.position += velocity * averageUpdateTime;
			}
		}
		else
		{
			if (!player.idleUpdate)
			{
				playerIsIdle = true;
			}
		}
	}
	std::vector<SharedCell> playerCells;
	if (!playerIsIdle)
	{
		core->getGrid()->findAllCells(player, playerCells);
	}
	else
	{
		core->getGrid()->findMinimalCells(player, playerCells);
	}
	if (!playerCells.empty())
	{
		if (automatic)
		{
			if (!core->getData()->pickups.empty())
			{
				processPickups(player, playerCells);
			}
		}
		if (!playerIsIdle)
		{
			if (!core->getData()->objects.empty())
			{
				processObjects(player, playerCells);
			}
			if (!core->getData()->checkpoints.empty())
			{
				processCheckpoints(player, playerCells);
			}
			if (!core->getData()->raceCheckpoints.empty())
			{
				processRaceCheckpoints(player, playerCells);
			}
			if (!core->getData()->mapIcons.empty())
			{
				processMapIcons(player, playerCells);
			}
			if (!core->getData()->textLabels.empty())
			{
				processTextLabels(player, playerCells);
			}
			if (!core->getData()->areas.empty())
			{
				processAreas(player, playerCells);
			}
		}
	}
	if (automatic)
	{
		player.position = position;
	}
}

void Streamer::executeCallbacks(const std::multimap<bool, boost::tuple<int, int> > &areaCallbacks)
{
	for (std::multimap<bool, boost::tuple<int, int> >::const_iterator c = areaCallbacks.begin(); c != areaCallbacks.end(); ++c)
	{
		if (c->first)
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerEnterDynamicArea", &index))
				{
					amx_Push(*a, c->second.get<0>());
					amx_Push(*a, c->second.get<1>());
					amx_Exec(*a, NULL, index);
				}
			}
		}
		else
		{
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int index = 0;
				if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicArea", &index))
				{
					amx_Push(*a, c->second.get<0>());
					amx_Push(*a, c->second.get<1>());
					amx_Exec(*a, NULL, index);
				}
			}
		}
	}
}

void Streamer::executeCallbacks(const std::vector<int> &objectCallbacks)
{
	for (std::vector<int>::const_iterator c = objectCallbacks.begin(); c != objectCallbacks.end(); ++c)
	{
		for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
		{
			int index = 0;
			if (!amx_FindPublic(*a, "OnDynamicObjectMoved", &index))
			{
				amx_Push(*a, *c);
				amx_Exec(*a, NULL, index);
			}
		}
	}
}

void Streamer::processAreas(Player &player, const std::vector<SharedCell> &playerCells)
{
	std::multimap<bool, boost::tuple<int, int> > areaCallbacks;
	for (std::vector<SharedCell>::const_iterator c = playerCells.begin(); c != playerCells.end(); ++c)
	{
		for (boost::unordered_map<int, Element::SharedArea>::const_iterator a = (*c)->areas.begin(); a != (*c)->areas.end(); ++a)
		{
			bool check = false, show = false;
			if (checkPlayer(a->second->players, player.playerID, a->second->interiors, player.interiorID, a->second->worlds, player.worldID))
			{
				boost::unordered_set<int>::iterator d = player.disabledAreas.find(a->first);
				if (d == player.disabledAreas.end())
				{
					check = true;
				}
			}
			if (check)
			{
				switch (a->second->type)
				{
					case STREAMER_AREA_TYPE_CIRCLE:
					{
						if (a->second->attach)
						{
							if (boost::geometry::comparable_distance(Eigen::Vector2f(player.position[0], player.position[1]), Eigen::Vector2f(a->second->attach->position[0], a->second->attach->position[1])) <= a->second->size)
							{
								show = true;
							}
						}
						else
						{
							if (boost::geometry::comparable_distance(Eigen::Vector2f(player.position[0], player.position[1]), boost::get<Eigen::Vector2f>(a->second->position)) <= a->second->size)
							{
								show = true;
							}
						}
					}
					break;
					case STREAMER_AREA_TYPE_RECTANGLE:
					{
						show = boost::geometry::within(Eigen::Vector2f(player.position[0], player.position[1]), boost::get<Element::Box2D>(a->second->position));
					}
					break;
					case STREAMER_AREA_TYPE_SPHERE:
					{
						if (a->second->attach)
						{
							if (boost::geometry::comparable_distance(player.position, a->second->attach->position) <= a->second->size)
							{
								show = true;
							}
						}
						else
						{
							if (boost::geometry::comparable_distance(player.position, boost::get<Eigen::Vector3f>(a->second->position)) <= a->second->size)
							{
								show = true;
							}
						}
					}
					break;
					case STREAMER_AREA_TYPE_CUBE:
					{
						show = boost::geometry::within(player.position, boost::get<Element::Box3D>(a->second->position));
					}
					break;
					case STREAMER_AREA_TYPE_POLYGON:
					{
						if (player.position[2] >= boost::get<Element::Polygon2D>(a->second->position).get<1>()[0] && player.position[2] <= boost::get<Element::Polygon2D>(a->second->position).get<1>()[1])
						{
							show = boost::geometry::within(Eigen::Vector2f(player.position[0], player.position[1]), boost::get<Element::Polygon2D>(a->second->position).get<0>());
						}
					}
					break;
				}
			}
			boost::unordered_set<int>::iterator i = player.internalAreas.find(a->first);
			if (show)
			{
				if (i == player.internalAreas.end())
				{
					player.internalAreas.insert(a->first);
					areaCallbacks.insert(std::make_pair(show, boost::make_tuple(a->first, player.playerID)));
				}
				if (a->second->cell)
				{
					player.visibleCell->areas.insert(*a);
				}
			}
			else
			{
				if (i != player.internalAreas.end())
				{
					player.internalAreas.quick_erase(i);
					areaCallbacks.insert(std::make_pair(show, boost::make_tuple(a->first, player.playerID)));
				}
			}
		}
	}
	if (!areaCallbacks.empty())
	{
		executeCallbacks(areaCallbacks);
	}
}

void Streamer::processCheckpoints(Player &player, const std::vector<SharedCell> &playerCells)
{
	std::multimap<float, Element::SharedCheckpoint> discoveredCheckpoints;
	for (std::vector<SharedCell>::const_iterator c = playerCells.begin(); c != playerCells.end(); ++c)
	{
		for (boost::unordered_map<int, Element::SharedCheckpoint>::const_iterator d = (*c)->checkpoints.begin(); d != (*c)->checkpoints.end(); ++d)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(d->second->players, player.playerID, d->second->interiors, player.interiorID, d->second->worlds, player.worldID))
			{
				boost::unordered_set<int>::iterator e = player.disabledCheckpoints.find(d->first);
				if (e == player.disabledCheckpoints.end())
				{
					distance = boost::geometry::comparable_distance(player.position, d->second->position);
				}
			}
			if (distance <= d->second->streamDistance)
			{
				discoveredCheckpoints.insert(std::make_pair(distance, d->second));
			}
			else
			{
				if (d->first == player.visibleCheckpoint)
				{
					DisablePlayerCheckpoint(player.playerID);
					player.activeCheckpoint = 0;
					player.visibleCheckpoint = 0;
				}
			}
		}
	}
	if (!discoveredCheckpoints.empty())
	{
		std::multimap<float, Element::SharedCheckpoint>::iterator d = discoveredCheckpoints.begin();
		if (d->second->checkpointID != player.visibleCheckpoint)
		{
			if (player.visibleCheckpoint)
			{
				DisablePlayerCheckpoint(player.playerID);
				player.activeCheckpoint = 0;
			}
			SetPlayerCheckpoint(player.playerID, d->second->position[0], d->second->position[1], d->second->position[2], d->second->size);
			player.visibleCheckpoint = d->second->checkpointID;
		}
		if (d->second->cell)
		{
			player.visibleCell->checkpoints.insert(std::make_pair(d->second->checkpointID, d->second));
		}
	}
}

void Streamer::processMapIcons(Player &player, const std::vector<SharedCell> &playerCells)
{
	std::multimap<float, Element::SharedMapIcon> discoveredMapIcons, existingMapIcons;
	for (std::vector<SharedCell>::const_iterator c = playerCells.begin(); c != playerCells.end(); ++c)
	{
		for (boost::unordered_map<int, Element::SharedMapIcon>::const_iterator m = (*c)->mapIcons.begin(); m != (*c)->mapIcons.end(); ++m)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(m->second->players, player.playerID, m->second->interiors, player.interiorID, m->second->worlds, player.worldID))
			{
				distance = boost::geometry::comparable_distance(player.position, m->second->position);
			}
			boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(m->first);
			if (distance <= m->second->streamDistance)
			{
				if (i == player.internalMapIcons.end())
				{
					discoveredMapIcons.insert(std::make_pair(distance, m->second));
				}
				else
				{
					if (m->second->cell)
					{
						player.visibleCell->mapIcons.insert(*m);
					}
					existingMapIcons.insert(std::make_pair(distance, m->second));
				}
			}
			else
			{
				if (i != player.internalMapIcons.end())
				{
					RemovePlayerMapIcon(player.playerID, i->second);
					player.mapIconIdentifier.remove(i->second, player.internalMapIcons.size());
					player.internalMapIcons.quick_erase(i);
				}
			}
		}
	}
	for (std::multimap<float, Element::SharedMapIcon>::iterator d = discoveredMapIcons.begin(); d != discoveredMapIcons.end(); ++d)
	{
		if (player.internalMapIcons.size() == visibleMapIcons)
		{
			std::multimap<float, Element::SharedMapIcon>::reverse_iterator e = existingMapIcons.rbegin();
			if (e != existingMapIcons.rend())
			{
				if (d->first < e->first)
				{
					boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(e->second->mapIconID);
					if (i != player.internalMapIcons.end())
					{
						RemovePlayerMapIcon(player.playerID, i->second);
						player.mapIconIdentifier.remove(i->second, player.internalMapIcons.size());
						player.internalMapIcons.quick_erase(i);
					}
					if (e->second->cell)
					{
						player.visibleCell->mapIcons.erase(e->second->mapIconID);
					}
					existingMapIcons.erase(--e.base());
				}
			}
			if (player.internalMapIcons.size() == visibleMapIcons)
			{
				break;
			}
		}
		int internalID = player.mapIconIdentifier.get();
		SetPlayerMapIcon(player.playerID, internalID, d->second->position[0], d->second->position[1], d->second->position[2], d->second->type, d->second->color, d->second->style);
		player.internalMapIcons.insert(std::make_pair(d->second->mapIconID, internalID));
		if (d->second->cell)
		{
			player.visibleCell->mapIcons.insert(std::make_pair(d->second->mapIconID, d->second));
		}
	}
}

void Streamer::processObjects(Player &player, const std::vector<SharedCell> &playerCells)
{
	std::multimap<float, Element::SharedObject> discoveredObjects, existingObjects;
	for (std::vector<SharedCell>::const_iterator c = playerCells.begin(); c != playerCells.end(); ++c)
	{
		for (boost::unordered_map<int, Element::SharedObject>::const_iterator o = (*c)->objects.begin(); o != (*c)->objects.end(); ++o)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(o->second->players, player.playerID, o->second->interiors, player.interiorID, o->second->worlds, player.worldID))
			{
				distance = boost::geometry::comparable_distance(player.position, o->second->position);
			}
			boost::unordered_map<int, int>::iterator i = player.internalObjects.find(o->first);
			if (distance <= o->second->streamDistance)
			{
				if (i == player.internalObjects.end())
				{
					discoveredObjects.insert(std::make_pair(distance, o->second));
				}
				else
				{
					if (o->second->cell)
					{
						player.visibleCell->objects.insert(*o);
					}
					existingObjects.insert(std::make_pair(distance, o->second));
				}
			}
			else
			{
				if (i != player.internalObjects.end())
				{
					DestroyPlayerObject(player.playerID, i->second);
					player.internalObjects.quick_erase(i);
				}
			}
		}
	}
	for (std::multimap<float, Element::SharedObject>::iterator d = discoveredObjects.begin(); d != discoveredObjects.end(); ++d)
	{
		if (player.internalObjects.size() == player.visibleObjects)
		{
			std::multimap<float, Element::SharedObject>::reverse_iterator e = existingObjects.rbegin();
			if (e != existingObjects.rend())
			{
				if (d->first < e->first)
				{
					boost::unordered_map<int, int>::iterator i = player.internalObjects.find(e->second->objectID);
					if (i != player.internalObjects.end())
					{
						DestroyPlayerObject(player.playerID, i->second);
						player.internalObjects.quick_erase(i);
					}
					if (e->second->cell)
					{
						player.visibleCell->objects.erase(e->second->objectID);
					}
					existingObjects.erase(--e.base());
				}
			}
		}
		if (player.internalObjects.size() == visibleObjects)
		{
			player.visibleObjects = player.internalObjects.size();
			break;
		}
		int internalID = CreatePlayerObject(player.playerID, d->second->modelID, d->second->position[0], d->second->position[1], d->second->position[2], d->second->rotation[0], d->second->rotation[1], d->second->rotation[2], d->second->drawDistance);
		if (internalID == INVALID_GENERIC_ID)
		{
			player.visibleObjects = player.internalObjects.size();
			break;
		}
		if (d->second->move)
		{
			MovePlayerObject(player.playerID, internalID, d->second->move->position.get<0>()[0], d->second->move->position.get<0>()[1], d->second->move->position.get<0>()[2], d->second->move->speed, d->second->move->rotation.get<0>()[0], d->second->move->rotation.get<0>()[1], d->second->move->rotation.get<0>()[2]);
		}
		player.internalObjects.insert(std::make_pair(d->second->objectID, internalID));
		if (d->second->cell)
		{
			player.visibleCell->objects.insert(std::make_pair(d->second->objectID, d->second));
		}
	}
}

void Streamer::processPickups(Player &player, const std::vector<SharedCell> &playerCells)
{
	static boost::unordered_map<int, Element::SharedPickup> discoveredPickups, existingPickups;
	for (std::vector<SharedCell>::const_iterator c = playerCells.begin(); c != playerCells.end(); ++c)
	{
		for (boost::unordered_map<int, Element::SharedPickup>::const_iterator p = (*c)->pickups.begin(); p != (*c)->pickups.end(); ++p)
		{
			boost::unordered_map<int, Element::SharedPickup>::iterator d = discoveredPickups.find(p->first), e = existingPickups.find(p->first);
			if (d == discoveredPickups.end() && e == existingPickups.end())
			{
				if (checkPlayer(p->second->players, player.playerID, p->second->interiors, player.interiorID, p->second->worlds, player.worldID))
				{
					if (boost::geometry::comparable_distance(player.position, p->second->position) <= p->second->streamDistance)
					{
						boost::unordered_map<int, int>::iterator i = internalPickups.find(p->first);
						if (i == internalPickups.end())
						{
							discoveredPickups.insert(*p);
						}
						else
						{
							existingPickups.insert(*p);
						}
					}
				}
			}
		}
	}
	if (processingFinalPlayer)
	{
		boost::unordered_map<int, int>::iterator i = internalPickups.begin();
		while (i != internalPickups.end())
		{
			boost::unordered_map<int, Element::SharedPickup>::iterator e = existingPickups.find(i->first);
			if (e == existingPickups.end())
			{
				DestroyPickup(i->second);
				i = internalPickups.erase(i);
			}
			else
			{
				++i;
			}
		}
		existingPickups.clear();
		for (boost::unordered_map<int, Element::SharedPickup>::iterator d = discoveredPickups.begin(); d != discoveredPickups.end(); ++d)
		{
			if (internalPickups.size() == visiblePickups)
			{
				break;
			}
			int internalID = CreatePickup(d->second->modelID, d->second->type, d->second->position[0], d->second->position[1], d->second->position[2], -1);
			if (internalID == INVALID_ALTERNATE_ID)
			{
				break;
			}
			internalPickups.insert(std::make_pair(d->second->pickupID, internalID));
		}
		discoveredPickups.clear();
	}
}

void Streamer::processRaceCheckpoints(Player &player, const std::vector<SharedCell> &playerCells)
{
	std::multimap<float, Element::SharedRaceCheckpoint> discoveredRaceCheckpoints;
	for (std::vector<SharedCell>::const_iterator c = playerCells.begin(); c != playerCells.end(); ++c)
	{
		for (boost::unordered_map<int, Element::SharedRaceCheckpoint>::const_iterator r = (*c)->raceCheckpoints.begin(); r != (*c)->raceCheckpoints.end(); ++r)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(r->second->players, player.playerID, r->second->interiors, player.interiorID, r->second->worlds, player.worldID))
			{
				boost::unordered_set<int>::iterator d = player.disabledRaceCheckpoints.find(r->first);
				if (d == player.disabledRaceCheckpoints.end())
				{
					distance = boost::geometry::comparable_distance(player.position, r->second->position);
				}
			}
			if (distance <= r->second->streamDistance)
			{
				discoveredRaceCheckpoints.insert(std::make_pair(distance, r->second));
			}
			else
			{
				if (r->first == player.visibleRaceCheckpoint)
				{
					DisablePlayerRaceCheckpoint(player.playerID);
					player.activeRaceCheckpoint = 0;
					player.visibleRaceCheckpoint = 0;
				}
			}
		}
	}
	if (!discoveredRaceCheckpoints.empty())
	{
		std::multimap<float, Element::SharedRaceCheckpoint>::iterator d = discoveredRaceCheckpoints.begin();
		if (d->second->raceCheckpointID != player.visibleRaceCheckpoint)
		{
			if (player.visibleRaceCheckpoint)
			{
				DisablePlayerRaceCheckpoint(player.playerID);
				player.activeRaceCheckpoint = 0;
			}
			SetPlayerRaceCheckpoint(player.playerID, d->second->type, d->second->position[0], d->second->position[1], d->second->position[2], d->second->next[0], d->second->next[1], d->second->next[2], d->second->size);
			player.visibleRaceCheckpoint = d->second->raceCheckpointID;
		}
		if (d->second->cell)
		{
			player.visibleCell->raceCheckpoints.insert(std::make_pair(d->second->raceCheckpointID, d->second));
		}
	}
}

void Streamer::processTextLabels(Player &player, const std::vector<SharedCell> &playerCells)
{
	std::multimap<float, Element::SharedTextLabel> discoveredTextLabels, existingTextLabels;
	for (std::vector<SharedCell>::const_iterator c = playerCells.begin(); c != playerCells.end(); ++c)
	{
		for (boost::unordered_map<int, Element::SharedTextLabel>::const_iterator t = (*c)->textLabels.begin(); t != (*c)->textLabels.end(); ++t)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(t->second->players, player.playerID, t->second->interiors, player.interiorID, t->second->worlds, player.worldID))
			{
				if (t->second->attach)
				{
					distance = boost::geometry::comparable_distance(player.position, t->second->attach->position);
				}
				else
				{
					distance = boost::geometry::comparable_distance(player.position, t->second->position);
				}
			}
			boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(t->first);
			if (distance <= t->second->streamDistance)
			{
				if (i == player.internalTextLabels.end())
				{
					discoveredTextLabels.insert(std::make_pair(distance, t->second));
				}
				else
				{
					if (t->second->cell)
					{
						player.visibleCell->textLabels.insert(*t);
					}
					existingTextLabels.insert(std::make_pair(distance, t->second));
				}
			}
			else
			{
				if (i != player.internalTextLabels.end())
				{
					DeletePlayer3DTextLabel(player.playerID, i->second);
					player.internalTextLabels.quick_erase(i);
				}
			}
		}
	}
	for (std::multimap<float, Element::SharedTextLabel>::iterator d = discoveredTextLabels.begin(); d != discoveredTextLabels.end(); ++d)
	{
		if (player.internalTextLabels.size() == player.visibleTextLabels)
		{
			std::multimap<float, Element::SharedTextLabel>::reverse_iterator e = existingTextLabels.rbegin();
			if (e != existingTextLabels.rend())
			{
				if (d->first < e->first)
				{
					boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(e->second->textLabelID);
					if (i != player.internalTextLabels.end())
					{
						DeletePlayer3DTextLabel(player.playerID, i->second);
						player.internalTextLabels.quick_erase(i);
					}
					if (e->second->cell)
					{
						player.visibleCell->textLabels.erase(e->second->textLabelID);
					}
					existingTextLabels.erase(--e.base());
				}
			}
		}
		if (player.internalTextLabels.size() == visibleTextLabels)
		{
			player.visibleTextLabels = player.internalTextLabels.size();
			break;
		}
		int internalID = CreatePlayer3DTextLabel(player.playerID, d->second->text.c_str(), d->second->color, d->second->position[0], d->second->position[1], d->second->position[2], d->second->drawDistance, (d->second->attach ? d->second->attach->player : INVALID_GENERIC_ID), (d->second->attach ? d->second->attach->vehicle : INVALID_GENERIC_ID), d->second->testLOS);
		if (internalID == INVALID_GENERIC_ID)
		{
			player.visibleTextLabels = player.internalTextLabels.size();
			break;
		}
		player.internalTextLabels.insert(std::make_pair(d->second->textLabelID, internalID));
		if (d->second->cell)
		{
			player.visibleCell->textLabels.insert(std::make_pair(d->second->textLabelID, d->second));
		}
	}
}

void Streamer::processActiveItems()
{
	if (!attachedAreas.empty())
	{
		processAttachedAreas();
	}
	if (!attachedTextLabels.empty())
	{
		processAttachedTextLabels();
	}
	if (!movingObjects.empty())
	{
		processMovingObjects();
	}
}

void Streamer::processAttachedAreas()
{
	for (boost::unordered_set<Element::SharedArea>::iterator m = attachedAreas.begin(); m != attachedAreas.end(); ++m)
	{
		boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find((*m)->areaID);
		if (a != core->getData()->areas.end())
		{
			if (a->second->attach)
			{
				bool adjust = false;
				if (a->second->attach->player != INVALID_GENERIC_ID)
				{
					adjust = GetPlayerPos(a->second->attach->player, &a->second->attach->position[0], &a->second->attach->position[1], &a->second->attach->position[2]);
				}
				else if (a->second->attach->vehicle != INVALID_GENERIC_ID)
				{
					adjust = GetVehiclePos(a->second->attach->vehicle, &a->second->attach->position[0], &a->second->attach->position[1], &a->second->attach->position[2]);
				}
				if (adjust)
				{
					if (a->second->cell)
					{
						core->getGrid()->removeArea(a->second, true);
					}
				}
				else
				{
					a->second->attach->position.fill(std::numeric_limits<float>::infinity());
				}
			}
		}
	}
}

void Streamer::processAttachedTextLabels()
{
	for (boost::unordered_set<Element::SharedTextLabel>::iterator m = attachedTextLabels.begin(); m != attachedTextLabels.end(); ++m)
	{
		boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find((*m)->textLabelID);
		if (t != core->getData()->textLabels.end())
		{
			bool adjust = false;
			if (t->second->attach)
			{
				if (t->second->attach->player != INVALID_GENERIC_ID)
				{
					adjust = GetPlayerPos(t->second->attach->player, &t->second->attach->position[0], &t->second->attach->position[1], &t->second->attach->position[2]);
				}
				else if (t->second->attach->vehicle != INVALID_GENERIC_ID)
				{
					adjust = GetVehiclePos(t->second->attach->vehicle, &t->second->attach->position[0], &t->second->attach->position[1], &t->second->attach->position[2]);
				}
				if (adjust)
				{
					if (t->second->cell)
					{
						core->getGrid()->removeTextLabel(t->second, true);
					}
				}
				else
				{
					t->second->attach->position.fill(std::numeric_limits<float>::infinity());
				}
			}
		}
	}
}

void Streamer::processMovingObjects()
{
	std::vector<int> objectCallbacks;
	boost::chrono::steady_clock::time_point currentTime = boost::chrono::steady_clock::now();
	boost::unordered_set<Element::SharedObject>::iterator m = movingObjects.begin();
	while (m != movingObjects.end())
	{
		bool objectFinishedMoving = false;
		boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find((*m)->objectID);
		if (o != core->getData()->objects.end())
		{
			if (o->second->move)
			{
				boost::chrono::duration<float, boost::milli> elapsedTime = currentTime - o->second->move->time;
				if (elapsedTime.count() < o->second->move->duration)
				{
					o->second->position = o->second->move->position.get<1>() + (o->second->move->position.get<2>() * elapsedTime.count());
					if (o->second->move->rotation.get<0>().maxCoeff() > -1000.0f)
					{
						o->second->rotation = o->second->move->rotation.get<1>() + (o->second->move->rotation.get<2>() * elapsedTime.count());
					}
				}
				else
				{
					o->second->position = o->second->move->position.get<0>();
					if (o->second->move->rotation.get<0>().maxCoeff() > -1000.0f)
					{
						o->second->rotation = o->second->move->rotation.get<0>();
					}
					o->second->move.reset();
					objectCallbacks.push_back(o->first);
					objectFinishedMoving = true;
				}
				if (o->second->cell)
				{
					core->getGrid()->removeObject(o->second, true);
				}
			}
		}
		if (objectFinishedMoving)
		{
			m = movingObjects.erase(m);
		}
		else
		{
			++m;
		}
	}
	if (!objectCallbacks.empty())
	{
		executeCallbacks(objectCallbacks);
	}
}
