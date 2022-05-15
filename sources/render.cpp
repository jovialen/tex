#include "tex/render.hpp"

#include <GLFW/glfw3.h>

#include "tex/display.hpp"
#include "tex/error.hpp"
#include "tex/world.hpp"

namespace tex
{
	namespace backend
	{
		static const float vertices[] = {
			-0.5f,  0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
		};

		static const int indices[] = {
			0, 1, 2,
			1, 3, 2,
		};

		render_data::render_data(const display &display)
		{
			activate_context(display);

			gl_context = std::make_unique<GladGLContext>();
			if (!gladLoadGLContext(gl_context.get(), (GLADloadfunc) glfwGetProcAddress))
			{
				TEX_ERROR("failed to load opengl");
			}

			auto &gl = gl_context;

			gl->CreateVertexArrays(1, &quad.vao);

			gl->CreateBuffers(1, &quad.vbo);
			gl->CreateBuffers(1, &quad.ebo);

			gl->NamedBufferData(quad.vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
			gl->NamedBufferData(quad.ebo, sizeof(indices), indices, GL_STATIC_DRAW);

			gl->EnableVertexArrayAttrib(quad.vao, 0);
			gl->VertexArrayAttribBinding(quad.vao, 0, 0);
			gl->VertexArrayAttribFormat(quad.vao, 0, 3, GL_FLOAT, GL_FALSE, 0);

			gl->VertexArrayVertexBuffer(quad.vao, 0, quad.vbo, 0, 3 * sizeof(float));
			gl->VertexArrayElementBuffer(quad.vao, quad.ebo);
		}

		render_data::~render_data()
		{
			auto &gl = gl_context;

			gl->DeleteBuffers(1, &quad.vbo);
			gl->DeleteBuffers(1, &quad.ebo);
			gl->DeleteVertexArrays(1, &quad.vao);
		}

		TEX_DLL void render(const world &world)
		{
			activate_context(world.disp);

			auto &gl = world.rd.gl_context;
			gl->ClearColor(1, 1, 0, 1);
			gl->Clear(GL_COLOR_BUFFER_BIT);

			gl->BindVertexArray(world.rd.quad.vao);
			gl->DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}