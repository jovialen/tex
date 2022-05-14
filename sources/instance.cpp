#include "tex/instance.hpp"

#include <GLFW/glfw3.h>

#include "tex/error.hpp"

namespace tex
{
	TEX_DLL void init()
	{
		if (!glfwInit())
		{
			TEX_ERROR("failed to initialize glfw");
		}
	}

	TEX_DLL void quit()
	{
		glfwTerminate();
	}
}
