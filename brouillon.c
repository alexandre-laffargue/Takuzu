#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "queue.h"

game game_new(square* squares) {
  game g = memory_alloc(sizeof(int) +
                        (DEFAULT_SIZE * DEFAULT_SIZE * sizeof(square)));
  g->size = DEFAULT_SIZE;
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      game_set_square(g, i, j, squares[i * g->size + j]);
    }
  }

  return g;
}

game game_new(square* squares) {
  game g = memory_alloc(sizeof(int) +
                        (DEFAULT_SIZE * DEFAULT_SIZE * sizeof(square)));
  g->size = DEFAULT_SIZE;
  g->square_array = memory_alloc(DEFAULT_SIZE * DEFAULT_SIZE * sizeof(square));
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      game_set_square(g, i, j, squares[i * g->size + j]);
    }
  }

  return g;
}

int game_has_error(cgame g, uint i, uint j) {
  int cpth = 1;
  int cptv = 1;
  if (game_get_next_number(g, i, j, LEFT, 1) == game_get_number(g, i, j)) {
    cpth++;
    if (game_get_next_number(g, i, j, LEFT, 2) == game_get_number(g, i, j)) {
      return -1;
    }
  }
  if (game_get_next_number(g, i, j, RIGHT, 1) == game_get_number(g, i, j)) {
    cpth++;
    if (cpth > 2) {
      return -1;
    }
    if (game_get_next_number(g, i, j, RIGHT, 2) == game_get_number(g, i, j)) {
      return -1;
    }
  }

  if (game_get_next_number(g, i, j, UP, 1) == game_get_number(g, i, j)) {
    cptv++;
    if (game_get_next_number(g, i, j, UP, 2) == game_get_number(g, i, j)) {
      return -2;
    }
  }
  if (game_get_next_number(g, i, j, DOWN, 1) == game_get_number(g, i, j)) {
    cptv++;
    if (cptv > 2) {
      return -2;
    }
    if (game_get_next_number(g, i, j, DOWN, 2) == game_get_number(g, i, j)) {
      return -2;
    }
  }
  return 0;
}

game g = game_new_empty_ext(6, 4, true, true);