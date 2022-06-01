#include "tex/map.hpp"

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

	TEX_DLL void save(world &world, std::filesystem::path output_path)
	{
		auto size = tex::size(world);

		tex::vec4<char> *data = new tex::vec4<char>[size.x * size.y];
		std::transform(tex::begin(world), tex::end(world), data, [](tex::vec4<float> cell) {
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
		if (!std::filesystem::exists(input_path)) return;

		tex::vec2<int> size;
		int comps;

		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(input_path.filename().c_str(), &size.x, &size.y, &comps, 4);

		if (data == nullptr) return;

		auto world_size = tex::size(*world);
		if (size.x != world_size.x || size.y != world_size.y)
		{
			TEX_ERROR("attempted to load image of different size to world");
		}

		for (int i = 0; i < size.x * size.y; i++)
		{
			world->m.data[i].r = data[i * 4 + 0] / 255.0f;
			world->m.data[i].g = data[i * 4 + 1] / 255.0f;
			world->m.data[i].b = data[i * 4 + 2] / 255.0f;
			world->m.data[i].a = data[i * 4 + 3] / 255.0f;
		}

		stbi_image_free(data);
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
