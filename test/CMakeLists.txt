# Adding compile and link options MUST be done before calling 'add_library(), add_executable()' commands
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	include(CoverageCompileOpts)
endif()

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

# Third-party software default versions
set(PREFERRED_VERSION_GOOGLETEST release-1.12.0)

# Download, unpack, and build googletest at configure time
set(BUILD_GMOCK OFF)
set(INSTALL_GTEST OFF)
message(STATUS "Googletest ${PREFERRED_VERSION_GOOGLETEST} is downloaded and used in the build")
include(FetchContent)
FetchContent_Populate(googletest
	GIT_REPOSITORY    https://github.com/google/googletest.git
	GIT_TAG           ${PREFERRED_VERSION_GOOGLETEST}
	)
# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(
	${CMAKE_CURRENT_BINARY_DIR}/googletest-src
	${CMAKE_CURRENT_BINARY_DIR}/googletest-build
	EXCLUDE_FROM_ALL
	)

include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}/include
	)

add_executable(publish-subscribe-test
	${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp
	)


# target_include_directories(publish-subscribe-test
# 	)

target_link_libraries(publish-subscribe-test
	GTest::gtest_main
	)

include(GoogleTest)
gtest_discover_tests(publish-subscribe-test)

# Create the coverage target. Run coverage tests with 'make coverage'
# Code coverage is available for Debug build only because running code coverage
# on the code compiled with optimization may yield incorrect results
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	find_program(
		LCOV_EXECUTABLE
		NAMES lcov
		DOC "lcov code coverage tool executable location"
		)
	message(STATUS "lcov executable: ${LCOV_EXECUTABLE}")
	if(LCOV_EXECUTABLE STREQUAL "LCOV_EXECUTABLE-NOTFOUND")
		message(SEND_ERROR "lcov not found, try installing it")
	endif()

	find_program(
		GCOVR_EXECUTABLE
		NAMES gcovr
		DOC "gcovr code coverage tool executable location"
		)
	message(STATUS "gcovr executable: ${GCOVR_EXECUTABLE}")
	if(GCOVR_EXECUTABLE STREQUAL "GCOVR_EXECUTABLE-NOTFOUND")
		message(SEND_ERROR "gcovr not found, try installing it")
	endif()

	set(COVERAGE_REPORT_DIR "coverage")
	add_custom_target(coverage
		COMMAND mkdir -p ${CMAKE_BINARY_DIR}/${COVERAGE_REPORT_DIR}
		BYPRODUCTS GENERATED ${CMAKE_BINARY_DIR}/${COVERAGE_REPORT_DIR}
		)
	add_custom_command(TARGET coverage
		COMMAND echo "=================== coverage ===================="
		COMMAND rm -fv publish-subscribe*.coverage.info
		COMMAND lcov
		--capture
		--directory ${CMAKE_BINARY_DIR}
		--output-file publish-subscribe.coverage.info
		COMMAND lcov
		--extract publish-subscribe.coverage.info ${CMAKE_SOURCE_DIR}/src/*
		-o publish-subscribe.coverage.info
		COMMAND lcov
		--add-tracefile publish-subscribe.coverage.info
		-o publish-subscribe.coverage.info
		COMMAND genhtml publish-subscribe.coverage.info
		--output-directory html
		COMMAND echo "-- Coverage html report has been output to ${CMAKE_BINARY_DIR}/${COVERAGE_REPORT_DIR}/html"
		COMMAND mkdir -p txt
		COMMAND gcovr
		--keep
		--root ${CMAKE_SOURCE_DIR}
		--filter ${CMAKE_SOURCE_DIR}/src/
		-o txt/coverage-line.info
		COMMAND gcovr
		--keep
		--branches
		--root ${CMAKE_SOURCE_DIR}
		--filter ${CMAKE_SOURCE_DIR}/src/
		-o txt/coverage-branch.info
		COMMAND echo "-- Coverage text report has been output to ${CMAKE_BINARY_DIR}/${COVERAGE_REPORT_DIR}/txt"
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${COVERAGE_REPORT_DIR}
		)
else()
	add_custom_target(coverage
		COMMAND echo "-- Code coverage report is available for Debug build only, this is ${CMAKE_BUILD_TYPE} build"
		)
endif()

