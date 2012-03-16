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

#ifndef UTILITY_H
#define UTILITY_H

namespace Utility
{
	cell AMX_NATIVE_CALL hookedNative(AMX *amx, cell *params);

	bool catchRuntimeErrorsInInterface(AMX *amx);
	void destroyAllItemsInInterface(AMX *amx);

	boost::unordered_map<int, Element::SharedArea>::iterator destroyArea(boost::unordered_map<int, Element::SharedArea>::iterator a);
	boost::unordered_map<int, Element::SharedCheckpoint>::iterator destroyCheckpoint(boost::unordered_map<int, Element::SharedCheckpoint>::iterator c);
	boost::unordered_map<int, Element::SharedMapIcon>::iterator destroyMapIcon(boost::unordered_map<int, Element::SharedMapIcon>::iterator m);
	boost::unordered_map<int, Element::SharedObject>::iterator destroyObject(boost::unordered_map<int, Element::SharedObject>::iterator o);
	boost::unordered_map<int, Element::SharedPickup>::iterator destroyPickup(boost::unordered_map<int, Element::SharedPickup>::iterator p);
	boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator destroyRaceCheckpoint(boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r);
	boost::unordered_map<int, Element::SharedTextLabel>::iterator destroyTextLabel(boost::unordered_map<int, Element::SharedTextLabel>::iterator t);

	inline bool addToContainer(boost::unordered_set<int> &container, int value)
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

	template<size_t N>
	inline bool addToContainer(std::bitset<N> &container, size_t value)
	{
		if (value >= 0 && value < container.size())
		{
			container.set(value);
			return true;
		}
		else
		{
			container.set();
		}
		return false;
	}

	inline bool removeFromContainer(boost::unordered_set<int> &container, int value)
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

	template<size_t N>
	inline bool removeFromContainer(std::bitset<N> &container, size_t value)
	{
		if (value >= 0 && value < container.size())
		{
			container.reset(value);
			return true;
		}
		else
		{
			container.reset();
		}
		return false;
	}

	template<typename T>
	inline void getArrayFromNative(AMX *amx, cell input, cell size, T &container)
	{
		cell *array = NULL;
		amx_GetAddr(amx, input, &array);
		for (size_t i = 0; i < static_cast<size_t>(size); ++i)
		{
			if (!addToContainer(container, array[i]))
			{
				return;
			}
		}
	}

	void getPolygonFromNative(AMX *amx, cell input, cell size, Element::Polygon2D &polygon);
	std::string getStringFromNative(AMX *amx, cell input);
}

#endif
