#include "tex/input.hpp"

#include <iostream>

#include "tex/world.hpp"

namespace tex
{
	TEX_DLL bool get_mouse_down(const world &world, mouse_button button)
	{
		return glfwGetMouseButton(world.disp.window, (int) button) == GLFW_PRESS;
	}

	TEX_DLL bool get_mouse_up(const world &world, mouse_button button)
	{
		return glfwGetMouseButton(world.disp.window, (int) button) == GLFW_RELEASE;
	}

	TEX_DLL vec2<double> get_mouse_position(const world &world)
	{
		vec2<double> mouse_pos;
		glfwGetCursorPos(world.disp.window, &mouse_pos.x, &mouse_pos.y);
		return mouse_pos;
	}

	TEX_DLL bool get_key_down(const world &world, key k)
	{
		return glfwGetKey(world.disp.window, (int) k) == GLFW_PRESS;
	}

	TEX_DLL bool get_key_up(const world &world, key k)
	{
		return glfwGetKey(world.disp.window, (int) k) == GLFW_RELEASE;
	}

	TEX_DLL vec2<int> get_hovered_cell(const world &world)
	{
		vec2<double> mouse_pos = get_mouse_position(world);

		vec4<int> viewport_size = backend::get_viewport(world);
		vec2<int> window_size = backend::display_get_window_size(world.disp);

		// mouse coordinates start at top-left, coordinates start at bottom-left
		mouse_pos.y = window_size.y - mouse_pos.y;

		// make mouse relative to viewport instead of window
		mouse_pos.x -= viewport_size.x;
		mouse_pos.y -= viewport_size.y;

		// find cell mouse is hovering over
		mouse_pos.x = mouse_pos.x / viewport_size.z;
		mouse_pos.y = mouse_pos.y / viewport_size.w;

		vec2<int> cell;
		cell.x = (int) ((float) mouse_pos.x * (float) world.m.size.x);
		cell.y = (int) ((float) mouse_pos.y * (float) world.m.size.y);

		return cell;
	}
}
