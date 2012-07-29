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

#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include "common.h"

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <vector>

class Grid
{
public:
	Grid();

	void addArea(const Item::SharedArea &area);
	void addCheckpoint(const Item::SharedCheckpoint &checkpoint);
	void addMapIcon(const Item::SharedMapIcon &mapIcon);
	void addObject(const Item::SharedObject &object);
	void addPickup(const Item::SharedPickup &pickup);
	void addRaceCheckpoint(const Item::SharedRaceCheckpoint &raceCheckpoint);
	void addTextLabel(const Item::SharedTextLabel &textLabel);

	void rebuildGrid();
	void removeAllItems(int type);

	void removeArea(const Item::SharedArea &area, bool reassign = false);
	void removeCheckpoint(const Item::SharedCheckpoint &checkpoint, bool reassign = false);
	void removeMapIcon(const Item::SharedMapIcon &mapIcon, bool reassign = false);
	void removeObject(const Item::SharedObject &object, bool reassign = false);
	void removePickup(const Item::SharedPickup &pickup, bool reassign = false);
	void removeRaceCheckpoint(const Item::SharedRaceCheckpoint &raceCheckpoint, bool reassign = false);
	void removeTextLabel(const Item::SharedTextLabel &textLabel, bool reassign = false);

	void findAllCells(Player &player, std::vector<SharedCell> &playerCells);
	void findMinimalCells(Player &player, std::vector<SharedCell> &playerCells);

	float cellDistance;
	float cellSize;
private:
	SharedCell globalCell;
	Eigen::Matrix<float, 2, 9> translationMatrix;

	boost::unordered_map<CellID, SharedCell> cells;

	inline void calculateTranslationMatrix()
	{
		translationMatrix << 0.0f, 0.0f, cellSize, cellSize, cellSize * -1.0f, 0.0f, cellSize * -1.0f, cellSize, cellSize * -1.0f,
		                     0.0f, cellSize, 0.0f, cellSize, 0.0f, cellSize * -1.0f, cellSize, cellSize * -1.0f, cellSize * -1.0f;
	}

	inline void eraseCellIfEmpty(const SharedCell &cell)
	{
		if (cell->areas.empty() && cell->checkpoints.empty() && cell->mapIcons.empty() && cell->objects.empty() && cell->pickups.empty() && cell->raceCheckpoints.empty() && cell->textLabels.empty())
		{
			cells.erase(cell->cellID);
		}
	}

	CellID getCellID(const Eigen::Vector2f &position, bool insert = true);
	void processDiscoveredCells(Player &player, std::vector<SharedCell> &playerCells, const boost::unordered_set<CellID> &discoveredCells);
};

#endif
