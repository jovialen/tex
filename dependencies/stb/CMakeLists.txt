cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(stb LANGUAGES C CXX)

add_library(stb STATIC "stb_impl.cpp")
target_include_directories(stb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(stb PROPERTIES
	POSITION_INDEPENDENT_CODE ON)
