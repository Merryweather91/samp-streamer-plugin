/*
    SA-MP Streamer Plugin v2.6
    Copyright � 2011 Incognito

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
#include "Manipulation.h"
#include "Utility.h"

using namespace Manipulation;

int Manipulation::getFloatData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				cell *result = NULL;
				amx_GetAddr(amx, params[4], &result);
				switch (static_cast<int>(params[3]))
				{
					case DrawDistance:
					{
						*result = amx_ftoc(o->second->drawDistance);
						return 1;
					}
					break;
					case MoveSpeed:
					{
						if (o->second->move)
						{
							*result = amx_ftoc(o->second->move->speed);
							return 1;
						}
					}
					break;
					case MoveRX:
					{
						if (o->second->move)
						{
							*result = amx_ftoc(o->second->move->rotation.get<0>()[0]);
							return 1;
						}
					}
					break;
					case MoveRY:
					{
						if (o->second->move)
						{
							*result = amx_ftoc(o->second->move->rotation.get<0>()[1]);
							return 1;
						}
					}
					break;
					case MoveRZ:
					{
						if (o->second->move)
						{
							*result = amx_ftoc(o->second->move->rotation.get<0>()[2]);
							return 1;
						}
					}
					break;
					case MoveX:
					{
						if (o->second->move)
						{
							*result = amx_ftoc(o->second->move->position.get<0>()[0]);
							return 1;
						}
					}
					break;
					case MoveY:
					{
						if (o->second->move)
						{
							*result = amx_ftoc(o->second->move->position.get<0>()[1]);
							return 1;
						}
					}
					break;
					case MoveZ:
					{
						if (o->second->move)
						{
							*result = amx_ftoc(o->second->move->position.get<0>()[2]);
							return 1;
						}
					}
					break;
					case RX:
					{
						*result = amx_ftoc(o->second->rotation[0]);
						return 1;
					}
					break;
					case RY:
					{
						*result = amx_ftoc(o->second->rotation[1]);
						return 1;
					}
					break;
					case RZ:
					{
						*result = amx_ftoc(o->second->rotation[2]);
						return 1;
					}
					break;
					case StreamDistance:
					{
						float streamDistance = sqrt(o->second->streamDistance);
						*result = amx_ftoc(streamDistance);
						return 1;
					}
					break;
					case X:
					{
						*result = amx_ftoc(o->second->position[0]);
						return 1;
					}
					break;
					case Y:
					{
						*result = amx_ftoc(o->second->position[1]);
						return 1;
					}
					break;
					case Z:
					{
						*result = amx_ftoc(o->second->position[2]);
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				cell *result = NULL;
				amx_GetAddr(amx, params[4], &result);
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						float streamDistance = sqrt(p->second->streamDistance);
						*result = amx_ftoc(streamDistance);
						return 1;
					}
					break;
					case X:
					{
						*result = amx_ftoc(p->second->position[0]);
						return 1;
					}
					break;
					case Y:
					{
						*result = amx_ftoc(p->second->position[1]);
						return 1;
					}
					break;
					case Z:
					{
						*result = amx_ftoc(p->second->position[2]);
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				cell *result = NULL;
				amx_GetAddr(amx, params[4], &result);
				switch (static_cast<int>(params[3]))
				{
					case Size:
					{
						*result = amx_ftoc(c->second->size);
						return 1;
					}
					break;
					case StreamDistance:
					{
						float streamDistance = sqrt(c->second->streamDistance);
						*result = amx_ftoc(streamDistance);
						return 1;
					}
					break;
					case X:
					{
						*result = amx_ftoc(c->second->position[0]);
						return 1;
					}
					break;
					case Y:
					{
						*result = amx_ftoc(c->second->position[1]);
						return 1;
					}
					break;
					case Z:
					{
						*result = amx_ftoc(c->second->position[2]);
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				cell *result = NULL;
				amx_GetAddr(amx, params[4], &result);
				switch (static_cast<int>(params[3]))
				{
					case NextX:
					{
						*result = amx_ftoc(r->second->next[0]);
						return 1;
					}
					break;
					case NextY:
					{
						*result = amx_ftoc(r->second->next[1]);
						return 1;
					}
					break;
					case NextZ:
					{
						*result = amx_ftoc(r->second->next[2]);
						return 1;
					}
					break;
					break;
					case Size:
					{
						*result = amx_ftoc(r->second->size);
						return 1;
					}
					break;
					case StreamDistance:
					{
						float streamDistance = sqrt(r->second->streamDistance);
						*result = amx_ftoc(streamDistance);
						return 1;
					}
					break;
					case X:
					{
						*result = amx_ftoc(r->second->position[0]);
						return 1;
					}
					break;
					case Y:
					{
						*result = amx_ftoc(r->second->position[1]);
						return 1;
					}
					break;
					case Z:
					{
						*result = amx_ftoc(r->second->position[2]);
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				cell *result = NULL;
				amx_GetAddr(amx, params[4], &result);
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						float streamDistance = sqrt(m->second->streamDistance);
						*result = amx_ftoc(streamDistance);
						return 1;
					}
					break;
					case X:
					{
						*result = amx_ftoc(m->second->position[0]);
						return 1;
					}
					break;
					case Y:
					{
						*result = amx_ftoc(m->second->position[1]);
						return 1;
					}
					break;
					case Z:
					{
						*result = amx_ftoc(m->second->position[2]);
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				cell *result = NULL;
				amx_GetAddr(amx, params[4], &result);
				switch (static_cast<int>(params[3]))
				{
					case DrawDistance:
					{
						*result = amx_ftoc(t->second->drawDistance);
						return 1;
					}
					break;
					case StreamDistance:
					{
						float streamDistance = sqrt(t->second->streamDistance);
						*result = amx_ftoc(streamDistance);
						return 1;
					}
					break;
					case X:
					{
						*result = amx_ftoc(t->second->position[0]);
						return 1;
					}
					break;
					case Y:
					{
						*result = amx_ftoc(t->second->position[1]);
						return 1;
					}
					break;
					case Z:
					{
						*result = amx_ftoc(t->second->position[2]);
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				cell *result = NULL;
				amx_GetAddr(amx, params[4], &result);
				switch (static_cast<int>(params[3]))
				{
					case X:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							{
								*result = amx_ftoc(boost::get<Eigen::Vector2f>(a->second->position)[0]);
							}
							break;
							case STREAMER_AREA_TYPE_SPHERE:
							{
								*result = amx_ftoc(boost::get<Eigen::Vector3f>(a->second->position)[0]);
							}
							break;
						}
						return 1;
					}
					break;
					case Y:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							{
								*result = amx_ftoc(boost::get<Eigen::Vector2f>(a->second->position)[1]);
							}
							break;
							case STREAMER_AREA_TYPE_SPHERE:
							{
								*result = amx_ftoc(boost::get<Eigen::Vector3f>(a->second->position)[1]);
							}
							break;
						}
						return 1;
					}
					break;
					case Z:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_SPHERE:
							{
								*result = amx_ftoc(boost::get<Eigen::Vector3f>(a->second->position)[2]);
							}
							break;
						}
						return 1;
					}
					break;
					case MaxX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								*result = amx_ftoc(boost::get<Element::Box2D>(a->second->position).max_corner()[0]);
							}
							break;
							case STREAMER_AREA_TYPE_CUBE:
							{
								*result = amx_ftoc(boost::get<Element::Box3D>(a->second->position).max_corner()[0]);
							}
							break;
						}
						return 1;
					}
					break;
					case MaxY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								*result = amx_ftoc(boost::get<Element::Box2D>(a->second->position).max_corner()[1]);
							}
							break;
							case STREAMER_AREA_TYPE_CUBE:
							{
								*result = amx_ftoc(boost::get<Element::Box3D>(a->second->position).max_corner()[1]);
							}
							break;
						}
						return 1;
					}
					break;
					case MaxZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBE:
							{
								*result = amx_ftoc(boost::get<Element::Box3D>(a->second->position).max_corner()[2]);
							}
							break;
							case STREAMER_AREA_TYPE_POLYGON:
							{
								*result = amx_ftoc(boost::get<Element::Polygon2D>(a->second->position).get<1>()[1]);
							}
							break;
						}
						return 1;
					}
					break;
					case MinX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								*result = amx_ftoc(boost::get<Element::Box2D>(a->second->position).min_corner()[0]);
							}
							break;
							case STREAMER_AREA_TYPE_CUBE:
							{
								*result = amx_ftoc(boost::get<Element::Box3D>(a->second->position).min_corner()[0]);
							}
							break;
						}
						return 1;
					}
					break;
					case MinY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								*result = amx_ftoc(boost::get<Element::Box2D>(a->second->position).min_corner()[1]);
							}
							break;
							case STREAMER_AREA_TYPE_CUBE:
							{
								*result = amx_ftoc(boost::get<Element::Box3D>(a->second->position).min_corner()[0]);
							}
							break;
						}
						return 1;
					}
					break;
					case MinZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBE:
							{
								*result = amx_ftoc(boost::get<Element::Box3D>(a->second->position).min_corner()[2]);
							}
							break;
							case STREAMER_AREA_TYPE_POLYGON:
							{
								*result = amx_ftoc(boost::get<Element::Polygon2D>(a->second->position).get<1>()[0]);
							}
							break;
						}
						return 1;
					}
					break;
					case Size:
					{
						float size = sqrt(a->second->size);
						*result = amx_ftoc(size);
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
		}
		break;
		default:
		{
			logprintf("*** Streamer_GetFloatData: Invalid type specified");
		}
		break;
	}
	return 0;
}

int Manipulation::setFloatData(AMX *amx, cell *params)
{
	bool reassign = false, update = false;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case DrawDistance:
					{
						o->second->drawDistance = amx_ctof(params[4]);
						update = true;
					}
					break;
					case MoveRX:
					case MoveRY:
					case MoveRZ:
					case MoveSpeed:
					case MoveX:
					case MoveY:
					case MoveZ:
					{
						logprintf("*** Streamer_SetFloatData: Use MoveDynamicObject to adjust moving object data");
					}
					break;
					case RX:
					{
						o->second->rotation[0] = amx_ctof(params[4]);
						update = true;
					}
					break;
					case RY:
					{
						o->second->rotation[1] = amx_ctof(params[4]);
						update = true;
					}
					break;
					case RZ:
					{
						o->second->rotation[2] = amx_ctof(params[4]);
						update = true;
					}
					break;
					case StreamDistance:
					{
						o->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case X:
					{
						if (o->second->move)
						{
							logprintf("*** Streamer_SetFloatData: Object must be stopped first");
							return 0;
						}
						o->second->position[0] = amx_ctof(params[4]);
						if (o->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Y:
					{
						if (o->second->move)
						{
							logprintf("*** Streamer_SetFloatData: Object must be stopped first");
							return 0;
						}
						o->second->position[1] = amx_ctof(params[4]);
						if (o->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Z:
					{
						if (o->second->move)
						{
							logprintf("*** Streamer_SetFloatData: Object must be stopped first");
							return 0;
						}
						o->second->position[2] = amx_ctof(params[4]);
						update = true;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
					}
					break;
				}
				if (reassign)
				{
					core->getGrid()->removeObject(o->second, true);
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
						if (i != p->second.internalObjects.end())
						{
							sampgdk::DestroyPlayerObject(p->first, i->second);
							i->second = sampgdk::CreatePlayerObject(p->first, o->second->modelID, o->second->position[0], o->second->position[1], o->second->position[2], o->second->rotation[0], o->second->rotation[1], o->second->rotation[2], o->second->drawDistance);
							if (o->second->move)
							{
								sampgdk::MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
							}
						}
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						p->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case X:
					{
						p->second->position[0] = amx_ctof(params[4]);
						if (p->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Y:
					{
						p->second->position[1] = amx_ctof(params[4]);
						if (p->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Z:
					{
						p->second->position[2] = amx_ctof(params[4]);
						update = true;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
					}
					break;
				}
				if (reassign)
				{
					core->getGrid()->removePickup(p->second, true);
				}
				if (update)
				{
					boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.find(p->first);
					if (i != core->getStreamer()->internalPickups.end())
					{
						sampgdk::DestroyPickup(i->second);
						i->second = sampgdk::CreatePickup(p->second->modelID, p->second->type, p->second->position[0], p->second->position[1], p->second->position[2], p->second->worldID);
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Size:
					{
						c->second->size = amx_ctof(params[4]);
						update = true;
					}
					break;
					case StreamDistance:
					{
						c->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case X:
					{
						c->second->position[0] = amx_ctof(params[4]);
						if (c->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Y:
					{
						c->second->position[1] = amx_ctof(params[4]);
						if (c->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Z:
					{
						c->second->position[2] = amx_ctof(params[4]);
						update = true;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
					}
					break;
				}
				if (reassign)
				{
					core->getGrid()->removeCheckpoint(c->second, true);
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						if (p->second.visibleCheckpoint == c->first)
						{
							sampgdk::DisablePlayerCheckpoint(p->first);
							sampgdk::SetPlayerCheckpoint(p->first, c->second->position[0], c->second->position[1], c->second->position[2], c->second->size);
						}
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case NextX:
					{
						r->second->next[0] = amx_ctof(params[4]);
						update = true;
					}
					break;
					case NextY:
					{
						r->second->next[1] = amx_ctof(params[4]);
						update = true;
					}
					break;
					case NextZ:
					{
						r->second->next[2] = amx_ctof(params[4]);
						update = true;
					}
					break;
					break;
					case Size:
					{
						r->second->size = amx_ctof(params[4]);
						update = true;
					}
					break;
					case StreamDistance:
					{
						r->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case X:
					{
						r->second->position[0] = amx_ctof(params[4]);
						if (r->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Y:
					{
						r->second->position[1] = amx_ctof(params[4]);
						if (r->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Z:
					{
						r->second->position[2] = amx_ctof(params[4]);
						update = true;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data for type specified");
					}
					break;
				}
				if (reassign)
				{
					core->getGrid()->removeRaceCheckpoint(r->second, true);
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						if (p->second.visibleRaceCheckpoint == r->first)
						{
							sampgdk::DisablePlayerRaceCheckpoint(p->first);
							sampgdk::SetPlayerRaceCheckpoint(p->first, r->second->type, r->second->position[0], r->second->position[1], r->second->position[2], r->second->next[0], r->second->next[1], r->second->next[2], r->second->size);
						}
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						m->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case X:
					{
						m->second->position[0] = amx_ctof(params[4]);
						if (m->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Y:
					{
						m->second->position[1] = amx_ctof(params[4]);
						if (m->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Z:
					{
						m->second->position[2] = amx_ctof(params[4]);
						update = true;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
					}
					break;
				}
				if (reassign)
				{
					core->getGrid()->removeMapIcon(m->second, true);
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
						if (i != p->second.internalMapIcons.end())
						{
							sampgdk::RemovePlayerMapIcon(p->first, i->second);
							sampgdk::SetPlayerMapIcon(p->first, i->second, m->second->position[0], m->second->position[1], m->second->position[2], m->second->type, m->second->color, m->second->style);
						}
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case DrawDistance:
					{
						t->second->drawDistance = amx_ctof(params[4]);
						update = true;
					}
					break;
					case StreamDistance:
					{
						t->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case X:
					{
						t->second->position[0] = amx_ctof(params[4]);
						if (t->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Y:
					{
						t->second->position[1] = amx_ctof(params[4]);
						if (t->second->cell)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Z:
					{
						t->second->position[2] = amx_ctof(params[4]);
						update = true;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
					}
					break;
				}
				if (reassign)
				{
					core->getGrid()->removeTextLabel(t->second, true);
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
						if (i != p->second.internalTextLabels.end())
						{
							sampgdk::DeletePlayer3DTextLabel(p->first, i->second);
							i->second = sampgdk::CreatePlayer3DTextLabel(p->first, t->second->text.c_str(), t->second->color, t->second->position[0], t->second->position[1], t->second->position[2], t->second->drawDistance, (t->second->attach ? t->second->attach->player : INVALID_GENERIC_ID), (t->second->attach ? t->second->attach->vehicle : INVALID_GENERIC_ID), t->second->testLOS);
						}
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case X:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							{
								boost::get<Eigen::Vector2f>(a->second->position)[0] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
							case STREAMER_AREA_TYPE_SPHERE:
							{
								boost::get<Eigen::Vector3f>(a->second->position)[0] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
						}
					}
					break;
					case Y:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							{
								boost::get<Eigen::Vector2f>(a->second->position)[1] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
							case STREAMER_AREA_TYPE_SPHERE:
							{
								boost::get<Eigen::Vector3f>(a->second->position)[1] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
						}
					}
					break;
					case Z:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_SPHERE:
							{
								boost::get<Eigen::Vector3f>(a->second->position)[2] = amx_ctof(params[4]);
							}
							break;
						}
					}
					break;
					case MaxX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								boost::get<Element::Box2D>(a->second->position).max_corner()[0] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Element::Box3D>(a->second->position).max_corner()[0] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
						}
					}
					break;
					case MaxY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								boost::get<Element::Box2D>(a->second->position).max_corner()[1] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Element::Box3D>(a->second->position).max_corner()[1] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
						}
					}
					break;
					case MaxZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Element::Box3D>(a->second->position).max_corner()[2] = amx_ctof(params[4]);
							}
							break;
							case STREAMER_AREA_TYPE_POLYGON:
							{
								boost::get<Element::Polygon2D>(a->second->position).get<1>()[1] = amx_ctof(params[4]);
							}
							break;
						}
					}
					break;
					case MinX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								boost::get<Element::Box2D>(a->second->position).min_corner()[0] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Element::Box3D>(a->second->position).min_corner()[0] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
						}
					}
					break;
					case MinY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								boost::get<Element::Box2D>(a->second->position).min_corner()[1] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Element::Box3D>(a->second->position).min_corner()[1] = amx_ctof(params[4]);
								reassign = true;
							}
							break;
						}
						return 1;
					}
					break;
					case MinZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Element::Box3D>(a->second->position).min_corner()[2] = amx_ctof(params[4]);
							}
							break;
							case STREAMER_AREA_TYPE_POLYGON:
							{
								boost::get<Element::Polygon2D>(a->second->position).get<1>()[0] = amx_ctof(params[4]);
							}
							break;
						}
					}
					break;
					case Size:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							case STREAMER_AREA_TYPE_SPHERE:
							{
								a->second->size = amx_ctof(params[4]) * amx_ctof(params[4]);
								reassign = true;
							}
							break;
						}
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
					}
					break;
				}
				if (reassign)
				{
					switch (a->second->type)
					{
						case STREAMER_AREA_TYPE_RECTANGLE:
						{
							boost::geometry::correct(boost::get<Element::Box2D>(a->second->position));
							a->second->size = boost::geometry::comparable_distance(boost::get<Element::Box2D>(a->second->position).min_corner(), boost::get<Element::Box2D>(a->second->position).max_corner());
						}
						break;
						case STREAMER_AREA_TYPE_CUBE:
						{
							boost::geometry::correct(boost::get<Element::Box3D>(a->second->position));
							a->second->size = boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Element::Box3D>(a->second->position).min_corner()[0], boost::get<Element::Box3D>(a->second->position).min_corner()[1]), Eigen::Vector2f(boost::get<Element::Box3D>(a->second->position).max_corner()[0], boost::get<Element::Box3D>(a->second->position).max_corner()[1]));
						}
						break;
					}
					core->getGrid()->removeArea(a->second, true);
					return 1;
				}
				return 0;
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
		}
		break;
		default:
		{
			logprintf("*** Streamer_SetFloatData: Invalid type specified");
		}
		break;
	}
	return 0;
}

int Manipulation::getIntData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						return o->second->extraID;
					}
					break;
					case ModelID:
					{
						return o->second->modelID;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						return p->second->extraID;
					}
					break;
					case ModelID:
					{
						return p->second->modelID;
					}
					break;
					case Type:
					{
						return p->second->type;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						return c->second->extraID;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						return r->second->extraID;
					}
					break;
					case Type:
					{
						return r->second->type;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Color:
					{
						return m->second->color;
					}
					break;
					case ExtraID:
					{
						return m->second->extraID;
					}
					break;
					case Style:
					{
						return m->second->style;
					}
					break;
					case Type:
					{
						return m->second->type;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedPlayer:
					{
						if (t->second->attach)
						{
							return t->second->attach->player;
						}
						else
						{
							return INVALID_GENERIC_ID;
						}
					}
					break;
					case AttachedVehicle:
					{
						if (t->second->attach)
						{
							return t->second->attach->vehicle;
						}
						else
						{
							return INVALID_GENERIC_ID;
						}
					}
					break;
					case Color:
					{
						return t->second->color;
					}
					break;
					case ExtraID:
					{
						return t->second->extraID;
					}
					break;
					case TestLOS:
					{
						return t->second->testLOS;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedPlayer:
					{
						if (a->second->attach)
						{
							return a->second->attach->player;
						}
						else
						{
							return INVALID_GENERIC_ID;
						}
					}
					break;
					case AttachedVehicle:
					{
						if (a->second->attach)
						{
							return a->second->attach->vehicle;
						}
						else
						{
							return INVALID_GENERIC_ID;
						}
					}
					break;
					case ExtraID:
					{
						return a->second->extraID;
					}
					break;
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
		}
		break;
		default:
		{
			logprintf("*** Streamer_GetIntData: Invalid type specified");
		}
		break;
	}
	return 0;
}


int Manipulation::setIntData(AMX *amx, cell *params)
{
	bool update = false;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						o->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					break;
					case ModelID:
					{
						o->second->modelID = static_cast<int>(params[4]);
						update = true;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
					}
					break;
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
						if (i != p->second.internalObjects.end())
						{
							sampgdk::DestroyPlayerObject(p->first, i->second);
							i->second = sampgdk::CreatePlayerObject(p->first, o->second->modelID, o->second->position[0], o->second->position[1], o->second->position[2], o->second->rotation[0], o->second->rotation[1], o->second->rotation[2], o->second->drawDistance);
							if (o->second->move)
							{
								sampgdk::MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
							}
						}
					}
					return 1;
				}
				return 0;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						p->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					break;
					case ModelID:
					{
						p->second->modelID = static_cast<int>(params[4]);
						update = true;
					}
					break;
					case Type:
					{
						p->second->type = static_cast<int>(params[4]);
						update = true;
					}
					break;
					case WorldID:
					{
						p->second->worldID = static_cast<int>(params[4]);
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
					}
					break;
				}
				if (update)
				{
					boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.find(p->first);
					if (i != core->getStreamer()->internalPickups.end())
					{
						sampgdk::DestroyPickup(i->second);
						i->second = sampgdk::CreatePickup(p->second->modelID, p->second->type, p->second->position[0], p->second->position[1], p->second->position[2], p->second->worldID);
					}
					return 1;
				}
				return 0;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						c->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						r->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					break;
					case Type:
					{
						r->second->type = static_cast<int>(params[4]);
						update = true;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
					}
					break;
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						if (p->second.visibleRaceCheckpoint == r->first)
						{
							sampgdk::DisablePlayerRaceCheckpoint(p->first);
							sampgdk::SetPlayerRaceCheckpoint(p->first, r->second->type, r->second->position[0], r->second->position[1], r->second->position[2], r->second->next[0], r->second->next[1], r->second->next[2], r->second->size);
						}
					}
					return 1;
				}
				return 0;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Color:
					{
						m->second->color = static_cast<int>(params[4]);
						update = true;
					}
					break;
					case ExtraID:
					{
						m->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					break;
					case Style:
					{
						m->second->style = static_cast<int>(params[4]);
						update = true;
					}
					break;
					case Type:
					{
						m->second->type = static_cast<int>(params[4]);
						update = true;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
					}
					break;
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
						if (i != p->second.internalMapIcons.end())
						{
							sampgdk::RemovePlayerMapIcon(p->first, i->second);
							sampgdk::SetPlayerMapIcon(p->first, i->second, m->second->position[0], m->second->position[1], m->second->position[2], m->second->type, m->second->color, m->second->style);
						}
					}
					return 1;
				}
				return 0;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedPlayer:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							t->second->attach = boost::intrusive_ptr<Element::TextLabel::Attach>(new Element::TextLabel::Attach);
							t->second->attach->player = static_cast<int>(params[4]);
							t->second->attach->vehicle = INVALID_GENERIC_ID;
							core->getStreamer()->attachedTextLabels.insert(t->second);
						}
						else
						{
							if (t->second->attach)
							{
								if (t->second->attach->player != INVALID_GENERIC_ID)
								{
									t->second->attach.reset();
									core->getStreamer()->attachedTextLabels.erase(t->second);
								}
							}
						}
						update = true;
					}
					break;
					case AttachedVehicle:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							t->second->attach = boost::intrusive_ptr<Element::TextLabel::Attach>(new Element::TextLabel::Attach);
							t->second->attach->player = INVALID_GENERIC_ID;
							t->second->attach->vehicle = static_cast<int>(params[4]);
							core->getStreamer()->attachedTextLabels.insert(t->second);
						}
						else
						{
							if (t->second->attach)
							{
								if (t->second->attach->vehicle != INVALID_GENERIC_ID)
								{
									t->second->attach.reset();
									core->getStreamer()->attachedTextLabels.erase(t->second);
								}
							}
						}
						update = true;
					}
					break;
					case Color:
					{
						t->second->color = static_cast<int>(params[4]);
						update = true;
					}
					break;
					case ExtraID:
					{
						t->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					break;
					case TestLOS:
					{
						t->second->testLOS = static_cast<int>(params[4]) != 0;
						update = true;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
					}
					break;
				}
				if (update)
				{
					if (t->second->attach)
					{
						if (t->second->position.cwiseAbs().maxCoeff() > 50.0f)
						{
							t->second->position.setZero();
						}
					}
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
						if (i != p->second.internalTextLabels.end())
						{
							sampgdk::DeletePlayer3DTextLabel(p->first, i->second);
							i->second = sampgdk::CreatePlayer3DTextLabel(p->first, t->second->text.c_str(), t->second->color, t->second->position[0], t->second->position[1], t->second->position[2], t->second->drawDistance, (t->second->attach ? t->second->attach->player : INVALID_GENERIC_ID), (t->second->attach ? t->second->attach->vehicle : INVALID_GENERIC_ID), t->second->testLOS);
						}
					}
					return 1;
				}
				return 0;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedPlayer:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							a->second->attach = boost::intrusive_ptr<Element::Area::Attach>(new Element::Area::Attach);
							a->second->attach->player = static_cast<int>(params[4]);
							a->second->attach->vehicle = INVALID_GENERIC_ID;
							core->getStreamer()->attachedAreas.insert(a->second);
						}
						else
						{
							if (a->second->attach)
							{
								if (a->second->attach->player != INVALID_GENERIC_ID)
								{
									a->second->attach.reset();
									core->getStreamer()->attachedAreas.erase(a->second);
								}
							}
						}
						return 1;
					}
					break;
					case AttachedVehicle:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							a->second->attach = boost::intrusive_ptr<Element::Area::Attach>(new Element::Area::Attach);
							a->second->attach->player = INVALID_GENERIC_ID;
							a->second->attach->vehicle = static_cast<int>(params[4]);
							core->getStreamer()->attachedAreas.insert(a->second);
						}
						else
						{
							if (a->second->attach)
							{
								if (a->second->attach->vehicle != INVALID_GENERIC_ID)
								{
									a->second->attach.reset();
									core->getStreamer()->attachedAreas.erase(a->second);
								}
							}
						}
						return 1;
					}
					break;
					case ExtraID:
					{
						a->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
		}
		break;
		default:
		{
			logprintf("*** Streamer_SetIntData: Invalid type specified");
		}
		break;
	}
	return 0;
}

int Manipulation::isInArrayData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (o->second->interiors.find(static_cast<int>(params[4])) != o->second->interiors.end())
							{
								return 1;
							}
						}
						else
						{
							if (o->second->interiors.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case PlayerID:
					{
						if (static_cast<size_t>(params[4]) >= 0 && static_cast<size_t>(params[4]) < o->second->players.size())
						{
							if (o->second->players[static_cast<size_t>(params[4])])
							{
								return 1;
							}
						}
						else
						{
							if (o->second->players.count() == o->second->players.size())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case WorldID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (o->second->worlds.find(static_cast<int>(params[4])) != o->second->worlds.end())
							{
								return 1;
							}
						}
						else
						{
							if (o->second->worlds.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					default:
					{
						logprintf("*** Streamer_IsInArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_IsInArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (p->second->interiors.find(static_cast<int>(params[4])) != p->second->interiors.end())
							{
								return 1;
							}
						}
						else
						{
							if (p->second->interiors.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case PlayerID:
					{
						if (static_cast<size_t>(params[4]) >= 0 && static_cast<size_t>(params[4]) < p->second->players.size())
						{
							if (p->second->players[static_cast<size_t>(params[4])])
							{
								return 1;
							}
						}
						else
						{
							if (p->second->players.count() == p->second->players.size())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case WorldID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (p->second->worlds.find(static_cast<int>(params[4])) != p->second->worlds.end())
							{
								return 1;
							}
						}
						else
						{
							if (p->second->worlds.empty())
							{
								return 1;
							}
						}
					}
					break;
					default:
					{
						logprintf("*** Streamer_IsInArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_IsInArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (c->second->interiors.find(static_cast<int>(params[4])) != c->second->interiors.end())
							{
								return 1;
							}
						}
						else
						{
							if (c->second->interiors.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case PlayerID:
					{
						if (static_cast<size_t>(params[4]) >= 0 && static_cast<size_t>(params[4]) < c->second->players.size())
						{
							if (c->second->players[static_cast<size_t>(params[4])])
							{
								return 1;
							}
						}
						else
						{
							if (c->second->players.count() == c->second->players.size())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case WorldID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (c->second->worlds.find(static_cast<int>(params[4])) != c->second->worlds.end())
							{
								return 1;
							}
						}
						else
						{
							if (c->second->worlds.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					default:
					{
						logprintf("*** Streamer_IsInArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_IsInArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (r->second->interiors.find(static_cast<int>(params[4])) != r->second->interiors.end())
							{
								return 1;
							}
						}
						else
						{
							if (r->second->interiors.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case PlayerID:
					{
						if (static_cast<size_t>(params[4]) >= 0 && static_cast<size_t>(params[4]) < r->second->players.size())
						{
							if (r->second->players[static_cast<size_t>(params[4])])
							{
								return 1;
							}
						}
						else
						{
							if (r->second->players.count() == r->second->players.size())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case WorldID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (r->second->worlds.find(static_cast<int>(params[4])) != r->second->worlds.end())
							{
								return 1;
							}
						}
						else
						{
							if (r->second->worlds.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					default:
					{
						logprintf("*** Streamer_IsInArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_IsInArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (m->second->interiors.find(static_cast<int>(params[4])) != m->second->interiors.end())
							{
								return 1;
							}
						}
						else
						{
							if (m->second->interiors.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case PlayerID:
					{
						if (static_cast<size_t>(params[4]) >= 0 && static_cast<size_t>(params[4]) < m->second->players.size())
						{
							if (m->second->players[static_cast<size_t>(params[4])])
							{
								return 1;
							}
						}
						else
						{
							if (m->second->players.count() == m->second->players.size())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case WorldID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (m->second->worlds.find(static_cast<int>(params[4])) != m->second->worlds.end())
							{
								return 1;
							}
						}
						else
						{
							if (m->second->worlds.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					default:
					{
						logprintf("*** Streamer_IsInArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_IsInArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (t->second->interiors.find(static_cast<int>(params[4])) != t->second->interiors.end())
							{
								return 1;
							}
						}
						else
						{
							if (t->second->interiors.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case PlayerID:
					{
						if (static_cast<size_t>(params[4]) >= 0 && static_cast<size_t>(params[4]) < t->second->players.size())
						{
							if (t->second->players[static_cast<size_t>(params[4])])
							{
								return 1;
							}
						}
						else
						{
							if (t->second->players.count() == t->second->players.size())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case WorldID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (t->second->worlds.find(static_cast<int>(params[4])) != t->second->worlds.end())
							{
								return 1;
							}
						}
						else
						{
							if (t->second->worlds.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					default:
					{
						logprintf("*** Streamer_IsInArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_IsInArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (a->second->interiors.find(static_cast<int>(params[4])) != a->second->interiors.end())
							{
								return 1;
							}
						}
						else
						{
							if (a->second->interiors.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case PlayerID:
					{
						if (static_cast<size_t>(params[4]) >= 0 && static_cast<size_t>(params[4]) < a->second->players.size())
						{
							if (a->second->players[static_cast<size_t>(params[4])])
							{
								return 1;
							}
						}
						else
						{
							if (a->second->players.count() == a->second->players.size())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case WorldID:
					{
						if (static_cast<int>(params[4]) >= 0)
						{
							if (a->second->worlds.find(static_cast<int>(params[4])) != a->second->worlds.end())
							{
								return 1;
							}
						}
						else
						{
							if (a->second->worlds.empty())
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					default:
					{
						logprintf("*** Streamer_IsInArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_IsInArrayData: Invalid ID specified");
		}
		break;
		default:
		{
			logprintf("*** Streamer_IsInArrayData: Invalid type specified");
		}
		break;
	}
	return 0;
}

int Manipulation::appendArrayData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::addToContainer(o->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::addToContainer(o->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::addToContainer(o->second->worlds, static_cast<int>(params[4]));
						return 1;
					}
					break;
					default:
					{
						logprintf("*** Streamer_AppendArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_AppendArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::addToContainer(p->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::addToContainer(p->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::addToContainer(p->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_AppendArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_AppendArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::addToContainer(c->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::addToContainer(c->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::addToContainer(c->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_AppendArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_AppendArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::addToContainer(r->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::addToContainer(r->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::addToContainer(r->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_AppendArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_AppendArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::addToContainer(m->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::addToContainer(m->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::addToContainer(m->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_AppendArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_AppendArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::addToContainer(t->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::addToContainer(t->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::addToContainer(t->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_AppendArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_AppendArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::addToContainer(a->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::addToContainer(a->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::addToContainer(a->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_AppendArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_AppendArrayData: Invalid ID specified");
		}
		break;
		default:
		{
			logprintf("*** Streamer_AppendArrayData: Invalid type specified");
		}
		break;
	}
	return 0;
}

int Manipulation::removeArrayData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::removeFromContainer(o->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::removeFromContainer(o->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::removeFromContainer(o->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_RemoveArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_RemoveArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::removeFromContainer(p->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::removeFromContainer(p->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::removeFromContainer(p->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_RemoveArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_RemoveArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::removeFromContainer(c->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::removeFromContainer(c->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::removeFromContainer(c->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_RemoveArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_RemoveArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::removeFromContainer(r->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::removeFromContainer(r->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::removeFromContainer(r->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_RemoveArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_RemoveArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::removeFromContainer(m->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::removeFromContainer(m->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::removeFromContainer(m->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_RemoveArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_RemoveArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::removeFromContainer(t->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::removeFromContainer(t->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::removeFromContainer(t->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_RemoveArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_RemoveArrayData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case InteriorID:
					{
						Utility::removeFromContainer(a->second->interiors, static_cast<int>(params[4]));
						return 1;
					}
					break;
					case PlayerID:
					{
						Utility::removeFromContainer(a->second->players, static_cast<size_t>(params[4]));
						return 1;
					}
					break;
					case WorldID:
					{
						Utility::removeFromContainer(a->second->worlds, static_cast<int>(params[4]));
					}
					break;
					default:
					{
						logprintf("*** Streamer_RemoveArrayData: Invalid data specified");
					}
					break;
				}
				return 0;
			}
			logprintf("*** Streamer_RemoveArrayData: Invalid ID specified");
		}
		break;
		default:
		{
			logprintf("*** Streamer_RemoveArrayData: Invalid type specified");
		}
		break;
	}
	return 0;
}
