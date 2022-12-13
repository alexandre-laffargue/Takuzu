#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_aux.h"
#include "game_ext.h"

struct game_s {
  square* square_array;
  bool wrapping;
  bool unique;
  uint nb_rows;
  uint nb_cols;
};

void* memory_alloc(uint size) {
  void* tmp = malloc(size);
  if (tmp == NULL) {
    fprintf(stderr, "Memory allocation failed \n");
    exit(EXIT_FAILURE);
  } else {
    return tmp;
  }
}

game game_new(square* squares) {
  if (squares == NULL) {
    exit(EXIT_FAILURE);
  }
  game new = memory_alloc(sizeof(struct game_s));
  new->nb_rows = DEFAULT_SIZE;
  new->nb_cols = DEFAULT_SIZE;
  square* array = memory_alloc((new->nb_rows* new->nb_cols) * sizeof(square));

  for (int i = 0; i < (new->nb_rows* new->nb_cols); i++) {
    square tmp = squares[i];
    array[i] = tmp;
  }
  new->square_array = array;
  return new;
}

game game_new_empty(void) {
  game g = memory_alloc(sizeof(struct game_s));
  g->nb_rows = DEFAULT_SIZE;
  g->nb_cols = DEFAULT_SIZE;
  square* array = memory_alloc((g->nb_rows * g->nb_cols) * sizeof(square));

  for (int i = 0; i < g->nb_rows * g->nb_cols; i++) {
    array[i] = S_EMPTY;
  }
  g->square_array = array;
  return g;
}

game game_copy(cgame g) {
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  game copy = memory_alloc(sizeof(struct game_s));
  copy->nb_rows = g->nb_rows;
  copy->nb_cols = g->nb_cols;
  copy->square_array = memory_alloc((copy->nb_rows * copy->nb_cols) * sizeof(square));
  for (int i = 0; i < copy->nb_rows; i++) {
    for (int j = 0; j < copy->nb_cols; j++) {
      game_set_square(copy, i, j, game_get_square(g, i, j));
    }
  }

  return copy;
}

bool game_equal(cgame g1, cgame g2) {
  if (g1 == NULL || g2 == NULL) {
    exit(EXIT_FAILURE);
  }
  if ((g1->nb_rows != g2->nb_rows) || (g1->nb_cols != g2->nb_cols)) {
    return false;
  }
  for (int i = 0; i < g1->nb_rows * g1->nb_cols; i++) {
    if (g1->square_array[i] != g2->square_array[i]) {
      return false;
    }
  }
  return true;
}

void game_delete(game g) {
  if (g != NULL) {
    if (g->square_array != NULL) {
      free(g->square_array);
    }
    free(g);
  }
}

void game_set_square(game g, uint i, uint j, square s) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols ||
      (s != S_EMPTY && s != S_IMMUTABLE_ONE && s != S_IMMUTABLE_ZERO &&
       s != S_ONE && s != S_ZERO)) {
    exit(EXIT_FAILURE);
  }
  uint index = (i * g->nb_rows) + j;
  g->square_array[index] = s;
}

square game_get_square(cgame g, uint i, uint j) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    exit(EXIT_FAILURE);
  }
  uint index = (i * g->nb_rows) + j;
  return g->square_array[index];
}

int game_get_number(cgame g, uint i, uint j) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    exit(EXIT_FAILURE);
  }
  uint index = (i * g->nb_rows) + j;
  square sq = g->square_array[index];
  if (sq == S_ZERO || sq == S_IMMUTABLE_ZERO) {
    return 0;
  } else if (sq == S_ONE || sq == S_IMMUTABLE_ONE) {
    return 1;
  } else
    return -1;
}

int game_get_next_square(cgame g, uint i, uint j, direction dir, uint dist) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols || dist > 2) {
    exit(EXIT_FAILURE);
  }
  uint index = (i * g->nb_rows) + j;
  if (dir == UP) {
    int coord = i - dist;
    if (coord >= 0 && coord < g->nb_cols) {
      uint indexf = index - (dist * g->nb_cols);
      square sq = g->square_array[indexf];
      return sq;
    } else {
      return -1;
    }
  } else if (dir == DOWN) {
    int coord = i + dist;
    if (coord >= 0 && coord < g->nb_cols) {
      uint indexf = index + (dist * g->nb_cols);
      square sq = g->square_array[indexf];
      return sq;
    } else {
      return -1;
    }
  } else if (dir == LEFT) {
    int coord = j - dist;
    if (coord >= 0 && coord < g->nb_rows) {
      uint indexf = index - dist;
      square sq = g->square_array[indexf];
      return sq;
    } else {
      return -1;
    }
  } else if (dir == RIGHT) {
    int coord = j + dist;
    if (coord >= 0 && coord < g->nb_rows) {
      uint indexf = index + dist;
      square sq = g->square_array[indexf];
      return sq;
    } else {
      return -1;
    }
  }
  exit(EXIT_FAILURE);
}

int game_get_next_number(cgame g, uint i, uint j, direction dir, uint dist) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols || dist > 2) {
    exit(EXIT_FAILURE);
  }
  int sq = game_get_next_square(g, i, j, dir, dist);
  if (sq == -1) {
    return -1;
  }
  if (sq == S_ZERO || sq == S_IMMUTABLE_ZERO) {
    return 0;
  } else if (sq == S_ONE || sq == S_IMMUTABLE_ONE) {
    return 1;
  } else
    return -1;
}

bool game_is_empty(cgame g, uint i, uint j) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    exit(EXIT_FAILURE);
  }
  if (game_get_square(g, i, j) != S_EMPTY) {
    return false;
  }
  return true;
}

bool game_is_immutable(cgame g, uint i, uint j) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    exit(EXIT_FAILURE);
  }
  square sq = game_get_square(g, i, j);
  if (sq == S_IMMUTABLE_ONE || sq == S_IMMUTABLE_ZERO) {
    return true;
  } else {
    return false;
  }
}

int game_has_error(cgame g, uint i, uint j) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    exit(EXIT_FAILURE);
  }
  if (game_get_square(g, i, j) == S_EMPTY) {
    return 0;
  }
  int cpt_ver = 1, cpt_hor = 1;
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, RIGHT, 1)) {
    cpt_hor++;
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, RIGHT, 2)) {
      return -1;
    }
  }
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, LEFT, 1)) {
    cpt_hor++;
    if (cpt_hor > 2) {
      return -1;
    }
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, LEFT, 2)) {
      return -1;
    }
  }
  /* vertical*/
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, UP, 1)) {
    cpt_ver++;
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, UP, 2)) {
      return -1;
    }
  }
  if (game_get_number(g, i, j) == game_get_next_number(g, i, j, DOWN, 1)) {
    cpt_ver++;
    if (cpt_ver > 2) {
      return -1;
    }
    if (game_get_number(g, i, j) == game_get_next_number(g, i, j, DOWN, 2)) {
      return -1;
    }
  }
  int cpt_hor1 = 0, cpt_ver1 = 0;
  for (uint k = 0; k < g->nb_rows; k++) {
    if (game_get_number(g, k, j) == game_get_number(g, i, j)) {
      cpt_hor1++;
    }
    if (game_get_number(g, i, k) == game_get_number(g, i, j)) {
      cpt_ver1++;
    }
  }
  if (cpt_hor1 > (g->nb_rows / 2) || cpt_ver1 > (g->nb_cols / 2)) {
    return -1;
  } else {
    return 0;
  }
}

bool game_check_move(cgame g, uint i, uint j, square s) {
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  if (s == S_IMMUTABLE_ONE || s == S_IMMUTABLE_ZERO || i >= g->nb_rows ||
      j >= g->nb_cols) {
    return false;
  }
  square sq = game_get_square(g, i, j);
  if (sq != S_IMMUTABLE_ONE && sq != S_IMMUTABLE_ZERO) {
    return true;
  } else {
    return false;
  }
}

void game_play_move(game g, uint i, uint j, square s) {
  if (g == NULL || i >= g->nb_rows || j >= g->nb_cols) {
    exit(EXIT_FAILURE);
  }
  if (s == S_IMMUTABLE_ONE && s == S_IMMUTABLE_ONE) {
    exit(EXIT_FAILURE);
  }
  if (game_get_square(g, i, j) != S_IMMUTABLE_ONE &&
      game_get_square(g, i, j) != S_IMMUTABLE_ZERO) {
    game_set_square(g, i, j, s);
  }
}

bool game_is_over(cgame g) {
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  for (uint k = 0; k < g->nb_rows; k++) {
    for (uint l = 0; l < g->nb_cols; l++) {
      if (game_has_error(g, k, l) != 0) {
        return false;
      }
      if (game_get_square(g, k, l) == S_EMPTY) {
        return false;
      }
    }
  }
  return true;
}

void game_restart(game g) {
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  for (uint i = 0; i < g->nb_rows; i++) {
    for (uint j = 0; j < g->nb_cols; j++) {
      if (game_get_square(g, i, j) != S_IMMUTABLE_ONE &&
          game_get_square(g, i, j) != S_IMMUTABLE_ZERO) {
        game_set_square(g, i, j, S_EMPTY);
      }
    }
  }
}


bool game_is_unique(cgame g){
  if(g == NULL){
    exit(EXIT_FAILURE);
  }
  return g->unique;
  }

bool game_is_wrapping(cgame g){
  if(g == NULL){
    exit(EXIT_FAILURE);
  }
    return g->wrapping;
  }

uint game_nb_cols(cgame g){
  if(g == NULL){
    exit(EXIT_FAILURE);
  }
  return g->nb_cols; 
}

uint game_nb_rows(cgame g){
  if(g == NULL){
    exit(EXIT_FAILURE);
  }
  return g->nb_rows; 
}



game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping, bool unique){
  game g = memory_alloc(sizeof(struct game_s));
  g->nb_rows = nb_rows;
  g->nb_cols = nb_cols;
  g->wrapping = wrapping;
  g->unique = unique;
  square* array = memory_alloc((g->nb_rows * g->nb_cols) * sizeof(square));

  for (int i = 0; i < g->nb_rows * g->nb_cols; i++) {
    array[i] = S_EMPTY;
  }
  g->square_array = array;
  return g;

}

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping, bool unique){
  if (squares == NULL) {
    exit(EXIT_FAILURE);
  }
  game new = memory_alloc(sizeof(struct game_s));
  new->nb_rows = nb_rows;
  new->nb_cols = nb_cols;
  new->wrapping = wrapping;
  new->unique = unique;
  square* array = memory_alloc((new->nb_rows* new->nb_cols) * sizeof(square));

  for (int i = 0; i < (new->nb_rows* new->nb_cols); i++) {
    square tmp = squares[i];
    array[i] = tmp;
  }
  new->square_array = array;
  return new;
}