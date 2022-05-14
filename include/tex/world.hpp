#pragma once

#include <string>

#include "tex/display.hpp"
#include "tex/export.hpp"

namespace tex
{
	struct TEX_DLL world
	{
		display disp;

		world(const std::string &name = "Tex");
	};

	TEX_DLL bool update(const world &world);
}