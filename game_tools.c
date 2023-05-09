#include "game_tools.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"

game game_load(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    printf("Error: cannot open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  int rows, cols, wrapping, unique;

  int rFscanf = fscanf(f, " %d %d %d %d", &rows, &cols, &wrapping, &unique);
  rFscanf++;
  game g = game_new_empty_ext(rows, cols, wrapping, unique);

  fgetc(f);
  int i = 0;
  while (!feof(f) && i < rows) {
    for (int j = 0; j < cols; j++) {
      int c = fgetc(f);
      if (c == 119) {  // 119 = w en ASCII
        game_set_square(g, i, j, S_ZERO);
      } else if (c == 98) {  // 98 = b en ASCII
        game_set_square(g, i, j, S_ONE);
      } else if (c == 87) {  // 87 = W en ASCII
        game_set_square(g, i, j, S_IMMUTABLE_ZERO);
      } else if (c == 66) {  // 66 = B en ASCII
        game_set_square(g, i, j, S_IMMUTABLE_ONE);
      }
    }
    fgetc(f);
    i++;
  }
  fclose(f);
  return g;
}

void game_save(cgame g, char *filename) {
  FILE *f = fopen(filename, "w");
  if (f == NULL) {
    printf("Error: cannot open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  char *c;
  int a, b = 0;
  a = fprintf(f, "%d %d %d %d\n", game_nb_rows(g), game_nb_cols(g),
              game_is_wrapping(g), game_is_unique(g));
  for (int i = 0; i < game_nb_rows(g); i++) {
    for (int j = 0; j < game_nb_cols(g); j++) {
      square sq = game_get_square(g, i, j);
      if (sq == S_EMPTY) {
        c = "e";
      }
      if (sq == S_IMMUTABLE_ONE) {
        c = "B";
      }
      if (sq == S_IMMUTABLE_ZERO) {
        c = "W";
      }
      if (sq == S_ONE) {
        c = "b";
      }
      if (sq == S_ZERO) {
        c = "w";
      }

      fprintf(f, "%s", c);
    }
    fprintf(f, "\n");
  }
  b += a;
  fclose(f);
}

void game_copy_2(cgame g, game g2) {
  for (int i = 0; i < game_nb_rows(g); i++) {
    for (int j = 0; j < game_nb_cols(g); j++) {
      game_set_square(g2, i, j, game_get_square(g, i, j));
    }
  }
}

bool game_build_solution(game g, uint i, uint j, game solu) {
  bool retour1 = false;
  bool retour2 = false;

  if (j == game_nb_cols(g)) {
    i++;
    j = 0;
  }

  while (game_get_square(g, i, j) == S_IMMUTABLE_ONE ||
         game_get_square(g, i, j) == S_IMMUTABLE_ZERO) {
    if ((j + 1) < game_nb_cols(g)) {
      j++;
    } else if (((j + 1) == game_nb_cols(g)) && ((i + 1) < game_nb_rows(g))) {
      i++;
      j = 0;
    } else {  // derniere case du tableau
      if (game_is_over(g)) {
        game_copy_2(g, solu);
        return true;
      }
      return false;
    }
  }
  // dernière case du tableau
  if (((j + 1) == game_nb_cols(g)) && ((i + 1) == game_nb_rows(g))) {
    game_set_square(g, i, j, S_ONE);
    if (game_is_over(g)) {
      game_copy_2(g, solu);
      retour1 = true;
    }
    if (!retour1) {
      game_set_square(g, i, j, S_ZERO);
      if (game_is_over(g)) {
        game_copy_2(g, solu);
        retour2 = true;
      }
    }
  } else {  // toutes les autres cases
    game_set_square(g, i, j, S_ONE);
    if (game_has_error(g, i, j) == 0) {
      retour1 = game_build_solution(g, i, j + 1, solu);
    }
    if (!retour1) {
      game_set_square(g, i, j, S_ZERO);
      if (game_has_error(g, i, j) == 0) {
        retour2 = game_build_solution(g, i, j + 1, solu);
      }
    }
  }
  game_set_square(g, i, j, S_EMPTY);
  return retour1 || retour2;
}

bool game_solve(game g) {
  if (game_is_over(g)) return true;

  uint i = 0;
  uint j = 0;
  game search = game_copy(g);
  game soluce = game_copy(g);

  bool ret = game_build_solution(search, i, j, soluce);
  if (ret) {
    game_copy_2(soluce, g);
    printf("Il y a une ou plusieurs solutions.\n");
  } else
    printf("Il n'y a pas de solution.\n");
  game_delete(search);
  game_delete(soluce);
  return ret;
}

uint game_build_nb(game g, uint i, uint j) {
  uint rt1 = 0;
  uint rt2 = 0;
  if (j == game_nb_cols(g)) {
    i++;
    j = 0;
  }

  while (game_is_immutable(g, i, j)) {
    if ((j + 1) < game_nb_cols(g)) {
      j++;
    } else if (((j + 1) == game_nb_cols(g)) && ((i + 1) < game_nb_rows(g))) {
      i++;
      j = 0;
    } else {  // derniere case du tableau
      if (game_is_over(g)) {
        return (uint)1;
      }
      return (uint)0;
    }
  }
  // derniere case du tableau
  if (((j + 1) == game_nb_cols(g)) && ((i + 1) == game_nb_rows(g))) {
    game_set_square(g, i, j, S_ONE);
    if (game_is_over(g)) {
      rt1 = (uint)1;
    }
    game_set_square(g, i, j, S_ZERO);
    if (game_is_over(g)) {
      rt2 = (uint)1;
    }
  } else {  // toutes les autres cases
    game_set_square(g, i, j, S_ONE);
    if (game_has_error(g, i, j) == 0) {
      rt1 = game_build_nb(g, i, j + 1);
    }
    game_set_square(g, i, j, S_ZERO);
    if (game_has_error(g, i, j) == 0) {
      rt2 = game_build_nb(g, i, j + 1);
    }
  }
  game_set_square(g, i, j, S_EMPTY);
  return (rt1 + rt2);
}

uint game_nb_solutions(cgame g) {
  uint i = 0;
  uint j = 0;
  game gs = game_copy(g);

  uint ret = game_build_nb(gs, i, j);
  game_delete(gs);
  printf("Il y a %d solution(s).\n", ret);
  return ret;
}

/* ************************************************************************** */
/*                            Random Game Generator                           */
/* ************************************************************************** */

static game game_set_some_mutable_squares(game g, uint nb_empty)
{
  assert(g);
  uint nb_rows = game_nb_rows(g);
  uint nb_cols = game_nb_cols(g);
  uint nb_squares = nb_rows * nb_cols;
  assert(nb_empty <= nb_squares);
  uint nb_empty1 = nb_empty;
  while (nb_empty1 > 0) {
    uint pos = rand() % nb_squares;
    uint row = pos / nb_cols;
    uint col = pos % nb_cols;
    if (game_is_immutable(g, row, col)) {
      square s = game_get_number(g, row, col);
      game_set_square(g, row, col, s + 1);
      nb_empty1--;
    }
  }
  return g;
}

/* ************************************************************************** */

static void game_flip_one_square(game g, int i, int j)
{
  square s = game_get_square(g, i, j);
  if (s == S_IMMUTABLE_ONE)
    game_set_square(g, i, j, S_IMMUTABLE_ZERO);
  else
    game_set_square(g, i, j, S_IMMUTABLE_ONE);
}

/* ************************************************************************** */

static bool try_flip(game g, int i1, int j1, int i2, int j2)
{
  if (i1 == i2 && j1 == j2) return false;
  assert(game_is_over(g));
  square s11 = game_get_square(g, i1, j1);
  square s22 = game_get_square(g, i2, j2);
  square s12 = game_get_square(g, i1, j2);
  square s21 = game_get_square(g, i2, j1);

  if (s11 == s22 && s12 == s21 && s11 != s12) {
    game_flip_one_square(g, i1, j1);
    game_flip_one_square(g, i2, j2);
    game_flip_one_square(g, i1, j2);
    game_flip_one_square(g, i2, j1);

    if (game_is_over(g)) {
      return true;
    } else {  // undo
      game_flip_one_square(g, i1, j1);
      game_flip_one_square(g, i2, j2);
      game_flip_one_square(g, i1, j2);
      game_flip_one_square(g, i2, j1);
      assert(game_is_over(g));
      return false;
    }
  }
  return false;
}

/* ************************************************************************** */

static void apply_nb_flips(game g, uint nb)
{
  uint nb_rows = game_nb_rows(g);
  uint nb_cols = game_nb_cols(g);
  while (nb > 0) {
    uint i1 = rand() % nb_rows;
    uint j1 = rand() % nb_cols;
    uint i2 = rand() % nb_rows;
    uint j2 = rand() % nb_cols;
    if (try_flip(g, i1, j1, i2, j2)) nb--;
  }
}

/* ************************************************************************** */

game game_random(uint nb_rows, uint nb_cols, bool wrapping, uint uniq, bool with_solution)
{
  // step 0: create an empty game
  game g = game_new_empty_ext(nb_rows, nb_cols, wrapping, uniq);

  // fill the grid with initial values
  for (uint i = 0; i < nb_rows; i++)
    for (uint j = 0; j < nb_cols; j++) game_set_square(g, i, j, (i + j) % 2 + 3);

  // Make it unique if it is square
  if (nb_cols == nb_rows) {
    for (uint i = 0; i < nb_rows / 2; i++) {
      game_flip_one_square(g, 2 * i, 2 * i);
      game_flip_one_square(g, 2 * i, 2 * i + 1);
      game_flip_one_square(g, 2 * i + 1, 2 * i);
      game_flip_one_square(g, 2 * i + 1, 2 * i + 1);
    }
  }
  assert(game_is_over(g));
  // apply some flips
  apply_nb_flips(g, nb_rows * nb_cols * 10);

  assert(game_is_over(g));
  // check

  game_set_some_mutable_squares(g, (nb_rows * nb_cols * 1) / 2);
  if (!with_solution) game_restart(g);
  return g;
}

/* ************************************************************************** */
