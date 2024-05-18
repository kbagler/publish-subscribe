# Adding compile and link options MUST be done before calling 'add_library(), add_executable()' commands
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	include(CoverageCompileOpts)
endif()

add_subdirectory(client)
add_subdirectory(server)

