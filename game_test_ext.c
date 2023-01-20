#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

bool test_game_undo() {
  game g1 = game_new_empty_ext(4, 6, false, false);
  game_play_move(g1, 0, 0, S_ONE);
  game_undo(g1);
  if (game_get_square(g1, 0, 0) != S_EMPTY) {
    game_delete(g1);
    return false;
  }
  game_redo(g1);
  if (game_get_square(g1, 0, 0) != S_ONE) {
    game_delete(g1);
    return false;
  }
  game_play_move(g1, 2, 2, S_ONE);
  game_play_move(g1, 1, 3, S_ZERO);
  game_play_move(g1, 2, 2, S_ZERO);
  game_undo(g1);
  if (game_get_square(g1, 2, 2) != S_ONE) {
    game_delete(g1);
    return false;
  }


  game_undo(g1);

  return true;
}

bool test_game_redo() {
  game g = game_new_empty_ext(4, 6, false, false);
  game_play_move(g, 1, 1, S_ONE);
  game_play_move(g, 2, 2, S_ZERO);
  game_undo(g);
  game_undo(g);
  game_redo(g);
  game_redo(g);
  if (game_get_square(g, 1, 1) != S_ONE || game_get_square(g, 2, 2) != S_ZERO) {
    game_delete(g);
    return false;
  }
  game_undo(g);
  game_undo(g);
  if (game_get_square(g, 1, 1) != S_EMPTY ||
      game_get_square(g, 2, 2) != S_EMPTY) {
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

bool test_game_nb_rows() {
  game g = game_new_empty_ext(4, 6, false, false);
  if (game_nb_rows(g) != 4) {
    game_delete(g);
    return false;
  }
  game_delete(g);

  game g2 = game_new_empty_ext(6, 2, true, false);
  if (game_nb_rows(g2) != 6) {
    game_delete(g2);
    return false;
  }
  game_delete(g2);

  game g3 = game_new_empty_ext(2, 4, true, true);
  if (game_nb_rows(g3) != 2) {
    game_delete(g3);
    return false;
  }
  game_delete(g3);

  game g4 = game_new_empty_ext(8, 4, false, true);
  if (game_nb_rows(g4) != 8) {
    game_delete(g4);
    return false;
  }
  game_delete(g4);

  return true;
}

bool test_game_nb_cols() {
  game g = game_new_empty_ext(4, 6, false, false);
  if (game_nb_cols(g) != 6) {
    game_delete(g);
    return false;
  }
  game_delete(g);

  game g2 = game_new_empty_ext(2, 4, true, false);
  if (game_nb_cols(g2) != 4) {
    game_delete(g2);
    return false;
  }
  game_delete(g2);

  game g3 = game_new_empty_ext(6, 8, true, true);
  if (game_nb_cols(g3) != 8) {
    game_delete(g3);
    return false;
  }
  game_delete(g3);

  game g4 = game_new_empty_ext(4, 2, false, true);
  if (game_nb_cols(g4) != 2) {
    game_delete(g4);
    return false;
  }
  game_delete(g4);

  return true;
}

bool test_game_is_wrapping() {
  game g1 = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, false);
  game g2 = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, true, false);
  bool test = !game_is_wrapping(g1) && game_is_wrapping(g2);
  game_delete(g1);
  game_delete(g2);
  return test;
}

bool test_game_is_unique() {
  game g1 = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, false);
  game g2 = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, true);
  bool test = !game_is_unique(g1) && game_is_unique(g2);
  game_delete(g1);
  game_delete(g2);
  return test;
}

bool test_game_new_empty_ext() {
  game g = game_new_empty_ext(8, 4, true, false);
  for (int i = 0; i < game_nb_rows(g); i++) {
    for (int j = 0; j < game_nb_cols(g); j++) {
      square tmp = game_get_square(g, i, j);
      if (tmp != S_EMPTY) {
        game_delete(g);
        return false;
      }
    }
  }
  if (game_is_wrapping(g) != true || game_is_unique(g) != false) {
    game_delete(g);
    return false;
  }
  if (game_nb_rows(g) != 8 || game_nb_cols(g) != 4) {
    game_delete(g);
    return false;
  }
  game_undo(g);
  game_redo(g);

  game g2 = game_new_empty_ext(6, 8, false, true);
  for (int i = 0; i < g2->nb_rows; i++) {
    for (int j = 0; j < g2->nb_cols; j++) {
      square tmp = game_get_square(g2, i, j);
      if (tmp != S_EMPTY) {
        game_delete(g);
        game_delete(g2);
        return false;
      }
    }
  }
  if (game_is_unique(g2) != true || game_is_wrapping(g2) != false) {
    game_delete(g);
    game_delete(g2);
    return false;
  }
  if (game_nb_rows(g2) != 6 || game_nb_cols(g2) != 8) {
    game_delete(g);
    game_delete(g2);
    return false;
  }
  game_undo(g);
  game_redo(g);

  game_delete(g);
  game_delete(g2);
  return true;
}

bool test_game_new_ext() {
  square *square_array = malloc(sizeof(square) * (8 * 4));

  for (int i = 0; i < 32; i++) {
    square_array[i] = S_EMPTY;
  }
  game g = game_new_ext(8, 4, square_array, true, true);
  for (int i = 0; i < g->nb_rows; i++) {
    for (int j = 0; j < g->nb_cols; j++) {
      if (game_get_square(g, i, j) != S_ZERO &&
          game_get_square(g, i, j) != S_EMPTY &&
          game_get_square(g, i, j) != S_IMMUTABLE_ONE &&
          game_get_square(g, i, j) != S_IMMUTABLE_ZERO &&
          game_get_square(g, i, j) != S_ONE) {
        game_delete(g);
        free(square_array);
        return false;
      }
    }
  }
  if (game_is_unique(g) != true || game_is_wrapping(g) != true) {
    game_delete(g);
    free(square_array);
    return false;
  }
  if (game_nb_cols(g) != 4 || game_nb_rows(g) != 8) {
    game_delete(g);
    free(square_array);
    return false;
  }
  if (g->annulation == NULL || g->historique == NULL) {
    game_delete(g);
    free(square_array);
    return false;
  }

  game_delete(g);
  free(square_array);
  return true;
}

int main(int argc, char *argv[]) {
  if (argc == 1) usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("game_nb_rows", argv[1]) == 0)
    ok = test_game_nb_rows();
  else if (strcmp("game_nb_cols", argv[1]) == 0)
    ok = test_game_nb_cols();
  else if (strcmp("game_is_wrapping", argv[1]) == 0)
    ok = test_game_is_wrapping();
  else if (strcmp("game_new_empty_ext", argv[1]) == 0)
    ok = test_game_new_empty_ext();
  else if (strcmp("game_new_ext", argv[1]) == 0)
    ok = test_game_new_ext();
  else if (strcmp("game_is_unique", argv[1]) == 0)
    ok = test_game_is_unique();
  else if (strcmp("game_undo", argv[1]) == 0)
    ok = test_game_undo();
  else if (strcmp("game_redo", argv[1]) == 0)
    ok = test_game_redo();

  else {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}