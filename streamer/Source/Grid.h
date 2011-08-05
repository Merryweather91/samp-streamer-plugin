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

class Grid
{
public:
	Grid();

	class Cell
	{
		friend class Grid;

	public:
		Cell();
		Cell(int assignedID, float requestedX, float requestedY);

		bool operator()(const boost::intrusive_ptr<Cell> & cellA, const boost::intrusive_ptr<Cell> & cellB) const
		{
			return cellA->id < cellB->id;
		}

		int id;
		int references;

		boost::unordered_map<int, Core::SharedArea> areas;
		boost::unordered_map<int, Core::SharedCheckpoint> checkpoints;
		boost::unordered_map<int, Core::SharedMapIcon> mapIcons;
		boost::unordered_map<int, Core::SharedObject> objects;
		boost::unordered_map<int, Core::SharedPickup> pickups;
		boost::unordered_map<int, Core::SharedRaceCheckpoint> raceCheckpoints;
		boost::unordered_map<int, Core::SharedTextLabel> textLabels;
	private:
		float centerX;
		float centerY;
		float x1;
		float x2;
		float y1;
		float y2;
	};

	typedef boost::intrusive_ptr<Cell> SharedCell;

	boost::unordered_map<int, SharedCell> cells;

	std::pair<std::set<int>, int> deletedCells;

	SharedCell globalCell;

	void addArea(const Core::SharedArea & area);
	void addCheckpoint(const Core::SharedCheckpoint & checkpoint);
	void addMapIcon(const Core::SharedMapIcon & mapIcon);
	void addObject(const Core::SharedObject & object);
	void addPickup(const Core::SharedPickup & pickup);
	void addRaceCheckpoint(const Core::SharedRaceCheckpoint & raceCheckpoint);
	void addTextLabel(const Core::SharedTextLabel & textLabel);
	void eraseAllItems(int type);
	void findNearbyCells(Data::Player & player, std::vector<SharedCell> & playerCells, std::set<SharedCell, Cell> & totalCells);
	void mergeRemainingCells(std::set<SharedCell, Cell> & totalCells);
	void rebuildGrid();
	void removeArea(const Core::SharedArea & area, bool reassign = false);
	void removeCheckpoint(const Core::SharedCheckpoint & checkpoint, bool reassign = false);
	void removeMapIcon(const Core::SharedMapIcon & mapIcon, bool reassign = false);
	void removeObject(const Core::SharedObject & object, bool reassign = false);
	void removePickup(const Core::SharedPickup & pickup, bool reassign = false);
	void removeRaceCheckpoint(const Core::SharedRaceCheckpoint & raceCheckpoint, bool reassign = false);
	void removeTextLabel(const Core::SharedTextLabel & textLabel, bool reassign = false);
private:
	void eraseCellIfEmpty(const SharedCell & cell);
	int obtainCellID();
};

namespace boost
{
	inline void intrusive_ptr_add_ref(Grid::Cell * cell)
	{
		++cell->references;
	}

	inline void intrusive_ptr_release(Grid::Cell * cell)
	{
		if (!(--cell->references))
		{
			delete cell;
		}
	}
};

extern Grid * grid;
