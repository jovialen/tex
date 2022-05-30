#pragma once

#include "export.hpp"

namespace tex
{
	template<typename T>
	struct TEX_DLL vec4
	{
		union { T x, r; };
		union { T y, g; };
		union { T z, b; };
		union { T w, a; };
	};

	template<typename T>
	struct TEX_DLL vec3
	{
		union { T x, r; };
		union { T y, g; };
		union { T z, b; };
	};

	template<typename T>
	struct TEX_DLL vec2
	{
		union { T x, r; };
		union { T y, g; };
	};
}
