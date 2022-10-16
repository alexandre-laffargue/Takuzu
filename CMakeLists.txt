cmake_minimum_required(VERSION 3.3)

project(game_text C)



set(CMAKE_C_CFLAGS "-std=c99 -g -Wall")

link_directories(${CMAKE_SOURCE_DIR})

add_executable(game_text game_text.c)


target_link_libraries(game_text game)
