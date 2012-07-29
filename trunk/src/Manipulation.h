/*
    SA-MP Streamer Plugin v2.6.1
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

#ifndef MANIPULATION_H
#define MANIPULATION_H

#include "main.h"
#include "utility.h"

#include <sampgdk/plugin.h>

namespace Manipulation
{
	enum
	{
		AttachedObject,
		AttachedPlayer,
		AttachedVehicle,
		AttachOffsetX,
		AttachOffsetY,
		AttachOffsetZ,
		AttachRX,
		AttachRY,
		AttachRZ,
		AttachX,
		AttachY,
		AttachZ,
		Color,
		DrawDistance,
		ExtraID,
		InteriorID,
		MaxX,
		MaxY,
		MaxZ,
		MinX,
		MinY,
		MinZ,
		ModelID,
		MoveRX,
		MoveRY,
		MoveRZ,
		MoveSpeed,
		MoveX,
		MoveY,
		MoveZ,
		NextX,
		NextY,
		NextZ,
		PlayerID,
		RX,
		RY,
		RZ,
		Size,
		StreamDistance,
		Style,
		TestLOS,
		Type,
		WorldID,
		X,
		Y,
		Z
	};

	int getFloatData(AMX *amx, cell *params);
	int setFloatData(AMX *amx, cell *params);
	int getIntData(AMX *amx, cell *params);
	int setIntData(AMX *amx, cell *params);
	int getArrayData(AMX *amx, cell *params);
	int setArrayData(AMX *amx, cell *params);
	int isInArrayData(AMX *amx, cell *params);
	int appendArrayData(AMX *amx, cell *params);
	int removeArrayData(AMX *amx, cell *params);

	template <typename T>
	int getArrayDataForItem(T &container, AMX *amx, int id, int type, cell output, cell size)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (type)
			{
				case ExtraID:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->extras) != 0;
				}
				case InteriorID:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->interiors) != 0;
				}
				case PlayerID:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->players) != 0;
				}
				case WorldID:
				{
					return Utility::convertContainerToArray(amx, output, size, i->second->worlds) != 0;
				}
				default:
				{
					logprintf("*** Streamer_GetArrayData: Invalid data specified");
					return 0;
				}
			}
		}
		logprintf("*** Streamer_GetArrayData: Invalid ID specified");
		return 0;
	}

	template <typename T>
	int setArrayDataForItem(T &container, AMX *amx, int id, int type, cell input, cell size)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (type)
			{
				case ExtraID:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->extras) != 0;
				}
				case InteriorID:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->interiors) != 0;
				}
				case PlayerID:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->players) != 0;
				}
				case WorldID:
				{
					return Utility::convertArrayToContainer(amx, input, size, i->second->worlds) != 0;
				}
				default:
				{
					logprintf("*** Streamer_SetArrayData: Invalid data specified");
					return 0;
				}
			}
		}
		logprintf("*** Streamer_SetArrayData: Invalid ID specified");
		return 0;
	}

	template <typename T>
	int isInArrayDataForItem(T &container, int id, int type, int value)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (type)
			{
				case ExtraID:
				{
					return Utility::isInContainer(i->second->extras, value) != 0;
				}
				case InteriorID:
				{
					return Utility::isInContainer(i->second->interiors, value) != 0;
				}
				case PlayerID:
				{
					return Utility::isInContainer(i->second->players, value) != 0;
				}
				case WorldID:
				{
					return Utility::isInContainer(i->second->worlds, value) != 0;
				}
				default:
				{
					logprintf("*** Streamer_IsInArrayData: Invalid data specified");
					return 0;
				}
			}
		}
		logprintf("*** Streamer_IsInArrayData: Invalid ID specified");
		return 0;
	}

	template <typename T>
	int appendArrayDataForItem(T &container, int id, int type, int value)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (type)
			{
				case ExtraID:
				{
					return Utility::addToContainer(i->second->extras, value) != 0;
				}
				case InteriorID:
				{
					return Utility::addToContainer(i->second->interiors, value) != 0;
				}
				case PlayerID:
				{
					return Utility::addToContainer(i->second->players, value) != 0;
				}
				case WorldID:
				{
					return Utility::addToContainer(i->second->worlds, value) != 0;
				}
				default:
				{
					logprintf("*** Streamer_AppendArrayData: Invalid data specified");
					return 0;
				}
			}
		}
		logprintf("*** Streamer_AppendArrayData: Invalid ID specified");
		return 0;
	}

	template <typename T>
	int removeArrayDataForItem(T &container, int id, int type, int value)
	{
		typename T::iterator i = container.find(id);
		if (i != container.end())
		{
			switch (type)
			{
				case ExtraID:
				{
					return Utility::removeFromContainer(i->second->extras, value) != 0;
				}
				case InteriorID:
				{
					return Utility::removeFromContainer(i->second->interiors, value) != 0;
				}
				case PlayerID:
				{
					return Utility::removeFromContainer(i->second->players, value) != 0;
				}
				case WorldID:
				{
					return Utility::removeFromContainer(i->second->worlds, value) != 0;
				}
				default:
				{
					logprintf("*** Streamer_RemoveArrayData: Invalid data specified");
					return 0;
				}
			}
		}
		logprintf("*** Streamer_RemoveArrayData: Invalid ID specified");
		return 0;
	}
}

#endif
