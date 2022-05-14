#pragma once

#include <memory>
#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "tex/export.hpp"

namespace tex
{
	struct TEX_DLL display
	{
		GLFWwindow *window;
		std::unique_ptr<GladGLContext> gl_context;

		display(const std::string &title);
		~display();
	};

	namespace backend
	{
		TEX_DLL void activate_context(const display &display);
		TEX_DLL void display_next_frame(const display &display);
		TEX_DLL bool display_should_close(const display &display);
	}
}
