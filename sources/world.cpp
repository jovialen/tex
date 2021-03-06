#include "tex/world.hpp"

#include <glad/gl.h>

namespace tex
{
	world::world(const std::string &name, tex::vec2<std::size_t> size)
		: disp(name), m(size), rd(disp)
	{

	}

	TEX_DLL bool update(world &world)
	{
		backend::tick(world.clock);
		backend::render(world);
		backend::display_next_frame(world.disp);
		return !backend::display_should_close(world.disp);
	}
}
