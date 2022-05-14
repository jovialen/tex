cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(tex LANGUAGES CXX C)

option(TEX_BUILD_EXAMPLES "Build the examples for Tex" TRUE)

set(TEX_SOURCES "sources/tex.cpp")

add_library(tex_shared SHARED ${TEX_SOURCES})
add_library(tex_static STATIC ${TEX_SOURCES})

target_include_directories(tex_shared PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(tex_static PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(tex_shared PUBLIC __tex_dll)
target_compile_definitions(tex_shared PRIVATE __tex_build_dll)

add_library(tex ALIAS tex_static)
add_library(tex::tex ALIAS tex_static)
add_library(tex::static ALIAS tex_static)
add_library(tex::shared ALIAS tex_shared)

if (TEX_BUILD_EXAMPLES)
	add_executable(hello_tex "examples/hello_tex.cpp")
	target_link_libraries(hello_tex PRIVATE tex::tex)
endif()
