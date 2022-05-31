#include "tex/map.hpp"

#include <cstdlib>

#include "tex/world.hpp"

namespace tex
{
	map::map(vec2<std::size_t> size)
		: size(size)
	{
		data = (vec4<float> *) malloc(size.x * size.y * sizeof(vec4<float>));
	}

	map::~map()
	{
		free(data);
	}

	TEX_DLL bool in_bounds(const world &world, vec2<int> position)
	{
		return position.x >= 0 && position.y >= 0 &&
			position.x < world.m.size.x && position.y < world.m.size.y;
	}

	TEX_DLL vec4<float> get(const world &world, vec2<int> position)
	{
		return world.m.data[backend::get_linear_index(world, position)];
	}

	TEX_DLL void set(world &world, vec2<int> position, vec4<float> value)
	{
		world.m.data[backend::get_linear_index(world, position)] = value;
	}

	TEX_DLL void process(world &world, map_op op)
	{
		for (int x = 0; x < world.m.size.x; x++)
		{
			for (int y = 0; y < world.m.size.y; y++)
			{
				set(world, { x, y }, op(world, { x, y }));
			}
		}
	}

	namespace backend
	{
		int get_linear_index(const world &world, vec2<int> position)
		{
			return position.y * world.m.size.x + position.x;
		}
	}
}
