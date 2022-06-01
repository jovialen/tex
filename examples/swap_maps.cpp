#include <algorithm>

#include <tex.hpp>

int main(int argc, char *argv[])
{
	tex::world world("Swap maps", { 128, 128 });
	tex::map back_map({ 64, 64 });

	std::fill(tex::begin(world),    tex::end(world),    tex::vec4<float>{ 1, 1, 1, 1 });
	std::fill(tex::begin(back_map), tex::end(back_map), tex::vec4<float>{ 0, 0, 0, 1 });

	double timer = 0;
	while (tex::update(world))
	{
		timer += tex::get_delta_time(world);

		if (timer > 1)
		{
			timer = 0;
			tex::swap(world, back_map);
		}
	}
}
