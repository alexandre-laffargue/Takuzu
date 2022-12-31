cmake_minimum_required(VERSION 3.3)

project(game_text C)
include(CTest)
enable_testing()



set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
link_directories(${CMAKE_SOURCE_DIR})
add_library(game game.c game_aux.c game_ext.c queue.c)
add_executable(game_text game_text.c)
target_link_libraries(game_text game )



add_executable(game_test_abahraoui game_test_abahraoui.c)
target_link_libraries(game_test_abahraoui game )

add_executable(game_test_alelaffargue game_test_alelaffargue.c)
target_link_libraries(game_test_alelaffargue game )

add_executable(game_test_rolalanne game_test_rolalanne.c)
target_link_libraries(game_test_rolalanne game )

add_executable(game_test_ext game_test_ext.c)
target_link_libraries(game_test_ext game)

add_test(test_abahraoui_game_is_empty ./game_test_abahraoui game_is_empty)
add_test(test_abahraoui_game_play_move ./game_test_abahraoui game_play_move)
add_test(test_abahraoui_game_has_error ./game_test_abahraoui game_has_error)
add_test(test_abahraoui_game_restart ./game_test_abahraoui game_restart)
add_test(test_abahraoui_game_check_move ./game_test_abahraoui game_check_move)
add_test(test_abahraoui_game_is_over ./game_test_abahraoui game_is_over)

add_test(test_alelaffargue_dummy ./game_test_alelaffargue dummy)
add_test(test_alelaffargue_game_set_square ./game_test_alelaffargue game_set_square)
add_test(test_alelaffargue_game_default_solution ./game_test_alelaffargue game_default_solution)
add_test(test_alelaffargue_game_get_square ./game_test_alelaffargue game_get_square)
add_test(test_alelaffargue_game_get_number ./game_test_alelaffargue game_get_number)
add_test(test_alelaffargue_game_get_next_square ./game_test_alelaffargue game_get_next_square)
add_test(test_alelaffargue_game_get_next_number ./game_test_alelaffargue game_get_next_number)
add_test(test_alelaffargue_game_game_is_immutable ./game_test_alelaffargue game_game_is_immutable)


add_test(test_rolalanne_dummy ./game_test_rolalanne dummy)
add_test(test_rolalanne_game_print ./game_test_rolalanne game_print)
add_test(test_rolalanne_game_delete ./game_test_rolalanne game_delete)
add_test(test_rolalanne_game_new ./game_test_rolalanne game_new)
add_test(test_rolalanne_game_new_empty ./game_test_rolalanne game_new_empty)
add_test(test_rolalanne_game_copy ./game_test_rolalanne game_copy)
add_test(test_rolalanne_game_equal ./game_test_rolalanne game_equal)
add_test(test_rolalanne_game_default ./game_test_rolalanne game_default)
add_test(test_rolalanne_game_is_wrapping ./game_test_rolalanne game_is_wrapping)

add_test(test_ext_game_nb_rows ./game_test_ext game_nb_rows)
add_test(test_ext_game_nb_cols ./game_test_ext game_nb_cols)
add_test(test_ext_game_is_wrapping ./game_test_ext game_is_wrapping)