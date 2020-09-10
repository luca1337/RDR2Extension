#pragma once

#include <string>
#include "types.h"

struct WeaponInfo
{
	std::string hashKey;
	std::string uiName;
};

struct TeleportList
{
	std::string locationName;
	Vector3 locationCoords;
};

extern WeaponInfo weaponList[63];

extern TeleportList teleportList[39];