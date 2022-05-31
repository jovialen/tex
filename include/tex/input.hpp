#pragma once

#include <GLFW/glfw3.h>

#include "export.hpp"
#include "types.hpp"

namespace tex
{
	struct world;

	enum class TEX_DLL mouse_button
	{
		ONE    = GLFW_MOUSE_BUTTON_1,
		TWO    = GLFW_MOUSE_BUTTON_2,
		THREE  = GLFW_MOUSE_BUTTON_3,
		FOUR   = GLFW_MOUSE_BUTTON_4,
		FIVE   = GLFW_MOUSE_BUTTON_5,
		SIX    = GLFW_MOUSE_BUTTON_6,
		SEVEN  = GLFW_MOUSE_BUTTON_7,
		EIGHT  = GLFW_MOUSE_BUTTON_8,
		LEFT   = GLFW_MOUSE_BUTTON_LEFT,
		RIGHT  = GLFW_MOUSE_BUTTON_RIGHT,
		MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
	};

	TEX_DLL bool get_mouse_down(const world &world, mouse_button button);
	TEX_DLL bool get_mouse_up(const world &world, mouse_button button);
	TEX_DLL vec2<double> get_mouse_position(const world &world);
	TEX_DLL vec2<int> get_hovered_cell(const world &world);
}