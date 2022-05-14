#include "tex/world.hpp"

namespace tex
{
	world::world(const std::string &name)
		: disp(name)
	{

	}

	bool update(const world &world)
	{
		backend::display_next_frame(world.disp);
		return !backend::display_should_close(world.disp);
	}
}
