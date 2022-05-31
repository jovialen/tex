#include <tex.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
	tex::world world("Hello Tex", { 16, 16 });

	while (tex::update(world))
	{
		tex::process(world, [](tex::world &world, tex::vec2<int> position) {
			tex::vec4<float> color = {
				(float) position.x / (float) tex::size(world).x,
				(float) position.y / (float) tex::size(world).y,
				0,
				1 };
			return color;
		});
	}
}
