#pragma once

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
		vec4<uint8_t> *data;
		vec2<std::size_t> size;

		map(vec2<std::size_t> size);
		~map();
	};

	TEX_DLL bool in_bounds(const world &world, vec2<int> position);

	TEX_DLL vec4<uint8_t> get(const world &world, vec2<int> position);
	TEX_DLL void set(world &world, vec2<int> position, vec4<uint8_t> value);

	typedef vec4<uint8_t>(*map_op)(world&,vec2<int>);
	TEX_DLL void process(world &world, map_op op);

	namespace backend
	{
		int get_linear_index(const world &world, vec2<int> position);
	}
}