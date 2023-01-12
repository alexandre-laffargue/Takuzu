#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "queue.h"

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

bool test_dummy() { return true; }

bool test_game_print() {
  game g = game_default();
  game_print(g);
  game_delete(g);
  return true;
}
bool test_game_new() {
  square *square_array = malloc(sizeof(square) * (DEFAULT_SIZE * DEFAULT_SIZE));

  for (int i = 0; i < 36; i++) {
    square_array[i] = S_EMPTY;
  }
  game g = game_new(square_array);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; i < 6; i++) {
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
  if (g->unique != false || g->wrapping != false) {
    game_delete(g);
    free(square_array);
    return false;
  }
  if (g->nb_cols != DEFAULT_SIZE || g->nb_rows != DEFAULT_SIZE) {
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
bool test_game_new_empty() {
  game g = game_new_empty();
  for (int i = 0; i < g->nb_rows; i++) {
    for (int j = 0; j < g->nb_cols; j++) {
      square tmp = game_get_square(g, i, j);
      if (tmp != S_EMPTY) {
        game_delete(g);
        return false;
      }
    }
  }
  if (g->unique != false || g->wrapping != false) {
    game_delete(g);
    return false;
  }
  if (g->nb_cols != DEFAULT_SIZE || g->nb_rows != DEFAULT_SIZE) {
    game_delete(g);
    return false;
  }
  if (g->annulation == NULL || g->historique == NULL) {
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}
bool test_game_copy() {
  game g = game_new_empty_ext(8, 4, true, true);
  game copy = game_copy(g);

  if (game_equal(g, copy) == false) {
    game_delete(g);
    game_delete(copy);
    return false;
  }
  game_play_move(g, 6, 2, S_ZERO);
  if (game_get_square(copy, 6, 2) == S_ZERO) {
    game_delete(g);
    game_delete(copy);
    return false;
  }
  
  if(game_is_wrapping(g) != game_is_wrapping(copy)){
    game_delete(g);
    game_delete(copy);
    return false;
  }

  if(game_is_unique(g) != game_is_unique(copy)){
    game_delete(g);
    game_delete(copy);
    return false;
  }

  g->wrapping = false;
  g->unique = false;
  
  if(game_is_wrapping(g) == game_is_wrapping(copy)){
    game_delete(g);
    game_delete(copy);
    return false;
  }

  if(game_is_unique(g) == game_is_unique(copy)){
    game_delete(g);
    game_delete(copy);
    return false;
  }
  game_delete(g);
  game_delete(copy);
  return true;
}

bool test_game_equal() {
  game g = game_new_empty();
  game dif = game_new_empty();
  game_set_square(g, 0, 0, S_EMPTY);
  game_set_square(g, 1, 1, S_ZERO);
  game_set_square(g, 3, 4, S_ONE);
  game_set_square(g, 2, 1, S_IMMUTABLE_ONE);
  game_set_square(g, 2, 2, S_IMMUTABLE_ZERO);
  game copy = game_copy(g);
  game difstate = game_copy(g);
  game_set_square(difstate, 1, 1, S_IMMUTABLE_ZERO);
  game_set_square(difstate, 3, 3, S_IMMUTABLE_ONE);

  game g2 = game_new_empty_ext(6, 4, false, false);
  game dif2 = game_new_empty_ext(6, 4, false, false);
  game_set_square(g2, 0, 0, S_EMPTY);
  game_set_square(g2, 1, 1, S_ZERO);
  game_set_square(g2, 5, 3, S_ONE);
  game_set_square(g2, 2, 1, S_IMMUTABLE_ONE);
  game_set_square(g2, 2, 2, S_IMMUTABLE_ZERO);
  game copy2 = game_copy(g2);
  game difstate2 = game_copy(g2);
  difstate2->unique = true;
  game_set_square(difstate2, 1, 1, S_IMMUTABLE_ZERO);
  game_set_square(difstate2, 3, 3, S_IMMUTABLE_ONE);

  if (game_equal(g, dif)) {
    game_delete(g);
    game_delete(dif);
    game_delete(copy);
    game_delete(difstate);
    game_delete(g2);
    game_delete(dif2);
    game_delete(copy2);
    game_delete(difstate2);
    return false;
  } else if (!game_equal(g, copy)) {
    game_delete(g);
    game_delete(dif);
    game_delete(copy);
    game_delete(difstate);
    game_delete(g2);
    game_delete(dif2);
    game_delete(copy2);
    game_delete(difstate2);
    return false;
  } else if (game_equal(g, difstate)) {
    game_delete(g);
    game_delete(dif);
    game_delete(copy);
    game_delete(difstate);
    game_delete(g2);
    game_delete(dif2);
    game_delete(copy2);
    game_delete(difstate2);
    return false;
  }
  if (game_equal(g, copy)) {
    if (g->wrapping != copy->wrapping || g->unique != copy->unique ||
        g->nb_cols != copy->nb_cols || g->nb_rows != copy->nb_rows) {
      game_delete(g);
      game_delete(dif);
      game_delete(copy);
      game_delete(difstate);
      game_delete(g2);
      game_delete(dif2);
      game_delete(copy2);
      game_delete(difstate2);
      return false;
    }
  }

  if (game_equal(g2, dif2)) {
    game_delete(g);
    game_delete(dif);
    game_delete(copy);
    game_delete(difstate);
    game_delete(g2);
    game_delete(dif2);
    game_delete(copy2);
    game_delete(difstate2);
    return false;
  } else if (!game_equal(g2, copy2)) {
    game_delete(g);
    game_delete(dif);
    game_delete(copy);
    game_delete(difstate);
    game_delete(g2);
    game_delete(dif2);
    game_delete(copy2);
    game_delete(difstate2);
    return false;
  } else if (game_equal(g2, difstate2)) {
    game_delete(g);
    game_delete(dif);
    game_delete(copy);
    game_delete(difstate);
    game_delete(g2);
    game_delete(dif2);
    game_delete(copy2);
    game_delete(difstate2);
    return false;
  }
  if (game_equal(g2, copy2)) {
    if (g2->wrapping != copy2->wrapping || g2->unique != copy2->unique ||
        g2->nb_cols != copy2->nb_cols || g2->nb_rows != copy2->nb_rows) {
      game_delete(g);
      game_delete(dif);
      game_delete(copy);
      game_delete(difstate);
      game_delete(g2);
      game_delete(dif2);
      game_delete(copy2);
      game_delete(difstate2);
      return false;
    }
  }

  game_delete(g);
  game_delete(dif);
  game_delete(copy);
  game_delete(difstate);
  game_delete(g2);
  game_delete(dif2);
  game_delete(copy2);
  game_delete(difstate2);
  return true;
}

bool test_game_delete() {
  game g = game_default();
  game_delete(g);
  return true;
}
bool test_game_default() {
  game g = game_default();
  for (int i = 0; i <= 5; i++) {
    for (int j = 0; j <= 5; j++) {
      if ((i == 0 && j == 1) || (i == 3 && j == 2) || (i == 4 && j == 2)) {
        if (game_get_square(g, i, j) != S_IMMUTABLE_ONE) {
          game_delete(g);
          return false;
        }
      } else if ((i == 0 && j == 2) || (i == 2 && j == 1) ||
                 (i == 2 && j == 4) || (i == 3 && j == 1) ||
                 (i == 4 && j == 5) || (i == 5 && j == 5)) {
        if (game_get_square(g, i, j) != S_IMMUTABLE_ZERO) {
          game_delete(g);
          return false;
        }
      } else {
        if (game_get_square(g, i, j) != S_EMPTY) {
          game_delete(g);
          return false;
        }
      }
    }
  }
  game_delete(g);

  return true;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    usage(argc, argv);
  }
  fprintf(stderr, "-> Start test \"%s\"\n", argv[1]);
  bool tmp = false;

  if (strcmp("dummy", argv[1]) == 0) {
    tmp = test_dummy();
  }

  else if (strcmp("game_print", argv[1]) == 0) {
    tmp = test_game_print();

  }

  else if (strcmp("game_delete", argv[1]) == 0) {
    tmp = test_game_delete();

  } else if (strcmp("game_new", argv[1]) == 0) {
    tmp = test_game_new();

  } else if (strcmp("game_new_empty", argv[1]) == 0) {
    tmp = test_game_new_empty();

  } else if (strcmp("game_copy", argv[1]) == 0) {
    tmp = test_game_copy();

  } else if (strcmp("game_equal", argv[1]) == 0) {
    tmp = test_game_equal();

  } else if (strcmp("game_default", argv[1]) == 0) {
    tmp = test_game_default();

  } else {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  if (tmp == true) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}
