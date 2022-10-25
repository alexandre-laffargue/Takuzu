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
target_link_libraries(game_test_alelaffargue game libgame)

add_executable(game_test_rolalanne game_test_rolalanne.c)
target_link_libraries(game_test_rolalanne game libgame)

add_test(test_abahraoui_game_is_empty ./game_test_abahraoui game_is_empty)
add_test(test_abahraoui_game_play_move ./game_test_abahraoui game_play_move)
add_test(test_alelaffargue_dummy ./game_test_alelaffargue dummy)
add_test(test_rolalanne_dummy ./game_test_rolalanne dummy)
add_test(test_rolalanne_game_print ./game_test_rolalanne game_print)