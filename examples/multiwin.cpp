#include <tex.hpp>

int main(int argc, char *argv[])
{
	tex::world worlds[4];

	bool running = true;
	while (running)
	{
		for (int i = 0; i < 4; i++)
		{
			running &= tex::update(worlds[i]);

			tex::process(worlds[i], [](tex::world &world, tex::vec2<int> position) {
				int scale = 256 / world.m.size.x;
				return (tex::vec4<uint8_t>) { (uint8_t) (position.x * scale), (uint8_t) (position.y * scale), 0, 255 };
			});
		}
	}
}
