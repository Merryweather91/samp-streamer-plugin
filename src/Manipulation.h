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

namespace Manipulation
{
	enum
	{
		AttachedObject,
		AttachedPlayer,
		AttachedVehicle,
		Color,
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
		MoveRX,
		MoveRY,
		MoveRZ,
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
		StreamDistance,
		Style,
		TestLOS,
		Type,
		WorldID,
		X,
		Y,
		Z
	};

	int getFloatData(AMX *amx, cell *params);
	int setFloatData(AMX *amx, cell *params);
	int getIntData(AMX *amx, cell *params);
	int setIntData(AMX *amx, cell *params);
	int getArrayData(AMX *amx, cell *params);
	int setArrayData(AMX *amx, cell *params);
	int isInArrayData(AMX *amx, cell *params);
	int appendArrayData(AMX *amx, cell *params);
	int removeArrayData(AMX *amx, cell *params);
}
