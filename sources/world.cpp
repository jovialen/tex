#include "tex/world.hpp"

#include <glad/gl.h>

namespace tex
{
	world::world(const std::string &name)
		: disp(name)
	{

	}

	TEX_DLL bool update(const world &world)
	{
		backend::activate_context(world.disp);

		auto &gl = world.disp.gl_context;
		gl->ClearColor(1, 1, 1, 1);
		gl->Clear(GL_COLOR_BUFFER_BIT);

		backend::display_next_frame(world.disp);
		return !backend::display_should_close(world.disp);
	}
}
