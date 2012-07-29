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

#include "item.h"

#include "identifier.h"

Identifier Item::Area::identifier;
Identifier Item::Checkpoint::identifier;
Identifier Item::MapIcon::identifier;
Identifier Item::Object::identifier;
Identifier Item::Pickup::identifier;
Identifier Item::RaceCheckpoint::identifier;
Identifier Item::TextLabel::identifier;

Item::Area::Area() : references(0) {}
Item::Area::Attach::Attach() : references(0) {}
Item::Checkpoint::Checkpoint() : references(0) {}
Item::MapIcon::MapIcon() : references(0) {}
Item::Object::Object() : references(0) {}
Item::Object::Attach::Attach() : references(0) {}
Item::Object::Material::Main::Main() : references(0) {}
Item::Object::Material::Text::Text() : references(0) {}
Item::Object::Move::Move() : references(0) {}
Item::Pickup::Pickup() : references(0) {}
Item::RaceCheckpoint::RaceCheckpoint() : references(0) {}
Item::TextLabel::TextLabel() : references(0) {}
Item::TextLabel::Attach::Attach() : references(0) {}
