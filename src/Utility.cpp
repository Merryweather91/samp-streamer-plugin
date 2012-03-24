/*
    SA-MP Streamer Plugin v2.6
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

#include "Main.h"
#include "Utility.h"

using namespace Utility;

cell AMX_NATIVE_CALL Utility::hookedNative(AMX *amx, cell *params)
{
	return 1;
}

void Utility::checkIncludeFileInInterface(AMX *amx)
{
	bool anyNativesFound = false;
	bool anyNativesHooked = false;
	AMX_HEADER *header = reinterpret_cast<AMX_HEADER*>(amx->base);
	AMX_FUNCSTUBNT *natives = reinterpret_cast<AMX_FUNCSTUBNT*>(amx->base + header->natives);
	int numberOfNatives = 0;
	amx_NumNatives(amx, &numberOfNatives);
	for (int i = 0; i < numberOfNatives; ++i)
	{
		char *name = reinterpret_cast<char*>(amx->base + natives[i].nameofs);
		if (std::string(name).find("Streamer_") != std::string::npos)
		{
			anyNativesFound = true;
			if (!natives[i].address)
			{
				char *name = reinterpret_cast<char*>(amx->base + natives[i].nameofs);
				if (std::string(name).find("Streamer_") != std::string::npos)
				{
					natives[i].address = reinterpret_cast<cell>(hookedNative);
					anyNativesHooked = true;
				}
			}
		}
	}
	if (anyNativesFound)
	{
		cell amx_addr = 0;
		bool checkPassed = false;
		if (!amx_FindPubVar(amx, "Streamer_IncludeFileVersion", &amx_addr))
		{
			cell *phys_addr = NULL;
			if (!amx_GetAddr(amx, amx_addr, &phys_addr))
			{
				if (static_cast<int>(*phys_addr) == INCLUDE_VERSION)
				{
					checkPassed = true;
				}
			}
		}
		if (!checkPassed)
		{
			logprintf("*** Streamer Plugin: Include file version does not match plugin version (script needs to be recompiled with the latest include file)");
		}
	}
	if (anyNativesHooked)
	{
		logprintf("*** Streamer Plugin: Obsolete or invalid native found (script needs to be recompiled with the latest include file)");
	}
}

void Utility::destroyAllItemsInInterface(AMX *amx)
{
	boost::unordered_map<int, Element::SharedObject>::iterator o = core->getData()->objects.begin();
	while (o != core->getData()->objects.end())
	{
		if (o->second->amx == amx)
		{
			o = destroyObject(o);
		}
		else
		{
			++o;
		}
	}
	boost::unordered_map<int, Element::SharedPickup>::iterator p = core->getData()->pickups.begin();
	while (p != core->getData()->pickups.end())
	{
		if (p->second->amx == amx)
		{
			p = destroyPickup(p);
		}
		else
		{
			++p;
		}
	}
	boost::unordered_map<int, Element::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin();
	while (c != core->getData()->checkpoints.end())
	{
		if (c->second->amx == amx)
		{
			c = destroyCheckpoint(c);
		}
		else
		{
			++c;
		}
	}
	boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin();
	while (r != core->getData()->raceCheckpoints.end())
	{
		if (r->second->amx == amx)
		{
			r = destroyRaceCheckpoint(r);
		}
		else
		{
			++r;
		}
	}
	boost::unordered_map<int, Element::SharedMapIcon>::iterator m = core->getData()->mapIcons.begin();
	while (m != core->getData()->mapIcons.end())
	{
		if (m->second->amx == amx)
		{
			m = destroyMapIcon(m);
		}
		else
		{
			++m;
		}
	}
	boost::unordered_map<int, Element::SharedTextLabel>::iterator t = core->getData()->textLabels.begin();
	while (t != core->getData()->textLabels.end())
	{
		if (t->second->amx == amx)
		{
			t = destroyTextLabel(t);
		}
		else
		{
			++t;
		}
	}
	boost::unordered_map<int, Element::SharedArea>::iterator a = core->getData()->areas.begin();
	while (a != core->getData()->areas.end())
	{
		if (a->second->amx == amx)
		{
			a = destroyArea(a);
		}
		else
		{
			++a;
		}
	}
}

boost::unordered_map<int, Element::SharedArea>::iterator Utility::destroyArea(boost::unordered_map<int, Element::SharedArea>::iterator a)
{
	Element::Area::identifier.remove(a->first, core->getData()->areas.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		p->second.disabledAreas.erase(a->first);
		p->second.internalAreas.erase(a->first);
		p->second.visibleCell->areas.erase(a->first);
	}
	core->getGrid()->removeArea(a->second);
	return core->getData()->areas.erase(a);
}

boost::unordered_map<int, Element::SharedCheckpoint>::iterator Utility::destroyCheckpoint(boost::unordered_map<int, Element::SharedCheckpoint>::iterator c)
{
	Element::Checkpoint::identifier.remove(c->first, core->getData()->checkpoints.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		if (p->second.visibleCheckpoint == c->first)
		{
			DisablePlayerCheckpoint(p->first);
			p->second.activeCheckpoint = 0;
			p->second.visibleCheckpoint = 0;
		}
		p->second.disabledCheckpoints.erase(c->first);
		p->second.visibleCell->checkpoints.erase(c->first);
	}
	core->getGrid()->removeCheckpoint(c->second);
	return core->getData()->checkpoints.erase(c);
}

boost::unordered_map<int, Element::SharedMapIcon>::iterator Utility::destroyMapIcon(boost::unordered_map<int, Element::SharedMapIcon>::iterator m)
{
	Element::MapIcon::identifier.remove(m->first, core->getData()->mapIcons.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
		if (i != p->second.internalMapIcons.end())
		{
			RemovePlayerMapIcon(p->first, i->second);
			p->second.mapIconIdentifier.remove(i->second, p->second.internalMapIcons.size());
			p->second.internalMapIcons.quick_erase(i);
		}
		p->second.visibleCell->mapIcons.erase(m->first);
	}
	core->getGrid()->removeMapIcon(m->second);
	return core->getData()->mapIcons.erase(m);
}

boost::unordered_map<int, Element::SharedObject>::iterator Utility::destroyObject(boost::unordered_map<int, Element::SharedObject>::iterator o)
{
	Element::Object::identifier.remove(o->first, core->getData()->objects.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
		if (i != p->second.internalObjects.end())
		{
			DestroyPlayerObject(p->first, i->second);
			p->second.internalObjects.quick_erase(i);
		}
		p->second.visibleCell->objects.erase(o->first);
	}
	core->getGrid()->removeObject(o->second);
	return core->getData()->objects.erase(o);
}

boost::unordered_map<int, Element::SharedPickup>::iterator Utility::destroyPickup(boost::unordered_map<int, Element::SharedPickup>::iterator p)
{
	Element::Pickup::identifier.remove(p->first, core->getData()->pickups.size());
	boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.find(p->first);
	if (i != core->getStreamer()->internalPickups.end())
	{
		DestroyPickup(i->second);
		core->getStreamer()->internalPickups.quick_erase(i);
	}
	core->getGrid()->removePickup(p->second);
	return core->getData()->pickups.erase(p);
}

boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator Utility::destroyRaceCheckpoint(boost::unordered_map<int, Element::SharedRaceCheckpoint>::iterator r)
{
	Element::RaceCheckpoint::identifier.remove(r->first, core->getData()->raceCheckpoints.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		if (p->second.visibleRaceCheckpoint == r->first)
		{
			DisablePlayerRaceCheckpoint(p->first);
			p->second.activeRaceCheckpoint = 0;
			p->second.visibleRaceCheckpoint = 0;
		}
		p->second.disabledRaceCheckpoints.erase(r->first);
		p->second.visibleCell->raceCheckpoints.erase(r->first);
	}
	core->getGrid()->removeRaceCheckpoint(r->second);
	return core->getData()->raceCheckpoints.erase(r);
}

boost::unordered_map<int, Element::SharedTextLabel>::iterator Utility::destroyTextLabel(boost::unordered_map<int, Element::SharedTextLabel>::iterator t)
{
	Element::TextLabel::identifier.remove(t->first, core->getData()->textLabels.size());
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
		if (i != p->second.internalTextLabels.end())
		{
			DeletePlayer3DTextLabel(p->first, i->second);
			p->second.internalTextLabels.quick_erase(i);
		}
		p->second.visibleCell->textLabels.erase(t->first);
	}
	core->getGrid()->removeTextLabel(t->second);
	return core->getData()->textLabels.erase(t);
}

void Utility::convertArrayToPolygon(AMX *amx, cell input, cell size, Element::Polygon2D &polygon)
{
	cell *array = NULL;
	std::vector<Eigen::Vector2f> points;
	amx_GetAddr(amx, input, &array);
	for (std::size_t i = 0; i < static_cast<std::size_t>(size); i += 2)
	{
		points.push_back(Eigen::Vector2f(amx_ctof(array[i]), amx_ctof(array[i + 1])));
	}
	boost::geometry::assign_points(polygon.get<0>(), points);
	boost::geometry::correct(polygon.get<0>());
}

std::string Utility::getStringFromNative(AMX *amx, cell input)
{
	char *string = NULL;
	amx_StrParam(amx, input, string);
	return string ? string : "";
}
