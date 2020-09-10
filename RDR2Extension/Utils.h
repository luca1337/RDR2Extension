#pragma once

#include "natives.h"
#include "types.h"
#include <tuple>

namespace utils
{
	std::pair<Ped*, int> WorldGetAllPeds()
	{
		const int arrSize = 1024;
		Ped* peds = new Ped[arrSize];
		int foundPedCount = worldGetAllPeds(peds, arrSize);
		return std::make_pair(peds, foundPedCount);
	}
}