#include "tex/instance.hpp"

#include <GLFW/glfw3.h>

#include "tex/error.hpp"

namespace tex
{
	void init()
	{
		if (!glfwInit())
		{
			TEX_ERROR("failed to initialize glfw");
		}
	}

	void quit()
	{
		glfwTerminate();
	}
}
