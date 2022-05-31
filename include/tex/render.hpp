#pragma once

#include <memory>

#include <glad/gl.h>

#include "export.hpp"
#include "types.hpp"

namespace tex
{
	struct world;
	struct display;

	namespace backend
	{
		struct TEX_DLL mesh
		{
			GLuint vao;
			GLuint vbo;
			GLuint ebo;
		};

		struct TEX_DLL pipeline
		{
			GLuint program;
		};

		struct TEX_DLL texture
		{
			GLuint id;
		};

		struct TEX_DLL render_data
		{
			std::unique_ptr<GladGLContext> gl_context;

			pipeline pip;
			mesh quad;
			texture tex;

			render_data(const display &display);
			~render_data();
		};

		TEX_DLL void render(const world &world);

		TEX_DLL vec4<int> get_viewport(const world &world);
	}
}
