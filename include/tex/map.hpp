#pragma once

#include <filesystem>
#include <functional>

#include <cstddef>
#include <cstdint>

#include "export.hpp"
#include "types.hpp"

namespace tex
{
	struct world;

	struct TEX_DLL map
	{
		vec4<float> *data;
		vec2<std::size_t> size;

		map(vec2<std::size_t> size);
		~map();
	};

	TEX_DLL bool in_bounds(const world &world, vec2<int> position);
	TEX_DLL bool in_bounds(const map &map,     vec2<int> position);
	TEX_DLL vec2<size_t> size(const world &world);
	TEX_DLL vec2<size_t> size(const map &map);

	TEX_DLL vec4<float> *begin(world &world);
	TEX_DLL vec4<float> *end(world &world);
	TEX_DLL vec4<float> *begin(map &map);
	TEX_DLL vec4<float> *end(map &map);

	TEX_DLL map *get_map(world &world);
	TEX_DLL tex::vec4<float> *get_map_data(world &world);
	TEX_DLL tex::vec4<float> *get_map_data(map &map);

	TEX_DLL void swap(world &world, map &map);
	TEX_DLL void swap(map &map1, map &map2);
	TEX_DLL vec4<float> get(const world &world, vec2<int> position);
	TEX_DLL vec4<float> get(const map &map,     vec2<int> position);
	TEX_DLL void set(world &world, vec2<int> position, vec4<float> value);
	TEX_DLL void set(map &map,     vec2<int> position, vec4<float> value);

	TEX_DLL void save(world &world, std::filesystem::path output_path);
	TEX_DLL void save(map &map,     std::filesystem::path output_path);
	TEX_DLL void load(world *world, std::filesystem::path input_path);
	TEX_DLL void load(map *map,     std::filesystem::path input_path);

	using map_op = std::function<vec4<float>(map&,vec2<int>)>;
	TEX_DLL void process(world &world, map_op op);
	TEX_DLL void process(map &map, map_op op);
	TEX_DLL void process(map &src, map *dst, map_op op);

	namespace backend
	{
		TEX_DLL int get_linear_index(const world &world, vec2<int> position);
		TEX_DLL int get_linear_index(const map &map,     vec2<int> position);
	}
}