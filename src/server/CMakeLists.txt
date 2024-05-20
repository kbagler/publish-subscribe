find_package(Threads)

# Object library is used here because we need to use all of the src/*.c files
# except main.cpp in unit tests
add_library(Server OBJECT)
target_sources(Server
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Message.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/MessageDispatcher.cpp
	)

# target_include_directories(dummy
# 	)

# target_link_libraries(dummy
# 	)

add_executable(server)
target_sources(server
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Server_TCP.cpp
	)

target_link_libraries(server
	${CMAKE_THREAD_LIBS_INIT}
	Server
	)

# target_compile_definitions(dummy
# 	)

set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)
set(APP_VERSION_PATCH 0)
set(APP_VERSION ${APP_VERSION_MAJOR}.${APP_VERSION_MINOR}.${APP_VERSION_PATCH})

set_target_properties(server PROPERTIES VERSION ${APP_VERSION})
add_compile_definitions(SERVER_VERSION="${APP_VERSION}")
