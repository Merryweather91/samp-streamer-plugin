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

#ifndef CORE_H
#define CORE_H

#include "data.h"
#include "events.h"
#include "grid.h"
#include "streamer.h"

#include <boost/scoped_ptr.hpp>

class Core
{
public:
	Core();

	inline Data *getData()
	{
		return data.get();
	}

	inline Events *getEvents()
	{
		return events.get();
	}

	inline Grid *getGrid()
	{
		return grid.get();
	}

	inline Streamer *getStreamer()
	{
		return streamer.get();
	}
private:
	boost::scoped_ptr<Data> data;
	boost::scoped_ptr<Events> events;
	boost::scoped_ptr<Grid> grid;
	boost::scoped_ptr<Streamer> streamer;
};

extern boost::scoped_ptr<Core> core;

#endif
