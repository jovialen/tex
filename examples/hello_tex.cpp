#include <tex.hpp>

int main(int argc, char *argv[])
{
	tex::init();

	tex::world world;

	while (tex::update(world))
	{
		
	}

	tex::quit();
}
