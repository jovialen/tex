#include "tex/world.hpp"

#include <glad/gl.h>

namespace tex
{
	world::world(const std::string &name)
		: disp(name), rd(disp)
	{

	}

	TEX_DLL bool update(const world &world)
	{
		backend::render(world);
		backend::display_next_frame(world.disp);
		return !backend::display_should_close(world.disp);
	}
}
