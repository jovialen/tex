#include "tex/time.hpp"

#include "tex/world.hpp"

namespace tex
{
	TEX_DLL double get_delta_time(const world &world)
	{
		return world.clock.delta;
	}

	namespace backend
	{
		TEX_DLL void tick(clock &clock)
		{
			double now = glfwGetTime();
			clock.delta = now - clock.last;
			clock.last = now;
		}
	}
}
