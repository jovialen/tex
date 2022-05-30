#include <tex.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
	tex::world world("Hello Tex", { 16, 16 });

	while (tex::update(world))
	{
		tex::process(world, [](tex::world &world, tex::vec2<int> position) {
			return (tex::vec4<uint8_t>) { (uint8_t) (position.x * 16), (uint8_t) (position.y * 16), 0, 255 };
		});
	}
}
