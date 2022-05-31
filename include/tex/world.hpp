#pragma once

#include <string>

#include "tex/display.hpp"
#include "tex/export.hpp"
#include "tex/instance.hpp"
#include "tex/map.hpp"
#include "tex/render.hpp"
#include "tex/time.hpp"

namespace tex
{
	struct TEX_DLL world
	{
		backend::instance inst;
		display disp;
		map m;
		backend::render_data rd;
		backend::clock clock;

		world(const std::string &name = "Tex", tex::vec2<std::size_t> size = { 64, 64 });
	};

	TEX_DLL bool update(world &world);
}
