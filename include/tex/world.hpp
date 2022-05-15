#pragma once

#include <string>

#include "tex/display.hpp"
#include "tex/export.hpp"
#include "tex/instance.hpp"
#include "tex/render.hpp"

namespace tex
{
	struct TEX_DLL world
	{
		backend::instance inst;
		display disp;
		backend::render_data rd;

		world(const std::string &name = "Tex");
	};

	TEX_DLL bool update(const world &world);
}
