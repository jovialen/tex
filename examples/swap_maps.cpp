#include <algorithm>

#include <tex.hpp>

int main(int argc, char *argv[])
{
	tex::world world("Swap maps");
	tex::map back_map(tex::size(world));

	while (tex::update(world))
	{
		std::swap(tex::get_map(world), back_map);
	}
}
