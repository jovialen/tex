#include <algorithm>

#include <tex.hpp>

int main(int argc, char *argv[])
{
	tex::world world("Mouse");

	// Fill map with black
	std::fill(tex::begin(world), tex::end(world), tex::vec4<float>{ 0, 0, 0, 1 });

	while (tex::update(world))
	{
		// Darken tail over time
		std::for_each(tex::begin(world), tex::end(world), [&world](tex::vec4<float> &cell) {
			cell.r *= 1 - tex::get_delta_time(world);
			cell.g *= 1 - tex::get_delta_time(world);
			cell.b *= 1 - tex::get_delta_time(world);
		});

		// Make hovered cell (if any) white
		tex::vec2<int> mouse_cell = tex::get_hovered_cell(world);
		if (tex::in_bounds(world, mouse_cell) && tex::get_mouse_down(world, tex::mouse_button::LEFT))
		{
			tex::set(world, mouse_cell, tex::vec4<float>{ 1, 1, 1, 1 });
		}

		if (tex::get_key_down(world, tex::key::SPACE))
		{
			std::fill(tex::begin(world), tex::end(world), tex::vec4<float>{ 0, 0, 0, 1 });
		}
	}
}
