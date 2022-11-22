cmake_minimum_required(VERSION 3.3.0)
project(era_game_lib_test)

# Setup testing
enable_testing()
find_package(GTest REQUIRED)

# set source files
file(GLOB_RECURSE TEST_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(era_game_lib_test ${TEST_SOURCE_FILES})
target_link_libraries(era_game_lib_test
	PRIVATE
	GTest::GTest
	GTest::gmock
	GTest::Main
	era_game_lib
)
