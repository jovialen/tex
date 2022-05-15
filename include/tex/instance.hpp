#pragma once

#include <memory>

#include "tex/export.hpp"

namespace tex
{
	namespace backend
	{
		struct TEX_DLL instance
		{
			static bool initialized;
			static int instances;

			instance();
			~instance();
		};
	}
}
