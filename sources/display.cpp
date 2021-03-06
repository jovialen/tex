#include "tex/display.hpp"

#include "tex/error.hpp"

namespace tex
{
	display::display(const std::string &title)
	{
		window = glfwCreateWindow(500, 500, title.c_str(), nullptr, nullptr);
		if (!window)
		{
			TEX_ERROR("failed to create window");
		}
	}

	display::~display()
	{
		glfwDestroyWindow(window);
	}

	namespace backend
	{
		TEX_DLL void activate_context(const display &display)
		{
			glfwMakeContextCurrent(display.window);
		}

		TEX_DLL void display_next_frame(const display &display)
		{
			glfwSwapBuffers(display.window);
		}
		
		TEX_DLL bool display_should_close(const display &display)
		{
			glfwPollEvents();
			return glfwWindowShouldClose(display.window);
		}

		TEX_DLL vec2<int> display_get_window_size(const display &display)
		{
			vec2<int> size;
			glfwGetWindowSize(display.window, &size.x, &size.y);
			return size;
		}

		TEX_DLL vec2<int> display_get_framebuffer_size(const display &display)
		{
			vec2<int> size;
			glfwGetFramebufferSize(display.window, &size.x, &size.y);
			return size;
		}
	}
}