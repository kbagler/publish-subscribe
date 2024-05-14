# Adding compile and link options MUST be done before calling 'add_library(), add_executable()' commands
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	include(CoverageCompileOpts)
endif()

# Object library is used here because we need to use all of the src/*.c files
# except main.c in unit tests
# add_library(dummy OBJECT)
# target_sources(dummy
# 	)

# target_include_directories(dummy
# 	)

# target_link_libraries(dummy
# 	)

add_executable(dummy)
target_sources(dummy
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	)

target_link_libraries(dummy
	)

# target_compile_definitions(dummy
# 	)

set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)
set(APP_VERSION_PATCH 0)
set(APP_VERSION ${APP_VERSION_MAJOR}.${APP_VERSION_MINOR}.${APP_VERSION_PATCH})

set_target_properties(dummy PROPERTIES VERSION ${APP_VERSION})

