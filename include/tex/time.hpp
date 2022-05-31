#pragma once

#include "export.hpp"

namespace tex
{
	struct world;

	TEX_DLL double get_delta_time(const world &world);

	namespace backend
	{
		struct TEX_DLL clock
		{
			double last;
			double delta;
		};

		TEX_DLL void tick(clock &clock);
	}
}
