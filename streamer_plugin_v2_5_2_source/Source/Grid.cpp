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

Grid * grid;

Grid::Grid()
{
	globalCell = SharedCell(new Cell());
}

Grid::Cell::Cell()
{
	references = 0;
}

Grid::Cell::Cell(int assignedID, float requestedX, float requestedY)
{
	id = assignedID;
	x1 = floor((requestedX / core->global.cellSize)) * core->global.cellSize;
	x2 = x1 + core->global.cellSize;
	centerX = core->findMidpoint(x1, x2);
	y1 = floor((requestedY / core->global.cellSize)) * core->global.cellSize;
	y2 = y1 + core->global.cellSize;
	centerY = core->findMidpoint(y1, y2);
	references = 0;
}

void Grid::addArea(const Core::SharedArea & area)
{
	float areaDistance = 0.0f, areaX = 0.0f, areaY = 0.0f;
	switch (area->type)
	{
		case 0:
		case 2:
		{
			areaDistance = area->size;
			if (area->attach)
			{
				areaX = area->attach->x;
				areaY = area->attach->y;
			}
			else
			{
				areaX = area->x1;
				areaY = area->y1;
			}
		}
		break;
		case 1:
		case 3:
		{
			areaDistance = core->findDistance2D(area->x1, area->y1, area->x2, area->y2);
			areaX = core->findMidpoint(area->x1, area->x2);
			areaY = core->findMidpoint(area->y1, area->y2);
		}
		break;
	}
	if (areaDistance > core->global.cellDistance)
	{
		globalCell->areas.insert(std::make_pair(area->areaID, area));
		area->cellID = 0;
		return;
	}
	for (boost::unordered_map<int, SharedCell>::iterator s = cells.begin(); s != cells.end(); ++s)
	{
		if (core->checkArea2D(areaX, areaY, s->second->x1, s->second->y1, s->second->x2, s->second->y2))
		{
			s->second->areas.insert(std::make_pair(area->areaID, area));
			area->cellID = s->first;
			return;
		}
	}
	int cellID = obtainCellID();
	cells.insert(std::make_pair(cellID, SharedCell(new Cell(cellID, areaX, areaY))));
	cells[cellID]->areas.insert(std::make_pair(area->areaID, area));
	area->cellID = cellID;
}

void Grid::addCheckpoint(const Core::SharedCheckpoint & checkpoint)
{
	if (checkpoint->distance > core->global.cellDistance)
	{
		globalCell->checkpoints.insert(std::make_pair(checkpoint->checkpointID, checkpoint));
		checkpoint->cellID = 0;
		return;
	}
	for (boost::unordered_map<int, SharedCell>::iterator s = cells.begin(); s != cells.end(); ++s)
	{
		if (core->checkArea2D(checkpoint->x, checkpoint->y, s->second->x1, s->second->y1, s->second->x2, s->second->y2))
		{
			s->second->checkpoints.insert(std::make_pair(checkpoint->checkpointID, checkpoint));
			checkpoint->cellID = s->first;
			return;
		}
	}
	int cellID = obtainCellID();
	cells.insert(std::make_pair(cellID, SharedCell(new Cell(cellID, checkpoint->x, checkpoint->y))));
	cells[cellID]->checkpoints.insert(std::make_pair(checkpoint->checkpointID, checkpoint));
	checkpoint->cellID = cellID;
}

void Grid::addMapIcon(const Core::SharedMapIcon & mapIcon)
{
	if (mapIcon->distance > core->global.cellDistance)
	{
		globalCell->mapIcons.insert(std::make_pair(mapIcon->mapIconID, mapIcon));
		mapIcon->cellID = 0;
		return;
	}
	for (boost::unordered_map<int, SharedCell>::iterator s = cells.begin(); s != cells.end(); ++s)
	{
		if (core->checkArea2D(mapIcon->x, mapIcon->y, s->second->x1, s->second->y1, s->second->x2, s->second->y2))
		{
			s->second->mapIcons.insert(std::make_pair(mapIcon->mapIconID, mapIcon));
			mapIcon->cellID = s->first;
			return;
		}
	}
	int cellID = obtainCellID();
	cells.insert(std::make_pair(cellID, SharedCell(new Cell(cellID, mapIcon->x, mapIcon->y))));
	cells[cellID]->mapIcons.insert(std::make_pair(mapIcon->mapIconID, mapIcon));
	mapIcon->cellID = cellID;
}

void Grid::addObject(const Core::SharedObject & object)
{
	if (object->distance > core->global.cellDistance)
	{
		globalCell->objects.insert(std::make_pair(object->objectID, object));
		object->cellID = 0;
		return;
	}
	for (boost::unordered_map<int, SharedCell>::iterator s = cells.begin(); s != cells.end(); ++s)
	{
		if (core->checkArea2D(object->x, object->y, s->second->x1, s->second->y1, s->second->x2, s->second->y2))
		{
			s->second->objects.insert(std::make_pair(object->objectID, object));
			object->cellID = s->first;
			return;
		}
	}
	int cellID = obtainCellID();
	cells.insert(std::make_pair(cellID, SharedCell(new Cell(cellID, object->x, object->y))));
	cells[cellID]->objects.insert(std::make_pair(object->objectID, object));
	object->cellID = cellID;
}

void Grid::addPickup(const Core::SharedPickup & pickup)
{
	if (pickup->distance > core->global.cellDistance)
	{
		globalCell->pickups.insert(std::make_pair(pickup->pickupID, pickup));
		pickup->cellID = 0;
		return;
	}
	for (boost::unordered_map<int, SharedCell>::iterator s = cells.begin(); s != cells.end(); ++s)
	{
		if (core->checkArea2D(pickup->x, pickup->y, s->second->x1, s->second->y1, s->second->x2, s->second->y2))
		{
			s->second->pickups.insert(std::make_pair(pickup->pickupID, pickup));
			pickup->cellID = s->first;
			return;
		}
	}
	int cellID = obtainCellID();
	cells.insert(std::make_pair(cellID, SharedCell(new Cell(cellID, pickup->x, pickup->y))));
	cells[cellID]->pickups.insert(std::make_pair(pickup->pickupID, pickup));
	pickup->cellID = cellID;
}

void Grid::addRaceCheckpoint(const Core::SharedRaceCheckpoint & raceCheckpoint)
{
	if (raceCheckpoint->distance > core->global.cellDistance)
	{
		globalCell->raceCheckpoints.insert(std::make_pair(raceCheckpoint->checkpointID, raceCheckpoint));
		raceCheckpoint->cellID = 0;
		return;
	}
	for (boost::unordered_map<int, SharedCell>::iterator s = cells.begin(); s != cells.end(); ++s)
	{
		if (core->checkArea2D(raceCheckpoint->x, raceCheckpoint->y, s->second->x1, s->second->y1, s->second->x2, s->second->y2))
		{
			s->second->raceCheckpoints.insert(std::make_pair(raceCheckpoint->checkpointID, raceCheckpoint));
			raceCheckpoint->cellID = s->first;
			return;
		}
	}
	int cellID = obtainCellID();
	cells.insert(std::make_pair(cellID, SharedCell(new Cell(cellID, raceCheckpoint->x, raceCheckpoint->y))));
	cells[cellID]->raceCheckpoints.insert(std::make_pair(raceCheckpoint->checkpointID, raceCheckpoint));
	raceCheckpoint->cellID = cellID;
}

void Grid::addTextLabel(const Core::SharedTextLabel & textLabel)
{
	if (textLabel->distance > core->global.cellDistance)
	{
		globalCell->textLabels.insert(std::make_pair(textLabel->textLabelID, textLabel));
		textLabel->cellID = 0;
		return;
	}
	float textLabelX = 0.0f, textLabelY = 0.0f;
	if (textLabel->attach)
	{
		textLabelX = textLabel->attach->x;
		textLabelY = textLabel->attach->y;
	}
	else
	{
		textLabelX = textLabel->x;
		textLabelY = textLabel->y;
	}
	for (boost::unordered_map<int, SharedCell>::iterator s = cells.begin(); s != cells.end(); ++s)
	{
		if (core->checkArea2D(textLabelX, textLabelY, s->second->x1, s->second->y1, s->second->x2, s->second->y2))
		{
			s->second->textLabels.insert(std::make_pair(textLabel->textLabelID, textLabel));
			textLabel->cellID = s->first;
			return;
		}
	}
	int cellID = obtainCellID();
	cells.insert(std::make_pair(cellID, SharedCell(new Cell(cellID, textLabelX, textLabelY))));
	cells[cellID]->textLabels.insert(std::make_pair(textLabel->textLabelID, textLabel));
	textLabel->cellID = cellID;
}

void Grid::eraseAllItems(int type)
{
	boost::unordered_map<int, SharedCell> temporaryCells(cells);
	switch (type)
	{
		case STREAMER_TYPE_OBJECT:
		{
			globalCell->objects.clear();
			for (boost::unordered_map<int, SharedCell>::iterator s = temporaryCells.begin(); s != temporaryCells.end(); ++s)
			{
				s->second->objects.clear();
				eraseCellIfEmpty(s->second);
			}
		}
		break;
		case STREAMER_TYPE_PICKUP:
		{
			globalCell->pickups.clear();
			for (boost::unordered_map<int, SharedCell>::iterator s = temporaryCells.begin(); s != temporaryCells.end(); ++s)
			{
				s->second->pickups.clear();
				eraseCellIfEmpty(s->second);
			}
		}
		break;
		case STREAMER_TYPE_CP:
		{
			globalCell->checkpoints.clear();
			for (boost::unordered_map<int, SharedCell>::iterator s = temporaryCells.begin(); s != temporaryCells.end(); ++s)
			{
				s->second->checkpoints.clear();
				eraseCellIfEmpty(s->second);
			}
		}
		break;
		case STREAMER_TYPE_RACE_CP:
		{
			globalCell->raceCheckpoints.clear();
			for (boost::unordered_map<int, SharedCell>::iterator s = temporaryCells.begin(); s != temporaryCells.end(); ++s)
			{
				s->second->raceCheckpoints.clear();
				eraseCellIfEmpty(s->second);
			}
		}
		break;
		case STREAMER_TYPE_MAP_ICON:
		{
			globalCell->mapIcons.clear();
			for (boost::unordered_map<int, SharedCell>::iterator s = temporaryCells.begin(); s != temporaryCells.end(); ++s)
			{
				s->second->mapIcons.clear();
				eraseCellIfEmpty(s->second);
			}
		}
		break;
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			globalCell->textLabels.clear();
			for (boost::unordered_map<int, SharedCell>::iterator s = temporaryCells.begin(); s != temporaryCells.end(); ++s)
			{
				s->second->textLabels.clear();
				eraseCellIfEmpty(s->second);
			}
		}
		break;
		case STREAMER_TYPE_AREA:
		{
			globalCell->areas.clear();
			for (boost::unordered_map<int, SharedCell>::iterator s = temporaryCells.begin(); s != temporaryCells.end(); ++s)
			{
				s->second->areas.clear();
				eraseCellIfEmpty(s->second);
			}
		}
		break;
	}
}

void Grid::eraseCellIfEmpty(const SharedCell & cell)
{
	if (cell->areas.empty() && cell->checkpoints.empty() && cell->mapIcons.empty() && cell->objects.empty() && cell->pickups.empty() && cell->raceCheckpoints.empty() && cell->textLabels.empty())
	{
		if (cells.size() > 1)
		{
			deletedCells.first.insert(cell->id);
		}
		else
		{
			deletedCells = std::make_pair(std::set<int>(), 0);
		}
		cells.erase(cell->id);
	}
}

void Grid::findNearbyCells(Data::Player & player, std::vector<SharedCell> & playerCells, std::set<SharedCell, Cell> & totalCells)
{
	playerCells.push_back(globalCell);
	for (boost::unordered_map<int, SharedCell>::iterator s = cells.begin(); s != cells.end(); ++s)
	{
		boost::unordered_set<int>::iterator f = player.visibleCells.find(s->first);
		if (f != player.visibleCells.end() || core->findDistance2D(player.x, player.y, s->second->centerX, s->second->centerY) <= core->global.cellDistance)
		{
			playerCells.push_back(s->second);
			if (!core->pickups.empty())
			{
				totalCells.insert(s->second);
			}
		}
	}
	player.visibleCells.clear();
}

void Grid::mergeRemainingCells(std::set<SharedCell, Cell> & totalCells)
{
	totalCells.insert(globalCell);
	for (boost::unordered_map<int, SharedCell>::iterator s = cells.begin(); s != cells.end(); ++s)
	{
		boost::unordered_set<int>::iterator f = core->global.visibleCells.find(s->first);
		if (f != core->global.visibleCells.end())
		{
			totalCells.insert(s->second);
		}
	}
	core->global.visibleCells.clear();
}

int Grid::obtainCellID()
{
	int id = 0;
	if (!grid->deletedCells.first.empty())
	{
		id = * grid->deletedCells.first.begin();
		grid->deletedCells.first.erase(grid->deletedCells.first.begin());
	}
	else
	{
		id = ++grid->deletedCells.second;
	}
	return id;
}

void Grid::rebuildGrid()
{
	cells.clear();
	deletedCells = std::make_pair(std::set<int>(), 0);
	globalCell = Grid::SharedCell(new Grid::Cell());
	for (boost::unordered_map<int, Core::SharedArea>::iterator a = core->areas.begin(); a != core->areas.end(); ++a)
	{
		addArea(a->second);
	}
	for (boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = core->checkpoints.begin(); c != core->checkpoints.end(); ++c)
	{
		addCheckpoint(c->second);
	}
	for (boost::unordered_map<int, Core::SharedMapIcon>::iterator m = core->mapIcons.begin(); m != core->mapIcons.end(); ++m)
	{
		addMapIcon(m->second);
	}
	for (boost::unordered_map<int, Core::SharedObject>::iterator o = core->objects.begin(); o != core->objects.end(); ++o)
	{
		addObject(o->second);
	}
	for (boost::unordered_map<int, Core::SharedPickup>::iterator p = core->pickups.begin(); p != core->pickups.end(); ++p)
	{
		addPickup(p->second);
	}
	for (boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = core->raceCheckpoints.begin(); r != core->raceCheckpoints.end(); ++r)
	{
		addRaceCheckpoint(r->second);
	}
	for (boost::unordered_map<int, Core::SharedTextLabel>::iterator t = core->textLabels.begin(); t != core->textLabels.end(); ++t)
	{
		addTextLabel(t->second);
	}
}

void Grid::removeArea(const Core::SharedArea & area, bool reassign)
{
	bool found = false;
	if (area->cellID)
	{
		boost::unordered_map<int, SharedCell>::iterator s = cells.find(area->cellID);
		if (s != cells.end())
		{
			boost::unordered_map<int, Core::SharedArea>::iterator a = s->second->areas.find(area->areaID);
			if (a != s->second->areas.end())
			{
				s->second->areas.quick_erase(a);
				eraseCellIfEmpty(s->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Core::SharedArea>::iterator a = globalCell->areas.find(area->areaID);
		if (a != globalCell->areas.end())
		{
			globalCell->areas.quick_erase(a);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addArea(area);
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				boost::unordered_set<int>::iterator f = p->visibleAreas.find(area->areaID);
				if (f != p->visibleAreas.end())
				{
					p->visibleCells.insert(area->cellID);
				}
			}
		}
		else
		{
			if (area->attach)
			{
				core->movingAreas.erase(area);
			}
		}
	}
}

void Grid::removeCheckpoint(const Core::SharedCheckpoint & checkpoint, bool reassign)
{
	bool found = false;
	if (checkpoint->cellID)
	{
		boost::unordered_map<int, SharedCell>::iterator s = cells.find(checkpoint->cellID);
		if (s != cells.end())
		{
			boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = s->second->checkpoints.find(checkpoint->checkpointID);
			if (c != s->second->checkpoints.end())
			{
				s->second->checkpoints.quick_erase(c);
				eraseCellIfEmpty(s->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Core::SharedCheckpoint>::iterator c = globalCell->checkpoints.find(checkpoint->checkpointID);
		if (c != globalCell->checkpoints.end())
		{
			globalCell->checkpoints.quick_erase(c);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addCheckpoint(checkpoint);
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				if (p->visibleCheckpoint == checkpoint->checkpointID)
				{
					p->visibleCells.insert(checkpoint->cellID);
				}
			}
		}
	}
}

void Grid::removeMapIcon(const Core::SharedMapIcon & mapIcon, bool reassign)
{
	bool found = false;
	if (mapIcon->cellID)
	{
		boost::unordered_map<int, SharedCell>::iterator s = cells.find(mapIcon->cellID);
		if (s != cells.end())
		{
			boost::unordered_map<int, Core::SharedMapIcon>::iterator m = s->second->mapIcons.find(mapIcon->mapIconID);
			if (m != s->second->mapIcons.end())
			{
				s->second->mapIcons.quick_erase(m);
				eraseCellIfEmpty(s->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Core::SharedMapIcon>::iterator m = globalCell->mapIcons.find(mapIcon->mapIconID);
		if (m != globalCell->mapIcons.end())
		{
			globalCell->mapIcons.quick_erase(m);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addMapIcon(mapIcon);
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				boost::unordered_map<int, int>::iterator f = p->internalMapIcons.find(mapIcon->mapIconID);
				if (f != p->internalMapIcons.end())
				{
					p->visibleCells.insert(mapIcon->cellID);
				}
			}
		}
	}
}

void Grid::removeObject(const Core::SharedObject & object, bool reassign)
{
	bool found = false;
	if (object->cellID)
	{
		boost::unordered_map<int, SharedCell>::iterator s = cells.find(object->cellID);
		if (s != cells.end())
		{
			boost::unordered_map<int, Core::SharedObject>::iterator o = s->second->objects.find(object->objectID);
			if (o != s->second->objects.end())
			{
				s->second->objects.quick_erase(o);
				eraseCellIfEmpty(s->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Core::SharedObject>::iterator o = globalCell->objects.find(object->objectID);
		if (o != globalCell->objects.end())
		{
			globalCell->objects.quick_erase(o);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addObject(object);
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				boost::unordered_map<int, int>::iterator f = p->internalObjects.find(object->objectID);
				if (f != p->internalObjects.end())
				{
					p->visibleCells.insert(object->cellID);
				}
			}
		}
		else
		{
			if (object->move)
			{
				core->movingObjects.erase(object);
			}
		}
	}
}

void Grid::removePickup(const Core::SharedPickup & pickup, bool reassign)
{
	bool found = false;
	if (pickup->cellID)
	{
		boost::unordered_map<int, SharedCell>::iterator s = cells.find(pickup->cellID);
		if (s != cells.end())
		{
			boost::unordered_map<int, Core::SharedPickup>::iterator p = s->second->pickups.find(pickup->pickupID);
			if (p != s->second->pickups.end())
			{
				s->second->pickups.quick_erase(p);
				eraseCellIfEmpty(s->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Core::SharedPickup>::iterator p = globalCell->pickups.find(pickup->pickupID);
		if (p != globalCell->pickups.end())
		{
			globalCell->pickups.quick_erase(p);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addPickup(pickup);
			boost::unordered_map<int, int>::iterator f = core->global.internalPickups.find(pickup->pickupID);
			if (f != core->global.internalPickups.end())
			{
				core->global.visibleCells.insert(pickup->cellID);
			}
		}
	}
}

void Grid::removeRaceCheckpoint(const Core::SharedRaceCheckpoint & raceCheckpoint, bool reassign)
{
	bool found = false;
	if (raceCheckpoint->cellID)
	{
		boost::unordered_map<int, SharedCell>::iterator s = cells.find(raceCheckpoint->cellID);
		if (s != cells.end())
		{
			boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = s->second->raceCheckpoints.find(raceCheckpoint->checkpointID);
			if (r != s->second->raceCheckpoints.end())
			{
				s->second->raceCheckpoints.quick_erase(r);
				eraseCellIfEmpty(s->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Core::SharedRaceCheckpoint>::iterator r = globalCell->raceCheckpoints.find(raceCheckpoint->checkpointID);
		if (r != globalCell->raceCheckpoints.end())
		{
			globalCell->raceCheckpoints.quick_erase(r);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addRaceCheckpoint(raceCheckpoint);
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				if (p->visibleRaceCheckpoint == raceCheckpoint->checkpointID)
				{
					p->visibleCells.insert(raceCheckpoint->cellID);
				}
			}
		}
	}
}

void Grid::removeTextLabel(const Core::SharedTextLabel & textLabel, bool reassign)
{
	bool found = false;
	if (textLabel->cellID)
	{
		boost::unordered_map<int, SharedCell>::iterator s = cells.find(textLabel->cellID);
		if (s != cells.end())
		{
			boost::unordered_map<int, Core::SharedTextLabel>::iterator t = s->second->textLabels.find(textLabel->textLabelID);
			if (t != s->second->textLabels.end())
			{
				s->second->textLabels.quick_erase(t);
				eraseCellIfEmpty(s->second);
				found = true;
			}
		}
	}
	else
	{
		boost::unordered_map<int, Core::SharedTextLabel>::iterator t = globalCell->textLabels.find(textLabel->textLabelID);
		if (t != globalCell->textLabels.end())
		{
			globalCell->textLabels.quick_erase(t);
			found = true;
		}
	}
	if (found)
	{
		if (reassign)
		{
			addTextLabel(textLabel);
			for (std::vector<Data::Player>::iterator p = core->players.begin(); p != core->players.end(); ++p)
			{
				boost::unordered_map<int, int>::iterator f = p->internalTextLabels.find(textLabel->textLabelID);
				if (f != p->internalTextLabels.end())
				{
					p->visibleCells.insert(textLabel->cellID);
				}
			}
		}
		else
		{
			if (textLabel->attach)
			{
				core->movingTextLabels.erase(textLabel);
			}
		}
	}
}
