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

#include "Main.h"

using namespace Element;

Identifier Area::identifier;
Identifier Checkpoint::identifier;
Identifier MapIcon::identifier;
Identifier Object::identifier;
Identifier Pickup::identifier;
Identifier RaceCheckpoint::identifier;
Identifier TextLabel::identifier;

Area::Area()
{
	references = 0;
}

Area::Attach::Attach()
{
	references = 0;
}

Checkpoint::Checkpoint()
{
	references = 0;
}

MapIcon::MapIcon()
{
	references = 0;
}

Object::Object()
{
	references = 0;
}

Object::Move::Move()
{
	references = 0;
}

Pickup::Pickup()
{
	references = 0;
}

RaceCheckpoint::RaceCheckpoint()
{
	references = 0;
}

TextLabel::TextLabel()
{
	references = 0;
}

TextLabel::Attach::Attach()
{
	references = 0;
}
