/*
 * Copyright (C) 2012 Incognito
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "manipulation.h"

#include "core.h"
#include "main.h"
#include "utility.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

#include <sampgdk/a_objects.h>
#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/plugin.h>

#include <bitset>
#include <cmath>

using namespace Manipulation;

int Manipulation::getFloatData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachOffsetX:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->offset[0]);
							return 1;
						}
						return 0;
					}
					case AttachOffsetY:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->offset[1]);
							return 1;
						}
						return 0;
					}
					case AttachOffsetZ:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->offset[2]);
							return 1;
						}
						return 0;
					}
					case AttachRX:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->rotation[0]);
							return 1;
						}
						return 0;
					}
					case AttachRY:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->rotation[1]);
							return 1;
						}
						return 0;
					}
					case AttachRZ:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->rotation[2]);
							return 1;
						}
						return 0;
					}
					case AttachX:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->position[0]);
							return 1;
						}
						return 0;
					}
					case AttachY:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->position[1]);
							return 1;
						}
						return 0;
					}
					case AttachZ:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->position[2]);
							return 1;
						}
						return 0;
					}
					case DrawDistance:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->drawDistance);
						return 1;
					}
					case MoveSpeed:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->speed);
							return 1;
						}
						return 0;
					}
					case MoveRX:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->rotation.get<0>()[0]);
							return 1;
						}
						return 0;
					}
					case MoveRY:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->rotation.get<0>()[1]);
							return 1;
						}
						return 0;
					}
					case MoveRZ:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->rotation.get<0>()[2]);
							return 1;
						}
						return 0;
					}
					case MoveX:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->position.get<0>()[0]);
							return 1;
						}
						return 0;
					}
					case MoveY:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->position.get<0>()[1]);
							return 1;
						}
						return 0;
					}
					case MoveZ:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->position.get<0>()[2]);
							return 1;
						}
						return 0;
					}
					case RX:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->rotation[0]);
						return 1;
					}
					case RY:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->rotation[1]);
						return 1;
					}
					case RZ:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->rotation[2]);
						return 1;
					}
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], std::sqrt(o->second->streamDistance));
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->position[2]);
						return 1;
					}
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], std::sqrt(p->second->streamDistance));
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], p->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], p->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], p->second->position[2]);
						return 1;
					}
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Size:
					{
						Utility::storeFloatInNative(amx, params[4], c->second->size);
						return 1;
					}
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], std::sqrt(c->second->streamDistance));
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], c->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], c->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], c->second->position[2]);
						return 1;
					}
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case NextX:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->next[0]);
						return 1;
					}
					case NextY:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->next[1]);
						return 1;
					}
					case NextZ:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->next[2]);
						return 1;
					}
					case Size:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->size);
						return 1;
					}
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], std::sqrt(r->second->streamDistance));
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->position[2]);
						return 1;
					}
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], std::sqrt(m->second->streamDistance));
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], m->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], m->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], m->second->position[2]);
						return 1;
					}
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachX:
					{
						if (t->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], t->second->attach->position[0]);
							return 1;
						}
						return 0;
					}
					case AttachY:
					{
						if (t->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], t->second->attach->position[1]);
							return 1;
						}
						return 0;
					}
					case AttachZ:
					{
						if (t->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], t->second->attach->position[2]);
							return 1;
						}
						return 0;
					}
					case DrawDistance:
					{
						Utility::storeFloatInNative(amx, params[4], t->second->drawDistance);
						return 1;
					}
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], std::sqrt(t->second->streamDistance));
						return 1;
					}
					case AttachOffsetX:
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], t->second->position[0]);
						return 1;
					}
					case AttachOffsetY:
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], t->second->position[1]);
						return 1;
					}
					case AttachOffsetZ:
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], t->second->position[2]);
						return 1;
					}
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachX:
					{
						if (a->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], a->second->attach->position[0]);
							return 1;
						}
						return 0;
					}
					case AttachY:
					{
						if (a->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], a->second->attach->position[1]);
							return 1;
						}
						return 0;
					}
					case AttachZ:
					{
						if (a->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], a->second->attach->position[2]);
							return 1;
						}
						return 0;
					}
					case MaxX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box2D>(a->second->position).max_corner()[0]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).max_corner()[0]);
								return 1;
							}
						}
						return 0;
					}
					case MaxY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box2D>(a->second->position).max_corner()[1]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).max_corner()[1]);
								return 1;
							}
						}
						return 0;
					}
					case MaxZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).max_corner()[2]);
								return 1;
							}
							case STREAMER_AREA_TYPE_POLYGON:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Polygon2D>(a->second->position).get<1>()[1]);
								return 1;
							}
						}
						return 0;
					}
					case MinX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box2D>(a->second->position).min_corner()[0]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).min_corner()[0]);
								return 1;
							}
						}
						return 0;
					}
					case MinY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box2D>(a->second->position).min_corner()[1]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).min_corner()[1]);
								return 1;
							}
						}
						return 0;
					}
					case MinZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).min_corner()[2]);
								return 1;
							}
							case STREAMER_AREA_TYPE_POLYGON:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Polygon2D>(a->second->position).get<1>()[0]);
								return 1;
							}
						}
						return 0;
					}
					case Size:
					{
						Utility::storeFloatInNative(amx, params[4], std::sqrt(a->second->size));
						return 1;
					}
					case X:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Eigen::Vector2f>(a->second->position)[0]);
								return 1;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Eigen::Vector3f>(a->second->position)[0]);
								return 1;
							}
						}
						return 0;
					}
					case Y:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Eigen::Vector2f>(a->second->position)[1]);
								return 1;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Eigen::Vector3f>(a->second->position)[1]);
								return 1;
							}
						}
						return 0;
					}
					case Z:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_SPHERE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Eigen::Vector3f>(a->second->position)[2]);
								return 1;
							}
						}
						return 0;
					}
					default:
					{
						logprintf("*** Streamer_GetFloatData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetFloatData: Invalid ID specified");
			return 0;
		}
		default:
		{
			logprintf("*** Streamer_GetFloatData: Invalid type specified");
			return 0;
		}
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
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachOffsetX:
					{
						if (o->second->attach)
						{
							o->second->attach->offset[0] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachOffsetY:
					{
						if (o->second->attach)
						{
							o->second->attach->offset[1] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachOffsetZ:
					{
						if (o->second->attach)
						{
							o->second->attach->offset[2] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachRX:
					{
						if (o->second->attach)
						{
							o->second->attach->rotation[0] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachRY:
					{
						if (o->second->attach)
						{
							o->second->attach->rotation[1] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachRZ:
					{
						if (o->second->attach)
						{
							o->second->attach->rotation[2] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case DrawDistance:
					{
						o->second->drawDistance = amx_ctof(params[4]);
						update = true;
						break;
					}
					case MoveRX:
					case MoveRY:
					case MoveRZ:
					case MoveSpeed:
					case MoveX:
					case MoveY:
					case MoveZ:
					{
						logprintf("*** Streamer_SetFloatData: Use MoveDynamicObject to adjust moving object data");
						return 0;
					}
					case RX:
					{
						o->second->rotation[0] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case RY:
					{
						o->second->rotation[1] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case RZ:
					{
						o->second->rotation[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						o->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
						break;
					}
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
						break;
					}
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
						break;
					}
					case Z:
					{
						if (o->second->move)
						{
							logprintf("*** Streamer_SetFloatData: Object must be stopped first");
							return 0;
						}
						o->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
						return 0;
					}
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
							DestroyPlayerObject(p->first, i->second);
							i->second = CreatePlayerObject(p->first, o->second->modelID, o->second->position[0], o->second->position[1], o->second->position[2], o->second->rotation[0], o->second->rotation[1], o->second->rotation[2], o->second->drawDistance);
							if (o->second->attach)
							{
								AttachPlayerObjectToVehicle(p->first, i->second, o->second->attach->vehicle, o->second->attach->offset[0], o->second->attach->offset[1], o->second->attach->offset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);		
							}
							else if (o->second->move)
							{
								MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
							}
							for (boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
							{
								if (m->second.main)
								{
									SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
								}
								else if (m->second.text)
								{
									SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
								}
							}
						}
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						p->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case X:
					{
						p->second->position[0] = amx_ctof(params[4]);
						if (p->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Y:
					{
						p->second->position[1] = amx_ctof(params[4]);
						if (p->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Z:
					{
						p->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
						return 0;
					}
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
						DestroyPickup(i->second);
						i->second = CreatePickup(p->second->modelID, p->second->type, p->second->position[0], p->second->position[1], p->second->position[2], p->second->worldID);
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Size:
					{
						c->second->size = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						c->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case X:
					{
						c->second->position[0] = amx_ctof(params[4]);
						if (c->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Y:
					{
						c->second->position[1] = amx_ctof(params[4]);
						if (c->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Z:
					{
						c->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
						return 0;
					}
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
							DisablePlayerCheckpoint(p->first);
							SetPlayerCheckpoint(p->first, c->second->position[0], c->second->position[1], c->second->position[2], c->second->size);
						}
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case NextX:
					{
						r->second->next[0] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case NextY:
					{
						r->second->next[1] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case NextZ:
					{
						r->second->next[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case Size:
					{
						r->second->size = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						r->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case X:
					{
						r->second->position[0] = amx_ctof(params[4]);
						if (r->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Y:
					{
						r->second->position[1] = amx_ctof(params[4]);
						if (r->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Z:
					{
						r->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data for type specified");
						return 0;
					}
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
							DisablePlayerRaceCheckpoint(p->first);
							SetPlayerRaceCheckpoint(p->first, r->second->type, r->second->position[0], r->second->position[1], r->second->position[2], r->second->next[0], r->second->next[1], r->second->next[2], r->second->size);
						}
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						m->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case X:
					{
						m->second->position[0] = amx_ctof(params[4]);
						if (m->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Y:
					{
						m->second->position[1] = amx_ctof(params[4]);
						if (m->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Z:
					{
						m->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
						return 0;
					}
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
							RemovePlayerMapIcon(p->first, i->second);
							SetPlayerMapIcon(p->first, i->second, m->second->position[0], m->second->position[1], m->second->position[2], m->second->type, m->second->color, m->second->style);
						}
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case DrawDistance:
					{
						t->second->drawDistance = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						t->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case AttachOffsetX:
					case X:
					{
						t->second->position[0] = amx_ctof(params[4]);
						if (t->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case AttachOffsetY:
					case Y:
					{
						t->second->position[1] = amx_ctof(params[4]);
						if (t->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case AttachOffsetZ:
					case Z:
					{
						t->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
						return 0;
					}
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
							DeletePlayer3DTextLabel(p->first, i->second);
							i->second = CreatePlayer3DTextLabel(p->first, t->second->text.c_str(), t->second->color, t->second->position[0], t->second->position[1], t->second->position[2], t->second->drawDistance, t->second->attach ? t->second->attach->player : INVALID_GENERIC_ID, t->second->attach ? t->second->attach->vehicle : INVALID_GENERIC_ID, t->second->testLOS);
						}
					}
				}
				return (reassign || update);
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case MaxX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								boost::get<Box2D>(a->second->position).max_corner()[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Box3D>(a->second->position).max_corner()[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case MaxY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								boost::get<Box2D>(a->second->position).max_corner()[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Box3D>(a->second->position).max_corner()[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case MaxZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Box3D>(a->second->position).max_corner()[2] = amx_ctof(params[4]);
								return 1;
							}
							case STREAMER_AREA_TYPE_POLYGON:
							{
								boost::get<Polygon2D>(a->second->position).get<1>()[1] = amx_ctof(params[4]);
								return 0;
							}
						}
						return 0;
					}
					case MinX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								boost::get<Box2D>(a->second->position).min_corner()[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Box3D>(a->second->position).min_corner()[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case MinY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								boost::get<Box2D>(a->second->position).min_corner()[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Box3D>(a->second->position).min_corner()[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case MinZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBE:
							{
								boost::get<Box3D>(a->second->position).min_corner()[2] = amx_ctof(params[4]);
								return 1;
							}
							case STREAMER_AREA_TYPE_POLYGON:
							{
								boost::get<Polygon2D>(a->second->position).get<1>()[0] = amx_ctof(params[4]);
								return 1;
							}
						}
						return 0;
					}
					case Size:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							case STREAMER_AREA_TYPE_SPHERE:
							{
								a->second->size = amx_ctof(params[4]) * amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case X:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							{
								boost::get<Eigen::Vector2f>(a->second->position)[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								boost::get<Eigen::Vector3f>(a->second->position)[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case Y:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							{
								boost::get<Eigen::Vector2f>(a->second->position)[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								boost::get<Eigen::Vector3f>(a->second->position)[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case Z:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_SPHERE:
							{
								boost::get<Eigen::Vector3f>(a->second->position)[2] = amx_ctof(params[4]);
								return 1;
							}
						}
						return 0;
					}
					default:
					{
						logprintf("*** Streamer_SetFloatData: Invalid data specified");
						return 0;
					}
				}
				if (reassign)
				{
					switch (a->second->type)
					{
						case STREAMER_AREA_TYPE_RECTANGLE:
						{
							boost::geometry::correct(boost::get<Box2D>(a->second->position));
							a->second->size = static_cast<float>(boost::geometry::comparable_distance(boost::get<Box2D>(a->second->position).min_corner(), boost::get<Box2D>(a->second->position).max_corner()));
							break;
						}
						case STREAMER_AREA_TYPE_CUBE:
						{
							boost::geometry::correct(boost::get<Box3D>(a->second->position));
							a->second->size = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Box3D>(a->second->position).min_corner()[0], boost::get<Box3D>(a->second->position).min_corner()[1]), Eigen::Vector2f(boost::get<Box3D>(a->second->position).max_corner()[0], boost::get<Box3D>(a->second->position).max_corner()[1])));
							break;
						}
					}
					core->getGrid()->removeArea(a->second, true);
				}
				return reassign;
			}
			logprintf("*** Streamer_SetFloatData: Invalid ID specified");
			return 0;
		}
		default:
		{
			logprintf("*** Streamer_SetFloatData: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

int Manipulation::getIntData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedVehicle:
					{
						if (o->second->attach)
						{
							return o->second->attach->vehicle;
						}
						return INVALID_GENERIC_ID;
					}
					case ExtraID:
					{
						return o->second->extraID;
					}
					case ModelID:
					{
						return o->second->modelID;
					}
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						return p->second->extraID;
					}
					case ModelID:
					{
						return p->second->modelID;
					}
					case Type:
					{
						return p->second->type;
					}
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						return c->second->extraID;
					}
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						return r->second->extraID;
					}
					case Type:
					{
						return r->second->type;
					}
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Color:
					{
						return m->second->color;
					}
					case ExtraID:
					{
						return m->second->extraID;
					}
					case Style:
					{
						return m->second->style;
					}
					case Type:
					{
						return m->second->type;
					}
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
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
						return INVALID_GENERIC_ID;
					}
					case AttachedVehicle:
					{
						if (t->second->attach)
						{
							return t->second->attach->vehicle;
						}
						return INVALID_GENERIC_ID;
					}
					case Color:
					{
						return t->second->color;
					}
					case ExtraID:
					{
						return t->second->extraID;
					}
					case TestLOS:
					{
						return t->second->testLOS;
					}
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedObject:
					{
						if (a->second->attach)
						{
							return a->second->attach->object.get<0>();
						}
						return INVALID_GENERIC_ID;
					}
					case AttachedPlayer:
					{
						if (a->second->attach)
						{
							return a->second->attach->player;
						}
						return INVALID_GENERIC_ID;
					}
					case AttachedVehicle:
					{
						if (a->second->attach)
						{
							return a->second->attach->vehicle;
						}
						return INVALID_GENERIC_ID;
					}
					case ExtraID:
					{
						return a->second->extraID;
					}
					case Type:
					{
						return a->second->type;
					}
					default:
					{
						logprintf("*** Streamer_GetIntData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_GetIntData: Invalid ID specified");
			return 0;
		}
		default:
		{
			logprintf("*** Streamer_GetIntData: Invalid type specified");
			return 0;
		}
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
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedVehicle:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							o->second->attach = boost::intrusive_ptr<Item::Object::Attach>(new Item::Object::Attach);
							o->second->attach->vehicle = static_cast<int>(params[4]);
							o->second->attach->offset.setZero();
							o->second->attach->rotation.setZero();
							core->getStreamer()->attachedObjects.insert(o->second);
							update = true;
						}
						else
						{
							if (o->second->attach)
							{
								if (o->second->attach->vehicle != INVALID_GENERIC_ID)
								{
									o->second->attach.reset();
									core->getStreamer()->attachedObjects.erase(o->second);
									core->getGrid()->removeObject(o->second, true);
									update = true;
								}
							}
						}
						break;
					}
					case ExtraID:
					{
						o->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					case ModelID:
					{
						o->second->modelID = static_cast<int>(params[4]);
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
						return 0;
					}
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
						if (i != p->second.internalObjects.end())
						{
							DestroyPlayerObject(p->first, i->second);
							i->second = CreatePlayerObject(p->first, o->second->modelID, o->second->position[0], o->second->position[1], o->second->position[2], o->second->rotation[0], o->second->rotation[1], o->second->rotation[2], o->second->drawDistance);
							if (o->second->attach)
							{
								AttachPlayerObjectToVehicle(p->first, i->second, o->second->attach->vehicle, o->second->attach->offset[0], o->second->attach->offset[1], o->second->attach->offset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);
							}
							else if (o->second->move)
							{
								MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
							}
							for (boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
							{
								if (m->second.main)
								{
									SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
								}
								else if (m->second.text)
								{
									SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
								}
							}
						}
					}
					return update;
				}
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						p->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					case ModelID:
					{
						p->second->modelID = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case Type:
					{
						p->second->type = static_cast<int>(params[4]);
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
						return 0;
					}
				}
				if (update)
				{
					boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.find(p->first);
					if (i != core->getStreamer()->internalPickups.end())
					{
						DestroyPickup(i->second);
						i->second = CreatePickup(p->second->modelID, p->second->type, p->second->position[0], p->second->position[1], p->second->position[2], p->second->worldID);
					}
				}
				return update;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						c->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case ExtraID:
					{
						r->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					case Type:
					{
						r->second->type = static_cast<int>(params[4]);
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
						return 0;
					}
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						if (p->second.visibleRaceCheckpoint == r->first)
						{
							DisablePlayerRaceCheckpoint(p->first);
							SetPlayerRaceCheckpoint(p->first, r->second->type, r->second->position[0], r->second->position[1], r->second->position[2], r->second->next[0], r->second->next[1], r->second->next[2], r->second->size);
						}
					}
				}
				return update;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Color:
					{
						m->second->color = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case ExtraID:
					{
						m->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					case Style:
					{
						m->second->style = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case Type:
					{
						m->second->type = static_cast<int>(params[4]);
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
						return 0;
					}
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
						if (i != p->second.internalMapIcons.end())
						{
							RemovePlayerMapIcon(p->first, i->second);
							SetPlayerMapIcon(p->first, i->second, m->second->position[0], m->second->position[1], m->second->position[2], m->second->type, m->second->color, m->second->style);
						}
					}
				}
				return update;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedPlayer:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							t->second->attach = boost::intrusive_ptr<Item::TextLabel::Attach>(new Item::TextLabel::Attach);
							t->second->attach->player = static_cast<int>(params[4]);
							t->second->attach->vehicle = INVALID_GENERIC_ID;
							core->getStreamer()->attachedTextLabels.insert(t->second);
							update = true;
						}
						else
						{
							if (t->second->attach)
							{
								if (t->second->attach->player != INVALID_GENERIC_ID)
								{
									t->second->attach.reset();
									core->getStreamer()->attachedTextLabels.erase(t->second);
									core->getGrid()->removeTextLabel(t->second, true);
									update = true;
								}
							}
						}
						break;
					}
					case AttachedVehicle:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							t->second->attach = boost::intrusive_ptr<Item::TextLabel::Attach>(new Item::TextLabel::Attach);
							t->second->attach->player = INVALID_GENERIC_ID;
							t->second->attach->vehicle = static_cast<int>(params[4]);
							core->getStreamer()->attachedTextLabels.insert(t->second);
							update = true;
						}
						else
						{
							if (t->second->attach)
							{
								if (t->second->attach->vehicle != INVALID_GENERIC_ID)
								{
									t->second->attach.reset();
									core->getStreamer()->attachedTextLabels.erase(t->second);
									core->getGrid()->removeTextLabel(t->second, true);
									update = true;
								}
							}
						}
						break;
					}
					case Color:
					{
						t->second->color = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case ExtraID:
					{
						t->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					case TestLOS:
					{
						t->second->testLOS = static_cast<int>(params[4]) != 0;
						update = true;
						break;
					}
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
						return 0;
					}
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
							DeletePlayer3DTextLabel(p->first, i->second);
							i->second = CreatePlayer3DTextLabel(p->first, t->second->text.c_str(), t->second->color, t->second->position[0], t->second->position[1], t->second->position[2], t->second->drawDistance, t->second->attach ? t->second->attach->player : INVALID_GENERIC_ID, t->second->attach ? t->second->attach->vehicle : INVALID_GENERIC_ID, t->second->testLOS);
						}
					}
				}
				return update;
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
			return 0;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedObject:
					{
						logprintf("*** Streamer_SetFloatData: Use AttachDynamicAreaToObject to adjust attached area data");
						return 0;
					}
					case AttachedPlayer:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
							a->second->attach->object.get<0>() = INVALID_GENERIC_ID;
							a->second->attach->player = static_cast<int>(params[4]);
							a->second->attach->vehicle = INVALID_GENERIC_ID;
							core->getStreamer()->attachedAreas.insert(a->second);
							return 1;
						}
						else
						{
							if (a->second->attach)
							{
								if (a->second->attach->player != INVALID_GENERIC_ID)
								{
									a->second->attach.reset();
									core->getStreamer()->attachedAreas.erase(a->second);
									core->getGrid()->removeArea(a->second, true);
									return 1;
								}
							}
						}
						return 0;
					}
					case AttachedVehicle:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
							a->second->attach->object.get<0>() = INVALID_GENERIC_ID;
							a->second->attach->player = INVALID_GENERIC_ID;
							a->second->attach->vehicle = static_cast<int>(params[4]);
							core->getStreamer()->attachedAreas.insert(a->second);
							return 1;
						}
						else
						{
							if (a->second->attach)
							{
								if (a->second->attach->vehicle != INVALID_GENERIC_ID)
								{
									a->second->attach.reset();
									core->getStreamer()->attachedAreas.erase(a->second);
									core->getGrid()->removeArea(a->second, true);
									return 1;
								}
							}
						}
						return 0;
					}
					case ExtraID:
					{
						a->second->extraID = static_cast<int>(params[4]);
						return 1;
					}
					default:
					{
						logprintf("*** Streamer_SetIntData: Invalid data specified");
						return 0;
					}
				}
			}
			logprintf("*** Streamer_SetIntData: Invalid ID specified");
			return 0;
		}
		default:
		{
			logprintf("*** Streamer_SetIntData: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

int Manipulation::getArrayData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			return getArrayDataForItem(core->getData()->objects, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_PICKUP:
		{
			return getArrayDataForItem(core->getData()->pickups, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_CP:
		{
			return getArrayDataForItem(core->getData()->checkpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_RACE_CP:
		{
			return getArrayDataForItem(core->getData()->raceCheckpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			return getArrayDataForItem(core->getData()->mapIcons, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			return getArrayDataForItem(core->getData()->textLabels, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_AREA:
		{
			return getArrayDataForItem(core->getData()->areas, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		default:
		{
			logprintf("*** Streamer_GetArrayData: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

int Manipulation::setArrayData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			return setArrayDataForItem(core->getData()->objects, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_PICKUP:
		{
			return setArrayDataForItem(core->getData()->pickups, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_CP:
		{
			return setArrayDataForItem(core->getData()->checkpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_RACE_CP:
		{
			return setArrayDataForItem(core->getData()->raceCheckpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			return setArrayDataForItem(core->getData()->mapIcons, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			return setArrayDataForItem(core->getData()->textLabels, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		case STREAMER_TYPE_AREA:
		{
			return setArrayDataForItem(core->getData()->areas, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5]);
		}
		default:
		{
			logprintf("*** Streamer_SetArrayData: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

int Manipulation::isInArrayData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			return isInArrayDataForItem(core->getData()->objects, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_PICKUP:
		{
			return isInArrayDataForItem(core->getData()->pickups, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_CP:
		{
			return isInArrayDataForItem(core->getData()->checkpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_RACE_CP:
		{
			return isInArrayDataForItem(core->getData()->raceCheckpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			return isInArrayDataForItem(core->getData()->mapIcons, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			return isInArrayDataForItem(core->getData()->textLabels, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_AREA:
		{
			return isInArrayDataForItem(core->getData()->areas, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		default:
		{
			logprintf("*** Streamer_IsInArrayData: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

int Manipulation::appendArrayData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			return appendArrayDataForItem(core->getData()->objects, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_PICKUP:
		{
			return appendArrayDataForItem(core->getData()->pickups, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_CP:
		{
			return appendArrayDataForItem(core->getData()->checkpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_RACE_CP:
		{
			return appendArrayDataForItem(core->getData()->raceCheckpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			return appendArrayDataForItem(core->getData()->mapIcons, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			return appendArrayDataForItem(core->getData()->textLabels, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_AREA:
		{
			return appendArrayDataForItem(core->getData()->areas, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		default:
		{
			logprintf("*** Streamer_AppendArrayData: Invalid type specified");
			return 0;
		}
	}
	return 0;
}

int Manipulation::removeArrayData(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			return removeArrayDataForItem(core->getData()->objects, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_PICKUP:
		{
			return removeArrayDataForItem(core->getData()->pickups, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_CP:
		{
			return removeArrayDataForItem(core->getData()->checkpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_RACE_CP:
		{
			return removeArrayDataForItem(core->getData()->raceCheckpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			return removeArrayDataForItem(core->getData()->mapIcons, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			return removeArrayDataForItem(core->getData()->textLabels, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		case STREAMER_TYPE_AREA:
		{
			return removeArrayDataForItem(core->getData()->areas, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]));
		}
		default:
		{
			logprintf("*** Streamer_RemoveArrayData: Invalid type specified");
			return 0;
		}
	}
	return 0;
}
