#include <tex.hpp>

int main(int argc, char *argv[])
{
	tex::world world1("1");
	tex::world world2("2");

	while (tex::update(world1) && tex::update(world2))
	{
		
	}
}
