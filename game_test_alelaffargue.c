#define __USE_GNU
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "queue.h"
/*****TEST*****/
bool test_dummy() { return true; }

bool test_game_set_square() {
  game g = game_default();
  game_set_square(g, 1, 0, S_ONE);
  if (game_get_square(g, 1, 0) != S_ONE &&
      game_get_square(g, 0, 1) != S_EMPTY) {
    game_delete(g);
    return false;
  }

  game_set_square(g, 0, 0, S_ZERO);
  if (game_get_square(g, 0, 0) != S_ZERO) {
    game_delete(g);
    return false;
  }
  game_set_square(g, 0, 0, S_ONE);
  if (game_get_square(g, 0, 0) != S_ONE) {
    game_delete(g);
    return false;
  }
  game_set_square(g, 0, 0, S_EMPTY);
  if (game_get_square(g, 0, 0) != S_EMPTY) {
    game_delete(g);
    return false;
  }
  game_set_square(g, 0, 0, S_IMMUTABLE_ZERO);
  if (game_get_square(g, 0, 0) != S_IMMUTABLE_ZERO) {
    game_delete(g);
    return false;
  }
  game_set_square(g, 0, 1, S_IMMUTABLE_ONE);
  if (game_get_square(g, 0, 1) != S_IMMUTABLE_ONE) {
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

bool test_game_get_square() {
  square *square_array = malloc(sizeof(square) * (DEFAULT_SIZE * DEFAULT_SIZE));

  for (int i = 0; i < 36; i++) {
    square_array[i] = S_EMPTY;
  }
  square_array[0] = S_ZERO;
  square_array[1] = S_ONE;
  square_array[2] = S_IMMUTABLE_ONE;
  square_array[3] = S_IMMUTABLE_ZERO;
  game g = game_new(square_array);
  free(square_array);
  if (game_get_square(g, 0, 0) != S_ZERO) {
    game_delete(g);
    return false;
  } else if (game_get_square(g, 0, 1) != S_ONE) {
    game_delete(g);
    return false;
  } else if (game_get_square(g, 0, 2) != S_IMMUTABLE_ONE) {
    game_delete(g);
    return false;
  } else if (game_get_square(g, 0, 3) != S_IMMUTABLE_ZERO) {
    game_delete(g);
    return false;
  } else if (game_get_square(g, 0, 4) != S_EMPTY) {
    game_delete(g);
    return false;
  } else {
    game_delete(g);
    return true;
  }
}

bool test_game_get_number() {
  square *square_array = malloc(sizeof(square) * (DEFAULT_SIZE * DEFAULT_SIZE));

  for (int i = 0; i < 36; i++) {
    square_array[i] = S_EMPTY;
  }
  square_array[0] = S_ZERO;
  square_array[1] = S_ONE;
  square_array[2] = S_IMMUTABLE_ONE;
  square_array[3] = S_IMMUTABLE_ZERO;
  game g = game_new(square_array);
  free(square_array);
  if (game_get_number(g, 0, 0) != 0) {
    game_delete(g);
    return false;
  } else if (game_get_number(g, 0, 1) != 1) {
    game_delete(g);
    return false;
  } else if (game_get_number(g, 0, 2) != 1) {
    game_delete(g);
    return false;
  } else if (game_get_number(g, 0, 3) != 0) {
    game_delete(g);
    return false;
  } else if (game_get_number(g, 0, 4) != -1) {
    game_delete(g);
    return false;
  } else {
    game_delete(g);
    return true;
  }
}

bool test_game_get_next_square() {
  square *square_array = malloc(sizeof(square) * (DEFAULT_SIZE * DEFAULT_SIZE));
  for (int i = 0; i < 36; i++) {
    square_array[i] = S_EMPTY;
  }
  square *square_array_with_wrapping = malloc(sizeof(square) * (4 * 6));
  for (int i = 0; i < 24; i++) {
    square_array_with_wrapping[i] = S_EMPTY;
  }
  square_array[0] = S_ZERO;
  square_array[1] = S_ONE;
  square_array[2] = S_IMMUTABLE_ONE;
  square_array[3] = S_IMMUTABLE_ZERO;
  square_array[11] = S_IMMUTABLE_ZERO;
  square_array[12] = S_ONE;
  square_array[17] = S_IMMUTABLE_ONE;
  square_array[32] = S_ONE;
  square_array[34] = S_ZERO;

  square_array_with_wrapping[3] = S_ONE;
  square_array_with_wrapping[7] = S_ONE;
  square_array_with_wrapping[8] = S_IMMUTABLE_ONE;
  square_array_with_wrapping[12] = S_ZERO;
  square_array_with_wrapping[17] = S_IMMUTABLE_ONE;
  square_array_with_wrapping[20] = S_ONE;
  square_array_with_wrapping[22] = S_ZERO;
  square_array_with_wrapping[23] = S_IMMUTABLE_ZERO;

  game g = game_new(square_array);
  game g_with_wrapping =
      game_new_ext(4, 6, square_array_with_wrapping, true, true);
  free(square_array);
  free(square_array_with_wrapping);
  if (game_get_next_square(g, 1, 0, UP, 1) !=
      S_ZERO) {  // test à l'interieur de la grille
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 1, 0, DOWN, 1) != S_ONE) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 0, 1, LEFT, 1) != S_ZERO) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 0, 1, RIGHT, 1) != S_IMMUTABLE_ONE) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 2, 0, UP, 2) != S_ZERO) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 0, 0, DOWN, 2) != S_ONE) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 0, 5, LEFT, 2) != S_IMMUTABLE_ZERO) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 2, 0, RIGHT, 2) != S_EMPTY) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // début test à travers les bordures
  else if (game_get_next_square(g_with_wrapping, 2, 5, RIGHT, 1) != S_ZERO) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g_with_wrapping, 1, 5, RIGHT, 2) != S_ONE) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g_with_wrapping, 3, 0, LEFT, 1) !=
             S_IMMUTABLE_ZERO) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g_with_wrapping, 2, 1, LEFT, 2) !=
             S_IMMUTABLE_ONE) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g_with_wrapping, 0, 2, UP, 1) != S_ONE) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g_with_wrapping, 1, 4, UP, 2) != S_ZERO) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g_with_wrapping, 3, 3, DOWN, 1) != S_ONE) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g_with_wrapping, 3, 2, DOWN, 2) !=
             S_IMMUTABLE_ONE) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // début test à travers les bordures avec l'option wrapping fausse.
  else if (game_get_next_square(g, 0, 5, RIGHT, 1) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 0, 5, RIGHT, 2) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 1, 0, LEFT, 1) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 3, 1, LEFT, 2) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 0, 2, UP, 1) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 1, 4, UP, 2) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 5, 1, DOWN, 1) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_square(g, 4, 2, DOWN, 2) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else {
    game_delete(g);
    game_delete(g_with_wrapping);
    return true;
  }
}

bool test_game_get_next_number() {
  square *square_array = malloc(sizeof(square) * (DEFAULT_SIZE * DEFAULT_SIZE));
  for (int i = 0; i < 36; i++) {
    square_array[i] = S_EMPTY;
  }
  square *square_array_with_wrapping = malloc(sizeof(square) * (4 * 6));
  for (int i = 0; i < 24; i++) {
    square_array_with_wrapping[i] = S_EMPTY;
  }
  square_array[0] = S_ZERO;
  square_array[1] = S_ONE;
  square_array[2] = S_IMMUTABLE_ONE;
  square_array[3] = S_IMMUTABLE_ZERO;
  square_array[11] = S_IMMUTABLE_ZERO;
  square_array[12] = S_ONE;
  square_array[17] = S_IMMUTABLE_ONE;
  square_array[32] = S_ONE;
  square_array[34] = S_ZERO;

  square_array_with_wrapping[3] = S_ONE;
  square_array_with_wrapping[7] = S_ONE;
  square_array_with_wrapping[8] = S_IMMUTABLE_ONE;
  square_array_with_wrapping[12] = S_ZERO;
  square_array_with_wrapping[17] = S_IMMUTABLE_ONE;
  square_array_with_wrapping[20] = S_ONE;
  square_array_with_wrapping[22] = S_ZERO;
  square_array_with_wrapping[23] = S_IMMUTABLE_ZERO;

  game g = game_new(square_array);
  game g_with_wrapping =
      game_new_ext(4, 6, square_array_with_wrapping, true, true);
  free(square_array);
  free(square_array_with_wrapping);
  if (game_get_next_number(g, 1, 0, UP, 1) != 0) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // case valant S_ZERO
  else if (game_get_next_number(g, 1, 0, DOWN, 1) != 1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // case valant S_ONE
  else if (game_get_next_number(g, 0, 1, LEFT, 1) != 0) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // case valant S_ZERO
  else if (game_get_next_number(g, 0, 1, RIGHT, 1) != 1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // case valant S_IMMUTABLE_ONE
  else if (game_get_next_number(g, 2, 0, UP, 2) != 0) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // case valant S_ZERO
  else if (game_get_next_number(g, 0, 0, DOWN, 2) != 1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // case valant S_ONE
  else if (game_get_next_number(g, 0, 5, LEFT, 2) != 0) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // case valant S_IMMUTABLE_ZERO
  else if (game_get_next_number(g, 2, 0, RIGHT, 2) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // case valant S_EMPTY
  // début test à travers les bordures
  else if (game_get_next_number(g_with_wrapping, 2, 5, RIGHT, 1) != 0) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g_with_wrapping, 1, 5, RIGHT, 2) != 1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g_with_wrapping, 3, 0, LEFT, 1) != 0) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g_with_wrapping, 2, 1, LEFT, 2) != 1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g_with_wrapping, 0, 2, UP, 1) != 1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g_with_wrapping, 1, 4, UP, 2) != 0) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g_with_wrapping, 3, 3, DOWN, 1) != 1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g_with_wrapping, 3, 2, DOWN, 2) != 1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  }  // début test à travers les bordures avec l'option wrapping fausse.
  else if (game_get_next_number(g, 0, 5, RIGHT, 1) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g, 0, 5, RIGHT, 2) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g, 1, 0, LEFT, 1) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g, 3, 1, LEFT, 2) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g, 0, 2, UP, 1) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g, 1, 4, UP, 2) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g, 5, 1, DOWN, 1) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else if (game_get_next_number(g, 4, 2, DOWN, 2) != -1) {
    game_delete(g);
    game_delete(g_with_wrapping);
    return false;
  } else {
    game_delete(g);
    game_delete(g_with_wrapping);
    return true;
  }
}

bool test_game_is_immutable() {
  square *square_array = malloc(sizeof(square) * (DEFAULT_SIZE * DEFAULT_SIZE));

  for (int i = 0; i < 36; i++) {
    square_array[i] = S_EMPTY;
  }
  square_array[0] = S_ZERO;
  square_array[1] = S_ONE;
  square_array[2] = S_IMMUTABLE_ONE;
  square_array[3] = S_IMMUTABLE_ZERO;
  square_array[6] = S_IMMUTABLE_ONE;
  game g = game_new(square_array);
  free(square_array);
  if (!game_is_immutable(g, 0, 2)) {
    game_delete(g);
    return false;
  }  // case valant S_IMMUTABLE_ONE
  else if (!game_is_immutable(g, 0, 3)) {
    game_delete(g);
    return false;
  }  // case valant S_IMMUTABLE_ZERO
  else if (!game_is_immutable(g, 1, 0)) {
    game_delete(g);
    return false;
  }  // case valant S_IMMUTABLE_ONE
  else if (game_is_immutable(g, 0, 0)) {
    game_delete(g);
    return false;
  }  // case valant S_ZERO
  else if (game_is_immutable(g, 0, 1)) {
    game_delete(g);
    return false;
  }  // case valant S_ONE
  else if (game_is_immutable(g, 0, 4)) {
    game_delete(g);
    return false;
  }  // case valant S_EMPTY
  else {
    game_delete(g);
    return true;
  }
}

bool test_game_default_solution() {
  game g = game_default_solution();
  if (game_is_over(g)) {
    game_delete(g);
    return true;
  } else {
    game_delete(g);
    return false;
  }
}

/****USAGE****/
void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/****MAIN****/
int main(int argc, char *argv[]) {
  if (argc == 1) {
    usage(argc, argv);
  }

  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;

  if (strcmp("dummy", argv[1]) == 0) {
    ok = test_dummy();
  } else if (strcmp("game_set_square", argv[1]) == 0) {
    ok = test_game_set_square();
  } else if (strcmp("game_get_square", argv[1]) == 0) {
    ok = test_game_get_square();
  } else if (strcmp("game_get_number", argv[1]) == 0) {
    ok = test_game_get_number();
  } else if (strcmp("game_get_next_square", argv[1]) == 0) {
    ok = test_game_get_next_square();
  } else if (strcmp("game_get_next_number", argv[1]) == 0) {
    ok = test_game_get_next_number();
  } else if (strcmp("game_game_is_immutable", argv[1]) == 0) {
    ok = test_game_is_immutable();
  } else if (strcmp("game_default_solution", argv[1]) == 0) {
    ok = test_game_default_solution();
  }

  else {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // print test result
  if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}