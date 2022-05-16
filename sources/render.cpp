#include "tex/render.hpp"

#include <GLFW/glfw3.h>

#include "tex/display.hpp"
#include "tex/error.hpp"
#include "tex/types.hpp"
#include "tex/world.hpp"

namespace tex
{
	namespace backend
	{
		struct vertex
		{
			vec3 position;
			vec2 uv;
		};

		static const vertex vertices[] = {
			{ { -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f } },
			{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f } },
			{ {  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f } },
			{ {  0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f } },
		};

		static const int indices[] = {
			0, 1, 2,
			1, 3, 2,
		};

		static const char *vertex_source = "#version 330 core\n"
			"layout(location = 0) in vec3 i_pos;"
			"layout(location = 1) in vec2 i_uv;"
			"out vec2 v_uv;"
			"void main() {"
			"	gl_Position = vec4(i_pos, 1.0);"
			"	v_uv = i_uv;"
			"}";

		static const char *fragment_source = "#version 330 core\n"
			"in vec2 v_uv;"
			"out vec4 o_col;"
			"void main() {"
			"	o_col = vec4(v_uv, 0.0, 1.0);"
			"}";

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
			gl->VertexArrayAttribFormat(quad.vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(vertex, position));

			gl->EnableVertexArrayAttrib(quad.vao, 1);
			gl->VertexArrayAttribBinding(quad.vao, 1, 0);
			gl->VertexArrayAttribFormat(quad.vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(vertex, uv));

			gl->VertexArrayVertexBuffer(quad.vao, 0, quad.vbo, 0, sizeof(vertex));
			gl->VertexArrayElementBuffer(quad.vao, quad.ebo);

			pip.program = gl->CreateProgram();

			GLuint vs, fs;
			GLint status;
			vs = gl->CreateShader(GL_VERTEX_SHADER);
			fs = gl->CreateShader(GL_FRAGMENT_SHADER);

			gl->ShaderSource(vs, 1, &vertex_source, nullptr);
			gl->CompileShader(vs);

			gl->GetShaderiv(vs, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				TEX_ERROR("failed to compile vertex shader: \n");
			}

			gl->ShaderSource(fs, 1, &fragment_source, nullptr);
			gl->CompileShader(fs);

			gl->GetShaderiv(fs, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				TEX_ERROR("failed to compile fragment shader: \n");
			}

			gl->AttachShader(pip.program, vs);
			gl->AttachShader(pip.program, fs);
			gl->LinkProgram(pip.program);

			gl->GetProgramiv(pip.program, GL_LINK_STATUS, &status);
			if (!status)
			{
				TEX_ERROR("failed to link shader program: \n");
			}
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

			ivec2 size = backend::display_get_window_size(world.disp);

			auto &gl = world.rd.gl_context;

			gl->Viewport(0, 0, size.x, size.y);
			gl->ClearColor(1, 1, 1, 1);
			gl->Clear(GL_COLOR_BUFFER_BIT);

			gl->UseProgram(world.rd.pip.program);
			gl->BindVertexArray(world.rd.quad.vao);
			gl->DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}