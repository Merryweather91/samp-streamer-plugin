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

class Streamer
{
public:
	void processAreas(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells);
	void processCheckpoints(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells);
	void processMapIcons(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells);
	void processObjects(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells);
	void processPickups(const std::set<Grid::SharedCell, Grid::Cell> & totalCells);
	void processRaceCheckpoints(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells);
	void processTextLabels(Data::Player & player, const std::vector<Grid::SharedCell> & playerCells);
	void updateMovingAreas();
	void updateMovingObjects();
	void updateMovingTextLabels();
private:
	inline bool checkPlayer(const std::bitset<MAX_INTERIORS> & a, int b, const std::bitset<MAX_PLAYERS> & c, int d, int e, int f)
	{
		return (a[b] && c[d] && (e == -1 || e == f));
	}

	inline bool checkPlayer(const std::bitset<MAX_INTERIORS> & a, int b, const std::bitset<MAX_PLAYERS> & c, int d, const std::set<int> & e, int f)
	{
		return (a[b] && c[d] && (e.empty() || e.find(f) != e.end()));
	}
};

extern Streamer * streamer;
