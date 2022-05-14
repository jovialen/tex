#pragma once

#include <string>

#include "tex/display.hpp"

namespace tex
{
	struct world
	{
		display disp;

		world(const std::string &name = "Tex");
	};

	bool update(const world &world);
}