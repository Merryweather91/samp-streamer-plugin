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

#include "main.h"
#include "Source/Core.h"
#include "Source/Grid.h"
#include "Source/Invoke.h"
#include "Source/Streamer.h"
#include "Source/Natives.h"

logprintf_t logprintf;

extern void * pAMXFunctions;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void ** ppData)
{
	core = new Core;
	grid = new Grid;
	invoke = new Invoke;
	streamer = new Streamer;
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	logprintf("\n\n*** Streamer Plugin v%s by Incognito loaded ***\n", PLUGIN_VERSION);
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("\n\n*** Streamer Plugin v%s by Incognito unloaded ***\n", PLUGIN_VERSION);
}

AMX_NATIVE_INFO natives[] =
{
	{ "Streamer_TickRate", Natives::Streamer_TickRate },
	{ "Streamer_MaxItems", Natives::Streamer_MaxItems },
	{ "Streamer_VisibleItems", Natives::Streamer_VisibleItems },
	{ "Streamer_CellDistance", Natives::Streamer_CellDistance },
	{ "Streamer_CellSize", Natives::Streamer_CellSize },
	{ "Streamer_Update", Natives::Streamer_Update },
	{ "Streamer_UpdateEx", Natives::Streamer_UpdateEx },
	{ "Streamer_GetFloatData", Natives::Streamer_GetFloatData },
	{ "Streamer_SetFloatData", Natives::Streamer_SetFloatData },
	{ "Streamer_GetIntData", Natives::Streamer_GetIntData },
	{ "Streamer_SetIntData", Natives::Streamer_SetIntData },
	{ "Streamer_IsInArrayData", Natives::Streamer_IsInArrayData },
	{ "Streamer_AppendArrayData", Natives::Streamer_AppendArrayData },
	{ "Streamer_RemoveArrayData", Natives::Streamer_RemoveArrayData },
	{ "Streamer_GetUpperBound", Natives::Streamer_GetUpperBound },
	{ "Streamer_IsItemVisible", Natives::Streamer_IsItemVisible },
	{ "Streamer_CountVisibleItems", Natives::Streamer_CountVisibleItems },
	{ "Streamer_DestroyAllVisibleItems", Natives::Streamer_DestroyAllVisibleItems },
	{ "CreateDynamicObject", Natives::CreateDynamicObject },
	{ "DestroyDynamicObject", Natives::DestroyDynamicObject },
	{ "IsValidDynamicObject", Natives::IsValidDynamicObject },
	{ "SetDynamicObjectPos", Natives::SetDynamicObjectPos },
	{ "GetDynamicObjectPos", Natives::GetDynamicObjectPos },
	{ "SetDynamicObjectRot", Natives::SetDynamicObjectRot },
	{ "GetDynamicObjectRot", Natives::GetDynamicObjectRot },
	{ "MoveDynamicObject", Natives::MoveDynamicObject },
	{ "StopDynamicObject", Natives::StopDynamicObject },
	{ "DestroyAllDynamicObjects", Natives::DestroyAllDynamicObjects },
	{ "CountDynamicObjects", Natives::CountDynamicObjects },
	{ "CreateDynamicPickup", Natives::CreateDynamicPickup },
	{ "DestroyDynamicPickup", Natives::DestroyDynamicPickup },
	{ "IsValidDynamicPickup", Natives::IsValidDynamicPickup },
	{ "DestroyAllDynamicPickups", Natives::DestroyAllDynamicPickups },
	{ "CountDynamicPickups", Natives::CountDynamicPickups },
	{ "CreateDynamicCP", Natives::CreateDynamicCP },
	{ "DestroyDynamicCP", Natives::DestroyDynamicCP },
	{ "IsValidDynamicCP", Natives::IsValidDynamicCP },
	{ "TogglePlayerDynamicCP", Natives::TogglePlayerDynamicCP },
	{ "TogglePlayerAllDynamicCPs", Natives::TogglePlayerAllDynamicCPs },
	{ "IsPlayerInDynamicCP", Natives::IsPlayerInDynamicCP },
	{ "DestroyAllDynamicCPs", Natives::DestroyAllDynamicCPs },
	{ "CountDynamicCPs", Natives::CountDynamicCPs },
	{ "CreateDynamicRaceCP", Natives::CreateDynamicRaceCP },
	{ "DestroyDynamicRaceCP", Natives::DestroyDynamicRaceCP },
	{ "IsValidDynamicRaceCP", Natives::IsValidDynamicRaceCP },
	{ "TogglePlayerDynamicRaceCP", Natives::TogglePlayerDynamicRaceCP },
	{ "TogglePlayerAllDynamicRaceCPs", Natives::TogglePlayerAllDynamicRaceCPs },
	{ "IsPlayerInDynamicRaceCP", Natives::IsPlayerInDynamicCP },
	{ "DestroyAllDynamicRaceCPs", Natives::DestroyAllDynamicRaceCPs },
	{ "CountDynamicRaceCPs", Natives::CountDynamicRaceCPs },
	{ "CreateDynamicMapIcon", Natives::CreateDynamicMapIcon },
	{ "DestroyDynamicMapIcon", Natives::DestroyDynamicMapIcon },
	{ "IsValidDynamicMapIcon", Natives::IsValidDynamicMapIcon },
	{ "DestroyAllDynamicMapIcons", Natives::DestroyAllDynamicMapIcons },
	{ "CountDynamicMapIcons", Natives::CountDynamicMapIcons },
	{ "CreateDynamic3DTextLabel", Natives::CreateDynamic3DTextLabel },
	{ "DestroyDynamic3DTextLabel", Natives::DestroyDynamic3DTextLabel },
	{ "IsValidDynamic3DTextLabel", Natives::IsValidDynamic3DTextLabel },
	{ "UpdateDynamic3DTextLabelText", Natives::UpdateDynamic3DTextLabelText },
	{ "DestroyAllDynamic3DTextLabels", Natives::DestroyAllDynamic3DTextLabels },
	{ "CountDynamic3DTextLabels", Natives::CountDynamic3DTextLabels },
	{ "CreateDynamicCircle", Natives::CreateDynamicCircle },
	{ "CreateDynamicRectangle", Natives::CreateDynamicRectangle },
	{ "CreateDynamicSphere", Natives::CreateDynamicSphere },
	{ "CreateDynamicCube", Natives::CreateDynamicCube },
	{ "DestroyDynamicArea", Natives::DestroyDynamicArea },
	{ "IsValidDynamicArea", Natives::IsValidDynamicArea },
	{ "TogglePlayerDynamicArea", Natives::TogglePlayerDynamicArea },
	{ "TogglePlayerAllDynamicAreas", Natives::TogglePlayerAllDynamicAreas },
	{ "IsPlayerInDynamicArea", Natives::IsPlayerInDynamicArea },
	{ "AttachDynamicAreaToPlayer", Natives::AttachDynamicAreaToPlayer },
	{ "AttachDynamicAreaToVehicle", Natives::AttachDynamicAreaToVehicle },
	{ "DestroyAllDynamicAreas", Natives::DestroyAllDynamicAreas },
	{ "CountDynamicAreas", Natives::CountDynamicAreas },
	{ "Streamer_AddPlayer", Natives::Streamer_AddPlayer },
	{ "Streamer_RemovePlayer", Natives::Streamer_RemovePlayer },
	{ "Streamer_VerifyPickup", Natives::Streamer_VerifyPickup },
	{ "Streamer_VerifyCheckpoint", Natives::Streamer_VerifyCheckpoint },
	{ "Streamer_RegisterInterface", Natives::Streamer_RegisterInterface },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX * amx)
{
	invoke->amx_list.push_back(amx);
	return amx_Register(amx, natives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX * amx)
{
	for (std::list<AMX *>::iterator i = invoke->amx_list.begin(); i != invoke->amx_list.end(); ++i)
	{
		if (* i == amx)
		{
			invoke->amx_list.erase(i);
			break;
		}
	}
	boost::unordered_map<int, Core::SharedObject>::iterator o = core->objects.begin();
	while (o != core->objects.end())
	{
		if (o->second->amx == amx)
		{
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				boost::unordered_map<int, int>::iterator f = p->internalObjects.find(o->first);
				if (f != p->internalObjects.end())
				{
					invoke->callNative(&PAWN::DestroyPlayerObject, p->playerID, f->second);
					p->internalObjects.quick_erase(f);
				}
			}
			if (core->objects.size() > 1)
			{
				core->global.deletedObjects.first.insert(o->first);
			}
			else
			{
				core->global.deletedObjects = std::make_pair(std::set<int>(), 0);
			}
			grid->removeObject(o->second);
			o = core->objects.erase(o);
		}
		else
		{
			++o;
		}
	}
	boost::unordered_map<int, Core::SharedPickup>::iterator p = core->pickups.begin();
	while (p != core->pickups.end())
	{
		if (p->second->amx == amx)
		{
			boost::unordered_map<int, int>::iterator f = core->global.internalPickups.find(p->first);
			if (f != core->global.internalPickups.end())
			{
				invoke->callNative(&PAWN::DestroyPickup, f->second);
				core->global.internalPickups.quick_erase(f);
			}
			if (core->pickups.size() > 1)
			{
				core->global.deletedPickups.first.insert(p->first);
			}
			else
			{
				core->global.deletedPickups = std::make_pair(std::set<int>(), 0);
			}
			grid->removePickup(p->second);
			p = core->pickups.erase(p);
		}
		else
		{
			++p;
		}
	}
	boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = core->checkpoints.begin();
	while (c != core->checkpoints.end())
	{
		if (c->second->amx == amx)
		{
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				if (p->visibleCheckpoint == c->first)
				{
					invoke->callNative(&PAWN::DisablePlayerCheckpoint, p->playerID);
					p->activeCheckpoint = 0;
					p->visibleCheckpoint = 0;
				}
				p->disabledCheckpoints.erase(c->first);
			}
			if (core->checkpoints.size() > 1)
			{
				core->global.deletedCheckpoints.first.insert(c->first);
			}
			else
			{
				core->global.deletedCheckpoints = std::make_pair(std::set<int>(), 0);
			}
			grid->removeCheckpoint(c->second);
			c = core->checkpoints.erase(c);
		}
		else
		{
			++c;
		}
	}
	boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = core->raceCheckpoints.begin();
	while (r != core->raceCheckpoints.end())
	{
		if (r->second->amx == amx)
		{
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				if (p->visibleRaceCheckpoint == r->first)
				{
					invoke->callNative(&PAWN::DisablePlayerRaceCheckpoint, p->playerID);
					p->activeRaceCheckpoint = 0;
					p->visibleRaceCheckpoint = 0;
				}
				p->disabledRaceCheckpoints.erase(r->first);
			}
			if (core->raceCheckpoints.size() > 1)
			{
				core->global.deletedRaceCheckpoints.first.insert(r->first);
			}
			else
			{
				core->global.deletedRaceCheckpoints = std::make_pair(std::set<int>(), 0);
			}
			grid->removeRaceCheckpoint(r->second);
			r = core->raceCheckpoints.erase(r);
		}
		else
		{
			++r;
		}
	}
	boost::unordered_map<int, Core::SharedMapIcon>::iterator m = core->mapIcons.begin();
	while (m != core->mapIcons.end())
	{
		if (m->second->amx == amx)
		{
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				boost::unordered_map<int, int>::iterator f = p->internalMapIcons.find(m->first);
				if (f != p->internalMapIcons.end())
				{
					invoke->callNative(&PAWN::RemovePlayerMapIcon, p->playerID, f->second);
					p->sortedInternalMapIcons.erase(f->second);
					p->internalMapIcons.quick_erase(f);
				}
			}
			if (core->mapIcons.size() > 1)
			{
				core->global.deletedMapIcons.first.insert(m->first);
			}
			else
			{
				core->global.deletedMapIcons = std::make_pair(std::set<int>(), 0);
			}
			grid->removeMapIcon(m->second);
			m = core->mapIcons.erase(m);
		}
		else
		{
			++m;
		}
	}
	boost::unordered_map<int, Core::SharedTextLabel>::iterator t = core->textLabels.begin();
	while (t != core->textLabels.end())
	{
		if (t->second->amx == amx)
		{
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				boost::unordered_map<int, int>::iterator f = p->internalTextLabels.find(t->first);
				if (f != p->internalTextLabels.end())
				{
					invoke->callNative(&PAWN::DeletePlayer3DTextLabel, p->playerID, f->second);
					p->internalTextLabels.quick_erase(f);
				}
			}
			if (core->textLabels.size() > 1)
			{
				core->global.deletedTextLabels.first.insert(t->first);
			}
			else
			{
				core->global.deletedTextLabels = std::make_pair(std::set<int>(), 0);
			}
			grid->removeTextLabel(t->second);
			t = core->textLabels.erase(t);
		}
		else
		{
			++t;
		}
	}
	boost::unordered_map<int, Core::SharedArea>::iterator a = core->areas.begin();
	while (a != core->areas.end())
	{
		if (a->second->amx == amx)
		{
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				p->disabledAreas.erase(a->first);
				p->visibleAreas.erase(a->first);
			}
			if (core->areas.size() > 1)
			{
				core->global.deletedAreas.first.insert(a->first);
			}
			else
			{
				core->global.deletedAreas = std::make_pair(std::set<int>(), 0);
			}
			grid->removeArea(a->second);
			a = core->areas.erase(a);
		}
		else
		{
			++a;
		}
	}
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	if (core->global.tickCount >= core->global.tickRate)
	{
		if (!core->movingAreas.empty())
		{
			streamer->updateMovingAreas();
		}
		if (!core->movingObjects.empty())
		{
			streamer->updateMovingObjects();
		}
		if (!core->movingTextLabels.empty())
		{
			streamer->updateMovingTextLabels();
		}
		if (!core->players.empty())
		{
			std::set<Grid::SharedCell, Grid::Cell> totalCells;
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				int playerState = invoke->callNative(&PAWN::GetPlayerState, p->playerID);
				if (playerState != PLAYER_STATE_NONE && playerState != PLAYER_STATE_WASTED)
				{
					float playerX = p->x, playerY = p->y, playerZ = p->z;
					invoke->callNative(&PAWN::GetPlayerPos, p->playerID, &p->x, &p->y, &p->z);
					if (playerX != p->x || playerY != p->y || playerZ != p->z)
					{
						std::vector<Grid::SharedCell> playerCells;
						grid->findNearbyCells(* p, playerCells, totalCells);
						p->interiorID = invoke->callNative(&PAWN::GetPlayerInterior, p->playerID);
						if (p->interiorID >= MAX_INTERIORS)
						{
							p->interiorID = 0;
						}
						p->worldID = invoke->callNative(&PAWN::GetPlayerVirtualWorld, p->playerID);
						if (!playerCells.empty())
						{
							if (!core->objects.empty())
							{
								streamer->processObjects(* p, playerCells);
							}
							if (!core->checkpoints.empty())
							{
								streamer->processCheckpoints(* p, playerCells);
							}
							if (!core->raceCheckpoints.empty())
							{
								streamer->processRaceCheckpoints(* p, playerCells);
							}
							if (!core->mapIcons.empty())
							{
								streamer->processMapIcons(* p, playerCells);
							}
							if (!core->textLabels.empty())
							{
								streamer->processTextLabels(* p, playerCells);
							}
							if (!core->areas.empty())
							{
								streamer->processAreas(* p, playerCells);
							}
						}
					}
				}
			}
			if (!core->pickups.empty())
			{
				grid->mergeRemainingCells(totalCells);
				streamer->processPickups(totalCells);
			}
		}
		core->global.tickCount = 0;
	}
	if (!invoke->amx_list.empty())
	{
		++core->global.tickCount;
	}
}
