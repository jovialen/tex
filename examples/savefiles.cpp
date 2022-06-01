#include <tex.hpp>

tex::vec4<float> get_cell_color(tex::world &world, tex::vec2<int> cell_position)
{
	return tex::vec4<float>{
		(float) cell_position.x / (float) tex::size(world).x,
		(float) cell_position.y / (float) tex::size(world).y,
		1,
		1,
	};
}

int main(int argc, char *argv[])
{
	tex::world world("Save and load images");

	std::for_each(tex::begin(world), tex::end(world), [](tex::vec4<float> &v) { v = tex::vec4<float>{ 0, 0, 0, 1 }; });

	tex::load(&world, "./savefile.bmp");

	while (tex::update(world))
	{
		auto hovered_cell = tex::get_hovered_cell(world);
		if (tex::in_bounds(world, hovered_cell))
		{
			if (tex::get_mouse_down(world, tex::mouse_button::LEFT))
			{
				tex::set(world, hovered_cell, get_cell_color(world, hovered_cell));
			}
			else if (tex::get_mouse_down(world, tex::mouse_button::RIGHT))
			{
				tex::set(world, hovered_cell, tex::vec4<float>{ 0, 0, 0, 1 });
			}
		}
	}

	tex::save(world, "./savefile.bmp");
}
