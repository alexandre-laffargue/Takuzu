cmake_minimum_required(VERSION 3.3)

project(game_text C)
include(CTest)
enable_testing()



set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
link_directories(${CMAKE_SOURCE_DIR})
add_library(libgame game_text.c)
add_executable(game_text game_text.c)
target_link_libraries(game_text game libgame)



add_executable(game_test_abahraoui game_test_abahraoui.c)
target_link_libraries(game_test_abahraoui game libgame)

add_executable(game_test_alelaffargue game_test_alelaffargue.c)

add_test(test_abahraoui_dummy ./game_test_abahraoui dummy)
add_test(test_alelaffargue_test_dummy ./game_test_alelaffargue dummy)
