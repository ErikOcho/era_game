# Projekt ERA GAME.
cmake_minimum_required(VERSION 3.0.0)
project(era_game VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
add_executable(era_program ${SOURCE_FILES})

# Pridanie knihovny era_game_lib.
add_subdirectory(era_game_lib)
target_link_libraries(era_program PRIVATE era_game_lib)

add_subdirectory(test)
