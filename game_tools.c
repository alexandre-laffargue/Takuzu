#include "game_tools.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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