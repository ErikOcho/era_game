cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 20)
project(era_game_lib)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_library(
	era_game_lib STATIC
	${SOURCE_FILES}
)

# # Pridanie kniznice nlohmann/json.
# add_subdirectory(json)
# target_link_libraries(era_game_lib PUBLIC nlohmann_json)

target_include_directories(era_game_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(era_game_lib PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann/json")

