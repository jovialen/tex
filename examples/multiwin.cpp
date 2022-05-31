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
				return (tex::vec4<float>) {
					(float) position.x / (float) world.m.size.x,
					(float) position.y / (float) world.m.size.y,
					0,
					1 };
			});
		}
	}
}
