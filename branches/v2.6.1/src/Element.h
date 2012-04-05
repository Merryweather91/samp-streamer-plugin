/*
    SA-MP Streamer Plugin v2.6.1
    Copyright � 2012 Incognito

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

#ifndef ELEMENT_H
#define ELEMENT_H

namespace Element
{
	struct Area
	{
		Area();

		AMX *amx;
		int areaID;
		SharedCell cell;
		int extraID;
		int references;
		float size;
		int type;

		boost::variant<Polygon2D, Box2D, Box3D, Eigen::Vector2f, Eigen::Vector3f> position;

		struct Attach
		{
			Attach();

			boost::tuple<int, int, int> object;
			int player;
			Eigen::Vector3f position;
			int references;
			int vehicle;
		};

		boost::intrusive_ptr<Attach> attach;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct Checkpoint
	{
		Checkpoint();

		AMX *amx;
		SharedCell cell;
		int checkpointID;
		int extraID;
		Eigen::Vector3f position;
		int references;
		float size;
		float streamDistance;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct MapIcon
	{
		MapIcon();

		AMX *amx;
		SharedCell cell;
		int color;
		int extraID;
		int mapIconID;
		Eigen::Vector3f position;
		int references;
		float streamDistance;
		int style;
		int type;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct Object
	{
		Object();

		AMX *amx;
		SharedCell cell;
		float drawDistance;
		int extraID;
		int modelID;
		int objectID;
		Eigen::Vector3f position;
		int references;
		Eigen::Vector3f rotation;
		float streamDistance;

		struct Attach
		{
			Attach();

			Eigen::Vector3f position;
			Eigen::Vector3f offset;
			int references;
			Eigen::Vector3f rotation;
			int vehicle;
		};

		boost::intrusive_ptr<Attach> attach;

		struct Material
		{
			Material();

			int color;
			int index;
			int modelID;
			int references;
			std::string textureName;
			std::string txdName;
		};

		boost::intrusive_ptr<Material> material;

		struct Move
		{
			Move();

			int duration;
			boost::tuple<Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f> position;
			int references;
			boost::tuple<Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f> rotation;
			float speed;
			boost::chrono::steady_clock::time_point time;
		};

		boost::intrusive_ptr<Move> move;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct Pickup
	{
		Pickup();

		AMX *amx;
		SharedCell cell;
		int extraID;
		int modelID;
		int pickupID;
		Eigen::Vector3f position;
		int references;
		float streamDistance;
		int type;
		int worldID;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct RaceCheckpoint
	{
		RaceCheckpoint();

		AMX *amx;
		SharedCell cell;
		int extraID;
		Eigen::Vector3f next;
		Eigen::Vector3f position;
		int raceCheckpointID;
		int references;
		float size;
		float streamDistance;
		int type;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};

	struct TextLabel
	{
		TextLabel();

		AMX *amx;
		SharedCell cell;
		int color;
		float drawDistance;
		int extraID;
		Eigen::Vector3f position;
		int references;
		float streamDistance;
		bool testLOS;
		std::string text;
		int textLabelID;

		struct Attach
		{
			Attach();

			int player;
			Eigen::Vector3f position;
			int references;
			int vehicle;
		};

		boost::intrusive_ptr<Attach> attach;

		boost::unordered_set<int> extras;
		boost::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		boost::unordered_set<int> worlds;

		static Identifier identifier;
	};
}

namespace boost
{
	inline void intrusive_ptr_add_ref(Element::Area *area)
	{
		++area->references;
	}

	inline void intrusive_ptr_release(Element::Area *area)
	{
		if (!(--area->references))
		{
			delete area;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Area::Attach *attach)
	{
		++attach->references;
	}

	inline void intrusive_ptr_release(Element::Area::Attach *attach)
	{
		if (!(--attach->references))
		{
			delete attach;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Checkpoint *checkpoint)
	{
		++checkpoint->references;
	}

	inline void intrusive_ptr_release(Element::Checkpoint *checkpoint)
	{
		if (!(--checkpoint->references))
		{
			delete checkpoint;
		}
	}

	inline void intrusive_ptr_add_ref(Element::MapIcon *mapIcon)
	{
		++mapIcon->references;
	}

	inline void intrusive_ptr_release(Element::MapIcon *mapIcon)
	{
		if (!(--mapIcon->references))
		{
			delete mapIcon;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Object *object)
	{
		++object->references;
	}

	inline void intrusive_ptr_release(Element::Object *object)
	{
		if (!(--object->references))
		{
			delete object;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Object::Attach *attach)
	{
		++attach->references;
	}

	inline void intrusive_ptr_release(Element::Object::Attach *attach)
	{
		if (!(--attach->references))
		{
			delete attach;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Object::Material *material)
	{
		++material->references;
	}

	inline void intrusive_ptr_release(Element::Object::Material *material)
	{
		if (!(--material->references))
		{
			delete material;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Object::Move *move)
	{
		++move->references;
	}

	inline void intrusive_ptr_release(Element::Object::Move *move)
	{
		if (!(--move->references))
		{
			delete move;
		}
	}

	inline void intrusive_ptr_add_ref(Element::Pickup *pickup)
	{
		++pickup->references;
	}

	inline void intrusive_ptr_release(Element::Pickup *pickup)
	{
		if (!(--pickup->references))
		{
			delete pickup;
		}
	}

	inline void intrusive_ptr_add_ref(Element::RaceCheckpoint *raceCheckpoint)
	{
		++raceCheckpoint->references;
	}

	inline void intrusive_ptr_release(Element::RaceCheckpoint *raceCheckpoint)
	{
		if (!(--raceCheckpoint->references))
		{
			delete raceCheckpoint;
		}
	}

	inline void intrusive_ptr_add_ref(Element::TextLabel *textLabel)
	{
		++textLabel->references;
	}

	inline void intrusive_ptr_release(Element::TextLabel *textLabel)
	{
		if (!(--textLabel->references))
		{
			delete textLabel;
		}
	}

	inline void intrusive_ptr_add_ref(Element::TextLabel::Attach *attach)
	{
		++attach->references;
	}

	inline void intrusive_ptr_release(Element::TextLabel::Attach *attach)
	{
		if (!(--attach->references))
		{
			delete attach;
		}
	}
}

#endif
