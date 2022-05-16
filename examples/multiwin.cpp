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
		}
	}
}
