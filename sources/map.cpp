#include "tex/map.hpp"

#include "tex/world.hpp"

namespace tex
{
	map::map(vec2<std::size_t> size)
		: size(size)
	{
		data = new vec4<float>[size.x * size.y];
	}

	map::~map()
	{
		delete[] data;
	}

	TEX_DLL bool in_bounds(const world &world, vec2<int> position)
	{
		return position.x >= 0 && position.y >= 0 &&
			position.x < world.m.size.x && position.y < world.m.size.y;
	}

	TEX_DLL vec2<size_t> size(const world &world)
	{
		return world.m.size;
	}

	TEX_DLL vec4<float> *begin(world &world)
	{
		return &world.m.data[0];
	}

	TEX_DLL vec4<float> *end(world &world)
	{
		return &world.m.data[world.m.size.x * world.m.size.y];
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
		TEX_DLL int get_linear_index(const world &world, vec2<int> position)
		{
			return position.y * world.m.size.x + position.x;
		}
	}
}
