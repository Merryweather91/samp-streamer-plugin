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
#include "Manipulation.h"

using namespace Manipulation;

int Manipulation::getFloatData(AMX * amx, cell * params)
{
	switch ((int)params[1])
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Core::SharedObject>::iterator o = core->objects.find((int)params[2]);
			if (o != core->objects.end())
			{
				cell * result;
				amx_GetAddr(amx, params[4], &result);
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						float distance = sqrt(o->second->distance);
						* result = amx_ftoc(distance);
						return 1;
					}
					break;
					case Data::DrawDistance:
					{
						* result = amx_ftoc(o->second->drawDistance);
						return 1;
					}
					break;
					case Data::MoveSpeed:
					{
						if (o->second->move)
						{
							* result = amx_ftoc(o->second->move->speed);
							return 1;
						}
					}
					break;
					case Data::MoveX:
					{
						if (o->second->move)
						{
							* result = amx_ftoc(o->second->move->x);
							return 1;
						}
					}
					break;
					case Data::MoveY:
					{
						if (o->second->move)
						{
							* result = amx_ftoc(o->second->move->y);
							return 1;
						}
					}
					break;
					case Data::MoveZ:
					{
						if (o->second->move)
						{
							* result = amx_ftoc(o->second->move->z);
							return 1;
						}
					}
					break;
					case Data::RX:
					{
						* result = amx_ftoc(o->second->rX);
						return 1;
					}
					break;
					case Data::RY:
					{
						* result = amx_ftoc(o->second->rY);
						return 1;
					}
					break;
					case Data::RZ:
					{
						* result = amx_ftoc(o->second->rZ);
						return 1;
					}
					break;
					case Data::X:
					{
						* result = amx_ftoc(o->second->x);
						return 1;
					}
					break;
					case Data::Y:
					{
						* result = amx_ftoc(o->second->y);
						return 1;
					}
					break;
					case Data::Z:
					{
						* result = amx_ftoc(o->second->z);
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
			boost::unordered_map<int, Core::SharedPickup>::iterator p = core->pickups.find((int)params[2]);
			if (p != core->pickups.end())
			{
				cell * result;
				amx_GetAddr(amx, params[4], &result);
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						float distance = sqrt(p->second->distance);
						* result = amx_ftoc(distance);
						return 1;
					}
					break;
					case Data::X:
					{
						* result = amx_ftoc(p->second->x);
						return 1;
					}
					break;
					case Data::Y:
					{
						* result = amx_ftoc(p->second->y);
						return 1;
					}
					break;
					case Data::Z:
					{
						* result = amx_ftoc(p->second->z);
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
			boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = core->checkpoints.find((int)params[2]);
			if (c != core->checkpoints.end())
			{
				cell * result;
				amx_GetAddr(amx, params[4], &result);
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						float distance = sqrt(c->second->distance);
						* result = amx_ftoc(distance);
						return 1;
					}
					break;
					case Data::Size:
					{
						* result = amx_ftoc(c->second->size);
						return 1;
					}
					break;
					case Data::X:
					{
						* result = amx_ftoc(c->second->x);
						return 1;
					}
					break;
					case Data::Y:
					{
						* result = amx_ftoc(c->second->y);
						return 1;
					}
					break;
					case Data::Z:
					{
						* result = amx_ftoc(c->second->z);
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
			boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = core->raceCheckpoints.find((int)params[2]);
			if (r != core->raceCheckpoints.end())
			{
				cell * result;
				amx_GetAddr(amx, params[4], &result);
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						float distance = sqrt(r->second->distance);
						* result = amx_ftoc(distance);
						return 1;
					}
					break;
					case Data::NextX:
					{
						* result = amx_ftoc(r->second->nextX);
						return 1;
					}
					break;
					case Data::NextY:
					{
						* result = amx_ftoc(r->second->nextY);
						return 1;
					}
					break;
					case Data::NextZ:
					{
						* result = amx_ftoc(r->second->nextZ);
						return 1;
					}
					break;
					break;
					case Data::Size:
					{
						* result = amx_ftoc(r->second->size);
						return 1;
					}
					break;
					case Data::X:
					{
						* result = amx_ftoc(r->second->x);
						return 1;
					}
					break;
					case Data::Y:
					{
						* result = amx_ftoc(r->second->y);
						return 1;
					}
					break;
					case Data::Z:
					{
						* result = amx_ftoc(r->second->z);
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
			boost::unordered_map<int, Core::SharedMapIcon>::iterator m = core->mapIcons.find((int)params[2]);
			if (m != core->mapIcons.end())
			{
				cell * result;
				amx_GetAddr(amx, params[4], &result);
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						float distance = sqrt(m->second->distance);
						* result = amx_ftoc(distance);
						return 1;
					}
					break;
					case Data::X:
					{
						* result = amx_ftoc(m->second->x);
						return 1;
					}
					break;
					case Data::Y:
					{
						* result = amx_ftoc(m->second->y);
						return 1;
					}
					break;
					case Data::Z:
					{
						* result = amx_ftoc(m->second->z);
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
			boost::unordered_map<int, Core::SharedTextLabel>::iterator t = core->textLabels.find((int)params[2]);
			if (t != core->textLabels.end())
			{
				cell * result;
				amx_GetAddr(amx, params[4], &result);
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						float distance = sqrt(t->second->distance);
						* result = amx_ftoc(distance);
						return 1;
					}
					break;
					case Data::DrawDistance:
					{
						* result = amx_ftoc(t->second->drawDistance);
						return 1;
					}
					break;
					case Data::X:
					{
						* result = amx_ftoc(t->second->x);
						return 1;
					}
					break;
					case Data::Y:
					{
						* result = amx_ftoc(t->second->y);
						return 1;
					}
					break;
					case Data::Z:
					{
						* result = amx_ftoc(t->second->z);
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
			boost::unordered_map<int, Core::SharedArea>::iterator a = core->areas.find((int)params[2]);
			if (a != core->areas.end())
			{
				cell * result;
				amx_GetAddr(amx, params[4], &result);
				switch ((int)params[3])
				{
					case Data::MinX:
					case Data::X:
					{
						* result = amx_ftoc(a->second->x1);
						return 1;
					}
					break;
					case Data::MinY:
					case Data::Y:
					{
						* result = amx_ftoc(a->second->y1);
						return 1;
					}
					break;
					case Data::MinZ:
					case Data::Z:
					{
						* result = amx_ftoc(a->second->z1);
						return 1;
					}
					break;
					case Data::MaxX:
					{
						* result = amx_ftoc(a->second->x2);
						return 1;
					}
					break;
					case Data::MaxY:
					{
						* result = amx_ftoc(a->second->y2);
						return 1;
					}
					break;
					case Data::MaxZ:
					{
						* result = amx_ftoc(a->second->z2);
						return 1;
					}
					break;
					case Data::Size:
					{
						float size = sqrt(a->second->size);
						* result = amx_ftoc(size);
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

int Manipulation::setFloatData(AMX * amx, cell * params)
{
	bool reassign = false, update = false;
	switch ((int)params[1])
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Core::SharedObject>::iterator o = core->objects.find((int)params[2]);
			if (o != core->objects.end())
			{
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						o->second->distance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case Data::DrawDistance:
					{
						o->second->drawDistance = amx_ctof(params[4]);
						update = true;
					}
					break;
					case Data::MoveSpeed:
					case Data::MoveX:
					case Data::MoveY:
					case Data::MoveZ:
					{
						logprintf("*** Streamer_SetFloatData: Use MoveDynamicObject to adjust moving object data");
					}
					break;
					case Data::RX:
					{
						o->second->rX = amx_ctof(params[4]);
						update = true;
					}
					break;
					case Data::RY:
					{
						o->second->rY = amx_ctof(params[4]);
						update = true;
					}
					break;
					case Data::RZ:
					{
						o->second->rZ = amx_ctof(params[4]);
						update = true;
					}
					break;
					case Data::X:
					{
						if (o->second->move)
						{
							logprintf("*** Streamer_SetFloatData: Object must be stopped first");
							return 0;
						}
						o->second->x = amx_ctof(params[4]);
						if (o->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Y:
					{
						if (o->second->move)
						{
							logprintf("*** Streamer_SetFloatData: Object must be stopped first");
							return 0;
						}
						o->second->y = amx_ctof(params[4]);
						if (o->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Z:
					{
						if (o->second->move)
						{
							logprintf("*** Streamer_SetFloatData: Object must be stopped first");
							return 0;
						}
						o->second->z = amx_ctof(params[4]);
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
					grid->removeObject(o->second, true);
				}
				if (update)
				{
					for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator f = p->internalObjects.find(o->first);
						if (f != p->internalObjects.end())
						{
							invoke->callNative(&PAWN::DestroyPlayerObject, p->playerID, f->second);
							f->second = invoke->callNative(&PAWN::CreatePlayerObject, p->playerID, o->second->modelID, o->second->x, o->second->y, o->second->z, o->second->rX, o->second->rY, o->second->rZ, o->second->drawDistance);
							if (o->second->move)
							{
								invoke->callNative(&PAWN::MovePlayerObject, p->playerID, f->second, o->second->move->x, o->second->move->y, o->second->move->z, o->second->move->speed);
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
			boost::unordered_map<int, Core::SharedPickup>::iterator p = core->pickups.find((int)params[2]);
			if (p != core->pickups.end())
			{
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						p->second->distance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case Data::X:
					{
						p->second->x = amx_ctof(params[4]);
						if (p->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Y:
					{
						p->second->y = amx_ctof(params[4]);
						if (p->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Z:
					{
						p->second->z = amx_ctof(params[4]);
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
					grid->removePickup(p->second, true);
				}
				if (update)
				{
					boost::unordered_map<int, int>::iterator f = core->global.internalPickups.find(p->first);
					if (f != core->global.internalPickups.end())
					{
						invoke->callNative(&PAWN::DestroyPickup, f->second);
						f->second = invoke->callNative(&PAWN::CreatePickup, p->second->modelID, p->second->type, p->second->x, p->second->y, p->second->z, p->second->worldID);
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
		}
		break;
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = core->checkpoints.find((int)params[2]);
			if (c != core->checkpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						c->second->distance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case Data::Size:
					{
						c->second->size = amx_ctof(params[4]);
						update = true;
					}
					break;
					case Data::X:
					{
						c->second->x = amx_ctof(params[4]);
						if (c->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Y:
					{
						c->second->y = amx_ctof(params[4]);
						if (c->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Z:
					{
						c->second->z = amx_ctof(params[4]);
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
					grid->removeCheckpoint(c->second, true);
				}
				if (update)
				{
					for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
					{
						if (p->visibleCheckpoint == c->first)
						{
							invoke->callNative(&PAWN::DisablePlayerCheckpoint, p->playerID);
							invoke->callNative(&PAWN::SetPlayerCheckpoint, p->playerID, c->second->x, c->second->y, c->second->z, c->second->size);
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
			boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = core->raceCheckpoints.find((int)params[2]);
			if (r != core->raceCheckpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						r->second->distance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case Data::NextX:
					{
						r->second->nextX = amx_ctof(params[4]);
						update = true;
					}
					break;
					case Data::NextY:
					{
						r->second->nextY = amx_ctof(params[4]);
						update = true;
					}
					break;
					case Data::NextZ:
					{
						r->second->nextZ = amx_ctof(params[4]);
						update = true;
					}
					break;
					break;
					case Data::Size:
					{
						r->second->size = amx_ctof(params[4]);
						update = true;
					}
					break;
					case Data::X:
					{
						r->second->x = amx_ctof(params[4]);
						if (r->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Y:
					{
						r->second->y = amx_ctof(params[4]);
						if (r->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Z:
					{
						r->second->z = amx_ctof(params[4]);
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
					grid->removeRaceCheckpoint(r->second, true);
				}
				if (update)
				{
					for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
					{
						if (p->visibleRaceCheckpoint == r->first)
						{
							invoke->callNative(&PAWN::DisablePlayerRaceCheckpoint, p->playerID);
							invoke->callNative(&PAWN::SetPlayerRaceCheckpoint, p->playerID, r->second->type, r->second->x, r->second->y, r->second->z, r->second->nextX, r->second->nextY, r->second->nextZ, r->second->size);
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
			boost::unordered_map<int, Core::SharedMapIcon>::iterator m = core->mapIcons.find((int)params[2]);
			if (m != core->mapIcons.end())
			{
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						m->second->distance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case Data::X:
					{
						m->second->x = amx_ctof(params[4]);
						if (m->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Y:
					{
						m->second->y = amx_ctof(params[4]);
						if (m->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Z:
					{
						m->second->z = amx_ctof(params[4]);
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
					grid->removeMapIcon(m->second, true);
				}
				if (update)
				{
					for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator f = p->internalMapIcons.find(m->first);
						if (f != p->internalMapIcons.end())
						{
							invoke->callNative(&PAWN::RemovePlayerMapIcon, p->playerID, f->second);
							invoke->callNative(&PAWN::SetPlayerMapIcon, p->playerID, f->second, m->second->x, m->second->y, m->second->z, m->second->type, m->second->color, m->second->style);
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
			boost::unordered_map<int, Core::SharedTextLabel>::iterator t = core->textLabels.find((int)params[2]);
			if (t != core->textLabels.end())
			{
				switch ((int)params[3])
				{
					case Data::Distance:
					{
						t->second->distance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case Data::DrawDistance:
					{
						t->second->drawDistance = amx_ctof(params[4]);
						update = true;
					}
					break;
					case Data::X:
					{
						t->second->x = amx_ctof(params[4]);
						if (t->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Y:
					{
						t->second->y = amx_ctof(params[4]);
						if (t->second->cellID)
						{
							reassign = true;
						}
						update = true;
					}
					break;
					case Data::Z:
					{
						t->second->z = amx_ctof(params[4]);
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
					grid->removeTextLabel(t->second, true);
				}
				if (update)
				{
					for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator f = p->internalTextLabels.find(t->first);
						if (f != p->internalTextLabels.end())
						{
							invoke->callNative(&PAWN::DeletePlayer3DTextLabel, p->playerID, f->second);
							f->second = invoke->callNative(&PAWN::CreatePlayer3DTextLabel, p->playerID, t->second->text.c_str(), t->second->color, t->second->x, t->second->y, t->second->z, t->second->drawDistance, (t->second->attach ? t->second->attach->player : INVALID_GENERIC_ID), (t->second->attach ? t->second->attach->vehicle : INVALID_GENERIC_ID), t->second->testLOS);
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
			boost::unordered_map<int, Core::SharedArea>::iterator a = core->areas.find((int)params[2]);
			if (a != core->areas.end())
			{
				switch ((int)params[3])
				{
					case Data::MinX:
					case Data::X:
					{
						a->second->x1 = amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case Data::MinY:
					case Data::Y:
					{
						a->second->y1 = amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case Data::MinZ:
					case Data::Z:
					{
						a->second->z1 = amx_ctof(params[4]);
						return 1;
					}
					break;
					case Data::MaxX:
					{
						a->second->x2 = amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case Data::MaxY:
					{
						a->second->y2 = amx_ctof(params[4]);
						reassign = true;
					}
					break;
					case Data::MaxZ:
					{
						a->second->z2 = amx_ctof(params[4]);
						return 1;
					}
					break;
					case Data::Size:
					{
						a->second->size = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
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
					grid->removeArea(a->second, true);
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

int Manipulation::getIntData(AMX * amx, cell * params)
{
	switch ((int)params[1])
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Core::SharedObject>::iterator o = core->objects.find((int)params[2]);
			if (o != core->objects.end())
			{
				switch ((int)params[3])
				{
					case Data::ExtraID:
					{
						return o->second->extraID;
					}
					break;
					case Data::ModelID:
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
			boost::unordered_map<int, Core::SharedPickup>::iterator p = core->pickups.find((int)params[2]);
			if (p != core->pickups.end())
			{
				switch ((int)params[3])
				{
					case Data::ExtraID:
					{
						return p->second->extraID;
					}
					break;
					case Data::ModelID:
					{
						return p->second->modelID;
					}
					break;
					case Data::Type:
					{
						return p->second->type;
					}
					break;
					case Data::WorldID:
					{
						return p->second->worldID;
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
			boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = core->checkpoints.find((int)params[2]);
			if (c != core->checkpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::ExtraID:
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
			boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = core->raceCheckpoints.find((int)params[2]);
			if (r != core->raceCheckpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::ExtraID:
					{
						return r->second->extraID;
					}
					break;
					case Data::Type:
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
			boost::unordered_map<int, Core::SharedMapIcon>::iterator m = core->mapIcons.find((int)params[2]);
			if (m != core->mapIcons.end())
			{
				switch ((int)params[3])
				{
					case Data::Color:
					{
						return m->second->color;
					}
					break;
					case Data::ExtraID:
					{
						return m->second->extraID;
					}
					break;
					case Data::Style:
					{
						return m->second->style;
					}
					break;
					case Data::Type:
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
			boost::unordered_map<int, Core::SharedTextLabel>::iterator t = core->textLabels.find((int)params[2]);
			if (t != core->textLabels.end())
			{
				switch ((int)params[3])
				{
					case Data::AttachedPlayer:
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
					case Data::AttachedVehicle:
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
					case Data::Color:
					{
						return t->second->color;
					}
					break;
					case Data::ExtraID:
					{
						return t->second->extraID;
					}
					break;
					case Data::TestLOS:
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
			boost::unordered_map<int, Core::SharedArea>::iterator a = core->areas.find((int)params[2]);
			if (a != core->areas.end())
			{
				switch ((int)params[3])
				{
					case Data::AttachedPlayer:
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
					case Data::AttachedVehicle:
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
					case Data::ExtraID:
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


int Manipulation::setIntData(AMX * amx, cell * params)
{
	bool update = false;
	switch ((int)params[1])
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Core::SharedObject>::iterator o = core->objects.find((int)params[2]);
			if (o != core->objects.end())
			{
				switch ((int)params[3])
				{
					case Data::ExtraID:
					{
						o->second->extraID = (int)params[4];
						return 1;
					}
					break;
					case Data::ModelID:
					{
						o->second->modelID = (int)params[4];
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
					for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator f = p->internalObjects.find(o->first);
						if (f != p->internalObjects.end())
						{
							invoke->callNative(&PAWN::DestroyPlayerObject, p->playerID, f->second);
							f->second = invoke->callNative(&PAWN::CreatePlayerObject, p->playerID, o->second->modelID, o->second->x, o->second->y, o->second->z, o->second->rX, o->second->rY, o->second->rZ, o->second->drawDistance);
							if (o->second->move)
							{
								invoke->callNative(&PAWN::MovePlayerObject, p->playerID, f->second, o->second->move->x, o->second->move->y, o->second->move->z, o->second->move->speed);
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
			boost::unordered_map<int, Core::SharedPickup>::iterator p = core->pickups.find((int)params[2]);
			if (p != core->pickups.end())
			{
				switch ((int)params[3])
				{
					case Data::ExtraID:
					{
						p->second->extraID = (int)params[4];
						return 1;
					}
					break;
					case Data::ModelID:
					{
						p->second->modelID = (int)params[4];
						update = true;
					}
					break;
					case Data::Type:
					{
						p->second->type = (int)params[4];
						update = true;
					}
					break;
					case Data::WorldID:
					{
						p->second->worldID = (int)params[4];
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
					boost::unordered_map<int, int>::iterator f = core->global.internalPickups.find(p->first);
					if (f != core->global.internalPickups.end())
					{
						invoke->callNative(&PAWN::DestroyPickup, f->second);
						f->second = invoke->callNative(&PAWN::CreatePickup, p->second->modelID, p->second->type, p->second->x, p->second->y, p->second->z, p->second->worldID);
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
			boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = core->checkpoints.find((int)params[2]);
			if (c != core->checkpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::ExtraID:
					{
						c->second->extraID = (int)params[4];
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
			boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = core->raceCheckpoints.find((int)params[2]);
			if (r != core->raceCheckpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::ExtraID:
					{
						r->second->extraID = (int)params[4];
						return 1;
					}
					break;
					case Data::Type:
					{
						r->second->type = (int)params[4];
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
					for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
					{
						if (p->visibleRaceCheckpoint == r->first)
						{
							invoke->callNative(&PAWN::DisablePlayerRaceCheckpoint, p->playerID);
							invoke->callNative(&PAWN::SetPlayerRaceCheckpoint, p->playerID, r->second->type, r->second->x, r->second->y, r->second->z, r->second->nextX, r->second->nextY, r->second->nextZ, r->second->size);
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
			boost::unordered_map<int, Core::SharedMapIcon>::iterator m = core->mapIcons.find((int)params[2]);
			if (m != core->mapIcons.end())
			{
				switch ((int)params[3])
				{
					case Data::Color:
					{
						m->second->color = (int)params[4];
						update = true;
					}
					break;
					case Data::ExtraID:
					{
						m->second->extraID = (int)params[4];
						return 1;
					}
					break;
					case Data::Style:
					{
						m->second->style = (int)params[4];
						update = true;
					}
					break;
					case Data::Type:
					{
						m->second->type = (int)params[4];
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
					for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator f = p->internalMapIcons.find(m->first);
						if (f != p->internalMapIcons.end())
						{
							invoke->callNative(&PAWN::RemovePlayerMapIcon, p->playerID, f->second);
							invoke->callNative(&PAWN::SetPlayerMapIcon, p->playerID, f->second, m->second->x, m->second->y, m->second->z, m->second->type, m->second->color, m->second->style);
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
			boost::unordered_map<int, Core::SharedTextLabel>::iterator t = core->textLabels.find((int)params[2]);
			if (t != core->textLabels.end())
			{
				switch ((int)params[3])
				{
					case Data::AttachedPlayer:
					{
						if ((int)params[4] != INVALID_GENERIC_ID)
						{
							t->second->attach = boost::intrusive_ptr<Element::TextLabel::Attach>(new Element::TextLabel::Attach);
							t->second->attach->player = (int)params[4];
							t->second->attach->vehicle = INVALID_GENERIC_ID;
							core->movingTextLabels.insert(t->second);
						}
						else
						{
							if (t->second->attach)
							{
								if (t->second->attach->player != INVALID_GENERIC_ID)
								{
									t->second->attach.reset();
									core->movingTextLabels.erase(t->second);
								}
							}
						}
						update = true;
					}
					break;
					case Data::AttachedVehicle:
					{
						if ((int)params[4] != INVALID_GENERIC_ID)
						{
							t->second->attach = boost::intrusive_ptr<Element::TextLabel::Attach>(new Element::TextLabel::Attach);
							t->second->attach->player = INVALID_GENERIC_ID;
							t->second->attach->vehicle = (int)params[4];
							core->movingTextLabels.insert(t->second);
						}
						else
						{
							if (t->second->attach)
							{
								if (t->second->attach->vehicle != INVALID_GENERIC_ID)
								{
									t->second->attach.reset();
									core->movingTextLabels.erase(t->second);
								}
							}
						}
						update = true;
					}
					break;
					case Data::Color:
					{
						t->second->color = (int)params[4];
						update = true;
					}
					break;
					case Data::ExtraID:
					{
						t->second->extraID = (int)params[4];
						return 1;
					}
					break;
					case Data::TestLOS:
					{
						t->second->testLOS = (int)params[4];
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
						if (fabs(t->second->x) > 50.0f || fabs(t->second->y) > 50.0f || fabs(t->second->z) > 50.0f)
						{
							t->second->x = 0.0f;
							t->second->y = 0.0f;
							t->second->z = 0.0f;
						}
					}
					for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator f = p->internalTextLabels.find(t->first);
						if (f != p->internalTextLabels.end())
						{
							invoke->callNative(&PAWN::DeletePlayer3DTextLabel, p->playerID, f->second);
							f->second = invoke->callNative(&PAWN::CreatePlayer3DTextLabel, p->playerID, t->second->text.c_str(), t->second->color, t->second->x, t->second->y, t->second->z, t->second->drawDistance, (t->second->attach ? t->second->attach->player : INVALID_GENERIC_ID), (t->second->attach ? t->second->attach->vehicle : INVALID_GENERIC_ID), t->second->testLOS);
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
			boost::unordered_map<int, Core::SharedArea>::iterator a = core->areas.find((int)params[2]);
			if (a != core->areas.end())
			{
				switch ((int)params[3])
				{
					case Data::AttachedPlayer:
					{
						if ((int)params[4] != INVALID_GENERIC_ID)
						{
							a->second->attach = boost::intrusive_ptr<Element::Area::Attach>(new Element::Area::Attach);
							a->second->attach->player = (int)params[4];
							a->second->attach->vehicle = INVALID_GENERIC_ID;
							core->movingAreas.insert(a->second);
						}
						else
						{
							if (a->second->attach)
							{
								if (a->second->attach->player != INVALID_GENERIC_ID)
								{
									a->second->attach.reset();
									core->movingAreas.erase(a->second);
								}
							}
						}
						return 1;
					}
					break;
					case Data::AttachedVehicle:
					{
						if ((int)params[4] != INVALID_GENERIC_ID)
						{
							a->second->attach = boost::intrusive_ptr<Element::Area::Attach>(new Element::Area::Attach);
							a->second->attach->player = INVALID_GENERIC_ID;
							a->second->attach->vehicle = (int)params[4];
							core->movingAreas.insert(a->second);
						}
						else
						{
							if (a->second->attach)
							{
								if (a->second->attach->vehicle != INVALID_GENERIC_ID)
								{
									a->second->attach.reset();
									core->movingAreas.erase(a->second);
								}
							}
						}
						return 1;
					}
					break;
					case Data::ExtraID:
					{
						a->second->extraID = (int)params[4];
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

int Manipulation::isInArrayData(AMX * amx, cell * params)
{
	switch ((int)params[1])
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Core::SharedObject>::iterator o = core->objects.find((int)params[2]);
			if (o != core->objects.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							if (o->second->interiors[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (o->second->interiors.count() == MAX_INTERIORS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							if (o->second->players[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (o->second->players.count() == MAX_PLAYERS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							if (o->second->worlds.find((int)params[4]) != o->second->worlds.end())
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
			boost::unordered_map<int, Core::SharedPickup>::iterator p = core->pickups.find((int)params[2]);
			if (p != core->pickups.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							if (p->second->interiors[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (p->second->interiors.count() == MAX_INTERIORS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							if (p->second->players[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (p->second->players.count() == MAX_PLAYERS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::WorldID:
					{
						logprintf("*** Streamer_IsInArrayData: Use Streamer_GetIntData to get the virtual world for pickups");
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
			boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = core->checkpoints.find((int)params[2]);
			if (c != core->checkpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							if (c->second->interiors[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (c->second->interiors.count() == MAX_INTERIORS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							if (c->second->players[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (c->second->players.count() == MAX_PLAYERS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							if (c->second->worlds.find((int)params[4]) != c->second->worlds.end())
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
			boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = core->raceCheckpoints.find((int)params[2]);
			if (r != core->raceCheckpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							if (r->second->interiors[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (r->second->interiors.count() == MAX_INTERIORS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							if (r->second->players[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (r->second->players.count() == MAX_PLAYERS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							if (r->second->worlds.find((int)params[4]) != r->second->worlds.end())
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
			boost::unordered_map<int, Core::SharedMapIcon>::iterator m = core->mapIcons.find((int)params[2]);
			if (m != core->mapIcons.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							if (m->second->interiors[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (m->second->interiors.count() == MAX_INTERIORS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							if (m->second->players[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (m->second->players.count() == MAX_PLAYERS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							if (m->second->worlds.find((int)params[4]) != m->second->worlds.end())
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
			boost::unordered_map<int, Core::SharedTextLabel>::iterator t = core->textLabels.find((int)params[2]);
			if (t != core->textLabels.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							if (t->second->interiors[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (t->second->interiors.count() == MAX_INTERIORS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							if (t->second->players[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (t->second->players.count() == MAX_PLAYERS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							if (t->second->worlds.find((int)params[4]) != t->second->worlds.end())
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
			boost::unordered_map<int, Core::SharedArea>::iterator a = core->areas.find((int)params[2]);
			if (a != core->areas.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							if (a->second->interiors[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (a->second->interiors.count() == MAX_INTERIORS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							if (a->second->players[(int)params[4]])
							{
								return 1;
							}
						}
						else
						{
							if (a->second->players.count() == MAX_PLAYERS)
							{
								return 1;
							}
						}
						return 0;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							if (a->second->worlds.find((int)params[4]) != a->second->worlds.end())
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

int Manipulation::appendArrayData(AMX * amx, cell * params)
{
	switch ((int)params[1])
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Core::SharedObject>::iterator o = core->objects.find((int)params[2]);
			if (o != core->objects.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							o->second->interiors.set((int)params[4]);
						}
						else
						{
							o->second->interiors.set();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							o->second->players.set((int)params[4]);
						}
						else
						{
							o->second->players.set();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							o->second->worlds.insert((int)params[4]);
						}
						else
						{
							o->second->worlds.clear();
						}
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
			boost::unordered_map<int, Core::SharedPickup>::iterator p = core->pickups.find((int)params[2]);
			if (p != core->pickups.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							p->second->interiors.set((int)params[4]);
						}
						else
						{
							p->second->interiors.set();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							p->second->players.set((int)params[4]);
						}
						else
						{
							p->second->players.set();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						logprintf("*** Streamer_RemoveArrayData: Use Streamer_SetIntData to set the virtual world for pickups");
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
			boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = core->checkpoints.find((int)params[2]);
			if (c != core->checkpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							c->second->interiors.set((int)params[4]);
						}
						else
						{
							c->second->interiors.set();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							c->second->players.set((int)params[4]);
						}
						else
						{
							c->second->players.set();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							c->second->worlds.insert((int)params[4]);
						}
						else
						{
							c->second->worlds.clear();
						}
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
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = core->raceCheckpoints.find((int)params[2]);
			if (r != core->raceCheckpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							r->second->interiors.set((int)params[4]);
						}
						else
						{
							r->second->interiors.set();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							r->second->players.set((int)params[4]);
						}
						else
						{
							r->second->players.set();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							r->second->worlds.insert((int)params[4]);
						}
						else
						{
							r->second->worlds.clear();
						}
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
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Core::SharedMapIcon>::iterator m = core->mapIcons.find((int)params[2]);
			if (m != core->mapIcons.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							m->second->interiors.set((int)params[4]);
						}
						else
						{
							m->second->interiors.set();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							m->second->players.set((int)params[4]);
						}
						else
						{
							m->second->players.set();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							m->second->worlds.insert((int)params[4]);
						}
						else
						{
							m->second->worlds.clear();
						}
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
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Core::SharedTextLabel>::iterator t = core->textLabels.find((int)params[2]);
			if (t != core->textLabels.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							t->second->interiors.set((int)params[4]);
						}
						else
						{
							t->second->interiors.set();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							t->second->players.set((int)params[4]);
						}
						else
						{
							t->second->players.set();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							t->second->worlds.insert((int)params[4]);
						}
						else
						{
							t->second->worlds.clear();
						}
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
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Core::SharedArea>::iterator a = core->areas.find((int)params[2]);
			if (a != core->areas.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							a->second->interiors.set((int)params[4]);
						}
						else
						{
							a->second->interiors.set();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							a->second->players.set((int)params[4]);
						}
						else
						{
							a->second->players.set();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							a->second->worlds.insert((int)params[4]);
						}
						else
						{
							a->second->worlds.clear();
						}
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
		default:
		{
			logprintf("*** Streamer_AppendArrayData: Invalid type specified");
		}
		break;
	}
	return 0;
}

int Manipulation::removeArrayData(AMX * amx, cell * params)
{
	switch ((int)params[1])
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Core::SharedObject>::iterator o = core->objects.find((int)params[2]);
			if (o != core->objects.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							o->second->interiors.reset((int)params[4]);
						}
						else
						{
							o->second->interiors.reset();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							o->second->players.reset((int)params[4]);
						}
						else
						{
							o->second->players.reset();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							o->second->worlds.erase((int)params[4]);
						}
						return 1;
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
			boost::unordered_map<int, Core::SharedPickup>::iterator p = core->pickups.find((int)params[2]);
			if (p != core->pickups.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							p->second->interiors.reset((int)params[4]);
						}
						else
						{
							p->second->interiors.reset();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							p->second->players.reset((int)params[4]);
						}
						else
						{
							p->second->players.reset();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						logprintf("*** Streamer_RemoveArrayData: Use Streamer_SetIntData to set the virtual world for pickups");
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
			boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = core->checkpoints.find((int)params[2]);
			if (c != core->checkpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							c->second->interiors.reset((int)params[4]);
						}
						else
						{
							c->second->interiors.reset();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							c->second->players.reset((int)params[4]);
						}
						else
						{
							c->second->players.reset();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							c->second->worlds.erase((int)params[4]);
						}
						return 1;
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
			boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = core->raceCheckpoints.find((int)params[2]);
			if (r != core->raceCheckpoints.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							r->second->interiors.reset((int)params[4]);
						}
						else
						{
							r->second->interiors.reset();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							r->second->players.reset((int)params[4]);
						}
						else
						{
							r->second->players.reset();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							r->second->worlds.erase((int)params[4]);
						}
						return 1;
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
			boost::unordered_map<int, Core::SharedMapIcon>::iterator m = core->mapIcons.find((int)params[2]);
			if (m != core->mapIcons.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							m->second->interiors.reset((int)params[4]);
						}
						else
						{
							m->second->interiors.reset();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							m->second->players.reset((int)params[4]);
						}
						else
						{
							m->second->players.reset();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							m->second->worlds.erase((int)params[4]);
						}
						return 1;
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
			boost::unordered_map<int, Core::SharedTextLabel>::iterator t = core->textLabels.find((int)params[2]);
			if (t != core->textLabels.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							t->second->interiors.reset((int)params[4]);
						}
						else
						{
							t->second->interiors.reset();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							t->second->players.reset((int)params[4]);
						}
						else
						{
							t->second->players.reset();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							t->second->worlds.erase((int)params[4]);
						}
						return 1;
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
			boost::unordered_map<int, Core::SharedArea>::iterator a = core->areas.find((int)params[2]);
			if (a != core->areas.end())
			{
				switch ((int)params[3])
				{
					case Data::InteriorID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_INTERIORS)
						{
							a->second->interiors.reset((int)params[4]);
						}
						else
						{
							a->second->interiors.reset();
						}
						return 1;
					}
					break;
					case Data::PlayerID:
					{
						if ((int)params[4] >= 0 && (int)params[4] < MAX_PLAYERS)
						{
							a->second->players.reset((int)params[4]);
						}
						else
						{
							a->second->players.reset();
						}
						return 1;
					}
					break;
					case Data::WorldID:
					{
						if ((int)params[4] >= 0)
						{
							a->second->worlds.erase((int)params[4]);
						}
						return 1;
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
