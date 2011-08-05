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

#ifndef _WIN32
	#include <sys/time.h>
#endif

namespace Data
{
	enum
	{
		AttachedPlayer,
		AttachedVehicle,
		Color,
		Distance,
		DrawDistance,
		ExtraID,
		InteriorID,
		MaxX,
		MaxY,
		MaxZ,
		MinX,
		MinY,
		MinZ,
		ModelID,
		MoveSpeed,
		MoveX,
		MoveY,
		MoveZ,
		NextX,
		NextY,
		NextZ,
		PlayerID,
		RX,
		RY,
		RZ,
		Size,
		Style,
		TestLOS,
		Type,
		WorldID,
		X,
		Y,
		Z
	};

	struct Global
	{
		Global();

		float cellDistance;
		float cellSize;
		std::size_t maxAreas;
		std::size_t maxCheckpoints;
		std::size_t maxMapIcons;
		std::size_t maxObjects;
		std::size_t maxPickups;
		std::size_t maxRaceCheckpoints;
		std::size_t maxTextLabels;
		int tickCount;
		int tickRate;
		std::size_t visibleMapIcons;
		std::size_t visibleObjects;
		std::size_t visiblePickups;
		std::size_t visibleTextLabels;

		boost::unordered_map<int, int> internalPickups;

		boost::unordered_set<int> visibleCells;

		std::pair<std::set<int>, int> deletedAreas;
		std::pair<std::set<int>, int> deletedCheckpoints;
		std::pair<std::set<int>, int> deletedMapIcons;
		std::pair<std::set<int>, int> deletedObjects;
		std::pair<std::set<int>, int> deletedRaceCheckpoints;
		std::pair<std::set<int>, int> deletedPickups;
		std::pair<std::set<int>, int> deletedTextLabels;
	};

	struct Player
	{
		int activeCheckpoint;
		int activeRaceCheckpoint;
		int interiorID;
		int playerID;
		int visibleCheckpoint;
		int visibleRaceCheckpoint;
		std::size_t visibleObjects;
		int worldID;
		float x;
		float y;
		float z;

		boost::unordered_set<int> disabledAreas;
		boost::unordered_set<int> disabledCheckpoints;
		boost::unordered_set<int> disabledRaceCheckpoints;

		boost::unordered_map<int, int> internalMapIcons;
		boost::unordered_map<int, int> internalObjects;
		boost::unordered_map<int, int> internalTextLabels;

		boost::unordered_set<int> visibleAreas;
		boost::unordered_set<int> visibleCells;

		std::set<int> sortedInternalMapIcons;
	};
};

namespace Element
{
	struct Area
	{
		Area()
		{
			references = 0;
		}

		AMX * amx;
		int areaID;
		int cellID;
		int extraID;
		int references;
		float size;
		int type;
		float x1;
		float x2;
		float y1;
		float y2;
		float z1;
		float z2;

		struct Attach
		{
			Attach()
			{
				references = 0;
			}

			int player;
			int references;
			int vehicle;
			float x;
			float y;
			float z;
		};

		boost::intrusive_ptr<Attach> attach;

		std::bitset<MAX_INTERIORS> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::set<int> worlds;
	};

	struct Checkpoint
	{
		Checkpoint()
		{
			references = 0;
		}

		AMX * amx;
		int cellID;
		int checkpointID;
		float distance;
		int extraID;
		int references;
		float size;
		float x;
		float y;
		float z;

		std::bitset<MAX_INTERIORS> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::set<int> worlds;
	};

	struct MapIcon
	{
		MapIcon()
		{
			references = 0;
		}

		AMX * amx;
		int cellID;
		int color;
		float distance;
		int extraID;
		int mapIconID;
		int references;
		int style;
		int type;
		float x;
		float y;
		float z;

		std::bitset<MAX_INTERIORS> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::set<int> worlds;
	};

	struct Object
	{
		Object()
		{
			references = 0;
		}

		AMX * amx;
		int cellID;
		float distance;
		float drawDistance;
		int extraID;
		int modelID;
		int objectID;
		int references;
		float rX;
		float rY;
		float rZ;
		float x;
		float y;
		float z;

		struct Move
		{
			Move()
			{
				references = 0;
			}

			int duration;
			float offsetX;
			float offsetY;
			float offsetZ;
			int references;
			float speed;
			int startTime;
			float startX;
			float startY;
			float startZ;
			float x;
			float y;
			float z;
		};

		boost::intrusive_ptr<Move> move;

		std::bitset<MAX_INTERIORS> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::set<int> worlds;
	};

	struct Pickup
	{
		Pickup()
		{
			references = 0;
		}

		AMX * amx;
		int cellID;
		float distance;
		int extraID;
		int modelID;
		int pickupID;
		int references;
		int type;
		int worldID;
		float x;
		float y;
		float z;

		std::bitset<MAX_INTERIORS> interiors;
		std::bitset<MAX_PLAYERS> players;
	};

	struct RaceCheckpoint
	{
		RaceCheckpoint()
		{
			references = 0;
		}

		AMX * amx;
		int cellID;
		int checkpointID;
		float distance;
		int extraID;
		float nextX;
		float nextY;
		float nextZ;
		int references;
		float size;
		int type;
		float x;
		float y;
		float z;

		std::bitset<MAX_INTERIORS> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::set<int> worlds;
	};

	struct TextLabel
	{
		TextLabel()
		{
			references = 0;
		}

		AMX * amx;
		int cellID;
		int color;
		float distance;
		float drawDistance;
		int extraID;
		int references;
		int testLOS;
		std::string text;
		int textLabelID;
		float x;
		float y;
		float z;

		struct Attach
		{
			Attach()
			{
				references = 0;
			}

			int player;
			int references;
			int vehicle;
			float x;
			float y;
			float z;
		};

		boost::intrusive_ptr<Attach> attach;

		std::bitset<MAX_INTERIORS> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::set<int> worlds;
	};
};

class Core
{
public:
	inline bool checkArea2D(float x, float y, float x1, float y1, float x2, float y2)
	{
		return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
	}

	inline bool checkArea3D(float x, float y, float z, float x1, float y1, float z1, float x2, float y2, float z2)
	{
		return (x >= x1 && x <= x2 && y >= y1 && y <= y2 && z >= z1 && z <= z2);
	}

	inline float findDistance2D(float x1, float y1, float x2, float y2)
	{
		return (((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
	}

	inline float findDistance3D(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		return (((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) + ((z1 - z2) * (z1 - z2)));
	}

	inline float findMidpoint(float x, float y)
	{
		return (x + y) / 2.0f;
	}

	int obtainCurrentTime();

	Data::Global global;

	std::vector<Data::Player> players;

	typedef boost::intrusive_ptr<Element::Area> SharedArea;
	typedef boost::intrusive_ptr<Element::Checkpoint> SharedCheckpoint;
	typedef boost::intrusive_ptr<Element::MapIcon> SharedMapIcon;
	typedef boost::intrusive_ptr<Element::Object> SharedObject;
	typedef boost::intrusive_ptr<Element::Pickup> SharedPickup;
	typedef boost::intrusive_ptr<Element::RaceCheckpoint> SharedRaceCheckpoint;
	typedef boost::intrusive_ptr<Element::TextLabel> SharedTextLabel;

	boost::unordered_map<int, SharedArea> areas;
	boost::unordered_map<int, SharedCheckpoint> checkpoints;
	boost::unordered_map<int, SharedMapIcon> mapIcons;
	boost::unordered_map<int, SharedObject> objects;
	boost::unordered_map<int, SharedPickup> pickups;
	boost::unordered_map<int, SharedRaceCheckpoint> raceCheckpoints;
	boost::unordered_map<int, SharedTextLabel> textLabels;

	boost::unordered_set<SharedArea> movingAreas;
	boost::unordered_set<SharedObject> movingObjects;
	boost::unordered_set<SharedTextLabel> movingTextLabels;
};

namespace boost
{
	inline void intrusive_ptr_add_ref(Element::Area * area)
	{
		++area->references;
	}

	inline void intrusive_ptr_release(Element::Area * area)
	{
		if (!(--area->references))
		{
			delete area;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Area::Attach * attach)
	{
		++attach->references;
	}

	inline void intrusive_ptr_release(Element::Area::Attach * attach)
	{
		if (!(--attach->references))
		{
			delete attach;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Checkpoint * checkpoint)
	{
		++checkpoint->references;
	}

	inline void intrusive_ptr_release(Element::Checkpoint * checkpoint)
	{
		if (!(--checkpoint->references))
		{
			delete checkpoint;
		}
	}

	inline void intrusive_ptr_add_ref(Element::MapIcon * mapIcon)
	{
		++mapIcon->references;
	}

	inline void intrusive_ptr_release(Element::MapIcon * mapIcon)
	{
		if (!(--mapIcon->references))
		{
			delete mapIcon;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Object * object)
	{
		++object->references;
	}

	inline void intrusive_ptr_release(Element::Object * object)
	{
		if (!(--object->references))
		{
			delete object;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Object::Move * move)
	{
		++move->references;
	}

	inline void intrusive_ptr_release(Element::Object::Move * move)
	{
		if (!(--move->references))
		{
			delete move;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Pickup * pickup)
	{
		++pickup->references;
	}

	inline void intrusive_ptr_release(Element::Pickup * pickup)
	{
		if (!(--pickup->references))
		{
			delete pickup;
		}
	}

	inline void intrusive_ptr_add_ref(Element::RaceCheckpoint * raceCheckpoint)
	{
		++raceCheckpoint->references;
	}

	inline void intrusive_ptr_release(Element::RaceCheckpoint * raceCheckpoint)
	{
		if (!(--raceCheckpoint->references))
		{
			delete raceCheckpoint;
		}
	}

	inline void intrusive_ptr_add_ref(Element::TextLabel * textLabel)
	{
		++textLabel->references;
	}

	inline void intrusive_ptr_release(Element::TextLabel * textLabel)
	{
		if (!(--textLabel->references))
		{
			delete textLabel;
		}
	}

	inline void intrusive_ptr_add_ref(Element::TextLabel::Attach * attach)
	{
		++attach->references;
	}

	inline void intrusive_ptr_release(Element::TextLabel::Attach * attach)
	{
		if (!(--attach->references))
		{
			delete attach;
		}
	}
};

extern Core * core;
