#include "tex/instance.hpp"

#include <GLFW/glfw3.h>

#include "tex/error.hpp"

namespace tex
{
	namespace backend
	{
		bool instance::initialized = false;
		int instance::instances = 0;

		instance::instance()
		{
			instances++;
			if (instances > 0 && !initialized)
			{
				if (!glfwInit())
				{
					TEX_ERROR("failed to initialize glfw");
				}
				initialized = true;
			}
		}

		instance::~instance()
		{
			instances--;
			if (instances <= 0 && initialized)
			{
				instances = 0;
				initialized = false;
				glfwTerminate();
			}
		}
	}
}
