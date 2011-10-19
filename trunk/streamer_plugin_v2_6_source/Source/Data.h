/*
    SA-MP Streamer Plugin v2.6
    Copyright © 2011 Incognito

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

class Data
{
public:
	std::set<AMX*> interfaces;

	boost::unordered_map<int, Player> players;

	boost::unordered_map<int, Element::SharedArea> areas;
	boost::unordered_map<int, Element::SharedCheckpoint> checkpoints;
	boost::unordered_map<int, Element::SharedMapIcon> mapIcons;
	boost::unordered_map<int, Element::SharedObject> objects;
	boost::unordered_map<int, Element::SharedPickup> pickups;
	boost::unordered_map<int, Element::SharedRaceCheckpoint> raceCheckpoints;
	boost::unordered_map<int, Element::SharedTextLabel> textLabels;
};
