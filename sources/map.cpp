#include "tex/map.hpp"

#include <algorithm>

#include <stb_image.h>
#include <stb_image_write.h>

#include "tex/error.hpp"
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
		return in_bounds(world.m, position);
	}

	TEX_DLL bool in_bounds(const map &map, vec2<int> position)
	{
		return position.x >= 0 && position.y >= 0 &&
			position.x < map.size.x && position.y < map.size.y;
	}

	TEX_DLL vec2<size_t> size(const world &world)
	{
		return size(world.m);
	}

	TEX_DLL vec2<size_t> size(const map &map)
	{
		return map.size;
	}

	TEX_DLL vec4<float> *begin(world &world)
	{
		return begin(world.m);
	}

	TEX_DLL vec4<float> *end(world &world)
	{
		return end(world.m);
	}

	TEX_DLL vec4<float> *begin(map &map)
	{
		return &map.data[0];
	}

	TEX_DLL vec4<float> *end(map &map)
	{
		return &map.data[map.size.x * map.size.y];
	}

	TEX_DLL map *get_map(world &world)
	{
		return &world.m;
	}

	TEX_DLL tex::vec4<float> *get_map_data(world &world)
	{
		return get_map_data(world.m);
	}

	TEX_DLL tex::vec4<float> *get_map_data(map &map)
	{
		return map.data;
	}

	TEX_DLL void swap(world &world, map &map)
	{
		swap(world.m, map);
	}

	TEX_DLL void swap(map &map1, map &map2)
	{
		std::swap(map1.data, map2.data);
		std::swap(map1.size, map2.size);
	}

	TEX_DLL vec4<float> get(const world &world, vec2<int> position)
	{
		return get(world.m, position);
	}

	TEX_DLL vec4<float> get(const map &map, vec2<int> position)
	{
		return map.data[backend::get_linear_index(map, position)];
	}

	TEX_DLL void set(world &world, vec2<int> position, vec4<float> value)
	{
		set(world.m, position, value);
	}

	TEX_DLL void set(map &map, vec2<int> position, vec4<float> value)
	{
		map.data[backend::get_linear_index(map, position)] = value;
	}

	TEX_DLL void save(world &world, std::filesystem::path output_path)
	{
		save(world.m, output_path);
	}

	TEX_DLL void save(map &map, std::filesystem::path output_path)
	{
		auto size = tex::size(map);

		tex::vec4<char> *data = new tex::vec4<char>[size.x * size.y];
		std::transform(tex::begin(map), tex::end(map), data, [](tex::vec4<float> cell) {
			return tex::vec4<char>{
				(char) (255 * cell.r),
				(char) (255 * cell.g),
				(char) (255 * cell.b),
				(char) (255 * cell.a),
			};
		});

		stbi_flip_vertically_on_write(true);
		stbi_write_bmp(output_path.filename().c_str(), size.x, size.y, 4, data);

		delete[] data;
	}

	TEX_DLL void load(world *world, std::filesystem::path input_path)
	{
		load(&world->m, input_path);
	}

	TEX_DLL void load(map *map, std::filesystem::path input_path)
	{
		if (!std::filesystem::exists(input_path)) return;

		tex::vec2<int> size;
		int comps;

		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(input_path.filename().c_str(), &size.x, &size.y, &comps, 4);

		if (data == nullptr)
		{
			TEX_ERROR("failed to load image file to world map");
		}

		auto map_size = tex::size(*map);
		if (size.x != map_size.x || size.y != map_size.y)
		{
			TEX_ERROR("attempted to load image of different size to world map");
		}

		for (int i = 0; i < size.x * size.y; i++)
		{
			map->data[i].r = data[i * 4 + 0] / 255.0f;
			map->data[i].g = data[i * 4 + 1] / 255.0f;
			map->data[i].b = data[i * 4 + 2] / 255.0f;
			map->data[i].a = data[i * 4 + 3] / 255.0f;
		}

		stbi_image_free(data);
	}

	TEX_DLL void process(world &world, map_op op)
	{
		process(world.m, op);
	}

	TEX_DLL void process(map &map, map_op op)
	{
		process(map, &map, op);
	}

	TEX_DLL void process(map &src, map *dst, map_op op)
	{
		auto src_size = size(src);
		auto dst_size = size(*dst);

		if (src_size.x != dst_size.x || src_size.y != dst_size.y)
		{
			TEX_ERROR("cannot process source map of different size to destination map");
		}

		for (int x = 0; x < src.size.x; x++)
		{
			for (int y = 0; y < src.size.y; y++)
			{
				set(*dst, { x, y }, op(src, { x, y }));
			}
		}
	}

	namespace backend
	{
		TEX_DLL int get_linear_index(const world &world, vec2<int> position)
		{
			return get_linear_index(world.m, position);
		}

		TEX_DLL int get_linear_index(const map &map, vec2<int> position)
		{
			return position.y * map.size.x + position.x;
		}
	}
}
