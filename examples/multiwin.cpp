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

			tex::process(worlds[i], [](tex::map &map, tex::vec2<int> position) {
				tex::vec4<float> color = {
					(float) position.x / (float) tex::size(map).x,
					(float) position.y / (float) tex::size(map).y,
					0,
					1 };
				return color;
			});
		}
	}
}
