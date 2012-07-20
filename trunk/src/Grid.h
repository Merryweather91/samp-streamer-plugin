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

class Grid
{
public:
	Grid();

	void addArea(const Element::SharedArea &area);
	void addCheckpoint(const Element::SharedCheckpoint &checkpoint);
	void addMapIcon(const Element::SharedMapIcon &mapIcon);
	void addObject(const Element::SharedObject &object);
	void addPickup(const Element::SharedPickup &pickup);
	void addRaceCheckpoint(const Element::SharedRaceCheckpoint &raceCheckpoint);
	void addTextLabel(const Element::SharedTextLabel &textLabel);

	void rebuildGrid();
	void removeAllItems(int type);

	void removeArea(const Element::SharedArea &area, bool reassign = false);
	void removeCheckpoint(const Element::SharedCheckpoint &checkpoint, bool reassign = false);
	void removeMapIcon(const Element::SharedMapIcon &mapIcon, bool reassign = false);
	void removeObject(const Element::SharedObject &object, bool reassign = false);
	void removePickup(const Element::SharedPickup &pickup, bool reassign = false);
	void removeRaceCheckpoint(const Element::SharedRaceCheckpoint &raceCheckpoint, bool reassign = false);
	void removeTextLabel(const Element::SharedTextLabel &textLabel, bool reassign = false);

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
