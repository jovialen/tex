#include <chrono>
#include <iostream>

#include <tex.hpp>

int main(int argc, char *argv[])
{
	tex::world world("Interval", { 32, 32 });

	double timer = 0;
	int iterations = 0;
	while (tex::update(world))
	{
		timer += tex::get_delta_time(world);

		if (timer > (1.0 / 30.0)) // 30 ticks per second
		{
			timer = 0;
			iterations++;

			tex::process(world, [iterations](tex::map &map, tex::vec2<int> position) {
				tex::vec4<float> color = {
					(float) ((position.x - iterations) % tex::size(map).x) / (float) tex::size(map).x,
					(float) ((position.y - iterations) % tex::size(map).y) / (float) tex::size(map).y,
					0,
					1 };
				return color;
			});
		}
	}
}
