cmake_minimum_required(VERSION 3.16.3)
project(publish-subscribe-p3 LANGUAGES C CXX)

include(CTest)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

if (NOT CMAKE_BUILD_TYPE)
	message("Build Type not set, defaulting to Release...")
	set(CMAKE_BUILD_TYPE "Release")
else()
	message("Build Type set to ${CMAKE_BUILD_TYPE}")
endif()

add_subdirectory(src)

enable_testing()
add_subdirectory(test)

