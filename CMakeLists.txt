cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(tex LANGUAGES CXX C)

add_subdirectory("dependencies/glad/cmake")
add_subdirectory("dependencies/glfw")

GLAD_ADD_LIBRARY(glad_opengl_46_core REPRODUCIBLE MX API gl:core=4.6)

option(TEX_BUILD_EXAMPLES "Build the examples for Tex" TRUE)

set(TEX_SOURCES "sources/tex.cpp"
	"sources/display.cpp" "sources/instance.cpp" "sources/map.cpp"
	"sources/render.cpp" "sources/time.cpp" "sources/types.cpp"
	"sources/world.cpp")

add_library(tex_shared SHARED ${TEX_SOURCES})
add_library(tex_static STATIC ${TEX_SOURCES})

target_include_directories(tex_shared PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(tex_static PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(tex_shared PUBLIC __tex_dll)
target_compile_definitions(tex_shared PRIVATE __tex_build_dll)

target_link_libraries(tex_shared PUBLIC glfw glad_opengl_46_core)
target_link_libraries(tex_static PUBLIC glfw glad_opengl_46_core)

add_library(tex ALIAS tex_static)
add_library(tex::tex ALIAS tex_static)
add_library(tex::static ALIAS tex_static)
add_library(tex::shared ALIAS tex_shared)

if (TEX_BUILD_EXAMPLES)
	add_executable(hello_tex "examples/hello_tex.cpp")
	target_link_libraries(hello_tex PRIVATE tex::tex)

	add_executable(tex_dll "examples/hello_tex.cpp")
	target_link_libraries(tex_dll PRIVATE tex::shared)

	add_executable(multiwin "examples/multiwin.cpp")
	target_link_libraries(multiwin PRIVATE tex::tex)

	add_executable(interval "examples/interval.cpp")
	target_link_libraries(interval PRIVATE tex::tex)
endif()
