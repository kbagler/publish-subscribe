find_package(Threads)

# Object library is used here because we need to use all of the src/*.c files
# except main.cpp in unit tests
add_library(Client OBJECT)
target_sources(Client
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Client.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Input.cpp
	)

# target_link_libraries(dummy
# 	)

add_executable(client)
target_sources(client
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/InputConsole.cpp
	)

# target_include_directories(client
# 	)

target_link_libraries(client
	Client
	${CMAKE_THREAD_LIBS_INIT}
	)

# target_compile_definitions(dummy
# 	)

set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)
set(APP_VERSION_PATCH 0)
set(APP_VERSION ${APP_VERSION_MAJOR}.${APP_VERSION_MINOR}.${APP_VERSION_PATCH})

set_target_properties(client PROPERTIES VERSION ${APP_VERSION})

