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
#include "Manipulation.h"
#include "Natives.h"
#include "Utility.h"

using namespace Natives;

cell AMX_NATIVE_CALL Natives::Streamer_TickRate(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_TickRate");
	if (!core->getStreamer()->setTickRate(static_cast<int>(params[1])))
	{
		logprintf("*** Streamer_TickRate: Invalid tick rate specified");
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_MaxItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_MaxItems");
	if (!core->getData()->setMaxItems(static_cast<int>(params[1]), static_cast<int>(params[2])))
	{
		logprintf("*** Streamer_MaxItems: Invalid type specified");
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_VisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_VisibleItems");
	if (!core->getStreamer()->setVisibleItems(static_cast<int>(params[1]), static_cast<int>(params[2])))
	{
		logprintf("*** Streamer_VisibleItems: Invalid type specified");
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_CellDistance(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_CellDistance");
	core->getGrid()->cellDistance = amx_ctof(params[1]) * amx_ctof(params[1]);
	core->getGrid()->rebuildGrid();
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_CellSize(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_CellSize");
	core->getGrid()->cellSize = amx_ctof(params[1]);
	core->getGrid()->rebuildGrid();
	return 1;
}

cell AMX_NATIVE_CALL Natives::Streamer_Update(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_Update");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.interiorID = GetPlayerInterior(p->first);
		p->second.worldID = GetPlayerVirtualWorld(p->first);
		GetPlayerPos(p->first, &p->second.position[0], &p->second.position[1], &p->second.position[2]);
		core->getStreamer()->startManualUpdate(p->second);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_UpdateEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(6, "Streamer_UpdateEx");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		if (static_cast<int>(params[5]) >= 0)
		{
			p->second.worldID = static_cast<int>(params[5]);
		}
		else
		{
			p->second.worldID = GetPlayerVirtualWorld(p->first);
		}
		if (static_cast<int>(params[6]) >= 0)
		{
			p->second.interiorID = static_cast<int>(params[6]);
		}
		else
		{
			p->second.interiorID = GetPlayerInterior(p->first);
		}
		core->getStreamer()->startManualUpdate(p->second);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_ToggleIdleUpdate(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_ToggleIdleUpdate");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.idleUpdate = static_cast<int>(params[2]) != 0;
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_GetFloatData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_GetFloatData");
	return static_cast<cell>(Manipulation::getFloatData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetFloatData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_SetFloatData");
	return static_cast<cell>(Manipulation::setFloatData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_GetIntData(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_GetIntData");
	return static_cast<cell>(Manipulation::getIntData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetIntData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_SetIntData");
	return static_cast<cell>(Manipulation::setIntData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_GetArrayData(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "Streamer_GetArrayData");
	return static_cast<cell>(Manipulation::getArrayData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_SetArrayData(AMX *amx, cell *params)
{
	CHECK_PARAMS(5, "Streamer_SetArrayData");
	return static_cast<cell>(Manipulation::setArrayData(amx, params));
}


cell AMX_NATIVE_CALL Natives::Streamer_IsInArrayData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_IsInArrayData");
	return static_cast<cell>(Manipulation::isInArrayData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_AppendArrayData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_AppendArrayData");
	return static_cast<cell>(Manipulation::appendArrayData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_RemoveArrayData(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "Streamer_RemoveArrayData");
	return static_cast<cell>(Manipulation::removeArrayData(amx, params));
}

cell AMX_NATIVE_CALL Natives::Streamer_GetUpperBound(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "Streamer_GetUpperBound");
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			int objectID = 0;
			for (boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.begin(); o != core->getData()->objects.end(); ++o)
			{
				if (o->first > objectID)
				{
					objectID = o->first;
				}
			}
			return static_cast<cell>(objectID + 1);
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			int pickupID = 0;
			for (boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.begin(); p != core->getData()->pickups.end(); ++p)
			{
				if (p->first > pickupID)
				{
					pickupID = p->first;
				}
			}
			return static_cast<cell>(pickupID + 1);
		}
		break;
		case STREAMER_TYPE_CP:
		{
			int checkpointID = 0;
			for (boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin(); c != core->getData()->checkpoints.end(); ++c)
			{
				if (c->first > checkpointID)
				{
					checkpointID = c->first;
				}
			}
			return static_cast<cell>(checkpointID + 1);
		}
		break;
		case STREAMER_TYPE_RACE_CP:
		{
			int raceCheckpointID = 0;
			for (boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin(); r != core->getData()->raceCheckpoints.end(); ++r)
			{
				if (r->first > raceCheckpointID)
				{
					raceCheckpointID = r->first;
				}
			}
			return static_cast<cell>(raceCheckpointID + 1);
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			int mapIconID = 0;
			for (boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.begin(); m != core->getData()->mapIcons.end(); ++m)
			{
				if (m->first > mapIconID)
				{
					mapIconID = m->first;
				}
			}
			return static_cast<cell>(mapIconID + 1);
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			int textLabelID = 0;
			for (boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.begin(); t != core->getData()->textLabels.end(); ++t)
			{
				if (t->first > textLabelID)
				{
					textLabelID = t->first;
				}
			}
			return static_cast<cell>(textLabelID + 1);
		}
		break;
		case STREAMER_TYPE_AREA:
		{
			int areaID = 0;
			for (boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				if (a->first > areaID)
				{
					areaID = a->first;
				}
			}
			return static_cast<cell>(areaID + 1);
		}
		break;
		default:
		{
			logprintf("*** Streamer_GetUpperBound: Invalid type specified");
		}
		break;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_IsItemVisible(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "Streamer_IsItemVisible");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		switch (static_cast<int>(params[2]))
		{
			case STREAMER_TYPE_OBJECT:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(static_cast<int>(params[3]));
				if (i != p->second.internalObjects.end())
				{
					return 1;
				}
			}
			break;
			case STREAMER_TYPE_PICKUP:
			{
				boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.find(static_cast<int>(params[3]));
				if (i != core->getStreamer()->internalPickups.end())
				{
					return 1;
				}
			}
			break;
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
			}
			break;
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint == static_cast<int>(params[3]))
				{
					return 1;
				}
			}
			break;
			case STREAMER_TYPE_MAP_ICON:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(static_cast<int>(params[3]));
				if (i != p->second.internalMapIcons.end())
				{
					return 1;
				}
			}
			break;
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(static_cast<int>(params[3]));
				if (i != p->second.internalTextLabels.end())
				{
					return 1;
				}
			}
			case STREAMER_TYPE_AREA:
			{
				boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[3]));
				if (i != p->second.internalAreas.end())
				{
					return 1;
				}
			}
			break;
			default:
			{
				logprintf("*** Streamer_IsItemVisible: Invalid type specified");
			}
			break;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_DestroyAllVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_DestroyAllVisibleItems");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		switch (static_cast<int>(params[2]))
		{
			case STREAMER_TYPE_OBJECT:
			{
				for (boost::unordered_map<int, int>::iterator o = p->second.internalObjects.begin(); o != p->second.internalObjects.end(); ++o)
				{
					DestroyPlayerObject(p->first, o->second);
				}
				p->second.internalObjects.clear();
				return 1;
			}
			break;
			case STREAMER_TYPE_PICKUP:
			{
				for (boost::unordered_map<int, int>::iterator q = core->getStreamer()->internalPickups.begin(); q != core->getStreamer()->internalPickups.end(); ++q)
				{
					DestroyPickup(q->second);
				}
				core->getStreamer()->internalPickups.clear();
				return 1;
			}
			break;
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint)
				{
					DisablePlayerCheckpoint(p->first);
					p->second.activeCheckpoint = 0;
					p->second.visibleCheckpoint = 0;
				}
				return 1;
			}
			break;
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint)
				{
					DisablePlayerRaceCheckpoint(p->first);
					p->second.activeRaceCheckpoint = 0;
					p->second.visibleRaceCheckpoint = 0;
				}
				return 1;
			}
			break;
			case STREAMER_TYPE_MAP_ICON:
			{
				for (boost::unordered_map<int, int>::iterator m = p->second.internalMapIcons.begin(); m != p->second.internalMapIcons.end(); ++m)
				{
					RemovePlayerMapIcon(p->first, m->second);
				}
				p->second.internalMapIcons.clear();
				return 1;
			}
			break;
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				for (boost::unordered_map<int, int>::iterator t = p->second.internalTextLabels.begin(); t != p->second.internalTextLabels.end(); ++t)
				{
					DeletePlayer3DTextLabel(p->first, t->second);
				}
				p->second.internalTextLabels.clear();
				return 1;
			}
			break;
			case STREAMER_TYPE_AREA:
			{
				p->second.internalAreas.clear();
				return 1;
			}
			break;
			default:
			{
				logprintf("*** Streamer_DestroyAllVisibleItems: Invalid type specified");
			}
			break;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::Streamer_CountVisibleItems(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "Streamer_CountVisibleItems");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		switch (static_cast<int>(params[2]))
		{
			case STREAMER_TYPE_OBJECT:
			{
				return static_cast<cell>(p->second.internalObjects.size());
			}
			break;
			case STREAMER_TYPE_PICKUP:
			{
				return static_cast<cell>(core->getStreamer()->internalPickups.size());
			}
			break;
			case STREAMER_TYPE_CP:
			{
				if (p->second.visibleCheckpoint)
				{
					return 1;
				}
			}
			break;
			case STREAMER_TYPE_RACE_CP:
			{
				if (p->second.visibleRaceCheckpoint)
				{
					return 1;
				}
			}
			break;
			case STREAMER_TYPE_MAP_ICON:
			{
				return static_cast<cell>(p->second.internalMapIcons.size());
			}
			break;
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				return static_cast<cell>(p->second.internalTextLabels.size());
			}
			break;
			case STREAMER_TYPE_AREA:
			{
				return static_cast<cell>(p->second.internalAreas.size());
			}
			break;
			default:
			{
				logprintf("*** Streamer_CountVisibleItems: Invalid type specified");
			}
			break;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::CreateDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(11, "CreateDynamicObject");
	if (core->getData()->getMaxItems(STREAMER_TYPE_OBJECT) == core->getData()->objects.size())
	{
		return 0;
	}
	int objectID = Element::Object::identifier.get();
	Element::SharedObject object(new Element::Object);
	object->amx = amx;
	object->drawDistance = 0.0f;
	object->extraID = 0;
	object->objectID = objectID;
	object->modelID = static_cast<int>(params[1]);
	object->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	object->rotation = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	Utility::addToContainer(object->worlds, static_cast<int>(params[8]));
	Utility::addToContainer(object->interiors, static_cast<int>(params[9]));
	Utility::addToContainer(object->players, static_cast<int>(params[10]));
	object->streamDistance = amx_ctof(params[11]) * amx_ctof(params[11]);
	core->getGrid()->addObject(object);
	core->getData()->objects.insert(std::make_pair(objectID, object));
	return static_cast<cell>(objectID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicObject");
	boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		Utility::destroyObject(o);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicObject");
	boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectPos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicObjectPos");
	boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		Eigen::Vector3f position = o->second->position;
		o->second->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				SetPlayerObjectPos(p->first, i->second, o->second->position[0], o->second->position[1], o->second->position[2]);
			}
		}
		if (position[0] != o->second->position[0] || position[1] != o->second->position[1])
		{
			if (o->second->cell)
			{
				core->getGrid()->removeObject(o->second, true);
			}
		}
		if (o->second->move)
		{
			o->second->move->duration = static_cast<int>((boost::geometry::distance(o->second->move->position.get<0>(), o->second->position) / o->second->move->speed) * 1000.0f);
			o->second->move->position.get<1>() = o->second->position;
			o->second->move->position.get<2>() = (o->second->move->position.get<0>() - o->second->position) / static_cast<float>(o->second->move->duration);
			if (o->second->move->rotation.get<0>().maxCoeff() > -1000.0f)
			{
				o->second->move->rotation.get<1>() = o->second->rotation;
				o->second->move->rotation.get<2>() = (o->second->move->rotation.get<0>() - o->second->rotation) / static_cast<float>(o->second->move->duration);
			}
			o->second->move->time = boost::chrono::steady_clock::now();
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectPos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicObjectPos");
	boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		cell *x = NULL, *y = NULL, *z = NULL;
		amx_GetAddr(amx, params[2], &x);
		amx_GetAddr(amx, params[3], &y);
		amx_GetAddr(amx, params[4], &z);
		*x = amx_ftoc(o->second->position[0]);
		*y = amx_ftoc(o->second->position[1]);
		*z = amx_ftoc(o->second->position[2]);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectRot(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicObjectRot");
	boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			return 0;
		}
		o->second->rotation = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				SetPlayerObjectRot(p->first, i->second, o->second->rotation[0], o->second->rotation[1], o->second->rotation[2]);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectRot(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicObjectRot");
	boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		cell *rX = NULL, *rY = NULL, *rZ = NULL;
		amx_GetAddr(amx, params[2], &rX);
		amx_GetAddr(amx, params[3], &rY);
		amx_GetAddr(amx, params[4], &rZ);
		*rX = amx_ftoc(o->second->rotation[0]);
		*rY = amx_ftoc(o->second->rotation[1]);
		*rZ = amx_ftoc(o->second->rotation[2]);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::MoveDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "MoveDynamicObject");
	if (!amx_ctof(params[5]))
	{
		return 0;
	}
	boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		Eigen::Vector3f position(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		Eigen::Vector3f rotation(amx_ctof(params[6]), amx_ctof(params[7]), amx_ctof(params[8]));
		o->second->move = boost::intrusive_ptr<Element::Object::Move>(new Element::Object::Move);
		o->second->move->duration = static_cast<int>((boost::geometry::distance(position, o->second->position) / amx_ctof(params[5])) * 1000.0f);
		o->second->move->position.get<0>() = position;
		o->second->move->position.get<1>() = o->second->position;
		o->second->move->position.get<2>() = (position - o->second->position) / static_cast<float>(o->second->move->duration);
		o->second->move->rotation.get<0>() = rotation;
		if (o->second->move->rotation.get<0>().maxCoeff() > -1000.0f)
		{
			o->second->move->rotation.get<1>() = o->second->rotation;
			o->second->move->rotation.get<2>() = (rotation - o->second->rotation) / static_cast<float>(o->second->move->duration);
		}
		o->second->move->speed = amx_ctof(params[5]);
		o->second->move->time = boost::chrono::steady_clock::now();
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				StopPlayerObject(p->first, i->second);
				MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
			}
		}
		core->getStreamer()->movingObjects.insert(o->second);
		return static_cast<cell>(o->second->move->duration);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::StopDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "StopDynamicObject");
	boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
				if (i != p->second.internalObjects.end())
				{
					StopPlayerObject(p->first, i->second);
				}
			}
			o->second->move.reset();
			core->getStreamer()->movingObjects.erase(o->second);
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsDynamicObjectMoving(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsDynamicObjectMoving");
	boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicObjects(AMX *amx, cell *params)
{
	Element::Object::identifier.reset();
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		for (boost::unordered_map<int, int>::iterator o = p->second.internalObjects.begin(); o != p->second.internalObjects.end(); ++o)
		{
			DestroyPlayerObject(p->first, o->second);
		}
		p->second.internalObjects.clear();
	}
	core->getGrid()->eraseAllItems(STREAMER_TYPE_OBJECT);
	core->getStreamer()->movingObjects.clear();
	core->getData()->objects.clear();
	return 1;
}

cell AMX_NATIVE_CALL Natives::CountDynamicObjects(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getData()->objects.size());
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPickup(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicPickup");
	if (core->getData()->getMaxItems(STREAMER_TYPE_PICKUP) == core->getData()->pickups.size())
	{
		return 0;
	}
	int pickupID = Element::Pickup::identifier.get();
	Element::SharedPickup pickup(new Element::Pickup);
	pickup->amx = amx;
	pickup->extraID = 0;
	pickup->pickupID = pickupID;
	pickup->worldID = 0;
	pickup->modelID = static_cast<int>(params[1]);
	pickup->type = static_cast<int>(params[2]);
	pickup->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	Utility::addToContainer(pickup->worlds, static_cast<int>(params[6]));
	Utility::addToContainer(pickup->interiors, static_cast<int>(params[7]));
	Utility::addToContainer(pickup->players, static_cast<int>(params[8]));
	pickup->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	core->getGrid()->addPickup(pickup);
	core->getData()->pickups.insert(std::make_pair(pickupID, pickup));
	return static_cast<cell>(pickupID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicPickup(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicPickup");
	boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[1]));
	if (p != core->getData()->pickups.end())
	{
		Utility::destroyPickup(p);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicPickup(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicPickup");
	boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[1]));
	if (p != core->getData()->pickups.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicPickups(AMX *amx, cell *params)
{
	Element::Pickup::identifier.reset();
	for (boost::unordered_map<int, int>::iterator p = core->getStreamer()->internalPickups.begin(); p != core->getStreamer()->internalPickups.end(); ++p)
	{
		DestroyPickup(p->second);
	}
	core->getStreamer()->internalPickups.clear();
	core->getGrid()->eraseAllItems(STREAMER_TYPE_PICKUP);
	core->getData()->pickups.clear();
	return 1;
}

cell AMX_NATIVE_CALL Natives::CountDynamicPickups(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getData()->pickups.size());
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "CreateDynamicCP");
	if (core->getData()->getMaxItems(STREAMER_TYPE_CP) == core->getData()->checkpoints.size())
	{
		return 0;
	}
	int checkpointID = Element::Checkpoint::identifier.get();
	Element::SharedCheckpoint checkpoint(new Element::Checkpoint);
	checkpoint->amx = amx;
	checkpoint->checkpointID = checkpointID;
	checkpoint->extraID = 0;
	checkpoint->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	checkpoint->size = amx_ctof(params[4]);
	Utility::addToContainer(checkpoint->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(checkpoint->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(checkpoint->players, static_cast<int>(params[7]));
	checkpoint->streamDistance = amx_ctof(params[8]) * amx_ctof(params[8]);
	core->getGrid()->addCheckpoint(checkpoint);
	core->getData()->checkpoints.insert(std::make_pair(checkpointID, checkpoint));
	return static_cast<cell>(checkpointID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicCP");
	boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[1]));
	if (c != core->getData()->checkpoints.end())
	{
		Utility::destroyCheckpoint(c);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicCP");
	boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[1]));
	if (c != core->getData()->checkpoints.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "TogglePlayerDynamicCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_set<int>::iterator d = p->second.disabledCheckpoints.find(static_cast<int>(params[2]));
		if (static_cast<int>(params[3]))
		{
			if (d != p->second.disabledCheckpoints.end())
			{
				p->second.disabledCheckpoints.quick_erase(d);
				return 1;
			}
		}
		else
		{
			if (d == p->second.disabledCheckpoints.end())
			{
				if (p->second.visibleCheckpoint == static_cast<int>(params[2]))
				{
					DisablePlayerCheckpoint(p->first);
					p->second.activeCheckpoint = 0;
					p->second.visibleCheckpoint = 0;
				}
				p->second.disabledCheckpoints.insert(static_cast<int>(params[2]));
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerAllDynamicCPs(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "TogglePlayerAllDynamicCPs");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.disabledCheckpoints.clear();
		if (!static_cast<int>(params[2]))
		{
			if (p->second.visibleCheckpoint != 0)
			{
				DisablePlayerCheckpoint(p->first);
				p->second.activeCheckpoint = 0;
				p->second.visibleCheckpoint = 0;
			}
			for (boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin(); c != core->getData()->checkpoints.end(); ++c)
			{
				p->second.disabledCheckpoints.insert(c->first);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsPlayerInDynamicCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint == static_cast<int>(params[2]))
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicCPs(AMX *amx, cell *params)
{
	Element::Checkpoint::identifier.reset();
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		p->second.disabledCheckpoints.clear();
		if (p->second.visibleCheckpoint != 0)
		{
			DisablePlayerCheckpoint(p->first);
			p->second.activeCheckpoint = 0;
			p->second.visibleCheckpoint = 0;
		}
	}
	core->getGrid()->eraseAllItems(STREAMER_TYPE_CP);
	core->getData()->checkpoints.clear();
	return 1;
}

cell AMX_NATIVE_CALL Natives::CountDynamicCPs(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getData()->checkpoints.size());
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicRaceCP");
	if (core->getData()->getMaxItems(STREAMER_TYPE_RACE_CP) == core->getData()->raceCheckpoints.size())
	{
		return 0;
	}
	int raceCheckpointID = Element::RaceCheckpoint::identifier.get();
	Element::SharedRaceCheckpoint raceCheckpoint(new Element::RaceCheckpoint);
	raceCheckpoint->amx = amx;
	raceCheckpoint->extraID = 0;
	raceCheckpoint->raceCheckpointID = raceCheckpointID;
	raceCheckpoint->type = static_cast<int>(params[1]);
	raceCheckpoint->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	raceCheckpoint->next = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	raceCheckpoint->size = amx_ctof(params[8]);
	Utility::addToContainer(raceCheckpoint->worlds, static_cast<int>(params[9]));
	Utility::addToContainer(raceCheckpoint->interiors, static_cast<int>(params[10]));
	Utility::addToContainer(raceCheckpoint->players, static_cast<int>(params[11]));
	raceCheckpoint->streamDistance = amx_ctof(params[12]) * amx_ctof(params[12]);
	core->getGrid()->addRaceCheckpoint(raceCheckpoint);
	core->getData()->raceCheckpoints.insert(std::make_pair(raceCheckpointID, raceCheckpoint));
	return static_cast<cell>(raceCheckpointID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicRaceCP");
	boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[1]));
	if (r != core->getData()->raceCheckpoints.end())
	{
		Utility::destroyRaceCheckpoint(r);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicRaceCP");
	boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[1]));
	if (r != core->getData()->raceCheckpoints.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "TogglePlayerDynamicRaceCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_set<int>::iterator d = p->second.disabledRaceCheckpoints.find(static_cast<int>(params[2]));
		if (static_cast<int>(params[3]))
		{
			if (d != p->second.disabledRaceCheckpoints.end())
			{
				p->second.disabledRaceCheckpoints.quick_erase(d);
				return 1;
			}
		}
		else
		{
			if (d == p->second.disabledRaceCheckpoints.end())
			{
				if (p->second.visibleRaceCheckpoint == static_cast<int>(params[2]))
				{
					DisablePlayerRaceCheckpoint(p->first);
					p->second.activeRaceCheckpoint = 0;
					p->second.visibleRaceCheckpoint = 0;
				}
				p->second.disabledRaceCheckpoints.insert(static_cast<int>(params[2]));
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerAllDynamicRaceCPs(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "TogglePlayerAllDynamicRaceCPs");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.disabledRaceCheckpoints.clear();
		if (!static_cast<int>(params[2]))
		{
			if (p->second.visibleRaceCheckpoint != 0)
			{
				DisablePlayerRaceCheckpoint(p->first);
				p->second.activeRaceCheckpoint = 0;
				p->second.visibleRaceCheckpoint = 0;
			}
			for (boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin(); r != core->getData()->raceCheckpoints.end(); ++r)
			{
				p->second.disabledRaceCheckpoints.insert(r->first);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicRaceCP(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsPlayerInDynamicRaceCP");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint == static_cast<int>(params[2]))
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicRaceCPs(AMX *amx, cell *params)
{
	Element::RaceCheckpoint::identifier.reset();
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		p->second.disabledRaceCheckpoints.clear();
		if (p->second.visibleRaceCheckpoint != 0)
		{
			DisablePlayerRaceCheckpoint(p->first);
			p->second.activeRaceCheckpoint = 0;
			p->second.visibleRaceCheckpoint = 0;
		}
	}
	core->getGrid()->eraseAllItems(STREAMER_TYPE_RACE_CP);
	core->getData()->raceCheckpoints.clear();
	return 1;
}

cell AMX_NATIVE_CALL Natives::CountDynamicRaceCPs(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getData()->raceCheckpoints.size());
}

cell AMX_NATIVE_CALL Natives::CreateDynamicMapIcon(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicMapIcon");
	if (core->getData()->getMaxItems(STREAMER_TYPE_MAP_ICON) == core->getData()->mapIcons.size())
	{
		return 0;
	}
	int mapIconID = Element::MapIcon::identifier.get();
	Element::SharedMapIcon mapIcon(new Element::MapIcon);
	mapIcon->amx = amx;
	mapIcon->extraID = 0;
	mapIcon->mapIconID = mapIconID;
	mapIcon->style = 0;
	mapIcon->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	mapIcon->type = static_cast<int>(params[4]);
	mapIcon->color = static_cast<int>(params[5]);
	Utility::addToContainer(mapIcon->worlds, static_cast<int>(params[6]));
	Utility::addToContainer(mapIcon->interiors, static_cast<int>(params[7]));
	Utility::addToContainer(mapIcon->players, static_cast<int>(params[8]));
	mapIcon->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	core->getGrid()->addMapIcon(mapIcon);
	core->getData()->mapIcons.insert(std::make_pair(mapIconID, mapIcon));
	return static_cast<cell>(mapIconID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicMapIcon(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicMapIcon");
	boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[1]));
	if (m != core->getData()->mapIcons.end())
	{
		Utility::destroyMapIcon(m);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicMapIcon(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicMapIcon");
	boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[1]));
	if (m != core->getData()->mapIcons.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicMapIcons(AMX *amx, cell *params)
{
	Element::MapIcon::identifier.reset();
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		for (boost::unordered_map<int, int>::iterator m = p->second.internalMapIcons.begin(); m != p->second.internalMapIcons.end(); ++m)
		{
			RemovePlayerMapIcon(p->first, m->second);
		}
		p->second.mapIconIdentifier.reset();
		p->second.internalMapIcons.clear();
	}
	core->getGrid()->eraseAllItems(STREAMER_TYPE_MAP_ICON);
	core->getData()->mapIcons.clear();
	return 1;
}

cell AMX_NATIVE_CALL Natives::CountDynamicMapIcons(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getData()->mapIcons.size());
}

cell AMX_NATIVE_CALL Natives::CreateDynamic3DTextLabel(AMX *amx, cell *params)
{
	CHECK_PARAMS(13, "CreateDynamic3DTextLabel");
	if (core->getData()->getMaxItems(STREAMER_TYPE_3D_TEXT_LABEL) == core->getData()->textLabels.size())
	{
		return 0;
	}
	int textLabelID = Element::TextLabel::identifier.get();
	Element::SharedTextLabel textLabel(new Element::TextLabel);
	textLabel->amx = amx;
	textLabel->extraID = 0;
	textLabel->textLabelID = textLabelID;
	textLabel->text = Utility::getStringFromNative(amx, params[1]);
	textLabel->color = static_cast<int>(params[2]);
	textLabel->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	textLabel->drawDistance = amx_ctof(params[6]);
	if (static_cast<int>(params[7]) != INVALID_GENERIC_ID || static_cast<int>(params[8]) != INVALID_GENERIC_ID)
	{
		textLabel->attach = boost::intrusive_ptr<Element::TextLabel::Attach>(new Element::TextLabel::Attach);
		textLabel->attach->player = static_cast<int>(params[7]);
		textLabel->attach->vehicle = static_cast<int>(params[8]);
		if (textLabel->position.cwiseAbs().maxCoeff() > 50.0f)
		{
			textLabel->position.setZero();
		}
		core->getStreamer()->attachedTextLabels.insert(textLabel);
	}
	textLabel->testLOS = static_cast<int>(params[9]) != 0;
	Utility::addToContainer(textLabel->worlds, static_cast<int>(params[10]));
	Utility::addToContainer(textLabel->interiors, static_cast<int>(params[11]));
	Utility::addToContainer(textLabel->players, static_cast<int>(params[12]));
	textLabel->streamDistance = amx_ctof(params[13]) * amx_ctof(params[13]);
	core->getGrid()->addTextLabel(textLabel);
	core->getData()->textLabels.insert(std::make_pair(textLabelID, textLabel));
	return static_cast<cell>(textLabelID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamic3DTextLabel(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamic3DTextLabel");
	boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[1]));
	if (t != core->getData()->textLabels.end())
	{
		Utility::destroyTextLabel(t);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamic3DTextLabel(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamic3DTextLabel");
	boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[1]));
	if (t != core->getData()->textLabels.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::UpdateDynamic3DTextLabelText(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "UpdateDynamic3DTextLabelText");
	boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[1]));
	if (t != core->getData()->textLabels.end())
	{
		t->second->color = static_cast<int>(params[2]);
		t->second->text = Utility::getStringFromNative(amx, params[3]);
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
			if (i != p->second.internalTextLabels.end())
			{
				UpdatePlayer3DTextLabelText(p->first, i->second, t->second->color, t->second->text.c_str());
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamic3DTextLabels(AMX *amx, cell *params)
{
	Element::TextLabel::identifier.reset();
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		for (boost::unordered_map<int, int>::iterator t = p->second.internalTextLabels.begin(); t != p->second.internalTextLabels.end(); ++t)
		{
			DeletePlayer3DTextLabel(p->first, t->second);
		}
		p->second.internalTextLabels.clear();
	}
	core->getGrid()->eraseAllItems(STREAMER_TYPE_3D_TEXT_LABEL);
	core->getStreamer()->attachedTextLabels.clear();
	core->getData()->textLabels.clear();
	return 1;
}

cell AMX_NATIVE_CALL Natives::CountDynamic3DTextLabels(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getData()->textLabels.size());
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCircle(AMX *amx, cell *params)
{
	CHECK_PARAMS(6, "CreateDynamicCircle");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Element::Area::identifier.get();
	Element::SharedArea area(new Element::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_CIRCLE;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->size = amx_ctof(params[3]) * amx_ctof(params[3]);
	Utility::addToContainer(area->worlds, static_cast<int>(params[4]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[5]));
	Utility::addToContainer(area->players, static_cast<int>(params[6]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRectangle(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "CreateDynamicRectangle");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Element::Area::identifier.get();
	Element::SharedArea area(new Element::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_RECTANGLE;
	area->position = Element::Box2D(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), Eigen::Vector2f(amx_ctof(params[3]), amx_ctof(params[4])));
	boost::geometry::correct(boost::get<Element::Box2D>(area->position));
	area->size = boost::geometry::comparable_distance(boost::get<Element::Box2D>(area->position).min_corner(), boost::get<Element::Box2D>(area->position).max_corner());
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicSphere(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "CreateDynamicSphere");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Element::Area::identifier.get();
	Element::SharedArea area(new Element::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_SPHERE;
	area->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	area->size = amx_ctof(params[4]) * amx_ctof(params[4]);
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCube(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicCube");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Element::Area::identifier.get();
	Element::SharedArea area(new Element::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_CUBE;
	area->position = Element::Box3D(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])));
	boost::geometry::correct(boost::get<Element::Box3D>(area->position));
	area->size = boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Element::Box3D>(area->position).min_corner()[0], boost::get<Element::Box3D>(area->position).min_corner()[1]), Eigen::Vector2f(boost::get<Element::Box3D>(area->position).max_corner()[0], boost::get<Element::Box3D>(area->position).max_corner()[1]));
	Utility::addToContainer(area->worlds, static_cast<int>(params[7]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[8]));
	Utility::addToContainer(area->players, static_cast<int>(params[9]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPolygon(AMX *amx, cell *params)
{
	CHECK_PARAMS(7, "CreateDynamicPolygon");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	if (static_cast<int>(params[4] >= 2 && static_cast<int>(params[4]) % 2))
	{
		logprintf("*** CreateDynamicPolygon: Number of points must be divisible by two");
		return 0;
	}
	int areaID = Element::Area::identifier.get();
	Element::SharedArea area(new Element::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_POLYGON;
	Utility::convertArrayToPolygon(amx, params[1], params[4], boost::get<Element::Polygon2D>(area->position));
	Element::Box2D box = boost::geometry::return_envelope<Element::Box2D>(boost::get<Element::Polygon2D>(area->position).get<0>());
	area->size = boost::geometry::comparable_distance(box.min_corner(), box.max_corner());
	boost::get<Element::Polygon2D>(area->position).get<1>() = Eigen::Vector2f(amx_ctof(params[2]), amx_ctof(params[3]));
	Utility::addToContainer(area->worlds, static_cast<int>(params[5]));
	Utility::addToContainer(area->interiors, static_cast<int>(params[6]));
	Utility::addToContainer(area->players, static_cast<int>(params[7]));
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicArea");
	boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		Utility::destroyArea(a);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicArea");
	boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(3, "TogglePlayerDynamicArea");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_set<int>::iterator d = p->second.disabledAreas.find(static_cast<int>(params[2]));
		if (static_cast<int>(params[3]))
		{
			if (d != p->second.disabledAreas.end())
			{
				p->second.disabledAreas.quick_erase(d);
				return 1;
			}
		}
		else
		{
			if (d == p->second.disabledAreas.end())
			{
				p->second.disabledAreas.insert(static_cast<int>(params[2]));
				p->second.internalAreas.erase(static_cast<int>(params[2]));
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::TogglePlayerAllDynamicAreas(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "TogglePlayerAllDynamicAreas");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		p->second.disabledAreas.clear();
		if (!static_cast<int>(params[2]))
		{
			for (boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				p->second.disabledAreas.insert(a->first);
			}
			p->second.internalAreas.clear();
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsPlayerInDynamicArea");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[2]));
		if (i != p->second.internalAreas.end())
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsPlayerInAnyDynamicArea(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsPlayerInAnyDynamicArea");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		if (!p->second.internalAreas.empty())
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicAreaToPlayer(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "AttachDynamicAreaToPlayer");
	boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if (a->second->type == 1 || a->second->type == 3)
		{
			logprintf("*** AttachDynamicAreaToPlayer: Only circles and spheres may be attached to players");
			return 0;
		}
		if (static_cast<int>(params[2]) != INVALID_GENERIC_ID)
		{
			a->second->attach = boost::intrusive_ptr<Element::Area::Attach>(new Element::Area::Attach);
			a->second->attach->player = static_cast<int>(params[2]);
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
					core->getGrid()->removeArea(a->second, true);
				}
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicAreaToVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "AttachDynamicAreaToVehicle");
	boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[1]));
	if (a != core->getData()->areas.end())
	{
		if (a->second->type == 1 || a->second->type == 3)
		{
			logprintf("*** AttachDynamicAreaToVehicle: Only circles and spheres may be attached to vehicles");
			return 0;
		}
		if (static_cast<int>(params[2]) != INVALID_GENERIC_ID)
		{
			a->second->attach = boost::intrusive_ptr<Element::Area::Attach>(new Element::Area::Attach);
			a->second->attach->player = INVALID_GENERIC_ID;
			a->second->attach->vehicle = static_cast<int>(params[2]);
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
					core->getGrid()->removeArea(a->second, true);
				}
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DestroyAllDynamicAreas(AMX *amx, cell *params)
{
	Element::Area::identifier.reset();
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		p->second.disabledAreas.clear();
		p->second.internalAreas.clear();
	}
	core->getGrid()->eraseAllItems(STREAMER_TYPE_AREA);
	core->getStreamer()->attachedAreas.clear();
	core->getData()->areas.clear();
	return 1;
}

cell AMX_NATIVE_CALL Natives::CountDynamicAreas(AMX *amx, cell *params)
{
	return static_cast<cell>(core->getData()->areas.size());
}

cell AMX_NATIVE_CALL Natives::CreateDynamicObjectEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(15, "CreateDynamicObjectEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_OBJECT) == core->getData()->objects.size())
	{
		return 0;
	}
	int objectID = Element::Object::identifier.get();
	Element::SharedObject object(new Element::Object);
	object->amx = amx;
	object->extraID = 0;
	object->objectID = objectID;
	object->modelID = static_cast<int>(params[1]);
	object->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	object->rotation = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	object->drawDistance = amx_ctof(params[8]) * amx_ctof(params[8]);
	object->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	Utility::convertArrayToContainer(amx, params[10], params[13], object->worlds);
	Utility::convertArrayToContainer(amx, params[11], params[14], object->interiors);
	Utility::convertArrayToContainer(amx, params[12], params[15], object->players);
	core->getGrid()->addObject(object);
	core->getData()->objects.insert(std::make_pair(objectID, object));
	return static_cast<cell>(objectID);
	return 1;
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPickupEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicPickupEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_PICKUP) == core->getData()->pickups.size())
	{
		return 0;
	}
	int pickupID = Element::Pickup::identifier.get();
	Element::SharedPickup pickup(new Element::Pickup);
	pickup->amx = amx;
	pickup->extraID = 0;
	pickup->pickupID = pickupID;
	pickup->modelID = static_cast<int>(params[1]);
	pickup->type = static_cast<int>(params[2]);
	pickup->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	pickup->streamDistance = amx_ctof(params[6]) * amx_ctof(params[6]);
	Utility::convertArrayToContainer(amx, params[7], params[10], pickup->worlds);
	Utility::convertArrayToContainer(amx, params[8], params[11], pickup->interiors);
	Utility::convertArrayToContainer(amx, params[9], params[12], pickup->players);
	core->getGrid()->addPickup(pickup);
	core->getData()->pickups.insert(std::make_pair(pickupID, pickup));
	return static_cast<cell>(pickupID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCPEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(11, "CreateDynamicCPEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_CP) == core->getData()->checkpoints.size())
	{
		return 0;
	}
	int checkpointID = Element::Checkpoint::identifier.get();
	Element::SharedCheckpoint checkpoint(new Element::Checkpoint);
	checkpoint->amx = amx;
	checkpoint->checkpointID = checkpointID;
	checkpoint->extraID = 0;
	checkpoint->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	checkpoint->size = amx_ctof(params[4]);
	checkpoint->streamDistance = amx_ctof(params[5]) * amx_ctof(params[5]);
	Utility::convertArrayToContainer(amx, params[6], params[9], checkpoint->worlds);
	Utility::convertArrayToContainer(amx, params[7], params[10], checkpoint->interiors);
	Utility::convertArrayToContainer(amx, params[8], params[11], checkpoint->players);
	core->getGrid()->addCheckpoint(checkpoint);
	core->getData()->checkpoints.insert(std::make_pair(checkpointID, checkpoint));
	return static_cast<cell>(checkpointID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRaceCPEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(15, "CreateDynamicRaceCPEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_RACE_CP) == core->getData()->raceCheckpoints.size())
	{
		return 0;
	}
	int raceCheckpointID = Element::RaceCheckpoint::identifier.get();
	Element::SharedRaceCheckpoint raceCheckpoint(new Element::RaceCheckpoint);
	raceCheckpoint->amx = amx;
	raceCheckpoint->extraID = 0;
	raceCheckpoint->raceCheckpointID = raceCheckpointID;
	raceCheckpoint->type = static_cast<int>(params[1]);
	raceCheckpoint->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	raceCheckpoint->next = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	raceCheckpoint->size = amx_ctof(params[8]);
	raceCheckpoint->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	Utility::convertArrayToContainer(amx, params[10], params[13], raceCheckpoint->worlds);
	Utility::convertArrayToContainer(amx, params[11], params[14], raceCheckpoint->interiors);
	Utility::convertArrayToContainer(amx, params[12], params[15], raceCheckpoint->players);
	core->getGrid()->addRaceCheckpoint(raceCheckpoint);
	core->getData()->raceCheckpoints.insert(std::make_pair(raceCheckpointID, raceCheckpoint));
	return static_cast<cell>(raceCheckpointID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicMapIconEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(13, "CreateDynamicMapIconEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_MAP_ICON) == core->getData()->mapIcons.size())
	{
		return 0;
	}
	int mapIconID = Element::MapIcon::identifier.get();
	Element::SharedMapIcon mapIcon(new Element::MapIcon);
	mapIcon->amx = amx;
	mapIcon->extraID = 0;
	mapIcon->mapIconID = mapIconID;
	mapIcon->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	mapIcon->type = static_cast<int>(params[4]);
	mapIcon->color = static_cast<int>(params[5]);
	mapIcon->style = static_cast<int>(params[6]);
	mapIcon->streamDistance = amx_ctof(params[7]) * amx_ctof(params[7]);
	Utility::convertArrayToContainer(amx, params[8], params[11], mapIcon->worlds);
	Utility::convertArrayToContainer(amx, params[9], params[12], mapIcon->interiors);
	Utility::convertArrayToContainer(amx, params[10], params[13], mapIcon->players);
	core->getGrid()->addMapIcon(mapIcon);
	core->getData()->mapIcons.insert(std::make_pair(mapIconID, mapIcon));
	return static_cast<cell>(mapIconID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamic3DTextLabelEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(16, "CreateDynamic3DTextLabelEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_3D_TEXT_LABEL) == core->getData()->textLabels.size())
	{
		return 0;
	}
	int textLabelID = Element::TextLabel::identifier.get();
	Element::SharedTextLabel textLabel(new Element::TextLabel);
	textLabel->amx = amx;
	textLabel->extraID = 0;
	textLabel->textLabelID = textLabelID;
	textLabel->text = Utility::getStringFromNative(amx, params[1]);
	textLabel->color = static_cast<int>(params[2]);
	textLabel->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	textLabel->drawDistance = amx_ctof(params[6]);
	if (static_cast<int>(params[7]) != INVALID_GENERIC_ID || static_cast<int>(params[8]) != INVALID_GENERIC_ID)
	{
		textLabel->attach = boost::intrusive_ptr<Element::TextLabel::Attach>(new Element::TextLabel::Attach);
		textLabel->attach->player = static_cast<int>(params[7]);
		textLabel->attach->vehicle = static_cast<int>(params[8]);
		if (textLabel->position.cwiseAbs().maxCoeff() > 50.0f)
		{
			textLabel->position.setZero();
		}
		core->getStreamer()->attachedTextLabels.insert(textLabel);
	}
	textLabel->testLOS = static_cast<int>(params[9]) != 0;
	textLabel->streamDistance = amx_ctof(params[10]) * amx_ctof(params[10]);
	Utility::convertArrayToContainer(amx, params[11], params[14], textLabel->worlds);
	Utility::convertArrayToContainer(amx, params[12], params[15], textLabel->interiors);
	Utility::convertArrayToContainer(amx, params[13], params[16], textLabel->players);
	core->getGrid()->addTextLabel(textLabel);
	core->getData()->textLabels.insert(std::make_pair(textLabelID, textLabel));
	return static_cast<cell>(textLabelID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCircleEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicCircleEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Element::Area::identifier.get();
	Element::SharedArea area(new Element::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_CIRCLE;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->size = amx_ctof(params[3]) * amx_ctof(params[3]);
	Utility::convertArrayToContainer(amx, params[4], params[7], area->worlds);
	Utility::convertArrayToContainer(amx, params[5], params[8], area->interiors);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRectangleEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicRectangleEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Element::Area::identifier.get();
	Element::SharedArea area(new Element::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_RECTANGLE;
	area->position = Element::Box2D(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), Eigen::Vector2f(amx_ctof(params[3]), amx_ctof(params[4])));
	boost::geometry::correct(boost::get<Element::Box2D>(area->position));
	area->size = boost::geometry::comparable_distance(boost::get<Element::Box2D>(area->position).min_corner(), boost::get<Element::Box2D>(area->position).max_corner());
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicSphereEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicSphereEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Element::Area::identifier.get();
	Element::SharedArea area(new Element::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_SPHERE;
	area->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	area->size = amx_ctof(params[4]) * amx_ctof(params[4]);
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCubeEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicCubeEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Element::Area::identifier.get();
	Element::SharedArea area(new Element::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_CUBE;
	area->position = Element::Box3D(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])));
	boost::geometry::correct(boost::get<Element::Box3D>(area->position));
	area->size = boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Element::Box3D>(area->position).min_corner()[0], boost::get<Element::Box3D>(area->position).min_corner()[1]), Eigen::Vector2f(boost::get<Element::Box3D>(area->position).max_corner()[0], boost::get<Element::Box3D>(area->position).max_corner()[1]));
	Utility::convertArrayToContainer(amx, params[7], params[10], area->worlds);
	Utility::convertArrayToContainer(amx, params[8], params[11], area->interiors);
	Utility::convertArrayToContainer(amx, params[9], params[12], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPolygonEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicPolygonEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	if (static_cast<int>(params[4] >= 2 && static_cast<int>(params[4]) % 2))
	{
		logprintf("*** CreateDynamicPolygonEx: Number of points must be divisible by two");
	}
	int areaID = Element::Area::identifier.get();
	Element::SharedArea area(new Element::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->extraID = 0;
	area->type = STREAMER_AREA_TYPE_POLYGON;
	Utility::convertArrayToPolygon(amx, params[1], params[4], boost::get<Element::Polygon2D>(area->position));
	Element::Box2D box = boost::geometry::return_envelope<Element::Box2D>(boost::get<Element::Polygon2D>(area->position).get<0>());
	area->size = boost::geometry::comparable_distance(box.min_corner(), box.max_corner());
	boost::get<Element::Polygon2D>(area->position).get<1>() = Eigen::Vector2f(amx_ctof(params[2]), amx_ctof(params[3]));
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::Streamer_CallbackHook(AMX *amx, cell *params)
{
	core->getEvents()->setInterface(amx);
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_OPC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerConnect(static_cast<int>(*playerid)));
		}
		break;
		case STREAMER_OPDC:
		{
			CHECK_PARAMS(3, "Streamer_CallbackHook");
			cell *playerid = NULL, *reason = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &reason);
			return static_cast<cell>(core->getEvents()->OnPlayerDisconnect(static_cast<int>(*playerid), static_cast<int>(*reason)));
		}
		break;
		case STREAMER_OPPP:
		{
			CHECK_PARAMS(3, "Streamer_CallbackHook");
			cell *playerid = NULL, *pickupid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &pickupid);
			return static_cast<cell>(core->getEvents()->OnPlayerPickUpPickup(static_cast<int>(*playerid), static_cast<int>(*pickupid)));
		}
		break;
		case STREAMER_OPEC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerEnterCheckpoint(static_cast<int>(*playerid)));
		}
		break;
		case STREAMER_OPLC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerLeaveCheckpoint(static_cast<int>(*playerid)));
		}
		break;
		case STREAMER_OPERC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerEnterRaceCheckpoint(static_cast<int>(*playerid)));
		}
		break;
		case STREAMER_OPLRC:
		{
			CHECK_PARAMS(2, "Streamer_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			return static_cast<cell>(core->getEvents()->OnPlayerLeaveRaceCheckpoint(static_cast<int>(*playerid)));
		}
		break;
	}
	return 0;
}
