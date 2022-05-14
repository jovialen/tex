#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace tex
{
	struct display
	{
		GLFWwindow *window;

		display(const std::string &title);
		~display();
	};

	namespace backend
	{
		void display_next_frame(const display &display);
		bool display_should_close(const display &display);
	}
}
