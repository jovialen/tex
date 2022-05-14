#pragma once

#include <string>

#include <GLFW/glfw3.h>

#include "tex/export.hpp"

namespace tex
{
	struct TEX_DLL display
	{
		GLFWwindow *window;

		display(const std::string &title);
		~display();
	};

	namespace backend
	{
		TEX_DLL void display_next_frame(const display &display);
		TEX_DLL bool display_should_close(const display &display);
	}
}
