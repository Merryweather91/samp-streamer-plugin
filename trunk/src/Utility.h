/*
    SA-MP Streamer Plugin v2.6.1
    Copyright � 2012 Incognito

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

#ifndef UTILITY_H
#define UTILITY_H

#include "common.h"
#include "item.h"

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <Eigen/Core>

#include <sampgdk/plugin.h>

#include <bitset>
#include <string>

namespace Utility
{
	cell AMX_NATIVE_CALL hookedNative(AMX *amx, cell *params);

	int checkInterfaceAndRegisterNatives(AMX *amx, AMX_NATIVE_INFO *amxNativeList);
	void destroyAllItemsInInterface(AMX *amx);

	boost::unordered_map<int, Item::SharedArea>::iterator destroyArea(boost::unordered_map<int, Item::SharedArea>::iterator a);
	boost::unordered_map<int, Item::SharedCheckpoint>::iterator destroyCheckpoint(boost::unordered_map<int, Item::SharedCheckpoint>::iterator c);
	boost::unordered_map<int, Item::SharedMapIcon>::iterator destroyMapIcon(boost::unordered_map<int, Item::SharedMapIcon>::iterator m);
	boost::unordered_map<int, Item::SharedObject>::iterator destroyObject(boost::unordered_map<int, Item::SharedObject>::iterator o);
	boost::unordered_map<int, Item::SharedPickup>::iterator destroyPickup(boost::unordered_map<int, Item::SharedPickup>::iterator p);
	boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator destroyRaceCheckpoint(boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r);
	boost::unordered_map<int, Item::SharedTextLabel>::iterator destroyTextLabel(boost::unordered_map<int, Item::SharedTextLabel>::iterator t);

	bool isPointInArea(const Eigen::Vector3f &point, const Item::SharedArea &area);

	template<typename T>
	inline bool addToContainer(boost::unordered_set<T> &container, T value)
	{
		if (value >= 0)
		{
			container.insert(value);
			return true;
		}
		else
		{
			container.clear();
		}
		return false;
	}

	template<std::size_t N, typename T>
	inline bool addToContainer(std::bitset<N> &container, T value)
	{
		if (value >= 0 && static_cast<std::size_t>(value) < N)
		{
			container.set(static_cast<std::size_t>(value));
			return true;
		}
		else
		{
			container.set();
		}
		return false;
	}

	template<typename T>
	inline bool isInContainer(boost::unordered_set<T> &container, T value)
	{
		if (value >= 0)
		{
			if (container.find(value) != container.end())
			{
				return true;
			}
		}
		else
		{
			if (container.empty())
			{
				return true;
			}
		}
		return false;
	}

	template<std::size_t N, typename T>
	inline bool isInContainer(std::bitset<N> &container, T value)
	{
		if (value >= 0 && static_cast<std::size_t>(value) < N)
		{
			if (container[static_cast<std::size_t>(value)])
			{
				return true;
			}
		}
		else
		{
			if (container.count() == N)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline bool removeFromContainer(boost::unordered_set<T> &container, T value)
	{
		if (value >= 0)
		{
			container.erase(value);
			return true;
		}
		else
		{
			container.clear();
		}
		return false;
	}

	template<std::size_t N, typename T>
	inline bool removeFromContainer(std::bitset<N> &container, T value)
	{
		if (value >= 0 && static_cast<std::size_t>(value) < N)
		{
			container.reset(static_cast<std::size_t>(value));
			return true;
		}
		else
		{
			container.reset();
		}
		return false;
	}

	template<typename T>
	inline bool convertArrayToContainer(AMX *amx, cell input, cell size, boost::unordered_set<T> &container)
	{
		cell *array = NULL;
		amx_GetAddr(amx, input, &array);
		container.clear();
		for (std::size_t i = 0; i < static_cast<std::size_t>(size); ++i)
		{
			if (!addToContainer(container, static_cast<T>(array[i])))
			{
				return false;
			}
		}
		return true;
	}

	template<std::size_t N>
	inline bool convertArrayToContainer(AMX *amx, cell input, cell size, std::bitset<N> &container)
	{
		cell *array = NULL;
		amx_GetAddr(amx, input, &array);
		container.reset();
		for (std::size_t i = 0; i < static_cast<std::size_t>(size); ++i)
		{
			if (!addToContainer(container, static_cast<std::size_t>(array[i])))
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline bool convertContainerToArray(AMX *amx, cell output, cell size, boost::unordered_set<T> &container)
	{
		cell *array = NULL;
		std::size_t i = 0;
		amx_GetAddr(amx, output, &array);
		for (typename boost::unordered_set<T>::iterator c = container.begin(); c != container.end(); ++c)
		{
			if (i == static_cast<std::size_t>(size))
			{
				return false;
			}
			array[i++] = static_cast<cell>(*c);
		}
		return true;
	}

	template<std::size_t N>
	inline bool convertContainerToArray(AMX *amx, cell output, cell size, std::bitset<N> &container)
	{
		cell *array = NULL;
		std::size_t i = 0;
		amx_GetAddr(amx, output, &array);
		for (std::size_t c = 0; c < N; ++c)
		{
			if (i == static_cast<std::size_t>(size))
			{
				return false;
			}
			if (container[c])
			{
				array[i++] = static_cast<cell>(c);
			}
		}
		return true;
	}

	void convertArrayToPolygon(AMX *amx, cell input, cell size, Polygon2D &polygon);
	std::string convertNativeStringToString(AMX *amx, cell input);
	void convertStringToNativeString(AMX *amx, cell output, cell size, std::string string);
	void storeFloatInNative(AMX *amx, cell output, float number);
	void storeIntegerInNative(AMX *amx, cell output, int number);
}

#endif
