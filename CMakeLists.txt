cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(tex LANGUAGES CXX C)

add_subdirectory("dependencies/glad/cmake")
add_subdirectory("dependencies/glfw")
add_subdirectory("dependencies/stb")

GLAD_ADD_LIBRARY(glad_opengl_46_core REPRODUCIBLE MX API gl:core=4.6)

option(TEX_BUILD_EXAMPLES "Build the examples for Tex" TRUE)

set(TEX_SOURCES "sources/tex.cpp"
	"sources/display.cpp" "sources/input.cpp" "sources/instance.cpp"
	"sources/map.cpp" "sources/render.cpp" "sources/time.cpp"
	"sources/types.cpp" "sources/world.cpp")

add_library(tex_shared SHARED ${TEX_SOURCES})
add_library(tex_static STATIC ${TEX_SOURCES})

target_include_directories(tex_shared PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(tex_static PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(tex_shared PUBLIC __tex_dll)
target_compile_definitions(tex_shared PRIVATE __tex_build_dll)

target_compile_definitions(tex_static PUBLIC GLFW_INCLUDE_NONE)
target_compile_definitions(tex_shared PUBLIC GLFW_INCLUDE_NONE)

target_link_libraries(tex_shared PUBLIC glfw glad_opengl_46_core stb)
target_link_libraries(tex_static PUBLIC glfw glad_opengl_46_core stb)

set_target_properties(tex_shared PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON)

set_target_properties(tex_static PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON)

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

	add_executable(mouse "examples/mouse.cpp")
	target_link_libraries(mouse PRIVATE tex::tex)

	add_executable(savefile "examples/savefiles.cpp")
	target_link_libraries(savefile PRIVATE tex::tex)

	add_executable(swap "examples/swap_maps.cpp")
	target_link_libraries(swap PRIVATE tex::tex)
endif()
